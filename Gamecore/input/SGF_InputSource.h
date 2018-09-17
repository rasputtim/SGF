#ifndef SGF_Input_Source_h
#define SGF_Input_Source_h
namespace SGF{

/* this class should abstract over actual devices (keyboard, joystick)
 * and return a list of events on request.
 */

class CInputSource{
public:
    CInputSource();
    /* keyboard specifies the configuration to use.
     * joystick specifies the configuration and which physical joystick to use.
     * -1 for keyboard/joystick means don't use it
     * mouse specifies the configuration to use.
     * -1 for keyboard/joystick/mouse means don't use it
     */

    CInputSource(int keyboard, int joystick, int mouse);
    CInputSource(const CInputSource & copy);
    virtual ~CInputSource();

    CInputSource & operator=(const CInputSource &);

    virtual bool useKeyboard() const;
    virtual int getKeyboard() const;
    virtual bool useJoystick() const;
    virtual int getJoystick() const;
	virtual bool useMouse() const;
    virtual int getMouse() const;


private:
    int m_keyboard;
    int m_joystick;
	int m_mouse;
};
} //end SGF
#endif
