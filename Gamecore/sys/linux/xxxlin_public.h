
#ifndef __LINUX_LOCAL_H__
#define __LINUX_LOCAL_H__

/*
===============================================================================

	Non-portable system services.

===============================================================================
*/
#include "SGF_Config.h"
#include "util/SGF_UtilStructs.h"
#ifndef _WIN32  //Todo  verificar corretamente se é linux

namespace SGF {
  
typedef struct {
/*	HWND			hWnd;
	HINSTANCE		hInstance;

	bool			activeApp;		// changed with WM_ACTIVATE messages
	bool			mouseReleased;		// when the game has the console down or is doing a long operation
	bool			movingWindow;		// inhibit mouse grab when dragging the window
	bool			mouseGrabbed;		// current state of grab and hide

	OSVERSIONINFOEX	osversion;

	cpuid_t			cpuid;

	// when we get a windows message, we store the time off so keyboard processing
	// can know the exact time of an event (not really needed now that we use async direct input)
	int				sysMsgTime;

	bool			windowClassRegistered;

	WNDPROC			wndproc;

	HDC				hDC;							// handle to device context
	HGLRC			hGLRC;						// handle to GL rendering context
	PIXELFORMATDESCRIPTOR pfd;		
	int				pixelformat;

	HINSTANCE		hinstOpenGL;	// HINSTANCE for the OpenGL library

	int				desktopBitsPixel;
	int				desktopWidth, desktopHeight;

	bool			cdsFullscreen;

	FILE			*log_fp;

	unsigned short	oldHardwareGamma[3][256];
	// desktop gamma is saved here for restoration at exit
*/
	/*
	static CSysVar	sys_arch;
	static CSysVar	sys_cpustring;
	static CSysVar	in_mouse;
	static CSysVar	win_allowAltTab;
	static CSysVar	win_notaskkeys;
	static CSysVar	win_username;
	static CSysVar	win_xpos;			// archived X coordinate of window position
	static CSysVar	win_ypos;			// archived Y coordinate of window position
	static CSysVar	win_outputDebugString;
	static CSysVar	win_outputEditString;
	static CSysVar	win_viewlog;
	static CSysVar	win_timerUpdate;
	static CSysVar	win_allowMultipleInstances;
	*/
//	CRITICAL_SECTION criticalSections[MAX_CRITICAL_SECTIONS];
/*	HANDLE			backgroundDownloadSemaphore;

	HINSTANCE		hInstDI;			// direct input
		
	HANDLE			renderCommandsEvent;
	HANDLE			renderCompletedEvent;
	HANDLE			renderActiveEvent;
	HANDLE			renderThreadHandle;
	unsigned long	renderThreadId;
	void			(*glimpRenderThread)();
	void			*smpData;
	int				wglErrors;
	// SMP acceleration vars
*/
} LinVars_t;

extern LinVars_t	systemInfo;
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

typedef enum {
	FPU_ROUNDING_TO_NEAREST				= 0,
	FPU_ROUNDING_DOWN					= 1,
	FPU_ROUNDING_UP						= 2,
	FPU_ROUNDING_TO_ZERO				= 3
} fpuRounding_t;

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


void			Sys_Init();
void			Sys_Shutdown();


bool			Sys_AlreadyRunning();

// note that this isn't journaled...
char *			Sys_GetClipboardData();
void			Sys_SetClipboardData( const char *string );

// will go to the various text consoles
// NOT thread safe - never use in the async paths
void			Sys_Printf( const char *msg, ... )id_attribute((format(printf,1,2)));

// guaranteed to be thread-safe
void			Sys_DebugPrintf( const char *fmt, ... )id_attribute((format(printf,1,2)));
void			Sys_DebugVPrintf( const char *fmt, va_list arg );

// a decent minimum sleep time to avoid going below the process scheduler speeds
#define			SYS_MINSLEEP	20

// allow game to yield CPU time
// NOTE: due to SYS_MINSLEEP this is very bad portability karma, and should be completely removed
void			Sys_Sleep( int msec );

// Sys_Milliseconds should only be used for profiling purposes,
// any game related timing information should come from event timestamps
int				Sys_Milliseconds();

// for accurate performance testing
double			Sys_GetClockTicks();
double			Sys_ClockTicksPerSecond();

// returns a selection of the CPUID_* flags
cpuid_t			Sys_GetProcessorId();
const char *		Sys_GetProcessorString();

// returns true if the FPU stack is empty
bool			Sys_FPU_StackIsEmpty();

// empties the FPU stack
void			Sys_FPU_ClearStack();

// returns the FPU state as a string
const char *	Sys_FPU_GetState();

// enables the given FPU exceptions
void		Sys_FPU_EnableExceptions( int exceptions );

// sets the FPU precision
void		Sys_FPU_SetPrecision( int precision );

// sets the FPU rounding mode
void		Sys_FPU_SetRounding( int rounding );

// sets Flush-To-Zero mode (only available when CPUID_FTZ is set)
void		Sys_FPU_SetFTZ( bool enable );

// sets Denormals-Are-Zero mode (only available when CPUID_DAZ is set)
void		Sys_FPU_SetDAZ( bool enable );

// returns amount of system ram
int		Sys_GetSystemRam();

// returns amount of video ram
int		Sys_GetVideoRam();

// returns amount of drive space in path
int		Sys_GetDriveFreeSpace( const char *path );

// returns memory stats
void		Sys_GetCurrentMemoryStatus( sysMemoryStats_t &stats );
void		Sys_GetExeLaunchMemoryStatus( sysMemoryStats_t &stats );

// lock and unlock memory
bool		Sys_LockMemory( void *ptr, int bytes );
bool		Sys_UnlockMemory( void *ptr, int bytes );

// set amount of physical work memory
void		Sys_SetPhysicalWorkMemory( int minBytes, int maxBytes );

// allows retrieving the call stack at execution points
void		Sys_GetCallStack( address_t *callStack, const int callStackSize );
const char *	Sys_GetCallStackStr( const address_t *callStack, const int callStackSize );
const char *	Sys_GetCallStackCurStr( int depth );
const char *	Sys_GetCallStackCurAddressStr( int depth );
void		Sys_ShutdownSymbols();

// DLL loading, the path should be a fully qualified OS path to the DLL file to be loaded
int			Sys_DLL_Load( const char *dllName );
void *			Sys_DLL_GetProcAddress( int dllHandle, const char *procName );
void			Sys_DLL_Unload( int dllHandle );


void			Sys_Mkdir( const char *path );
//ID_TIME_T		Sys_FileTimeStamp( FILE *fp );
// NOTE: do we need to guarantee the same output on all platforms?
//const char *	Sys_TimeStampToStr( ID_TIME_T timeStamp );
const char *	Sys_DefaultCDPath();
const char *	Sys_DefaultBasePath();
const char *	Sys_DefaultSavePath();
const char *	Sys_EXEPath();

// use fs_debug to verbose Sys_ListFiles
// returns -1 if directory was not found (the list is cleared)
int			Sys_ListFiles( const char *directory, const char *extension, CList<class CMyString> &list );

// know early if we are performing a fatal error shutdown so the error message doesn't get lost
void			Sys_SetFatalError( const char *error );

// display perference dialog
void			Sys_DoPreferences();




/*
==============================================================

	Multi-threading

==============================================================
*/
#if 0
typedef unsigned int (*xthread_t)( void * );

typedef enum {
	THREAD_NORMAL,
	THREAD_ABOVE_NORMAL,
	THREAD_HIGHEST
} xthreadPriority;

typedef struct {
	const char *	name;
	int				threadHandle;
	unsigned long	threadId;
} xthreadInfo;

const int MAX_THREADS				= 10;
extern xthreadInfo *g_threads[MAX_THREADS];
extern int			g_thread_count;

void				Sys_CreateThread( xthread_t function, void *parms, xthreadPriority priority, xthreadInfo &info, const char *name, xthreadInfo *threads[MAX_THREADS], int *thread_count );
void				Sys_DestroyThread( xthreadInfo& info ); // sets threadHandle back to 0

// find the name of the calling thread
// if index != NULL, set the index in g_threads array (use -1 for "main" thread)
const char *		Sys_GetThreadName( int *index = 0 );
 
const int MAX_CRITICAL_SECTIONS		= 4;

enum {
	CRITICAL_SECTION_ZERO = 0,
	CRITICAL_SECTION_ONE,
	CRITICAL_SECTION_TWO,
	CRITICAL_SECTION_THREE
};

void				Sys_EnterCriticalSection( int index = CRITICAL_SECTION_ZERO );
void				Sys_LeaveCriticalSection( int index = CRITICAL_SECTION_ZERO );

const int MAX_TRIGGER_EVENTS		= 4;

enum {
	TRIGGER_EVENT_ZERO = 0,
	TRIGGER_EVENT_ONE,
	TRIGGER_EVENT_TWO,
	TRIGGER_EVENT_THREE
};

void				Sys_WaitForEvent( int index = TRIGGER_EVENT_ZERO );
void				Sys_TriggerEvent( int index = TRIGGER_EVENT_ZERO );


#endif
} //end SGF



#endif _WIN32
#endif
