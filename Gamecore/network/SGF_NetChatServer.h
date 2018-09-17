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

#ifndef _S_G_F_chat_server_h
#define _S_G_F_chat_server_h
#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "../network/SGF_Network.h"
#include "../util/SGF_Thread.h"
#include "../util/SGF_Messages.h"
#include "../util/SGF_Pointer.h"


namespace SGF{

namespace Gui{
    class CLineEdit;
}

class CBitmap;

class CKeyboard;



class keys;
class CChatServer;

/**
 * \class CNetClient
 *
 * \ingroup SGF_Network
 * 
 * \brief Classe Cliente de Rede
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 12 de fevereiro de 2012
 */
class  SGE_API CNetClient{
public:
	CNetClient( Network::Socket socket, CChatServer * server, unsigned int id );

	inline unsigned int getId(){
		return id;
	}

	inline Network::Socket getSocket(){
		return socket;
	}
	
	inline CChatServer * getServer(){
		return server;
	}

	inline Util::Thread::ThreadId_t getInputThread(){
		return inputThread;
	}

	inline Util::Thread::ThreadId_t getOutputThread(){
		return outputThread;
	}

	inline void setOk(){
		ok = true;
	}

	inline bool isOk(){
		return ok;
	}

	void kill();
	bool isAlive();
	bool canKill();

	string getName();
	void setName( const string & s );
	
	bool getOutgoing( Network::Message & m );

	void addOutputMessage( const Network::Message & s );

	void startThreads();

	virtual ~CNetClient();
private:

	Network::Socket socket;
	CChatServer * server;
	unsigned int id;
	bool alive;
	/* ok to use this client */
	bool ok;
	bool started;
	string name;
        Util::Thread::ThreadId_t inputThread;
        Util::Thread::ThreadId_t outputThread;
        Util::Thread::LockObject lock;
	vector< Network::Message > outgoing;
};

/**
 * \class CChatServer
 *
 * \ingroup SGF_Network
 * 
 * \brief Implementa um servidor de Chat de Rede
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 12 de fevereiro de 2012
 */
class SGE_API CChatServer{
public:
	CChatServer( const string & name, Network::Socket socket );

	/* run the chat server - accept connections and handle input */
	virtual void run();

	/* add a connection from a client */
	virtual void addConnection( Network::Socket socket );

	Network::Socket getSocket(){
		return socket;
	}

	/** \brief finaliza a conexão 
	* \param c: cliente a ser finalizado
	*/
	void killClient( CNetClient * c );

	/** \brief adiciona uma mensagem na caixa de chat e envia
	* \param s: mensagem a ser enviada
	* \param id: identificador de rede do destinatário
	*/
	void addMessage( const string & s, unsigned int id );
	
	/* send a message from the guy who is identified by id */
	void sendMessage( const Network::Message & message, unsigned int id );

        /* send the message immediately */
        void sendMessageNow(const Network::Message & message, unsigned int id);
	
	/* need to update the screen because a message came through or
	 * the user typed something in the chat box
	 */
	void needUpdate();
		
	/* is accepting connections from clients */
	bool isAccepting();
        
        /* each new client starts an accepting thread */
        void addAccepter(Util::Thread::ThreadId_t accepter);
        
        /* add a message to the chat box */
        void addLine(Gui::CLineEdit & line);

	/* get the list of connected clients */
        vector<CNetClient*> getConnectedClients();

	inline const string getName() const {
		return name;
	}

	virtual ~CChatServer();

protected:
	/* force kill all client threads */
	void killAllClients();

	/* notify clients that the game is about to start */
	void shutdownClientThreads();

	/* do chat logic */
	bool logic();

	/* true if a redraw is needed */
	bool needToDraw();

	/* draw things to work */
	void draw(const CBitmap & work, Gui::CLineEdit & lineEdit, Network::Focus focus);
	
	/* draw the input box */
	// void drawInputBox( int x, int y, const Graphics::Bitmap & work );

	/* draw the buddy list */
	void drawBuddyList( int x, int y, const CBitmap & work, const CFont & font );

	/* get the next widget to be focused */
	Network::Focus nextFocus( Network::Focus f );

	/* get the color a focused widget should be drawn with */
	// int focusColor( Focus f );

	/* stop accepting new connections */
	void stopAccepting();

	/* used to start threads in the run() method instead of elsewhere */
	void startThreadsHack();

	/* return a new connection id */
	inline int clientId(){
		return client_id++;
	}

        // static void next_focus(void * self);
	
protected:
	bool need_update;
	Network::Socket socket;
        Util::CReferenceCount<CBitmap> background;
		Messages::CMessages messages;
	// string input;
	// Focus focus;
	unsigned int client_id;
        Util::Thread::LockObject lock;
        Util::Thread::ThreadId_t acceptThread;
	vector< CNetClient * > clients;
	string name;
	bool accepting;
	// unsigned long long editCounter;
	// bool enterPressed;
        vector<Util::Thread::ThreadId_t> accepted;
        // Gui::LineEdit * lineEdit;
};
} //end SGF
#endif
