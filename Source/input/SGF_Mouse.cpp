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
#include "input/SGF_Mouse.h"
#include "util/SGF_Util.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include "util/SGF_Debug.h"

#include "external/fastevents.h"


using namespace std;
namespace SGF {
//const int CMouse::Key_LEFT = SDL_BUTTON_LEFT;
//const int CMouse::Key_MIDDLE = SDL_BUTTON_MIDDLE;
//const int CMouse::Key_RIGHT = SDL_BUTTON_RIGHT;
//const int CMouse::Key_X1 = SDL_BUTTON_X1;
//const int CMouse::Key_X2 = SDL_BUTTON_X2;


/** @fn CMouse::create()
@brief Função que cria um objeto do tipo Mouse
@param nenhum
@return ponteiro para o objeto CMouse Criado
@warning deve ser utilizada se o suporte a mouse for habilitado no módulo de configuração
**/
CMouse * CMouse::create(){
	Debug::debug(Debug::input,__FUNCTION__) << "Will Create a Mouse"<<endl;

    return new CMouse();

}

/** @fn CMouse::CMouse()
@brief Construtor do objeto do tipo Mouse
@param nenhum
@return nenhum
@warning é chamada pelo método create()
**/
CMouse::CMouse():
enableBuffer(true){

	//for ( int q = 0; q < 323; q++ ){
	//	my_mousekeys[ q ] = 0;
	//}
	//setAllDelay( 0 );

	//! TO THE OLD mUGEN

	memset(&PlayerMouseKeys,0,sizeof(PlayerMouseKeys));


	PlayerMouseKeys.Left.key  =SDL_BUTTON_LEFT;
    PlayerMouseKeys.Middle.key =SDL_BUTTON_MIDDLE;
    PlayerMouseKeys.Right.key =SDL_BUTTON_RIGHT;
    PlayerMouseKeys.X1.key =SDL_BUTTON_X1;
    PlayerMouseKeys.X2.key =SDL_BUTTON_X2;

    //for now only Keyboard is support
    PlayerMouseKeys.bMouse=true;


}
/** @fn CMouse::~CMouse()
@brief Destrutor do objeto do tipo Mouse
@param nenhum
@return nenhum
@warning
**/
CMouse::~CMouse(){
	//teste
}
void CMouse::clearBuffer() {
	buffer.clear();
}
void CMouse::clearAbsoluteBuffer(){
	if (absolutebuffer.size() >0 )
	absolutebuffer.clear();

}
void CMouse::clearRelativeBuffer(){
	if (relativebuffer.size() >0 )
	relativebuffer.clear();

}

/** @fn CMouse::poll()
@brief Limpa os buffers de eventos do Mouse
@warning a coleta de novos eventos é feita pela classe CKeyboard
**/
void CMouse::poll(){
	 Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  " << endl;
	 //Clear the prev state of the keys
	 if (buffer.size() > 0) buffer.clear();
	 clearAbsoluteBuffer();
	 clearRelativeBuffer();
	 PlayerMouseKeys.nKey=0;
     //SDL_PumpEvents();  // Já é feita a coleta pela classe keyboard
     Debug::debug(Debug::input,__FUNCTION__) << "END  " << endl;
}

//A continuous mouse click works the same as continuous keystrokes, as they will generate multiple events until the key is depressed. Examples:
//Multiple Item Selection - When you desire to select multiple items by dragging some kind of selector tool around them.
// The old Drag and Drop.

void CMouse::HandleMouseRepeating(MOUSEDATA *lpMouse)  // repeating or continous
{
	/*
	Gets a snapshot of the current mouse state.
	*/
#ifdef USE_FASTEVENTS
	FE_PumpEvents();
#else
    SDL_PumpEvents();
#endif

    Uint8 mousestate = SDL_GetMouseState(NULL,NULL);

    //Process Mouse input
	if(lpMouse->bMouse)
    {
          //Check down Mousekey/
		/*
		Bellow we grab a snapshot of the current button state of the mouse and compare that data with the value of SDL_BUTTON(x). When used together with the binary 'and', we will either get a 0 or 1 result.
		*/
          if(mousestate && SDL_BUTTON(Key_WUP))
           {
              lpMouse->nKey+=BUTTONX1+PRESSED;
              lpMouse->X1.bPressed=true;
              lpMouse->X1.nTime++;
           }
           else if(lpMouse->X1.bPressed)
           {
             lpMouse->nKey+=BUTTONX1+RELEASED;
             lpMouse->X1.bPressed=false;
             lpMouse->X1.nTime=0;
           }
          if(mousestate && SDL_BUTTON(Key_WDOWN))
           {
              lpMouse->nKey+=BUTTONX2+PRESSED;
              lpMouse->X2.bPressed=true;
              lpMouse->X2.nTime++;
           }
           else if(lpMouse->X2.bPressed)
           {
             lpMouse->nKey+=BUTTONX2+RELEASED;
             lpMouse->X2.bPressed=false;
             lpMouse->X2.nTime=0;
           }

		  if(mousestate && SDL_BUTTON(Key_LEFT)) //
           {
              lpMouse->nKey=LEFT+PRESSED;
              lpMouse->Left.bPressed=true;
              lpMouse->Left.nTime++;
           }
           else if(lpMouse->Left.bPressed)
           {
             lpMouse->nKey+=LEFT+RELEASED;
             lpMouse->Left.bPressed=false;
             lpMouse->Left.nTime=0;
           }



		  if(mousestate && SDL_BUTTON(Key_RIGHT))
           {
              lpMouse->nKey+=RIGHT+PRESSED;
              lpMouse->Right.bPressed=true;
              lpMouse->Right.nTime++;
           }
           else if(lpMouse->Right.bPressed)
           {
             lpMouse->nKey+=RIGHT+RELEASED;
             lpMouse->Right.bPressed=false;
             lpMouse->Right.nTime=0;
           }


		  if(mousestate && SDL_BUTTON(Key_MIDDLE))
           {
              lpMouse->nKey+=MIDDLE+PRESSED;
              lpMouse->Middle.bPressed=true;
              lpMouse->Middle.nTime++;
           }
           else if(lpMouse->Middle.bPressed)
           {
             lpMouse->nKey+=MIDDLE+RELEASED;
             lpMouse->Middle.bPressed=false;
             lpMouse->Middle.nTime=0;
           }

           //Check for a Mousekey release


    }

}
#if 0
void CMouse::HandleMouseRepeating() {
	//! retira os eventos dos dispositivos
#ifdef USE_FASTEVENTS
	FE_PumpEvents();
#else
    SDL_PumpEvents();
#endif

	int x,y; //posição do mouse nesse instante
	//! pea o estado atual do mouse
	 Uint8 imousestate = SDL_GetMouseState(&x,&y);
	 Debug::debug(Debug::input,__FUNCTION__) << "BEGIN // Preenche my_mousekeys  // " << endl;

	 for(int i = 1; i <= 5; i++) {
		if(imousestate && SDL_BUTTON(i))  //true se for precionada a tecla// i:  1 for the left button, 2 for middle, 3 for the right
		{  //se a tecla do mouse foi pressionada

			if ( my_mousekeys[ i ] <= 0 ){ //! a tecla foi pressionada pela primeira vez
			 // my_mousekeys[ q ] se  torna negativo, podendo assim um tecla
			 // ser pressionada pela primeira vez sem ter que
			 // esperar por um delay

				my_mousekeys[ i ] -= 1;
				Debug::debug(Debug::input,__FUNCTION__) << "CMouse::my_mousekeys[ "<< i <<" ] =" << my_mousekeys[i] << endl;

			} else {
                my_mousekeys[ i ] += 1;
				Debug::debug(Debug::input,__FUNCTION__) << "CMouse::my_mousekeys[ "<< i <<" ] =" << my_mousekeys[i] << endl;

			}
			// printf( "Mousekey %d = %d\n", q, my_mousekeys[ q ] );
		}else { //se a tecla do mouse não foi pressionada
			my_mousekeys[ i ] = 0;
			Debug::debug(Debug::input,__FUNCTION__) << "CMouse::my_mousekeys[ "<< i <<" ] =" << my_mousekeys[i] << endl;

		}
    }


}
#endif
/** @fn CMouse::readMouseKeys( vector< int > & all_keys )
@brief coloca todas as teclas pressionadas que foram coletadas pela rotina pool no vetor passado
@param vector< int > & all_keys - Vetor a ser preenchido com as teclas do mouse que foram precionadas
@return nenhum
@warning
**/
void CMouse::readMouseKeys( vector< MouseKeyType > & all_keys ){

	Debug::debug(Debug::input,__FUNCTION__) << "BEGIN  " << endl;
	for (map<MouseKeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
        MouseKeyType Mousekey = it->first;
        const Event & data = it->second;
        if (data.enabled){
            all_keys.push_back(Mousekey);
        }
    }

	Debug::debug(Debug::input,__FUNCTION__) << "END // " << endl;
}
#if 0

void CMouse::readMouseKeys(vector<int> & all_keys){
    for (map<MouseKeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
        MouseKeyType Mousekey = it->first;
        const Event & data = it->second;
        if (data.enabled){
            all_keys.push_back(::SDL_GetKeyFromScancode((SDL_scancode)Mousekey));
        }
    }
}


#endif

/** @fn CMouse::readMouseKey()
@brief espera até que uma tecla do mouse seja pressionada
@param nemhum
@return o valor da tecla que foi pressionada
@warning
**/
int CMouse::readMouseKey(){
	SDL_Event oSdlEvent;
#ifdef USE_FASTEVENTS
	while (FE_WaitEvent(&oSdlEvent))
#else
 while (SDL_WaitEvent(&oSdlEvent))
#endif
	{
		if ( SDL_MOUSEBUTTONDOWN == oSdlEvent.type )
		{
			//Debug::debug(Debug::resources,__FUNCTION__) << "The Mousekey was pressed="<< SDL_GetKeyName(event.button.button)<<endl;
    		return oSdlEvent.button.button;;
		}

	}	// Polling events

	// Code will never reach this point, unless there's an error.
	return SDLK_ESCAPE;

}


void CMouse::setDelay( const int Mousekey, const int delay ){
	key_delay[ Mousekey ] = delay;
}

void CMouse::setAllDelay( const int delay ){
	setDelay( Key_LEFT, delay );
	setDelay( Key_MIDDLE, delay );
	setDelay( Key_RIGHT, delay );
	setDelay( Key_WUP, delay );
	setDelay( Key_WDOWN, delay );

}

/** @fn CMouse::wait()
@brief espera até que todas as teclas sejam soltas
@param nemhum
@return nenhum
@warning
**/
void CMouse::wait(){
	while ( mousekeypressed() ){
		poll();
		Util::rest( 1 );
	}
}
/** @fn CMouse::mousekeypressed()
@brief retorna verdadeiro se alguma tecla do mouse foi pressionada
@param nemhum
@return verdadeiro se um tecla foi precssionada ou false caso nenhuma tecla foi pressionada
@warning
**/
bool CMouse::mousekeypressed(){
	//int keys=0;
	Uint8 imousestate = SDL_GetMouseState(NULL,NULL);
	for(int i = 1; i <= 5; i++) {
		  if (imousestate && SDL_BUTTON(i) == 1){
            return true;
	}
	}
	return false;
}


void CMouse::clear(){
	clearBuffer();
	clearAbsoluteBuffer();
	clearRelativeBuffer();
	keyState.clear();
}

/** @fn CMouse::keyToName( int Mousekey )
@brief retorna o nome da tecla passada
@param int Mousekey: o índice da tecla que deseja saber o nome
@return retorna o nome da tecla passada no parâmetro
@warning
**/
const char * CMouse::keyToName( int Mousekey ){
	//return SDL_GetKeyName(Mousekey);
	switch (Mousekey) {
	case Key_LEFT: return "Key Left";break;   // 0
	case Key_MIDDLE: return "Key Middle";break;  // 2  WhellButton
	case Key_RIGHT: return "Key Right";break;  // 1
	case Key_WUP: return "MOUSE Wheel UP";break;  //   Forward
	case Key_WDOWN: return "Mouse Wheel DOWN";break;
	case Key_MoveUP: return "Mouse Moved UP";break;  // Virtual key switched when mouse move
	case Key_MoveDOWN: return "Mouse Moved DOWN";break;  // Virtual key switched when mouse move
	case Key_MoveLEFT: return "Mouse Moved LEFT";break;  // Virtual key switched when mouse move
	case key_MoveRIGHT: return "Mouse Moved Right";break; // Virtual key switched when mouse move

default: return "Unknow";break;
	}
}

/** @fn CMouse::press(MouseKeyType Mousekey)
@brief habilita a tecla pressionada e a coloca no  buffer
@param int Mousekey: o índice da tecla que que foi pressionada
	   int x: x position of the mouse
	   int y: y position of the mouse
@return nada
@warning
**/
void CMouse::press(MouseKeyType Mousekey, int x, int y){
	if(Mousekey != Invalid) {
	Debug::debug(Debug::input,__FUNCTION__) << "Mousekeytype: "<< Mousekey <<endl;
   	keyState[Mousekey].Mousekey = Mousekey;
    keyState[Mousekey].enabled = true;
    keyState[Mousekey].x = x;
	keyState[Mousekey].y = y;
	if (enableBuffer){
        buffer.push_back(keyState[Mousekey]);
     }
   }
    /*
    Event data(Mousekey, true);
    for (vector<Observer>::iterator it = observers.begin(); it != observers.end(); it++){
        Observer observer = (*it);
        observer.callback(data, observer.extra);
    }
    */
}
/** @fn CMouse::release(MouseKeyType Mousekey)
@brief habilita a tecla pressionada e a coloca no  buffer
@param int Mousekey: o índice da tecla que que foi pressionada
	   int x: x position of the mouse
	   int y: y position of the mouse
@return nada
@warning
**/
void CMouse::release(MouseKeyType Mousekey,int x, int y){
	if(Mousekey != Invalid) {
	Debug::debug(Debug::input,__FUNCTION__) << "Mousekeytype: "<< Mousekey <<endl;

    keyState[Mousekey].enabled = false;
     if (enableBuffer){
		 buffer.push_back(keyState[Mousekey]);
	 }
	}
	 keyState[Mousekey].x = x;
	 keyState[Mousekey].y = y;
    /*
    Event data(Mousekey, 0, false);
    for (vector<Observer>::iterator it = observers.begin(); it != observers.end(); it++){
        Observer observer = (*it);
        observer.callback(data, observer.extra);
    }
    */
}

void CMouse::wheelMoved(signed int x,signed int y){

	Debug::debug(Debug::input,__FUNCTION__) << " Wheel Moved x: "<< x << "  Wheel Moved y: "<< y <<endl;
    //MouseMoveData *movement = new MouseMoveData(x,y,true,true);
	MouseKeyType Mousekey = Invalid;
	/*
	if (x > 0) {
				Debug::debug(Debug::input,__FUNCTION__) << "Mouse Moved Right "<< endl;
				//movement->movedRight=true;
				Mousekey = key_MoveRIGHT;
				keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
				//	buffer.push_back(keyState[Mousekey]);
				}
	}			// Virtual keys switched when mouse move



	if (x < 0) {
		Debug::debug(Debug::input,__FUNCTION__) << "Mouse Moved Left "<< endl;
		//movement->movedLeft=true;
		Mousekey = Key_MoveLEFT;
		keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
				//	buffer.push_back(keyState[Mousekey]);
				}
	} */
	if (y > 0) {
		Debug::debug(Debug::input,__FUNCTION__) << "Mouse Wheel Moved Down "<< endl;
		//movement->movedDown=true;
		Mousekey = Key_WDOWN;
		keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
					buffer.push_back(keyState[Mousekey]);
				}
	}
	if (y < 0) {
		Debug::debug(Debug::input,__FUNCTION__) << "Mouse Wheel Moved UP "<< endl;
		//movement->movedUp=true;
		Mousekey = Key_WUP;
		keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
					buffer.push_back(keyState[Mousekey]);
				}
	}





}



 /** @fn CMouse::moved(signed int x, signed int y)
@brief
@param
@return nada
@warning
**/
void CMouse::moved(signed int x, signed int y){
	Debug::debug(Debug::input,__FUNCTION__) << "Move x: "<< x << "  Move y: "<< y <<endl;
    MouseMoveDatatype *movement = new MouseMoveDatatype(x,y,true,true);
	//get the last absolute movement and verify
	//MouseKeyType Mousekey = Invalid;
	if (absolutebuffer.size() > 0) {
	MouseMoveDatatype last = absolutebuffer[absolutebuffer.size() -1];

	if (x > last.position.x) {
				movement->movedRight=true;
	}			// Virtual keys switched when mouse move
	if (x < last.position.x) {
		movement->movedLeft=true;
	}
	if (y > last.position.y) {
		movement->movedDown=true;
	}
	if (y < last.position.y) {
		movement->movedUp=true;
	}
	}

	if (enableBuffer){
		absolutebuffer.push_back(*movement);
    }
	delete movement;
    /*
    Event data(Mousekey, true);
    for (vector<Observer>::iterator it = observers.begin(); it != observers.end(); it++){
        Observer observer = (*it);
        observer.callback(data, observer.extra);
    }
    */
}

 /** @fn CMouse::movedRelative(signed int x, signed int y)
@brief
@param
@return nada
@warning
**/
void CMouse::movedRelative(signed int x, signed int y){
	Debug::debug(Debug::input,__FUNCTION__) << "RelativeMove x: "<< x << "  RelativeMove y: "<< y <<endl;
    MouseMoveData *movement = new MouseMoveData(x,y,true,true);
	MouseKeyType Mousekey = Invalid;

	if (x > 0) {
				Debug::debug(Debug::input,__FUNCTION__) << "Mouse Moved Right "<< endl;
				movement->movedRight=true;
				Mousekey = key_MoveRIGHT;
				keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
					buffer.push_back(keyState[Mousekey]);
				}
	}			// Virtual keys switched when mouse move



	if (x < 0) {
		Debug::debug(Debug::input,__FUNCTION__) << "Mouse Moved Left "<< endl;
		movement->movedLeft=true;
		Mousekey = Key_MoveLEFT;
		keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
					buffer.push_back(keyState[Mousekey]);
				}
	}
	if (y > 0) {
		Debug::debug(Debug::input,__FUNCTION__) << "Mouse Moved Down "<< endl;
		movement->movedDown=true;
		Mousekey = Key_MoveDOWN;
		keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
					buffer.push_back(keyState[Mousekey]);
				}
	}
	if (y < 0) {
		Debug::debug(Debug::input,__FUNCTION__) << "Mouse Moved UP "<< endl;
		movement->movedUp=true;
		Mousekey = Key_MoveUP;
		keyState[Mousekey].Mousekey = Mousekey;
				keyState[Mousekey].enabled = true;

				if (enableBuffer){
					buffer.push_back(keyState[Mousekey]);
				}
	}


	if (enableBuffer){
		relativebuffer.push_back(*movement);
    }
	delete movement;
    /*
    Event data(Mousekey, true);
    for (vector<Observer>::iterator it = observers.begin(); it != observers.end(); it++){
        Observer observer = (*it);
        observer.callback(data, observer.extra);
    }
    */
}

int CMouse::getXposition() {
	//vector<MouseMoveDatatype>::iterator it=absolutebuffer.begin();
	if(absolutebuffer.size() >0)
		{
			return absolutebuffer.back().position.x;

	}
	//for(it=relativebuffer.begin(); it <= relativebuffer.end(); it++){
	//	delete (*it);
	//}

}
int CMouse::getYposition() {
	if(absolutebuffer.size() >0)
		{
			return absolutebuffer.back().position.y;

	}
}


void CMouse::readMouseBufferedKeys(vector<MouseKeyType> & keys){
    for (vector<Event>::iterator it = buffer.begin(); it != buffer.end(); it++){
        const Event & data = *it;
        keys.push_back(data.Mousekey);
    }
}

vector<CMouse::Event> CMouse::readData(){
    vector<CMouse::Event> out;
    for (map<MouseKeyType, Event>::iterator it = keyState.begin(); it != keyState.end(); it++){
       // MouseKeyType Mousekey = it->first;
        const Event & data = it->second;
        if (data.enabled){
            out.push_back(data);
        }
    }
    return out;
}

vector<CMouse::MouseMoveDatatype> CMouse::readPositionData(){
    vector<CMouse::MouseMoveDatatype> out;
    for (vector<CMouse::MouseMoveDatatype>::iterator it = absolutebuffer.begin(); it != absolutebuffer.end(); it++){
        const MouseMoveDatatype data= (*it);

        if (data.enabled){
            out.push_back(data);
        }
    }
    return out;
}
vector<CMouse::MouseMoveDatatype> CMouse::readPositionRelativeData(){
    vector<CMouse::MouseMoveDatatype> out;
    for (vector<CMouse::MouseMoveDatatype>::iterator it = relativebuffer.begin(); it != absolutebuffer.end(); it++){
        const MouseMoveDatatype data= (*it);

        if (data.enabled){
            out.push_back(data);
        }
    }
    return out;
}

} //end SGF