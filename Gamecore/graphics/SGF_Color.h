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
#ifndef _S_G_F_COLOR_LIB_H_
#define _S_G_F_COLOR_LIB_H_

#include <assert.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"


#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))
#define MID(x,y,z)   MAX((x), MIN((y), (z)))
#define TT(x, y, n)   (((y) - (x)) * (n) / 255 + (x))

using namespace std;
namespace SGF {
	class CBitmap;
namespace Colors {
extern SDL_PixelFormat * Pformat;
extern int _color_depth;
extern bool sdlCompatibility;

/** \brief indica qual o modo de compatibilidade utilizado pelo SDL
* \return true: se o modo de compatibilidade com sdl 1.2 estiver habilitado
* \return false: se o modo de compatibilidade estiver desabilitado
* \note se o CSDLManager não estiver sido inicializado, cria uma instância do mesmo
*/
bool getCompatibilityMode();
SDL_PixelFormat * getCurrentPixelFormat();
void convertpixelFormat(CBitmap *bitmap);
void init_colors ();
void destroy_colors();
Uint32 makeColor( int r, int g, int b );
typedef unsigned int (*blender)(unsigned int pixel_color1, unsigned int pixel_color2, unsigned int alpha);


			 /**
			 * Corresponde a uma definição de cor de pixel
 			 * que é codificada num formato específico de pixel
			 *
			 */
			typedef Uint32 PixelColor ;



			/**
			 * Corresponds to a bit mask which allows to define how to
			 * get color coordinates from a PixelColor, for example
			 * depending on the endianness of the system.
			 *
			 */
			typedef Uint32 ColorMask ;



			/**
			 * Descreve uma coordenada utilizada no espaço das cores, inclusive alpha
			 *
			 */
			typedef Uint8 ColorElement ;



			/**
			 * A coordenada Alpha que corresponde à um pixel transparente
			 * @note é o reverso do openGL.
			 *
			 */
			const ColorElement AlphaTransparent = 0 ;



			/**
			 * A coordenada Alpha que corresponde à um pixel opaco (solido)
			 * pixels.
			 *
			 * @note é o reverso do openGL.
			 *
			 */
			const ColorElement AlphaOpaque = 255 ;



			/**
			 * Descreve uma coordenada de ponto flutuante utilizada no espaço das cores
			 * incluindo alpha.
			 *
			 * @note estas coordenadas, são muito uteis noOpenGL, são esperadas
			 * de variar num range entre zero e intensidade máxima, em [0,1].
			 *
			 */
			typedef Float32 FloatColorElement ;
			
			/**
			 * Descreve uma definição de cor não convertida para nenhum formato
			 * \note extende a definição do SDL_Color
			 */
			//typedef ::SDL_Color ColorDefinition ;
			typedef struct ColorDefinition {
			public:
				
			const ColorDefinition & operator=(const ColorDefinition &copy){
				if (&copy==this) return *this;
				this->r= copy.r;
				this->g= copy.g;
				this->b= copy.b;
				this->a= copy.a;
				return *this;
			};

			//!não leva em consideração o alpha da cor, ou seja a mesma cor com diferentes alphas é a mesma cor

			bool operator==(const ColorDefinition & who) const{
				return ((this->r==who.r) && (this->g==who.g) && (this->b == who.b));
			};

			SDL_Color toSDL() {
				SDL_Color newColor;
				newColor.r=this->r;
				newColor.g=this->g;
				newColor.b=this->b;
				return newColor;
			 };

			public:
				Uint8 r;
				Uint8 g;
				Uint8 b;
				Uint8 a;
			}ColorDefinition;
Uint32 makeColor( ColorDefinition color );

void blend_palette(  Colors::ColorDefinition * pal, int mp,  Colors::ColorDefinition sc,  Colors::ColorDefinition ec );

static SGF_INLINE unsigned int noBlender(unsigned int a, unsigned int b, unsigned int c){
    return a;
}
/* taken from allegro 4.2: src/colblend.c, _blender_trans16 */
//x=source pixel
//y=dest pixel
//n=alpha

/* taken from allegro 4.2: src/colblend.c, _blender_trans16 */
/* this function performs a psuedo-SIMD operation on the pixel
 * components in RGB 5-6-5 format. To get this to work for some
 * other format probably all that needs to happen is to change
 * the 0x7E0F81F constant to something else. 5-5-5:
 * binary: 0011 1110 000 0111 1100 0001 1111
 * hex:    0x174076037
 */
static SGF_INLINE unsigned int transBlender(unsigned int x, unsigned int y, unsigned int n){
    unsigned long result,g;

	int mode=Colors::Pformat->BitsPerPixel;//CSDLManager::GetInstance()->state->surface_format.BitsPerPixel;
	//Debug::debug(Debug::resources,__FUNCTION__) << "Mode1(_color_depth): " << _color_depth << "state=> BitsPerPixel: " << mode <<endl;
	switch(mode) {
	 case 15:
		 if (n)
		n = (n + 1) / 8;
		x = ((x & 0xFFFF) | (x << 16)) & 0x3E07C1F;
		y = ((y & 0xFFFF) | (y << 16)) & 0x3E07C1F;
		result = ((x - y) * n / 32 + y) & 0x3E07C1F;
		return ((result & 0xFFFF) | (result >> 16));
	 case 16:
		if (n)
        n = (n + 1) / 8;

		x = ((x & 0xFFFF) | (x << 16)) & 0x7E0F81F;
		y = ((y & 0xFFFF) | (y << 16)) & 0x7E0F81F;

		result = ((x - y) * n / 32 + y) & 0x7E0F81F;

		return ((result & 0xFFFF) | (result >> 16));
		break;
     case 32:

		if (n)
		n++;

		result = ((x & 0xFF00FF) - (y & 0xFF00FF)) * n / 256 + y;
		y &= 0xFF00;
		x &= 0xFF00;
		g = (x - y) * n / 256 + y;

		result &= 0xFF00FF;
		g &= 0xFF00;

		return result | g;
		break;
	}
}
//x=source pixel
//y=dest pixel
//n=alpha

static SGF_INLINE  unsigned int alphaBlender(unsigned int x, unsigned int y, unsigned int n){
    Uint8 source = n >> 8;
    Uint8 dest = n & 0xff;

    /*
    unsigned long result;

    x = ((x & 0xFFFF) | (x << 16)) & 0x7E0F81F;
    y = ((y & 0xFFFF) | (y << 16)) & 0x7E0F81F;

    result = ((x * source / 255) + (y * dest / 255)) & 0x7E0F81F;

    return ((result & 0xFFFF) | (result >> 16));
    */
	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

    int r = (redY * dest + redX * source) / 256;
    int g = (greenY * dest + greenX * source) / 256;
    int b = (blueY * dest + blueX * source) / 256;

    r = MIN(r, 255);
    g = MIN(g, 255);
    b = MIN(b, 255);

    // return transBlender(makeColor(r, g, b), y, dest);

    return Colors::makeColor(r, g, b);
    // return y;
}

static SGF_INLINE unsigned int multiplyBlender(unsigned int x, unsigned int y, unsigned int n){

	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
	SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

    int r = redX * redY / 256;
    int g = greenX * greenY / 256;
    int b = blueX * blueY / 256;
    return transBlender(makeColor(r, g, b), y, n);
}
//x=source pixel
//y=dest pixel
//n=alpha

static SGF_INLINE unsigned int addBlender(unsigned int x, unsigned int y, unsigned int n){
    Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
	SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

    int r = redY + redX * n / 256;
    int g = greenY + greenX * n / 256;
    int b = blueY + blueX * n / 256;

    r = MIN(r, 255);
    g = MIN(g, 255);
    b = MIN(b, 255);

    return makeColor(r, g, b);
}

static SGF_INLINE int iabs(int x){
    return x < 0 ? -x : x;
}
//x=source pixel
//y=dest pixel
//n=alpha

static SGF_INLINE unsigned int differenceBlender(unsigned int x, unsigned int y, unsigned int n){

	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x,Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y,Colors::Pformat, &redY, &greenY, &blueY);

    int r = iabs(redY - redX);
    int g = iabs(greenY - greenX);
    int b = iabs(blueY - blueX);
    return transBlender(makeColor(r, g, b), y, n);
}


static SGF_INLINE unsigned int screenBlender(unsigned int x, unsigned int y, unsigned int n){

	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

    int r = 255 - ((255 - redX) * (255 - redY)) / 256;
    int g = 255 - ((255 - greenX) * (255 - greenY)) / 256;
    int b = 255 - ((255 - blueX) * (255 - blueY)) / 256;
    return transBlender(makeColor(r, g, b), y, n);
}


static SGF_INLINE unsigned int burnBlender(unsigned int x, unsigned int y, unsigned int n){
    Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

    int r = MAX(redX - redY, 0);
    int g = MAX(greenX - greenY, 0);
    int b = MAX(blueX - blueY, 0);
    return transBlender(makeColor(r, g, b), y, n);
}


static SGF_INLINE unsigned int dodgeBlender(unsigned int x, unsigned int y, unsigned int n){
    if (!Colors::Pformat) {
		Colors::init_colors();
		if (!Colors::Pformat) {
//			Debug::debug(Debug::error,__FUNCTION__) << " Error initiating Colors: " << SDL_GetError() << endl;
		}
	}
	Uint8 redX = 0;
    Uint8 greenX= 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x,Colors::Pformat , &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

    int r = redX + (redY * n / 256);
    int g = greenX + (greenY * n / 256);
    int b = blueX + (blueY * n / 256);
    return transBlender(makeColor(r, g, b), y, n);
}
static SGF_INLINE unsigned int invertBlender(unsigned int x, unsigned int y, unsigned int n){
    if (!Colors::Pformat) {
		Colors::init_colors();
		if (!Colors::Pformat) {
//			Debug::debug(Debug::error,__FUNCTION__) << " Error initiating Colors: " << SDL_GetError() << endl;
		}
	}
	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x, Colors::Pformat , &redX, &greenX, &blueX);

    int r = 255-redX;
    int g = 255-greenX;
    int b = 255-blueX;
    return transBlender(makeColor(r, g, b), y, n);
}

static SGF_INLINE unsigned int dissolveBlender(unsigned int x, unsigned int y, unsigned int n){

return ((rand() & 255) > (int)n) ? x : y;
}

struct BlendingData{
    BlendingData():
    blendName("noBlender"), red(0), green(0), blue(0), alpha(0), currentBlender(noBlender){}
	string blendName;
    Uint8 red, green, blue, alpha;
	int sourcePixel,destPixel; //usados no aalphaBlender ou em outros modos de blendin pixels
    blender currentBlender;
};

extern BlendingData globalBlend;

/* default truecolor pixel format */
#define DEFAULT_RGB_R_SHIFT_15  0
#define DEFAULT_RGB_G_SHIFT_15  5
#define DEFAULT_RGB_B_SHIFT_15  10
#define DEFAULT_RGB_R_SHIFT_16  0
#define DEFAULT_RGB_G_SHIFT_16  5
#define DEFAULT_RGB_B_SHIFT_16  11
#define DEFAULT_RGB_R_SHIFT_24  0
#define DEFAULT_RGB_G_SHIFT_24  8
#define DEFAULT_RGB_B_SHIFT_24  16
#define DEFAULT_RGB_R_SHIFT_32  0
#define DEFAULT_RGB_G_SHIFT_32  8
#define DEFAULT_RGB_B_SHIFT_32  16
#define DEFAULT_RGB_A_SHIFT_32  24
#define PAL_SIZE     256


typedef struct {
   unsigned char data[32][32][32];
} RGB_MAP;

typedef struct {
   unsigned char data[PAL_SIZE][PAL_SIZE];
} COLOR_MAP;


extern RGB_MAP * rgb_map;
extern COLOR_MAP * color_map;

//SDL_Palette *CurrentPalette;

extern int _rgb_r_shift_15;
extern int _rgb_g_shift_15;
extern int _rgb_b_shift_15;
extern int _rgb_r_shift_16;
extern int _rgb_g_shift_16;
extern int _rgb_b_shift_16;
extern int _rgb_r_shift_24;
extern int _rgb_g_shift_24;
extern int _rgb_b_shift_24;
extern int _rgb_r_shift_32;
extern int _rgb_g_shift_32;
extern int _rgb_b_shift_32;
extern int _rgb_a_shift_32;

extern int _rgb_scale_5[];
extern int _rgb_scale_6[];

#define MASK_COLOR_8       0
#define MASK_COLOR_15      0x7C1F
#define MASK_COLOR_16      0xF81F
#define MASK_COLOR_24      0xFF00FF
#define MASK_COLOR_32      0xFF00FF

extern int * palette_color;

void destroy_colors();
void set_color (int idx, const SDL_Color *p);
void set_palette(const SDL_Palette p);
void set_palette_range (const SDL_Palette p, int from, int to, int retracesync);

void get_color (int idx, SDL_Color *p);
void get_palette (SDL_Palette p);
void get_palette_range (SDL_Palette p, int from, int to);

void fade_interpolate (const SDL_Palette source, const SDL_Palette dest, SDL_Palette output, int pos, int from, int to);
void fade_from_range (const SDL_Palette source, const SDL_Palette dest, int speed, int from, int to);
void fade_in_range (const SDL_Palette p, int speed, int from, int to);
void fade_out_range (int speed, int from, int to);
void fade_from (const SDL_Palette source, const SDL_Palette dest, int speed);
void fade_in (const SDL_Palette p, int speed);
void fade_out (int speed);

void select_palette (const SDL_Palette p);
void unselect_palette (void);

void generate_332_palette (SDL_Palette pal);
//s int generate_optimized_palette (struct CBitmap *image, SDL_Palette pal, const signed char rsvdcols[256]);

//void create_rgb_table (RGB_MAP *table, const SDL_Palette pal, AL_METHOD(void callback (int pos)));
//void create_light_table (COLOR_MAP *table, const SDL_Palette pal, int r, int g, int b, AL_METHOD(void callback (int pos)));
//void create_trans_table (COLOR_MAP *table, const SDL_Palette pal, int r, int g, int b, AL_METHOD(void callback (int pos)));
//void create_color_table (COLOR_MAP *table, const SDL_Palette pal, AL_METHOD(void blend (const SDL_Palette pal, int x, int y, SDL_Color *rgb)), AL_METHOD(void callback (int pos)));
//void create_blender_table (COLOR_MAP *table, const SDL_Palette pal, AL_METHOD(void callback (int pos)));
//typedef AL_METHOD(unsigned long, BLENDER_FUNC (unsigned long x, unsigned long y, unsigned long n);

//void set_blender_mode (BLENDER_FUNC b15, BLENDER_FUNC b16, BLENDER_FUNC b24, int r, int g, int b, int a);
//void set_blender_mode_ex (BLENDER_FUNC b15, BLENDER_FUNC b16, BLENDER_FUNC b24, BLENDER_FUNC b32, BLENDER_FUNC b15x, BLENDER_FUNC b16x, BLENDER_FUNC b24x, int r, int g, int b, int a);

void set_alpha_blender (void);
void set_write_alpha_blender (void);
void set_trans_blender (int r, int g, int b, int a);
void set_add_blender (int r, int g, int b, int a);
void set_burn_blender (int r, int g, int b, int a);
void set_color_blender (int r, int g, int b, int a);
void set_difference_blender (int r, int g, int b, int a);
void set_dissolve_blender (int r, int g, int b, int a);
void set_dodge_blender (int r, int g, int b, int a);
void set_hue_blender (int r, int g, int b, int a);
void set_invert_blender (int r, int g, int b, int a);
void set_luminance_blender (int r, int g, int b, int a);
void set_multiply_blender (int r, int g, int b, int a);
void set_saturation_blender (int r, int g, int b, int a);
void set_screen_blender (int r, int g, int b, int a);


int bestfit_color (SDL_Palette *pal, int r, int g, int b);

int makecol (int r, int g, int b);
int makecol8 (int r, int g, int b);
int makecol_depth (int color_depth, int r, int g, int b);

int makeacol (int r, int g, int b, int a);
int makeacol_depth (int color_depth, int r, int g, int b, int a);

int makecol15_dither (int r, int g, int b, int x, int y);
int makecol16_dither (int r, int g, int b, int x, int y);

int getr (int c);
int getg (int c);
int getb (int c);
int geta (int c);

/** getRed:
 *  Estrai o componente Vermelho (0-255) de um pixel no formato sendo
 *  usado pelo modo de video atualmente usado no display
 */
Uint8 getRed( int pixel );
/** getBlue:
 *  Estrai o componente azul (0-255) de um pixel no formato sendo
 *  usado pelo modo de video atualmente usado no display
 */
Uint8 getBlue( int pixel );
/** getGreen:
 *  Estrai o componente verde (0-255) de um pixel no formato sendo
 *  usado pelo modo de video atualmente usado no display
 */
Uint8 getGreen( int pixel );
/** getBlue:
 *  Estrai o componente de tranaparência (0-255) de um pixel no formato sendo
 *  usado pelo modo de video atualmente usado no display
 */
Uint8 getAlpha( int pixel );

	/** Adiciona duas Cores
	* \param color1: primeira cor a ser adicionada no formato ColorDefinition
	* \param color2: segunda cor a ser adicionada no formato ColorDefinition
	* \return integral representando o pixel na cor final no formato do display
	*/
	int addColor( ColorDefinition color1, ColorDefinition color2 );
	/** Adiciona duas Cores
	* \param color1: primeira cor a ser adicionada no formato do display atualmente em uso
	* \param color2: segunda cor a ser adicionada no formato do display atualmente em uso
	* \return integral representando o pixel na cor final no formato do display
	*/
	int addColor( int color1, int color2 );



         /*
         * Converte valores de cor entre os espaços de cor HSV and RGB.
         * Os valores de cor no espaço RGB variam de 0 a 255
         * Hue variam de 0 to 360, e saturação varia entre 0 e 1
         */

		void rgb_to_hsv (int r, int g, int b, float *h, float *s, float *v);
        /*
         * Converte valores de cor entre os espaços de cor HSV and RGB.
         * Os valores de cor no espaço RGB variam de 0 a 255
         * Hue variam de 0 to 360, e saturação varia entre 0 e 1
         */
		void hsv_to_rgb (float h, float s, float v, int *r, int *g, int *b);


		/** escurece uma cor por um determinado fator
		*/
		Uint32 darken( int color, double factor );


        /* converte de cymk para rgb.
		* \note values devem estar no the range 0-255,
		*/
        void cymkToRGB(int c, int y, int m, int k, int * r, int * g, int * b);

int getr8 (int c);
int getg8 (int c);
int getb8 (int c);


int getr_depth (int color_depth, int c);
int getg_depth (int color_depth, int c);
int getb_depth (int color_depth, int c);
int geta_depth (int color_depth, int c);

SGF_INLINE int makecol15 (int r, int g, int b)
{
   return (((r >> 3) << _rgb_r_shift_15) |
           ((g >> 3) << _rgb_g_shift_15) |
           ((b >> 3) << _rgb_b_shift_15));
}

SGF_INLINE int makecol16 (int r, int g, int b)
{
   return (((r >> 3) << _rgb_r_shift_16) |
           ((g >> 2) << _rgb_g_shift_16) |
           ((b >> 3) << _rgb_b_shift_16));
}


SGF_INLINE int makecol24 (int r, int g, int b)
{
   return ((r << _rgb_r_shift_24) |
           (g << _rgb_g_shift_24) |
           (b << _rgb_b_shift_24));
}


SGF_INLINE int makecol32 (int r, int g, int b)
{
   return ((r << _rgb_r_shift_32) |
           (g << _rgb_g_shift_32) |
           (b << _rgb_b_shift_32));
}


SGF_INLINE int makeacol32 (int r, int g, int b, int a)
{
   return ((r << _rgb_r_shift_32) |
           (g << _rgb_g_shift_32) |
           (b << _rgb_b_shift_32) |
           (a << _rgb_a_shift_32));
}

/*
SGF_INLINE int getr8 (int c)
{
   return _rgb_scale_6[(int)CurrentPalette->colors[c].r];
}


SGF_INLINE int getg8 (int c)
{
   return _rgb_scale_6[(int)CurrentPalette->colors[c].g];
}


SGF_INLINE int getb8 (int c)
{
   return _rgb_scale_6[(int)CurrentPalette->colors[c].b];
}
*/

SGF_INLINE int getr15 (int c)
{
   return _rgb_scale_5[(c >> _rgb_r_shift_15) & 0x1F];
}


SGF_INLINE int getg15 (int c)
{
   return _rgb_scale_5[(c >> _rgb_g_shift_15) & 0x1F];
}


SGF_INLINE int getb15 (int c)
{
   return _rgb_scale_5[(c >> _rgb_b_shift_15) & 0x1F];
}


SGF_INLINE int getr16 (int c)
{
   return _rgb_scale_5[(c >> _rgb_r_shift_16) & 0x1F];
}


SGF_INLINE int getg16 (int c)
{
   return _rgb_scale_6[(c >> _rgb_g_shift_16) & 0x3F];
}


SGF_INLINE int getb16 (int c)
{
   return _rgb_scale_5[(c >> _rgb_b_shift_16) & 0x1F];
}


SGF_INLINE int getr24 (int c)
{
   return ((c >> _rgb_r_shift_24) & 0xFF);
}


SGF_INLINE int getg24 (int c)
{
   return ((c >> _rgb_g_shift_24) & 0xFF);
}


SGF_INLINE int getb24 (int c)
{
   return ((c >> _rgb_b_shift_24) & 0xFF);
}


SGF_INLINE int getr32 (int c)
{
   return ((c >> _rgb_r_shift_32) & 0xFF);
}


SGF_INLINE int getg32 (int c)
{
   return ((c >> _rgb_g_shift_32) & 0xFF);
}


SGF_INLINE int getb32 (int c)
{
   return ((c >> _rgb_b_shift_32) & 0xFF);
}


SGF_INLINE int geta32 (int c)
{
   return ((c >> _rgb_a_shift_32) & 0xFF);
}


SGF_INLINE void _set_color (int idx, const SDL_Color *p)
{
   set_color(idx, p);
}

static SGF_INLINE unsigned int colorBlender(unsigned int x, unsigned int y, unsigned int n){
    Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
	SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y,Colors::Pformat, &redY, &greenY, &blueY);

   float xh, xs, xv;
   float yh, ys, yv;
   int r, g, b;

   rgb_to_hsv(redX, greenX, blueX, &xh, &xs, &xv);
   rgb_to_hsv(redY, greenY, blueY, &yh, &ys, &yv);

   xs = TT(xs, ys, n);
   xh = TT(xh, yh, n);

   hsv_to_rgb(xh, xs, xv, &r, &g, &b);

    return makeColor(r, g, b);
}






static SGF_INLINE unsigned int luminanceBlender(unsigned int x, unsigned int y, unsigned int n){
    Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y,Colors::Pformat, &redY, &greenY, &blueY);

   float xh, xs, xv;
   float yh, ys, yv;
   int r, g, b;

   rgb_to_hsv(redX, greenX, blueX, &xh, &xs, &xv);
   rgb_to_hsv(redY, greenY, blueY, &yh, &ys, &yv);

   xv = TT(xv, yv, n);

   hsv_to_rgb(xh, xs, xv, &r, &g, &b);

    return makeColor(r, g, b);
}

static SGF_INLINE unsigned int hueBlender(unsigned int x, unsigned int y, unsigned int n){
    Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
    SDL_GetRGB(x, Colors::Pformat, &redX, &greenX, &blueX);
    Uint8 redY = 0;
    Uint8 greenY = 0;
    Uint8 blueY = 0;
    SDL_GetRGB(y, Colors::Pformat, &redY, &greenY, &blueY);

   float xh, xs, xv;
   float yh, ys, yv;
   int r, g, b;

   rgb_to_hsv(redX, greenX, blueX, &xh, &xs, &xv);
   rgb_to_hsv(redY, greenY, blueY, &yh, &ys, &yv);

   xh = TT(xh, yh, n);

   hsv_to_rgb(xh, xs, xv, &r, &g, &b);


    return makeColor(r, g, b);
}

#define MOOSEPIC_W 64
#define MOOSEPIC_H 88
#define MOOSEFRAME_SIZE (MOOSEPIC_W * MOOSEPIC_H)
#define MOOSEFRAMES_COUNT 10
//SDL_Color PixelBuffer[MOOSEPIC_H][MOOSEPIC_W];


			/**
			 * Cor transparente (alpha defindo para não opaco).
			 * Com um alpha opaco deve ser preto puro.
			 *
			 * Esta cor é util para especificar que, por exemplo, um
			 * background deve permanecer vazio, i.e. totalmente transparente.
			 *
			 */
			extern SGE_API const ColorDefinition Transparent ;


			/// Shades of Grey:

			extern SGE_API const ColorDefinition Black ;
			extern SGE_API const ColorDefinition Grey ;
			extern SGE_API const ColorDefinition DimGrey ;
			extern SGE_API const ColorDefinition LightGrey ;
			extern SGE_API const ColorDefinition SlateGrey ;
			extern SGE_API const ColorDefinition Silver ;
			extern SGE_API const ColorDefinition MortalLightGrey ;
			extern SGE_API const ColorDefinition DarkGrey ;
			


			/// Shades of Blue:

			extern SGE_API const ColorDefinition AliceBlue ;
			extern SGE_API const ColorDefinition BlueViolet ;
			extern SGE_API const ColorDefinition CadetBlue ;
			extern SGE_API const ColorDefinition DarkSlateBlue ;
			extern SGE_API const ColorDefinition DarkTurquoise ;
			extern SGE_API const ColorDefinition DeepSkyBlue ;
			extern SGE_API const ColorDefinition DodgerBlue ;
			extern SGE_API const ColorDefinition LightBlue ;
			extern SGE_API const ColorDefinition LightCyan ;
			extern SGE_API const ColorDefinition MediumBlue ;
			extern SGE_API const ColorDefinition NavyBlue ;
			extern SGE_API const ColorDefinition RoyalBlue ;
			extern SGE_API const ColorDefinition SkyBlue ;
			extern SGE_API const ColorDefinition SlateBlue ;
			extern SGE_API const ColorDefinition SteelBlue ;
			extern SGE_API const ColorDefinition Aquamarine ;
			extern SGE_API const ColorDefinition Azure ;
			extern SGE_API const ColorDefinition Blue ;
			extern SGE_API const ColorDefinition Cyan ;
			extern SGE_API const ColorDefinition Turquoise ;
			extern SGE_API const ColorDefinition MidnightBlue ;
			extern SGE_API const ColorDefinition MortalBlue ;
			extern SGE_API const ColorDefinition MortalCyan ;
			extern SGE_API const ColorDefinition MortalLightBlue;
			extern SGE_API const ColorDefinition MortalLightCyan;
			/// Shades of Brown:

			extern SGE_API const ColorDefinition Brown ;
			extern SGE_API const ColorDefinition RosyBrown ;
			extern SGE_API const ColorDefinition SaddleBrown ;
			extern SGE_API const ColorDefinition Beige ;
			extern SGE_API const ColorDefinition Burlywood ;
			extern SGE_API const ColorDefinition Chocolate ;
			extern SGE_API const ColorDefinition Peru ;
			extern SGE_API const ColorDefinition Tan ;
			extern SGE_API const ColorDefinition Copper ;



			/// Shades of Green:

			extern SGE_API const ColorDefinition DarkGreen ;
			extern SGE_API const ColorDefinition DarkOliveGreen ;
			extern SGE_API const ColorDefinition ForestGreen ;
			extern SGE_API const ColorDefinition GreenYellow  ;
			extern SGE_API const ColorDefinition LawnGreen ;
			extern SGE_API const ColorDefinition LimeGreen ;
			extern SGE_API const ColorDefinition MintCream ;
			extern SGE_API const ColorDefinition OliveDrab ;
			extern SGE_API const ColorDefinition PaleGreen ;
			extern SGE_API const ColorDefinition SeaGreen ;
			extern SGE_API const ColorDefinition SpringGreen ;
			extern SGE_API const ColorDefinition YellowGreen ;
			extern SGE_API const ColorDefinition Chartreuse ;
			extern SGE_API const ColorDefinition Green ;
			extern SGE_API const ColorDefinition Khaki ;
			extern SGE_API const ColorDefinition MortalGreen ;
			extern SGE_API const ColorDefinition LightGreen ;


			/// Shades of Orange:

			extern SGE_API const ColorDefinition DarkOrange ;
			extern SGE_API const ColorDefinition DarkSalmon ;
			extern SGE_API const ColorDefinition LightCoral ;
			extern SGE_API const ColorDefinition LightSalmon ;
			extern SGE_API const ColorDefinition PeachPuff ;
			extern SGE_API const ColorDefinition Bisque ;
			extern SGE_API const ColorDefinition Coral ;
			extern SGE_API const ColorDefinition Honeydew ;
			extern SGE_API const ColorDefinition Orange ;
			extern SGE_API const ColorDefinition Salmon ;
			extern SGE_API const ColorDefinition Sienna ;



			/// Shades of Red:

			extern SGE_API const ColorDefinition DeepPink ;
			extern SGE_API const ColorDefinition HotPink ;
			extern SGE_API const ColorDefinition IndianRed ;
			extern SGE_API const ColorDefinition LightPink ;
			extern SGE_API const ColorDefinition MediumVioletRed ;
			extern SGE_API const ColorDefinition MistyRose ;
			extern SGE_API const ColorDefinition OrangeRed ;
			extern SGE_API const ColorDefinition VioletRed ;
			extern SGE_API const ColorDefinition Firebrick ;
			extern SGE_API const ColorDefinition Pink ;
			extern SGE_API const ColorDefinition Red ;
			extern SGE_API const ColorDefinition LightRed;
			extern SGE_API const ColorDefinition Tomato ;
			extern SGE_API const ColorDefinition MortalRed ;
			extern SGE_API const ColorDefinition MortalLightRed ;

			/// Shades of Violet:

			extern SGE_API const ColorDefinition DarkOrchid ;
			extern SGE_API const ColorDefinition DarkViolet ;
			extern SGE_API const ColorDefinition LavenderBlush ;
			extern SGE_API const ColorDefinition MediumOrchid ;
			extern SGE_API const ColorDefinition MediumPurple ;
			extern SGE_API const ColorDefinition Lavender ;

			/// Pure magenta is the OSDL default color key.
			extern SGE_API const ColorDefinition Magenta ;
			extern SGE_API const ColorDefinition MaskColor ;

			extern SGE_API const ColorDefinition Maroon ;
			extern SGE_API const ColorDefinition Orchid ;
			extern SGE_API const ColorDefinition Plum ;
			extern SGE_API const ColorDefinition Purple ;
			extern SGE_API const ColorDefinition Thistle ;
			extern SGE_API const ColorDefinition Violet ;
			extern SGE_API const ColorDefinition MortalMagenta ;
			extern SGE_API const ColorDefinition LightMagenta ;


			/// Shades of White:

			extern SGE_API const ColorDefinition AntiqueWhite ;
			extern SGE_API const ColorDefinition FloralWhite ;
			extern SGE_API const ColorDefinition GhostWhite ;
			extern SGE_API const ColorDefinition NavajoWhite ;
			extern SGE_API const ColorDefinition OldLace ;
			extern SGE_API const ColorDefinition WhiteSmoke ;
			extern SGE_API const ColorDefinition Gainsboro ;
			extern SGE_API const ColorDefinition Ivory ;
			extern SGE_API const ColorDefinition Linen ;
			extern SGE_API const ColorDefinition Seashell ;
			extern SGE_API const ColorDefinition Snow ;
			extern SGE_API const ColorDefinition Wheat ;
			extern SGE_API const ColorDefinition White ;



			/// Shades of Yellow:

			extern SGE_API const ColorDefinition BlanchedAlmond ;
			extern SGE_API const ColorDefinition DarkGoldenrod ;
			extern SGE_API const ColorDefinition LemonChiffon ;
			extern SGE_API const ColorDefinition LightGoldenrod ;
			extern SGE_API const ColorDefinition LightYellow ;
			extern SGE_API const ColorDefinition PaleGoldenrod ;
			extern SGE_API const ColorDefinition PapayaWhip ;
			extern SGE_API const ColorDefinition Cornsilk ;
			extern SGE_API const ColorDefinition Gold ;
			extern SGE_API const ColorDefinition Goldenrod ;
			extern SGE_API const ColorDefinition Moccasin ;
			extern SGE_API const ColorDefinition Yellow ;
			extern SGE_API const ColorDefinition MortalYellow;


			/// Pure magenta is the SGF default color key.
			extern SGE_API const ColorDefinition DefaultColorkey ;

/**
* Formato independente de descrição da cor.
*
* Corresponde à informação RBGA descrevendo uma cor
* Definida no espaço  32-bit de cor,
* nesta ordem: o mais recente coordenada é o canal alpha do pixel
*
* \note A coordenada alfa nem sempre é levada em conta e confiável.
*
* \See Uma lista de nomes de cores (ex: Colors:: RoyalBlue).
*
*/




   /** getPixel:
	*  Estrai o valor do pixel na posição x,y da surface
	*
	*/
	Uint32  getPixel(SDL_Surface *bmp, const int x,const  int y) ;




	/** replaceColorSurface:
	* Substitui o valor do pixel original pelo pixel replaced na surface dada
	*  \note substitui todos os pixels que possuem o valor original
	*/
	void replaceColorSurface(SDL_Surface *bmp, int original, int replaced);
	/** putPixelSurface:
	* Coloca o valor do pixel dado na posição x,y da surface dada
	*
	*/
	void putPixelSurface(SDL_Surface *bmp, int x, int y, Uint32 pixel, bool translucent=false );
	/** putPixelSurface:
	Coloca um pixel com a cor (r,g,b) na posição x,y da surface dada
	*
	*/
	void putPixelSurface(SDL_Surface *bmp, int x, int y, Uint8 r, Uint8 g, Uint8 b);
	/** putPixelTexture:
	* Coloca o valor do pixel dado na posição x,y da textura dada
	*
	*/
	void putPixelTexture(SDL_Texture *bmp, int x, int y, Uint32 pixel, bool translucent=false );
	/** putPixelTexture:
	* Coloca um pixel com a cor (r,g,b) na posição x,y da textura dada
	*
	*/
	void putPixelTexture(SDL_Texture *bmp, int x, int y, Uint8 r, Uint8 g, Uint8 b);

	//* não testadas aindas
	void putPixelTexture(SDL_Texture *texture, int x, int y, SDL_Color cor);
	void UpdateTextureFromBuffer(SDL_Texture *texture, SDL_Color ** PixelBuffer);

	/** SDL_InitFormat:
	* Faz o mesmo que a função SDL_AllocFormat do SDL 1.3
	*
	*/
	SDL_PixelFormat & SDL_InitFormat(SDL_PixelFormat & format, int bpp, Uint32 Rmask, Uint32 Gmask,
               Uint32 Bmask, Uint32 Amask);

	/** @fn SDL_PixelFormat * getPixelFormat2()
	@brief Retorna uma estrutura SDL_PixelFormat preenchida de acordo com o formato do display atual
	@warning Esta função não é mais usada desde que sdl 1.3 possui SDL_AllocFormat .
	@warning Lembrar de deletar o formato depois de usá-lo, ou haverá memory leak

	**/
	 SDL_PixelFormat *getPixelFormat2();  //!para janelas  SDLWindow apenas

	/** @fn toString( ColorDefinition color ) throw()
	@brief Mostra de uma forma legível a definição de uma cor
	**/
	string toString( ColorDefinition color ) throw();
	/** @fn toString( PixelColor pixel, const SDL_PixelFormat & format ) throw()
	@brief Mostra de uma forma legível a definição de um pixel
	@param pixel: o pixel que se deseja descrever
	@param format: o formato SDL do pixel
	**/
	string toString( PixelColor pixel, const SDL_PixelFormat & format ) throw()	;
	/** @fn toString( PixelColor pixel ) throw()
	@brief Mostra de uma forma legível a definição de um pixel
	@note assume-se que o pixel esteja no formato atual do display
	@param pixel: o pixel que se deseja descrever
	**/
	string toString( PixelColor pixel, const SDL_PixelFormat & format ) throw()	;
	/** @fn toString( const SDL_PixelFormat & format ) throw()
	@brief Mostra de uma forma legível a definição de um formato
	@param format:  O SDL_PixelFormat que se deseja descrever
	**/
	string toString( const SDL_PixelFormat & format ) throw();


} // end namespace Colors

} //end namespace SGF

#endif

