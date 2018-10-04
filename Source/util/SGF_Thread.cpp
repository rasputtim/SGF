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
#include "util/SGF_Debug.h"
using namespace std;
namespace SGF {

namespace Util{

namespace Thread{

#if defined(USE_SDL_THREADS) && !defined(USE_NACL)
ThreadId_t uninitializedValue = NULL;
#else
	#ifdef WINDOWS
	ThreadId_t uninitializedValue = 0;
	#else
	ThreadId_t uninitializedValue = 0;
	#endif
#endif

bool isUninitialized(ThreadId_t thread){


    return thread == uninitializedValue;
}

#if defined(USE_SDL_THREADS) && !defined(USE_NACL)

bool createThread(ThreadId_t * thread, void * attributes, ThreadFunction function, void * arg){
	CNamedThread estethread("name",thread);

#ifdef WII
    return wiiCreateThread(thread, attributes, function, arg);
#else
	const char *name = "";
	*thread = SDL_CreateThread(function,name,arg);
	return *thread != NULL;
#endif
}

void joinThread(ThreadId_t thread){
    if (!isUninitialized(thread)){
#ifdef WII
        wiiJoinThread(thread);
#else
        SDL_WaitThread(thread, NULL);
#endif
    }
}


#else
#ifdef WINDOWS
#include <process.h>
bool createThread(ThreadId_t * thread, void * attributes, ThreadFunction function, void * arg){
		//if( _my_thread ) CloseHandle(_my_thread);
	HANDLE m_thread;
#ifdef USE_BEGIN_THREAD
		m_thread = (HANDLE )_beginthreadex(NULL,(unsigned int)DEFAULT_STACK_SIZE,function,(LPVOID)arg,0,thread);
#else
		m_thread = CreateThread(NULL,DEFAULT_STACK_SIZE ,function,(LPVOID)arg,0,thread);
#endif

		if( !m_thread )
		{
			perror("thread creation failed");
			return FALSE;
		}

}

void joinThread(ThreadId_t thread){
    if (!isUninitialized(thread)){
 
	
	}
}

void cancelThread(ThreadId_t thread){
 

}
#else
bool createThread(ThreadId_t * thread, void * attributes, ThreadFunction function, void * arg){
    return pthread_create(thread, (pthread_attr_t*) attributes, function, arg) == 0;
}

void joinThread(ThreadId_t thread){
    if (!isUninitialized(thread)){
        pthread_join(thread, NULL);
    }
}

void cancelThread(ThreadId_t thread){
    /* FIXME: cancel is not implemented for libogc, find another way.
     * thread suspend/resume is there, though.
     */
#if !defined(WII) && !defined(USE_NACL)
    pthread_cancel(thread);
#endif

}
#endif
#endif
//=================================
//CThread
//=============================================


/**
 * 
 * _THKERNEL
 * thread callback function used by CreateThread
 *
 *
 **/
#ifdef WINDOWS
#ifdef USE_BEGIN_THREAD
unsigned __stdcall
#else
DWORD WINAPI
#endif
#else
LPVOID
#endif



_THKERNEL( LPVOID lpvData /* CThread Object */ )
{
	CThread *pThread = (CThread *)lpvData;
	ThreadType_t lastType;
	/*
	 *
	 * initialization
	 *
	 */


    pThread->m_mutex.lock();
	pThread->setState( ThreadStateWaiting);
	pThread->setRunning(true);
#ifndef WINDOWS
        pThread->_my_dwId = CThread::getThreadId();
#endif
	pThread->m_mutex.Unlock();
	
	while( true )
	{
		lastType = pThread->getTreadType();

		if( lastType == ThreadTypeHomogeneous ||
			lastType == ThreadTypeSpecialized ||
			lastType == ThreadTypeNotDefined )
		{
			if( ! pThread->getEventTask().wait()  )  // wait for a message
					break;
			pThread->getEventTask().reset(); // message recieved
		}
	    //run the onTask method
		if( ! pThread->KernelProcess() ) 
				break;


		/*if( lastType == ThreadTypeHomogeneous ||
			lastType == ThreadTypeSpecialized ||
			lastType == ThreadTypeNotDefined )
		{
			pThread->_my_event.Reset();
		} */

		if( pThread->getTreadType() == ThreadTypeIntervalDriven )
			Util::rest(pThread->getIddleTime());

	}


	pThread->m_mutex.lock();
		pThread->setState(ThreadStateDown);
		pThread->setRunning(false);
	pThread->m_mutex.Unlock();


#ifdef WINDOWS
	return 0;
#else
	return (LPVOID)0;
#endif
}

/**
 *
 * FromSameThread
 * determines if the calling thread is the same
 * as the thread associated with the object
 *
 **/
bool
CThread::FromSameThread()
{
	ThreadId_t id = getThreadId();
    if( threadIdsEqual(&id,&_my_dwId) ) return true;
    return false;
}

/**
 *
 * onTask
 * called when a thread is tasked using the Event
 * member function
 *
 **/
bool 
CThread::onTask( LPVOID lpvData /*data passed from thread*/ 
					   )
{
    ASSERT(lpvData && _my_type == ThreadTypeHomogeneous);

	if( _my_type != ThreadTypeHomogeneous )
	{
		Debug::debug(Debug::error,__FUNCTION__) << "Warning CThread::onTask:\n\tOnTask(LPVOID) called for a non-homogeneous thread!" << endl;
        return false;
	}

	((CTask *)lpvData)->SetTaskStatus(TaskStatusBeingProcessed);
    bool bReturn = ((CTask *)lpvData)->Task();
	((CTask *)lpvData)->SetTaskStatus(TaskStatusCompleted);

	return bReturn; 
} 



/**
 *
 * onTask
 * overloaded implementation of onTask that
 * takes no arguments
 *
 **/
bool
CThread::onTask()
{
	ASSERT(_my_type == ThreadTypeIntervalDriven);
	if( _my_type != ThreadTypeIntervalDriven )
	{
		Debug::debug(Debug::error,__FUNCTION__) <<"called for a non-event driven thread!" <<endl;
        return false;
	}

	printf("\nthread is alive\n");

	return true;
}

/**
 *
 * addEvent
 * used to place tasks on the threads event queue
 * wakes up thread.
 *
 **/
bool
CThread::addEvent(CTask *pvTask /* data to be processed by thread */
			   )
{
	m_mutex.lock();

	ASSERT(_my_type == ThreadTypeHomogeneous ||
	       _my_type == ThreadTypeNotDefined );

	try 
	{
		if( FromSameThread() )
		{
			throw "\n\tit is illegal for a thread to place an event on its own event stack!\n";
		}


		// make sure that the thread is running 
		if( !_my_bRunning && _my_dwObjectCondition == NO_ERRORS )
		{
			m_mutex.Unlock();
			pingThread(_my_dwIdle*2); // wait two idle cycles for it to start
			m_mutex.lock();
		}
		if( !_my_bRunning ) // if it is not running return FALSE;
		{
			m_mutex.Unlock();
            return false;
		}


		if( _my_dwObjectCondition & ILLEGAL_USE_OF_EVENT )
			_my_dwObjectCondition = _my_dwObjectCondition ^ ILLEGAL_USE_OF_EVENT;
		if( _my_dwObjectCondition & EVENT_AND_TYPE_DONT_MATCH)
			_my_dwObjectCondition = _my_dwObjectCondition ^ EVENT_AND_TYPE_DONT_MATCH;

		if( _my_type != ThreadTypeHomogeneous &&
			_my_type != ThreadTypeNotDefined    )
		{
			m_mutex.Unlock();
			_my_dwObjectCondition |= ILLEGAL_USE_OF_EVENT;
			_my_dwObjectCondition |= EVENT_AND_TYPE_DONT_MATCH;
			_my_state = ThreadStateFault;
			Debug::debug(Debug::error,__FUNCTION__) << "Warning: invalid call to CEvent::Event(CTask *), thread type is not specialized" << endl;

            return false;
		}

		_my_type = ThreadTypeHomogeneous;
		m_mutex.Unlock();

		pvTask->SetId(&_my_dwId);
		if( ! push((LPVOID)pvTask) )
            return false;

		pvTask->SetTaskStatus(TaskStatusWaitingOnQueue);
		_my_event.set();

	}
	catch (char *psz)
	{
	Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		

	}
    return true;
}

/**
 *
 * addEvent
 * used to place tasks on the threads event queue
 * wakes up thread.
 *
 **/
bool
CThread::addEvent(LPVOID lpvData /* data to be processed by thread */
			   )
{

	m_mutex.lock();
	ASSERT( _my_type == ThreadTypeSpecialized ||
		    _my_type == ThreadTypeNotDefined );
	try 
	{
		if( FromSameThread() )
		{
			throw "\n\tit is illegal for a thread to place an event on its own event stack!\n";
		}
	}
	catch (char *psz)
	{
	Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		

	}

	// make sure that the thread is running 
	if( !_my_bRunning && _my_dwObjectCondition == NO_ERRORS )
	{
		m_mutex.Unlock();
		  pingThread(_my_dwIdle*2); // wait two idle cycles for it to start
		m_mutex.lock();
	}
	if( !_my_bRunning ) // if it is not running return FALSE;
	{
		m_mutex.Unlock();
        return false;
	}

	if( _my_dwObjectCondition & ILLEGAL_USE_OF_EVENT )
		_my_dwObjectCondition = _my_dwObjectCondition ^ ILLEGAL_USE_OF_EVENT;
	if( _my_dwObjectCondition & EVENT_AND_TYPE_DONT_MATCH)
		_my_dwObjectCondition = _my_dwObjectCondition ^ EVENT_AND_TYPE_DONT_MATCH;

	if( _my_type != ThreadTypeSpecialized && 
		_my_type != ThreadTypeNotDefined )
	{
		_my_dwObjectCondition |= ILLEGAL_USE_OF_EVENT;
		_my_dwObjectCondition |= EVENT_AND_TYPE_DONT_MATCH;
		Debug::debug(Debug::error,__FUNCTION__) << "Warning: invalid call to CEvent::Event(LPVOID), thread type is not specialized"<<endl;
		m_mutex.Unlock();
        return false;
	}
	_my_type = ThreadTypeSpecialized;

	m_mutex.Unlock();
	if( ! push(lpvData) )
	{
        return false;
	}
	// set the event to signaled
	_my_event.set();

    return true;
}


/**
 *
 * setPriority
 * sets a threads run priority, see SetThreadPriority
 * Note: only works for Windows family of operating systems
 *
 *
 **/
void

#ifdef USE_SDL_THREADS
	CThread::setPriority(SDL_ThreadPriority dwPriority)
{
	SDL_SetThreadPriority(dwPriority);
#else
#ifdef WINDOWS
	CThread::setPriority(DWORD dwPriority)
{
	SetThreadPriority(_my_thread,dwPriority);
#endif
	/* nothing */
#endif
}

	  
/**
 *
 * KernelProcess
 * routes thread activity
 * run onTask method
 * used on the callback function to run the onTask method
 **/
bool
CThread::KernelProcess()
{

	m_mutex.lock();
	_my_state = ThreadStateBusy;
	if( !_my_bRunning )
	{
		_my_state = ThreadStateShuttingDown;
		m_mutex.Unlock();
		return false;
	}
	m_mutex.Unlock();

	if( !isEmpty() )
	{
		while( !isEmpty() )
		{
			pop();
			if( !onTask(_my_lpvProcessor) )
			{
				m_mutex.lock();
				_my_lpvProcessor = NULL;
				_my_state = ThreadStateShuttingDown;
				m_mutex.Unlock();
                return false;
			}
		}
		m_mutex.lock();
		_my_lpvProcessor = NULL;
		_my_state = ThreadStateWaiting;
	}
	else {
		if( !onTask() )
		{
			m_mutex.lock();
			_my_state = ThreadStateShuttingDown;
			m_mutex.Unlock();
			return false;
		}
		m_mutex.lock();
		_my_state = ThreadStateWaiting;
	}

	m_mutex.Unlock();

	return true;
}


/**
 * 
 * getEventsPending
 * returns the total number of vents waiting
 * in the event que
 * 
 **/
unsigned int
CThread::getEventsPending()
{
	unsigned int chEventsWaiting;

	m_mutex.lock();
	  chEventsWaiting = _my_queuePos;
    m_mutex.Unlock();

	return chEventsWaiting;
}


/**
 *
 * CThread
 * instanciates thread object and
 * starts thread.
 *
 **/
CThread::CThread(void)
:_my_bRunning(false)
#ifdef WINDOWS
,_my_thread(NULL)
#endif
,_my_dwId(0L)
,_my_state(ThreadStateDown)
,_my_dwIdle(100)
,_my_lppvQueue(NULL)
,_my_lpvProcessor(NULL)
,_my_chQueue(QUEUE_SIZE)
,_my_type(ThreadTypeNotDefined)
,_my_stackSize(DEFAULT_STACK_SIZE)
,_my_queuePos(0)
,_my_StopTimeout(30)
{

	_my_dwObjectCondition = NO_ERRORS;

	_my_lppvQueue = new LPVOID [QUEUE_SIZE];

	if( !_my_lppvQueue ) 
	{
		_my_dwObjectCondition |= MEMORY_FAULT;
		_my_state = ThreadStateFault;
		return;
	}

	if( !m_mutex.m_bCreated )
	{
		perror("mutex creation failed");
		_my_dwObjectCondition |= MUTEX_CREATION;
		_my_state = ThreadStateFault;
		return;
	}


	if( !_my_event.m_bCreated )
	{
		perror("event creation failed");
		_my_dwObjectCondition |= EVENT_CREATION;
		_my_state = ThreadStateFault;
		return;
	}


	start();

}


/**
 *
 * PercentCapacity
 * returns a floating point value identifying
 * the current workload of the thread
 *
 **/
float
CThread::PercentCapacity()
{
	float fValue = 0;
	m_mutex.lock();
		fValue = (float)_my_queuePos/_my_chQueue;
	m_mutex.Unlock();
	return fValue;
}

/**
 *
 * setQueueSize
 * changes the threads queue size
 *
 **/
bool
CThread::setQueueSize( unsigned int ch )
{
	LPVOID * newQueue = NULL;

	m_mutex.lock();
	    ASSERT(ch > _my_queuePos);

	    if( ch <= _my_queuePos )
		{
			Debug::debug(Debug::error,__FUNCTION__) << "Warning CThread::SetQueueSize:\n\tthe new queue size is less than the number of tasks on a non-empty queue! Request ignored."<<endl;
			m_mutex.Unlock();
            return false;
		}

		newQueue = new LPVOID [ch];
		if(  !newQueue )
		{
			Debug::debug(Debug::error,__FUNCTION__) << "Warning CThread::SetQueueSize:\n\ta low memory, could not reallocate queue!"<<endl;
			m_mutex.Unlock();
            return false;
		}

		for( unsigned int i=0;i<_my_queuePos; i++ )
		{
			newQueue[i] = _my_lppvQueue[i];
		}

		delete [] _my_lppvQueue;

		_my_chQueue = ch;
		_my_lppvQueue = newQueue;

	m_mutex.Unlock();

    return true;
}



/**
 *
 * Empty
 * returns a value of TRUE if there are no items on the threads que
 * otherwise a value of FALSE is returned.
 *
 **/
bool
CThread::isEmpty()
{
	m_mutex.lock();
	if( _my_queuePos <= 0 )
	{
		m_mutex.Unlock();
		return true;
	}
	m_mutex.Unlock();
	return false;
}



/**
 *
 * push
 * place a data object in the threads queue
 *
 **/
bool
CThread::push( LPVOID lpv )
{
    if( !lpv ) return true;

	m_mutex.lock();

	if( _my_queuePos+1 >= _my_chQueue ) {
		_my_dwObjectCondition |= STACK_OVERFLOW;
		m_mutex.Unlock();
		return false;
	}
	if( _my_dwObjectCondition & STACK_EMPTY    )
		_my_dwObjectCondition = _my_dwObjectCondition ^ STACK_EMPTY;

	if( _my_dwObjectCondition & STACK_OVERFLOW ) 
		_my_dwObjectCondition = _my_dwObjectCondition ^ STACK_OVERFLOW;

	_my_lppvQueue[_my_queuePos++] = lpv;
	if( _my_queuePos+1 >= _my_chQueue )
		_my_dwObjectCondition |= STACK_FULL;

	m_mutex.Unlock();
	return true;
}


/**
 *
 * Pop
 * move an object from the input que to the processor
 *
 **/
bool
CThread::pop()
{

	m_mutex.lock();
	if( _my_queuePos-1 < 0 )
	{
		_my_queuePos = 0;
		_my_dwObjectCondition |= STACK_EMPTY;
		m_mutex.Unlock();
        return false;
	}
	if( _my_dwObjectCondition & STACK_EMPTY )
		_my_dwObjectCondition = _my_dwObjectCondition ^ STACK_EMPTY;
	if( _my_dwObjectCondition & STACK_OVERFLOW )
		_my_dwObjectCondition = _my_dwObjectCondition ^ STACK_OVERFLOW;
	if( _my_dwObjectCondition & STACK_FULL )
		_my_dwObjectCondition = _my_dwObjectCondition ^ STACK_FULL;

	_my_queuePos--;
	_my_lpvProcessor = _my_lppvQueue[_my_queuePos];
	m_mutex.Unlock();
	return true;
}


/**
 *
 * setThreadType
 * specifies the type of threading that is to be performed.
 *
 * ThreadTypeEventDriven (default): an event must be physically sent
 *									to the thread using the Event member
 *									function.
 *
 * ThreadTypeIntervalDriven       : an event occurs automatically every 
 *                                  dwIdle milli seconds.
 *
 **/
void
CThread::setThreadType(ThreadType_t typ,
              DWORD dwIdle)
{

	try 
	{
		if( FromSameThread() )
		{
			throw "\n\tit is illegal for a thread to change its own type!\n";
		}


		m_mutex.lock();
		_my_dwIdle = dwIdle;


		if( _my_type == typ ) {
			m_mutex.Unlock();
			return;
		}
		if( _my_dwObjectCondition & ILLEGAL_USE_OF_EVENT )
			_my_dwObjectCondition = _my_dwObjectCondition ^ ILLEGAL_USE_OF_EVENT;
		if( _my_dwObjectCondition & EVENT_AND_TYPE_DONT_MATCH )
			_my_dwObjectCondition = _my_dwObjectCondition ^ EVENT_AND_TYPE_DONT_MATCH;

		_my_type = typ;


		m_mutex.Unlock();
		_my_event.set();
	}
	catch (char *psz)
	{
	Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		

	}
}


/**
 *
 * stop
 * stop thread 
 *
 **/
bool
CThread::stop()
{
	try 
	{
		if( FromSameThread() )
		{
			throw "\n\tit is illegal for a thread to attempt to signal itself to stop!\n";
		}

		m_mutex.lock();
        _my_bRunning = false;
		m_mutex.Unlock();
		_my_event.set();

		int ticks = (_my_StopTimeout*1000)/100;

		for( int i=0; i<ticks; i++ )
		{
			Util::rest(100);

			m_mutex.lock();
			if( _my_state == ThreadStateDown )
			{
				m_mutex.Unlock();
                return true;
			}
			m_mutex.Unlock();

		} 
	}
	catch (char *psz)
	{
	Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		

	}
    return false;
}


/**
 *
 * setIdle
 * changes the threads idle interval
 *
 **/
void
CThread::setIdle(DWORD dwIdle)
{
	m_mutex.lock();
	_my_dwIdle = dwIdle;
	m_mutex.Unlock();
}

/**
 *
 * start
 * start thread
 *
 **/
bool
CThread::start()
{
	try 
	{
		if( FromSameThread() )
		{
			throw "\n\tit is illegal for a thread to attempt to start itself!\n";
		}


		m_mutex.lock();
		if( _my_bRunning ) 
		{
			m_mutex.Unlock();
            return true;
		}

		m_mutex.Unlock();


		if( _my_dwObjectCondition & THREAD_CREATION )
			_my_dwObjectCondition = _my_dwObjectCondition ^ THREAD_CREATION;
#ifdef USE_SDL_THREADS
		_my_thread= createThread(&_my_dwId, NULL, _THKERNEL,(LPVOID)this);
 /**   (pthread_t *thread, const pthread_attr_t *attr, 
    void *(*start_routine)(void*), void *arg);
	int error = pthread_create(&_my_thread,&attr,_THKERNEL,(LPVOID)this);
**/
		if( !_my_thread )
		{
			perror("thread creation failed");
			_my_dwObjectCondition |= THREAD_CREATION;
			_my_state = ThreadStateFault;
            return false;
		}
#else
#ifdef WINDOWS
		if( _my_thread ) CloseHandle(_my_thread);
#ifdef USE_BEGIN_THREAD
		_my_thread = (HANDLE )_beginthreadex(NULL,(unsigned int)_my_stackSize,_THKERNEL,(LPVOID)this,0,&_my_dwId);
#else
		_my_thread = CreateThread(NULL,_my_stackSize ,_THKERNEL,(LPVOID)this,0,&_my_dwId);
#endif

		if( !_my_thread )
		{
			perror("thread creation failed");
			_my_dwObjectCondition |= THREAD_CREATION;
			_my_state = ThreadStateFault;
			return FALSE;
		}
#else
		pthread_attr_t attr;

		pthread_attr_init(&attr);

#ifdef VMS
		if( _my_stackSize == 0 )
			pthread_attr_setstacksize(&attr,PTHREAD_STACK_MIN*10);
#endif
		if( _my_stackSize != 0 )
			pthread_attr_setstacksize(&attr,_my_stackSize);

		int error = pthread_create(&_my_thread,&attr,_THKERNEL,(LPVOID)this);

		if( error != 0 )
		{
			_my_dwObjectCondition |= THREAD_CREATION;
			_my_state = ThreadStateFault;

#if defined(HPUX) || defined(SUNOS) || defined(LINUX)
			switch(error)/* show the thread error */
			{

			case EINVAL:
				cerr << "error: attr in an invalid thread attributes object\n";
				break;
			case EAGAIN:
				cerr << "error: the necessary resources to create a thread are not\n";
				cerr << "available.\n";
				break;
			case EPERM:
				cerr << "error: the caller does not have the privileges to create\n";
				cerr << "the thread with the specified attr object.\n";
				break;
#if defined(HPUX)
			case ENOSYS:

				cerr << "error: pthread_create not implemented!\n";
				if( __is_threadlib_linked()==0 )
				{
					cerr << "error: threaded library not being used, improper linkage \"-lpthread -lc\"!\n";
				}
				break;
#endif
			default:
				cerr << "error: an unknown error was encountered attempting to create\n";
				cerr << "the requested thread.\n";
				break;
			}
#else
			cerr << "error: could not create thread, pthread_create failed (" << error << ")!\n";
#endif

			return FALSE;	
		}
#endif //end ifdef WINDOWS
#endif //end USE_SDL_THREADS
	}
	catch (char *psz)
	{
	Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		
	}
	return true;
}

/**
 *
 * atCapacity
 * returns TRUE if the threads queue is full, and the thread
 * is busy processing an event or the thread is not running
 *
 **/
bool
CThread::atCapacity()
{
	m_mutex.lock();
		if( ((_my_dwObjectCondition & STACK_OVERFLOW ||
			  _my_dwObjectCondition & STACK_FULL ) &&
			  _my_state == ThreadStateBusy) || !_my_bRunning)
		{
			m_mutex.Unlock();
            return true;
		}
	m_mutex.Unlock();
    return false;
}

/**
 *
 * ThreadState
 * return the current state of the thread
 *
 **/
ThreadState_t 
CThread::ThreadState()
{
	ThreadState_t currentState;
	m_mutex.lock();
		currentState = _my_state;
	m_mutex.Unlock();
	return currentState;
}

/**
 *
 * ~CThread
 * destructor.  Stop should be called prior to destruction to
 * allow for gracefull thread termination.
 *
 **/
CThread::~CThread(void)
{
	if( _my_bRunning ) // gracefull termination
	{
		try 
		{
			if( !stop() )
			{
				throw "\n\tthread failed to stop in a timely manner!\n";
			}
		}
		catch( char *psz )
		{
			Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		
		}
	}
#ifndef USE_SDL_THREADS
#ifdef WINDOWS
	CloseHandle(_my_thread);
#endif
#endif
	delete [] _my_lppvQueue;
}


/**
 *
 * pingThread
 * used to determine if a thread is running
 *
 **/
bool
CThread::pingThread(DWORD dwTimeout /* timeout in milli-seconds */
				 )
{
    DWORD dwTotal = 0;

	while(true)
	{
		if( dwTotal > dwTimeout && dwTimeout > 0 )
            return false;
		m_mutex.lock();
			if( _my_bRunning )
			{
				m_mutex.Unlock();
				return true;
			}
		dwTotal += _my_dwIdle;
		m_mutex.Unlock();
		Util::rest(_my_dwIdle);
	}

	return false;
}

/**
 *
 * WaitTillExit
 * blocks caller until thread exits
 *
 **/
void
CThread::WaitTillExit()
{

	/*
	 *
	 * prevent users from calling this function from within the same thread
	 * of execution
	 *
	 */
	try 
	{
		if( FromSameThread() )
			throw "\n\tthis function can not be called from within the same thread!\n";




		if( !_my_bRunning ) return;
#ifdef USE_SDL_THREADS
		joinThread(_my_dwId);
#else
#ifdef WINDOWS
		WaitForSingleObject(_my_thread,INFINITE);
#else
		LPVOID lpv;

		pthread_join(_my_thread,&lpv);
#endif
#endif
	}
	catch( char *psz )
	{
			Debug::debug(Debug::error,__FUNCTION__) << "Fatal exception  "<< psz << endl;
		

	}
}


//=============================================

ThreadObject::ThreadObject(void * data, void * (function)(void * arg)):
_my_pData(data),
function(function),
_my_thread(uninitializedValue){
}

bool ThreadObject::start(){
    if (_my_thread == uninitializedValue){
        return createThread(&_my_thread, NULL, (Thread::ThreadFunction) function, _my_pData);
    } else {
        return false;
    }
}

ThreadObject::~ThreadObject(){
    if (_my_thread != uninitializedValue){
        joinThread(_my_thread);
        _my_thread = uninitializedValue;
    }
}




WaitThread::WaitThread():
_my_done(false){
    Thread::initializeLock(&_my_doneLock);
}

WaitThread::WaitThread(Thread::ThreadFunction thread, void * arg){
    Thread::initializeLock(&_my_doneLock);
    start(thread, arg);
}

static void * do_thread(void * arg){
    WaitThread * thread = (WaitThread *) arg;
    thread->doRun();
    return NULL;
}

void WaitThread::doRun(){
    this->_my_function(this->_my_pArg);

    Thread::acquireLock(&_my_doneLock);
    this->_my_done = true;
    Thread::releaseLock(&_my_doneLock);
}

void WaitThread::start(Thread::ThreadFunction thread, void * arg){
    _my_done = false;
    this->_my_pArg = arg;
    this->_my_function = thread;
    Thread::createThread(&this->_my_thread, NULL, (Thread::ThreadFunction) do_thread, this);
}

bool WaitThread::isRunning(){
    Thread::acquireLock(&_my_doneLock);
    bool what = _my_done;
    Thread::releaseLock(&_my_doneLock);
    return what;
}

void WaitThread::kill(){
    Thread::joinThread(_my_thread);
}

WaitThread::~WaitThread(){
    /* FIXME: Should we join the thread? */
    /* pthread_join(thread); */
    Thread::joinThread(_my_thread);
}

ThreadBoolean::ThreadBoolean(volatile bool & what, Thread::Lock & lock):
_my_what(what),
_my_lock(lock){
}

bool ThreadBoolean::get(){
    Thread::acquireLock(&_my_lock);
    bool b = _my_what;
    Thread::releaseLock(&_my_lock);
    return b;
}

void ThreadBoolean::set(bool value){
    Thread::acquireLock(&_my_lock);
    _my_what = value;
    Thread::releaseLock(&_my_lock);
}
} //end Thread
} //end Util
} //end SGF
