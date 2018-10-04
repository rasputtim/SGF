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


#include "resource/SGF_ResourceManager.h"
#include "util/SGF_FontInfo.h"
#include "../Gamecore/compiler/DefCompiler/def_driver.h"
#include "../Gamecore/compiler/CMDCompiler/cmd_driver.h"
#include "../Gamecore/compiler/AirCompiler/air_driver.h"
#include "../Gamecore/compiler/COMCompiler/com_driver.h"
#include "../Gamecore/mugen/ast/astManager.h"




using namespace std;
namespace SGF{

//antes de usar deve inicializar a classe collector primeiro
CResource * CResource::my_resource = NULL;
//std::list<Util::Thread::NamedThread *> CResource::threadList;
std::list<Ast::CCollectable> CResource::saved_pointers;
list<Ast::CSection*> * CResource::copy(list<Ast::CSection*> * input){
    list<Ast::CSection*> * output = new list<Ast::CSection*>();

    for (list<Ast::CSection*>::iterator it = input->begin(); it != input->end(); it++){
        output->push_back((Ast::CSection*) (*it)->copy());
    }

    return output;
}
int CResource::getCacheSize(cacheType cache){
	switch(cache) {
		case	cachedSounds: return 10; break;
		case	cachedMusics: return 10; break;
		case	cachedDefParsedFiles: return 10; break;
		case	cachedCMDParsedFiles: return 10; break;
		case	cachedBitmaps: return 10; break;
		case	cachedPaths: return 10; break;
		case	cachedMugenSprites: return 10; break;
		case	cachedMugenSpriteMaps: return 10; break;
		case	cachedMugenSffManagers: return 10; break;
		default: return 10;
	}

};

CSound * CResource::getSound(const string & path) throw (Exception::Filesystem::CNotFound){
    Debug::debug(Debug::resources,__FUNCTION__) << path << endl;
    if (path.length() == 0){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getSound(path);


}

CSound * CResource::getSound(const Filesystem::CRelativePath & path) throw (Exception::Filesystem::CNotFound){

    Debug::debug(Debug::resources,__FUNCTION__) << "Start to Load: " << path.path() << endl;
	if (!path.exist()){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
		return NULL;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo
	Filesystem::CAbsolutePath temp= Filesystem::CAbsolutePath(path);
	return my_resource->_getSound(temp);


}

void CResource::getMugenSounds(const string & filename, MugenSoundMap & m_sounds){
   Debug::debug(Debug::resources,__FUNCTION__) << filename << endl;
    if (filename.length() == 0){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getMugenSounds(filename,m_sounds);


}

CBitmap * CResource::getBitmap(const string & path) throw (Exception::Filesystem::CNotFound){
	Debug::debug(Debug::resources,__FUNCTION__) << "Start to Load: " << path << endl;
    if (path.length() == 0){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");

	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getBitmap(path);

}


CBitmap * CResource::getBitmap(const Filesystem::CAbsolutePath &path) throw (Exception::Filesystem::CNotFound){
	Debug::debug(Debug::resources,__FUNCTION__) << "Start to Load: " << path.path() << endl;
	if (!path.exist()){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
		return NULL;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getBitmap(path);

}

CBitmap * CResource::getBitmap(const Filesystem::CRelativePath &path) throw (Exception::Filesystem::CNotFound){
	Debug::debug(Debug::resources,__FUNCTION__) << "Start to Load: " << path.path() << endl;
	if (!path.exist()){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
		return NULL;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo
	Filesystem::CAbsolutePath temp= Filesystem::CAbsolutePath(path);
	return my_resource->_getBitmap(temp);

}
/*
CTTFFont * CResource::getTTFont(const string & path,int ptsize) throw (Exception::Filesystem::CNotFound){
    Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // fonte:" <<path<< endl;
	if (path.length() == 0){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
		return NULL;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getTTFont(path,ptsize);

}
*/
CTTFFont * CResource::getDefaultFont(){

    string font( WORKFONT);
	return (CTTFFont *)my_resource->_getTTFont(font , 16,16);
}

CTTFFont * CResource::getDefaultFont(int x,int y){
	// return getFont( "tmp/comic.ttf" );
    return (CTTFFont *)my_resource->_getTTFont( WORKFONT ,x,y );
}

CTTFFont * CResource::getTTFont(const string & path,int width, int height) throw (Exception::Filesystem::CNotFound){
    //Todo: convert width e height to ptsize

	Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // fonte:" <<path<< endl;
	if (path.length() == 0){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");

	 }
	//int pt_size=Util::getPtSize(width,height);
	//return my_resource->_getTTFont(path,pt_size);
	return (CTTFFont *) my_resource->_getTTFont(path,width, height);
}

CBitmapFont * CResource::getBitmapFont(const string & path,int width, int height) throw (Exception::Filesystem::CNotFound){

	Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // fonte:" <<path<< endl;
	if (path.length() == 0){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");
		return NULL;
	 }
	return (CBitmapFont *)my_resource->_getBitmapFont(path,width, height);

}
CSffSpriteManager * CResource::getSffSpriteManager(const Filesystem::CAbsolutePath & filename,const Filesystem::CAbsolutePath & palette, bool mask){
	Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // file:" <<filename.path()<< endl;
	if (!filename.exist()){
		ostringstream out;
	    out << "CAbsolutePath Cannot find " << filename.path() <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
	}
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getSffSpriteManager(filename,palette,mask);

}

void CResource::getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath & filename, const SGF::Filesystem::CAbsolutePath & palette, SGF::Mugen::SpriteMap & sprites, bool mask){
		Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // file:" <<filename.path()<< endl;
	if (!filename.exist()){
		ostringstream out;
	    out << "CAbsolutePath Cannot find " << filename.path() <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
	}
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getMugenSpriteMap(filename,palette,sprites, mask);
}

Mugen::SpriteMap CResource::getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath &filename,  bool mask, const SGF::Filesystem::CAbsolutePath & palette){
	Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // file:" <<filename.path()<< endl;
	if (!filename.exist()){
		ostringstream out;
	    out << "CAbsolutePath Cannot find " << filename.path() <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
	}
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getMugenSpriteMap(filename, mask,palette);


}
Util::CReferenceCount<CMugenSprite> CResource::getMugenSprite(const SGF::Filesystem::CAbsolutePath &filename, int groupNumber, int spriteNumber, bool mask, const SGF::Filesystem::CAbsolutePath & palette){
	Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // file:" <<filename.path()<< endl;
	if (!filename.exist()){
		ostringstream out;
	    out << "CAbsolutePath Cannot find " << filename.path() <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
	}
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getMugenSprite(filename, groupNumber, spriteNumber, mask,palette);


}



Filesystem::CAbsolutePath & CResource::getPath(const string & path) throw (Exception::Filesystem::CNotFound) {//throw (LoadException){
    Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // file:" <<path<< endl;
	 if (path.length() == 0){
		  ostringstream out;
	     out << "CAbsolutePath Cannot find " << path <<endl;
	     throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
	 }
	return my_resource->_getPath(path);

}
Filesystem::CAbsolutePath & CResource::getPath(char &file) {//throw (LoadException){
    Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // file:" <<file<< endl;

	string temp = temp.assign(&file);
	if (temp!="")
	return my_resource->_getPath(temp);
	else {
		//report error
	}
}

Filesystem::CAbsolutePath & CResource::getPath(Filesystem::CAbsolutePath &path) throw (Exception::Filesystem::CNotFound){
	try {
	return my_resource-> _getPath(path.path());
	}catch (Exception::Filesystem::CNotFound &ex) {
		throw ex;
	}
}
Filesystem::CAbsolutePath & CResource::getPath(Filesystem::CRelativePath &path) throw (Exception::Filesystem::CNotFound){
	try {
	return my_resource-> _getPath(path.path());
	}catch (Exception::Filesystem::CNotFound &ex) {
		throw ex;
	}
}

const CFont & CResource::getFont(const string & path,int width, int height){
    Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // fonte:" <<path<< endl;
	if (path.length() == 0){
		//throw NotFound("Filesystem::getInstance().find - No path given");
		//todo throw an exception
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getFont(path, width,  height);

}

SGF::Util::CReferenceCount<SGF::Ast::CAstManager> CResource::getDEFParsedFile(const Filesystem::CAbsolutePath & path){
	 Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // path:" <<path.path()<< endl;
	 if (!path.exist()){
		throw Exception::Filesystem::CNotFound(__FUNCTION__,__LINE__," No path given");

	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getDEFParsedFile(path);
}

SGF::Util::CReferenceCount<SGF::Ast::CAstManager>  CResource::getAIRParsedFile(const Filesystem::CAbsolutePath & path){

	if (path.isEmpty()){
		//throw NotFound("Filesystem::getInstance().find - No path given");
		//return NULL;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getAIRParsedFile(path);
}

SGF::Util::CReferenceCount<SGF::Ast::CAstManager>  CResource::getCMDParsedFile(const Filesystem::CAbsolutePath & path){

	if (path.isEmpty()){
		//throw CNotFound("Filesystem::getInstance().find - No path given");
		//return;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo
	//Wait lock to be released

	return my_resource->_getCMDParsedFile(path);
}
SGF::Util::CReferenceCount<SGF::Ast::CAstManager>  CResource::getCOMParsedFile(const Filesystem::CAbsolutePath & path){

	if (path.isEmpty()){
		//throw CNotFound("Filesystem::getInstance().find - No path given");
		//return;
	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo
	//Wait lock to be released

	return my_resource->_getCOMParsedFile(path);
}

SGF::Util::CReferenceCount<SGF::Ast::CAstManager>  CResource::getCMDParsedString(const string & string){

	if (string.empty()){
		Debug::debug(Debug::resources,__FUNCTION__) << "ERROR // String is Empty"<<endl;
		//throw CNotFound("Filesystem::getInstance().find - No path given");

	 }
	//Todo: Verificar se o caminho é completo, senão adicionar o caminho completo ao arquivo

	return my_resource->_getCMDParsedString(string);
}

CMusic *  CResource::getMusic(const Filesystem::CRelativePath & path){
	return my_resource->_getMusic(path);
}
Util::CSmartPtr_MT<CMusic>  CResource::getMusic(const Filesystem::CAbsolutePath & path){
	return my_resource->_getMusic(path);
}

/* the resource is created in the CCollector */
CResource::CResource():
my_musicInstance(NULL){
my_resource = this;

}

CResource::~CResource(){
	// Release CMugenSound
	for (NamedMugenSoundMap::iterator it = my_mugenSounds.begin(); it != my_mugenSounds.end(); it++){
        if ((*it).second)delete (*it).second;
    }

    for (map<string, CSound*>::iterator it = my_sounds.begin(); it != my_sounds.end(); it++){
        if ((*it).second)delete (*it).second;
    }

    for (map<string, CBitmap*>::iterator it = my_bitmaps.begin(); it != my_bitmaps.end(); it++){
        if ((*it).second)delete (*it).second;
    }
	 for (map<string, Filesystem::CAbsolutePath*>::iterator it = my_files.begin(); it != my_files.end(); it++){
        if ((*it).second)delete (*it).second;
    }


	for (map<string, Ast::CAstManager*>::iterator it = my_defParses.begin(); it != my_defParses.end(); it++){
        if ((*it).second)delete (*it).second;
    }

   for (map<string, Ast::CAstManager*>::iterator it = my_comParses.begin(); it != my_comParses.end(); it++){
        if ((*it).second)delete (*it).second;
    }

    for (PalletizedSffManagerMap::iterator first_it = my_sffSpriteMans.begin(); first_it != my_sffSpriteMans.end(); first_it++){
		for(map<string, CSffSpriteManager*>::iterator it = first_it->second.begin();it != first_it->second.end();it++){
                if ((*it).second)delete (*it).second;
                }
    }

/*	for (CTTFFontSizedMap::iterator first_it = ttfsizedfonts.begin(); first_it != ttfsizedfonts.end(); first_it++){
		for(map<string, CTTFFont *>::iterator it = first_it->second.begin();it != first_it->second.end();it++){
                if ((*it).second) delete (*it).second;
                }
    } */
	for (FontSizedMap::iterator first_it = my_sizedfonts.begin(); first_it != my_sizedfonts.end(); first_it++){
		for(map<string, CFont *>::iterator it = first_it->second.begin();it != first_it->second.end();it++){
                if ((*it).second)delete (*it).second;
                }
    }
	//if(musicInstance) {
	//	delete musicInstance;
	//}
}

CSound * CResource::_getSound(const string & file){
    Debug::debug(Debug::resources,__FUNCTION__) <<  file << endl;

	map<string,CSound*>::iterator it;
	it = this->my_sounds.find(file);

	if( it == this->my_sounds.end() ) {
		 Filesystem::CRelativePath cfgPath(file);
			if (cfgPath.exist()) {
				Debug::debug(Debug::menu,__FUNCTION__) << "Loading Sound Data from: " << cfgPath.completePath() <<endl;
				my_sounds[file] =  new CSound(cfgPath.completePath());
			}else {
				ostringstream out;
				out << "CRelativePath Cannot find: " << cfgPath.completePath() <<endl;
				throw Exception::Filesystem::CNotFound(__FILE__, __LINE__,out.str());
			}

			}
   return my_sounds[file];

}

CBitmap * CResource::_getBitmap(const string & file) throw (Exception::Filesystem::CNotFound){//{

	map<string,CBitmap*>::iterator it;
	it = this->my_bitmaps.find(file);

	if( it == this->my_bitmaps.end() ) {
		Filesystem::CRelativePath bitPath(file);
		if (bitPath.exist()) {
			my_bitmaps[file] =  new CBitmap(bitPath.completePath());
		}else {
			ostringstream out;
			out << "CRelativePath Cannot find: " << bitPath.completePath() <<endl;
			throw  Exception::Filesystem::CNotFound(__FILE__, __LINE__,out.str());
		}


			}
   return my_bitmaps[file];

}


 CBitmap * CResource::_getBitmap(const Filesystem::CAbsolutePath & path) throw (Exception::Filesystem::CNotFound){//{
	if (!path.exist()) throw Exception::Filesystem::CNotFound(__FILE__,__LINE__, "No Path Given");
	map<string,CBitmap*>::iterator it;
	it = this->my_bitmaps.find(path.path());

	if( it == this->my_bitmaps.end() ) {
			my_bitmaps[path.path()] =  new CBitmap(path.path());
			}
   return my_bitmaps[path.path()];

}

CSound * CResource::_getSound(const Filesystem::CAbsolutePath & file) throw (Exception::Filesystem::CNotFound){
if (!file.exist()) throw Exception::Filesystem::CNotFound(__FILE__,__LINE__, "No Path Given");


    //Todo Implementar getsound
    map<string,CSound*>::iterator it;
	it = this->my_sounds.find(file.path());

            if( it == this->my_sounds.end() ) {
		 	Debug::debug(Debug::menu,__FUNCTION__) << "Loading Sound Data from: " << file.path() <<endl;
			my_sounds[file.path()] =  new CSound(file.path());

			}
   return my_sounds[file.path()];
}
CSffSpriteManager * CResource::_getSffSpriteManager(const Filesystem::CAbsolutePath & file,const Filesystem::CAbsolutePath & pallete, bool mask) {
	Debug::debug(Debug::resources,__FUNCTION__) << "set pallet and extract images:file,pallette: // " << file.path()<<" // "<<pallete.path()  << endl;
	PalletizedSffManagerMap::iterator first_it = my_sffSpriteMans.find(file.path());
            if (first_it == my_sffSpriteMans.end()){
					CSffSpriteManager *pSffSprite =	new CSffSpriteManager(file.path().c_str());
					pSffSprite->set_mask(mask);
					my_sffSpriteMans[file.path()][pallete.path()] = pSffSprite;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set pallet and extract images:file,pallette: // " << file.path()<<" // "<<pallete.path()  << endl;
					pSffSprite->getSpritesforPalette(pallete.path().c_str()); //! le o arquivo e extrai os sprites
			}else { //achou o caminho. agora achará o pallete
				map<string, CSffSpriteManager*>::iterator it = first_it->second.find(pallete.path());
                if (it == first_it->second.end()){
					CSffSpriteManager *pSffSprite =	new CSffSpriteManager(file.path().c_str());
					pSffSprite->set_mask(mask);
					my_sffSpriteMans[file.path()][pallete.path()] = pSffSprite;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set pallet and extract images:file,pallette: // " << file.path()<<" // "<<pallete.path()  << endl;
					pSffSprite->getSpritesforPalette(pallete.path().c_str()); //! le o arquivo e extrai os sprites
                }
            }

	Debug::debug(Debug::resources,__FUNCTION__) << "END - SPrites Extracted from file:  " << file.path()<<" // "<<pallete.path()  << endl;

			return my_sffSpriteMans[file.path()][pallete.path()];

}

void CResource::_getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath & filename, const SGF::Filesystem::CAbsolutePath & palette, SGF::Mugen::SpriteMap & mySpritemap, bool mask){

Debug::debug(Debug::resources,__FUNCTION__) << "set pallet and extract images:file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
			CSffSpriteManager * spritemanager= CResource::_getSffSpriteManager(filename,palette,mask);
			map< string, Mugen::SpriteMap>::iterator it;
			PalletizedSffFileSpriteMap::iterator first_it = my_MugenSpritemaps.find(filename.path());
            if (first_it == my_MugenSpritemaps.end()){
					spritemanager->getMugenSprites(mySpritemap);
					my_MugenSpritemaps[filename.path()][palette.path()] = mySpritemap;
					Debug::debug(Debug::resources,__FUNCTION__) << "set spritemap:file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;

			}else { //achou o caminho. agora procurará o pallete
				 it= first_it->second.find(palette.path());
				//se achou o caminho e não achou o palette
                if (it == first_it->second.end()){
					spritemanager->getMugenSprites(mySpritemap);
					my_MugenSpritemaps[filename.path()][palette.path()] = mySpritemap;
					Debug::debug(Debug::resources,__FUNCTION__) << "set spritemap:file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
					}else {// achou o caminho e achou o palette
					//Copia mapa de sprites
					for (Mugen::SpriteMap::iterator third_it = my_MugenSpritemaps[filename.path()][palette.path()].begin(); third_it != my_MugenSpritemaps[filename.path()][palette.path()].end(); third_it++){
							for(map<unsigned int, Util::CReferenceCount<CMugenSprite> >::iterator fouth_it = third_it->second.begin();fouth_it != third_it->second.end();fouth_it++){
								Util::CReferenceCount<CMugenSprite> temp= this->my_MugenSpritemaps[filename.path()][palette.path()][(*fouth_it).second->getGroupNumber()][(*fouth_it).second->getImageNumber()];
								Debug::debug(Debug::objects,__FUNCTION__) << "Copiando imagem (Grupo,Imagem) = ( "<<(*fouth_it).second->getGroupNumber() << " , "<<(*fouth_it).second->getImageNumber() <<" ) [ CMugemSprite: "<< temp.raw() << " ]"<< endl;
		   						mySpritemap[(*fouth_it).second->getGroupNumber()][(*fouth_it).second->getImageNumber()] =  temp;
							}

					}
				}

				// copia mapa de sprites
				Debug::debug(Debug::objects,__FUNCTION__) << "Copia todos os sprites e preenche o Mapa SpriteMap"<< endl;
				for (Mugen::SpriteMap::iterator third_it = my_MugenSpritemaps[filename.path()][palette.path()].begin(); third_it != my_MugenSpritemaps[filename.path()][palette.path()].end(); third_it++){
				for(map<unsigned int, Util::CReferenceCount<CMugenSprite> >::iterator fouth_it = third_it->second.begin();fouth_it != third_it->second.end();fouth_it++){
					Util::CReferenceCount<CMugenSprite> temp= this->my_MugenSpritemaps[filename.path()][palette.path()][(*fouth_it).second->getGroupNumber()][(*fouth_it).second->getImageNumber()];
					Debug::debug(Debug::objects,__FUNCTION__) << "Copiando imagem (Grupo,Imagem) = ( "<<(*fouth_it).second->getGroupNumber() << " , "<<(*fouth_it).second->getImageNumber() <<" ) [ CMugemSprite: "<< temp.raw() << " ]"<< endl;
		   			mySpritemap[(*fouth_it).second->getGroupNumber()][(*fouth_it).second->getImageNumber()] =  temp;
					}
				}
			}

}


Util::CReferenceCount<CMugenSprite> CResource::_getMugenSprite(const SGF::Filesystem::CAbsolutePath &filename, int groupNumber, int spriteNumber, bool mask, const SGF::Filesystem::CAbsolutePath & palette){
	CSffSpriteManager * spritemanager= CResource::_getSffSpriteManager(filename,palette,mask);


	Mugen::SpriteMap mySpritemap;
			map< string, Mugen::SpriteMap>::iterator it;
			Mugen::SpriteMap::iterator sprMapIt;
			Mugen::GroupMap::iterator sprImgIt;
			PalletizedSffFileSpriteMap::iterator first_it = my_MugenSpritemaps.find(filename.path());
            if (first_it == my_MugenSpritemaps.end()){ //não achou o filename
				my_MugenBitmaps[filename.path()][palette.path()][groupNumber][spriteNumber] = spritemanager->getMugenSprite(groupNumber,spriteNumber, mask);
					 Debug::debug(Debug::resources,__FUNCTION__) << "set sprite for :file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;

			}else { //achou o filename. agora procurará o pallete
				 it= first_it->second.find(palette.path());
				//se achou o filename e não achou o palette
                if (it == first_it->second.end()){
						 my_MugenBitmaps[filename.path()][palette.path()][groupNumber][spriteNumber] = spritemanager->getMugenSprite(groupNumber,spriteNumber, mask);
					 Debug::debug(Debug::resources,__FUNCTION__) << "set sprite for :file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
				}else {// achou o caminho e achou o palette. vai procurar o grupo
					   /*
					   typedef map< unsigned int, Util::CReferenceCount<CMugenSprite> > GroupMap;
						typedef map< unsigned int, GroupMap> SpriteMap;
						*/
					   sprMapIt = it->second.find(groupNumber);
					   // se não achou o grupo, cria
					   if (sprMapIt == it->second.end()){
						 my_MugenBitmaps[filename.path()][palette.path()][groupNumber][spriteNumber] = spritemanager->getMugenSprite(groupNumber,spriteNumber, mask);
					     Debug::debug(Debug::resources,__FUNCTION__) << "set sprite for :file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
						}else{ //se achou o grupo, procura a imagem
							sprImgIt = sprMapIt->second.find(spriteNumber);
							if (sprImgIt == sprMapIt->second.end()){ // se não achou o grupo nem o sprite
								my_MugenBitmaps[filename.path()][palette.path()][groupNumber][spriteNumber] = spritemanager->getMugenSprite(groupNumber,spriteNumber, mask);
								Debug::debug(Debug::resources,__FUNCTION__) << "set sprite for :file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
							}else{
								return sprImgIt->second;
							}

					   }

					}
				}

	            return my_MugenBitmaps[filename.path()][palette.path()][groupNumber][spriteNumber];


}
Mugen::SpriteMap CResource::_getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath &filename, bool mask, const SGF::Filesystem::CAbsolutePath & palette){

Debug::debug(Debug::resources,__FUNCTION__) << "set pallet and extract images:file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
			CSffSpriteManager * spritemanager= CResource::_getSffSpriteManager(filename,palette,mask);
			Mugen::SpriteMap mySpritemap;
			map< string, Mugen::SpriteMap>::iterator it;
			PalletizedSffFileSpriteMap::iterator first_it = my_MugenSpritemaps.find(filename.path());
            if (first_it == my_MugenSpritemaps.end()){
					spritemanager->getMugenSprites(mySpritemap);
					my_MugenSpritemaps[filename.path()][palette.path()] = mySpritemap;
					Debug::debug(Debug::resources,__FUNCTION__) << "set spritemap:file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;

			}else { //achou o caminho. agora procurará o pallete
				 it= first_it->second.find(palette.path());
				//se achou o caminho e não achou o palette
                if (it == first_it->second.end()){
					spritemanager->getMugenSprites(mySpritemap);
					my_MugenSpritemaps[filename.path()][palette.path()] = mySpritemap;
					Debug::debug(Debug::resources,__FUNCTION__) << "set spritemap:file,pallette: // " << filename.path()<<" // "<<palette.path()  << endl;
					}else {// achou o caminho e achou o palette
					mySpritemap =  my_MugenSpritemaps[filename.path()][palette.path()];

					}
				}

			return mySpritemap;
}



const CFont & CResource::_getFont(const string & file, int width, int height) const throw (Exception::Filesystem::CNotFound){
     if (file.length() == 0){
		ostringstream out;
	    out << "Cannot find empty font: " << file <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
	 }

	;
	Util::CReferenceCount<CFontInfo> myFontInfo;
	if(CFontList::GetInstance()->isAvailable(file)) {
		myFontInfo = CFontList::GetInstance()->findFont(file);
		myFontInfo->setWidth(width);
		myFontInfo->setHeight(height);
		return myFontInfo->get();

	}else { //todo: retornar a fonte default
		if ( myFontInfo != NULL){
		return myFontInfo->get();
		}else {
			ostringstream out;
	    out << "Cannot find font: " << file <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());
		}

	}

/*
	FontSizedMap::iterator first_it = sizedfonts.find(height);
            if (first_it == sizedfonts.end()){
					CTTFFont *pCFont =	new CTTFFont(file,height);
					ttfsizedfonts[height][file] = pCFont;
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file <<" ' size: "<< width << " , "<< height  << endl;

			}else { //achou o camhinho. agora achará o pallete
				map<string, CFont*>::iterator it = first_it->second.find(file);
                if (it == first_it->second.end()){
					CTTFFont *pFFont =	new CTTFFont(file,height);
					ttfsizedfonts[height][file] = pFFont;
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file <<" ' size: "<< width << " , "<< height  << endl;

                }
            }


			return sizedfonts[height][file];
			*/

}
/*
CTTFFont * CResource::_getTTFont(const string & file,unsigned int ptsize){//{
     if (file.length() == 0){
		//throw NotFound("Filesystem::getInstance().find - No path given");
		return NULL;
	 }

		CTTFFontSizedMap::iterator first_it = ttfsizedfonts.find(ptsize);
            if (first_it == ttfsizedfonts.end()){
					CTTFFont *pCTTFFont =	new CTTFFont(file,ptsize);
					ttfsizedfonts[ptsize][file] = pCTTFFont;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file<<" ' "<<ptsize  << endl;

			}else { //achou o caminho. agora achará o pallete
				map<string, CTTFFont*>::iterator it = first_it->second.find(file);
                if (it == first_it->second.end()){
					CTTFFont *pCTTFFont =	new CTTFFont(file,ptsize);
					ttfsizedfonts[ptsize][file] = pCTTFFont;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file<<" ' "<<ptsize  << endl;

                }
            }


			return ttfsizedfonts[ptsize][file];

}*/
CFont * CResource::_getTTFont(const string & file,int width , int height){//{
     if (file.length() == 0){
		//throw NotFound("Filesystem::getInstance().find - No path given");
		return NULL;
	 }
	 int pt_size=Util::getPtSize(width,height);
	 Gui::CAbsolutePoint point(width , height);
		FontSizedMap::iterator first_it = my_sizedfonts.find(point);
            if (first_it == my_sizedfonts.end()){
					CTTFFont *pCTTFFont =	new CTTFFont(file,pt_size);
					my_sizedfonts[point][file] = pCTTFFont;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file<<" ' "<<pt_size  << endl;

			}else { //achou o tamanho. agora achará o nome
				map<string, CFont*>::iterator it = first_it->second.find(file);
                if (it == first_it->second.end()){
					CTTFFont *pCTTFFont =	new CTTFFont(file,pt_size);
					my_sizedfonts[point][file] = pCTTFFont;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file<<" ' "<<pt_size  << endl;

                }
            }


			return my_sizedfonts[point][file];

}

CFont * CResource::_getBitmapFont(const string & file,int width , int height){//{

    if (file.length() == 0){
		//throw NotFound("Filesystem::getInstance().find - No path given");
		return NULL;
	 }
	 Gui::CAbsolutePoint point(width , height);
		FontSizedMap::iterator first_it = my_sizedfonts.find(point);
            if (first_it == my_sizedfonts.end()){
				CFont *pCTTFFont =	new CBitmapFont(file,SGF::CBitmapFont::SGF_type);
					my_sizedfonts[point][file] = pCTTFFont;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file<<" ' "<< width << " , " <<height  << endl;

			}else { //achou o tamanho. agora achará o nome
				map<string, CFont*>::iterator it = first_it->second.find(file);
                if (it == first_it->second.end()){
					CFont *pCTTFFont =	new CBitmapFont(file,CBitmapFont::SGF_type);
					my_sizedfonts[point][file] = pCTTFFont;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					Debug::debug(Debug::resources,__FUNCTION__) << "set size and initialize font:file,size" << file<<" ' "<<width << " , " <<height  << endl;

                }
            }


			return my_sizedfonts[point][file];
}

Filesystem::CAbsolutePath & CResource::_getPath(const string & file) throw (Exception::Filesystem::CNotFound){
    //checkloaded
	string temp=file;
	Debug::debug(Debug::resources,__FUNCTION__) << "BEGIN // fonte:" <<file<< endl;
	 if (file.length() == 0){
		ostringstream out;
	    out << "CAbsolutePath Cannot find enpty file: " << file <<endl;
	    throw Exception::Filesystem::CNotFound(__FUNCTION__, __LINE__,out.str());

	 }
	if  (file=="") {
	Filesystem::CAbsolutePath caminho;
		return caminho;
}
	map<string,Filesystem::CAbsolutePath*>::iterator it;
	it = this->my_files.find(file);

	if( it == this->my_files.end() ) {
//	            Filesystem::CAbsolutePath Base;

		my_files[file] =  new Filesystem::CAbsolutePath(Filesystem::CRelativePath(temp));

		//	files[file]->Append(temp);

	}
			//strret=ttfonts.insert(pair<string,CTTFFont*>(path,teste));
			//if (strret.second==false) {
			//		cout << "element" <<path << "already existed";
		//			cout << " with a value of " << strret.first->second << endl;
		//		}
          //   } catch (const LoadException & le){
            //    Debug::debug(Debug::resources,__FUNCTION__) << "CResource::_getTTFont - Could not load TTFfont " << path << endl;
                // we failed, so load a default font

           //  }
	//else
	//	ttfonts[path] = it->second;
	//return teste;

   return my_files[file]->copy();
}

SGF::Util::CReferenceCount<SGF::Ast::CAstManager> CResource::_getDEFParsedFile(const Filesystem::CAbsolutePath & path){
	if (path.exist()) {
	int	wasparsed = 0;
	my_lockdef.acquire();

	string file = path.path();
	map<string, Ast::CAstManager*>::iterator it;
	Ast::CAstManager *parsed;
	it = this->my_defParses.find(file);

	if( it == this->my_defParses.end() ) {

	TimeDifference diff;
    diff.startTime();
	parsed = new Ast::CAstManager();
	DefCompiler::Driver defCompiler(parsed);
	defCompiler.parse_file(file);
	diff.endTime();
    Debug::debug(Debug::resources,__FUNCTION__) << "Parsed mugen file " + file + " in" + diff.printTime("") << endl;
	my_defParses[file] =  parsed;
	wasparsed = 1;
	}else{
		parsed=it->second;
	}
	Debug::debug(Debug::resources,__FUNCTION__) << "WILL CREATE ANOTHER CAST MANAGER "  << endl;
	Ast::CAstManager *parsed2 = new Ast::CAstManager();
    Debug::debug(Debug::resources,__FUNCTION__) << "WILL COPY THE CAST MANAGER "  << endl;
	parsed2->copyFrom(parsed);
	//Debug::debug(Debug::resources,__FUNCTION__) << "END COPY THE CAST MANAGER "  << endl;
	//if (wasparsed) parsed2->debugExplain();
	if (Debug::getDebug(Debug::resources)) parsed2->debugExplain();

    //Debug::debug(Debug::resources,__FUNCTION__ ) << "UnLock loading" << endl;

	my_lockdef.release();
	return SGF::Util::CReferenceCount<SGF::Ast::CAstManager>(parsed2);
   	}else {
	Debug::debug(Debug::resources,__FUNCTION__) << "ERROR PATH ENPTY // TODO: THROW AN EXCEPTION "  << endl;

	}
}
SGF::Util::CReferenceCount<SGF::Ast::CAstManager> CResource::_getCMDParsedFile(const Filesystem::CAbsolutePath & path){

	if (path.exist()) {
		my_lockcmd.acquire();

	int wasparsed = 0;
	string file = path.path();
	map<string, Ast::CAstManager*>::iterator it;
	it = this->my_defParses.find(file);
	Ast::CAstManager *parsed;
	if( it == this->my_defParses.end() ) {

	TimeDifference diff;
    diff.startTime();
	parsed = new Ast::CAstManager();
	CmdCompiler::Driver cmdCompiler(parsed);
	cmdCompiler.parse_file(file);
	diff.endTime();
    Debug::debug(Debug::resources,__FUNCTION__) << "Parsed mugen file " + file + " in" + diff.printTime("") << endl;
	my_defParses[file] =  parsed;
	wasparsed = 1;
	}else {
		parsed=it->second;
	}
	Debug::debug(Debug::resources,__FUNCTION__) << "WILL CREATE ANOTHER CAST MANAGER "  << endl;
	Ast::CAstManager *parsed2 = new Ast::CAstManager();
    Debug::debug(Debug::resources,__FUNCTION__) << "WILL COPY THE CAST MANAGER "  << endl;

	parsed2->copyFrom(parsed);

	 Debug::debug(Debug::resources,__FUNCTION__) << "END COPY THE CAST MANAGER "  << endl;
	 if(Debug::getDebug(Debug::resources)) parsed->debugExplain();

       // Debug::debug(Debug::resources,__FUNCTION__ ) << "UnLock loading" << endl;

	my_lockcmd.release();
	return SGF::Util::CReferenceCount<SGF::Ast::CAstManager>(parsed2);
	//return *my_defParses[file];
	//defParses[file]->debugExplain();
	//return *defParses[file];
	}else {
	Debug::debug(Debug::resources,__FUNCTION__) << "ERROR PATH ENPTY // TODO: THROW AN EXCEPTION "  << endl;

	}
}
SGF::Util::CReferenceCount<SGF::Ast::CAstManager> CResource::_getCOMParsedFile(const Filesystem::CAbsolutePath & path){

	if (path.exist()) {
		my_lockcmd.acquire();

	int wasparsed = 0;
	string file = path.path();
	map<string, Ast::CAstManager*>::iterator it;
	Ast::CAstManager *parsed;
	it = this->my_comParses.find(file);

	if( it == this->my_comParses.end() ) {

	TimeDifference diff;
    diff.startTime();
	parsed = new Ast::CAstManager();
	ComCompiler::Driver comCompiler(parsed);
	comCompiler.parse_file(file);
	diff.endTime();
    Debug::debug(Debug::resources,__FUNCTION__) << "Parsed mugen file " + file + " in" + diff.printTime("") << endl;
	my_comParses[file] =  parsed;
	wasparsed = 1;
	}else{
		parsed = it->second;
	}
	Debug::debug(Debug::resources,__FUNCTION__) << "WILL CREATE ANOTHER CAST MANAGER "  << endl;
	Ast::CAstManager *parsed2 = new Ast::CAstManager();
    Debug::debug(Debug::resources,__FUNCTION__) << "WILL COPY THE CAST MANAGER "  << endl;

	parsed2->copyFrom(parsed);

	 Debug::debug(Debug::resources,__FUNCTION__) << "END COPY THE CAST MANAGER "  << endl;
	 if(Debug::getDebug(Debug::resources)) parsed->debugExplain();

       // Debug::debug(Debug::resources,__FUNCTION__ ) << "UnLock loading" << endl;

	my_lockcmd.release();
	return SGF::Util::CReferenceCount<SGF::Ast::CAstManager>(parsed2);
	//return *my_defParses[file];
	//defParses[file]->debugExplain();
	//return *defParses[file];
	}else {
	Debug::debug(Debug::resources,__FUNCTION__) << "ERROR PATH ENPTY // TODO: THROW AN EXCEPTION "  << endl;

	}
}

SGF::Util::CReferenceCount<SGF::Ast::CAstManager> CResource::_getAIRParsedFile(const Filesystem::CAbsolutePath & path){
	if (path.exist()) {
		my_lockair.acquire();
	int wasparsed=0;

	string file = path.path();
	map<string, Ast::CAstManager*>::iterator it;
	Ast::CAstManager *parsed;
	it = this->my_defParses.find(file);

	if( it == this->my_defParses.end() ) {

	TimeDifference diff;
    diff.startTime();
	parsed = new Ast::CAstManager();
	AirCompiler::Driver airCompiler(parsed);
	airCompiler.parse_file(file);
	diff.endTime();
    Debug::debug(Debug::resources,__FUNCTION__) << "Parsed mugen file " + file + " in" + diff.printTime("") << endl;
	wasparsed = 1;
	my_defParses[file] =  parsed;
	}else{
		parsed = it->second;
	}
	Debug::debug(Debug::resources,__FUNCTION__) << "WILL CREATE ANOTHER CAST MANAGER "  << endl;
	Ast::CAstManager *parsed2 = new Ast::CAstManager();
    Debug::debug(Debug::resources,__FUNCTION__) << "WILL COPY THE CAST MANAGER "  << endl;

	parsed2->copyFrom(parsed);

	 Debug::debug(Debug::resources,__FUNCTION__) << "END COPY THE CAST MANAGER "  << endl;
	 if(Debug::getDebug(Debug::resources)) parsed->debugExplain();


    //    Debug::debug(Debug::resources,__FUNCTION__ ) << "UnLock loading" << endl;

		my_lockair.release();
	return SGF::Util::CReferenceCount<SGF::Ast::CAstManager>(parsed2);
	//defParses[file]->debugExplain();
	//return *defParses[file];
	}else {
	Debug::debug(Debug::resources,__FUNCTION__) << "ERROR PATH ENPTY // TODO: THROW AN EXCEPTION "  << endl;

	}
}

Util::CReferenceCount<SGF::Ast::CAstManager>  CResource::_getCMDParsedString(const string & path){
	if (!path.empty()) {
		Debug::debug(Debug::resources,__FUNCTION__)<< "Parsing String: " << path <<endl;
	map<string, Ast::CAstManager*>::iterator it;
	Ast::CAstManager *parsed;
	it = this->my_defParses.find(path);

	//if( it == this->defParses.end() ) {

	TimeDifference diff;
    diff.startTime();
	parsed = new Ast::CAstManager();
	CmdCompiler::Driver cmdCompiler(parsed);
	cmdCompiler.parse_string(path);
	diff.endTime();
    Debug::debug(Debug::resources,__FUNCTION__) << "Parsed mugen string in" + diff.printTime("") << endl;
	my_defParses[path] =  parsed;
	//}
	Debug::debug(Debug::resources,__FUNCTION__) << "WILL CREATE ANOTHER CAST MANAGER "  << endl;
	Ast::CAstManager *parsed2 = new Ast::CAstManager();
    Debug::debug(Debug::resources,__FUNCTION__) << "WILL COPY THE CAST MANAGER "  << endl;

	parsed2->copyFrom(parsed);

	// Debug::debug(Debug::resources,__FUNCTION__) << "END COPY THE CAST MANAGER "  << endl;
	if (Debug::getDebug(Debug::resources)) parsed->debugExplain();
	return SGF::Util::CReferenceCount<SGF::Ast::CAstManager>(parsed2);
	//defParses[file]->debugExplain();
	//return *defParses[file];
	}else {
	Debug::debug(Debug::resources,__FUNCTION__) << "ERROR TODO: THROW AN EXCEPTION "  << endl;

	}
}

CMusic * CResource::_getMusic(const Filesystem::CRelativePath & path){
	 try{
		 if (path.isComplete && path.exist()){
		 Filesystem::CAbsolutePath teste = Filesystem::CAbsolutePath(path);
			 _getMusic(teste);

		 }else {
				 Filesystem::CAbsolutePath teste = path;
		_getMusic(teste);
		 }

	 } catch (const Exception::Filesystem::CNotFound & fail){
        Debug::debug(Debug::resources,__FUNCTION__) << "Could not load music because " << fail.getTrace() << endl;
		return NULL;
    }



}

Util::CSmartPtr_MT<CMusic> CResource::_getMusic(const Filesystem::CAbsolutePath & path){

	if(path.exist()) {
				if(!my_musicInstance) {
					my_musicInstance = new CMusic(true);
				}
				my_musicInstance->loadSong( path.path());
				return my_musicInstance;
		} else {
			 Debug::debug(Debug::resources,__FUNCTION__) << "Could not load music " <<  endl;
			return NULL;
		}


}


void CResource::_getMugenSounds(const string & filename, MugenSoundMap & m_sounds){
	CSndSoundManager *pMugenSndManager=NULL;
	NamedMugenSoundMap::iterator it;
	it = this->my_mugenSounds.find(filename);

	if( it == this->my_mugenSounds.end() ) {
	    pMugenSndManager = new CSndSoundManager(filename);
		pMugenSndManager->readSounds(filename,m_sounds);
		my_mugenSounds[filename]= pMugenSndManager;
	}else {
		pMugenSndManager = my_mugenSounds[filename];
		pMugenSndManager->readSounds(filename,m_sounds);

	}
}
} // end SGF
