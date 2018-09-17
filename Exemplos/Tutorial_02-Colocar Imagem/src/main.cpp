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

//#include <libintl.h>
//#include <locale.h>
//#define _(String) gettext (String)

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
	#undef open
	ofstream file;
	file.open ("log_pacman.txt");
    cout.rdbuf(file.rdbuf());
	// Setta o nivel de debug que queremos no sistema
	SGF::Debug::setDebugAll();
	//Debug::setDebug(Debug::input);
	//Debug::setDebug(Debug::bitmap);
	//Debug::debug(1,__FUNCTION__) << gettext("Debug mode test") << "  " << gettext("TEST OK") << endl;

	
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
	//! Deve ser feito antes de inicializar o objeto CTutGameControl

	//Define o Tamanho da Janela
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
	
    //shutdown
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "Shutdown" <<endl;

	
	return 0;
}



