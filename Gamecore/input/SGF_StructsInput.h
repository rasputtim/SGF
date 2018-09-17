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

#ifndef _S_G_F_INPUT_STRUCTS_H_
#define _S_G_F_INPUT_STRUCTS_H_

#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"

using namespace std;
namespace SGF{

#ifndef STRINGSIZE
	#define STRINGSIZE 30
#endif
//! struct criada para armazenar o estado das teclas físicas do joystick num determinado instante
// false significa que o botão não foi pressionado e 1 significa que o botão foi pressionado
// esse controle é digital apenas. não mede a quantidade de tempo que uma tecla foi ou não pressionada

struct JoystickInput{
    JoystickInput():
        j_axis_0_left(false),
        j_axis_0_right(false),
        j_axis_1_up(false),
        j_axis_1_down(false),
		j_axis_2_direction1(false),
		j_axis_2_direction2(false),
		j_axis_3_direction1(false),
		j_axis_3_direction2(false),
		j_axis_4_direction1(false),
		j_axis_4_direction2(false),
		jbutton1(false),
        jbutton2(false),
        jbutton3(false),
        jbutton4(false),
		jbutton5(false),
		jbutton6(false),
		jbutton7(false),
        jbutton8(false),
        jbutton9(false),
        jbutton10(false),
		jbutton11(false),
		jbutton12(false),
		jhat1(false),
		jhat2(false),
		jhat3(false),
		jhat4(false),
		jhat5(false),
		jhat6(false),
		jhat7(false),
		jhat8(false),
		jtrack1(false),
		jtrack2(false),
		jquit(false){
    }

    JoystickInput(const JoystickInput & copy):
        j_axis_0_left(copy.j_axis_0_left),
        j_axis_0_right(copy.j_axis_0_right),
        j_axis_1_up(copy.j_axis_1_up),
        j_axis_1_down(copy.j_axis_1_down),
		j_axis_2_direction1(copy.j_axis_2_direction1),
		j_axis_2_direction2(copy.j_axis_2_direction2),
		j_axis_3_direction1(copy.j_axis_3_direction1),
		j_axis_3_direction2(copy.j_axis_3_direction2),
		j_axis_4_direction1(copy.j_axis_4_direction1),
		j_axis_4_direction2(copy. j_axis_4_direction2),
		jbutton1(copy.jbutton1),
        jbutton2(copy.jbutton2),
        jbutton3(copy.jbutton3),
        jbutton4(copy.jbutton4),
		jbutton5(copy.jbutton5),
		jbutton6(copy.jbutton6),
		jbutton7(copy.jbutton7),
        jbutton8(copy.jbutton8),
        jbutton9(copy.jbutton9),
        jbutton10(copy.jbutton10),
		jbutton11(copy.jbutton11),
		jbutton12(copy.jbutton12),
		jhat1(copy.jhat1),
		jhat2(copy.jhat2),
		jhat3(copy.jhat3),
		jhat4(copy.jhat4),
		jhat5(copy.jhat5),
		jhat6(copy.jhat6),
		jhat7(copy.jhat7),
		jhat8(copy.jhat8),
		jtrack1(copy.jtrack1),
		jtrack2(copy.jtrack2),
		jquit(copy.jquit){

    }

		/* true if something is pressed */
    bool pressed(){
        bool press = j_axis_0_left || j_axis_0_right || j_axis_1_up || j_axis_1_down ||
				j_axis_2_direction1 || j_axis_2_direction2 || j_axis_3_direction1 ||j_axis_3_direction2 ||
				j_axis_4_direction1 ||j_axis_4_direction2 ||
				jbutton1 || jbutton2 || jbutton3 || jbutton4||
			   jbutton5 || jbutton6 || jbutton7 || jbutton8 ||
			   jbutton9 || jbutton10 || jbutton11 || jbutton12 ||
			   jhat1 || jhat2 || jhat3 ||
			   jhat4 || jhat5 || jhat6 || jhat7 || jhat8 ||
			   jtrack1 || jtrack2 || jquit;
		return press;
	}
    bool j_axis_0_left;
    bool j_axis_0_right;
    bool j_axis_1_up;
    bool j_axis_1_down;
	bool j_axis_2_direction1;
    bool j_axis_2_direction2;
    bool j_axis_3_direction1;
    bool j_axis_3_direction2;
	bool j_axis_4_direction1;
    bool j_axis_4_direction2;
    bool jbutton1;
    bool jbutton2;
    bool jbutton3;
    bool jbutton4;
	bool jbutton5;
	bool jbutton6;
	bool jbutton7;
    bool jbutton8;
	bool jbutton9;
    bool jbutton10;
    bool jbutton11;
    bool jbutton12;
	bool jhat1;
	bool jhat2;
	bool jhat3;
	bool jhat4;
	bool jhat5;
	bool jhat6;
	bool jhat7;
	bool jhat8;
	bool jtrack1;
	bool jtrack2;
	bool jquit;  // botao virtual
};

//#define MAX_PATH 255

#define PRESSED  200
#define RELEASED 100
//#define NONE     0   //redefinido no arquivo mugen/menu_v1.h

//Define  Controller buttoms
#define RIGHT     1   // mouse and keyboard
#define LEFT      2   // mouse and keyboard
#define UP        3
#define DOWN      4
#define BUTTONA   5
#define BUTTONB   6
#define BUTTONC   7
#define BUTTONX   8
#define BUTTONY   9
#define BUTTONZ   10
#define MIDDLE	  11   // mouse
#define BUTTONX1		  12   // mouse
#define BUTTONX2        13   // mouse



struct PLKEY
{
    Sint32 key;   //scancode da tecla
    Uint32 nTime;  //delay da tecla pressionada
    bool bPressed; // se foi pressionada ou não

};

struct KEYELEMENT
{
    Uint16 nKey;
    Uint32 nTime;
    Uint32 nKeyTime;


};

#define MAXCOMMAND 30

//now lets define a command
struct PLCOMMAND
{
    Uint16 nCommand[MAXCOMMAND];
    Uint8 nHowManyCommand;
    Uint8 nCommandTime;
    char strCommand[STRINGSIZE];

};


//Movedata Struct for Saving the current Button States
struct KEYBOARDDATA
{
  PLKEY Right;
  PLKEY Left;
  PLKEY Up;
  PLKEY Down;
  PLKEY ButtonA;
  PLKEY ButtonB;
  PLKEY ButtonC;
  PLKEY ButtonX;
  PLKEY ButtonY;
  PLKEY ButtonZ;
  PLKEY bStart;
  PLKEY bPause;
  short nKey;  //scancode da tecla
  bool bKeyBoard;
};

struct MOUSEMOVE
	{

	MOUSEMOVE():
	x(0),
	y(0),
	bRelative(0){}

	signed int x;
    signed int y;
    bool bRelative;   // 0  means absolute - 1 means relative

	};

struct MOUSEDATA
{
  PLKEY Right;
  PLKEY Left;
  PLKEY Middle;
  PLKEY X1;
  PLKEY X2;
  short nKey;
  bool bMouse;
};

struct MouseMoveData{
       MouseMoveData():
       	movedUp(0),
		movedDown(0),
		movedLeft(0),
		movedRight(0),
		enabled(false){
        }

       MouseMoveData(signed int x, signed int y, bool enabled, bool relative):
		enabled(enabled){
			position.x=x;
			position.y=y;
			position.bRelative=relative;
        }
		 MouseMoveData & operator=(const  MouseMoveData & data){
			if (&data==this){
				 return *this;
			 }

			this->position.bRelative = data.position.bRelative;
			this->position.x = data.position.x;
			this->position.y = data.position.y;
			this->movedDown = data.movedDown;
			this->movedLeft = data.movedLeft;
			this->movedRight = data.movedLeft;
			this->movedRight = data.movedRight;
			return *this;
		};

		MOUSEMOVE position;
        bool movedUp;
		bool movedDown;
		bool movedLeft;
		bool movedRight;
        /* whether the Mousekey is being pressed */
        bool enabled;
    };
} //end SGF
#endif
