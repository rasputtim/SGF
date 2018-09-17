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



#ifndef _S_G_F_gui_timer_h
#define _S_G_F_gui_timer_h

#include "../SGF_Config.h"

#ifdef sleep
#undef sleep
#endif

#if defined (_WIN32)
#include <windows.h>
#else
#include <time.h>
#include <sys/time.h>
#endif
namespace SGF{
namespace Gui {
class CTimer
{
		private:
#if defined (SGE_ON_WINDOWS)
			//! tempo inicial para o timer
    			unsigned long long startTime;
    			
    			//! tempo atual para comparar com o tempo inicial
    			unsigned long long currentTime;
#endif
#if defined (SGE_ON_LINUX)

			//! tempo inicial para o timer
    			timeval startTime;
    		
			//! tempo atual para comparar com o tempo inicial
			timeval currentTime;
#endif
		public:
			
			CTimer();
			
			
			~CTimer();
			
			/** retorna o tempo em microsegundos */
			unsigned int usecs();
			
			/** \brief  retorna o tempo em millisegundos 
			*/
			unsigned int msecs();
			
			/** \brief retorna o tempo atual em segundos */
			unsigned int secs();
			
			/** \brief reinicializa o timer */
			void reset();
			
			/** \brief para o processamento por x milisegundos
			* \param msecs: milisegundos de parada
			*/
			static void sleep(int msecs);
			/** para o processamento por x segundos
			* \param msecs: segundos de parada
			*/
			static void sleepSecs(int secs);
};

}
} //end SGF
#endif
