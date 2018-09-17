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
#ifndef mugen_sprite_h
#define mugen_sprite_h

//#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>
#include "../SGF_Config.h"
#include "SGF_Efects.h"
#include "SGF_SffSprMan.h"

namespace SGF {
class CBitmap;
class CSffSpriteManager;
namespace Mugen {
	class CEffects;
}

/* thread safe mugen Sprite
http://www.justsoftwaresolutions.co.uk/threading/thread-safe-copy-constructors.html
*/

struct BaseCMugenSprite{
	BaseCMugenSprite():
	unmaskedBitmap(SGF::Util::CReferenceCount<CBitmap>(NULL)),
    maskedBitmap(SGF::Util::CReferenceCount<CBitmap>(NULL))
	{};
	/* Loaded with a palette that may not be our own */
    SGF::Util::CReferenceCount<CBitmap> unmaskedBitmap;
    SGF::Util::CReferenceCount<CBitmap> maskedBitmap;

};

/* There are two types of sprites and an interface common to both here.
 *   CMugenSpriteV1 - Sprites that are tied to an sff v1 file. these are always pcx
 *   CMugenSpriteV2 - Sprites that come from an sff v2 and consist of an already made Bitmap
 *   CMugenSprite - interface that has some common operations like draw()
 */

/**
 * \class CMugenSprite
 *
 * \ingroup SGF_Sprite
 * 
 * \brief Sprites do MUGEN
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */


class CMugenSprite  {
public:
    CMugenSprite();
    virtual ~CMugenSprite();
	
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual short getX() const = 0;
    virtual short getY() const = 0;
    virtual unsigned short getGroupNumber() const = 0;
    virtual unsigned short getImageNumber() const = 0;
    virtual void render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects = Mugen::CEffects()) = 0;
	virtual void drawPartStretched(int sourceX1, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, const Mugen::CEffects & effects, const CBitmap & work) = 0; 
};


class  SGE_API CMugenSpriteV1 : public CMugenSprite ,private BaseCMugenSprite
{
    public:
	CMugenSpriteV1();
	~CMugenSpriteV1();
	CMugenSpriteV1(SGF::PCXDATA *pcx, bool mask);
	CMugenSpriteV1( const CMugenSpriteV1 &copy );

	CMugenSpriteV1 & operator=( const CMugenSpriteV1 &copy );
	// For map searching
	bool operator<( const CMugenSpriteV1 &copy );
	
	// Reads in the sprite info from stream
	//! foi substituído pelo SFFManager
	//void read(ifstream & ifile, const int loc);
	
	// Render sprite
	
	void render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects = Mugen::CEffects());
	virtual void drawPartStretched(int sourceX1, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, const Mugen::CEffects & effects, const CBitmap & work); 
	
	// load/reload sprite
	//! create a Bitmap from the pcx and store it internally
	//! verify the necessity of this method since the getBitmap also create a bitmap to 
	//! give it to the caller
	void load(bool mask=true);

	void reload(bool mask=true);

	bool isPCXLoaded() const {
		return pPCXSprite->isLoaded();
	};
	bool isBitmapLoaded() const {
		return loaded;
	};
	/* deletes raw pcx data */
    void unloadRaw();  

     /* just copies the bitmap */
    void copyImage(const CMugenSpriteV1 * copy);
	

	int getWidth() const;
	int getHeight() const;
	
        /* FIXME: replace types with uintX_t */
	// Setters getters
	inline void setNext(const long n) { my_next = n; }
	inline void setLocation(const long l) { my_location = l; }
	inline void setLength(const long l) { pPCXSprite->Lenght = l; }
	inline void setRealLength(const long l) { pPCXSprite->RealLenght = l; }
	inline void setNewLength(const long l) { pPCXSprite->RealLenght = l; }
	inline void setX(const short x){ pPCXSprite->x = x; }
	inline void setY(const short y){ pPCXSprite->y = y; }
	inline void setGroupNumber(const unsigned short gn){ pPCXSprite->GroupNumber = gn; }
	inline void setImageNumber(const unsigned short in){ pPCXSprite->ImageNumber = in; }
	inline void setPrevious(const unsigned short p){ my_prev = p; }
	inline void setSamePalette(const bool p){ pPCXSprite->bPalletSame = p; };
	//! método foi substituído pelo SFFManager
	//void loadPCX(ifstream & ifile, bool islinked, bool useact, unsigned char palsave1[]);
	
	inline unsigned long getNext() const { return my_next; }
	inline unsigned long getLocation() const { return my_location; }
	inline unsigned long getLength() const { return pPCXSprite->Lenght; }
	inline unsigned long getRealLength() const { return pPCXSprite->RealLenght; }
	//inline unsigned long getNewLength() const { return newlength; }
	inline short getX() const { return pPCXSprite->x; }
	inline short getY() const { return pPCXSprite->y; }
	inline unsigned short getGroupNumber() const { return pPCXSprite->GroupNumber; }
	inline unsigned short getImageNumber() const { return pPCXSprite->ImageNumber; }
	inline unsigned short getPrevious() const { return my_prev; }
	inline bool getSamePalette() const { return pPCXSprite->bPalletSame; }
	inline char *getComments() { return pPCXSprite->comments; }
		
		// get sprite
		Util::CReferenceCount<CBitmap> getBitmap(bool mask);
	    /* get the properly scaled sprite */
        Util::CReferenceCount<CBitmap> getFinalBitmap(const Mugen::CEffects & effects);


protected:
        /* destroy allocated things */
        void cleanup();
	
private:
		Util::Thread::LockObject my_spriteLock;
		PCXDATA *pPCXSprite;  //estrutura criada na Classe CSSFManager que comtém o sprite PCX já carregado
		
	/* FIXME: replace these types with explicitly sized types like
     * unsigned long -> uint32
     * short -> int16
     */
	uint32_t my_next;
	uint16_t my_prev;
	uint32_t my_location;
	int maskColor;
   //usado apenas pelo método render
	void draw(const Util::CReferenceCount<CBitmap> &, const int xaxis, const int yaxis, const CBitmap &, const Mugen::CEffects &);
    //mean the bitmap is created from the PCX
	bool loaded;
    
};


class  SGE_API CMugenSpriteV2: public CMugenSprite{
public:
    CMugenSpriteV2(const CBitmap & image, int group, int item, int x, int y);
    virtual ~CMugenSpriteV2();
	
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual short getX() const;
    virtual short getY() const;
    virtual unsigned short getGroupNumber() const;
    virtual unsigned short getImageNumber() const;
    virtual void render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects =Mugen::CEffects());
    virtual void drawPartStretched(int sourceX1, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, const Mugen::CEffects & effects, const CBitmap & work);

protected:
    CBitmap image;
    int group;
    int item;
    int x, y;
};


} //end SGF
#endif
