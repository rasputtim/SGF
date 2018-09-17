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
#include "util/SGF_Thread.h"


#include <iostream>
using namespace std;
namespace SGF {
namespace Util{
namespace Thread{

CEventTask::CEventTask(void)
:m_bCreated(true)
{
	memset(&_my_owner,0,sizeof(ThreadId_t));
#ifdef USE_SDL_THREADS
	initializeLock(&m_lock);
    initializeCondition(&m_ready);
#else
#ifdef WINDOWS
	/**
	Creates or opens a named or unnamed event object.
	If the function succeeds, the return value is a handle to the event object. 
	If the named event object existed before the function call, 
	the function returns a handle to the existing object and GetLastError returns ERROR_ALREADY_EXISTS.
	If the function fails, the return value is NULL. 
	To get extended error information, call GetLastError.
	**/
	_my_event = CreateEvent(NULL,FALSE,FALSE,NULL);
	if( !_my_event )
	{
		m_bCreated = FALSE;
	}
#else
	pthread_mutexattr_t mattr;
	
	pthread_mutexattr_init(&mattr);
	pthread_mutex_init(&m_lock,&mattr);
	pthread_cond_init(&m_ready,NULL);

#endif	
#endif
}

CEventTask::~CEventTask(void)
{
#ifdef USE_SDL_THREADS
    destroyCondition(&m_ready);	
	destroyLock(&m_lock);

#else
#ifdef WINDOWS
	CloseHandle(_my_event);
#else
	pthread_cond_destroy(&m_ready);
	pthread_mutex_destroy(&m_lock);
#endif
#endif
}


/**
 *
 * set
 * set an event to signaled
 *
 **/
void
CEventTask::set()
{
#ifdef USE_SDL_THREADS
	conditionSignal(&m_ready);
#else
#ifdef WINDOWS
	SetEvent(_my_event);
#else
	pthread_cond_signal(&m_ready);
#endif
#endif
}

/**
 *
 * wait
 * wait for an event -- wait for an event object
 * to be set to signaled.  must be paired with a
 * call to reset within the same thread.
 * This function atomically release mutex and cause the calling thread to block on the condition variable cond; 
 * Upon successful return true and the mutex has been locked and is owned by the calling thread. 
 **/
bool
CEventTask::wait()
{

	try
	{
		ThreadId_t id = CThread::getThreadId();
		if( CThread::threadIdsEqual(&id,&_my_owner) )
		{
			throw "\n\tinvalid Wait call, Wait can not be called more than once"
				"\n\twithout a corresponding call to Reset!\n";
		}
		ThreadId_t zero;
		memset(&zero,0,sizeof(ThreadId_t));

		if( memcmp(&zero,&_my_owner,sizeof(ThreadId_t)) != 0 )
		{
			throw "\n\tanother thread is already waiting on this event!\n";
		}

		_my_owner = CThread::getThreadId();
#ifdef USE_SDL_THREADS
		acquireLock(&m_lock);
		conditionWait(&m_ready,&m_lock);
		return true;
#else
#ifdef WINDOWS
		if( WaitForSingleObject(_my_event,INFINITE) != WAIT_OBJECT_0 )
		{
			return FALSE;
		}
#else
		pthread_mutex_lock(&m_lock);
		pthread_cond_wait(&m_ready,&m_lock);
		return true;
#endif
#endif
	}
	catch( char *psz )
	{
     Debug::debug(Debug::error,__FILE__) << "Fatal exception CEventTask::Wait" << psz << endl;

	}
	return true;
}

/**
 *
 * reset
 * reset an event flag to unsignaled
 * wait must be paired with reset within the same thread.
 *
 **/
void
CEventTask::reset()
{
	try 
	{
		ThreadId_t id = CThread::getThreadId();
		if( !CThread::threadIdsEqual(&id,&_my_owner) )
		{
			throw "\n\tunbalanced call to Reset, Reset must be called from\n"
				  "\n\tthe same Wait-Reset pair!\n";
		}

		memset(&_my_owner,0,sizeof(ThreadId_t));
#ifdef USE_SDL_THREADS
		releaseLock(&m_lock);
#else
#ifndef WINDOWS
		pthread_mutex_unlock(&m_lock);
#endif
#endif
	}
	catch( char *psz )
	{

     Debug::debug(Debug::error,__FILE__) << "Fatal exception CEventTask::Reset" << psz << endl;

		//MessageBoxA(NULL,&psz[2],"Fatal exception CEventTask::Reset",MB_ICONHAND);

	}
}

}}} //end SGF/Util/Thread