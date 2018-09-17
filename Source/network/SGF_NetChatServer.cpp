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


#ifdef HAVE_NETWORKING

#include "graphics/all.h"
#include "network/SGF_Network.h"
#include "input/all.h"
#include "network/SGF_NetChatServer.h"
#include "network/SGF_NetChat.h"
#include "util/SGF_Util.h"
#include "util/SGF_FontSystem.h"
#include "util/SGF_FileSystem.h"
#include "exceptions/all.h"
#include "gui/all.h"
#include "util/SGF_Timer.h"
#include <iostream>
#include <sstream>
#include "resource/all.h"
#include "util/SGF_AudioSystem.h"

#include <signal.h>

using namespace std;
namespace SGF {

CNetClient::CNetClient( Network::Socket socket, CChatServer * server, unsigned int id ):
socket(socket),
server(server),
id(id),
alive(true),
started(false){
}

CNetClient::~CNetClient(){
}

string CNetClient::getName(){
    string s;
    lock.acquire();
    s = name;
    lock.release();
    return s;
}

void CNetClient::kill(){
    lock.acquire();
    alive = false;
    lock.release();
}

bool CNetClient::isAlive(){
    bool b;
    lock.acquire();
    b = alive;
    lock.release();
    return b;
}

void CNetClient::setName( const string & s ){
    lock.acquire();
    name = s;
    lock.release();
}

static void * clientInput( void * client_ ){
    CNetClient * client = (CNetClient *) client_;
    bool done = false;
    bool error = false;
    while ( ! done ){
        try{
            Debug::debug(Debug::network, __FUNCTION__) << "Client " << client->getId() << " waiting for message" << endl;
            Network::Message message( client->getSocket() );
            Debug::debug(Debug::network, __FUNCTION__) << client->getId() << " Got a message: '" << message.path << "'" << endl;
            int type;
            message >> type;
            switch (type){
                case CHANGE_NAME : {
                    message << client->getId();
                    client->getServer()->sendMessage( message, client->getId() );
                    client->setName( message.path );
                    client->getServer()->needUpdate();
                    break;
                }
                case ADD_MESSAGE : {
                    client->getServer()->addMessage( client->getName() + ":" + message.path, client->getId() );
                    break;
                }
                case OK_TO_START : {
                    client->setOk();
                    done = true;
                    break;
                }
            }
            // done = ! client->isAlive();
            Util::rest(1);
        } catch ( const Exception::CNetworkException & e ){
            Debug::debug(Debug::error,__FUNCTION__) << "Client input " << client->getId() << " died" << endl;
            done = true;
            error = true;
        }
    }

    Debug::debug(Debug::network, __FUNCTION__) << client->getId() << " is done" << endl;

    // if ( client->canKill() ){
    // }
    if (error){
        Debug::debug(Debug::network, __FUNCTION__) << "Input thread killing client" << endl;
        client->getServer()->killClient( client );
    }

    return NULL;
}

static void * clientOutput( void * client_ ){
    CNetClient * client = (CNetClient *) client_;
    bool done = false;
    bool error = false;
    while ( ! done ){
        Network::Message message;
        done = ! client->isAlive();
        if ( client->getOutgoing( message ) != false ){
            Debug::debug(Debug::network, __FUNCTION__) << "Sending a message to " << client->getId() << endl;
            try{
                /*
                   Network::Message net;
                   net.path = message;
                   net.send( client->getSocket() );
                   */
                message.send( client->getSocket() );
                Debug::debug(Debug::network, __FUNCTION__) << "Sent a message to " << client->getId() << endl;
            } catch ( const Exception::CNetworkException & e ){
                Debug::debug(Debug::error, __FUNCTION__) << "Client output " << client->getId() << " died" << endl;
                done = true;
                error = true;
            }
        } else {
            Util::rest( 1 );
        }
    }

    Debug::debug(Debug::network, __FUNCTION__) << "Output thread for client " << client->getId() << " is done" << endl;

    if (error){
        Debug::debug(Debug::network, __FUNCTION__) << "Output thread killing client" << endl;
        client->getServer()->killClient( client );
    }

    return NULL;
}

bool CNetClient::canKill(){
    bool f;
    lock.acquire();
    f = alive;
    /* why set alive to false here?
     * it was supposed to check if the client was already dead.
     */
    alive = false;
    lock.release();
    return f;
}

bool CNetClient::getOutgoing(Network::Message & m){
    bool has;
    lock.acquire();
    has = ! outgoing.empty();
    if (has){
        m = outgoing.front();
        outgoing.erase(outgoing.begin());
    }
    lock.release();
    return has;
}

void CNetClient::addOutputMessage(const Network::Message & s){
    lock.acquire();
    outgoing.push_back(s);
    lock.release();
}

void CNetClient::startThreads(){
    lock.acquire();
    if (! started){
        Util::Thread::createThread(&inputThread, NULL, (Util::Thread::ThreadFunction) clientInput, this);
        Util::Thread::createThread(&outputThread, NULL, (Util::Thread::ThreadFunction) clientOutput, this);
        started = true;
    }
    lock.release();
}

struct do_add_stuff{
    do_add_stuff(CChatServer * server, Network::Socket socket):
    server(server), socket(socket){
    }

    CChatServer * server;
    Network::Socket socket;
};

static void kill_socket(void * arg){
    Network::Socket socket = *(Network::Socket *) arg;
	Network::closeSocket(socket);
}

static void * do_add(void * stuff_){
    do_add_stuff * stuff = (do_add_stuff *) stuff_;
    CChatServer * server = stuff->server;
    Network::Socket socket = stuff->socket;
    /* client has 5 seconds to perform the handshake */
    Util::CTimer fail(5, &kill_socket, &socket);
    /* there is a very unlikely chance that addConnection will be processing
     * the client while the timer expires. A normal scenario is:
     *  1. client connects
     *  2. client sends HELLO
     *  3. server sends ADD_BUDDY messages to the clients (by putting the
     *    messages into queues)
     *  4. server stores the client in internal datastructures
     *
     * After the client sends the HELLO the other steps should be fast, like
     * a few microseconds at the most. So if the client takes 4.9999 seconds
     * to send HELLO then 5 seconds could expire during step 3 or something.
     *
     * This is so remote I don't care about fixing it at the moment. A possible
     * fix is to do everything after step 2 outside of the timer so that
     * if the client sends a HELLO then the server can take its time doing
     * the rest of the processing.
     */
    try{
        /* if the timer expires the socket will close and send a NetworkException */
        server->addConnection(socket);
        /* the timer could also expire right *here* and then things would break */
        fail.stop();
    } catch ( const Exception::CNetworkException & e ){
        Debug::debug(Debug::error,__FUNCTION__) << "Timer expired while processing client! Client dropped." << endl;
    }

    delete stuff;

    return NULL;
}

static void * acceptConnections( void * server_ ){
    bool done = false;
    CChatServer * server = (CChatServer *) server_;
    Network::Socket socket = server->getSocket();
    Debug::debug(Debug::network, __FUNCTION__) << "Accepting connections" << endl;
    while (! done){
        done = ! server->isAccepting();
        try{
            /* start the accepting handshake in a thread in case
             * the client dies or has an invalid version.
             */
			Network::Socket client = Network::acceptConnections(socket);
            Util::Thread::ThreadId_t accepter;
            do_add_stuff * stuff = new do_add_stuff(server, client);
            Util::Thread::createThread(&accepter, NULL, (Util::Thread::ThreadFunction) do_add, stuff);
            server->addAccepter(accepter);
            // server->addConnection(client);
        } catch ( const Exception::CNoConnectionsPendingException & e ){
        } catch ( const Exception::CNetworkException & e ){
            Debug::debug(Debug::error,__FUNCTION__) << "Error accepting connections: " << e.getMessage() << endl;
            done = true;
        }
        Util::rest(1);
    }

#ifdef _WIN32
    Network::closeSocket( socket );
#endif

    Debug::debug(Debug::network, __FUNCTION__)  << "Accept connection thread is done" << endl;

    return NULL;
}

/*
static void enter_pressed(void * self){
    CChatServer * chat = (CChatServer *) self;
    chat->addLine();
}
*/

static const char * welcomeMessage(){
    switch (Util::rnd(5)){
        case 0: return "Hi!";
        case 1: return "Hey!";
        case 2: return "What's up?";
        case 3: return "Cool!";
        case 4: return "Rockin!";
        default: return "Hi!";
    }
}

CChatServer::CChatServer(const string & name, Network::Socket socket):
need_update(true),
socket(socket),
messages(400, 350),
client_id(1),
name(name),
accepting(true){
    background = new CBitmap(CConfiguration::gameTitleScreen.getString());
	
    Debug::debug(Debug::network, __FUNCTION__) << "Start accepting connections" << endl;

    // editCounter = 0;

    /* listen() may throw an exception, so call it here so that the destructor
     * can properly delete the other objects that were created.
     */
    Debug::debug(Debug::network, __FUNCTION__) << "Listen on socket" << endl;
    Network::enableListen(socket);
}

void CChatServer::addLine(Gui::CLineEdit & line){
    if (line.getText().size() > 0){
        addMessage(name + ": " + line.getText(), 0);
        line.clearText();
        needUpdate();
    }
}

bool CChatServer::isAccepting(){
    bool f = false;
    lock.acquire();
    f = accepting;
    lock.release();
    return f;
}

void CChatServer::addAccepter(Util::Thread::ThreadId_t accepter){
    lock.acquire();
    accepted.push_back(accepter);
    lock.release();
}

void CChatServer::stopAccepting(){
    Debug::debug(Debug::network, __FUNCTION__) << "Stop accepting" << endl;
    lock.acquire();
    accepting = false;
    lock.release();
    // #ifndef WINDOWS
	Network::closeSocket(socket);
    // #endif
    Debug::debug(Debug::network, __FUNCTION__) << "Waiting for client accept threads to stop" << endl;
    lock.acquire();
    for (vector<Util::Thread::ThreadId_t>::iterator it = accepted.begin(); it != accepted.end(); it++){
        Util::Thread::ThreadId_t accept = *it;
        Debug::debug(Debug::network, __FUNCTION__) << "Waiting for client accept thread " << endl;
        Util::Thread::joinThread(accept);
    }
    lock.release();
    Debug::debug(Debug::network, __FUNCTION__) << "Waiting for accepting thread to stop" << endl;
    Util::Thread::joinThread(acceptThread);
    Debug::debug(Debug::network, __FUNCTION__) << "Not accepting any connections" << endl;
}

void CChatServer::addConnection(Network::Socket s){
    CNetClient * client = new CNetClient(s, this, clientId());

    /* the client should send a hello message to us immediately */
    try{
        Network::Message hello(s);
        int type;
        hello >> type;
        if (type != HELLO){
            ostringstream out;
            out << "Client sent something other than a HELLO: " << type;
            throw CLoadException(__FILE__, __LINE__, out.str());
        }
        unsigned int magic;
        hello >> magic;
        if (magic != Global::MagicId){
            ostringstream out;
            out << "Invalid magic id: " << magic;
            throw CLoadException(__FILE__, __LINE__, out.str());
        }
        int version;
        hello >> version;
        if (! Util::checkVersion(version)){
            ostringstream out;
            out << "Invalid version: " << version;
            throw CLoadException(__FILE__, __LINE__, out.str());
        }
        string name;
        name = hello.path;
        client->setName(name);
    } catch (const Exception::CNetworkException & e){
        delete client;
        throw e;
    } catch (const CLoadException & e){
        delete client;
        Debug::debug(Debug::error,__FUNCTION__) << "Dropping connection: " << e.getTrace() << endl;
        return;
    }

    /* send the server name to the just connected client */
    {
        Network::Message message;
        message << ADD_BUDDY;
        message << 0;
        message.path = getName();
        client->addOutputMessage(message);
    }

    /* send all the other client names to the just connected client */
    lock.acquire();
    for ( vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++ ){
        CNetClient * c = *it;
        Network::Message message;
        message << ADD_BUDDY;
        message << c->getId();
        message.path = c->getName();
        client->addOutputMessage( message );
    }
    lock.release();

    Debug::debug(Debug::network, __FUNCTION__) << "Adding client " << client->getId() << endl;

    /* don't know the name of the client yet. the client will send
     * a CHANGE_NAME packet very soon.
     */
    addMessage(string("** Client ") + client->getName() + " joined", 0);

    Network::Message message;
    message << ADD_BUDDY;
    message << client->getId();
    message << client->getName();
    sendMessage(message, 0);

    lock.acquire();
    clients.push_back(client);
    lock.release();

    CResource::getSound(Filesystem::CRelativePath("menu/sounds/chip-in.wav"))->play();
}

#if 0
static char lowerCase( const char * x ){
	if ( x[0] >= 'A' && x[0] <= 'Z' ){
		return x[0] - 'A' + 'a';
	}
	return x[0];
}
#endif

void CChatServer::sendMessageNow(const Network::Message & message, unsigned int id){
    lock.acquire();
    for (vector<CNetClient *>::iterator it = clients.begin(); it != clients.end(); it++){
        CNetClient * c = *it;
        if (c->getId() != id){
            message.send(c->getSocket());
        }
    }
    lock.release();
}

void CChatServer::sendMessage( const Network::Message & message, unsigned int id ){
    lock.acquire();
    for ( vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++ ){
        CNetClient * c = *it;
        if ( c->getId() != id ){
            c->addOutputMessage( message );
        }
    }
    lock.release();
}

void CChatServer::addMessage(const string & s, unsigned int id){
    Network::Message message;
    message << ADD_MESSAGE;
    message.path = s;
    lock.acquire();
    messages.addMessage(s);
    needUpdate();
    lock.release();

    sendMessage(message, id);
    /*
       for ( vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++ ){
       CNetClient * c = *it;
       if ( c->getId() != id ){
       c->addOutputMessage( message );
       }
       }
       */
}

void CChatServer::shutdownClientThreads(){
    Debug::debug(Debug::network, __FUNCTION__) << "Shutting down client threads" << endl;

    /* end the output threads */
    lock.acquire();
    for ( vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++ ){
        CNetClient * c = *it;
        c->kill();
        Util::Thread::joinThread(c->getOutputThread());
    }
    lock.release();

    /* tell clients that the game is starting */
    Network::Message message;
    message << START_THE_GAME;
    sendMessageNow(message, 0);

    /* wait for clients to finish processing. clients should receive START_THE_GAME
     * then send back OK_TO_START and then finish.
     */
    for (vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++){
        CNetClient * c = *it;
        Debug::debug(Debug::network, __FUNCTION__) << "Waiting for client " << c->getId() << " to finish input/output threads" << endl;
        Util::Thread::joinThread(c->getInputThread());
        Debug::debug(Debug::network, __FUNCTION__) << "Input thread done for " << c->getId() << endl;
        // Debug::debug(Debug::network, __FUNCTION__) << "Output thread done for " << c->getId() << endl;
        Debug::debug(Debug::network, __FUNCTION__) << "Client " << c->getId() << " is done" << endl;
    }

    Debug::debug(Debug::network, __FUNCTION__) << "Shut down all clients" << endl;
}

vector<CNetClient*> CChatServer::getConnectedClients(){
    vector<CNetClient*> out;

    for (vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++){
        CNetClient * c = *it;
        if (c->isOk()){
            out.push_back(c);
        }
    }

    return out;
}

void CChatServer::killAllClients(){
    vector< CNetClient * > all;
    lock.acquire();
    all = clients;
    lock.release();
    for ( vector< CNetClient * >::iterator it = all.begin(); it != all.end(); it++ ){
        killClient( *it );
    }
}

void CChatServer::killClient(CNetClient * c){
    int id = c->getId();
    string name = c->getName();
    lock.acquire();
    for ( vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); ){
        CNetClient * client = *it;
        if ( client == c ){
            Debug::debug(Debug::network, __FUNCTION__) << "Killing client " << c->getId() << endl;
            c->kill();
            Debug::debug(Debug::network, __FUNCTION__) << "Closing client socket " << c->getSocket() << endl;
			Network::closeSocket( c->getSocket() );
            /* It looks like the client that called killClient is waiting
             * for itself to exit but pthread_join won't block if the
             * argument is the same as the calling thread, so its ok.
             * TODO: ensure this semantics works with SDL threads too
             */
            Debug::debug(Debug::network, __FUNCTION__) << "Waiting for input thread to die" << endl;
            Util::Thread::joinThread(c->getInputThread());
            Debug::debug(Debug::network, __FUNCTION__) << "Waiting for output thread to die" << endl;
            Util::Thread::joinThread(c->getOutputThread());
            Debug::debug(Debug::network, __FUNCTION__) << "Deleting client" << endl;
            /* delete can be moved to the input/output thread exit part
             * if need be.
             */
            delete client;
            it = clients.erase( it );
        } else {
            it++;
        }
    }
    needUpdate();
    lock.release();
    addMessage("** " + name + " quit", 0);
    CResource::getSound(Filesystem::CRelativePath("menu/sounds/chip-out.wav"))->play();
    Network::Message remove;
    remove << REMOVE_BUDDY;
    remove << id;
    sendMessage(remove, 0);
}

bool CChatServer::logic(){
    /*
    const Font & font = Font::getFont(string(Global::DEFAULT_FONT), 20, 20);
    lineEdit->act(font);
    if (lineEdit->didChanged(editCounter)){
        needUpdate();
    }
    */

#if 0
    if (keyboard[Keyboard::Key_TAB]){
        focus = nextFocus( focus );
        needUpdate();
    }

    keyInputManager::update();
    /*
       lineEdit->setFont(Menu::getFont()); lineEdit->logic();
       */

    lineEdit->setFocused(false);
    switch (focus){
        case INPUT_BOX : {
            lineEdit->setFocused(true);
            handleInput( keyboard );
            // handleInput( keyboard );
            lineEdit->colors.border = Bitmap::makeColor(255,255,0);
            break;
        }
        case START_GAME : {
            if ( keyboard[ Keyboard::Key_ENTER ] ){
                return true;
            }
            lineEdit->colors.border = Bitmap::makeColor(255,255,255);
            break;
        }
        case QUIT : {
            if ( keyboard[ Keyboard::Key_ENTER ] ){
                return true;
            }
            lineEdit->colors.border = Bitmap::makeColor(255,255,255);
            break;
        }
    }
#endif

    return false;
}

void CChatServer::needUpdate(){
    need_update = true;
}

Network::Focus CChatServer::nextFocus(Network::Focus f){
    switch (f){
        case Network::INPUT_BOX: return Network::START_GAME;
        case Network::START_GAME: return Network::QUIT;
        case Network::QUIT: return Network::INPUT_BOX;
        default : return Network::INPUT_BOX;
    }
}

bool CChatServer::needToDraw(){
    return need_update;
}

/*
void CChatServer::drawInputBox(int x, int y, const Graphics::Bitmap & work){
    const Font & font = Font::getFont(string(Global::DEFAULT_FONT), 20, 20 );

    // work.drawingMode( Bitmap::MODE_TRANS );
    Graphics::Bitmap::transBlender( 0, 0, 0, 128 );
    work.translucent().rectangleFill( x, y, x + messages.getWidth(), y + font.getHeight() + 1, Graphics::makeColor( 0, 0, 0 ) );
    // work.drawingMode( Bitmap::MODE_SOLID );
    int color = Graphics::makeColor(255, 255, 255);
    if (focus == INPUT_BOX){
        color = Graphics::makeColor(255, 255, 0);
    }
    work.rectangle(x, y, x + messages.getWidth(), y + font.getHeight(), color);
    Graphics::Bitmap input_box( work, x + 1, y, messages.getWidth(), font.getHeight() );
    // font.printf( x + 1, y, Bitmap::makeColor( 255, 255, 255 ), work, input, 0 );
    // font.printf( 0, 0, Bitmap::makeColor( 255, 255, 255 ), input_box, input, 0 );
}
*/

void CChatServer::drawBuddyList( int x, int y, const CBitmap & work, const CFont & font ){
	CBitmap buddyList( work, x, y, CConfiguration::screenWidth.getInteger() - x - 5, 200 );
    // buddyList.drawingMode( Bitmap::MODE_TRANS );
    CBitmap::transBlender( 0, 0, 0, 128 );
    buddyList.translucent().rectangleFill( 0, 0, buddyList.getWidth(), buddyList.getHeight(), Colors::Transparent );
    // buddyList.drawingMode( Bitmap::MODE_SOLID );
    buddyList.polygon().rectangle( 0, 0, buddyList.getWidth() -1, buddyList.getHeight() - 1, Colors::White );
    int fy = 1;
    for ( vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++ ){
        CNetClient * client = *it;
        const string & name = client->getName();
		font.drawText( 1, fy, Colors::White, buddyList, name.c_str(), 0 );
        fy += font.getHeight();
    }
}

static Colors::ColorDefinition focusColor(Network::Focus want, Network::Focus now){
    if (want == now){
        return Colors::Yellow ;
    }
    return Colors::White;
}

void CChatServer::draw(const CBitmap & work, Gui::CLineEdit & lineEdit, Network::Focus focus){
    int start_x = 20;
    int start_y = 20;
    const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20);
    background->BlitSurface(work);
    messages.draw(start_x, start_y, work, font);

    // drawInputBox( start_x, start_y + messages.getHeight() + 5, work );

    drawBuddyList(start_x + messages.getWidth() + 10, start_y, work, font);

    font.drawText(start_x, start_y + messages.getHeight() + 5 + font.getHeight() * 2 + 5, focusColor(Network::START_GAME, focus), work, "Start the game", 0);
    font.drawText(start_x + font.getTextLength("Start the game") + 20, start_y + messages.getHeight() + 5 + font.getHeight() * 2 + 5, focusColor(Network::QUIT, focus), work, "Quit", 0);

    lineEdit.render(work);

    need_update = false;
}

void CChatServer::startThreadsHack(){
    lock.acquire();
    for (vector< CNetClient * >::iterator it = clients.begin(); it != clients.end(); it++){
        CNetClient * c = *it;
        c->startThreads();
    }
    lock.release();
}

static void set_to_true(void * b){
    bool * what = (bool *) b;
    *what = true;
}

/*
void CChatServer::next_focus(void * self){
    CChatServer * chat = (CChatServer*) self;
    chat->focus = chat->nextFocus(chat->focus);
    chat->lineEdit->setFocused(chat->focus == INPUT_BOX);
    if (chat->focus == INPUT_BOX){
        chat->lineEdit->colors.border = Graphics::makeColor(255,255,0);
    } else {
        chat->lineEdit->colors.border = Graphics::makeColor(255,255,255);
    }
    chat->needUpdate();
}
*/

void CChatServer::run(){
    // Global::speed_counter2 = 0;
    Util::Thread::createThread(&acceptThread, NULL, (Util::Thread::ThreadFunction) acceptConnections, this);

    Gui::CLineEdit lineEdit;
    lineEdit.location.setPosition(Gui::CAbsolutePoint(20, 20 + messages.getHeight() + 5));
    lineEdit.location.setDimensions(400, 30);
    lineEdit.transforms.setRadius(5);

	lineEdit.colors.body = Colors::Transparent;
    lineEdit.colors.body.a = 128;
	lineEdit.colors.border = Colors::Yellow;
    lineEdit.setHorizontalAlign(Gui::CLineEdit::T_Left);
    lineEdit.setTextColor( Colors::White );

    lineEdit.setText(welcomeMessage());
    // lineEdit->setFont(Menu::getFont());
    lineEdit.setFont(& CFont::getFont(string(Global::DEFAULT_FONT), 20, 20));
    lineEdit.setFocused(true);

    class Logic: public Input::CLogic {
    public:
        Logic(Gui::CLineEdit & lineEdit, CChatServer & server, Network::Focus & focus):
        editCounter(0),
        forceQuit(false),
        lineEdit(lineEdit),
        focus(focus),
        is_done(false),
        server(server){
            input.set(CKeyboard::Key_TAB, 0, true, 0);
            input.set(CKeyboard::Key_ENTER, 0, true, 1);
            input.set(CKeyboard::Key_ESC, 0, true, 2);
            lineEdit.hookKey(CKeyboard::Key_ENTER, enter_pressed, this);
            lineEdit.hookKey(CKeyboard::Key_ESC, set_to_true, &forceQuit);
            lineEdit.hookKey(CKeyboard::Key_TAB, next_focus, this);
        }

        CInputMap<int> input;
        unsigned long long editCounter;
        bool forceQuit;
        Gui::CLineEdit & lineEdit;
        Network::Focus & focus;
        bool is_done;
        CChatServer & server;

        double ticks(double system){
            return system;
        }

        static void enter_pressed(void * self){
            Logic * logic = (Logic*) self;
            logic->server.addLine(logic->lineEdit);
        }

        static Network::Focus nextFocus(Network::Focus f){
            switch (f){
                case Network::INPUT_BOX: return Network::START_GAME;
                case Network::START_GAME: return Network::QUIT;
                case Network::QUIT: return Network::INPUT_BOX;
                default : return Network::INPUT_BOX;
            }
        }

        static void next_focus(void * self){
            Logic * logic = (Logic*) self;
            logic->focus = nextFocus(logic->focus);
            logic->lineEdit.setFocused(logic->focus == Network::INPUT_BOX);
            if (logic->focus == Network::INPUT_BOX){
				logic->lineEdit.colors.border = Colors::Yellow;
            } else {
                logic->lineEdit.colors.border = Colors::White;
            }
            logic->server.needUpdate();
        }

        void startGame(){
            server.stopAccepting();
            Debug::debug(Debug::network, __FUNCTION__) << "Shut down client threads" << endl;
            server.shutdownClientThreads();
            Debug::debug(Debug::network, __FUNCTION__) << "Finished shutting things down" << endl;
            is_done = true;
        }

        void doQuit(){
            server.addMessage("** Server quit", 0);
            server.stopAccepting();
            server.killAllClients();
            is_done = true;
            throw Exception::Return(__FILE__, __LINE__);
        }

        void handleInput(bool inputHadFocus){
            vector<CInputMap<int>::InputEvent> events = CInputManager::getEvents(input);
            bool select = false;
            bool next = false;
            bool quit = false;
            for (vector<CInputMap<int>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
                const CInputMap<int>::InputEvent & event = *it;
                if (!event.enabled){
                    continue;
                }
                next = next || event[0];
                select = select || event[1];
                quit = quit || event[2];
            }

            if (forceQuit || (is_done && focus == Network::QUIT) || quit){
                doQuit();
            }

            if (next && !inputHadFocus){
                next_focus(this);
            }

            if (select){
                switch (focus){
                    case Network::START_GAME: {
                        startGame();
                        break;
                    }
                    case Network::QUIT: {
                        doQuit();
                        break;
                    }
                    case Network::INPUT_BOX: {
                        Debug::debug(Debug::error,__FUNCTION__) << "Shouldn't get here" << endl;
                        throw Exception::Return(__FILE__, __LINE__);
                    }
                }
            }
        }

        void run(int delay=0){
            server.startThreadsHack();

            /* hack to know if the input box had the focus so we don't register
             * the TAB key too many times.
             * if the input box has focus and tab is pressed, the next_focus()
             * function will be executed twice, once due to the input box
             * and once due to the loop below.
             */
            bool inputHadFocus = focus == Network::INPUT_BOX;

            const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20);
            lineEdit.act(font);
            if (lineEdit.didChanged(editCounter)){
                server.needUpdate();
            }

            handleInput(inputHadFocus);
        }

        bool done(){
            return is_done;
        }
    };

    class Draw: public Input::CDraw {
    public:
        Draw(Gui::CLineEdit & lineEdit, CChatServer & server, Network::Focus & focus):
        lineEdit(lineEdit),
        server(server),
        focus(focus){
        }

        Gui::CLineEdit & lineEdit;
        CChatServer & server;
        Network::Focus & focus;

        void draw(double fps){
            if (server.needToDraw()){
                //S server.draw(work, lineEdit, focus);
               //S  work.BlitToScreen();
            }
        }
    };

    Network::Focus focus(Network::INPUT_BOX);
    Logic logic(lineEdit, *this, focus);
    Draw draw(lineEdit, *this, focus);

    needUpdate();
    Input::SGE_standardLoop(logic, draw);

#if 0
    class Release{
    public:
        Release(Gui::LineEdit * line):
        line(line){
        }

        Gui::LineEdit * line;

        ~Release(){
            line->setFocused(false);
        }
    };

    Release release(lineEdit);

    InputMap<int> input;
    input.set(Keyboard::Key_TAB, 0, true, 0);
    input.set(Keyboard::Key_ENTER, 0, true, 1);
    input.set(Keyboard::Key_ESC, 0, true, 2);
    bool forceQuit = false;
    lineEdit->hookKey(Keyboard::Key_ESC, set_to_true, &forceQuit);
    lineEdit->hookKey(Keyboard::Key_TAB, CChatServer::next_focus, this);
    bool done = false;
    while (! done){
        int think = Global::speed_counter2;
        Global::speed_counter2 = 0;
        while (think > 0){
            InputManager::poll();
            /* I forgot why this hack needs to be put inside the main loop.
             * When I remember please explain it here.
             * Possible reason: the client thread can't be started as soon
             * as the client connects (why?) but has to be started at some point.
             * Putting the hack here ensures that the client thread starts at some
             * point but after the server has initialized whatever it needs.
             */
            startThreadsHack();

            /* hack to know if the input box had the focus so we don't register
             * the TAB key too many times.
             * if the input box has focus and tab is pressed, the next_focus()
             * function will be executed twice, once due to the input box
             * and once due to the loop below.
             */
            bool inputHadFocus = focus == INPUT_BOX;

            done = logic();
            think -= 1;

            vector<InputMap<int>::InputEvent> events = InputManager::getEvents(input);
            bool select = false;
            bool next = false;
            bool quit = false;
            for (vector<InputMap<int>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
                const InputMap<int>::InputEvent & event = *it;
                if (!event.enabled){
                    continue;
                }
                next = next || event[0];
                select = select || event[1];
                quit = quit || event[2];
            }

            if (forceQuit || (done && focus == QUIT) || quit){
                addMessage( "** Server quit", 0 );
                stopAccepting();
                killAllClients();
                done = true;
                throw Exception::Return(__FILE__, __LINE__);
            }

            if (next && !inputHadFocus){
                next_focus(this);
            }

            if (select){
                switch (focus){
                    case START_GAME: {
                        stopAccepting();
                        Debug::debug(Debug::network, __FUNCTION__) << "Shut down client threads" << endl;
                        shutdownClientThreads();
                        Debug::debug(Debug::network, __FUNCTION__) << "Finished shutting things down. Done is " << done << endl;
                        done = true;
                        Debug::debug(Debug::network, __FUNCTION__) << "Done is " << done << endl;
                        break;
                    }
                    case QUIT: {
                        addMessage( "** Server quit", 0 );
                        stopAccepting();
                        killAllClients();
                        done = true;
                        throw Exception::Return(__FILE__, __LINE__);
                    }
                    case INPUT_BOX: {
                        Debug::debug(Debug::error,__FUNCTION__) << "Shouldn't get here" << endl;
                        throw Exception::Return(__FILE__, __LINE__);
                    }
                }
            }
        }

        if (needToDraw()){
            draw(work);
            work.BlitToScreen();
            work.clear();
        }

        while (Global::speed_counter2 == 0){
            Util::rest(1);
        }
    }
#endif

    Debug::debug(Debug::network, __FUNCTION__) << "Chat server done" << endl;
}

CChatServer::~CChatServer(){
    // delete background;
    for (vector<CNetClient *>::iterator it = clients.begin(); it != clients.end(); it++){
        delete *it;
    }
    // delete lineEdit;
}
} //end SGF
#endif
