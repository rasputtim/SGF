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
#ifndef _S_G_F_keyboard_h
#define _S_G_F_keyboard_h

#include "../../ExternalLibs/SDL2/include/SDL.h"
#include <map>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../SGF_Config.h"
#include "../util/SGF_Util.h"
#include "SGF_StructsInput.h"
#include "../../ExternalLibs/SDL2/include/SDL_keycode.h"

namespace SGF{


/**
 * \class CKeyboard
 *
 * \ingroup SGF_Input
 *
 * \brief Tratamento do Teclado
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CKeyboard {
public:

enum Key{
MIN = -1,
Invalid = MIN,
Key_A = ::SDLK_a,
Key_B = ::SDLK_b,
Key_C = ::SDLK_c,
Key_D = ::SDLK_d,
Key_E = ::SDLK_e,
Key_F = ::SDLK_f,
Key_G = ::SDLK_g,
Key_H = ::SDLK_h,
Key_I = ::SDLK_i,
Key_J = ::SDLK_j,
Key_K = ::SDLK_k,
Key_L = ::SDLK_l,
Key_M = ::SDLK_m,
Key_N = ::SDLK_n,
Key_O = ::SDLK_o,
Key_P = ::SDLK_p,
Key_Q = ::SDLK_q,
Key_R = ::SDLK_r,
Key_S = ::SDLK_s,
Key_T = ::SDLK_t,
Key_U = ::SDLK_u,
Key_V = ::SDLK_v,
Key_W = ::SDLK_w,
Key_X = ::SDLK_x,
Key_Y = ::SDLK_y,
Key_Z = ::SDLK_z,
Key_0 = ::SDLK_0,
Key_1 = ::SDLK_1,
Key_2 = ::SDLK_2,
Key_3 = ::SDLK_3,
Key_4 = ::SDLK_4,
Key_5 = ::SDLK_5,
Key_6 = ::SDLK_6,
Key_7 = ::SDLK_7,
Key_8 = ::SDLK_8,
Key_9 = ::SDLK_9,
Key_0_PAD = ::SDLK_KP_0,
Key_1_PAD = ::SDLK_KP_1,
Key_2_PAD = ::SDLK_KP_2,
Key_3_PAD = ::SDLK_KP_3,
Key_4_PAD = ::SDLK_KP_4,
Key_5_PAD = ::SDLK_KP_5,
Key_6_PAD = ::SDLK_KP_6,
Key_7_PAD = ::SDLK_KP_7,
Key_8_PAD = ::SDLK_KP_8,
Key_9_PAD = ::SDLK_KP_9,
Key_F1 = ::SDLK_F1,
Key_F2 = ::SDLK_F2,
Key_F3 = ::SDLK_F3,
Key_F4 = ::SDLK_F4,
Key_F5 = ::SDLK_F5,
Key_F6 = ::SDLK_F6,
Key_F7 = ::SDLK_F7,
Key_F8 = ::SDLK_F8,
Key_F9 = ::SDLK_F9,
Key_F10 = ::SDLK_F10,
Key_F11 = ::SDLK_F11,
Key_F12 = ::SDLK_F12,
Key_ESC = ::SDLK_ESCAPE,
Key_TILDE = ::SDLK_BACKQUOTE,
Key_MINUS = ::SDLK_MINUS,
Key_EQUALS = ::SDLK_EQUALS,
Key_BACKSPACE = ::SDLK_BACKSPACE,
Key_TAB = ::SDLK_TAB,
Key_OPENBRACE = ::SDLK_LEFTBRACKET,
Key_CLOSEBRACE = ::SDLK_RIGHTBRACKET,
Key_ENTER = ::SDLK_RETURN,
Key_COLON = ::SDLK_COLON,
Key_QUOTE = ::SDLK_QUOTE,
Key_BACKSLASH = ::SDLK_BACKSLASH,
Key_BACKSLASH2 = 999,
Key_COMMA = ::SDLK_COMMA,
Key_STOP = ::SDLK_PERIOD,
Key_SLASH = ::SDLK_SLASH,
Key_SPACE = ::SDLK_SPACE,
Key_INSERT = ::SDLK_INSERT,
Key_DEL = ::SDLK_DELETE,
Key_HOME = ::SDLK_HOME,
Key_END = ::SDLK_END,
Key_PGUP = ::SDLK_PAGEUP,
Key_PGDN = ::SDLK_PAGEDOWN,
Key_LEFT = ::SDLK_LEFT,
Key_RIGHT = ::SDLK_RIGHT,
Key_UP = ::SDLK_UP,
Key_DOWN = ::SDLK_DOWN,
Key_SLASH_PAD = ::SDLK_KP_PERIOD,
Key_ASTERISK = ::SDLK_ASTERISK,
Key_MINUS_PAD = ::SDLK_KP_MINUS,
Key_PLUS_PAD = ::SDLK_KP_PLUS,
Key_DEL_PAD = 1000,
Key_ENTER_PAD = ::SDLK_KP_ENTER,
Key_PRTSCR = ::SDLK_PRINTSCREEN,
Key_PAUSE = ::SDLK_PAUSE,
//Key_ABNT_C1 = ::KEY_ABNT_C1,
Key_YEN = 1002,
Key_KANA = 1003,
Key_CONVERT = 1004,
Key_NOCONVERT = 1005,
Key_AT = ::SDLK_AT,
Key_CIRCUMFLEX = ::SDLK_CARET,
Key_COLON2 = 1006,
Key_KANJI = 1007,
Key_EQUALS_PAD = ::SDLK_KP_EQUALS,
Key_BACKQUOTE = 1008,
Key_SEMICOLON = ::SDLK_SEMICOLON,
Key_COMMAND = 1009,
//Key_UNKNOWN1 = ::KEY_UNKNOWN1,
//Key_UNKNOWN2 = ::KEY_UNKNOWN2,
//Key_UNKNOWN3 = ::KEY_UNKNOWN3,
//Key_UNKNOWN4 = ::KEY_UNKNOWN4,
//Key_UNKNOWN5 = ::KEY_UNKNOWN5,
//Key_UNKNOWN6 = ::KEY_UNKNOWN6,
//Key_UNKNOWN7 = ::KEY_UNKNOWN7,
Key_UNKNOWN = ::SDLK_UNKNOWN,
Key_MODIFIERS = 1010,
Key_LSHIFT = ::SDLK_LSHIFT,
Key_RSHIFT = ::SDLK_RSHIFT,
Key_LCONTROL = ::SDLK_LCTRL,
Key_RCONTROL = ::SDLK_RCTRL,
Key_ALT = ::SDLK_LALT,
Key_ALTGR = ::SDLK_RALT,
Key_LWIN = ::SDLK_LGUI,
Key_RWIN = ::SDLK_RGUI,
Key_MENU = ::SDLK_MENU,
Key_SCRLOCK = ::SDLK_SCROLLLOCK,
Key_NUMLOCK = ::SDLK_NUMLOCKCLEAR,
Key_CAPSLOCK = ::SDLK_CAPSLOCK,
MAX = Key_CAPSLOCK
};

enum Mod{
ModMIN = -1,
ModInvalid = ModMIN,
Mod_NONE=::KMOD_NONE,	//No modifiers applicable
Mod_NUM=::KMOD_NUM,	//Numlock is down
Mod_CAPS=::KMOD_CAPS,	//Capslock is down
Mod_LCTRL=::KMOD_LCTRL,	//Left Control is down
Mod_RCTRL=::KMOD_RCTRL,	//Right Control is down
Mod_RSHIFT=::KMOD_RSHIFT,	//Right Shift is down
Mod_LSHIFT=::KMOD_LSHIFT,	//Left Shift is down
Mod_RALT=::KMOD_RALT,	//Right Alt is down
Mod_LALT=::KMOD_LALT,	//Left Alt is down
Mod_RGUI=::KMOD_RGUI,
Mod_LGUI=::KMOD_LGUI,
Mod_MODE=::KMOD_MODE,
ModMax=Mod_MODE
};


#define Mod_CTRL	(Mod_LCTRL|Mod_RCTRL)
#define Mod_SHIFT	(Mod_LSHIFT|Mod_RSHIFT)
#define Mod_ALT	(Mod_LALT|Mod_RALT)
#define Mod_GUI	(Mod_LGUI|Mod_RGUI)

	friend class CInputManager;
    typedef Key KeyType;
	typedef Mod KeyModifier;
    typedef uint32_t unicode_t;
    struct Event{
        Event():
        Mod(ModInvalid),
        key(Invalid),
		unicode(-1),
        enabled(false){
        }

        Event(KeyType key, KeyModifier Mod, unicode_t unicode, bool enabled):
        Mod(Mod),
        key(key),
		unicode(unicode),
        enabled(enabled){
        }
		KeyModifier Mod;
        KeyType key;
        /* Converted to a unicode character in UTF-32 */
        unicode_t unicode;
        /* whether the key is being pressed */
        bool enabled;
    };
	CKeyboard();
  //  KEYBOARDDATA Player1Keys;
 //   KEYBOARDDATA Player2Keys;
	/* poll:
	 * Put the keys in SDL key[] array into our map of int -> bool
	 */
	void poll();
    void HandleKeyboardRepeating();
//	void HandleKeyboardRepeating(KEYBOARDDATA *lpKeyBoard);
	/* wait for all keys to be released */
	void wait();

#if 0
	/** este método de sobrecarda do operador '[' retorna
	* verdadeiro se a tecla (i) foi pressionada pela primeira vez
	*/
	inline bool operator[] ( const int i ){

		if ( my_keys[ i ] < 0 ){ //! no método HandleKeyboardRepeating() i é negativado qdo a tecla é pressionada pela primeira vez
			my_keys[ i ] = 1;
			return true;
		}
		// se o valor de my_keys for maior que o valor de key_delay a tecla
		// também foi pressionada pela primeira vez
		bool b = my_keys[ i ] > key_delay[ i ];
		if ( b ){
			my_keys[ i ] = 1;
		}
		return b;
	}
#endif
	/** retorna verdadeiro se alguma tecla foi pressionada */
	bool keypressed();
	/** Armazena todas as teclas pressionadas num vetor fornecido pelo usuário */
	void readKeys( vector< KeyType > & all_keys );
	/**
	Waits for a key event and returns it. 
	**/
	static int readKey();
	/** Armazena todas as teclas do buffer num vetor fornecido pelo usuário */
	void readBufferedKeys(vector<KeyType> & keys);
    vector<Event> readData();
	//! não utilizado, utilizar CTextInput
    vector<unicode_t> readText();

    void clear();
	/* sets the latest repeat state. popping the state restores the previous state */
    static void pushRepeatState(bool enabled);
    static void popRepeatState();

	   /* true on systems that probably have a keyboard, like pc.
     * false on ps3, wii, etc.
     */
    static bool haveKeyboard();


	static void disableKeyRepeat();
    static void enableKeyRepeat();

	void setDelay( const int key, const int delay );
	void setAllDelay( const int delay );
    inline const vector<Event> & getBufferedKeys() const {
        return buffer;
    }
	static const char * keyToName( int key );
	static bool isNumber( int key );
	static bool isChar( int key );
	static bool isAlpha( int key );

	/** \brief registra quando uma tecla é pressionada
	* \parameter key: a tecla que foi pressionada
	* \parameter mod: o modificador (CTRL,ALT,NUM, etc)
	* \parameter unicode: o código unicode da tecla pressionada
	* \note no sdl o código unicode não é utilizado. o suporte a edição de texto é feito pelo evento SDL_TextInputEvent/SDL_TextEditingEvent
	* quando ocorre um evento de KEYDOWN, o event manager registra a tecla pressionada atrvés deste método
	*/
	void press(KeyType key,  KeyModifier mod,unicode_t unicode);
    /** \brief registra quando uma tecla é solta
	* \parameter key: qual atecla que foi solta
	* quando ocorre um evento de KEYUP, o event manager registra a tecla solta atrvés deste método
	*/
	void release(KeyType key);


protected:
    vector<Event> buffer;
	//map<int,int> my_keys;   //mapa indexado por scancode
    map<int,int> key_delay;  // mapa indexado por scancode
	map<KeyType, Event> keyState;
	bool enableBuffer;
	static vector<bool> repeatState;
	int numkeys; //número de teclas do teclado retornado pelo método HandleKeyboardRepeating. -1 -> não inicializado
};
} //end SGF
#endif
