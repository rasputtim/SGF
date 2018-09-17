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
#include "input/SGF_InputManager.h"
#include "SGF_Global.h"

using namespace std;
namespace SGF {
static Input::CEventManager eventManager;

CInputManager * CInputManager::manager = 0;

Util::Thread::LockObject CInputManager::inputLock;

CInputManager::CInputManager():
capture(0),
textInput(Util::CSmartPtr_MT<CTextInput>()){
    manager = this;
   if (CConfiguration::JoystickEnabled.getBool()){
	   
        joysticks.clear();
		for (int i = 0; i < CJoystick::numberOfJoysticks(); i++){
        joysticks[i] = CJoystick::create(i);
		}
   }else joystick = Util::CSmartPtr_MT<CJoystick>();
   if (CConfiguration::MouseEnabled.getBool()){
	   
	mouse = CMouse::create();
   }else mouse = Util::CSmartPtr_MT<CMouse>();
}

CInputManager::~CInputManager(){
}

void CInputManager::deferResizeEvents(bool defer){
    if (manager != NULL){
        eventManager.deferResizeEvents(defer);
		//manager->eventManager.deferResizeEvents(defer);
    }
}
bool CInputManager::anyInput(){
    if (manager == 0){
        Debug::debug(Debug::input,__FUNCTION__) << "*BUG* Input manager not set up" << endl;
        exit(0);
    }

    return manager->_anyInput();
}

bool CInputManager::_anyInput(){
    if (keyboard.keypressed()){
        return true;
    }
	for (map<int, Util::CSmartPtr_MT<CJoystick> >::iterator it = joysticks.begin(); it != joysticks.end(); it++){
        Util::CSmartPtr_MT<CJoystick> joystick = it->second;
        if (joystick != NULL){
           //   return joystick->pressed();  //Não usa mais a struct Joystick Input aqui
			JoystickInput all_joystick = joystick->readAll();
			if (all_joystick.pressed()){
            return true;
        }
        }
    }

    return false;
}

void CInputManager::waitForClear(){
    manager->keyboard.clear();
	if (manager->mouse.raw()) manager->mouse->clear();
    while (anyInput()){
       poolEvents();

        Util::rest(1);
    }
}


// Old manter por compatibilidade com versões anteriores
void CInputManager::waitForKeys(CKeyboard::Key key1, CKeyboard::Key key2){
    CInputMap<int> wait;
    wait.set(key1, 0, false, 1);
    wait.set(key2, 0, false, 1);
    CInputManager::waitForRelease(wait, 1);
    CInputManager::waitForPress(wait, 1);
    CInputManager::waitForRelease(wait, 1);
}
// Old manter por compatibilidade com versões anteriores
void CInputManager::waitForKeys(CKeyboard::Key key){
    CInputMap<int> wait;
    wait.set(key, 0, false, 1);
    CInputManager::waitForRelease(wait, 1);
    CInputManager::waitForPress(wait, 1);
    CInputManager::waitForRelease(wait, 1);
}
//new
void CInputManager::waitForKeys(CKeyboard::Key key1, CKeyboard::Key key2,const CInputSource & source){
    CInputMap<int> wait;
    wait.set(key1, 0, false, 1);
    wait.set(key2, 0, false, 1);
    CInputManager::waitForRelease(wait, source,1);
    CInputManager::waitForPress(wait,source, 1);
    CInputManager::waitForRelease(wait,source, 1);
}

void CInputManager::waitForKeys(CKeyboard::Key key, const CInputSource & source){
    CInputMap<int> wait;
    wait.set(key, 0, false, 1);
    CInputManager::waitForRelease(wait, source,1);
    CInputManager::waitForPress(wait,source, 1);
    CInputManager::waitForRelease(wait,source, 1);
}



/* these mappings should agree with configuration.cpp:defaultJoystick1Keys,
 * but otherwise they are completely arbitrary
 */
/*
static CInput::GameKeys convertJoystickKey(const CJoystick::Key key, const int facing){
    switch (key){
        case CJoystick::Up : return CInput::Up;
        case CJoystick::Down : return CInput::Down;
        case CJoystick::Left : {
            if (facing == CObject::FACING_RIGHT){
                return CInput::Back;
            } else {
                return CInput::Forward;
            }
        }
        case CJoystick::Right : {
            if (facing == CObject::FACING_RIGHT){
                return CInput::Forward;
            } else {
                return CInput::Back;
            }
        }
        case CJoystick::Button1 : return CInput::Button1;
        case CJoystick::Button2 : return CInput::Button2;
        case CJoystick::Button3 : return CInput::Button3;
        case CJoystick::Button4 : return CInput::Button4;
        default : return CInput::Unknown;
    }
}
//! convete as teclas do joystick para a configuração//mapeamento que foi feito na configuração =>  (Joystick//Input)
static vector<CInput::GameKeys> convertJoystick(CConfiguration & configuration, JoystickInput input, const int facing){
    vector<CInput::GameKeys> all;

	//Se a tecla física up foi detectada (pressionada) coloca no vetor o Valor CInput equivalente
	if (input.j_axis_1_up){
        all.push_back(convertJoystickKey(CConfiguration::intToJoystick(configuration.getJoyKey("joy-key-up")), facing));
    }

    if (input.j_axis_0_right){
        all.push_back(convertJoystickKey(configuration.getJoystickRight(), facing));
    }

    if (input.j_axis_0_left){
        all.push_back(convertJoystickKey(configuration.getJoystickLeft(), facing));
    }

    if (input.j_axis_1_down){
        all.push_back(convertJoystickKey(configuration.getJoystickDown(), facing));
    }

    if (input.jbutton1){
        all.push_back(convertJoystickKey(configuration.getJoystickButtonA(), facing));
    }

    if (input.jbutton2){
        all.push_back(convertJoystickKey(configuration.getJoystickButtonB(), facing));
    }

    if (input.jbutton3){
        all.push_back(convertJoystickKey(configuration.getJoystickButtonC(), facing));
    }

    if (input.jbutton4){
        all.push_back(convertJoystickKey(configuration.getJoystickButtonX(), facing));
    }

    return all;
}
*/


int CInputManager::readKey(){
    return manager->_readKey();
}
int CInputManager::readMouseKey(){
    return manager->_readMouseKey();
}
int CInputManager::readJoyKey(){
    return manager->_readJoyKey();
}
int CInputManager::_readKey(){
    return CKeyboard::readKey();
}
int CInputManager::_readMouseKey(){
	return CMouse::readMouseKey();
}
int CInputManager::_readJoyKey(){
	return CJoystick::readJoyKey();
}

void CInputManager::poolEvents(){

	if (manager == 0){
        Debug::debug(Debug::input,__FUNCTION__) << "*BUG* "<<"CInputManager::poll " <<"Input manager not set up" << endl;
        //The problem is who will delete the manager?
		// SDLManager shuld delete it
		//manager=CInputManager::GetInstance();
		exit(0);
    }

    /*
        Handle mouse button held down continuously
    */
    //HandleMouseRepeating();
   return manager->_poll();
	


}

void CInputManager::_poll(){
    Debug::debug(Debug::input,__FUNCTION__) << "BEGIN // CInputManager::_poll // " << endl;
#ifdef PS3
    checkJoysticks();
#endif
	/** Cria um objeto da classe CEventManager. Este objeto irá cuidar de toda entrada de eventos,
	* gerencoamento do teclado, mouse e joystick
	*/

    /*
    if (bufferKeys){
        eventManager.enableKeyBuffer();
    }
    */
	eventManager.run(keyboard, joysticks,mouse,textInput);

	Debug::debug(Debug::input,__FUNCTION__) << "END // CInputManager::_poll // " << endl;

}



void CInputManager::HandleKeySingle(SDL_KeyboardEvent key) {
  switch(key.keysym.sym) {

  }
}


CInputManager* CInputManager::GetInstance()
{
   Util::Thread::ScopedLock scoped(inputLock);
	if (!manager)
			  manager = new CInputManager();
          return manager;
}

} //end SGF