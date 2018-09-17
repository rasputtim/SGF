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
#ifndef _S_G_F_input_manager
#define _S_G_F_input_manager

//#include <queue>
#include <vector>
#include <stdlib.h>
#include "../SGF_Config.h"
#include "SGF_Input.h"
#include "SGF_Events.h"
#include "SGF_Mouse.h"
#include "SGF_Joystick.h"
#include "SGF_InputMap.h"
#include "SGF_TextInput.h"
#include "SGF_InputSource.h"
#include "../configuration/SGF_Configuration.h"
#include "../util/SGF_Debug.h"
namespace SGF{

class CConfiguration;
class CJoystick;
class CMouse;
class CGame;
class CTextInput;


/**
 * \class CInputHandler
 *
 * \ingroup SGF_Input
 *
 * \brief Gerenciador de Entrada para o Jogo
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
template <class Output>
class  SGE_API CInputHandler{
public:
    CInputHandler(){
    }

    virtual ~CInputHandler(){

    }

    virtual void press(const Output & out, CKeyboard::unicode_t unicode) = 0;
    virtual void release(const Output & out, CKeyboard::unicode_t unicode) = 0;
};


//typedef int ( *EventFunction)();
/* handles keyboard/joystick/mouse whatever input during the game */
class  SGE_API CInputManager :public CInput{
public:
    static CInputManager* GetInstance();

	
	/* main has one instance of this and thats it.
     * should the janitor have the reference instead?
     */
    friend int main(int, char **);
    /* returns true if any input device is activated (keys pressed, joystick button */
    static bool anyInput();

    bool bError;

    //CMusic *pMusic; //musica para testar a classe Cmusic

	void HandleEventInput();

	void HandleKeySingle(SDL_KeyboardEvent key);
	/** - Overloaded - Keyboard key has been released.
		@param iKeyEnum The key number.
	**/
	virtual void HandleKeySingleKeyup(const int& iKeyEnum) {}
//	void RegisterCallBack(Uint8 tipo_de_evento, EventFunction function);


	static vector<CInput::GameKeys> getInput(const CConfiguration & configuration, const int facing);
    static void poolEvents();

/*
    static void enableBufferInput();
    static void disableBufferInput();
    */

	//static int enableMouse();
	//static int enableJoystick();
	static void waitForKeys(CKeyboard::Key key1, CKeyboard::Key key2);
	static void waitForKeys(CKeyboard::Key key1);
    static void waitForKeys(CKeyboard::Key key1, CKeyboard::Key key2,const CInputSource &);
	static void waitForKeys(CKeyboard::Key key1,const CInputSource &);
    //! wait for a key to be pressed and retur it.
	//! this is a blocking method
	static int readKey();
	static int readMouseKey();
	static int readJoyKey();
    static void waitForClear();
	static void deferResizeEvents(bool defer);


	static vector<CKeyboard::unicode_t> readText(){
        return manager->keyboard.readText();
    }

    template <typename X>
    static vector<CKeyboard::unicode_t> readText(CInputMap<X> & input, typename CInputMap<X>::Output & output){
        return manager->_readText(input, output);
    }

#if 0
    template <typename X>
    static typename CInputMap<X>::Output getMap(CInputMap<X> & input){
        if (manager){
            return manager->_getMap(input);
        }
        /* just crash hard.. who cares */
        *(char *)0 = 0;
        /* make the compiler happy about returning something */
        return *(typename CInputMap<X>::Output*)1;
    }
	// OLD KEEP FOR COMPATIBILITY
#endif
	template <typename X>
    static typename std::vector<typename CInputMap<X>::InputEvent> getEvents(CInputMap<X> & input){
        return manager->_getEvents(input);

    }
	// NEW
	template <typename X>
    static typename std::vector<typename CInputMap<X>::InputEvent> getEvents(CInputMap<X> & input, const CInputSource & source){
        return manager->_getEvents(input, source);
    }
	
	 template <typename X>
    static void handleEvents(CInputMap<X> & input, CInputHandler<X> & handler){
        typename std::vector<typename CInputMap<X>::InputEvent> events = getEvents(input);
        for (typename vector<typename CInputMap<X>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
            const typename CInputMap<X>::InputEvent & event = *it;
            if (event.enabled){
                handler.press(event.out, event.unicode);
            } else {
                handler.release(event.out, event.unicode);
            }
        }
    }
	//old keep for compatibility
    template <typename X>
    static bool pressed(CInputMap<X> & input, X out){
        if (manager){
            return manager->_pressed(input, out);
        }
        return false;
    }
	//new
	template <typename X>
    static bool pressed(CInputMap<X> & input, const CInputSource & source, X out){
        if (manager){
            return manager->_pressed(input, source, out);
        }
        return false;
    }
    /* wait for a key to be released
     * really this waits for all inputs that would result in `out'
     * being generated to stop.
     */
	// old keep for compatibility
    template <typename X>
    static void waitForRelease(CInputMap<X> & input, X out){
        while (CInputManager::pressed(input, out)){
			Util::rest(1);
            CInputManager::poolEvents();
        }
    }
	//new
	template <typename X>
    static void waitForRelease(CInputMap<X> & input, const CInputSource & source, X out){
        while (CInputManager::pressed(input, source, out)){
            Util::rest(1);
            CInputManager::poolEvents();
        }
    }
	//old keep for compatibility iussues
    template <typename X>
    static void waitForPress(CInputMap<X> & input, X out){
        while (!CInputManager::pressed(input, out)){
            Util::rest(1);
            CInputManager::poolEvents();
        }
    }
	template <typename X>
	 static void waitForPress(CInputMap<X> & input, const CInputSource & source, X out){
        while (!CInputManager::pressed(input, source, out)){
            Util::rest(1);
           CInputManager::poolEvents();
        }
    }
 /*
	 template <typename X>
    static void captureInput(CInputMap<X>& input){
		if (!manager) manager = CInputManager::GetInstance();
		manager->_captureInput(input);
    }

    template <typename X>
    static void releaseInput(CInputMap<X> & input){
		if (!manager) manager = CInputManager::GetInstance();
        manager->_releaseInput(input);
    }
	*/
    static void captureTextInput(CTextInput & input){
		if (!manager) manager = CInputManager::GetInstance();
		manager->_captureTextInput(input);
    }

    
    static void releaseTextInput(CTextInput & input){
		if (!manager) manager = CInputManager::GetInstance();
        manager->_releaseTextInput(input);
    }
  virtual ~CInputManager();
protected:
	CInputManager();
    virtual bool _anyInput();
    virtual int _readKey();
	virtual int _readMouseKey();
	virtual int _readJoyKey();
   // virtual vector<CInput::GameKeys> _getInput(const CConfiguration & configuration, const int facing);
/*
    template <typename X>
    void _captureInput(CInputMap<X> & input){

		capture = (void *)input;
    }
	
	template <typename X>
    void _releaseInput(CInputMap<X> & input){
        if (capture == (void*) &input){
            capture = 0;
        }

    }
	*/
	
    void _captureTextInput(CTextInput & input){
		//Util::CSmartPtr_MT<CTextInput> input=&input;
		textInput = Util::CSmartPtr_MT<CTextInput>(&input);
    }

    
	void _releaseTextInput(CTextInput & input){
		if  (textInput==&input) {
			textInput.clear();
		}
    }

   template <typename X>
    vector<CKeyboard::unicode_t> _readText(CInputMap<X> & input, typename CInputMap<X>::Output & output){
        vector<CKeyboard::unicode_t> text;
        vector<CKeyboard::Event> all = keyboard.readData();
        for (vector<CKeyboard::Event>::iterator it = all.begin(); it != all.end(); it++){
            const CKeyboard::Event & data = *it;
			Util::CReferenceCount<KeyState<X> >state = input.getState2(data.key,output);
            if (state != NULL){
                text.push_back(data.unicode);
            }

        }

        return text;
    }

    void removeDuplicates(vector<CKeyboard::Key> & storage){
        vector<CKeyboard::Key> output;
        int last = -1;
        for (vector<CKeyboard::Key>::iterator it = storage.begin(); it != storage.end(); it++){
            if (*it != last){
                output.push_back(*it);
                last = *it;
            }
        }
        storage = output;
    }
	//! preenche o vetor eventos com os eventos armazenados nas classes (Joystick, mouse e keyboard)
    //OLD  KEEP FOR COMPATIBILITY
	template <typename X>
    typename std::vector<typename CInputMap<X>::InputEvent> _getEvents(CInputMap<X> & input){
		std::vector<typename CInputMap<X>::InputEvent> events;
        if (capture != NULL && capture != &input){
            return events;
        }
		Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  Get Keyboard Events" << endl;
        const vector<typename CKeyboard::Event> & buffer = keyboard.getBufferedKeys();
		Debug::debug(Debug::input,__FUNCTION__) << "Got Keyboard Events: "<< buffer.size() << endl;
        for (vector<CKeyboard::Event>::const_iterator it = buffer.begin(); it != buffer.end(); it++){
            const CKeyboard::Event & data = *it;
			std::vector<Util::CReferenceCount<KeyState<X> > > statesVector;
			
			// 
			input.getStatesVector(data.key,statesVector);
			for(typename std::vector<Util::CReferenceCount<KeyState<X> > >::iterator statesIterator=statesVector.begin();statesIterator!=statesVector.end();statesIterator++) {
			Util::CReferenceCount<KeyState<X> > state =(*statesIterator);  
				if (state != NULL){
					events.push_back(typename CInputMap<X>::InputEvent(state->out, data.Mod,data.unicode, data.enabled));
				}
			}
        }


        if (joystick.raw()!=NULL){
			Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  Get Joystick Events" << endl;
            const vector<typename CJoystick::Event> & joystickEvents = joystick->getEvents();
           Debug::debug(Debug::input,__FUNCTION__) << "Got Joystick Events: "<< joystickEvents.size() << endl;
			for (vector<CJoystick::Event>::const_iterator it = joystickEvents.begin(); it != joystickEvents.end(); it++){
                CJoystick::Event event = *it;
                Util::CReferenceCount<JoystickState<X> > state = input.getJoystickState(event.key);
                if (state != NULL){
                    events.push_back(typename CInputMap<X>::InputEvent(state->out, event.enabled));
                }
            }
        }


		if (mouse.raw()!=NULL){
			Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  Get Mouse Events" << endl;
			const vector<typename CMouse::Event> & mousebuffer = mouse->getBufferedMouseKeys();
			Debug::debug(Debug::input,__FUNCTION__) << "Got Mouse Events: "<< mousebuffer.size() << endl;
			if (mousebuffer.size() > 0) {
			for (vector<CMouse::Event>::const_iterator it = mousebuffer.begin(); it != mousebuffer.end(); it++){
					const CMouse::Event & data = *it;
					Util::CReferenceCount<MouseState<X> > state = input.getMouseState(data.Mousekey);
					//! get x,y mouse position;
					//state->x= data.y;
					//state->y= data.y;
					if (state != NULL){
					events.push_back(typename CInputMap<X>::InputEvent(state->out, data.enabled,data.x,data.y));
					}
			 }
			}
			const vector<typename CMouse::MouseMoveDatatype> & mouseAbsolutePositionbuffer = mouse->getBufferedMouseAbsolutePositions();
			Debug::debug(Debug::input,__FUNCTION__) << "Got Mouse Absolute Move Events: "<< mouseAbsolutePositionbuffer.size() << endl;

			if (mouseAbsolutePositionbuffer.size() > 0) {
				for (vector<CMouse::MouseMoveDatatype>::const_iterator it = mouseAbsolutePositionbuffer.begin(); it != mouseAbsolutePositionbuffer.end(); it++){
				//	const CMouse::MouseMoveDatatype & data = *it;
				//	MouseState<X> * state = input.getMouseMovementState();
				//	if (state != NULL){
				//	events.push_back(typename CInputMap<X>::InputEvent(state->out,-1, data.enabled));
				//	}
			 }
			}
			const vector<typename CMouse::MouseMoveDatatype> & mouseRelativePositionbuffer = mouse->getBufferedMouseRelativePositions();
			Debug::debug(Debug::input,__FUNCTION__) << "Got Mouse Relative Move Events: "<< mousebuffer.size() << endl;
			if (mouseRelativePositionbuffer.size() > 0){
			for (vector<CMouse::MouseMoveDatatype>::const_iterator it = mouseRelativePositionbuffer.begin(); it != mouseRelativePositionbuffer.end(); it++){
				//	const CMouse::MouseMoveDatatype & data = *it;
				//	MouseState<X> * state = input.getMouseState(data.Mousekey);
				//	if (state != NULL){
				//	events.push_back(typename CInputMap<X>::InputEvent(state->out,-1, data.enabled));
				//	}
			 }
			}
		}
		Debug::debug(Debug::input,__FUNCTION__) << "END" << endl;
        return events;
    }

	//new======
	    //OLD  KEEP FOR COMPATIBILITY
	template <typename X>
    typename std::vector<typename CInputMap<X>::InputEvent> _getEvents(CInputMap<X> & input, const CInputSource & source){
		vector<typename CInputMap<X>::InputEvent> events;
        if (capture != NULL && capture != &input){
            return events;
        }
		if (source.useKeyboard()){
			Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  Get Keyboard Events" << endl;
			const std::vector<typename CKeyboard::Event> & buffer = keyboard.getBufferedKeys();
			Debug::debug(Debug::input,__FUNCTION__) << "Got Keyboard Events: "<< buffer.size() << endl;
			for (vector<CKeyboard::Event>::const_iterator it = buffer.begin(); it != buffer.end(); it++){
				const CKeyboard::Event & data = *it;
				std::vector<Util::CReferenceCount<KeyState<X> > > statesVector;
			
			input.getStatesVector(data.key,statesVector);
			for(typename std::vector<Util::CReferenceCount<KeyState<X> > >::iterator statesIterator=statesVector.begin();statesIterator!=statesVector.end();statesIterator++) {
			Util::CReferenceCount<KeyState<X> > state =(*statesIterator);  
				if (state != NULL ){
					events.push_back(typename CInputMap<X>::InputEvent(state->out, data.Mod,data.unicode, data.enabled));
				}
			}
			}
		}
        if (source.getJoystick() >= 0 && (unsigned) source.getJoystick() < joysticks.size()){

			if (joystick.raw()!=NULL){
				Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  Get Joystick Events" << endl;
				const vector<typename CJoystick::Event> & joystickEvents = joystick->getEvents();
			   Debug::debug(Debug::input,__FUNCTION__) << "Got Joystick Events: "<< joystickEvents.size() << endl;
				for (vector<CJoystick::Event>::const_iterator it = joystickEvents.begin(); it != joystickEvents.end(); it++){
					CJoystick::Event event = *it;
					Util::CReferenceCount<JoystickState<X> > state = input.getJoystickState(event.key);
					if (state != NULL){
						events.push_back(typename CInputMap<X>::InputEvent(state->out, event.enabled));
					}
				}
			}
		}
		if (source.useMouse()){	
			if (mouse.raw()!=NULL){
				Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  Get Mouse Events" << endl;
				const vector<typename CMouse::Event> & mousebuffer = mouse->getBufferedMouseKeys();
				Debug::debug(Debug::input,__FUNCTION__) << "Got Mouse Events: "<< mousebuffer.size() << endl;
				if (mousebuffer.size() > 0) {
				for (vector<CMouse::Event>::const_iterator it = mousebuffer.begin(); it != mousebuffer.end(); it++){
						const CMouse::Event & data = *it;
						Util::CReferenceCount<MouseState<X> > state = input.getMouseState(data.Mousekey);
						//! get x,y mouse position;
						//state->x= data.y;
						//state->y= data.y;
						if (state != NULL){
						events.push_back(typename CInputMap<X>::InputEvent(state->out, data.enabled,data.x,data.y));
						}
				 }
				}
				const vector<typename CMouse::MouseMoveDatatype> & mouseAbsolutePositionbuffer = mouse->getBufferedMouseAbsolutePositions();
				Debug::debug(Debug::input,__FUNCTION__) << "Got Mouse Absolute Move Events: "<< mouseAbsolutePositionbuffer.size() << endl;

				if (mouseAbsolutePositionbuffer.size() > 0) {
					for (vector<CMouse::MouseMoveDatatype>::const_iterator it = mouseAbsolutePositionbuffer.begin(); it != mouseAbsolutePositionbuffer.end(); it++){
					//	const CMouse::MouseMoveDatatype & data = *it;
					//	Util::CReferenceCount<MouseState<X> >state = input.getMouseMovementState();
					//	if (state != NULL){
					//	events.push_back(typename CInputMap<X>::InputEvent(state->out,-1, data.enabled));
					//	}
				 }
				}
				const vector<typename CMouse::MouseMoveDatatype> & mouseRelativePositionbuffer = mouse->getBufferedMouseRelativePositions();
				Debug::debug(Debug::input,__FUNCTION__) << "Got Mouse Relative Move Events: "<< mousebuffer.size() << endl;
				if (mouseRelativePositionbuffer.size() > 0){
				for (vector<CMouse::MouseMoveDatatype>::const_iterator it = mouseRelativePositionbuffer.begin(); it != mouseRelativePositionbuffer.end(); it++){
					//	const CMouse::MouseMoveDatatype & data = *it;
					//	Util::CReferenceCount<MouseState<X> > state = input.getMouseState(data.Mousekey);
					//	if (state != NULL){
					//	events.push_back(typename CInputMap<X>::InputEvent(state->out,-1, data.enabled));
					//	}
				 }
				}
			}
		}
		Debug::debug(Debug::input,__FUNCTION__) << "END" << endl;
        return events;
    }

	//=============
    template <typename X>
    typename CInputMap<X>::Output _getMap(CInputMap<X> & input){
        typename CInputMap<X>::Output output;

        if (capture != 0 && capture != &input){
            return output;
        }

        vector<CKeyboard::Key> all_keys;
        Debug::debug(Debug::input,__FUNCTION__) << "Template // _getinput  // Will readKeys" << endl;
		keyboard.readKeys(all_keys);
        Debug::debug(Debug::input,__FUNCTION__) << "Template // _getinput  // Put keys to output Vector" << endl;
        input.read(all_keys, &output);
		if (mouse.raw()){
		vector<CMouse::Key> all_keys;
        Debug::debug(Debug::input,__FUNCTION__) << "Template // _getinput  // Will read Mouse Keys" << endl;
		mouse->readMouseKeys(all_keys);
		Debug::debug(Debug::input,__FUNCTION__) << "Template // _getinput  // Put keys to output Vector" << endl;
        input.read(all_keys, &output);
		}
        if (joystick.raw() != NULL){
            JoystickInput all_joystick = joystick->readAll();
            input.read(all_joystick, &output);
        }

        /* just bumps an internal counter */
        input.update();

        return output;
    }
	//old keep compatibility
    template <typename X>
    bool _pressed(CInputMap<X> & input, X result){

        if (capture != 0 && capture != &input){
            return false;
        }

		vector<CKeyboard::Key> all_keys;
        keyboard.readKeys(all_keys);
        bool out = false;

        out = input.pressed(all_keys, result);
		if (mouse.raw()) {
		vector<CMouse::Key> all_mouse_keys;
        mouse->readMouseKeys(all_mouse_keys);
        out |= input.pressed(all_mouse_keys, result);

		}
        if (joystick.raw() != NULL){
            JoystickInput all_joystick = joystick->readAll();
            out |= input.pressed(all_joystick, result);
        }

        return out;
    }
//new
template <typename X>
    bool _pressed(CInputMap<X> & input, const CInputSource & source, X result){
        /* FIXME: use the input source, luke */
		//in this case the input is captured to another manager
        if (capture != 0 && capture != &input){
            return false;
        }
        vector<CKeyboard::Key> all_keys;
        keyboard.readKeys(all_keys);
        // all_keys.insert(all_keys.end(), bufferedKeys.begin(), bufferedKeys.end());
        std::sort(all_keys.begin(), all_keys.end());
        removeDuplicates(all_keys);
        // bufferedKeys.clear();
        bool out = false;

        out = input.pressed(all_keys, result);
		if (mouse.raw()) {
		vector<CMouse::Key> all_mouse_keys;
        mouse->readMouseKeys(all_mouse_keys);
        out |= input.pressed(all_mouse_keys, result);

		}
         if (joystick.raw() != NULL){
            JoystickInput all_joystick = joystick->readAll();
            out |= input.pressed(all_joystick, result);
        }
		 if (textInput.raw() != NULL) {

			 //???? to do what with text input?
		 }
        return out;
    }
    virtual void _poll();


	SDL_Event event;

private:
	static Util::Thread::LockObject inputLock;
	static CInputManager * manager;
	Util::CSmartPtr_MT<CTextInput> textInput;
    void * capture;
	map<int, Util::CSmartPtr_MT<CJoystick> > joysticks;
	Util::CSmartPtr_MT<CJoystick> joystick;
    Util::CSmartPtr_MT<CMouse> mouse;
	//! para cuidar da ebtrada de texto unicode/UTF
	//Input::CEventManager eventManager;
	CKeyboard keyboard;

};

 }//end SGF
#endif
