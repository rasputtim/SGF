

#ifndef _SGF_SYSTEM_MINGW__
#define _SGF_SYSTEM_MINGW__

/*
===============================================================================

	Lots of Non-portable system services.

===============================================================================
*/
/* system utilities */
#include <stdint.h>

#include <string>
#include "../SGF_Config.h"
#include "../util/SGF_UtilStructs.h"
namespace SGF {
namespace System {

typedef enum {
	FPU_ROUNDING_TO_NEAREST				= 0,
	FPU_ROUNDING_DOWN					= 1,
	FPU_ROUNDING_UP						= 2,
	FPU_ROUNDING_TO_ZERO				= 3
} fpuRounding_t;
typedef enum {
	FPU_EXCEPTION_INVALID_OPERATION		= 1,
	FPU_EXCEPTION_DENORMALIZED_OPERAND	= 2,
	FPU_EXCEPTION_DIVIDE_BY_ZERO		= 4,
	FPU_EXCEPTION_NUMERIC_OVERFLOW		= 8,
	FPU_EXCEPTION_NUMERIC_UNDERFLOW		= 16,
	FPU_EXCEPTION_INEXACT_RESULT		= 32
} fpuExceptions_t;

typedef enum {
	FPU_PRECISION_SINGLE				= 0,
	FPU_PRECISION_DOUBLE				= 1,
	FPU_PRECISION_DOUBLE_EXTENDED		= 2
} fpuPrecision_t;
typedef struct sysMemoryStats_s {
	int memoryLoad;
	int totalPhysical;
	int availPhysical;
	int totalPageFile;
	int availPageFile;
	int totalVirtual;
	int availVirtual;
	int availExtendedVirtual;
} sysMemoryStats_t;

typedef unsigned long address_t;

template<class type> class CList;		// for Sys_ListFiles

        uint64_t currentMicroseconds();
		unsigned long memoryUsage();
		uint64_t currentSeconds();



class CSys {
public:
	virtual void		DebugPrintf( const char *fmt, ... )id_attribute((format(printf,2,3))) = 0;
	virtual void		DebugVPrintf( const char *fmt, va_list arg ) = 0;

	virtual double		GetClockTicks() = 0;
	virtual double		ClockTicksPerSecond() = 0;
	virtual cpuid_t		GetProcessorId() = 0;
	virtual const char *	GetProcessorString() = 0;
	virtual const char *	FPU_GetState() = 0;
	virtual bool		FPU_StackIsEmpty() = 0;
	virtual void		FPU_SetFTZ( bool enable ) = 0;
	virtual void		FPU_SetDAZ( bool enable ) = 0;

	virtual void		FPU_EnableExceptions( int exceptions ) = 0;

	virtual bool		LockMemory( void *ptr, int bytes ) = 0;
	virtual bool		UnlockMemory( void *ptr, int bytes ) = 0;

	//virtual void		GetCallStack( address_t *callStack, const int callStackSize ) = 0;
	//virtual const char *	GetCallStackStr( const address_t *callStack, const int callStackSize ) = 0;
	virtual const char *	GetCallStackCurStr( int depth ) = 0;
	virtual void			ShutdownSymbols() = 0;
#ifdef _WIN32
	virtual void *		DLL_Load( const char *dllName ) = 0;
	virtual void *		DLL_GetProcAddress( void * dllHandle, const char *procName ) = 0;
	virtual void		DLL_Unload( void * dllHandle ) = 0;
	virtual void		DLL_GetFileName( const char *baseName, char *dllName, int maxLength ) = 0;
#endif
	//virtual void		OpenURL( const char *url, bool quit ) = 0;
	//virtual void		StartProcess( const char *exePath, bool quit ) = 0;
};

class CSysLocal : public CSys {
public:
	virtual void		DebugPrintf( const char *fmt, ... )id_attribute((format(printf,2,3)));
	virtual void		DebugVPrintf( const char *fmt, va_list arg );

	virtual double		GetClockTicks();
	virtual double		ClockTicksPerSecond();
	virtual cpuid_t		GetProcessorId();
	virtual const char *	GetProcessorString();
	virtual const char *	FPU_GetState();
	virtual bool		FPU_StackIsEmpty();
	virtual void		FPU_SetFTZ( bool enable );
	virtual void		FPU_SetDAZ( bool enable );

	virtual void		FPU_EnableExceptions( int exceptions );

//	virtual void		GetCallStack( address_t *callStack, const int callStackSize );
//	virtual const char *	GetCallStackStr( const address_t *callStack, const int callStackSize );
	virtual const char *	GetCallStackCurStr( int depth );
	virtual void		ShutdownSymbols();

	virtual bool		LockMemory( void *ptr, int bytes );
	virtual bool		UnlockMemory( void *ptr, int bytes );

	virtual void *		DLL_Load( const char *dllName );
	virtual void *		DLL_GetProcAddress( void * dllHandle, const char *procName );
	virtual void		DLL_Unload( void * dllHandle );
	virtual void		DLL_GetFileName( const char *baseName, char *dllName, int maxLength );


	//virtual void		OpenURL( const char *url, bool quit );
	//virtual void		StartProcess( const char *exeName, bool quit );
};
void		Sys_Init();
void		Sys_Shutdown();


bool		Sys_AlreadyRunning();

#ifdef _WIN32
// note that this isn't journaled...
char *		Sys_GetClipboardData();
void		Sys_SetClipboardData( const char *string );
#endif

// a decent minimum sleep time to avoid going below the process scheduler speeds
#define			SYS_MINSLEEP	20

// Sys_Milliseconds should only be used for profiling purposes,
// any game related timing information should come from event timestamps
// return the elapsed time in mileseconds from the first running of the function.
int		getElapsedMilliseconds();

// for accurate performance testing
/*
 * Using the "rdtsc"
This method use rdtsc.
rdtsc is a time stamp counter that returns  the number of clock ticks from the time the system was last reset.
The rdtsc instruction returns the time stamp counter in EDX:EAX.

This instruction is useful when you want to measure the performance of a certain code or application in clock ticks,
or compare the performance of two programs, which are too small to be counted in seconds.*/
double		getClockTicks();
double		getClockTicksPerSecond();

// returns a selection of the CPUID_* flags
cpuid_t		getProcessorId();
const char *	getProcessorString();


//=======================================
// FLOAT Point UNIT
//=======================================
// returns true if the FPU stack is empty
bool		fpu_StackIsEmpty();

// empties the FPU stack
void		fpu_ClearStack();

// returns the FPU state as a string
const char *	Sys_FPU_GetState();

// enables the given FPU exceptions
// FE_DIVBYZERO, FE_INEXACT, FE_INVALID, FE_OVERFLOW, FE_UNDERFLOW
void		fpu_EnableExceptions( int exceptions );
void 		fpu_DisableExceptions( int exceptions );

// sets the FPU precision
/*
The PC field (bits 9 and 8) or Precision Control determines to what precision the FPU rounds results after each arithmetic instruction in one of three ways:

00 = 24 bits (REAL4)
01 = Not used
10 = 53 bits (REAL8)
11 = 64 bits (REAL10) (this is the initialized state)
*/
void		fpu_SetPrecision( int precision );

// sets the FPU rounding mode
/*The RC field (bits 11 and 10) or Rounding Control determines how the FPU will round results in one of four ways:

00 = Round to nearest, or to even if equidistant (this is the initialized state)
01 = Round down (toward -infinity)
10 = Round up (toward +infinity)
11 = Truncate (toward 0)
*/

#if defined(WIN32)  && defined(_MSC_VER)

// x87 fpu
#define getx87cr(x)    __asm fnstcw x;
#define setx87cr(x)    __asm fldcw x;
#define getx87sr(x)    __asm fnstsw x;

// SIMD, gcc with Intel Core 2 Duo uses SSE2(4)
#define getmxcsr(x)   __asm stmxcsr   x;
#define setmxcsr(x)    __asm ldmxcsr   x;

#define saveFX(fx,err)  __asm fxsave   state ;
#define loadFX(fx)	__asm __asm ldmxcsr   x;
#else
// x87 fpu
#define getx87cr(x)    asm ("fnstcw %0" : "=m" (x));
#define setx87cr(x)    asm ("fldcw %0"  : "=m" (x));
#define getx87sr(x)    asm ("fnstsw %0" : "=m" (x));
// SIMD, gcc with Intel Core 2 Duo uses SSE2(4)
#define getmxcsr(fx)    asm volatile("stmxcsr %0" : "=m" (fx));
#define setmxcsr(fx)    asm volatile("ldmxcsr %0" : "=m" (fx));

#define saveFX(fx,err)      asm volatile("fxsave (%[fxx])\n\t" : [err] "=r" (err): [fxx] "r" (fx));
#endif
void	fpu_SetRounding( int16_t rounding );
int16_t	fpu_getRounding( int16_t rounding );

// http://software.intel.com/en-us/articles/x87-and-sse-floating-point-assists-in-ia-32-flush-to-zero-ftz-and-denormals-are-zero-daz
//set CPUID_FTZ and enable/disable FTZ
void    fpu_enableFTZ();
void 	fpu_disableFTZ();
// sets Flush-To-Zero mode (only available when CPUID_FTZ is set)
void	fpu_SetFTZ( bool enable );

// set CPUID_DAZ and enable/disable DAZ
void	fpu_enableDAZ();
void    fpu_disableDAZ();
// sets Denormals-Are-Zero mode (only available when CPUID_DAZ is already set)
void	fpu_SetDAZ( bool enable );

//================================================
//  END FPU
//=================================================
// returns amount of system ram
int		getSystemRam();

// returns amount of video ram
int		getVideoRam();

// returns amount of drive space in path
int		Sys_GetDriveFreeSpace( const char *path );

// returns memory stats
void		getCurrentMemoryStatus( sysMemoryStats_t &stats );
void		getExeLaunchMemoryStatus( sysMemoryStats_t &stats );

// lock and unlock memory
/*Locks the specified region of the process's virtual address space into physical memory, 
ensuring that subsequent access to the region will not incur a page fault.
*/
bool		lockMemory( void *ptr, int bytes );
bool		unlockMemory( void *ptr, int bytes );
char *getCurrentUser(); //return the current username

// allows retrieving the call stack at execution points
void		Sys_GetCallStack( address_t *callStack, const int callStackSize );
const char *	Sys_GetCallStackStr( const address_t *callStack, const int callStackSize );
const char *	Sys_GetCallStackCurStr( int depth );
const char *	Sys_GetCallStackCurAddressStr( int depth );
void		Sys_ShutdownSymbols();

/**
 *  This function dynamically loads a shared object and returns a pointer
 *  to the object handle (or NULL if there was an error).
 *  The 'dllName' parameter is a system dependent name of the object file.
 * DLL loading, the path should be a fully qualified OS path to the DLL file to be loaded
 */
void *		Sys_DLL_Load( const char *dllName );
/**
 *  Given an object handle, this function looks up the address of the
 *  named function in the shared object and returns it.  This address
 *  is no longer valid after calling Sys_DLL_Unload.
 */
void *	Sys_DLL_GetProcAddress( void * dllHandle, const char *procName );
/**
 *  Unload a shared object from memory.
 */
void	Sys_DLL_Unload( void * dllHandle );


void		Sys_Mkdir( const char *path );
//ID_TIME_T	Sys_FileTimeStamp( FILE *fp );
// NOTE: do we need to guarantee the same output on all platforms?
const char *	timeStampToStr( time_t timeStamp );

// use fs_debug to verbose Sys_ListFiles
// returns -1 if directory was not found (the list is cleared)
int				Sys_ListFiles( const char *directory, const char *extension, CList<class CMyString> &list );

// know early if we are performing a fatal error shutdown so the error message doesn't get lost
void			Sys_SetFatalError( const char *error );

// display perference dialog
void			Sys_DoPreferences();


} //end Global
} //end SGF
#endif /* !__SYS_PUBLIC__ */
