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
#ifndef _S_G_F_lit_bitmap_h
#define _S_G_F_lit_bitmap_h
#include "../SGF_Config.h"
#include "SGF_Bitmap.h"


namespace SGF {
/**
 * \class LitBitmap
 *
 * \ingroup SGF_Graphics
 * 
 * \brief Bitmap Iluminado (lit)
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API LitBitmap: public CBitmap {
public:
	LitBitmap( const CBitmap & b );
	LitBitmap();
	virtual ~LitBitmap();

        using CBitmap::draw;
	virtual void draw( const int x, const int y, const CBitmap & where ) const;
        using CBitmap::drawHFlip;
	virtual void drawHFlip( const int x, const int y, const CBitmap & where ) const;
	virtual void drawVFlip( const int x, const int y, const CBitmap & where ) const;
	virtual void drawHVFlip( const int x, const int y, const CBitmap & where ) const;
};
} //end namespace SGF
#endif
