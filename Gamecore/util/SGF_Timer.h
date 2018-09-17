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
#ifndef _util_timer_h
#define _util_timer_h
#include <iostream>
#include <vector>
#include "../SGF_Config.h"
#include "SGF_Thread.h"

using namespace std;
namespace SGF {

namespace Util{

/**
 * \class Timer
 *
 * \ingroup SGF_Util
 * 
 * \brief Chama uma função ou método depois de X segundos a menos que stop() seja chamado antes
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CTimer{
public:
    typedef void (*timeout)(void * arg);
    CTimer(unsigned int seconds_to_wait, timeout func, void * arg);
    
    void stop();

    friend void * do_wait(void * timer_);

protected:
    unsigned int wait;
    timeout func;
    void * arg;
    bool stopped;
    Thread::Lock lock;
    Thread::ThreadId_t timer;
};

void startTimers();
void stopTimers();
}



} //end SGF
#endif
