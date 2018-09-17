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
#ifndef _S_G_F_chat_client_h
#define _S_G_F_chat_client_h


#include <queue>
#include "../SGF_Config.h"
#include "SGF_Network.h"
#include "../util/SGF_Messages.h"
#include <string>
#include "../util/SGF_Thread.h"
#include "../input/all.h"

using namespace std;
namespace SGF{


class CKeyboard;
class CBitmap;

namespace Gui{
    class CLineEdit;
}
class keys;

struct Buddy{
	string name;
	int id;
};

class  SGE_API CChatClient{
public:
	CChatClient( Network::Socket socket, const string & name );

	void run();

	virtual ~CChatClient();

	inline Network::Socket getSocket(){
		return socket;
	}
	
	void addMessage( const string & s, unsigned int id );
	void removeBuddy( int id );
	void changeName( int id, const string & s );
	void addBuddy( int id, const string & s );
	void finish();
	bool isFinished();

protected:
	void killInputThread();
	bool logic();
	Network::Focus nextFocus( Network::Focus f );
	bool needToDraw();
	void draw( const CBitmap & bitmap );
	void needUpdate();
	void drawInputBox( int x, int y, const CBitmap & work );
	void drawBuddies( const CBitmap & area, int x, int y, const CFont & f );
	bool sendMessage( const string & message );
	static void popup(const CBitmap & work, const string & str );

        static void enter_pressed(void * self);
        static void next_focus(void * self);

private:
    CBitmap * background;
	bool need_update;
	::SGF::Messages::CMessages messages;
	Network::Socket socket;
	string input;
	Network::Focus focus;
    ::SGF::Util::Thread::Lock lock;
    ::SGF::Util::Thread::ThreadId_t inputThread;
	vector< Buddy > buddies;
	bool finished;
    Gui::CLineEdit * lineEdit;
	unsigned long long editCounter;
	bool enterPressed;
    ::std::queue<string> toSend;
};
} //end SGF
#endif
