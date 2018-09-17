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


#include "sprite/SGF_SffSprMan.h"
#include "graphics/all.h"
#include "util/SGF_Debug.h"
#include "../../ExternalLibs/SDL2_image-2.0.0/SDL_image.h"
using namespace std;
namespace SGF {

CSffSpriteManager::CSffSpriteManager()
{

}
CSffSpriteManager::CSffSpriteManager(const char* strFileName):
CSFFManager(strFileName,NULL)
{
	Debug::debug(Debug::resources,__FUNCTION__) << "CSffSpriteManager::CSffSpriteManager = " << strFileName<< endl;
	//getMugenSpritesFromPCX();
}

CSffSpriteManager::~CSffSpriteManager()
{
    
}

//Set the ColorPallet file the pcx images and extract the images from the sff file
void CSffSpriteManager::getSpritesforPalette(const char* strFileName)
{
	this->set_act_file(string(strFileName));
	this->set_use_act(true);
	this->extract();
	this->getMugenSpritesFromPCX();

}


PCXDATA *CSffSpriteManager::GetPCXSprite(unsigned int nGroupNumber,unsigned int nImageNumber) {
	return this->PCXList[nGroupNumber][nImageNumber];
}


//Cria um objeto CMugenSprite
Util::CReferenceCount<CMugenSprite> CSffSpriteManager::getMugenSprite(int groupNumber,int spriteNumber,bool mask) {
	PCXDATA *tempPCXDATA = GetPCXSprite(groupNumber,spriteNumber);

	if (tempPCXDATA) {
		return Util::CReferenceCount<CMugenSprite>(new CMugenSpriteV1(tempPCXDATA,mask));

	} else return Util::CReferenceCount<CMugenSprite>(NULL);

}
void CSffSpriteManager::getMugenSprites(Mugen::SpriteMap &sprites) {
	
	Debug::debug(Debug::objects,__FUNCTION__) << "Copia todos os sprites e preenche o Mapa SpriteMap"<< endl;
	for (Mugen::SpriteMap::iterator first_it = SpriteList.begin(); first_it != SpriteList.end(); first_it++){
		for(map<unsigned int, Util::CReferenceCount<CMugenSprite> >::iterator it = first_it->second.begin();it != first_it->second.end();it++){
			Util::CReferenceCount<CMugenSprite> temp= this->SpriteList[(*it).second->getGroupNumber()][(*it).second->getImageNumber()];
			Debug::debug(Debug::objects,__FUNCTION__) << "Copiando imagem (Grupo,Imagem) = ( "<<(*it).second->getGroupNumber() << " , "<<(*it).second->getImageNumber() <<" ) [ CMugemSprite: "<< temp.raw() << " ]"<< endl;
		   	sprites[(*it).second->getGroupNumber()][(*it).second->getImageNumber()] =  temp;
		}
    }
	
}

void CSffSpriteManager::getMugenSpritesFromPCX() {
	
	Debug::debug(Debug::objects,__FUNCTION__) << "Copia todos os sprites e preenche o Mapa SpriteMap"<< endl;
	for (PCXDATAMap::iterator first_it = PCXList.begin(); first_it != PCXList.end(); first_it++){
		for(map< unsigned int, PCXDATA*>::iterator it = first_it->second.begin();it != first_it->second.end();it++){
			PCXDATA* tempPCXDATA= this->PCXList[(*it).second->GroupNumber][(*it).second->ImageNumber];
			int group= (*it).second->GroupNumber;
			int imagenumber= (*it).second->ImageNumber;
			//sprites[(*it).second->GroupNumber][(*it).second->ImageNumber] =  temp;
			// Cria um novo Sprite e adiciona ao mapa
			Debug::debug(Debug::resources,__FUNCTION__) << "Adding Sprite to spritelist (Group,Image)"<<" ( "<<tempPCXDATA->GroupNumber <<" , "<<tempPCXDATA->ImageNumber <<" )" << endl;
			SpriteList[group][imagenumber] =  new CMugenSpriteV1(tempPCXDATA,false);
		}
    }
	
}


}//end SGF