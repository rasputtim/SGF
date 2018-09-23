

//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include <io.h>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include "game.h"
#include "TutGlobal.h"


using namespace std;
using std::set_terminate;
using std::set_unexpected;
using std::set_new_handler;

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
	file.open ("log_tut_01.txt");
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
	//! Define o Tamanho da Janela que ser� criada
	//! Deve ser feito antes de inicializar o objeto CTutGameControl

	//Define o Tamanho da Janela
	CConfiguration::screenHeight.setInteger(300);

	CConfiguration::screenWidth.setInteger(300);

		//init settings

	//Init the game
	CTutGameControl *m_GameControl =new CTutGameControl();

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


