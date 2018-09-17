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

#include "graphics/all.h"
#include <string.h>
#include <math.h>
#include "sprite/SGF_MugenSprite.h"
#include "util/SGF_Util.h"
#include "SGF_Global.h"
#include "util/SGF_Debug.h"
#include "objects/SGF_Object.h"

using namespace std;
using namespace SGF::Mugen;

namespace SGF{

CMugenSprite::CMugenSprite(){
}

CMugenSprite::~CMugenSprite(){
}

CMugenSpriteV1::CMugenSpriteV1():
pPCXSprite(0),
my_next(0),
my_prev(0),
my_location(0),
loaded(false)
{
    //Nothing
}

CMugenSpriteV1::CMugenSpriteV1(PCXDATA *pcx, bool mask):
pPCXSprite(pcx),
my_next(0),
my_prev(0),
my_location(0),
loaded(false)
{
 
	load(mask);


}

CMugenSpriteV1::CMugenSpriteV1( const CMugenSpriteV1 &copy ):
BaseCMugenSprite((Util::Thread::ScopedLock(copy.my_spriteLock),copy)),
pPCXSprite(0),
my_next(copy.my_next),
my_prev(copy.my_prev),
my_location(copy.my_location),
loaded(copy.loaded){

	Debug::debug(Debug::resources,__FUNCTION__) << "Copiando o conteudo do CMugenSpriteV1: [ "<< &copy << " ] para o novo objeto: [ " << this << " ]" << endl;
    if (copy.unmaskedBitmap != NULL){

	this->unmaskedBitmap = new CBitmap(*copy.unmaskedBitmap);
	   Debug::debug(Debug::resources,__FUNCTION__) << " Creating copy of unmaskedBitmap: [ CBitmap: " << unmaskedBitmap.raw() << " ] " << endl;
	}

    if (copy.maskedBitmap != NULL){
	this->maskedBitmap = new CBitmap(*copy.maskedBitmap);
		   Debug::debug(Debug::resources,__FUNCTION__) << " Creating copy of maskedBitmap: [ CBitmap: " << maskedBitmap.raw() << " ] " << endl;

	}


}

CMugenSpriteV1 & CMugenSpriteV1::operator=( const CMugenSpriteV1 &copy ){
    // Check for self-assignment!
    if (this == &copy)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.
	cleanup();

    this->my_next = copy.my_next;
	this->my_prev = copy.my_prev;
    this->my_location = copy.my_location;
	this->loaded = copy.loaded;
    if (copy.unmaskedBitmap != NULL){
	this->unmaskedBitmap = new CBitmap(*copy.unmaskedBitmap);
	}

    if (copy.maskedBitmap != NULL){
	this->maskedBitmap = new CBitmap(*copy.maskedBitmap);
	}

    return *this;
}

void CMugenSpriteV1::copyImage(const CMugenSpriteV1 * copy){
    cleanup();

    if (copy->unmaskedBitmap != NULL){
	this->unmaskedBitmap = new CBitmap(*copy->unmaskedBitmap,true);

    }

    if (copy->maskedBitmap !=NULL){
	this->maskedBitmap = new CBitmap(*copy->maskedBitmap,true);

    }
}


bool CMugenSpriteV1::operator<( const CMugenSpriteV1 &copy ){
	return ( (this->pPCXSprite->GroupNumber < copy.pPCXSprite->GroupNumber) && (this->pPCXSprite->ImageNumber < copy.pPCXSprite->ImageNumber) );
}

void CMugenSpriteV1::cleanup(){
   if (pPCXSprite){
        delete pPCXSprite;
        pPCXSprite = NULL;
    }
   loaded=false;
}

CMugenSpriteV1::~CMugenSpriteV1(){
    cleanup();
}

static bool isScaled(const Mugen::CEffects & effects){
    double epsilon = 0.00001;
    return fabs(effects.scalex - 1) > epsilon ||
           fabs(effects.scaley - 1) > epsilon;
}

Util::CReferenceCount<CBitmap> CMugenSpriteV1::getFinalBitmap(const Mugen::CEffects & effects){
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Will Get the final bitmap"<< endl;
    return getBitmap(effects.mask);
	//Scalling is treated on texture level
	//CBitmap * use = getBitmap(effects.mask);
    //CBitmap modImage = *use;

	/*if (isScaled(effects)){
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Scaled Bitmap with rotozoom"<< endl;
		Debug::debug(Debug::bitmap,__FUNCTION__) << " Is Scaled" << endl;
        modImage = CBitmap::temporaryBitmap((int) (use->getWidth() * effects.scalex), (int) (use->getHeight() * effects.scaley));
        use->Stretch(modImage);
    }*/
    // return modImage;
}


void CMugenSpriteV1::render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects){


    Debug::debug(Debug::bitmap,__FUNCTION__) << "Rendering to (x,y)= ( "<<xaxis<< " , " << yaxis << " )"<< endl;
	//getFinalBitmap(effects).Blit(xaxis,yaxis,where);
	draw(getFinalBitmap(effects), xaxis, yaxis, where, effects);


}

void CMugenSpriteV1::drawPartStretched(int sourceX1, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, const Mugen::CEffects & effects, const CBitmap & work){
	getBitmap(effects.mask)->BlitMasked(sourceX1, sourceY, sourceWidth,  sourceHeight, destX,destHeight, work);

}

void CMugenSpriteV1::load(bool mask){
	Debug::debug(Debug::bitmap,__FUNCTION__)<<"BEGIN _________________________________________" << endl;

	if (this->pPCXSprite->pImageData){
		CBitmap *temp= new CBitmap(pPCXSprite);
		if (!temp->getError()){
			if (mask){
				maskedBitmap = temp;
				// a cor da mascara é controlada no CBitmap pela propriedade createdFromPCX.
				// não é preciso mais fazer o replaceColor
				//maskedBitmap->replaceColor(maskedBitmap->get8BitMaskColor(), CBitmap::getDefaultColorkey());
				//maskedBitmap->applyTrans(maskedBitmap->getPCXMaskColor());
			} else {
			 unmaskedBitmap = temp;

			}
			loaded=true;
		}else {
			maskedBitmap=NULL;
			unmaskedBitmap=NULL;
			//Maybe throw an exception
			Debug::debug(Debug::gameObject,__FUNCTION__) <<" Error Creating bitmap from PCX" << endl;
		}


    }
	Debug::debug(Debug::bitmap,__FUNCTION__)<<"END _________________________________________" << endl;

}

void CMugenSpriteV1::reload(bool mask){
    maskedBitmap = NULL;
    unmaskedBitmap = NULL;

    // transforma o pcx num CBitmap
    load(mask);
}

Util::CReferenceCount<CBitmap> CMugenSpriteV1::getBitmap(bool mask)  {
      Debug::debug(Debug::bitmap,__FUNCTION__) << "CMugenSpriteV1: [ "<< this << " ] - Will Get the bitmap with mask: "<< mask << endl;
    if (mask){
        if (maskedBitmap!=NULL){
            return maskedBitmap;
        }else
        if (unmaskedBitmap!=NULL){
            maskedBitmap = Util::CReferenceCount<CBitmap>(new CBitmap(*unmaskedBitmap, true));
            return maskedBitmap;
        }
    } else {
        if (unmaskedBitmap !=NULL){
            return unmaskedBitmap;
        }else if (maskedBitmap != NULL)
        return maskedBitmap;
		else Debug::debug(Debug::error,__FUNCTION__) <<" There is neither masked or unmasked bitmap load - Todo:: Throw a exception" << endl;
    }
    return NULL;
}

/* deletes raw data */
void CMugenSpriteV1::unloadRaw(){
    if (pPCXSprite){
        delete pPCXSprite;
        pPCXSprite = NULL;
    }
	
}
int CMugenSpriteV1::getWidth()const{
    if (maskedBitmap != NULL){
        return maskedBitmap->getWidth();
    }
    return unmaskedBitmap->getWidth();
}

int CMugenSpriteV1::getHeight()const{
    if (maskedBitmap !=NULL){
        return maskedBitmap->getHeight();
    }
    return unmaskedBitmap->getHeight();
}



//usado no:
//CCharacter::drawAfterImage
// método draw interno
static void doDraw( CBitmap *bmp, const int xaxis, const int yaxis, const int x, const int y, const CBitmap &where, const Mugen::CEffects &effects){
    Debug::debug(Debug::bitmap,__FUNCTION__) << "REALLY DRAWING THE BITMAP to ( "<<xaxis<< " , " << yaxis << " )"<< endl;
	Debug::debug(Debug::bitmap,__FUNCTION__) << "H_FLIP ( "<< effects.hflip << " )"<< endl;
    Debug::debug(Debug::bitmap,__FUNCTION__) << "V_FLIP ( "<< effects.vflip << " )"<< endl;

	if (bmp == NULL){
        return;
    }
	Debug::debug(Debug::bitmap,__FUNCTION__) << "BEGIN" << endl;
	bmp->setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	int startWidth = 0;
    int startHeight = 0;
    int width = bmp->getWidth();
    int height = bmp->getHeight();

    if (effects.dimension.x1 != -1){
        startWidth = effects.dimension.x1;
    }

    if (effects.dimension.x2 != -1){
        width = effects.dimension.x2;
    }

    if (effects.dimension.y1 != -1){
        startHeight = effects.dimension.y1;
    }

    if (effects.dimension.y2 != -1){
        height = effects.dimension.y2;
    }

    bool rotated = fabs(effects.rotation) > 0.1;

    const int normalX = (xaxis - x);
    const int normalY = (yaxis - y);
    const int flippedX = (xaxis - bmp->getWidth() + x);
    const int flippedY = (yaxis - bmp->getHeight() + y);

 
	switch (effects.trans){
		case AddAlpha : {
            CBitmap::transBlender(0, 0, 0, effects.alphaSource);
	    //TODO:: Verificar porque não está funcionando alphaBender
		//	CBitmap::alphaBlender(effects.alphaSource, effects.alphaDest);
	    break;
	}
	case Translucent : {
	    // Need to figure out blend correctly addalpha is given to two locations low and high ?
	    CBitmap::transBlender(0, 0, 0, effects.alphaSource);
	    break;
	}
	case Add : {
	    // this additive 100% I assume... not totally sure
	    // CBitmap::addBlender( 255, 255, 255, 255 );
	    CBitmap::addBlender(0, 0, 0, 255);
	    break;
	}
	case Add1 : {
	    // 50%
	    CBitmap::addBlender(128, 128, 128, 255);
	    break;
	}
	case Sub : {
	    // Shadow effect
	    // CBitmap::multiplyBlender( 0, 0, 0, 128 );
	    CBitmap::differenceBlender(0, 0, 0, 255);
	    break;
	}
	case None:
	default:{
	    break;
	}
    }
//Todo: implementar as novas funções com efeito
	if (rotated){
        /* FIXME: handle trans and flipping */
        // bmp->drawRotate(normalX, normalY, (int) effects.rotation, where);
        bmp->drawPivot(width / 2, height, xaxis, yaxis, (int) effects.rotation, where);
    } else {
	if (effects.hflip && !effects.vflip){
        if (effects.trans != None){
            bmp->translucent().drawHFlip(flippedX, normalY, effects.filter, where);
			
        } else {
            bmp->drawHFlip(flippedX, normalY, startWidth, startHeight, width, height, effects.filter, where);
		
        }
    } else if ( effects.vflip && !effects.hflip){
        if (effects.trans != None){
            bmp->translucent().drawVFlip(normalX, flippedY, effects.filter, where);
		
        } else {
         bmp->drawVFlip(normalX, flippedY, effects.filter, where);
		 
        }
    } else if (effects.vflip && effects.hflip){
        if (effects.trans != None){
            bmp->translucent().drawHVFlip(flippedX, flippedY, effects.filter, where);
		} else {
         bmp->drawHVFlip(flippedX, flippedY, effects.filter, where);
		}
    } else {
        //if( effects.mask ){
        if (effects.trans != None){
             bmp->translucent().draw(normalX, normalY, effects.filter, where);
		 } else {
             bmp->draw(normalX, normalY, startWidth, startHeight, width, height, effects.filter, where);
		}
        //} else {
        //    bmp.Blit( placex, placey, where );
        //	}
    }
	} //end rotaded
	Debug::debug(Debug::bitmap,__FUNCTION__) << "END" << endl;

}

static void doDraw(const Util::CReferenceCount<CBitmap> & bmp, const int xaxis, const int yaxis, const int x, const int y, const CBitmap &where, const CEffects &effects){
    doDraw(bmp.raw(), xaxis, yaxis, x, y, where, effects);
}




//usado apenas pelo método render
void CMugenSpriteV1::draw(const Util::CReferenceCount<CBitmap> &bmp, const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects){
    
	doDraw(bmp.raw(), xaxis, yaxis, this->pPCXSprite->x, this->pPCXSprite->y, where, effects);
}



CMugenSpriteV2::CMugenSpriteV2(const CBitmap & image, int group, int item, int x, int y):
image(image),
group(group),
item(item),
x(x),
y(y){
}

CMugenSpriteV2::~CMugenSpriteV2(){
}

int CMugenSpriteV2::getWidth() const {
    return image.getWidth();
}

int CMugenSpriteV2::getHeight() const {
    return image.getHeight();
}

short CMugenSpriteV2::getX() const {
    return x;
}

short CMugenSpriteV2::getY() const {
    return y;
}

unsigned short CMugenSpriteV2::getGroupNumber() const {
    return group;
}

unsigned short CMugenSpriteV2::getImageNumber() const {
    return item;
}

void CMugenSpriteV2::render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects){
    doDraw(&image, xaxis, yaxis, this->x * effects.scalex, this->y * effects.scaley, where, effects);
}

void CMugenSpriteV2::drawPartStretched(int sourceX1, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, const Mugen::CEffects & effects, const CBitmap & work){
    CBitmap single(image, sourceX1, sourceY, sourceWidth, sourceHeight);
    single.drawStretched(destX, destY, destWidth, destHeight, work);
}




} //end SGF