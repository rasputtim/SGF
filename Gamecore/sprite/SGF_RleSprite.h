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

#ifndef __SGF_RLESPRITE_H
#define __SGF_RLESPRITE_H

#include "../../ExternalLibs/SDL2/include/SDL.h"
//#include "graphics/SGF_Bitmap.h"

namespace SGF {

class CBitmap;

	/** The TintEnum contains values that can be passed to RlePack::SetTint.

The tint is some modification of the original palette of an RlePack. This
is used for two things:

\li In case both players choose the same fighter, player 2's fighter is
tinted so they won't get confused.
\li Some special effects (e.g. frozen) make the fighter tinted as well.

The Tint of players is stored by PlayerSelect and applied by RlePack::SetTint().
*/
enum TintEnum {
	NO_TINT = 0,
	ZOMBIE_TINT,
	GRAY_TINT,
	DARK_TINT,
	INVERTED_TINT,
	FROZEN_TINT,
};

typedef struct RLE_SPRITE           /* a RLE compressed sprite */
{
	Uint16 dummy;					// For better alignment... NASTY NASTY HACK!!
	Uint16 color_depth;                 /* color depth of the image */
	Uint16 w, h;                        /* width and height in pixels */
	Uint32 size;
	signed char dat[0];
} RLE_SPRITE;


struct RlePack_P
{
	SDL_Color		m_aoPalette[256];
	SDL_Color		m_aoTintedPalette[256];
	TintEnum		m_enTint;
	int				m_iCount;
	int				m_iArraysize;
	RLE_SPRITE**	m_pSprites;
	void*			m_pData;

	int				m_iColorCount;
	int				m_iColorOffset;
	Uint32			m_aiRGBPalette[256];

	void			draw_rle_sprite8(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite_v_flip8(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite16( SDL_Surface* dst,RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite_v_flip16(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite24(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite_v_flip24(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite32(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
	void			draw_rle_sprite_v_flip32(SDL_Surface* dst, RLE_SPRITE* a_poSprite, int a_dx, int a_dy );
};



/**
\class CRleSprite
\brief CRleSprite is responsible for loading and drawing "sprites" from a .DAT file.

CRleSprite loads the sprites from a .DAT file in its constructor. If there is
an error (e.g. file doesn't exist), the number of sprites loaded will be 0.

The palette by default ranges from 1 to N (the number of colors). This,
however, can be changed with OffsetSprites(). This is used to make sure that
the two loaded fighters don't overwrite each others palettes or the background
palette.

The 'tint' can be set with the SetTint method. It will not immediately appear
until ApplyPalette() is called. For an explanation about tints, please see the
TintEnum documentation.

\sa TintEnum
*/

class CRleSprite
{

public:
	CRleSprite( const char* a_pcFilename, int a_iNumColors );
	~CRleSprite();

	void		Clear();
	int			LoadFile( const char* a_pcFilename, int a_iNumColors );
	int			Count();
	void		OffsetSprites( int a_iOffset );
	void		SetTint( TintEnum a_enTint );
	void		ApplyPalette();

	int			GetWidth( int a_iIndex );
	int			GetHeight( int a_iIndex );
	void		Draw(CBitmap* dst, int a_iIndex, int a_iX, int a_iY, bool a_bFlipped=false );
	CBitmap* CreateBitmap( int a_iIndex, bool a_bFlipped=false );

private:
	RlePack_P*	my_data;
};
} //End SGF
#endif
