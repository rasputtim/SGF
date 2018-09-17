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
#ifndef _joystick_h
#define _joystick_h

#include <vector>
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"
#include "SGF_StructsInput.h"
#include "../util/SGF_Thread.h"


using namespace std;
namespace SGF{

class CButtonMapping;


/**
 * \class CJoystick
 *
 * \ingroup SGF_Input
 * 
 * \brief Classe Base para tratamento de Joystick
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CJoystick{
public:
    virtual void poll() = 0;
    virtual JoystickInput readAll() = 0;
    virtual bool pressed();
    virtual ~CJoystick();

	virtual int getDeviceId() const = 0;
    virtual void pressButton(int button)= 0;
    virtual void releaseButton(int button)= 0;
    virtual void axisMotion(int axis, int motion)= 0;
	virtual void hatMotion(int motion)=0;

    static CJoystick * create(int id=0);
	static int readJoyKey();
	static int numberOfJoysticks();
		/*
Mapeamento de joystick PS2 para SGF::CJoystick

Botao 1 = Triangulo
Botao 2 = Circulo
Botao 3 = cruz
Botao 4 = quadrado
Botao 5 = L1
Botao 6 = R1
Botao 7 = L2
Botao 8 = R2
Botao 9 = Select
Botao 10 = Start
Botao 11 = L3
Botao 12 = R3


*/
    enum Key{
		MIN = -1,
        Invalid = MIN,
        Up = 0,  //equivalente a axis 1D1
        Down,    //equivalente a axis 1D2
        Left,  //equivalente a axis 0D1
        Right,  //equivalent a axis 0D2
		Axis2D1,
		Axis2D2,
		Axis3D1,
		Axis3D2,
		Axis4D1,
		Axis4D2,
        Button1,
        Button2,
        Button3,
        Button4,
		Button5,
        Button6,
		Button7,
        Button8,
		Button9,
        Button10,
		Button11,
        Button12,
        Hat1,
		Hat2,
		Hat3,
		Hat4,
		Hat5,
		Hat6,
		Hat7,
		Hat8,
		Track1,
		Track2,
		MAX = Track2
    };

	//typedef Key Event;
    
	struct Event{
        Event(Key key, bool enabled):
        key(key), enabled(enabled){
        }

        Key key;
        bool enabled;
    };

    virtual inline const vector<Event> & getEvents() const {
        return events;
    }
	

    static const char * keyToName(Key key);
    void GetDefaults();
	void Lock() { joystickLock.acquire();}
	void Unlock() { joystickLock.release();}
protected:
	::SGF::Util::Thread::LockObject joystickLock;
	
    vector<Event> events;
    CJoystick();
    
};
} //end SGF
#endif
