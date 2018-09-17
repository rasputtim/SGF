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
#include "../SGF_Config.h"
#include "graphics/all.h"
#include "network/SGF_Network.h"
#include "input/all.h"
#include "network/SGF_NetChatClient.h"
#include "network/SGF_NetChat.h"
#include "util/SGF_FontSystem.h"
#include "util/SGF_Util.h"
#include "util/SGF_FileSystem.h"
#include "gui/SGF_LineEdit.h"
#include "resource/all.h"
#include "util/SGF_AudioSystem.h"

using namespace std;
namespace SGF {
static void * serverInput( void * client_ ){
    CChatClient * client = (CChatClient *) client_;
    bool done = false;
    while ( ! done ){
        try{
            Debug::debug(Debug::network, __FUNCTION__) << "Waiting to receive a message" << endl;
            Network::Message message(client->getSocket());
            int x;
            ChatType kind;
            message >> x;
            kind = (ChatType) x;
            Debug::debug(Debug::network, __FUNCTION__) << "Received message type " << kind << endl;
            switch ( kind ){
                case HELLO : {
                    Debug::debug(Debug::error, __FUNCTION__) << "Client should not see a HELLO message!" << endl;
                    break;
                }
                case ADD_MESSAGE : {
                    client->addMessage( message.path, 0 );
                    break;
                }
                case CHANGE_NAME : {
                    int id;
                    string name;
                    message >> id;
                    name = message.path;
                    client->changeName( id, name );
                    break;
                }
                case REMOVE_BUDDY : {
                    int id;
                    message >> id;
                    client->removeBuddy( id );
                    break;
                }
                case OK_TO_START : {
                    break;
                }
                case START_THE_GAME : {
                    /* shut down threads and prepare to play */
                    done = true;
                    client->finish();
                    break;
                }
                case ADD_BUDDY : {
                    int id;
                    string name;
                    message >> id;
                    name = message.path;
                    client->addBuddy( id, name );
                    break;
                }
            }
        } catch ( const Exception::CNetworkException & e ){
            Debug::debug(Debug::error, __FUNCTION__) << "Input thread died" << endl;
            done = true;
        }
    }

    return NULL;
}

void CChatClient::enter_pressed(void * self){
    CChatClient * chat = (CChatClient*) self;
    if (chat->lineEdit->getText().size() > 0){
        chat->addMessage("You: " + chat->lineEdit->getText(), 0);
        chat->toSend.push(chat->lineEdit->getText());
        chat->lineEdit->clearText();
        chat->needUpdate();
    }
}

CChatClient::CChatClient( Network::Socket socket, const string & name ):
need_update(true),
messages( 400, 300 ),
socket(socket),
focus(INPUT_BOX),
finished(false),
enterPressed( false ){
	background = new CBitmap(CConfiguration::gameTitleScreen.getString());
    Util::Thread::initializeLock(&lock);

    Util::Thread::createThread(&inputThread, NULL, (Util::Thread::ThreadFunction) serverInput, this);

    try{
        Network::Message nameMessage;
        nameMessage.path = name;
        nameMessage << HELLO;
        nameMessage << Global::MagicId;
        nameMessage << Global::getVersion();
        nameMessage.send(socket);
    } catch (const Exception::CNetworkException & n){
        Debug::debug(Debug::error, __FUNCTION__) << "Could not send username: " << n.getMessage() << endl;
    }

    lineEdit = new Gui::CLineEdit();
    lineEdit->location.setPosition(Gui::CAbsolutePoint(20, 20 + messages.getHeight() + 5));
    lineEdit->location.setDimensions(400, 30);
    lineEdit->transforms.setRadius(5);

	lineEdit->colors.body = Colors::Transparent;
    lineEdit->colors.body.a = 128;
    lineEdit->colors.border = Colors::Yellow;
    lineEdit->setHorizontalAlign(Gui::CLineEdit::T_Left);
    lineEdit->setTextColor(Colors::White);

    lineEdit->setText("Hi!");
    // lineEdit->setFont(Menu::getFont());
    lineEdit->setFont(& CFont::getFont(string(Global::DEFAULT_FONT), 20, 20));
    lineEdit->hookKey(CKeyboard::Key_ENTER, enter_pressed, this);
    lineEdit->hookKey(CKeyboard::Key_TAB, next_focus, this);
    lineEdit->setFocused(true);

    editCounter = 0;
}

bool CChatClient::needToDraw(){
    return need_update;
}

Focus CChatClient::nextFocus(Focus f){
    switch (f){
        case INPUT_BOX: return QUIT;
        case QUIT: return INPUT_BOX;
        default: return INPUT_BOX;
    }
}

void CChatClient::addBuddy( int id, const string & s ){
    Buddy b;
    b.id = id;
    b.name = s;
    Util::Thread::acquireLock( &lock );
    buddies.push_back(b);
    needUpdate();
    Util::Thread::releaseLock( &lock );
    CResource::getSound(Filesystem::CRelativePath("menu/sounds/chip-in.wav"))->play();
}

void CChatClient::changeName( int id, const string & s ){
    Util::Thread::acquireLock( &lock );
    for ( vector< Buddy >::iterator it = buddies.begin(); it != buddies.end(); it++ ){
        Buddy & buddy = *it;
        if (buddy.id == id){
            buddy.name = s;
        }
    }
    needUpdate();
    Util::Thread::releaseLock( &lock );
}

void CChatClient::removeBuddy( int id ){
    Util::Thread::acquireLock( &lock );
    for ( vector< Buddy >::iterator it = buddies.begin(); it != buddies.end(); ){
        const Buddy & b = *it;
        if ( b.id == id ){
            it = buddies.erase( it );
        } else {
            it ++;
        }
    }
    needUpdate();
    Util::Thread::releaseLock( &lock );
    CResource::getSound(Filesystem::CRelativePath("menu/sounds/chip-out.wav"))->play();
}

void CChatClient::addMessage( const string & s, unsigned int id ){
    Util::Thread::acquireLock( &lock );
    messages.addMessage( s );
    needUpdate();
    Util::Thread::releaseLock( &lock );
}

/*
static char lowerCase( const char * x ){
	if ( x[0] >= 'A' && x[0] <= 'Z' ){
		return x[0] - 'A' + 'a';
	}
	return x[0];
}
*/

bool CChatClient::sendMessage( const string & message ){
    try{
        Network::Message net;
        net << ADD_MESSAGE;
        net.path = message;
        net.send( socket );
        return true;
    } catch ( const Exception::CNetworkException & e ){
        Debug::debug(Debug::error, __FUNCTION__) << "Client could not send message" << endl;
    }
    return false;
}

void CChatClient::popup(const CBitmap & work, const string & str ){
    const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20 );
    int length = font.textLength( str.c_str() ) + 20;
    int height = font.getHeight() * 2;
    CBitmap area( work, work.getWidth() / 2 - length / 2, work.getHeight() / 2, length, height );
    area.translucent().rectangleFill( 0, 0, area.getWidth(), area.getHeight(), Colors::LightRed );
	Colors::ColorDefinition color = Colors::White;
    area.polygon().rectangle( 0, 0, area.getWidth() - 1, area.getHeight() - 1, color );
    font.printf( 10, area.getHeight() / 3, Colors::White, area, str, 0 );
    work.BlitToScreen();

    /*
    key.wait();
    key.readKey();
    */
}

#if 0
void CChatClient::handleInput( Keyboard & keyboard ){
    /*
       vector< int > keys;
       keyboard.readKeys( keys );

       for ( vector< int >::iterator it = keys.begin(); it != keys.end(); it++ ){
       int key = *it;
       if ( key == Keyboard::Key_BACKSPACE ){
       if ( input != "" ){
       input = input.substr( 0, input.length() - 1 );
       needUpdate();
       }
       } else if ( Keyboard::isAlpha( key ) ){
       input += lowerCase( Keyboard::keyToName( key ) );
       needUpdate();
       } else if ( key == Keyboard::Key_SPACE ){
       input += " ";
       needUpdate();
       } else if ( key == Keyboard::Key_ENTER ){
       addMessage( "You: " + input, 0 );
       if ( ! sendMessage( input ) ){
       popup( keyboard, "Could not send message" );
       }
       input = "";
       needUpdate();
       }
       }
       */

    const Font & font = Font::getFont(string(Global::DEFAULT_FONT), 20, 20 );
    lineEdit->act(font);

    if ( lineEdit->didChanged( editCounter ) ){
        needUpdate();
    }

    if ( enterPressed && lineEdit->getText().length() > 0 ){
        // enterPressed = false;
        addMessage( "You: " + lineEdit->getText(), 0 );
        toSend.push(lineEdit->getText());
        lineEdit->clearText();
        needUpdate();
    }
}
#endif

void CChatClient::needUpdate(){
	need_update = true;
}

void CChatClient::next_focus(void * self){
    CChatClient * chat = (CChatClient*) self;
    chat->focus = chat->nextFocus(chat->focus);
    chat->lineEdit->setFocused(chat->focus == INPUT_BOX);
    if (chat->focus == INPUT_BOX){
        chat->lineEdit->colors.border = Colors::Yellow;
    } else {
        chat->lineEdit->colors.border = Colors::White;
    }
    chat->needUpdate();
}

bool CChatClient::logic(){
    const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20);
    lineEdit->act(font);
    if (lineEdit->didChanged(editCounter)){
        needUpdate();
    }

    return false;

    /*
	if ( keyboard[ Keyboard::Key_TAB ] ){
		focus = nextFocus( focus );
                Debug::debug(Debug::network, __FUNCTION__) << "Focus is " << focus << endl;
		needUpdate();
	}

	lineEdit->setFocused(false);
	switch ( focus ){
		case INPUT_BOX : {
			lineEdit->setFocused(true);
			lineEdit->colors.border = Bitmap::makeColor(255,255,0);
			handleInput( keyboard );
			return false;
		}
		case QUIT : {
			lineEdit->colors.border = Bitmap::makeColor(255,255,255);
			if ( keyboard[ Keyboard::Key_ENTER ] ){
				return true;
			}
			break;
		}
	}
	return false;
        */
}

void CChatClient::drawInputBox( int x, int y, const CBitmap & work ){
    const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20 );

    CBitmap::transBlender( 0, 0, 0, 128 );
	work.translucent().rectangleFill( x, y, x + messages.getWidth(), y + font.getHeight() + 1, Colors::Transparent );
	Colors::ColorDefinition color = Colors::White;
    if ( focus == INPUT_BOX ){
        color = Colors::Yellow;
    }
    work.polygon().rectangle( x, y, x + messages.getWidth(), y + font.getHeight(), color );
    CBitmap input_box( work, x + 1, y, messages.getWidth(), font.getHeight() );
    // font.printf( x + 1, y, Bitmap::makeColor( 255, 255, 255 ), work, input, 0 );
    font.printf( 0, 0, Colors::White, input_box, input, 0 );

}

void CChatClient::drawBuddies( const CBitmap & area, int x, int y, const CFont & font ){
	CBitmap buddyList( area, x, y, CConfiguration::screenWidth.getInteger() - x - 5, 200 );
    // buddyList.drawingMode( CBitmap::MODE_TRANS );
    CBitmap::transBlender( 0, 0, 0, 128 );
	buddyList.translucent().rectangleFill( 0, 0, buddyList.getWidth(), buddyList.getHeight(), Colors::Transparent );
    // buddyList.drawingMode( Bitmap::MODE_SOLID );
    buddyList.polygon().rectangle( 0, 0, buddyList.getWidth() -1, buddyList.getHeight() - 1, Colors::White );
    int fy = 1;
    for ( vector< Buddy >::iterator it = buddies.begin(); it != buddies.end(); it++ ){
        Buddy & buddy = *it;
        const string & name = buddy.name;
        font.printf( 1, fy, Colors::White, buddyList, name, 0 );
        fy += font.getHeight();
    }
}

void CChatClient::draw( const CBitmap & work ){
    int start_x = 20;
    int start_y = 20;
    const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20 );
    background->Blit( work );
    messages.draw( start_x, start_y, work, font );
    // drawInputBox( start_x, start_y + messages.getHeight() + 5, work );
    lineEdit->render(work);
    drawBuddies( work, start_x + messages.getWidth() + 10, start_y, font );

    Colors::ColorDefinition color = Colors::White;
    if ( focus == QUIT ){
        color = Colors::Yellow;
    }
    font.printf( start_x, start_y + messages.getHeight() + 5 + font.getHeight() + 20, color, work, "Back", 0 );

    need_update = false;
}

bool CChatClient::isFinished(){
    bool b;
    Util::Thread::acquireLock( &lock );
    b = finished;
    Util::Thread::releaseLock( &lock );
    return b;
}

void CChatClient::finish(){
    Util::Thread::acquireLock( &lock );
    finished = true;
    Util::Thread::releaseLock( &lock );
}

void CChatClient::killInputThread(){
    Debug::debug(Debug::error, __FUNCTION__) << "Killing input socket" << endl;
    Network::close(getSocket());
    Debug::debug(Debug::error, __FUNCTION__) << "Waiting for input thread to die" << endl;
    Util::Thread::joinThread(inputThread);
    Debug::debug(Debug::error, __FUNCTION__) << "Input thread killed" << endl;
}

static void set_to_true(void * b){
    bool * what = (bool*) b;
    *what = true;
}

void CChatClient::run(){
    // Global::speed_counter2 = 0;

    class Logic: public Input::CLogic {
    public:
        Logic(bool & kill, CChatClient & client):
        is_done(false),
        kill(kill),
        client(client),
        forceQuit(false){
            input.set(CKeyboard::Key_TAB, 0, true, 0);
            input.set(CKeyboard::Key_ENTER, 0, true, 1);
            input.set(CKeyboard::Key_ESC, 0, true, 2);
            client.lineEdit->hookKey(CKeyboard::Key_ESC, set_to_true, &forceQuit);
        }

        CInputMap<int> input;
        bool is_done;
        bool & kill;
        CChatClient & client;
        bool forceQuit;

        double ticks(double system){
            return system;
        }

        bool done(){
            return is_done;
        }

        void run(){
            vector<CInputMap<int>::InputEvent> events = CInputManager::getEvents(input);

            bool hasInputFocus = client.focus == INPUT_BOX;
            bool next = false;
            bool select = false;
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

            if (client.logic() || forceQuit || quit){
                kill = true;
                is_done = true;
                return;
            }

            if (next && !hasInputFocus){
                next_focus(&client);
            }

            if (quit || (select && client.focus == QUIT)){
                Debug::debug(Debug::error, __FUNCTION__) << "Quit!" << endl;
                kill = true;
                is_done = true;
            }

            while (! client.toSend.empty()){
                if (! client.sendMessage(client.toSend.front())){
					popup(CBitmap(CConfiguration::screenWidth.getInteger(),CConfiguration::screenHeight.getInteger()), "Could not send message" );
                }
                client.toSend.pop();
            }

            is_done = is_done || client.isFinished();
        }
    };

    class Draw: public Input::CDraw {
    public:
        Draw(CChatClient & client):
        client(client){
        }

        CChatClient & client;

        void draw(double fps){
            if (client.needToDraw()){
                // s client.draw(work);
               //s  work.BlitToScreen();
               //s  work.clear();
            }
        }
    };

    bool kill = false;
    Logic logic(kill, *this);
    Draw draw(*this);

    Input::SGE_standardLoop(logic, draw);

#if 0
    InputMap<int> input;
    input.set(Keyboard::Key_TAB, 0, true, 0);
    input.set(Keyboard::Key_ENTER, 0, true, 1);
    input.set(Keyboard::Key_ESC, 0, true, 2);

    bool forceQuit = false;
    bool done = false;
    lineEdit->hookKey(Keyboard::Key_ESC, set_to_true, &forceQuit);
    while (! done){
        int think = Global::speed_counter2;
        Global::speed_counter2 = 0;
        while (think > 0){
            InputManager::poll();
            vector<InputMap<int>::InputEvent> events = InputManager::getEvents(input);

            bool hasInputFocus = focus == INPUT_BOX;
            bool next = false;
            bool select = false;
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

            if (logic() || forceQuit || quit){
                kill = true;
                done = true;
                break;
            }

            if (next && !hasInputFocus){
                next_focus(this);
            }

            if (quit || (select && focus == QUIT)){
                Global::Debug::debug(Debug::error, __FUNCTION__) << "Quit!" << endl;
                kill = true;
                done = true;
            }

            while (! toSend.empty()){
                if (! sendMessage( toSend.front() )){
                    popup(work, "Could not send message" );
                }
                toSend.pop();
            }

            think -= 1;
            done = done || isFinished();

            /*
            if ( keyboard[ Keyboard::Key_ESC ] ){
                kill = true;
                done = true;
                break;
            }
            */
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

    lineEdit->setFocused(false);

    if (kill){
        killInputThread();
    } else {
        /* when OK_TO_START is sent there are guaranteed to be no other
         * packets in front of it to confuse the server
         */
        Network::Message message;
        message << OK_TO_START;
        message.send(getSocket());
    }
}

CChatClient::~CChatClient(){
    delete background;
    delete lineEdit;
}
} //end SGF
#endif
