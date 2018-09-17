#include "input/SGF_InputSource.h"

using namespace std;
namespace SGF {

CInputSource::CInputSource():
m_keyboard(0),
m_joystick(0),
m_mouse(0){
}
    
CInputSource::CInputSource(int keyboard, int joystick, int mouse):
m_keyboard(keyboard),
m_joystick(joystick),
m_mouse(mouse){
}
    
CInputSource::CInputSource(const CInputSource & copy):
m_keyboard(copy.m_keyboard),
m_joystick(copy.m_joystick),
m_mouse(copy.m_mouse){
}
    
CInputSource & CInputSource::operator=(const CInputSource & copy){
    this->m_keyboard = copy.m_keyboard;
    this->m_joystick = copy.m_joystick;
	this->m_mouse = copy.m_mouse;
    return *this;
}

CInputSource::~CInputSource(){
}
    
bool CInputSource::useKeyboard() const {
    return m_keyboard >= 0;
}

bool CInputSource::useJoystick() const {
    return m_joystick >= 0;
}
bool CInputSource::useMouse() const {
    return m_mouse >= 0;
}

int CInputSource::getKeyboard() const{
    return m_keyboard;
}
    
int CInputSource::getJoystick() const {
    return m_joystick;
}
int CInputSource::getMouse() const{
    return m_mouse;
}

} //end SGF