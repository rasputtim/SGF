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

#ifndef _trans_bitmap_h
#define _trans_bitmap_h

#include "../SGF_Config.h"
#include "SGF_Bitmap.h"
#include "SGF_Color.h"

namespace SGF {

class CFilter;
/**
 * \class CTranslucentBitmap
 *
 * \ingroup SGF_Graphics
 * 
 * \brief bitmap Translucido
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CTranslucentBitmap: public CBitmap {
public:
    CTranslucentBitmap(const CBitmap & b);
    CTranslucentBitmap();
    virtual ~CTranslucentBitmap();

    virtual void putPixelNormal(int x, int y, int col) const;
    virtual void roundRect(int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color) const;
	virtual void roundRectFill(int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color) const;
	virtual void rectangleFill(int x1, int y1, int x2, int y2, int color) const;
	virtual void rectangleFill(int x1, int y1, int x2, int y2, Colors::ColorDefinition color) const;
    virtual void rectangle(int x1, int y1, int x2, int y2, int color) const;
	virtual void rectangle(int x1, int y1, int x2, int y2, Colors::ColorDefinition color) const;
    virtual void fill(int color);
    virtual void hLine( const int x1, const int y, const int x2, const int color ) const;
	virtual void hLine( const int x1, const int y, const int x2, const Colors::ColorDefinition color ) const;
    virtual void circleFill( int x, int y, int radius, int color ) const;

    //!NEW to IMPLEMENT
    virtual void ellipse( int x, int y, int rx, int ry, int color ) const;

	using CBitmap::draw;
    virtual void draw(const int x, const int y, const CBitmap & where) const;
    virtual void draw(const int x, const int y, CFilter * filter, const CBitmap & where) const;
    // virtual void draw(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, const Bitmap & where) const;
    // virtual void draw(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, Filter * filter, const Bitmap & where) const;

    using CBitmap::drawHFlip;
    virtual void drawHFlip(const int x, const int y, const CBitmap & where) const;
    virtual void drawHFlip(const int x, const int y, CFilter * filter, const CBitmap & where) const;
    // virtual void drawHFlip(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, const Bitmap & where) const;
    // virtual void drawHFlip(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, Filter * filter, const Bitmap & where) const;
    virtual void drawVFlip( const int x, const int y, const CBitmap & where ) const;
    virtual void drawVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const;
    virtual void drawHVFlip( const int x, const int y, const CBitmap & where ) const;
    virtual void drawHVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const;

};
} //end namespace SGF
#endif
