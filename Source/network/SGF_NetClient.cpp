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
#include "network/SGF_NetClient.h"

#ifdef HAVE_NETWORKING

#include "graphics/SGF_Bitmap.h"
#include "graphics/SGF_TransBitmap.h"
#include "input/all.h"
#include "objects/all.h"
#include "game/all.h"
#include "network/SGF_Network.h"
#include <string>
#include <sstream>
#if 0
#include "util/parameter.h"
#include "util/init.h"
#include "util/funcs.h"
#include "util/font.h"
#include "util/file-system.h"
#include "../level/utils.h"
#include "factory/font_render.h"
#include "../factory/object_factory.h"
#include "../factory/heart_factory.h"
#include "util/music.h"
#include "network_world_client.h"
#include "util/exceptions/exception.h"
#include "util/loading.h"
#include "chat_client.h"
#include "configuration.h"
#include "util/system.h"
#endif
using namespace std;
namespace SGF {
namespace Network{

static bool uniqueId( const vector< CObject * > & objs, CObject::networkid_t id ){
    for ( vector< CObject * >::const_iterator it = objs.begin(); it != objs.end(); it++ ){
        CObject * o = *it;
        if ( o->getNetId() == id ){
            return false;
        }
    }
    return true;
}

/* send ok to server, get an ok back */
static void waitForServer(Socket socket){
    Message ok;
    ok << CTheater::OK;
    ok.send( socket );
    Debug::debug(Debug::network, __FUNCTION__)<< "Sent ok " << endl;
    Message ok_ack(socket);
    int type;
    ok_ack >> type;
    if (type != CTheater::OK){
        Debug::debug(Debug::error, __FUNCTION__) << "Did not receive ok from the server, instead received " << type << ". Badness may ensure" << endl;
    }
    Debug::debug(Debug::network, __FUNCTION__)<< "Received ok " << endl;
}

static void sendDummy(Socket socket){
    Message dummy;
    dummy.id = 0;
    dummy << CTheater::IGNORE_MESSAGE;
    dummy.send(socket);
}

static void sendQuit(Socket socket){
    Message quit;
    quit.id = 0;
    quit << CTheater::QUIT;
    quit.send(socket);
}

#if 0
/* select a player through the usual select screen then tell the server
 * about our existence and get back an id for the player
 */
static CPlayer * createNetworkPlayer(Socket socket){
    class Context: public Loader::LoadingContext {
    public:
        Context(Socket socket, Level::LevelInfo & info, const Filesystem::AbsolutePath & playerPath, int remap):
        socket(socket),
        info(info),
        playerPath(playerPath),
        remap(remap),
        player(NULL){
        }

        Socket socket;
        Level::LevelInfo & info;
        const Filesystem::AbsolutePath & playerPath;
        int remap;
        CPlayer * player;

        virtual void load(){
            Global::info("Create player " + playerPath.path());
            player = new CPlayer(playerPath, Util::ReferenceCount<InputSource>(new InputSource(0, 0)));
            player->setMap(remap);
            player->ignoreLives();
            Filesystem::RelativePath cleanPath = Storage::instance().cleanse(playerPath);

            Global::info("Notify server");
            /* send the path of the chosen player */
            Message create;
            create << CTheater::CREATE_CHARACTER;
            create.path = cleanPath.path();
            create.send(socket);

            Global::info("Waiting for id from server");
            /* get the id from the server */
            Message myid(socket);
            int type;
            int alliance;
            myid >> type;
            SGF::CObject::networkid_t client_id = (SGF::CObject::networkid_t) -1;
            if (type == CTheater::SET_ID){
                myid >> client_id >> alliance;
                player->setId(client_id);
                player->setAlliance(alliance);
                Debug::debug(Debug::network, __FUNCTION__) << "Client id is " << client_id << endl;
            } else {
                Debug::debug(Debug::error, __FUNCTION__) << "Bogus message, expected SET_ID(" << CTheater::SET_ID << ") got " << type << endl;
            }
            Global::info("Received an id");
        }
    };

    /* TODO: get the info from the server */
    Level::LevelInfo info;

    /* remap will be modified by the selectPlayer method */
    int remap = 0;
    Filesystem::AbsolutePath playerPath = Mod::getCurrentMod()->selectPlayer("Pick a player", info, remap, InputSource());

    Context context(socket, info, playerPath, remap);
    Loader::loadScreen(context, Level::convert(info));
    return context.player;
}


/* TODO: simplify this code */
static void playGame(Socket socket){
    // Util::Thread::ThreadId_t loadingThread;
    try{
        CPlayer * player = createNetworkPlayer(socket);
        vector<SGF::CObject *> players;
        players.push_back(player);

        map<SGF::CObject::networkid_t, string> clientNames;

        bool done = false;
        while (! done){
            class Dispatcher: public Loader::LoadingContext {
            public:
                Dispatcher(vector<SGF::CObject*> & players,
                           CPlayer * player,
                           map<SGF::CObject::networkid_t, string> & clientNames,
                           bool & done,
                           Socket socket):
                players(players),
                player(player),
                clientNames(clientNames),
                done(done),
                socket(socket),
                play(false),
                world(NULL){
                }

                vector<SGF::CObject*> & players;
                CPlayer * player;
                map<SGF::CObject::networkid_t, string> & clientNames;
                bool & done;
                Socket socket;
                bool play;

                NetworkWorldClient * world;

                virtual ~Dispatcher(){
                    delete world;
                }

                void createCharacter(Message & next){
                    SGF::CObject::networkid_t id;
                    int alliance;
                    next >> id >> alliance;
                    if (uniqueId(players, id)){
                        Debug::debug(Debug::network, __FUNCTION__) << "Create a new network player id " << id << " alliance " << alliance << endl;
                        Global::info("Create character " + next.path);
                        CCharacter * c = new CNetworkPlayer(Storage::instance().find(Filesystem::RelativePath(next.path)), alliance);
                        c->setId(id);
                        ((CNetworkCharacter *)c)->alwaysShowName();
                        players.push_back(c);
                    }

                }

                void clientInfo(Message & next){
                    SGF::CObject::networkid_t id;
                    next >> id;
                    string name = next.path;
                    clientNames[id] = name;
                    Global::info("Player " + name);
                }

                void loadLevel(Message & next){
                    Filesystem::AbsolutePath level = Storage::instance().find(Filesystem::RelativePath(next.path));
                    /* TODO: handle LoadException here */
                    this->world = new NetworkWorldClient(socket, players, level, player->getId(), clientNames);
                    Music::changeSong();

                    Global::info("Waiting for ok from server");
                    waitForServer(socket);

                    this->world->startMessageHandler();
                    play = true;
                }

                void gameOver(){
                    done = true;
                }

                virtual void load(){
                    while (!done && !play){
                        Message next(socket);
                        int type;
                        next >> type;
                        switch (type){
                            case CTheater::CREATE_CHARACTER : {
                                createCharacter(next);
                                break;
                            }
                            case CTheater::CLIENT_INFO : {
                                clientInfo(next);
                                break;
                            }
                            case CTheater::LOAD_LEVEL : {
                                loadLevel(next);
                                break;
                            }
                            /* thats all folks! */
                            case CTheater::GAME_OVER : {
                                gameOver();
                                break;
                            }
                        }
                    }
                }
            };

            Dispatcher dispatch(players, player, clientNames, done, socket);
            Level::LevelInfo info;
            Loader::loadScreen(dispatch, Level::convert(info));

            if (dispatch.play){
                NetworkWorldClient & world = *dispatch.world;
                try{
                    vector<SGF::CObject*> xplayers;
                    bool forceQuit = ! Game::playLevel(world, xplayers);

                    ObjectFactory::destroy();
                    HeartFactory::destroy();

                    if (forceQuit){
                        Global::debug(1, __FILE__) << "Force quit" << endl;
                        sendQuit(socket);
                        /* After quit is sent the socket will be closed
                         * by someone later on. The input handler in the client
                         * world will throw a network exception and then
                         * the thread will die.
                         */
                        done = true;
                    } else {
                        Debug::debug(Debug::network, __FUNCTION__) << "Stop running client world" << endl;
                        /* this dummy lets the server message handler
                         * stop running. its currently blocked waiting for
                         * a message to come through.
                         */
                        sendDummy(socket);
                        world.stopRunning();
                        Debug::debug(Debug::network, __FUNCTION__) << "Wait for server " << endl;
                        /* then wait for a barrier */
                        waitForServer(socket);
                    }
                } catch ( const Exception::Return & e ){
                    /* do we need to close the socket here?
                     * when this function returns the socket will be
                     * closed anyway.
                     */
                    Network::close(socket);
                }
            }
        }

        for (vector<SGF::CObject*>::iterator it = players.begin(); it != players.end(); it++){
            delete *it;
        }
    } catch ( const LoadException & le ){
        Global::debug(0, "client") << "Load exception: " + le.getTrace() << endl;
    }
}
#endif
static void drawBox( const CBitmap & area, const CBitmap & copy, const string & str, const CFont & font, bool hasFocus ){
    copy.BlitSurface( area );
    CBitmap::transBlender( 0, 0, 0, 192 );
    // area.drawingMode( CBitmap::MODE_TRANS );
    area.translucent().rectangleFill( 0, 0, area.getWidth(), area.getHeight(), Colors::makeColor( 0, 0, 0 ) );
    // area.drawingMode( CBitmap::MODE_SOLID );
    int color = Colors::makeColor( 255, 255, 255);
    if (hasFocus){
        color = Colors::makeColor( 255, 255, 0 );
    }
    area.polygon().rectangle( 0, 0, area.getWidth() - 1, area.getHeight() - 1, color );
	font.drawText( 1, 0, Colors::Black, area, str.c_str(), 0 );
}

static char lowerCase( const char * x ){
	if ( x[0] >= 'A' && x[0] <= 'Z' ){
		return x[0] - 'A' + 'a';
	}
	return x[0];
}

/*
static bool handleNameInput( string & str, const vector< int > & keys ){
	bool cy = false;
	for ( vector< int >::const_iterator it = keys.begin(); it != keys.end(); it++ ){
		const int & key = *it;
		if ( str.length() < 16 && CKeyboard::isAlpha( key ) ){
			str += lowerCase( CKeyboard::keyToName( key ) );
			cy = true;
		} else if ( key == CKeyboard::Key_BACKSPACE ){
			if ( str != "" ){
				str = str.substr( 0, str.length() - 1 );
				cy = true;
			}
		}
	}
	return cy;
}
*/

/*
static bool handleHostInput( string & str, const vector< int > & keys ){
	bool cy = false;
	for ( vector< int >::const_iterator it = keys.begin(); it != keys.end(); it++ ){
		const int & key = *it;
		if ( CKeyboard::isAlpha( key ) || key == CKeyboard::Key_STOP ){
			str += lowerCase( CKeyboard::keyToName( key ) );
			cy = true;
		} else if ( key == CKeyboard::Key_BACKSPACE ){
			if ( str != "" ){
				str = str.substr( 0, str.length() - 1 );
				cy = true;
			}
		}
	}
	return cy;
}
*/

/*
static bool handlePortInput( string & str, const vector< int > & keys ){
	bool cy = false;
	for ( vector< int >::const_iterator it = keys.begin(); it != keys.end(); it++ ){
		const int & key = *it;
		if ( CKeyboard::isNumber( key ) || key == CKeyboard::Key_STOP ){
			str += CKeyboard::keyToName( key );
			cy = true;
		} else if ( key == CKeyboard::Key_BACKSPACE ){
			if ( str != "" ){
				str = str.substr( 0, str.length() - 1 );
			cy = true;
			}
		}
	}
	return cy;
}
*/



static const char * getANumber(){
    switch (Util::rnd(10)){
        case 0 : return "0";
        case 1 : return "1";
        case 2 : return "2";
        case 3 : return "3";
        case 4 : return "4";
        case 5 : return "5";
        case 6 : return "6";
        case 7 : return "7";
        case 8 : return "8";
        case 9 : return "9";
        default : return "0";
    }
}

const char * propertyLastClientName = "network:last-client-name";
const char * propertyLastClientHost = "network:last-client-host";
const char * propertyLastClientPort = "network:last-client-port";

enum ClientActions{
    Next,
    Back,
    Quit,
    Action
};

void runClient(const string & name, const string & host, const string & port){
    CConfiguration::setStringProperty(propertyLastClientName, name);
    CConfiguration::setStringProperty(propertyLastClientHost, host);
    CConfiguration::setStringProperty(propertyLastClientPort, port);
    istringstream stream(port);
    int portNumber;
    stream >> portNumber;
    Debug::debug(Debug::network, __FUNCTION__) << "Connecting to host " << host << " on port " << portNumber << endl;
    Network::Socket socket = Network::connectTo(host, portNumber);
    try{
       //s  ChatClient chat(socket, name);
       //s chat.run();
       /* s if (chat.isFinished()){
            playGame(socket);
        } */
		Network::closeSocket(socket);
    } catch (...){
		Network::closeSocket(socket);
        throw;
    }
}

enum CliFocus{
    Name, Host, Port, Connect, FocusBack
};

struct FocusBundle{
    FocusBundle(CliFocus & focus, CTextInput & name, CTextInput & port, CTextInput & host):
    focus(focus),
    name(name),
    port(port),
    host(host){
    }

    CliFocus & focus;
    CTextInput & name;
    CTextInput & port;
    CTextInput & host;
};

static void nextFocus(void * stuff){
    FocusBundle * focus = (FocusBundle*) stuff;
    focus->name.disable();
    focus->port.disable();
    focus->host.disable();
    switch (focus->focus){
        case Name: focus->focus = Host; focus->host.enable(); break;
        case Host: focus->focus = Port; focus->port.enable(); break;
        case Port: focus->focus = Connect; break;
        case Connect: focus->focus = FocusBack; break;
        case FocusBack: focus->focus = Name; focus->name.enable(); break;
        default: focus->focus = Host; focus->host.enable(); break;
    }
}

static void previousFocus(void * stuff){
    FocusBundle * focus = (FocusBundle*) stuff;
    focus->name.disable();
    focus->host.disable();
    focus->port.disable();
    switch (focus->focus){
        case Name: focus->focus = FocusBack; break;
        case Host: focus->focus = Name; focus->name.enable(); break;
        case Port: focus->focus = Host; focus->host.enable(); break;
        case Connect: focus->focus = Port; focus->port.enable(); break;
        case FocusBack: focus->focus = Connect; break;
        default: focus->focus = Host; focus->host.enable(); break;
    }
}

static void doQuit(void * stuff){
    throw Exception::Return(__FILE__, __LINE__);
}

/* this whole thing needs to be modularized and abstracted away into
 * some domain specific language.
 */
void networkClient(){
    // Global::speed_counter = 0;

    CTextInput nameInput(CConfiguration::getStringProperty(propertyLastClientName, string("player") + getANumber() + getANumber()));
    CTextInput hostInput(CConfiguration::getStringProperty(propertyLastClientHost, "localhost"));
    CTextInput portInput(CConfiguration::getStringProperty(propertyLastClientPort, "7887"));

    CliFocus focus = Name;
    nameInput.enable();

    FocusBundle bundle(focus, nameInput, portInput, hostInput);

    nameInput.addBlockingHandle(CKeyboard::Key_TAB, nextFocus, &bundle);
    portInput.addBlockingHandle(CKeyboard::Key_TAB, nextFocus, &bundle);
    hostInput.addBlockingHandle(CKeyboard::Key_TAB, nextFocus, &bundle);

    nameInput.addBlockingHandle(CKeyboard::Key_DOWN, nextFocus, &bundle);
    portInput.addBlockingHandle(CKeyboard::Key_DOWN, nextFocus, &bundle);
    hostInput.addBlockingHandle(CKeyboard::Key_DOWN, nextFocus, &bundle);

    nameInput.addBlockingJoystickHandle(CJoystick::Down, nextFocus, &bundle);
    portInput.addBlockingJoystickHandle(CJoystick::Down, nextFocus, &bundle);
    hostInput.addBlockingJoystickHandle(CJoystick::Down, nextFocus, &bundle);

    nameInput.addBlockingHandle(CKeyboard::Key_UP, previousFocus, &bundle);
    portInput.addBlockingHandle(CKeyboard::Key_UP, previousFocus, &bundle);
    hostInput.addBlockingHandle(CKeyboard::Key_UP, previousFocus, &bundle);

    nameInput.addBlockingJoystickHandle(CJoystick::Up, previousFocus, &bundle);
    portInput.addBlockingJoystickHandle(CJoystick::Up, previousFocus, &bundle);
    hostInput.addBlockingJoystickHandle(CJoystick::Up, previousFocus, &bundle);

    nameInput.addBlockingHandle(CKeyboard::Key_ESC, doQuit, NULL);
    portInput.addBlockingHandle(CKeyboard::Key_ESC, doQuit, NULL);
    hostInput.addBlockingHandle(CKeyboard::Key_ESC, doQuit, NULL);

    nameInput.addBlockingJoystickHandle(CJoystick::Button9, doQuit, NULL); //botao select
    portInput.addBlockingJoystickHandle(CJoystick::Button9, doQuit, NULL);
    hostInput.addBlockingJoystickHandle(CJoystick::Button9, doQuit, NULL);

    struct State{
        bool draw;
    };

    class Logic: public Input::CLogic {
    public:
        Logic(CliFocus & focus, State & state, CTextInput & nameInput, CTextInput & portInput, CTextInput & hostInput, FocusBundle & bundle):
        is_done(false),
        focus(focus),
        state(state),
        nameInput(nameInput),
        portInput(portInput),
        hostInput(hostInput),
        bundle(bundle){
            input.set(CKeyboard::Key_TAB, 0, true, Next);
            input.set(CKeyboard::Key_DOWN, 0, true, Next);
            input.set(CJoystick::Down, 0, true, Next);
            input.set(CKeyboard::Key_UP, 0, true, Back);
            input.set(CJoystick::Up, 0, true, Back);
            input.set(CKeyboard::Key_ESC, 0, true, Quit);
            input.set(CJoystick::Button9, 0, true, Quit);
            input.set(CKeyboard::Key_ENTER, 0, true, Action);
            input.set(CJoystick::Button1, 0, true, Action);
        }

        bool is_done;
        CliFocus & focus;
        State & state;
        CInputMap<ClientActions> input;

        CTextInput & nameInput;
        CTextInput & portInput;
        CTextInput & hostInput;

        FocusBundle & bundle;

        double ticks(double system){
            return system;
        }

        void run(int){
            CliFocus oldFocus = focus;
            vector<CInputMap<ClientActions>::InputEvent> events = CInputManager::getEvents(input);

            switch (focus){
                case Name: state.draw = state.draw || nameInput.doInput(); break;
                case Port: state.draw = state.draw || portInput.doInput(); break;
                case Host: state.draw = state.draw || hostInput.doInput(); break;
                default: break;
            }

            for (vector<CInputMap<ClientActions>::InputEvent>::iterator it = events.begin(); it != events.end() && !is_done; it++){
                const CInputMap<ClientActions>::InputEvent & event = *it;
                if (!event.enabled){
                    continue;
                }

                if (event[Next]){
                    nextFocus(&bundle);
                }

                if (event[Back]){
                    previousFocus(&bundle);
                }

                if (event[Quit]){
                    throw Exception::Return(__FILE__, __LINE__);
                }

                if (event[Action]){
                    switch (focus){
                        case Name:
                        case Host:
                        case Port: break;
                        case Connect: {
                            is_done = true;
                            try{
                                CInputManager::waitForRelease(input,  Action);
                                runClient(nameInput.getText(), hostInput.getText(), portInput.getText());
                            } catch (const Exception::CNetworkException & e){
                                const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20);
                                Util::popup(font, e.getMessage());
                                CInputManager::waitForRelease(input,  Action);
                                CInputManager::waitForPress(input,  Action);
                                CInputManager::waitForRelease(input,  Action);

                                is_done = false;
                                state.draw = true;
                            }
                            break;
                        }
                        case FocusBack : is_done = true; break;
                    }
                }

            }

            state.draw = state.draw || oldFocus != focus;
        }

        bool done(){
            return is_done;
        }
    };

    class Draw: public Input::CDraw {
    public:
        Draw(State & state, const CliFocus & focus, CTextInput & nameInput, CTextInput & portInput, CTextInput & hostInput):
        state(state),
        background(CConfiguration::gameTitleScreen.getString()),
        focus(focus),
        nameInput(nameInput),
        portInput(portInput),
        hostInput(hostInput){
        }

        State & state;
        CBitmap background;
        const CliFocus & focus;

        CTextInput & nameInput;
        CTextInput & portInput;
        CTextInput & hostInput;

        void draw(double fps){
            if (state.draw){
                state.draw = false;
                const CFont & font = *CResource::getDefaultFont();//CResource::getDefaultFont( 20, 20 );
				background.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
				background.Blit();

                const int inputBoxLength = font.getTextLength("a") * 40;
                const int min_y = 140;

                font.drawText( 20, min_y - font.getHeight() * 3 - 1, Colors::Black, background, "Your name", 0 );
                CBitmap nameBox( background, 20, min_y - font.getHeight() * 2, inputBoxLength, font.getHeight() );
                CBitmap copyNameBox( nameBox.getWidth(), nameBox.getHeight() );
                nameBox.BlitSurface(copyNameBox);

                font.drawText( 20, min_y - font.getHeight() - 1, Colors::Black, background, "Host (IP address or name)", 0 );
                CBitmap hostBox(background, 20, min_y, inputBoxLength, font.getHeight());
                CBitmap copyHostBox( hostBox.getWidth(), hostBox.getHeight() );
                hostBox.BlitSurface(copyHostBox);

                font.drawText( 20, min_y + font.getHeight() * 2 - font.getHeight() - 1, Colors::Black, background, "Network Host Port", 0 );
                CBitmap portBox(background, 20, min_y + font.getHeight() * 2, inputBoxLength, font.getHeight());
                CBitmap copyPortBox( portBox.getWidth(), portBox.getHeight() );
                portBox.BlitSurface(copyPortBox);

                font.drawText( 20, 20, Colors::Black, background, "Press TAB to cycle the next input", 0 );

                int focusColor = Colors::makeColor( 255, 255, 0 );
                int unFocusColor = Colors::makeColor( 255, 255, 255 );

                drawBox(nameBox, copyNameBox, nameInput.getText(), font, focus == Name);
                drawBox(hostBox, copyHostBox, hostInput.getText(), font, focus == Host);
                drawBox(portBox, copyPortBox, portInput.getText(), font, focus == Port);
                font.drawText( 20, min_y + font.getHeight() * 5, focus == Connect ? focusColor : unFocusColor, background, "Connect", 0 );
                font.drawText( 20, min_y + font.getHeight() * 6 + 5, focus == FocusBack ? focusColor : unFocusColor, background, "Back", 0 );

                background.BlitToScreen();
				background.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

            }
        }
    };

    State state;
    state.draw = true;
    Logic logic(focus, state, nameInput, portInput, hostInput, bundle);
    Draw draw(state, focus, nameInput, portInput, hostInput);

    //draw.draw(*Graphics::screenParameter.current());
    Input::SGE_standardLoop(logic, draw);
}

}
} //end SGF
#endif
