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
#include <stdlib.h>
#include "SDL.h"
#include "SGF_Global.h"
#include "input/SGF_Joystick.h"
#include "input/sdl-joystick.h"
#include "input/SGF_ButtonMapping.h"

/*
#ifdef LINUX
#include "linux_joystick.h"
#endif
*/


using namespace std;
namespace SGF {
CJoystick * CJoystick::create(int id){
	Debug::debug(Debug::input,__FUNCTION__) << "Will Create a Joystick"<<endl;
 #ifdef WII
    return new CSDLJoystick(id);
    // return new WiiJoystick();
#elif MINPSPW
    return new PSPJoystick(id);
#else
    return new CSDLJoystick(id);
#endif
/*
#ifdef LINUX
    return new LinuxJoystick(id);
#endif
    return NULL;
*/

}

CJoystick::CJoystick(){
}

CJoystick::~CJoystick(){

}
void CJoystick::GetDefaults(){
//Query joystick característics

}
const char * CJoystick::keyToName(Key key){
    switch (key){
        case Invalid : return "Invalid";
        case Up : return "Button Up";
        case Down : return "Button Down";
        case Left : return "Button Left";
        case Right : return "Button Right";
        case Button1 : return "Button1";
        case Button2 : return "Button2";
        case Button3 : return "Button3";
        case Button4 : return "Button4";
		case Button5 : return "Button5";
        case Button6 : return "Button6";
        case Button7 : return "Button7";
        case Button8 : return "Button8";
		case Button9 : return "Button9";
        case Button10 : return "Button10";
        case Button11 : return "Button11";
        case Button12 : return "Button12";
        case Axis2D1 : return "Axis 2 Dirction 1";
        case Axis2D2 : return "Axis 2 Direction 2";
        case Axis3D1 : return "Axis 3 Direction 1";
        case Axis3D2 : return "Axis 3 Direction 2";
        case Axis4D1 : return "Axis 4 Direction 1";
        case Axis4D2 : return "Axis 4 direction 2";
        case Hat1 : return "Hat 1";
        case Hat2 : return "Hat 2";
        case Hat3 : return "Hat 3";
        case Hat4 : return "Hat 4";
        case Hat5 : return "Hat 5";
        case Hat6 : return "Hat 6";
        case Hat7 : return "Hat 7";
        case Hat8 : return "Hat 8";
        case Track1 : return "Track 1";
        case Track2 : return "Track 2";
        //case Quit: return "Quit";
    }
    return "Unknown";
}
bool CJoystick::pressed(){
    JoystickInput input = readAll();
    return input.j_axis_1_up || input.j_axis_1_down || input.j_axis_0_left || input.j_axis_0_right ||
			input.j_axis_2_direction1 || input.j_axis_2_direction2 || input.j_axis_3_direction1 ||input.j_axis_3_direction2 ||
			input.j_axis_4_direction1 ||input.j_axis_4_direction2 ||
			input.jbutton1 || input.jbutton2 || input.jbutton3 || input.jbutton4 ||
		    input.jbutton5 || input.jbutton6 || input.jbutton7 || input.jbutton8 ||
			input.jbutton9 || input.jbutton10 || input.jbutton11 || input.jbutton12 ||
           input.jquit;
}

} //end SGF