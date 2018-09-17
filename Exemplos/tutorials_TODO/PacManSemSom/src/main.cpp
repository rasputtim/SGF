//    Open Mugen is a redevelopment of Elecbyte's M.U.G.E.N wich will be 100% compatible to it
//    Copyright (C) 2004  Sahin Vardar
//
//    If you know bugs or have a wish on Open Muegn or (money/girls/a car) for me ;-)
//    Feel free and email me: sahin_v@hotmail.com  ICQ:317502935
//    Web: http://openmugen.sourceforge.net/
//    --------------------------------------------------------------------------
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifdef WIN32
//#pragma comment(lib, "SDL.lib")
//#pragma comment(lib, "SDLmain.lib")
#endif


#include <io.h>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include "game.h"
#include "PacGlobal.h"
#include "Settings.h"

//#include <libintl.h>
//#include <locale.h>
//#define _(String) gettext (String)

using namespace std;
using std::set_terminate;
using std::set_unexpected;
using std::set_new_handler;

CPacConfiguration settings;
Debug::CLog		logtxt;
Game	game;

//This is for the normal PC
//The programm entry point
int main(int argc,char *argv[])
{



    //usado no sistema de debug
   //codigo para enviar coout para arquivo
	std::string str="",level="",skin="",editfile="";
    bool editor=false;

	ofstream file;
	file.open ("log_pacman.txt");
    streambuf* sbuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());
	// Setta o nivel de debug que queremos no sistema
	Debug::setDebugAll();
	//Debug::setDebug(Debug::input);
	//Debug::setDebug(Debug::bitmap);
	//Debug::debug(1,__FUNCTION__) << gettext("Debug mode test") << "  " << gettext("TEST OK") << endl;

	Global::InitExceptions();
	//Codigo para o gettext
	//char *locale =setlocale( LC_ALL, "" );
	//printf("locale = %s\n",locale);
	//bindtextdomain( "openmugen", "data\\locale" );
    //textdomain( "openmugen" );
    //Debug::debug(20) <<  gettext("TEST OK") <<endl;
    //teste xmltools
	//XmlTools::XmlParseFile("data\\teste.xml");
	//todo resolver problena na hoara do debug qdo carrega Tokens
	//CTokenReaderXML reader("data\\menu\\main.xml");
   // Token * head = reader.readToken();

	//TokenReader reader2("data\\main.txt");
    //Token * head2 = reader2.readToken();


	/* teste listagem de arquivos do file system
	list<FILELIST> MyList;
	string path;
	cout << "Enter starting path ... ";
	getline(cin,path);
	Filesystem::TransverseDirectory(path,MyList);
	list<FILELIST>::iterator it;
	for(it = MyList.begin(); it != MyList.end(); it++)
	{
		vector<string>::iterator its;
		for(its = (*it).theList.begin(); its != (*it).theList.end(); its++)
		{
			cout << (*it).path + "\\" + (*its) << endl;
		}

	}
	cin.ignore();
	*/
	//! Define o Tamanho da Janela que será criada
	//! Deve ser feito antes de inicializar o objeto CPacGameControl

	settings.loadConfigurations();

	if ( !settings.fieldwidth || !settings.fieldheight || !settings.tilesize ) {
            Debug::debug(Debug::gameEngine,__FUNCTION__) << "fieldheight/fieldwidth/tilesize is not set, reverting to default window dimensions";
        }
        else {

				settings.setScreenHeight((settings.fieldheight*settings.tilesize)+EXTRA_Y_SPACE);

				settings.setScreenWidth(settings.fieldwidth*settings.tilesize);

        }

		//init settings

	//Init the game
	CPacGameControl *m_GameControl =new CPacGameControl();

	game.setGameControl(m_GameControl);
	//init window
	if ( !m_GameControl->getQuit() ) m_GameControl->initWindow();


   //set editorpath
    if ( editfile!="" ) {
        game.setEditorPath("./levels/" + editfile + "/");
    }

    //init game class
    if ( !m_GameControl->getQuit() ) game.gameInit(level,skin,editor);

	try {
    //main loop
    while ( ! m_GameControl->getQuit() ) {

		game.run(game);

    }
	}catch(...) {

	}
	delete m_GameControl;
    //shutdown
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "Shutdown" <<endl;

	/*
	bool mugen=false;
	bool normal_quit=false;
	bool just_network_server = false;
	bool allow_quit = true;
	while(true) {
				m_Game->setTitle( gettext("Loading...") );
				m_Game->runMenu();
				m_Game->setTitle( gettext("Quitting...") );

	 try{
            // fadein from white
            //Menu game(true, Bitmap::makeColor(255, 255, 255));
            //game.load(mainMenuPath());
            if (just_network_server){
#ifdef HAVE_NETWORKING
                Network::networkServer();
#endif
            } else if (networkJoin.enabled){
                string port = networkJoin.port;
                string host = networkJoin.host;
                string name = networkJoin.name;
                if (port == ""){
                    /// FIXME: replace 7887 with a constant
                 //   port = CConfiguration::getStringProperty(Network::propertyLastClientPort, "7887");
                }
                if (host == ""){
                //    host = CConfiguration::getStringProperty(Network::propertyLastClientHost, "127.0.0.1");
                }
                if (name == ""){
                //    name = CConfiguration::getStringProperty(Network::propertyLastClientName, "player");
                }
                Debug::debug(1) << "Client " << name << " " << host << " " << port << endl;
                //try{
                   // Network::runClient(name, host, port);
                //} catch (const Network::NetworkException & fail){
                 //   Debug::debug(Debug::error) << "Error running the network client: " << fail.getMessage() << endl;
                //}
            } else if (mugen){
                //setMugenMotif(mainMenuPath());
               // Mugen::run();
            } else if (mugenInstant.enabled && mugenInstant.kind == MugenInstant::Training){
            //    setMugenMotif(mainMenuPath());
            //    runMugenTraining(mugenInstant.player1, mugenInstant.player2, mugenInstant.stage);
            } else if (mugenInstant.enabled && mugenInstant.kind == MugenInstant::Watch){
            //    setMugenMotif(mainMenuPath());
            //    runMugenWatch(mugenInstant.player1, mugenInstant.player2, mugenInstant.stage);
            } else {
				m_Game->setTitle( gettext("Loading...") );
				m_Game->runMenu();
				m_Game->setTitle( gettext("Quitting...") );

            }
            normal_quit = true;
        } catch (const Filesystem::CException & ex){
            Debug::debug(Debug::error) << "There was a problem loading the main menu. Error was:\n  " << ex.getTrace() << endl;
        } catch (const CTokenException & ex){
            Debug::debug(Debug::error) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
            return -1;
        } catch (const LoadException & ex){
            Debug::debug(Debug::error) << "There was a problem loading the main menu. Error was:\n  " << ex.getTrace() << endl;
            return -1;
        } catch (const Exception::Return & ex){
        } catch (const CShutdownException & shutdown){
            Debug::debug(1) << "Forced a shutdown. Cya!" << endl;
        } catch (const CMugenException & m){
            Debug::debug(Debug::error) << "Mugen exception: " << m.getReason() << endl;
        } catch (const CReloadMenuException & ex){
            Debug::debug(Debug::error) << "Menu Reload Requested. Restarting...." << endl;
            continue;
        } catch (const Exception::CBase & base){
            // Global::debug(0) << "Freetype exception caught. Error was:\n" << ex.getReason() << endl;
            Debug::debug(Debug::error) << "Base exception: " << base.getTrace() << endl;
        } catch (const std::bad_alloc & fail){
           //Debug::debug(Debug::error) << "Failed to allocate memory. Usage is " << System::memoryUsage() << endl;
        } catch (...){
            Debug::debug(Debug::error) << "Uncaught exception!" << endl;
        }

        if (allow_quit && normal_quit){
            break;
        } else if (normal_quit && !allow_quit){
        } else if (!normal_quit){
            break;
        }


	}

    //CConfiguration::saveConfiguration();
	m_Game->quit();
    Debug::debug(Debug::error) << "Bye!" << endl;
    return 0;
	*/

	return 0;
}



