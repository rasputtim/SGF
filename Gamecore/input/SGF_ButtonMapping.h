
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

#ifndef _SGF_BuTTON_MAPPING_h
#define _SGF_BuTTON_MAPPING_h

#include "SGF_Joystick.h"
#include <vector>

using namespace std;
namespace SGF{

class CJoystick;


/**
 * \class CButtonMapping
 *
 * \ingroup SGF_Input
 * 
 * \brief Mapeamento de Botões do Joystick
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class CButtonMapping{
public:
    CButtonMapping(){
    }

    virtual ~CButtonMapping(){
    }

    virtual int toNative(int button) = 0;
    virtual int fromNative(int button) = 0;
    virtual CJoystick::Key toKey(int button) = 0;
    virtual void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events) = 0;
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events) = 0;

};

class DefaultButtonMapping: public CButtonMapping {
public:
    int toNative(int button){
        return button;
    }

    int fromNative(int button){
        return button;
    }

    CJoystick::Key toKey(int button);
    
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);

    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);
};

/* used when a ps3 controller is plugged into a usb port of a normal pc */
class Playstation3Controller: public CButtonMapping {
public:
    enum Buttons{
        Cross = 14,
        Circle = 13,
        Triangle = 12,
        Square = 15,
        Start = 3,
        Select = 0,
        Up = 4,
        Left = 7,
        Down = 6,
        Right = 5,
        Stick1_L3 = 1,
        Stick2_R3 = 2,
        L2 = 8,
        L1 = 10,
        R2 = 9,
        R1 = 11,
		/* the middle ps3 button */
        Ps3 = 16
    };

    int toNative(int button);

    int fromNative(int button);

    CJoystick::Key toKey(int button);
    
    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);

    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);
};

class LogitechPrecision: public CButtonMapping {
public:
    enum Buttons{
        Button1 = 0,
        Button2 = 1,
        Button3 = 2,
        Button4 = 3,
        Start = 8,
        Select = 9,
        R2 = 7,
        R1 = 5,
        L2 = 6,
        L1 = 4
    };

    int toNative(int button){
        return -1;
    }

    int fromNative(int button){
        return -1;
    }
    
    CJoystick::Key toKey(int button);
    
    /* axis 1. negative up, positive down
     * axis 0, negative left, positive right
     */
    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);

};

/* used for the ps3 controller with psl1ght's SDL version */
class Ps3Controller: public CButtonMapping {
public:
    enum Buttons{
        Left = 0,
        Down = 1,
        Right = 2,
        Up = 3,
        Select = 7,
        Start = 4,
        Square = 8,
        Cross = 9,
        Circle = 10,
        Triangle = 11,
        L1 = 13,
        R1 = 12,
        L2 = 15,
        R2 = 14,
        L3 = 6,
        R3 = 5
    };

    int toNative(int button);

    int fromNative(int button);

    CJoystick::Key toKey(int button);

    
    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);
    
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);
};

class XBox360Controller: public CButtonMapping {
public:
    enum Buttons{
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        L1 = 4,
        R1 = 5,
        Start = 6,
        Xbox = 7,
        L3 = 8,
        R3 = 9,
        select = 10
    };

    int toNative(int button){
        return 0;
    }

    int fromNative(int button){
    	return 0;
    }
    
    CJoystick::Key toKey(int button);
    
    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);
    
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);
};

class Wiimote: public CButtonMapping {
public:
    enum Buttons{
        A = 0,
        B = 1,
        Button1 = 2,
        Button2 = 3,
        Minus = 4,
        Plus = 5,
        Home = 6
    };

    int toNative(int button){
        return 0;
    }

    int fromNative(int button){
    	return 0;
    }
    
    CJoystick::Key toKey(int button);
    
    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);
    
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);
};

class GamecubePad: public CButtonMapping {
public:
    enum Buttons{
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        Z = 4,
        Start = 7
    };

    int toNative(int button){
        return 0;
    }

    int fromNative(int button){
    	return 0;
    }
    
    CJoystick::Key toKey(int button);
    
    void axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events);
    
    virtual void hatMotionEvents(int motion, vector<CJoystick::Event> & events);

};

} // end SGF
#endif
