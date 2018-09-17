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
#include "network/SGF_NetServer.h"

#ifdef HAVE_NETWORKING
#include "network/SGF_Network.h"
#include "graphics/SGF_Bitmap.h"
#include "graphics/SGF_TransBitmap.h"
#include "resource/all.h"
#include "input/all.h"
#include "util/SGF_FileSystem.h"
#include "util/SGF_FontInfo.h"
#include "structures/SGF_Parameter.h"
#include "objects/all.h"
#include "util/SGF_Util.h"
#include "exceptions/SGF_NetException.h"

using namespace std;
namespace SGF {
namespace Network{

//static std::ostream & debug(int level){
//    return Global::debug(level, "[server]");
//}

static void set_to_true(void * what){
    bool * b = (bool *) what;
    *b = true;
}

static void do_quit(void * what){
    throw Exception::Return(__FILE__, __LINE__);
}

static int getServerPort(){
    CBitmap background(CConfiguration::gameTitleScreen.getString());
    const int drawY = 250;
    {
        // background.BlitToScreen();
		const CFont & font = *CResource::getDefaultFont();//CResource::getDefaultFont( 20, 20 );
		background.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
        CBitmap black( 300, font.getHeight() * 4 );
        black.clear();
        black.border( 0, 1, Colors::makeColor( 255, 255, 0 ) );
        CBitmap::transBlender( 0, 0, 0, 92 );
        black.translucent().draw( 20, drawY - font.getHeight() - 20, background );
        background.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		background.updateTexture();

		background.Blit();
		font.drawText( 40, drawY, Colors::makeColor( 255, 255, 0 ), background, "Port:", 0 );
        font.drawText( 40, drawY - font.getHeight() - 5, Colors::makeColor( 255, 255, 0 ), background, "Enter to start. ESC to quit", 0 );
		background.BlitToScreen();
		background.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

    }

    /* TODO: add filter for numbers */
    CTextInput input("7887");
    input.addBlockingHandle(CKeyboard::Key_ESC, do_quit, NULL);

    class Logic: public Input::CLogic {
    public:
        Logic(CTextInput & input, bool & draw):
        input(input),
        is_done(false),
        draw(draw){
            input.addBlockingHandle(CKeyboard::Key_ENTER, set_to_true, &is_done);
            input.enable();
        }

        CTextInput & input;
        bool is_done;
        bool & draw;

        bool done(){
            return is_done;
        }

        double ticks(double system){
            return system;
        }

        void run(int){
			try {
				draw = input.doInput();
			}catch(Exception::Return){
				is_done=true;
			}
           
        }
    };

    class Draw: public Input::CDraw {
    public:
        Draw(CBitmap & background, CTextInput & input, int drawY, bool & need_draw):
        background(background),
        input(input),
        drawY(drawY),
        need_draw(need_draw){
        }

        CBitmap & background;
         CTextInput & input;
        int drawY;
        bool & need_draw;

        void draw(double fps){
            if (need_draw){
				const CFont & font = *CResource::getDefaultFont();//CResource::getDefaultFont( 20, 20 );

				//background.Blit();
                //CBitmap work(100, drawY, 200, 25);
                //work.clear();
				//CResource::getDefaultFont(20,20)->printf(100, drawY, Colors::White, background, "Teste", 0);
				//const CFont & font = *CResource::getDefaultFont();//CResource::getDefaultFont( 20, 20 );

				//font.printf( 1000, drawY, Colors::makeColor( 255, 255, 255 ), background, "Teste:", 0 );

                //const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20 );
                //font.printf(100, drawY, Colors::White, background, input.getText(), 0);
                // work.Blit(100, drawY, background);
                // background.BlitToScreen();
				CBitmap black( 300, font.getHeight() * 4 );
        black.clear();
        black.border( 0, 1, Colors::makeColor( 255, 255, 0 ) );
        CBitmap::transBlender( 0, 0, 0, 92 );
        black.translucent().draw( 20, drawY - font.getHeight() - 20, background );
        background.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		background.updateTexture();
		background.Blit();

				font.drawText( 40, drawY, Colors::makeColor( 255, 255, 0 ), background, "Port:", 0 );
				font.drawText( 40, drawY - font.getHeight() - 5, Colors::makeColor( 255, 255, 0 ), background, "Enter to start. ESC to quit", 0 );

				//CResource::getDefaultFont()->DrawTextNew(100,drawY,Colors::Blue, background,"%2.2f FPS",fps);
				CResource::getDefaultFont(20,20)->drawText(100, drawY, Colors::Red, background, input.getText(), 0);

				background.BlitToScreen();
				background.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

            }
        }
    };

    bool draw = true;
    Logic logic(input, draw);
    Draw drawer(background, input, drawY, draw);
    //drawer.draw(*Graphics::screenParameter.current());

    Input::SGE_standardLoop(logic, drawer);

#if 0
    bool draw = true;
    Global::speed_counter2 = 0;
    while (! done){
        while (Global::speed_counter2 > 0){
            CInputManager::poll();
            draw = input.doInput();
            Global::speed_counter2 -= 1;
        }

        if (draw){
            work.clear();
            const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 20, 20 );
            font.printf(0, 0, Colors::makeColor( 255, 255, 255 ), work, input.getText(), 0);
            work.Blit(100, drawY, background);
            background.BlitToScreen();
        }

        draw = false;

        while ( Global::speed_counter2 == 0 ){
            Util::rest(1);
        }
    }
#endif

    istringstream str(input.getText());
    int port;
    str >> port;
    return port;
}

#if 0
static void networkGame( const vector< Object * > & players, const string & levelFile, const vector< NLsocket > & sockets ){

	vector< string > levels = Level::readLevels( levelFile );

	// global_debug = true;

	int showHelp = 300;
	for ( vector< string >::iterator it = levels.begin(); it != levels.end(); it++ ){
		Global::done_loading = false;
		pthread_t loading_screen_thread;

		startLoading( &loading_screen_thread );

		networkSendLevel( sockets, *it );

		bool gameState = false;
		try {
			// vector< Object * > players;
			// players.push_back( player );
			NetworkWorld world( sockets, players, *it );

			Music::pause();
			Music::fadeOut( 0.3 );
			Util::rest( 100 );
			Music::fadeIn( 0.3 );
			Music::loadSong( Util::getFiles( Util::getDataPath() + "/music/", "*" ) );
			Music::play();

			for ( vector< Object * >::const_iterator it = players.begin(); it != players.end(); it++ ){
				Player * playerX = (Player *) *it;
				playerX->setY( 200 );
				/* setMoving(false) sets all velocities to 0 */
				playerX->setMoving( false );
				/* but the player is falling so set it back to true */
				playerX->setMoving( true );

				playerX->setStatus( Status_Falling );
				world.addMessage( playerX->movedMessage() );
			}

			stopLoading( loading_screen_thread );

			// nlDisable( NL_BLOCKING_IO );
			gameState = playLevel( world, players, showHelp );
			// nlEnable( NL_BLOCKING_IO );
			showHelp = 0;

			world.addMessage( world.finishMessage() );
			world.flushOutgoing();

		} catch ( const CLoadException & le ){
			Global::debug( 0 ) << "Could not load " << *it << " because " << le.getReason() << endl;
			/* if the level couldn't be loaded turn off
			 * the loading screen
			 */
			stopLoading( loading_screen_thread );
		}

		ObjectFactory::destroy();
		HeartFactory::destroy();

		if ( ! gameState ){
			return;
		}

		fadeOut( "Next level" );
	}

	for ( vector< NLsocket >::const_iterator it = sockets.begin(); it != sockets.end(); it++ ){
		NLsocket s = *it;
		Network::send16( s, -1 );
	}

	fadeOut( "You win!" );
}
#endif


static void sendToAll( const vector< Socket > & sockets, const Message & message ){
    for ( vector< Socket >::const_iterator it = sockets.begin(); it != sockets.end(); it++ ){
        const Socket & socket = *it;
        message.send( socket );
    }
}
#if 0

static int allAlliance = ALLIANCE_FREE_FOR_ALL;
static int playerAlliance(){
    if (CConfiguration::getPlayMode() == CConfiguration::FreeForAll){
        return allAlliance++;
    } else {
        return ALLIANCE_PLAYER;
    }
}

static void waitAllOk(const vector<Socket> & sockets){
    Debug::debug(Debug::network,__FUNCTION__) << "Waiting for an ok from all clients" << endl;
    Global::info("Waiting for all clients..");
    for (vector<Socket>::const_iterator it = sockets.begin(); it != sockets.end(); it++){
        bool done = false;
        while (!done){
            Message ok(*it);
            int type;
            ok >> type;
            if (type == World::OK){
                Debug::debug(Debug::network,__FUNCTION__) << "Received ok from client " << *it << endl;
                done = true;
            } else {
                Debug::debug(Debug::network,__FUNCTION__) << "Received " << type << " from client " << *it << ". Ignoring.." << endl;
            }
        }
    }
}

static void waitAllFinish(const vector<Socket> & sockets){
    for (vector<Socket>::const_iterator it = sockets.begin(); it != sockets.end(); it++){
        bool done = false;
        while (!done){
            Message ok(*it);
            int type;
            ok >> type;
            if (type == World::FINISH){
                Debug::debug(Debug::network,__FUNCTION__) << "Received finish from client " << *it << endl;
                done = true;
            } else {
                Debug::debug(Debug::network,__FUNCTION__) << "Received " << type << " from client " << *it << ". Ignoring.." << endl;
            }
        }
    }
}

static void sendAllOk(const vector<Socket> & sockets){
    Message ok;
    ok << World::OK;
    Debug::debug(Debug::network,__FUNCTION__) << "Sending an ok to all clients" << endl;
    sendToAll(sockets, ok);
}

static Level::LevelInfo selectLevels(){
    /* then the user selects a set of levels to play */
    Menu::Context context;

    /* FIXME: get a better Menu::Context object, one that already has
     * a font set and a background.
     */
    context.setFont(Util::CReferenceCount<Menu::FontInfo>(new Menu::RelativeFontInfo(Global::DEFAULT_FONT, 20, 20)));
    CBitmap normalBackground(Global::titleScreen().path());
    context.addBackground(normalBackground);
    return doLevelMenu("/levels", context);
}

/* for each client get the player they want and send back an id */
static void createClients(const vector<CNetClient*> & clients, vector<Network::Socket> & sockets, map<SGF::CObject::networkid_t, string> & clientNames, map<SGF::CObject*, Socket> & characterToSocket, vector<SGF::CObject *> & players){
    /* clients start at id 2 because the server is 1 */
    SGF::CObject::networkid_t id = 2;
    /* all other players will send their chosen character as a
     * CREATE_CHARACTER message. after receiving it, send back the
     * network id for that character.
     */

    /* bundle up all the client infos and send them after setting up the clients */
    vector<Message> clientInfos;

    for (vector<CNetClient*>::const_iterator it = clients.begin(); it != clients.end(); it++){
        CNetClient * client = *it;
        Debug::debug(Debug::network,__FUNCTION__) << "Setting up client " << client->getName() << endl;
        Global::info("Setting up client " + client->getName());
        Socket socket = client->getSocket();
        sockets.push_back(socket);
        Debug::debug(Debug::network,__FUNCTION__) << "Read character path from " << id << endl;
        Message message(socket);
        int type;
        message >> type;
        if (type == World::CREATE_CHARACTER){
            int alliance = playerAlliance();
            Global::info(" creating " + message.path);
            ::CCharacter * client_character = new NetworkPlayer(Storage::instance().find(Filesystem::RelativePath(message.path)), alliance);
            characterToSocket[client_character] = socket;
            /* FIXME: Don't need this line now that NetworkPlayer exists.
             * take it out at some point.
             */
            ((NetworkCharacter *)client_character)->alwaysShowName();

            players.push_back(client_character);
            client_character->setLives(1);
            client_character->setId(id);
            Message clientId;
            clientId << World::SET_ID;
            clientId << id;
            clientId << alliance;
            clientId.send(socket);

            clientNames[id] = client->getName();

            Message info;
            info.id = 0;
            info << World::CLIENT_INFO;
            info << id;
            info << client->getName();
            clientInfos.push_back(info);

            id += 1;
        } else {
            Debug::debug(Debug::error,__FUNCTION__) << "Got a bogus message: " << type << endl;
        }
    }

    Global::info("Notify all clients");
    for (vector<Message>::iterator it = clientInfos.begin(); it != clientInfos.end(); it++){
        sendToAll(sockets, *it);
    }
}

/* TODO: simplify this code */
static void playGame(vector<CNetClient*> & clients){
    vector<SGF::CObject *> players;
    try{
        /* first the user selects his own player */
        Level::LevelInfo info;
        int remap = 0;
        Filesystem::AbsolutePath playerPath = Mod::getCurrentMod()->selectPlayer("Pick a player", info, remap, InputSource());
        CPlayer * player = new CPlayer(playerPath, Util::ReferenceCount<InputSource>(new InputSource(0, 0)));
        player->setMap(remap);
        player->ignoreLives();
        players.push_back(player);

        Level::LevelInfo levelInfo = selectLevels();

        /* reset the alliance settings */
        allAlliance = ALLIANCE_FREE_FOR_ALL;

        /* the server player is network id 1 */
        player->setId(1);
        /* the server's player alliance can just be ALLIANCE_PLAYER, so no
         * need to change it
         */

        /* sockets for clients. why cant we get this from the Client class? */
        vector<Network::Socket> sockets;

        /* keep track of characters and their related sockets (clients) */
        map<SGF::CObject*, Socket> characterToSocket;

        map<SGF::CObject::networkid_t, string> clientNames;

        class ClientContext: public Loader::LoadingContext {
        public:
            ClientContext(const vector<CNetClient*> & clients,
                          vector<Network::Socket> & sockets,
                          map<SGF::CObject::networkid_t, string> & clientNames,
                          map<SGF::CObject*, Socket> & characterToSocket,
                          vector<SGF::CObject *> & players):
            clients(clients),
            sockets(sockets),
            clientNames(clientNames),
            characterToSocket(characterToSocket),
            players(players){
            }

            const vector<CNetClient*> & clients;
            vector<Network::Socket> & sockets;
            map<SGF::CObject::networkid_t, string> & clientNames;
            map<SGF::CObject*, Socket> & characterToSocket;
            vector<SGF::CObject *> & players;

            virtual void load(){
                createClients(clients, sockets, clientNames, characterToSocket, players);

                /* send all created characters to all clients */
                for (vector<SGF::CObject *>::iterator it = players.begin(); it != players.end(); it++){
                    CCharacter * c = (CCharacter *) *it;
                    Filesystem::RelativePath path = Storage::instance().cleanse(c->getPath());
                    // path.erase( 0, Util::getDataPath().length() );
                    Message add;
                    add << World::CREATE_CHARACTER;
                    add << c->getId();
                    add << c->getAlliance();
                    add.path = path.path();
                    sendToAll(sockets, add);
                }
            }
        };

        ClientContext context(clients, sockets, clientNames, characterToSocket, players);
        Loader::loadScreen(context, Level::convert(levelInfo));

        for (vector< string >::const_iterator it = levelInfo.getLevels().begin(); it != levelInfo.getLevels().end(); it++){
            string level = *it;
            Debug::debug(Debug::network,__FUNCTION__) << "Sending level '" << level << "'" << endl;
            Message loadLevel;
            loadLevel << World::LOAD_LEVEL;
            loadLevel.path = level;
            sendToAll(sockets, loadLevel);

            class GameContext: public Loader::LoadingContext {
            public:
                GameContext(const string & level,
                            vector<Network::Socket> & sockets,
                            map<SGF::CObject*, Socket> & characterToSocket,
                            map<SGF::CObject::networkid_t, string> & clientNames,
                            vector<SGF::CObject *> & players):
                world(NULL),
                level(level),
                sockets(sockets),
                characterToSocket(characterToSocket),
                clientNames(clientNames),
                players(players){
                }

                CNetworkWorld * world;
                string level;
                vector<Network::Socket> & sockets;
                map<SGF::CObject*, Socket> & characterToSocket;
                map<SGF::CObject::networkid_t, string> & clientNames;
                vector<SGF::CObject *> & players;

                virtual ~GameContext(){
                    delete world;
                }

                virtual void load(){
                    Debug::debug(Debug::network,__FUNCTION__) << "Create network world" << endl;
                    /* TODO: handle CLoadException here */
                    world = new NetworkWorld(sockets, players, characterToSocket, Storage::instance().find(Filesystem::RelativePath(level)), clientNames);

                    Debug::debug(Debug::network,__FUNCTION__) << "Load music" << endl;

                    Music::changeSong();

                    /* wait for an ok from all the clients, then send another
                     * ok to continue
                     */
                    waitAllOk(sockets);
                    sendAllOk(sockets);
                }
            };

            for (vector<SGF::CObject *>::const_iterator it = players.begin(); it != players.end(); it++){
                CCharacter * playerX = (CCharacter *) *it;
                playerX->setY(200);
                /* setMoving(false) sets all velocities to 0 */
                playerX->setMoving(false);
                /* but the player is falling so set it back to true */
                playerX->setMoving(true);

                playerX->setStatus(CStatus_Falling);
            }

            GameContext gameContext(level, sockets, characterToSocket, clientNames, players);
            Loader::loadScreen(gameContext, Level::convert(levelInfo));

            NetworkWorld & world = *gameContext.world;
            world.startMessageHandlers();

            bool played = Game::playLevel(world, players);

            ObjectFactory::destroy();
            HeartFactory::destroy();

            world.stopRunning();
            Message finish;
            finish << World::FINISH;
            finish.id = 0;
            Debug::debug(Debug::network,__FUNCTION__) << "Sending finish message to all clients" <<  endl;
            sendToAll(sockets, finish);
            world.waitForHandlers();

            Debug::debug(Debug::network,__FUNCTION__) << "Waiting for finish from all clients " << endl;
            waitAllFinish(sockets);

            Message ignore;
            ignore << World::IGNORE_MESSAGE;
            ignore.id = 0;
            Debug::debug(Debug::network,__FUNCTION__) << "Sending ignore to all clients" << endl;
            sendToAll(sockets, ignore);

            /* another ok barrier */
            Debug::debug(Debug::network,__FUNCTION__) << "Wait for all clients to ok" << endl;
            waitAllOk(sockets);
            sendAllOk(sockets);

            /* if the server quits, then everyone quits */
            if (!played){
                Debug::debug(Debug::network,__FUNCTION__) << "Server exiting early.." << endl;
                break;
            }
        }
        Network::Message gameOver;
        gameOver.id = 0;
        gameOver << World::GAME_OVER;
        sendToAll(sockets, gameOver);
    } catch ( const CLoadException & le ){
        Debug::debug(Debug::error,__FUNCTION__) << "Load exception: " + le.getTrace() << endl;
    } catch ( const Exception::Return & re ){
    } catch ( const Exception::CNetworkException & ne ){
        Debug::debug(Debug::error,__FUNCTION__) << "Network excetion: " + ne.getMessage() << endl;
    }

    for ( vector< SGF::CObject * >::iterator it = players.begin(); it != players.end(); it++ ){
        delete *it;
    }

    for ( vector<CNetClient*>::const_iterator it = clients.begin(); it != clients.end(); it++ ){
        Network::close((*it)->getSocket());
    }
}

static void popup( const CFont & font, const string & message ){
	int length = font.textLength( message.c_str() ) + 20;
        CBitmap background(Global::titleScreen().path());
        CBitmap area( background, background.getWidth() / 2 - length / 2, 220, length, font.getHeight() * 3 );
        CBitmap::transBlender( 0, 0, 0, 128 );
	// area.drawingMode( Bitmap::MODE_TRANS );
	area.translucent().rectangleFill( 0, 0, area.getWidth(), area.getHeight(), Colors::makeColor( 64, 0, 0 ) );
	// area.drawingMode( Bitmap::MODE_SOLID );
        int color = Colors::makeColor( 255, 255, 255 );
	area.polygon().rectangle( 0, 0, area.getWidth() - 1, area.getHeight() - 1, color );
	font.printf( 10, area.getHeight() / 2, Colors::makeColor( 255, 255, 255 ), area, message, 0 );
        background.BlitToScreen();
}
#endif
void networkServer(){

    // const int startingLives = 4;
    int port = getServerPort();

    // Keyboard key;

    Debug::debug(Debug::network,__FUNCTION__) << "Port is " << port << endl;

    //const CFont & font = *CResource::getDefaultFont();//CResource::getDefaultFont( 20, 20 );

	try{
        /*
#ifdef _WIN32
Network::blocking( false );
#endif
*/
        Debug::debug(Debug::network,__FUNCTION__) << "Get socket" << endl;
		Network::Socket server = Network::openSocket(port);

        /*
        // NLsocket server = nlOpen( port, NL_RELIABLE_PACKETS );
        if ( server == NL_INVALID ){
        Global::debug( 0 ) << "hawknl error: " << nlGetSystemErrorStr( nlGetSystemError() ) << endl;
        throw ReturnException();
        }
        */

        Debug::debug(Debug::network,__FUNCTION__) << "Run chat server" << endl;

       //s  ChatServer chat("server", server);
       //s chat.run();
        /*
#ifdef _WIN32
Network::blocking( true );
#endif
*/
     /*   vector<CNetClient*> clients = chat.getConnectedClients();
        if (! clients.empty()){
            Debug::debug(Debug::network,__FUNCTION__) << "Start game with " << clients.size() << " clients" << endl;
            playGame(clients);
        } else {
            // key.poll();
            Util::popup(font, "No clients connected" );
            CInputManager::waitForKeys(CKeyboard::Key_ENTER, CKeyboard::Key_ESC, CInputSource());
            // key.wait();
            // key.readKey();
        }  */
		Network::closeSocket( server );
    } catch ( const Exception::CNetworkException & ne ){
        Debug::debug(Debug::error,__FUNCTION__) << "Network error: " << ne.getMessage() << endl;
        // key.poll();
		ostringstream out;
        out << "Press ENTER to continue\n";
        out << "\n";
        out << "We are very sorry but an error has occured while trying to set up Network.";
		Util::showError(ne,out.str());
        //s popup(font, "Network error: " + ne.getMessage());
        CInputManager::waitForKeys(CKeyboard::Key_ENTER, CKeyboard::Key_ESC, CInputSource());
        /*
        key.wait();
        key.readKey();
        */
    }
    return;
}
}
} //end SGF
#endif
