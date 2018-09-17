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

#ifndef USE_SDL
#define USE_SDL
#endif
#include "graphics/SGF_Bitmap.h"
#include "exceptions/all.h"
#include "configuration/SGF_Configuration.h"
#include "util/SGF_Debug.h"
#include "util/SGF_Thread.h"
#include "input/SGF_Events.h"
#include "util/SGF_SdlManager.h"

using namespace std;
namespace SGF {
class CBitmap;


namespace Input{


unsigned long long int CDraw::frameTime=0; //! registra o tempo que dura para desenhar o jogo na tela
unsigned long long int CLogic::logicTime=0; //! registra o tempo que dura para roda a lógica do jogo
int CLogic::runCount=0;

CEventManager::CEventManager():
bufferKeys(false),
deferResize(false){
	resize.enable = false;

}

#ifdef USE_SDL


static void HandleMouseMotion(Util::CSmartPtr_MT<CMouse> mouse, const SDL_Event & event){
	if (mouse.raw() !=NULL) {
	mouse->moved(event.motion.x,event.motion.y);
	mouse->movedRelative(event.motion.xrel,event.motion.yrel);
	}
}
static void HandleMouseSingle() {}
//static void HandleMouseRepeating(){}

static void handleMouseWheel(Util::CSmartPtr_MT<CMouse> mouse , const SDL_Event & event){
	if (mouse.raw() != NULL) {
	mouse->wheelMoved(event.wheel.x,event.wheel.y);
	}
}

static void handleMouseKeyUp(Util::CSmartPtr_MT<CMouse> mouse, const SDL_Event & event){
	if (mouse.raw() != NULL) {
	mouse->release(CConfiguration::intToMouse(event.button.button), event.button.x,event.button.y);
	}
}

// A single mouse click works in the same fashion as the single keystroke; it will only trigger a single event until it is depressed. Examples of when this is desired:
// Selection of an item - when a mouse clicks on an item we wish to select, we do not wish to repeat the selection algorithm for as long as the button is pressed, as we already have our selection.
// Single Action Events - Perhaps we wish to shoot a basketball with the mouse. We only have one ball at a time, so why keep trying the shoot algorithm when the ball is no longer in our possession after the shot.
static void handleMouseKeyDown(Util::CSmartPtr_MT<CMouse> mouse, const SDL_Event & event){
    if (mouse.raw() !=NULL) {
	mouse->press(CConfiguration::intToMouse(event.button.button), event.button.x,event.button.y);
	}
}


static void handleKeyUp(CKeyboard & keyboard, const SDL_Event & event){
	keyboard.release(CConfiguration::intToKeyboard(event.key.keysym.sym));
}

static void handleKeyDown(CKeyboard & keyboard, const SDL_Event & event){
	keyboard.press(CConfiguration::intToKeyboard(event.key.keysym.sym), CConfiguration::intToKeyboardMod(event.key.keysym.mod), event.key.keysym.sym);//.unicode);
}


static void handtextInput(Util::CSmartPtr_MT<CTextInput> textinput, const SDL_Event & event){

	if (event.text.text[0] !=0) {
		textinput->press(event.text.text,event.text.windowID);

	}
}

static void handtextEdit(Util::CSmartPtr_MT<CTextInput> textinput, const SDL_Event & event){
	if (event.edit.text[0] !=0) {
		textinput->edit(event.edit.text,event.edit.start,event.edit.length,event.edit.windowID);

	}
}
static void handleJoystickButtonUp(map<int, Util::CSmartPtr_MT<CJoystick> > joysticks, const SDL_Event & event){
    int device = event.jbutton.which;
    int button = event.jbutton.button;
	Util::CSmartPtr_MT<CJoystick> joystick = joysticks[device];

    if (joystick != NULL){
        joystick->releaseButton(button);
    }
}

static void handleJoystickHat(map<int, Util::CSmartPtr_MT<CJoystick> > joysticks, const SDL_Event & event){
    int device = event.jhat.which;
    int motion = event.jhat.value;
	Util::CSmartPtr_MT<CJoystick> joystick = joysticks[device];

    /* should up/down control left/right -- flip these values? */
#if WII
    const int axis_up_down = 0;
    const int axis_left_right = 1;
    const int _up = 1;
    const int _down = -1;
    const int left = -1;
    const int right = 1;
#else
    const int axis_up_down = 1;
    const int axis_left_right = 0;
	const int axis_down_right_up_left=2;
    const int axis_down_left_up_right = 3;
    //!mesmo mapeamento de CObject::FACE_UP
	const int _up = -1;
	//!mesmo mapeamento de CObject::FACE_DOWN
    const int _down = 1;
	//!mesmo mapeamento de CObject::FACE_LEFT
    const int left = -1;
	//!mesmo mapeamento de CObject::FACE_RIGHT
    const int right = 1;
#endif
	if (joystick != NULL) {
	// trata hat motion como hat mesmo
	joystick->hatMotion(motion);
	//Transforma hat motion em axismotion
    switch (motion){
        case SDL_HAT_CENTERED: break;
        case SDL_HAT_UP: joystick->axisMotion(axis_up_down, _up); break;
        case SDL_HAT_DOWN: joystick->axisMotion(axis_up_down, _down); break;
        case SDL_HAT_RIGHT: joystick->axisMotion(axis_left_right, right); break;
		case SDL_HAT_RIGHTUP: joystick->axisMotion(axis_down_left_up_right, right); break;
		case SDL_HAT_RIGHTDOWN: joystick->axisMotion(axis_down_right_up_left, right); break;
        case SDL_HAT_LEFT: joystick->axisMotion(axis_left_right, left); break;
		case SDL_HAT_LEFTDOWN: joystick->axisMotion(axis_down_left_up_right, left); break;
		case SDL_HAT_LEFTUP: joystick->axisMotion(axis_down_right_up_left, left); break;
        default: break;
    }

  }
}

static void handleJoystickButtonDown(map<int, Util::CSmartPtr_MT<CJoystick> > joysticks, const SDL_Event & event){

    int device = event.jbutton.which;
    int button = event.jbutton.button;
	Util::CSmartPtr_MT<CJoystick> joystick = joysticks[device];
	Debug::debug(Debug::input,__FUNCTION__) << "joystick: "<< device <<endl;
    if (joystick !=NULL){
        joystick->pressButton(button);
    }
}

static void handleJoystickAxis(map<int, Util::CSmartPtr_MT<CJoystick> > joysticks, const SDL_Event & event){
    int device = event.jaxis.which;
    int axis = event.jaxis.axis;
    int value = event.jaxis.value;
	Util::CSmartPtr_MT<CJoystick> joystick = joysticks[device];
    if (joystick != NULL){
        joystick->axisMotion(axis, value);
    }
}



void CEventManager::HandleEventInput(CKeyboard & keyboard, map<int, Util::CSmartPtr_MT<CJoystick> > joysticks, Util::CSmartPtr_MT<CMouse> mouse,Util::CSmartPtr_MT<CTextInput> textinput){
	Debug::debug(Debug::input,__FUNCTION__) << "Num joysticks: "<< joysticks.size() <<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "keyboard: "<< &keyboard <<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Mouse: "<< mouse.raw() <<endl;
    keyboard.poll();
	for (map<int, Util::CSmartPtr_MT<CJoystick> >::iterator it = joysticks.begin(); it != joysticks.end(); it++){
        Util::CSmartPtr_MT<CJoystick> joystick = it->second;
        if (joystick != NULL){
            joystick->poll();
        }
    }

	if (mouse !=NULL){
        mouse->poll();
    }
    SDL_Event event;
#ifdef USE_FASTEVENTS
	while (FE_PollEvent(&event) == 1){
#else
    while (SDL_PollEvent(&event) == 1){
#endif

        switch (event.type){
            case SDL_QUIT : {

				dispatch(CloseWindow);
                break;
            }
            case SDL_KEYDOWN : {
                handleKeyDown(keyboard, event);
				 // dispatch(Key, event.key.keysym.sym); // NOT USED. WILL BUFFER THE KEYS
                
                 break;
            }
            case SDL_KEYUP : {
                handleKeyUp(keyboard, event);
                break;
            }
			case SDL_TEXTINPUT : {
				if(textinput.raw() !=NULL) {
				handtextInput(textinput, event);
				}
				break;
			}
			case SDL_TEXTEDITING : {
				if(textinput.raw() !=NULL) {
				handtextEdit(textinput, event);
				}
				break;
			}

            case SDL_JOYBUTTONDOWN: {

                    handleJoystickButtonDown(joysticks, event);

                break;
            }
            case SDL_JOYHATMOTION : {

                    handleJoystickHat(joysticks, event);

                break;
            }
            case SDL_JOYBUTTONUP: {

                    handleJoystickButtonUp(joysticks, event);

                break;
            }
            case SDL_JOYAXISMOTION: {

                    handleJoystickAxis(joysticks, event);

                break;
            }
#if 0 //todo convert to sDL 2.0
			case SDL_VIDEORESIZE : {
                int width = event.resize.w;
                int height = event.resize.h;
                // para manter a perspectiva correta
                double ratio = CConfiguration::screenWidth.getInteger()/CConfiguration::screenHeight.getInteger();
                if (width > height){
                    height = (int)((double) width / ratio);
                } else {
                    width = (int)((double) height * ratio);
                }
                dispatch(ResizeScreen, width, height);
                break;
            }
#endif
			    case SDL_MOUSEMOTION:
					 if (mouse != NULL){
						HandleMouseMotion(mouse,event);
						/*	MouseMoved(
						event.button.button,
						event.motion.x,
						event.motion.y,
						event.motion.xrel,
						event.motion.yrel);*/
					 }
			break;

		case SDL_MOUSEBUTTONUP:
			 if (mouse != NULL){
				handleMouseKeyUp(mouse, event);
				/*	MouseButtonUp(
				event.button.button,
				event.motion.x,
				event.motion.y,
				event.motion.xrel,
				event.motion.yrel); */
			 }
			break;

		  case SDL_MOUSEBUTTONDOWN:
			   if (mouse != NULL){
				handleMouseKeyDown(mouse, event);
				/*	  MouseButtonDown(
				event.button.button,
				event.motion.x,
				event.motion.y,
				event.motion.xrel,
				event.motion.yrel); */
			   }
			break;
	     case SDL_MOUSEWHEEL:
			  if (mouse != NULL){
				handleMouseWheel(mouse, event);
			  }
			break;

		  case SDL_WINDOWEVENT:
			break;
		  case SDL_SYSWMEVENT:
			  break;
            default : {
                break;
            }
        }
    }
}
#endif

void CEventManager::run(CKeyboard & keyboard, map<int, Util::CSmartPtr_MT<CJoystick> > joysticks, Util::CSmartPtr_MT<CMouse> mouse,Util::CSmartPtr_MT<CTextInput> textinput){
#ifdef USE_SDL
    HandleEventInput(keyboard, joysticks,mouse, textinput );
#endif
}

/* kill the program if the user requests */
void CEventManager::waitForThread(Util::Thread::WaitThread & thread){
    // CKeyboard dummy;
    while (!thread.isRunning()){
        try{
            /* input manager will run the event manager */
            CInputManager::poolEvents();
            // run(dummy);
        } catch (const CShutdownException & death){
            thread.kill();
            throw death;
        }
        Util::rest(10);
    }
}

CEventManager::~CEventManager(){
}

void CEventManager::enableKeyBuffer(){
    bufferKeys = true;
}

void CEventManager::disableKeyBuffer(){
    bufferKeys = false;
}

void CEventManager::dispatch(Event type, int arg1){
    switch (type){
        case Key : {
            if (bufferKeys){
                keys.push_back(KeyType(arg1));
            }
            break;
        }
        default : {
            break;
        }
    }
}

void CEventManager::dispatch(Event type, int arg1, int arg2){
    switch (type){
        case ResizeScreen : {
            if (deferResize){
                resize.type = ResizeScreen;
                resize.width = arg1;
                resize.height = arg2;
                resize.enable = true;
            } else {
                Debug::debug(Debug::input,__FUNCTION__) << "Resizing screen to " << arg1 << ", " << arg2 << endl;
            /*if (Graphics::setGraphicsMode(0, arg1, arg2) == 0){
                    CConfiguration::setScreenWidth(arg1);
                    CConfiguration::setScreenHeight(arg2);
                }*/
            }
            break;
        }
        default : break;
    }
}

void CEventManager::dispatch(Event type){
    switch (type){
        case CloseWindow : {
			throw CShutdownException();
        }
        default : break;
    }
}
void CEventManager::deferResizeEvents(bool defer){
    deferResize = defer;
    if (!deferResize && resize.enable){
        dispatch(resize.type, resize.width, resize.height);
        resize.enable = false;
    }
}

class CLoopDone: public std::exception {
public:
    CLoopDone(){
    }

    ~CLoopDone() throw () {
    }
};


CDraw::CDraw():
frames(0),
fps(0),
contador(0),
second_counter(Global::second_counter),
delay(0){
}



CLogic::~CLogic(){
}

CDraw::~CDraw(){
}

double CDraw::getFps() const {
    return fps;
}
void CDraw::updateFrames(){
#ifdef SGF_USE_INTERNAL_TIMER
	    if (second_counter != Global::second_counter){
        int difference = Global::second_counter - second_counter;
        double alpha = 0.2;
        /* unlikely, but just in case */
        if (difference == 0){
            difference = 1;
        }
        fps = (alpha * fps) + ((1 - alpha) * (double) frames / difference);
        // fps[fps_index] = (double) frames / (double) difference;
        // fps_index = (fps_index+1) % max_fps_index;
        second_counter = Global::second_counter;
        frames = 0;
    }

    frames += 1;
#else // SDL_Timers are not very acurate speedcounter and secondcounter are nor SDL_Getticks based
	int nowTime=SDL_GetTicks();   // numero de milisegundos desde a inicialização do SDL
	delay = nowTime -contador;
    if(delay > 500)  //passou no mínimo 0,5 segundos para calcular novamente
    {
        fps=(double)(frames*1000)/delay;
		frames=0;
        contador=nowTime;
     }
	frames++;
#endif
}

static void changeScreenMode(){
    CConfiguration::fullScreen.setBool(!CConfiguration::fullScreen.getBool());
	CConfiguration::fullScreen.getBool() ? CBitmap::_my_state->Screen[0]->SetFullScreen() : CBitmap::_my_state->Screen[0]->SetWindowed();
	
}
static void checkFullscreen(){
    CInputMap<int> input;
    input.set(CKeyboard::Key_F11, 0, true, 5);
    vector<CInputMap<int>::InputEvent> events = CInputManager::getEvents(input);//, InputSource());

    for (vector<CInputMap<int>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
        CInputMap<int>::InputEvent event = *it;

        if (!event.enabled){
            continue;
        }

        if (event.out == 5){
            changeScreenMode();
        }
    }
}

static void doLoop(CLogic & logic, CDraw & draw){
    Global::speed_counter = 0;
	//bool show_fps = true;
    double runCounter = 0;
	TimeDifference diff;
	const int maxCount = 20;  //tempo usado para fazer o calculo da média de tempo gasto
    int frameCount = 0;
    int logicCount = 0;
        
    try{
        while (!logic.done()){  //run flag
            if (Global::speed_counter > 0){   // espera o próximo game tick
				Debug::debug(Debug::gameEngine,__FUNCTION__) << "XSpeed Counter: " << Global::speed_counter << " SDL ticks (ms): " << SDL_GetTicks() <<endl;
				runCounter += logic.ticks(Global::speed_counter);  //calcula o delay time. passa quantos milisegundos se passaram desde a última verificação = dt
				CLogic::runCount = (int) runCounter;
				Global::speed_counter = 0;
                bool need_draw = false;
                Debug::debug(Debug::gameEngine,__FUNCTION__) << "RunCounter: " << runCounter << endl;
				Debug::debug(Debug::gameEngine,__FUNCTION__) << "Speed Counter should be 0: " << Global::speed_counter  << " SDL ticks (ms): " << SDL_GetTicks() << endl;

				while (runCounter >= 1.0){
                    need_draw = true;
                    CInputManager::poolEvents();
                    runCounter -= 1;
					logicCount += 1;
                    diff.startTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "RunCounter after get events: " << runCounter << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			
                    logic.run();
					diff.endTime();
					CLogic::logicTime=diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to run the logic: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			        
					if (logicCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Logic average " << (CLogic::logicTime / logicCount / 1000.0) << "ms" << std::endl;
                        logicCount = 0;
                        CLogic::logicTime = 0;
                    }
                    
					if (Global::shutdown()){
                        throw CShutdownException();
                    }

                    if (logic.done()){
                        /* quit the loop immediately */
                        throw CLoopDone();
                    }
                }

                if (need_draw){
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					frameCount += 1;
					draw.updateFrames();
					diff.startTime();
	                draw.draw(draw.getFps());

					diff.endTime();
					CDraw::frameTime = diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to draw the game: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					if (frameCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Draw average " << (CDraw::frameTime / frameCount / 1000.0) << "ms" << std::endl;
                        frameCount = 0;
                        CDraw::frameTime = 0;
                    }
                }
            }
			Debug::debug(Debug::gameEngine,__FUNCTION__) << "Speed Counter after logic and draw: " << Global::speed_counter  << " SDL ticks (ms): " << SDL_GetTicks() << endl;

           while (Global::speed_counter == 0){  //espera o próximo tick
                /* if the fps is limited then don't keep redrawing */
                if (true){  //rate limit
                    Util::rest(1);
                } else {
                    draw.updateFrames();
                    draw.draw(draw.getFps());
                }
            }
        }
    } catch (const CLoopDone & done){
    }
}
////===========   DIFERENT GAMELOOPS ==============
/*
Implementation

Our first solution, FPS dependent on Constant Game Speed, has a problem when running on slow hardware. Both the game speed and the framerate will drop in that case. A possible solution for this could be to keep updating the game at that rate, but reduce the rendering framerate. This can be done using following game loop:

    const int TICKS_PER_SECOND = 50;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

    DWORD next_game_tick = GetTickCount();
    int loops;

    bool game_is_running = true;
    while( game_is_running ) {

        loops = 0;
        while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
            update_game();

            next_game_tick += SKIP_TICKS;
            loops++;
        }

        display_game();
    }

The game will be updated at a steady 50 times per second, and rendering is done as fast as possible. Remark that when rendering is done more than 50 times per second, some subsequent frames will be the same, so actual visual frames will be dispayed at a maximum of 50 frames per second. When running on slow hardware, the framerate can drop until the game update loop will reach MAX_FRAMESKIP. In practice this means that when our render FPS drops below 5 (= FRAMES_PER_SECOND / MAX_FRAMESKIP), the actual game will slow down.
Slow hardware

On slow hardware the frames per second will drop, but the game itself will hopefully run at the normal speed. If the hardware still can’t handle this, the game itself will run slower and the framerate will not be smooth at all.
Fast hardware

The game will have no problems on fast hardware, but like the first solution, you are wasting so many precious clock cycles that can be used for a higher framerate. Finding the balance between a fast update rate and being able to run on slow hardware is crucial.
Conclusion

Using a constant game speed with a maximum FPS is a solution that is easy to implement and keeps the game code simple. But there are still some problems: Defining a high FPS can still pose problems on slow hardware (but not as severe as the first solution), and defining a low FPS will waste visual appeal on fast hardware.


*/
static void GSConstWithMaxFPS(CLogic & logic, CDraw & draw){
    //bool show_fps = true;
	int next_game_tick=SDL_GetTicks();
	double runCounter = 0;
	TimeDifference diff;
	const int maxCount = 20;  //tempo usado para fazer o calculo da média de tempo gasto
    int frameCount = 0;
    int logicCount = 0;
    int MAX_FRAMESKIP =10;

    try{
        while (!logic.done()){  //run flag
        //    if (Global::speed_counter > 0){   // espera o próximo game tick
				Debug::debug(Debug::gameEngine,__FUNCTION__) << "Speed Counter: " << Global::speed_counter << " SDL ticks (ms): " << SDL_GetTicks() <<endl;
				runCounter = 0;
				CLogic::runCount = (int) runCounter;
				bool need_draw = false;
                Debug::debug(Debug::gameEngine,__FUNCTION__) << "RunCounter: " << runCounter << endl;
				
				while (SDL_GetTicks() > next_game_tick && runCounter < MAX_FRAMESKIP){
                    need_draw = true;
                    CInputManager::poolEvents();
                    runCounter ++;
					logicCount += 1;
                    diff.startTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "RunCounter after get events: " << runCounter << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			
                    logic.run();
					diff.endTime();
					CLogic::logicTime=diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to run the logic: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			        next_game_tick += Global::SKIP_TICKS;
					if (logicCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Logic average " << (CLogic::logicTime / logicCount / 1000.0) << "ms" << std::endl;
                        logicCount = 0;
                        CLogic::logicTime = 0;
                    }
                    
					if (Global::shutdown()){
                        throw CShutdownException();
                    }

                    if (logic.done()){
                        /* quit the loop immediately */
                        throw CLoopDone();
                    }
                }

                if (need_draw){
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					frameCount += 1;
					draw.updateFrames();
					diff.startTime();
	                draw.draw(draw.getFps());

					diff.endTime();
					CDraw::frameTime = diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to draw the game: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					if (frameCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Draw average " << (CDraw::frameTime / frameCount / 1000.0) << "ms" << std::endl;
                        frameCount = 0;
                        CDraw::frameTime = 0;
                    }
                }
          //  }  //end if
			Debug::debug(Debug::gameEngine,__FUNCTION__) << "Speed Counter after logic and draw: " << Global::speed_counter  << " SDL ticks (ms): " << SDL_GetTicks() << endl;

          
        }
    } catch (const CLoopDone & done){
    }
}

/*
Would it be possible to improve the above solution even further to run faster on slow hardware, and be visually more atractive on faster hardware? Well, lucky for us, this is possible. The game state itself doesn’t need to be updated 60 times per second. Player input, AI and the updating of the game state have enough with 25 frames per second. So let’s try to call the update_game() 25 times per second, no more, no less. The rendering, on the other hand, needs to be as fast as the hardware can handle. But a slow frame rate shouldn’t interfere with the updating of the game. The way to achieve this is by using the following game loop:

    const int TICKS_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    DWORD next_game_tick = GetTickCount();
    int loops;
    float interpolation;

    bool game_is_running = true;
    while( game_is_running ) {

        loops = 0;
        while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
            update_game();

            next_game_tick += SKIP_TICKS;
            loops++;
        }

        interpolation = float( GetTickCount() + SKIP_TICKS - next_game_tick )
                        / float( SKIP_TICKS );
        display_game( interpolation );
    }

With this kind of game loop, the implementation of update_game() will stay easy. But unfortunately, the display_game() function gets more complex. You will have to implement a prediction function that takes the interpolation as argument. But don’t worry, this isn’t hard, it just takes a bit more work. I’ll explain below how this interpolation and prediction works, but first let me show you why it is needed.
The Need for Interpolation

The gamestate gets updated 25 times per second, so if you don’t use interpolation in your rendering, frames will also be displayed at this speed. Remark that 25 fps isn’t as slow as some people think, movies for example run at 24 frames per second. So 25 fps should be enough for a visually pleasing experience, but for fast moving objects, we can still see a improvement when doing more FPS. So what we can do is make fast movements more smooth in between the frames. And this is where interpolation and a prediction function can provide a solution.
Interpolation and Prediction

Like I said the game code runs on it’s own frames per second, so when you draw/render your frames, it is possible that it’s in between 2 gameticks. Let’s say you have just updated your gamestate for the 10Th time, and now you are going to render the scene. This render will be in between the 10Th and 11Th game update. So it is possible that the render is at about 10.3. The ‘interpolation’ value then holds 0.3. Take this example: I have a car that moves every game tick like this:

    position = position + speed;

If in the 10Th gametick the position is 500, and the speed is 100, then in the 11Th gametick the position will be 600. So where will you place your car when you render it? You could just take the position of the last gametick (in this case 500). But a better way is to predict where the car would be at exact 10.3, and this happens like this:

    view_position = position + (speed * interpolation)

The car will then be rendered at position 530. So basically the interpolation variable contains the value that is in between the previous gametick and the next one (previous = 0.0, next = 1.0). What you have to do then is make a “prediction” function where the car/camera/… would be placed at the render time. You can base this prediction function on the speed of the object, steering or rotation speed. It doesn’t need to be complicated because we only use it to smooth things out in between the frames. It is indeed possible that an object gets rendered into another object right before a collision gets detected. But like we have seen before, the game is updated 25 frames per second, and so when this happens, the error is only shown for a fraction of a second, hardly noticeable to the human eye.
Slow Hardware

In most cases, update_game() will take far less time than display_game(). In fact, we can assume that even on slow hardware the update_game() function can run 25 times per second. So our game will handle player input and update the game state without much trouble, even if the game will only display 15 frames per second.
Fast Hardware

On fast hardware, the game will still run at a constant pace of 25 times per second, but the updating of the screen will be way faster than this. The interpolation/prediction method will create the visual appeal that the game is actually running at a high frame rate. The good thing is that you kind of cheat with your FPS. Because you don’t update your game state every frame, only the visualization, your game will have a higher FPS than with the second method I described.
Conclusion

Making the game state independent of the FPS seems to be the best implementation for a game loop. However, you will have to implement a prediction function in display_game(), but this isn’t that hard to achieve.

*/
static void GSConstIndFPS(CLogic & logic, CDraw & draw){
    
	int next_game_tick=SDL_GetTicks();
	double runCounter = 0;
	TimeDifference diff;
	const int maxCount = 20;  //tempo usado para fazer o calculo da média de tempo gasto
    int frameCount = 0;
    int logicCount = 0;
    int MAX_FRAMESKIP =10;

    try{
        while (!logic.done()){  //run flag
        //    if (Global::speed_counter > 0){   // espera o próximo game tick
				Debug::debug(Debug::gameEngine,__FUNCTION__) << "Speed Counter: " << Global::speed_counter << " SDL ticks (ms): " << SDL_GetTicks() <<endl;
				runCounter = 0;
				CLogic::runCount = (int) runCounter;
				bool need_draw = false;
				float interpolation;
                Debug::debug(Debug::gameEngine,__FUNCTION__) << "RunCounter: " << runCounter << endl;
				
				while (SDL_GetTicks() > next_game_tick && runCounter < MAX_FRAMESKIP){
                    need_draw = true;
                    CInputManager::poolEvents();
                    runCounter ++;
					logicCount += 1;
                    diff.startTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "RunCounter after get events: " << runCounter << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			
                    logic.run();
					diff.endTime();
					CLogic::logicTime=diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to run the logic: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			        next_game_tick += Global::SKIP_TICKS;
					if (logicCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Logic average " << (CLogic::logicTime / logicCount / 1000.0) << "ms" << std::endl;
                        logicCount = 0;
                        CLogic::logicTime = 0;
                    }
                    
					if (Global::shutdown()){
                        throw CShutdownException();
                    }

                    if (logic.done()){
                        /* quit the loop immediately */
                        throw CLoopDone();
                    }
                }

                if (need_draw){
					interpolation = float( SDL_GetTicks()+ Global::SKIP_TICKS - next_game_tick )
                        / float( Global::SKIP_TICKS );
        
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					frameCount += 1;
					draw.updateFrames();
					diff.startTime();
	                draw.draw(interpolation);

					diff.endTime();
					CDraw::frameTime = diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to draw the game: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					if (frameCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Draw average " << (CDraw::frameTime / frameCount / 1000.0) << "ms" << std::endl;
                        frameCount = 0;
                        CDraw::frameTime = 0;
                    }
                }
          //  }  //end if
			Debug::debug(Debug::gameEngine,__FUNCTION__) << "Speed Counter after logic and draw: " << Global::speed_counter  << " SDL ticks (ms): " << SDL_GetTicks() << endl;

          
        }
    } catch (const CLoopDone & done){
    }
}


// http://www.koonsolo.com/news/dewitters-gameloop/
////http://entropyinteractive.com/2011/02/game-engine-design-the-game-loop/
//
/*
This is a solution with one huge benefit: it’s simple! Since you know that update_game() gets called 25 times per second, writing your game code is quite straight forward. For example, implementing a replay function in this kind of game loop is easy. If no random values are used in the game, you can just log the input changes of the user and replay them later. On your testing hardware you can adapt the FRAMES_PER_SECOND to an ideal value, but what will happen on faster or slower hardware? Well, let’s find out.
Slow hardware

If the hardware can handle the defined FPS, no problem. But the problems will start when the hardware can’t handle it. The game will run slower. In the worst case the game has some heavy chunks where the game will run really slow, and some chunks where it runs normal. The timing becomes variable which can make your game unplayable.
Fast hardware

The game will have no problems on fast hardware, but you are wasting so many precious clock cycles. Running a game on 25 or 30 FPS when it could easily do 300 FPS… shame on you! You will lose a lot of visual appeal with this, especially with fast moving objects. On the other hand, with mobile devices, this can be seen as a benefit. Not letting the game constantly run at it’s edge could save some battery time.
Conclusion

Making the FPS dependent on a constant game speed is a solution that is quickly implemented and keeps the game code simple. But there are some problems: Defining a high FPS will pose problems on slower hardware, and defining a low FPS will waste visual appeal on fast hardware.

*/
static void FPSDependentConstantGmeSpeedLoop(CLogic & logic, CDraw & draw) {
	unsigned long long int next_game_tick =SDL_GetTicks();
	int sleep_time =0;
	TimeDifference diff;
	bool need_draw=true;
	const int maxCount = 20;  //tempo usado para fazer o calculo da média de tempo gasto
    int frameCount = 0;
    int logicCount = 0;

try{
        while (!logic.done()){  //run flag
        
           			logicCount += 1;
                    CInputManager::poolEvents();
                    
					diff.startTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			
                    logic.run();
					diff.endTime();
					CLogic::logicTime=diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to run the logic: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			        
					if (logicCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Logic average " << (CLogic::logicTime / logicCount / 1000.0) << "ms" << std::endl;
                        logicCount = 0;
                        CLogic::logicTime = 0;
                    }
                    
					if (Global::shutdown()){
                        throw CShutdownException();
                    }

                    if (logic.done()){
                        /* quit the loop immediately */
                        throw CLoopDone();
                    }



		if (need_draw){  //always true
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					frameCount += 1;
					draw.updateFrames();
					diff.startTime();
	                draw.draw(draw.getFps());

					diff.endTime();
					CDraw::frameTime = diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to draw the game: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					if (frameCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Draw average " << (CDraw::frameTime / frameCount / 1000.0) << "ms" << std::endl;
                        frameCount = 0;
                        CDraw::frameTime = 0;
                    }
			} //end draw

		next_game_tick += Global::SKIP_TICKS;
		sleep_time= next_game_tick - SDL_GetTicks();
		if ( sleep_time >=0) {
			Util::rest(sleep_time);
		}else {
			//maquina muito lenta
		}

		} //end while

	} catch (const CLoopDone & done){
		}
}
/*
Another implementation of a game loop is to let it run as fast as possible, and let the FPS dictate the game speed. The game is updated with the time difference of the previous frame.

    DWORD prev_frame_tick;
    DWORD curr_frame_tick = GetTickCount();

    bool game_is_running = true;
    while( game_is_running ) {
        prev_frame_tick = curr_frame_tick;
        curr_frame_tick = GetTickCount();

        update_game( curr_frame_tick - prev_frame_tick );
        display_game();
    }

The game code becomes a bit more complicated because we now have to consider the time difference in the update_game() function. But still, it’s not that hard. At first sight this looks like the ideal solution to our problem. I have seen many smart programmers implement this kind of game loop. Some of them probably wished they would have read this article before they implemented their loop. I will show you in a minute that this loop can have serious problems on both slow and fast (yes, FAST!) hardware.
Slow Hardware

Slow hardware can sometimes cause certain delays at some points, where the game gets “heavy”. This can definitely occur with a 3D game, where at a certain time too many polygons get shown. This drop in frame rate will affect the input response time, and therefore also the player’s reaction time. The updating of the game will also feel the delay and the game state will be updated in big time-chunks. As a result the reaction time of the player, and also that of the AI, will slow down and can make a simple maneuver fail, or even impossible. For example, an obstacle that could be avoided with a normal FPS, can become impossible to avoid with a slow FPS. A more serious problem with slow hardware is that when using physics, your simulation can even explode

!
Fast Hardware

You are probably wondering how the above game loop can go wrong on fast hardware. Unfortunately, it can, and to show you, let me first explain something about math on a computer. The memory space of a float or double value is limited, so some values cannot be represented. For example, 0.1 cannot be represented binary, and therefore is rounded when stored in a double. Let me show you using python:

>>> 0.1
0.10000000000000001

This itself is not dramatic, but the consequences are. Let’s say you have a race-car that has a speed of 0.001 units per millisecond. After 10 seconds your race-car will have traveled a distance of 10.0. If you split this calculation up like a game would do, you have the following function using frames per second as input:

>>> def get_distance( fps ):
...     skip_ticks = 1000 / fps
...     total_ticks = 0
...     distance = 0.0
...     speed_per_tick = 0.001
...     while total_ticks < 10000:
...             distance += speed_per_tick * skip_ticks
...             total_ticks += skip_ticks
...     return distance

Now we can calculate the distance at 40 frames per second:

>>> get_distance( 40 )
10.000000000000075

Wait a minute… this is not 10.0??? What happened? Well, because we split up the calculation in 400 additions, a rounding error got big. I wonder what will happen at 100 frames per second…

>>> get_distance( 100 )
9.9999999999998312

What??? The error is even bigger!! Well, because we have more additions at 100 fps, the rounding error has more chance to get big. So the game will differ when running at 40 or 100 frames per second:

>>> get_distance( 40 ) - get_distance( 100 )
2.4336088699783431e-13

You might think that this difference is too small to be seen in the game itself. But the real problem will start when you use this incorrect value to do some more calculations. This way a small error can become big, and fuck up your game at high frame rates. Chances of that happening? Big enough to consider it! I have seen a game that used this kind of game loop, and which indeed gave trouble at high frame rates. After the programmer found out that the problem was hiding in the core of the game, only a lot of code rewriting could fix it.
Conclusion

This kind of game loop may seem very good at first sight, but don’t be fooled. Both slow and fast hardware can cause serious problems for your game. And besides, the implementation of the game update function is harder than when you use a fixed frame rate, so why use it?


*/
static void GSDepOnVariableFPSLoop(CLogic & logic, CDraw & draw) {
	unsigned long long int prev_game_tick ;
	unsigned long long int curr_game_tick =SDL_GetTicks();
	TimeDifference diff;
	bool need_draw=true;
	const int maxCount = 20;  //tempo usado para fazer o calculo da média de tempo gasto
    int frameCount = 0;
    int logicCount = 0;

try{
        while (!logic.done()){  //run flag
					prev_game_tick=curr_game_tick;
					curr_game_tick=SDL_GetTicks();
					CLogic::runCount=curr_game_tick-prev_game_tick;
           			logicCount += 1;
                    CInputManager::poolEvents();
					diff.startTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			
                    logic.run(CLogic::runCount);
					diff.endTime();
					CLogic::logicTime=diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to run the logic: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			        
					if (logicCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Logic average " << (CLogic::logicTime / logicCount / 1000.0) << "ms" << std::endl;
                        logicCount = 0;
                        CLogic::logicTime = 0;
                    }
                    
					if (Global::shutdown()){
                        throw CShutdownException();
                    }

                    if (logic.done()){
                        /* quit the loop immediately */
                        throw CLoopDone();
                    }



		if (need_draw){  //always true
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					frameCount += 1;
					draw.updateFrames();
					diff.startTime();
	                draw.draw(draw.getFps());

					diff.endTime();
					CDraw::frameTime = diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to draw the game: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					if (frameCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Draw average " << (CDraw::frameTime / frameCount / 1000.0) << "ms" << std::endl;
                        frameCount = 0;
                        CDraw::frameTime = 0;
                    }
			}
		} //end draw

	} catch (const CLoopDone & done){
		}
}
/* Adding A wait to next tick for very fast machines*/
static void GSDepOnVariableFPS_ADVLoop(CLogic & logic, CDraw & draw) {
	unsigned long long int first_game_tick ;
	unsigned long long int prev_game_tick ;
	unsigned long long int curr_game_tick =SDL_GetTicks();
	TimeDifference diff;
	bool need_draw=true;
	const int maxCount = 20;  //tempo usado para fazer o calculo da média de tempo gasto
    int frameCount = 0;
    int logicCount = 0;
	curr_game_tick=SDL_GetTicks()/logic.ticks(0);
	prev_game_tick=curr_game_tick-1;
	first_game_tick=SDL_GetTicks()/logic.ticks(0);
try{
        while (!logic.done()){  //run flag
		prev_game_tick=curr_game_tick;
		// 1. Wait for the next tick (on extremely fast machines..)
		while (1)
		{
			curr_game_tick = SDL_GetTicks()/logic.ticks(0);
			if ( prev_game_tick==curr_game_tick )
			{
				SDL_Delay(1);
			}
			else
			{
				break;
			}
		}
		
		CLogic::runCount=curr_game_tick-prev_game_tick;
        
					
           			CInputManager::poolEvents();
                    logicCount += 1;
                    diff.startTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			
                    logic.run(CLogic::runCount);
					diff.endTime();
					CLogic::logicTime=diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to run the logic: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END RUN LOGIC =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
			        
					if (logicCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Logic average " << (CLogic::logicTime / logicCount / 1000.0) << "ms" << std::endl;
                        logicCount = 0;
                        CLogic::logicTime = 0;
                    }
                    
					if (Global::shutdown()){
                        throw CShutdownException();
                    }

                    if (logic.done()){
                        /* quit the loop immediately */
                        throw CLoopDone();
                    }



		if (need_draw){  //always true
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					frameCount += 1;
					draw.updateFrames();
					diff.startTime();
	                draw.draw(draw.getFps());

					diff.endTime();
					CDraw::frameTime = diff.getTime();
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "Time to draw the game: " + diff.printTime("") << endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "===END DRAW GAME =================================: " <<  endl;
					Debug::debug(Debug::gameEngine,__FUNCTION__) << "=================================================: " <<  endl;
					if (frameCount >= maxCount){
                        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Draw average " << (CDraw::frameTime / frameCount / 1000.0) << "ms" << std::endl;
                        frameCount = 0;
                        CDraw::frameTime = 0;
                    }
			}
		} //end draw

	} catch (const CLoopDone & done){
		}
}





void SGE_standardLoop(CLogic & logic, CDraw & draw){
         Input::CLogic::type localLogicType = logic.m_logicType;  
	switch(localLogicType) {
	  case Input::CLogic::PT_Logic: doLoop(logic,draw);
		   break;
	case Input::CLogic::FPS_Dep_GS_Const:  FPSDependentConstantGmeSpeedLoop(logic,draw);
           break;
	case Input::CLogic::FPS_Dep_GS_Const_Adv:  break;
	case Input::CLogic::FPS_Dep_GF_Const_MAdv:  break;
	case Input::CLogic::GS_Dep_FPS_Var: GSDepOnVariableFPSLoop(logic,draw); break;
	case Input::CLogic::GS_Dep_FPS_Var_Adv: GSDepOnVariableFPS_ADVLoop(logic,draw); break;
	case Input::CLogic::GS_Const_FPS_Max: GSConstWithMaxFPS(logic,draw); break;
	case Input::CLogic::GS_Const_InDep_FPS_Var: GSConstIndFPS(logic,draw); break;

	default: doLoop(logic,draw); break;
	}
}

}

} //end SGF