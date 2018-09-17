

#ifndef __SYS_SGF_PUBLIC__
#define __SYS_SGF_PUBLIC__

/*
===============================================================================

	Non-portable system services.

===============================================================================
*/
#include "../SGF_Config.h"
#include "util/SGF_UtilStructs.h"
#include "../SGF_System.h"
#ifdef _WIN32
#include  <Windows.h>



namespace SGF {
namespace System{  
typedef struct {
	HWND			hWnd;
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
	HANDLE			backgroundDownloadSemaphore;

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

} Win32Vars_t;

extern Win32Vars_t	win32;

} //end system
} //end SGF
#endif // end WIN
#endif /* !__SYS_PUBLIC__ */
