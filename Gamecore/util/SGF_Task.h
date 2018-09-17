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
//COMPILER NOTES:
// On Unix you must use -lpthread a -lrt
// On Windows you must specify threaded under C++ code generation
#ifndef SGF_EVENT_TASK
#define SGF_EVENT_TASK
#include "../SGF_Config.h"
#include "../exceptions/all.h"
#include "SGF_Util.h"
#include "SGF_ThreadDefs.h"
namespace SGF {

namespace Util{

/* Either uses pthreads or SDL_thread */

namespace Thread{
class CEventTask
{
private:
	ThreadId_t _my_owner;
#ifdef USE_SDL_THREADS
		Condition m_ready;
		Lock  m_lock;

#else
#ifdef WINDOWS
	HANDLE _my_event;
#else
	pthread_cond_t m_ready;
	pthread_mutex_t m_lock;
#endif
#endif
public:
	bool m_bCreated;
	/**
	*
	* set
	* set an event to signaled
	*
	**/
	void set();
	/**
	*
	* wait
	* wait for an event -- wait for an event object
	* to be set to signaled.  must be paired with a
	* call to reset within the same thread.
	* This function atomically release mutex and cause the calling thread to block on the condition variable cond; 
	* Upon successful return true and the mutex has been locked and is owned by the calling thread. 
	**/
	bool wait(); //used o the callback function of CTred class
	/**
	*
	* reset
	* reset an event flag to unsignaled
	* wait must be paired with reset within the same thread.
	*
	**/
	void reset(); //used o the callback function of CTred class
	CEventTask(void);
	~CEventTask(void);
};
}}}  //end SGF/UTIL/Threds
#endif

