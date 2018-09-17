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
#ifndef SDLMANAGER_
#define SDLMANAGER_
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"
#include "../SGF_Global.h"
#include "SGF_UtilStructs.h"
#include "all_sound.h"
#include "../../ExternalLibs/SDL2_mixer-2.0.2/SDL_mixer.h"
#include "../external/SDL_framerate.h"
#include "SGF_FontSystem.h"
#include "../external/glSDL.h"
#include "../external/fastevents.h"
#include "../input/SGF_InputManager.h"


#define NUM_SPRITES	100
#define MAX_NUM_WINDOWS 10
#define MAX_SPEED 	1

namespace SGF {


struct pformat {
    Uint32 id;
    const char* idstr;
};

class CSoundSystem;
class CTTFFont;
class CInputManager;



/**
 * \class CSDLManager
 *
 * \ingroup SGF_Util
 *
 * \brief Singleton de gerenciamento do API do SDL
 *
 * Gerencia VIDEO, AUDIO, FONTE, FRAMERATE, TIMERS
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

class  SGE_API CSDLManager
{
public:

//Contructor and Desconstructor

    ~CSDLManager();
    bool Init();
	bool InitWindows();
    void CleanSDL();

public:
    CSoundSystem m_AudioSystem;
	//call back function to increment the timer of seconds
#ifdef SGF_USE_INTERNAL_TIMER
	static void inc_speed_counter();
	static void inc_second_counter();
#else
	static Uint32 inc_second_counter(Uint32 interval , void *param);
	static Uint32 inc_speed_counter(Uint32 interval , void *param);

#endif
	SDL_TimerID count_seconds;
	SDL_TimerID count_speed;

	static void FPS_Manager();
	//The joystick that will be used
   static Uint32 nFrameCount;  //contador de frames desenhados na tela
   static CInputManager *s_GameInput;
   static void setInputManager (CInputManager &curInputManager) {
        s_GameInput= &curInputManager;
	}

   static SDLState_t * CreateState(Uint32 flags, int numWindows=1);
   SDLState_t *state;
   SDL_BlendMode blendMode;

   static CSDLManager* GetInstance();
   static void quit(void);
   bool cycle_color;
   bool cycle_alpha;
   static CTTFFont *m_Text;
   static float nFps;
   static const char* PixelFormatToString(Uint32 pformat);
   //!Window Methods
   void setWindowTitle(const char * title, int window=0);
   void setWindowIcon(const char *icon, int window=0);
   void setWindowX(int x, int window=0);
   void setWindowY(int y, int window=0);
   void setWindowCoordinates(int x, int y, int w, int h, int window=0);
   void setWindowWidth(int w,int window=0);
   void setWindowHeight(int h, int window=0);
   static void CommonQuit(SDLState_t * state);

   void changeGameFPS();

   // check state methods

   bool isNetworkStarted() {return this->state->startedModules.NETWORK;};
   bool isWindowStarted() {return this->state->startedModules.WINDOW;};
   bool isTTFStarted(){return this->state->startedModules.TTF;};
   bool isAudioStarted(){return this->state->startedModules.AUDIO;};
   bool isFrameRMStarted(){return this->state->startedModules.FRAMERATEMANAGER;};
   bool isTimerStarted(){return this->state->startedModules.TIMER;};
   bool isFastEventsStarted() {return this->state->startedModules.FASTEVENTS;};
   bool isJoysTickStarted(){return this->state->startedModules.JOYSTICK;}
   bool isTextSuportStarted(){return this->state->startedModules.TEXTSUPPORT;};

private:
	bool videoInitiated;
	//!========================GL

	void PrintEvent(SDL_Event * event);
	///////////////////////
	CSDLManager();
	//! ponteiro para a instância da classe
	static CSDLManager* pCSDLManager;
	static Util::Thread::LockObject sldManagerLock;
	static void PrintRenderer(SDL_RendererInfo * info);
	static void PrintPixelFormat(Uint32 format);
	static void PrintBlendMode(Uint32 flag);
	static void PrintRendererFlag(Uint32 flag);

	bool CommonInit(SDLState_t * state);

	bool InitWindows(SDLState_t * state);  //Cria Janelas
	int flags; // SDL Initialization flags
	//Uint8* deltaPtr;
    static Uint32 nowTime,lastTime;
    static FPSmanager m_FPSmanager;

};


} //end SGF
#endif /*SDLMANAGER_*/
