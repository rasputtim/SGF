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
#ifndef _S_G_F_GAME_CONTROL_H_
#define _S_G_F_GAME_CONTROL_H_

#include <time.h>
#include "../SGF_Config.h"
#include "../gui/SGF_Box.h"
#include "../graphics/SGF_Bitmap.h"
#include "../resource/SGF_Collector.h"
#include "../game/SGF_Mod.h"
#include "../util/SGF_SdlManager.h"
#include "../configuration/SGF_Configuration.h"

//#define _(STRING) gettext(STRING)
namespace SGF {
class CCollector;
class CBitmap;
//class Gui::CBox;
/**
 * \class CGameControl
 *
 * \ingroup SGF_Game
 *
 * \brief Esta é a classe principal de controle do jogo
 *
 * Esta Classe fornece controle sobre a tela, entrada (teclado, mouse, joystick)
 * cuida do gerenciamento do timer e frame control e outras atividades
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CGameControl
{



public:
//Contructor Destructor
    CGameControl();
    ~CGameControl();
CBitmap *work;
//Needed Variables
CSDLManager *pSdlManager;
CInputManager *pCurInputManager;  //! inicializa Input Manager
    
bool bError;
bool bGame;
float nStartTime,nEndTime;
float nFrameRate;
virtual int runMenu()=0;
virtual bool loadConfiguration()=0;
void quit();
void crash();
void	setTitle	(const char* Title);

private:
	/** The title of the window **/
	const char* m_Title;
	/** garbage collection ? **/
	CCollector *janitor;


};

} //end SGF


#endif /*GAME_H_*/
