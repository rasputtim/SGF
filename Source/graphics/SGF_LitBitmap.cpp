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
#include "graphics/SGF_LitBitmap.h"
namespace SGF {
LitBitmap::LitBitmap( const CBitmap & b ):
CBitmap( b ){
}

LitBitmap::LitBitmap():
CBitmap(){
}

LitBitmap::~LitBitmap(){
}

void LitBitmap::draw( const int x, const int y, const CBitmap & where ) const {
	///The basic drawing operation assumes the default transparency color (255,0,255) in the sprite bitmap:
	// ::draw_sprite_ex( where.getBitmap(), getBitmap(), x, y, SPRITE_LIT );
	// ::draw_sprite( where.getBitmap(), getBitmap(), x, y );
	// CBitmap::draw( x, y, where );
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	CBitmap::draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_LIT, CBitmap::SPRITE_NO_FLIP,NULL ,mask);
}

void LitBitmap::drawHFlip( const int x, const int y, const CBitmap & where ) const {
	//CBitmap::draw( x, y, where );
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_LIT, CBitmap::SPRITE_H_FLIP,NULL,mask);
}

void LitBitmap::drawVFlip( const int x, const int y, const CBitmap & where ) const {
	//CBitmap::draw( x, y, where );
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_LIT, CBitmap::SPRITE_V_FLIP,NULL,mask);
}

void LitBitmap::drawHVFlip( const int x, const int y, const CBitmap & where ) const {
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	//CBitmap::draw( x, y, where );
	CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_LIT, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP,NULL,mask);
}


} //end namespace SGF