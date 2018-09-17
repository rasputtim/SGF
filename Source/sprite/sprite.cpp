#include "../graphics/all.h"
#include <string.h>
#include <math.h>
#include "sprite.h"
#include "../util/SGE_Util.h"
#include "../global.h"
#include "../util/debug.h"

using namespace std;
using namespace Mugen;

CMugenSprite::CMugenSprite():
next(0),
location(0),
length(0),
reallength(0),
newlength(0),
x(0),
y(0),
groupNumber(0),
imageNumber(0),
prev(0),
samePalette(0),
pcx(NULL),
unmaskedBitmap(NULL),
maskedBitmap(NULL),
pPCXSprite(0)
{
    //Nothing
}

CMugenSprite::CMugenSprite(PCXDATA *pcx, bool mask):
next(0),
location(0),
length(0),
reallength(0),
newlength(0),
x(0),
y(0),
groupNumber(0),
imageNumber(0),
prev(0),
samePalette(0),
pcx(NULL),
unmaskedBitmap(NULL),
maskedBitmap(NULL),
pPCXSprite(pcx)
{
    Debug::debug(1900,__FUNCTION__)<< endl;
	this->next = 0;
    this->location = 0;
    this->length = pcx->Lenght;
	this->reallength = pcx->RealLenght;
    this->newlength = pcx->RealLenght;
	this->x = pcx->x;
    this->y = pcx->y;
    this->groupNumber = pcx->GroupNumber;
    this->imageNumber = pcx->ImageNumber;
    this->prev = 0;
    this->samePalette = pcx->bPalletSame;
    if (pcx->comments != 0){
        /* this line is right */
        memcpy(this->comments, pcx->comments, sizeof(CMugenSprite::comments));
    }

    /* why do we need to copy the pcx data if we already have the CBitmap? */
    if (pcx->pImageData != 0){
        this->pcx = new unsigned char[this->reallength];
        /* this line is right */
		memcpy(this->pcx, pcx->pImageData, this->reallength);
    } else {
        this->pcx = 0;
    }
    
	//maskedBitmap = new CBitmap(pPCXSprite);
	//unmaskedBitmap = new CBitmap(pPCXSprite);
    load(mask);
	
	    
}

CMugenSprite::CMugenSprite( const CMugenSprite &copy ):next(0),
location(0),
length(0),
reallength(0),
newlength(0),
x(0),
y(0),
groupNumber(0),
imageNumber(0),
prev(0),
samePalette(0),
pcx(NULL),
unmaskedBitmap(NULL),
maskedBitmap(NULL),
pPCXSprite(0){
	
	Debug::debug(10,__FUNCTION__) << "Copiando o conteudo do CMugenSprite: [ "<< &copy << " ] para o novo objeto: [ " << this << " ]" << endl;
    this->next = copy.next;
    this->location = copy.location;
    this->length = copy.length;
    this->reallength = copy.reallength;
    this->newlength = copy.newlength;
    this->x = copy.x;
    this->y = copy.y;
    this->groupNumber = copy.groupNumber;
    this->imageNumber = copy.imageNumber;
    this->prev = copy.prev;
    this->samePalette = copy.samePalette;

    if (copy.comments != 0){
        /* this line is right */
        memcpy(this->comments, copy.comments, sizeof(CMugenSprite::comments));
    }

    /* why do we need to copy the pcx data if we already have the CBitmap? */
    /*if (copy.pcx != 0){
        this->pcx = new unsigned char[this->reallength];
        // this line is right 
        memcpy(this->pcx, copy.pcx, this->reallength);
    } else {
        this->pcx = 0;
    } */
	this->pcx = 0;

    if (copy.unmaskedBitmap){
		
	this->unmaskedBitmap = new CBitmap(*copy.unmaskedBitmap);
	   Debug::debug(10,__FUNCTION__) << " Creating copy of unmaskedBitmap: [ CBitmap: " << unmaskedBitmap << " ] " << endl;
	}

    if (copy.maskedBitmap){
	this->maskedBitmap = new CBitmap(*copy.maskedBitmap);
		   Debug::debug(10,__FUNCTION__) << " Creating copy of maskedBitmap: [ CBitmap: " << maskedBitmap << " ] " << endl;
    
	}
	

}

CMugenSprite & CMugenSprite::operator=( const CMugenSprite &copy ){
    // Check for self-assignment!
    if (this == &copy)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.

   
	
	cleanup();
    
    this->next = copy.next;
    this->location = copy.location;
    this->length = copy.length;
    this->reallength = copy.reallength;
    this->newlength = copy.newlength;
    this->x = copy.x;
    this->y = copy.y;
    this->groupNumber = copy.groupNumber;
    this->imageNumber = copy.imageNumber;
    this->prev = copy.prev;
    this->samePalette = copy.samePalette;
    if (copy.comments){
        memcpy( this->comments, copy.comments, sizeof(CMugenSprite::comments) );
    }

    if (copy.pcx){
        this->pcx = new unsigned char[this->reallength];
        memcpy(this->pcx, copy.pcx, this->reallength);
    }

    if (copy.unmaskedBitmap){
	this->unmaskedBitmap = new CBitmap(*copy.unmaskedBitmap);
	}

    if (copy.maskedBitmap){
	this->maskedBitmap = new CBitmap(*copy.maskedBitmap);
	}
    
    return *this;
}
        
void CMugenSprite::copyImage(const CMugenSprite * copy){
    cleanup();

    if (copy->unmaskedBitmap){
	this->unmaskedBitmap = new CBitmap(*copy->unmaskedBitmap,true);
/*	if(!CSDLManager::GetInstance()->state->SDL_compatibility) {
		if(this->unmaskedBitmap->GetTexture())
			this->unmaskedBitmap->updateTexture();
		else
			this->unmaskedBitmap->CreateTextureFromBitmap();
	}*/
    }

    if (copy->maskedBitmap){
	this->maskedBitmap = new CBitmap(*copy->maskedBitmap,true);
	/*if(!CSDLManager::GetInstance()->state->SDL_compatibility) {
	if(this->unmaskedBitmap->GetTexture())
			this->maskedBitmap->updateTexture();
		else
			this->maskedBitmap->CreateTextureFromBitmap();
	}*/
    }
}

bool CMugenSprite::operator<( const CMugenSprite &copy ){
    return ( (this->groupNumber < copy.groupNumber) && (this->imageNumber < copy.imageNumber) );
}

void CMugenSprite::cleanup(){
    /* **FIXME** this needs fixing on determining pcx is empty or not */
    if (pcx){
        delete[] pcx;
        pcx = NULL;
    }

    if (unmaskedBitmap){
	delete unmaskedBitmap;
    unmaskedBitmap = NULL;
    }

    if (maskedBitmap){
	delete maskedBitmap;
    maskedBitmap = NULL;
    }
}

CMugenSprite::~CMugenSprite(){
    cleanup();
}

// Set sprite info
// Foi substituído pelo SFFManager
/*
void CMugenSprite::read(std::ifstream & ifile, const int loc){
    // Go to next sprite
    ifile.seekg(loc, std::ios::beg);
    
    // set the sprite location
    this->location = loc;
    
    ifile.read((char *)&next, sizeof(next));
    ifile.read((char *)&length, sizeof(length));
    ifile.read((char *)&x, sizeof(x));
    ifile.read((char *)&y, sizeof(y));
    ifile.read((char *)&groupNumber, sizeof(groupNumber));
    ifile.read((char *)&imageNumber, sizeof(imageNumber));
    ifile.read((char *)&prev, sizeof(prev));
    ifile.read((char *)&samePalette, sizeof(samePalette));
    ifile.read((char *)comments, sizeof(comments));
    newlength = reallength = next - loc - 32;
     
    // Last sprite
    if (next == 0){
	if (samePalette){
            newlength = reallength = length - 768;
        } else {
            newlength = reallength = length;
        }
    }
} */
/*
void MugenSprite::render(const int xaxis, const int yaxis, CBitmap &where, const double scalex, const double scaley){
    const int placex = (xaxis - this->x );
    const int placey = (yaxis - this->y );
    
    // temp for scaling
    CBitmap modImage = CBitmap::temporaryBitmap(CBitmap->getWidth() * scalex, CBitmap->getHeight() * scaley);
    CBitmap->Stretch(modImage);
    
    modImage.draw(placex, placey, where);
}

void MugenSprite::render(int facing, int vfacing, const int xaxis, const int yaxis, CBitmap &where, const double scalex, const double scaley){
    const int placex = (xaxis - this->x );
    const int placey = (yaxis - this->y );
    // temp for scaling
    CBitmap modImage = CBitmap::temporaryBitmap(CBitmap->getWidth() * scalex, CBitmap->getHeight() * scaley);
    CBitmap->Stretch(modImage);
    
    if (!facing && vfacing){
	modImage.drawHFlip(placex + modImage.getWidth(), placey, where);
	
    } else if (!vfacing && facing){
	modImage.drawVFlip(placex, placey - modImage.getHeight(), where);
	
    } else if ( !vfacing && !facing ){
	modImage.drawHVFlip(placex + modImage.getWidth(), placey - modImage.getHeight(), where);
	
    } else{
	modImage.draw(placex, placey, where);
    }
}
*/
static bool isScaled(const Mugen::CEffects & effects){
    double epsilon = 0.00001;
    return fabs(effects.scalex - 1) > epsilon ||
           fabs(effects.scaley - 1) > epsilon;
}

CBitmap CMugenSprite::getFinalBitmap(const Mugen::CEffects & effects){
	Debug::debug(2100,__FUNCTION__) << "Will Get the final bitmap"<< endl;
    CBitmap * use = getBitmap(effects.mask);
    CBitmap modImage = *use;
    if (isScaled(effects)){
		Debug::debug(2100,__FUNCTION__) << "Scaled Bitmap with rotozoom"<< endl;
		Debug::debug(1900,__FUNCTION__) << " Is Scaled" << endl;
        modImage = CBitmap::temporaryBitmap((int) (use->getWidth() * effects.scalex), (int) (use->getHeight() * effects.scaley));
        use->Stretch(modImage);
    }
     return modImage;
}

void CMugenSprite::render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects){
    
	
    Debug::debug(1900,__FUNCTION__) << "Rendering to (x,y)= ( "<<xaxis<< " , " << yaxis << " )"<< endl;
	//getFinalBitmap(effects).Blit(xaxis,yaxis,where);
	draw(getFinalBitmap(effects), xaxis, yaxis, where, effects);
	

}


void CMugenSprite::load(bool mask){
   Debug::debug(10,__FUNCTION__) << endl;
	 
	if (pcx){
		CBitmap *temp= new CBitmap(pPCXSprite);
		if (!temp->getError()){
			if (mask){
				maskedBitmap = temp;
				maskedBitmap->replaceColor(maskedBitmap->get8BitMaskColor(), CBitmap::MaskColor());
		
			} else {
			 unmaskedBitmap = temp;
			//unmaskedBitmap = new CBitmap(temp, mask);
			
			}
		
		}else {
			maskedBitmap=NULL;
			unmaskedBitmap=NULL;
			//Maybe throw an exception
			Debug::debug(100,__FUNCTION__) <<" Error Creating bitmap from PCX" << endl;
		}

        
    }
}

void CMugenSprite::reload(bool mask){
    if (maskedBitmap){
        delete maskedBitmap;
        maskedBitmap = NULL;
    }

    if (unmaskedBitmap){
        delete unmaskedBitmap;
        unmaskedBitmap = NULL;
    }
    // transforma o pcx num CBitmap
    load(mask);
}

CBitmap *CMugenSprite::getBitmap(bool mask)  {
      Debug::debug(2100,__FUNCTION__) << "CMugenSprite: [ "<< this << " ] - Will Get the bitmap with mask: "<< mask << endl;
    if (mask){
        if (maskedBitmap){
            return maskedBitmap;
        }
        if (unmaskedBitmap){
            maskedBitmap = new CBitmap(*unmaskedBitmap, true);
            //maskedBitmap = new CBitmap(pPCXSprite);
			int bitmask = maskedBitmap->get8BitMaskColor();
			//Debug::debug(1900,__FUNCTION__) << " CMugenSprite::getBitmap Mask 8 bit color = " << bitmask << endl;//(int) bitmask.r<< " , "<<(int) bitmask.g<< " , "<<(int) bitmask.b<< endl;
			//Debug::debug(1900,__FUNCTION__) << " CMugenSprite::getBitmap Pixel 0 color = " << maskedBitmap->getPixel(0,0) << endl;
            //Debug::debug(1900,__FUNCTION__) << " CMugenSprite::getBitmap Def Mask Color = " << Colors::makeColor(255,0,255) << endl;
			//maskedBitmap->replaceColor(maskedBitmap->getPixel(0,0), Colors::makeColor(255,0,255));
            maskedBitmap->replaceColor(bitmask, CBitmap::MaskColor());
            return maskedBitmap;
        }
    } else {
        if (unmaskedBitmap){
            return unmaskedBitmap;
        }
        return maskedBitmap;
    }
    return NULL;
}

/* deletes raw data */
void CMugenSprite::unloadRaw(){
    if (pcx){
        delete[] pcx;
        pcx = NULL;
    }
}
const int CMugenSprite::getWidth(){
    if (maskedBitmap){
        return maskedBitmap->getWidth();
    }
    return unmaskedBitmap->getWidth();
}

const int CMugenSprite::getHeight(){
    if (maskedBitmap){
        return maskedBitmap->getHeight();
    }
    return unmaskedBitmap->getHeight();
}
//! método foi substituído pelo SFFManager
/*	
void CMugenSprite::loadPCX(std::ifstream & ifile, bool islinked, bool useact, unsigned char palsave1[]){
    // TODO: 768 is littered everywhere, replace with a constant 
    ifile.seekg(location + 32, ios::beg);
    if (samePalette){
	// Lets give it space for the palette
	Debug::debug(1900,__FUNCTION__) << "This sprite is less that 768 or has a shared palette - Group: " << getGroupNumber() << " | Image: " << getImageNumber() << endl;
	newlength += 768;
	pcx = new unsigned char[newlength];
        memset(pcx, 0, newlength);
    } else {
	pcx = new unsigned char[reallength];
        memset(pcx, 0, reallength);
    }
    ifile.read((char *)pcx, reallength); 
    if (!islinked){
	if (!useact){
	    if (samePalette){
		memcpy( pcx + (reallength), palsave1, 768);
		Debug::debug(1,__FUNCTION__) << "Applying 1st palette to Sprite: " << imageNumber << " in Group: " << groupNumber << endl;
	    } else {
		memcpy(palsave1, pcx+(reallength)-768, 768);
	    }
	} else {
	    // Replace all palettes with the one supplied in act
	    if ( samePalette){
		memcpy(pcx + (reallength), palsave1, 768);
	    } else {
                // TODO: add an explanation of what group 9000 means here 
		if (!(groupNumber == 9000 && imageNumber == 1)){
		    memcpy(pcx + (reallength)-768, palsave1, 768);
		} 
	    }
	}
    }
    
    load();
}
*/
/*
void CMugenSprite::draw(const CBitmap &bmp, const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects){

	
	int startWidth = 0;
    int startHeight = 0;
    int width = bmp.getWidth();
    int height = bmp.getHeight();

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

    const int normalX = (xaxis - this->x);
    const int normalY = (yaxis - this->y);
    const int flippedX = (xaxis - bmp.getWidth() + this->x);
    const int flippedY = (yaxis - bmp.getHeight() + this->y);

    const int FLIPPED = -1;
    const int NOT_FLIPPED = 1;
    

// This needs to be a switch trans = None, Add, Add1, Sub1, Addalpha
   
	switch (effects.trans){
	case AddAlpha:{
	    // Need to figure out blend correctly addalpha is given to two locations low and high ?
	    CBitmap::transBlender(0, 0, 0, effects.alphalow);
	    break;
	}
	case Add:{
	    // this additive 100% I assume... not totally sure
	    // CBitmap::addBlender( 255, 255, 255, 255 );
	    CBitmap::addBlender(0, 0, 0, 255);
	    break;
	}
	case Add1:{
	    // 50%
	    CBitmap::addBlender(128, 128, 128, 255);
	    break;
	}
	case Sub:{
	    // Shadow effect
	    // CBitmap::multiplyBlender( 0, 0, 0, 128 );
		// no diference blender os valores de r,g,b aqui não importam e não são usados. só o valor de alpha é usado
	    CBitmap::differenceBlender(0, 0, 0, 128);
	     break;
	}
	case None:
	default:{
	    break;
	}
    }



	if ( (effects.facing == FLIPPED) && (effects.vfacing == NOT_FLIPPED)){
	if (effects.trans != None){
	    bmp.drawTransHFlip(flippedX, normalY, where);
	} else {
	    // bmp.drawHFlip(placex + bmp.getWidth() / 2, placey, where);
	    bmp.drawHFlip(flippedX, normalY, startWidth, startHeight, width, height, where);
	}
	
	} else if ( (effects.facing == NOT_FLIPPED) &&(effects.vfacing == FLIPPED) ){
	if (effects.trans != None){
	    bmp.drawTransVFlip(normalX, flippedY, where);
	} else {
	    bmp.drawVFlip(normalX, flippedY, where);
	}
    } else if ((effects.facing == FLIPPED) && (effects.vfacing == FLIPPED) ){
		if (effects.trans != None){
		 bmp.drawTransHVFlip(flippedX, flippedY, where);
		} else {
	    bmp.drawHVFlip(flippedX, flippedY, where);
		}
    } else {
	//if( effects.mask ){
	if (effects.trans != None){
		bmp.drawTrans(normalX, normalY, where);
	} else {
	    bmp.draw(normalX, normalY, startWidth, startHeight, width, height, where);
	} 
	//} else {
	//    bmp.Blit( placex, placey, where );
//	}
	
}
	
}
*/

void CMugenSprite::draw(const CBitmap &bmp, const int xaxis, const int yaxis, const int x, const int y, const CBitmap &where, const Mugen::CEffects &effects){
    Debug::debug(1900,__FUNCTION__) << endl;
	
	int startWidth = 0;
    int startHeight = 0;
    int width = bmp.getWidth();
    int height = bmp.getHeight();

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



    const int normalX = (xaxis - x);
    const int normalY = (yaxis - y);
    const int flippedX = (xaxis - bmp.getWidth() + x);
    const int flippedY = (yaxis - bmp.getHeight() + y);

    const int FLIPPED = -1;
    const int NOT_FLIPPED = 1;

	switch (effects.trans){
	case AddAlpha : {
	    // Need to figure out blend correctly addalpha is given to two locations low and high ?
	    CBitmap::transBlender(0, 0, 0, effects.alphalow);
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
	    CBitmap::differenceBlender(0, 0, 0, 128);
	    break;
	}
	case None:
	default:{
	    break;
	}
    }
//Todo: implementar as novas funções com efeito
    if ((effects.facing == FLIPPED) && (effects.vfacing == NOT_FLIPPED)){
        if (effects.trans != None){
            bmp.translucent().drawHFlip(flippedX, normalY, effects.filter, where);
			//bmp.drawTransHFlip(flippedX, normalY, where);
        } else {
            // bmp.drawHFlip(placex + bmp.getWidth() / 2, placey, where);
            bmp.drawHFlip(flippedX, normalY, startWidth, startHeight, width, height, effects.filter, where);
			//bmp.drawHFlip(flippedX, normalY, startWidth, startHeight, width, height,  where);
			
        }
    } else if ( (effects.vfacing == FLIPPED) && (effects.facing == NOT_FLIPPED)){
        if (effects.trans != None){
            bmp.translucent().drawVFlip(normalX, flippedY, effects.filter, where);
			//bmp.drawTransVFlip(flippedX, normalY, where);
        } else {
         bmp.drawVFlip(normalX, flippedY, effects.filter, where);
		 //	bmp.drawVFlip(normalX, flippedY, where);
        }
    } else if ((effects.vfacing == FLIPPED) && (effects.facing == FLIPPED)){
        if (effects.trans != None){
            bmp.translucent().drawHVFlip(flippedX, flippedY, effects.filter, where);
			//bmp.drawTransHVFlip(flippedX, normalY, where);
        } else {
         bmp.drawHVFlip(flippedX, flippedY, effects.filter, where);
			//bmp.drawHVFlip(flippedX, flippedY,  where);
        }
    } else {
        //if( effects.mask ){
        if (effects.trans != None){
             bmp.translucent().draw(normalX, normalY, effects.filter, where);
			//bmp.drawTrans(normalX, normalY, where);
        } else {
             bmp.draw(normalX, normalY, startWidth, startHeight, width, height, effects.filter, where);
			//bmp.draw(normalX, normalY, startWidth, startHeight, width, height,  where);
		}
        //} else {
        //    bmp.Blit( placex, placey, where );
        //	}
    }
}

void CMugenSprite::draw(const CBitmap &bmp, const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects){
    draw(bmp, xaxis, yaxis, this->x, this->y, where, effects);
}