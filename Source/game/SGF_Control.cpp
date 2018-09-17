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



#include "game/SGF_Control.h"


using namespace std;
namespace SGF {

//Constructor
CGameControl::CGameControl():
pSdlManager(NULL), //nao inicializa nada só cria o objeto
bError(false),
    bGame(true),
    nStartTime(0),
	nEndTime(0),
	janitor(NULL),  //init the collector
	pCurInputManager(NULL)
{
	pSdlManager=CSDLManager::GetInstance();
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "Welcome to SGF Version: " << VER <<endl;
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "START LOADING CONFIGURATIONS (CConfiguration)================" << endl;
    // Carrega as Configurações padrao do SGF
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "Welcome to SGF Version: " << VER <<endl;
    CConfiguration::loadConfigurations(); //carrega também as configurações de debug

	Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN CREATING JANITOR (GARBAGE COLLECTOR)================" << endl;
    
	janitor = new CCollector();
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END CREATING JANITOR (GARBAGE COLLECTOR)================" << endl;
   
	
	//Set Debug Level
	//Primeiro inicializa o sistema de logs
	//Global::InitLogFile();
    //Now print Welcome Message
    
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "END LOADING CONFIGURATIONS (CConfiguration)================" << endl;
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "START LOADING MOD (OpenMugen::Mod)================" << endl;

	// Carrega o modelo do Jogo
	SGF::Mod::loadMod(CConfiguration::gameModDir.getString());//getcurrentgame retorna o diretório default do jogo
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "END LOADING MOD (OpenMugen::Mod)================" << endl;
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "START SDL PHASE 1 (CSDLMANAGER)================" << endl;

	//Now init SDL system
	// Need to Setup window parameters here
	CGlobalConfiguration::getsdlConfig()->window_infos[0]->w=CConfiguration::screenWidth.getInteger();
	CGlobalConfiguration::getsdlConfig()->window_infos[0]->h=CConfiguration::screenHeight.getInteger();

   
    if(!pSdlManager->Init())
    {
        Debug::debug(Debug::gameEngine,__FUNCTION__) << "SDL Initialization failed" << endl;
        bError=true;

    }

   Debug::debug(Debug::gameEngine,__FUNCTION__) << "END STARTING SDL PHASE 1 (CSDLMANAGER)================" << endl;
   Debug::debug(Debug::gameEngine,__FUNCTION__) << "START SDL PHASE 2 (CSDLMANAGER)================" << endl;
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "WILL INIT THE NECESSARY WINDOWS (Screens)================" << endl;

	// Init Window (Screen) System
	if(!pSdlManager->InitWindows())
    {
        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Window Initialization failed" << endl;
        bError=true;

    }
		//======================
	// Create Work surface

		if (CBitmap::_my_state !=NULL) {
		work = CBitmap::_my_state->Screen[0];
		} else work=NULL;
		//limpa as janelas existentes
//		for (int i=0;i<=(CSDLManager::GetInstance()->state->num_windows-1);i++) {
			//CBitmap::_my_state->Screen[i]->fill(0,0,255,255);
//		}

	/* initialize random number generator */
    srand( time( NULL ) );

    //Restet the Game timer
	Global::ResetGameTimer();
	//init the collector
	//CCollector janitor;
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END SDL PHASE 2 (CSDLMANAGER)================" << endl;
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "END CONSTRUCTING CGAME OBJECT ================" << endl;
	pCurInputManager = CInputManager::GetInstance();
}

//Destructor
CGameControl::~CGameControl()
{
Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN Cleaning Up" << endl;

	if (janitor) delete janitor;
	if (pSdlManager) delete pSdlManager;
	if (pCurInputManager!=NULL) delete pCurInputManager;
	janitor = NULL;
	pCurInputManager=NULL;
	pSdlManager = NULL;
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END Cleaning Up" << endl;
}




void CGameControl::setTitle(const char* czTitle)
{
	m_Title = czTitle;
	//todo converto to sdl 2.0
	//SDL_WM_SetCaption( m_Title, 0 );
}


//Exit the game and cleans the memory and SDL
void CGameControl::quit()
{
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "Quitting Game" << endl;
	pSdlManager->CleanSDL(); //apaga audio e video data
}

void CGameControl::crash()
{
  Debug::debug(Debug::gameEngine,__FUNCTION__) << "Crashing Game" << endl;
  pSdlManager->CleanSDL();
  SDL_Quit();
}
} //end SGF