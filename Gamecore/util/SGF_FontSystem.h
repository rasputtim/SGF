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

#ifndef TEXT_H
#define TEXT_H


#include "../../ExternalLibs/SDL2/include/SDL.h"
#include <map>
#include <stdio.h>
#include <string.h>

#include "../SGF_Config.h"
//use complete path here so will not be necessary to include the path
//on the project that will use sgffabric
#include "../../ExternalLibs/SDL2_ttf-2.0.12/SDL_ttf.h"
#include "SGF_Pointer.h"
#include "../graphics/SGF_Bitmap.h"
#include "SGF_FileSystem.h"
#include "SGF_UtilStructs.h"
#include "../structures/SGF_DynamicArray.h"


//Define Game states ,MENU will have separate STATES
#define WORKFONT "C:/WINDOWS/FONTS/arial.TTF"

using namespace ::std;
namespace SGF {

class CBitmap;
class CFontInfo;
//Esta Classe cria uma lista de todas as fontes disponíveis, tanto TTF quanto CBitmap
// Estas fontes podem ser carregadas posteriormente, para serem utilizadas

#undef printf

/**
 * \class CFontList
 *
 * \ingroup SGF_Util
 *
 * \brief Singleton que possui uma lista com todas as fontes disponíveis
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CFontList
{

public:
	static CFontList* GetInstance();
    ~CFontList();

//static void operator delete (void *arg) // operator delete is implicitely static
//{/
//::delete arg; // Call the global delete operator.
//pCText = 0; // A very important step.
//}

/** \brief carrega a lista com as fontes do systema
*/
void findFonts() throw(CLoadException);
/** \brief vetor com as estruturas de informação de todas as fontes disponíveis
*/
vector<SGF::Util::CReferenceCount<CFontInfo> > & getAvailableFonts() { return availableFonts;}
/** \brief método que carrega as fontes já disponíveis no sistema operacional
*/
static vector<Filesystem::CAbsolutePath> findSystemFonts();

/**encontra uma fonte na lista de fontes
* \param name: o nome da fonte que se deseja encontrar
*/
vector<SGF::Util::CReferenceCount<CFontInfo> >::iterator findFontVector(string name);
//!encontra uma fonte na lista de fontes
::SGF::Util::CReferenceCount<CFontInfo> findFont(string name);
//! retorna o caminho para uma fonte, caso esteja na lista de fontes disponíveis;
string GetFontPath(const string fonte) throw(CLoadException);
//verifica se a fonte está disponível na lista de fontes
int isAvailable(string fonte) throw(CLoadException);
void CleanUp();

//private:
//retorna -1 se houve problema na inicialização da fonte
int InitFont(char* file, int ftSize=12);
int InitFont(string filename, int ftSize=12);
// LoadFonts cria uma lista de todas as fontes ttf que tem no diretório passado
//int LoadFonts(Filesystem::CAbsolutePath &path=Filesystem::CAbsolutePath(DEF_FONT_PATH));
int LoadFonts(Filesystem::CAbsolutePath &path);
//print the list of fonts
void PrintFonts();
int GetNumFontsTTF();
int GetNumFontsBitmap();
//mapa de fontes carregadas
private:

// indica quantas fontes TTF existem na lista
int NumFontsTTF;
int NumFontsBitmap;
public:
//indica se a lista de fontes ttf já foi carrefada com algmas fontes
bool DefFontsLoaded;  //! indica que as fontes default do ambiente já foram adicionadas à lista de fontes
private:
//Contructor
    CFontList();
	//! ponteiro para a instância única da classe
	static CFontList* pCText;
	//!lista de fontes disponíveis
	static vector<SGF::Util::CReferenceCount<CFontInfo> > availableFonts;
};
/**
 * \class CFont
 *
 * \ingroup SGF_Util
 *
 * \brief Classe Base para Tratamento de Fontes
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CFont{
public:
	enum fonttype {
	Unknown,
	TrueTypeFont,
	BitmapFont,
	MUGENFont
	};

	enum Font_Constants {
	AlignHCenter	= 1,
	AlignVCenter	= 2,
	AlignCenter		= 3,
	UseTilde		= 4,
	UseShadow		= 8,
	UseUnicode		= 16,
	UseUTF8         = 32,
	};

	CFont(CFont * Font);
	virtual ~CFont();

	virtual void setSize( const int x, const int y ) = 0;
	virtual int getSizeX() const = 0;
	virtual int getSizeY() const = 0;
	virtual CFont *getFont() const =0;
	//! return the lenght of the text in pixels
	virtual int getTextLength( const char * text ) const = 0;
	//! return the height of the text in pixels
	virtual int getTextHeight( const char * text  ) const = 0;
	//! return the size of the text in pixels
	virtual MESSAGESIZE getTextSize( const char * text ) const =0;
	//! return the size of the text in pixels from position 0 to the position lenght
	virtual MESSAGESIZE getTextSize( const char * text , int lenght) const=0;
	virtual int getHeight() const = 0;
	virtual int getType() const = 0;
	//This should print directly to the renderWindow
	//virtual void printF( int x, int y, int xSize, int ySize,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... ) const = 0;
	//virtual void printF( int x, int y,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... ) const = 0;
	virtual void drawText( int x, int y, int xSize, int ySize,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... ); //=0
	virtual void drawText( int x, int y, int xSize, int ySize,  Colors::ColorDefinition color, CBitmap & work, const string & str, int marker, ... );
	virtual void drawText( int x, int y, int xSize, int ySize, int color, const CBitmap & work, const string & str, int marker, ... ) const; //=0
	virtual void drawText( int x, int y,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... );
	virtual void drawText( int x, int y,  Colors::ColorDefinition color, const CBitmap & work, const string & str, int marker, ... ) const;
	virtual void drawText( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const string & str, int marker, ... ) ;
	virtual void drawText( int x, int y,  Colors::ColorDefinition color, CBitmap &work, const char *strText,...) ;
	virtual void drawText( int x, int y, int color, const CBitmap & work, const string & str, int marker, ... ) const;  //=0

	// This should draw the text to surfaces or textures
	virtual void drawToSurface( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... )const=0;
	virtual void drawToTexture( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... )const=0;
	virtual void drawToRenderer( int x, int y,  Colors::ColorDefinition color, const char *strText, int marker, ... )const=0;


	virtual void printfWrap( int x, int y, int color, const CBitmap & work, int maxWidth, const string & str, int marker, ... ) const;

	static const CFont & getDefaultFont();
	static const CFont & getDefaultFont(int width, int height);
	static const CFont & getFont( const string & name, const int x = 32, const int y = 32 );
	static const CFont & getFont( const Filesystem::CRelativePath & name, const int x = 32, const int y = 32 );
	static const CFont & getFont( const Filesystem::CAbsolutePath & name, const int x = 32, const int y = 32 );
	void setFontOK() {fontOk=true;};
	bool isFontOK() { return fontOk;};
	/* store all the freetype fonts forever */
	//static vector< ftalleg::freetype * > cacheFreeType;
protected:
		fonttype type;
        void printfWrapLine(int x, int & y, int color, const CBitmap & work, int maxWidth, const char * line) const;
		CFont * _real_Font;
		bool fontOk;
};

/**
 * \class CTTFFont
 *
 * \ingroup SGF_Util
 *
 * \brief Classe de Fontes True Type
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CTTFFont :public CFont{
private:
	enum RenderingMode {
		Solid=0,
		Shaded,
		Blended
	};

	enum style {
		Normal=0x00,
		Bold=0x01,
		Italic=0x02,
		Underline=0x04,
		StrikeThrough=0x08

	};


public:
	 //CTTFFont(int fontnumber, int ptsize=12);
	CTTFFont(const string, int ptsize=12);
    ~CTTFFont();
	CFontList * AvailableFonts;

	//Needed Variables
    SDL_Surface *umessage;

	void setStyle(int style);
    //The font
    //static CTTFFont *CheckLoaded(int fontnumber);
	static CTTFFont *CheckLoaded(string fonte);
	TTF_Font *fonte;
    //coloca nas variáveis h w h o tamanho do texto renderizado
	MESSAGESIZE *GetTextSize(const char *text);
    inline CFont *getFont() const{
		return (CFont *)_my_font;
	}
	//static CTTFFont &getFont( const string & name, const int x, const int y );
	//static CTTFFont &getDefaultFont();  //todo transformar em static
	TTF_Font *LoadFont(int fontnumber, int ftSize=12);
	TTF_Font *LoadFont(string fonte, int ftSize=12) throw(CLoadException);

	//==== RENDERING ====================================
	SDL_Surface * RenderUNICODE(const Uint16 *text, SDL_Color fg, SDL_Color bg);

	virtual void RenderToSurface(int x,int y, const CBitmap &dst,  Colors::ColorDefinition textColor, char *string) ;
	virtual void RenterToRenderer(int x, int y, int TargetWindow, SDL_Surface &text ,int ascent);

	SDL_Rect textoutf(CBitmap *TargetBitmap, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha ,const char *format,...);
	SDL_Rect textout_UTF8(CBitmap *TargetBitmap,  const char *string, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha);
	SDL_Rect textout_UTF8(CBitmap *TargetBitmap, const char *string, Sint16 x, Sint16 y, Uint32 fcolor, Uint32 bcolor, int Alpha);
	SDL_Rect textout_UNI(CBitmap *TargetBitmap, const Uint16 *uni, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha);
	SDL_Rect textout_UNI(CBitmap *TargetBitmap,  const Uint16 *uni, Sint16 x, Sint16 y, Uint32 fcolor, Uint32 bcolor, int Alpha);
	SDL_Rect textout(CBitmap *TargetBitmap,  const char *string, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha);
	SDL_Rect textout(CBitmap *TargetBitmap,  const char *string, Sint16 x, Sint16 y, Uint32 fcolor, Uint32 bcolor, int Alpha);

	SDL_Rect textout_UNI_Renderer(int TargetWindow, const Uint16 *uni, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB, int Alpha);


	//======================
	virtual void printF( int x, int y, int flags, int fg,const char* text );

	virtual void printfWrap( int x, int y, int color, const CBitmap & work, int maxWidth, const string & str, int marker, ... ) const;
	//using CFont::drawText;
	virtual void DrawTextNew(int x,int y,  Colors::ColorDefinition textColor,  CBitmap &work, const char *strText,...) ;
	virtual void drawToSurface( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... ) const;
	virtual void drawToTexture( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... ) const;
	virtual void drawToRenderer( int x, int y,  Colors::ColorDefinition color, const char *strText, int marker, ... ) const;
	virtual int	drawTextMSZ( const char* text,  int x, int y, int flags, int fg, CBitmap* target );
	//! draw ext to the renderer or surface depending on the Tgt Bitmap mode
	virtual void drawGradientText( const char* text,  int y, CBitmap* tgt);
	virtual int getType() const { return type; }

	//retorna o tmanho máximo que esta fonte pode atingir
	virtual int getMaxHeight() const;
	virtual int getWidth() const;
	virtual int getTextLength( const string & str ) const;
	virtual int getTextLength( const char * text ) const;
	virtual int getTextHeight( const string & str ) const;
    virtual int getTextHeight( const char * text ) const;
	virtual MESSAGESIZE getTextSize( const string & str ) const;
    virtual MESSAGESIZE getTextSize( const char * text ) const;
	MESSAGESIZE getTextSizeUNI(const Uint16 *text)const;
	//!return the size of the message until the a_iMaxLength position of the text
	MESSAGESIZE getTextSize(const char *text, int a_iMaxLength)const;

	//==================================================================================
	// Get font geometrics
	//==================================================================================
	//! Returns: The maximum pixel height of all glyphs in the font.
	int getHeight()const;
	//! Returns: The maximum pixel ascent of all glyphs in the font.
	/*
	Get the maximum pixel ascent of all glyphs of the loaded font.
	This can also be interpreted as the distance from the top of the font to the baseline. It could be used when drawing an individual glyph relative to a top point, by combining it with the glyph's maxy metric to resolve the top of the rectangle used when blitting the glyph on the screen.
	*/
	int getFontAscent()const;
	//! Returns: The maximum pixel descent of all glyphs in the font.
	/*
	Get the maximum pixel descent of all glyphs of the loaded font.
	This can also be interpreted as the distance from the baseline to the bottom of the font. It could be used when drawing an individual glyph relative to a bottom point, by combining it with the glyph's maxy metric to resolve the top of the rectangle used when blitting the glyph on the screen.
	*/
	int getFontDescent()const;
	//! Returns: The maximum pixel height of all glyphs in the font.
	//!The loaded font to get the line skip height of.
    //!Get the reccomended pixel height of a rendered line of text of the loaded font. This is usually larger than the TTF_FontHeight of the font.
    int getFontLineSkip()const;

	virtual void setSize( const int x, const int y );
	virtual int getSizeX() const;
	virtual int getSizeY() const;
	//Turns anti-aliasing for truetype output on/off. Defaults to ON. You can also enable alpha blending support (very nice but slow).
	void AAenable();
	void AAdisable();
	void AlphaRenderEnaable();
protected:
	void printfWrapLine(int x, int & y, int color, const CBitmap & work, int maxWidth, const char * line) const;
	void closeFont();
	string fontName;
	void releaseInternalFont();
	int sizeX;
	int sizeY;
    inline void setFont( TTF_Font * font ){
            if ( font == NULL ){
                //cout << "*FATAL* Setting null font" << endl;
            }
            _my_font = font;
        }

	TTF_Font * _my_font;
	fonttype type;
	RenderingMode TTF_AA;     //Rendering mode: 0-OFF, 1-AA, 2-Alpha
	style _my_style;
};

/**
 * \class CBitmapFont
 * \ingroup SGF_Util
 *
 * \brief Classe de Fontes tipo Bitmap
  * Detailed Description

* Bitmap font handling and effects.

* Print with bitmap fonts, including animated text effects.

* Bitmap fonts are wide PNG images having all characters in one row, split by a single pixel line of pink color (0xff00ff).

* If the font is called myfont.png, there has to be a file called myfont.png.map which lists the characters from the image, so if your image shows the characters SGE, then your map file should read 'SGE'

* Just have a look at the standard fonts to see how they are done.
*
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CBitmapFont :public CFont{
private:
typedef struct {
	int offset;
	int width;
} BITMAPFONTINFO;

/**
 * @struct SGEBITMAPFONT
 * @brief a bitmap font structure
 */
typedef struct {
	/** @privatesection */
	CBitmap *bitmap;
	string charmap;
	CDynamicArray<BITMAPFONTINFO *> info;
	map<int,CBitmap *> alphabet;
	int Chars;
} BITMAPFONT;

public:

	enum bitmaptype{
		SGF_type,
		FIXEDSIZE_type,
		SGE_type
	};

	 //CBitmapFont(int fontnumber, int ptsize=12);
	//CBitmapFont(const string, int ptsize=12);
	/**
 * @brief cria uma nova fonte de um arquivo
 * @param string o caminho da fonte
 * @param x a largura de cada caracter
 * @param y a altura de cada caracter
 */
	CBitmapFont(const string,bitmaptype =SGF_type);
    ~CBitmapFont();
	CFontList * AvailableFonts;

	//Needed Variables
    SDL_Surface *umessage;
    //The font
    //static CBitmapFont *CheckLoaded(int fontnumber);
	static CBitmapFont *CheckLoaded(string fonte);
	inline BITMAPFONT GetFont() const{
		return _my_font;
	}
	inline CFont * getFont() const{
		return (CFont *) this;
	}
	//static CBitmapFont &getFont( const string & name, const int x, const int y );
	//static CBitmapFont &getDefaultFont();  //todo transformar em static
	CBitmap * LoadFont(string fonte) throw(CLoadException)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     ;
	bool loadCharMap(string file);

	virtual void Render(char *string, const CBitmap &dst, int x,int y, Colors::ColorDefinition textColor) ;


	//! print to default render window
	//Todo
	virtual void printfWrap( int x, int y, int color, const CBitmap & work, int maxWidth, const string & str, int marker, ... ) const;

	//!draw the text to de Bitmap or texture, depending on BitmapMode
	//!work like printF
	virtual void drawText(int x,int y,  Colors::ColorDefinition textColor,  CBitmap &work, const char *strText,...) ;
	virtual void drawToSurface( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... )const ;
	virtual void drawToTexture( int x, int y,  Colors::ColorDefinition color, CBitmap & work, const char *strText, int marker, ... )const ;
	virtual void drawToRenderer( int x, int y,  Colors::ColorDefinition color, const char *strText, int marker, ... ) const;

	virtual int getHeight() const { return sizeY;};

	//retorna o tmanho máximo que esta fonte pode atingir
	virtual int getMaxHeight() const ;
	virtual int getWidth() const  { return sizeX;};
	virtual int getTextLength( const string & str ) const;
	virtual int getTextLength( const char * text ) const;
	virtual int getTextHeight( const string & str ) const;
    virtual int getTextHeight( const char * text ) const;
	//coloca nas variáveis h w h o tamanho do texto renderizado
	MESSAGESIZE getTextSize(const char *text)const;
    //!return the size of the message until the a_iMaxLength position of the text
	MESSAGESIZE getTextSize(const char *text, int a_iMaxLength)const;

	virtual void setSize( const int x, const int y ) { sizeX=x; sizeY=y;} ;
	virtual int getSizeX(void) const { return sizeX;} ;
	virtual int getSizeY(void) const { return sizeY;};
	virtual int getType() const { return type; };
	SDL_Surface *  printBitmap(const char *text);

protected:
	void printfWrapLine(int x, int & y, int color, const CBitmap & work, int maxWidth, const char * line) const;
	void closeFont();
	string fontName;
	void releaseInternalFont();
	int sizeX;
	int sizeY;
    inline void setFont( CBitmap * font ){
            if ( font == NULL ){
                //cout << "*FATAL* Setting null font" << endl;
            }
            _my_font.bitmap = font;
        }

	BITMAPFONT _my_font;
	fonttype type;
	bitmaptype _my_bitmaptype;
	//Temporário
	//sge_bmpFont* _my_sge_font;
};
} //end SGF
#endif
