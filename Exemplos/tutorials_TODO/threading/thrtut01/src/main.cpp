
#include <io.h>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <iostream>


#include "SGF.h"

using namespace std;
using std::set_terminate;
using std::set_unexpected;
using std::set_new_handler;

#undef printf


#include <iostream>
using namespace std;
using namespace SGF::Util::Thread;
/*
 * CIncrementThread
 * Class derived from CThread which redefines OnTask
 *
 */
class CIncrementThread : public SGF::Util::Thread::CThread
{
public:
	int counter;

	virtual bool onTask( LPVOID lpv )
	{
		ThreadId_t id;

		getId(&id);
		if( lpv )
		{
			int *pInt = (int *)lpv;

			//dont' use cout here, output could be broken up due to threading
			printf("\tthread(%ld, counter+%d=%d, counter incremented\n",id,*pInt,(counter+=*pInt));
		}
		return true;
	}

	virtual bool onTask()
	{
		ThreadId_t id;

		getId(&id);
		//don't use cout here, output could be broken up due to threading
                m_mutex.Lock();  // protect the counter variable
		  printf("\tthread(%ld, counter++= %d, counter incremented)\n",id,(++counter));
                m_mutex.Unlock();


		return true;
	}

        int GetValue()
        {
            int counterValue = 0;
            m_mutex.Lock();       // protect the counter variable
              counterValue = counter;
            m_mutex.Unlock();
            return counter;
         }
           
        void Reset()
        {
            m_mutex.Lock();
               counter = 0;
            m_mutex.Unlock();
        }

	CIncrementThread(){counter=0;}
	~CIncrementThread(){}
};

class CTaskIncrementer: public CTask
{
private:
	int counter;
	int incr;
public:
	void SetIncr(int iValue) 
	{
		m_mutex.Lock();
		  incr = iValue;
	    m_mutex.Unlock();
	}

	int GetIncrementValue()
	{
		int incrValue;
		m_mutex.Lock();
		  incrValue=incr;
		m_mutex.Unlock();
		return incrValue;
	}

	int GetValue()
	{
		int counterValue = 0;
		m_mutex.Lock();       // protect the counter variable
		  counterValue = counter;
		m_mutex.Unlock();
		return counter;
	}

	bool Task() 
	{
		ThreadId_t id;

	    Thread(&id);
		m_mutex.Lock();
		  printf("\tthread(%ld, counter+%d=%d, counter incremented\n",id,incr,(counter+=incr));
	    m_mutex.Unlock();
		return true;
	}
	CTaskIncrementer(){counter=0;}
	~CTaskIncrementer(){}
};



/*
 *
 * MyTaskClass
 * class derived from CTask which redefines Task
 * Task is called by CThreads OnTask member function.
 *
 */
class MyTaskClass: public CTask
{
public:
	bool Task()
	{
		cout << "\tperformed a ctask task\n";
		return true;
	}
	MyTaskClass(){}
	~MyTaskClass(){}
};

//This is for the normal PC
//The programm entry point
int main(int argc,char *argv[])
{
    printf("TESTE");
	int increment=10;

	CIncrementThread *pThreadInc;

	cout << "\n****** T H R E A D  T E S T *********\n\n";

	cout << "--INSTANTIATING CINCREMENTTHREAD DERIVED FROM CTHREAD\n";
	pThreadInc = new CIncrementThread;

	if( pThreadInc )
	{
		if( pThreadInc->pingThread(500) )
		{
			cout << "\nSENDING EVENT + 10\n";
			pThreadInc->addEvent((LPVOID)&increment);
			Sleep(500);
			cout << "\nSENDING EVENT ++\n";
			pThreadInc->addEvent();
			Sleep(500);
		}
		else {
			cout << "\nTHREAD DID NOT START\n";
			exit(0);
		}
		cout << "\n--CHANGING THREAD MODEL TO INTERVAL BASED\n";
		pThreadInc->setThreadType(ThreadTypeIntervalDriven,100);
		Util::rest(500);
		pThreadInc->setThreadType();
		Util::rest(500);
		cout << "\nTHREAD MODEL RESET TO EVENT DRIVEN\n";
		cout << "\n--SENDING + 10\n";
		pThreadInc->addEvent((LPVOID)&increment);
		Util::rest(500);
		cout << "\n--DESTROYING OBJECT\n";
		delete pThreadInc;
		Util::rest(500);
	}
	else
	{
		cout << "FAILED TO ALLOCATE THREAD\n";
		exit(0);
	}

	cout << "\n--INSTANTIATING AN ARRAY OF TEN CINCREMENTTHREADS DERIVED FROM CTHREAD\n";
	pThreadInc = new CIncrementThread [10];
	if( pThreadInc )
	{
		if( pThreadInc[9].pingThread(2000) )
		{
			for(int i=0; i<10 ; i++ )
			{
				pThreadInc[i].addEvent();
			}
			Util::rest(500);
			cout << "\n\n--DESTROYING OBJECT ARRAY\n";
			delete [] pThreadInc;
		}
		else {
			cout << "\nTHREADS DID NOT START\n";
			exit(0);
		}
	}
	else {
		cout << "FAILED TO ALLOCATE THREADS\n";
		exit(0);
	}

	cout << "\n--INSTANTIATING A CINCRMENTTHREAD BY DECLARATION\n";
	{
		CIncrementThread th;

		if( th.pingThread(2000) )
		{
			cout << "\nSENDING EVENT\n";
			th.addEvent();
			Util::rest(500);
		}
		else
		{
			cout << "FAILED TO START THREAD\n";
			exit(0);
		}
		cout << "\nLEAVING SCOPE\n";
		
	}

    cout << "\n--INSTANTIATING A CINCREMENTTHREAD BY DECLARATION\n";
	{
		CIncrementThread MyThread; // object allocated and thread started
		int two = 2;
		while( MyThread.GetValue() < 20 )
		{
			MyThread.addEvent();  // increment value by one
			Util::rest(100);        // pauses the root thread for 100 milli-seconds
		}

		MyThread.Reset();
		while( MyThread.GetValue() < 40 )
		{
			MyThread.addEvent(&two);
			Util::rest(100);
		}

	}

	cout << "--INSTANTIATING THE ORIGIONAL CTHREAD CLASS BY DECLARATION\n";
	{
		MyTaskClass myTask;
		CThread thread;
		thread.addEvent(&myTask);
		while( myTask.Status() != TaskStatusCompleted )
				Util::rest(500);
		thread.addEvent(&myTask);
		myTask.Wait(1);
	}

	cout << "\n--INSTANTIATING THE ORIGIONAL CTHREAD CLASS BY DECLARATION\n";
	{
		MyTaskClass *pMyTask = new MyTaskClass;

		CThread thread;
		thread.addEvent(pMyTask);
		if( pMyTask->Wait(1) )
		{
			cout << "\tfreeing pMyTask\n";
			delete pMyTask;
		}
	}

	cout << "\n--INSTANTIATING a CTHREAD AND USING A CTASK OBJECT\n";
	{
		CTaskIncrementer incr;
		CThread thr;

		if( thr.pingThread(200) )
		{
			incr.SetIncr(2);
			while( incr.GetValue() < 40 ) {
				thr.addEvent(&incr);
				Util::rest(100);
			}
		}
	}
	cout << "\ndone\n";
    return 0;

}



