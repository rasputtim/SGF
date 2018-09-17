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
#ifndef _SGF_input_map_h
#define _SGF_input_map_h

//#include <queue>
#include <map>
#include <vector>
#include <iostream>
#include "SGF_Keyboard.h"
#include "SGF_Joystick.h"
#include "SGF_Mouse.h"
#include "../util/SGF_Pointer.h"

using namespace std;
namespace SGF{


//inicio do template 1 - Keystate
template <typename X>
struct KeyState{
    KeyState(unsigned int delay, bool block, X out, unsigned int last_read):
        delay(delay),
        block(block),
        out(out),
        pressed(false),
        last_read(last_read),
        seen(0){
    }
	KeyState(const KeyState &copy):
        delay(copy.delay),
        block(copy.block),
        out(copy.out),
		pressed(copy.pressed),
        last_read(copy.last_read),
		seen(copy.seen){
    }
    unsigned int delay;
    bool block;
    X out;
    bool pressed;
    unsigned int last_read;
    unsigned int seen;
};  //fim do template 1
//================================END Template 1
/* cant typedef a template'd struct so we have to copy/paste the definition
 */
template <typename X>
struct JoystickState{
    JoystickState(unsigned int delay, bool block, X out, unsigned int last_read):
        delay(delay),
        block(block),
        out(out),
        pressed(false),
        last_read(last_read),
        seen(0){
    }

    unsigned int delay;
    bool block;
    X out;
    bool pressed;
    unsigned int last_read;
    unsigned int seen;
};
//================================END Template 2
template <typename X>
struct MouseState{
    MouseState(unsigned int delay, bool block, X out, unsigned int last_read):
        delay(delay),
        block(block),
        out(out),
        pressed(false),
        last_read(last_read),
		seen(0),
		x(0),  //to future
		y(0)  //to future
        {
    }

    unsigned int delay;
    bool block;
    X out;
    bool pressed;
    unsigned int last_read;
    unsigned int seen;
	int x;
	int y;
};
//================================END Template 3

/**
 * \class CInputMap
 *
 * \ingroup SGF_Input
 *
 * \brief Gerenciador de Entrada para o Jogo. 
 * CInputMap mantem um registro dos eventos de entrada.
 * cada evento de dispositivo de entrada, como uma tecla, ou tecla do mouse, 
 * ou movimento do joystick relaciona se com um evento do jogo 
 * definidos pelo usuário e configurado através do método set.
 * Então a Classe cria um mapa que relaciona os eventos dos dispositivos de entrada com eventos do jogo
 * Permite que configure mais de jogo para uma determinado evento de entrada
 *
 * Mapeia um dispositivo de entrada (keyboard, joystick, etc.) para
 * tipos de dados definidos pelo usuário
 *
 * \note o parâmetro X do template é o tipo de dados definido pelo usuário
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
template <typename X>
class  SGE_API CInputMap{
public:
    typedef map<X,bool> Output;

    struct InputEvent{
        InputEvent(const X & out, CKeyboard::Mod keymodifier, CKeyboard::unicode_t unicode, bool enabled):
        out(out),
        unicode(unicode),
		keymodifier(keymodifier),
        enabled(enabled),
		mouseXpos(0),
		mouseYpos(0){
        }
		InputEvent(const X & out, bool enabled):
        out(out),
        unicode(-1),
		keymodifier(CKeyboard::ModInvalid),
       	enabled(enabled),
       	mouseXpos(0),
		mouseYpos(0)
		{
        }
		InputEvent(const X & out, bool enabled, int x, int y):
        out(out),
        unicode(-1),
		keymodifier(CKeyboard::ModInvalid),
        enabled(enabled),
		mouseXpos(x),
		mouseYpos(y){
        }
        InputEvent(const InputEvent & input):
        out(input.out),
		unicode(input.unicode),
		keymodifier(input.keymodifier),
        enabled(input.enabled),
		mouseXpos(input.mouseXpos),
		mouseYpos(input.mouseYpos){
        }

        InputEvent(){
        }

        bool operator[](const X & is) const {
            return this->out == is;
        }

        X out;
        CKeyboard::unicode_t unicode;
		CKeyboard::Mod keymodifier;
		bool enabled;
		int mouseXpos;
		int mouseYpos;

    };

    CInputMap():
        last_read(0){
    }
	 CInputMap(const CInputMap & copy){
        copyMap(copy);
    }
	CInputMap & operator=(const CInputMap & copy){
        copyMap(copy);
        return *this;
    }

   void copyMap(const CInputMap & copy){
		key_states.clear();
		
		for (typename multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::const_iterator it = copy.key_states.begin(); it != copy.key_states.end(); it++){
				if ((*it).second != NULL){


				key_states.insert(pair<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >((*it).first, Util::CReferenceCount<KeyState<X> >(new KeyState<X>(*(*it).second ))));
				int delay=(*it).second->delay;
				bool bock =(*it).second->block;
				X out=(*it).second->out;
				int last_read = (*it).second->last_read;
				
				}
			
		//	if (it->second != NULL){
		//	key_states[(*it).first] = Util::CReferenceCount<KeyState<X> >(new KeyState<X>(*(*it).second));
		//	}


		}
		joy_states.clear();
        for (typename map<typename CJoystick::Key, Util::CReferenceCount<JoystickState<X> > >::const_iterator it = copy.joy_states.begin(); it != copy.joy_states.end(); it++){
          if (it->second != NULL){
			  joy_states[(*it).first] = Util::CReferenceCount<JoystickState<X> >(new JoystickState<X>(*(*it).second));
			}
		}
		mousekey_states.clear();
        for (typename map<typename CMouse::Key, Util::CReferenceCount<MouseState<X> > >::const_iterator it = copy.mousekey_states.begin(); it != copy.mousekey_states.end(); it++){
           if (it->second != NULL){
			   mousekey_states[(*it).first] = Util::CReferenceCount<MouseState<X> >(new MouseState<X>(*(*it).second));
			}
		}
		last_read = copy.last_read;
    }

 typedef typename multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::iterator multiKeyIterator;
    virtual ~CInputMap(){
      /* map will clear itself, reference count will delete all objects */
      }

    /** key: the keyboard key to recognize, something like KEY_A
     * delay: time before successive keys are recognized (if held down)
     * block: if true then the key must be released before it will
     *   be recognized again. false allows repetition.
     * out: user defined value to set if this key is pressed
     */
    void set(CKeyboard::KeyType key, int delay, bool block, X out){
     bool replaceKey=false;
		//   key_states[key] = Util::CReferenceCount<KeyState<X> >(new KeyState<X>(delay, block, out, last_read));
    	if (replaceKey) {
		//find old keys
		std::pair < multiKeyIterator, multiKeyIterator > ret;
		ret = key_states.equal_range(key);
	 for (typename std::multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::iterator it=ret.first; it!=ret.second; ++it)
	 			//delete all elements with the old keys
				key_states.erase(it);
	}
     //INSERT THE NEW KEY
	
	//key_states.insert(pair<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >(key, Util::CReferenceCount<KeyState<X> >(new KeyState<X>(delay, block, out, last_read))));
	key_states.insert(std::make_pair(key, Util::CReferenceCount<KeyState<X> >(new KeyState<X>(delay, block, out, last_read))));

	
	}

	void set(CKeyboard::KeyType key, X out){
        set(key, 0, false, out);
    }
	//TODO
    /* change an existing key */  
/*    void update(CKeyboard::KeyType key, int delay, bool block, X out){
    multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::const_iterator it=key_states.find(key);
	if(it!=key_states.end()) {
		for(it=key_states.begin();it!=key_states.end();it++){
          Util::CReferenceCount<KeyState<X> > state = (*it2).second;
		  if(state->out== out){

		  }

		}	
	}
	if (key_states[key] != 0){
            key_states[key]->delay = delay;
            key_states[key]->block = block;
            key_states[key]->out = out;
        }
    }
*/
    /* mostly the same stuff but for joysticks.
     */
    void set(typename CJoystick::Key key, int delay, bool block, X out){
        joy_states[key] = Util::CReferenceCount<JoystickState<X> >(new JoystickState<X>(delay, block, out, last_read));
    }

	void set(typename CJoystick::Key key, X out){
        set(key, 0, false, out);
    }
	/* mostly the same stuff but for mouse.
     */
    void set(CMouse::Key key, int delay, bool block, X out){
       mousekey_states[key] = Util::CReferenceCount<MouseState<X> >(new MouseState<X>(delay, block, out, last_read));
    }
	void set(CMouse::Key key, X out){
        set(key, 0, false, out);
    }
    static vector<X> getAllPressed(const Output & output){
        vector<X> out;

        for (typename Output::const_iterator it = output.begin(); it != output.end(); it++){
            if ((*it).second){
                out.push_back((*it).first);
            }
        }

        return out;
    }
	//! to know if a key with thar event was pressed
    bool pressed(const vector<CKeyboard::Key> & keys, X out){
        for (vector<CKeyboard::Key>::const_iterator it = keys.begin(); it != keys.end(); it++){
            CKeyboard::KeyType key = *it;
			if (key_states.find(key) != key_states.end()) {
			
			//find old keys
			std::pair <multiKeyIterator, multiKeyIterator> ret;
			ret = key_states.equal_range(key);
			for (typename std::multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::iterator it=ret.first; it!=ret.second; ++it){
	 			 Util::CReferenceCount<KeyState<X> > state =(*it).second;
						if (state->out == out){
							return true;
						}
			}
			
			}

          //   Util::CReferenceCount<KeyState<X> > state = key_states[key];
          //  if (state != 0){
          //      if (state->out == out){
          //          return true;
          //      }
          //  }
        }
        return false;
    }

   bool pressed(const vector<CMouse::Key> & keys, X out){
        for (vector<CMouse::Key>::const_iterator it = keys.begin(); it != keys.end(); it++){
            CMouse::MouseKeyType key = *it;
            Util::CReferenceCount<MouseState<X> > state = mousekey_states[key];
            if (state != 0){
                if (state->out == out){
                    return true;
                }
            }
        }
        return false;
    }
 
 /*  virtual Util::CReferenceCount<KeyState<X> > getState(CKeyboard::KeyType key){
 	  return key_states[key];
    }
	*/
virtual Util::CReferenceCount<KeyState<X> > getState2(CKeyboard::KeyType key,typename CInputMap<X>::Output & output){
 typename multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::const_iterator it2=key_states.find(key);
					if(it2!=key_states.end()){
					
					//find old keys
					std::pair <multiKeyIterator,multiKeyIterator> ret;
					ret = key_states.equal_range(key);
					for (typename std::multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::iterator it=ret.first; it!=ret.second; ++it) {
	 					Util::CReferenceCount<KeyState<X> > state = (*it2).second;
						if (output[state->out]){
							return state;
						}else return  Util::CReferenceCount<KeyState<X> >();
					}
					}	 
}

virtual void getStatesVector(CKeyboard::KeyType key,vector<Util::CReferenceCount<KeyState<X> > > &statesVector){
 typename multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::const_iterator it=key_states.find(key);
 if (it!=key_states.end()) {
	std::pair <multiKeyIterator , multiKeyIterator> ret;
	ret = key_states.equal_range(key);
	 for (typename std::multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::iterator it=ret.first; it!=ret.second; ++it)
	 
		 statesVector.push_back((*it).second);
	 
 }
}

  
 
    virtual Util::CReferenceCount<JoystickState<X> > getJoystickState(CJoystick::Key key){
        return joy_states[key];
    }
	virtual Util::CReferenceCount<MouseState<X> > getMouseState(CMouse::Key key){
        return mousekey_states[key];
    }

    void read(const vector<CKeyboard::Key> & keys, Output * output){
        for (vector<CKeyboard::Key>::const_iterator it = keys.begin(); it != keys.end(); it++){
            CKeyboard::KeyType key = *it;


			//find old keys
			std::pair <multiKeyIterator, multiKeyIterator> ret;
			ret = key_states.equal_range(key);
	 for (typename std::multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > >::iterator it=ret.first; it!=ret.second; ++it){
  			
				Util::CReferenceCount<KeyState<X> > state = (*it).second;//key_states[key];
				if (state != 0){
                bool use = false;
                Debug::debug(50,__FUNCTION__) << "read " << key << " last read is " << state->last_read << " my last read is " << last_read << endl;
                if (state->block){
                    if (last_read - state->last_read > 1){
                        use = true;
                    }
                } else if (last_read - state->last_read > 1 || state->seen >= state->delay){
                    use = true;
                    state->seen = 0;
                } else {
                    state->seen += 1;
                }

                state->last_read = last_read;

                // state->last_read = last_read;

                (*output)[state->out] = use;
            }

		}//end for
        }
    }
	   void read(const vector<CMouse::Key> & keys, Output * output){
        for (vector<CMouse::Key>::const_iterator it = keys.begin(); it != keys.end(); it++){
            CMouse::MouseKeyType key = *it;
            Util::CReferenceCount<MouseState<X> > state = mousekey_states[key];
            if (state != 0){
                bool use = false;
                Debug::debug(50,__FUNCTION__) << "read " << key << " last read is " << state->last_read << " my last read is " << last_read << endl;
                if (state->block){
                    if (last_read - state->last_read > 1){
                        use = true;
                    }
                } else if (last_read - state->last_read > 1 || state->seen >= state->delay){
                    use = true;
                    state->seen = 0;
                } else {
                    state->seen += 1;
                }

                state->last_read = last_read;


                (*output)[state->out] = use;
            }
        }
    }

	const std::multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > > & getKeyStates() const {
        return key_states;
    }

    /* called by the input manager when the map is read */
    void update(){
        last_read += 1;
    }


//!Le o estado dos botoes do joystick e coloca no Output
//	Digital . não se preocupa com o tempo que as teclas foram pressionadas

void read(const JoystickInput & joystick, Output * output){

#define do_joy(field, key) if (joystick.field){\
    Util::CReferenceCount<JoystickState<X> > state = joy_states[CJoystick::key];\
    doJoyState(state, output);\
}

        do_joy(j_axis_1_down, Down);
        do_joy(j_axis_1_up, Up);
        do_joy(j_axis_0_left, Left);
        do_joy(j_axis_0_right, Right);
        do_joy(jbutton1, Button1);
        do_joy(jbutton2, Button2);
        do_joy(jbutton3, Button3);
        do_joy(jbutton4, Button4);
		do_joy(jbutton5, Button5);
        do_joy(jbutton6, Button6);
        do_joy(jbutton7, Button7);
        do_joy(jbutton8, Button8);
		do_joy(jbutton9, Button9);
        do_joy(jbutton10, Button10);
        do_joy(jbutton11, Button11);
        do_joy(jbutton12, Button12);
	//	do_joy(jquit, Quit);
    /*  o define do_joy(field, key) faz exatamente o que está definido abaixo:
        if (joystick.up){
            JoystickState<X> * state = joy_states[Joystick::Up];
            doJoyState(state);
        }

        if (joystick.down){
            JoystickState<X> * state = joy_states[Joystick::Down];
            doJoyState(state);
        }
        */
#undef do_joy

    }

    bool pressed(const JoystickInput & joystick, X out){
#define do_joy(field, key) if (joystick.field){\
    Util::CReferenceCount<JoystickState<X> > state = joy_states[CJoystick::key];\
    if (state != 0 && state->out == out){\
        return true;\
    }\
}

        do_joy(j_axis_1_down, Down);
        do_joy(j_axis_1_up, Up);
        do_joy(j_axis_0_left, Left);
        do_joy(j_axis_0_right, Right);
        do_joy(jbutton1, Button1);
        do_joy(jbutton2, Button2);
        do_joy(jbutton3, Button3);
        do_joy(jbutton4, Button4);
		do_joy(jbutton5, Button5);
        do_joy(jbutton6, Button6);
        do_joy(jbutton7, Button7);
        do_joy(jbutton8, Button8);
		do_joy(jbutton9, Button9);
        do_joy(jbutton10, Button10);
        do_joy(jbutton11, Button11);
        do_joy(jbutton12, Button12);
//		do_joy(jquit, Quit);


#undef do_joy
        return false;
    }

protected:
    void doJoyState(JoystickState<X> * state, Output * output){
        if (state != 0){
            bool use = false;
            if (state->block){
                if (last_read - state->last_read > 1){
                    use = true;
                }
            } else if (last_read - state->last_read > 1 || state->seen >= state->delay){
                use = true;
                state->seen = 0;
            } else {
                state->seen += 1;
            }

            state->last_read = last_read;

            // state->last_read = last_read;

            (*output)[state->out] = use;
        }
    }

private:
    //map<CKeyboard::KeyType,  Util::CReferenceCount<KeyState<X> > > key_states;
    multimap<CKeyboard::KeyType, Util::CReferenceCount<KeyState<X> > > key_states;
	map<typename CJoystick::Key,  Util::CReferenceCount<JoystickState<X> > > joy_states;
	map<CMouse::Key,  Util::CReferenceCount<MouseState<X> > > mousekey_states;
    unsigned int last_read;
};  //================================END Template 3
} //end SGF
#endif
