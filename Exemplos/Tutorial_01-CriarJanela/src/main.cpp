

#include "../../../Gamecore/SGF.h"
//#include <io.h>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include "Game.h"

using namespace std;
using std::set_terminate;
using std::set_unexpected;
using std::set_new_handler;

SGF::Debug::CLog		logtxt;
Game	game;

//This is for the normal PC
//The programm entry point
int main(int argc,char *argv[])
{



    //usado no sistema de debug
   //codigo para enviar coout para arquivo
	#undef open;
	std::ofstream file;
	file.open("log_pacman.txt");
    cout.rdbuf(file.rdbuf());
	// Setta o nivel de debug que queremos no sistema
	SGF::Debug::setDebugAll();

	SGF::Global::InitExceptions();

	//Define o Tamanho da Janela
	SGF::CConfiguration::screenWidth.setInteger(300);

	SGF::CConfiguration::screenHeight.setInteger(300);

		//init settings

	//Init the game
	CTutGameControl *m_GameControl =new CTutGameControl();

	game.setGameControl(m_GameControl);
	//init window
	if ( !m_GameControl->getQuit() ) m_GameControl->initWindow();


     //init game class
    if ( !m_GameControl->getQuit() ) game.gameInit();

	try {
    //main loop
    while ( ! m_GameControl->getQuit() ) {

		game.run(game);

    }
	}catch(...) {

	}
	//delete m_GameControl;
    //shutdown
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "Shutdown" <<endl;


	
	return 0;
}



