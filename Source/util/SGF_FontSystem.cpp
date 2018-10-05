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


#include <locale.h>
#include "util/SGF_FontSystem.h"
#include "SGF_Global.h"
#include "SDL_ttf.h"
#include "util/SGF_SdlManager.h"
#include "util/SGF_Debug.h"
#include "exceptions/all.h"
#include "util/SGF_Util.h"
#include "resource/all.h"
#include "configuration/SGF_Configuration.h"
#include "util/SGF_Loading.h"
#include "util/SGF_FontInfo.h"
#include "util/SGF_Utf.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;
#if defined vsnprintf
#undef vsnprintf
#endif
#define NUM_GRAYS       256
namespace SGF {


//inicializa vari�veis est�ticas
CFontList* CFontList::pCText=NULL;   //! ponteiro para a int�ncia �nica da classe
vector<Util::CReferenceCount<CFontInfo> > CFontList::availableFonts;

//! este template � utilizado para o operador + da fun��o findsystemfonts
template <class X>
static vector<X> operator+(const vector<X> & v1, const vector<X> & v2){
    vector<X> out;
    for (typename vector<X>::const_iterator it = v1.begin(); it != v1.end(); it++){
        out.push_back(*it);
    }
    for (typename vector<X>::const_iterator it = v2.begin(); it != v2.end(); it++){
        out.push_back(*it);
    }
    return out;
}

static string joinPaths(const vector<Filesystem::CAbsolutePath> & strings, const string & middle){
    ostringstream out;

    for (vector<Filesystem::CAbsolutePath>::const_iterator it = strings.begin(); it != strings.end(); it++){
        out << (*it).path() << middle;
    }

    return out.str();
}

static bool sortInfo(const Util::CReferenceCount<CFontInfo> & info1,
                     const Util::CReferenceCount<CFontInfo> & info2){
    string name1 = Util::lowerCaseAll(info1->getName());
    string name2 = Util::lowerCaseAll(info2->getName());
    return name1 < name2;
}


static bool saneFont(const Util::CReferenceCount<CFontInfo> & info){
    Debug::debug(Debug::font,__FUNCTION__) << "BEGIN" <<endl;
    class CContext: public Loader::CLoadingContext {
    public:
        CContext(const Util::CReferenceCount<CFontInfo> & info):
            info(info),
            isok(false){
            }

        bool ok(){
            try{
                const CFont & font = info->get();
                return font.getTextLength("A") != 0 &&
                    font.getHeight() != 0;
            } catch (const Exception::CBase & ignore){
                return true;
            }
        }

        virtual void load(){
            isok = ok();
        }

        const Util::CReferenceCount<CFontInfo> & info;
        bool isok;
    };

    CContext context(info);
    //an empty LevelInfo object, we don't really care about it
    Level::CLevelInfo level;
	Loader::loadScreen(context, level, Loader::Default); //Loader::SimpleCircle);
    Debug::debug(Debug::font,__FUNCTION__) << "END - returning: "<< context.isok <<endl;
    return context.isok;
}
/*
static void saneFont2(vector<Util::CReferenceCount<CFontInfo> > fontvector ) {
	const Util::CReferenceCount<CFontInfo> info;
    Debug::debug(Debug::font,__FUNCTION__) << "BEGIN" <<endl;
    class CContext: public Loader::CLoadingContext {
    public:
        CContext(vector<Util::CReferenceCount<CFontInfo> > fontvector):
            fonts(fontvector){
            }

        bool ok(Util::CReferenceCount<CFontInfo> & info){
            try{
                const CFont & font = info->get();
                Debug::debug(Debug::font,__FUNCTION__) << info->getName() << " / Testing Lenght: " << font.textLength("A") << endl;
				return font.textLength("A") != 0;// && font.getHeight() != 0;
            } catch (const Exception::CBase & ignore){
                return true;
            }
        }
		//! metodo que roda quando chama-se loadScreen
        virtual void load(){
			int index=0;
			int max = fonts.size()-1;
			vector<int> deletes;
			for (vector<Util::CReferenceCount<CFontInfo> >::iterator it = fonts.begin(); it != fonts.end(); it++){
                Debug::debug(Debug::font,__FUNCTION__) << "Testing font " << (*it)->getName() << "'" << endl;
				if (!ok((*it))){
                Debug::debug(Debug::font,__FUNCTION__) << "Warning: will marlk to delete font " << (*it)->getName() << "'" << endl;
				//fonts.erase(it);
				deletes.push_back(index);

 				}
				index++;
			}

			 for (vector<int >::iterator it = deletes.begin(); it != deletes.end(); it++) {
                Debug::debug(Debug::font,__FUNCTION__) << "Font Erased from vector: " <<  endl;
				//fonts[(*it)]->getName();
			}

		}
		vector<Util::CReferenceCount<CFontInfo> > fonts;


    };

    CContext context(fontvector);
   // an empty LevelInfo object, we don't really care about it
    Level::CLevelInfo level;
	Loader::loadScreen(context, level, Loader::Default);//Loader::SimpleCircle);
    Debug::debug(Debug::font,__FUNCTION__) << "END - returning: "<<endl;

}
*/
vector<Filesystem::CAbsolutePath> CFontList::findSystemFonts(){
    Debug::debug(Debug::font,__FUNCTION__) << "BEGIN " << endl;
    if (Util::isWindows()){
        const char * windows = getenv("windir");
        if (windows != NULL){
			Filesystem::CAbsolutePath dir = Filesystem::CAbsolutePath(string(windows) + DIR_SEPARATOR +"fonts");
            Debug::debug(Debug::font,__FUNCTION__) << "Will get windows fonts at: "<< dir.path() << endl;

            return Filesystem::getInstance().getFilesRecursive(dir, "*.ttf");
        }
        return vector<Filesystem::CAbsolutePath>();
    } else if (Util::isOSX()){
        return Filesystem::getInstance().getFilesRecursive(Filesystem::CAbsolutePath("/Library/Fonts"), "*.ttf");
    } else if (Util::isLinux()) {
        /* assume unix/linux conventions */
        Debug::debug(Debug::font,__FUNCTION__) << "Will get Linux fonts at: "<< "/usr/share/fonts/truetype" << endl;
        Debug::debug(Debug::font,__FUNCTION__) << "Will get Linux fonts at: "<< "/usr/local/share/fonts/truetype" << endl;

		return Filesystem::getInstance().getFilesRecursive(Filesystem::CAbsolutePath("/usr/share/fonts/truetype"), "*.ttf") +
              Filesystem::getInstance().getFilesRecursive(Filesystem::CAbsolutePath("/usr/local/share/fonts/truetype"), "*.ttf");

    }

}

void CFontList::findFonts() throw(CLoadException){
    Debug::debug(Debug::font,__FUNCTION__) << "BEGIN " << endl;

    try{
		Filesystem::CRelativePath fontsDirectory(CConfiguration::gameFontDirectory.getString());
			if (fontsDirectory.exist()){
            Debug::debug(Debug::font, __FUNCTION__) << "Get Font directory " << fontsDirectory.path() << endl;
			vector<Filesystem::CAbsolutePath> ttfFonts = Filesystem::getInstance().getFiles(fontsDirectory, "*.ttf");
            Debug::debug(Debug::font, __FUNCTION__) << "Found ttf fonts " << joinPaths(ttfFonts, ", ") << endl;
			vector<Filesystem::CAbsolutePath> otfFonts = Filesystem::getInstance().getFiles(fontsDirectory, "*.otf");
            Debug::debug(Debug::font,__FUNCTION__) << "Found otf fonts " << joinPaths(otfFonts, ", ") << endl;
			vector<Filesystem::CAbsolutePath> bitmapFonts = Filesystem::getInstance().getFiles(fontsDirectory, "*.png");
            Debug::debug(Debug::font,__FUNCTION__) << "Found bitmap fonts " << joinPaths(bitmapFonts, ", ") << endl;

            Debug::debug(Debug::font,__FUNCTION__) << "Now add the fonts to vector" << endl;
			for (vector<Filesystem::CAbsolutePath>::iterator it = ttfFonts.begin(); it != ttfFonts.end(); it++){
                Debug::debug(Debug::font,__FUNCTION__) << "Adding ttf fonts `" << (*it).path() << "'" << endl;
				availableFonts.push_back(new CAbsoluteFontInfo(*it, CConfiguration::menuFontSize.getInteger(), CConfiguration::menuFontSize.getInteger(),CFont::TrueTypeFont));
				NumFontsTTF++;
			}

			for (vector<Filesystem::CAbsolutePath>::iterator it = otfFonts.begin(); it != otfFonts.end(); it++){
                Debug::debug(Debug::font,__FUNCTION__) << "Adding otf fonts `" << (*it).path() << "'" << endl;
				availableFonts.push_back(new CAbsoluteFontInfo(*it, CConfiguration::menuFontSize.getInteger(), CConfiguration::menuFontSize.getInteger(),CFont::TrueTypeFont));
				NumFontsTTF++;
			}
			// Load Bitmap fonts
			for (vector<Filesystem::CAbsolutePath>::iterator it = bitmapFonts.begin(); it != bitmapFonts.end(); it++){
                Debug::debug(Debug::font,__FUNCTION__) << "Adding bitmap fonts `" << (*it).path() << "'" << endl;
				availableFonts.push_back(new CAbsoluteFontInfo(*it, CConfiguration::menuFontSize.getInteger(), CConfiguration::menuFontSize.getInteger(),CFont::BitmapFont));
				NumFontsBitmap++;
			}

        }
			/* S.O. specific fonts */
			vector<Filesystem::CAbsolutePath> systemFonts = findSystemFonts();
			for (vector<Filesystem::CAbsolutePath>::iterator it = systemFonts.begin(); it != systemFonts.end(); it++){
                Debug::debug(Debug::font,__FUNCTION__) << "Adding system font `" << (*it).path() << "'" << endl;
				availableFonts.push_back(new CAbsoluteFontInfo(*it, CConfiguration::menuFontSize.getInteger(), CConfiguration::menuFontSize.getInteger(),CFont::TrueTypeFont));
				NumFontsTTF++;
			}

			//saneFont2(fonts);
			//bool found=false;
            Debug::debug(Debug::font,__FUNCTION__) << "WILL SORT FONTS `" <<  endl;
			sort(availableFonts.begin(), availableFonts.end(), sortInfo);
            Debug::debug(Debug::font,__FUNCTION__) << "END SORTING FONTS `" <<  endl;
	   /*     for (vector<Util::CReferenceCount<CFontInfo> >::iterator it = fonts.begin(); it != fonts.end(); it++){
				for (vector<Util::CReferenceCount<CFontInfo> >::iterator it2 = availableFonts.begin(); it2 != availableFonts.end(); it2++){
					if ((*it)==(*it2))	found=true;
				}
				if (found) {
                Debug::debug(Debug::font,__FUNCTION__) << "Adding to available fonts -> system font `" << (*it)->getName() << "'" << endl;
				availableFonts.push_back((*it));
				found=false;
				}

			}  */
			// DEFAULT (blank)
			//s fonts.insert(fonts.begin(), NULL);
			DefFontsLoaded = true;
            Debug::debug(Debug::font,__FUNCTION__) << "Fonts added and sorted - Returning " << endl;
            Debug::debug(Debug::font,__FUNCTION__) << "END " << endl;

    } catch (const Exception::Filesystem::CNotFound & e){
        throw CLoadException(__FILE__, __LINE__, e, "Could not load font");
    }


}


CFontList::CFontList():
NumFontsTTF(0),
NumFontsBitmap(0),
DefFontsLoaded(0)
{
    Debug::debug(Debug::font,__FUNCTION__) << "Initializing Font List " << endl;
			//Se as fontes n�o foram carregadas, carregas as fontes ttf padr�o num ambiente windows
	if (!DefFontsLoaded)
	//LoadFonts(Filesystem::CAbsolutePath("fonts"));
	findFonts();
	//Todo: Carregar as fontes bitmap dispon�veis
}

//Destructor
CFontList::~CFontList()
{

}


void CFontList::CleanUp() {
//Debug::debug(Debug::font, __FUNCTION__) << "CFontList:: Cleaning SDL_ttf"<<endl;

}



/** @fn CFontList::LoadFonts(string path)
@brief rotina que varre o diret�rio e retorna duas listas com os nomes dos aquivos extens�o .ttf ou .fon
@param path: caminho do diret�rio a ser verificado
@return 0 se ok
        1 se aconteceu algum erro
@warning Obs: preenche dois mapas: MyTTFFonts com o nome da fonte e o caminho
**/
/*
int CFontList::LoadFonts(Filesystem::CAbsolutePath & path) {
	Debug::debug(Debug::font, __FUNCTION__) << "path : "<< path.path() <<endl;
	int fontnum=0;
	//pair<map<int, string>::iterator,bool> ret;
	pair<map<string, string>::iterator,bool> strret;
	list<FILELIST> MyList;
	Filesystem::TransverseDirectory(path.path(),MyList);
    list<FILELIST>::iterator it;

	for(it = MyList.begin(); it != MyList.end(); it++)
	{
      vector<string>::iterator its;
		for(its = (*it).theList.begin(); its != (*it).theList.end(); its++)
		{
		   if ( Filesystem::checkExtension((*its))=="fon" || Filesystem::checkExtension((*its))=="FON" || Filesystem::checkExtension((*its))=="ttf" || Filesystem::checkExtension((*its))=="TTF" || Filesystem::checkExtension((*its))=="otf" || Filesystem::checkExtension((*its))=="OTF") {

			strret=MyTTFFonts.insert(pair<string,string>((*its),(*it).path+(*its)));
			if (strret.second==false) {

					cout << "element" <<fontnum << " already existed";
					cout << " with a value of " << strret.first->second << endl;
				}
			else
			   fontnum++;
		}
		//Debug::debug(1,__FUNCTION__) << "CFontList::LoadFonts // //=> font: " <<(*it)<< endl;

		}

	}
	this->NumFontsTTF=MyTTFFonts.size();
	//pMyTTfFonts= &MyTtfFonts;
	pMyAvailabeTTFFonts= &MyTTFFonts;
	if(path.path() == DEF_FONT_PATH)
	   this->DefFontsLoaded=1;
return 0;
}
*/
/** @fn CFontList::GetNumFontsTTF()
@brief rotina que retorna o n�mero de fontes ttf carregadas na lista
@return o n�mero de fontes carregadas
@warning
**/
int CFontList::GetNumFontsTTF() {
return NumFontsTTF;
}


/** @fn CFontList::GetNumFontsBitmap()
@brief rotina que retorna o n�mero de fontes bitmap carregadas na lista
@return o n�mero de fontes carregadas
@warning
**/
int CFontList::GetNumFontsBitmap() {
return NumFontsBitmap;
}

vector<Util::CReferenceCount<CFontInfo> >::iterator CFontList::findFontVector(string name) {
	name=Filesystem::stripDir(name);
	vector<Util::CReferenceCount<CFontInfo> >::iterator it=availableFonts.begin();
		while(it != availableFonts.end()) {
			if((*it)->getName()==name){
				Debug::debug(Debug::resources,__FUNCTION__) << "caminho da fonte encontrado : "<< (*it)->getPath() <<endl;

			return it;
			}else it++;

		}
		Debug::debug(Debug::resources,__FUNCTION__) << "caminho da fonte: "<< name <<"  N�O encontrado " <<endl;
		return availableFonts.end();
}
//deve usar isAvailable antes de chamar est m�todo sen�o pode dar erro
Util::CReferenceCount<CFontInfo> CFontList::findFont(string name) {
	name=Filesystem::stripDir(name);
	vector<Util::CReferenceCount<CFontInfo> >::iterator it=availableFonts.begin();
		while(it != availableFonts.end()) {
			if((*it)->getName()==name){
				Debug::debug(Debug::resources,__FUNCTION__) << "caminho da fonte encontrado : "<< (*it)->getPath() <<endl;

			return (*it);
			}else it++;

		}

}
/** @fn CFontList::GetFontPath(const string fonte)
@brief retorna o caminho para uma fonte, dado seu nome
@param fonte: nome da fonte que se procura na lista
@return o caminho para a fonte ou uma string vazia se a fonte n�o estiver dispon�vel
@warning Todo: o que acontece se tiver mais de uma fonte com o mesmo nome?
**/
string CFontList::GetFontPath(const string fonte) throw(CLoadException){
	// verifica se o mapa foi inicializado
	if (this->DefFontsLoaded) {
		Debug::debug(Debug::resources,__FUNCTION__) << "fonte : "<< fonte <<endl;
		vector<Util::CReferenceCount<CFontInfo> >::iterator it=findFontVector(fonte);
		if (it!=availableFonts.end()) {
			Debug::debug(Debug::resources,__FUNCTION__) << "Achou o caminho para a fonte:" << (*it)->getPath() <<endl;
			return (*it)->getPath();
			}else {
			Debug::debug(Debug::resources,__FUNCTION__) << "n�o achou o caminho " <<endl;
			throw CLoadException(__FILE__, __LINE__,"Could not find font");

			}
	}else {
    throw CLoadException(__FILE__, __LINE__,"Font List not initialized");
    }
}
/** @fn CFontList::isAvailable(string fonte)
@brief verifica se a fonte desejada est� na lista de fontes dispon�veis
@param fonte: nome da fonte que se procura na lista
@return 1 se a fonte est� dispon�vel
//          0 se a fonte n�o est� dispon�vel
@warning
**/
int CFontList::isAvailable(string fonte) throw (CLoadException) {

	//verifica se alista de fontes foi inicializada
	if (this->DefFontsLoaded) {
        vector<Util::CReferenceCount<CFontInfo> >::iterator it=findFontVector(fonte);
		if (it!=availableFonts.end()) return true;
		else return false;

	} else {
    throw CLoadException(__FILE__, __LINE__,"CFontList::isAvailable - Font List not initialized");
    }


}
/** @fn CFontList::GetInstance()
@brief retorna o ponteiro para a inst�ncia da classe CFontList (Singleton)
@param
@return Ponteiro para a inst�ncia da Classe CFontList
@warning
**/
 CFontList*  CFontList::GetInstance()
{
          if (!pCText)
			  pCText = new CFontList();
          return pCText;
}


//==============================================================
// Objetivo: Construtor: inicializar uma fonte TTF
// Par�metros: fonte: nome da fonte a ser carregada sem o caminho

CTTFFont::CTTFFont(const string fonte, int ptsize):
CFont((CFont *) this),
AvailableFonts(CFontList::GetInstance()),
umessage(NULL),
fontName(""),
sizeX(16),
sizeY(16),
_my_font(NULL),
type(TrueTypeFont),
TTF_AA(Solid),
_my_style(Normal){
    Debug::debug(Debug::font, __FUNCTION__) << "Constructor // Fontes Dispon�veis="<< AvailableFonts->GetNumFontsTTF() <<endl;
	//verifica se existe esta fonte na lista de fontes disponiveis
	//verifica se foi passado com ou sem diret�rio
	//se foi passado com diret�rio, tira o diret�rio e carrega todas as fontes que tem nesse diret�rio na lista de fontes
	// Se foi passado sem diret�rio, tem que ter a lista carregada

	string::iterator it;
    bool withpath=0;
	if(fonte.find('/')!=string::npos){
   	  	withpath=1;
	}else if (fonte.find('\\')!=string::npos) {
        withpath=1;
	}
	if(withpath) {
	setFont( LoadFont(Filesystem::stripDir(fonte),ptsize) );
	fontName = fonte; //Todo: retirar o caminho da fonte
	sizeY = getHeight();
	sizeX = getWidth();

	} else
	{
	  if (!AvailableFonts->DefFontsLoaded) {
      // inicializa a lista de fontes
		  Debug::debug(Debug::resources,__FUNCTION__) << "Lista de fontes ainda n�o inicializada="<< endl;
	  }else {
	  setFont( LoadFont(fonte,ptsize) );
	  sizeY = getHeight();
	  sizeX = getWidth();

	  fontName = fonte; //Todo: retirar o caminho da fonte
	  }
	}
	TTF_SetFontStyle(_my_font, Normal);
	//inicializa a fonte
}


CTTFFont::~CTTFFont () {}


void CTTFFont::setStyle(int style){
	//Todo  Checar se style � um valor v�lido
	TTF_SetFontStyle(_my_font, style);
}
// Objetivo: Imprimir no arquivo de logs as fontes dispon�veis e o seu caminho
// Par�metros: nenhum
// retorno: Nada
void CFontList::PrintFonts() {

    Debug::debug(Debug::font,__FUNCTION__) << "Printing List of Available Fonts " << endl;

	vector<Util::CReferenceCount<CFontInfo> >::iterator first_it;
	for (first_it=availableFonts.begin(); first_it != availableFonts.end(); first_it++) {
		cout << (*first_it)->getName() << " - Path: "<< (*first_it)->getPath() << endl;
	}
}


TTF_Font *CTTFFont::LoadFont(string font, int ftSize) throw(CLoadException) {

	string file;
	//pair<map<int, TTF_Font (*)::iterator,bool> ret;
    //Debug::debug(Debug::font, __FUNCTION__) << "CFontList:: Initiating ttf Fonts"<<endl;
     //Open the font
	Debug::debug(Debug::font,__FUNCTION__) << "Iniciando a fonte : "<< font <<endl;
	//se foi passado o diret�rio junto com o nome da fonte.....
	string::iterator it;
    bool withpath=0;
	if(font.find('/')!=string::npos){
   	  	withpath=1;
	}else if (font.find('\\')!=string::npos) {
        withpath=1;
	}
	if (font=="") {
        font=WORKFONT;
        Debug::debug(Debug::resources,__FUNCTION__) << "Carregando a fonte Default : "<< font <<endl;
	    }
	if (withpath){
		file = font;
	}else {
		Debug::debug(Debug::resources,__FUNCTION__) << "Will get fonte Path to : "<< font <<endl;

		  file=  AvailableFonts->GetFontPath(font);
          Debug::debug(Debug::resources,__FUNCTION__) << "Path is: " << file <<endl;

	}

    // carrega fonte que foi passada sem diret�rio
	try {
	if (!Util::exists(file)) {
       throw CLoadException(__FILE__, __LINE__,"Caminho N�o encontrado");
	   return NULL;
	}else {
	Debug::debug(Debug::resources,__FUNCTION__) << "caminho para a fonte Encontrado: "<< file <<endl;
	fonte = TTF_OpenFont( file.c_str(), ftSize );
     //If there was an error in loading the font
    if( fonte == NULL )
    {
		Debug::debug(Debug::resources,__FUNCTION__) << "Erro iniciando a fonte erro:"<<TTF_GetError()<<endl;
        return NULL;

    }
	this->setFontOK();
    Debug::debug(Debug::resources,__FUNCTION__) << "Font initiated OK"<<endl;
	//Coloca o ponteiro da fonte na lista de fontes carregadas
	//AvailableFonts->MyTTFLoadedFonts[font] = this;  //! controlado atrav�s do font_factory
	/*ret=MyLoadedFonts.insert(pair<int,TTF_Font (*)(fontnumber,fonte));
			if (ret.second==false) {

					cout << "element" <<fontnum << "already existed";
					cout << " with a value of " << ret.first->second << endl;
				} */
	return fonte;
	}
	}catch (const CLoadException & le){
                    //throw le;
					Debug::debug(Debug::resources,__FUNCTION__) << "Could not load font " << file << " because " << le.getReason() << endl;
                    // we failed, so set the backSound to nothing
                    font=WORKFONT;//"arial.ttf";
					//file=  AvailableFonts->GetFontPath(font);
					fonte = TTF_OpenFont( file.c_str(), ftSize );
					return fonte;
    }catch (...) {
		Debug::debug(Debug::resources,__FUNCTION__) << "Erro ao iniciar a fonte. carregando fonte default"<<endl;

	}
}



void CTTFFont::DrawTextNew(int x,int y,   Colors::ColorDefinition textColor,  CBitmap &work,const char *strText,...)
{
  char string[512];                  // Temporary string
  va_list ap;                // Pointer To List Of Arguments
  va_start(ap, strText);         // Parses The String For Variables
  std::vsprintf(string, strText, ap); // Converts Symbols To Actual Numbers
  va_end(ap);

  work.Render(string,x,y,textColor,(CFont*) this);
}



//Render to Surface Methods===========================================

//==================================================================================
// TT Render (unicode)
// Returns an 8bit or 32bit(8/8/8/8-alpha) surface with TT text
//==================================================================================
SDL_Surface * CTTFFont::RenderUNICODE(const Uint16 *text, SDL_Color fg, SDL_Color bg)
{
	int xstart, width;
	int w, h;
	SDL_Surface *textbuf;
	SDL_Palette *palette;
	int index;
	int rdiff, gdiff, bdiff;
	const Uint16 *ch;
	Uint8 *src, *dst;
	Uint32 *dst32;
	Uint32 alpha=0;
	Uint32 pixel=0;
	Uint32 Rmask=0, Gmask=0, Bmask=0, Amask=0;
	int row, col;
	int error;

	/* Get the dimensions of the text surface */
	MESSAGESIZE ret=getTextSizeUNI(text);
	w=ret.w; h=ret.h;
	if ( !w ) {
		Debug::debug(Debug::error,__FUNCTION__)<<"SGE - Text has zero width"<<endl;
		return(NULL);
	}
#if 0
	/* Create the target surface */
	width = w;
	if(TTF_AA!=Blended) /* Allocate an 8-bit pixmap */
		textbuf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 8, 0, 0, 0, 0);
	else{ /* Allocate an 32-bit alpha pixmap */
		if ( SDL_BYTEORDER == SDL_LIL_ENDIAN ) {
			Rmask = 0x000000FF;
			Gmask = 0x0000FF00;
			Bmask = 0x00FF0000;
			Amask = 0xFF000000;
		} else {
			Rmask = 0xFF000000;
			Gmask = 0x00FF0000;
			Bmask = 0x0000FF00;
			Amask = 0x000000FF;
		}
		textbuf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, Rmask, Gmask, Bmask, Amask);
	}

	if ( textbuf == NULL ) {
		SDL_SetError("SGE - Out of memory");
		return(NULL);
	}


	/* Setup our colors */
	switch(TTF_AA){

		case Solid:{  /* No fancy antialiasing or alpha component */
			palette = textbuf->format->palette;

			palette->colors[0].r = bg.r;
			palette->colors[0].g = bg.g;
			palette->colors[0].b = bg.b;
			palette->colors[1].r = fg.r;
			palette->colors[1].g = fg.g;
			palette->colors[1].b = fg.b;
		}
		break;

		case Shaded:{  /* Fill the palette with NUM_GRAYS levels of shading from bg to fg */
			palette = textbuf->format->palette;

			rdiff = fg.r - bg.r;
			gdiff = fg.g - bg.g;
			bdiff = fg.b - bg.b;
			for ( index=0; index< NUM_GRAYS; ++index ) {
				palette->colors[index].r = bg.r + (index*rdiff)/(NUM_GRAYS-1);
				palette->colors[index].g = bg.g + (index*gdiff)/(NUM_GRAYS-1);
				palette->colors[index].b = bg.b + (index*bdiff)/(NUM_GRAYS-1);
			}
		}
		break;

		case Blended:{  /* Alpha component magic */
			SDL_FillRect(textbuf,NULL, SDL_MapRGBA(textbuf->format, bg.r,bg.g,bg.b,SDL_ALPHA_TRANSPARENT));
			//pixel = (fg.r<<16)|(fg.g<<8)|fg.b;
			pixel = (fg.b<<16)|(fg.g<<8)|fg.r;
		}
		break;
	}


	/* Load and render each character */
	xstart = 0;
	for ( ch=text; *ch; ++ch ) {
		// ch is unicode
		TTF_GlyphMetrics(_my_font, *ch, *minx, *maxx,  *miny,  *maxy,  *advance);

			error = Find_Glyph(font, *ch, CACHED_METRICS|CACHED_PIXMAP);

		if ( ! error ) {
			w = font->current->pixmap.width;
			src = (Uint8 *)font->current->pixmap.buffer;
			for ( row = 0; row < font->current->pixmap.rows; ++row ) {
				dst = (Uint8 *)textbuf->pixels + (row + font->current->yoffset)* textbuf->pitch + xstart + font->current->minx;

				switch(TTF_AA){

					case Solid:{  /* Normal */
						src = font->current->pixmap.buffer + row * font->current->pixmap.pitch;
						for ( col=w; col>0; --col ) {
							*dst++ |= (*src++<NUM_GRAYS/2)? 0:1;
						}
					}
					break;
					case Shaded:{  /* Antialiasing */
						src = font->current->pixmap.buffer + row * font->current->pixmap.pitch;
						for ( col=w; col>0; --col ) {
							*dst++ |= *src++;
						}
					}
					break;

					case Blended:{  /* Alpha */
						dst32 = (Uint32 *)textbuf->pixels + (row + font->current->yoffset)* textbuf->pitch/4 + xstart + font->current->minx;
						for ( col=w; col>0; --col ) {
							alpha = *src++;
							*dst32++ |= pixel | (alpha << 24);
						}
					}
					break;
				}
			}

			xstart += font->current->advance;
			if ( font->style & SGE_TTF_BOLD ) {
				xstart += font->glyph_overhang;
			}
		}
	}
#endif

					switch(TTF_AA){

					case Solid:{
						textbuf=TTF_RenderUNICODE_Solid(_my_font,text, fg);
					}
					break;
					case Shaded:{
						textbuf=TTF_RenderUNICODE_Shaded(_my_font, text, fg,  bg);
					}
					break;

					case Blended:{
						textbuf=TTF_RenderUNICODE_Blended(_my_font, text, fg);
					}
					break;
				}
#if 0
	/* Handle the underline style */
	if ( font->style & Underline ) {
		int row_offset;

		row_offset = font->ascent - font->underline_offset - 1;
		if ( row_offset > textbuf->h ) {
			row_offset = (textbuf->h-1) - font->underline_height;
		}

		if(TTF_AA==Solid){
			dst = (Uint8 *)textbuf->pixels + row_offset * textbuf->pitch;
			for ( row=font->underline_height; row>0; --row ) {
				memset(dst, 1, textbuf->w );
				dst += textbuf->pitch;
			}
		}else if(TTF_AA==Shaded){
			dst = (Uint8 *)textbuf->pixels + row_offset * textbuf->pitch;
			for ( row=font->underline_height; row>0; --row ) {
				memset(dst, NUM_GRAYS - 1, textbuf->w );
				dst += textbuf->pitch;
			}
		}else{
			pixel |= Amask;
			dst32 = (Uint32 *)textbuf->pixels+row_offset*textbuf->pitch/4;
			for ( row=font->underline_height; row>0; --row ) {
				for ( col=0; col < textbuf->w; ++col ) {
					dst32[col] = pixel;
				}
				dst32 += textbuf->pitch/4;
			}
		}
	}
#endif
	return(textbuf);
}



//==================================================================================
// Renders the Unicode string to TrueType on surface or Renderer (depending on the target CBitmap mode, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (255-solid, 0-max).
//==================================================================================
SDL_Rect CTTFFont::textout_UNI(CBitmap *TargetBitmap, const Uint16 *uni, Sint16 x, Sint16 y, Uint32 fcolor, Uint32 bcolor, int Alpha)
{
	SDL_Rect ret; ret.x=0; ret.y=0; ret.w=0; ret.h=0;

	SDL_Surface *text;
	SDL_Color fgcolor,bgcolor;
	fgcolor.r=Colors::getRed(fcolor);
	fgcolor.g=Colors::getGreen(fcolor);
	fgcolor.b=Colors::getBlue(fcolor);
	bgcolor.r=Colors::getRed(bcolor);
	bgcolor.g=Colors::getGreen(bcolor);
	bgcolor.b=Colors::getBlue(bcolor);

	text=RenderUNICODE(uni,fgcolor,bgcolor);

	if(text==NULL){return ret;}

 	// Align the surface text to the baseline
	Uint16 ascent= this->getFontAscent();


	// Set the color to be transparent
	//Uint32 Clear = SDL_MapRGB(text->format,temp.r,temp.g,temp.b);
 	::SDL_SetColorKey(text, SDL_TRUE, bcolor);
	SDL_Rect retanguloDest;
	retanguloDest.x =x;
	retanguloDest.y=y-ascent;
	retanguloDest.w=text->w;
	retanguloDest.h=text->h;
 	// Set the alpha value

	::SDL_SetSurfaceAlphaMod(text,Alpha);


	if  (TargetBitmap->getBitmapMode() == SGF::CBitmap::DRAW_TYPE_TEXTURE) {

		RenterToRenderer(x, y,TargetBitmap->getMyRenderWindow(), *text ,ascent);

	//===END BLIT TO RENDERER ===========================
	ret.x=x; ret.y=y-ascent; ret.w=text->w; ret.h=text->h;

	}else if (TargetBitmap->getBitmapMode() == SGF::CBitmap::DRAW_TYPE_SURFACE) {
		//================   BLIT TO BITMAP SURFACE ================
		//Get offsets
    retanguloDest.x = x;
    retanguloDest.y = y-ascent;
	retanguloDest.w = text->w;
    retanguloDest.h = text->h;
	if (SDL_MUSTLOCK(TargetBitmap->getBitmap()))
		::SDL_LockSurface(TargetBitmap->getBitmap());

	if(SDL_BlitSurface(text, NULL, TargetBitmap->getBitmap(), &retanguloDest)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;


	}
	::SDL_UnlockSurface(TargetBitmap->getBitmap());

	SDL_FreeSurface(text);
	return ret;
}


//==================================================================================
// Renders the Unicode UTF16 string to TrueType on surface, or Renderer (depending on the target CBitmap mode, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max). (RGB)
//==================================================================================


SDL_Rect CTTFFont::textout_UNI(CBitmap *TargetBitmap, const Uint16 *uni, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha)
{
	SDL_Rect ret; ret.x=0; ret.y=0; ret.w=0; ret.h=0;
	SDL_Surface *text;

	SDL_Color Color1,Color2;
	Color1.r= fR;
    Color1.g=fG;
	Color1.b=fB;
	Color2.r=bR;
	Color2.g=bG;
	Color2.b=bB;

	text=RenderUNICODE(uni,Color1,Color2);
	if(text==NULL){return ret;}

	/* Align the surface text to the baseline */
	Uint16 ascent=this->getFontAscent();


	::SDL_SetColorKey(text, SDL_TRUE, SDL_MapRGB(text->format,bR,bG,bB));
	SDL_Rect retanguloDest;
	retanguloDest.x =x;
	retanguloDest.y=y-ascent;
	retanguloDest.w=text->w;
	retanguloDest.h=text->h;

	::SDL_SetSurfaceAlphaMod(text,Alpha);
	if (TargetBitmap->getBitmapMode() == SGF::CBitmap::DRAW_TYPE_TEXTURE) {
		RenterToRenderer(x, y,TargetBitmap->getMyRenderWindow(), *text ,ascent);
	}else if (TargetBitmap->getBitmapMode() == SGF::CBitmap::DRAW_TYPE_SURFACE) {
		//================   BLIT TO BITMAP SURFACE ================
		//Get offsets
    retanguloDest.x = x;
    retanguloDest.y = y-ascent;
	retanguloDest.w = text->w;
    retanguloDest.h = text->h;
		if (SDL_MUSTLOCK(TargetBitmap->getBitmap()))
		::SDL_LockSurface(TargetBitmap->getBitmap());

			if(SDL_BlitSurface(text, NULL, TargetBitmap->getBitmap(), &retanguloDest)!=0)
					Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;


			}
		::SDL_UnlockSurface(TargetBitmap->getBitmap());

	SDL_FreeSurface(text);
	return ret;
}



//==================================================================================
// Renders the Unicode string to TrueType on surface, or Renderer (depending on the target CBitmap mode, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max). (RGB)
//==================================================================================


SDL_Rect CTTFFont::textout_UNI_Renderer(int TargetWindow, const Uint16 *uni, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha)
{
	SDL_Rect ret; ret.x=0; ret.y=0; ret.w=0; ret.h=0;
	SDL_Surface *text;

	SDL_Color Color1,Color2;
	Color1.r= fR;
    Color1.g=fG;
	Color1.b=fB;
	Color2.r=bR;
	Color2.g=bG;
	Color2.b=bB;

	text=RenderUNICODE(uni,Color1,Color2);
	if(text==NULL){return ret;}

	/* Align the surface text to the baseline */
	Uint16 ascent=this->getFontAscent();


	::SDL_SetColorKey(text, SDL_TRUE, SDL_MapRGB(text->format,bR,bG,bB));
	SDL_Rect retanguloDest;
	retanguloDest.x =x;
	retanguloDest.y=y-ascent;
	retanguloDest.w=text->w;
	retanguloDest.h=text->h;

	::SDL_SetSurfaceAlphaMod(text,Alpha);

	RenterToRenderer(x, y,TargetWindow, *text ,ascent);

	SDL_FreeSurface(text);

	ret.x=x; ret.y=y-ascent; ret.w=text->w; ret.h=text->h;
	return ret;
}


//==================================================================================
// Renders the Latin-1 string to TrueType on surface, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max).
//==================================================================================
SDL_Rect CTTFFont::textout(CBitmap *TargetBitmap, const char *string, Sint16 x, Sint16 y, Uint32 fcolor, Uint32 bcolor, int Alpha)
{
	SDL_Rect ret;
	ret.w=ret.h=ret.x=ret.y=0;
	if (!TargetBitmap) return ret;

	if (_my_font ==NULL) return ret;
	else{
	Uint16 *uni;

	uni=Utf::Latin1_Uni(string);

	ret=textout_UNI(TargetBitmap,uni,x,y,fcolor,bcolor,Alpha);
	free(uni);
	}
	return ret;
}

//==================================================================================
// Renders the Latin-1 string to TrueType on surface, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max). (RGB)
//==================================================================================
SDL_Rect CTTFFont::textout(CBitmap *TargetBitmap, const char *string, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha)
{
	SDL_Rect ret;
	ret.w=ret.h=ret.x=ret.y=0;
	if (!TargetBitmap) return ret;

	if (_my_font ==NULL) return ret;

	else {
	Uint16 *uni;

	uni=Utf::Latin1_Uni(string);

	ret=textout_UNI(TargetBitmap,uni,x,y, fR,fG,fB, bR,bG,bB, Alpha);
	free(uni);
}
	return ret;
}


//==================================================================================
// Renders the UTF-8 string to TrueType on surface, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max).
//==================================================================================
SDL_Rect CTTFFont::textout_UTF8(CBitmap *TargetBitmap, const char *string, Sint16 x, Sint16 y, Uint32 fcolor, Uint32 bcolor, int Alpha)
{
	SDL_Rect ret;
	ret.w=ret.h=ret.x=ret.y=0;
	if (_my_font ==NULL) return ret;
	else {
	Uint16 *uni;

	uni=Utf::UTF8_Uni(string);

	ret=textout_UNI(TargetBitmap,uni,x,y,fcolor,bcolor,Alpha);
	free(uni);
	}
	return ret;
}

//==================================================================================
// Renders the UTF-8 string to TrueType on surface, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max). (RGB)
//==================================================================================
SDL_Rect CTTFFont::textout_UTF8(CBitmap *TargetBitmap, const char *string, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha)
{
	SDL_Rect ret;
	ret.w=ret.h=ret.x=ret.y=0;
	if (_my_font ==NULL) return ret;
	else {
	Uint16 *uni;

	uni=Utf::UTF8_Uni(string);

	ret=textout_UNI(TargetBitmap,uni,x,y, fR,fG,fB, bR,bG,bB, Alpha);
	free(uni);
	}
	return ret;
}


//==================================================================================
// Renders the formatet Latin-1 string to TrueType on surface, with the color fcolor.
// bcolor is the target color for the antialiasing.
// Alpha sets the transparency of the text (0-solid, 255-max). (RGB ONLY)
// * just like printF(char *format,...) *
//==================================================================================
SDL_Rect CTTFFont::textoutf(CBitmap *TargetBitmap, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha ,const char *format,...)
{
	char buf[256];

	va_list ap;

	#ifdef __WIN32__
	va_start(ap, format); //va_start((va_list*)ap, format); //Stupid win32 crosscompiler
	#else
	va_start(ap, format);
	#endif

	std::vsprintf(buf, format, ap);
	va_end(ap);

	return textout(TargetBitmap, buf, x,y, fR,fG,fB, bR,bG,bB, Alpha);
}








void CFont::drawText( int x, int y, int xSize, int ySize,  Colors::ColorDefinition color, CBitmap & work, const string & str, int marker, ... )  {
    char buf[512];
    va_list ap;
    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);

    //int old_x = 0;
    //int old_y = 0;
    //this->getSize(&old_x, &old_y);

    //setSize(xSize, ySize);
	// Colors::ColorDefinition cor= work.getColor(color);
	work.Render(buf,x,y,color,_real_Font);
	if(work.getError())
        Debug::debug(Debug::font,__FUNCTION__) << "CBitmap ERROR "<< endl;

    //this->setSize(old_x, old_y);

}
void CFont::drawText( int x, int y, int xSize, int ySize, int color, const CBitmap & work, const string & str, int marker, ... )const{
	 Colors::ColorDefinition tempColor;
	tempColor.r=Colors::getRed(color);
	tempColor.g=Colors::getGreen(color);
	tempColor.b=Colors::getBlue(color);
	//printF(x,y,xSize,ySize,tempColor,work,str,marker);
	char buf[512];
    va_list ap;
    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);

    //int old_x = 0;
    //int old_y = 0;
    //this->getSize(&old_x, &old_y);

    //setSize(xSize, ySize);
	// Colors::ColorDefinition cor= work.getColor(color);
	work.Render(buf,x,y,tempColor,_real_Font);
	if(work.getError())
        Debug::debug(Debug::font,__FUNCTION__) << "CBitmap ERROR "<< endl;
}
void CFont::drawText( int x, int y, int xSize, int ySize,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... )  {

	char buf[512];
    va_list ap;
    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);

    //int old_x = 0;
    //int old_y = 0;
    //this->getSize(&old_x, &old_y);

    //setSize(xSize, ySize);
	// Colors::ColorDefinition cor= work.getColor(color);
	work.Render(buf,x,y,color,_real_Font);
	if(work.getError())
        Debug::debug(Debug::font,__FUNCTION__) << "CBitmap ERROR "<< endl;

    //this->setSize(old_x, old_y);

}

void CFont::drawText( int x, int y, int color_sdl, const CBitmap & work, const string & str, int marker, ... ) const {

	 Colors::ColorDefinition color;
	color.r= Colors::getRed(color_sdl);
	color.g= Colors::getGreen(color_sdl);
	color.b= Colors::getBlue(color_sdl);

	Debug::debug(Debug::bitmap,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);
    Debug::debug(Debug::bitmap,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	// Colors::ColorDefinition cor=work.getColor(color);
	work.Render(buf,x,y,color,_real_Font);

}
//Draw a string to video using CBitmap
void CFont::drawText(int x,int y, Colors::ColorDefinition textColor,  CBitmap &work,const char *strText,...)
{
  char string[512];          // Temporary string
  va_list ap;                // Pointer To List Of Arguments
  va_start(ap, strText);     // Parses The String For Variables
  std::vsprintf(string, strText, ap); // Converts Symbols To Actual Numbers
  va_end(ap);

  work.Render(string,x,y,textColor,_real_Font);
}
void CFont::drawText( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const string & str, int marker, ... )  {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	// Colors::ColorDefinition cor=work.getColor(color);
	work.Render(buf,x,y,color,_real_Font);

}

void CTTFFont::drawToSurface( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... ) const {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), strText, ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;

	work.useSurface();
	work.Render(buf,x,y,color,(CFont *)this);
	work.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

}

void CTTFFont::drawToTexture( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... ) const {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), strText, ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	// Colors::ColorDefinition cor=work.getColor(color);
	work.useTexture();
	work.Render(buf,x,y,color,(CFont *)this);
	work.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

}

void CTTFFont::drawToRenderer( int x, int y,  Colors::ColorDefinition color, const char *strText, int marker, ... ) const {
//TODO

}
//TODO:  Not Working correctly.
// Solve the problmem when rendering centralizad text
void CTTFFont::printF( int x, int y, int flags, int fg,const char* text ){
	MESSAGESIZE tamanho= getTextSize(text);
	CBitmap destino(tamanho.w,tamanho.h);
	destino.SetBlendMode(CBitmap::MODE_TRANS);
	destino.useSurface();
	destino.fill(0);
	destino.applyTrans(0);
	drawTextMSZ(text,0,0,flags,fg,&destino);
	destino.CreateTextureFromBitmap();
	destino.useTexture();
	destino.Blit(x,y);
}
char *my_strdup(const char *str) {
    size_t len = strlen(str);
    char *x = (char *)malloc(len+1); /* 1 for the null terminator */
    if(!x) return NULL; /* malloc could not allocate memory */
    memcpy(x,str,len+1); /* copy the string into the new buffer */
    return x;
}

int CTTFFont::drawTextMSZ( const char* string, int x, int y, int flags,
	int fg, CBitmap* tgt )
{


	int retval = 0;

	if (!string || !*string) return retval;

	if (flags & UseTilde)
	{
		char *str2 = my_strdup( string );
		char onechar[2];
		char *c1, *c2, *c3;
		int w = 0;
		int i, j;
		bool notend;

		if (flags & AlignHCenter)
		{
			// Determine width of the string without the stupid tildes
			c1 = c2 = str2;
			notend = true;


			while (notend)
			{
				c2 = c1;								// c1: start of this run
				while (*c2 && (*c2!='~')) c2++;			// c2: end of this run
				notend = *c2;
				*c2 = 0;
				MESSAGESIZE tamanho =this->getTextSize(c1);
				i= tamanho.w;
				j=tamanho.h;
				w += i;

				if (notend) { *c2='~'; c1=c2+1; }		// next run..
			}

			x -= w/2;
		}

		flags &= ~(UseTilde | AlignHCenter);

		c1 = str2;
		onechar[1]=0;
		notend = true;

		while (1)
		{
			c2 = c1;
			while (*c2 && (*c2!='~')) c2++;			// c2: end of this run
			notend = *c2;
			*c2 = 0;
			MESSAGESIZE tamanho =this->getTextSize(c1);
				i= tamanho.w;
				j=tamanho.h;
			//sge_TTF_SizeText( font, c1, &i, &j);
			drawTextMSZ( c1, x, y, flags, fg, tgt );
			x += i;

			// At this point, we're either at a ~ or end of the text (notend)
			if (!notend) break;

			onechar[0]= *++c2;						// Could be 0, if ~ at end.
			if (!onechar[0]) break;
			tamanho =this->getTextSize(onechar);
				i= tamanho.w;
				j=tamanho.h;
			//sge_TTF_SizeText( font, onechar, &i, &j);
			drawTextMSZ( onechar, x, y, flags, Colors::makeColor(Colors::MortalLightCyan), tgt );
			x += i;
			retval += i;
			c1 = c2+1;


			if (!*c1) break;						// ~X was end of string
		}

	//	delete( str2 );
		return retval;
	}

	SDL_Rect dest;
	int w, h;
	MESSAGESIZE tamanho =this->getTextSize(string);
				w= tamanho.w;
				h=tamanho.h;
	//sge_TTF_SizeText( font, string, &w, &h );
	dest.w = retval = w;
	dest.h = h;
	dest.x = flags & AlignHCenter ? x-dest.w/2 : x;
	dest.y = flags & AlignVCenter ? y-dest.h/2 : y;

	//Debug::debug(Debug::error,__FUNCTION__) << "X: %d, Y: %d, W: %d, H: %d\n", dest.x, dest.y, dest.w, dest.h );

	if ( flags & UseShadow )
	{
		if ( flags & UseUTF8 )
		this->textout_UTF8( tgt, string, dest.x+2, dest.y+2+this->getFontAscent(), Colors::makeColor(Colors::Black),Colors::makeColor(Colors::Black), 255 );
		else
		this->textout( tgt, string, dest.x+2, dest.y+2+this->getFontAscent(), Colors::makeColor(Colors::Black),Colors::makeColor(Colors::Black), 255 );

	}

	this->AAenable();
	if ( flags & UseUTF8 )
	dest =textout_UTF8(  tgt, string, dest.x, dest.y+this->getFontAscent(), fg,Colors::makeColor(Colors::Black), 255 );
	else
	dest = this->textout( tgt, string, dest.x, dest.y+this->getFontAscent(), fg, Colors::makeColor(Colors::Black), 255 );

	this->AAdisable();

	return dest.w;
}

void CTTFFont::drawGradientText( const char* text,  int y, CBitmap* tgt)
{
	int i, j;
	SDL_Surface* target = tgt->getBitmap();

	// 1. CREATE OFFSCREEN SURFACE
	MESSAGESIZE ssize = this->getTextSize((char*)text );
	SDL_Rect size;
	size.w=ssize.w;
	size.h=ssize.h;
	size.w += 2;
	size.h += 2;
	size.x = 320 - size.w / 2;
	if ( size.x < 0 ) size.x = 0;
	size.y = y;
	CBitmap *surface = NULL;

	surface = new CBitmap(size.w, size.h);

	if ( NULL == surface )
	{
		Debug::debug(Debug::error,__FUNCTION__) << "DrawGradientText: Couldn't allocate surface (w,h): " << size.w << " , " << size.h <<endl;
		return;
	}
	surface->useSurface();
	surface->fill(0);

	// 2. SET OFFSCREEN SURFACE COLORS
	surface->applyTrans(0);

	Effects::CGradientSimple gradiente(256,Colors::Red,Colors::Yellow);

	// 3. DRAW TEXT, APPLY BORDER, APPLY GRADIENT.

	int y1 = this->getFontAscent();
	Uint32 bcolor = Colors::makeColor(Colors::Red);
	Colors::ColorDefinition color2 = Colors::Black;
	this->textout( surface, text, 1, y1, bcolor, 0, 255);  //the text is on the surface

	if ( SDL_MUSTLOCK(surface->getBitmap()) ) SDL_LockSurface(surface->getBitmap());
	for ( y=1; y<size.h-1; ++y )
	{
		Colors::ColorDefinition cor = gradiente.current();
		gradiente.update(size.h,y);
		for ( int x=1; x<size.w-1; ++x )
		{
			Uint32 pixelOrigem=surface->getPixelSurface(x,y);
			if ( pixelOrigem == bcolor) surface->putPixelSurface(x,y,cor.r,cor.g,cor.b);
			else surface->putPixelSurface(x,y,color2.r,color2.g,color2.b);
		}

	}
	if ( SDL_MUSTLOCK(surface->getBitmap()) ) SDL_UnlockSurface(surface->getBitmap());
	if(tgt->getBitmapMode()==CBitmap::DRAW_TYPE_TEXTURE) {
	// 4. FINALLY
	surface->useTexture();
	surface->SetBlendMode(SGF::CBitmap::MODE_TRANS);
	surface->applyTrans(Colors::makeColor(Colors::Black)); //aqui a textura � atualizada
	surface->Blit(size.x, size.y);
	}else {
	surface->useSurface();
	surface->SetBlendMode(SGF::CBitmap::MODE_TRANS);
	surface->applyTrans(Colors::makeColor(Colors::Black)); //aqui a textura � atualizada
	surface->BlitSurface(size.x, size.y,*tgt);

	}
	delete surface;
	//surface->BlitToScreen();
	//SDL_BlitSurface( surface, NULL, target, &size );
	//SDL_FreeSurface( surface );
	//SDL_UpdateRect( target, size.x, size.y, size.w, size.h );

}


void CFont::drawText( int x, int y,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... )  {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	// Colors::ColorDefinition cor=work.getColor(color);
	work.Render(buf,x,y,color,_real_Font);

}

void CFont::drawText( int x, int y,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... ) const {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	// Colors::ColorDefinition cor=work.getColor(color);
	work.Render(buf,x,y,color,_real_Font);

}
//! m�todo usado para m�dulo de compatibilidade
void CTTFFont::RenderToSurface( int x, int y, const CBitmap &dst, Colors::ColorDefinition textColor,char *string){
     // N�o adaptada para SDL 1.3 sem o modo de compatibilidade. neste caso utile a fun��o do m�dulo CBitmap
     //Debug::debug(Debug::font, __FUNCTION__) << "string =");
     //Debug::debug(Debug::font, __FUNCTION__) << string);
     //Holds offsets
    SDL_Rect offset;
    //Get offsets
    offset.x = x;
    offset.y = y;
	umessage = TTF_RenderText_Solid( (TTF_Font*)getFont(), string, textColor.toSDL() );

	// todo usar Cbitmap ao inves de SDL
	SDL_BlitSurface(umessage, NULL, dst.getBitmap(), &offset );
	 SDL_FreeSurface(umessage);

}

void CTTFFont::RenterToRenderer(int x, int y, int TargetWindow, SDL_Surface &text ,int ascent){

	//=======CREATE TEXTURE==============
	SDL_Texture *TextTexture;

	TextTexture=SDL_CreateTextureFromSurface(CBitmap::getMyRenderer(TargetWindow), &text);

	if ( ! TextTexture ){
//			error = true;
			Debug::debug(220) << "Could not create Texture! - Error=" << SDL_GetError()<< endl;
		}else { }

    //=====END CREATE TEXTURE ==============

	//================   BLIT TO RENDER ================
	SDL_Rect retanguloDest;

    //Get offsets
    retanguloDest.x = x;
    retanguloDest.y = y-ascent;
	retanguloDest.w = text.w;
    retanguloDest.h = text.h;
		Debug::debug(Debug::bitmap,__FUNCTION__) << "[Destino(window): "<<TargetWindow <<" ] x= "<<x <<" , y= "<<y <<" , w= " << retanguloDest.w << ", h= " <<retanguloDest.h << endl;
			if(SDL_RenderCopy(CBitmap::getMyRenderer(TargetWindow),TextTexture, NULL, &retanguloDest)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

	//===END BLIT TO RENDER===========================

	SDL_DestroyTexture(TextTexture);

}


/*
CTTFFont *CTTFFont::CheckLoaded(int fontnumber) {
map<int,void*>::iterator it = MyLoadedFonts.find(100);
	if( it != MyLoadedFonts.end() )

	return NULL;
	else
		return (CTTFFont *) it->second;

} */

//! Vefifica se a fonte est� na lista de fontes dispon�veis
//! Agora � feito na font_factory
/*
CTTFFont *CTTFFont::CheckLoaded(string fonte) {
    if  (fonte=="")
		return NULL;
	map<string,void*>::iterator it;

	it = CFontList::GetInstance()->MyTTFLoadedFonts.find(fonte);
	if( it == CFontList::GetInstance()->MyTTFLoadedFonts.end() )
	return NULL;
	else
		return (CTTFFont *) it->second;

}
*/
int CTTFFont::getMaxHeight() const {
	if (_my_font !=NULL)
	 return TTF_FontHeight(this->_my_font);
	else return -1;
}
int CTTFFont::getHeight() const {
	int height;
	if (this->_my_font !=NULL){
		height=TTF_FontLineSkip(this->_my_font);
		if(height==-1){
			//printF("%s\n",TTF_GetError());
		}else {
		//printF("minx    : %d\n",minx);
		//printF("maxx    : %d\n",maxx);
		//printF("miny    : %d\n",miny);
		//printF("maxy    : %d\n",maxy);
		//printF("Height : %d\n",height);
		return height; // coloque 3 pixels para testar
		}

	}else return 0;

}

int CTTFFont::getFontAscent()const{
	if (_my_font !=NULL)
	return TTF_FontAscent(_my_font);
	else return -1;
	}
int CTTFFont::getFontDescent()const{
	if (_my_font !=NULL)
	return TTF_FontDescent(_my_font);
	else return -1;

}
int CTTFFont::getFontLineSkip()const{
	if (_my_font !=NULL)
	return TTF_FontLineSkip(_my_font);
	else return -1;
}
//=Anti Aliasing============
void CTTFFont::AAenable(){
	TTF_AA=Shaded;
}
void CTTFFont::AAdisable(){
	TTF_AA=Solid;
}
void CTTFFont::AlphaRenderEnaable(){
	TTF_AA=Blended;
}

//=============
int CTTFFont::getTextHeight( const string & str ) const{
if (this->_my_font !=NULL)
	return ::TTF_FontHeight(this->_my_font);
	else return 0;

}


int CTTFFont::getWidth() const {
	int minx,maxx,miny,maxy,advance;
	if (this->_my_font !=NULL){
		if(TTF_GlyphMetrics(_my_font,'g',&minx,&maxx,&miny,&maxy,&advance)==-1) {
				//printF("%s\n",TTF_GetError());
		}else {
		//printF("minx    : %d\n",minx);
		//printF("maxx    : %d\n",maxx);
		//printF("miny    : %d\n",miny);
		//printF("maxy    : %d\n",maxy);
		//printF("advance : %d\n",advance);
		return advance+3;  //coloquei 3 pixels para testar
		}

	}else return 0;
}
int CTTFFont::getTextLength( const string & str ) const{
if (this->_my_font !=NULL)
return getTextLength( str.c_str() );
	else return 0;

}

void CTTFFont::setSize( const int x, const int y ){
    this->sizeX = -1;
    this->sizeY = y;
	closeFont();
	setFont( LoadFont(this->fontName,sizeX) );
	//this->_my_font   //font->setSize( this->sizeX, this->sizeY );
}

int CTTFFont::getSizeX() const {
    return this->sizeX;
}

int CTTFFont::getSizeY() const {
    return this->sizeY;
}

void CTTFFont::closeFont() {

TTF_CloseFont(this->_my_font);
}

int CTTFFont::getTextLength( const char * text ) const {

MESSAGESIZE tamanho;
tamanho.w=0;
tamanho.h=0;
if (getFont()!=NULL) {
	::TTF_SizeText((TTF_Font*)getFont(), text, &tamanho.w, &tamanho.h);
	}
	return tamanho.w;

}

int CTTFFont::getTextHeight( const char * text ) const {

MESSAGESIZE tamanho;
tamanho.w=0;
tamanho.h=0;
	if (getFont()!=NULL) {
	::TTF_SizeText((TTF_Font *) getFont(), text, &tamanho.w, &tamanho.h);
	}
	return tamanho.h;


}

// lembrar de deletar a mensagem retornada para evitar memory leak
MESSAGESIZE *CTTFFont::GetTextSize(const char *text ) {
	static MESSAGESIZE tamanho;
	::TTF_SizeText((TTF_Font *)getFont(), text, &tamanho.w, &tamanho.h);
   return &tamanho;
}

MESSAGESIZE CTTFFont::getTextSize( const char * text ) const{
MESSAGESIZE tamanho;
tamanho.w=0;
tamanho.h=0;
	if (getFont()!=NULL) {
	::TTF_SizeText((TTF_Font *) getFont(), text, &tamanho.w, &tamanho.h);
	}
	return tamanho;

}
MESSAGESIZE CTTFFont::getTextSize( const string & text ) const{
	return getTextSize(text.c_str());
}

//==================================================================================
// Get the width of the text with the given font
//==================================================================================
MESSAGESIZE CTTFFont::getTextSizeUNI(const Uint16 *text)const
{

	MESSAGESIZE ret; ret.w=0, ret.h=0;
	if (_my_font!=NULL) {
	if(TTF_SizeUNICODE((TTF_Font *) _my_font,text,&ret.w,&ret.h)) {
		return ret;
		// perhaps print the current TTF_GetError(), the string can't be rendered...
		}
	}
	return ret;
}

MESSAGESIZE  CTTFFont::getTextSize(const char *text, int a_iMaxLength)const
{
	MESSAGESIZE ret;
	Uint16 *unicode_text;
	int unicode_len;

	/* Copy the Latin-1 text to a UNICODE text buffer */
	unicode_len = strlen(text);
	if ( unicode_len > a_iMaxLength
		&& a_iMaxLength>=0 )
	{
		unicode_len = a_iMaxLength;
	}
	unicode_text = (Uint16 *)malloc((unicode_len+1)*(sizeof *unicode_text));
	if ( unicode_text == NULL ) {
		Debug::debug(Debug::error,__FUNCTION__)<<" Out of memory"<< endl;
		return ret;
	}
	Utf::ASCII_to_UNICODE( unicode_text, text, unicode_len );

	/* Render the new text */
	ret = getTextSizeUNI(unicode_text);

	/* Free the text buffer and return */
	free(unicode_text);

	return ret;
}




//====================END Text Sizing================



void CTTFFont::printfWrapLine(int x, int & y, int color, const CBitmap & work, int maxWidth, const char * line) const {
   Debug::debug(Debug::font, __FUNCTION__) << endl;
		int height = getHeight();
    while (*line != '\0'){
        char tmp2[1024];
        int left = strlen(line);
        int min = 0;
        int max = left;
        int current = (min + max) / 2;
        strncpy(tmp2, line, current);
        tmp2[current] = '\0';
        bool done = false;
        while (!done){
            int length = getTextLength(tmp2);
            if (length >= maxWidth){
                max = current;
                current = (min + max) / 2;
                strncpy(tmp2, line, current);
                tmp2[current] = '\0';
            } else if (length < maxWidth && current < max){
                min = current;
                current = (min + max) / 2;
                if (current == max - 1){
                    current = max;
                    done = true;
                }
                strncpy(tmp2, line, current);
                tmp2[current] = '\0';
            } else {
                done = true;
            }
        }

		CFont::drawText(x, y, color, work, string(tmp2), 0);
        y += height;

        line += current;
    }

    y += height / 2;
}

void CTTFFont::printfWrap(int x, int y, int color, const CBitmap & work, int maxWidth, const string & str, int marker, ... ) const {
    Debug::debug(Debug::font, __FUNCTION__) << endl;
	char buf[4096];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);

    char * start = buf;
    char * end = strchr(start, '\n');
    while (end != NULL){
        char tmp[1024];
        unsigned int ender = end - start;
        if (ender >= sizeof(tmp) - 1){
            ender = sizeof(tmp) - 1;
        }

        strncpy(tmp, start, ender);
        tmp[ender] = '\0';
        printfWrapLine(x, y, color, work, maxWidth, tmp);

        start = end + 1;
        end = strchr(start, '\n');
    }
    printfWrapLine(x, y, color, work, maxWidth, start);
}

//Todo:  feito na font_factory
/*
CTTFFont & CTTFFont::getFont( const string & name, const int x, const int y ){
    //verificar se afonte est� inicializada, sen�o inicialiar e retornar um ponteiro para a calsse criada
	//arrumar...verificar o tamanho da fonte e se ela esta carregada coorretamente
	CTTFFont *teste = CheckLoaded(name);
	if(teste==NULL)
		teste = new CTTFFont(name,y);

   return *teste;
}

CTTFFont & CTTFFont::getDefaultFont(){
	// return getFont( "tmp/comic.ttf" );
    return getFont( WORKFONT, 16, 16 );
}
*/
//==================================CFont===========================
CFont::CFont(CFont * Font):
_real_Font(Font),
fontOk(false)
{
}
CFont::~CFont(){
}

void CFont::printfWrapLine(int x, int & y, int color, const CBitmap & work, int maxWidth, const char * line) const {
	Debug::debug(Debug::font, __FUNCTION__) << endl;
		int height = getHeight();
    while (*line != '\0'){
        char tmp2[1024];
        int left = strlen(line);
        int min = 0;
        int max = left;
        int current = (min + max) / 2;
        strncpy(tmp2, line, current);
        tmp2[current] = '\0';
        bool done = false;
        while (!done){
            int length = getTextLength(tmp2);
            if (length >= maxWidth){
                max = current;
                current = (min + max) / 2;
                strncpy(tmp2, line, current);
                tmp2[current] = '\0';
            } else if (length < maxWidth && current < max){
                min = current;
                current = (min + max) / 2;
                if (current == max - 1){
                    current = max;
                    done = true;
                }
                strncpy(tmp2, line, current);
                tmp2[current] = '\0';
            } else {
                done = true;
            }
        }
		drawText(x, y, color, work, string(tmp2), 0);
        y += height;

        line += current;
    }

    y += height / 2;
}

void CFont::printfWrap(int x, int y, int color, const CBitmap & work, int maxWidth, const string & str, int marker, ... ) const {
    Debug::debug(Debug::font, __FUNCTION__) << endl;
	char buf[4096];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), str.c_str(), ap);
    va_end(ap);

    char * start = buf;
    char * end = strchr(start, '\n');
    while (end != NULL){
        char tmp[1024];
        unsigned int ender = end - start;
        if (ender >= sizeof(tmp) - 1){
            ender = sizeof(tmp) - 1;
        }

        strncpy(tmp, start, ender);
        tmp[ender] = '\0';
        printfWrapLine(x, y, color, work, maxWidth, tmp);

        start = end + 1;
        end = strchr(start, '\n');
    }
    printfWrapLine(x, y, color, work, maxWidth, start);
}


/* name should be the path of a .ttf file in the fonts/ directory.
 * something like 'arial.ttf'
 */
const CFont & CFont::getFont(const Filesystem::CRelativePath & name, const int x, const int y){
	const CFont & font = CResource::getFont(name.path(), x,y);
    /* sanity check */
    if (font.getTextHeight("A") == 0){
        return getDefaultFont();
    }
    return font;
}

const CFont & CFont::getFont( const Filesystem::CAbsolutePath & name, const int x, const int y){
    return CResource::getFont(name.path(), x,y);
}

const CFont & CFont::getFont( const string & name, const int x, const int y){
	return CResource::getFont(name, x,y);
}


const CFont & CFont::getDefaultFont(){
    return CResource::getFont(Filesystem::CRelativePath(string(DEF_FONT_PATH)+WORKFONT).path(), 16, 16);
}
const CFont & CFont::getDefaultFont(int width, int height){
    return CResource::getFont(Filesystem::CRelativePath(string(DEF_FONT_PATH)+WORKFONT).path(), width, height);
}
//==========================BMPFONT  ===================


CBitmapFont::CBitmapFont(const string fonte,bitmaptype _type):
CFont((CFont *) this),
AvailableFonts(CFontList::GetInstance()),
fontName(fonte),
sizeX(0),
sizeY(0),
type(BitmapFont),
_my_bitmaptype(_type)
{

	Debug::debug(Debug::font, __FUNCTION__) << "Constructor // Fontes Dispon�veis="<< AvailableFonts->GetNumFontsBitmap() <<endl;
	//verifica se existe esta fonte na lista de fontes disponiveis
	//verifica se foi passado com ou sem diret�rio
	//se foi passado com diret�rio, tira o diret�rio e carrega todas as fontes que tem nesse diret�rio na lista de fontes
	// Se foi passado sem diret�rio, tem que ter a lista carregada

	string::iterator it;
    bool withpath=0;
	if(fonte.find('/')!=string::npos){
   	  	withpath=1;
	}else if (fonte.find('\\')!=string::npos) {
        withpath=1;
	}
	if(withpath) {
	if (Filesystem::stripDir(fonte).empty()) return;
	setFont( LoadFont(Filesystem::stripDir(fonte)) );
	fontName = fonte; //Todo: retirar o caminho da fonte


	} else
	{
	  if (!AvailableFonts->DefFontsLoaded) {
      // inicializa a lista de fontes
		  Debug::debug(Debug::font,__FUNCTION__) << "Lista de fontes ainda n�o inicializada="<< endl;
	  }else {
		  if (fontName.empty()) return;
	  setFont( LoadFont(fontName) );


	  fontName = fonte; //Todo: retirar o caminho da fonte
	  }
	}

}

CBitmap * CBitmapFont::LoadFont(string font) throw(CLoadException)
{
	string file;
	//pair<map<int, TTF_Font (*)::iterator,bool> ret;
    //Debug::debug(Debug::font, __FUNCTION__) << "CFontList:: Initiating ttf Fonts"<<endl;
     //Open the font
	Debug::debug(Debug::font,__FUNCTION__) << "Iniciando a fonte : "<< font <<endl;
	//se foi passado o diret�rio junto com o nome da fonte.....
	string::iterator it;
    bool withpath=0;
	if(font.find('/')!=string::npos){
   	  	withpath=1;
	}else if (font.find('\\')!=string::npos) {
        withpath=1;
	}
	if (font=="") {
        font=WORKFONT;
        Debug::debug(Debug::resources,__FUNCTION__) << "Carregando a fonte Default : "<< font <<endl;
	    }
	if (withpath){
		file = font;
	}else {
		Debug::debug(Debug::resources,__FUNCTION__) << "Will get fonte Path to : "<< font <<endl;

		  file=  AvailableFonts->GetFontPath(font);

	}



	if (!Util::exists(file)) {
       throw CLoadException(__FILE__, __LINE__,"Caminho N�o encontrado");
	   return NULL;
	}else {
	//char *tmp;
	int offset=0;
	Debug::debug(Debug::font, __FUNCTION__) << "caminho para a fonte: "<< file <<endl;
	//Debug::debug(Debug::sdlmanager,__FUNCTION__) << "font: " << file << endl;
	//string sPath = string(DATADIR) + "/fonts/" + file;
	//string sPath = a_pcFilename;
	_my_font.bitmap= new CBitmap(file);
	bool map=loadCharMap(file+".map");
	if (!map) { //load default charmap
		//try to load fixed font
		//_my_bitmaptype=FIXEDSIZE_type;
		string dir = Filesystem::getBaseDir();
		bool map=loadCharMap(dir+"open\\defaultchar.png.map");
		if (!map) throw CLoadException(__FILE__, __LINE__,"Can not find CharMap");
	};

	switch(_my_bitmaptype) {
	case SGF_type: {
				int pi;
				int i;
				CBitmap * tempBitmap;
				string::iterator it=_my_font.charmap.begin();
				_my_font.Chars=0;
				int largeWidth = 0;
				for (i=0;i<_my_font.bitmap->getWidth();i++) {
					pi=_my_font.bitmap->getPixelSurface(i,0);

					Debug::debug(Debug::font, __FUNCTION__) << "Pixel Color / R / G / B / A / - / "<< Colors::getRed(pi) << " / " << Colors::getGreen(pi) << " / " << Colors::getBlue(pi) << " / " << Colors::getAlpha(pi)<< " / "<<endl;


					if (
							(
							(Colors::getRed(pi)==255) &&
							 (Colors::getGreen(pi)==0) &&
							 (Colors::getBlue(pi)==255)
							 && (Colors::getAlpha(pi)==255)
							) ||
							(i==_my_font.bitmap->getWidth()-1)
					) {

						BITMAPFONTINFO *fi = new BITMAPFONTINFO();
						fi->offset=offset;
						fi->width=i-offset-1;
						_my_font.info.push_back(fi);
						tempBitmap = new CBitmap(*_my_font.bitmap,offset,0,fi->width,_my_font.bitmap->getHeight(),USE_SURFACE);
						_my_font.alphabet[*it]= tempBitmap;
						Debug::debug(Debug::font, __FUNCTION__) << "Found Character / char / offset / width / : / "<< *it << " / " << offset << " / " << fi->width << " / " <<endl;
						offset=i+1;
						it++;
						_my_font.Chars++;
						sizeX = (fi->width > largeWidth ? fi->width : largeWidth);
					}
						sizeY = _my_font.bitmap->getHeight();
				}  //end for
		break;
		}
	case FIXEDSIZE_type: {
		CBitmap * tempBitmap;
		string::iterator it=_my_font.charmap.begin();
		int mapSize=_my_font.charmap.size();
		int CharWidth = _my_font.bitmap->getWidth()/(256); //256 asc - 32 sem caracter (os primeiros 31 characters)
		int CharHeight = _my_font.bitmap->getHeight();
		_my_font.Chars=256;
		sizeY = _my_font.bitmap->getHeight();
		sizeX = CharWidth;
		for (int i=0;i<_my_font.bitmap->getWidth();i+=CharWidth) {
		BITMAPFONTINFO *fi = new BITMAPFONTINFO();
		char asciiChar = static_cast<char>(*it);
		fi->offset=offset;
		//fi->offset= (*it) * CharWidth;
		fi->width=CharWidth;
		_my_font.info.push_back(fi);
		tempBitmap = new CBitmap(*_my_font.bitmap,offset,0,fi->width,_my_font.bitmap->getHeight(),USE_SURFACE);
		_my_font.alphabet[*it]= tempBitmap;

		Debug::debug(Debug::font, __FUNCTION__) << "Found Character / intchar/char / offset / width / : / "<< (int)*it << " / " << asciiChar<<" / "<< offset << " / " << fi->width << " / " <<endl;
		if( it== _my_font.charmap.end()) break;
		it++;
		offset+=CharWidth;
		}

		break;
	}
	case SGE_type: {  /* Karl Bartel's sfont */
		CBitmap * tempBitmap;
		string::iterator it=_my_font.charmap.begin();
		_my_font.Chars=0;
		int largeWidth = 0;


		SDL_Surface *fnt = this->_my_font.bitmap->getBitmap();
		Sint16 x=0;
		int i=0;
		//na primeira linha desta fonte tem um mapeamento de pixels que determina o tamanho de cada caracter baseado na cor do pixel
		Uint32 pi = SGF::Colors::getPixel(fnt,0,0);
		Debug::debug(Debug::font, __FUNCTION__) << "Pixel SGE 0 Color / R / G / B / A / - / "<< Colors::getRed(pi) << " / " << Colors::getGreen(pi) << " / " << Colors::getBlue(pi) << " / " << Colors::getAlpha(pi)<< " / "<<endl;
		//varrelista de characters
		int posicaoInicial,posicaoFinal=0;
		while (x<fnt->w && _my_font.Chars<256){
			BITMAPFONTINFO *fi = new BITMAPFONTINFO();

				if (SGF::Colors::getPixel(fnt,x,0)==pi) {
				//	posicaoInicial=x;
				offset=x;
				Debug::debug(Debug::font, __FUNCTION__) << "Found SGE CHAR ["<< i <<"] at position : "<< x <<endl;

				while (x<fnt->w-1 && SGF::Colors::getPixel(fnt,x,0)==pi)
						x++;   //enquanto for a mesma cor, incrementa x

				posicaoFinal=x;
				fi->offset=posicaoInicial;
				fi->width= posicaoFinal-posicaoInicial;
				//font->CharPos[i++]=x;
				posicaoInicial=posicaoFinal;

				Debug::debug(Debug::font, __FUNCTION__) << "Found SGE CHAR {"<< i <<"} at position : "<< x <<endl;

				_my_font.Chars++;
				sizeX = (fi->width > largeWidth ? fi->width : largeWidth);
				_my_font.info.push_back(fi);
				tempBitmap = new CBitmap(*_my_font.bitmap,fi->offset,1,fi->width,_my_font.bitmap->getHeight()-1,USE_SURFACE);
				_my_font.alphabet[*it]= tempBitmap;
				Debug::debug(Debug::font, __FUNCTION__) << "Found Character / CHAR / offset / width / : / "<< (int)*it << " / " << fi->offset << " / " << fi->width << " / " <<endl;
			    it++;


			} //se a cor n�o for igaual a color, incrementa a posi��o X
			x++;
		}
		sizeY = _my_font.bitmap->getHeight()-1;
		//font->CharHeight = this->_my_font.bitmap->getHeight()-1;
		//font->CharWidth = 0;
		//font->yoffs = 1;


		//this->_my_sge_font = font;

		break;
	}
} //end switch

	if ( !_my_font.bitmap || !map )
	{
		string erro(SDL_GetError());
		Debug::debug(Debug::error,__FUNCTION__) << "LoadBMPFont Couldn't load font: " << file << "error: " << erro <<endl;

	}else this->setFontOK();
	Debug::debug(Debug::sdlmanager,__FUNCTION__) << "load ok: " << file << endl;
	return _my_font.bitmap;
	}
}

MESSAGESIZE CBitmapFont::getTextSize(const char *text)const{
	static MESSAGESIZE tamanho;
	const string str(text);
	const int size = getTextLength(text);
	SDL_Rect  dstRect;
	int offset=0;
	map<int,CBitmap *>::const_iterator first_it;
	string::const_iterator it=str.begin();
	Debug::debug(Debug::error,__FUNCTION__) << "Character: " << (*it) <<endl;

	for (it=str.begin() ;it < str.end();it++) {

		first_it =  _my_font.alphabet.find((int)*it);
		if( first_it != _my_font.alphabet.end() ) {
			dstRect.x=offset;
			dstRect.y=0;
			dstRect.w= (*first_it).second->getWidth();
			dstRect.h= (*first_it).second->getHeight();
			offset+=(*first_it).second->getWidth();
			//Debug::debug(Debug::error,__FUNCTION__) << "Character: " << (*it) <<endl;
			tamanho.w+=offset;
			tamanho.h = (tamanho.h<dstRect.h? dstRect.h : tamanho.h);
		}

	}

	Debug::debug(Debug::error,__FUNCTION__) << "size: " << size <<endl;

   return tamanho;
}


MESSAGESIZE CBitmapFont::getTextSize(const char *text, int a_iMaxLength)const{
	MESSAGESIZE tamanho;
	return tamanho;
}

void CBitmapFont::printfWrap( int x, int y, int color, const CBitmap & work, int maxWidth, const string & str, int marker, ... ) const{
	//Todo
}


int CBitmapFont::getTextHeight( const string & str ) const {
	return _my_font.bitmap->getHeight();
}

int CBitmapFont::getTextHeight( const char * text ) const{
	return _my_font.bitmap->getHeight();
}
int CBitmapFont::getTextLength( const string & str ) const {
	//int c,idx;
	int ret=0;
	map<int,CBitmap *>::const_iterator first_it;
	string::const_iterator it=str.begin();
	Debug::debug(Debug::error,__FUNCTION__) << "Character: " << (*it) <<endl;

	for (it=str.begin() ;it < str.end();it++) {

		first_it =  _my_font.alphabet.find((int)*it);
		if( first_it != _my_font.alphabet.end() ) {
			//Debug::debug(Debug::error,__FUNCTION__) << "Character: " << (*it) <<endl;

			ret +=(*first_it).second->getWidth();
		}

	}
	Debug::debug(Debug::error,__FUNCTION__) << "size: " << ret <<endl;

	return ret;
}

int CBitmapFont::getTextLength( const char * text ) const{
	string string1(text);
	return getTextLength(string1);
}

int CBitmapFont::getMaxHeight() const{
	return 0;
}

void CBitmapFont::drawToSurface( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... ) const  {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf),strText, ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	// Colors::ColorDefinition cor=work.getColor(color);
	work.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	work.Render(buf,x,y,color,(CFont*)this);
	work.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

}
void CBitmapFont::drawToTexture( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... ) const  {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	Debug::debug(Debug::font,__FUNCTION__) << "CBitmap: "<< &work<< endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), strText, ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	work.useTexture();
	work.Render(buf,x,y,color,(CFont*)this);
	work.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

}

void CBitmapFont::drawToRenderer( int x, int y,  Colors::ColorDefinition color,const char *strText, int marker, ... ) const  {
    Debug::debug(Debug::font,__FUNCTION__) << "Parametros: "<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "x: "<< x<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "y: "<< y<< endl;
	Debug::debug(Debug::font,__FUNCTION__) << "Color: "<<(int) color.r << " , "<<(int) color.g << " , "<< (int) color.b << endl;
	char buf[512];
    va_list ap;

    va_start(ap, marker);
    vsnprintf(buf, sizeof(buf), strText, ap);
    va_end(ap);
    Debug::debug(Debug::font,__FUNCTION__) << "Mensagem: "<< buf<< endl;
	//TODO
	//work.useTexture();
	//work.Render(buf,x,y,color,(CFont*)this);
	//work.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

}


//Draw a string to video
void CBitmapFont::drawText(int x,int y,   Colors::ColorDefinition textColor,  CBitmap &work,const char *strText,...)
{
  char string[512];                  // Temporary string
  va_list ap;                // Pointer To List Of Arguments
  va_start(ap, strText);         // Parses The String For Variables
  std::vsprintf(string, strText, ap); // Converts Symbols To Actual Numbers
  va_end(ap);

  work.Render(string,x,y,textColor,(CFont*)this);
}

void CBitmapFont::Render(char *string, const CBitmap &dst, int x,int y, Colors::ColorDefinition textColor){
     // N�o adaptada para SDL 1.3 sem o modo de compatibilidade. neste caso utile a fun��o do m�dulo CBitmap
     //Debug::debug(Debug::font, __FUNCTION__) << "string =");
     //Debug::debug(Debug::font, __FUNCTION__) << string);
     //Holds offsets
    SDL_Rect offset;
    //Get offsets
    offset.x = x;
    offset.y = y;
	//umessage = TTF_RenderText_Solid( GetFont(), string, textColor );

	// todo usar Cbitmap ao inves de SDL
	 SDL_BlitSurface(umessage, NULL, dst.getBitmap(), &offset );
	 SDL_FreeSurface(umessage);

}

bool CBitmapFont::loadCharMap(string file){
	Debug::debug(Debug::font,__FUNCTION__) << " LOADING CHAR MAP: "<< file <<endl;

    string tmp;
    ifstream filein;

    filein.open( file.c_str() );
	if (!filein ) {
        return false;
    }
	stringstream buffer;
	buffer << filein.rdbuf();
	string contents(buffer.str());
    _my_font.charmap = contents;
/*    if (count != size) {
        logtxt.print(file + " - Loading error");
        gameControl->setQuit(true);
        return false;
    }
	*/
    //logtxt.print(file + " loaded");
	Debug::debug(Debug::font,__FUNCTION__) << " CHAR MAP LOADED OK "<<endl;

    return true;

}

static SDL_Surface * CreateSurface(int width, int height)
{
	SDL_Surface* temp=NULL;
	SDL_PixelFormat * pixelFormat= Colors::getCurrentPixelFormat();
	/*	int Bpp;
		Uint32 Rmask,Gmask,Bmask,Amask;
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);

		SDL_PixelFormatEnumToMasks(mode.format, &Bpp,
                                    &Rmask, &Gmask, &Bmask, &Amask);
									*/
	temp= SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,  pixelFormat->BitsPerPixel, pixelFormat->Rmask, pixelFormat->Gmask, pixelFormat->Bmask, pixelFormat->Amask);

		if(temp==NULL) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Create Surface Failed " <<SDL_GetError()<<endl;

		}else {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Create Surface ok " <<temp<<endl;

		}

	return temp;
}
SDL_Surface * CBitmapFont::printBitmap(const char *text) {
	if (*text == NULL) return NULL;
	const string str(text);
	const int size = getTextLength(text);

	SDL_Surface *dest = CreateSurface(size,_my_font.bitmap->getHeight());
	SDL_Rect  dstRect;
	int offset=0;
	map<int,CBitmap *>::const_iterator first_it;
	string::const_iterator it=str.begin();
	Debug::debug(Debug::error,__FUNCTION__) << "Character: " << (*it) <<endl;

	for (it=str.begin() ;it < str.end();it++) {

		first_it =  _my_font.alphabet.find((int)*it);
		if( first_it != _my_font.alphabet.end() ) {
			dstRect.x=offset;
			dstRect.y=0;
			dstRect.w= (*first_it).second->getWidth();
			dstRect.h= (*first_it).second->getHeight();
			offset+=(*first_it).second->getWidth();
			//Debug::debug(Debug::error,__FUNCTION__) << "Character: " << (*it) <<endl;
			SDL_Surface *src = (*first_it).second->getBitmap();
			SDL_BlitSurface(src,NULL, dest, &dstRect);
		}

	}

	Debug::debug(Debug::error,__FUNCTION__) << "size: " << size <<endl;
	return dest;

}
CBitmapFont::~CBitmapFont(){
	// destroy the BITMAPFONTINFO's
	if (_my_font.bitmap) {
		delete _my_font.bitmap;
		_my_font.bitmap=NULL;
	}

	//SGF::CDynamicArray<BITMAPFONTINFO *> info;
	for (int i=0;i<_my_font.info.size();i++) {
		if (_my_font.info[i]) delete (_my_font.info[i]);
		_my_font.info[i]=NULL;
	}
	map<int,CBitmap *>::const_iterator first_it;
	for (first_it=_my_font.alphabet.begin();first_it!=_my_font.alphabet.end();first_it++) {
		if ((*first_it).second) delete ((*first_it).second);
		//(*first_it).second=NULL;
	}


}
} //end SGF
