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

#include "util/SGF_Timer.h"
//#include "init.h"
#include "util/SGF_Util.h"
#include "SGF_Global.h"
#include "util/SGF_SdlManager.h"
#include "util/SGF_Thread.h"
#include "util/SGF_Debug.h"

using namespace std;
namespace SGF {

namespace Util{

struct TimerInfo{
	 typedef void (*func)();
    TimerInfo( func pFunctionPointer, int y):
        tick(NULL), frequency(y){tick=pFunctionPointer;}

    func tick;
    int frequency;
};
static volatile bool run_timer=true;
Util::Thread::Lock run_timer_lock;
Util::Thread::ThreadBoolean run_timer_guard(run_timer, run_timer_lock);
vector<Util::Thread::ThreadId_t> running_timers;




/* game counter, controls FPS */
static void inc_speed_counter(){
    /* probably put input polling here, InputManager::poll(). no, don't do that.
     * polling is done in the standardLoop now.
     */
    Global::speed_counter += 1;
	//Debug::debug(Debug::sdlmanager,__FUNCTION__)<<endl << "Global::speed_counter = "<< Global::speed_counter << " / SDL_GetTicks(): " << SDL_GetTicks() << endl;
	
}
/* if you need to count seconds for some reason.. */
static void inc_second_counter() {
    Global::second_counter += 1;
}

static void closeTimers(){
    run_timer_guard.set(false);
    for (vector<Util::Thread::ThreadId_t>::iterator it = running_timers.begin(); it != running_timers.end(); it++){
        Util::Thread::ThreadId_t timer = *it;
        Util::Thread::joinThread(timer);
    }
    running_timers.clear();
}
void * do_wait(void * timer_){
    CTimer * timer = (CTimer *) timer_;
    unsigned int now = Global::second_counter;
    /* add 1 because the current time is in between X and X+1 */
    while (Global::second_counter - now < timer->wait+1){
        Util::rest(50);
        bool do_stop = false;
        Thread::acquireLock(&timer->lock);
        do_stop = timer->stopped;
        Thread::releaseLock(&timer->lock);
        if (do_stop){
            return NULL;
        }
    }
    timer->func(timer->arg);
    return NULL;
}

CTimer::CTimer(unsigned int seconds_to_wait, timeout func, void * arg):
wait(seconds_to_wait),
func(func),
arg(arg),
stopped(false){
    Thread::initializeLock(&lock);
    Thread::createThread(&timer, NULL, (Util::Thread::ThreadFunction) do_wait, this);

}

void CTimer::stop(){
    Thread::acquireLock(&lock);
    stopped = true;
    Thread::releaseLock(&lock);
    Thread::joinThread(timer);
}

//==========================================================

static void * do_timer(void * arg){
    TimerInfo info = *(TimerInfo *) arg;
    uint32_t delay = (uint32_t)(1000.0 / (double) info.frequency);

    /* assuming SDL_GetTicks() starts at 0, this should last for about 50 days
     * before overflowing. overflow should work out fine. Assuming activate occurs
     * when the difference between now and ticks is at least 6, the following will happen.
     * ticks      now        now-ticks
     * 4294967294 4294967294 0
     * 4294967294 4294967295 1
     * 4294967294 0          2
     * 4294967294 1          3
     * 4294967294 2          4
     * 4294967294 3          5
     * 4294967294 4          6
     * Activate
     * 3          5          2
     * 3          6          3
     * 3          7          4
     * 3          8          5
     * 3          9          6
     * Activate
     *
     * Can 'now' ever be much larger than 'ticks' due to overflow?
     * It doesn't seem like it.
     */
    uint32_t ticks = SDL_GetTicks();

    /* TODO: pass in some variable that tells this loop to quit */
   
    while (run_timer_guard.get()){
        uint32_t now = SDL_GetTicks();
        while (now - ticks >= delay){
            // Global::debug(0) << "Tick!" << endl;
            info.tick();
            ticks += delay;
        }
        SDL_Delay(1);
    }

    delete (TimerInfo *) arg;

    return NULL;
}

static Util::Thread::ThreadId_t start_timer(void (*func)(), int frequency){
    TimerInfo * speed = new TimerInfo(func, frequency);
	
	/*
    speed.tick = func;
    speed.frequency = frequency;
	*/
    Util::Thread::ThreadId_t thread;
    Util::Thread::createThread(&thread, NULL, (Util::Thread::ThreadFunction) do_timer, (void*) speed);
	
	return thread;
}



void startTimers(){
#ifdef SGF_USE_INTERNAL_TIMER	
	Util::Thread::initializeLock(&run_timer_lock);
    run_timer = true;
    run_timer_guard.set(true);

    running_timers.push_back(start_timer(inc_speed_counter, Global::TICS_PER_SECOND));  //frequencia 40 vezes por segundo ou a cada 25 ms ou 0,025 s
    running_timers.push_back(start_timer(inc_second_counter, 1));  //frequencia 1 vez por segundo
 

#endif
	
}

void stopTimers(){
   closeTimers();
}
}
} //end SGF
