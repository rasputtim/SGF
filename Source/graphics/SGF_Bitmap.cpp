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
#include <string>
#include <stdlib.h>
#include <math.h>

#if defined(_WIN32) && !defined(APIENTRY) && \
		!defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#include <windows.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif defined(ANDROID)
// open GL libs

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdarg.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include "../../ExternalLibs/SDL2/src/render/SDL_sysrender.h"
#include "../../ExternalLibs/SDL2/include/SDL_video.h"
#include "../../ExternalLibs/SDL2_image-2.0.3/SDL_image.h"
#include "../../ExternalLibs/SDL_gfx-2.0.24/SDL_gfxPrimitives.h"
#include "../../ExternalLibs/SDL_gfx-2.0.24/SDL_rotozoom.h"
#include "graphics/SGF_Bitmap.h"
#include "exceptions/all.h"
#include "util/SGF_Util.h"
#include "SGF_Global.h"
#include "util/SGF_Debug.h"
#include "util/SGF_SdlManager.h"
#include "graphics/SGF_Color.h"
#include "external/DT_drawtext.h"
#include "external/scale2x.h"
#include "sprite/defs.h"
//#include "sprig.h"
#include "graphics/SGF_Poligon.h"

typedef scale2x_uint16* conv16;

#ifdef _WIN32
#define EXTERNAL_VARIABLE __declspec(dllimport)
#else
#define EXTERNAL_VARIABLE
#endif


using namespace std;


namespace SGF {

int CBitmap::SCALE_X = 0;
int CBitmap::SCALE_Y = 0;

CBitmap * CBitmap::temporary_bitmap = NULL;
CBitmap * CBitmap::temporary_bitmap2 = NULL;
bool CBitmap::GLenabled = false;

const SDL_BlendMode CBitmap::MODE_TRANS = SDL_BLENDMODE_BLEND;
const SDL_BlendMode CBitmap::MODE_SOLID = SDL_BLENDMODE_NONE;
const SDL_BlendMode CBitmap::MODE_ADD = SDL_BLENDMODE_ADD;
const SDL_BlendMode CBitmap::MODE_MOD = SDL_BLENDMODE_MOD;

const BitmapType CBitmap::DRAW_TYPE_TEXTURE=USE_TEXTURE;
const BitmapType CBitmap::DRAW_TYPE_SURFACE=USE_SURFACE;
const BitmapType CBitmap::DRAW_TYPE_TEX_SURF=BOTH_TEXTURE_SURFACE;
const BitmapType CBitmap::DRAW_TYPE_GL=USE_GL_TEXTURE;
const BitmapType CBitmap::DRAW_TYPE_RENDERER=USE_RENDERER;
BitmapType CBitmap::DRAW_TYPE_DEFAULT=BOTH_TEXTURE_SURFACE;
/*
const int CBitmap::SPRITE_NO_FLIP = 0;
const int CBitmap::SPRITE_V_FLIP = 1;
const int CBitmap::SPRITE_H_FLIP = 2;

const int CBitmap::SPRITE_NORMAL = 1;
const int CBitmap::SPRITE_LIT = 2;
const int CBitmap::SPRITE_TRANS = 3;
*/

static int surfaceDrawingMode = CBitmap::MODE_SOLID;

static int drawingAlpha(){
    switch (surfaceDrawingMode){
        case CBitmap::MODE_SOLID : return 255;
		case CBitmap::MODE_TRANS : return Colors::globalBlend.alpha;
        default : return 255;
    }
}



SDLState_t* CBitmap::_my_state = NULL;

static inline Uint8* computeOffset(SDL_Surface * surface, int x, int y){
    int bpp = surface->format->BytesPerPixel;
    return ((Uint8*)surface->pixels) + y * surface->pitch + x * bpp;
}

static inline Uint8* computeOffset(SDL_Texture * surface, int x, int y){
	Uint32 format = surface->format;
	int    bitspp;
    Uint32 Rmask;
    Uint32 Gmask;
    Uint32 Bmask;
    Uint32 Amask;
	int bytespp;
	SDL_PixelFormatEnumToMasks(format,
                                    &bitspp,
                                    &Rmask,
                                    &Gmask,
                                    &Bmask,
                                    &Amask);
	switch (bitspp) {
	case 15: bytespp = 2;  break;
	case 16: bytespp = 2;  break;
	case 24: bytespp = 3; break;
	case 32: bytespp = 4; break;
	default: bytespp = 4; break;
	}

    return ((Uint8*)surface->pixels) + y * surface->pitch + x * bytespp;
}


void CBitmap::replace32(SDL_Surface * dst, const int original, const int replace){
    int y1 = 0;
    int y2 = dst->h;
    int x1 = 0;
    int x2 = dst->w - 1;

    y1 = dst->clip_rect.y;
    y2 = dst->clip_rect.y + dst->clip_rect.h;
    x1 = dst->clip_rect.x;
    x2 = dst->clip_rect.x + dst->clip_rect.w;

    int bpp = dst->format->BytesPerPixel;


    if (SDL_MUSTLOCK(dst)){
        SDL_LockSurface(dst);
    }

    for (int y = y1; y < y2; y++) {
        Uint8 * sourceLine = computeOffset(dst, x1, y);

        for (int x = x2 - 1; x >= x1; sourceLine += bpp, x--) {
            unsigned long sourcePixel = *(Uint32*) sourceLine;
            if ((int) sourcePixel == original){
                *(Uint32 *)sourceLine = replace;
            }
        }
    }

    if (SDL_MUSTLOCK(dst)){
        SDL_UnlockSurface(dst);
    }
}


void replace16(SDL_Surface * dst, const int original, const int replace){
    int y1 = 0;
    int y2 = dst->h;
    int x1 = 0;
    int x2 = dst->w - 1;

    y1 = dst->clip_rect.y;
    y2 = dst->clip_rect.y + dst->clip_rect.h;
    x1 = dst->clip_rect.x;
    x2 = dst->clip_rect.x + dst->clip_rect.w;

    int bpp = dst->format->BytesPerPixel;


    if (SDL_MUSTLOCK(dst)){
        SDL_LockSurface(dst);
    }

    for (int y = y1; y < y2; y++) {
        Uint8 * sourceLine = computeOffset(dst, x1, y);

        for (int x = x2 - 1; x >= x1; sourceLine += bpp, x--) {
            unsigned long sourcePixel = *(Uint16*) sourceLine;
            if ((int) sourcePixel == original){
                *(Uint16 *)sourceLine = replace;
            }
        }
    }

    if (SDL_MUSTLOCK(dst)){
        SDL_UnlockSurface(dst);
    }
}


void CBitmap::draw_sprite_ex32(SDL_Texture * dst, SDL_Surface * src, int dx, int dy, int mode, int flip, CBitmap::CFilter * filter,unsigned int maskColor){
    int x, y, w, h;
    int x_dir = 1, y_dir = 1;
    int dxbeg, dybeg;
    int sxbeg, sybeg;
    /*
    SGE_DLS_BLENDER lit_blender;
    SGE_DTS_BLENDER trans_blender;
    */

    /*
    ASSERT(dst);
    ASSERT(src);
    */
    int pitch;
	void *pixels;
    if (SDL_MUSTLOCK(src)){
        SDL_LockSurface(src);
    }

    SDL_LockTexture(dst, NULL,
                &pixels,
                &pitch);

    if ( flip & CBitmap::SPRITE_V_FLIP ){
        y_dir = -1;
    }
    if ( flip & CBitmap::SPRITE_H_FLIP ){
        x_dir = -1;
    }

    if (true /* dst->clip*/ ) {
        int tmp;

		tmp = dst->locked_rect.x - dx;
        sxbeg = ((tmp < 0) ? 0 : tmp);
        dxbeg = sxbeg + dx;

        tmp = dst->locked_rect.x + dst->locked_rect.w - dx;
        w = ((tmp > src->w) ? src->w : tmp) - sxbeg;
        if (w <= 0)
            return;

        if ( flip & CBitmap::SPRITE_H_FLIP ){
            /* use backward drawing onto dst */
            sxbeg = src->w - (sxbeg + w);
            dxbeg += w - 1;
        }

        tmp = dst->locked_rect.y - dy;
        sybeg = ((tmp < 0) ? 0 : tmp);
        dybeg = sybeg + dy;

        tmp = dst->locked_rect.y + dst->locked_rect.h - dy;
        h = ((tmp > src->h) ? src->h : tmp) - sybeg;
        if (h <= 0)
            return;

        if ( flip & CBitmap::SPRITE_V_FLIP ){
            /* use backward drawing onto dst */
            sybeg = src->h - (sybeg + h);
            dybeg += h - 1;
        }
    } else {
        w = src->w;
        h = src->h;
        sxbeg = 0;
        sybeg = 0;
        dxbeg = dx;
        if ( flip & CBitmap::SPRITE_H_FLIP ){
            dxbeg = dx + w - 1;
        }
        dybeg = dy;
        if ( flip & CBitmap::SPRITE_V_FLIP ){
            dybeg = dy + h - 1;
        }
    }

    /*
    lit_blender = SGE_MAKE_DLS_BLENDER(0);
    trans_blender = SGE_MAKE_DTS_BLENDER();
    */

#if 0
    if (dst->id & (BMP_ID_VIDEO | BMP_ID_SYSTEM)) {
        bmp_select(dst);

        switch (mode){
            case CBitmap::SPRITE_NORMAL : {
                                             for (y = 0; y < h; y++) {
                                                 SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
                                                 SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);
                                                 for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {

                                                     unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                                                     if (!SGE_IS_SPRITE_MASK(src, c)) {
                                                         SGE_PUT_PIXEL(d, c);
                                                     }
                                                 }
                                             }

                                             break;
                                         }
            case CBitmap::SPRITE_LIT : {
                                          for (y = 0; y < h; y++) {
                                              SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
                                              SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);
                                              for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {

                                                  unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                                                  if (!SGE_IS_SPRITE_MASK(src, c)) {
                                                      c = SGE_IS_SPRITE_MASK(lit_blender, c);
                                                      SGE_PUT_PIXEL(d, c);
                                                  }
                                              }
                                          }
                                          break;
                                      }
            case CBitmap::SPRITE_TRANS : {
                                            for (y = 0; y < h; y++) {
                                                SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
                                                SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);
                                                for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {

                                                    unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                                                    if (!SGE_IS_SPRITE_MASK(src, c)) {
                                                        c = SGE_DTS_BLEND(trans_blender, SGE_IS_SPRITE_MASK(d), c);
                                                        SGE_PUT_PIXEL(d, c);
                                                    }
                                                }
                                            }
                                            break;
                                        }
        }
#xendif

        for (y = 0; y < h; y++) {
            SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);

            /* flipped if y_dir is -1 */
            SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);

            /* d is incremented by x_dir, -1 if flipped */
            for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {
                unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                if (!SGE_IS_SPRITE_MASK(src, c)) {
                    switch( mode ){
                        case CBitmap::SPRITE_NORMAL : break;
                        case CBitmap::SPRITE_LIT : {
                                                      c = SGE_IS_SPRITE_MASK(lit_blender, c);
                                                      break;
                                                  }
                        case CBitmap::SPRITE_TRANS : {
                                                        c = SGE_DTS_BLEND(trans_blender, SGE_IS_SPRITE_MASK(d), c);
                                                        break;
                                                    }
                    }
                    SGE_PUT_PIXEL(d, c);
                }
            }
        }

        bmp_unwrite_line(dst);
    }
    else {
#endif
        {

        switch (mode){
            case CBitmap::SPRITE_NORMAL : {

                unsigned int mask = maskColor;
                int bpp = src->format->BytesPerPixel;
                for (y = 0; y < h; y++) {
                    Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        if (!(sourcePixel == mask)){
                            // unsigned int destPixel = *(Uint32*) destLine;
                            // sourcePixel = globalBlend.currentBlender(destPixel, sourcePixel, globalBlend.alpha);
                            if (filter != NULL){
                                *(Uint32 *)destLine = filter->filter(sourcePixel);
                            } else {
                                *(Uint32 *)destLine = sourcePixel;
                            }
                        }
                    }
                }
                break;

		}
             case CBitmap::SPRITE_LIT : {

                int bpp = src->format->BytesPerPixel;
				int litColor = Colors::makeColor(Colors::globalBlend.red, Colors::globalBlend.green, Colors::globalBlend.blue);
                unsigned int mask = maskColor;
                for (y = 0; y < h; y++) {
                    Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        if (!(sourcePixel == mask)){
                            // unsigned int destPixel = *(Uint32*) destLine;
                            if (filter != NULL){
                                sourcePixel = Colors::globalBlend.currentBlender(litColor, filter->filter(sourcePixel), Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            } else {
                                sourcePixel = Colors::globalBlend.currentBlender(litColor, sourcePixel, Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            }
                        }
                    }
                }
                break;

			}
            case CBitmap::SPRITE_TRANS : {

                int bpp = src->format->BytesPerPixel;
                unsigned int mask = maskColor;
                for (y = 0; y < h; y++) {
                    Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        if (!(sourcePixel == mask)){
                            unsigned int destPixel = *(Uint32*) destLine;
                            if (filter != NULL){
                                sourcePixel = Colors::globalBlend.currentBlender(filter->filter(sourcePixel), destPixel, Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            } else {
                                sourcePixel = Colors::globalBlend.currentBlender(sourcePixel, destPixel, Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            }
                        }
                    }
                }
                break;


		}
            default : { break; }
        }

#if 0
        for (y = 0; y < h; y++) {
            SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
            SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);

            for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {
                unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                if (!SGE_IS_SPRITE_MASK(src, c)) {
                    switch( mode ){
                        case CBitmap::SPRITE_NORMAL : break;
                        case CBitmap::SPRITE_LIT : {
                                                      c = SGE_IS_SPRITE_MASK(lit_blender, c);
                                                      break;
                                                  }
                        case CBitmap::SPRITE_TRANS : {
                                                        c = SGE_DTS_BLEND(trans_blender, SGE_IS_SPRITE_MASK(d), c);
                                                        break;
                                                    }
                    }
                    SGE_PUT_MEMORY_PIXEL(d, c);
                }
            }
        }
#endif
    }

    if (SDL_MUSTLOCK(src)){
        SDL_UnlockSurface(src);
    }

    SDL_UnlockTexture(dst);
}

void CBitmap::draw_sprite_ex32(SDL_Surface * dst, SDL_Surface * src, int dx, int dy, int mode, int flip, CBitmap::CFilter * filter, unsigned int maskColor){

	int x_dir = 1, y_dir = 1;
    int x, y, w, h;		// width and height of visible area
	int dxbeg, dybeg;	// beginning in destination
	int sxbeg, sybeg;	// beginning in source
	
    /*
    SGE_DLS_BLENDER lit_blender;
    SGE_DTS_BLENDER trans_blender;
    */

    /*
    ASSERT(dst);
    ASSERT(src);
    */

    if (SDL_MUSTLOCK(src)){
        SDL_LockSurface(src);
    }

    if (SDL_MUSTLOCK(dst)){
        SDL_LockSurface(dst);
    }

    if ( flip & CBitmap::SPRITE_V_FLIP ){
        y_dir = -1;
    }
    if ( flip & CBitmap::SPRITE_H_FLIP ){
        x_dir = -1;
    }

	// Clip to dst->clip_rect
	int dst_cl_x1 = dst->clip_rect.x;  //calc x1
	int dst_cr_x2 = dst->clip_rect.w + dst_cl_x1 - 1; //  calc x2
	int dst_ct_y1 = dst->clip_rect.y;           //calc y1
	int dst_cb_x2 = dst->clip_rect.h + dst_ct_y1;  //calc y2


    if (true /* dst->clip*/ ) {
        int tmp;

        tmp = dst_cl_x1 - dx;
        sxbeg = ((tmp < 0) ? 0 : tmp);
        dxbeg = sxbeg + dx;

        tmp = dst_cl_x1 + dst->clip_rect.w - dx;
        w = ((tmp > src->w) ? src->w : tmp) - sxbeg;
        if (w <= 0)
            return;

        if ( flip & CBitmap::SPRITE_H_FLIP ){
            /* use backward drawing onto dst */
            sxbeg = src->w - (sxbeg + w);
            dxbeg += w - 1;
        }

        tmp = dst_ct_y1 - dy;
        sybeg = ((tmp < 0) ? 0 : tmp);
        dybeg = sybeg + dy;

        tmp = dst_ct_y1 + dst->clip_rect.h - dy;
        h = ((tmp > src->h) ? src->h : tmp) - sybeg;
        if (h <= 0)
            return;

        if ( flip & CBitmap::SPRITE_V_FLIP ){
            /* use backward drawing onto dst */
            sybeg = src->h - (sybeg + h);
            dybeg += h - 1;
        }
    } else {
        w = src->w;
        h = src->h;
        sxbeg = 0;
        sybeg = 0;
        dxbeg = dx;
        if ( flip & CBitmap::SPRITE_H_FLIP ){
            dxbeg = dx + w - 1;
        }
        dybeg = dy;
        if ( flip & CBitmap::SPRITE_V_FLIP ){
            dybeg = dy + h - 1;
        }
    }

    /*
    lit_blender = SGE_MAKE_DLS_BLENDER(0);
    trans_blender = SGE_MAKE_DTS_BLENDER();
    */

#if 0
    if (dst->id & (BMP_ID_VIDEO | BMP_ID_SYSTEM)) {
        bmp_select(dst);

        switch (mode){
            case CBitmap::SPRITE_NORMAL : {
                                             for (y = 0; y < h; y++) {
                                                 SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
                                                 SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);
                                                 for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {

                                                     unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                                                     if (!SGE_IS_SPRITE_MASK(src, c)) {
                                                         SGE_PUT_PIXEL(d, c);
                                                     }
                                                 }
                                             }

                                             break;
                                         }
            case CBitmap::SPRITE_LIT : {
                                          for (y = 0; y < h; y++) {
                                              SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
                                              SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);
                                              for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {

                                                  unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                                                  if (!SGE_IS_SPRITE_MASK(src, c)) {
                                                      c = SGE_IS_SPRITE_MASK(lit_blender, c);
                                                      SGE_PUT_PIXEL(d, c);
                                                  }
                                              }
                                          }
                                          break;
                                      }
            case CBitmap::SPRITE_TRANS : {
                                            for (y = 0; y < h; y++) {
                                                SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
                                                SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);
                                                for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {

                                                    unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                                                    if (!SGE_IS_SPRITE_MASK(src, c)) {
                                                        c = SGE_DTS_BLEND(trans_blender, SGE_IS_SPRITE_MASK(d), c);
                                                        SGE_PUT_PIXEL(d, c);
                                                    }
                                                }
                                            }
                                            break;
                                        }
        }
#evndif

        for (y = 0; y < h; y++) {
            SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);

            /* flipped if y_dir is -1 */
            SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);

            /* d is incremented by x_dir, -1 if flipped */
            for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {
                unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                if (!SGE_IS_SPRITE_MASK(src, c)) {
                    switch( mode ){
                        case CBitmap::SPRITE_NORMAL : break;
                        case CBitmap::SPRITE_LIT : {
                                                      c = SGE_IS_SPRITE_MASK(lit_blender, c);
                                                      break;
                                                  }
                        case CBitmap::SPRITE_TRANS : {
                                                        c = SGE_DTS_BLEND(trans_blender, SGE_IS_SPRITE_MASK(d), c);
                                                        break;
                                                    }
                    }
                    SGE_PUT_PIXEL(d, c);
                }
            }
        }

        bmp_unwrite_line(dst);
    }
    else {
#endif
        {

        switch (mode){
            case CBitmap::SPRITE_NORMAL : {

                unsigned int mask = maskColor;
                int bpp = src->format->BytesPerPixel;
                for (y = 0; y < h; y++) {
                    Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        if (!(sourcePixel == mask)){
                            // unsigned int destPixel = *(Uint32*) destLine;
                            // sourcePixel = globalBlend.currentBlender(destPixel, sourcePixel, globalBlend.alpha);
                            if (filter != NULL){
                                *(Uint32 *)destLine = filter->filter(sourcePixel);
                            } else {
                                *(Uint32 *)destLine = sourcePixel;
                            }
                        }
                    }
                }
                break;

			}
             case CBitmap::SPRITE_LIT : {

                int bpp = src->format->BytesPerPixel;
				int litColor = Colors::makeColor(Colors::globalBlend.red, Colors::globalBlend.green, Colors::globalBlend.blue);
                unsigned int mask = maskColor;
                for (y = 0; y < h; y++) {
                    Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);  //compute offset based on bpp
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        if (!(sourcePixel == mask)){
                            // unsigned int destPixel = *(Uint32*) destLine;
                            if (filter != NULL){
                                sourcePixel = Colors::globalBlend.currentBlender(litColor, filter->filter(sourcePixel), Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            } else {
                                sourcePixel = Colors::globalBlend.currentBlender(litColor, sourcePixel, Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            }
                        }
                    }
                }
                break;

			}
            case CBitmap::SPRITE_TRANS : {

				int bpp = src->format->BytesPerPixel;
                unsigned int mask = maskColor;
                for (y = 0; y < h; y++) {
                    Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        if (!(sourcePixel == mask)){
                            unsigned int destPixel = *(Uint32*) destLine;
                            if (filter != NULL){
                                sourcePixel =  Colors::globalBlend.currentBlender(filter->filter(sourcePixel), destPixel, Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            } else {
                                sourcePixel =  Colors::globalBlend.currentBlender(sourcePixel, destPixel, Colors::globalBlend.alpha);
                                *(Uint32 *)destLine = sourcePixel;
                            }
                        }
                    }
                }
                break;

		}
            default : { break; }
        }

#if 0
        for (y = 0; y < h; y++) {
            SGE_PIXEL_PTR s = SGE_OFFSET_PIXEL_PTR(src->line[sybeg + y], sxbeg);
            SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y * y_dir), dxbeg);

            for (x = w - 1; x >= 0; SGE_INC_PIXEL_PTR(s), SGE_INC_PIXEL_PTR_EX(d,x_dir), x--) {
                unsigned long c = SGE_GET_MEMORY_PIXEL(s);
                if (!SGE_IS_SPRITE_MASK(src, c)) {
                    switch( mode ){
                        case CBitmap::SPRITE_NORMAL : break;
                        case CBitmap::SPRITE_LIT : {
                                                      c = SGE_IS_SPRITE_MASK(lit_blender, c);
                                                      break;
                                                  }
                        case CBitmap::SPRITE_TRANS : {
                                                        c = SGE_DTS_BLEND(trans_blender, SGE_IS_SPRITE_MASK(d), c);
                                                        break;
                                                    }
                    }
                    SGE_PUT_MEMORY_PIXEL(d, c);
                }
            }
        }
#endif

    }

    if (SDL_MUSTLOCK(src)){
        SDL_UnlockSurface(src);
    }

    if (SDL_MUSTLOCK(dst)){
        SDL_UnlockSurface(dst);
    }


}

void CBitmap::draw_sprite_filter_ex16(SDL_Surface * dst, SDL_Surface * src, int dx, int dy, const CBitmap::CFilter & filter){
    int x, y, w, h;
    int x_dir = 1, y_dir = 1;
    int dxbeg, dybeg;
    int sxbeg, sybeg;

    if (SDL_MUSTLOCK(dst)){
        SDL_LockSurface(dst);
    }
	// Clip to dst->clip_rect
	int dst_cl_x1 = dst->clip_rect.x;  //calc x1
	int dst_cr_x2 = dst->clip_rect.w + dst_cl_x1 - 1; //  calc x2
	int dst_ct_y1 = dst->clip_rect.y;           //calc y1
	int dst_cb_y2 = dst->clip_rect.h + dst_ct_y1;  //calc y2

    if (true /* dst->clip*/ ) {
        int tmp;

        tmp = dst_cl_x1 - dx;
        sxbeg = ((tmp < 0) ? 0 : tmp);
        dxbeg = sxbeg + dx;

        tmp = dst_cl_x1 + dst->clip_rect.w - dx;
        w = ((tmp > src->w) ? src->w : tmp) - sxbeg;
        if (w <= 0)
            return;

        tmp = dst_ct_y1 - dy;
        sybeg = ((tmp < 0) ? 0 : tmp);
        dybeg = sybeg + dy;

        tmp = dst_cb_y2 - dy;
        h = ((tmp > src->h) ? src->h : tmp) - sybeg;
        if (h <= 0)
            return;
    }

    unsigned int mask = Colors::makeColor(255, 0, 255);
    int bpp = src->format->BytesPerPixel;
    for (y = 0; y < h; y++) {
        Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
        Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

        for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
            unsigned long sourcePixel = *(Uint16*) sourceLine;
            if (!(sourcePixel == mask)){
                *(Uint16 *)destLine = filter.filter(sourcePixel);
            } else {
                *(Uint16 *)destLine = mask;
            }
        }
    }

    if (SDL_MUSTLOCK(dst)){
        SDL_UnlockSurface(dst);
    }
}

static void light32(SDL_Surface * dst, const int x, const int y, int width, int height, const int start_y, const int focus_alpha, const int edge_alpha, const Colors::ColorDefinition focus_color, const Colors::ColorDefinition edge_color){

    if (width > dst->w){
        width = dst->w;
    }

    if (height > dst->h){
        height = dst->h;
    }

    int dxbeg = x - width;
    int x_dir = 1;
    unsigned char * alphas = new unsigned char[width];
    //int * colors = new int[width];
	Colors::ColorDefinition * colors = new Colors::ColorDefinition[width];
    for (int i = 0; i < width; i++){
        alphas[i] = (unsigned char)((double)(edge_alpha - focus_alpha) * (double)i / (double)width + focus_alpha);
    }
    Colors::blend_palette(colors, width, focus_color, edge_color);

    if (SDL_MUSTLOCK(dst)){
        SDL_LockSurface(dst);
    }

    int min_y, max_y, min_x, max_x;
    min_y = dst->clip_rect.y;
    max_y = dst->clip_rect.y + dst->clip_rect.h - 1;
    min_x = dst->clip_rect.x;
    max_x = dst->clip_rect.x + dst->clip_rect.w - 1;

    int dybeg = y;

    /* tan(theta) = y / x */
    double xtan = (double) height / (double) width;
    int bpp = dst->format->BytesPerPixel;
    for (int sy = start_y; sy < height; sy++) {
        if (dybeg + sy < min_y || dybeg + sy > max_y){
            continue;
        }
        /* x = y / tan(theta) */
        int top_width = (int)((double) sy / xtan);
        if (top_width == 0){
            continue;
        }

        dxbeg = x - top_width;
        Uint8* line = computeOffset(dst, dxbeg, dybeg + y);

        for (int sx = -top_width; sx <= top_width; line += x_dir * bpp, sx++) {
            if (sx + x < min_x || sx + x > max_x){
                continue;
            }

            unsigned long c = *(Uint32*) line;

            /* TODO:
             * converting to a double and calling fabs is overkill, just
             * write an integer abs() function.
             */
            int sx_abs = (int) fabs((double) sx);
            int alphaUse = alphas[sx_abs];
			int color = Colors::makeColor(colors[sx_abs].r,colors[sx_abs].g,colors[sx_abs].b);

            c = Colors::globalBlend.currentBlender(color, c, alphaUse);

            *(Uint32*) line = c;
        }
    }
    delete[] alphas;
    delete[] colors;

    if (SDL_MUSTLOCK(dst)){
        SDL_UnlockSurface(dst);
    }
}

static void light16(SDL_Surface * dst, const int x, const int y, int width, int height, const int start_y, const int focus_alpha, const int edge_alpha, const Colors::ColorDefinition focus_color, const Colors::ColorDefinition edge_color){

    if (width > dst->w){
        width = dst->w;
    }

    if (height > dst->h){
        height = dst->h;
    }

    int dxbeg = x - width;
    int x_dir = 1;
    unsigned char * alphas = new unsigned char[width];
   // int * colors = new int[width];
	Colors::ColorDefinition *colors = new Colors::ColorDefinition[width];
	for (int i = 0; i < width; i++){
        alphas[i] = (unsigned char)((double)(edge_alpha - focus_alpha) * (double)i / (double)width + focus_alpha);
    }
    Colors::blend_palette(colors, width, focus_color, edge_color);

    if (SDL_MUSTLOCK(dst)){
        SDL_LockSurface(dst);
    }

    int min_y, max_y, min_x, max_x;
    min_y = dst->clip_rect.y;
    max_y = dst->clip_rect.y + dst->clip_rect.h - 1;
    min_x = dst->clip_rect.x;
    max_x = dst->clip_rect.x + dst->clip_rect.w - 1;

    int dybeg = y;

    /* tan(theta) = y / x */
    double xtan = (double) height / (double) width;
    int bpp = dst->format->BytesPerPixel;
    for (int sy = start_y; sy < height; sy++) {
        if (dybeg + sy < min_y || dybeg + sy > max_y){
            continue;
        }
        /* x = y / tan(theta) */
        int top_width = (int)((double) sy / xtan);
        if (top_width == 0){
            continue;
        }

        dxbeg = x - top_width;
        Uint8* line = computeOffset(dst, dxbeg, dybeg + y);

        for (int sx = -top_width; sx <= top_width; line += x_dir * bpp, sx++) {
            if (sx + x < min_x || sx + x > max_x){
                continue;
            }

            unsigned long c = *(Uint16*) line;

            /* TODO:
             * converting to a double and calling fabs is overkill, just
             * write an integer abs() function.
             */
            int sx_abs = (int) fabs((double) sx);
            int alphaUse = alphas[sx_abs];
			int color = Colors::makecol16(colors[sx_abs].r,colors[sx_abs].g,colors[sx_abs].b);

            c = Colors::globalBlend.currentBlender(color, c, alphaUse);

            *(Uint16*) line = c;
        }
    }
    delete[] alphas;
    delete[] colors;

    if (SDL_MUSTLOCK(dst)){
        SDL_UnlockSurface(dst);
    }
}


void CBitmap::replaceColor(int original, int replaced){
   replace32(getBitmap(), original, replaced);
#if 0
	for (int x = 0; x < getWidth(); x++){
        for (int y = 0; y < getHeight(); y++){
	    int pixel = getPixelSurface(x, y);
		if (pixel==original){
            putPixelSurface(x, y, replaced);
		}
        }
    }
     //Todo: Use replace32 to get speed
#endif
	//replace32(getBitmap(), original, replaced);
}

vector<Gui::CAbsolutePoint> CBitmap::getPixelsCoord(Colors::PixelColor mask){
	CBitmap *letters = this;
	// Graphics::Bitmap letters(width, height);
	//int mask =  Colors::makeColor(255,0,255);
	//int mask = letters.getPCXMaskColor();
	//letters.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	
	vector< Gui::CAbsolutePoint > pairs;
 	for ( int x = 0; x < letters->getWidth(); x++ ){
        for ( int y = 0; y < letters->getHeight(); y++ ){
            int pixel = letters->getPixelSurface( x, y );
            //Debug::debug( 2 ) << "Loader:loading screen // Letters Pixel | Mask = "<< pixel <<" | "<< Colors::makeColor(255,0,255) << endl;

			if ( pixel ==  mask){
                Debug::debug(10,__FUNCTION__ ) << " Creating Letters: Putting Pixel (x,y) = "<<"( "<<x<<","<<y<<" )" << endl;
				Gui::CAbsolutePoint p;
                p.x = x;
                p.y = y;
                pairs.push_back( p );
            }
        }
    }
    return pairs;
}

vector<Gui::CAbsolutePoint> CBitmap::getPixelsCoordInverted(Colors::PixelColor mask){
	CBitmap *letters = this;
	// Graphics::Bitmap letters(width, height);
	//int mask =  Colors::makeColor(255,0,255);
	//int mask = letters.getPCXMaskColor();
	//letters.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	
	vector< Gui::CAbsolutePoint > pairs;
 	for ( int x = 0; x < letters->getWidth(); x++ ){
        for ( int y = 0; y < letters->getHeight(); y++ ){
            int pixel = letters->getPixelSurface( x, y );
            //Debug::debug( 2 ) << "Loader:loading screen // Letters Pixel | Mask = "<< pixel <<" | "<< Colors::makeColor(255,0,255) << endl;

			if ( pixel !=  mask){
                Debug::debug(10,__FUNCTION__ ) << " Creating Letters: Putting Pixel (x,y) = "<<"( "<<x<<","<<y<<" )" << endl;
				Gui::CAbsolutePoint p;
                p.x = x;
                p.y = y;
                pairs.push_back( p );
            }
        }
    }
    return pairs;
}


void CBitmap::setPCXMaskColor(Colors::ColorDefinition color){
    bitPCXMaskColor.r = color.r;
	bitPCXMaskColor.g = color.g;
	bitPCXMaskColor.b = color.b;
}


unsigned int CBitmap::getPCXMaskColor() const{
	return Colors::makeColor(bitPCXMaskColor.r,bitPCXMaskColor.g,bitPCXMaskColor.b);
}

//====================================================
//lOAD IMAGE
/** @fn CBitmap::load_image( const char *  filename )
@brief Função carrega uma imagem de um arquivo e otimiza para o formato da tela
* suporta todos os tipos de imagem suportados pelo SDL_image
@param filename: nome do arquivo contendo a imagem
@return ponteiro para a superfície SDL criada a partir da imagem carregada
        se não conseguir carregar a imagem retorna NULL
@warning nenhum aviso
**/

SDL_Surface *CBitmap::load_image( const char *  filename )
{
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Loading:" <<filename <<endl;
	//Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
 	loadedImage = IMG_Load(filename);

	//loadedImage = SDL_LoadBMP( filename );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Optimazing:" <<filename <<" - Loaded  on: " << loadedImage <<endl;
        //Create an optimized image
        if((optimizedImage = SDL_ConvertSurface(loadedImage,Colors::getCurrentPixelFormat(),SDL_SWSURFACE))==NULL) {

			return loadedImage;

		}else {
		//Free the old image
        SDL_FreeSurface( loadedImage );
        Debug::debug(Debug::bitmap,__FUNCTION__) << "Returning Image Loaded:" << optimizedImage <<endl;
			//Return the optimized image

		return optimizedImage;
		}

    }else {
		Debug::debug(Debug::error,__FUNCTION__) << "Error loading image( "<<filename<<" ): " << SDL_GetError() <<endl;
	}

}

SDL_Surface *CBitmap::load_image( BYTE * file, int size )
{

	Debug::debug(Debug::bitmap,__FUNCTION__) << "Loading:" <<endl;
    /* This is the RWops structure we'll be using */
	SDL_RWops *rw;

	/* This is where we actually create our RWops structure.  Here we're
    instructing SDL to get it from the file pointer we just opened */
	rw = ::SDL_RWFromMem(file,size);

	//Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);
	SDL_PixelFormat *pixelFormat = SDL_AllocFormat(mode.format);
	if (pixelFormat == NULL) {
		Debug::debug(Debug::error,__FUNCTION__) << "Error: " << SDL_GetError() <<endl;

	}
    //Load the image
 	try {
		loadedImage = IMG_Load_RW(rw,1);
	} catch (...) {

		Debug::debug(Debug::bitmap,__FUNCTION__) << "IMG_Load_RW Error Loadind: " << IMG_GetError() <<endl;
	}
	//If nothing went wrong in loading the image
    if( loadedImage != NULL )
	{
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Optimazing: image- Loaded  on: " << loadedImage <<endl;
        //Create an optimized image
		try {
			optimizedImage = SDL_ConvertSurface(loadedImage,pixelFormat,SDL_SWSURFACE);
			 if (pixelFormat !=NULL) SDL_FreeFormat(pixelFormat);
		}catch(...) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Can not optmize image. Returning loaded image withou optimization"<<endl;
			return loadedImage;
		}
        if(optimizedImage==NULL) {
           return loadedImage;

		}else {
		//Free the old image
        SDL_FreeSurface( loadedImage );
        Debug::debug(Debug::bitmap,__FUNCTION__) << "Returning Image Loaded:" << optimizedImage <<endl;
			//Return the optimized image

		return optimizedImage;
		}
    }

}

/** @fn CBitmap::CreateSurface(int width, int height)
@brief Cria uma superfície SDL com o tamanho especificado nos parâmetros
@param width: Largura da superfície a ser criada
@param height: Altura da superfície a ser criada
@return ponteiro para a superfície SDL que foi criada
        NULL caso não conseguir criar a superfície desejada
@warning por padrão esta função cria uma superfície com os mesmos parâmetros de formato da superfície que foi criada na inicialização do SDL
**/
SDL_Surface * CBitmap::CreateSurface(int width, int height)
{
	SDL_Surface* temp=NULL;
		int Bpp;
		Uint32 Rmask,Gmask,Bmask,Amask;
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);

		SDL_PixelFormatEnumToMasks(mode.format, &Bpp,
                                    &Rmask, &Gmask, &Bmask, &Amask);
		temp= SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, Bpp, Rmask, Gmask, Bmask, Amask);

		if(temp==NULL) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Create Surface Failed " <<SDL_GetError()<<endl;

		}else {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Create Surface ok " <<temp<<endl;

		}
	
	return temp;
}

/* decrement bitmap reference counter and free memory if counter hits 0 */
void BitSurfaces::releaseInternalBitmap(){
    const int MAGIC_DEBUG = 0xa5a5a5;
    if (own != NULL){
        if (*own == MAGIC_DEBUG){
			Debug::debug(Debug::error,__FUNCTION__) << "[bitmap] Trying to delete an already deleted reference counter: "<< own << endl;
        }

        (*own) -= 1;
        if ( *own == 0 ){
			//Debug::debug(Debug::bitmap,__FUNCTION__) << " Own: " << *own << " Releasing internal bitmap and texture" << endl;
            *own = MAGIC_DEBUG;
            delete own;
            ::SDL_FreeSurface(getBitmap());
			if(GetTexture()!=NULL) {
			SDL_DestroyTexture(GetTexture());

			}
			own = NULL;
        }
    }
}





CBitmap::CBitmap(int window):
//own( NULL ),
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(0),
_my_height(0),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	setBitmap( CreateSurface( 10, 10 ) );
	if ( ! getBitmap() ){
		error = true;
		cerr << "Could not create bitmap!" << endl;
	} else {
		if (GLenabled){
		InitGL(10, 10);  //inicializa openGL no modo 3D por default
		_my_bitmap.setGLTexture( (void *)malloc( 10 * 10 * 4 ));
		SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		clear();
		_my_width=getBitmap()->w;
		_my_height=getBitmap()->h;
		_my_bitmap.start();
	}
	
}

CBitmap::CBitmap( PCXDATA *image, int window ):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(0),
_my_height(0),
createdFromPCX(true),
bitPCXMaskColor(Colors::DefaultColorkey){
	Debug::debug(Debug::bitmap,__FUNCTION__) << "( PCXData *image ) - //Constructor // pcxdata= " << image << endl;

	BYTE *imagem=(BYTE*) image->pImageData;
	int size=image->Lenght;
	if (size <= 0) {
    Debug::debug(Debug::bitmap,__FUNCTION__) << "Zero sized CBitmap= "  << endl;

		error = true;
	return;
	}
	setBitmap( load_image( imagem,size ) );

	if ( ! getBitmap() ){
		//cout<<"Could not load "<<load_file<<". Using default"<<endl;
		setBitmap( CreateSurface( 10, 10 ) );
		if ( ! getBitmap() ){
			cout<<"Out of memory or SDL not initialized"<<endl;
			error = true;
			return;
		}else {
			if (GLenabled){
				InitGL(10, 10);  //inicializa openGL no modo 3D por default
				_my_bitmap.setGLTexture( (void *)malloc( 10 * 10 * 4 ));
			SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
			}
			// clear( my_bitmap );
			clear();
			// cout<<"Could not load "<<load_file<<endl;
			error = true;
			_my_bitmap.start();
		}
	}else {

		this->setPCXMaskColor(image->ColorPallet[0]);
		Debug::debug(Debug::bitmap,__FUNCTION__) << " CBitmap::load_image Default Mask Color 2= " << (int)image->ColorPallet[0].r << " , " << (int)image->ColorPallet[0].g<<" , " << (int)image->ColorPallet[0].b  << endl;


		if (GLenabled){
			InitGL(_my_state->Screen[this->_my_renderWindow]->getBitmap()->w, _my_state->Screen[this->_my_renderWindow]->getBitmap()->h);  //inicializa openGL no modo 3D por default
			_my_bitmap.setGLTexture( (void *)malloc(  getBitmap()->w * getBitmap()->h * 4 ));
			SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		
		}
		//cria textura padrão
		this->_my_bitmap.setTexture(CreateTextureFromBitmap(window));
		this->SetBlendMode(CSDLManager::GetInstance()->blendMode);
		
		_my_width=getBitmap()->w;
		_my_height=getBitmap()->h;

		_my_bitmap.start();
	}



}

//usa como default a janela 0, ou Screen[0]
CBitmap::CBitmap( int width, int height , int window):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(width),
_my_height(height),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	if ( width < 1 ){
		width = 1;
	}
	if ( height < 1 ){
		height = 1;
	}
	setBitmap( CreateSurface( width, height ) );
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Creating Internal Texture" <<  endl;
	//_my_bitmap._my_SDLTexture(copyTextureFromSurface());
	setTexture( createTextureStreaming(width,height));
	if ( ! getBitmap() ){
		error = true;
		Debug::debug(Debug::bitmap,__FUNCTION__) << "CBitmap::CBitmap( int x, int y ) // Constructor //=> Could not create bitmap! " <<  endl;

		//cerr << "Could not create bitmap!" << endl;
	} else {
		if (GLenabled){
		InitGL(width, height);  //inicializa openGL no modo 3D por default
		_my_bitmap.setGLTexture( (void *)malloc( width * height * 4 ));
		SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		_my_width=getBitmap()->w;
		_my_height=getBitmap()->h;
		_my_bitmap.start();
		// seta o renderer para este bitmap, caso seja criada textura
		//SetWindow(Screen[window]->GetWindow());


	}

}

/* If a BITMAP is given to us, we didn't make it so we don't own it */
CBitmap::CBitmap( SDL_Surface * who, bool deep_copy, bool initconsole, int window  ):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(who->w),
_my_height(who->h),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	if ( deep_copy ){
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);
		SDL_PixelFormat *pixelFormat = SDL_AllocFormat(mode.format);

		SDL_Surface * his = SDL_ConvertSurface(who, pixelFormat,SDL_SWSURFACE);//who;

		setBitmap( his );

		if ( ! getBitmap() ){
			setBitmap(who);
			cout << "Could not create new bitmap" << endl;
			error = true;
		}else {

		
		if (GLenabled){
		InitGL(his->w, his->h);  //inicializa openGL no modo 3D por default
		_my_bitmap.setGLTexture( (void *)malloc( his->w * his->h * 4 ));
		SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		
		}
			//blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
        //::blit( his, getBitmap(), 0, 0, 0, 0, his->w, his->h );
		/*SDL_Rect * retanguloSource = new SDL_Rect;
	    SDL_Rect * retanguloDest = new SDL_Rect;

		retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=his->h;
        retanguloSource->w=his->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=his->w;
		retanguloDest->h=his->h;

		::SDL_BlitSurface(his, retanguloSource, getBitmap(), retanguloDest);
		delete retanguloSource;
		delete retanguloDest;
		*/
		_my_bitmap.start();
		//own = new int;
		//*own = 1;
		//this->set8BitMaskColor(this->getPixel(0,0));  //! set the mask to pixel 0,0 color
		}
	} else {
		Debug::debug(Debug::bitmap,__FUNCTION__) << "CBitmap::CBitmap // Constructor //=> CBitmap Created Who " << who << endl;
		setBitmap( who );
		if (GLenabled){
			InitGL(who->w, who->h);  //inicializa openGL no modo 3D por default
			_my_bitmap.setGLTexture( (void *)malloc(  who->w * who->h * 4 ));
			SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		//_my_bitmap.own = NULL;
		_my_bitmap.start();
		
	}
	// cria texura
			//SetWindow(Screen[window]->GetWindow());
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Will Create Texture From Bitmap " << getBitmap() << endl;

			CreateTextureFromBitmap(window);
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Texture Created From Bitmap " << GetTexture() << endl;

			SetBlendMode(CSDLManager::GetInstance()->blendMode);

		
}

/* If a BITMAP is given to us, we didn't make it so we don't own it */
CBitmap::CBitmap( SDL_Window * who, bool deep_copy, bool initconsole,int window  ):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(_my_state->window_infos[0]->w),   //Todo SOlve when there are more than 1 window
_my_height(_my_state->window_infos[0]->h),  //Todo SOlve when there are more than 1 window
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	if ( deep_copy ){
		/*
		SDL_Surface * his = who;

		setBitmap( CreateSurface( his->w, his->h ) );

		if ( ! getBitmap() ){
			cout << "Could not create bitmap" << endl;
			error = true;
		}else {
		if (GLenabled){
		InitGL(his->w, his->h);  //inicializa openGL no modo 3D por default
		_my_bitmap._my_GLTexture = (void *)malloc( his->w * his->h * 4 );
		SetGLBitmap((Uint8 *) _my_bitmap._my_GLTexture);
		}
			//blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
        //::blit( his, getBitmap(), 0, 0, 0, 0, his->w, his->h );
		SDL_Rect * retanguloSource = new SDL_Rect;
	    SDL_Rect * retanguloDest = new SDL_Rect;

		retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=his->h;
        retanguloSource->w=his->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=his->w;
		retanguloDest->h=his->h;
		_my_width=his->w;
		_my_height=his->h;

		::SDL_BlitSurface(his, retanguloSource, getBitmap(), retanguloDest);
		delete retanguloSource;
		delete retanguloDest;
		own = new int;
		*own = 1;
		} */
	} else {
		Debug::debug(Debug::bitmap,__FUNCTION__) << "CBitmap::CBitmap // Constructor //=> CBitmap Created Window Who: " << who << endl;
		//SetWindow( who );
		//_my_bitmap.own = NULL;
		if (initconsole  ){
		 //InitConsole();
		}
	}
}

CBitmap::CBitmap( const char * load_file ,int window):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(0),
_my_height(0),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	Debug::debug(Debug::bitmap,__FUNCTION__) << "( const char * load_file ) - //Constructor // filename= " << load_file << endl;
	internalLoadFile( load_file,window );
	/*
	my_bitmap = load_image( load_file );
	if ( !my_bitmap ){
		my_bitmap = CreateSurface( 100, 100 );
		clear( my_bitmap );
		cout<<"Could not load "<<load_file<<endl;
		error = true;
	}
	own = true;
	*/

}

CBitmap::CBitmap( const string & load_file, int window ):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(0),
_my_height(0),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	Debug::debug(Debug::bitmap,__FUNCTION__) << "( const string & load_file ) - //Constructor // filename= " << load_file << endl;
    internalLoadFile( load_file.c_str(),window );

}

CBitmap::CBitmap( const char * load_file, int sx, int sy, int window ):
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(0),
_my_height(0),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	path = load_file;
	SDL_Surface * temp = load_image( load_file );
	// my_bitmap = load_image( load_file );
	setBitmap( CreateSurface( sx, sy ) );
	// clear( my_bitmap );
	if ( !temp || ! getBitmap() ){
		cout<<"Could not load "<<load_file<<endl;
		error = true;
	} else {
		if (GLenabled){
			InitGL(sx, sy);  //inicializa openGL no modo 3D por default
			_my_bitmap.setGLTexture( (void *)malloc( sx * sy * 4  ));
			SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		clear();
		SDL_Rect  retanguloSource;
	    SDL_Rect  retanguloDest;

		retanguloSource.x=0;
        retanguloSource.y=0;
        retanguloSource.h=temp->h;
        retanguloSource.w=temp->w;
        retanguloDest.x=0;
		retanguloDest.y=0;
		retanguloDest.w=getBitmap()->w;
		retanguloDest.h=getBitmap()->h;
		_my_width=getBitmap()->w;
		_my_height=getBitmap()->h;

		::SDL_BlitSurface(temp, &retanguloSource, getBitmap(), &retanguloDest);
		::SDL_FreeSurface(temp);

	}
	// cria texura
			//SetWindow(Screen[window]->GetWindow());
			CreateTextureFromBitmap(window);
			SetBlendMode(CSDLManager::GetInstance()->blendMode);

		
			_my_bitmap.start();
}

#if 0
CBitmap::CBitmap( const char * load_file, int sx, int sy, double accuracy ,int window):
own( NULL ),
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(window),
_my_texture_draw_blend_mode(MODE_SOLID),
_my_actual_draw_type(USE_TEXTURE),
_my_default_draw_type(DRAW_TYPE_DEFAULT),
_my_width(0),
_my_height(0),
createdFromPCX(false),
bitPCXMaskColor(Colors::DefaultColorkey){
	path = load_file;
	SDL_Surface * temp = load_image( load_file );
	own = new int;
	*own = 1;
	if ( !temp ){
		cout<<"Could not load "<<load_file<<endl;
		setBitmap( CreateSurface( sx, sy ) );
		// clear( my_bitmap );
		clear();
		error = true;
	} else {
		if (GLenabled){
		InitGL(sx, sy);  //inicializa openGL no modo 3D por default
		_my_bitmap._my_GLTexture = (void *)malloc( sx * sy * 4 );
		SetGLBitmap((Uint8 *) _my_bitmap._my_GLTexture);
		}
		if ( temp->w > sx || temp->h > sy ){
			double bx = temp->w / sx;
			double by = temp->h / sy;
			double use;
			use = bx > by ? bx : by;
			int fx = (int)(sx / use);
			int fy = (int)(sy / use);
			setBitmap( CreateSurface( fx, fy ) );

		SDL_Rect * retanguloSource = new SDL_Rect;
	    SDL_Rect * retanguloDest = new SDL_Rect;

		//stretch_blit( temp, getBitmap(), 0, 0, temp->w, temp->h, 0, 0, getBitmap()->w, getBitmap()->h );
		retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=temp->h;
        retanguloSource->w=temp->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=getBitmap()->w;
		retanguloDest->h=getBitmap()->h;
		_my_width=getBitmap()->w;
		_my_height=getBitmap()->h;
		::SDL_BlitSurface(temp, retanguloSource, getBitmap(), retanguloDest);
		::SDL_FreeSurface(temp);
		delete retanguloSource;
	    delete retanguloDest;

		} else {
			setBitmap( temp );
			if (GLenabled){
				InitGL(temp->w, temp->h);  //inicializa openGL no modo 3D por default
				_my_bitmap._my_GLTexture = (void *)malloc( sx * sy * 4 );
				SetGLBitmap((Uint8 *) _my_bitmap._my_GLTexture);
			}
		}
	}
	// cria texura
			//SetWindow(Screen[window]->GetWindow());
			CreateTextureFromBitmap(window);
			SetBlendMode(CSDLManager::GetInstance()->blendMode);
//		    SetScaleMode(CSDLManager::GetInstance()->scaleMode);


	// own = true;
}

#endif

//====================== COPY CONSTRUCTORS ================
CBitmap::CBitmap( const CBitmap & copy, int sizex, int sizey ):
BaseCBitmap(/*(Util::Thread::ScopedLock(copy.bitmapLock),*/copy/*)*/,true),
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(copy._my_renderWindow),
_my_texture_draw_blend_mode(copy._my_texture_draw_blend_mode),
_my_actual_draw_type(copy._my_actual_draw_type),
_my_default_draw_type(copy._my_default_draw_type),
_my_width(sizex),
_my_height(sizey),
createdFromPCX(copy.createdFromPCX),
bitPCXMaskColor(copy.bitPCXMaskColor){
	path = copy.getPath();
	SDL_Surface * temp = copy.getBitmap();
	setBitmap( CreateSurface( sizex, sizey ) );
	if ( ! getBitmap() ){
		error = true;
		cout << "Could not copy bitmap" << endl;
	}else {
		//deep_copy = false
	if (GLenabled){
		InitGL(sizex, sizey);  //inicializa openGL no modo 3D por default
		_my_bitmap.setGLTexture( (void *)malloc( sizex * sizey * 4 ));
		SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		clear();
		SDL_Rect retanguloSource;
	    SDL_Rect retanguloDest;

	    retanguloSource.x=0;
        retanguloSource.y=0;
        retanguloSource.h=sizey;
        retanguloSource.w=sizex;
        retanguloDest.x=0;
		retanguloDest.y=0;
		retanguloDest.w=getBitmap()->w;
		retanguloDest.h=getBitmap()->h;
		SDL_BlitSurface(temp, &retanguloSource, getBitmap(), &retanguloDest);
		// cria texura
		//Todo: Habilitar a cópia do bitmap para outra window
		//SetWindow(copy.GetWindow());
		CreateTextureFromBitmap();
		SetBlendMode(copy._my_texture_draw_blend_mode);
		
	//_my_bitmap.own = new int;
	//*_my_bitmap.own = 1;
	}

}

#if 0
CBitmap::CBitmap( const CBitmap & copy, int sizex, int sizey, double accuracy ):
BaseCBitmap((Util::Thread::ScopedLock(copy.bitmapLock),copy)),own( NULL ),
error( false ),
GL3D(false),
GL2D(false),
path(""),
raw(NULL),
_my_bitmap(copy._my_bitmap),
_my_renderWindow(copy._my_renderWindow),
_my_texture_draw_blend_mode(copy._my_texture_draw_blend_mode),
_my_actual_draw_type(copy._my_actual_draw_type),
_my_default_draw_type(copy._my_default_draw_type),
_my_width(sizex),
_my_height(sizey),
createdFromPCX(copy.createdFromPCX),
bitPCXMaskColor(copy.bitPCXMaskColor){
	path = copy.getPath();
	SDL_Surface * temp = copy.getBitmap();
	own = new int;
	*own = 1;
    if(!copy.ClipRectText.empty()) {
			ClipRectText = copy.ClipRectText;

		}

	if ( temp->w > sizex || temp->h > sizey ){
		double bx = (double)temp->w / (double)sizex;
		double by = (double)temp->h / (double)sizey;
		double use;
		use = bx > by ? bx : by;
		int fx = (int)(temp->w / use);
		int fy = (int)(temp->h / use);
		setBitmap( CreateSurface( fx, fy ) );

		if ( ! getBitmap() ){
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Constructor //=> Could Not Create CBitmap " << endl;

			// own = false;
			// own = copy.own;
			// *own++;
			error = true;
			return;
		}else {
	        if (GLenabled){
				InitGL(fx, fy);  //inicializa openGL no modo 3D por default
				_my_bitmap._my_GLTexture = (void *)malloc( fx * fy * 4 );
				SetGLBitmap((Uint8 *) _my_bitmap._my_GLTexture);
			}
			//stretch_blit( temp, getBitmap(), 0, 0, temp->w, temp->h, 0, 0, getBitmap()->w, getBitmap()->h );
			SDL_Rect retanguloSource;
			SDL_Rect retanguloDest;

			retanguloSource.x=0;
			retanguloSource.y=0;
			retanguloSource.h=temp->h;
			retanguloSource.w=temp->w;
			retanguloDest.x=0;
			retanguloDest.y=0;
			retanguloDest.w=getBitmap()->w;
			retanguloDest.h=getBitmap()->h;

			::SDL_BlitSurface(temp, &retanguloSource, getBitmap(), &retanguloDest);
			//SetWindow(copy.GetWindow());
			CreateTextureFromBitmap();
			SetBlendMode(CSDLManager::GetInstance()->blendMode);
			
		}
	    } else {
		setBitmap( CreateSurface( temp->w, temp->h ) );
		if (GLenabled){
		InitGL(temp->w, temp->h);  //inicializa openGL no modo 3D por default
		_my_bitmap._my_GLTexture = (void *)malloc( temp->w * temp->h * 4 );
		SetGLBitmap((Uint8 *) _my_bitmap._my_GLTexture);
		}
		//blit( temp, getBitmap(), 0, 0, 0, 0, temp->w, temp->h );
		SDL_Rect retanguloSource;
	    SDL_Rect retanguloDest;
		retanguloSource.x=0;
        retanguloSource.y=0;
        retanguloSource.h=temp->h;
        retanguloSource.w=temp->w;
        retanguloDest.x=0;
		retanguloDest.y=0;
		retanguloDest.w=temp->w;
		retanguloDest.h=temp->h;

		::SDL_BlitSurface(temp, &retanguloSource, getBitmap(), &retanguloDest);
			//SetWindow(copy.GetWindow());
			CreateTextureFromBitmap();
			SetBlendMode(copy._my_texture_draw_blend_mode);
		    
	}
}

#endif
//! convert the surface to the current screen format
CBitmap::CBitmap( const CBitmap & copy, bool deep_copy ):
BaseCBitmap(/*(Util::Thread::ScopedLock(copy.bitmapLock),*/copy/*)*/,deep_copy),
error( false ),
GL3D(false),
GL2D(false),
path(""),
_my_renderWindow(copy._my_renderWindow),
_my_texture_draw_blend_mode(copy._my_texture_draw_blend_mode),
_my_actual_draw_type(copy._my_actual_draw_type),
_my_default_draw_type(copy._my_default_draw_type),
_my_width(copy._my_width),
_my_height(copy._my_height),
createdFromPCX(copy.createdFromPCX),
bitPCXMaskColor(copy.bitPCXMaskColor){
	path = copy.getPath();
	if ( deep_copy ){
        if(!copy.ClipRectText.empty()) {
			ClipRectText = copy.ClipRectText;
		}
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);
		SDL_PixelFormat *pixelFormat = SDL_AllocFormat(mode.format);

		SDL_Surface * his = ::SDL_ConvertSurface(copy.getBitmap(), pixelFormat, SDL_SWSURFACE);
		if (his) {
		setBitmap(his);


		}else {
			error=true;
			Debug::debug(Debug::error,__FUNCTION__) << "Could not create surface copy. Error: "<< SDL_GetError() << endl;
		}
		if ( ! getBitmap() ){
			cout << "Could not create bitmap" << endl;
			_my_bitmap.setTexture(NULL);
			error = true;
		}else {
			if (GLenabled){
				InitGL(his->w, his->h);  //inicializa openGL no modo 3D por default
				_my_bitmap.setGLTexture( (void *)malloc( his->w * his->h * 4 ));
				SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
			}


			//SetWindow(copy.GetWindow());
			CreateTextureFromBitmap();
			SetBlendMode(copy._my_texture_draw_blend_mode);
			
		}
	} else {
		setBitmap( copy.getBitmap() );
		if (GLenabled){
			InitGL(copy.getBitmap()->w, copy.getBitmap()->h);  //inicializa openGL no modo 3D por default
			_my_bitmap.setGLTexture( (void *)malloc( copy.getBitmap()->w * copy.getBitmap()->h * 4 ));
			SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		setTexture(copy.GetTexture());
		
	}

}

// Todo:  init GL neste construtor  e init default window no modo nao compatibility
CBitmap::CBitmap( const CBitmap & copy, int x, int y, int width, int height, BitmapType bitmapTypeToCopy):
BaseCBitmap(/*(Util::Thread::ScopedLock(copy.bitmapLock),*/copy/*)*/, true),
error( false ),
GL3D(false),
GL2D(false),
path(copy.getPath()),
_my_renderWindow(copy._my_renderWindow),
_my_texture_draw_blend_mode(copy._my_texture_draw_blend_mode),
_my_actual_draw_type(copy._my_actual_draw_type),
_my_default_draw_type(copy._my_default_draw_type),
_my_width(width),
_my_height(height),
createdFromPCX(copy.createdFromPCX),
bitPCXMaskColor(copy.bitPCXMaskColor)
{
	path = copy.getPath();
	SDL_Surface * temp = copy.getBitmap();
	setBitmap( CreateSurface( width, height ) );
	if ( ! getBitmap() ){
		error = true;
		cout << "Could not copy bitmap" << endl;
	}else {
	if (GLenabled){
		InitGL(width, height);  //inicializa openGL no modo 3D por default
		_my_bitmap.setGLTexture( (void *)malloc( width * height * 4 ));
		SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		clear();
		SDL_Rect retanguloSource;
	    SDL_Rect retanguloDest;

	    retanguloSource.x=x;
        retanguloSource.y=y;
        retanguloSource.h=height;
        retanguloSource.w=width;
        retanguloDest.x=0;
		retanguloDest.y=0;
		retanguloDest.w=getBitmap()->w;
		retanguloDest.h=getBitmap()->h;
		SDL_BlitSurface(temp, &retanguloSource, getBitmap(), &retanguloDest);
		// cria texura
		//Todo: Habilitar a cópia do bitmap para outra window
		
			//SetWindow(copy.GetWindow());
			CreateTextureFromBitmap();
			SetBlendMode(copy._my_texture_draw_blend_mode);
		   
	//own = new int;
	//*own = 1;
	}
#if 0
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"Copying CBitmap from: "<< &copy<<endl;
	if(!copy.ClipRectText.empty()) {
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"Copying CClipRetangle: "<< &copy<<endl;

		ClipRectText = copy.ClipRectText;
	}
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"End Copying CClipRetangle: "<< &copy<<endl;
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);
	SDL_PixelFormat *pixelFormat = SDL_AllocFormat(mode.format);

	SDL_Surface * his = ::SDL_ConvertSurface(copy.getBitmap(), pixelFormat, SDL_SWSURFACE);
	if ( x < 0 )
		x = 0;
	if ( y < 0 )
		y = 0;
	if ( width > his->w )
		width = his->w;
	if ( height > his->h )
		height = his->h;
	_my_actual_draw_type=copy._my_actual_draw_type;
	_my_default_draw_type=copy._my_default_draw_type;
	//!copy the bitmap
	if (his) {
   	setBitmap( his );
	}else {
		error=true;
		Debug::debug(Debug::error,__FUNCTION__) << "Could not create Bitmap Susface for copy. Error: " << SDL_GetError() << endl;
	}
	if ( ! getBitmap() ){
		Debug::debug(Debug::bitmap,__FUNCTION__) <<"Could not create sub-bitmap"<<endl;
		setBitmap( CreateSurface( 10, 10 ) );
		// clear( my_bitmap );
		clear();
	}else {
			//SetWindow(copy.GetWindow());
			SetBlendMode(copy._my_texture_draw_blend_mode);
		    if (bitmapTypeToCopy==USE_TEXTURE || bitmapTypeToCopy== BOTH_TEXTURE_SURFACE) CreateTextureFromBitmap();

			
	}
	// own = true;
	own = new int;
	*own = 1;
#endif
}

//não é mais utilizada. nem dentro do CBitmap
 SDL_Surface * CBitmap::RotatePicture ( int rotate, int flip, int smooth)
{
	SDL_Surface *screen = CreateSurface(this->getBitmap()->w,this->getBitmap()->h);
	SDL_Surface *picture=this->getBitmap();

	SDL_Surface *rotozoom_picture;
	SDL_Rect dest;
	int framecount, framemax, frameinc;
	double angle, zoomf, zoomfx, zoomfy;

	//fprintf(stderr, "%s\n", messageText);

	/* Rotate and display the picture */
	framemax=4*360; frameinc=1;
	for (framecount=-360; framecount<framemax; framecount += frameinc) {
		if ((framecount % 360)==0) frameinc++;
		//HandleEvent();
		//ClearScreen(screen);
		zoomf=(float)(framecount+2*360)/(float)framemax;
		zoomf=1.5*zoomf*zoomf;
		/* Are we in flipping mode? */
		if (flip) {
			/* Flip X factor */
			if (flip & 1) {
				zoomfx=-zoomf;
			} else {
				zoomfx=zoomf;
			}
			/* Flip Y factor */
			if (flip & 2) {
				zoomfy=-zoomf;
			} else {
				zoomfy=zoomf;
			}
			angle=framecount*rotate;
			//if (((framecount % 120)==0) || (delay>0)) {
			//	printf ("  Frame: %i   Rotate: angle=%.2f  Zoom: x=%.2f y=%.2f\n",framecount,angle,zoomfx,zoomfy);
			//}
			if ((rotozoom_picture=rotozoomSurfaceXY (picture, angle, zoomfx, zoomfy, smooth))!=NULL) {
				dest.x = (screen->w - rotozoom_picture->w)/2;;
				dest.y = (screen->h - rotozoom_picture->h)/2;
				dest.w = rotozoom_picture->w;
				dest.h = rotozoom_picture->h;
				if ( SDL_BlitSurface(rotozoom_picture, NULL, screen, &dest) < 0 ) {
					fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
					break;
				}
				SDL_FreeSurface(rotozoom_picture);
		 }
		} else {
			angle=framecount*rotate;
			if ((framecount % 120)==0) {
				printf ("  Frame: %i   Rotate: angle=%.2f  Zoom: f=%.2f \n",framecount,angle,zoomf);
			}
			if ((rotozoom_picture=rotozoomSurface (picture, angle, zoomf, smooth))!=NULL) {
				dest.x = (screen->w - rotozoom_picture->w)/2;;
				dest.y = (screen->h - rotozoom_picture->h)/2;
				dest.w = rotozoom_picture->w;
				dest.h = rotozoom_picture->h;
				if ( SDL_BlitSurface(rotozoom_picture, NULL, screen, &dest) < 0 ) {
					fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
					break;
				}
				SDL_FreeSurface(rotozoom_picture);
		 }
		}

		//stringRGBA(screen, 8, 8, messageText, 255, 255, 255, 255);

		/* Display by flipping screens */
		//SDL_Flip(SDL_GetVideoSurface());

		/* Maybe delay */
		//if (delay>0) {
		//	SDL_Delay(delay);
		//}
	}

	if (rotate) {
		/* Final display with angle=0 */
		//HandleEvent();
		//ClearScreen(screen);
		if (flip) {
			if ((rotozoom_picture=rotozoomSurfaceXY (picture, 0.01, zoomfx, zoomfy, smooth))!=NULL) {
				dest.x = (screen->w - rotozoom_picture->w)/2;;
				dest.y = (screen->h - rotozoom_picture->h)/2;
				dest.w = rotozoom_picture->w;
				dest.h = rotozoom_picture->h;
				if ( SDL_BlitSurface(rotozoom_picture, NULL, screen, &dest) < 0 ) {
					fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
					return NULL;
				}
				SDL_FreeSurface(rotozoom_picture);
			}
		} else {
			if ((rotozoom_picture=rotozoomSurface (picture, 0.01, zoomf, smooth))!=NULL) {
				dest.x = (screen->w - rotozoom_picture->w)/2;;
				dest.y = (screen->h - rotozoom_picture->h)/2;
				dest.w = rotozoom_picture->w;
				dest.h = rotozoom_picture->h;
				if ( SDL_BlitSurface(rotozoom_picture, NULL, screen, &dest) < 0 ) {
					fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
					return NULL;
				}
				SDL_FreeSurface(rotozoom_picture);
			}
		}

		//stringRGBA(screen, 8, 8, messageText, 255, 255, 255, 255);

		/* Display by flipping screens */
		// retirada para acabar com o módo de compatibilidade SDL 1.2
		//s SDL_Flip(SDL_GetVideoSurface());

		/* Maybe delay */
		//if (delay>0) {
		//	SDL_Delay(delay);
		//}
	}

	/* Pause for a sec */
	//SDL_Delay(1000);
	return screen;
}

 SDL_Surface* CBitmap::RotateSurface( double angle, double zoomx, double zoomy ) {

	    SDL_Surface *src = this->getBitmap();

        SDL_Surface *tmpSurface = rotozoomSurfaceXY(src,angle,zoomx,zoomy,SMOOTHING_OFF);
		SDL_FreeSurface(src);
		return tmpSurface;
		//SDL_SetColorKey(tmpSurface,SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(src->format,255,0,255));

        //rotozoom breaks color keys so we need to recreate the surface with the correct format
        //SDL_Surface *tmpFixedSurface = SDL_DisplayFormatAlpha(tmpSurface);
        //SDL_FreeSurface(tmpSurface);

       // return tmpFixedSurface;


    }

void CBitmap::rotateFromBitmap(double angle, double zoomx, double zoomy ) {

		setBitmap(RotateSurface(angle,zoomx,zoomy));
		CreateTextureFromBitmap();


	
}

void CBitmap::load( const string & str,int window ){
	_my_bitmap.releaseInternalBitmap();
	internalLoadFile( str.c_str(),window );
}
	/** @fn CBitmap::InternalLoadFile( const char * load_file )
@brief Função carrega uma imagem de um arquivo cria um objeto CBitmap
@param filename: nome do arquivo contendo a imagem
@return nada
@warning nenhum aviso
**/
void CBitmap::internalLoadFile( const char * load_file, int window ){
	path = load_file;
	setBitmap( load_image( load_file ) );
	if ( ! getBitmap() ){
		Debug::debug(Debug::bitmap,__FUNCTION__) <<"Could not load "<<load_file<<". Using default"<<endl;
		setBitmap( CreateSurface( 10, 10 ) );
		if ( ! getBitmap() ){
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Out of memory or SDL not initialized"<<endl;
			error = true;
			return;
		}else {
			if (GLenabled){
				InitGL(10, 10);  //inicializa openGL no modo 3D por default
				_my_bitmap.setGLTexture( (void *)malloc( 10 * 10 * 4 ));
				SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}

			// clear( my_bitmap );
			clear();
			// cout<<"Could not load "<<load_file<<endl;
			error = true;

		}
	}else {
		if (GLenabled){
			InitGL(_my_state->Screen[this->_my_renderWindow]->getBitmap()->w, _my_state->Screen[this->_my_renderWindow]->getBitmap()->h);  //inicializa openGL no modo 3D por default
			_my_bitmap.setGLTexture( (void *)malloc( getBitmap()->w * getBitmap()->h * 4  ));
			SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
		// cria texura
		//SetWindow(Screen[window]->GetWindow());
		CreateTextureFromBitmap(window);
		SetBlendMode(CSDLManager::GetInstance()->blendMode);
		
		
	// own = true;
	_my_width=getBitmap()->w;
	_my_height=getBitmap()->h;

	_my_bitmap.start();
	error = false;
	}
}
void CBitmap::convertpixelFormat() {
	SDL_Surface* temp = SDL_ConvertSurface(getBitmap(),Colors::getCurrentPixelFormat(),SDL_RLEACCEL);
	if(temp!=NULL) {
	SDL_FreeSurface(getBitmap());
	setBitmap(temp);
	}
}
void CBitmap::updateTexture()const {

	SDL_Rect rect;
	SDL_Surface *temp=getBitmap();
	/*
	Uint32 formato,RM,GM,BM,AM;
	int acess,w,h;
	int Bpp = temp->format->BitsPerPixel;
	int TextureBpp;
	SDL_QueryTexture(this->GetTexture(),&formato,&acess,&w,&h);
	SDL_PixelFormatEnumToMasks(formato, &TextureBpp,&RM,&GM,&BM,&AM);
	if(Bpp != TextureBpp) convertpixelFormat();*/
	//SDL_FreeSurface(getBitmap());
	//this->setBitmap(temp);
	//if(Bpp != TextureBpp) convertpixelFormat();
	rect.x= 0;
		rect.y=0;
		rect.w=temp->w;
		rect.h=temp->h;

	if (::SDL_UpdateTexture(GetTexture(),
                      &rect,
                      temp->pixels,
                      temp->pitch)<0) {
						  Debug::debug(Debug::error,__FUNCTION__)<<" Error Updating Texture: "<< SDL_GetError() <<endl;
	}


}




static CBitmap makeTemporaryBitmap(CBitmap *& temporary_bitmap,int w, int h){
    Debug::debug(Debug::bitmap,__FUNCTION__)<< "Starting to Make Temporary Bitmap" << endl;
	if (temporary_bitmap == NULL){
        temporary_bitmap = new CBitmap(w, h);
    } else if (temporary_bitmap->getWidth() < w || temporary_bitmap->getHeight() < h){
		int mw = MAX(temporary_bitmap->getWidth(), w);
        int mh = MAX(temporary_bitmap->getHeight(), h);
        delete temporary_bitmap;
        temporary_bitmap = new CBitmap(mw, mh);
    }
    if (temporary_bitmap == NULL){
        Debug::debug(Debug::error,__FUNCTION__)<<"*bug* temporary bitmap is null"<<endl;
    }
	Debug::debug(Debug::bitmap,__FUNCTION__)<< "END to Make Temporary Bitmap" << endl;
    return *temporary_bitmap;
}


CBitmap CBitmap::temporaryBitmap(int w, int h){
    return makeTemporaryBitmap(temporary_bitmap, w, h);
}

CBitmap CBitmap::temporaryBitmap2(int w, int h){
    return makeTemporaryBitmap(temporary_bitmap2, w, h);
}
void CBitmap::cleanupTemporaryBitmaps(){
	Debug::debug(Debug::bitmap,__FUNCTION__) << "BEGIN Cleaning Up Temporary Bitmaps" << endl;
	if (temporary_bitmap != NULL){
        delete temporary_bitmap;
        temporary_bitmap = NULL;
    }

    if (temporary_bitmap2 != NULL){
        delete temporary_bitmap2;
        temporary_bitmap2 = NULL;
    }
	Debug::debug(Debug::bitmap,__FUNCTION__) << "END Cleaning Up Temporary Bitmaps" << endl;
}

void CBitmap::save( const string & str ){
	//save_bitmap( str.c_str(), getBitmap(), NULL );
	::SDL_SaveBMP(getBitmap(), str.c_str());
}


void CBitmap::setBitmapMode( BitmapType mode )const {
	if (mode == DRAW_TYPE_DEFAULT) {
		_my_actual_draw_type = _my_default_draw_type;
	}else {
		_my_default_draw_type = _my_actual_draw_type;
		_my_actual_draw_type = mode;
	}
	}

void CBitmap::setClipRect( int x1, int y1, int x2, int y2 ) const {

		switch(this->getBitmapMode()) {

				case DRAW_TYPE_TEXTURE:
						setTextureClipRect(x1,y1,x2,y2);

					break;

				case DRAW_TYPE_SURFACE:
					setSurfaceClipRect( x1, y1, x2, y2 );
				break;

				case DRAW_TYPE_TEX_SURF:
					setTextureClipRect(x1,y1,x2,y2);
					setSurfaceClipRect(x1,y1,x2,y2);
				break;
				default:
				break;
				}

	
}

void CBitmap::setTextureClipRect( int x1, int y1, int x2, int y2 ) const {

		if(x1!=0 && y1!=0 && x2!=getWidth() && y2 !=getHeight()){
							ClipRectText.x=x1;
							ClipRectText.y=y1;
							ClipRectText.width=x2-x1;
							ClipRectText.height=y2-y1;
							Debug::debug(Debug::bitmap,__FUNCTION__) << "                  x:" << x1 << endl;
							Debug::debug(Debug::bitmap,__FUNCTION__) << "                  y:" << y1 <<endl;
							Debug::debug(Debug::bitmap,__FUNCTION__) << "                  w:" << x2-x1 <<endl;
							Debug::debug(Debug::bitmap,__FUNCTION__) << "                  h:" << y2 - y1 <<endl;
		}else {
							Debug::debug(Debug::bitmap,__FUNCTION__) << "Reseting" << endl;
							ClipRectText.clear();
		}


}
void CBitmap::setSurfaceClipRect( int x1, int y1, int x2, int y2 ) const{
	SDL_Rect rect;
	rect.x=x1;
	rect.y=y1;
	rect.w=x2-x1;
	rect.h=y2-y1;
	::SDL_SetClipRect( getBitmap(), &rect );

}

void CBitmap::getClipRect( int& x1, int &y1, int& x2, int& y2 ) const {
			switch(this->getBitmapMode()) {

				case DRAW_TYPE_TEXTURE:
					getTextureClipRect(x1,y1,x2,y2);

					break;

				case DRAW_TYPE_SURFACE:
					getSurfaceClipRect( x1, y1, x2, y2 );
				break;

				case DRAW_TYPE_TEX_SURF:
					//todo Verificar se os valores são os mesmos e escolher um
					// seguindo algum critério
					//getTextureClipRect(x1,y1,x2,y2);
					getSurfaceClipRect(x1,y1,x2,y2);
				break;
				default:
				break;
				}

}
void CBitmap::getSurfaceClipRect(int & x1, int & y1, int & x2, int & y2) const {
    SDL_Surface *temp= getBitmap();
	x1 = temp->clip_rect.x;
    y1 = temp->clip_rect.y;
	x2 = x1+temp->clip_rect.w;
    y2 = y1+temp->clip_rect.h;
}

void CBitmap::getTextureClipRect(int & x1, int & y1, int & x2, int & y2) const {
   
	x1 = ClipRectText.x;
    y1 = ClipRectText.y;
	x2 = x1+ClipRectText.width;
    y2 = y1+ClipRectText.height;
				
							
				
}


/* resize the internal bitmap. not guaranteed to destroy the internal bitmap */
void CBitmap::resize( const int width, const int height ){

    /* if internal bitmap is already the proper size, do nothing */
    if ( getWidth() == width && getHeight() == height ){
        return;
    }

    SDL_Surface * b = CreateSurface( width, height );
    //::stretch_blit( getBitmap(), b, 0, 0, getBitmap()->w, getBitmap()->h, 0, 0, b->w, b->h );
       SDL_Rect * retanguloSource = new SDL_Rect;
	    SDL_Rect * retanguloDest = new SDL_Rect;
		retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=getBitmap()->h;
        retanguloSource->w=getBitmap()->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=b->w;
		retanguloDest->h=b->h;

		::SDL_BlitSurface(getBitmap(), retanguloSource, b, retanguloDest);
        delete retanguloSource;
	    delete retanguloDest;
		_my_bitmap.releaseInternalBitmap();

    _my_bitmap.start();
    setBitmap( b );
    
}


void CBitmap::debugSelf() const{
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"CBitmap: "<<endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"Self = "<< getBitmap() <<endl;
	//Debug::debug(Debug::bitmap,__FUNCTION__) <<"Own = "<< _my_bitmap.own <<" : "<< *_my_bitmap.own <<endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) <<"Path = "<<path<<endl;
}

CBitmap & CBitmap::operator=( const CBitmap & copy ){
	_my_bitmap.releaseInternalBitmap();
	path = copy.getPath();
	GL3D=copy.GL3D;
	GL2D=copy.GL2D;
	_my_bitmap=copy._my_bitmap;
	
	ClipRectText=copy.ClipRectText;
	bitPCXMaskColor=copy.bitPCXMaskColor;
	createdFromPCX=copy.createdFromPCX;

	if (GLenabled){
		InitGL(copy.getBitmap()->w, copy.getBitmap()->h);  //inicializa openGL no modo 3D por default
		_my_bitmap.setGLTexture( (void *)malloc( copy.getBitmap()->w * copy.getBitmap()->h * 4  ));
		SetGLBitmap((Uint8 *) _my_bitmap.GetGLTexture());
		}
	return *this;
}

/** @fn CBitmap::CBitmap()
@brief Desstrutor da Classe CBitmap
* destrói um objeto carregando a imagem do arquivo
* aqui deve limpar toda a memória
@param load_file: caminho para o arquivo da imagem
@return nenhum.
@warning ainda incompleta
**/
CBitmap::~CBitmap(){
//	Debug::debug(Debug::error,__FUNCTION__) << " DESTRUCTOR  Own: " << (own!=NULL ? *own :0) << endl;
	if(GLenabled) {
		for (int i=0; i<=MAX_TEXTURES ; i++)
			glDeleteTextures (1,(GLuint *) &texture[i]);
	}
	

}




void CBitmap::detach(){

	/*
	if ( own ){
		(*own)--;

		if ( *own == 0 ){
			destroy_bitmap( getBitmap() );
			delete own;
		}
	}
	*/
	_my_bitmap.releaseInternalBitmap();
}


CBitmap CBitmap::greyScale(){
    CBitmap grey(getWidth(), getHeight());

    for (int x = 0; x < getWidth(); x++){
        for (int y = 0; y < getHeight(); y++){
	    int pixel = getPixelSurface(x, y);
            int val = (int)((0.299*Colors::getRed(pixel) + 0.587*Colors::getGreen(pixel) + 0.114*Colors::getBlue(pixel) + 0.5) + 16);
            if (val > 255){
                val = 255;
            }
			grey.putPixelSurface(x, y, Colors::makeColor(val, val, val));
        }
    }

    return grey;
}

bool CBitmap::getError(){
	return error;
}

bool CBitmap::getError() const{
	return error;
}
/*
int CBitmap::getWidth(){
	return my_bitmap->w;
}

int CBitmap::getHeight(){
	return my_bitmap->h;
}

*/
void CBitmap::locksurface() {
	CBitmap::acquire();
}

void CBitmap::unlocksurface() {
	CBitmap::release();
}
void CBitmap::acquire(){
	if (SDL_MUSTLOCK(getBitmap()))
		::SDL_LockSurface(getBitmap());
	//acquire_bitmap( getBitmap() );
}

void CBitmap::release(){
	if (SDL_MUSTLOCK(getBitmap()))
		::SDL_UnlockSurface(getBitmap());
	//release_bitmap( getBitmap() );
}
/*
void CBitmap::floodfill( const int x, const int y, const int color ) const {
	::floodfill( getBitmap(), x, y, color );
}

void CBitmap::drawCharacter( const int x, const int y, const int color, const int background, const CBitmap & where ) const {
	::draw_character_ex( where.getBitmap(), getBitmap(), x, y, color, background );
} */





void CBitmap::hueBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="hueBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::hueBlender;
}


void CBitmap::dodgeBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="dodgeBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::dodgeBlender;
}
void CBitmap::luminanceBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="luminancenBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::luminanceBlender;
}

void CBitmap::colorBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="colorBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::colorBlender;
}

void CBitmap::burnBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="burnBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::burnBlender;
}
void CBitmap::screenBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="screenBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::screenBlender;
}

void CBitmap::invertBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="invertBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::invertBlender;
}

void CBitmap::dissolveBlender( int r, int g, int b, int a ){
	Colors::globalBlend.blendName="dissolveBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::dissolveBlender;
}
void CBitmap::addBlender( int r, int g, int b, int a ){
    Colors::globalBlend.blendName="addBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
	Colors::globalBlend.currentBlender = Colors::addBlender;
}

void CBitmap::multiplyBlender( int r, int g, int b, int a ){
    Colors::globalBlend.blendName="multiplyBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
    Colors::globalBlend.currentBlender = Colors::multiplyBlender;
}

void CBitmap::differenceBlender( int r, int g, int b, int a ){
    Colors::globalBlend.blendName="differenceBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
    Colors::globalBlend.currentBlender = Colors::differenceBlender;
}
void CBitmap::transBlender( int r, int g, int b, int a ){
    Colors::globalBlend.blendName="transBlender";
	Colors::globalBlend.red = r;
    Colors::globalBlend.green = g;
    Colors::globalBlend.blue = b;
    Colors::globalBlend.alpha = a;
    Colors::globalBlend.currentBlender = Colors::transBlender;
}

void CBitmap::alphaBlender(int source, int dest ){
    Colors::globalBlend.blendName="AlphaBlender";
	Colors::globalBlend.sourcePixel = source;
    Colors::globalBlend.destPixel = dest;
	Colors::globalBlend.red = 0;
	Colors::globalBlend.blue = 0;
    Colors::globalBlend.green = 0;
    Colors::globalBlend.alpha = 0;
    Colors::globalBlend.currentBlender = Colors::alphaBlender;
}

int CBitmap::SetBlendMode(SDL_BlendMode blendmode)const{
	int errorcode=0;
	SDL_SetTextureBlendMode(GetTexture(), blendmode);
	return errorcode;

}

void CBitmap::setDrawBlendMode( SDL_BlendMode mode ) const{
	switch(this->getBitmapMode()) {

	case DRAW_TYPE_TEXTURE:
	_my_texture_draw_blend_mode=mode;
	if(SDL_SetRenderDrawBlendMode(getMyRender(),mode)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
	
	break;

	case DRAW_TYPE_SURFACE:
		if (mode == CBitmap::MODE_SOLID)
			surfaceDrawingMode = mode;
		else
			surfaceDrawingMode = CBitmap::MODE_TRANS;
	break;

	case DRAW_TYPE_TEX_SURF:
        if (mode == CBitmap::MODE_SOLID)
			surfaceDrawingMode = mode;
		else
			surfaceDrawingMode = CBitmap::MODE_TRANS;
		if(true) {
		_my_texture_draw_blend_mode=mode;
		if(SDL_SetRenderDrawBlendMode(getMyRender(),mode)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		}
		break;
	default:
		break;
	}
}




double CBitmap::getScale(){
    /* the game is pretty much hard coded to run at 320 scaled upto 640
     * and then scaled to whatever the user wants, but as long as
     * 320 and 640 remain this number will be 2.
     * maybe calculate this at some point
     */
	
    return 2;
	
    if (_my_state->Scaler != NULL && _my_state->Buffer != NULL){
        double x1 = _my_state->Scaler->getWidth();
        double x2 = _my_state->Buffer->getWidth();
        return x2 / x1;
    }
    return 1;

}




	/*
 * Return the pixel value at (x, y)
funcionando ok
 */
Uint32 CBitmap::getPixelSurface( const int x,const  int y) const{
	SDL_Surface *bmp = getBitmap();
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
#if 0
Uint32 CBitmap::getPixel(SDL_Surface *bmp, const int x,const  int y) {

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
#endif
//Le uma linha de bits da Surface e armazena no vetor vec
//
//
void CBitmap::readLine( vector< int > & vec, int y ){
	int col;
	if ( y >= 0 && y < getBitmap()->h ){
		for ( int q = 0; q < getBitmap()->w; q++ ){
			// int col = my_bitmap->line[ y ][ q ];
			col= getPixelSurface( q,y );
			vec.push_back( col );
		}
	}
}

/*
int CBitmap::setGfxModeText(){
	return setGraphicsMode( GFX_TEXT, 0, 0 );
} */

int CBitmap::setGfxModeFullscreen( int x, int y ){
	return 1;//setGraphicsMode( SDL_FULLSCREEN, x, y );
}

int CBitmap::setGfxModeWindowed( int x, int y ){
	return 1;//setGraphicsMode( SDL_RESIZABLE, x, y );
}





int CBitmap::getDefaultColorkey(){
	const static int mask = Colors::makeColor(255, 0, 255);
    return mask;
}

int CBitmap::makeColor(int r, int g, int b){
	return Colors::makeColor(r,g,b);
}

void CBitmap::putPixelNormal(int x, int y, int pixel) const {
    putPixelSurface( x, y, pixel);

}

//! putpixel só funciona para surfaces
void CBitmap::putPixelSurface( int x, int y, Uint8 r, Uint8 g, Uint8 b) const {
	Colors::putPixelSurface( this->getBitmap(),x, y, r,g,b);

}

/*
 * Set the pixel at (x, y) to the given value
  */
void CBitmap::putPixelSurface( int x, int y, Uint32 pixel, bool translucent) const {

	Colors::putPixelSurface(this->getBitmap(),x,y,pixel,translucent);

}




// solução de colocar pixels na surface: http://slouken.blogspot.com/2011/02/streaming-textures-with-sdl-13.html
void CBitmap::putPixelTexture( int x, int y, Uint8 r, Uint8 g, Uint8 b) const {

	Uint32 pixel = Colors::makeColor(r,g,b);
	putPixelTexture( x, y, pixel);

}

/*
 * Set the pixel at (x, y) to the given value
  */
void CBitmap::putPixelTexture( int x, int y, Uint32 pixel, bool translucent) const {
	SDL_Surface *bmp = getBitmap();
	SDL_Texture *mytexture = this->GetTexture();

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
void CBitmap::printf( int x, int y, int color, FONT * f, const char * str, ... ) const{

	char buf[512];
	va_list ap;

	va_start(ap, str);
	uvszprintf(buf, sizeof(buf), str, ap);
	va_end(ap);

	textout_ex( getBitmap(), f, buf, x, y, color, -1);
}

void CBitmap::printf( int x, int y, int color, const Font * const f, const char * str, ... ) const{

	char buf[512];
	va_list ap;

	va_start(ap, str);
	uvszprintf(buf, sizeof(buf), str, ap);
	va_end(ap);

	textout_ex( getBitmap(), f->getInternalFont(), buf, x, y, color, -1);
}

void CBitmap::printf( int x, int y, int color, const Font * const f, const string & str ) const{
	printf( x, y, color, f, str.c_str() );
}

void CBitmap::printf( int x, int y, int color, const Font & f, const string & str ) const{
	printf( x, y, color, &f, str );
}

void CBitmap::printfNormal( int x, int y, int color, const char * str, ... ) const{

	char buf[512];
	va_list ap;

	va_start(ap, str);
	uvszprintf(buf, sizeof(buf), str, ap);
	va_end(ap);

	textout_ex( getBitmap(), font, buf, x, y, color, -1);

}

void CBitmap::printfNormal( int x, int y, int color, const string & str ) const{
	printfNormal( x, y, color, "%s", str.c_str() );
}
*/






void CBitmap::border( int min, int max, int color ) const {
	int w = getWidth();
	int h = getHeight();
	for ( int i = min; i < max; i++ ){
	polygon().rectangle( i, i, w - 1 - i, h - 1 - i, color );
	}
}


/*
int CBitmap::getPixel( int x, int y ){
	if ( x >= 0 && x < my_bitmap->w && y >= 0 && y <= my_bitmap->h )
		return _getpixel16( my_bitmap, x, y );
	return -1;
}
*/






/*
void CBitmap::clear(){
	this->fill( 0,0,0 );
}
*/



//este método só trabalha com surface tanto no modo de compatibilidade quanto no modo normal SDL 1.3
/*
void CBitmap::draw( const int x, const int y, const CBitmap & where ) const {
	if (this->_my_actual_draw_type == this->DRAW_TYPE_SURFACE ){
	//este método só trabalha com surface tanto no modo de compatibilidade quanto no modo normal SDL 1.3
	Blit( x,  y, where );
	//The basic drawing operation assumes the default transparency color (255,0,255) in the sprite bitmap:
	}else {
		Debug::debug(Debug::menu,__FUNCTION__) << "This methos only work with surface. CHANGE BITMAP DRAW TYPE MODE "<< endl;
	}
}
*/
void CBitmap::draw(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, CFilter * filter, const CBitmap & where) const {
    //this only works for surface
	const BitmapType mode = this->_my_actual_draw_type;
	//CBitmap sub(*this, startWidth, startHeight, width, height,USE_SURFACE);

	setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	//sub.
	draw(x + startWidth, y + startHeight, filter, where);
	setBitmapMode(mode);

}
// old
//void CBitmap::draw(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, const CBitmap & where) const {
// 	CBitmap sub(*this, startWidth, startHeight, width, height,USE_SURFACE);
//    sub.Blit(x + startWidth, y + startHeight, where);
//}

void CBitmap::draw(const int x, const int y, CFilter * filter, const CBitmap & where) const {

	const int mode = getBitmapMode();
	unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	if (mode == DRAW_TYPE_SURFACE) {
		draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_NO_FLIP, filter,mask);
	}else if (mode == DRAW_TYPE_TEXTURE){
		draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_NO_FLIP, filter,mask);
	}else if (mode == this->DRAW_TYPE_TEX_SURF) {
		draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_NO_FLIP, filter,mask);
	    draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_NO_FLIP, filter,mask);

	}

}

/*
void CBitmap::drawHFlip(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, const CBitmap & where) const {

    //CBitmap sub(*this, startWidth, startHeight, width, height);
    // sub.drawHFlip(x + startWidth, y + startHeight, where);
    //sub.drawHFlip(x + startWidth, y + startHeight, where);


    CBitmap sub(*this, getWidth() - width, getHeight() - height, getWidth() - startWidth, getHeight() - startHeight);
    // sub.drawHFlip(x + startWidth, y + startHeight, where);
    // sub.drawHFlip(x + startWidth, y + startHeight, where);
    sub.drawHFlip(x + startWidth, y + startHeight, where);
} */


void CBitmap::drawHFlip(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, CFilter * filter, const CBitmap & where) const {
    CBitmap sub(*this, getWidth() - width, getHeight() - height, getWidth() - startWidth, getHeight() - startHeight);
    sub.drawHFlip(x + startWidth, y + startHeight, filter, where);
}




void CBitmap::drawHFlip(const int x, const int y, CFilter * filter, const CBitmap & where) const {
const int mode = getBitmapMode();
unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	if (mode == DRAW_TYPE_SURFACE) {
		draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_H_FLIP, filter,mask);
	}else if (mode == DRAW_TYPE_TEXTURE){
		draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_H_FLIP, filter,mask);
	}else if (mode == this->DRAW_TYPE_TEX_SURF) {
		draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_H_FLIP, filter,mask);
	    draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_H_FLIP, filter,mask);

	}
}



void CBitmap::drawVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const {
const int mode = getBitmapMode();
unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();
	if (mode == DRAW_TYPE_SURFACE) {
		draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP, filter,mask);
	}else if (mode == DRAW_TYPE_TEXTURE){
		draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP, filter,mask);
	}else if (mode == this->DRAW_TYPE_TEX_SURF) {
		draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP, filter,mask);
	    draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP, filter,mask);

	}

}



void CBitmap::drawHVFlip( const int x, const int y, CFilter * filter, const CBitmap & where ) const {
const int mode = getBitmapMode();
unsigned int mask;
	if (createdFromPCX) {
		mask = getPCXMaskColor();
	}else mask = getDefaultColorkey();

	if (mode == DRAW_TYPE_SURFACE) {
		draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP, filter,mask);
	}else if (mode == DRAW_TYPE_TEXTURE){
		draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP, filter,mask);
	}else if (mode == this->DRAW_TYPE_TEX_SURF) {
		draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP, filter,mask);
	    draw_sprite_ex32(where.GetTexture(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP, filter,mask);

	}

}

/*

void CBitmap::drawTrans( const int x, const int y, const CBitmap & where ) const {
    draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_NO_FLIP);
}

void CBitmap::drawTransHFlip( const int x, const int y, const CBitmap & where ) const {
    draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_H_FLIP);
}

void CBitmap::drawTransVFlip( const int x, const int y, const CBitmap & where ) const {
    draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_V_FLIP);
}

void CBitmap::drawTransHVFlip( const int x, const int y, const CBitmap & where ) const {
    draw_sprite_ex32(where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, SPRITE_V_FLIP | SPRITE_H_FLIP);
} */
//===================
/*
void CBitmap::drawHFlip( const int x, const int y, const CBitmap & where ) const {
	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_H_FLIP );
	::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_X,SMOOTHING_OFF);
	Blit( x,  y, where );
	//The basic drawing operation assumes the default transparency color (255,0,255) in the sprite bitmap:
	// ::draw_sprite_h_flip( where.getBitmap(), getBitmap(), x, y );
}

void CBitmap::drawHFlip(const int x, const int y, const int startWidth, const int startHeight, const int width, const int height, const CBitmap & where) const {
    //
    //CBitmap sub(*this, startWidth, startHeight, width, height);
    // sub.drawHFlip(x + startWidth, y + startHeight, where);
    //sub.drawHFlip(x + startWidth, y + startHeight, where);


    CBitmap sub(*this, getWidth() - width, getHeight() - height, getWidth() - startWidth, getHeight() - startHeight);
    // sub.drawHFlip(x + startWidth, y + startHeight, where);
    // sub.drawHFlip(x + startWidth, y + startHeight, where);
    sub.drawHFlip(x + startWidth, y + startHeight, where);
}

void CBitmap::drawVFlip( const int x, const int y, const CBitmap & where ) const {
	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP );
	::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_Y,SMOOTHING_OFF);
	Blit( x,  y, where );
	//The basic drawing operation assumes the default transparency color (255,0,255) in the sprite bitmap:
	// ::draw_sprite_h_flip( where.getBitmap(), getBitmap(), x, y );
}

void CBitmap::drawHVFlip( const int x, const int y, const CBitmap & where ) const {
	::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_XY,SMOOTHING_OFF);
	Blit( x,  y, where );
	//The basic drawing operation assumes the default transparency color (255,0,255) in the sprite bitmap:
	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_NORMAL, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP );
}*/

/*
void CBitmap::drawLit( const int x, const int y, const int level, const CBitmap & where ) const{
	::draw_lit_sprite( where.getBitmap(), getBitmap(), x, y, level );
}


void CBitmap::drawTrans( const int x, const int y, const CBitmap & where ) const{
	// ::draw_trans_sprite( where.getBitmap(), getBitmap(), x, y );
	Blit( x,  y, where );
	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_NO_FLIP );
}

void CBitmap::drawTransHFlip( const int x, const int y, const CBitmap & where ) const {
	//int angle=0;
	//::rotozoomSurfaceXY (where.getBitmap(), angle, zoomfx, zoomfy, smooth)
	::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_X,SMOOTHING_OFF);
	Blit( x,  y, where );
	//todo ver onde colocar a scrreen x,y,
	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_H_FLIP );
}

void CBitmap::drawTransVFlip( const int x, const int y, const CBitmap & where ) const {
	::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_Y,SMOOTHING_OFF);
	Blit( x,  y, where );
	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_V_FLIP );
}

void CBitmap::drawTransHVFlip( const int x, const int y, const CBitmap & where ) const {
	::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_XY,SMOOTHING_OFF);
	Blit( x,  y, where );

	//draw_sprite_ex32( where.getBitmap(), getBitmap(), x, y, CBitmap::SPRITE_TRANS, CBitmap::SPRITE_V_FLIP | CBitmap::SPRITE_H_FLIP );
}
*/
void CBitmap::drawRotate( const int x, const int y, const int angle, const CBitmap & where ){
	//::fixed fang = itofix( (360 - angle) % 360 * 256 / 360 );
	::rotozoomSurface(getBitmap(), (double )angle, 0, SMOOTHING_OFF);
	BlitSurface( x,  y, where );
	//::RotatePicture(getBitmap(),where.getBitmap(),ROTATE_OFF,FLIP_XY,SMOOTHING_OFF);
	//::rotate_sprite( where.getBitmap(), getBitmap(), x, y, fang );
	//todo draw the sprite to the position x,y
}

void CBitmap::drawPivot( const int centerX, const int centerY, const int x, const int y, const int angle, const CBitmap & where ){
    //::fixed fang = ftofix( (double)((360 - angle) % 360) * 256.0 / 360.0 );
    //::pivot_sprite( where.getBitmap(), getBitmap(), x, y, centerX, centerY, fang );
	//draw colocando centro dado centerx,centery do sprite na posicão x,y
	//	roda o bitmap angle
}

void CBitmap::drawPivot( const int centerX, const int centerY, const int x, const int y, const int angle, const double scale, const CBitmap & where ){
    //::fixed fscale = ftofix(scale);
    //::fixed fang = ftofix( (double)((360 - angle) % 360) * 256.0 / 360.0 );
    //::pivot_scaled_sprite( where.getBitmap(), getBitmap(), x, y, centerX, centerY, fang, fscale );
}

void CBitmap::drawStretched( const int x, const int y, const int new_width, const int new_height, const CBitmap & who )const{
	//SDL_Surface * bmp = who.getBitmap();
	//::masked_stretch_blit( getBitmap(), bmp, 0, 0, getBitmap()->w, getBitmap()->h, x,y, new_width, new_height );
}
void CBitmap::drawStretched(const CBitmap & who) const {
    drawStretched(0, 0, who.getWidth(), who.getHeight(), who);
}




void CBitmap::applyTrans(){
    SDL_Surface *temp=getBitmap();
    if (temp->format->palette) {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    } else {
        switch (temp->format->BitsPerPixel) {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE, (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE, (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
             SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }
	if(this->GetTexture()) {
			updateTexture();
		//this->CreateTextureFromBitmap();
	}
	
}

void CBitmap::applyTrans(int color){
	int r = Colors::getRed(color);
	int g = Colors::getGreen(color);
	int b = Colors::getBlue(color);
	SDL_Surface *temp=getBitmap();
	// set color key magenta
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format,r,g,b));
	if(this->GetTexture()) this->CreateTextureFromBitmap();
	
}

void CBitmap::applyDefTrans(){

	SDL_Surface *temp=getBitmap();
	// set color key magenta
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format,255,0,255));
	if(this->GetTexture()) this->CreateTextureFromBitmap();
	
}

void CBitmap::applyAlphaTrans(const int alpha){
    
		switch(this->getBitmapMode()) { //textura e surface

				case DRAW_TYPE_TEXTURE:
					SDL_SetTextureAlphaMod(GetTexture(),alpha);
					break;

				case DRAW_TYPE_SURFACE:
					SDL_SetSurfaceAlphaMod(getBitmap(), alpha);
					if(this->GetTexture()) this->CreateTextureFromBitmap();
					//SetBlendMode(CSDLManager::GetInstance()->blendMode);
					break;

				case DRAW_TYPE_TEX_SURF:
					SDL_SetSurfaceAlphaMod(getBitmap(), alpha);
					SDL_SetTextureAlphaMod(GetTexture(),alpha);
					break;
				default:
				break;
				}

}
//este método não é utilizado em nenhum lugar.
//eu acho que ele está errado
void CBitmap::drawMaskSurface( const int _x, const int _y, const CBitmap & where ){
	unsigned int mask = CBitmap::getDefaultColorkey();
	for ( int x = 0; x < getWidth(); x++ ){
		for ( int y = 0; y < getHeight(); y++ ){
			if ( getPixelSurface( x,y ) == mask ){
				where.putPixelSurface( x+_x, y+_y, mask );
			}
		}
	}
}

void CBitmap::StretchBy2( const CBitmap & where ){
	SDL_Surface * bmp = where.getBitmap();
    SDL_Rect * retanguloSource = new SDL_Rect;
	SDL_Rect * retanguloDest = new SDL_Rect;
	if ( where.getWidth() == getWidth() && where.getHeight() == getHeight() ){
		//::blit( getBitmap(), bmp, 0, 0, 0, 0, getBitmap()->w, getBitmap()->h );

		retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=getBitmap()->h;
        retanguloSource->w=getBitmap()->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=getBitmap()->h;
		retanguloDest->h=getBitmap()->w;

		::SDL_BlitSurface(getBitmap(), retanguloSource, bmp, retanguloDest);


		return;
	}

	if ( where.getWidth() != getWidth()*2 ||
		where.getHeight() != getHeight()*2 ){
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"Wrong dimensions"<<endl;
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"My:  "<< getWidth() << " " << getHeight() << endl;
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"Him: "<<where.getWidth()<< " " << where.getHeight()<<endl;
			return;
	}
	// debug
	//::stretch_blit( getBitmap(), bmp, 0, 0, getBitmap()->w, getBitmap()->h, 0, 0, bmp->w, bmp->h );
	retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=getBitmap()->h;
        retanguloSource->w=getBitmap()->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=bmp->w;
		retanguloDest->h=bmp->h;

		::SDL_BlitSurface(getBitmap(), retanguloSource, bmp, retanguloDest);
		// não sei se é para limpar ou não
		//::SDL_FreeSurface(bmp);

	// fblend_2x_stretch( my_bitmap, bmp, 0, 0, 0, 0, my_bitmap->w, my_bitmap->h);
	// scale2x_allegro( my_bitmap, bmp, 2 );
	// debug
    delete retanguloSource;
	delete retanguloDest;
}

void CBitmap::StretchBy4( const CBitmap & where ){

	SDL_Surface * bmp = where.getBitmap();
	SDL_Rect * retanguloSource = new SDL_Rect;
	    SDL_Rect * retanguloDest = new SDL_Rect;
	if ( where.getWidth() != getWidth()*4 ||
		where.getHeight() != getHeight()*4 ){
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"Wrong dimensions"<<endl;
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"My:  "<< getWidth() << " " << getHeight() << endl;
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"Him: "<<where.getWidth()<< " " << where.getHeight()<<endl;
			Debug::debug(Debug::bitmap,__FUNCTION__)<<"Scaled: "<<getWidth()*4<<" "<< getHeight()*4<<endl;
			return;
	}
	// fblend_2x_stretch( my_bitmap, bmp, 0, 0, 0, 0, my_bitmap->w, my_bitmap->h);
	// scale4x_allegro( my_bitmap, bmp, 2 );
	//::stretch_blit( getBitmap(), bmp, 0, 0, getBitmap()->w, getBitmap()->h, 0, 0, bmp->w, bmp->h );
        retanguloSource->x=0;
        retanguloSource->y=0;
        retanguloSource->h=getBitmap()->h;
        retanguloSource->w=getBitmap()->w;
        retanguloDest->x=0;
		retanguloDest->y=0;
		retanguloDest->w=bmp->w;
		retanguloDest->h=bmp->h;

		::SDL_BlitSurface(getBitmap(), retanguloSource, bmp, retanguloDest);
		delete retanguloSource;
	    delete retanguloDest;
}


//!este método é apenas para surfaces
//! Faz o bitmap ficar do tamanho da surface destino
void CBitmap::Stretch( const CBitmap & where ) const {
    if (getWidth() == where.getWidth() && getHeight() == where.getHeight()){
        BlitSurface(where);
    } else {
        Stretch(where, 0, 0, getWidth(), getHeight(), 0, 0, where.getWidth(), where.getHeight());
    }
}


//!este método é apenas para surfaces
//! Faz o bitmap ficar do tamanho da surface destino
void CBitmap::Stretch( const CBitmap & where, const int sourceX, const int sourceY, const int sourceWidth, const int sourceHeight, const int destX, const int destY, const int destWidth, const int destHeight ) const {

	double angle=0.01;
	int smooth=1000;

    SDL_Surface * src = getBitmap();
    SDL_Surface * dst = where.getBitmap();
    if (dst!=NULL) {
		float xscale = (float) destWidth / (float) sourceWidth;
    float yscale = (float) destHeight / (float) sourceHeight;
    SDL_SetColorKey(src, SDL_TRUE, getDefaultColorkey());
	//::SPG_TransformX(src, dst, 0, xscale, yscale, sourceX, sourceY, destX, destY, SPG_NONE);
	//Todo: ver se funciona com CBitmap::SDL_ScaleSurface
	dst=rotozoomSurfaceXY (src, angle, (double) xscale,(double) yscale, smooth);
	}else {
	Debug::debug(Debug::bitmap,__FUNCTION__) << "ERROR // Destination CBitmap NULL " << endl;
	}
}


void CBitmap::Blit( const string & xpath ) const {
	CBitmap duh( xpath );
	duh.BlitSurface( *this );
}


void CBitmap::BlitMasked( const int mx, const int my, const int width, const int height, const int wx, const int wy, const CBitmap & where ) const {
	SDL_Surface * bmp = where.getBitmap();
	/*
	if (source surface has SDL_SRCALPHA set) {
    if (source surface has alpha channel (that is, format->Amask != 0))
        blit using per-pixel alpha, ignoring any colour key
    else {
        if (source surface has SDL_SRCCOLORKEY set)
            blit using the colour key AND the per-surface alpha value
        else
            blit using the per-surface alpha value
    }
} else {
    if (source surface has SDL_SRCCOLORKEY set)
        blit using the colour key
    else
        ordinary opaque rectangular blit
}
*/

	///usado para não imprimir as partes transparentes do bitmap.
	//::masked_blit( getBitmap(), bmp, mx, my, wx, wy, width, height );
        SDL_Rect retanguloSource;
	    SDL_Rect retanguloDest;;

	    retanguloSource.x=mx;
        retanguloSource.y=my;
        retanguloSource.w=width;
        retanguloSource.h=height;
        retanguloDest.x=wx;
		retanguloDest.y=wy;
		retanguloDest.w=width;
		retanguloDest.h=height;
		::SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format,255,0,255));
		::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);

}

void CBitmap::BlitFromScreen(const int x, const int y) const {

	_my_state->Screen[this->_my_renderWindow]->BlitSurface(x, y, getWidth(), getHeight(), 0, 0, *this);
}

//! blit to defalut render window
void CBitmap::Blit() const {

	if (this->_my_actual_draw_type == this->DRAW_TYPE_SURFACE){
		Debug::debug(Debug::error,__FUNCTION__) << "This method only works to Texture. Change Draw_type mode" << endl;

	}else{
	this->Blit( 0, 0 );
	}
}


void CBitmap::Blit(int x, int y) const {
	SDL_Rect retanguloDest;
    //Get offsets
    retanguloDest.x = x;
    retanguloDest.y = y;
	retanguloDest.w=this->getBitmap()->w;
	retanguloDest.h=this->getBitmap()->h;

	//Debug::debug(Debug::bitmap,__FUNCTION__) << "[Destino(window): "<<GetWindow() <<" ] x= "<<x <<" , y= "<<y <<" , w= " << retanguloDest.w << ", h= " <<retanguloDest.h << endl;
	if(SDL_RenderCopy(getMyRender(),this->GetTexture(), NULL, &retanguloDest)!=0)
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;


}

//! Blit to Default render Window
//! this method only works to SDL 1.3 with texture
void CBitmap::Blit( const int OrigX, const int OrigY, const int width, const int height, const int DestX, const int DestY,int DestW, int DestH) const {
	SDL_Rect retanguloSource;
	SDL_Rect retanguloDest;
		//Get offsets
	 retanguloSource.x=OrigX;
     retanguloSource.y=OrigY;
     retanguloSource.w=width;
     retanguloSource.h=height;
	/*	if (!where.ClipRectText.empty()) {
			if (wx<=!where.ClipRectText.getX1())
			  retanguloDest->x=!where.ClipRectText.getX1();
			else if (wx>=(!where.ClipRectText.getX1()+!where.ClipRectText.getW()))
			  retanguloDest->x=!where.ClipRectText.getX1()+!where.ClipRectText.getW();
			if (wy<=!where.ClipRectText.getY1())
				 retanguloDest->y=!where.ClipRectText.getY1();
			else if (wy>=(!where.ClipRectText.getY1()+!where.ClipRectText.getH()))
				retanguloDest->y=!where.ClipRectText.getY1()+!where.ClipRectText.getH();
			retanguloDest->w=!where.ClipRectText.getW();
		    retanguloDest->h=!where.ClipRectText.getH();
		}else {  */
	 if (DestW== -1) DestW = this->getWidth();
	 if (DestW== -1) DestH = this->getHeight();

		retanguloDest.x=DestX;
		retanguloDest.y=DestY;
		retanguloDest.w=DestW;
		retanguloDest.h=DestH;
	//}
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Blitting to render: [Origem] x = " <<retanguloSource.x<<" , "<<  " y= "<< retanguloSource.y  <<", w= " << retanguloSource.w << ", h= " << retanguloSource.h  <<" // [Destino(window): "<<GetWindow() <<" ] x= "<<retanguloDest.x <<" , y= "<<retanguloDest.y <<" , w= " << retanguloDest.w << ", h= " <<retanguloDest.h << endl;
			
		if(SDL_RenderCopy(getMyRender(),this->GetTexture(), &retanguloSource, &retanguloDest)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;




}


//! blit to default render window stretching the texture
//! only work without the compatibility mode
void CBitmap::BlitStretched() const {
	if (_my_actual_draw_type == DRAW_TYPE_SURFACE){
		Debug::debug(Debug::error,__FUNCTION__) << "This method only works to Texture. Change Bitmap Draw_type mode" << endl;

	}else{
	this->BlitStretched( 0, 0 );
	}

}
//! Método que só funciona com textura
void CBitmap::BlitStretched(int x, int y) const {

	Debug::debug(Debug::bitmap,__FUNCTION__) << "[Destino(window): "<<GetWindow() <<" ] x= "<<x <<" , y= "<<y <<  endl;
	if(SDL_RenderCopy(getMyRender(),this->GetTexture(), NULL, NULL)!=0)
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

		
}


//Todo: suporte a mais de uma janela

void CBitmap::BlitToScreen() const {

		switch(this->getBitmapMode()) { //textura e surface

				case DRAW_TYPE_TEXTURE:
					Debug::debug(20,__FUNCTION__) << "Blit to window = " << GetWindow() << endl;

					/* Update the screen! */
					SDL_RenderPresent(getMyRender());
					break;
                // Não é permitido surface blit to screen nesse módulo
				case DRAW_TYPE_SURFACE:
					//BlitToScreen( 0 , 0 );
					break;

				case DRAW_TYPE_TEX_SURF:
					Debug::debug(20,__FUNCTION__) << "Update Texture First then Blit to window = " << GetWindow() << endl;
					updateTexture();
					/* Update the screen! */
					SDL_RenderPresent(getMyRender());
					break;
				default:
				break;
				}



}

void CBitmap::BlitRenderToScreen(int renderWindow) {


	Debug::debug(Debug::bitmap,__FUNCTION__) << "Update Texture First then Blit to window = " << renderWindow << endl;
	/* Update the screen! */
	SDL_RenderPresent(_my_state->renderers[renderWindow]);


}

#if 0
//usada no modo de SDL 1.2
void CBitmap::BlitToScreen(const int upper_left_x, const int upper_left_y) const {

	switch (_my_actual_draw_type) {
	case DRAW_TYPE_SURFACE:
		if ( Scaler == NULL ){
			this->Blit( upper_left_x, upper_left_y, *_my_state->Screen[this->_my_renderWindow] );
		} else {
        this->Blit( upper_left_x, upper_left_y, *Buffer );
        Buffer->Stretch( *Scaler );
        Scaler->Blit( 0, 0, 0, 0, *_my_state->Screen[this->_my_renderWindow] );
		}
		if (mMainConsole!=NULL) CON_DrawConsole(mMainConsole);
		::SDL_Flip(_my_state->Screen[this->_my_renderWindow]->getBitmap());
		break;
	default:
		Debug::debug(Debug::error,__FUNCTION__) << "This method only works to Surface. Change Bitmap Draw_type mode" << endl;



	}

}
#endif
//-------------- Métodos de Blit (draw) que utilizam o Blit do SDL----------------


void CBitmap::BlitSurface( const CBitmap & where ) const {
	this->BlitSurface( 0, 0, where );
}
//! This method only works with Surfaces tanto no modo de compatibiidade quanto no modo normal SDL 1.3
void CBitmap::BlitSurface( const int SrcX, const int SrcY, const int width, const int height, const int DstX, const int DstY, const CBitmap & where ) const {

		SDL_Rect retanguloSource;
	    SDL_Rect retanguloDest;
		retanguloSource.x=SrcX;
        retanguloSource.y=SrcY;
        retanguloSource.w=width;
        retanguloSource.h=height;

		if (!where.ClipRectText.empty()) {
			if (DstX<=!where.ClipRectText.getX1())
			  retanguloDest.x=!where.ClipRectText.getX1();
			else if (DstX>=(!where.ClipRectText.getX1()+!where.ClipRectText.getW()))
			  retanguloDest.x=!where.ClipRectText.getX1()+!where.ClipRectText.getW();
			if (DstY<=!where.ClipRectText.getY1())
				 retanguloDest.y=!where.ClipRectText.getY1();
			else if (DstY>=(!where.ClipRectText.getY1()+!where.ClipRectText.getH()))
				retanguloDest.y=!where.ClipRectText.getY1()+!where.ClipRectText.getH();
			retanguloDest.w=!where.ClipRectText.getW();
		    retanguloDest.h=!where.ClipRectText.getH();
		}else {
		retanguloDest.x=DstX;
		retanguloDest.y=DstY;
		retanguloDest.w=width;
		retanguloDest.h=height;
		}

		SDL_Surface * bmp = where.getBitmap();
		Debug::debug(Debug::bitmap,__FUNCTION__) << "[Origem] x = 0, y= 0, w= " << retanguloSource.w << ", h= " << retanguloSource.h  <<" // [Destino( " <<&where<<  " )] x=0, y=0, w= " << retanguloDest.w << ", h= " <<retanguloDest.h << endl;
		::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);


}
void CBitmap::BlitSurface( const int SrcX, const int SrcY, const int width, const int height, const int DstX, const int DstY) const {


		BitmapType mode =_my_actual_draw_type;
        setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		//Todo Verificar se dá para atualizar só uma parte da Textura
		updateTexture(); //update texture with the work done on the bitmap
		Blit(SrcX, SrcY, width, height, DstX, DstY); //put texture to the renderer
		setBitmapMode(mode);
		//SDL_Surface * bmp = where.getBitmap();
		//::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);


}
void CBitmap::BlitSurface( ) const {
		int width=this->getHeight();
		int height=this->getHeight();
		BitmapType mode =_my_actual_draw_type;
        setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		//Todo Verificar se dá para atualizar só uma parte da Textura
		updateTexture(); //update texture with the work done on the bitmap
		Blit(0,0, width, height, 0,0); //put texture to the renderer
		setBitmapMode(mode);
		//SDL_Surface * bmp = where.getBitmap();
		//::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);


}
void CBitmap::BlitSurfaceToScreen( const int SrcX, const int SrcY, const int width, const int height) const {


		BitmapType mode =_my_actual_draw_type;
        setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		//Todo Verificar se dá para atualizar só uma parte da Textura
		updateTexture(); //update texture with the work done on the bitmap
		Blit(SrcX, SrcY, width, height,SrcX, SrcY); //put texture to the renderer
		BlitToScreen();  //put the render on the screen
		setBitmapMode(mode);

		//SDL_Surface * bmp = where.getBitmap();
		//::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);


}

void CBitmap::BlitSurfaceToScreen( const int SrcX, const int SrcY, const int width, const int height, const int DstX, const int DstY) const {


		BitmapType mode =_my_actual_draw_type;
        setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		//Todo Verificar se dá para atualizar só uma parte da Textura
		updateTexture(); //update texture with the work done on the bitmap
		Blit(SrcX, SrcY, width, height, DstX, DstY); //put texture to the renderer
		BlitToScreen();  //put the render on the screen
		setBitmapMode(mode);

		//SDL_Surface * bmp = where.getBitmap();
		//::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);


}


//! este método só trabalha com surface tanto no modo de compatibilidade quanto no modo normal SDL 2.0
void CBitmap::BlitSurface( const int x, const int y, const CBitmap & where ) const {
	//Debug::debug(Debug::bitmap,__FUNCTION__) << "Blit to: " << &where << endl;
	SDL_Surface * bmp = where.getBitmap();
	SDL_Rect retanguloSource;
	SDL_Rect retanguloDest;
		retanguloSource.x=0;
        retanguloSource.y=0;
        retanguloSource.h=getBitmap()->h;
        retanguloSource.w=getBitmap()->w;
		if (!where.ClipRectText.empty()) {
			if (x<=!where.ClipRectText.getX1())
			  retanguloDest.x=!where.ClipRectText.getX1();
			else if (x>=(!where.ClipRectText.getX1()+!where.ClipRectText.getW()))
			  retanguloDest.x=!where.ClipRectText.getX1()+!where.ClipRectText.getW();
			if (y<=!where.ClipRectText.getY1())
				 retanguloDest.y=!where.ClipRectText.getY1();
			else if (y>=(!where.ClipRectText.getY1()+!where.ClipRectText.getH()))
				retanguloDest.y=!where.ClipRectText.getY1()+!where.ClipRectText.getH();
			retanguloDest.w=!where.ClipRectText.getW();
		    retanguloDest.h=!where.ClipRectText.getH();
		}else {
		retanguloDest.x=x;
		retanguloDest.y=y;
		retanguloDest.w=getBitmap()->w;
		retanguloDest.h=getBitmap()->h;
		}

		Debug::debug(Debug::bitmap,__FUNCTION__) << "Blitting from ( CBitmap:: "<< this <<")(Surface:: "<<getBitmap()<<") x = 0, y= 0, w= " << retanguloSource.w << ", h= " << retanguloSource.h  <<" // Blitting To: " <<  " [( CBitmap:: " << &where <<  ")(Surface:: "<< &bmp<<")] x=0, y=0, w= " << retanguloDest.w << ", h= " <<retanguloDest.h << endl;
		::SDL_BlitSurface(getBitmap(), &retanguloSource, bmp, &retanguloDest);


}

void CBitmap::BlitSurface( const int SrcX, const int SrcY, const int DstX, const int DstY, const CBitmap & where ) const {

	    SDL_Rect * retanguloSource = new SDL_Rect;
	    SDL_Rect * retanguloDest = new SDL_Rect;
	    retanguloSource->x=SrcX;
        retanguloSource->y=SrcY;
        retanguloSource->h=getBitmap()->h;
        retanguloSource->w=getBitmap()->w;
        if (!where.ClipRectText.empty()) {
			if (DstX<=!where.ClipRectText.getX1())
			  retanguloDest->x=!where.ClipRectText.getX1();
			else if (DstX>=(!where.ClipRectText.getX1()+!where.ClipRectText.getW()))
			  retanguloDest->x=!where.ClipRectText.getX1()+!where.ClipRectText.getW();
			if (DstY<=!where.ClipRectText.getY1())
				 retanguloDest->y=!where.ClipRectText.getY1();
			else if (DstY>=(!where.ClipRectText.getY1()+!where.ClipRectText.getH()))
				retanguloDest->y=!where.ClipRectText.getY1()+!where.ClipRectText.getH();
			retanguloDest->w=!where.ClipRectText.getW();
		    retanguloDest->h=!where.ClipRectText.getH();
		}else {
		retanguloDest->x=DstX;
		retanguloDest->y=DstY;
		retanguloDest->w=where.getBitmap()->w;
		retanguloDest->h=where.getBitmap()->h;
		}
		
		SDL_Surface * bmp = where.getBitmap();
		Debug::debug(Debug::bitmap,__FUNCTION__) << "[Origem] x = 0, y= 0, w= " << retanguloSource->w << ", h= " << retanguloSource->h  <<" // [Destino(Screen)] x=0, y=0, w= " << retanguloDest->w << ", h= " <<retanguloDest->h << endl;
		::SDL_BlitSurface(getBitmap(), retanguloSource, bmp, retanguloDest);
			
		
		//	Debug::debug(Debug::bitmap,__FUNCTION__) << "[Origem] x = 0, y= 0, w= " << retanguloSource->w << ", h= " << retanguloSource->h  <<" // [Destino(window): "<<where.GetWindow() <<" ] x= "<<wx <<" , y= "<<wy <<" , w= " << retanguloDest->w << ", h= " <<retanguloDest->h << endl;
		//	if(SDL_RenderCopy(getMyRender(),GetTexture(), retanguloSource, retanguloDest)!=0)
		//	Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		//	break;

		
		
		delete retanguloSource;
	    delete retanguloDest;
}

void CBitmap::BlitSurfaceToScreen(bool stretched){
 // Finally render to screen
	    BitmapType mode =_my_actual_draw_type;
        setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
		updateTexture(); //update texture with the work done on the bitmap
		if(!stretched ) Blit();
		else BlitStretched(); //put the work from texture to the render
		BlitToScreen();  //put the render on the screen
		setBitmapMode(mode);


}

void CBitmap::BlitAreaToScreen(const int upper_left_x, const int upper_left_y) const {

    if ( _my_state->Scaler != NULL ){
        double mult_x = (double) _my_state->Scaler->getWidth() / (double) SCALE_X;
        double mult_y = (double) _my_state->Scaler->getHeight() / (double) SCALE_Y;

        int x = (int)(upper_left_x * mult_x);
        int y = (int)(upper_left_y * mult_y);
        int w = (int)(this->getWidth() * mult_x);
        int h = (int)(this->getHeight() * mult_y);

        // printf("ux %d uy %d uw %d uh %d. x %d y %d w %d h %d\n", upper_left_x, upper_left_y, getWidth(), getHeight(), x, y, w, h );

        this->Stretch( *_my_state->Scaler, 0, 0, this->getWidth(), this->getHeight(), x, y, w, h );

        CBitmap tmp(*_my_state->Scaler, x, y, w, h );
        tmp.BlitSurface( x, y, *_my_state->Screen[this->_my_renderWindow] );

        // Scaler->Blit( x, y, w, h, *Screen[0] );
    } else {
        this->Blit( upper_left_x, upper_left_y); //! blit to default render window

    }
}


#if 0
#define SGE_DLS_BLENDER BLENDER_FUNC
#define SGE_DTS_BLENDER BLENDER_FUNC
#define SGE_MAKE_DLS_BLENDER(a) _blender_func16
#define SGE_MAKE_DTS_BLENDER() _blender_func16
#define SGE_PIXEL_PTR unsigned short*
#define SGE_OFFSET_PIXEL_PTR(p,x) ((SGE_PIXEL_PTR) (p) + (x))
#define SGE_INC_PIXEL_PTR(p) ((p)++)
#define SGE_INC_PIXEL_PTR_EX(p,d)  ((p) += d)
#define SGE_GET_MEMORY_PIXEL(p)    (*(p))
#define SGE_IS_SPRITE_MASK(b,c)    ((unsigned long) (c) == (unsigned long) (b)->vtable->mask_color)
#define SGE_IS_SPRITE_MASK(b,n)       ((*(b))(_blender_col_16, (n), _blender_alpha))
#define SGE_IS_SPRITE_MASK(p)           bmp_read16((uintptr_t) (p))
#define SGE_DTS_BLEND(b,o,n)       ((*(b))((n), (o), _blender_alpha))
#define SGE_PUT_PIXEL(p,c)         bmp_write16((uintptr_t) (p), (c))
#define SGE_PUT_MEMORY_PIXEL(p,c)  (*(p) = (c))
#define SGE_SET_ALPHA(a)           (_blender_alpha = (a))
#endif
/* defined at allegro/include/internal/aintern.h:457 */
///extern EXTERNAL_VARIABLE BLENDER_FUNC _blender_func16;
/* defined at allegro/include/internal/aintern.h:466 */
extern EXTERNAL_VARIABLE int _blender_col_16;
/* defined at allegro/include/internal/aintern.h:470 */
extern EXTERNAL_VARIABLE int _blender_alpha;


/*

/// mix pixels with the given color in with each non-masking pixel in dst
static void applyTrans16(SDL_Surface * dst, const int color){
  //  int y1 = 0;
  //  int y2 = dst->h;
  //  int x1 = 0;
  //  int x2 = dst->w - 1;

  //  if (dst->clip){
        y1 = dst->clip_rect.y;  ///top
        y2 = dst->clip_rect.y + dst->clip_rect.h  - 1;  ///botton
        x1 = dst->clip_rect.x;     ///left
		x2 = dst->clip_rect.x  + dst->clip_rect.w - 1; ///right
   // }

    SGE_DTS_BLENDER trans_blender;
    trans_blender = SGE_MAKE_DTS_BLENDER();
    if (dst->id & (BMP_ID_VIDEO | BMP_ID_SYSTEM)) {
    } else {
        for (int y = y1; y < y2; y++) {
            SGE_PIXEL_PTR d = SGE_OFFSET_PIXEL_PTR(bmp_write_line(dst, y), x1);
            for (int x = x2; x >= x1; SGE_INC_PIXEL_PTR_EX(d,1), x--) {
                unsigned long c = SGE_GET_MEMORY_PIXEL(d);
                if (!SGE_IS_SPRITE_MASK(dst, c)) {
                    //#define SGE_DTS_BLEND(b,o,n)       ((*(b))((n), (o), _blender_alpha))
					//c = (*trans_blender)(c, color, _blender_alpha)
					c = SGE_DTS_BLEND(trans_blender, color, c);
                    SGE_PUT_MEMORY_PIXEL(d, c);
                }
            }
        }
    }
}



*/


void CBitmap::DrawRect16(Sint16 x,Sint16 y,Sint16 x1,Sint16 y1,Uint8 R,Uint8 G,Uint8 B)
{
    SDL_Surface *work = getBitmap();
	Uint16 Color;
    Uint16 *lpData=NULL;
    Uint16 nPitch;
    Sint16 temp;
    Sint16 w,h;

    Color=SDL_MapRGB(_my_state->Screen[this->_my_renderWindow]->getBitmap()->format,R,G,B);

    SDL_LockSurface(work);

    lpData=(Uint16*)work->pixels;
    nPitch=work->pitch/2;

    if(x>x1)
    {
        temp=x1;
        x1=x;
        x=temp;

    }

    if(y>y1)
    {
        temp=y1;
        y1=y;
        y=temp;

    }
    ///Clipping
    if(y1>SCREENY_LIMIT)
        y1=SCREENY_LIMIT;

    if(x1>SCREENX_LIMIT)
        x1=SCREENX_LIMIT;

    if(x<0)
        x=0;

    if(y<0)
        y=0;
   ///Endof Clipping

    temp=y;
    w=x+(x1-x);

    for(;y<y1;y++)
    {
       lpData[y*nPitch+x]=Color;
       lpData[y*nPitch+w]=Color;

    }

    y=temp;
    h=y+(y1-y);

    for(;x<x1;x++)
    {
       lpData[y*nPitch+x]=Color;
       lpData[h*nPitch+x]=Color;
    }


    SDL_UnlockSurface(work);


}

void CBitmap::DrawRect32(Sint32 x,Sint32 y,Sint32 x1,Sint32 y1,Uint8 R,Uint8 G,Uint8 B)
{
    SDL_Surface *work = getBitmap();
	Uint32 Color;
    Uint32 *lpData=NULL;
    Uint32 nPitch;
    Sint32 temp;
    Sint32 w,h;

    Color=SDL_MapRGB(_my_state->Screen[this->_my_renderWindow]->getBitmap()->format,R,G,B);

    SDL_LockSurface(work);

    lpData=(Uint32*)work->pixels;
    nPitch=work->pitch/4;  //! numero de bytes por pixel

    if(x>x1)
    {
        temp=x1;
        x1=x;
        x=temp;

    }

    if(y>y1)
    {
        temp=y1;
        y1=y;
        y=temp;

    }
    ///Clipping
    if(y1>SCREENY_LIMIT)
        y1=SCREENY_LIMIT;

    if(x1>SCREENX_LIMIT)
        x1=SCREENX_LIMIT;

    if(x<0)
        x=0;

    if(y<0)
        y=0;
   ///Endof Clipping

    temp=y;
    w=x+(x1-x);

    for(;y<y1;y++)
    {
       lpData[y*nPitch+x]=Color;
       lpData[y*nPitch+w]=Color;

    }

    y=temp;
    h=y+(y1-y);

    for(;x<x1;x++)
    {
       lpData[y*nPitch+x]=Color;
       lpData[h*nPitch+x]=Color;
    }


    SDL_UnlockSurface(work);


}

///Draw a string to video
void CBitmap::DrawText(int x,int y,char *strText,...)
{
   SDL_Surface *work = getBitmap();
	char string[255];                  /// Temporary string
  //int fonte = 1;
  va_list ap;                /// Pointer To List Of Arguments
  va_start(ap, strText);         /// Parses The String For Variables
  std::vsprintf(string, strText, ap); /// Converts Symbols To Actual Numbers
  va_end(ap);
  //m_Text.Render(string, work, fonte, x,y);
  DT_DrawText(string,work,0,x,y);

}

///this is the MMX version of Scale2x only uses this if we have a CPU with MMX support
// ok para surfaces de 16 bpp
// todo: converter para 32 bpp
void CBitmap::FilterImage()
{
    SDL_Surface *work = getBitmap();
	SDL_Surface *screen = _my_state->Screen[this->_my_renderWindow]->getBitmap();
	if(SDL_LockSurface(work) < 0)
        Debug::debug(Debug::bitmap,__FUNCTION__) << "Was not able to lock work surface"<< endl;

    if(SDL_LockSurface(screen) < 0)
        Debug::debug(Debug::bitmap,__FUNCTION__) << "Was not able to lock screen surface"<<endl;

   conv16 dst0;
   conv16 dst1;
   conv16 Scr0;
   conv16 Scr1;
   conv16 Scr2;
   //scale2x_uint16 *dst0,*dst1;
   //scale2x_uint16 *scr0,*scr1,*scr2;


   dst0=(scale2x_uint16*)screen->pixels;
   dst1=dst0+(screen->pitch/2);

   Scr0=(scale2x_uint16*)work->pixels;
   Scr1=Scr0 + (work->pitch/2);
   Scr2=Scr1 + (work->pitch/2);

   scale2x_16_def(dst0,dst1,Scr0,Scr1,Scr2,CConfiguration::screenWidth.getInteger());

  for(int i=0;i<239;i++)
  {
      scale2x_16_def(dst0,dst1,Scr0,Scr1,Scr2,CConfiguration::screenWidth.getInteger());
      dst0+=(screen->pitch);
      dst1+=(screen->pitch);

      Scr0=Scr1;
      Scr1=Scr2;
      Scr2+=(work->pitch/2);


  }

   SDL_UnlockSurface(work);
   SDL_UnlockSurface(screen);

   ///Clear the MMX
   //scale2x_mmx_emms();

}

void CBitmap::Draw()
{
   FilterImage();

    //scale2x(work,screen);
    //SDL_BlitSurface(work,NULL,screen,NULL);
   //if (mMainConsole!=NULL)
   //CON_DrawConsole(mMainConsole);
   //retirada para acabar com o modo de compatibiolidade SDL 1.2
 //s   SDL_Flip(_my_state->Screen[this->_my_renderWindow]->getBitmap()/*SDL_GetVideoSurface()*/);

}


//! método mantido apenas por referência
SDL_Surface * CBitmap::ConvertImageToSDL(BYTE *byImageData,Colors::ColorDefinition* ColorPallet)
{
    SDL_Surface *temp= this->getBitmap();
    unsigned short * lpData=NULL;  //unsigned short = WORD
    short nPitch;
	short nWidth=temp->w;
	short nHeight=temp->h;

    //const SDL_VideoInfo* myPointer = ::SDL_GetVideoInfo();

    //temp=CreateSurface(nWidth,nHeight);
	//temp=SDL_CreateRGBSurface(SDL_SWSURFACE,nWidth,nHeight,16,myPointer->vfmt->Rmask
      //                                            ,myPointer->vfmt->Gmask
        //                                          ,myPointer->vfmt->Bmask
          //                                        ,myPointer->vfmt->Amask);

	//if(temp==NULL)
      //  Debug::debug(Debug::bitmap,__FUNCTION__) << "CreateSurface failed");

    SDL_LockSurface(temp);

    /// Todo: Wrong Pitch  must be korrect
    lpData=(unsigned short*)temp->pixels;
    nPitch=temp->pitch/2 ;


    ///It is a 8bit image with a ColorPallet
	if(ColorPallet!=NULL)
	{
		for(short x=0;x<nWidth;x++)
		{
			for(short y=0;y<nHeight;y++)
			{

				lpData[y*nPitch+x] = (unsigned short) SDL_MapRGB(_my_state->Screen[this->_my_renderWindow]->getBitmap()->format,
                                                      ColorPallet[byImageData[x + y * nWidth]].r,
                                                      ColorPallet[byImageData[x + y * nWidth]].g,
                                                      ColorPallet[byImageData[x + y * nWidth]].b);
			}


		}

	}
	else
	{
	///this is for a true Color PCX image(24bit)
		for(short x=0;x<nWidth;x++)
		{
			for(short y=0;y<nHeight;y++)
			{
				lpData[y*nPitch+x] = (unsigned short) SDL_MapRGB(_my_state->Screen[this->_my_renderWindow]->getBitmap()->format,
                                                       byImageData[x + (y * nWidth*3)],
                                                       byImageData[x + nWidth   + (y * nWidth*3)],
                                                       byImageData[x + (nWidth*2) + (y * nWidth*3)]);

			}


		}
	}

	SDL_UnlockSurface(temp);
	return temp;
}
//! método mantido apenas por referência
SDL_Surface * CBitmap::ConvertImageToSDL32(BYTE *byImageData,Colors::ColorDefinition* ColorPallet)
{
    SDL_Surface *temp= this->getBitmap();
    Uint32* lpData=NULL;
    short nPitch;
	short nWidth=temp->w;
	short nHeight=temp->h;
	SDL_PixelFormat formato;
	int bpp;
		SDL_DisplayMode mode;
		int n = SDL_GetNumVideoDisplays();
		if (n>1) {
			Debug::debug(Debug::bitmap,__FUNCTION__) <<"Assuming display number 1 from "<< n<<endl;
		}
		SDL_GetDesktopDisplayMode(0,&mode);
		SDL_PixelFormatEnumToMasks(mode.format, &bpp, &formato.Rmask, &formato.Gmask, &formato.Bmask, &formato.Amask);
		formato.BitsPerPixel= bpp;

				switch(bpp) {
				case  8:
					formato.BytesPerPixel=1;
					formato.palette=NULL; //todo: arrumar o pallete aqui
				break;
				case 15:
					formato.BytesPerPixel=2;
					formato.palette=NULL;
				break;
				case 16:
					formato.BytesPerPixel=2;
					formato.palette=NULL;
				break;
				case 24:
					formato.BytesPerPixel=3;
					formato.palette=NULL;
				break;
				case 32:
					formato.BytesPerPixel=4;
					formato.palette=NULL;
					break;
			}
	
    SDL_LockSurface(temp);

    /// Todo: Wrong Pitch  must be korrect
    lpData=(Uint32*)temp->pixels;
    nPitch=temp->pitch/4 ;


    ///It is a 8bit image with a ColorPallet
	if(ColorPallet!=NULL)
	{
		for(short x=0;x<nWidth;x++)
		{
			for(short y=0;y<nHeight;y++)
			{
				
				lpData[y*nPitch+x] = (Uint32) SDL_MapRGB(&formato,
                                                      ColorPallet[byImageData[x + y * nWidth]].r,
                                                      ColorPallet[byImageData[x + y * nWidth]].g,
                                                      ColorPallet[byImageData[x + y * nWidth]].b);

				
				}


		}

	}
	else
	{
	///this is for a true Color PCX image(24bit)
		for(short x=0;x<nWidth;x++)
		{
			for(short y=0;y<nHeight;y++)
			{
				

				lpData[y*nPitch+x] = (Uint32) SDL_MapRGB(&formato,
                                                       byImageData[x + (y * nWidth*3)],
                                                       byImageData[x + nWidth   + (y * nWidth*3)],
                                                       byImageData[x + (nWidth*2) + (y * nWidth*3)]);

				

			}


		}
	}

	SDL_UnlockSurface(temp);
	return temp;
}
//! only used on paralax2
CBitmap *CBitmap::ConvetToDysplayFormat(){
	//Todo converter para o formato do dysplay no  modo (SDL 1.3)

#if 0
	SDL_Surface *temp;
	temp= ::SDL_DisplayFormat(this->getBitmap());
	if (temp !=NULL) {
	CBitmap *temp_bitmap = new CBitmap(temp,false,false);
	return temp_bitmap;
	} else {
	return NULL;
	}
#endif
return NULL;

}
 Colors::ColorDefinition CBitmap::getColor(Uint32 pixel) {
	 Colors::ColorDefinition cor;
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);
	SDL_PixelFormat *pixelFormat = SDL_AllocFormat(mode.format);
	if (pixelFormat == NULL) {
		Debug::debug(Debug::error,__FUNCTION__) << "Error: " << SDL_GetError() <<endl;

	}
	SDL_GetRGB(pixel, pixelFormat, &cor.r, &cor.g, &cor.b);
	if (pixelFormat !=NULL) SDL_FreeFormat(pixelFormat);
    return cor;
}
/// Objetivo: Fazer uma ampliação da imagem
///Parâmetros:
///Surface: The original surface the caller of the function wants to be scaled.
///Width: The width the caller wants the scaled surface to be (we use Uint16 because this is SDL’s standard for width).
///Height: The height the caller wants the scaled surface to be (we use Uint16 because this is SDL’s standard for height).
/// Retorno: Uma surface da imagem ampliada

SDL_Surface* CBitmap::SDL_ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height) const {
/// http://www.sdltutorials.com/sdl-scale-surface/
   if(!Surface || !Width || !Height)
        return 0;

    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

    double  _stretch_factor_x = (static_cast<double>(Width)  / static_cast<double>(Surface->w)),
        _stretch_factor_y = (static_cast<double>(Height) / static_cast<double>(Surface->h));

    for(Sint32 y = 0; y < Surface->h; y++)
        for(Sint32 x = 0; x < Surface->w; x++)
            for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    Colors::putPixelSurface(_ret, static_cast<Sint32>(_stretch_factor_x * x) + o_x,
                        static_cast<Sint32>(_stretch_factor_y * y) + o_y, Colors::getPixel(Surface, x, y));

    return _ret;

}
//===================SDL 1.3===========================
// FUNÇÕES Portadas para o SDL 1.3                   //
//=====================================================

// Init Methods

/** @fn CBitmap::setGraphicsMode(SDLState_t *state,int i)
@brief Função que inicializa A Classe CBitmap e um modo de vídeo com a largura e altura passadas e também com os modificadores SDL
@param mode: flags SDL
/sa http://sdl.beuc.net/sdl.wiki/SDL_SetVideoMode
@param width: largura da tela a inicializar
@param height: altura da tela a inicializar
@return 0: se não ocorrer nenhum erro
        1: se não conseguir inicializar o modo de vídeo requerido
@warning sempre inicializa a tela na profundidade de 32 bits por padrão
		 Não usar CBitmap sem antes rodar este método
**/
int CBitmap::init(SDLState_t *state,int i){
	int ret=1;
	//CBitmap * tempBitmap=NULL;
    int width = state->window_infos[i]->w;
	int height = state->window_infos[i]->h;
    int mode = state->flags;
	_my_state=state;

	Debug::debug(Debug::bitmap,__FUNCTION__) << "Parameters: " << endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "state: " << state << endl;
    Debug::debug(Debug::bitmap,__FUNCTION__) << "mode: " << mode << endl;
    Debug::debug(Debug::bitmap,__FUNCTION__) << "width: " << width << endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "height: " << height << endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Screen["<<i<<"]: " << state->Screen[i]  << endl;


		SDL_Window *ok = state->windows[i];
        Debug::debug(Debug::bitmap,__FUNCTION__) << "ok: " << ok << endl;
		if ( ok != NULL ){
		ret =0;
		//if ((mode & SDL_OPENGL)== SDL_OPENGL)
			GLenabled=false; //só no modo 1.2
        if (SCALE_X == 0){
            SCALE_X = width;
        }
        if (SCALE_Y == 0){
            SCALE_Y = height;
        }
        if ( state->Screen[i] != NULL ){
            delete state->Screen[i];
            state->Screen[i] = NULL;
        }
        if ( state->Scaler != NULL ){
            delete state->Scaler;
            state->Scaler = NULL;
        }
        if ( state->Buffer != NULL ){
            delete state->Buffer;
            state->Buffer = NULL;
        }
		if (width != 0 && height != 0){
			state->Screen[i] = new CBitmap( ok ,false,true,i);
			Debug::debug(Debug::bitmap,__FUNCTION__) << "New Screen["<<i<<"] = "<< _my_state->Screen[i] <<  endl;
			state->Screen[i]->_my_renderWindow=i;
			Colors::init_colors();
            if ( width != 0 && height != 0 && (width != SCALE_X || height != SCALE_Y) ){
                state->Scaler = new CBitmap(width, height);
                state->Buffer = new CBitmap(SCALE_X, SCALE_Y);
            }
        }

		}



	Debug::debug(20) << "ret= " << ret << endl;
	return ret;
}

//-------------------Coloring an d Drawing Functions-------------------------
//
//-------------------------------------------------------------


 Colors::ColorDefinition CBitmap::makeSDLColor( int r, int g, int b ){
 Colors::ColorDefinition color;
color.r=r;
color.g=g;
color.b=b;
return color;
}





void CBitmap::fillSurface( Uint32 pixel) const{
	if(this->getBitmap()) {
		Debug::debug(Debug::bitmap,__FUNCTION__)  << "Color: "<< pixel << endl;
		::SDL_FillRect(getBitmap(), NULL, pixel);	}else {
	//erro bitmap invalido
	}

}


void CBitmap::fill(  Colors::ColorDefinition cor ,Uint8 a) const{
		fill(cor.r,cor.g,cor.b,a);
}

void CBitmap::fillTexture(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
		if (!ClipRectText.empty()) {
			polygon().rectangleFill( ClipRectText.getX1(), ClipRectText.getY1(), ClipRectText.getX2(),ClipRectText.getY2(), r, g, b, a  );
		}else if(this->GetTexture()!=NULL)
		{

		// guardar a cor atual
		Uint8 r1,g1,b1,a1;
		::SDL_GetRenderDrawColor(getMyRender(),&r1,&g1,&b1, &a1);
		::SDL_SetRenderDrawColor(getMyRender(),r, g, b, a);
		::SDL_RenderClear(getMyRender());
		::SDL_SetRenderDrawColor(getMyRender(),r1, g1, b1, a1);
		//recuperar a cor antiga
		}
	
}


void CBitmap::fill( Uint8 r, Uint8 g, Uint8 b ,Uint8 a) const{

	
		Uint32 color_pixel;
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);
		SDL_PixelFormat *pixelFormat = SDL_AllocFormat(mode.format);
		if (pixelFormat == NULL) {
			Debug::debug(Debug::error,__FUNCTION__) << "Error: " << SDL_GetError() <<endl;

		}
		switch(this->getBitmapMode()) { //textura e surface

				case DRAW_TYPE_TEXTURE:
						fillTexture(r,g,b,a);
					break;

				case DRAW_TYPE_SURFACE:
					color_pixel=SDL_MapRGBA(pixelFormat,r,g,b,a);
					fillSurface(color_pixel);
					if (pixelFormat !=NULL) SDL_FreeFormat(pixelFormat);
				break;

				case DRAW_TYPE_TEX_SURF:
					color_pixel=SDL_MapRGBA(pixelFormat,r,g,b,a);
					fillSurface(color_pixel);
                    fillTexture(r,g,b,a);
					if (pixelFormat !=NULL) SDL_FreeFormat(pixelFormat);
				break;
				default:
				break;
				}


}
/** @fn CBitmap::fill( Uint32 pixel )
@brief Função que preenche a superfície da classe com o pixel passado como parâmetro
@param pixel: valor do pixel a ser colocado na superfície
@param width: largura da tela a inicializar
@param height: altura da tela a inicializar
@return nada
@warning
**/
void CBitmap::fill( Uint32 pixel ) const{

					Uint8 redX;
					Uint8 greenX;
					Uint8 blueX;
					Uint8 alphaX;
					SDL_DisplayMode mode;
					SDL_GetDesktopDisplayMode(0,&mode);
					SDL_GetRGBA(pixel, SDL_AllocFormat(mode.format), &redX, &greenX, &blueX, &alphaX);

					fill(redX,greenX,blueX,alphaX);



}

void CBitmap::fill(int x, int y, int w, int h, int pixel){
	int x1,y1,x2,y2;

	this->getClipRect(x1,y1,x2,y2);
	//tanto para surface quanto para textura, dependendo do modo
	this->setClipRect(x,y,x+w,y+h);
	fill(pixel);
	this->setClipRect(x1,y1,x2,y2);
}

void CBitmap::fill_all_screen( Uint8 r, Uint8 g, Uint8 b ,Uint8 a) const{


//		::SDL_SelectRenderer(GetWindow());
		// guardar a cor atual
		Uint8 r1,g1,b1,a1;
		::SDL_GetRenderDrawColor(getMyRender(),&r1,&g1,&b1, &a1);
		::SDL_SetRenderDrawColor(getMyRender(),r, g, b, a);
		::SDL_RenderClear(getMyRender());
		::SDL_SetRenderDrawColor(getMyRender(),r1, g1, b1, a1);
		//recuperar a cor antiga

	

}



//-------------Texture Methods -------------


/** @fn CBitmap::CreateTextureFromBitmap()
@brief Função que converte o bitmap para uma textura openGL
		utilizando o SDL 1.3
@param renderWindow. Índice que determina qual janela será utilizada como render para esta textura
@return Retorna um ponteiro para a textura criada
@warning Precisa selecionar o render antes de chamar este método
**/
SDL_Texture * CBitmap::CreateTextureFromBitmap(int renderWindow) {
	Debug::debug(Debug::bitmap,__FUNCTION__)  <<  endl;
		SDL_Texture *temp=NULL;
		try {
			locksurface();
			//temp=this->copyTextureFromSurface();  //cria textura streaming mas não aceita ColorKey
			temp=SDL_CreateTextureFromSurface(getMyRender(), getBitmap());  //cria textura statica mas com colorkey
			if(GetTexture()!=NULL) {
				SDL_DestroyTexture(GetTexture());
			}
			this->setTexture(temp);
			unlocksurface();
			return temp;

		}catch(...) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Could not create Texture! Error= " <<  SDL_GetError()  << endl;
			error = true;
			//lock.release();
			return GetTexture();
		}

	

}

/** @fn CBitmap::CreateTexture(int x, int y, int renderwindow)
@brief Função que converte o bitmap para uma textura SDL
		utilizando o SDL 2.0
@param renderWindow. Índice que determina qual janela será utilizada como render para esta textura
@return Retorna um ponteiro para a textura criada
@warning Precisa selecionar o render antes de chamar este método
@note Texturas criadas com o parâmetro SDL_TEXTUREACCESS_STREAMING, que podem ser utilizadas para
objetos que mudam frequentemente e podem ser atualizadas.
Streaming textures are designed for things that update frequently, every few seconds, or every frame.  You can also update them with SDL_UpdateTexture(), but for optimal performance you lock them, write the pixels, and then unlock them.
http://slouken.blogspot.com.br/2011/02/streaming-textures-with-sdl-13.html

**/
SDL_Texture * CBitmap::createTextureStreaming(int x, int y, int renderWindow) {
	Debug::debug(Debug::bitmap,__FUNCTION__)  <<  endl;


		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);

		SDL_Texture *temp=NULL;

			temp = ::SDL_CreateTexture(getMyRender(),mode.format,SDL_TEXTUREACCESS_STREAMING,x,y);

			if(temp) {
				return temp;
			}else{
			Debug::debug(1,__FUNCTION__) << "Could not create Texture! Error= " <<  SDL_GetError()  << endl;
			error = true;
			return GetTexture();
			}



}

/** @fn CBitmap::getTextureAccessMode()
@brief Método que retorna o tipo de modo de acesso com o qual
		a textura foi criada utilizando o SDL 2.0
@return O valor do modo de acesso:
	SDL_TEXTUREACCESS_STATIC  - changes rarely, not lockable
	SDL_TEXTUREACCESS_STREAMING - changes frequently, lockable
	SDL_TEXTUREACCESS_TARGET - can be used as a render target

**/	
int CBitmap::getTextureAccessMode(){

	Uint32 formato;
	int acess,w,h;
	
	if(	SDL_QueryTexture(GetTexture(),&formato,&acess,&w,&h)==0) {
		return acess;
	}else {
		//error
	}


}
/** @fn CBitmap::isTextureStatic()
@brief Método que retorna verdadeiro se o modo de acesso da extura e Static
@return verdadeiro se o modo de acesso da textura é
	SDL_TEXTUREACCESS_STATIC  - changes rarely, not lockable
**/
bool CBitmap::isTextureStatic(){

return  (getTextureAccessMode()==(int)SDL_TEXTUREACCESS_STATIC); 

}
/** @fn CBitmap::isTextureStreaming()
@brief Método que retorna verdadeiro se o modo de acesso da extura e Streaming
@return verdadeiro se o modo de acesso da textura é
	SDL_TEXTUREACCESS_STREAMING - changes frequently, lockable
**/
bool CBitmap::isTextureStreaming(){
return  (getTextureAccessMode()==(int)SDL_TEXTUREACCESS_STREAMING); 

}
/** @fn CBitmap::isTextureTarget()
@brief Método que retorna verdadeiro se o modo de acesso da extura e Target
@return verdadeiro se o modo de acesso da textura é
	SDL_TEXTUREACCESS_TARGET - can be used as a render target

**/
bool CBitmap::isTextureTarget(){
return  (getTextureAccessMode()==(int)SDL_TEXTUREACCESS_TARGET); 

}
	



/** @fn copyTextureFromSurface()
@brief Função que cria uma textura a partir da Surface SDL
@note Texturas criadas com o parâmetro SDL_TEXTUREACCESS_STREAMING, que podem ser utilizadas para
objetos que mudam frequentemente e podem ser atualizadas.
Streaming textures are designed for things that update frequently, every few seconds, or every frame.  You can also update them with SDL_UpdateTexture(), but for optimal performance you lock them, write the pixels, and then unlock them.
http://slouken.blogspot.com.br/2011/02/streaming-textures-with-sdl-13.html

**/

SDL_Texture * CBitmap::copyTextureFromSurface()
{
	SDL_Renderer * renderer = this->getMyRender();
	SDL_Surface * surface = this->getBitmap();
    Uint32 format;
    SDL_Texture *texture;

    //CHECK_RENDERER_MAGIC(renderer, NULL);

    if (!surface) {
        SDL_SetError("SDL_CreateTextureFromSurface() passed NULL surface");
        return NULL;
    }

    /* See what the best texture format is */
    //fmt = surface->format;
   // if (fmt->Amask || SDL_GetColorKey(surface, NULL) == 0) {
   //     needAlpha = SDL_TRUE;
  //  } else {
   //     needAlpha = SDL_FALSE;
   // }
    SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);


	format = mode.format;


    texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, surface->w, surface->h);
    if (!texture) {
        //error=1;
		return NULL;

    }

    if (format == surface->format->format) {
        if (SDL_MUSTLOCK(surface)) {
            SDL_LockSurface(surface);

			SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);

            SDL_UnlockSurface(surface);
        } else {
			
            SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        }
    } else {
        SDL_PixelFormat *dst_fmt;
        SDL_Surface *temp = NULL;

        /* Set up a destination surface for the texture update */
        dst_fmt = SDL_AllocFormat(format);
        temp = SDL_ConvertSurface(surface, dst_fmt, 0);
        SDL_FreeFormat(dst_fmt);
        if (temp) {
            SDL_UpdateTexture(texture, NULL, temp->pixels, temp->pitch);
            SDL_FreeSurface(temp);
        } else {
            SDL_DestroyTexture(texture);
            return NULL;
        }
    }

    {
        Uint8 r, g, b, a;
        SDL_BlendMode blendMode;

        SDL_GetSurfaceColorMod(surface, &r, &g, &b);
        SDL_SetTextureColorMod(texture, r, g, b);

        SDL_GetSurfaceAlphaMod(surface, &a);
        SDL_SetTextureAlphaMod(texture, a);

        if (SDL_GetColorKey(surface, NULL) == 0) {
            /* We converted to a texture with alpha format */
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        } else {
            SDL_GetSurfaceBlendMode(surface, &blendMode);
            SDL_SetTextureBlendMode(texture, blendMode);
        }
    }
    return texture;
}

/** @fn copyTextureFromTexture()
@brief Função que cria uma textura a partir da Textura atul do Bitmap
@note Texturas criadas com o parâmetro SDL_TEXTUREACCESS_STREAMING, que podem ser utilizadas para
objetos que mudam frequentemente e podem ser atualizadas.
Streaming textures are designed for things that update frequently, every few seconds, or every frame.  You can also update them with SDL_UpdateTexture(), but for optimal performance you lock them, write the pixels, and then unlock them.
http://slouken.blogspot.com.br/2011/02/streaming-textures-with-sdl-13.html

**/
//DO NOT WORK!!! I CAN NOT GET THE ORIGIN PIXEL FROM TEXTURE
SDL_Texture * CBitmap::copyTextureFromTexture()
{
	
	
	SDL_Renderer * renderer = this->getMyRender();
	SDL_Texture * surface = this->GetTexture();
	Uint32 format;
    SDL_Texture *texture;
	/*void *native_pixels;
        int native_pitch;

	SDL_QueryTexturePixels(surface,
                           native_pixels, 
                           &native_pitch);
						   */
    //CHECK_RENDERER_MAGIC(renderer, NULL);

    if (!surface) {
        SDL_SetError("SDL_CreateTextureFromSurface() passed NULL surface");
        return NULL;
    }

    /* See what the best texture format is */
    //fmt = surface->format;
   // if (fmt->Amask || SDL_GetColorKey(surface, NULL) == 0) {
   //     needAlpha = SDL_TRUE;
  //  } else {
   //     needAlpha = SDL_FALSE;
   // }
    SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);


	format = mode.format;


    texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING
,
                                surface->w, surface->h);
    if (!texture) {
        return NULL;
    }
	if (surface->access == SDL_TEXTUREACCESS_STREAMING) {
    Uint32 *dst, *org;
    if (format == surface->format) {  //textures with same format

		// lock destination texture
        if (SDL_LockTexture(texture,NULL,&texture->pixels,&texture->pitch) >=0) {
           
			//SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
			for (int row = 0; row < texture->h; ++row) {
             org = (Uint32*)((Uint8*)surface->pixels + row * surface->pitch);
             dst = (Uint32*)((Uint8*)texture->pixels + row * texture->pitch);
             for (int col = 0; col < texture->w; ++col) {
                 SDL_Color color;
				 color.r= 25;
				 color.g= 125;
				 color.b=45;
                 *dst++ = *org++;//(0xFF000000|(color.r<<16)|(color.g<<8)|color.b);
             }
         }

            SDL_UnlockTexture(texture);
        }else {
			SDL_GetError();
		}
    
	
	} else {
   /*     SDL_PixelFormat *dst_fmt;
        SDL_Surface *temp = NULL;

        // Set up a destination surface for the texture update 
        dst_fmt = SDL_AllocFormat(format);
        temp = SDL_ConvertSurface(surface, dst_fmt, 0);
        SDL_FreeFormat(dst_fmt);
        if (temp) {
            SDL_UpdateTexture(texture, NULL, temp->pixels, temp->pitch);
            SDL_FreeSurface(temp);
        } else {
            SDL_DestroyTexture(texture);
            return NULL;
        } */
    }

    {
        Uint8 r, g, b, a;
        SDL_BlendMode blendMode;

        SDL_GetTextureColorMod(surface, &r, &g, &b);
        SDL_SetTextureColorMod(texture, r, g, b);

        SDL_GetTextureAlphaMod(surface, &a);
        SDL_SetTextureAlphaMod(texture, a);

		SDL_GetTextureBlendMode(surface, &blendMode);
        SDL_SetTextureBlendMode(texture, blendMode);
       
    }
	} // end texture acces type test
    return texture; //se o formato não estiver correto, retorna uma textura vazia
}

void CBitmap::copyTextureFromBitmap(CBitmap &origem) {

	SDL_Texture * novaTextura= origem.copyTextureFromTexture();
	if (novaTextura !=NULL) {
		SDL_DestroyTexture(this->GetTexture());
		this->setTexture(novaTextura);

	}

}



/*
int CBitmap::SetScaleMode(int scalemode){
    int code=0;
			code= SDL_SetTextureScaleMode(GetTexture(), scalemode);

		return code;
}*/

/*
		When a texture is rendered, during the copy operation the source alpha value is modulated by this alpha value according to the following formula:
         srcA = srcA * alpha
        */
int CBitmap::SetAlphaMod(int alpha){
	int code=0;
	code= SDL_SetTextureAlphaMod(GetTexture(), (Uint8) alpha);
	return code;



}
/*
void CBitmap::SetWindow( SDL_Window * window ){
            if ( window == NULL ){
                Debug::debug(Debug::bitmap,__FUNCTION__) << "*FATAL* Setting null window" << endl;
			}else{
			    Debug::debug(Debug::bitmap,__FUNCTION__) << "Window setted: "<< window <<endl;
			    _my_window = window;
			}
        }
		*/
void CBitmap::SetDefColor(int R, int G, int B, int A){
	SDL_SetRenderDrawColor(getMyRender(),R, G, B, A);

}

#ifndef ANDROID

//todo: add Gles (externalLibs ges 1.4) tocompile under android
//==============  GL ==================================
//  FUNÇÕES QUE TRABALHAM NO MODO OpenGL Diretamente //
//=====================================================

// Convert CBitmap To Textures
/** @fn CBitmap::ConvertToTexture()
@brief Função que converte o bitmap para uma textura openGL
@return 0 se sucesso ou 1 se erro
@warning
**/
int CBitmap::ConvertToTexture()
{
SDL_Surface *sdlimage;

int w, h, i, j, bpp;
Uint8 *srcPixel, *dstPixel;
Uint32 truePixel;

sdlimage = getBitmap();
if ( !sdlimage ) {
printf("SDL_Image load error: %s\n", IMG_GetError());
return 0;
}
if ( sdlimage->format->BytesPerPixel < 2 ) {
printf("Bad image -- not true color!\n");
SDL_FreeSurface (sdlimage);
return 0;
}

w = sdlimage->w;
h = sdlimage->h;


dstPixel = GetGLBitmap();


SDL_LockSurface( sdlimage );

bpp = sdlimage->format->BytesPerPixel;

for ( i = h-1 ; i >= 0 ; i-- ) {
for ( j = 0 ; j < w ; j++ ) {
srcPixel = (Uint8 *)sdlimage->pixels + i * sdlimage->pitch + j * bpp;
switch (bpp) {
case 1:
truePixel = *srcPixel;
break;

case 2:
truePixel = *(Uint16 *)srcPixel;
break;

case 3:
if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
truePixel = srcPixel[0] << 16 | srcPixel[1] << 8 | srcPixel[2];
} else {
truePixel = srcPixel[0] | srcPixel[1] << 8 | srcPixel[2] << 16;
}
break;

case 4:
truePixel = *(Uint32 *)srcPixel;
break;

default:
printf("Image bpp of %d unusable\n", bpp);
return 0;
break;
}
SDL_GetRGBA( truePixel, sdlimage->format, &(dstPixel[0]), &(dstPixel[1]), &(dstPixel[2]), &(dstPixel[3]));
dstPixel++;
dstPixel++;
dstPixel++;
dstPixel++;
}
}

SDL_UnlockSurface( sdlimage );
SDL_FreeSurface( sdlimage );
return 0;
}

/** @fn CBitmap::CreateGLTexture()
@brief Função que cria uma textura openGL
@return 0 se sucesso ou 1 se erro
@warning
**/
int CBitmap::CreateGLTexture() {
	// checar se atextura já está carregada;
	if (_my_bitmap.GetGLTexture()!=NULL) {
		GLenum errorCode;
		int w;int h;
		w=this->getBitmap()->w;
		h=this->getBitmap()->h;
		while ( glGetError() ) { ; }

		errorCode = glGetError();
		if ( errorCode != 0 ) {
			if ( errorCode == GL_OUT_OF_MEMORY ) {
			printf("Out of texture memory!\n");
			}
			return 0;
		}

    // Create Textures
    glGenTextures(3, (GLuint *)&texture[0]);

    // texture 1 (poor quality scaling)
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // cheap scaling when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // cheap scaling when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, GetGLBitmap());

    // texture 2 (linear scaling)
    glBindTexture(GL_TEXTURE_2D, texture[1]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, GetGLBitmap());

    // texture 3 (mipmapped scaling)
    glBindTexture(GL_TEXTURE_2D, texture[2]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // scale linearly + mipmap when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, GetGLBitmap());

    // 2d texture, 3 colors, width, height, RGB in that order, byte data, and the data.
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, GetGLBitmap());


	errorCode = glGetError();
	if ( errorCode != 0 ) {
		if ( errorCode == GL_OUT_OF_MEMORY ) {
		printf("Out of texture memory!\n");
		}
	return 0;
	}
	glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
	return 0;
	}else
		return 1;
}



/** @fn CBitmap::Switch2D()
@brief Inicialização do OpenGL no modo 2D
* To achieve exact pixelization (pixel-precise drawing), it's important to understand that coordinates in OpenGL are technically not tied to the actual screen pixels,
* so even if you set up 2D projection as explained above,
* you still specify the locations with higher than pixel granularity.
* That is, (0,0) corresponds to the top-left corner inside the top-left pixel,
* while (0.5, 0.5) corresponds to the center of that pixel.
* Forgetting about this can easily lead to quite unpredictable misplacements of primitives
* and to unwanted anti-aliasing blur.
* For example, if you want to lit pixels using GL_POINTS, you should use coordinates that end
* with a half (like 10.5 instead of 10), as in principle you want to put that point at
* the center of the pixel, not at the corner of it, as in the last case the point will
* overlap with the neighbor pixels (because an OpenGL "point" of default size 1 is in
* fact a 1x1 square), hence possibly painting some of those screen pixels.
* But if for example you draw lines (GL_LINES) or polygons (GL_QUADS, etc.),
* you want to put the vertices at the edges of the pixels, so you will often use integer coordinates.
* If you are not using anti-aliasing, a popular trick to avoid all this mess is to
* apply glTranslatef (0.375, 0.375, 0) on the GL_MODELVIEW matrix, and then use integer coordinates everywhere;
* this displacement will keep the edges of the primitives away from the places where OpenGL vacillates about which screen pixels to paint.
@return nenhum.
@warning
**/
void CBitmap::Switch2D()
{
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
glOrtho (0, _my_state->Screen[this->_my_renderWindow]->getBitmap()->w,_my_state->Screen[this->_my_renderWindow]->getBitmap()->h,0, -1, 1);
glMatrixMode (GL_MODELVIEW);
glTranslatef (0.375, 0.375, 0);
glLoadIdentity();
glDisable(GL_DEPTH_TEST);
GL2D=true;
GL3D=false;
}
/** @fn CBitmap::Switch3D()
@brief Inicializa o OpenGL no modo 3D
@param nenhum
@return nenhum.
@warning nenhum aviso
**/
/* The main drawing function. */
void CBitmap::Switch3D()
{
InitGL(_my_state->Screen[this->_my_renderWindow]->getBitmap()->w,_my_state->Screen[this->_my_renderWindow]->getBitmap()->h);

}

/** @fn CBitmap::DrawGLScene
@brief Função de desenho da superfície OpenGL
@warning nenhum aviso
**/
/* The main drawing function. */
void CBitmap::DrawGLScene()
{
  //!rtri: Variável que define o ângulo de rotação deo triângulo. é declarada estática para poder ser incrementada cada vez que esta função é chamada
  static float rtri=0.0;    // initialize the value only for the firs call to this function
  //!rquad: Variável que define o ângulo de rotação deo quadrado. é declarada estática para poder ser incrementada cada vez que esta função é chamada
  static float rquad=0.0;
  // incrementa o ângulo de rotação do triângulo e do quadrado
  rtri+=15.0f;					// Increase The Rotation Variable For The Triangle
  rquad-=15.0f;
  if(GL3D) {
	  glLoadIdentity();	// Reset The View
      glTranslatef(-1.5f,0.0f,-6.0f);		// Move Left 1.5 Units And Into The Screen 6.0
  }else if(GL2D)

  //!Desenha um Triângulo Colorido
  //DrawGLTriangleFilled(true,rtri);
  Triangle(110,20, 120,100,90,100,200,100,48);
    // Move 30 unidades para o lado
  glLoadIdentity();	// make sure we're no longer rotated.
  if (GL2D)
  glTranslatef(30.0f,0.0f,0.0f);		// Move Right 30 Units, and back into the screen 6.0
  else if (GL3D)
   glTranslatef(3.0f,0.0f,-6.0f);
   TriangleFill(110,20, 120,100,90,100,200,100,48);
    // Move 3 unidades para o lado
   glLoadIdentity();				// make sure we're no longer rotated.

   /*if (GL3D)
   glTranslatef(-0.5f,1.0f,-6.0f);

   //!Desenha um Quadrado
  Box(300,300,350,350,100,100,100,true,rquad);
     glLoadIdentity();				// make sure we're no longer rotated.
  //!Desenha um Quadrado
  		// Move Right 30 Units, and back into the screen 6.0
  if (GL2D)
  glTranslatef(300.0f,0.0f,0.0f);		// Move Right 30 Units, and back into the screen 6.0
  else if (GL3D)
   glTranslatef(2.0f,-1.0f,-6.0f);
  BoxFill(100,100,200,200,100,190,250,true,rquad);

 // Decrease The Rotation Variable For The Quad
  */
  // Move 3 unidades para o lado
  glLoadIdentity();				// make sure we're no longer rotated.
  if (GL3D){
   glTranslatef(-0.0f,-1.0f,-6.0f);		// Move Right 3 Units, and back into the screen 6.0
  Circle(0,0,0.5,255,255,0,true,rquad);
  } else if (GL2D) {
  Circle(300,350,50);
 	// make sure we're no longer rotated.
   CircleFill(300,350,5,255,0,0);
  }
  glLoadIdentity();				// make sure we're no longer rotated.
  glTranslatef(10.0f,10.0f,0.0f);		// Move Right 3 Units, and back into the screen 6.0

  Arc(300,350,30,90,50); //angulos em graus */
  glLoadIdentity();				// make sure we're no longer rotated.
  glTranslatef(10.0f,10.0f,0.0f);		// Move Right 3 Units, and back into the screen 6.0

  ArcFill(400,450,30,90,50); //angulos em graus */

}
/** @fn CBitmap::Line(const float x1,const float y1,const float x2,const float y2,const int R, const int G, const int B, const float z1,const float z2)
@brief Desenha uma Linha
@param   x1: coordenada do primeiro vértice no eixo x
@param   y1: coordenada do primeiro vértice no eixo y
@param   x2: coordenada do segundo vértice no eixo x
@param  y2: coordenada do segundo vértice no eixo y
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@param  z1: coordenada do primeiro vértice no eixo z (para o modo 3D apenas)
@param  z2: : coordenada do segundo vértice no eixo y (para o modo 3D apenas)
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         se não for passado nenhuma coordenada esta função desenha um ponto no vértice 0.0
**/
void CBitmap::GL_Line(const float x1,const float y1,const float x2,const float y2,const int R, const int G, const int B, const float z1,const float z2){
glColor3ub(R, G, B);
glBegin(GL_LINES);
glVertex3f(x1,y1,z1); glVertex3f(x2,y2,z2);
glEnd();
}
/** @fn CBitmap::Point(const float x,const float y,const int R, const int G, const int B, const float z)
@brief Desenha uma Linha
@param  x: coordenada do ponto no eixo x
@param  y: coordenada do ponto no eixo y
@param  z: coordenada do ponto no eixo z
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         se não for passado nenhuma coordenada esta função desenha um ponto no vértice 0.0
**/
void CBitmap::Point(const float x,const float y,const int R, const int G, const int B, const float z){
glColor3ub(R, G, B);
	glBegin(GL_POINTS);
 glVertex3f(x,y,z);
 glEnd();
}
/** @fn CBitmap::Circle(const float x,const float y,const float radius,const int R, const int G, const int B,bool rotate,float angle)
@brief Desenha um círculo
@param  x: coordenada do ponto central no eixo x
@param  y: coordenada do ponto centralno eixo y
@param  radius: raio do círdulo
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@param  rotate: true indica que haverá rotação, false indica qua não haverá rotação
@param  angle: indica o ângulo de rotação
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
		 falta testar qual dos três médodos de desenho é o mais eficiente
*/
void CBitmap::Circle(const float x,const float y,const float radius,const int R, const int G, const int B,bool rotate,float angle){ //Draw a Circle
	glColor3ub(R, G, B);
	float num_segments=  GetNumCircleSegments(radius);
	if (rotate)
			glRotatef(angle,1.0f,0.0f,0.0f);
	int method = 3;
switch (method) {

  case 1 :
	glBegin(GL_LINE_LOOP);
	//Método 1 testar eficiencia //http://basic4gl.wikispaces.com/2D+Drawing+in+OpenGL
	for (float angle=0;angle<=358;angle+=float(0.1))
	glVertex3f(x + sin(angle) * radius, y + cos(angle) * radius,0.0f);
	glEnd();
    break;
  case 2://método 2
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * float(_PI) * float(ii) / float(num_segments);//get the current angle

		float cx = radius * cosf(theta);//calculate the x component
		float cy = radius * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
 break;
 case 3:
	 // http://slabode.exofire.net/circle_draw.shtml
	float theta = 2 * float(_PI) / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	float cx = radius;//we start at angle = 0
	float cy = 0;

	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -cy;
		float ty = cx;

		//add the tangential vector

		cx += tx * tangetial_factor;
		cy += ty * tangetial_factor;

		//correct using the radial factor

		cx *= radial_factor;
		cy *= radial_factor;
	}
	glEnd();

	 break;
}
}


/** @fn CBitmap::CircleFill(const float x,const float y,const float radius,const int R, const int G, const int B,bool rotate,float angle)
@brief Desenha um circulo preenchido com a cor passada nos parâmetros
@param x: coordenada do ponto central no eixo x
@param y: coordenada do ponto centralno eixo y
@param radius: raio do círdulo
@param R: quantidade de Vermelho na definição da cor do objeto
@param G: quantidade de Verde na definição da cor do objeto
@param B: quantidade de Azul na definição da cor do objeto
@param rotate: indica se haverá ou não rotação do polígono. 0: sem rotação, 1: com rotação
@param angle: ângulo de rotação em graus.
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
		 falta testar qual dos três médodos de desenho é o mais eficiente
*/
void CBitmap::CircleFill(const float x,const float y,const float radius,const int R, const int G, const int B,bool rotate,float angle){ //Draw a Circle
	glPushMatrix();
	glColor3ub(R, G, B);
	float num_segments=  GetNumCircleSegments(radius);
	if (rotate)
			glRotatef(angle,1.0f,0.0f,0.0f);
	int method = 3;
switch (method) {

  case 1 :
	glBegin(GL_TRIANGLE_FAN);
	//Método 1 testar eficiencia //http://basic4gl.wikispaces.com/2D+Drawing+in+OpenGL
	for (float angle=0;angle<=358;angle+=float(0.1))
	glVertex3f(x + sin(angle) * radius, y + cos(angle) * radius,0.0f);
	glEnd();
    break;
  case 2://método 2
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * float(_PI) * float(ii) / float(num_segments);//get the current angle

		float cx = radius * cosf(theta);//calculate the x component
		float cy = radius * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
 break;
 case 3:
	 // http://slabode.exofire.net/circle_draw.shtml
	float theta = 2 * float(_PI) / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	float cx = radius;//we start at angle = 0
	float cy = 0;

	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -cy;
		float ty = cx;

		//add the tangential vector

		cx += tx * tangetial_factor;
		cy += ty * tangetial_factor;

		//correct using the radial factor

		cx *= radial_factor;
		cy *= radial_factor;
	}
	glEnd();

	 break;
}
glPopMatrix();
}

/** @fn CBitmap::Arc(const float x, const float y, const float startAngle, const float endAngle, const float radius,const int R, const int G, const int B) const
@brief Desenha um Arco
@param  x: coordenada do ponto central no eixo x
@param  y: coordenada do ponto centralno eixo y
@param  radius: raio do arco
@param  startAngle: ângulo inicial do arco em graus
@param  endAngle: ângulo final do arco em graus
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
		 falta testar qual dos dois médodos de desenho é o mais eficiente
*/
void CBitmap::Arc(const float x, const float y, const float startAngle, const float endAngle, const float radius,const int R, const int G, const int B) const{

// Define a cor do vértice
	glColor3ub(R, G, B);
  //glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Red
  int method=3;
  //convert to Rad
  float StartAngle=(float(_PI) * startAngle) / float(180.0) ;
  float EndAngle=(float(_PI) * endAngle) / float(180.0) ;
 float num_segments=GetNumCircleSegments(radius);
 switch (method) {

  case 1 :  //not working
	glBegin(GL_LINE_LOOP);
	//Método 1 testar eficiencia
	for (float angle=StartAngle;angle<=EndAngle;angle+=float(0.1))
	glVertex3f(x + sin(angle) * radius, y + cos(angle) * radius,0.0f);
	glEnd();
    break;
  case 2://método 2

  break;
  case 3:
	 // http://slabode.exofire.net/circle_draw.shtml
	//float theta = 2 * PI / float(num_segments - 1);
	float theta = EndAngle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open


	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	//float cx = radius;//we start at angle = 0
	//float cy = 0;
    float cx = radius * cosf(StartAngle);//we now start at the start angle
	float cy = radius * sinf(StartAngle);


	glBegin(GL_LINE_STRIP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -cy;
		float ty = cx;

		//add the tangential vector

		cx += tx * tangetial_factor;
		cy += ty * tangetial_factor;

		//correct using the radial factor

		cx *= radial_factor;
		cy *= radial_factor;
	}
	glEnd();

	 break;
}
}
/** @fn CBitmap::ArcFill(const float x, const float y, const float startAngle, const float endAngle, const float radius,const int R, const int G, const int B) const
@brief Desenha um Arco preenchido
@param  x: coordenada do ponto central no eixo x
@param  y: coordenada do ponto centralno eixo y
@param  radius: raio do arco
@param  startAngle: ângulo inicial do arco em graus
@param  endAngle: ângulo final do arco em graus
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
		 falta testar qual dos dois médodos de desenho é o mais eficiente
*/
void CBitmap::ArcFill(const float x, const float y, const float startAngle, const float endAngle, const float radius,const int R, const int G, const int B) const{


// Define a cor do vértice
	glColor3ub(R, G, B);
  //glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Red
  int method=3;
  //convert to Rad
  float StartAngle=(float(_PI) * startAngle) / float(180.0) ;
  float EndAngle=(float(_PI) * endAngle) / float(180.0) ;
 float num_segments=GetNumCircleSegments(radius);
 switch (method) {

  case 1 :  //not working
	glBegin(GL_LINE_LOOP);
	//Método 1 testar eficiencia
	for (float angle=StartAngle;angle<=EndAngle;angle+=float(0.1))
	glVertex3f(x + sin(angle) * radius, y + cos(angle) * radius,0.0f);
	glEnd();
    break;
  case 2://método 2

  break;
  case 3:
	 // http://slabode.exofire.net/circle_draw.shtml
	//float theta = 2 * PI / float(num_segments - 1);
	float theta = EndAngle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open


	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	//float cx = radius;//we start at angle = 0
	//float cy = 0;
    float cx = radius * cosf(StartAngle);//we now start at the start angle
	float cy = radius * sinf(StartAngle);


	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -cy;
		float ty = cx;

		//add the tangential vector

		cx += tx * tangetial_factor;
		cy += ty * tangetial_factor;

		//correct using the radial factor

		cx *= radial_factor;
		cy *= radial_factor;
	}
	glEnd();

	 break;
}
}


// sem querer fiz uma estrela
// Ver como funciona mais tarde
// passar o ângulo de -90 graus   // tem a ver com o fato de  eu ter passado um ângulo em graus e as funções esperarem um ângulo em radianos
void CBitmap::Star(const float x, const float y, const float startAngle, const float endAngle, const float radius) const{

// Define a cor do vértice
	//glColor3ub(R, G, B);
  glColor3f(1.0f,1.0f,0.0f);			// Set The Color
  int method=3;
 float num_segments=GetNumCircleSegments(radius);
 switch (method) {

  case 1 :  //not working
	glBegin(GL_LINE_LOOP);
	//Método 1 testar eficiencia
	for (float angle=startAngle;angle<=endAngle;angle+=float(0.1))
	glVertex3f(x + sin(angle) * radius, y + cos(angle) * radius,0.0f);
	glEnd();
    break;
  case 2://método 2

  break;
  case 3:
	 // http://slabode.exofire.net/circle_draw.shtml
	float theta = endAngle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float cx = radius * cosf(startAngle);//we now start at the start angle
	float cy = radius * sinf(startAngle);

	glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);

		float tx = -cy;
		float ty = cx;

		cx += tx * tangetial_factor;
		cy += ty * tangetial_factor;

		cx *= radial_factor;
		cy *= radial_factor;
	}
	glEnd();


  break;
}
}
/** @fn CBitmap::GetNumCircleSegments(float radius) const
@brief Retorna o número aproximado de segmentos necessários para desenhar um círculo, ou arco
@param radius: raio do arco
@return número de segmentos necessários
@warning cor padrão: falta implementart mecanismos de segurança caso sejam passados valores incoerentes
*/
float CBitmap::GetNumCircleSegments(float radius) const{
//
	return 50 * sqrtf(radius);//change the 10 to a smaller/bigger number as needed
}

/** @fn CBitmap::Triangle(const float x1, const float y1, const float x2, const float y2,const float x3,const float y3,const int R, const int G, const int B)
@brief Desenha um Triângulo
@param  x1: coordenada do primeiro vértice no eixo x
@param  y1: coordenada do primeiro vértice no eixo y
@param  x2: coordenada do segundo vértice no eixo x
@param  y2: coordenada do segundo vértice no eixo y
@param  x3: coordenada do terceiro vértice no eixo x
@param  y3: coordenada do terceiro vértice no eixo y
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
*/
void CBitmap::Triangle(const float x1, const float y1, const float x2, const float y2,const float x3,const float y3,const int R, const int G, const int B)
{
	glColor3ub(R, G, B);
	 if (GL2D) {
		    glBegin(GL_LINE_LOOP);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glVertex2f(x3, y3);
			glEnd();

	}else if (GL3D) {
		//! Desenha um triângulo e define as cores dos vértices
		  // Desenha um triângulo
		  // draw a triangle
		  glBegin(GL_LINE_LOOP);				 // start drawing a polygon
		  // Vértice superior
		  glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
		  // Vértice Direito
		  glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
		  // Vértice Esquerdo
		  glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
		  // Término do desenho do triângulo
		  glEnd();					// we're done with the polygon
		  // Move 3 unidades para o lado
		  glTranslatef(3.0f,0.0f,0.0f);		        // Move Right 3 Units
	}
}

/** @fn CBitmap::TriangleFill(const float x1, const float y1, const float x2, const float y2,const float x3, const float y3,const int R, const int G, const int B, bool rotate,float angle)
@brief Desenha um Triângulo preenchido
@param  x1: coordenada do primeiro vértice no eixo x
@param  y1: coordenada do primeiro vértice no eixo y
@param  x2: coordenada do segundo vértice no eixo x
@param  y2: coordenada do segundo vértice no eixo y
@param  x3: coordenada do terceiro vértice no eixo x
@param  y3: coordenada do terceiro vértice no eixo y
@param  rotate: true indica que haverá rotação, false indica qua não haverá rotação
@param  angle: indica o ângulo de rotação
@param  R: quantidade de Vermelho na definição da cor do objeto
@param  G: quantidade de Verde na definição da cor do objeto
@param  B: quantidade de Azul na definição da cor do objeto
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
*/
void CBitmap::TriangleFill(const float x1, const float y1, const float x2, const float y2,const float x3, const float y3,const int R, const int G, const int B, bool rotate,float angle)
{
	glColor3ub(R, G, B);
 if (GL2D) {
		    glBegin(GL_TRIANGLES);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glVertex2f(x3, y3);
			glEnd();

	}else if (GL3D) {
		if (rotate)
	glRotatef(angle,0.0f,1.0f,0.0f);		// Rotate The Triangle On The Y axis


//! Desenha um triângulo e define as cores dos vértices

// draw a triangle
  glBegin(GL_TRIANGLES);				 // start drawing a polygon
  // Define a cor do vértice em vermelho
  //glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
  // Vértice superior
  glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
  // Define a cor do vértice em verde
  glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
  // Vértice Direito
  glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
  //Define a cor do vértice em azul
  glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
  // Vértice Esquerdo
  glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
  // Término do desenho do triângulo
  glEnd();					// we're done with the polygon
 }
}

/** @fn CBitmap::Box(const float x1,const float y1, float y2,const float x2, const int R, const int G, const int B, bool rotate,float angle){
@brief Função que desenha um quadrado
@param  x1: coordenada do primeiro vértice no eixo x
@param  y1: coordenada do primeiro vértice no eixo y
@param  x2: coordenada do segundo vértice no eixo x
@param  y2: coordenada do segundo vértice no eixo y
@param R: quantidade de Vermelho na definição da cor do objeto
@param G: quantidade de Verde na definição da cor do objeto
@param B: quantidade de Azul na definição da cor do objeto
@param  rotate: true indica que haverá rotação, false indica qua não haverá rotação
@param  angle: indica o ângulo de rotação
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
**/
void CBitmap::Box(const float x1,const float y1, float x2,const float y2, const int R, const int G, const int B, bool rotate,float angle){
  //glTranslatef(10,10,10);
	//int method=1;
	//float xcenter= x2-x1;
	//float ycenter= y2-y1;
	//! Desenha um quadrado e define a cor
	glColor3ub(R, G, B);

	if (GL2D) {
		if (rotate)
			glRotatef(angle, 0.0, 0.0, 1.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
			glEnd();

	}else if (GL3D) {
		if (rotate)
        glRotatef(angle,1.0f,0.0f,0.0f);		// Rotate The Quad On The X axis
			// set color to a blue shade.
			//draw a square (quadrilateral)
			glBegin(GL_LINE_LOOP);				// start drawing a polygon (4 sided) //! Inicia o desenho do polígono de 4 lados
			// canto superior esquerdo
			glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
			// canto superior direito
			glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
			// canto inferior direito
			glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
			// canto inferior Esquerdo
			glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
			// Término do desenho
			glEnd();					// done with the polygon

	}

}
/** @fn CBitmap::BoxFill(const float x1,const float y1, float y2,const float x2, const int R, const int G, const int B, bool rotate,float angle){
@brief Função que desenha um quadrado preenchido
@param  x1: coordenada do primeiro vértice no eixo x
@param  y1: coordenada do primeiro vértice no eixo y
@param  x2: coordenada do segundo vértice no eixo x
@param  y2: coordenada do segundo vértice no eixo y
@param R: quantidade de Vermelho na definição da cor do objeto
@param G: quantidade de Verde na definição da cor do objeto
@param B: quantidade de Azul na definição da cor do objeto
@param  rotate: true indica que haverá rotação, false indica qua não haverá rotação
@param  angle: indica o ângulo de rotação
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
**/
void CBitmap::BoxFill(const float x1,const float y1, const float x2,const float y2,const int R, const int G, const int B, bool rotate,float angle){
    glColor3ub(R, G, B);
	if (GL2D) {
		    glBegin(GL_QUADS);
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
			glEnd();

	}else if (GL3D) {
		if (rotate)
			glRotatef(angle,1.0f,0.0f,0.0f);		// Rotate The Quad On The X axis

			//! Desenha um quadrado e define a cor para azul
			//glColor3f(0.5f,0.5f,1.0f);			// set color to a blue shade.
			//draw a square (quadrilateral)
			glBegin(GL_QUADS);				// start drawing a polygon (4 sided) //! Inicia o desenho do polígono de 4 lados
			// canto superior esquerdo
			glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
			// canto superior direito
			glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
			// canto inferior direito
			glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
			// canto inferior Esquerdo
			glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
			// Término do desenho
			glEnd();// done with the polygon
  }
}

/** @fn CBitmap::BoxTex(int filter, const float x1,const float y1, float x2,const float y2, const int R, const int G, const int B, bool rotate,float angle)
@brief Função que desenha um quadrado preenchido por uma textura
@param filter: índice da textura que será mapeada ao quadrado
@param  x1: coordenada do primeiro vértice no eixo x
@param  y1: coordenada do primeiro vértice no eixo y
@param  x2: coordenada do segundo vértice no eixo x
@param  y2: coordenada do segundo vértice no eixo y
@param R: quantidade de Vermelho na definição da cor do objeto
@param G: quantidade de Verde na definição da cor do objeto
@param B: quantidade de Azul na definição da cor do objeto
@param  rotate: true indica que haverá rotação, false indica qua não haverá rotação
@param  angle: indica o ângulo de rotação
@return nenhum.
@warning cor padrão: branco (se não for passada nenhuma cor)
         falta implementart mecanismos de segurança caso sejam passados valores incoerentes
**/
void CBitmap::BoxTex(int filter, const float x1,const float y1, float x2,const float y2, const int R, const int G, const int B, bool rotate,float angle){
//void CBitmap::BoxTex(int filter, float size, float xcenter ,float ycenter, float zcenter)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
    //float xcenter = 0.5;
	//float zcenter = 0.5;
	//float ycenter = 0.5;
	//float dx1,dx2,dy1,dy2;
	float ddx1,ddx2,ddy1,ddy2;
	//dx1 = -1.0;
	//dx2 = 1.0;
    //dy1 = 1.0;
	//dy2 = -1.0;
	ddx1 = this->ConvertXto3D(x1);
	ddx2 = this->ConvertXto3D(x2);
	ddy1 = this->ConvertXto3D(y1);
	ddy2 = this->ConvertXto3D(y2);
	//float size=2;
	/* floats for x rotation, y rotation, z rotation */
    static float xrot=0.0;
	static float yrot=0.0;
    static float zrot=0.0;
	glLoadIdentity();				// Reset The View


    glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.
	if (GL2D) {
		if (rotate)
			glRotatef(angle, 0.0, 0.0, 1.0);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);glVertex2f(x1, y1);
			glTexCoord2f(1.0f, 1.0f);glVertex2f(x2, y1);
			glTexCoord2f(1.0f, 0.0f);glVertex2f(x2, y2);
			glTexCoord2f(0.0f, 0.0f);glVertex2f(x1, y2);
			glEnd();

	}else if (GL3D) {
	float escalax=(x2-x1)/_my_state->Screen[this->_my_renderWindow]->getBitmap()->w;
	float escalay=(y2-y1)/_my_state->Screen[this->_my_renderWindow]->getBitmap()->h;
	         // move units into the screen.

	//não sei porque não consigo diminuir a coordenada z??????
	glTranslatef(ConvertXto3D(x1),ConvertYto3D(y1),-5.0f);

	glScalef(escalax,escalay,0.0f);

	if (rotate) {
	glRotatef(xrot,1.0f,0.0f,0.0f);		// Rotate On The X Axis
    glRotatef(yrot,0.0f,1.0f,0.0f);		// Rotate On The Y Axis
    glRotatef(zrot,0.0f,0.0f,1.0f);		// Rotate On The Z Axis
	}

	glBegin(GL_QUADS);		                // begin drawing a cube

    // Front Face (note that the texture's corners have to match the quad's corners)
    glNormal3f( 0.0f, 0.0f, 0.0f);
	// front face points out of the screen on z.
    glTexCoord2f(0.0f, 0.0f);glVertex3f(ddx1, ddy2,0.0f);   // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);glVertex3f(ddx2, ddy2,0.0f);   // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);glVertex3f(ddx2, ddy1,0.0f);   // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);glVertex3f(ddx1, ddy1,0.0f);   // Top Left Of The Texture and Quad
	glEnd();   // done with the polygon.

    xrot+=15.0f;		                // X Axis Rotation
    yrot+=15.0f;		                // Y Axis Rotation
    zrot+=15.0f;		                // Z Axis Rotation
    }
}
glPopMatrix();
}

float CBitmap::ConvertXto3D(int x) {
	// formula = Gl= (2P / (x2-x1)) -1
return (((float(2)*float(x))/float(getBitmap()->w))-float(1));
}

float CBitmap::ConvertYto3D(int y) {
    // formula = Gl= -(2P / (y2-y1)) -1
	return float(-1.0)*(((float(2)*float(y))/float(getBitmap()->h))-float(1));
}
float CBitmap::ConvertXto3D(float x) {
    // formula = Gl= (2P / (x2-x1)) -1
	return (((float(2)*x)/float(getBitmap()->w))-float(1));
}

float CBitmap::ConvertYto3D(float y) {
	// formula = Gl= -(2P / (y2-y1)) -1
return float(-1.0)*(((float(2)*y)/float(getBitmap()->h))-float(1));
}
float CBitmap::ConvertXto2D(float x) {
    //formula P=(((x2-x1) *(Gl-1))/2)
	return (float(getBitmap()->w) *(x+float(1.0)))/2;
}

float CBitmap::ConvertYto2D(float y) {
   //formula P=-(((y2-y1) *(Gl-1))/2)
	return (float(getBitmap()->h )*(y+float(1.0)))/2;
}


void CBitmap::SetLineWidth(float width){

glLineWidth(width);

}


/** @fn CBitmap::SetGLLight()
@brief Habilita o ambiente de iluminação 1
* detalhes http://www.inf.pucrs.br/~manssour/CG/pJavaIluminacao/
@param nenhum
@return nenhum.
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::SetGLLight()
{
    // set up light number 1.
   glEnable(GL_LIGHT1);
}

/** @fn CBitmap::SetGLLightAmbient(float r,float g,float b,float a)
@brief Configura a luz ambiente (1)
* Em OpenGL a cor de uma fonte de luz é caracterizada
* pela quantidade de vermelho (R), verde (G) e azul (B) que ela emite
* Então, OpenGL considera que a luz é dividida em quatro componentes independentes (que são colocadas juntas):
* Ambiente: resultado da luz refletida no ambiente; é a luz que vem de todas as direções;
* Difusa: luz que vem de uma direção, atinge a superfície e é refletida em todas as direções; assim, apresenta a mesma intensidade independente do local no qual o observador está posicionado;
* Especular: luz que vem de uma direção e tende a ser refletida numa única outra direção;
* Emissiva: simula a luz que se origina de um objeto; a cor emissiva de uma superfície adiciona intensidade luminosa ao objeto, mas não é afetada por qualquer fonte de luz e também não introduz luz adicional na cena.
@param r: intensidade de vermelho
@param g:: intensidade de verde
@param b: intensidade de azul
@param a: valor da transparência
@warning
**/
void CBitmap::SetGLLightAmbient(float r,float g,float b,float a){
    GLfloat teste[]={ r, g, b, a };
	glLightfv(GL_LIGHT1, GL_AMBIENT, teste);  // add lighting. (ambient)
}

/** @fn CBitmap::SetGLLightDiffuse(float r,float g,float b,float a)
@brief Configura a luz Difusa (1)
* Em OpenGL a cor de uma fonte de luz é caracterizada
* pela quantidade de vermelho (R), verde (G) e azul (B) que ela emite
* Então, OpenGL considera que a luz é dividida em quatro componentes independentes (que são colocadas juntas):
* Ambiente: resultado da luz refletida no ambiente; é a luz que vem de todas as direções;
* Difusa: luz que vem de uma direção, atinge a superfície e é refletida em todas as direções; assim, apresenta a mesma intensidade independente do local no qual o observador está posicionado;
* Especular: luz que vem de uma direção e tende a ser refletida numa única outra direção;
* Emissiva: simula a luz que se origina de um objeto; a cor emissiva de uma superfície adiciona intensidade luminosa ao objeto, mas não é afetada por qualquer fonte de luz e também não introduz luz adicional na cena.
@param r: intensidade de vermelho
@param g:: intensidade de verde
@param b: intensidade de azul
@param a: valor da transparência
**/
void CBitmap::SetGLLightDiffuse(float r,float g,float b,float a){
	GLfloat teste[]={ r, g, b, a };
	glLightfv(GL_LIGHT1, GL_DIFFUSE,teste);  // add lighting. (diffuse).
}


/** @fn CBitmap::SetGLLightPosition(float x,float y,float z,float p)
@brief Configura a posição da luz (1)
* Repare que são quatro os atributos de position .
* Isto ocorre porque os mesmos são especificados em coordenadas homogenias.
* Os  três primeiros parâmetros se referem a posição da fonte de luz.
@param x: se refere a posição daluz no eixo  X
@param y: se refere a posição daluz no eixo  Y
@param z: se refere a posição daluz no eixo  Z
@param p:  quando este parâmetro for 1.0 estamos referindo a um ponto e se for 0.0 estamos referindo a um vetor.
**/
void CBitmap::SetGLLightPosition(float x,float y,float z,float p){
    GLfloat teste[]= { x, y, z, p };
	glLightfv(GL_LIGHT1, GL_POSITION, teste); // set light position.
}

/** @fn CBitmap::DrawGLCube(int filter, float rotate_x,float xspeed, float rotate_y, float yspeed,float rotate_z, float zspeed,float z)
@brief Função de desenho da textura OpenGL
@param filter: numero do filtro a ser desenhado
@param rotate_x: a rotação no eixo x
@param xspeed: a velocidade da rotação no eixo x
@param rotate_y: a rotação no eixo y
@param yspeed: a velocidade da rotação no eixo y
@param rotate_z: a rotação no eixo z
@param zspeed: a velocidade da rotação no eixo z
@param z: a posição da textura no eixo z
**/
void CBitmap::DrawGLCube(int filter, float size, float xcenter,float ycenter,float zcenter,float rotate_x,float xspeed, float rotate_y, float yspeed,float rotate_z, float zspeed,float z)
{
	//! Se não usarmos glPushMatrix, todos os objetos serão afetados pelas transofrmações
    glPushMatrix();
	if(GL3D) {
	glColor3f(1.0f, 1.0f, 1.0f);
	/* floats for x rotation, y rotation, z rotation */
    static float xrot=0.0;
	static float yrot=0.0;
    static float zrot=0.0;
	glLoadIdentity();				// Reset The View
    float escala=(size/2);
	glTranslatef(xcenter,ycenter,zcenter+z);              // move z units out from the screen.
    glScalef(escala,escala,escala);
	if (rotate_x > 0.0)
    glRotatef(xrot,rotate_x,0.0f,0.0f);		// Rotate On The X Axis
    if (rotate_y > 0.0)
	glRotatef(yrot,0.0f,rotate_y,0.0f);		// Rotate On The Y Axis
    if (rotate_z > 0.0)
	glRotatef(zrot,0.0f,0.0f,rotate_z);		// Rotate On The Z Axis
    glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.

    glBegin(GL_QUADS);		                // begin drawing a cube

    // Front Face (note that the texture's corners have to match the quad's corners)
    glNormal3f( 0.0f, 0.0f, 1.0f);                              // front face points out of the screen on z.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad

    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);                              // back face points into the screen on z.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad

    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);                              // top face points up on y.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad

    // Bottom Face
    glNormal3f( 0.0f, -1.0f, 0.0f);                             // bottom face points down on y.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad

    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);                              // right face points right on x.
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);                              // left face points left on x.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad

    glEnd();   // done with the polygon.

    xrot+=xspeed;		                // X Axis Rotation
    yrot+=yspeed;		                // Y Axis Rotation
    zrot+=zspeed;		                // Z Axis Rotation
}
	glPopMatrix();
}

/** @fn CBitmap::EnGLLight()
@brief Habilita o ambiente de iluminação 1
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::EnGLLight()
{
  glEnable(GL_LIGHTING);
}

/** @fn CBitmap::DisGLLight()
@brief Habilita o ambiente de iluminação 1
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::DisGLLight()
{
  glDisable(GL_LIGHTING);
}

/** @fn CBitmap::SetGLBlending()
@brief Configura o blending
* detalhes:
* As funçoes de BLEND definem como é feita a mistura entre as cores do objeto que está sendo desenhado e as imagens que já estão na tela.
* Esta mistura é feita a partir de uma média ponderada entre o ponto da tela e o ponto do objeto que está sendo desenhado.
* É utilizada a função glBlendFunc(GLenum sfactor, GLenum dfactor).
* Esta função recebe dois parâmetros: o primeiro define o “peso” da cor dos novos pixeis
* e o segundo o “peso” da cor dos pixeis já existentes. Estes pesos, em OpenGL, são
* função do nível de transparência do objecto, ou seja, do valor do seu alfa.
* E para definir esse nível de transparência de um objeto é necessário especificar o ALFA de sua cor.
* Para isto usa-se o parâmetro alpha (4o) na função glColor.
* glColor4f(1,1,1,alfa);
* Este quarto parâmetro alfa pode variar entre 0 e 1,
* sendo 0 um objeto totalmente transparente e 1 um objeto opaco.
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::SetGLBlending()
{
 /* setup blending */
    /**a chamada:
	* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	* define que a nova cor do ponto na tela será:
	* NovaCorNaTela = CorDoObjeto * AlfaDoObjeto + CorAntigaNaTele * (1-AlfaDoObjeto);
	* Neste caso, as contantes tem o seguinte sifnificado:
    * GL_SRC_ALPHA: define que o peso da cor do objeto que está sendo desenhado é o próprio alfa de sua cor;
    * GL_ONE_MINUS_SRC_ALPHA: define que o peso da cor que já está na tela é de (1 - Alfa), onde alfa é o nível de transparência do objeto que está sendo desenhado.
    **/

	glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
    glColor4f(1.0f, 1.0f, 1.0f, 0.5);
}

/** @fn CBitmap::EnGLBlending()
@brief Habilita o blending
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::EnGLBlending(){
glEnable(GL_BLEND);		    // Turn Blending On
glDisable(GL_DEPTH_TEST);         // Turn Depth Testing Off
}

/** @fn CBitmap::DisGLBlending()
@brief Habilita o blending
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::DisGLBlending(){
glDisable(GL_BLEND);              // Turn Blending Off
glEnable(GL_DEPTH_TEST);          // Turn Depth Testing On
}


void CBitmap::DrawGLTexture(int filter, float rotate_x,float xspeed, float rotate_y, float yspeed,float rotate_z, float zspeed,float z)
{
    /* floats for x rotation, y rotation, z rotation */
    static float xrot=0.0;
	static float yrot=0.0;
    static float zrot=0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View

    glTranslatef(0.0f,0.0f,z);              // move z units out from the screen.
    if (rotate_x > 0.0)
    glRotatef(xrot,rotate_x,0.0f,0.0f);		// Rotate On The X Axis
    if (rotate_y > 0.0)
	glRotatef(yrot,0.0f,rotate_y,0.0f);		// Rotate On The Y Axis
    if (rotate_z > 0.0)
	glRotatef(zrot,0.0f,0.0f,rotate_z);		// Rotate On The Z Axis
    glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.

    glBegin(GL_QUADS);		                // begin drawing a cube

    // Front Face (note that the texture's corners have to match the quad's corners)
    glNormal3f( 0.0f, 0.0f, 1.0f);                              // front face points out of the screen on z.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad

    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);                              // back face points into the screen on z.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad

    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);                              // top face points up on y.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad

    // Bottom Face
    glNormal3f( 0.0f, -1.0f, 0.0f);                             // bottom face points down on y.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad

    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);                              // right face points right on x.
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);                              // left face points left on x.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad

    glEnd();   // done with the polygon.

    xrot+=xspeed;		                // X Axis Rotation
    yrot+=yspeed;		                // Y Axis Rotation
    zrot+=zspeed;		                // Z Axis Rotation

}


/* A general OpenGL initialization function.
 *Sets all of the initial parameters. */
/** @fn CBitmap::InitGL
@brief Inicialização Geral do OpenGL
*determina todos os parâmetros iniciais
@param Width: Largura da superfície a ser criada
@param Height: Altura da superfície a ser criada
@warning Devemos chamar esta função depois que a janela OpenGL for Criada
**/
void CBitmap::InitGL(int Width, int Height)	        //!< We call this right after our OpenGL window is created.
{
  glViewport(0, 0, Width, Height);
  //! Esta função irá preencher o fundo em preto
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  //! Habilita a limpeza do buffer de profundidade
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  //! O tipo de teste de profundidade a realizar
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  //! Habilita teste de profundidade
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  //! Habilita Shading de cores suave
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  //! Reseta a Matrix do projeto
  glLoadIdentity();				// Reset The Projection Matrix
  //! Calcula proporção da Janela
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
  //!avisa a classe que o openGL está habilitado

  GL2D=false;
  GL3D=true;


}

void CBitmap::ClearGL() const{
	if(GL3D)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	else if (GL2D)
		glClear(GL_COLOR_BUFFER_BIT);
}



/** @fn CBitmap::BlitGLToScreen()
@brief Função que coloca na tela o conteúdo da superfície openGL
@warning nenhum aviso
**/
void CBitmap::BlitGLToScreen(){
 // troca os buffers da tela. só no modo 1.2
 // SDL_GL_SwapBuffers();  // swap buffers to display, since we're double buffered.
}
#endif

//! render the text to the surface
void CBitmap::RenderToSurface(char *string,int x,int y, Colors::ColorDefinition textColor, CFont *fonte) const{
	if (strlen(string)<=0) return;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Surface:" << this << endl;
      SDL_Rect retanguloDest;
	 //Holds offsets
	if (fonte->getType() == fonte->TrueTypeFont) {
				SDL_Surface *temp;

				temp = TTF_RenderText_Blended((TTF_Font *) fonte->getFont(), string, textColor.toSDL() );
				retanguloDest.x=x;
				retanguloDest.y=y;
				retanguloDest.w=temp->w;
				retanguloDest.h=temp->h;
				if (temp !=NULL) {
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Surface:" << this << endl;
				::SDL_BlitSurface(temp, NULL, getBitmap(), &retanguloDest);
				::SDL_FreeSurface(temp);
				}else {
				// could not create surface from text
				   Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= Could not create surface from text" <<  endl;
				   error=1;
				}
	}else if (fonte->getType() == fonte->BitmapFont) {
		Debug::debug(Debug::bitmap,__FUNCTION__) << "print Bitmap Font text" <<  endl;

		SDL_Surface *temp;

		temp =((CBitmapFont *) fonte)->printBitmap(string);
				retanguloDest.x=0;
				retanguloDest.y=0;
				retanguloDest.w=temp->w;
				retanguloDest.h=temp->h;
				if (temp !=NULL) {
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Surface:" << this << endl;
				::SDL_BlitSurface(temp, NULL, getBitmap(), &retanguloDest);
				::SDL_FreeSurface(temp);
				}else {
				// could not create surface from text
				   Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= Could not create surface from text" <<  endl;
				   error=1;
				}
	}
}
/*
void CBitmap::Render(char *string,int x,int y, Colors::ColorDefinition textColor, TTF_Font *fonte){
     Debug::debug(Debug::bitmap,__FUNCTION__) << "------------------" << endl;
     //Debug::debug(Debug::bitmap,__FUNCTION__) << "string =");
     //Debug::debug(Debug::bitmap,__FUNCTION__) << string);

	 //Holds offsets

	//SDL_Texture *TextTexture;
	SDL_Surface *temp;

	temp = TTF_RenderText_Blended( fonte, string, textColor );

	if (temp !=NULL) {

	this->setBitmap(temp);
	this->CreateTextureFromBitmap();
	this->Blit(x,y);

	SDL_FreeSurface(temp);
	//SDL_DestroyTexture(TextTexture);
	}else {
    // could not create surface from text
       Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= Could not create surface from text" <<  endl;
       error=1;
	}

}*/

void CBitmap::Render(char *string,int x,int y, Colors::ColorDefinition textColor, CFont *fonte) const{
if (strlen(string)<=0) return;
		switch(this->getBitmapMode()) {

				case DRAW_TYPE_TEXTURE:
					RenderToTexture(string,x,y,textColor,fonte);

					break;

				case DRAW_TYPE_SURFACE:
					RenderToSurface(string,x,y,textColor,fonte);
				break;

				case DRAW_TYPE_TEX_SURF:
					RenderToTexture(string,x,y,textColor,fonte);
					RenderToSurface(string,x,y,textColor,fonte);
				break;
				default:
				break;
				}


}
void CBitmap::RenderToTexture(char *string,int x,int y, Colors::ColorDefinition textColor, CFont *fonte) const{
     Debug::debug(Debug::bitmap,__FUNCTION__) << "---------------------------" << endl;
     //Debug::debug(Debug::bitmap,__FUNCTION__) << "string =");
     //Debug::debug(Debug::bitmap,__FUNCTION__) << string);
	 ::std::string texto(string);
	 const int textsize = texto.size();
	 //Holds offsets
	int width,height; // to control Bitmap font size;
	SDL_Texture *TextTexture;
	SDL_Surface *temp;
    SDL_Rect retanguloDest;
    //Get offsets
    retanguloDest.x = x;
    retanguloDest.y = y;
	if (fonte->getType() == fonte->TrueTypeFont) {

	temp = TTF_RenderText_Blended( (TTF_Font *)fonte->getFont(), string, textColor.toSDL() );
	retanguloDest.w=temp->w;
	retanguloDest.h=temp->h;
	}else if (fonte->getType() == fonte->BitmapFont) {

		width= fonte->getSizeX();
		height = fonte->getSizeY();
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Print Bitmap Font text: "<< string << endl;
     	temp =  ((CBitmapFont *)fonte)->printBitmap(string);
		if (temp == NULL) return;
		SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format,0,0,0));
		retanguloDest.w=width * textsize;
		retanguloDest.h=height;
	}
	if (temp !=NULL) {

	//create texture
		if (SDL_MUSTLOCK(getBitmap()))
		::SDL_LockSurface(getBitmap());

		TextTexture=SDL_CreateTextureFromSurface(getMyRender(), temp);
		::SDL_UnlockSurface(getBitmap());
		//this->SetTexture(temp);
	if ( ! TextTexture ){
//			error = true;
			Debug::debug(220) << "Could not create Texture! - Error=" << SDL_GetError()<< endl;
		}else { }
	

		Debug::debug(Debug::bitmap,__FUNCTION__) << "[Destino(window): "<<GetWindow() <<" ] x= "<<x <<" , y= "<<y <<" , w= " << retanguloDest.w << ", h= " <<retanguloDest.h << endl;
			if(SDL_RenderCopy(getMyRender(),TextTexture, NULL, &retanguloDest)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

	
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(TextTexture);
	}else {
    // could not create surface from text
       Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= Could not create surface from text" <<  endl;
     //  error=1;
	}




}

void CBitmap::SetFullScreen(){
	//!nao sei se funciona no modo de compatibilidade
	//int erro=
	SDL_SetWindowFullscreen(GetWindow(),SDL_TRUE);
}

void CBitmap::SetWindowed(){
	//!nao sei se funciona no modo de compatibilidade
	//int erro=
	SDL_SetWindowFullscreen(GetWindow(),SDL_FALSE);

}

void CBitmap::SetWindowMode(int w, int h) {
	Debug::debug(Debug::bitmap,__FUNCTION__) << "w: "<<w <<" h: "<<h<<  endl;
SetWindowed();
SDL_DisplayMode fullscreen_mode;
        memset(&fullscreen_mode, 0, sizeof(fullscreen_mode));
        //SDL_zero();
        switch (GetState()->depth) {
        case 8:
            fullscreen_mode.format = SDL_PIXELFORMAT_INDEX8;
            break;
        case 15:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB555;
            break;
        case 16:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB565;
            break;
        case 24:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB24;
            break;
        default:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB888;
            break;
        }
        fullscreen_mode.refresh_rate = GetState()->refresh_rate;
	    fullscreen_mode.w=w;
		fullscreen_mode.h=h;
		fullscreen_mode.driverdata=0;
		int erro=SDL_SetWindowDisplayMode(GetWindow(),
                             &fullscreen_mode);
		if (erro !=0) {
		Debug::debug(Debug::bitmap,__FUNCTION__) << "erro: "<<SDL_GetError()<<  endl;

		}
		SetFullScreen();
}


} //end namespace SGF
