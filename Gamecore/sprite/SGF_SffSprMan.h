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

#ifndef SFFSPRITEMANAGER_H_
#define SFFSPRITEMANAGER_H_
#include <stdio.h>
#include "../SGF_Global.h"
#include "../util/AirManager.h"
#include "../graphics/all.h"
#include <string.h>
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../lists/all.h"
#include "SGF_SffManager.h"
#include "defs.h"
#include "SGF_MugenSprite.h"
#include "../SGF_Config.h"
#include "../graphics/SGF_Color.h"


using namespace std;
namespace SGF{
//class CSFFManager;
class CMugenSprite;

/**
 * \class CMugenSprite
 *
 * \ingroup SGF_Sprite
 *
 * \brief Gerenciador de sprites retirados de arquivos SFF
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CSffSpriteManager :public CSFFManager
{
//Public Functions
public:
	CSffSpriteManager(const char* strFileName);
	CSffSpriteManager();
	~CSffSpriteManager();
	PCXDATA *GetPCXSprite(unsigned int nGroupNumber,unsigned int nImageNumber);

	// Cria um objeto CMugenSprite que precisa ser deletado em algum momento
	Util::CReferenceCount<CMugenSprite> getMugenSprite(int groupNumber,int spriteNumber,bool mask);

	//!extract the PCX images from the sff file for the ColorPallet file
	void getSpritesforPalette(const char* strFileName);
    void getMugenSprites(Mugen::SpriteMap &sprites);

protected:
	//Quem irá deletar estes sprites??????
	Mugen::SpriteMap  SpriteList;
	void getMugenSpritesFromPCX();

};
} //end SGF
#endif /*SFFSPRITEMANAGER_H_*/
