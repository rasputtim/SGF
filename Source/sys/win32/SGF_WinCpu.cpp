

#if defined(_WIN32) && defined(_MSC_VER)
#include "sys/win32/win_public.h"
#include "util/SGF_Heap.h"
namespace SGF{
namespace System{
/*
==============================================================

	Clock ticks

==============================================================
*/

/*
================
getClockTicks
================
*/
double getClockTicks( void ) {
#if 0

	LARGE_INTEGER li;

	QueryPerformanceCounter( &li );
	return = (double ) li.LowPart + (double) 0xFFFFFFFF * li.HighPart;

#else
#if defined(_MSC_VER)
	unsigned long lo, hi;

	__asm {
		push ebx
		xor eax, eax
		cpuid
		rdtsc
		mov lo, eax
		mov hi, edx
		pop ebx
	}
	return (double ) lo + (double) 0xFFFFFFFF * hi;
#endif //#if defined(_MSC_VER)
#endif
}

/*
================
getClockTicksPerSecond
================
*/
double getClockTicksPerSecond( void ) {
	static double ticks = 0;
#if 0

	if ( !ticks ) {
		LARGE_INTEGER li;
		QueryPerformanceFrequency( &li );
		ticks = li.QuadPart;
	}

#else

	if ( !ticks ) {
		HKEY hKey;
		LPBYTE ProcSpeed;
		DWORD buflen, ret;

		if ( !RegOpenKeyEx( HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey ) ) {
			ProcSpeed = 0;
			buflen = sizeof( ProcSpeed );
			ret = RegQueryValueEx( hKey, "~MHz", NULL, NULL, (LPBYTE) &ProcSpeed, &buflen );
			// If we don't succeed, try some other spellings.
			if ( ret != ERROR_SUCCESS ) {
				ret = RegQueryValueEx( hKey, "~Mhz", NULL, NULL, (LPBYTE) &ProcSpeed, &buflen );
			}
			if ( ret != ERROR_SUCCESS ) {
				ret = RegQueryValueEx( hKey, "~mhz", NULL, NULL, (LPBYTE) &ProcSpeed, &buflen );
			}
			RegCloseKey( hKey );
			if ( ret == ERROR_SUCCESS ) {
				ticks = (double) ((unsigned long)ProcSpeed) * 1000000;
			}
		}
	}

#endif
	return ticks;
}


/*
==============================================================

	CPU

==============================================================
*/

/*
================
HasCPUID
================
*/
#if defined(_MSC_VER)
static bool HasCPUID( void ) {
	__asm
	{
		pushfd						// save eflags
		pop		eax
		test	eax, 0x00200000		// check ID bit
		jz		set21				// bit 21 is not set, so jump to set_21
		and		eax, 0xffdfffff		// clear bit 21
		push	eax					// save new value in register
		popfd						// store new value in flags
		pushfd
		pop		eax
		test	eax, 0x00200000		// check ID bit
		jz		good
		jmp		err					// cpuid not supported
set21:
		or		eax, 0x00200000		// set ID bit
		push	eax					// store new value
		popfd						// store new value in EFLAGS
		pushfd
		pop		eax
		test	eax, 0x00200000		// if bit 21 is on
		jnz		good
		jmp		err
	}

err:
	return false;
good:
	return true;
}
#endif
#define _REG_EAX		0
#define _REG_EBX		1
#define _REG_ECX		2
#define _REG_EDX		3
#if defined(_MSC_VER)
/*
================
CPUID
================
*/
static void CPUID( int func, unsigned regs[4] ) {
	unsigned regEAX, regEBX, regECX, regEDX;

	__asm pusha
	__asm mov eax, func
	__asm __emit 00fh
	__asm __emit 0a2h
	__asm mov regEAX, eax
	__asm mov regEBX, ebx
	__asm mov regECX, ecx
	__asm mov regEDX, edx
	__asm popa

	regs[_REG_EAX] = regEAX;
	regs[_REG_EBX] = regEBX;
	regs[_REG_ECX] = regECX;
	regs[_REG_EDX] = regEDX;
}

#endif
/*
================
IsAMD
================
*/
static bool IsAMD( void ) {
	char pstring[16];
	char processorString[13];

	// get name of processor
	CPUID( 0, ( unsigned int * ) pstring );
	processorString[0] = pstring[4];
	processorString[1] = pstring[5];
	processorString[2] = pstring[6];
	processorString[3] = pstring[7];
	processorString[4] = pstring[12];
	processorString[5] = pstring[13];
	processorString[6] = pstring[14];
	processorString[7] = pstring[15];
	processorString[8] = pstring[8];
	processorString[9] = pstring[9];
	processorString[10] = pstring[10];
	processorString[11] = pstring[11];
	processorString[12] = 0;

	if ( strcmp( processorString, "AuthenticAMD" ) == 0 ) {
		return true;
	}
	return false;
}

/*
================
HasCMOV
================
*/
static bool HasCMOV( void ) {
	unsigned regs[4];

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 15 of EDX denotes CMOV existence
	if ( regs[_REG_EDX] & ( 1 << 15 ) ) {
		return true;
	}
	return false;
}

/*
================
Has3DNow
================
*/
static bool Has3DNow( void ) {
	unsigned regs[4];

	// check AMD-specific functions
	CPUID( 0x80000000, regs );
	if ( regs[_REG_EAX] < 0x80000000 ) {
		return false;
	}

	// bit 31 of EDX denotes 3DNow! support
	CPUID( 0x80000001, regs );
	if ( regs[_REG_EDX] & ( 1 << 31 ) ) {
		return true;
	}

	return false;
}

/*
================
HasMMX
================
*/
static bool HasMMX( void ) {
	unsigned regs[4];

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 23 of EDX denotes MMX existence
	if ( regs[_REG_EDX] & ( 1 << 23 ) ) {
		return true;
	}
	return false;
}

/*
================
HasSSE
================
*/
static bool HasSSE( void ) {
	unsigned regs[4];

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 25 of EDX denotes SSE existence
	if ( regs[_REG_EDX] & ( 1 << 25 ) ) {
		return true;
	}
	return false;
}

/*
================
HasSSE2
================
*/
static bool HasSSE2( void ) {
	unsigned regs[4];

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 26 of EDX denotes SSE2 existence
	if ( regs[_REG_EDX] & ( 1 << 26 ) ) {
		return true;
	}
	return false;
}

/*
================
HasSSE3
================
*/
static bool HasSSE3( void ) {
	unsigned regs[4];

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 0 of ECX denotes SSE3 existence
	if ( regs[_REG_ECX] & ( 1 << 0 ) ) {
		return true;
	}
	return false;
}

/*
================
LogicalProcPerPhysicalProc
================
*/
#define NUM_LOGICAL_BITS   0x00FF0000     // EBX[23:16] Bit 16-23 in ebx contains the number of logical
                                          // processors per physical processor when execute cpuid with
                                          // eax set to 1
static unsigned char LogicalProcPerPhysicalProc( void ) {
	unsigned int regebx = 0;
	__asm {
		mov eax, 1
		cpuid
		mov regebx, ebx
	}
	return (unsigned char) ((regebx & NUM_LOGICAL_BITS) >> 16);
}

/*
================
GetAPIC_ID
================
*/
#define INITIAL_APIC_ID_BITS  0xFF000000  // EBX[31:24] Bits 24-31 (8 bits) return the 8-bit unique
                                          // initial APIC ID for the processor this code is running on.
                                          // Default value = 0xff if HT is not supported
static unsigned char GetAPIC_ID( void ) {
	unsigned int regebx = 0;
	__asm {
		mov eax, 1
		cpuid
		mov regebx, ebx
	}
	return (unsigned char) ((regebx & INITIAL_APIC_ID_BITS) >> 24);
}

/*
================
CPUCount

	logicalNum is the number of logical CPU per physical CPU
    physicalNum is the total number of physical processor
	returns one of the HT_* flags
================
*/
#define HT_NOT_CAPABLE				0
#define HT_ENABLED					1
#define HT_DISABLED					2
#define HT_SUPPORTED_NOT_ENABLED	3
#define HT_CANNOT_DETECT			4

int CPUCount( int &logicalNum, int &physicalNum ) {
	int statusFlag;
	SYSTEM_INFO info;

	physicalNum = 1;
	logicalNum = 1;
	statusFlag = HT_NOT_CAPABLE;

	info.dwNumberOfProcessors = 0;
	GetSystemInfo (&info);

	// Number of physical processors in a non-Intel system
	// or in a 32-bit Intel system with Hyper-Threading technology disabled
	physicalNum = info.dwNumberOfProcessors;

	unsigned char HT_Enabled = 0;

	logicalNum = LogicalProcPerPhysicalProc();

	if ( logicalNum >= 1 ) {	// > 1 doesn't mean HT is enabled in the BIOS
		HANDLE hCurrentProcessHandle;
		DWORD  dwProcessAffinity;
		DWORD  dwSystemAffinity;
		DWORD  dwAffinityMask;

		// Calculate the appropriate  shifts and mask based on the
		// number of logical processors.

		unsigned char i = 1, PHY_ID_MASK  = 0xFF, PHY_ID_SHIFT = 0;

		while( i < logicalNum ) {
			i *= 2;
 			PHY_ID_MASK  <<= 1;
			PHY_ID_SHIFT++;
		}

		hCurrentProcessHandle = GetCurrentProcess();
		GetProcessAffinityMask( hCurrentProcessHandle, &dwProcessAffinity, &dwSystemAffinity );

		// Check if available process affinity mask is equal to the
		// available system affinity mask
		if ( dwProcessAffinity != dwSystemAffinity ) {
			statusFlag = HT_CANNOT_DETECT;
			physicalNum = -1;
			return statusFlag;
		}

		dwAffinityMask = 1;
		while ( dwAffinityMask != 0 && dwAffinityMask <= dwProcessAffinity ) {
			// Check if this CPU is available
			if ( dwAffinityMask & dwProcessAffinity ) {
				if ( SetProcessAffinityMask( hCurrentProcessHandle, dwAffinityMask ) ) {
					unsigned char APIC_ID, LOG_ID, PHY_ID;

					Sleep( 0 ); // Give OS time to switch CPU

					APIC_ID = GetAPIC_ID();
					LOG_ID  = APIC_ID & ~PHY_ID_MASK;
					PHY_ID  = APIC_ID >> PHY_ID_SHIFT;

					if ( LOG_ID != 0 ) {
						HT_Enabled = 1;
					}
				}
			}
			dwAffinityMask = dwAffinityMask << 1;
		}

		// Reset the processor affinity
		SetProcessAffinityMask( hCurrentProcessHandle, dwProcessAffinity );

		if ( logicalNum == 1 ) {  // Normal P4 : HT is disabled in hardware
			statusFlag = HT_DISABLED;
		} else {
			if ( HT_Enabled ) {
				// Total physical processors in a Hyper-Threading enabled system.
				physicalNum /= logicalNum;
				statusFlag = HT_ENABLED;
			} else {
				statusFlag = HT_SUPPORTED_NOT_ENABLED;
			}
		}
	}
	return statusFlag;
}

/*
================
HasHTT
================
*/
static bool HasHTT( void ) {
	unsigned regs[4];
	int logicalNum, physicalNum, HTStatusFlag;

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 28 of EDX denotes HTT existence
	if ( !( regs[_REG_EDX] & ( 1 << 28 ) ) ) {
		return false;
	}

	HTStatusFlag = CPUCount( logicalNum, physicalNum );
	if ( HTStatusFlag != HT_ENABLED ) {
		return false;
	}
	return true;
}

/*
================
HasHTT
================
*/
static bool HasDAZ( void ) {
	__declspec(align(16)) unsigned char FXSaveArea[512];
	unsigned char *FXArea = FXSaveArea;
	DWORD dwMask = 0;
	unsigned regs[4];

	// get CPU feature bits
	CPUID( 1, regs );

	// bit 24 of EDX denotes support for FXSAVE
	if ( !( regs[_REG_EDX] & ( 1 << 24 ) ) ) {
		return false;
	}

	memset( FXArea, 0, sizeof( FXSaveArea ) );

	__asm {
		mov		eax, FXArea
		FXSAVE	[eax]
	}

	dwMask = *(DWORD *)&FXArea[28];						// Read the MXCSR Mask
	return ( ( dwMask & ( 1 << 6 ) ) == ( 1 << 6 ) );	// Return if the DAZ bit is set
}
/*
================
Sys_GetCPUId
================
*/
static cpuid_t getCPUId( void ) {
	int flags;

	// verify we're at least a Pentium or 486 with CPUID support
	if ( !HasCPUID() ) {
		return CPUID_UNSUPPORTED;
	}

	// check for an AMD
	if ( IsAMD() ) {
		flags = CPUID_AMD;
	} else {
		flags = CPUID_INTEL;
	}

	// check for Multi Media Extensions
	if ( HasMMX() ) {
		flags |= CPUID_MMX;
	}

	// check for 3DNow!
	if ( Has3DNow() ) {
		flags |= CPUID_3DNOW;
	}

	// check for Streaming SIMD Extensions
	if ( HasSSE() ) {
		flags |= CPUID_SSE | CPUID_FTZ;
	}

	// check for Streaming SIMD Extensions 2
	if ( HasSSE2() ) {
		flags |= CPUID_SSE2;
	}

	// check for Streaming SIMD Extensions 3 aka Prescott's New Instructions
	if ( HasSSE3() ) {
		flags |= CPUID_SSE3;
	}

	// check for Hyper-Threading Technology
	if ( HasHTT() ) {
		flags |= CPUID_HTT;
	}

	// check for Conditional Move (CMOV) and fast floating point comparison (FCOMI) instructions
	if ( HasCMOV() ) {
		flags |= CPUID_CMOV;
	}

	// check for Denormals-Are-Zero mode
	if ( HasDAZ() ) {
		flags |= CPUID_DAZ;
	}

	return (cpuid_t)flags;
}





/*
================
Sys_GetProcessorString
================
*/
const char *getProcessorString( void ) {
	  cpuid_t			cpuid;
	  string string;
		//
	// CPU type
	//
	if (true /* !CMyString::Icmp( win32.sys_cpustring.GetString(), "detect" )*/ ) {


		Debug::debug(Debug::error,__FUNCTION__)<< getClockTicksPerSecond() / 1000000.0f << " MHz "<<endl;

		cpuid = getCPUId();

		string.clear();

		if ( cpuid & CPUID_AMD ) {
			string += "AMD CPU";
		} else if ( cpuid & CPUID_INTEL ) {
			string += "Intel CPU";
		} else if ( cpuid & CPUID_UNSUPPORTED ) {
			string += "unsupported CPU";
		} else {
			string += "generic CPU";
		}

		string += " with ";
		if ( cpuid & CPUID_MMX ) {
			string += "MMX & ";
		}
		if ( cpuid & CPUID_3DNOW ) {
			string += "3DNow! & ";
		}
		if ( cpuid & CPUID_SSE ) {
			string += "SSE & ";
		}
		if ( cpuid & CPUID_SSE2 ) {
            string += "SSE2 & ";
		}
		if ( cpuid & CPUID_SSE3 ) {
			string += "SSE3 & ";
		}
		if ( cpuid & CPUID_HTT ) {
			string += "HTT & ";
		}
//Todo:  StripTrailing
	//s	string.StripTrailing(string.c_str(), " & " );
	//s	string.StripTrailing( " with " );

	} /*else {
		Debug::debug(Debug::math,__FUNCTION__) << "forcing CPU type to " );
		idLexer src( win32.sys_cpustring.GetString(), CMyString::Length( win32.sys_cpustring.GetString() ), "sys_cpustring" );
		idToken token;

		int id = CPUID_NONE;
		while( src.ReadToken( &token ) ) {
			if ( token.Icmp( "generic" ) == 0 ) {
				id |= CPUID_GENERIC;
			} else if ( token.Icmp( "intel" ) == 0 ) {
				id |= CPUID_INTEL;
			} else if ( token.Icmp( "amd" ) == 0 ) {
				id |= CPUID_AMD;
			} else if ( token.Icmp( "mmx" ) == 0 ) {
				id |= CPUID_MMX;
			} else if ( token.Icmp( "3dnow" ) == 0 ) {
				id |= CPUID_3DNOW;
			} else if ( token.Icmp( "sse" ) == 0 ) {
				id |= CPUID_SSE;
			} else if ( token.Icmp( "sse2" ) == 0 ) {
				id |= CPUID_SSE2;
			} else if ( token.Icmp( "sse3" ) == 0 ) {
				id |= CPUID_SSE3;
			} else if ( token.Icmp( "htt" ) == 0 ) {
				id |= CPUID_HTT;
			}
		}
		if ( id == CPUID_NONE ) {
			Debug::debug(Debug::error,__FUNCTION__)<< "WARNING: unknown sys_cpustring: ", win32.sys_cpustring.GetString() );
			id = CPUID_GENERIC;
		}
		win32.cpuid = (cpuid_t) id;
	}
	*/
	return string.c_str();
}



/*
================
Sys_GetProcessorId
================
*/
cpuid_t getProcessorId( void ) {
    return getCPUId();
}

////////////////////////////////////////////////////////////////////////////////////////
//  DLL and CLIPBOARD
//////////////////////////////
/*
================
Sys_GetClipboardData
================
*/
char *Sys_GetClipboardData( void ) {
	char *data = NULL;
	char *cliptext;

	if ( OpenClipboard( NULL ) != 0 ) {
		HANDLE hClipboardData;

		if ( ( hClipboardData = GetClipboardData( CF_TEXT ) ) != 0 ) {
			if ( ( cliptext = (char *)GlobalLock( hClipboardData ) ) != 0 ) {
				data = (char *)Mem_Alloc( GlobalSize( hClipboardData ) + 1 );
				strcpy( data, cliptext );
				GlobalUnlock( hClipboardData );

				strtok( data, "\n\r\b" );
			}
		}
		CloseClipboard();
	}
	return data;
}

/*
================
Sys_SetClipboardData
================
*/
void Sys_SetClipboardData( const char *string ) {
	HGLOBAL HMem;
	char *PMem;

	// allocate memory block
	HMem = (char *)::GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, strlen( string ) + 1 );
	if ( HMem == NULL ) {
		return;
	}
	// lock allocated memory and obtain a pointer
	PMem = (char *)::GlobalLock( HMem );
	if ( PMem == NULL ) {
		return;
	}
	// copy text into allocated memory block
	lstrcpy( PMem, string );
	// unlock allocated memory
	::GlobalUnlock( HMem );
	// open Clipboard
	if ( !OpenClipboard( 0 ) ) {
		::GlobalFree( HMem );
		return;
	}
	// remove current Clipboard contents
	EmptyClipboard();
	// supply the memory handle to the Clipboard
	SetClipboardData( CF_TEXT, HMem );
	HMem = 0;
	// close Clipboard
	CloseClipboard();
}

/*
========================================================================

DLL Loading

========================================================================
*/
static const int		MAX_OSPATH					= 256;
#define INTSIGNBITNOTSET(i)		((~((const unsigned long)(i))) >> 31)
/*
================
CMyString::IcmpPath
================
*/
static int IcmpPath( const char *s1, const char *s2 ) {
	int c1, c2, d;

#if 0
//#if !defined( _WIN32 )
	Debug::debug(Debug::math,__FUNCTION__) << "WARNING: IcmpPath used on a case-sensitive filesystem?\n" );
#endif

	do {
		c1 = *s1++;
		c2 = *s2++;

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c1 == '\\' ) {
				d += ('/' - '\\');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 == '\\' ) {
				d -= ('/' - '\\');
				if ( !d ) {
					break;
				}
			}
			// make sure folders come first
			while( c1 ) {
				if ( c1 == '/' || c1 == '\\' ) {
					break;
				}
				c1 = *s1++;
			}
			while( c2 ) {
				if ( c2 == '/' || c2 == '\\' ) {
					break;
				}
				c2 = *s2++;
			}
			if ( c1 && !c2 ) {
				return -1;
			} else if ( !c1 && c2 ) {
				return 1;
			}
			// same folder depth so use the regular compare
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;
}

/*
=====================
Sys_DLL_Load
=====================
*/
void * Sys_DLL_Load( const char *dllName ) {
	HINSTANCE	libHandle;
	libHandle = LoadLibrary( dllName );
	if ( libHandle ) {
		// since we can't have LoadLibrary load only from the specified path, check it did the right thing
		char loadedPath[ MAX_OSPATH ];
		GetModuleFileName( libHandle, loadedPath, sizeof( loadedPath ) - 1 );
		if ( IcmpPath( dllName, loadedPath ) ) {
			Debug::debug(Debug::error,__FUNCTION__)<< "ERROR: LoadLibrary "<< dllName<<" wants to load :"<< loadedPath <<endl;
			Sys_DLL_Unload( (void *)libHandle );
			return 0;
		}
	}
	return (void *)libHandle;
}

/*
=====================
Sys_DLL_GetProcAddress
=====================
*/
void *Sys_DLL_GetProcAddress( void * dllHandle, const char *procName ) {
	return GetProcAddress( (HINSTANCE)dllHandle, procName );
}

/*
=====================
Sys_DLL_Unload
=====================
*/
void Sys_DLL_Unload( void * dllHandle ) {
	if ( !dllHandle ) {
		return;
	}
	if ( FreeLibrary( (HINSTANCE)dllHandle ) == 0 ) {
		int lastError = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER,
		    NULL,
			lastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL
		);
		//s Sys_Error( "Sys_DLL_Unload: FreeLibrary failed - %s (%d)", lpMsgBuf, lastError );
	}
}

} //end Global
} //end SGF

#endif //_WIN32
