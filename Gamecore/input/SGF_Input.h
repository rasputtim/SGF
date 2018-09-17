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
#ifndef _S_G_F_INPUT_H___
#define _S_G_F_INPUT_H___

#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"

using namespace std;
namespace SGF{

/**
 * \class CInput
 *
 * \ingroup SGF_Input
 *
 * \brief Define e converte game input
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CInput
{
public:
    CInput();
    ~CInput();

/*Default game keys */
enum GameKeys{
        Unknown = -1,
		MINGameKey = 0,
        Forward = MINGameKey,
        Back = 1,
        Up = 2,
        Down = 3,
        Button1 = 4,
        Button2 = 5,
        Button3 = 6,
        Button4 = 7,
		Button5 = 8,
        Button6 = 9,
        Button7 = 10,
		Button8 = 11,
        Button9 = 12,
		Jump = 13,
		Grab = 14,
		Start = 15,
		Select = 16,
		Deal = 17,
		Bet = 18,
		DoubleUP = 19,
		Stand = 20,
		Open = 21,
        Config = 22,
		Pause = 23,
		Reset = 24,
		ShowGFX = 25,
		ShowFPS = 26,
		SaveConfig = 27,
		LoadConfig = 28,
		Debugger = 29,
		ToggleConsole = 30,
		Reload = 31,
		Cancel = 32,
		Quit = 33,
		MAXGameKey = Quit,
    };
#if 0
enum UserKeys{
	    MINUser = 100,
		Config = MINUser,
		Pause = 101,
		Reset = 102,
		ShowGFX = 103,
		ShowFPS = 104,
		SaveConfig = 105,
		LoadConfig = 106,
		Debugger = 107,
		ToggleConsole = 108,
		Reload = 109,
		MAXUser = Reload,
};
#endif
};
} //end SGF
#endif /*INPUT_H_*/
