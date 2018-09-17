#ifndef _S_G_F_wii_joystick_h
#define _S_G_F_wii_joystick_h

#ifdef WII

#include "../joystick.h"
namespace SGF{

class WiiJoystick: public Joystick {
public:
    virtual void poll();
    virtual int getDeviceId() const;

    virtual ~WiiJoystick();

    friend class Joystick;
protected:
    WiiJoystick();
};
} //end SGF
#endif

#endif
