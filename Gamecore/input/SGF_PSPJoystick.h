#ifndef _S_G_F_psp_joystick_h
#define _S_G_F_psp_joystick_h

#ifdef MINPSPW

#include "../joystick.h"

#include <pspctrl.h>
namespace SGF{

class PSPJoystick: public Joystick {
public:
    virtual void poll();
    virtual int getDeviceId() const;
    virtual void pressButton(int button);
    virtual void releaseButton(int button);
    virtual void axisMotion(int axis, int motion);

    virtual ~PSPJoystick();

    friend class Joystick;
protected:
    
    void doKeys();
    JoystickInput buffer;
    
    PSPJoystick();
    // joystick
    SceCtrlData joystick;
};
} //end SGF
#endif

#endif
