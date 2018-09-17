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
#ifndef _Mouse_h
#define _Mouse_h

#include <map>
#include <vector>
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"
#include "SGF_StructsInput.h"
#include "../util/SGF_Thread.h"
namespace SGF{

/**
 * \class CMoude
 *
 * \ingroup SGF_Input
 *
 * \brief Tratamento do Mouse
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CMouse {
public:

	enum Key{
		MIN = -1,
		Invalid = MIN,
		Key_LEFT = SDL_BUTTON_LEFT,
		Key_MIDDLE = SDL_BUTTON_MIDDLE,   // 2  WhellButton
		Key_RIGHT = SDL_BUTTON_RIGHT,
		Key_WUP = SDL_BUTTON_X1, //   Forward
		Key_WDOWN = SDL_BUTTON_X2, //   Backward
		Key_MoveUP,			// Virtual keys switched when mouse move
		Key_MoveDOWN,
		Key_MoveLEFT,
		key_MoveRIGHT,
		MAX = key_MoveRIGHT
    };
	friend class CInputManager;
    typedef Key MouseKeyType;
	typedef MouseMoveData MouseMoveDatatype;
	/** cria um objeto da Classse CMouse */
    static CMouse * create();

	//!Equicale a joystick Event e keyboard Event
    struct Event{
        Event():
        Mousekey(Invalid),
		enabled(false){
        }

        Event(MouseKeyType Mousekey, bool enabled):
        Mousekey(Mousekey),
        enabled(enabled){
        }

        MouseKeyType Mousekey;  // the code of the pessed key
        int x; //! mouse x position
		int y; //!mouse y position
		/* whether the Mousekey is being pressed */
        bool enabled;
    };



	CMouse();
	~CMouse();
    MOUSEDATA PlayerMouseKeys;  // compatibility to oldmugem


	/** Limpa os buffers internos de eventos
	* a coleta de novos eventos é feita pela classe keyboard
	*/
	void poll();
	/** Este método trata o Mouse quando seguramos o botão por um tempo longo
	* armazena o delay das teclas pressionadas
	*/
    void HandleMouseRepeating();
	void HandleMouseRepeating(MOUSEDATA *lpMouse);
	/* wait for all keys to be released */
	void wait();
	/* []:
	 * Extract a boolean value given a Mousekey number
	 */
#if 0
	inline bool operator[] ( const int i ){

		/* if the Mousekey has been pressed for the first time return true */
		if ( my_mousekeys[ i ] < 0 ){
			my_mousekeys[ i ] = 1;
			return true;
		}

		bool b = my_mousekeys[ i ] > key_delay[ i ];
		if ( b ){
			my_mousekeys[ i ] = 1;
		}
		return b;
	}
#endif
	/* mousekeypressed:
	 * Returns true if a Mousekey is pressed
	 */
	bool mousekeypressed();

	/* readMouseKeys:
	 * Store all pressed Mouse keys in a user supplied vector
	 */
	void readMouseKeys( vector< MouseKeyType > & all_keys );
	static int readMouseKey();
	void readMouseBufferedKeys(vector<MouseKeyType> & keys);
    vector<Event> readData();
	vector<MouseMoveDatatype> readPositionData();
	vector<MouseMoveDatatype> readPositionRelativeData();
    void clear();

	void setDelay( const int Mousekey, const int delay );
	void setAllDelay( const int delay );
    inline const vector<Event> & getBufferedMouseKeys() const {
        return buffer;
    }

	inline const vector<MouseMoveDatatype> & getBufferedMouseAbsolutePositions() const {
        return absolutebuffer;
    }

	inline const vector<MouseMoveDatatype> & getBufferedMouseRelativePositions() const {
        return relativebuffer;
    }
	static const char * keyToName( int Mousekey );

	void press(MouseKeyType Mousekey, int x, int y);  //Verificar a conversão de int para MouseKeyType
    void release(MouseKeyType Mousekey, int x , int y); //registra uma tecla do mouse que foi foi solta
	void moved(signed int x, signed int y); // registra o movimento do mouse vindo via exemplo
    void movedRelative(signed int x, signed int y); // registra o movimento do mouse vindo via exemplo
	void wheelMoved(signed int x,signed int y);
	int getXposition();
	int getYposition();
/*
    virtual void addObserver(ObserverCallback observer, void * extra);
    virtual void removeObserver(ObserverCallback observer, void * extra);
    */
	void Lock() { mouseLock.acquire();}
	void Unlock() { mouseLock.release();}
protected:
	Util::Thread::LockObject mouseLock;
	//map<int,int> my_mousekeys;   //!mapa indexado por codigo de botao
	map<int,int> key_delay;  //! mapa indexado por código de botão que computa o delay de pressionamento das eclas do mouse
	map<MouseKeyType, Event> keyState;
	vector<Event> buffer; // armazena as últimas teclas do mouse e seus estados
	vector<MouseMoveDatatype> absolutebuffer; //armazena as últimas movimentações do mouse
	vector<MouseMoveDatatype> relativebuffer; //armazena as últimas movimentações do mouse
	bool enableBuffer;
	void clearAbsoluteBuffer();
	void clearRelativeBuffer();
	void clearBuffer();
};
} //end SGF
#endif
