/***************************************************************************
                          CRleSprite.cpp  -  description
                             -------------------
    begin                : Mon Sep 24 2001
    copyright            : (C) 2001 by upi
    email                : upi@apocalypse.rulez.org
 ***************************************************************************/

#include "sprite/SGF_RleSprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "../Gamecore/mortal/gfx.h"
//#include "common.h"
#include "graphics/SGF_Color.h"


/// Sanity: This is the maximal number of entries in a .DAT file.
#define MAXDATACOUNT	65530

namespace SGF {
inline void ChangeEndian32( Uint32& a_riArg )
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	char* pcArg = (char*)&a_riArg;
	char cTemp;
	cTemp = pcArg[0]; pcArg[0] = pcArg[3]; pcArg[3] = cTemp;
	cTemp = pcArg[1]; pcArg[1] = pcArg[2]; pcArg[2] = cTemp;
#endif
}


inline void ChangeEndian16( Uint16& a_riArg )
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	char* pcArg = (char*)&a_riArg;
	char cTemp;
	cTemp = pcArg[0]; pcArg[0] = pcArg[1]; pcArg[1] = cTemp;
#endif
}


inline Uint32 ConvertEndian32( Uint32 a_iArg )
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	char* pcArg = (char*)&a_iArg;
	char cTemp;
	cTemp = pcArg[0]; pcArg[0] = pcArg[3]; pcArg[3] = cTemp;
	cTemp = pcArg[1]; pcArg[1] = pcArg[2]; pcArg[2] = cTemp;
#endif
	return a_iArg;
}


inline Uint16 ConvertEndian16( Uint16 a_iArg )
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	char* pcArg = (char*)&a_iArg;
	char cTemp;
	cTemp = pcArg[0]; pcArg[0] = pcArg[1]; pcArg[1] = cTemp;
#endif
	return a_iArg;
}



CRleSprite::CRleSprite( const char* a_pcFilename, int a_iNumColors )
{
	my_data = new RlePack_P;
	my_data->m_enTint = NO_TINT;
	my_data->m_iCount = 0;
	my_data->m_iArraysize = 0;
	my_data->m_pSprites = NULL;
	my_data->m_pData = NULL;
	
	my_data->m_iColorCount = 0;
	my_data->m_iColorOffset = 0;
	
	// Load file and stuff
	
	LoadFile( a_pcFilename, a_iNumColors );
}


CRleSprite::~CRleSprite()
{
	if (!my_data)
		return;
	
	if (my_data->m_pSprites)
	{
		delete[] my_data->m_pSprites;
		my_data->m_pSprites = NULL;
	}
	
	free( my_data->m_pData );
	delete( my_data );
	my_data = NULL;
}


void CRleSprite::Clear()
{
	if ( my_data && my_data->m_pSprites )
	{
		delete[] my_data->m_pSprites;
		my_data->m_pSprites = NULL;
	}
}


int CRleSprite::LoadFile( const char* a_pcFilename, int a_iNumColors )
{
	FILE* f;
	
	f = fopen( a_pcFilename, "rb" );
	if (f==NULL)
	{
		Debug::debug(Debug::error,__FUNCTION__) << "Can't open file: "<< a_pcFilename <<endl;
		return -1;
	}
	
	fseek( f, 0, SEEK_END );
	long iFileSize = ftell ( f );
	my_data->m_pData = malloc( iFileSize );
	if ( NULL == my_data->m_pData )
	{
		fclose( f );
		return -1;
	}
	
	fseek( f, 0, SEEK_SET );
	int iRead = fread( my_data->m_pData, 1, iFileSize, f );
	fclose( f );
	
	my_data->m_iColorCount = a_iNumColors;
	
	if ( iFileSize != iRead )
	{
		Debug::debug(Debug::error,__FUNCTION__) << "Warning CRleSprite(): iFileSize= " << iFileSize << " iRead= " <<  iRead <<endl;
	}
	
	struct SHeader
	{
		char	acDummy[8];
		Uint32	iDatacount;
	} *poHeader = (SHeader*) my_data->m_pData;
	
	ChangeEndian32( poHeader->iDatacount );
	Debug::debug(Debug::error,__FUNCTION__) << "File " << a_pcFilename<< " contains " <<poHeader->iDatacount << " entries." <<endl;
	
	if (poHeader->iDatacount>MAXDATACOUNT) poHeader->iDatacount = MAXDATACOUNT;		// Sanity
	
	my_data->m_iArraysize = poHeader->iDatacount;
	my_data->m_pSprites = new RLE_SPRITE*[ poHeader->iDatacount ];
	
	char* pcNext = ((char*)my_data->m_pData) + sizeof(SHeader);
	char* pcEnd = ((char*)my_data->m_pData) + iFileSize;
	
	while ( pcNext < pcEnd - 4 )
	{
		if ( 0 == strncmp( pcNext, "prop", 4 ) )
		{
			struct SProperty
			{
				char	acName[4];
				Uint32	iSize;
			} *poProperty = (SProperty*) (pcNext+4);
			ChangeEndian32( poProperty->iSize );
			
			pcNext += 4 + sizeof(SProperty) + poProperty->iSize;
		}
		else if ( 0 == strncmp( pcNext, "RLE ", 4 ) )
		{
			struct SRLE
			{
				RLE_SPRITE	oSprite;
			} *poRle = (SRLE*) (pcNext+10);
			poRle->oSprite.color_depth = ConvertEndian16(poRle->oSprite.color_depth);
			poRle->oSprite.w = ConvertEndian16(poRle->oSprite.w);
			poRle->oSprite.h = ConvertEndian16(poRle->oSprite.h);
			poRle->oSprite.size = ConvertEndian32(poRle->oSprite.size);
			
			my_data->m_pSprites[my_data->m_iCount] = &(poRle->oSprite);
			my_data->m_iCount++;
			pcNext += 10 + sizeof( SRLE ) + poRle->oSprite.size;
		}
		else if ( 0 == strncmp( pcNext, "PAL ", 4 ) )
		{
			struct SPAL
			{
				Uint32		iLength1;
				Uint32		iLength;
				SDL_Color	aoColors[256];
			} *poPal = (SPAL*) (pcNext+4);
			ChangeEndian32( poPal->iLength );
			
			int iNumColors = poPal->iLength>1024 ? 1024 : poPal->iLength;
			iNumColors /= 4;
			
			for (int i=0; i< iNumColors; i++)
			{
				my_data->m_aoPalette[i].r = poPal->aoColors[i].r*4;
				my_data->m_aoPalette[i].g = poPal->aoColors[i].g*4;
				my_data->m_aoPalette[i].b = poPal->aoColors[i].b*4;
				my_data->m_aoPalette[i].a = 0;
				my_data->m_aoTintedPalette[i] = my_data->m_aoPalette[i];
			}
			
			pcNext += 4 + 8 + poPal->iLength;
		}
		else
		{
			struct SUnknown
			{
				Uint32	iSize;
			} *poUnknown = (SUnknown*) (pcNext+4);
			ChangeEndian32( poUnknown->iSize );
			
			Debug::debug(Debug::error,__FUNCTION__) << "Unknown: " << pcNext << " size: " <<  poUnknown->iSize <<endl;
			
			pcNext += 4 + sizeof(SUnknown) + poUnknown->iSize;
		}
	}
	
	return my_data->m_iCount;
	
#if 0
	
	int datacount;
	
	#define READDW(I) {														\
		unsigned char data[4];														\
		fread( data, 4, 1, f );												\
		(I) = (data[0]<<24) + (data[1]<<16) + (data[2]<<8) + data[3]; }
	#define READW(I) {														\
		unsigned char data[2];														\
		fread( data, 2, 1, f );												\
		(I) = (data[0]<<8) + data[1]; }
	#define READCH(S,C) {													\
		fread( S, C, 1, f ); S[C] = 0; }
	
	fseek( f, 8, SEEK_SET );		// Skip header
	READDW( datacount );
	
	Debug::debug(Debug::error,__FUNCTION__) << "File " <<filename <<" contains entries:  " << datacount <<endl;
	if (datacount>500) datacount = 500;			// Sanity
	
	my_data->arraysize = datacount;
	my_data->sprites = new RLE_SPRITE*[ datacount ];
	
	while( (!feof(f)) && (!ferror(f)) && (datacount>0) )
	{
		char s[10];
		READCH( s, 4 );
		if ( !strcmp( s, "prop" ))				// Found a property
		{
			fseek( f, 4, SEEK_CUR );
			unsigned int propsize;
			READDW( propsize );
			fseek( f, propsize, SEEK_CUR );
		}
		else if (!strcmp( s, "RLE " ))			// Found an RLE_SPRITE
		{
			datacount--;
			
			unsigned int length, bpp, width, height, size;
			
			READDW( length );
			READDW( length );
			READW( bpp );
			READW( width );
			READW( height );
			READDW( size );
			
			RLE_SPRITE* sprite = (RLE_SPRITE*) malloc( sizeof(RLE_SPRITE) + size );
			my_data->sprites[ my_data->count ] = sprite;
			(my_data->count)++;
			sprite->w = width;
			sprite->h = height;
			sprite->color_depth = bpp;
			sprite->size = size;
			fread( sprite->dat, 1, size, f );
		}
		else if (!strcmp( s, "PAL "))			// Found a palette
		{
			datacount--;
			
			unsigned int length, pallength;
			READDW( length );
			READDW( length );
			pallength = length>1024 ? 1024 : length;
			pallength /= 4;
			
			for (unsigned int i=0; i< pallength; i++)
			{
				char c[4];
				fread( c, 4, 1, f );
				my_data->palette[i].r = c[0]*4;
				my_data->palette[i].g = c[1]*4;
				my_data->palette[i].b = c[2]*4;
				my_data->palette[i].unused = 0;
			}
			
			fseek( f, length - pallength*4, SEEK_CUR );
		}
		else									// Found something else
		{
			Debug::debug(Debug::error,__FUNCTION__) << "Unknown: " << s <<endl;
			datacount--;
		
			unsigned int length;
			READDW( length );
			READDW( length );
			fseek( f, length, SEEK_CUR );
		}
	}
	
	fclose( f );
#endif
}




int CRleSprite::Count()
{
	return my_data->m_iCount;
}


/** Worker method of CRleSprite::OffsetSprites() .*/

void OffsetRLESprite( RLE_SPRITE* spr, int offset ) // Static method
{
	if (!spr || !offset) return;
	
	signed char *s = spr->dat;
	signed char c;
	int y;
	
	for (y=0; y<spr->h; y++)
	{
		c = *s++;
		
		while (c)
		{
			// For positive c: solid pixels.
			for ( ; c>0; c-- )
			{
				*s = (*s) + offset;
				s++;
			}
			c = *s++;
		}
	}
}


/** Offsets the sprites "logical" palette values by the given offset.
This is only relevant in 8BPP mode; in other color depths this is a
no-op.

Explanation: RlePacks have an internal palette which contains up to 256
colors. These colors are always indexed from 0 up. However, if you load
two RlePacks with different palettes, the palettes will collide, and one
CRleSprite will be displayed with an incorrect palette.

To work around this, you can offset one of the sprites palette. For example,
you might load an CRleSprite with 16 colors, and another with 64 colors. You
can offset the second CRleSprite by 16 colors; the total effect is that the
two RlePacks now use 80 colors of the available 256 colors, the first using
colors 0-15, the second using colors 16-79.
*/

void CRleSprite::OffsetSprites( int a_iOffset )
{
	if ( (a_iOffset<=0) || (a_iOffset>255) || (8!=Colors::getCurrentPixelFormat()->BitsPerPixel) )
		return;

	my_data->m_iColorOffset = a_iOffset;

	int i;
	
	// Offset every RLE_SPRITE
	
	for ( i=0; i<my_data->m_iCount; ++i )
	{
		OffsetRLESprite( my_data->m_pSprites[i], a_iOffset );
	}
}


void CRleSprite::SetTint( TintEnum a_enTint )
{
	int i;

	switch( a_enTint )
	{
		case ZOMBIE_TINT:
		{
			for ( i=0; i<my_data->m_iColorCount; ++i )
			{
				my_data->m_aoTintedPalette[i].r = 0;
				my_data->m_aoTintedPalette[i].g = my_data->m_aoPalette[i].g;
				my_data->m_aoTintedPalette[i].b = 0;
			}
			break;
		}

		case GRAY_TINT:
		{
			int j;
			for ( i=0; i<my_data->m_iColorCount; ++i )
			{
				j = (my_data->m_aoPalette[i].r + my_data->m_aoPalette[i].g + my_data->m_aoPalette[i].b)/4;
				my_data->m_aoTintedPalette[i].r = j;
				my_data->m_aoTintedPalette[i].g = j;
				my_data->m_aoTintedPalette[i].b = j;
			}
			break;
		}

		case DARK_TINT:
		{
			for ( i=0; i<my_data->m_iColorCount; ++i )
			{
				my_data->m_aoTintedPalette[i].r = int(my_data->m_aoPalette[i].r) * 2 / 3;
				my_data->m_aoTintedPalette[i].g = int(my_data->m_aoPalette[i].g) * 2 / 3;
				my_data->m_aoTintedPalette[i].b = int(my_data->m_aoPalette[i].b) * 2 / 3;
			}
			break;
		}

		case INVERTED_TINT:
		{
			for ( i=0; i<my_data->m_iColorCount; ++i )
			{
				my_data->m_aoTintedPalette[i].r = 255 - my_data->m_aoPalette[i].r;
				my_data->m_aoTintedPalette[i].g = 255 - my_data->m_aoPalette[i].g;
				my_data->m_aoTintedPalette[i].b = 255 - my_data->m_aoPalette[i].b;
			}
			break;
		}

		case NO_TINT:
		default:
		{
			for ( i=0; i<my_data->m_iColorCount; ++i )
			{
				my_data->m_aoTintedPalette[i] = my_data->m_aoPalette[i];
			}
			break;
		}
		
	} // end of switch( a_enTint )

}


/** Loads the palette of the CRleSprite to the gamescreen.
This only works in 8BPP mode; in other modes the palette is always considered
to be loaded, and this is a no-operation.
*/

void CRleSprite::ApplyPalette()
{
	/*  Toto Work with 8 bit Bitmaps
	if ( 8 == Colors::getCurrentPixelFormat()->BitsPerPixel )
	{
		SDL_SetColors( gamescreen, my_data->m_aoTintedPalette, my_data->m_iColorOffset, my_data->m_iColorCount );
	}
	else
	{ */
		// Now is the time to compile m_aiRGBPalette
		for ( int i=0; i<my_data->m_iColorCount; ++i )
		{
			SDL_Color& roColor = my_data->m_aoTintedPalette[i];
			my_data->m_aiRGBPalette[i] = Colors::makeColor( roColor.r, roColor.g, roColor.b );
		}
	//}
}


/** Returns the width of a given sprite in pixels.

\param a_iIndex The index of the sprite, 0 <= a_iIndex < Count()
*/

int CRleSprite::GetWidth( int a_iIndex )
{
	if ( (a_iIndex<0) || (a_iIndex>=my_data->m_iCount) )
		return -1;

	RLE_SPRITE* poSprite = my_data->m_pSprites[a_iIndex];
	if (!poSprite)
		return -1;

	return poSprite->w;
}


/** Returns the height of a given sprite in pixels.

\param a_iIndex The index of the sprite, 0 <= a_iIndex < Count()
*/

int CRleSprite::GetHeight( int a_iIndex )
{
	if ( (a_iIndex<0) || (a_iIndex>=my_data->m_iCount) )
		return -1;

	RLE_SPRITE* poSprite = my_data->m_pSprites[a_iIndex];
	if (!poSprite)
		return -1;

	return poSprite->h;
}



#define METHODNAME				RlePack_P::draw_rle_sprite8
#define METHODNAME_FLIP			RlePack_P::draw_rle_sprite_v_flip8
#define PIXEL_PTR				unsigned char*
#define PUT_PIXEL(p,c)			(*((unsigned char *)(p)) = (c))
#define PITCH					(dst->pitch)
#include "sprite/DrawRle.h"
#undef METHODNAME
#undef METHODNAME_FLIP
#undef PIXEL_PTR
#undef PUT_PIXEL
#undef PITCH

#define METHODNAME				RlePack_P::draw_rle_sprite16
#define METHODNAME_FLIP			RlePack_P::draw_rle_sprite_v_flip16
#define PIXEL_PTR				Uint16*
#define PUT_PIXEL(p,c)			(*((PIXEL_PTR )(p)) = (m_aiRGBPalette[c]))
#define PITCH					(dst->pitch / 2)
#include "sprite/DrawRle.h"

#undef METHODNAME
#undef METHODNAME_FLIP
#undef PIXEL_PTR
#undef PUT_PIXEL
#undef PITCH

#define METHODNAME				RlePack_P::draw_rle_sprite32
#define METHODNAME_FLIP			RlePack_P::draw_rle_sprite_v_flip32
#define PIXEL_PTR				Uint32*
#define PUT_PIXEL(p,c)			(*((PIXEL_PTR )(p)) = (m_aiRGBPalette[c]))
#define PITCH					(dst->pitch / 4)
#include "sprite/DrawRle.h"

#undef METHODNAME
#undef METHODNAME_FLIP
#undef PIXEL_PTR
#undef PUT_PIXEL
#undef PITCH

#define METHODNAME				RlePack_P::draw_rle_sprite24
#define METHODNAME_FLIP			RlePack_P::draw_rle_sprite_v_flip24
#define PIXEL_PTR				Uint8*
#define PITCH					(dst->pitch)

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
 #define PUT_PIXEL(p,c) p[0] = ((m_aiRGBPalette[c]) >> 24) & 0xFF; \\
						p[1] = ((m_aiRGBPalette[c]) >> 16) & 0xFF; \\
						p[2] = ((m_aiRGBPalette[c]) >> 8) & 0xFF;
#else
 #define PUT_PIXEL(p,c)  \
        p[0] = (m_aiRGBPalette[c]) & 0xFF;  \
		p[1] = ((m_aiRGBPalette[c]) >> 8) & 0xFF; \
		p[2] = ((m_aiRGBPalette[c]) >> 16) & 0xFF;                        \

#endif
#include "sprite/DrawRle.h"

void CRleSprite::Draw( CBitmap* dst,int a_iIndex, int a_iX, int a_iY, bool a_bFlipped )
{
	if ( (a_iIndex<0) || (a_iIndex>=my_data->m_iCount) )
		return;
	
	RLE_SPRITE* poSprite = my_data->m_pSprites[a_iIndex];
	if (!poSprite)
		return;
	
	//CSurfaceLocker oLock;
	int bitPP=dst->getBitmap()->format->BitsPerPixel;
	//int desktopBpp = Colors::getCurrentPixelFormat()->BitsPerPixel;
	
	if ( a_bFlipped )
	{
		switch (bitPP)
		{
		case 8: 
			my_data->draw_rle_sprite_v_flip8(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		case 15: 
		case 16:
			my_data->draw_rle_sprite_v_flip16(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		case 24:
			my_data->draw_rle_sprite_v_flip24(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		case 32:
			my_data->draw_rle_sprite_v_flip32(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		}
	}
	else
	{
		switch (bitPP)
		{
		case 8:
			my_data->draw_rle_sprite8(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		case 15: 
		case 16:
			my_data->draw_rle_sprite16(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		case 24:
			my_data->draw_rle_sprite24(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		case 32:
			my_data->draw_rle_sprite32(dst->getBitmap(), poSprite, a_iX, a_iY ); break;
		}
	}
}


CBitmap* CRleSprite::CreateBitmap( int a_iIndex, bool a_bFlipped )
{
	if ( (a_iIndex<0) || (a_iIndex>=my_data->m_iCount) )
		return NULL;
	
	RLE_SPRITE* poSprite = my_data->m_pSprites[a_iIndex];
	if (!poSprite)
		return NULL;
	CBitmap * poBitmap = new CBitmap (poSprite->w, poSprite->h);
	
	//SDL_Surface* poSurface = SDL_CreateRGBSurface( SDL_SWSURFACE, poSprite->w, poSprite->h, Colors::getCurrentPixelFormat()->BitsPerPixel,
	//	Colors::getCurrentPixelFormat()->Rmask, Colors::getCurrentPixelFormat()->Gmask, Colors::getCurrentPixelFormat()->Bmask, Colors::getCurrentPixelFormat()->Amask );

	if ( NULL == poBitmap )
	{
		return NULL;
	}
	/*  Toto Work with 8 bit Bitmaps
	if ( Colors::getCurrentPixelFormat()->BitsPerPixel <= 8 )
	{
		SDL_SetColors( poSurface, Colors::getCurrentPixelFormat()->palette->colors, 0, Colors::getCurrentPixelFormat()->palette->ncolors );
	}
	*/
	poBitmap->clear();
	//SDL_FillRect( poSurface, NULL, 0 );// C_LIGHTGREEN );
	poBitmap->applyTrans(0);
	//SDL_SetColorKey( poSurface, SDL_TRUE, 0 ); //C_LIGHTGREEN );
		
	Draw(poBitmap, a_iIndex, 0, 0, a_bFlipped );  //Draw to Gamescreen
	

	return poBitmap;
}

} //end SGF
