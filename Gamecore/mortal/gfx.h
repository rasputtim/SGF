/***************************************************************************
                          gfx.h  -  description
                             -------------------
    begin                : Tue Apr 10 2001
    copyright            : (C) 2001 by UPi
    email                : upi@apocalypse.rulez.org
 ***************************************************************************/


#ifndef _MORTAL_GFXX_H
#define _MORTAL_GFXX_H

#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "util/SGF_FontSystem.h"


namespace SGF{

SDL_Color MakeColor( Uint8 r, Uint8 g, Uint8 b );

int SetColors(SDL_Surface * surface, const SDL_Color * colors, int firstcolor,int ncolors);
CBitmap* LoadBackground( const char* a_pcFilename, int a_iNumColors, int a_iPaletteOffset=0, bool a_bTransparent = false );

} //end SGF


#endif
