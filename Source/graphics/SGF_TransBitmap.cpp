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

#include "graphics/SGF_TransBitmap.h"
#include "graphics/SGF_Poligon.h"
#include "util/SGF_Debug.h"

using namespace std;
//====================  TRANSLUCENT ==============
namespace SGF {
//translucent bitmap usa o transpblender para controlar a transparencia do objeto gerado
CTranslucentBitmap CBitmap::translucent() const {
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Creating  translucent bitmap: "<< endl;
    return CTranslucentBitmap(*this);
}

CTranslucentBitmap CBitmap::translucent(int red, int green, int blue, int alpha) const {
    transBlender(red, green, blue, alpha);
    return CTranslucentBitmap(*this);
}
CTranslucentBitmap::CTranslucentBitmap(const CBitmap & b):
CBitmap(b){
    int x1, y1, x2, y2;
    b.getSurfaceClipRect(x1, y1, x2, y2);
    setSurfaceClipRect(x1, y1, x2, y2);
	b.setDrawBlendMode(CBitmap::MODE_TRANS);
}

CTranslucentBitmap::CTranslucentBitmap():
CBitmap(){
}

CTranslucentBitmap::~CTranslucentBitmap(){
}

void CTranslucentBitmap::fill(int color) {
    CBitmap::fill(color);
}

void CTranslucentBitmap::ellipse( int x, int y, int rx, int ry, int color ) const {
	int alpha = Colors::globalBlend.alpha;
	this->polygon().ellipse(x,y,rx,ry,color,alpha);
	//SPG_EllipseBlend(getBitmap(), x, y, rx, ry, color, alpha);
}

void CTranslucentBitmap::circleFill(int x, int y, int radius, int color) const {
    int alpha = Colors::globalBlend.alpha;
	CBitmap::polygon().circleFill(x,y,radius,color,alpha);
	//SPG_CircleFilledBlend(getBitmap(), x, y, radius, color, alpha);
}

void CTranslucentBitmap::hLine( const int x1, const int y, const int x2, const int color ) const {
    int alpha = Colors::globalBlend.alpha;
	this->polygon().hline(x1,y,x2,color,alpha);
    //SPG_LineHBlend(getBitmap(), x1, y, x2, color, alpha);
}
void CTranslucentBitmap::hLine( const int x1, const int y, const int x2, const Colors::ColorDefinition color ) const {
    int alpha = Colors::globalBlend.alpha;
	this->polygon().hline(x1,y,x2,color,alpha);
}
void CTranslucentBitmap::roundRect(int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color) const{
	int alpha = Colors::globalBlend.alpha;
	this->polygon().roundRect(radius,x1,y1,x2,y2,color,alpha);
}
void  CTranslucentBitmap::roundRectFill(int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color)const{
	int alpha = Colors::globalBlend.alpha;
	this->polygon().roundRectFill(radius,x1,y1,x2,y2,color,alpha);
}
void CTranslucentBitmap::rectangleFill(int x1, int y1, int x2, int y2, int color) const {
	int alpha = Colors::globalBlend.alpha;
	this->polygon().rectangleFill(x1,y1,x2,y2,color,alpha);
}

void CTranslucentBitmap::rectangleFill(int x1, int y1, int x2, int y2, Colors::ColorDefinition color) const {
	int alpha = Colors::globalBlend.alpha;
	this->polygon().rectangleFill(x1,y1,x2,y2,color,alpha);
	//::boxRGBA( getBitmap(), x1, y1, x2, y2,getRed(color),getGreen(color),getBlue(color),alpha  );
    //SPG_RectFilledBlend(getBitmap(), x1, y1, x2, y2, color, alpha);
}

void CTranslucentBitmap::rectangle( int x1, int y1, int x2, int y2, int color ) const {
	int alpha = Colors::globalBlend.alpha;
    this->polygon().rectangle(x1,y1,x2,y2,color,alpha);
	//SPG_RectBlend(getBitmap(), x1, y1, x2, y2, color, alpha);
}
void CTranslucentBitmap::rectangle( int x1, int y1, int x2, int y2, Colors::ColorDefinition color ) const {
	int alpha = Colors::globalBlend.alpha;
    this->polygon().rectangle(x1,y1,x2,y2,color,alpha);
	//SPG_RectBlend(getBitmap(), x1, y1, x2, y2, color, alpha);
}
void CTranslucentBitmap::draw(const int x, const int y, const CBitmap & where) const {
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"BEGIN" <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

    CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y,CBitmap::SPRITE_TRANS, CBitmap::SPRITE_NO_FLIP, NULL,mask);
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"END" <<  endl;
}

void CTranslucentBitmap::draw( const int x, const int y, CFilter * filter, const CBitmap & where ) const {
  	Debug::debug(Debug::bitmap,__FUNCTION__) <<"BEGIN" <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_NO_FLIP, filter,mask);
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"END" <<  endl;

}

void CTranslucentBitmap::drawHFlip( const int x, const int y, const CBitmap & where ) const {
    Debug::debug(Debug::bitmap,__FUNCTION__) <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_H_FLIP, NULL,mask);
}

void CTranslucentBitmap::drawHFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const {
    Debug::debug(Debug::bitmap,__FUNCTION__) <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_H_FLIP, filter,mask);
}

void CTranslucentBitmap::drawVFlip( const int x, const int y, const CBitmap & where ) const {
    Debug::debug(Debug::bitmap,__FUNCTION__) <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_V_FLIP, NULL,mask);
}

void CTranslucentBitmap::drawVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const {
    Debug::debug(Debug::bitmap,__FUNCTION__) <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_V_FLIP, filter,mask);
}

void CTranslucentBitmap::drawHVFlip( const int x, const int y, const CBitmap & where ) const {
    Debug::debug(Debug::bitmap,__FUNCTION__) <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, SPRITE_V_FLIP | SPRITE_H_FLIP, NULL,mask);
}

void CTranslucentBitmap::drawHVFlip( const int x, const int y, CFilter * filter,const CBitmap & where ) const {
    Debug::debug(Debug::bitmap,__FUNCTION__) <<  endl;
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

CBitmap::draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, SPRITE_V_FLIP | SPRITE_H_FLIP, filter,mask);
}

void CTranslucentBitmap::putPixelNormal(int x, int y, int color) const {
 //   if (getData().isClipped(x, y)){
 //       return;
 //   }

    SDL_Surface * surface = getBitmap();
    Colors::putPixelSurface(surface, x, y, color, true);
}


} //end namespace SGF