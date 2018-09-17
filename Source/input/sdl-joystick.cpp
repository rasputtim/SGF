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

#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include "input/sdl-joystick.h"
#include "util/SGF_Debug.h"
#include "input/SGF_ButtonMapping.h"
#include "external/fastevents.h"

/*
Mapeamento de joystick PS2 para SDL

Botao 0 = Triangulo
Botao 1 = Circulo
Botao 2 = cruz
Botao 3 = quadrado
Botao 4 = L1
Botao 5 = R1
Botao 6 = L2
Botao 7 = R2
Botao 8 = Select
Botao 9 = Start
Botao 10 = L3
Botao 11 = R3


*/

using namespace std;
namespace SGF {
class CJoystick;
static bool read_button(SDL_Joystick * joystick, int button){
    return SDL_JoystickGetButton(joystick, button);
}
void CSDLJoystick::poll(){
    events.clear();
	SDL_JoystickUpdate();
	//Updates the state(position, buttons, etc.) of all open joysticks. If joystick events have been enabled with SDL_JoystickEventState then this is called automatically in the event loop.
}
	/*
Mapeamento de joystick PS2 para SDL

Botao 0 = Triangulo
Botao 1 = Circulo
Botao 2 = cruz
Botao 3 = quadrado
Botao 4 = L1
Botao 5 = R1
Botao 6 = L2
Botao 7 = R2
Botao 8 = Select
Botao 9 = Start
Botao 10 = L3
Botao 11 = R3


*/
JoystickInput CSDLJoystick::readAll(){
	Debug::debug(Debug::input,__FUNCTION__) << endl;
	JoystickInput input;
	memset(&input,0,sizeof(input));
    //mapeia o estado dos botões do joystick na classe input
	if (stick) {
	switch(number_of_buttons > 12 ? 12 : number_of_buttons){
        case 12: input.jbutton12 = read_button(stick, 11);  //R3
		case 11: input.jbutton11 = read_button(stick, 10); // L3
        case 10: input.jbutton10 = read_button(stick, 9);  // start
		case 9: input.jbutton9= read_button(stick, 8); // Select
        case 8: input.jbutton8 = read_button(stick, 7);   //R2
        case 7: input.jbutton7 = read_button(stick, 6);   //L2
        case 6: input.jbutton6 = read_button(stick, 5);   //R1
		case 5: input.jbutton5= read_button(stick, 4);    // L1
		case 4: input.jbutton4 = read_button(stick, 3);   // b = retorna o estado on ou off do botão do joytstick
        case 3: input.jbutton3 = read_button(stick, 2);
        case 2: input.jbutton2 = read_button(stick, 1);
        case 1: input.jbutton1 = read_button(stick, 0);
        case 0: {
            break;
        }
    }
	input.jquit = input.jbutton9;  //user select como quit
	//wait for button

	Debug::debug(Debug::input,__FUNCTION__) << "input 1 button: "<< input.jbutton1<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 2 button: "<< input.jbutton2<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 3 button: "<< input.jbutton3<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 4 button: "<< input.jbutton4<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 5 button: "<< input.jbutton5<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 6 button: "<< input.jbutton6<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 7 button: "<< input.jbutton7<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 8 button: "<< input.jbutton8<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 9 button: "<< input.jbutton9<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 10 button: "<< input.jbutton10<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 11 button: "<< input.jbutton11<<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "input 12 button: "<< input.jbutton12<<endl;
	//Debug::debug(Debug::input,__FUNCTION__) << "input quit: "<< input.jquit<<endl;

        if (number_of_axis > 0){
            int position = SDL_JoystickGetAxis(stick, 0);  //retorna a posição desta axis
            if (position < 0){
                input.j_axis_0_left = true;
            } else if (position > 0){
                input.j_axis_0_right = true;
            }
        }
		if (number_of_axis > 1){
            int position = SDL_JoystickGetAxis(stick, 1);
            if (position < 0){
                input.j_axis_1_up = true;
            } else if (position > 0){
                input.j_axis_1_down = true;
            }
        }
		if (number_of_axis > 2){
            int position = SDL_JoystickGetAxis(stick, 2);
            if (position < 0){
               input.j_axis_2_direction1 = true;
            } else if (position > 0){
              input.j_axis_2_direction2 = true;
            }
        }
		if (number_of_axis > 3){
            int position = SDL_JoystickGetAxis(stick, 3);
            if (position < 0){
                input.j_axis_3_direction1 = true;
            } else if (position > 0){
                input.j_axis_3_direction2 = true;
            }
        }
		if (number_of_axis > 4){
            int position = SDL_JoystickGetAxis(stick, 4);
            if (position < 0){
                input.j_axis_4_direction1 = true;
            } else if (position > 0){
                input.j_axis_4_direction2 = true;
            }
        }

		if (number_of_hats > 0){
        int hat = SDL_JoystickGetHat(stick, 0);
        if ((hat & SDL_HAT_UP) == SDL_HAT_UP){
            input.j_axis_1_up = true;
        }
        if ((hat & SDL_HAT_DOWN) == SDL_HAT_DOWN){
            input.j_axis_1_down = true;
        }
        if ((hat & SDL_HAT_LEFT) == SDL_HAT_LEFT){
            input.j_axis_0_left = true;
        }
        if ((hat & SDL_HAT_RIGHT) == SDL_HAT_RIGHT){
            input.j_axis_0_right = true;
        }
        if ((hat & SDL_HAT_RIGHTUP) == SDL_HAT_RIGHTUP){
            input.j_axis_0_right = true;
            input.j_axis_1_up = true;
        }
        if ((hat & SDL_HAT_RIGHTDOWN) == SDL_HAT_RIGHTDOWN){
            input.j_axis_0_right = true;
            input.j_axis_1_down = true;
        }
        if ((hat & SDL_HAT_LEFTDOWN) == SDL_HAT_LEFTDOWN){
            input.j_axis_0_left = true;
            input.j_axis_1_down = true;
        }
        if ((hat & SDL_HAT_LEFTUP) == SDL_HAT_LEFTUP){
            input.j_axis_0_left = true;
            input.j_axis_1_up = true;
        }
    }



	}
    return input;

}



CSDLJoystick::~CSDLJoystick(){
	 if (stick){
		 ::SDL_JoystickClose(stick);
    }
}

CButtonMapping * makeButtonMapping(string name){
#ifdef PS3
    return new Ps3Controller();
#endif
    if (name == "Sony PLAYSTATION(R)3 Controller"){
        return new Playstation3Controller();
    }
    if (name.find("Logitech(R) Precision(TM) Gamepad") != string::npos){
        return new LogitechPrecision();
    }
    if (name == "Microsoft X-Box 360 pad"){
    	return new XBox360Controller();
    }
    if (name.find("Wiimote") != string::npos){
        return new Wiimote();
    }
    if (name.find("Gamecube") != string::npos){
        return new GamecubePad();
    }
    return new DefaultButtonMapping();
}


CSDLJoystick::CSDLJoystick(int id):
stick(NULL)
{

	//Check if there's any joysticks
	if( SDL_NumJoysticks() < 1 )
    {
		Debug::debug(Debug::input,__FUNCTION__) << "CSDLJoystick::CSDLJoystick There is No joystick Installed"<<endl;
    }
	else {
        //Open the joystick
        stick = SDL_JoystickOpen(id );

        //If there's a problem opening the joystick
        if( stick == NULL )
        {
        Debug::debug(Debug::input,__FUNCTION__) << "CSDLManager::Init Problem Opening joystick "<<endl;
        }
		buttonMapping = makeButtonMapping(SDL_JoystickNameForIndex(id));

		number_of_buttons = SDL_JoystickNumButtons(stick);
        number_of_axis = SDL_JoystickNumAxes(stick);
        number_of_balls = SDL_JoystickNumBalls(stick);
        number_of_hats = SDL_JoystickNumHats(stick);
		Debug::debug(Debug::input,__FUNCTION__) << "joystick Opened. Stick: "<< stick <<endl;
		Debug::debug(Debug::input,__FUNCTION__) << "Buttons: "<<number_of_buttons <<endl;
		Debug::debug(Debug::input,__FUNCTION__) << "Axis: "<<number_of_axis <<endl;
		Debug::debug(Debug::input,__FUNCTION__) << "balls: "<< number_of_balls<<endl;
		Debug::debug(Debug::input,__FUNCTION__) << "hats: "<< number_of_hats<<endl;
	}
}

void CSDLJoystick::pressButton(int button){
	Debug::debug(Debug::input,__FUNCTION__) << "button: "<< button <<endl;

	if (stick){
        Key event = buttonMapping->toKey(button);
        if (event != Invalid){
            events.push_back(Event(event, true));
        }
    }

	/*

	if (stick){
        Event event = Invalid;
        switch (button){
            case 0: event = Button1; break;  //triangle
            case 1: event = Button2; break;   //circle
            case 2: event = Button3; break;   // cross
            case 3: event = Button4; break;   //square
			case 4: event = Button5; break;  // L1
            case 5: event = Button6; break;   // R1
            case 6: event = Button7; break;   // L2
            case 7: event = Button8; break;   // R2
			case 8: event = Button9; break;  // Select
            case 9: event = Button10; break;   // Start
            case 10: event = Button11; break;   // L3
            case 11: event = Button12; break;   // R3
            default: break;
        }
        events.push_back(event);
    }*/
}

void CSDLJoystick::releaseButton(int button){
	   if (stick){
        Key event = buttonMapping->toKey(button);
        if (event != Invalid){
            events.push_back(Event(event, false));
        }
    }
}

void CSDLJoystick::hatMotion(int motion){
    if (stick){
        buttonMapping->hatMotionEvents(motion, events);
    }
}

void CSDLJoystick::axisMotion(int axis, int motion){
	Debug::debug(Debug::input,__FUNCTION__) << "axis: "<< axis <<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "motion: "<< motion <<endl;

	   if (stick){
        buttonMapping->axisMotionEvents(axis, motion, events);
        //
        //Event move = buttonMapping->axisMotionToEvent(axis, motion);
        //if (move.key != Invalid){
        //    events.push_back(move);
        //}
    }
}

int CSDLJoystick::getDeviceId() const {
    if (stick){
        return SDL_JoystickInstanceID(stick);
    }

    return -1;
}

int CJoystick::numberOfJoysticks(){
    return SDL_NumJoysticks();
}
int CJoystick::readJoyKey(){
		SDL_Event oSdlEvent;
#ifdef USE_FASTEVENTS
	while (FE_WaitEvent(&oSdlEvent))
#else
 while (SDL_WaitEvent(&oSdlEvent))
#endif
	{
		if ( SDL_JOYBUTTONDOWN == oSdlEvent.type )
		{
			//Debug::debug(Debug::resources,__FUNCTION__) << "The Joykey was pressed="<< SDL_GetKeyName(event.button.button)<<endl;
    		return oSdlEvent.jbutton.button;
		}

	}	// Polling events

	// Code will never reach this point, unless there's an error.
	return SDLK_ESCAPE;
}
} //end SGF