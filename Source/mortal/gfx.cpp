/***************************************************************************
                          gfx.cpp  -  description
                             -------------------
    begin                : Tue Apr 10 2001
    copyright            : (C) 2001 by UPi
    email                : upi@apocalypse.rulez.org
 ***************************************************************************/

#include <string.h>
#include <malloc.h>
#include <fstream>
#include <iostream>

#include "SDL.h"
#include "SDL_video.h"
#include "../../ExternalLibs/SDL2_image-2.0.0/SDL_image.h"
#include "util/SGF_Debug.h"
#include "graphics/SGF_Color.h"
#include "graphics/SGF_Bitmap.h"
#include "mortal/gfx.h"
#include "util/SGF_Util.h"
#include "graphics/SGF_GradientEffect.h"

//#include "Event.h"


namespace SGF {

static int SDL_SetPaletteColors(SDL_Palette * palette, const SDL_Color * colors, int firstcolor, int ncolors)
{
    int status = 0;

    /* Verify the parameters */
    if (!palette) {
        return -1;
    }
    if (ncolors > (palette->ncolors - firstcolor)) {
        ncolors = (palette->ncolors - firstcolor);
        status = -1;
    }

    if (colors != (palette->colors + firstcolor)) {
        SDL_memcpy(palette->colors + firstcolor, colors,
                   ncolors * sizeof(*colors));
    }
    ++palette->version;
    if (!palette->version) {
        palette->version = 1;
    }

    return status;
}

int
SetColors(SDL_Surface * surface, const SDL_Color * colors, int firstcolor, int ncolors)
{
    if (SGF::SDL_SetPaletteColors
        (surface->format->palette, colors, firstcolor, ncolors) == 0) {
        return 1;
    } else {
        return 0;
    }
}

Uint16 *UTF8_to_UNICODE(Uint16 *unicode, const char *utf8, int len);


SDL_Color MakeColor( Uint8 r, Uint8 g, Uint8 b )
{
	SDL_Color color;
	color.r = r; color.g = g; color.b = b; color.a = 0;
	return color;
}




CBitmap* LoadBackground( const char* a_pcFilename, int a_iNumColors, int a_iPaletteOffset, bool a_bTransparent )
{
	/*
	char acFilepath[FILENAME_MAX+1];
	strcpy( acFilepath, DATADIR );
	strcat( acFilepath, "/gfx/" );
	strcat( acFilepath, a_pcFilename );
	*/

	CBitmap* poBackground = new CBitmap( a_pcFilename );
	if (!poBackground)
	{
		Debug::debug(Debug::error,__FUNCTION__) << "Can't load file: "<< a_pcFilename <<endl;
		return NULL;
	}
	
	
	SDL_Palette* pal = poBackground->getBitmap()->format->palette;
	if ( pal && CBitmap::_my_state->Screen[0]->getBitmap()->format->palette )
	{
		int ncolors = pal->ncolors;
		if (ncolors>a_iNumColors) ncolors = a_iNumColors;
		if (ncolors+a_iPaletteOffset > 255) ncolors = 255 - a_iPaletteOffset;
		SetColors( CBitmap::_my_state->Screen[0]->getBitmap(), pal->colors, a_iPaletteOffset, ncolors );
	}
	
	//SDL_Surface* poRetval = SDL_DisplayFormat( poBackground );
	//SDL_FreeSurface( poBackground );
	
	// 2. TRY TO LOAD AN IMAGE MASK
	// This means trying to load a .png file which acts as a mask for the
	// original [jpg] image.
	// If the original file is <Basename>.jpg, the mask is <Basename>.mask.png
	
	int iLength = strlen( a_pcFilename );
	char acMaskFilename[FILENAME_MAX+1];
	strncpy( acMaskFilename, a_pcFilename, iLength-4 );
	acMaskFilename[iLength-4] = 0;
	strcat( acMaskFilename, ".mask.png" );
	
	SDL_Surface* poMask = IMG_Load( acMaskFilename );
	if ( !poMask )
	{
		// No mask.
		return poBackground;
	}
	
	if ( poMask->w < poBackground->getWidth()
		|| poMask->h < poBackground->getHeight() )
	{
		Debug::debug(Debug::error,__FUNCTION__) << "Error loading mask for -  mask is too small:" << a_pcFilename <<endl;
		SDL_FreeSurface( poMask );
		return poBackground;
	}
	
	Debug::debug(Debug::error,__FUNCTION__) << "Loading mask for: "<< a_pcFilename <<endl;
	
	Uint32 iTransparent = Colors::makeColor( 255, 217, 0 ); // an unlikely color in openmortal..
	Uint32 iMask = Colors::getPixel( poMask, 0, 0 );
	Uint32 iPixel;
	
	for ( int y = 0; y < poBackground->getHeight(); ++y ) {
		for ( int x=0; x< poBackground->getWidth(); ++x ) {
			iPixel = Colors::getPixel( poMask, x, y );
//			Debug::debug(Debug::error,__FUNCTION__) << "Pixel "<< iPixel <<endl;
			if ( iPixel == iMask ) { 
				Colors::putPixelSurface( poBackground->getBitmap(), x, y, iTransparent );
			}
		}
//		Debug::debug(Debug::error,__FUNCTION__) << "\n" );
	}
	
	SDL_FreeSurface( poMask );
	
	//SDL_SetColorKey( poBackground, SDL_TRUE, iTransparent );
	poBackground->applyTrans( iTransparent);
	return poBackground;
}

#if  0
bool SetVideoMode( bool a_bLarge, bool a_bFullScreen, int a_iAdditionalFlags )
{
	// SET THE PARAMETERS FOR THE VIDEO MODE

	int iBpp = 16;		// Try the display's BPP first.
	if ( NULL != gamescreen )
	{
		iBpp = gamescreen->getBitmap()->format->BitsPerPixel;
	}

	int iFlags = a_iAdditionalFlags;
	//Todo solve Fullscreen
	if ( a_bFullScreen )
	{
		//iFlags |= SDL_FULLSCREEN;
	}

	// CALL SDL_SetVideoMode

	int iWidth = a_bLarge ? 800 : 640;
	int iHeight = a_bLarge ? 600 : 480;
//	if ( !a_bFullScreen ) iHeight = 480;

	CBitmap *gamescreen = CBitmap::_my_state->Screen[0]; //.SDL_SetVideoMode( iWidth, iHeight, iBpp, iFlags );
	
	if ( NULL == gamescreen ) 
	{
		Debug::debug(Debug::error,__FUNCTION__) << "SDL_SetVideoMode( W, H, Bpp,Flags ) failed [ " << iWidth<<" , " << iHeight<<" , "<< iBpp<<" , "<< iFlags<<" ]"<<endl;
		return false;
	}

	// IF THE DISPLAY IS 24BPP OR 8 BPP OR LESS, EMULATE 16 BPP INSTEAD
	// (because we are lazy and won't write 8bpp and 24bpp code anymore)
/*
	if ( gamescreen->format->BytesPerPixel != 2
		&& gamescreen->format->BytesPerPixel != 4 )
	{
		//gamescreen = SDL_SetVideoMode( iWidth, iHeight, 16, iFlags );
		gamescreen = CBitmap::_my_state->Screen[0]; //.SDL_SetVideoMode( iWidth, iHeight, iBpp, iFlags );
	
		if ( NULL == gamescreen )
		{
			Debug::debug(Debug::error,__FUNCTION__) << "SDL_SetVideoMode( %d, %d, %d, %d ) failed [ "<< iWidth<<" , " << iHeight<<" , "<< 16<<" , "<< iFlags<<" ]"<<endl;
				return false;
		}
	}
	*/
	return true;
}
#endif
} // end SGF