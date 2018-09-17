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



#include "util/SGF_SdlManager.h"
#include "SGF_Global.h"
#include "graphics/all.h"
#include "util/SGF_Debug.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <time.h>
#include "util/SGF_FileSystem.h"
#include "resource/all.h"//inicializa variáveis estáticas
#include "configuration/SGF_Configuration.h"
#include "util/SGF_Timer.h"
#include "network/SGF_Network.h"
#include "SDL_stdinc.h"


using namespace std;

namespace SGF {

class CInputManager;

static int _strcasecmp(const char *str1, const char *str2)
{
    char a = 0;
    char b = 0;
    while (*str1 && *str2) {
        a = SDL_tolower((unsigned char) *str1);
        b = SDL_tolower((unsigned char) *str2);
        if (a != b)
            break;
        ++str1;
        ++str2;
    }
    a = SDL_tolower(*str1);
    b = SDL_tolower(*str2);
    return (int) ((unsigned char) a - (unsigned char) b);
}

class CConfiguration;
namespace Util{
class CTimer;
}

CSDLManager* CSDLManager::pCSDLManager=NULL;
Util::Thread::LockObject CSDLManager::sldManagerLock;
//extern ConsoleInformation *mMainConsole;
Uint32 CSDLManager::nowTime=0;
Uint32 CSDLManager::lastTime=0;
Uint32 CSDLManager::nFrameCount=0;


float CSDLManager::nFps=0;
FPSmanager CSDLManager::m_FPSmanager;
CInputManager *CSDLManager::s_GameInput=NULL;
CTTFFont *CSDLManager::m_Text=NULL;

//Destructor

pformat pixel_format[]={
    {SDL_PIXELFORMAT_INDEX1LSB, "SDL_PIXELFORMAT_INDEX1LSB"},
    {SDL_PIXELFORMAT_INDEX1MSB, "SDL_PIXELFORMAT_INDEX1MSB"},
    {SDL_PIXELFORMAT_INDEX4LSB, "SDL_PIXELFORMAT_INDEX4LSB"},
    {SDL_PIXELFORMAT_INDEX4MSB, "SDL_PIXELFORMAT_INDEX4MSB"},
    {SDL_PIXELFORMAT_INDEX8, "SDL_PIXELFORMAT_INDEX8"},
    {SDL_PIXELFORMAT_RGB332, "SDL_PIXELFORMAT_RGB332"},
    {SDL_PIXELFORMAT_RGB444, "SDL_PIXELFORMAT_RGB444"},
    {SDL_PIXELFORMAT_RGB555, "SDL_PIXELFORMAT_RGB555"},
    {SDL_PIXELFORMAT_BGR555, "SDL_PIXELFORMAT_BGR555"},
    {SDL_PIXELFORMAT_ARGB4444, "SDL_PIXELFORMAT_ARGB4444"},
    {SDL_PIXELFORMAT_ABGR4444, "SDL_PIXELFORMAT_ABGR4444"},
    {SDL_PIXELFORMAT_ARGB1555, "SDL_PIXELFORMAT_ARGB1555"},
    {SDL_PIXELFORMAT_ABGR1555, "SDL_PIXELFORMAT_ABGR1555"},
    {SDL_PIXELFORMAT_RGB565, "SDL_PIXELFORMAT_RGB565"},
    {SDL_PIXELFORMAT_BGR565, "SDL_PIXELFORMAT_BGR565"},
    {SDL_PIXELFORMAT_RGB24, "SDL_PIXELFORMAT_RGB24"},
    {SDL_PIXELFORMAT_BGR24, "SDL_PIXELFORMAT_BGR24"},
    {SDL_PIXELFORMAT_RGB888, "SDL_PIXELFORMAT_RGB888"},
    {SDL_PIXELFORMAT_BGR888, "SDL_PIXELFORMAT_BGR888"},
    {SDL_PIXELFORMAT_ARGB8888, "SDL_PIXELFORMAT_ARGB8888"},
    {SDL_PIXELFORMAT_RGBA8888, "SDL_PIXELFORMAT_RGBA8888"},
    {SDL_PIXELFORMAT_ABGR8888, "SDL_PIXELFORMAT_ABGR8888"},
    {SDL_PIXELFORMAT_BGRA8888, "SDL_PIXELFORMAT_BGRA8888"},
    {SDL_PIXELFORMAT_ARGB2101010, "SDL_PIXELFORMAT_ARGB2101010"},
    {SDL_PIXELFORMAT_YV12, "SDL_PIXELFORMAT_YV12"},
    {SDL_PIXELFORMAT_IYUV, "SDL_PIXELFORMAT_IYUV"},
    {SDL_PIXELFORMAT_YUY2, "SDL_PIXELFORMAT_YUY2"},
    {SDL_PIXELFORMAT_UYVY, "SDL_PIXELFORMAT_UYVY"},
    {SDL_PIXELFORMAT_YVYU, "SDL_PIXELFORMAT_YVYU"}
};

CSDLManager::~CSDLManager()
{

Debug::debug(Debug::sdlmanager,__FUNCTION__) << "BEGIN CSDLManager::~CSDLManager"<<endl;
if(s_GameInput) delete s_GameInput;
if(state) {
	 //for (int i =0 ;i < state->num_windows; i++) if (state->Screen[i]) delete state->Screen[i];
	 //if(state->Screen) ::SDL_free(state->Screen);
	 Debug::debug(Debug::sdlmanager,__FUNCTION__) << "Will Clean AuDIO SYSTEM"<<endl;
	 //if (state->Buffer !=NULL){ delete state->Buffer; state->Buffer=NULL;}
	 //if (state->Scaler !=NULL){ delete state->Scaler; state->Scaler=NULL;}
	 if (state->startedModules.AUDIO)m_AudioSystem.CleanUp();
	 Debug::debug(Debug::sdlmanager,__FUNCTION__) << "Will Clean SDL TTF"<<endl;
   	//Close the joystick

	//Clear SDL_ttf
	if (state->startedModules.TTF) {
		TTF_Quit();
	}
	 Debug::debug(Debug::sdlmanager,__FUNCTION__) << "Will Clean FASTEVENTS"<<endl;
	if (state->startedModules.FASTEVENTS && state->startedModules.TIMER) FE_Quit();
    Debug::debug(Debug::sdlmanager,__FUNCTION__) << "Will Clean STATE"<<endl;
	CommonQuit(state);

	 CleanSDL();
//	 state=NULL;
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "END "<<endl;

}
//if(m_Text) delete m_Text;  //Todo verificar porque não deleta
//Colors::destroy_colors();
}


//Constructor
CSDLManager::CSDLManager():
count_seconds(0),
count_speed(0),
state(NULL),
blendMode(SDL_BLENDMODE_BLEND),
cycle_color(false),
cycle_alpha(true),
videoInitiated(0),
flags(0)
{
//Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::CSDLManager // Criando Instância do CSDLManager"<<endl;
}

bool CSDLManager::InitWindows()
{
	state = CGlobalConfiguration::getsdlConfig();
	if (InitWindows(state)<=0) return false;
	else return true;
}

//Init the SDL SUB systems
bool CSDLManager::Init()
{
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init()"<<endl;
	int error = true;
	//state = CreateState(SDL_INIT_VIDEO,numWindows);
	state = CGlobalConfiguration::getsdlConfig();
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "STATE = " << state << endl;
	Global::second_counter=0;
	Global::speed_counter=0;
	Global::speed_counter=0;
	if (state->initModules.VIDEO) {
	flags = SDL_GLSDL ;
	//int i, done;
    //SDL_Event event;
    //Uint32 then, now, frames;

	//blendMode = SDL_BLENDMODE_NONE;
    //blendMode = SDL_BLENDMODE_MASK;
    //blendMode = SDL_BLENDMODE_BLEND;
    //blendMode = SDL_BLENDMODE_ADD;
    //blendMode = SDL_BLENDMODE_MOD;
    //scaleMode = SDL_TEXTURESCALEMODE_NONE;
    //scaleMode = SDL_TEXTURESCALEMODE_FAST;
    //scaleMode = SDL_TEXTURESCALEMODE_SLOW;
    //scaleMode = SDL_TEXTURESCALEMODE_BEST;
    //cycle_color = SDL_TRUE;
    //cycle_alpha = SDL_TRUE;
    //Now init our Video System
    if((flags & SDL_GLSDL) == SDL_GLSDL)
		Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init() // Requesting glSDL. // " << endl;
//	if((flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF)
	//	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init() // Requesting double buffered display. // " << endl;
//	if((flags & SDL_FULLSCREEN) == SDL_FULLSCREEN)
//		Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init() // Requesting fullscreen display. // " << endl;
//	    Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init() // Display size: // " << SCREEN_W <<" , "  << SCREEN_H << endl;

	/* Initialize SDL framework */
    if (!CommonInit(state)) {
		state->startedModules.VIDEO=false;
        error=false;
		quit();
    }
	state->startedModules.VIDEO=true;
	 Debug::debug(Debug::sdlmanager,__FUNCTION__) << "VIDEO OK"<<endl;

}

//=========================== INIT AUDIO ==============================
	if (state->initModules.AUDIO) {
		//Init SDL and the sub-systems of it(VIDEO, TIMER AND AUDIO SYSTEM)
		if(SDL_Init(SDL_INIT_AUDIO) < 0 )
		{
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Failed"<<endl;
			state->startedModules.AUDIO=false;
			error = false;
		}else {
		    Debug::debug(Debug::sdlmanager,__FUNCTION__) << "AUDIO OK"<<endl;
			m_AudioSystem.InitSystem();
			state->startedModules.AUDIO=true;
		}
	}
	//=========================== INIT JOYSTICK ==============================
	if (state->initModules.JOYSTICK) {
		//Init SDL and the sub-systems of it(VIDEO, TIMER AND AUDIO SYSTEM)
		if(SDL_Init(SDL_INIT_JOYSTICK) < 0 )
		{
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Failed"<<endl;
			state->startedModules.JOYSTICK=false;
			error = false;
		}else {
			state->startedModules.JOYSTICK=true;
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "JOYSTICK OK"<<endl;
		}
	}
	//=========================== INIT TIMER ==============================
	if (state->initModules.TIMER) {
    //Init SDL and the sub-systems of it(VIDEO, TIMER AND AUDIO SYSTEM)
    // O Timer SDL é utilizado pelo FEvents por isso necessita ser inicializado mesmo se usar SGF_USE_INTERNAL_TIMER
	if(SDL_Init(SDL_INIT_TIMER) < 0 )
    {
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Failed"<<endl;
			state->startedModules.TIMER=false;
			error = false;
	}else {
		state->startedModules.TIMER=true;

		//------------Set up SGF Timers-----------------------

		Debug::debug(Debug::sdlmanager,__FUNCTION__) << "TIMER OK"<<endl;

#ifdef SGF_USE_INTERNAL_TIMER
		Debug::debug(Debug::sdlmanager,__FUNCTION__) << "WILL START NEW TIMER"<<endl;
		Util::startTimers();
#else
		count_seconds = SDL_AddTimer(1000,&inc_second_counter,NULL);
		if(count_seconds == 0 )
		{
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Timer Seconds Failed"<<endl;
			error = false;
		} else {
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Timer Seconds OK"<<endl;
		}

		count_speed = SDL_AddTimer(1000/Global::TICS_PER_SECOND,&inc_speed_counter,NULL);

		if(count_speed == 0 )
		{
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Timer Speed Failed"<<endl;
			error = false;
		} else {
			Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Timer Speed OK"<<endl;
		}
#endif
		}

	}


   //=========================== INIT FRAME MANAGER ==============================
    if (state->initModules.FRAMERATEMANAGER) {
	SDL_initFramerate(&m_FPSmanager);
	SDL_setFramerate(&m_FPSmanager,Global::TICS_PER_SECOND);
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "FRAME MANAGER OK"<<endl;
	}
	//Set the icon for the application
    //SDL_WM_SetIcon(IMG_Load("icon.bmp"), NULL);
    //SDL_WM_SetCaption(OMTITLE,NULL);
    //==============FAST EVENTS ===============
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "WILL INIT FASTEVENTS: "<< state->initModules.FASTEVENTS<< " : " <<state->startedModules.TIMER <<endl;
	if (state->startedModules.TIMER && state->initModules.FASTEVENTS) {
#if 0
		int flag=0;

		    /* Toggle the event thread flags, based on OS requirements */
    #if defined(MUST_THREAD_EVENTS)
        flag |= SDL_INIT_EVENTTHREAD;
    #elif defined(CANT_THREAD_EVENTS)
        if ((flag & SDL_INIT_EVENTTHREAD) == SDL_INIT_EVENTTHREAD) {
            SDL_SetError("OS doesn't support threaded events");
            return -1;
        }
    #endif

       /* Start the event loop */
       if (SDL_StartEventLoop(flag) < 0) {
         return -1;
       }
#endif
	   //sdl already initialized
      //------------Set up FAST EVENTS TIMERS HERE-----------------------
     if (FE_Init()<0) {
		Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::SDL_Init Failed on Módule Fast Events"<<endl;
		state->startedModules.FASTEVENTS=false;
		error = false;
	 }
	 state->startedModules.FASTEVENTS=true;
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "FASTEVENTS OK"<<endl;

	}
	//=========================== INIT SDL TTF ==============================
	if (state->initModules.TTF) {
	if( TTF_Init() <0 )
    {
    Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init  init TTF Failed"<<endl;
	state->startedModules.TTF=false;
	error = false;
    }
	state->startedModules.TTF=true;
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "TTF OK"<<endl;
	// verificar antes se o nr da fonte existe

	try {
			m_Text = CResource::getTTFont("arial.ttf",30,30);

			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}
	m_Text->AvailableFonts->PrintFonts();
	}
	//Enable Unicode support
	if (state->initModules.TEXTSUPPORT) {
		Debug::debug(Debug::font,__FUNCTION__) << "ENABLING SDL UNICODE" << endl;
		// SDL 2.0 textsuport is enabled by default
		state->startedModules.TEXTSUPPORT=true;
	}
	//=======================INIT NETWORK==========================
	if (state->initModules.NETWORK) {
	#ifdef HAVE_NETWORKING
    Debug::debug(Debug::font,__FUNCTION__) << "INIT NETWORK" << endl;

	if (Network::init()){
		state->startedModules.NETWORK=true;
    atexit(Network::closeAll);
	}
	#endif
	}
	return error;



}

void CSDLManager::CleanSDL()
{
    Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager:: Cleaning SDL"<<endl;
    //if (mMainConsole)CON_Destroy(mMainConsole);

	//SDL_Quit();
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "END Cleaning SDL"<<endl;

}
#ifdef SGF_USE_INTERNAL_TIMER
/*
void CSDLManager::inc_speed_counter() {
    Global::speed_counter += 1;
	Debug::debug(Debug::sdlmanager,__FUNCTION__)<<endl << "Global::speed_counter = %i"<< Global::speed_counter << endl;
	//return Global::speed_counter;
}
void CSDLManager::inc_second_counter() {
    Global::second_counter += 1;
	//Debug::debug(Debug::sdlmanager,__FUNCTION__) << "Global::second_counter = %i"<< Global::second_counter << endl;
	//return Global::speed_counter;
}
*/

#else
Uint32 CSDLManager::inc_second_counter(Uint32 interval , void *param) {
    Global::second_counter += 1;
	//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<endl<< "Global::second_counter = %i"<< Global::second_counter <<endl;
	return Global::second_counter;
}

Uint32 CSDLManager::inc_speed_counter(Uint32 interval , void *param) {
    Global::speed_counter += 1;
	Debug::debug(Debug::sdlmanager,__FUNCTION__) <<endl << "Global::speed_counter = "<< Global::speed_counter<< "SDL_GetTicks: " << SDL_GetTicks() <<endl;
	return Global::speed_counter;
}

#endif

void CSDLManager::FPS_Manager()
{

    nowTime=SDL_GetTicks();   // numero de milisegundos desde a inicialização do SDL
    if(nowTime > lastTime+500)
    {
        nFps=(float)nFrameCount*1000 / (nowTime-lastTime);
        nFrameCount=0;
        lastTime=nowTime;
     }
	nFrameCount++;  //incrementa  o contador de frames
	SDL_framerateDelay(&m_FPSmanager); //aqui ele incrementa o numero de frames rodados

}

bool CSDLManager::CommonInit(SDLState_t * state)
{
    Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::CommonInit // -------------------------------------------"<<endl;

	int i, j, m, n;
    SDL_DisplayMode fullscreen_mode;
	//!Init Video
    if (state->flags & SDL_INIT_VIDEO) {
        if (state->verbose & VERBOSE_VIDEO) {
            n = SDL_GetNumVideoDrivers();
            if (n == 0) {
				Debug::debug(Debug::sdlmanager,__FUNCTION__) << "No built-in video drivers"<<endl;
                //fprintf(stderr, "No built-in video drivers\n");
            } else {
                Debug::debug(Debug::sdlmanager,__FUNCTION__) << "Built-in video drivers"<<endl;
                //fprintf(stderr, "Built-in video drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        Debug::debug(Debug::sdlmanager,__FUNCTION__)<<" / ";
                //fprintf(stderr, ",");
                    }
                    Debug::debug(Debug::sdlmanager,__FUNCTION__) <<SDL_GetVideoDriver(i);

					//fprintf(stderr, " %s", SDL_GetVideoDriver(i));
                }
                 Debug::debug(Debug::sdlmanager,__FUNCTION__) << endl;
                //fprintf(stderr, "\n");
            }
        }
        if (SDL_VideoInit(state->videodriver) < 0) {
            Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Couldn't initialize video driver: "<<SDL_GetError()<<endl;

			//fprintf(stderr, "Couldn't initialize video driver: %s\n",SDL_GetError());
            return SDL_FALSE;
		}else {  //não tirar essa parte do else. Feiot por mim para inicializar formatos
		// save format to work with surfaces
			videoInitiated = true;   //indicates that the video has been initiated sucssesfully
			int bpp;
            Uint32 Rmask, Gmask, Bmask, Amask;

		    n = SDL_GetNumVideoDisplays();
            Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Number of displays:: "<<n<<endl;
            //fprintf(stderr, "Number of displays: %d\n", n);
            for (i = 0; i < n; ++i) {
                Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Displays : "<<i<<endl;
           // fprintf(stderr, "Display %d:\n", i);
                //SDL_SelectVideoDisplay(i);
                SDL_DisplayMode mode;
                SDL_GetDesktopDisplayMode(i,&mode);

                SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask, &Gmask,
                                           &Bmask, &Amask);
                Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Current mode:   "<< SDL_GetCurrentVideoDriver()<<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Width:          "<< mode.w <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Height:	        "<< mode.h <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Refr. Rate:     "<< mode.refresh_rate << " Hz"<<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Bits per pixel: "<< bpp <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Pixel Format:   "<< PixelFormatToString(mode.format) <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Pixel Format:   "<< mode.format <<endl;

				//fprintf(stderr,
                //        "  Current mode: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                //        mode.w, mode.h, mode.refresh_rate, bpp,
                //        PixelFormatToString(mode.format));
                if (Rmask || Gmask || Bmask) {
                   //fprintf(stderr, "      Red Mask   = 0x%.8x\n", Rmask);
                    //fprintf(stderr, "      Green Mask = 0x%.8x\n", Gmask);
                    //fprintf(stderr, "      Blue Mask  = 0x%.8x\n", Bmask);
					Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Red Mask:   "<<  Rmask <<endl;
					Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Green Mask:   "<<  Gmask <<endl;
					Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Blue Mask:   "<<  Bmask <<endl;

					if (Amask) {
                        Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Alpha Mask:   "<<  Amask <<endl;
						//fprintf(stderr, "      Alpha Mask = 0x%.8x\n", Amask);
						//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Init Surface Format with Alpha:   "<<endl;

						//CBitmap::SDL_InitFormat(&state->surface_format,bpp, Rmask, Gmask, Bmask, Amask);
					}else {
						//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Init Surface Format no Alpha:   "<<endl;
						//CBitmap::SDL_InitFormat(&state->surface_format,bpp, Rmask, Gmask,Bmask, 0);
					}
					//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Surface Red Mask:   "<<  state->surface_format.Rmask <<endl;
					//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Surface Green Mask:   "<<  state->surface_format.Gmask <<endl;
					//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Surface Blue Mask:   "<<  state->surface_format.Bmask <<endl;
					///Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Surface Alpha Mask:   "<<  state->surface_format.Amask <<endl;
                    //Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Surface bpp:   " <<  (int)state->surface_format.BitsPerPixel <<endl;
					//Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Surface Bpp:   " <<  (int)state->surface_format.BytesPerPixel <<endl;
					//Debug::debug( 2 ) << "Surface RLoss : "<< (int)state->surface_format.Rloss<< endl;
					//Debug::debug( 2 ) << "Surface GLoss : "<< (int)state->surface_format.Gloss<< endl;
					//Debug::debug( 2 ) << "Surface BLoss : "<< (int)state->surface_format.Bloss<< endl;
					//Debug::debug( 2 ) << "Surface RShift: "<< (int)state->surface_format.Rshift<< endl;
					//Debug::debug( 2 ) << "Surface GShift : "<< (int)state->surface_format.Gshift<< endl;
					//Debug::debug( 2 ) << "Surface BShift : "<< (int)state->surface_format.Bshift<< endl;

                }
			}
		}
        if (state->verbose & VERBOSE_VIDEO) {
            Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Video driver: "<< SDL_GetCurrentVideoDriver()<<endl;

			//fprintf(stderr, "Video driver: %s\n",SDL_GetCurrentVideoDriver());
        }

        /* Upload GL settings */
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, state->gl_red_size);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, state->gl_green_size);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, state->gl_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, state->gl_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, state->gl_double_buffer);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, state->gl_buffer_size);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, state->gl_depth_size);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, state->gl_stencil_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, state->gl_accum_red_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, state->gl_accum_green_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, state->gl_accum_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, state->gl_accum_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_STEREO, state->gl_stereo);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, state->gl_multisamplebuffers);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, state->gl_multisamplesamples);
        if (state->gl_accelerated >= 0) {
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,
                                state->gl_accelerated);
        }
        SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, state->gl_retained_backing);
        if (state->gl_major_version) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, state->gl_major_version);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, state->gl_minor_version);
        }
        if (state->verbose & VERBOSE_MODES) {
            SDL_DisplayMode mode;
            int bpp;
            Uint32 Rmask, Gmask, Bmask, Amask;

            n = SDL_GetNumVideoDisplays();
            fprintf(stderr, "Number of displays: %d\n", n);
            for (i = 0; i < n; ++i) {
                fprintf(stderr, "Display %d:\n", i);
                //SDL_SelectVideoDisplay(i);

                SDL_GetDesktopDisplayMode(i, &mode);
                SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask, &Gmask, &Bmask, &Amask);
                Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Current mode:   "<< SDL_GetCurrentVideoDriver()<<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Width:          "<< mode.w <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Height:	        "<< mode.h <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Refr. Rate:     "<< mode.refresh_rate << " Hz"<<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Bits per pixel: "<< bpp <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Pixel Format:   "<< PixelFormatToString(mode.format) <<endl;
				Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Pixel Format:   "<< mode.format <<endl;

				//fprintf(stderr,
                //        "  Current mode: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                //        mode.w, mode.h, mode.refresh_rate, bpp,
                //        PixelFormatToString(mode.format));
                if (Rmask || Gmask || Bmask) {
                    Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Red Mask:   "<<  Rmask <<endl;
					Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Green Mask:   "<<  Gmask <<endl;
					Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Blue Mask:   "<<  Bmask <<endl;
					//fprintf(stderr, "      Red Mask   = 0x%.8x\n", Rmask);
                    //fprintf(stderr, "      Green Mask = 0x%.8x\n", Gmask);
                    //fprintf(stderr, "      Blue Mask  = 0x%.8x\n", Bmask);
                    if (Amask)
                        Debug::debug(Debug::sdlmanager,__FUNCTION__) <<"Alpha Mask:   "<<  Amask <<endl;
						//fprintf(stderr, "      Alpha Mask = 0x%.8x\n", Amask);
                }
				/* Print available fullscreen video modes */
                m = SDL_GetNumDisplayModes(i);
                if (m == 0) {
                    fprintf(stderr, "No available fullscreen video modes\n");
                } else {
                    fprintf(stderr, "  Fullscreen video modes:\n");
                    for (j = 0; j < m; ++j) {
                        SDL_GetDisplayMode(i,j, &mode);
                        SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask,
                                                   &Gmask, &Bmask, &Amask);
                        fprintf(stderr,
                                "    Mode %d: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                                j, mode.w, mode.h, mode.refresh_rate, bpp,
                                SDL_GetPixelFormatName(mode.format));
                        if (Rmask || Gmask || Bmask) {
                            fprintf(stderr, "        Red Mask   = 0x%.8x\n",
                                    Rmask);
                            fprintf(stderr, "        Green Mask = 0x%.8x\n",
                                    Gmask);
                            fprintf(stderr, "        Blue Mask  = 0x%.8x\n",
                                    Bmask);
                            if (Amask)
                                fprintf(stderr,
                                        "        Alpha Mask = 0x%.8x\n",
                                        Amask);
                        }
                    }
                }
            }
        }

        //SDL_SelectVideoDisplay(state->display);
        if (state->verbose & VERBOSE_RENDER) {
            SDL_RendererInfo info;

            n = SDL_GetNumRenderDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in render drivers\n");
            } else {
                fprintf(stderr, "Built-in render drivers:\n");
                for (i = 0; i < n; ++i) {
                    SDL_GetRenderDriverInfo(i, &info);
                    PrintRenderer(&info);
                }
            }
        }

		SDL_zero(fullscreen_mode);
       // memset(&fullscreen_mode, 0, sizeof(fullscreen_mode));
        //SDL_zero();
        switch (state->depth) {
        case 8:
            fullscreen_mode.format = SDL_PIXELFORMAT_INDEX8;
            break;
        case 15:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB555;
            break;
        case 16:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB565;
            break;
        case 24:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB24;
            break;
        default:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB888;
            break;
        }
        state->refresh_rate = fullscreen_mode.refresh_rate;

	//====================CBitmap Init aqui  para modo de compatibilidade SDL 1.2=====================
	/*	if (state->SDL_compatibility) {
		//Iniciar o CBitmap system aqui e usar a classe CBitmap
		int teste= CBitmap::setGraphicsMode( state,0 );
		Debug::debug(30,__FUNCTION__) << "CSDLManager::Init() // CALL setGraphicsMode // ret = " << teste <<endl;
			if(teste==1)
			{
			Debug::debug(20) << "CSDLManager::Init(Failed) // " <<  endl;
				return SDL_FALSE;
			}
		} */
}

    if (state->flags & SDL_INIT_AUDIO) {
        if (state->verbose & VERBOSE_AUDIO) {
            n = SDL_GetNumAudioDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in audio drivers\n");
            } else {
                fprintf(stderr, "Built-in audio drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetAudioDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_AudioInit(state->audiodriver) < 0) {
            fprintf(stderr, "Couldn't initialize audio driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Audio driver: %s\n",
                    SDL_GetCurrentAudioDriver());
        }

        if (SDL_OpenAudio(&state->audiospec, NULL) < 0) {
            fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
            return SDL_FALSE;
        }
    }

    return true;
}


bool CSDLManager::InitWindows(SDLState_t * state)
{
    Debug::debug(Debug::sdlmanager,__FUNCTION__) << " -------------------------------------------"<<endl;
    // Verificar se já foi feito o Init do Video
	if (!videoInitiated) {
		Debug::debug(Debug::error,__FUNCTION__) << "Must Initiate Video with CSDLManager::Init() first " <<endl;
		return false;
	}

	int i, j, m, n;
    SDL_DisplayMode fullscreen_mode;
	//!Init Video
    if (state->flags & SDL_INIT_VIDEO) {


		//Loop necessário para cada uma das Janelas que serão criadas
		 for (i = 0; i < state->num_windows; ++i) {
            char title[1024];

			//! inicializa o título das Janelas
            if (state->num_windows > 1) {
                SDL_snprintf(title, SDL_arraysize(title), "%s %d",
                             state->window_infos[i]->title, i + 1);
            }  else {
                SDL_strlcpy(title, state->window_infos[i]->title, SDL_arraysize(title));
            }

        //! inicializa as Janelas no modo SDL 1.3 ou acima
		if (true) {
				//! Cria as Janelas
				state->windows[i] = SDL_CreateWindow(title, state->window_infos[i]->x, state->window_infos[i]->y,
                                 state->window_infos[i]->w, state->window_infos[i]->h,
                                 state->window_infos[i]->flags);
				if (!state->windows[i]) {
					Debug::debug(Debug::error,__FUNCTION__) << "Couldn't create window: " << SDL_GetError() <<endl;
					return SDL_FALSE;
				}
				//----Janelas Criadas
				//-- preenche as indformações de tamanho de cada janela na variável state

				SDL_GetWindowSize(state->windows[i], &state->window_infos[i]->w, &state->window_infos[i]->h);

				if (SDL_SetWindowDisplayMode(state->windows[i], &fullscreen_mode) < 0) {
					Debug::debug(Debug::error,__FUNCTION__) <<"Can't set up fullscreen display mode: " << SDL_GetError()<<endl;
					return SDL_FALSE;
				}
				// coloca o ícone da janela
				if (state->window_infos[i]->icon) {
					CBitmap *icone = new CBitmap(state->window_infos[i]->icon);
					SDL_Surface *icon = icone->getBitmap();//LoadIcon(state->window_icon);
					if (icon) {
						SDL_SetWindowIcon(state->windows[i], icon);
						//SDL_FreeSurface(icon);
						delete icone;
					}
				}
				// icone da janela colocado
				// Mostra a Janela
				SDL_ShowWindow(state->windows[i]);

				// Inicializa o renderer da Janela
				state->renderers[i] = NULL;

				if (!state->skip_renderer
					&& (state->renderdriver
						|| !(state->window_infos[i]->flags & SDL_WINDOW_OPENGL))) {
					m = -1;
					if (state->renderdriver) {
						SDL_RendererInfo info;
						n = SDL_GetNumRenderDrivers();
						for (j = 0; j < n; ++j) {
                        SDL_GetRenderDriverInfo(j, &info);
                        if (_strcasecmp(info.name, state->renderdriver) == 0) {
                            m = j;
                            break;
                        }
                    }
						if (m == n) {
							Debug::debug(Debug::error,__FUNCTION__) << "Couldn't find render driver named: " << state->renderdriver << endl;
							return SDL_FALSE;
						}
					}
					state->renderers[i] = SDL_CreateRenderer(state->windows[i],
                                            m, state->render_flags);
					 if (!state->renderers[i]) {
                    Debug::debug(Debug::error,__FUNCTION__) << "Couldn't create renderer: " << SDL_GetError() <<endl;
                    return SDL_FALSE;
					}
					if (state->verbose & VERBOSE_RENDER) {
						SDL_RendererInfo info;

						Debug::debug(Debug::error,__FUNCTION__) << "Current renderer: " << SDL_GetRendererInfo(state->renderers[i],&info) << endl;
						PrintRenderer(&info);
					}

				} // fim da criação do renderer
		// inicializa a Screen
		state->Screen[i] = NULL;

		//====================CBitmap Init aqui  para o módo SDL 1.3 ou acima=====================

		int teste= CBitmap::init( state,i );
		Debug::debug(Debug::sdlmanager,__FUNCTION__) << "CSDLManager::Init() // CALL setGraphicsMode // ret = " << teste <<endl;
			if(teste==1)
			{
			Debug::debug(20) << "CSDLManager::Init(Failed) // " <<  endl;
				return SDL_FALSE;
			}
		} //end if compatibility
			//SDL_SelectRenderer(state->windows[0]);

		} //fim do loop das Janelas

}

	state->startedModules.WINDOW=true;
    return true;
}
const char* CSDLManager::PixelFormatToString(Uint32 pformat){
   Uint32 it=0;

   do {
      if (pixel_format[it].idstr == NULL) {
          break;
      }
      if (pixel_format[it].id == pformat) {
          return pixel_format[it].idstr;
      }
      it++;
   } while(1);

   return "SDL_PIXELFORMAT_UNKNOWN";
}

void CSDLManager::PrintRenderer(SDL_RendererInfo * info){
      unsigned int i, count;

    fprintf(stderr, "  Renderer %s:\n", info->name);

    fprintf(stderr, "    Flags: 0x%8.8X", info->flags);
    fprintf(stderr, " (");
    count = 0;
    for (i = 0; i < sizeof(info->flags) * 8; ++i) {
        Uint32 flag = (1 << i);
        if (info->flags & flag) {
            if (count > 0) {
                fprintf(stderr, " | ");
            }
            PrintRendererFlag(flag);
            ++count;
        }
    }
    fprintf(stderr, ")\n");

    fprintf(stderr, "    Texture formats (%d): ", info->num_texture_formats);
    for (i = 0; i < (int) info->num_texture_formats; ++i) {
        if (i > 0) {
            fprintf(stderr, ", ");
        }
        PrintPixelFormat(info->texture_formats[i]);
    }
    fprintf(stderr, "\n");

    if (info->max_texture_width || info->max_texture_height) {
        fprintf(stderr, "    Max Texture Size: %dx%d\n",
                info->max_texture_width, info->max_texture_height);
    }
}

void CSDLManager::PrintBlendMode(Uint32 flag){
    switch (flag) {
    case SDL_BLENDMODE_NONE:
        fprintf(stderr, "None");
        break;
    case SDL_BLENDMODE_BLEND:
        fprintf(stderr, "Blend");
        break;
    case SDL_BLENDMODE_ADD:
        fprintf(stderr, "Add");
        break;
    case SDL_BLENDMODE_MOD:
        fprintf(stderr, "Mod");
        break;
    default:
        fprintf(stderr, "0x%8.8x", flag);
        break;
    }
}
/*
void CSDLManager::PrintScaleMode(Uint32 flag){
    switch (flag) {
    case SDL_TEXTURESCALEMODE_NONE:
        fprintf(stderr, "None");
        break;
    case SDL_TEXTURESCALEMODE_FAST:
        fprintf(stderr, "Fast");
        break;
    case SDL_TEXTURESCALEMODE_SLOW:
        fprintf(stderr, "Slow");
        break;
    case SDL_TEXTURESCALEMODE_BEST:
        fprintf(stderr, "Best");
        break;
    default:
        fprintf(stderr, "0x%8.8x", flag);
        break;
    }
}
*/

void  CSDLManager::PrintRendererFlag(Uint32 flag)
{
    switch (flag) {
    case SDL_RENDERER_PRESENTVSYNC:
        fprintf(stderr, "PresentVSync");
        break;
    case SDL_RENDERER_ACCELERATED:
        fprintf(stderr, "Accelerated");
        break;
    default:
        fprintf(stderr, "0x%8.8x", flag);
        break;
    }
}
void CSDLManager::PrintPixelFormat(Uint32 format){
    switch (format) {
    case SDL_PIXELFORMAT_UNKNOWN:
        fprintf(stderr, "Unknwon");
        break;
    case SDL_PIXELFORMAT_INDEX1LSB:
        fprintf(stderr, "Index1LSB");
        break;
    case SDL_PIXELFORMAT_INDEX1MSB:
        fprintf(stderr, "Index1MSB");
        break;
    case SDL_PIXELFORMAT_INDEX4LSB:
        fprintf(stderr, "Index4LSB");
        break;
    case SDL_PIXELFORMAT_INDEX4MSB:
        fprintf(stderr, "Index4MSB");
        break;
    case SDL_PIXELFORMAT_INDEX8:
        fprintf(stderr, "Index8");
        break;
    case SDL_PIXELFORMAT_RGB332:
        fprintf(stderr, "RGB332");
        break;
    case SDL_PIXELFORMAT_RGB444:
        fprintf(stderr, "RGB444");
        break;
    case SDL_PIXELFORMAT_RGB555:
        fprintf(stderr, "RGB555");
        break;
    case SDL_PIXELFORMAT_BGR555:
        fprintf(stderr, "BGR555");
        break;
    case SDL_PIXELFORMAT_ARGB4444:
        fprintf(stderr, "ARGB4444");
        break;
    case SDL_PIXELFORMAT_ABGR4444:
        fprintf(stderr, "ABGR4444");
        break;
    case SDL_PIXELFORMAT_ARGB1555:
        fprintf(stderr, "ARGB1555");
        break;
    case SDL_PIXELFORMAT_ABGR1555:
        fprintf(stderr, "ABGR1555");
        break;
    case SDL_PIXELFORMAT_RGB565:
        fprintf(stderr, "RGB565");
        break;
    case SDL_PIXELFORMAT_BGR565:
        fprintf(stderr, "BGR565");
        break;
    case SDL_PIXELFORMAT_RGB24:
        fprintf(stderr, "RGB24");
        break;
    case SDL_PIXELFORMAT_BGR24:
        fprintf(stderr, "BGR24");
        break;
    case SDL_PIXELFORMAT_RGB888:
        fprintf(stderr, "RGB888");
        break;
    case SDL_PIXELFORMAT_BGR888:
        fprintf(stderr, "BGR888");
        break;
    case SDL_PIXELFORMAT_ARGB8888:
        fprintf(stderr, "ARGB8888");
        break;
    case SDL_PIXELFORMAT_RGBA8888:
        fprintf(stderr, "RGBA8888");
        break;
    case SDL_PIXELFORMAT_ABGR8888:
        fprintf(stderr, "ABGR8888");
        break;
    case SDL_PIXELFORMAT_BGRA8888:
        fprintf(stderr, "BGRA8888");
        break;
    case SDL_PIXELFORMAT_ARGB2101010:
        fprintf(stderr, "ARGB2101010");
        break;
    case SDL_PIXELFORMAT_YV12:
        fprintf(stderr, "YV12");
        break;
    case SDL_PIXELFORMAT_IYUV:
        fprintf(stderr, "IYUV");
        break;
    case SDL_PIXELFORMAT_YUY2:
        fprintf(stderr, "YUY2");
        break;
    case SDL_PIXELFORMAT_UYVY:
        fprintf(stderr, "UYVY");
        break;
    case SDL_PIXELFORMAT_YVYU:
        fprintf(stderr, "YVYU");
        break;
    default:
        fprintf(stderr, "0x%8.8x", format);
        break;
    }
}

//! Window Methods ------------------------------------

//!Window Methods
void CSDLManager::setWindowTitle(const char * title, int window){
if (!state){
	//Must run CommonInit first
	return;
	}

}
void CSDLManager::setWindowIcon(const char *icon, int window){
	if (!state){
	//Must run CommonInit first
	return;
	}
}
void CSDLManager::setWindowX(int x, int window){
	if (!state){
	//Must run CommonInit first
	return;
	}
}
void CSDLManager::setWindowY(int y, int window){
	if (!state){
	//Must run CommonInit first
	return;
	}
	state->window_infos[window]->y=y;
}
void CSDLManager::setWindowCoordinates(int x, int y, int w, int h, int window){
	if (!state){
	//Must run CommonInit first
	return;
	}
}
void CSDLManager::setWindowWidth(int w,int window){
	if (!state){
	//Must run CommonInit first
	return;
	}
}
void CSDLManager::setWindowHeight(int h, int window){
	if (!state){
	//Must run CommonInit first
	return;
	}
}
//--------------------------------------------------------

//! Cria initialization state with default values

SDLState_t * CSDLManager::CreateState(Uint32 flags,int numWindows)
{
   if (numWindows<=0) return NULL;
   SDLState_t *state = new SDLState(numWindows);

	/* Initialize some defaults */
    //state->argumentos = argumentos;
	//state->SDL_compatibility=false;
    state->flags = flags;
	//TODO:  preencher corretamente windowInfo_s
	for (int i=0; i< numWindows;i++) {
	state->window_infos[i]->title= "Default Title";
	//state->window_infos[i]->icon= "icon.bmp";  //!TODO: Solve problem to load icon.bmp
	//state->window_infos[i]->x = 0;//SDL_WINDOWPOS_UNDEFINED;
	//state->window_infos[i]->y = 0;//SDL_WINDOWPOS_UNDEFINED;
	state->window_infos[i]->x = SDL_WINDOWPOS_CENTERED;
    state->window_infos[i]->y = SDL_WINDOWPOS_CENTERED;
	state->window_infos[i]->w = CConfiguration::screenWidth.getInteger();
	state->window_infos[i]->h =  CConfiguration::screenHeight.getInteger();

	}
	//state->verbose |= (VERBOSE_VIDEO | VERBOSE_MODES | VERBOSE_RENDER | VERBOSE_EVENT);
	state->initModules.VIDEO=true;
	state->initModules.AUDIO=true;
	state->initModules.FRAMERATEMANAGER=true;
	state->initModules.JOYSTICK=true;
	state->initModules.TIMER=true;
	state->initModules.TTF=true;
	state->initModules.WINDOW=true;
	state->initModules.FASTEVENTS=true;
	state->initModules.TEXTSUPPORT=true;
	state->initModules.NETWORK=true;
    return state;
}
/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
void CSDLManager::quit(void)
{
	CSDLManager::CommonQuit(CSDLManager::GetInstance()->state);
    exit(3);
}
void
CSDLManager::CommonQuit(SDLState_t * state)
{
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "BEGIN DELETING STATE STUFF"<<endl;

	if (state==NULL) return;
	else delete state;
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "WILL DELETE STATE"<<endl;
	
	if (state->initModules.VIDEO) {
        SDL_VideoQuit();
    }
	if (state->initModules.AUDIO) {
        SDL_AudioQuit();
    }
	if (state->initModules.TIMER) {
#ifdef SGF_USE_INTERNAL_TIMER
	Util::stopTimers();
#endif

	}
#if 0
	
	if (state->renderdriver) delete state->renderdriver;
	if (state->audiodriver)  delete state->audiodriver;
	if (state->videodriver)  delete state->videodriver;

    if (state->windows) {
        Debug::debug(Debug::font,__FUNCTION__) << "Freeing state windows"<<endl;

		SDL_free(state->windows);
    }
	if (state->window_infos) {
		Debug::debug(Debug::font,__FUNCTION__) << "Freeing windows infos"<<endl;

        free(state->window_infos);
    }
	if (state->renderers) {
		for (int i = 0; i < state->num_windows; ++i) {
            if (state->renderers[i]) {
                SDL_DestroyRenderer(state->renderers[i]);
            }
        }
        SDL_free(state->renderers);
	}
	Debug::debug(Debug::font,__FUNCTION__) << "Freeing state"<<endl;

    SDL_free(state);
#endif

}

CSDLManager* CSDLManager::GetInstance()
{
    
	if (!pCSDLManager)
		Util::Thread::ScopedLock scoped(sldManagerLock);
		pCSDLManager = new CSDLManager();
    return pCSDLManager;
}


void CSDLManager::changeGameFPS() {
	//todo:implement speedcounter
	//m_SpeedCounter.changeTimer(CGlobalConfiguration::gameFPS);
}


void CSDLManager::PrintEvent(SDL_Event * event)
{
    fprintf(stderr, "SDL EVENT: ");
    switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            fprintf(stderr, "Window %d shown", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            fprintf(stderr, "Window %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            fprintf(stderr, "Window %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            fprintf(stderr, "Window %d moved to %d,%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            fprintf(stderr, "Window %d resized to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            fprintf(stderr, "Window %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            fprintf(stderr, "Window %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            fprintf(stderr, "Window %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            fprintf(stderr, "Mouse entered window %d",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            fprintf(stderr, "Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            fprintf(stderr, "Window %d gained keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            fprintf(stderr, "Window %d lost keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            fprintf(stderr, "Window %d closed", event->window.windowID);
            break;
        default:
            fprintf(stderr, "Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
        }
        break;
    case SDL_KEYDOWN:
        fprintf(stderr,
                "Keyboard: key pressed  in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID,
                event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
    case SDL_KEYUP:
        fprintf(stderr,
                "Keyboard: key released in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID,
                event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
    case SDL_TEXTINPUT:
        fprintf(stderr, "Keyboard: text input \"%s\" in window %d",
                event->text.text, event->text.windowID);
        break;
    case SDL_MOUSEMOTION:
        fprintf(stderr, "Mouse: moved to %d,%d (%d,%d) in window %d",
                event->motion.x, event->motion.y,
                event->motion.xrel, event->motion.yrel,
                event->motion.windowID);
        break;
    case SDL_MOUSEBUTTONDOWN:
        fprintf(stderr, "Mouse: button %d pressed at %d,%d in window %d",
                event->button.button, event->button.x, event->button.y,
                event->button.windowID);
        break;
    case SDL_MOUSEBUTTONUP:
        fprintf(stderr, "Mouse: button %d released at %d,%d in window %d",
                event->button.button, event->button.x, event->button.y,
                event->button.windowID);
        break;
    case SDL_MOUSEWHEEL:
        fprintf(stderr,
                "Mouse: wheel scrolled %d in x and %d in y in window %d",
                event->wheel.x, event->wheel.y, event->wheel.windowID);
        break;
    case SDL_JOYBALLMOTION:
        fprintf(stderr, "Joystick %d: ball %d moved by %d,%d",
                event->jball.which, event->jball.ball, event->jball.xrel,
                event->jball.yrel);
        break;
    case SDL_JOYHATMOTION:
        fprintf(stderr, "Joystick %d: hat %d moved to ", event->jhat.which,
                event->jhat.hat);
        switch (event->jhat.value) {
        case SDL_HAT_CENTERED:
            fprintf(stderr, "CENTER");
            break;
        case SDL_HAT_UP:
            fprintf(stderr, "UP");
            break;
        case SDL_HAT_RIGHTUP:
            fprintf(stderr, "RIGHTUP");
            break;
        case SDL_HAT_RIGHT:
            fprintf(stderr, "RIGHT");
            break;
        case SDL_HAT_RIGHTDOWN:
            fprintf(stderr, "RIGHTDOWN");
            break;
        case SDL_HAT_DOWN:
            fprintf(stderr, "DOWN");
            break;
        case SDL_HAT_LEFTDOWN:
            fprintf(stderr, "LEFTDOWN");
            break;
        case SDL_HAT_LEFT:
            fprintf(stderr, "LEFT");
            break;
        case SDL_HAT_LEFTUP:
            fprintf(stderr, "LEFTUP");
            break;
        default:
            fprintf(stderr, "UNKNOWN");
            break;
        }
        break;
    case SDL_JOYBUTTONDOWN:
        fprintf(stderr, "Joystick %d: button %d pressed",
                event->jbutton.which, event->jbutton.button);
        break;
    case SDL_JOYBUTTONUP:
        fprintf(stderr, "Joystick %d: button %d released",
                event->jbutton.which, event->jbutton.button);
        break;
    case SDL_CLIPBOARDUPDATE:
        fprintf(stderr, "Clipboard updated");
        break;
    case SDL_QUIT:
        fprintf(stderr, "Quit requested");
        break;
    case SDL_USEREVENT:
        fprintf(stderr, "User event %d", event->user.code);
        break;
    default:
        fprintf(stderr, "Unknown event %d", event->type);
        break;
    }
    fprintf(stderr, "\n");
}

} //end SGF