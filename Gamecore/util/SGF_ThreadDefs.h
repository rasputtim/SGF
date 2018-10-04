/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */
#ifndef _S_G_F_thread_DEFh
#define _S_G_F_thread_DEFh
#include <map>
#include "../SGF_Config.h"
#include "../exceptions/all.h"
#include "SGF_Util.h"
#include "SGF_Task.h"


#if defined(USE_SDL_THREADS) && !defined(USE_NACL)
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../../ExternalLibs/SDL2/include/SDL_thread.h"
#include "../../ExternalLibs/SDL2/include/SDL_mutex.h"
#ifdef WINDOWS
#include <windows.h>
#include <stdio.h>
#endif
#else

#ifndef WINDOWS
#if defined(WIN32) || defined(WIN64)
#define WINDOWS
#endif
#endif

#ifndef WINDOWS
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
typedef unsigned char bool;
#define true 1
#define false 0
typedef long DWORD;
typedef void *LPVOID;
#else
//#include "afx.h"
#include <windows.h>
#include <stdio.h>
#endif


#endif
using namespace std;

namespace SGF {

namespace Util{

/* Either uses pthreads or SDL_thread */

namespace Thread{
#define QUEUE_SIZE 100
#define DEFAULT_STACK_SIZE 0
#define NO_ERRORS			       0
#define MUTEX_CREATION		       0x01
#define EVENT_CREATION		       0x02
#define THREAD_CREATION		       0x04
#define UNKNOWN					   0x08
#define ILLEGAL_USE_OF_EVENT       0x10
#define MEMORY_FAULT               0x20
#define EVENT_AND_TYPE_DONT_MATCH  0x40
#define STACK_OVERFLOW             0x80
#define STACK_EMPTY                0x100
#define STACK_FULL                 0x200

#ifdef USE_SDL_THREADS
    typedef SDL_mutex* Lock;
    typedef SDL_Thread* ThreadId_t;
    typedef int (*ThreadFunction)(void*);
    typedef SDL_cond* Condition;
	#define INFINITE            0xFFFFFFFF  // Infinite timeout
	typedef bool ThreadHandle;
    // typedef SDL_semaphore* Semaphore;
#else
 
   
#ifdef WINDOWS
	typedef CONDITION_VARIABLE  Condition;
	typedef HANDLE Lock;
	typedef HANDLE ThreadHandle;
	Lock m_mutex;
	#ifdef USE_BEGIN_THREAD
	typedef unsigned  (__stdcall*ThreadFunction)(LPVOID lpvData);
	#else
	#define ThreadFunction LPTHREAD_START_ROUTINE
	typedef DWORD (__stdcall *ThreadFunction) (LPVOID lpvData);
	#endif
#if defined(AS400) || defined(OS400)
	typedef pthread_id_np_t ThreadId_t;
	typedef pthread_t ThreadHandle;
	#elif defined(VMS) 
	typedef pthread_t ThreadId_t;
	typedef pthread_t ThreadHandle;
	#else
		#ifdef USE_BEGIN_THREAD
		typedef unsigned ThreadId_t;
		#else
		typedef DWORD ThreadId_t;
		#endif
	#endif
#else
	typedef pthread_t ThreadHandle;
	typedef pthread_cond_t Condition;
	pthread_mutex_t Lock;
	Lock m_mutex;
	typedef void * (*ThreadFunction)(void*);
#endif
   
 
#endif

/* Makes the use of the named threads easier */
typedef map< string, ThreadId_t> NamedThread;




typedef enum {
	ThreadStateBusy,               // thread is currently handling a task
	ThreadStateWaiting,            // thread is waiting for something to do
    ThreadStateDown,               // thread is not running
    ThreadStateShuttingDown,       // thread is in the process of shutting down
    ThreadStateFault               // an error has occured and the thread could not
	                               // be launched
} ThreadState_t;

typedef enum {
	ThreadTypeHomogeneous,
	ThreadTypeSpecialized,
    ThreadTypeIntervalDriven,
    ThreadTypeNotDefined } ThreadType_t;

typedef enum {
	TaskStatusNotSubmitted,
	TaskStatusWaitingOnQueue,
	TaskStatusBeingProcessed,
	TaskStatusCompleted } TaskStatus_t;
#ifdef USE_SDL_THREADS
typedef enum {
ThreadPriorityAboveNormal=SDL_THREAD_PRIORITY_NORMAL,
ThreadPriorityBelowNormal=SDL_THREAD_PRIORITY_LOW,
ThreadPriorityHighest=SDL_THREAD_PRIORITY_HIGH,
ThreadPriorityIdle=SDL_THREAD_PRIORITY_LOW,
ThreadPriorityLowest =SDL_THREAD_PRIORITY_LOW,
ThreadPriorityNormal=SDL_THREAD_PRIORITY_NORMAL,
ThreadPriorityCritical= SDL_THREAD_PRIORITY_HIGH

	}  ThreadPriority_t;
#else
#ifdef WINDOWS

/**
Priority	Meaning

THREAD_MODE_BACKGROUND_BEGIN
0x00010000 Begin background processing mode. The system lowers the resource scheduling priorities of the thread so that it can perform background work without significantly affecting activity in the foreground.
			This value can be specified only if hThread is a handle to the current thread. The function fails if the thread is already in background processing mode.
			Windows Server 2003 and Windows XP:  This value is not supported.

THREAD_MODE_BACKGROUND_END
0x00020000	End background processing mode. The system restores the resource scheduling priorities of the thread as they were before the thread entered background processing mode.
			This value can be specified only if hThread is a handle to the current thread. The function fails if the thread is not in background processing mode.
			Windows Server 2003 and Windows XP:  This value is not supported.

THREAD_PRIORITY_ABOVE_NORMAL
1 Priority 1 point above the priority class.

THREAD_PRIORITY_BELOW_NORMAL
-1 Priority 1 point below the priority class.

THREAD_PRIORITY_HIGHEST
2 Priority 2 points above the priority class.

THREAD_PRIORITY_IDLE
-15 Base priority of 1 for IDLE_PRIORITY_CLASS, BELOW_NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, ABOVE_NORMAL_PRIORITY_CLASS, or HIGH_PRIORITY_CLASS processes, and a base priority of 16 for REALTIME_PRIORITY_CLASS processes.

THREAD_PRIORITY_LOWEST
-2 Priority 2 points below the priority class.

THREAD_PRIORITY_NORMAL
0 Normal priority for the priority class.

THREAD_PRIORITY_TIME_CRITICAL
15 Base priority of 15 for IDLE_PRIORITY_CLASS, BELOW_NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, ABOVE_NORMAL_PRIORITY_CLASS, or HIGH_PRIORITY_CLASS processes, and a base priority of 31 for REALTIME_PRIORITY_CLASS processes.

**/
typedef enum {
//ThreadPriorityBackGroundBegin=	THREAD_MODE_BACKGROUND_BEGIN,
//ThreadPriority=THREAD_MODE_BACKGROUND_END,
ThreadPriorityAboveNormal=THREAD_PRIORITY_ABOVE_NORMAL,
ThreadPriorityBelowNormal=THREAD_PRIORITY_BELOW_NORMAL,
ThreadPriorityHighest=THREAD_PRIORITY_HIGHEST,
ThreadPriorityIdle=THREAD_PRIORITY_IDLE,
ThreadPriorityLowest =THREAD_PRIORITY_LOWEST,
ThreadPriorityNormal=THREAD_PRIORITY_NORMAL,
ThreadPriorityCritical=THREAD_PRIORITY_TIME_CRITICAL

	}  ThreadPriority_t;
#else
	typedef enum {
ThreadPriorityNormal=0,
ThreadPriorityAboveNormal,
ThreadPriorityBelowNormal,
ThreadPriorityHighest,
ThreadPriorityIdle,
ThreadPriorityLowest,
ThreadPriorityCritical
	}  ThreadPriority_t;
#endif
#endif
} //end Thread
} //end util
} //end SGF
#endif
