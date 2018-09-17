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
#include "input/SGF_Keyboard.h"
#include "util/SGF_Debug.h"
#include "input/SGF_KeyMapping.h"
#include "external/fastevents.h"

#if SDL_VERSION_ATLEAST(1, 3, 0)
    const Uint8 * getKeyState(int * keys){
	return SDL_GetKeyboardState(keys);
    }
#else
    Uint8 * getKeyState(int * keys){
	return SDL_GetKeyState(keys);
    }
#endif

using namespace std;

namespace SGF{
vector<bool> CKeyboard::repeatState;
/*
const int CKeyboard::Key_A = ::SDLK_a;
const int CKeyboard::Key_B = ::SDLK_b;
const int CKeyboard::Key_C = ::SDLK_c;
const int CKeyboard::Key_D = ::SDLK_d;
const int CKeyboard::Key_E = ::SDLK_e;
const int CKeyboard::Key_F = ::SDLK_f;
const int CKeyboard::Key_G = ::SDLK_g;
const int CKeyboard::Key_H = ::SDLK_h;
const int CKeyboard::Key_I = ::SDLK_i;
const int CKeyboard::Key_J = ::SDLK_j;
const int CKeyboard::Key_K = ::SDLK_k;
const int CKeyboard::Key_L = ::SDLK_l;
const int CKeyboard::Key_M = ::SDLK_m;
const int CKeyboard::Key_N = ::SDLK_n;
const int CKeyboard::Key_O = ::SDLK_o;
const int CKeyboard::Key_P = ::SDLK_p;
const int CKeyboard::Key_Q = ::SDLK_q;
const int CKeyboard::Key_R = ::SDLK_r;
const int CKeyboard::Key_S = ::SDLK_s;
const int CKeyboard::Key_T = ::SDLK_t;
const int CKeyboard::Key_U = ::SDLK_u;
const int CKeyboard::Key_V = ::SDLK_v;
const int CKeyboard::Key_W = ::SDLK_w;
const int CKeyboard::Key_X = ::SDLK_x;
const int CKeyboard::Key_Y = ::SDLK_y;
const int CKeyboard::Key_Z = ::SDLK_z;
const int CKeyboard::Key_0 = ::SDLK_0;
const int CKeyboard::Key_1 = ::SDLK_1;
const int CKeyboard::Key_2 = ::SDLK_2;
const int CKeyboard::Key_3 = ::SDLK_3;
const int CKeyboard::Key_4 = ::SDLK_4;
const int CKeyboard::Key_5 = ::SDLK_5;
const int CKeyboard::Key_6 = ::SDLK_6;
const int CKeyboard::Key_7 = ::SDLK_7;
const int CKeyboard::Key_8 = ::SDLK_8;
const int CKeyboard::Key_9 = ::SDLK_9;
const int CKeyboard::Key_0_PAD = ::SDLK_KP0;
const int CKeyboard::Key_1_PAD = ::SDLK_KP1;
const int CKeyboard::Key_2_PAD = ::SDLK_KP2;
const int CKeyboard::Key_3_PAD = ::SDLK_KP3;
const int CKeyboard::Key_4_PAD = ::SDLK_KP4;
const int CKeyboard::Key_5_PAD = ::SDLK_KP5;
const int CKeyboard::Key_6_PAD = ::SDLK_KP6;
const int CKeyboard::Key_7_PAD = ::SDLK_KP7;
const int CKeyboard::Key_8_PAD = ::SDLK_KP8;
const int CKeyboard::Key_9_PAD = ::SDLK_KP9;
const int CKeyboard::Key_F1 = ::SDLK_F1;
const int CKeyboard::Key_F2 = ::SDLK_F2;
const int CKeyboard::Key_F3 = ::SDLK_F3;
const int CKeyboard::Key_F4 = ::SDLK_F4;
const int CKeyboard::Key_F5 = ::SDLK_F5;
const int CKeyboard::Key_F6 = ::SDLK_F6;
const int CKeyboard::Key_F7 = ::SDLK_F7;
const int CKeyboard::Key_F8 = ::SDLK_F8;
const int CKeyboard::Key_F9 = ::SDLK_F9;
const int CKeyboard::Key_F10 = ::SDLK_F10;
const int CKeyboard::Key_F11 = ::SDLK_F11;
const int CKeyboard::Key_F12 = ::SDLK_F12;
const int CKeyboard::Key_ESC = ::SDLK_ESCAPE;
const int CKeyboard::Key_TILDE = ::SDLK_BACKQUOTE;
const int CKeyboard::Key_MINUS = ::SDLK_MINUS;
const int CKeyboard::Key_EQUALS = ::SDLK_EQUALS;
const int CKeyboard::Key_BACKSPACE = ::SDLK_BACKSPACE;
const int CKeyboard::Key_TAB = ::SDLK_TAB;
const int CKeyboard::Key_OPENBRACE = ::SDLK_LEFTBRACKET;
const int CKeyboard::Key_CLOSEBRACE = ::SDLK_RIGHTBRACKET;
const int CKeyboard::Key_ENTER = ::SDLK_RETURN;
const int CKeyboard::Key_COLON = ::SDLK_COLON;
const int CKeyboard::Key_QUOTE = ::SDLK_QUOTE;
const int CKeyboard::Key_BACKSLASH = ::SDLK_BACKSLASH;
//const int CKeyboard::Key_BACKSLASH2 = ::KEY_BACKSLASH2;
const int CKeyboard::Key_COMMA = ::SDLK_COMMA;
const int CKeyboard::Key_STOP = ::SDLK_PERIOD;
const int CKeyboard::Key_SLASH = ::SDLK_SLASH;
const int CKeyboard::Key_SPACE = ::SDLK_SPACE;
const int CKeyboard::Key_INSERT = ::SDLK_INSERT;
const int CKeyboard::Key_DEL = ::SDLK_DELETE;
const int CKeyboard::Key_HOME = ::SDLK_HOME;
const int CKeyboard::Key_END = ::SDLK_END;
const int CKeyboard::Key_PGUP = ::SDLK_PAGEUP;
const int CKeyboard::Key_PGDN = ::SDLK_PAGEDOWN;
const int CKeyboard::Key_LEFT = ::SDLK_LEFT;
const int CKeyboard::Key_RIGHT = ::SDLK_RIGHT;
const int CKeyboard::Key_UP = ::SDLK_UP;
const int CKeyboard::Key_DOWN = ::SDLK_DOWN;
const int CKeyboard::Key_SLASH_PAD = ::SDLK_KP_PERIOD;
const int CKeyboard::Key_ASTERISK = ::SDLK_ASTERISK;
const int CKeyboard::Key_MINUS_PAD = ::SDLK_KP_MINUS;
const int CKeyboard::Key_PLUS_PAD = ::SDLK_KP_PLUS;
//const int CKeyboard::Key_DEL_PAD = ::KEY_DEL_PAD;
const int CKeyboard::Key_ENTER_PAD = ::SDLK_KP_ENTER;
const int CKeyboard::Key_PRTSCR = ::SDLK_PRINT;
const int CKeyboard::Key_PAUSE = ::SDLK_PAUSE;
//const int CKeyboard::Key_ABNT_C1 = ::KEY_ABNT_C1;
//const int CKeyboard::Key_YEN = ::KEY_YEN;
//const int CKeyboard::Key_KANA = ::KEY_KANA;
//const int CKeyboard::Key_CONVERT = ::KEY_CONVERT;
//const int CKeyboard::Key_NOCONVERT = ::KEY_NOCONVERT;
const int CKeyboard::Key_AT = ::SDLK_AT;
const int CKeyboard::Key_CIRCUMFLEX = ::SDLK_CARET;
//const int CKeyboard::Key_COLON2 = ::KEY_COLON2;
//const int CKeyboard::Key_KANJI = ::KEY_KANJI;
const int CKeyboard::Key_EQUALS_PAD = ::SDLK_KP_EQUALS;
const int CKeyboard::Key_BACKQUOTE = ::SDLK_BACKQUOTE;
const int CKeyboard::Key_SEMICOLON = ::SDLK_SEMICOLON;
const int CKeyboard::Key_COMMAND = ::SDLK_COMMA;
//const int CKeyboard::Key_UNKNOWN1 = ::KEY_UNKNOWN1;
//const int CKeyboard::Key_UNKNOWN2 = ::KEY_UNKNOWN2;
//const int CKeyboard::Key_UNKNOWN3 = ::KEY_UNKNOWN3;
//const int CKeyboard::Key_UNKNOWN4 = ::KEY_UNKNOWN4;
//const int CKeyboard::Key_UNKNOWN5 = ::KEY_UNKNOWN5;
//const int CKeyboard::Key_UNKNOWN6 = ::KEY_UNKNOWN6;
//const int CKeyboard::Key_UNKNOWN7 = ::KEY_UNKNOWN7;
const int CKeyboard::Key_UNKNOWN = ::SDLK_UNKNOWN;
//const int CKeyboard::Key_MODIFIERS = ::KEY_MODIFIERS;
const int CKeyboard::Key_LSHIFT = ::SDLK_LSHIFT;
const int CKeyboard::Key_RSHIFT = ::SDLK_RSHIFT;
const int CKeyboard::Key_LCONTROL = ::SDLK_LCTRL;
const int CKeyboard::Key_RCONTROL = ::SDLK_RCTRL;
const int CKeyboard::Key_ALT = ::SDLK_LALT;
const int CKeyboard::Key_ALTGR = ::SDLK_RALT;
const int CKeyboard::Key_LWIN = ::SDLK_LMETA;
const int CKeyboard::Key_RWIN = ::SDLK_RMETA;
const int CKeyboard::Key_MENU = ::SDLK_MENU;
const int CKeyboard::Key_SCRLOCK = ::SDLK_SCROLLOCK;
const int CKeyboard::Key_NUMLOCK = ::SDLK_NUMLOCK;
const int CKeyboard::Key_CAPSLOCK = ::SDLK_CAPSLOCK;
*/



CKeyboard::CKeyboard():
enableBuffer(false),
numkeys(-1){

	//for ( int q = 0; q < 323; q++ ){
	//	my_keys[ q ] = 0;
	//}

	setAllDelay( 0 );
/*	//! compatibilidade com o old mugen
	memset(&Player1Keys,0,sizeof(Player1Keys));
    memset(&Player2Keys,0,sizeof(Player2Keys));
    //Setup Player1 key config
    Player1Keys.Up.key        =SDLK_UP;
    Player1Keys.Down.key      =SDLK_DOWN;
    Player1Keys.Left.key      =SDLK_LEFT;
    Player1Keys.Right.key     =SDLK_RIGHT;
    Player1Keys.ButtonA.key   =SDLK_KP_4;
    Player1Keys.ButtonB.key   =SDLK_KP_5;
    Player1Keys.ButtonC.key   =SDLK_KP_6;
    Player1Keys.ButtonX.key   =SDLK_KP_7;
    Player1Keys.ButtonY.key   =SDLK_KP_8;
    Player1Keys.ButtonZ.key   =SDLK_KP_9;
    Player1Keys.bStart.key    =SDLK_RETURN;
    Player1Keys.bPause.key    =SDLK_TAB;
    //for now only Keyboard is support
    Player1Keys.bKeyBoard=true;

	//Setup Player1 key config
    Player2Keys.Up.key        =SDLK_UP;
    Player2Keys.Down.key      =SDLK_DOWN;
    Player2Keys.Left.key      =SDLK_LEFT;
    Player2Keys.Right.key     =SDLK_RIGHT;
    Player2Keys.ButtonA.key   =SDLK_KP_4;
    Player2Keys.ButtonB.key   =SDLK_KP_5;
    Player2Keys.ButtonC.key   =SDLK_KP_6;
    Player2Keys.ButtonX.key   =SDLK_KP_7;
    Player2Keys.ButtonY.key   =SDLK_KP_8;
    Player2Keys.ButtonZ.key   =SDLK_KP_9;
    Player2Keys.bStart.key    =SDLK_RETURN;
    Player2Keys.bPause.key    =SDLK_TAB;
    //for now only CKeyboard is support
    Player2Keys.bKeyBoard=true;
	*/
}


void CKeyboard::poll(){
	 Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  " << endl;
	 //Clear the prev state of the keys
     buffer.clear();
	 //Player1Keys.nKey=0;
     //Player2Keys.nKey=0;
	 //! pega os eventos dos devices e coloca nos buffers do SDL
#ifdef USE_FASTEVENTS
	FE_PumpEvents();
#else
    SDL_PumpEvents();
#endif

     Debug::debug(Debug::input,__FUNCTION__) << "END  " << endl;
}
#if 0
void CKeyboard::HandleKeyboardRepeating(KEYBOARDDATA *lpKeyBoard)
{
	/*
	Pega uma foto do estado do teclado
	O estado atual é retornado pelo SDL como um ponteiro para um Array.
	O tamanho desse Array é armazenado em numkeys.
	O array é indexado por SDL_Scancode http://wiki.libsdl.org/moin.cgi/SDL_Scancode.
	Valores 1 indicam que a tecla foi pressionada e 0 o contrário.
	O ponteiro que é retornado aponta para um Array SDL.
	Ele será válido pelo tempo que a aplicação estiver funcionando e não deve ser
	liberado ou deletado pelo usuário.
	*/

#ifdef USE_FASTEVENTS
	FE_PumpEvents();
#else
    SDL_PumpEvents();
#endif

    Uint8 *keystate = SDL_GetKeyboardState(&numkeys);

    //Process keyboard input
    if(lpKeyBoard->bKeyBoard)
    {
          //Check down Key///////////////
		  // pega o estado só das teclas definidas em lpkeyboard
		  // keystate equivale a my_keys
          if(keystate[lpKeyBoard->Up.key])
          {
             lpKeyBoard->nKey+=UP+PRESSED;
             lpKeyBoard->Up.bPressed=true;
             lpKeyBoard->Up.nTime++;
          }
          else if(lpKeyBoard->Up.bPressed)
          {
             lpKeyBoard->nKey+=UP+RELEASED;
             lpKeyBoard->Up.bPressed=false;
             lpKeyBoard->Up.nTime=0;
          }


		  if(keystate[lpKeyBoard->Down.key])
           {
              lpKeyBoard->nKey+=DOWN+PRESSED;
              lpKeyBoard->Down.bPressed=true;
              lpKeyBoard->Down.nTime++;
           }
           else if(lpKeyBoard->Down.bPressed)
           {
             lpKeyBoard->nKey+=DOWN+RELEASED;
             lpKeyBoard->Down.bPressed=false;
             lpKeyBoard->Down.nTime=0;
           }

		  if(keystate[lpKeyBoard->Left.key])
           {
              lpKeyBoard->nKey=LEFT+PRESSED;
              lpKeyBoard->Left.bPressed=true;
              lpKeyBoard->Left.nTime++;
           }
           else if(lpKeyBoard->Left.bPressed)
           {
             lpKeyBoard->nKey+=LEFT+RELEASED;
             lpKeyBoard->Left.bPressed=false;
             lpKeyBoard->Left.nTime=0;
           }



		  if(keystate[lpKeyBoard->Right.key])
           {
              lpKeyBoard->nKey+=RIGHT+PRESSED;
              lpKeyBoard->Right.bPressed=true;
              lpKeyBoard->Right.nTime++;
           }
           else if(lpKeyBoard->Right.bPressed)
           {
             lpKeyBoard->nKey+=RIGHT+RELEASED;
             lpKeyBoard->Right.bPressed=false;
             lpKeyBoard->Right.nTime=0;
           }


		  if(keystate[lpKeyBoard->ButtonA.key])
           {
              lpKeyBoard->nKey+=BUTTONA+PRESSED;
              lpKeyBoard->ButtonA.bPressed=true;
              lpKeyBoard->ButtonA.nTime++;
           }
           else if(lpKeyBoard->ButtonA.bPressed)
           {
             lpKeyBoard->nKey+=BUTTONA+RELEASED;
             lpKeyBoard->ButtonA.bPressed=false;
             lpKeyBoard->ButtonA.nTime=0;
           }


		  if(keystate[lpKeyBoard->ButtonB.key])
           {
              lpKeyBoard->nKey+=BUTTONB+PRESSED;
              lpKeyBoard->ButtonB.bPressed=true;
              lpKeyBoard->ButtonB.nTime++;
           }
           else if(lpKeyBoard->ButtonB.bPressed)
           {
             lpKeyBoard->nKey+=BUTTONB+RELEASED;
             lpKeyBoard->ButtonB.bPressed=false;
             lpKeyBoard->ButtonB.nTime=0;
           }

		  if(keystate[lpKeyBoard->ButtonC.key])
           {
              lpKeyBoard->nKey+=BUTTONC+PRESSED;
              lpKeyBoard->ButtonC.bPressed=true;
              lpKeyBoard->ButtonC.nTime++;
           }
           else if(lpKeyBoard->ButtonC.bPressed)
           {
             lpKeyBoard->nKey+=BUTTONC+RELEASED;
             lpKeyBoard->ButtonC.bPressed=false;
             lpKeyBoard->ButtonC.nTime=0;
           }

		  if(keystate[lpKeyBoard->ButtonX.key])
           {
              lpKeyBoard->nKey+=BUTTONX+PRESSED;
              lpKeyBoard->ButtonX.bPressed=true;
              lpKeyBoard->ButtonX.nTime++;
           }
           else if(lpKeyBoard->ButtonX.bPressed)
           {
             lpKeyBoard->nKey+=BUTTONX+RELEASED;
             lpKeyBoard->ButtonX.bPressed=false;
             lpKeyBoard->ButtonX.nTime=0;
           }

		  if(keystate[lpKeyBoard->ButtonY.key])
           {
              lpKeyBoard->nKey+=BUTTONY+PRESSED;
              lpKeyBoard->ButtonY.bPressed=true;
              lpKeyBoard->ButtonY.nTime++;
           }
           else if(lpKeyBoard->ButtonY.bPressed)
           {
             lpKeyBoard->nKey+=BUTTONY+RELEASED;
             lpKeyBoard->ButtonY.bPressed=false;
             lpKeyBoard->ButtonY.nTime=0;
           }

		  if(keystate[lpKeyBoard->ButtonZ.key])
           {
              lpKeyBoard->nKey+=BUTTONZ+PRESSED;
              lpKeyBoard->ButtonZ.bPressed=true;
              lpKeyBoard->ButtonZ.nTime++;
           }
           else if(lpKeyBoard->ButtonZ.bPressed)
           {
             lpKeyBoard->nKey+=BUTTONZ+RELEASED;
             lpKeyBoard->ButtonZ.bPressed=false;
             lpKeyBoard->ButtonZ.nTime=0;
           }

           //Check for a key release


    }

}
#endif
#if 0
void CKeyboard::HandleKeyboardRepeating() {
#ifdef USE_FASTEVENTS
	FE_PumpEvents();
#else
    SDL_PumpEvents();
#endif

	 Uint8 *iKeyState = SDL_GetKeyboardState(&numkeys);
	 Debug::debug(Debug::input,__FUNCTION__) << "BEGIN // CKeyboard::HandleKeyboardRepeating()  // " << endl;
	 Debug::debug(Debug::input,__FUNCTION__) << "INFO // CKeyboard::HandleKeyboardRepeating()  // Preenche my_keys" << endl;
	 /*
	Pega uma foto do estado do teclado
	O estado atual é retornado pelo SDL como um ponteiro para um Array.
	O tamanho desse Array é armazenado em numkeys.
	O array é indexado por SDL_Scancode http://wiki.libsdl.org/moin.cgi/SDL_Scancode.
	Valores 1 indicam que a tecla foi pressionada e 0 o contrário.
	O ponteiro que é retornado aponta para um Array SDL.
	Ele será válido pelo tempo que a aplicação estiver funcionando e não deve ser
	liberado ou deletado pelo usuário.
	*/
	 for(int i = 0; i <= SDL_NUM_SCANCODES; i++) {
	//	for(int i = 0; i <= numkeys; i++) {
		if(iKeyState[i])
		{

			if ( my_keys[ i ] <= 0 ){
			 // my_mousekeys[ q ] se  torna negativo, podendo assim um tecla
			 // ser pressionada pela primeira vez sem ter que
			 // esperar por um delay

				my_keys[ i ] -= 1;
				Debug::debug(Debug::input,__FUNCTION__) << "CKeyboard::My_keys[ "<< i <<" ] =" << my_keys[i] << endl;

			} else { // O operador '[' faz com que my_keys seja 1 deposi que a teca foi ressionada pela 1a vez
                my_keys[ i ] += 1;
				Debug::debug(Debug::input,__FUNCTION__) << "CKeyboard::My_keys[ "<< i <<" ] =" << my_keys[i] << endl;

			}
			// printf( "Key %d = %d\n", q, my_keys[ q ] );
		}else {
			my_keys[ i ] = 0;
			Debug::debug(Debug::input,__FUNCTION__) << "CKeyboard::My_keys[ "<< i <<" ] =" << my_keys[i] << endl;

		}
    }


}

#endif

void CKeyboard::readKeys( vector<KeyType> & all_keys ){
	//coloca todas as teclas pressionadas que foram coletadas pela rotina pool no vetor dado
	Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  " << endl;

	int keys = 0;
    const Uint8 * state = getKeyState(&keys);
 	for (int i = 0; i < SDL_NUM_SCANCODES; i++){
        if (i != SDLK_NUMLOCKCLEAR && state[i] == 1){
            all_keys.push_back(SDLKeyMapping::toKey(::SDL_GetKeyFromScancode((SDL_Scancode) i)));
        }
    }
	// tentativa 2
	/*for (map<KeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
        KeyType key = it->first;
        const Event & data = it->second;
        if (data.enabled){
            all_keys.push_back(key);
        }
    }
	*/
	/*for ( map<int,int>::const_iterator it = my_keys.begin(); it != my_keys.end(); it++ ){
		const int & key = it->first;
		const int & delay = it->second;
		if ( delay != 0 ){
			Debug::debug( 406 ) << "Key " << key << " delay " << delay << " key_delay " << key_delay[ key ] << endl;
		}
		if ( delay < 0 ){
			Debug::debug( 406 ) << "Key " << key << " delay " << delay << " key_delay " << key_delay[ key ] << endl;
			all_keys.push_back( ::SDL_GetKeyFromScancode((SDL_scancode) key) );  //key = scancode
			my_keys[ key ] = 1;
		} else if ( delay > key_delay[ ::SDL_GetKeyFromScancode((SDL_scancode)key) ] ){
            Debug::debug( 406 ) << "Key " << key << " delay " << delay << " key_delay " << key_delay[ key ] << endl;
			all_keys.push_back( ::SDL_GetKeyFromScancode((SDL_scancode)key) );
			my_keys[ key ] = 1;
		}
	}*/

	Debug::debug(Debug::input,__FUNCTION__) << "END // " << endl;
}
#if 0

void CKeyboard::readKeys(vector<int> & all_keys){
    for (map<KeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
        KeyType key = it->first;
        const Event & data = it->second;
        if (data.enabled){
            all_keys.push_back(::SDL_GetKeyFromScancode((SDL_scancode)key));
        }
    }
}


#endif
int CKeyboard::readKey(){
	SDL_Event oSdlEvent;
#ifdef USE_FASTEVENTS
	while (FE_WaitEvent(&oSdlEvent))
#else
 while (SDL_WaitEvent(&oSdlEvent))
#endif
	{
		if ( SDL_KEYDOWN == oSdlEvent.type )
		{
			return oSdlEvent.key.keysym.sym;
		}

	}	// Polling events

	// Code will never reach this point, unless there's an error.
	return SDLK_ESCAPE;
}

void CKeyboard::setDelay( const int key, const int delay ){
	key_delay[ ::SDL_GetScancodeFromKey(key) ] = delay;
}

void CKeyboard::setAllDelay( const int delay ){
	setDelay( Key_A, delay );
	setDelay( Key_B, delay );
	setDelay( Key_C, delay );
	setDelay( Key_D, delay );
	setDelay( Key_E, delay );
	setDelay( Key_F, delay );
	setDelay( Key_G, delay );
	setDelay( Key_H, delay );
	setDelay( Key_I, delay );
	setDelay( Key_J, delay );
	setDelay( Key_K, delay );
	setDelay( Key_L, delay );
	setDelay( Key_M, delay );
	setDelay( Key_N, delay );
	setDelay( Key_O, delay );
	setDelay( Key_P, delay );
	setDelay( Key_Q, delay );
	setDelay( Key_R, delay );
	setDelay( Key_S, delay );
	setDelay( Key_T, delay );
	setDelay( Key_U, delay );
	setDelay( Key_V, delay );
	setDelay( Key_W, delay );
	setDelay( Key_X, delay );
	setDelay( Key_Y, delay );
	setDelay( Key_Z, delay );
	setDelay( Key_0, delay );
	setDelay( Key_1, delay );
	setDelay( Key_2, delay );
	setDelay( Key_3, delay );
	setDelay( Key_4, delay );
	setDelay( Key_5, delay );
	setDelay( Key_6, delay );
	setDelay( Key_7, delay );
	setDelay( Key_8, delay );
	setDelay( Key_9, delay );
	setDelay( Key_0_PAD, delay );
	setDelay( Key_1_PAD, delay );
	setDelay( Key_2_PAD, delay );
	setDelay( Key_3_PAD, delay );
	setDelay( Key_4_PAD, delay );
	setDelay( Key_5_PAD, delay );
	setDelay( Key_6_PAD, delay );
	setDelay( Key_7_PAD, delay );
	setDelay( Key_8_PAD, delay );
	setDelay( Key_9_PAD, delay );
	setDelay( Key_F1, delay );
	setDelay( Key_F2, delay );
	setDelay( Key_F3, delay );
	setDelay( Key_F4, delay );
	setDelay( Key_F5, delay );
	setDelay( Key_F6, delay );
	setDelay( Key_F7, delay );
	setDelay( Key_F8, delay );
	setDelay( Key_F9, delay );
	setDelay( Key_F10, delay );
	setDelay( Key_F11, delay );
	setDelay( Key_F12, delay );
	setDelay( Key_ESC, delay );
	setDelay( Key_TILDE, delay );
	setDelay( Key_MINUS, delay );
	setDelay( Key_EQUALS, delay );
	setDelay( Key_BACKSPACE, delay );
	setDelay( Key_TAB, delay );
	setDelay( Key_OPENBRACE, delay );
	setDelay( Key_CLOSEBRACE, delay );
	setDelay( Key_ENTER, delay );
	setDelay( Key_COLON, delay );
	setDelay( Key_QUOTE, delay );
	setDelay( Key_BACKSLASH, delay );
	//setDelay( Key_BACKSLASH2, delay );
	setDelay( Key_COMMA, delay );
	//setDelay( Key_STOP, delay );
	setDelay( Key_SLASH, delay );
	setDelay( Key_SPACE, delay );
	setDelay( Key_INSERT, delay );
	setDelay( Key_DEL, delay );
	setDelay( Key_HOME, delay );
	setDelay( Key_END, delay );
	setDelay( Key_PGUP, delay );
	setDelay( Key_PGDN, delay );
	setDelay( Key_LEFT, delay );
	setDelay( Key_RIGHT, delay );
	setDelay( Key_UP, delay );
	setDelay( Key_DOWN, delay );
	setDelay( Key_SLASH_PAD, delay );
	setDelay( Key_ASTERISK, delay );
	setDelay( Key_MINUS_PAD, delay );
	setDelay( Key_PLUS_PAD, delay );
	//setDelay( Key_DEL_PAD, delay );
	setDelay( Key_ENTER_PAD, delay );
	setDelay( Key_PRTSCR, delay );
	setDelay( Key_PAUSE, delay );
	//setDelay( Key_ABNT_C1, delay );
	//setDelay( Key_YEN, delay );
	//setDelay( Key_KANA, delay );
	//setDelay( Key_CONVERT, delay );
	//setDelay( Key_NOCONVERT, delay );
	setDelay( Key_AT, delay );
	//setDelay( Key_CIRCUMFLEX, delay );
	//setDelay( Key_COLON2, delay );
	//setDelay( Key_KANJI, delay );
	setDelay( Key_EQUALS_PAD, delay );
	setDelay( Key_BACKQUOTE, delay );
	setDelay( Key_SEMICOLON, delay );
	setDelay( Key_COMMAND, delay );
	setDelay( Key_UNKNOWN, delay );
	//setDelay( Key_UNKNOWN2, delay );
	//setDelay( Key_UNKNOWN3, delay );
	//setDelay( Key_UNKNOWN4, delay );
	//setDelay( Key_UNKNOWN5, delay );
	//setDelay( Key_UNKNOWN6, delay );
	//setDelay( Key_UNKNOWN7, delay );
	//setDelay( Key_UNKNOWN8, delay );
	//setDelay( Key_MODIFIERS, delay );
	setDelay( Key_LSHIFT, delay );
	setDelay( Key_RSHIFT, delay );
	setDelay( Key_LCONTROL, delay );
	setDelay( Key_RCONTROL, delay );
	setDelay( Key_ALT, delay );
	setDelay( Key_ALTGR, delay );
	//setDelay( Key_LWIN, delay );
	//setDelay( Key_RWIN, delay );
	setDelay( Key_MENU, delay );
	setDelay( Key_SCRLOCK, delay );
	setDelay( Key_NUMLOCK, delay );
	setDelay( Key_CAPSLOCK, delay );
}

void CKeyboard::wait(){
	while ( keypressed() ){
		poll();
		Util::rest( 1 );
	}
}

bool CKeyboard::keypressed(){
	 //  int numkeys = 0;
    const Uint8 * state = getKeyState(NULL);
	for (int i = 0; i < SDL_NUM_SCANCODES; i++){
        if (i != SDLK_NUMLOCKCLEAR && state[i] == 1){
            return true;
        }
    }
    return false;

/*	for ( map<int,int>::const_iterator it = my_keys.begin(); it != my_keys.end(); it++ ){
		const int & n = (*it).second;
		if ( n < 0 || n > key_delay[ it->first ] ){
			return true;
		}
	}
	return false;*/
}


void CKeyboard::disableKeyRepeat(){
	//s ::SDL_EnableKeyRepeat(0, 0);
}

void CKeyboard::enableKeyRepeat(){
	//s ::SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

void CKeyboard::pushRepeatState(bool enabled){
    if (enabled){
        enableKeyRepeat();
    } else {
        disableKeyRepeat();
    }
    repeatState.push_back(enabled);
}

void CKeyboard::popRepeatState(){
    if (repeatState.size() > 0){
        bool last = repeatState.back();
        repeatState.pop_back();
        bool enabled = true;
        if (repeatState.size() > 0){
            enabled = repeatState.back();
        }

        if (enabled != last){
            if (enabled){
                enableKeyRepeat();
            } else {
                disableKeyRepeat();
            }
        }
    }
}

bool CKeyboard::isNumber( int key ){
	return key == Key_0 ||
	       key == Key_1 ||
	       key == Key_2 ||
	       key == Key_3 ||
	       key == Key_4 ||
	       key == Key_5 ||
	       key == Key_6 ||
	       key == Key_7 ||
	       key == Key_8 ||
	       key == Key_9;
}

bool CKeyboard::isChar( int key ){
	return key == Key_A ||
	       key == Key_B ||
			 key == Key_C ||
			 key == Key_D ||
			 key == Key_E ||
			 key == Key_F ||
			 key == Key_G ||
			 key == Key_H ||
			 key == Key_I ||
			 key == Key_J ||
			 key == Key_K ||
			 key == Key_L ||
			 key == Key_M ||
			 key == Key_N ||
			 key == Key_O ||
			 key == Key_P ||
			 key == Key_Q ||
			 key == Key_R ||
			 key == Key_S ||
			 key == Key_T ||
			 key == Key_U ||
			 key == Key_V ||
			 key == Key_W ||
			 key == Key_X ||
			 key == Key_Y ||
			 key == Key_Z ||
             key == Key_MINUS;
}

bool CKeyboard::isAlpha( int key ){
		  return isNumber( key ) || isChar( key );
}

void CKeyboard::clear(){
	buffer.clear();
	keyState.clear();
	//SDL_FlushEvents(SDL_KEYDOWN,SDL_KEYUP);
	//my_keys.clear();
}

const char * CKeyboard::keyToName( int key ){
	return SDL_GetKeyName(key);
}

bool CKeyboard::haveKeyboard(){
#if defined(WII) || defined(PS3) || defined(XENON)
    return false;
#endif
    return true;
}

void CKeyboard::press(KeyType key, KeyModifier mod, unicode_t unicode){
	Debug::debug(Debug::input,__FUNCTION__) << "key: "<< key <<endl;
    keyState[key].key = key;
	keyState[key].Mod = mod;
    keyState[key].unicode = unicode;
    keyState[key].enabled = true;
    // if (enableBuffer){
        buffer.push_back(keyState[key]);
    // }
    /*
    Event data(key, unicode, true);
    for (vector<Observer>::iterator it = observers.begin(); it != observers.end(); it++){
        Observer observer = (*it);
        observer.callback(data, observer.extra);
    }
    */
}

void CKeyboard::release(KeyType key){
	Debug::debug(Debug::input,__FUNCTION__) << "key: "<< key <<endl;
    keyState[key].enabled = false;
    buffer.push_back(keyState[key]);
    /*
    Event data(key, 0, false);
    for (vector<Observer>::iterator it = observers.begin(); it != observers.end(); it++){
        Observer observer = (*it);
        observer.callback(data, observer.extra);
    }
    */
}

void CKeyboard::readBufferedKeys(vector<KeyType> & keys){
    for (vector<Event>::iterator it = buffer.begin(); it != buffer.end(); it++){
        const Event & data = *it;
        keys.push_back(data.key);
    }
}

vector<CKeyboard::Event> CKeyboard::readData(){
    vector<CKeyboard::Event> out;
    for (map<KeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
        //KeyType key = it->first;
        const Event & data = it->second;
        if (data.enabled){
            out.push_back(data);
        }
    }
    return out;
}

//! não utilizado, utilizar CTextInput
vector<CKeyboard::unicode_t> CKeyboard::readText(){
    vector<CKeyboard::unicode_t> out;
    for (map<KeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
        //KeyType key = it->first;
        const Event & data = it->second;
        if (data.enabled){
            out.push_back(data.unicode);
        }
    }
    return out;
}



} //end SGF