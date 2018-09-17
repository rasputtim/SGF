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
#include <string.h>
#include <sstream>
#include <string>

#include "input/SGF_TextInput.h"
#include "input/SGF_InputManager.h"
//#include "utf8.h"
#include "util/SGF_Utf.h"
using namespace std;
namespace SGF {

	//TODO: change this to enum
static const int Shift = 198;
static const int Control = 199;
static const int Backspace = 200;
static const int Enter = 201;

CTextInput::CTextInput(const string & start):
CInputMap<unsigned char>(),
blockingKeys(false),
enabled(false),
handle(201){
    const int delay = 100;
   
    set(CKeyboard::Key_BACKSPACE, delay, false, Backspace);
	//Todo other edit keys, like diretional keys....
	text.str(start);
    text.rdbuf()->pubseekoff(0, ios_base::end, ios_base::out);
    text.clear();
}

int CTextInput::nextHandle(){
    int i = handle;
    handle += 1;
    return i;
}

void CTextInput::addBlockingHandle(CKeyboard::Key key, callbackVoid_t function, void * data, bool replaceKey){
    int handle = nextHandle();
    set(key, 1, true, handle);
    callbacks[handle] = CallbackVoid(function, data);
/*
	if (replaceKey) {
		//find old key
		std::multimap<int, Callback>::iterator it = callbacks.find(key);
		//delete all elements with the old keys
		if (it!=callbacks.end()) callbacks.erase(it);
	}else
	callbacks.insert(pair<int, Callback>(key,Callback(function, data)));
  */  
}

void CTextInput::addBlockingJoystickHandle(CJoystick::Key key, callbackVoid_t function, void * data){
    int handle = nextHandle();
    set(key, 1, true, handle);
	callbacks.insert(pair<int, CallbackVoid>(handle,CallbackVoid(function, data)));
    
}
void CTextInput::addHandle(CKeyboard::Key key, int delay, callbackVoid_t function, void * data, bool replaceKey){
    int handle = nextHandle();
    set(key, delay, false, handle);
	    callbacks[handle] = CallbackVoid(function, data);
/*	if (replaceKey) {
		//find old key
		std::multimap<int, Callback>::iterator it = callbacks.find(key);
		//delete all elements with the old keys
		if (it!=callbacks.end()) callbacks.erase(it);
	}else
		callbacks.insert(pair<int, Callback>(key,Callback(function, data)));
  */  
}

void CTextInput::press(const char text[], Uint32 windowID){
	//char texto[100];
	//convert to utf8 aqui
	//std::copy(text, text + 10,texto);
	//Utf::utf16_to_utf8(Utf:: Latin1_Uni(text));
	//string temp =Utf::utf16_to_utf8(Utf:: Latin1_Uni(text));;
	//TODO: convert from char utf 16 to utf 8 here
	
	string temp = string(text);

	textState[windowID].text = temp;
	textState[windowID].windowID=windowID;
	textState[windowID].editing=false;
	

}

void CTextInput::edit(const char text[],int start, int length, Uint32 windowID){
	string temp;
	temp = text;
	textState[windowID].text = temp;
	textState[windowID].start=start;
	textState[windowID].length=length;
	textState[windowID].windowID=windowID;
	textState[windowID].editing=true;
}

#if 0
/* FIXME: move this to a more general place */
//! deprecated SDL treats UTF
static string encodeUtf8(unsigned long unicode){
    ostringstream out;
    if (unicode < 128){
        out << (unsigned char) unicode;
    } else if (unicode < 2047){
        unsigned char byte1 = 192 + unicode / 64;
        unsigned char byte2 = 128 + unicode % 64;
        out << byte1 << byte2;
    } else if (unicode <= 65535){
        unsigned char byte1 = 224 + unicode / 4096;
        unsigned char byte2 = 128 + (unicode / 64) % 64;
        unsigned char byte3 = 128 + unicode % 64;

        out << byte1 << byte2 << byte3;
    } else if (unicode <= 2097151){
        unsigned char byte1 = 240 + unicode / 262144;
        unsigned char byte2 = 128 + (unicode / 4096) % 64;
        unsigned char byte3 = 128 + (unicode / 64) % 64;
        unsigned char byte4 = 128 + (unicode % 64);

        out << byte1 << byte2 << byte3 << byte4;
    } else if (unicode <= 67108863){
        unsigned char byte1 = 248 + (unicode / 16777216);
        unsigned char byte2 = 128 + ((unicode / 262144) % 64);
        unsigned char byte3 = 128 + ((unicode / 4096) % 64);
        unsigned char byte4 = 128 + ((unicode / 64) % 64);
        unsigned char byte5 = 128 + (unicode % 64);

        out << byte1 << byte2 << byte3 << byte4 << byte5;
    } else if (unicode <= 2147483647){
        unsigned char byte1 = 252 + (unicode / 1073741824);
        unsigned char byte2 = 128 + ((unicode / 16777216) % 64);
        unsigned char byte3 = 128 + ((unicode / 262144) % 64);
        unsigned char byte4 = 128 + ((unicode / 4096) % 64);
        unsigned char byte5 = 128 + ((unicode / 64) % 64);
        unsigned char byte6 = 128 + (unicode % 64);
    }
    return out.str();
}
#endif

bool CTextInput::doInput(){
    bool modified = false;
	   /* TODO: ensure these codes are consistent across platforms. So far
     * they seem to work in windows xp and linux (ubuntu)
     */
   // const CKeyboard::unicode_t control_u = 21;
   // const CKeyboard::unicode_t control_w = 23;


    if (enabled){
        vector<InputEvent> events = CInputManager::getEvents(*this);
		  /* the order of reading input is arbitrary right now. I'm not
         * sure it matters what order things are done in, but probably
         * a few corner cases exist. When they come up please document them.
         */

        for (vector<InputEvent>::iterator it = events.begin(); it != events.end(); it++){
            InputEvent event = *it;

            if (event.enabled){
               
               if (event.keymodifier == CKeyboard::Mod_LCTRL && event.out == CKeyboard::Key_U){
                    clearInput();
                    modified = true;
				}else  if (event.out == Backspace){
					backspace();
                    modified = true;
                }else if(event.keymodifier == CKeyboard::Mod_LCTRL && event.out == CKeyboard::Key_D){
				deleteLastWord();
				modified=true;
				}else if (callbacks.find(event.out) != callbacks.end()){
				   // Garantir que os eventos de CReadLine serão executados primeiro
					CallbackVoid & callback = callbacks[event.out];
                    callback.function(callback.data);
				
					/*	std::multimap<int, Callback>::iterator it = callbacks.find(event.out);
					for (it=callbacks.begin();it!=callbacks.end();it++) {
						Callback & callback = (*it).second;
						callback.function(callback.data);
					}*/
                    
				}else if (event.keymodifier == CKeyboard::Mod_LCTRL && event.out == CKeyboard::Key_ALT){ //Todo Detect ctrl + U
                    deleteLastWord();
                    modified = true;
                } /*else if (event.unicode >= 32 && event.unicode < 0xffffff){
                    // FIXME: whats the maximum unicode value?

                    // this->text << (unsigned char) event.unicode;
                    this->text << Utf::encodeUtf8(textState[1].text);
                    modified = true;
                }   */
				//TODO: Choose the active window
				else { 
					int activeWindow=1;
					Uint16 * buffer =SGF::Utf::UTF8_Uni(textState[activeWindow].text.c_str());
				if (buffer[0] >= 32 && buffer[0] <=0xff) {
					
					this->text << textState[activeWindow].text;
				}
				}
            }
        }
			int activeWindow=1;
				Uint16 * buffer =SGF::Utf::UTF8_Uni(textState[activeWindow].text.c_str());
				if (buffer[0] >= 32 && buffer[0] <=0xff) {
					
					this->text << textState[activeWindow].text;
					textState[activeWindow].text.clear();
				}
    }

    return modified;
}

void CTextInput::enable(){
	SDL_StartTextInput();
	CInputManager::captureTextInput(*this);
    enabled = true;
}

void CTextInput::disable(){
	SDL_StopTextInput();
    CInputManager::releaseTextInput(*this);
    enabled = false;
}

string CTextInput::getText() const{
    return text.str();
}

/*
void CTextInput::clear(){
    text.str("");
    text.clear();
}
*/

void CTextInput::setText(const string & text){
    this->text.str(text);
    this->text.rdbuf()->pubseekoff(0, ios_base::end, ios_base::out);
    this->text.clear();
}

void CTextInput::clearInput(){
  setText(string());
}

void CTextInput::backspace(){

    string now = text.str();
	if (now.size() >0){
    now = now.substr(0, now.size()-1);
    setText(now);
	}
}


void CTextInput::deleteLastWord(){
    string now = text.str();
    // Debug::debug(1,__FUNCTION__) << "Delete last word '" << now << "'" << endl;

    if (now.size() > 0){
        if (now.at(now.size() - 1) != ' '){
            int here = now.size() - 1;
            while (here > 0 && now.at(here) != ' '){
                here -= 1;
            }
            if (now.at(here) == ' '){
                here += 1;
            }
            now.erase(here);
        } else {
            int here = now.size() - 1;
            while (here > 0 && now.at(here) == ' '){
                here -= 1;
            }
            if (here > 0){
                while (here > 0 && now.at(here) != ' '){
                    here -= 1;
                }
                if (now.at(here) == ' '){
                    here += 1;
                }
            }
            now.erase(here);
        }
        setText(now);
    }

    /*
    size_t get = now.rfind(" ");
    if (get != string::npos){
        Debug::debug(1,__FUNCTION__) << "get " << get << " size " << now.size() << endl;
        if (get == now.size() - 1){
            get = now.find_last_not_of(' ');
            get = now.rfind(' ', get);
            if (get != string::npos){
                get = 0;
            }
            now.erase(get + 1);
        } else {
            now = now.substr(0, get + 1);
        }
        text.str(now);
        text.rdbuf()->pubseekoff(0, ios_base::end, ios_base::out);
        text.clear();
    } else {
        clearInput();
    }
    */
}

CTextInput::~CTextInput(){
    disable();
}

} //end SGF