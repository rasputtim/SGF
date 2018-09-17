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
#ifndef _S_G_F_bitmap_h_
#define _S_G_F_bitmap_h_

#include "../../ExternalLibs/SDL2/include/SDL.h"
#include <string>
#include <vector>
#include <iostream>
#include "../SGF_Config.h"
#include "../sprite/defs.h"
#include "SGF_Color.h"
#include "../gui/SGF_Coordinate.h"
#include "../gui/SGF_Rectarea.h"
#include "../util/SGF_UtilStructs.h"
#include "../util/SGF_Thread.h"

#define SCREENX_LIMIT 319
#define SCREENY_LIMIT 239
#define _PI 3.1415926
#define MAX_TEXTURES 10 //! pode armazenar até 10 texturas


using namespace std;
namespace SGF{
class CFont;
class CTranslucentBitmap;
class CPolygon;

typedef enum {
	USE_TEXTURE,
	USE_SURFACE,
	BOTH_TEXTURE_SURFACE,
	USE_GL_TEXTURE,
	USE_RENDERER,
} BitmapType;

/* thread safe Bitmap
http://www.justsoftwaresolutions.co.uk/threading/thread-safe-copy-constructors.html
*/


struct BitSurfaces{
public:
	BitSurfaces():
	_my_SDLSurface(NULL),
	_my_SDLTexture(NULL),
	_my_GLTexture(NULL),
	_my_gl_bitmap(NULL),
	own(NULL)
	{};
	BitSurfaces(const BitSurfaces & copy,bool deep_copy = false):
	_my_SDLSurface(copy._my_SDLSurface),
	_my_SDLTexture(copy._my_SDLTexture),
	_my_GLTexture(copy._my_GLTexture),
	_my_gl_bitmap(copy._my_gl_bitmap){
	if (deep_copy){
		own = new int;
		*own = 1;
	}else{
		own = copy.own;
		if ( own ){
			*own = *own + 1;
		}
	}
	};
	BitSurfaces & operator=(const BitSurfaces & copy){
	_my_SDLSurface=copy._my_SDLSurface;
	_my_SDLTexture=copy._my_SDLTexture;
	_my_GLTexture=copy._my_GLTexture;
	_my_gl_bitmap=copy._my_gl_bitmap;
	own = copy.own;
    if (own) *own += 1;

	return *this;
	}
	~BitSurfaces(){
		if( _my_gl_bitmap != NULL) {
			free (_my_gl_bitmap);
			_my_gl_bitmap=NULL;
		}
		releaseInternalBitmap();

	};
	void releaseInternalBitmap();
	void start() {
		own = new int;
		*own = 1;
	}
	//void addCopy() {
	//	if (own) *own += 1;
	//}
	SGF_INLINE SDL_Surface * getBitmap() const{
		return _my_SDLSurface;
	}
	SGF_INLINE SDL_Texture * GetTexture() const{
		return _my_SDLTexture;
	}
	SGF_INLINE void * GetGLTexture() const{
		return _my_GLTexture;
	}
	SGF_INLINE Uint8 * getGLBitmap() const{
		return _my_gl_bitmap;
	}
	SGF_INLINE void setBitmap( SDL_Surface * bitmap ){
            if ( bitmap == NULL ){
                cout << "*FATAL* Setting null bitmap" << endl;
            }
			_my_SDLSurface = bitmap;
        }
	SGF_INLINE void setTexture( SDL_Texture * texture ){
            if ( texture == NULL ){
				cout << "*FATAL* Setting null SDL Texture" << endl;
             //   Debug::debug(Debug::error,__FUNCTION__) << "*FATAL* Setting null bitmap" << endl;
			}else{
			_my_SDLTexture=texture;
			}
        }
	SGF_INLINE void setGLTexture( void * texture ){
            if ( texture == NULL ){
				cout << "*FATAL* Setting null GL Texture" << endl;
             //   Debug::debug(Debug::error,__FUNCTION__) << "*FATAL* Setting null bitmap" << endl;
			}else{
			_my_GLTexture=texture;
			}
        }

	 SGF_INLINE void SetGLBitmap( Uint8 * bitmap ){
            if ( bitmap == NULL ){
                cout << "*FATAL* Setting null GL bitmap" << endl;
            }
            _my_gl_bitmap = bitmap;
        }

	


private:
	SDL_Surface * _my_SDLSurface;
	SDL_Texture * _my_SDLTexture;
	void * _my_GLTexture;
	//! ponteiro para a textura interna da classe
	Uint8 * _my_gl_bitmap;
	//! indica se a classe é dona do bitmap interno
	int * own;
	
};
class CBitmap;

struct BaseCBitmap{
	BaseCBitmap()
	{};
	BaseCBitmap(const BaseCBitmap & copy, bool deep_copy):
		_my_bitmap(copy._my_bitmap, deep_copy)
	{};
	
//	BaseCBitmap(const CBitmap & copy):
//		_my_bitmap(copy._my_bitmap)
//	{};
	
	BaseCBitmap & operator=(BaseCBitmap & copy){
		_my_bitmap=copy._my_bitmap;
	};
	BitSurfaces _my_bitmap;
	

};

/**
 * \class CBitmap
 *
 * \ingroup SGF_Graphics
 *
 * \brief Controle de Bitmap, efeitos, drawing, blitting
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CBitmap: private BaseCBitmap {



public:

	/* equivalent to a GPU shader */
        class CFilter{
        public:
            virtual unsigned int filter(unsigned int pixel) const = 0;
            virtual ~CFilter(){
            }
        };

        static int SCALE_X;
        static int SCALE_Y;
	/** Este é o método inicial da Classe CBitmap
	* Antes de criar qualcrer Objeto CBitmap é necessário
	* iniciar o modo gráfico através deste método
	* \note é necessário inicializar o CBitmap para cada janela a ser utilizada
	* \note é utilizado pela classe CSDL_Manager após inicializar o SDL
	* \param state: estrutura que contém todos os parâmetros de inicialização
	* \param i: índice que indica a qual janela (SDL_Window) se refere esta inicialização
	*/
	static int init( SDLState_t *state ,int i=0);

	//=============CONSTRUCTORS==============================
	/* construtor padrão. cria um bitmap 10x10 */
	CBitmap( int window =0);
	CBitmap( int width, int height , int window=0); //usa como default a janela 0, ou Screen[0]
	CBitmap( const char * load_file, int window=0 );
	CBitmap( PCXDATA *image , int window=0);
	CBitmap( const string & load_file, int window=0 );
	CBitmap( const char * load_file, int sizex, int sizey , int window=0);
	//CBitmap( const char * load_file, int sizex, int sizey, double accuracy, int window=0 );
	CBitmap( const CBitmap & copy, bool deep_copy = false );
	CBitmap( const CBitmap & copy, int sizex, int sizey );
	/** \brief Cria um novo bitmap, copiando o retangulo com tamanho 0,0,sizex,sizey do Bitmap copy
	* \param copy: bitmap original do qual será copiado uma parte
	* \param sizex: tamanho horizontal em pixels do retângulo de cópia
	* \param sizey: tamanho vertical em pixels do retângulo de cópia
	* \param accuracy:
	*/
	// CBitmap( const CBitmap & copy, int sizex, int sizey, double accuracy );
	/** \brief Cria um novo bitmap, copiando o retangulo x,y,w,h do Bitmap copy
	* \param copy: bitmap original do qual será copiado uma parte
	* \param x: coordenada horizontal inicial do retângulo de cópia
	* \param y: coordenada vertical inicial do retângulo de cópia
	* \param width: largura do retângulo de cópia em pixels
	* \param height: altura do retângulo de cópia em pixels
	* \param bitmapTypeToCopy: tipo de cópia que deve ser feito (Só Surface, só textura ou ambos);
	*/
	CBitmap( const CBitmap & copy, int x, int y, int width, int height ,BitmapType bitmapTypeToCopy=BOTH_TEXTURE_SURFACE);

	//! Construtores de inicialização da tela
	explicit CBitmap( SDL_Surface * who, bool deep_copy = false,bool initconsole = false , int window=0);
	explicit CBitmap( SDL_Window * who, bool deep_copy = false,bool initconsole = false, int window=0 );
	static CBitmap memoryPCX(unsigned char * const data, const int length, const bool mask = true);
	        /* produce a temporary bitmap that is not guaranteed to be preserved
         * after your function returns. do *not* hold references to this bitmap
         * and if you make a temporary bitmap, do *not* call functions that
         * might also make temporary bitmaps.
         */
    static CBitmap temporaryBitmap(int w, int h);
	static CBitmap temporaryBitmap2(int w, int h);

        /* call this method to delete all temporary bitmaps.
         * don't call this unless you know what you are doing
         */
    static void cleanupTemporaryBitmaps();
	virtual ~CBitmap();

	//============  END CONSTRUCTORS===============================

	virtual CTranslucentBitmap translucent() const;
	virtual CTranslucentBitmap translucent(int red, int green, int blue, int alpha) const;
    //virtual CLitBitmap lit() const;

	virtual CPolygon polygon() const;
	virtual void save( const string & str );

	CBitmap & operator=( const CBitmap & );

	virtual void load( const string & str, int window=0 );
    /*
    const int getWidth() const;
	const int getHeight() const;
    */

	SGF_INLINE const int getWidth() const{
		return _my_width;
	}

	SGF_INLINE const int getHeight() const{
		return _my_height;
	}
	SGF_INLINE SDL_Surface * getBitmap() const{
		return _my_bitmap.getBitmap();
	}
	SGF_INLINE SDL_Texture * GetTexture() const{
		return _my_bitmap.GetTexture();
	}
	SGF_INLINE SDLState_t * GetState() const{
		return _my_state;
	}
	SGF_INLINE SDL_Window * GetWindow() const{
		return _my_state->windows[_my_renderWindow];
	}
	SGF_INLINE const SDL_BlendMode GetTextureDrawBlendMode() const{
		return _my_texture_draw_blend_mode;
	}
	SGF_INLINE const int getBitmapMode() const{
		return _my_actual_draw_type;
	}

	SGF_INLINE SDL_Renderer * getMyRender() const {
		return _my_state->renderers[_my_renderWindow];
	}
	//! Return the Renderer used on the especified window
	static SDL_Renderer * getMyRenderer(int RenderWindow) {
		return _my_state->renderers[RenderWindow];
	}
	SGF_INLINE const int getMyRenderWindow() const {
		return _my_renderWindow;
	}
	SGF_INLINE const string & getPath() const{
		return path;
	}

	/*
	inline const int getWidth() const{
		return my_bitmap->w;
	}

	inline const int getHeight() const{
		return my_bitmap->h;
	}
	*/

	//====================SDL Surface Methods======================
private:

	SDL_Surface* CreateSurface(int x,int y); //copiada do videosystem
	SDL_Surface* load_image( string filename );
	SDL_Surface* load_image( const char *  filename );
	SDL_Surface* load_image( BYTE * file, int size ); //used to load PCX Byte sprites
	//! estimate num of segments used to draw circle and arc in openGL
public:
    SDL_Surface* RotatePicture (int rotate, int flip, int smooth); // Nao testei não lembro pra que serve
	SDL_Surface* RotateSurface( double angle, double zoomx=1, double zoomy=1 );
	SDL_Surface* SDL_ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height)const;
	void convertpixelFormat(); //! convert surface to the current pixel format
	void rotateFromBitmap(double angle, double zoomx=1, double zoomy=1 );
    /* resize the internal Surface. not guaranteed to destroy the internal Surface */
	void resize( const int width, const int height );

    //======END SURFACE METHODS============
	//! release the internal Bitmap
	void detach();

	//=================SDL TEXTURE  METHODS================
	void updateTexture()const;
	SDL_Texture * CreateTextureFromBitmap(int renderWindow=0);
	//! Cria uma nova textura À partiir da Surface atual do Bitmap
	SDL_Texture * copyTextureFromSurface();
	//! Cria uma nova textura À partiir da textura atual do Bitmap
	//! nao esquecer que deve deleter a textura com SDL_DestroyTexture(SDL_Texture* texture) depois de utilizála
	SDL_Texture * copyTextureFromTexture();
	//! copia a txtura do bitmap atual à partir da Textura do Bitmap passado como parâmetro
	void copyTextureFromBitmap(CBitmap &origem);
	SDL_Texture * createTextureStreaming(int x, int y, int renderWindow=0);
	//! retorna o mode de acesso da textura
	/*
	SDL_TEXTUREACCESS_STATIC  - changes rarely, not lockable
	SDL_TEXTUREACCESS_STREAMING - changes frequently, lockable
	SDL_TEXTUREACCESS_TARGET - can be used as a render target
	*/
	int getTextureAccessMode(); 
	//! retorna treu se o modo de acesso da textura é estático
	bool isTextureStatic();
	//! retorna treu se o modo de acesso da textura é streaming
	bool isTextureStreaming();
	//! retorna treu se o modo de acesso da textura é Target
	bool isTextureTarget();
	//=============================================================


	// BLENDING METHODS===========================
	//Modos de blending dos métodos de rendering do SDL 2.0
	static const SDL_BlendMode MODE_TRANS;
	static const SDL_BlendMode MODE_SOLID;
	static const SDL_BlendMode MODE_ADD;
	static const SDL_BlendMode MODE_MOD;
	//Use this function to set the blend mode for a texture, used by SDL_RenderCopy().
	int SetBlendMode(SDL_BlendMode blendmode) const;
    //Use this function to set the blend mode used for drawing operations (Fill and Line).
	//Todo: mover este método para a classe polygon
	void setDrawBlendMode( SDL_BlendMode type ) const;

	// Modos de blending próprios do SGF

	 /* alphaBlender:  Blend between source pixel and destination pixel.
         * Source and dest should be 0-255.
         *source = 64, dest = 128
         * pixel = source_pixel * source / 255 + dest_pixel * dest / 255
         */ 
	static void alphaBlender(int source, int dest);
	static void transBlender( int r, int g, int b, int a );
	static void multiplyBlender( int r, int g, int b, int a );
	static void dissolveBlender( int r, int g, int b, int a );
	static void addBlender( int r, int g, int b, int a );
	static void burnBlender( int r, int g, int b, int a );
	static void colorBlender( int r, int g, int b, int a );
	static void differenceBlender( int r, int g, int b, int a );
	static void dodgeBlender( int r, int g, int b, int a );
	static void hueBlender( int r, int g, int b, int a );
	static void luminanceBlender( int r, int g, int b, int a );
	static void invertBlender( int r, int g, int b, int a );
	static void screenBlender( int r, int g, int b, int a );


	//================LOCK METHODS==============
	void acquire();
	void locksurface();
	void release();
    void unlocksurface();
	//=======END LOCK METHODS==============

    /** converte o bitmap para uma versão en escala de cinza
	*/
    virtual CBitmap greyScale();
 	
	//TODO: métodos que aplicam colorkey diretamente na textura? será necessário?
	//==Métodos de Transparência de Colorkey====
	//  Voce determina uma cor do bitmap que será totalmente transparente
	/** \brief usa a cor do pixel 0,0 como transparência
	* \note aplica a transparência na surface e depois atualiza a textura */
	virtual void applyTrans();
    /** \brief usa cor padrão (255,0,255) como transparência
	* \note aplica a transparência na surface e depois atualiza a textura */
	virtual void applyDefTrans();
    /** \brief  usa cor color como transparência
		* \note aplica a transparência na surface e depois atualiza a textura */
	virtual void applyTrans(int color);
	
	/** \brief inicializa qual a cor da máscara num bitmap que foi criado a partir de uma imagem PCX
	* \param color: definição da cor que representa a mascara (keycolor)
	*/
	int SetAlphaMod(int alpha);

	void setPCXMaskColor(Colors::ColorDefinition color);

	/** \brief método que informa qual a cor da máscara de um bitmap criado à partir de um PCX
	*\ return um inteiro que representa o pixel da cor de máscara no formato do display
	*/
	unsigned int getPCXMaskColor() const;

	/** \brief método que informa qual a cor da máscara padrão
	*\ return um inteiro que representa o pixel da cor de máscara no formato do display
	*/
	static  int getDefaultColorkey();


	//===Methods de transparência alpha
	virtual void applyAlphaTrans(const int alpha); //!usa o valor de alpha como transparência para a surface ou textura como um todo



	virtual void border( int min, int max, int color ) const;

	//=========PIXEL METHODS======================

	/** \brief Retorna um Vetor com as coordenadas (x,Y) de cada um dos pixels de uma determinada cor
	* \param original: pixel representando a cor a ser procurada no bitmap
	* \note: funciona com bitmap , não textura ainda
	*/
	vector<Gui::CAbsolutePoint> getPixelsCoord(Colors::PixelColor mask);
	/** \brief Retorna um Vetor com as coordenadas (x,Y) de cada um dos pixels que não são de uma determinada cor
	* \param original: pixel representando a cor a ser procurada no bitmap
	* \note: funciona com bitmap , não textura ainda
	*/
	vector<Gui::CAbsolutePoint> getPixelsCoordInverted(Colors::PixelColor mask);
	/** \brief troca os pixels de um Bitmap
	* \param original: pixel representando a cor de origem, que será trocada
	* \param replaced: pixel representando a nova cor, que será súbstituirá o original
	*/
	
	virtual void replaceColor(int original, int replaced);
	virtual void readLine( vector< int > & vec, int y );

    Uint32	getPixelSurface(int x, int y) const;
	void putPixelSurface( int x, int y, Uint32 pixel, bool translucent=false ) const;
	void putPixelSurface( int x, int y, Uint8 r, Uint8 g, Uint8 b) const;
    void putPixelTexture( int x, int y, Uint32 pixel, bool translucent=false ) const;
	void putPixelTexture( int x, int y, Uint8 r, Uint8 g, Uint8 b) const;
    /* respects the current trans mode */
	void putPixelNormal(int x, int y, int pixel) const; //not used anymore
	
	/** \brief método que informa qual o valor do pixel que representa a cor rgb (no formato do display)
	* \param r: quantidade de vermelho
	* \param g: quantidade de verde
	* \param b: quantidade de azul
	* \return um inteiro que representa o pixel da cor RGB no formato do display
	*/
	static  int makeColor(int r, int g, int b);
	static  Colors::ColorDefinition makeSDLColor( int r, int g, int b );
	Colors::ColorDefinition getColor(Uint32 pixel);

	//================DRAW METHODS========================================
	// Métodos que atuam diretamente nos pixels das imagens usanso acesso direto aos pixels via SGF
    
	//virtual void draw(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, const CBitmap & where) const;
	virtual void draw(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, CFilter * filter, const CBitmap & where) const;
	virtual void draw(const int x, const int y, CFilter * filter, const CBitmap & where) const;
	
	/* flip horizontally */
	virtual void drawHFlip(const int x, const int y, CFilter * filter, const CBitmap & where) const;
	virtual void drawHFlip(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, CFilter * filter, const CBitmap & where) const;

	/* flip vertically */
	virtual void drawVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const;

    /* flip horizontal and vertical */
	virtual void drawHVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const;

	//! método não usado ainda, acho que está com bug
	virtual void drawMaskSurface( const int x, const int y, const CBitmap & where );

	virtual void drawStretched( const int x, const int y, const int new_width, const int new_height, const CBitmap & who )const;
	virtual void drawStretched(const CBitmap & who) const;
	virtual void drawRotate( const int x, const int y, const int angle, const CBitmap & where );
	virtual void drawPivot( const int centerX, const int centerY, const int x, const int y, const int angle, const CBitmap & where );
	virtual void drawPivot( const int centerX, const int centerY, const int x, const int y, const int angle, const double scale, const CBitmap & where );
    virtual void Draw();
	virtual void Stretch( const CBitmap & where ) const;
	virtual void Stretch( const CBitmap & where, const int sourceX, const int sourceY, const int sourceWidth, const int sourceHeight, const int destX, const int destY, const int destWidth, const int destHeight ) const;
	virtual void StretchBy2( const CBitmap & where );
	virtual void StretchBy4( const CBitmap & where );

	static void draw_sprite_ex32(SDL_Surface * dst, SDL_Surface * src, int dx, int dy, int mode, int flip, CBitmap::CFilter * filter, unsigned int maskcolor);
	static void draw_sprite_ex32(SDL_Texture * dst, SDL_Surface * src, int dx, int dy, int mode, int flip, CBitmap::CFilter * filter, unsigned int maskcolor);
	
	static void replace16(SDL_Surface * dst, const int original, const int replace);
	static void replace32(SDL_Surface * dst, const int original, const int replace);
	
	//não utilizados, precisa revisá-los e testá-los
	static void draw_sprite_filter_ex16(SDL_Surface * dst, SDL_Surface * src, int x, int y, const CBitmap::CFilter & filter);
	/* caso especial para desenhar um luz light (como numa lampada).
	 * \note o centro da luz é  x,y
	 * \note brilha num triângulo isosceles perfeito.
	 */
	static void light16(SDL_Surface * dst, const int x, const int y, int width, int height, const int start_y, const int focus_alpha, const int edge_alpha, const int focus_color, const int edge_color);


	//=================BLIT METHODS=====================

	/** atualiza o renderer com o conteudo da Textura
     * \note  atualiza na posição 0,0
    */
	virtual void Blit() const;
	/** atualiza o renderer com o conteudo da Textura
    * \note  atualiza na posição x,y
    * \param x: coordenada x do ponto de início
	* \param y: coordenada y do ponto de início
    */
	virtual void Blit(int x, int y) const;

	/** atualiza o renderer com o conteudo da Textura
    * \note  atualiza na posição DestX,DestX
    * \param DestX: coordenada x do ponto destino
	* \param DestY: coordenada y do ponto destino 
	* \param DestW = -1 significa usar o bitmap inteiro 
    * \param DestH = -1 significa usar o bitmap inteiro 
    */
	virtual void Blit( const int OrigX, const int OrigY, const int width, const int height, const int Destx, const int Desty,int DestW=-1, int DestH=-1) const;


	/** atualiza o default renderer com o conteúdo da textura,
    * alongando a mesma até o tamanho da janela
	* \note blita na posição 0,0
	*/
	virtual void BlitStretched() const;
	/** atualiza o default renderer com o conteúdo da textura,
    * alongando a mesma até o tamanho da janela
    * \param x: coordenada x do ponto de início
	* \param y: coordenada y do ponto de início
	*/
	virtual void BlitStretched(int x, int y)const ;
	/** atualiza a janela com o conteúdo do renderer
	*/
	virtual void BlitToScreen() const;
	static void BlitRenderToScreen(int window);
	/** atualiza a janela com o conteúdo da surface
	* \note só funciona no modo SDL 1.2
	*/
	//virtual void BlitToScreen(const int upper_left_x, const int upper_left_y) const;

	// métodos de draw que utilizam o Blit do SDL
	
	//==== Blit the surface to another CBitmap
	//!copia a surface do Bitmap Atual para a Surface do bitmap Destino
	virtual void BlitSurface( const CBitmap & where ) const;
	//!copia a surface do Bitmap Atual para a Surface do bitmap Destino
	virtual void BlitSurface( const int x, const int y, const CBitmap & where ) const;
	//!copia a surface do Bitmap Atual para a Surface do bitmap Destino
	virtual void BlitSurface( const int SrcX, const int SrcY, const int Dstx, const int DstY, const CBitmap & where ) const;
	//!copia a surface do Bitmap Atual para a Surface do bitmap Destino
	virtual void BlitSurface( const int SrcX, const int SrcY, const int width, const int height, const int DstX, const int DstY, const CBitmap & where ) const;
	
	//!==== Blit the Surface to the Default Renderer
	virtual void BlitSurface( const int SrcX, const int SrcY, const int width, const int height, const int DstX, const int DstY) const;
	virtual void BlitSurface() const;
	//!==== Blit the Surface to the Default Renderer and to the Screen
	virtual void BlitSurfaceToScreen( const int SrcX, const int SrcY, const int width, const int height) const;
	virtual void BlitSurfaceToScreen( const int SrcX, const int SrcY, const int width, const int height, const int DstX, const int DstY) const;

	virtual void Blit( const string & xpath ) const;
								
	virtual void BlitMasked( const int sourceX1, const int sourceY, const int sourceWidth, const int sourceHeight, const int destX, const int destY, const CBitmap & where ) const;
	/** atualiza a textura com o trabalho feito na Surface, depois atuializa o render e depois coloca na janela
    * alongando a mesma até o tamanho da janela
    * \param x: coordenada x do ponto de início
	* \param y: coordenada y do ponto de início
	*/
	virtual void BlitSurfaceToScreen( bool stretched=false);
	virtual void BlitAreaToScreen(const int upper_left_x, const int upper_left_y) const;
	virtual void BlitFromScreen(const int x, const int y) const;


	// =================métodos de preenchimento

	virtual void fill(Uint8 r, Uint8 g, Uint8 b,Uint8 a=255 ) const;
	virtual void fill(Uint32 pixel ) const;
	virtual void fill( Colors::ColorDefinition color, Uint8 a=255 ) const;

	virtual void fill(int x, int y, int w, int h, int pixel);
	
	virtual void fill_all_screen( Uint8 r, Uint8 g, Uint8 b,Uint8 a=255 ) const;

	SGF_INLINE void clear() const{
		this->fill( 0,0,0 );
	}
	SGF_INLINE void clear_all_screen() const{
		this->fill_all_screen( 0,0,0 );
	}
    SGF_INLINE void clearToMask() const{
		this->fill(getDefaultColorkey());
	}


	//===============TEXT and  FONT METHODS=====================
	//! Render the string to this surface or texture depending on the bitmapmode
	virtual void Render(char *string,int x,int y, Colors::ColorDefinition textColor, CFont *fonte) const;  //!render SDL_ttf text to dst surface
	
	//! escolhe a cor padrão para o render
	void SetDefColor(int R, int G, int B, int A);
	//===========ERROR================
	//ainda não defini como será o tratamento de erros.
	bool getError();
	bool getError() const;
	
	//!Display debug information to the debug file
	void debugSelf() const;

	
	//Tanto para surface quanto para textura, dependendo do modo
	void setClipRect( int x1, int y1, int x2, int y2 ) const;
	void getClipRect( int& x1, int &y1, int& x2, int& y2 ) const;





    static double getScale();


	void SetFullScreen();
	void SetWindowed();
	void SetWindowMode(int w, int h);
	//static int setGfxModeText();
	static int setGfxModeFullscreen( int x, int y );
	static int setGfxModeWindowed( int x, int y );





	// Bitmap Modes for CBitmap
	//! indicate if it will work on texture, surface, both...
	static const BitmapType DRAW_TYPE_TEXTURE;
	static const BitmapType DRAW_TYPE_SURFACE;
	static const BitmapType DRAW_TYPE_TEX_SURF;
	static const BitmapType DRAW_TYPE_GL;
	static const BitmapType DRAW_TYPE_RENDERER;
	static BitmapType DRAW_TYPE_DEFAULT;

	//! Modes Of Work
	//! Work with texture, bitmap, both direct to the render
	SGF_INLINE void useTexture() { _my_actual_draw_type= USE_TEXTURE; };
	SGF_INLINE void useSurface(){ _my_actual_draw_type=USE_SURFACE; };
	SGF_INLINE void useRenderer(){ _my_actual_draw_type=USE_RENDERER; };
	SGF_INLINE void useGLTexture(){ _my_actual_draw_type=USE_GL_TEXTURE; };
	SGF_INLINE void useTexture()const { _my_actual_draw_type= USE_TEXTURE; };
	SGF_INLINE void useSurface()const { _my_actual_draw_type=USE_SURFACE; };
	SGF_INLINE void useRenderer()const{ _my_actual_draw_type=USE_RENDERER; };
	SGF_INLINE void useGLTexture()const{ _my_actual_draw_type=USE_GL_TEXTURE; };
	

	
	void setBitmapMode( BitmapType mode )const;

	// these are used on drw methods
	enum DrawMethod{
	SPRITE_NO_FLIP=0x1,
	SPRITE_V_FLIP=0x2,
	SPRITE_H_FLIP=0x4,
	SPRITE_NORMAL=0x8,
	SPRITE_LIT=0x10,
	SPRITE_TRANS=0x20,
	};
	// importadas do CvideoSystem // very old methods i think i do not use them anymore
    //funções obsoletas do openmugen original: evitar usar
    void DrawRect16(Sint16 x,Sint16 y,Sint16 w,Sint16 h,Uint8 R,Uint8 G,Uint8 B);
    void DrawRect32(Sint32 x,Sint32 y,Sint32 w,Sint32 h,Uint8 R,Uint8 G,Uint8 B);
    void DrawText(int x,int y,char *strText,...);
    void FilterImage();
    
	/** converte uma imgem para o formato surface do SDL
	* \note não utilizado mais. foi substituido pelo SDL_ConvertSurface
	*/
	SDL_Surface* ConvertImageToSDL(BYTE *byImageData,Colors::ColorDefinition* ColorPallet);
	/** converte uma imgem para o formato surface do SDL
	* \note não utilizado mais. foi substituido pelo SDL_ConvertSurface
	*/
	SDL_Surface* ConvertImageToSDL32(BYTE *byImageData,Colors::ColorDefinition* ColorPallet);
    CBitmap *ConvetToDysplayFormat();

	//OpenGL
	//! Desenha a superfície OpenGL
	void DrawGLScene();  // Draw GL
	void DrawGLCube(int texturenum, float size=2.0, float xcenter=0.0,float ycenter=0.0,float zcenter=0.0,float rotate_x=0.0,float xspeed=0.0, float rotate_y=0.0, float yspeed=0.0,float rotate_z=0.0, float zspeed=0.0, float z=-0.5);
	void DrawGLTexture(int texturenum,float rotate_x=0.0,float xspeed=0.0, float rotate_y=0.0, float yspeed=0.0,float rotate_z=0.0, float zspeed=0.0, float z=-0.5);

	//! Coloca a superfície openGL na tela
	void BlitGLToScreen(); // Blit GLTexture to Screen
	//! Retorna o bitmap interno do objeto criado
	int CreateGLTexture();
	// convert bitmap to GL format
	int ConvertToTexture();
	//! retorna a textura OpenGL referente ao CBitmap da Classe
	SGF_INLINE Uint8 * GetGLBitmap() const {
		return _my_bitmap.getGLBitmap();
	}

	//========OPENGL METHODS - used on the OPEN GL Mode of the CBitmap CLass
	
	void ClearGL()const;
	void Switch2D();
    void Switch3D();
	void Triangle(const float x1, const float y1, const float x2, const float y2,const float x3,const float y3, int R=255, const int G=255, const int B=255); // Draw Colored Triangle
    void TriangleFill(const float x1, const float y1, const float x2, const float y2,const float x3,const float y3,const int R=255, const int G=255, const int B=255, bool rotate=0,float angle=0.0); // Draw Colored Triangle
    
	//!Desenha um Quadrado azul
    void Box(const float x1, const float y1,const float x2, float y2, const int R=255, const int G=255, const int B=255,bool rotate=0,float angle=0.0); //Draw a Blue Box
	void BoxFill(const float x1,const float y1,const float x2, float y2, const int R=255, const int G=255, const int B=255, bool rotate=0,float angle=0.0); //Draw a Blue Box
	void BoxTex(int filter, const float x1, const float y1,const float x2, float y2, const int R=255, const int G=255, const int B=255,bool rotate=0,float angle=0.0); //Draw a Blue Box
	void GL_Line(const float x1=0.0,const float y1=0.0,const float x2=0.0,const float y2=0.0, const int R=255, const int G=255, const int B=255, const float z1=0.0,const float z2=0.0);
	void Point(const float x=0.0,const float y=0.0,const int R=255, const int G=255, const int B=255, const float z=0.0);
    //!Desenha um Circulo
    void CircleFill(const float x,const float y,const float radius,const int R=255, const int G=255, const int B=255,bool rotate=0,float angle=0.0); //Draw a Blue Circle
    void Circle(const float x,const float y,const float radius,const int R=255, const int G=255, const int B=255,bool rotate=0,float angle=0.0); //Draw a  Circle
	//void Arc(const float x, const float y, const float ang1, const float ang2, const float radius/*, const Uint32 pixel, Uint8 A=255*/ ) const;
    void Arc(const float x, const float y, const float startAngle, const float endAngle, const float radius, const int R=255,const int G=255,const int B=255/*, Uint8 A=255*/ ) const;
	void ArcFill(const float x, const float y, const float startAngle, const float endAngle, const float radius, const int R=255,const int G=255,const int B=255/*, Uint8 A=255*/ ) const;
	void Star(const float x, const float y, const float ang1, const float ang2, const float radius/*, const Uint32 pixel, Uint8 A=255*/ ) const;
    void SetLineWidth(float width=1);
    //! inicializa light no OpenGL
	void SetGLLight();
    //! Determina como a iluminação será usada
    void SetGLLightAmbient(float a,float b,float c,float d); /* white ambient light at half intensity (rgba) */
	void SetGLLightDiffuse(float a,float b,float c,float d);  /* super bright, full intensity diffuse light. */
	void SetGLLightPosition(float x,float y,float z,float p);  /* position of light (x, y, z, (position of light)) */
    void EnGLLight();
	void DisGLLight();
	//! inicializa o blending
	void SetGLBlending();
	//! Habilita o Blend para este bitmap
    void EnGLBlending();
    //! Habilita o Blend para este bitmap
    void DisGLBlending();
   

	static SDLState_t * _my_state;
protected:

	//Util::Thread::LockObject bitmapLock;
	float GetNumCircleSegments(float radius) const;
	void fillSurface( Uint32 pixel) const;  //! preenche apenas a surface
	void fillTexture( Uint8 r, Uint8 g, Uint8 b, Uint8 a) const; //!preenche apenas a Textura


	// Text methods
	void RenderToTexture(char *string,int x,int y, Colors::ColorDefinition textColor, CFont *fonte) const;  //!render SDL_ttf text to dst surface
	void RenderToSurface(char *string,int x,int y, Colors::ColorDefinition textColor, CFont *fonte) const;

	//Clip Rect Methods
	void setSurfaceClipRect( int x1, int y1, int x2, int y2 ) const;
	void setTextureClipRect( int x1, int y1, int x2, int y2 ) const;
	
	void getSurfaceClipRect(int & x1, int & y1, int & x2, int & y2) const;
	void getTextureClipRect(int & x1, int & y1, int & x2, int & y2) const;

	
	mutable RectArea ClipRectText;  //!usado para delimitar o retângulo nas operações com textura
    

    SGF_INLINE void setBitmap( SDL_Surface * bitmap ){
            _my_bitmap.setBitmap(bitmap);
        }
	SGF_INLINE void setTexture( SDL_Texture * texture ){
            
			_my_bitmap.setTexture(texture);
			
        }
    SGF_INLINE void SetGLBitmap( Uint8 * bitmap ){
		this->_my_bitmap.SetGLBitmap(bitmap);
        }


	void internalLoadFile( const char * load_file, int window );


	//! converte coordenada do eixo X 2D para 3D
	float ConvertXto3D(int x);
	//! converte coordenada do eixo Y 2D para 3D
	float ConvertYto3D(int y);
	//! converte coordenada do eixo X 2D para 3D
	float ConvertXto3D(float x);
	//! converte coordenada do eixo Y 2D para 3D
	float ConvertYto3D(float y);
	//! converte coordenada do eixo X 3D para 2D
	float ConvertXto2D(float x);
	//! converte coordenada do eixo Y 3D para 2D
	float ConvertYto2D(float y);
	//! determina a textura interno do objeto

	//!inicialização do OpenGL
	void InitGL(int width, int height);  // GL Functions
	static CBitmap * temporary_bitmap;
	static CBitmap * temporary_bitmap2;


	//! indica se ocorreu algum erro
	mutable bool error;
	// indica se o modo 3d está habilitado
	bool GL3D;
	// indica se o modo 2D está habilitado
	bool GL2D;
	//! caminho da imagem
	string path;
	//! armazenamento para uma textura
    int texture[MAX_TEXTURES]; /* storage for one texture  */
    //!Armazenamento de um GL CBitmapt
	//void *raw;
	//! indica se o openGl está habilitado ou não
	static bool GLenabled;
  //======================  SDL 2

	//! define janela padrão de renderização
	int _my_renderWindow;
	
	mutable SDL_BlendMode _my_texture_draw_blend_mode; // set the blend mode for a texture, used by SDL_RenderCopy().
	mutable BitmapType _my_actual_draw_type;  //determina o type de drawing a usar (textura, surface, GL, etc)
	mutable BitmapType _my_default_draw_type;
	int _my_width,_my_height;
	bool createdFromPCX; //!indica que este bitmap foi criado através de uma imagem pcx
	//! se foi criado de um PCX, indica qual a cor da mascara, senão indica a cor de máscara padrão (255,0,255)
     Colors::ColorDefinition bitPCXMaskColor;

	friend class CTranslucentBitmap;
	
	//BitSurfaces _my_bitmap;
    
};


} //end namespace SGF
#endif
