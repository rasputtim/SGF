/*
 * defs.h
 * ======
 *
 * This file holds common definitions.
 *
 * Copyright (C) 2010, Rasputtim
 *
 *  This file is part of Sffextractor.
 *
 *  Sffextractor is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *  Contributions:
 *  This software was based on Sffextract by Christophe.
 */


#ifndef _S_G_F_SPRITE_DEFS_H
#define _S_G_F_SPRITE_DEFS_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "../SGF_Config.h"
#include "../graphics/SGF_Color.h"
#include "../util/SGF_Pointer.h"

#ifndef BYTE
typedef unsigned char       BYTE;
#endif
#define int16 short int
#define FALSE 0
#define TRUE  1

//define the ImageList types
#define IMP1 0xc1
#define IMP2 0xc2
#define IMP3 0xc3
#define IMP4 0xc4
#define IMMENU 0xc5
#define IMSTAGE 0xc6
//Define Action FLIPFLAGS
#define HFLIPFLAG   0x11
#define VFLIPFLAG   0x12
#define HVFLIPFLAG  0x13
#if defined(__MSDOS) || defined(_WIN32)
#define DIR_SEPARATOR '\\'
#elif defined(_MAC)
/* Not at all sure about this: */
#define DIR_SEPARATOR ':'
#else
#define DIR_SEPARATOR '/'
#endif

#if !defined(_MSC_VER) && !defined(__BORLANDC__)
 /* Maximum filename length */
 /* Not very nice code, but it will do for now... */
 /* These values should probably be decreased when compiling for old Microsoft
    systems lacking long filename support.
    These values are unnecessarily limiting for Linux, but let's keep things
    consistent between systems as much as possible. */
  #ifndef _MAX_DRIVE
  #define _MAX_DRIVE 3
  #endif

  #ifndef _MAX_DIR
  #define _MAX_DIR 256
  #endif

  #ifndef _MAX_FNAME
  #define _MAX_FNAME 256
  #endif

  #ifndef _MAX_EXT
  #define _MAX_EXT 256
  #endif
#endif


#define SPRPALTYPE_INDIV  0
#define SPRPALTYPE_SHARED 1
#define SFF_SIGNATURE "ElecbyteSpr"


using namespace std;
namespace SGF {

class CMugenSprite;

/* -------------------------------------------------------------------------- */
/* Types'definitions */
//typedef unsigned char BYTE;

/* HEADER */
struct SFF_HEADER{
	SFF_HEADER():
	extracted(false){}
    char signature [12];      /* "ElecbyteSpr\0" signature */
    BYTE verhi;
    BYTE verlo;
    BYTE verlo2;
    BYTE verlo3;
    unsigned long nb_groups;  /* Number of groups */
    unsigned long nb_imgs;    /* Number of images */
    unsigned long sub_offset; /* File offset where first subfile is located */
    unsigned long sub_size;   /* Size of subheader in bytes */
    char palette_type;        /* 1 = SPRPALTPYE_SHARED or
                                 0 = SPRPALTYPE_INDIV */
    char blank [3];           /* Blank, set to zero */
    char comments [476];      /* Blank, can be used for comments */
	bool extracted;
};

namespace Mugen{
	using namespace ::SGF;
/* Makes the use of the sprite maps easier */
typedef map< unsigned int, Util::CReferenceCount<CMugenSprite> > GroupMap;
typedef map< unsigned int, GroupMap> SpriteMap;
}
typedef struct {
bool force;
bool create_pcx;
bool display_header;
bool display_options;
bool display_contents;
bool display_outfile; /* Little note: This refers to Sprmaker's
                output SFF filename, not any of Sffextract's output files. */
bool debug;
bool subdirectory;
bool absolute_paths;
bool use_act;
/* new , by [E] 13/08/2003 */
bool hex_output;
/* ends, by [E] 13/08/2003 */
bool short_output;
bool invert_shared;
bool linux_character; /* Indicator of whether to treat the SFF as being
                             for a character in-game in versions of Mugen
                             after 2001.04.14.  */
FILE * of;
FILE * ef;
/*char output_dir[_MAX_DRIVE + _MAX_DIR] = "";*/
string act_path;
/*char no_overwrite = FALSE;*/
} SFFBEHAVIOR;

/* SUBFILEHEADER */
typedef struct {
    unsigned long next_offset; /* File offset where next subfile in the "linked
                                  list" is located. Null if last subfile. */
    unsigned long length;      /* Subfile length (not including header).
                                  Length is zero if it is a linked sprite. */
    int16 xcoord;        /* Image axis X coordinate */
    int16 ycoord;        /* Image axis Y coordinate */
    unsigned short group;         /* Group number */
    unsigned short img;           /* Image number (in the group) */
    unsigned short prev; /* Index of previous copy of sprite (linked
                            sprites only) */
    BYTE same_pal;       /* True if palette is same as previous images. */
    char comments [13];  /* Blank, can be used for comments.
                            !! formats.txt says it's 14 bytes but it is
                            13 bytes in order to have a 32-bytes long
                            subheader !! */
} SFF_SUBHEADER;


/* PCX HEADER */
typedef struct {
    unsigned char manufacturer; /* Constant Flag, 10 = ZSoft .pcx */
    unsigned char version;      /* Version information */
    unsigned char encoding;     /* 1 = .PCX run length encoding */
    unsigned char BitsPerPixel; /* Number of bits to represent a pixel */
    short Xmin;                 /* Image Dimensions */
    short Ymin;
    short Xmax;
    short Ymax;
    unsigned short HDpi;         /* Horizontal Resolution of image in DPI */
    unsigned short VDpi;         /* Vertical Resolution of image in DPI */
    unsigned char colormap[48];  /* Color palette setting */
    unsigned char reserved;      /* Should be set to 0. */
    unsigned char NPlanes;       /* Number of color planes */
    unsigned short BytesPerLine; /* Number of bytes to allocate for a scanline plane. */
    unsigned short PaletteInfo;  /* How to interpret palette: 1 = Color/BW,
                                    2 = Grayscale (ignored in PB IV/ IV +) */
    unsigned short HscreenSize;  /* Horizontal screen size in pixels. */
    unsigned short VscreenSize;  /* Vertical screen size in pixels. */
    char filler[54];             /* Blank to fill out 128 byte header. */
} PCX_HEADER;
/* Source: ZSoft Corporation's PCX File Format Technical Reference Manual, Revision 5. */


/* PCX IMAGE */
struct PCXDATA{
	PCXDATA():
	Lenght(0),
	ImageNumber(0),
	GroupNumber(0),
	pImageData(NULL),
	x(0),
	y(0),
	bIsLinked(false),
	bPalletSame(false),
    RealLenght(0),
	loaded(false)
	{
	memset (&Name,0,FILENAME_MAX);
	memset (&comments,0,13);
	memset (&PcxHeader,0,sizeof(PcxHeader));
	}
	PCXDATA(const PCXDATA &copy):
		SGFCpConstr(Lenght)
		SGFCpConstr(ImageNumber)
		SGFCpConstr(GroupNumber)
		SGFCpConstr(pImageData)
		SGFCpConstr(x)
		SGFCpConstr(y)
		SGFCpConstr(bIsLinked)
		SGFCpConstr(bPalletSame)
		SGFCpConstr(RealLenght)
		SGFCpConstrLast(loaded){

		memcpy(Name,copy.Name,FILENAME_MAX);
		memcpy(comments,copy.comments,13);
		memcpy(&ColorPallet,&copy.ColorPallet,sizeof(ColorPallet));
		memcpy(&PcxHeader,&copy.PcxHeader,sizeof(PcxHeader));
		}
	const PCXDATA & operator=(const PCXDATA &copy){
				if (&copy==this) return *this;
				SGFCpField(Lenght)
				SGFCpField(ImageNumber)
				SGFCpField(GroupNumber)
				SGFCpField(pImageData)
				SGFCpField(x)
				SGFCpField(y)
				SGFCpField(bIsLinked)
				SGFCpField(bPalletSame)
				SGFCpField(RealLenght)
				SGFCpField(loaded)
				memcpy(Name,copy.Name,FILENAME_MAX);
				memcpy(comments,copy.comments,13);
				memcpy(&ColorPallet,&copy.ColorPallet,sizeof(ColorPallet));
				memcpy(&PcxHeader,&copy.PcxHeader,sizeof(PcxHeader));
				return *this;
			};
	~PCXDATA(){
	if(pImageData!=NULL){
		delete pImageData;
		pImageData=NULL;
	}

	}
	void setLoaded() { loaded=true;}
	bool isLoaded() { return loaded;}
	char Name[FILENAME_MAX];
	int Lenght;
	int ImageNumber;
	int GroupNumber;
	unsigned char *pImageData;
	short x;
	short y;
	bool bIsLinked;
	bool bPalletSame;
    int RealLenght;
	char comments[13];
	Colors::ColorDefinition ColorPallet[256];
	PCX_HEADER PcxHeader;
	bool loaded;  //! the struct is loaded weith a pcx image
};
//Linked list Struct
struct PCXLinkedList
{
	PCXDATA pcxdata;
	PCXLinkedList *Sucessor;
	PCXLinkedList *Antecessor;
};

} //nd SGF
#endif /* __DEFS_H */
