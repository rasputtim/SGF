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
// COMPILER NOTES:
// On Unix you must use -lpthread a -lrt
// On Windows you must specify threaded under C++ code generation

#ifndef _S_G_F_thread_h
#define _S_G_F_thread_h
#include "../SGF_Config.h"
#include "../exceptions/all.h"
#include "SGF_Util.h"
#include "SGF_Task.h"
#include "SGF_ThreadDefs.h"
#ifdef WINDOWS
#include <windows.h>
#include <stdio.h>
#endif

using namespace std;

namespace SGF {

namespace Util{

/* Either uses pthreads or SDL_thread */

namespace Thread{



class CNamedThread{
public:


	CNamedThread(string name, ThreadId_t *id):
		_my_Name(name),
		_my_ThreadId_t(id){}
	~CNamedThread(){}
	const CNamedThread & operator=(const CNamedThread & copy){
		if(this == &copy) return *this;
		this->_my_Name = copy._my_Name;
		this->_my_ThreadId_t = copy._my_ThreadId_t;
		return *this;
	}
string _my_Name;
ThreadId_t *_my_ThreadId_t;

};

    extern ThreadId_t uninitializedValue;
    bool isUninitialized(ThreadId_t thread);
    bool initializeLock(Lock * lock);

    void initializeCondition(Condition * condition);
    void destroyCondition(Condition * condition);
    int conditionWait(Condition * condition, Lock * lock);
    int conditionSignal(Condition * condition);


    int acquireLock(Lock * lock);
    int releaseLock(Lock * lock);
    void destroyLock(Lock * lock);
	/** cria um novo Trhead
		\param function: A função (assinatura ThreadFunction) que ira executar no thread criado
		\param arg: ponteiro para os argumentos que serão passados para a função function
		\param attributes: used to pass attributes to WII create Thread. For others platforms must be NULL
		\param ThreadId_t: The ThreadId_t of the new thread
		**/
    bool createThread(ThreadId_t * thread, void * attributes, ThreadFunction function, void * arg);


	/**  A thread pode executar o thread join e aguardar até a outra thread terminar.
	     Em geral o thread join é utilizado para a thread-mãe se sincronizar com uma das threads-filho.
		\param thread: o ThreadId_t do thread que deve ser aguardado
	**/
	void joinThread(ThreadId_t thread);

class CMutex
{
private:
	Lock m_mutex;
	ThreadId_t m_owner;
public:
	bool m_bCreated;
	void Unlock();
	void lock();
	void unlock();
	Util::Thread::Lock * getLock() {return &m_mutex;};
	CMutex(void);
	~CMutex(void);
};
    /* wraps a Lock in a c++ class */
    class  SGE_API LockObject{
    public:
        LockObject();

        int acquire() const;
        int release() const;

        Lock & getLock(){
            return lock;
        }

        /* wait until check is true.
         * you MUST acquire the lock before calling this function */
        void wait(volatile bool & check) const;

        /* just until we are signaled
         * you MUST acquire the lock before calling this function */
        void wait() const;

        /* you MUST acquire the lock before calling this function */
        void signal() const;

        /* gets the lock, sets the boolean, and signals the condition
         * you MUST NOT acquire the lock before calling this function
         */
        void lockAndSignal(volatile bool & check, bool what) const;

        virtual ~LockObject();

        Lock lock;
        Condition condition;
};

    /* acquires/releases the lock in RAII fashion */
    class  SGE_API ScopedLock{
    public:
        ScopedLock(const LockObject & lock);
        ~ScopedLock();
    private:
        const LockObject & _my_lock;
    };

    class  SGE_API ThreadObject{
    public:
        ThreadObject(void * data, void * (function)(void * arg));

        /* true if the thread was started, false otherwise */
        virtual bool start();
        virtual ~ThreadObject();

    protected:
        void * _my_pData;
        void * (*function)(void * arg);
        ThreadId_t _my_thread;
    };


#if 0


/**
 * \class CRegisteredThread
 *
 * \ingroup SGF_Util
 *
 * \brief Simple Thread registered with CResource Class
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2014
  */
class  SGE_API CRegisteredThread{
public:
    /** constrói o objeto, mas não inicia o novo thread ainda
	**/
    CRegisteredThread();

    /** constrói o objeto, e já inicia o novo thread
	\param thread: a função que será executada pelo novo thread
	\param arg: os parâmetros que serão passados para função a ser executada
	**/
   CRegisteredThread(Thread::ThreadFunction thread, void * arg);

    /** \brief inicia um thread
	\param thread: o thread a ser iniciado
	\param arg: osparâmetros que serão passados para a função a ser executada
	**/
    void start(Thread::ThreadFunction thread, void * arg);

	/** \brief retorna true se o thread estiver rodando
	**/
    bool isRunning();
	/** \brief espera até que o thread termine
	**/
    void kill();

    virtual ~CRegisteredThread();

public:
    /** \brief realmente roda o thread
	**/
    void doRun();

protected:
    Thread::Lock _my_doneLock;
    Thread::ThreadId_t _my_thread;
    volatile bool _my_done;
    void * _my_pArg;
    Thread::ThreadFunction _my_function;
};



#endif
//=========================


class CTask
{
private:
	TaskStatus_t m_state;
	ThreadId_t m_dwThread;
public:
	CMutex m_mutex;

	void SetTaskStatus(TaskStatus_t state)
	{
		m_mutex.lock();
			m_state=state;
		m_mutex.Unlock();
	}

	void SetId(ThreadId_t *pid)
	{
		memcpy(&m_dwThread,pid,sizeof(ThreadId_t));
	}

	/**
	 *
	 * Wait
	 * waits for upto timeoutSeconds for a task
	 * to complete
	 *
	 **/
	bool Wait(int timeoutSeconds)
	{
        timeoutSeconds = timeoutSeconds * 1000;
		if( Status() != TaskStatusCompleted &&
			timeoutSeconds > 0 )
		{
			SGF::Util::rest(100);
			timeoutSeconds = timeoutSeconds - 100;
		}
		if( Status() == TaskStatusCompleted ) return true;
		return false;
	}

	/**
	 *
	 * Status
	 * returns current state of a task
	 *
	 **/
	TaskStatus_t Status()
	{
		TaskStatus_t state ;

		m_mutex.lock();
		  state = m_state;
		m_mutex.Unlock();
	    return state;
	}

	void Thread(ThreadId_t *pId)
	{
		memcpy(pId,&m_dwThread,sizeof(ThreadId_t));
	}

	CTask(){m_state=TaskStatusNotSubmitted; memset(&m_dwThread,0,sizeof(ThreadId_t)); }
	~CTask(){}
	virtual bool Task()=0;
};


class CThread
#ifdef WINDOWS
//	: public CObject // use CObject as a base class so object can be used in lists and
	               // object arrays
#endif
{
public:
    ThreadId_t	  _my_dwId;          // id of this thread

private:
	CEventTask   _my_event;         // event controller
	int          _my_StopTimeout;   // specifies a timeout value for stop
	                               // if a thread fails to stop within _my_StopTimeout
	                               // seconds an exception is thrown

	bool		  _my_bRunning;      // set to true if thread is running
	ThreadHandle  _my_thread;		   // thread handle

	LPVOID        *_my_lppvQueue;    // task queue
	unsigned int  _my_chQueue;       // que depth
	unsigned int  _my_queuePos;      // current que possition
	LPVOID        _my_lpvProcessor;  // pointer to data which is currently being processed
	ThreadState_t _my_state;         // current state of thread see thread state data
	                               // structure.
	DWORD         _my_dwIdle;        // used for Sleep periods
	ThreadType_t  _my_type;
	DWORD		  _my_stackSize;     // thread stack size
	DWORD         _my_dwObjectCondition;
 /**
 *
 * push(LPVOID lpv)
 * \brief Coloca um elemnto na fila de threads
 * \return: true no sucesso
 *          false se houver alguma falha
 * \param lpv Ponteiro para o objeto a ser inserido na fila
 *
 **/
	bool		  push(LPVOID lpv);
/**
 *
 * pop()
 * \brief move an object from the input que to the processor
 * \return: true no sucesso
 *          false se houver alguma falha
 *
 *
 **/
	bool		  pop();
/**
 *
 * isEmpty()
 * \brief Verifica se há ou não threads na fila
 * \return: true se não há nenhum elemento na fila de threads ou
 *          false se houver algum
 *
 *
 **/
	bool		  isEmpty();
public:
	/**
	 *
	 * user definable member functions
	 *
	 **/
	CMutex	  m_mutex;         // mutex that protects threads internal data

	virtual bool onTask(LPVOID lpvData);     // called when an event occurs
	virtual bool onTask();                   // called when a time interval has elapsed
	void setState(ThreadState_t state) {_my_state=state; };
	void setRunning(bool runing) {this->_my_bRunning=runing;};
	void setThreadType(ThreadType_t  type) {  _my_type=type;};
	CEventTask  & getEventTask(){ return _my_event;};
	DWORD getIddleTime() { return _my_dwIdle;};
	ThreadType_t getTreadType(){return this->_my_type;};
	CThread(void);
	~CThread(void);
#ifdef USE_SDL_THREADS
	ThreadFunction _THKERNEL;
#else
#ifdef WINDOWS
#ifdef USE_BEGIN_THREAD
	friend unsigned __stdcall _THKERNEL(LPVOID lpvData);
#else
	friend DWORD WINAPI _THKERNEL( LPVOID lpvData );
#endif
#else
	friend LPVOID _THKERNEL(LPVOID lpvData);
#endif
#endif
	bool        FromSameThread();
	float		PercentCapacity();
	void        WaitTillExit();
	bool		KernelProcess();
	/**
	*
	* addEvent
	* used to place tasks on the threads event queue
	* wakes up thread.
	*
	**/
	bool		addEvent(LPVOID lpvData=NULL);
	/**
	*
	* addEvent
	* used to place tasks on the threads event queue
	* wakes up thread.
	*
	**/
	bool        addEvent(CTask *pvTask);
	void		setOnStopTimeout(int seconds ) { _my_StopTimeout = seconds; }
	/**
	*
	* setQueueSize
	* changes the threads queue size
	*
	**/
    bool        setQueueSize( unsigned int ch );
	bool		stop();
	bool		start();
	void		getId(ThreadId_t *pId) { memcpy(pId,&_my_dwId,sizeof(ThreadId_t)); }      // returns thread id
	ThreadState_t ThreadState();
	/**
	*
	* PingThread
	* used to determine if a thread is running
	*
	**/
	bool		pingThread(DWORD dwTimeout=0);
	/**
	*
	* atCapacity
	* returns TRUE if the threads queue is full, and the thread
	* is busy processing an event or the thread is not running
	*
	**/
	bool        atCapacity();

	/**
	*
	* setPriority
	* sets a threads run priority, see SetThreadPriority
	* Note: only works for Windows family of operating systems
	*
	*
	**/
	#ifdef USE_SDL_THREADS
		void		setPriority(SDL_ThreadPriority dwPriority=SDL_THREAD_PRIORITY_NORMAL);
#else
	void		setPriority(DWORD dwPriority=ThreadPriorityNormal);
#endif
	DWORD		getErrorFlags() { return _my_dwObjectCondition; } // returns state of object
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
	void		setThreadType(ThreadType_t typ=ThreadTypeNotDefined,DWORD dwIdle=100);
	/**
	*
	* setIdle
	* changes the threads idle interval
	*
	**/
	void		setIdle(DWORD dwIdle=100);
	/**
	*
	* getEventsPending
	* returns the total number of vents waiting
	* in the event que
	*
	**/
    unsigned int getEventsPending();

    static bool threadIdsEqual(ThreadId_t *p1,
						       ThreadId_t *p2)
	{
#if defined(AS400)||defined(OS400)
		return(( memcmp(p1,p2,sizeof(ThreadId_t))==0)?true:false);
#elif defined(VMS)
		return (( pthread_equal(*p1,*p2) )?true:false );
#else
		return ((*p1 == *p2)?true:false);
#endif

	}

	static ThreadId_t getThreadId()
	{
		ThreadId_t thisThreadsId ;
#if defined(AS400) || defined(OS400)
		pthread_t thread;
#endif
#ifdef USE_SDL_THREADS
		thisThreadsId = (ThreadId_t)SDL_GetThreadID(NULL);

#else
#ifdef WINDOWS
		thisThreadsId = (ThreadId_t)GetCurrentThreadId();
#else

#if defined(AS400) || defined(OS400)
		thread = pthread_self();
		pthread_getunique_np(&thread,&thisThreadsId);
#elif defined(ALPHA) || defined(DEC) || defined(VMS)
#ifdef VMS
		thisThreadsId = pthread_self();
#else
		thisThreadsId = pthread_getsequence_np(pthread_self());
#endif
#else
		thisThreadsId = pthread_self();
#endif
#endif
#endif
		return thisThreadsId;
	}


};

//==========================
/**
 * \class WaitThread
 *
 * \ingroup SGF_Util
 *
 * \brief
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2014
  */
class  SGE_API WaitThread{
public:
    /** constrói o objeto, mas não inicia o novo thread ainda
	**/
    WaitThread();

    /** constrói o objeto, e já inicia o novo thread
	\param thread: a função que será executada pelo novo thread
	\param arg: os parâmetros que serão passados para função a ser executada
	**/
    WaitThread(Thread::ThreadFunction thread, void * arg);

    /** \brief inicia um thread
	\param thread: o thread a ser iniciado
	\param arg: osparâmetros que serão passados para a função a ser executada
	**/
    void start(Thread::ThreadFunction thread, void * arg);

	/** \brief retorna true se o thread estiver rodando
	**/
    bool isRunning();
	/** \brief espera até que o thread termine
	**/
    void kill();

    virtual ~WaitThread();

public:
    /** \brief realmente roda o thread
	**/
    void doRun();

protected:
    Thread::Lock _my_doneLock;
    Thread::ThreadId_t _my_thread;
    volatile bool _my_done;
    void * _my_pArg;
    Thread::ThreadFunction _my_function;
};


/**
 * \class ThreadBoolean
 *
 * \ingroup SGF_Util
 *
 * \brief wraps a boolean with lock/unlock while checking/setting it
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2014
  */
class  SGE_API ThreadBoolean{
public:
    ThreadBoolean(volatile bool & what, Thread::Lock & lock);
	/** retorna o valor da variável boolean mas antes faz um lock nela
	\return: valor (verdadeiro ou falso) que estava armazenado
	**/
    bool get();
	/** seta o valor da variável boolean mas antes faz um lock nela
	\param value: valor (verdadeiro ou falso) a ser armazenado
	**/
    void set(bool value);

protected:
    volatile bool & _my_what;
    Thread::Lock & _my_lock;
};

/**
 * \class Future
 *
 * \ingroup SGF_Util
 *
 * \brief Computes stuff in a separate thread and gives it back when you ask for it.
 * As soon as the future is created a thread will start executing and compute
 * whatever it is that the class is supposed to do. You can then call `get'
 * on the future object to get the result. If the thread is still executing
 * then `get' will block until the future completes. If the future has already
 * completed then `get' will return immediately with the computed value.
 * The use case is computing something that has to be used later:
 *  Future future;
 *  future.start(); // might take a while to compute
 *  do_stuff_that_takes_a_while(); // future might finish sometime in here
 *  Object o = future.get(); // future is already done
 *
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2014
  */
template<class X>
class SGE_API  Future{
public:
    Future():
    thing(0),
    thread(uninitializedValue),
    done(false),
    exception(NULL),
    ran(false){
    }

    virtual ~Future(){
        Thread::joinThread(thread);
        delete exception;
    }

    virtual X get(){
        /* make sure the future has been started */
        if (Thread::isUninitialized(thread)){
            start();
        }
        Exception::CBase * failed = NULL;
        bool ok = false;
        while (!ok){
            future.acquire();
            if (!done){
                future.release();
                SGF::Util::rest(1);
            } else {
                ok = true;
            }
        }
        if (exception != NULL){
            failed = exception;
        }
        X out = thing;
        future.release();
        if (failed){
            failed->throwSelf();
        }
        return out;
    }

    virtual void start(){
        if (ran){
            return;
        }
        if (!Thread::createThread(&thread, NULL, (Thread::ThreadFunction) runit, this)){
            //Debug::debug(Debug::error,__FILE__) << "Could not create future thread. Blocking until its done" << endl;
            runit(this);
        }
        ran = true;
    }

protected:
    bool isDone(){
        Thread::ScopedLock scoped(future);
        return done;
    }

    static void * runit(void * arg){
        Future<X> * me = (Future<X>*) arg;
        try{
            me->compute();
        } catch (const CLoadException & load){
            me->exception = new CLoadException(load);
        } catch (const CTokenException & t){
            me->exception = new CTokenException(t);
        } catch (const CMugenException & m){
            me->exception = new CMugenException(m);
        } catch (const Exception::CBase & base){
            me->exception = new Exception::CBase(base);
        } catch (...){
            me->exception = new Exception::CBase(__FILE__, __LINE__);
        }
        me->future.acquire();
        me->done = true;
        me->future.release();
       return NULL;
    }

    virtual void set(X x){
        this->thing = x;
    }

    virtual void compute() = 0;

    X thing;
    Thread::ThreadId_t thread;
    Thread::LockObject future;
    volatile bool done;
    /* if any exceptions occur, throw them from `get' */
    Exception::CBase * exception;
    /* if the future was already started this is true so it can't be
     * accidentally started twice
     */
    bool ran;
};

} //end Thread
} //end util
} //end SGF
#endif
