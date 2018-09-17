#ifndef mugen_sprite_h
#define mugen_sprite_h

//#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>

#include "efects.h"
#include "../sprite/sffspritemanager.h"

class CBitmap;
class CSffSpriteManager;

// Cria uma classe para cada sprite... implementar essa clase no ImageManager...
class CMugenSprite {
    public:
	CMugenSprite();
	CMugenSprite(PCXDATA *pcx, bool mask);
	CMugenSprite( const CMugenSprite &copy );
	~CMugenSprite();
	
	CMugenSprite & operator=( const CMugenSprite &copy );
	// For map searching
	bool operator<( const CMugenSprite &copy );
	
	// Reads in the sprite info from stream
	//! foi substituído pelo SFFManager
	//void read(std::ifstream & ifile, const int loc);
	
	// Render sprite
	//void render(const int xaxis, const int yaxis, CBitmap &, const double scalex=1, const double scaley=1);
	//void render(int facing, int vfacing, const int xaxis, const int yaxis, CBitmap &, const double scalex=1, const double scaley=1);
	void render(const int xaxis, const int yaxis, const CBitmap &where, const Mugen::CEffects &effects = Mugen::CEffects());
	
	// load/reload sprite
	void load(bool mask=true);
	void reload(bool mask=true);
	/* deletes raw pcx data */
        void unloadRaw();  

        /* just copies the bitmap */
        void copyImage(const CMugenSprite * copy);
	
	// get sprite
	CBitmap *getBitmap(bool mask);
	/* get the properly scaled sprite */
    CBitmap getFinalBitmap(const Mugen::CEffects & effects);
	const int getWidth();
	const int getHeight();
	
        /* FIXME: replace types with uintX_t */
	// Setters getters
	inline void setNext(const long n) { next = n; }
	inline void setLocation(const long l) { location = l; }
	inline void setLength(const long l) { length = l; }
	inline void setRealLength(const long l) { reallength = l; }
	inline void setNewLength(const long l) { reallength = l; }
	inline void setX(const short x){ this->x = x; }
	inline void setY(const short y){ this->y = y; }
	inline void setGroupNumber(const unsigned short gn){ groupNumber = gn; }
	inline void setImageNumber(const unsigned short in){ imageNumber = in; }
	inline void setPrevious(const unsigned short p){ prev = p; }
	inline void setSamePalette(const bool p){ samePalette = p; };
	//! método foi substituído pelo SFFManager
	//void loadPCX(std::ifstream & ifile, bool islinked, bool useact, unsigned char palsave1[]);
	
	inline const unsigned long getNext() const { return next; }
	inline const unsigned long getLocation() const { return location; }
	inline const unsigned long getLength() const { return length; }
	inline const unsigned long getRealLength() const { return reallength; }
	inline const unsigned long getNewLength() const { return newlength; }
	inline const short getX() const { return x; }
	inline const short getY() const { return y; }
	inline const unsigned short getGroupNumber() const { return groupNumber; }
	inline const unsigned short getImageNumber() const { return imageNumber; }
	inline const unsigned short getPrevious() const { return prev; }
	inline const bool getSamePalette() const { return samePalette; }
	inline const char *getComments() const { return comments; }
    static void draw(const CBitmap &bmp, const int xaxis, const int yaxis, const int x, const int y, const CBitmap &where, const Mugen::CEffects &effects);
    protected:
        /* destroy allocated things */
        void cleanup();
	
    private:
		PCXDATA *pPCXSprite;
		//CSffSpriteManager *pSFFSpriteManager;
        /* FIXME: replace these types with explicitly sized types like
         * unsigned long -> uint32
         * short -> int16
         */
	uint32_t next;
	uint32_t location;
	uint32_t length;
	uint32_t reallength;
	uint32_t newlength;
	int16_t x;
	int16_t y;
	uint16_t groupNumber;
	uint16_t imageNumber;
	uint16_t prev;
	bool samePalette;
	char comments[13];
	unsigned char * pcx;   //armazena o pcx do sprite
	
	//CBitmap *bitmap; // contem o bitmap correspondente
	int maskColor;
	CBitmap * unmaskedBitmap;
    CBitmap * maskedBitmap;
    
	void draw(const CBitmap &, const int xaxis, const int yaxis, const CBitmap &, const Mugen::CEffects &);
    
};

#endif
