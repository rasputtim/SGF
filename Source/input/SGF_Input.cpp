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


#include "input/SGF_Input.h"


using namespace std;
namespace SGF {

//Constructor
CInput::CInput()
{}
//Destructor
CInput::~CInput()
{}
/*
static CInput::GameKeys convertKey(const CConfiguration & configuration, const int facing, const int key){
    if (key == configuration.getRight()){
        switch (facing){
            case CObject::FACING_LEFT : return CInput::Back;
            case CObject::FACING_RIGHT : return CInput::Forward;
        }
    } else if (key == configuration.getLeft()){
        switch (facing){
            case CObject::FACING_LEFT : return CInput::Forward;
            case CObject::FACING_RIGHT : return CInput::Back;
        }
    } else if (key == configuration.getButtonX()){  //jump
        return CInput::ButtonX;  //enum gameinput
    } else if (key == configuration.getUp()){
        return CInput::Up;
    } else if (key == configuration.getDown()){
        return CInput::Down;
    } else if (key == configuration.getButtonA()){
        return CInput::ButtonA;
    } else if (key == configuration.getButtonB()){
        return CInput::ButtonB;
    } else if (key == configuration.getButtonC()){
        return CInput::ButtonC;
    }

    return CInput::Unknown;
}

*/
//Process InputData


    
/*
void CInput::HandleKeyboardRepeating(KEYBOARDDATA *lpKeyBoard)
{

}

*/

/*
void CInput::HandleMouseMotion(){}
void CInput::HandleMouseSingle() {}
void CInput::HandleMouseRepeating(){}
void CInput::HandleInput() {}
void CInput::HandleKeySingle(SDL_KeyboardEvent key) {}
*/
} //end SGF