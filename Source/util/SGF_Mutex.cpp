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

#include <iostream>
using namespace std;
namespace SGF {

namespace Util{

/* Either uses pthreads or SDL_thread */

namespace Thread{

#if defined(USE_SDL_THREADS) && !defined(USE_NACL)

bool initializeLock(Lock * lock){
    *lock = SDL_CreateMutex();
    return *lock != NULL;
}

int acquireLock(Lock * lock){
    return SDL_LockMutex(*lock);
}

int releaseLock(Lock * lock){
	/*
	Returns 0 on success or a negative error code on failure; call SDL_GetError() for more information
	*/
    return SDL_UnlockMutex(*lock);
}

void destroyLock(Lock * lock){
    SDL_DestroyMutex(*lock);
}

void initializeCondition(Condition * condition){
    *condition = SDL_CreateCond();
    if (condition == NULL){
     //   Debug::debug(Debug::menu,__FILE__) << "Could not create condition" << endl;
    }
}

void destroyCondition(Condition * condition){
    ::SDL_DestroyCond(*condition);

}

int conditionWait(Condition * condition, Lock * lock){
	return ::SDL_CondWait(*condition, *lock);
}

int conditionSignal(Condition * condition){
    return ::SDL_CondBroadcast(*condition);
}


#else
#ifdef WINDOWS

bool initializeLock(Lock * lock){
   *lock= CreateMutex(NULL,false,NULL);
   if (lock==NULL) return false;
   else return true;
}
/**
If the function succeeds, the return value indicates the event that caused the function to return. It can be one of the following values.
Return code/value	Description

WAIT_ABANDONED
0x00000080L - The specified object is a mutex object that was not released by the thread that owned the mutex object before the owning thread terminated. 
Ownership of the mutex object is granted to the calling thread and the mutex state is set to nonsignaled.
			  If the mutex was protecting persistent state information, you should check it for consistency.

WAIT_OBJECT_0
0x00000000L - The state of the specified object is signaled.

WAIT_TIMEOUT
0x00000102L - The time-out interval elapsed, and the object's state is nonsignaled.

WAIT_FAILED
(DWORD)0xFFFFFFFF - The function has failed. To get extended error information, call GetLastError.

**/
int acquireLock(Lock * lock){
	DWORD returnCode = WaitForSingleObject(lock,INFINITE);
    if (returnCode != 0xFFFFFFFF ) return 0;
	else return 1;
}

int releaseLock(Lock * lock){
	/*
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. 
	To get extended error information, call GetLastError.
	*/
	if (ReleaseMutex(lock) !=0) return 0;
	else return 1;
}

void initializeCondition(Condition * condition){
   InitializeConditionVariable(condition);
}

void destroyCondition(Condition * condition){
    /**nothing **/
}

int conditionWait(Condition * condition, Lock * lock){
   /**
   If the function succeeds, the return value is nonzero.

If the function fails, the return value is zero. To get extended error information, call GetLastError.

If the timeout expires the function returns FALSE and GetLastError returns ERROR_TIMEOUT.
*/
	if( SleepConditionVariableSRW(condition, (PSRWLOCK)lock, INFINITE,CONDITION_VARIABLE_LOCKMODE_SHARED)!=0) return 0;
	else return 1;
}

int conditionSignal(Condition * condition){
    WakeAllConditionVariable(condition);
	return true;
}



void destroyLock(Lock * lock){
    acquireLock(lock);
	CloseHandle(lock);
}

#else


bool initializeLock(Lock * lock){
    return pthread_mutex_init(lock, NULL) == 0;
}

int acquireLock(Lock * lock){
	/*
	If successful, the pthread_mutex_lock() and pthread_mutex_unlock() functions shall return zero; otherwise, 
	an error number shall be returned to indicate the error. 
	*/
    return pthread_mutex_lock(lock);
}

int releaseLock(Lock * lock){
    return pthread_mutex_unlock(lock);
}

void initializeCondition(Condition * condition){
    pthread_cond_init(condition, NULL);
}

void destroyCondition(Condition * condition){
    pthread_cond_destroy(condition);
}

int conditionWait(Condition * condition, Lock * lock){
    return pthread_cond_wait(condition, lock);
}

int conditionSignal(Condition * condition){
    return pthread_cond_broadcast(condition);
}



void destroyLock(Lock * lock){
    pthread_mutex_lock(&lock);
	pthread_mutex_unlock(&lock); 
	pthread_mutex_destroy(&lock);
}
#endif
#endif

LockObject::LockObject(){
    initializeLock(&lock);
    initializeCondition(&condition);
	//Debug::debug(Debug::error,__FUNCTION__) << " creating Lock " << endl;
}

int LockObject::acquire() const {
	//Debug::debug(Debug::error,__FUNCTION__) << " Acquiring Lock " << endl;

    /* quick hack to get around annoying constness */
    return acquireLock((Lock*) &lock);
}

int LockObject::release() const {
	//Debug::debug(Debug::error,__FUNCTION__) << " Releasing Lock " << endl;

    return releaseLock((Lock*) &lock);
}

void LockObject::wait() const {
    int ok = 1;
    while (ok != 0){
        /* if conditionWait succeeds then ok will be 0 */
        ok = conditionWait((Condition*) &condition, (Lock*) &lock);
    }
}

void LockObject::wait(volatile bool & check) const {
    int ok = 0;
    /* only wait if check is false. if so then keep waiting until the condition
     * was successful as well.
     */
    while (!check || ok != 0){
        if (ok != 0){
            // Debug::debug(Debug::menu,__FILE__) << "Wait failed: " << SDL_GetError() << endl;
        }
        ok = conditionWait((Condition*) &condition, (Lock*) &lock);
    }
}

void LockObject::signal() const {
    conditionSignal((Condition*) &condition);
}

void LockObject::lockAndSignal(volatile bool & check, bool what) const {
    acquire();
    check = what;
    signal();
    release();
}

LockObject::~LockObject(){
	// da problema na hora de destruir tudo
	//Debug::debug(Debug::error,__FUNCTION__) << " Destroing Lock " << endl;

    destroyLock(&lock);
    destroyCondition(&condition);
}

ScopedLock::ScopedLock(const LockObject & lock):
_my_lock(lock){
	_my_lock.acquire();
}

ScopedLock::~ScopedLock(){
	//Debug::debug(Debug::error,__FUNCTION__) << " Releasing Lock " << endl;

    _my_lock.release();
}



CMutex::CMutex(void)
:m_bCreated(true)
{
	initializeLock(&m_mutex);
   if( !m_mutex ) m_bCreated = false;
   memset(&m_owner,0,sizeof(ThreadId_t));

}

CMutex::~CMutex(void)
{
	destroyLock(&m_mutex);
    
}
/**
 *
 * lock
 * wrap Lock
 *
 **/
void
CMutex::lock()
{
	ThreadId_t id = CThread::getThreadId();
	try {
		if(CThread::threadIdsEqual(&m_owner,&id) )
		    throw "\n\tthe same thread can not acquire a mutex twice!\n"; // the mutex is already locked by this thread
        acquireLock(&m_mutex);
		m_owner = CThread::getThreadId();
	}
	catch( char *psz )
	{
			Debug::debug(Debug::error,__FUNCTION__) << " Fatal exception CMutexClass::Lock " << endl;

	}
}


/**
 *
 * unlock
 * wrap Unlock
 *
 **/
void
CMutex::unlock()
{
CMutex::Unlock();
}

/**
 *
 * Unlock
 * releases a mutex.  only the thread that acquires
 * the mutex can release it.
 *
 **/
void 
CMutex::Unlock()
{
	ThreadId_t id = CThread::getThreadId();
	try 
	{
	  if( ! CThread::threadIdsEqual(&id,&m_owner) )
		throw "\n\tonly the thread that acquires a mutex can release it!"; 

	   memset(&m_owner,0,sizeof(ThreadId_t));
	   releaseLock(&m_mutex);

	}
	catch ( char *psz)
	{
			Debug::debug(Debug::error,__FUNCTION__)  << " Fatal exception CMutexClass::Unlock : "<< psz << endl;
	}
}



}}} //end SGF/Util/Thread
