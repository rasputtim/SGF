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

#include <limits.h>
#include <string.h>
#include <math.h>
#include "../../ExternalLibs/SDL2/src/render/SDL_sysrender.h"
#include "graphics/SGF_Color.h"
#include "util/SGF_SdlManager.h"
#include "graphics/SGF_Bitmap.h"
#include "util/SGF_Debug.h"


namespace SGF {
	
class CBitmap;

namespace Colors {

BlendingData globalBlend;
static int clamp(Uint8 in, Uint8 low = 0, Uint8 high = 255){
    return Util::clamp(static_cast<int>(in),static_cast<int>(low),static_cast<int>(high));
}
SDL_Palette *CurrentPalette = NULL;
SDL_PixelFormat * Pformat = NULL;
int _color_depth = 32; //default color depth
bool sdlCompatibility = false; //default is to work in SDL 1.3 Mode
static CSDLManager *pSdlManager = NULL;


bool getCompatibilityMode(){
return false;
}

SDL_PixelFormat * getCurrentPixelFormat(){
	if (Pformat==NULL) {
			SDL_DisplayMode mode;
			//Todo Change to GetCurrentDysplayMode
			SDL_GetDesktopDisplayMode(0,&mode);
			Pformat = SDL_AllocFormat(mode.format);
			if (Pformat == NULL) {
			Debug::debug(Debug::error,__FUNCTION__) << "Error: " << SDL_GetError() <<endl;
			}
	}
	return Pformat;
}
void convertpixelFormat(CBitmap *bitmap){
SDL_Surface* temp = SDL_ConvertSurface(bitmap->getBitmap(),getCurrentPixelFormat(),SDL_RLEACCEL);
	SDL_FreeSurface(bitmap->getBitmap());
//	bitmap->setBitmap(temp);

}
// Different colors described by name.
/// Fully Transparent special color:

extern const ColorDefinition Transparent     =
	{   0,   0,   0,  0  } ;

/// Shades of Grey:

extern const ColorDefinition Black           =
	{   0,   0,   0, 255 } ;

extern const ColorDefinition Grey            =
	{ 190, 190, 190, 255 } ;

extern const ColorDefinition DimGrey         =
	{ 105, 105, 105, 255 } ;

extern const ColorDefinition LightGrey       =
	{ 211, 211, 211, 255 } ;

extern const ColorDefinition SlateGrey       =
	{ 112, 128, 144, 255 } ;

extern const ColorDefinition Silver          =
	{ 230, 232, 250, 255 } ;

extern const ColorDefinition MortalLightGrey       =
	{ 168, 168, 168, 255 } ;

extern const ColorDefinition DarkGrey       =
	{ 84, 84, 84, 255 } ;




/// Shades of Blue:

extern const ColorDefinition AliceBlue       =
	{ 240, 248, 255, 255 } ;

extern const ColorDefinition BlueViolet      =
	{ 138,  43, 226, 255 } ;

extern const ColorDefinition CadetBlue       =
	{  95, 158, 160, 255 } ;

extern const ColorDefinition DarkSlateBlue   =
	{  72,  61, 139, 255 } ;

extern const ColorDefinition DarkTurquoise   =
	{   0, 206, 209, 255 } ;

extern const ColorDefinition DeepSkyBlue     =
	{   0, 191, 255, 255 } ;

extern const ColorDefinition DodgerBlue      =
	{  30, 144, 255, 255 } ;

extern const ColorDefinition LightBlue       =
	{ 173, 216, 230, 255 } ;

extern const ColorDefinition LightCyan       =
	{ 224, 255, 255, 255 } ;

extern const ColorDefinition MediumBlue      =
	{ 123, 104, 238, 255 } ;

extern const ColorDefinition NavyBlue        =
	{   0,   0, 128, 255 } ;

extern const ColorDefinition RoyalBlue       =
	{  65, 105, 225, 255 } ;

extern const ColorDefinition SkyBlue         =
	{ 135, 206, 235, 255 } ;

extern const ColorDefinition SlateBlue       =
	{ 106,  90, 205, 255 } ;

extern const ColorDefinition SteelBlue       =
	{  70, 130, 180, 255 } ;

extern const ColorDefinition Aquamarine      =
	{ 127, 255, 212, 255 } ;

extern const ColorDefinition Azure           =
	{ 240, 255, 255, 255 } ;

extern const ColorDefinition Blue            =
	{   0,   0, 255, 255 } ;

extern const ColorDefinition Cyan            =
	{   0, 255, 255, 255 } ;

extern const ColorDefinition Turquoise       =
	{  64, 224, 208, 255 } ;

extern const ColorDefinition MidnightBlue    =
	{  25,  25, 112, 255 } ;

extern const ColorDefinition MortalBlue    =
	{  0,  0, 168, 255 } ;

extern const ColorDefinition MortalCyan    =
	{  0,  168, 168, 255 } ;

extern const ColorDefinition MortalLightBlue    =
	{  84,  84, 255, 255 } ;

extern const ColorDefinition MortalLightCyan = 
	{  84,  255, 255, 255 } ;


/// Shades of Brown:

extern const ColorDefinition Brown           =
	{ 165,  42,  42, 255 } ;

extern const ColorDefinition RosyBrown       =
	{ 188, 143, 143, 255 } ;

extern const ColorDefinition SaddleBrown     =
	{ 139,  69,  19, 255 } ;

extern const ColorDefinition Beige           =
	{ 245,  42,  42, 255 } ;

extern const ColorDefinition Burlywood       =
	{ 222, 184, 135, 255 } ;

extern const ColorDefinition Chocolate       =
	{ 210, 105,  30, 255 } ;

extern const ColorDefinition Peru            =
	{ 205, 133,  63, 255 } ;

extern const ColorDefinition Tan             =
	{ 210, 180, 140, 255 } ;

extern const ColorDefinition Copper          =
	{ 184, 115,  51, 255 } ;




/// Shades of Green:

extern const ColorDefinition DarkGreen       =
	{	0, 100,   0, 255 } ;

extern const ColorDefinition DarkOliveGreen  =
	{  85, 107,  47, 255 } ;

extern const ColorDefinition ForestGreen     =
	{  34, 139,  34, 255 } ;

extern const ColorDefinition GreenYellow     =
	{ 173, 255,  47, 255 } ;

extern const ColorDefinition LawnGreen       =
	{ 124, 252,   0, 255 } ;

extern const ColorDefinition LimeGreen       =
	{  50, 205,  50, 255 } ;

extern const ColorDefinition MintCream       =
	{ 245, 255, 250, 255 } ;

extern const ColorDefinition OliveDrab       =
	{ 107, 142,  35, 255 } ;

extern const ColorDefinition PaleGreen       =
	{ 152, 251, 152, 255 } ;

extern const ColorDefinition SeaGreen        =
	{  46, 139,  87, 255 } ;

extern const ColorDefinition SpringGreen     =
	{	0, 255, 127, 255 } ;

extern const ColorDefinition YellowGreen     =
	{ 154, 205,  50, 255 } ;

extern const ColorDefinition Chartreuse      =
	{ 127, 255,   0, 255 } ;

extern const ColorDefinition Green           =
	{	0, 255,   0, 255 } ;

extern const ColorDefinition Khaki           =
	{ 240, 230, 140, 255 } ;
extern const ColorDefinition MortalGreen           =
	{	0, 168,   0, 255 } ;

extern const ColorDefinition LightGreen     =
	{ 84, 255, 84, 255 } ;



/// Shades of Orange:

extern const ColorDefinition DarkOrange      =
	{ 255, 140,   0, 255 } ;

extern const ColorDefinition DarkSalmon      =
	{ 233, 150, 122, 255 } ;

extern const ColorDefinition LightCoral      =
	{ 240, 128, 128, 255 } ;

extern const ColorDefinition LightSalmon     =
	{ 255, 160, 122, 255 } ;

extern const ColorDefinition PeachPuff       =
	{ 255, 218, 185, 255 } ;

extern const ColorDefinition Bisque          =
	{ 255, 228, 196, 255 } ;

extern const ColorDefinition Coral           =
	{ 255, 127,  80, 255 } ;

extern const ColorDefinition Honeydew        =
	{ 240, 255, 240, 255 } ;

extern const ColorDefinition Orange          =
	{ 255, 165,   0, 255 } ;

extern const ColorDefinition Salmon          =
	{ 250, 128, 114, 255 } ;

extern const ColorDefinition Sienna          =
	{ 160,  82,  45, 255 } ;




/// Shades of Red:

extern const ColorDefinition DeepPink        =
	{ 255,  20, 147, 255 } ;

extern const ColorDefinition HotPink         =
	{ 255, 105, 180, 255 } ;

extern const ColorDefinition IndianRed       =
	{ 205,  92,  92, 255 } ;

extern const ColorDefinition LightPink       =
	{ 255, 182, 193, 255 } ;

extern const ColorDefinition MediumVioletRed =
	{ 199,  21, 133, 255 } ;

extern const ColorDefinition MistyRose       =
	{ 255, 228, 225, 255 } ;

extern const ColorDefinition OrangeRed       =
	{ 255,  69,   0, 255 } ;

extern const ColorDefinition VioletRed       =
	{ 208,  32, 144, 255 } ;

extern const ColorDefinition Firebrick       =
	{ 178,  34, 34 , 255 } ;

extern const ColorDefinition Pink            =
	{ 255, 192, 203, 255 } ;

extern const ColorDefinition Red             =
	{ 255,   0,   0, 255 } ;

extern const ColorDefinition LightRed             =
	{ 65,   0,   0, 255 } ;

extern const ColorDefinition Tomato          =
	{ 255,  99,  71, 255 } ;
extern const ColorDefinition MortalRed          =
	{ 168,  0,  0, 255 } ;

extern const ColorDefinition MortalLightRed             =
	{ 255,   84,   84, 255 } ;




/// Shades of Violet:

extern const ColorDefinition DarkOrchid      =
	{ 153,  50, 204, 255 } ;

extern const ColorDefinition DarkViolet      =
	{ 148,   0, 211, 255 } ;

extern const ColorDefinition LavenderBlush   =
	{ 255, 240, 245, 255 } ;

extern const ColorDefinition MediumOrchid    =
	{ 186,  85, 211, 255 } ;

extern const ColorDefinition MediumPurple    =
	{ 147, 112, 219, 255 } ;

extern const ColorDefinition Lavender        =
	{ 230, 230, 250, 255 } ;

extern const ColorDefinition Magenta         =
	{ 255,   0, 255, 255 } ;

extern const ColorDefinition MaskColor         =
	{ 255,   0, 255, 255 } ;

extern const ColorDefinition Maroon          =
	{ 176,  48,  96, 255 } ;

extern const ColorDefinition Orchid          =
	{ 218, 112, 214, 255 } ;

extern const ColorDefinition Plum            =
	{ 221, 160, 221, 255 } ;

extern const ColorDefinition Purple          =
	{ 160,  32, 240, 255 } ;

extern const ColorDefinition Thistle         =
	{ 216, 191, 216, 255 } ;

extern const ColorDefinition Violet          =
	{ 238, 130, 238, 255 } ;

extern const ColorDefinition MortalMagenta         =
	{ 168,   0, 168, 255 } ;

extern const ColorDefinition LightMagenta         =
	{ 252,   84, 252, 255 } ;


/// Shades of White:

extern const ColorDefinition AntiqueWhite    =
	{ 250, 235, 215, 255 } ;

extern const ColorDefinition FloralWhite     =
	{ 255, 250, 240, 255 } ;

extern const ColorDefinition GhostWhite      =
	{ 248, 248, 255, 255 } ;

extern const ColorDefinition NavajoWhite     =
	{ 255, 222, 173, 255 } ;

extern const ColorDefinition OldLace         =
	{ 253, 245, 230, 255 } ;

extern const ColorDefinition WhiteSmoke      =
	{ 245, 245, 245, 255 } ;

extern const ColorDefinition Gainsboro       =
	{ 220, 220, 220, 255 } ;

extern const ColorDefinition Ivory           =
	{ 255, 255, 240, 255 } ;

extern const ColorDefinition Linen           =
	{ 250, 240, 230, 255 } ;

extern const ColorDefinition Seashell        =
	{ 255, 245, 238, 255 } ;

extern const ColorDefinition Snow            =
	{ 255, 250, 250, 255 } ;

extern const ColorDefinition Wheat           =
	{ 245, 222, 179, 255 } ;

extern const ColorDefinition White           =
	{ 255, 255, 255, 255 } ;




/// Shades of Yellow:

extern const ColorDefinition BlanchedAlmond  =
	{ 255, 235, 205, 255 } ;

extern const ColorDefinition DarkGoldenrod   =
	{ 184, 134,  11, 255 } ;

extern const ColorDefinition LemonChiffon    =
	{ 255, 250, 205, 255 } ;

extern const ColorDefinition LightGoldenrod  =
	{ 238, 221, 130, 255 } ;

extern const ColorDefinition LightYellow     =
	{ 255, 255, 224, 255 } ;

extern const ColorDefinition PaleGoldenrod   =
	{ 238, 232, 170, 255 } ;

extern const ColorDefinition PapayaWhip      =
	{ 255, 239, 213, 255 } ;

extern const ColorDefinition Cornsilk        =
	{ 255, 248, 220, 255 } ;

extern const ColorDefinition Gold            =
	{ 255, 215,   0, 255 } ;

extern const ColorDefinition Goldenrod       =
	{ 218, 165,  32, 255 } ;

extern const ColorDefinition Moccasin        =
	{ 255, 228, 181, 255 } ;

extern const ColorDefinition Yellow          =
	{ 255, 255,   0, 255 } ;

extern const ColorDefinition MortalYellow          =
	{ 255, 255,  84, 255 } ;

extern const ColorDefinition DefaultColorkey = Magenta ;

//ColorDefinition::ColorDefinition(Uint8 _r, Uint8 _g, Uint8 _b,Uint8 _a=255):
	//				r(_r),g(_g),b(_b),a(_a){}


void init_colors () {
#if 0
	if (getCompatibilityMode()) {

		const SDL_VideoInfo* myPointer = ::SDL_GetVideoInfo();
		Colors::_color_depth = myPointer->vfmt->BitsPerPixel;
		if (Colors::_color_depth == 8)
		CurrentPalette = myPointer->vfmt->palette;
		else
		CurrentPalette = NULL;
		sdlCompatibility = true;

	}else {
#endif
		getCurrentPixelFormat();
		Colors::_color_depth = Pformat->BitsPerPixel;//SDL_BITSPERPIXEL(mode.format);//CSDLManager::GetInstance()->state->surface_format.BitsPerPixel;
		if (_color_depth == 8)
		CurrentPalette = Pformat->palette;//CSDLManager::GetInstance()->state->surface_format.palette;
		else
		CurrentPalette = NULL;
	    sdlCompatibility = false;
//}
}

void destroy_colors(){


	if (Pformat) delete Pformat;
	if (CurrentPalette) delete CurrentPalette;
}

int _rgb_r_shift_15 = DEFAULT_RGB_R_SHIFT_15;     /* truecolor pixel format */
int _rgb_g_shift_15 = DEFAULT_RGB_G_SHIFT_15;
int _rgb_b_shift_15 = DEFAULT_RGB_B_SHIFT_15;
int _rgb_r_shift_16 = DEFAULT_RGB_R_SHIFT_16;
int _rgb_g_shift_16 = DEFAULT_RGB_G_SHIFT_16;
int _rgb_b_shift_16 = DEFAULT_RGB_B_SHIFT_16;
int _rgb_r_shift_24 = DEFAULT_RGB_R_SHIFT_24;
int _rgb_g_shift_24 = DEFAULT_RGB_G_SHIFT_24;
int _rgb_b_shift_24 = DEFAULT_RGB_B_SHIFT_24;
int _rgb_r_shift_32 = DEFAULT_RGB_R_SHIFT_32;
int _rgb_g_shift_32 = DEFAULT_RGB_G_SHIFT_32;
int _rgb_b_shift_32 = DEFAULT_RGB_B_SHIFT_32;
int _rgb_a_shift_32 = DEFAULT_RGB_A_SHIFT_32;

/* lookup table for scaling 5 bit colors up to 8 bits */
int _rgb_scale_5[32] =
{
   0,   8,   16,  24,  33,  41,  49,  57,
   66,  74,  82,  90,  99,  107, 115, 123,
   132, 140, 148, 156, 165, 173, 181, 189,
   198, 206, 214, 222, 231, 239, 247, 255
};


/* lookup table for scaling 6 bit colors up to 8 bits */
int _rgb_scale_6[64] =
{
   0,   4,   8,   12,  16,  20,  24,  28,
   32,  36,  40,  44,  48,  52,  56,  60,
   65,  69,  73,  77,  81,  85,  89,  93,
   97,  101, 105, 109, 113, 117, 121, 125,
   130, 134, 138, 142, 146, 150, 154, 158,
   162, 166, 170, 174, 178, 182, 186, 190,
   195, 199, 203, 207, 211, 215, 219, 223,
   227, 231, 235, 239, 243, 247, 251, 255
};

int getr8 (int c)
{
   return _rgb_scale_6[(int)CurrentPalette->colors[c].r];
}


int getg8 (int c)
{
   return _rgb_scale_6[(int)CurrentPalette->colors[c].g];
}


int getb8 (int c)
{
   return _rgb_scale_6[(int)CurrentPalette->colors[c].b];
}

// makecol8:
//   Converts R, G, and B values (ranging 0-255) to an 8 bit paletted color.
//   If the global rgb_map table is initialised, it uses that, otherwise
//   it searches through the current palette to find the best match.

int makecol8(int r, int g, int b)
{
 //  if (rgb_map)
 //     return rgb_map->data[r>>3][g>>3][b>>3];
 //  else
      return bestfit_color(CurrentPalette, r>>2, g>>2, b>>2);
}


/* makecol_depth:
 *  Converts R, G, and B values (ranging 0-255) to whatever pixel format
 *  is required by the specified color depth.
 */
int makecol_depth(int color_depth, int r, int g, int b)
{
   switch (color_depth) {

     case 8:
	   return makecol8(r, g, b);

      case 15:
	 return makecol15(r, g, b);

      case 16:
	 return makecol16(r, g, b);

      case 24:
	 return makecol24(r, g, b);

      case 32:
	 return makecol32(r, g, b);
   }

   return 0;
}



/* makeacol_depth:
 *  Converts R, G, B, and A values (ranging 0-255) to whatever pixel format
 *  is required by the specified color depth.
 */
int makeacol_depth(int color_depth, int r, int g, int b, int a)
{
   switch (color_depth) {

      case 8:
		  return makecol8(r, g, b);

      case 15:
	 return makecol15(r, g, b);

      case 16:
	 return makecol16(r, g, b);

      case 24:
	 return makecol24(r, g, b);

      case 32:
	 return makeacol32(r, g, b, a);
   }

   return 0;
}



/* makecol:
 *  Converts R, G, and B values (ranging 0-255) to whatever pixel format
 *  is required by the current video mode.
 */
int makecol(int r, int g, int b)
{
	//return ::SDL_MapRGB(SDL_PixelFormat *fmt, Uint8 r, Uint8 g, Uint8 b);
	return makecol_depth(_color_depth, r, g, b);
}



/* makeacol:
 *  Converts R, G, B, and A values (ranging 0-255) to whatever pixel format
 *  is required by the current video mode.
 */
int makeacol(int r, int g, int b, int a)
{
   return makeacol_depth(_color_depth, r, g, b, a);
}



/* getr_depth:
 *  Extracts the red component (ranging 0-255) from a pixel in the format
 *  being used by the specified color depth.
 */
int getr_depth(int color_depth, int c)
{
   switch (color_depth) {

      case 8:

		  return getr8(c);

      case 15:
	 return getr15(c);

      case 16:
	 return getr16(c);

      case 24:
	 return getr24(c);

      case 32:
	 return getr32(c);
   }

   return 0;
}



/* getg_depth:
 *  Extracts the green component (ranging 0-255) from a pixel in the format
 *  being used by the specified color depth.
 */
int getg_depth(int color_depth, int c)
{
   switch (color_depth) {

      case 8:

		  return getg8(c);

      case 15:
	 return getg15(c);

      case 16:
	 return getg16(c);

      case 24:
	 return getg24(c);

      case 32:
	 return getg32(c);
   }

   return 0;
}



/* getb_depth:
 *  Extracts the blue component (ranging 0-255) from a pixel in the format
 *  being used by the specified color depth.
 */
int getb_depth(int color_depth, int c)
{
   switch (color_depth) {

      case 8:

		return getb8(c);

      case 15:
	 return getb15(c);

      case 16:
	 return getb16(c);

      case 24:
	 return getb24(c);

      case 32:
	 return getb32(c);
   }

   return 0;
}



/* geta_depth:
 *  Extracts the alpha component (ranging 0-255) from a pixel in the format
 *  being used by the specified color depth.
 */
int geta_depth(int color_depth, int c)
{
   if (color_depth == 32)
      return geta32(c);

   return 0;
}



/* getr:
 *  Extracts the red component (ranging 0-255) from a pixel in the format
 *  being used by the current video mode.
 */
int getr(int c)
{
   return getr_depth(_color_depth, c);
}



/* getg:
 *  Extracts the green component (ranging 0-255) from a pixel in the format
 *  being used by the current video mode.
 */
int getg(int c)
{
   return getg_depth(_color_depth, c);
}



/* getb:
 *  Extracts the blue component (ranging 0-255) from a pixel in the format
 *  being used by the current video mode.
 */
int getb(int c)
{
   return getb_depth(_color_depth, c);
}







/* geta:
 *  Extracts the alpha component (ranging 0-255) from a pixel in the format
 *  being used by the current video mode.
 */
int geta(int c)
{
   return geta_depth(_color_depth, c);
}



	//dado o valor de uma cor em pixel format ele retorna a quantidade de
Uint8 getRed( int x ){
    Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
	if(getCompatibilityMode()){
	SDL_GetRGB(x, CBitmap::_my_state->Screen[0]->getBitmap()->format, &redX, &greenX, &blueX);
	}else {
		SDL_GetRGB(x, getCurrentPixelFormat(), &redX, &greenX, &blueX);

	}


    return redX;
}

Uint8 getBlue( int x ){
	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
   	if(getCompatibilityMode()){
	SDL_GetRGB(x, CBitmap::_my_state->Screen[0]->getBitmap()->format, &redX, &greenX, &blueX);
	}else {
		SDL_GetRGB(x, getCurrentPixelFormat(), &redX, &greenX, &blueX);

	}
	return blueX;
}

Uint8 getGreen( int x ){
	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
   	if(getCompatibilityMode()){
	SDL_GetRGB(x, CBitmap::_my_state->Screen[0]->getBitmap()->format, &redX, &greenX, &blueX);
	}else {
		SDL_GetRGB(x, getCurrentPixelFormat(), &redX, &greenX, &blueX);

	}
    return greenX;
}
Uint8 getAlpha( int x ){
	Uint8 redX = 0;
    Uint8 greenX = 0;
    Uint8 blueX = 0;
	Uint8 alphaX = 0;
   	if(getCompatibilityMode()){
	SDL_GetRGBA(x, CBitmap::_my_state->Screen[0]->getBitmap()->format, &redX, &greenX, &blueX, &alphaX);
	}else {
		SDL_GetRGBA(x, getCurrentPixelFormat(), &redX, &greenX, &blueX, &alphaX);

	}
    return alphaX;
}






//=======================================================



/* 1.5k lookup table for color matching */
static unsigned int col_diff[3*128];



/* bestfit_init:
 *  Color matching is done with weighted squares, which are much faster
 *  if we pregenerate a little lookup table...
 */
static void bestfit_init(void)
{
   int i;

   for (i=1; i<64; i++) {
      int k = i * i;
      col_diff[0  +i] = col_diff[0  +128-i] = k * (59 * 59);
      col_diff[128+i] = col_diff[128+128-i] = k * (30 * 30);
      col_diff[256+i] = col_diff[256+128-i] = k * (11 * 11);
   }
}



// bestfit_color:
 //  Searches a palette for the color closest to the requested R, G, B value.

int bestfit_color(SDL_Palette *pal, int r, int g, int b)
{
   int i, coldiff, lowest, bestfit;

   assert(r >= 0 && r <= 63);
   assert(g >= 0 && g <= 63);
   assert(b >= 0 && b <= 63);

   if (col_diff[1] == 0)
      bestfit_init();

   bestfit = 0;
   lowest = INT_MAX;

   // only the transparent (pink) color can be mapped to index 0
   if ((r == 63) && (g == 0) && (b == 63))
      i = 0;
   else
      i = 1;

   while (i<pal->ncolors) {
      const SDL_Color *rgb = &pal->colors[i];
      coldiff = (col_diff + 0) [ (rgb->g - g) & 0x7F ];
      if (coldiff < lowest) {
	 coldiff += (col_diff + 128) [ (rgb->r - r) & 0x7F ];
	 if (coldiff < lowest) {
	    coldiff += (col_diff + 256) [ (rgb->b - b) & 0x7F ];
	    if (coldiff < lowest) {
	       bestfit = rgb - pal->colors;    // faster than `bestfit = i;'
	       if (coldiff == 0)
		  return bestfit;
	       lowest = coldiff;
	    }
	 }
      }
      i++;
   }

   return bestfit;
}






// hsv_to_rgb:
 //  Converts from HSV colorspace to RGB values.

void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b)
{
   float f, x, y, z;
   int i;

   assert(s >= 0 && s <= 1);
   assert(v >= 0 && v <= 1);

   v *= 255.0f;

   if (s == 0.0f) { // ok since we don't divide by s, and faster
      *r = *g = *b = v + 0.5f;
   }
   else {
      h = fmod(h, 360.0f) / 60.0f;
      if (h < 0.0f)
	 h += 6.0f;

      i = (int)h;
      f = h - i;
      x = v * s;
      y = x * f;
      v += 0.5f; // round to the nearest integer below
      z = v - x;

      switch (i) {

	 case 6:
	 case 0:
	    *r = v;
	    *g = z + y;
	    *b = z;
	    break;

	 case 1:
	    *r = v - y;
	    *g = v;
	    *b = z;
	    break;

	 case 2:
	    *r = z;
	    *g = v;
	    *b = z + y;
	    break;

	 case 3:
	    *r = z;
	    *g = v - y;
	    *b = v;
	    break;

	 case 4:
	    *r = z + y;
	    *g = z;
	    *b = v;
	    break;

	 case 5:
	    *r = v;
	    *g = z;
	    *b = v - y;
	    break;
      }
   }
}



// rgb_to_hsv:
//   Converts an RGB value into the HSV colorspace.

void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v)
{
   int delta;

   assert(r >= 0 && r <= 255);
   assert(g >= 0 && g <= 255);
   assert(b >= 0 && b <= 255);

   if (r > g) {
      if (b > r) {
	 // b>r>g
	 delta = b-g;
	 *h = 240.0f + ((r-g) * 60) / (float)delta;
	 *s = (float)delta / (float)b;
	 *v = (float)b * (1.0f/255.0f);
      }
      else {
	 // r>g and r>b //
	 delta = r - MIN(g, b);
	 *h = ((g-b) * 60) / (float)delta;
	 if (*h < 0.0f)
	    *h += 360.0f;
	 *s = (float)delta / (float)r;
	 *v = (float)r * (1.0f/255.0f);
      }
   }
   else {
      if (b > g) {
	 // b>g>=r
	 delta = b-r;
	 *h = 240.0f + ((r-g) * 60) / (float)delta;
	 *s = (float)delta / (float)b;
	 *v = (float)b * (1.0f/255.0f);
      }
      else {
	 // g>=b and g>=r
	 delta = g - MIN(r, b);
	 if (delta == 0) {
	    *h = 0.0f;
	    if (g == 0)
	       *s = *v = 0.0f;
	    else {
	       *s = (float)delta / (float)g;
	       *v = (float)g * (1.0f/255.0f);
	    }
	 }
	 else {
	    *h = 120.0f + ((b-r) * 60) / (float)delta;
	    *s = (float)delta / (float)g;
	    *v = (float)g * (1.0f/255.0f);
	 }
      }
   }
}

/*

// create_rgb_table:
//   Fills an RGB_MAP lookup table with conversion data for the specified
//   palette. This is the faster version by Jan Hubicka.
//
//   Uses alg. similar to floodfill - it adds one seed per every color in
//   palette to its best position. Then areas around seed are filled by
//   same color because it is best approximation for them, and then areas
//   about them etc...
//
//   It does just about 80000 tests for distances and this is about 100
//   times better than normal 256*32000 tests so the calculation time
//   is now less than one second at all computers I tested.

void create_rgb_table(RGB_MAP *table, const SDL_Palette pal, void (*callback)(int pos))
{
   #define UNUSED 65535
   #define LAST 65532

   // macro add adds to single linked list
   #define add(i)    (next[(i)] == UNUSED ? (next[(i)] = LAST, \
		     (first != LAST ? (next[last] = (i)) : (first = (i))), \
		     (last = (i))) : 0)

   // same but w/o checking for first element
   #define add1(i)   (next[(i)] == UNUSED ? (next[(i)] = LAST, \
		     next[last] = (i), \
		     (last = (i))) : 0)

   // calculates distance between two colors
   #define dist(a1, a2, a3, b1, b2, b3) \
		     (col_diff[ ((a2) - (b2)) & 0x7F] + \
		     (col_diff + 128)[((a1) - (b1)) & 0x7F] + \
		     (col_diff + 256)[((a3) - (b3)) & 0x7F])

   // converts r,g,b to position in array and back
   #define pos(r, g, b) \
		     (((r) / 2) * 32 * 32 + ((g) / 2) * 32 + ((b) / 2))

   #define depos(pal, r, g, b) \
		     ((b) = ((pal) & 31) * 2, \
		      (g) = (((pal) >> 5) & 31) * 2, \
		      (r) = (((pal) >> 10) & 31) * 2)

   // is current color better than pal1?
   #define better(r1, g1, b1, pal1) \
		     (((int)dist((r1), (g1), (b1), \
				 (pal1).r, (pal1).g, (pal1).b)) > (int)dist2)

   // checking of position
   #define dopos(rp, gp, bp, ts) \
      if ((rp > -1 || r > 0) && (rp < 1 || r < 61) && \
	  (gp > -1 || g > 0) && (gp < 1 || g < 61) && \
	  (bp > -1 || b > 0) && (bp < 1 || b < 61)) { \
	 i = first + rp * 32 * 32 + gp * 32 + bp; \
         if (!data[i]) { \
	    data[i] = val; \
	    add1(i); \
	 } \
	 else if ((ts) && (data[i] != val)) { \
	    dist2 = (rp ? (col_diff+128)[(r+2*rp-pal[val].r) & 0x7F] : r2) + \
		    (gp ? (col_diff    )[(g+2*gp-pal[val].g) & 0x7F] : g2) + \
		    (bp ? (col_diff+256)[(b+2*bp-pal[val].b) & 0x7F] : b2); \
	    if (better((r+2*rp), (g+2*gp), (b+2*bp), pal[data[i]])) { \
	       data[i] = val; \
	       add1(i); \
	    } \
	 } \
      }

   int i, curr, r, g, b, val, dist2;
   unsigned int r2, g2, b2;
   unsigned short next[32*32*32];
   unsigned char *data;
   int first = LAST;
   int last = LAST;
   int count = 0;
   int cbcount = 0;

   #define AVERAGE_COUNT   18000

   if (col_diff[1] == 0)
      bestfit_init();

   memset(next, 255, sizeof(next));
   memset(table->data, 0, sizeof(char)*32*32*32);

   data = (unsigned char *)table->data;

   // add starting seeds for floodfill
   for (i=1; i<PAL_SIZE; i++) {
      curr = pos(pal[i].r, pal[i].g, pal[i].b);
      if (next[curr] == UNUSED) {
	 data[curr] = i;
	 add(curr);
      }
   }

   // main floodfill: two versions of loop for faster growing in blue axis
   while (first != LAST) {
      depos(first, r, g, b);

      // calculate distance of current color
      val = data[first];
      r2 = (col_diff+128)[((pal[val].r)-(r)) & 0x7F];
      g2 = (col_diff    )[((pal[val].g)-(g)) & 0x7F];
      b2 = (col_diff+256)[((pal[val].b)-(b)) & 0x7F];

      // try to grow to all directions
      dopos( 0, 0, 1, 1);
      dopos( 0, 0,-1, 1);
      dopos( 1, 0, 0, 1);
      dopos(-1, 0, 0, 1);
      dopos( 0, 1, 0, 1);
      dopos( 0,-1, 0, 1);

      // faster growing of blue direction
      if ((b > 0) && (data[first-1] == val)) {
	 b -= 2;
	 first--;
	 b2 = (col_diff+256)[((pal[val].b)-(b)) & 0x7F];

	 dopos(-1, 0, 0, 0);
	 dopos( 1, 0, 0, 0);
	 dopos( 0,-1, 0, 0);
	 dopos( 0, 1, 0, 0);

	 first++;
      }

      // get next from list
      i = first;
      first = next[first];
      next[i] = UNUSED;

      // second version of loop
      if (first != LAST) {
	 depos(first, r, g, b);

	 val = data[first];
	 r2 = (col_diff+128)[((pal[val].r)-(r)) & 0x7F];
	 g2 = (col_diff    )[((pal[val].g)-(g)) & 0x7F];
	 b2 = (col_diff+256)[((pal[val].b)-(b)) & 0x7F];

	 dopos( 0, 0, 1, 1);
	 dopos( 0, 0,-1, 1);
	 dopos( 1, 0, 0, 1);
	 dopos(-1, 0, 0, 1);
	 dopos( 0, 1, 0, 1);
	 dopos( 0,-1, 0, 1);

	 if ((b < 61) && (data[first + 1] == val)) {
	    b += 2;
	    first++;
	    b2 = (col_diff+256)[((pal[val].b)-(b)) & 0x7f];

	    dopos(-1, 0, 0, 0);
	    dopos( 1, 0, 0, 0);
	    dopos( 0,-1, 0, 0);
	    dopos( 0, 1, 0, 0);

	    first--;
	 }

	 i = first;
	 first = next[first];
	 next[i] = UNUSED;
      }

      count++;
      if (count == (cbcount+1)*AVERAGE_COUNT/256) {
	 if (cbcount < 256) {
	    if (callback)
	       callback(cbcount);
	    cbcount++;
	 }
      }
   }

   // only the transparent (pink) color can be mapped to index 0
   if ((pal[0].r == 63) && (pal[0].g == 0) && (pal[0].b == 63))
      table->data[31][0][31] = 0;

   if (callback)
      while (cbcount < 256)
	 callback(cbcount++);
}



// create_light_table:
//  Constructs a lighting color table for the specified palette. At light
//  intensity 255 the table will produce the palette colors directly, and
//  at level 0 it will produce the specified R, G, B value for all colors
//  (this is specified in 0-63 VGA format). If the callback function is
//  not NULL, it will be called 256 times during the calculation, allowing
//  you to display a progress indicator.

void create_light_table(COLOR_MAP *table, const SDL_Palette pal, int r, int g, int b, void (*callback)(int pos))
{
   int r1, g1, b1, r2, g2, b2, x, y;
   unsigned int t1, t2;

   ASSERT(table);
   ASSERT(r >= 0 && r <= 63);
   ASSERT(g >= 0 && g <= 63);
   ASSERT(b >= 0 && b <= 63);

   if (rgb_map) {
      for (x=0; x<PAL_SIZE-1; x++) {
	 t1 = x * 0x010101;
	 t2 = 0xFFFFFF - t1;

	 r1 = (1 << 24) + r * t2;
	 g1 = (1 << 24) + g * t2;
	 b1 = (1 << 24) + b * t2;

	 for (y=0; y<PAL_SIZE; y++) {
	    r2 = (r1 + pal[y].r * t1) >> 25;
	    g2 = (g1 + pal[y].g * t1) >> 25;
	    b2 = (b1 + pal[y].b * t1) >> 25;

	    table->data[x][y] = rgb_map->data[r2][g2][b2];
	 }
      }
      if (callback)
	 (*callback)(x);
   }
   else {
      for (x=0; x<PAL_SIZE-1; x++) {
	 t1 = x * 0x010101;
	 t2 = 0xFFFFFF - t1;

	 r1 = (1 << 23) + r * t2;
	 g1 = (1 << 23) + g * t2;
	 b1 = (1 << 23) + b * t2;

	 for (y=0; y<PAL_SIZE; y++) {
	    r2 = (r1 + pal[y].r * t1) >> 24;
	    g2 = (g1 + pal[y].g * t1) >> 24;
	    b2 = (b1 + pal[y].b * t1) >> 24;

	    table->data[x][y] = bestfit_color(pal, r2, g2, b2);
	 }
      }

      if (callback)
	 (*callback)(x);
   }

   for (y=0; y<PAL_SIZE; y++)
      table->data[255][y] = y;
}



// create_trans_table:
//   Constructs a translucency color table for the specified palette. The
//   r, g, and b parameters specifiy the solidity of each color component,
//   ranging from 0 (totally transparent) to 255 (totally solid). Source
//   color #0 is a special case, and is set to leave the destination
//   unchanged, so that masked sprites will draw correctly. If the callback
//   function is not NULL, it will be called 256 times during the calculation,
//   allowing you to display a progress indicator.

void create_trans_table(COLOR_MAP *table, const SDL_Palette pal, int r, int g, int b, void (*callback)(int pos))
{
   int tmp[768], *q;
   int x, y, i, j, k;
   unsigned char *p;
   int tr, tg, tb;
   int add;

   ASSERT(table);
   ASSERT(r >= 0 && r <= 255);
   ASSERT(g >= 0 && g <= 255);
   ASSERT(b >= 0 && b <= 255);

   // This is a bit ugly, but accounts for the solidity parameters
   //   being in the range 0-255 rather than 0-256. Given that the
   //   precision of r,g,b components is only 6 bits it shouldn't do any
   //   harm.
   if (r > 128)
      r++;
   if (g > 128)
      g++;
   if (b > 128)
      b++;

   if (rgb_map)
      add = 255;
   else
      add = 127;

   for (x=0; x<256; x++) {
      tmp[x*3]   = pal[x].r * (256-r) + add;
      tmp[x*3+1] = pal[x].g * (256-g) + add;
      tmp[x*3+2] = pal[x].b * (256-b) + add;
   }

   for (x=1; x<PAL_SIZE; x++) {
      i = pal[x].r * r;
      j = pal[x].g * g;
      k = pal[x].b * b;

      p = table->data[x];
      q = tmp;

      if (rgb_map) {
	 for (y=0; y<PAL_SIZE; y++) {
	    tr = (i + *(q++)) >> 9;
	    tg = (j + *(q++)) >> 9;
	    tb = (k + *(q++)) >> 9;
	    p[y] = rgb_map->data[tr][tg][tb];
	 }
      }
      else {
	 for (y=0; y<PAL_SIZE; y++) {
	    tr = (i + *(q++)) >> 8;
	    tg = (j + *(q++)) >> 8;
	    tb = (k + *(q++)) >> 8;
	    p[y] = bestfit_color(pal, tr, tg, tb);
	 }
      }

      if (callback)
	 (*callback)(x-1);
   }

   for (y=0; y<PAL_SIZE; y++) {
      table->data[0][y] = y;
      table->data[y][y] = y;
   }

   if (callback)
      (*callback)(255);
}


/*
// create_color_table:
//  Creates a color mapping table, using a user-supplied callback to blend
//  each pair of colors. Your blend routine will be passed a pointer to the
//  palette and the two colors to be blended (x is the source color, y is
//  the destination), and should return the desired output RGB for this
//  combination. If the callback function is not NULL, it will be called
//  256 times during the calculation, allowing you to display a progress
//  indicator.

void create_color_table(COLOR_MAP *table, const SDL_Palette pal, void (*blend)(const SDL_Palette pal, int x, int y, SDL_Color *rgb), void (*callback)(int pos))
{
   int x, y;
   SDL_Color c;

   for (x=0; x<PAL_SIZE; x++) {
      for (y=0; y<PAL_SIZE; y++) {
	 blend(pal, x, y, &c);

	 if (rgb_map)
	    table->data[x][y] = rgb_map->data[c.r>>1][c.g>>1][c.b>>1];
	 else
	    table->data[x][y] = bestfit_color(pal, c.r, c.g, c.b);
      }

      if (callback)
	 (*callback)(x);
   }
}



// create_blender_table:
// Fills the specified color mapping table with lookup data for doing a
// paletted equivalent of whatever truecolor blender mode is currently
// selected.

void create_blender_table(COLOR_MAP *table, const SDL_Palette pal, void (*callback)(int pos))
{
   int x, y, c;
   int r, g, b;
   int r1, g1, b1;
   int r2, g2, b2;

   ASSERT(_blender_func24);

   for (x=0; x<PAL_SIZE; x++) {
      for (y=0; y<PAL_SIZE; y++) {
	 r1 = (pal[x].r << 2) | ((pal[x].r & 0x30) >> 4);
	 g1 = (pal[x].g << 2) | ((pal[x].g & 0x30) >> 4);
	 b1 = (pal[x].b << 2) | ((pal[x].b & 0x30) >> 4);

	 r2 = (pal[y].r << 2) | ((pal[y].r & 0x30) >> 4);
	 g2 = (pal[y].g << 2) | ((pal[y].g & 0x30) >> 4);
	 b2 = (pal[y].b << 2) | ((pal[y].b & 0x30) >> 4);

	 c = _blender_func24(makecol24(r1, g1, b1), makecol24(r2, g2, b2), _blender_alpha);

	 r = getr24(c);
	 g = getg24(c);
	 b = getb24(c);

	 if (rgb_map)
	    table->data[x][y] = rgb_map->data[r>>3][g>>3][b>>3];
	 else
	    table->data[x][y] = bestfit_color(pal, r>>2, g>>2, b>>2);
      }

      if (callback)
	 (*callback)(x);
   }
}

*/
//========BLENDING======(SURFACE)==============

//SDL_Color Colors::makeColor(int r, int g, int b) {
//	SDL_Color teste = {r,g,b};
//	return teste;
//}
Uint32 makeColor( int r, int g, int b ){
	// toda vez que verifica instancia no sdlmanager gera um lock.
	//tentar colocar uma variável local que indica o modo de compatibilidade
	//é fundamental aumentar a performance do makecolor, pois
	//uma grande parte do blender utiliza para cada pixel

	if(!getCompatibilityMode()){

		/*	Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:----------------------------- "<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------Bits  Per Pixel: "<< dec << (int) CSDLManager::GetInstance()->state->surface_format.BitsPerPixel << endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------Bytes Per Pixel: "<< dec << (int) CSDLManager::GetInstance()->state->surface_format.BytesPerPixel<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------RMASK : "<< (int) CSDLManager::GetInstance()->state->surface_format.Rmask<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------GMASK : "<< (int) CSDLManager::GetInstance()->state->surface_format.Gmask<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------BMASK : "<< (int) CSDLManager::GetInstance()->state->surface_format.Bmask<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------RLoss : "<< (int) CSDLManager::GetInstance()->state->surface_format.Rloss<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------GLoss : "<< (int) CSDLManager::GetInstance()->state->surface_format.Gloss<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------BLoss : "<< (int) CSDLManager::GetInstance()->state->surface_format.Bloss<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------RShift: "<< (int) CSDLManager::GetInstance()->state->surface_format.Rshift<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------GShift : "<< (int) CSDLManager::GetInstance()->state->surface_format.Gshift<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = Formato:---------BShift : "<< (int) CSDLManager::GetInstance()->state->surface_format.Bshift<< endl;
			Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor (r,g,b) = ( "<< r <<","<< g <<","<< b <<" )"<< endl;
			*/
		//Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = ( "<< ::SDL_MapRGB(&CSDLManager::GetInstance()->state->surface_format, r, g, b)<<" )"<< endl;
			Uint32 color_pixel;
			color_pixel=SDL_MapRGB(getCurrentPixelFormat(),r,g,b);
			return color_pixel;

	}else {
		//Debug::debug( Debug::error,__FUNCTION__ ) << "makeColor pixel = (( "<< ::SDL_MapRGB(Screen[0]->getBitmap()->format, r, g, b)<<" ))"<< endl;
		return ::SDL_MapRGB(CBitmap::_my_state->Screen[0]->getBitmap()->format, r, g, b);
	}


	return 0;
}

Uint32 makeColor( ColorDefinition color ){

	return makeColor(color.r,color.g,color.b);
}

//a=source pixel
//b=dest pixel
//c=alpha


void blend_palette(  Colors::ColorDefinition * pal, int mp,  Colors::ColorDefinition sc,  Colors::ColorDefinition ec ) {
/*
	//ASSERT( pal );
	//ASSERT( mp != 0 );
    SDL_VideoInfo *info = SDL_GetVideoInfo();
	assert(pal);
	assert (mp !=0);
    */
	int sc_r = sc.r;
	int sc_g = sc.g;
	int sc_b = sc.b;

	int ec_r = ec.r;
	int ec_g = ec.b;
	int ec_b = ec.b;

	for ( int q = 0; q < mp; q++ ) {
		float j = (float)( q + 1 ) / (float)( mp );
		int f_r = (int)( 0.5 + (float)( sc_r ) + (float)( ec_r-sc_r ) * j );
		int f_g = (int)( 0.5 + (float)( sc_g ) + (float)( ec_g-sc_g ) * j );
		int f_b = (int)( 0.5 + (float)( sc_b ) + (float)( ec_b-sc_b ) * j );
		pal[q].r = f_r;
		pal[q].g = f_g;
		pal[q].b = f_b;
		//pal[q] = SDL_MapRGB( info->vfmt  ,f_r, f_g, f_b);
	}

}





/*
 * Return the pixel value at (x, y)
funcionando ok
 */

Uint32 getPixel(SDL_Surface *bmp, const int x,const  int y) {

	int bpp = bmp->format->BytesPerPixel;
	if (SDL_MUSTLOCK(bmp))
      SDL_LockSurface(bmp);

	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *) bmp->pixels + y * bmp->pitch + x * bpp;

	switch (bpp) {
	case 1:
		if (SDL_MUSTLOCK(bmp))
      SDL_LockSurface(bmp);
		return *p;
	case 2:
		if (SDL_MUSTLOCK(bmp))
      SDL_LockSurface(bmp);
		return *(Uint16 *) p;
	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			if (SDL_MUSTLOCK(bmp))
            SDL_LockSurface(bmp);
			return p[0] << 16 | p[1] << 8 | p[2]; }
		else {
			if (SDL_MUSTLOCK(bmp))
            SDL_LockSurface(bmp);
			return p[0] | p[1] << 8 | p[2] << 16; }
	case 4:
		if (SDL_MUSTLOCK(bmp))
        SDL_LockSurface(bmp);
		return *(Uint32 *) p;
	default:
		if (SDL_MUSTLOCK(bmp))
        SDL_LockSurface(bmp);
		return 0;	/* shouldn't happen, but avoids warnings */
	}
}
//Todo: Use replace32 to get speed
void replaceColorSurface(SDL_Surface *bmp, int original, int replaced){
	for (int x = 0; x < bmp->w; x++){
        for (int y = 0; y < bmp->h; y++){
	    int pixel = getPixel(bmp,x, y);
		if (pixel==original){
            putPixelSurface(bmp,x, y, replaced);
		}
        }
    }


	//replace32(getBitmap(), original, replaced);
}

/*
 * Set the pixel at (x, y) to the given value
  */
void putPixelSurface(SDL_Surface *bmp, int x, int y, Uint32 pixel, bool translucent) {

	int bpp = bmp->format->BytesPerPixel;
	if (SDL_MUSTLOCK(bmp))
      SDL_LockSurface(bmp);

	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *) bmp->pixels + y * bmp->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;
	case 2:
		if (translucent){
			*(Uint16 *)p = Colors::globalBlend.currentBlender(pixel, *(Uint16*)p, Colors::globalBlend.alpha);
            } else {
                *(Uint16 *)p = pixel;
            }
		break;
	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;
	case 4:
		if (translucent){
			*(Uint32 *)p = Colors::globalBlend.currentBlender(pixel, *(Uint32*)p, Colors::globalBlend.alpha);
            } else {
                *(Uint32 *) p = pixel;
            }

		break;
	default:
		break;
	}
	if (SDL_MUSTLOCK(bmp))
		::SDL_UnlockSurface(bmp);
}


void putPixelSurface(SDL_Surface *bmp, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
	Uint32 pixel = makeColor(r,g,b);
	putPixelSurface(bmp, x, y, pixel);

}



void putPixelTexture( SDL_Texture *mytexture, int x, int y, Uint8 r, Uint8 g, Uint8 b){

	Uint32 pixel = Colors::makeColor(r,g,b);
	putPixelTexture(mytexture, x, y, pixel);

}

/*
 * Set the pixel at (x, y) to the given value
  */
// solução de colocar pixels na surface: http://slouken.blogspot.com/2011/02/streaming-textures-with-sdl-13.html
void putPixelTexture(SDL_Texture *mytexture, int x, int y, Uint32 pixel, bool translucent){
	//SDL_Surface *bmp = getBitmap();
	int w,h;
	w=mytexture->w;
	h=mytexture->h;
	SDL_Surface *bmp = SDL_CreateRGBSurfaceFrom(NULL,
                                  w, h,
                                   32, 0,
                                   0x00FF0000,
                                   0x0000FF00,
                                   0x000000FF,
                                   0xFF000000);

	SDL_LockTexture(mytexture, NULL,
                &bmp->pixels,
                &bmp->pitch);

	int bpp = bmp->format->BytesPerPixel;
	if (SDL_MUSTLOCK(bmp))
      SDL_LockSurface(bmp);

	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *) bmp->pixels + y * bmp->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;
	case 2:
		if (translucent){
			*(Uint16 *)p = Colors::globalBlend.currentBlender(pixel, *(Uint16*)p, Colors::globalBlend.alpha);
            } else {
                *(Uint16 *)p = pixel;
            }
		break;
	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;
	case 4:
		if (translucent){
			*(Uint32 *)p = Colors::globalBlend.currentBlender(pixel, *(Uint32*)p, Colors::globalBlend.alpha);
            } else {
                *(Uint32 *) p = pixel;
            }

		break;
	default:
		break;
	}
	if (SDL_MUSTLOCK(bmp))
		::SDL_UnlockSurface(bmp);

	SDL_UnlockTexture(mytexture);
}

/*
void putPixelTexture(SDL_Texture *texture, int x, int y, SDL_Color cor)
{
         SDL_Color *color;
		 color->r= cor.r;
		 color->g= cor.g;
		 color->b= cor.b;
         Uint8 *src;
         Uint32 *dst;
         int row=y;
		 int col=x;
         void *pixels;
         int pitch;

         if (SDL_LockTexture(texture, NULL, &pixels, &pitch) < 0) {
             fprintf(stderr, "Couldn't lock texture: %s\n", SDL_GetError());
             //quit(5);
         }

         *dst++ = (0xFF000000|(color->r<<16)|(color->g<<8)|color->b);
         SDL_UnlockTexture(texture);
}
*/

/** @fn SDL_PixelFormat * getPixelFormat2()
@brief Retorna uma extrutura SDL_PixelFormat preenchida
@warning Esta função não é mais usada desde que sdl 1.3 possui SDL_AllocFormat .
@warning Lembrar de deletar o formato depois de usá-lo, ou haverá memory leak
**/


SDL_PixelFormat * getPixelFormat2(){
static SDL_PixelFormat formato;
memset(&formato,0,sizeof(formato));
	Debug::debug(Debug::bitmap,__FUNCTION__) << "--------------"<<endl;

    int bpp;
	Uint32 Rmask,Gmask,Bmask,Amask;
	if(!getCompatibilityMode()){
		int n = SDL_GetNumVideoDisplays();
		if (n>1) {
			Debug::debug(Debug::bitmap,__FUNCTION__) <<"Assuming display number 1 from "<< n<<endl;
		}
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);
		if(SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask, &Gmask, &Bmask, &Amask)>0) {
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Current mode:   "<< SDL_GetCurrentVideoDriver()<<endl;
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Width:          "<< mode.w <<endl;
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Height:	        "<< mode.h <<endl;
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Refr. Rate:     "<< mode.refresh_rate << " Hz"<<endl;
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Bits per pixel: "<< bpp <<endl;
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Pixel Format:   "<< CSDLManager::PixelFormatToString(mode.format) <<endl;
				Debug::debug(Debug::bitmap,__FUNCTION__) <<"Pixel Format:   "<< mode.format <<endl;
				
			if (Rmask || Gmask || Bmask) {
                   Debug::debug(Debug::bitmap,__FUNCTION__) <<"Red Mask:   "<<  Rmask <<endl;
					Debug::debug(Debug::bitmap,__FUNCTION__) <<"Green Mask:   "<<  Gmask <<endl;
					Debug::debug(Debug::bitmap,__FUNCTION__) <<"Blue Mask:   "<<  Bmask <<endl;
					
					//fprintf(stderr, "      Red Mask   = 0x%.8x\n", Rmask);
                    //fprintf(stderr, "      Green Mask = 0x%.8x\n", Gmask);
                    //fprintf(stderr, "      Blue Mask  = 0x%.8x\n", Bmask);
                    if (Amask)
                       Debug::debug(Debug::bitmap,__FUNCTION__) <<"Alpha Mask:   "<<  Amask <<endl;
						//fprintf(stderr, "      Alpha Mask = 0x%.8x\n", Amask);
                }
			SDL_InitFormat(formato,bpp,Rmask, Gmask, Bmask, Amask);
			//SDL_InitFormat(&formato,mode.format);
		return &formato;
		}else {
			//Debug::debug(Debug::bitmap,__FUNCTION__) << "CBitmap::GetPixelFormat() Failed: " <<SDL_GetError()<<endl;

		return NULL;
		}
	}
    return NULL;
}


SDL_PixelFormat &
SDL_InitFormat(SDL_PixelFormat & format, int bpp, Uint32 Rmask, Uint32 Gmask,
               Uint32 Bmask, Uint32 Amask)
{
 /*  Debug::debug(Debug::bitmap,__FUNCTION__) << "--------------------------" <<  endl;
   Debug::debug(Debug::bitmap,__FUNCTION__) << "bpp: " << bpp <<  endl;
   Debug::debug(Debug::bitmap,__FUNCTION__) << "Rmask: "<< Rmask <<  endl;
   Debug::debug(Debug::bitmap,__FUNCTION__) << "Gmask: " <<Gmask <<  endl;
   Debug::debug(Debug::bitmap,__FUNCTION__) << "Bmask: " <<Bmask <<  endl;
   Debug::debug(Debug::bitmap,__FUNCTION__) << "Amask: " <<Amask <<  endl;
	*/
	Uint32 mask;

    /* Set up the format */
    SDL_zerop(&format);
    format.BitsPerPixel = bpp;
    format.BytesPerPixel = (bpp + 7) / 8;
    if (Rmask || Bmask || Gmask) {      /* Packed pixels with custom mask */
        format.Rshift = 0;
        format.Rloss = 8;
        if (Rmask) {
            for (mask = Rmask; !(mask & 0x01); mask >>= 1)
                ++format.Rshift;
            for (; (mask & 0x01); mask >>= 1)
                --format.Rloss;
        }
        format.Gshift = 0;
        format.Gloss = 8;
        if (Gmask) {
            for (mask = Gmask; !(mask & 0x01); mask >>= 1)
                ++format.Gshift;
            for (; (mask & 0x01); mask >>= 1)
                --format.Gloss;
        }
        format.Bshift = 0;
        format.Bloss = 8;
        if (Bmask) {
            for (mask = Bmask; !(mask & 0x01); mask >>= 1)
                ++format.Bshift;
            for (; (mask & 0x01); mask >>= 1)
                --format.Bloss;
        }
        format.Ashift = 0;
        format.Aloss = 8;
        if (Amask) {
            for (mask = Amask; !(mask & 0x01); mask >>= 1)
                ++format.Ashift;
            for (; (mask & 0x01); mask >>= 1)
                --format.Aloss;
        }
        format.Rmask = Rmask;
        format.Gmask = Gmask;
        format.Bmask = Bmask;
        format.Amask = Amask;
    } else if (bpp > 8) {       /* Packed pixels with standard mask */
        /* R-G-B */
        if (bpp > 24)
            bpp = 24;
        format.Rloss = 8 - (bpp / 3);
        format.Gloss = 8 - (bpp / 3) - (bpp % 3);
        format.Bloss = 8 - (bpp / 3);
        format.Rshift = ((bpp / 3) + (bpp % 3)) + (bpp / 3);
        format.Gshift = (bpp / 3);
        format.Bshift = 0;
        format.Rmask = ((0xFF >> format.Rloss) << format.Rshift);
        format.Gmask = ((0xFF >> format.Gloss) << format.Gshift);
        format.Bmask = ((0xFF >> format.Bloss) << format.Bshift);
    } else {
        /* Palettized formats have no mask info */
        format.Rloss = 8;
        format.Gloss = 8;
        format.Bloss = 8;
        format.Aloss = 8;
        format.Rshift = 0;
        format.Gshift = 0;
        format.Bshift = 0;
        format.Ashift = 0;
        format.Rmask = 0;
        format.Gmask = 0;
        format.Bmask = 0;
        format.Amask = 0;
    }
    format.palette = NULL;

    return format;
}


void UpdateTextureFromBuffer(SDL_Texture *texture, SDL_Color ** PixelBuffer)
{
         SDL_Color *color;
         //Uint8 *src;
         Uint32 *dst;
         int row, col;
         void *pixels;
         int pitch;

         if (SDL_LockTexture(texture, NULL, &pixels, &pitch) < 0) {
             fprintf(stderr, "Couldn't lock texture: %s\n", SDL_GetError());
             //quit(5);
         }
         //src = PixelBuffer;
         for (row = 0; row < texture->h; ++row) {
             dst = (Uint32*)((Uint8*)pixels + row * pitch);
             for (col = 0; col < texture->w; ++col) {
                 color = &PixelBuffer[row][col];
                 *dst++ = (0xFF000000|(color->r<<16)|(color->g<<8)|color->b);
             }
         }
         SDL_UnlockTexture(texture);
}

int addColor( ColorDefinition color1, ColorDefinition color2 ){
	return Colors::makeColor( clamp(color1.r + color2.r),
		clamp(color1.g + color2.g),
		clamp(color1.b + color2.b ));
}

int addColor( int color1, int color2 ){
	return Colors::makeColor( clamp(getRed( color1 ) + getRed( color2 )),
		clamp(getGreen( color1 ) + getGreen( color2 )),
		clamp(getBlue( color1 ) + getBlue( color2 ) ));
}


Uint32 darken( int color, double factor ){

	int r = clamp((int)((double)getRed( color ) / factor));
	int g = clamp((int)((double)getGreen( color ) / factor));
	int b = clamp((int)((double)getBlue( color ) / factor));
	return makeColor( r, g, b );
}


/* taken from the color addon from allegro 4.9 */
void al_color_cmyk_to_rgb(float cyan, float magenta, float yellow, float key, float *red, float *green, float *blue){
    float max = 1 - key;
    *red = clamp(max - cyan * max);
    *green =clamp( max - magenta * max);
    *blue = clamp(max - yellow * max);
}

void cymkToRGB(int c, int y, int m, int k, int * r, int * g, int * b){
    float fc = (float)c / 255.0;
    float fy = (float)y / 255.0;
    float fm = (float)m / 255.0;
    float fk = (float)k / 255.0;

    float fr, fg, fb;
    al_color_cmyk_to_rgb(fc, fm, fy, fk, &fr, &fg, &fb);
    *r = (int)(fr * 255.0);
    *g = (int)(fg * 255.0);
    *b = (int)(fb * 255.0);
}

string toString( const SDL_PixelFormat & format ) throw()
{

	string result = "Pixel format description "
		"(masks are binary masks used to retrieve individual color values, "
		"loss is the precision loss of each color component, "
		"shift correspond to binary left shifts of each "
		"color component in the pixel value): " ;

	list<string> l ;

	l.push_back( Util::toNumericalString( format.BitsPerPixel )
		+ " bits per pixel." ) ;

	l.push_back( Util::toNumericalString( format.BytesPerPixel )
		+ " bytes per pixel." ) ;

	if ( format.palette )
		l.push_back( "Palette available." ) ;
	else
		l.push_back( "No palette used." ) ;


	l.push_back( "Rmask is " + Util::toString( format.Rmask, true ) + "." ) ;
	l.push_back( "Gmask is " + Util::toString( format.Gmask, true) + "." ) ;
	l.push_back( "Bmask is " + Util::toString( format.Bmask, true ) + "." ) ;
	l.push_back( "Amask is " + Util::toString( format.Amask, true ) + "." ) ;

	l.push_back( "Rshift is "
		+ Util::toNumericalString( format.Rshift ) + "." ) ;

	l.push_back( "Gshift is "
		+ Util::toNumericalString( format.Gshift ) + "." ) ;

	l.push_back( "Bshift is "
		+ Util::toNumericalString( format.Bshift ) + "." ) ;

	l.push_back( "Ashift is "
		+ Util::toNumericalString( format.Ashift ) + "." ) ;

	l.push_back( "Rloss is "
		+ Util::toNumericalString( format.Rloss ) + "." ) ;

	l.push_back( "Gloss is "
		+ Util::toNumericalString( format.Gloss ) + "." ) ;

	l.push_back( "Bloss is "
		+ Util::toNumericalString( format.Bloss ) + "." ) ;

	l.push_back( "Aloss is "
		+ Util::toNumericalString( format.Aloss ) + "." ) ;


	return result + Util::formatStringList( l ) ;

}



string toString( PixelColor pixel, const SDL_PixelFormat & format ) throw()
{
	ColorDefinition pixColor;
	SDL_GetRGBA( pixel, const_cast<SDL_PixelFormat *>( & format ),
		& pixColor.r, & pixColor.g, & pixColor.b, & pixColor.a ) ;
	return "Pixel whose color definition is "
		+ toString(pixColor ) ;

}

string toString( PixelColor pixel) throw()
{
	ColorDefinition pixColor;
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);
	SDL_GetRGBA( pixel, SDL_AllocFormat(mode.format),
		& pixColor.r, & pixColor.g, & pixColor.b, & pixColor.a ) ;
	return "Pixel whose color definition is "
		+ toString(pixColor ) ;

}

string toString( ColorDefinition color ) throw()
{

	string result = "[R;G;B;A] = [ "
			+ Util::toNumericalString( color.r ) + " ; "
			+ Util::toNumericalString( color.g ) + " ; "
			+ Util::toNumericalString( color.b ) + " ; "
			+ Util::toNumericalString( color.a ) + " ] " ;

	if ( Util::CTextDisplayable::GetOutputFormat()
		== Util::CTextDisplayable::html )
	{

		string hexcolor = Util::toHexString( color.r,
				/* prefix */ false, /* minDigits */ 2 )
			+ Util::toHexString( color.g ,
				/* prefix */ false, /* minDigits */ 2 )
			+ Util::toHexString( color.b ,
				/* prefix */ false, /* minDigits */ 2 ) ;

		/*
		 * Some characters have to be displayed so that the HTML table
		 * cell is drawn:
		 *
		 */
		result += "<table><tr><td style=\"background: #"
			+ hexcolor + "; color: #"
			+ hexcolor + "\">OSDL rocks !</td></tr></table>" ;

	}

	return result ;

}



}

} //end namespace SGF