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



#include "gui/SGF_GuiTimer.h"
#include "util/SGF_Util.h"

using namespace std;
namespace SGF{
namespace Gui {

	CTimer::CTimer()
	{
		// Setup initial
		reset();
	}
	
	CTimer::~CTimer()
	{
		
	}
#if defined (SGE_ON_WINDOWS)
	unsigned int CTimer::usecs()
	{
    		static bool onetime = 0;
    		static unsigned long long freq = 0;
    
    		if(!onetime) {
        		onetime = true;
	    		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    		}
    
    		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
    
    		currentTime *= 1000000;
    		currentTime /= freq;
    
    		return currentTime - startTime * 1000;
	}

	unsigned int CTimer::msecs()
	{
    		currentTime = GetTickCount();
    
    		return currentTime - startTime;

	}
	
	unsigned int CTimer::secs()
	{
		currentTime = GetTickCount();
		
		return (currentTime - startTime) / 1000;

	}
	
	// Reset timer
	void CTimer::reset()
	{
    		startTime = GetTickCount();

	}
	
	
	void CTimer::sleep(int msecs)
	{
            Sleep(msecs);

	}
	void CTimer::sleepSecs(int secs)
	{
            Sleep(secs*1000);

	}
#endif
#if defined (SGE_ON_LINUX)

unsigned int CTimer::usecs()
	{

    		gettimeofday(&currentTime, 0);
    
    		return (unsigned long)((currentTime.tv_sec - startTime.tv_sec) / 1000)
		    + (unsigned long)((currentTime.tv_usec - startTime.tv_usec));

	}

	unsigned int CTimer::msecs()
	{

    		gettimeofday(&currentTime, 0);
    
    		return (unsigned long)((currentTime.tv_sec - startTime.tv_sec) * 1000)
		    + (unsigned long)((currentTime.tv_usec - startTime.tv_usec) / 1000);

	}
	
	unsigned int CTimer::secs()
	{

    		gettimeofday(&currentTime, 0);
    
    		return (unsigned long)(currentTime.tv_sec - startTime.tv_sec);

	}
	
	// Reset timer
	void CTimer::reset()
	{

    		gettimeofday(&startTime, 0);

	}
	
	
	void CTimer::sleep(int msecs)
	{
            Util::rest(msecs);
            /*
		struct timespec timeOut;
		timeOut.tv_sec = 0;
		timeOut.tv_nsec = (msecs * 1000000);
		nanosleep(&timeOut, NULL);

*/
	}
	void CTimer::sleepSecs(int secs)
	{
            Util::rest(secs*1000);
            /*
		struct timespec timeOut;
		timeOut.tv_sec = 0;
		timeOut.tv_nsec = (secs * 1000000 * 1000);
		nanosleep(&timeOut, NULL);

	*/
	}
#endif
	}
	} //end SGF
