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


 *  Contributions:
 *  This software was based on Sffextract by Christophe.
 */

#ifndef _S_G_F_sff_sprite_h
#define _S_G_F_sff_sprite_h

#include <string>
#include <fstream>
#include <iostream>
#include "defs.h"
#include "../SGF_Config.h"

#ifndef INLINE
#define INLINE __inline
#endif
using namespace std;

class CMugenSprite;
namespace SGF {

typedef map< unsigned int, PCXDATA*> GroupPCXDATA;
typedef map< unsigned int, GroupPCXDATA> PCXDATAMap;
/**
 * \class CMugenSprite
 *
 * \ingroup SGF_Sprite
 *
 * \brief Manipulador de Arquivos do typo SFF que contém sprites do Mugen
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CSFFManager{
    public:
	CSFFManager(const char * filename,SFFBEHAVIOR *behavior);
	CSFFManager();
	~CSFFManager();
	/* The functions corresponding to the variables above */
	INLINE void set_display_header( bool value ) { my_display_header = value; }
	INLINE void set_display_options( bool value ) { my_display_options = value; }
	INLINE void set_display_contents( bool value ) { my_display_contents = value; }
	INLINE void set_display_outfile( bool value ) { my_display_outfile = value; }
	INLINE void set_force( bool value ) { my_force = value; }
	INLINE void set_create_pcx( bool value ) { my_create_pcx = value; }
	INLINE void set_debug( bool value ) { my_debug = value; }
	INLINE void set_subdirectory( bool value ) { my_subdirectory = value; }
	INLINE void set_absolute_paths( bool value ) { my_absolute_paths = value; }
	/* new , by [E] 13/08/2003 */
	INLINE void set_hex_output( bool value ) { my_hex_output = value; }
	/* ends, by [E] 13/08/2003 */
	INLINE void set_short_output( bool value ) { my_short_output = value; }
	INLINE void set_invert_shared( bool value ) { my_invert_shared = value; }
	INLINE void set_linux_character( bool value ) { my_linux_character = value; }
	/*void set_output_dir( char * dir ) { strcpy( output_dir, dir ); }*/
	INLINE void set_act_file( string  act ) { my_act_path=act; }
	INLINE void set_use_act( bool value ) { my_use_act = value; }
	INLINE void set_mask(bool mask) { this->mask=mask; }
	/*void set_no_overwrite( char value ) { no_overwrite = value; }*/

	int extract_header();
	int extract();
	int saveImage(unsigned int imageNumber, unsigned int group);
	int saveImageList();
	int createPCX( unsigned long *offset, unsigned long *imglist, unsigned char *dupcheck,unsigned long reallength,char dirprefix[_MAX_DRIVE + _MAX_DIR - 13],char *palselect, signed char is_8bitpal,signed char is_linked,unsigned char palsaveD[768],unsigned char palsave1[768],char found_1st, unsigned long i,char * pcxdata, char pcxname[FILENAME_MAX],char linked_name[FILENAME_MAX] ,FILE *pcxfile, FILE *linked_pcx, SFF_HEADER header,  SFF_SUBHEADER sub);
	//void getMugenSprites(Mugen::SpriteMap &sprites);
protected:
	void setBehavior(SFFBEHAVIOR *behavior);
    /* destroy allocated things */
    void cleanup();
    int	 treatFilesystem();
	int  treatACT();
	int  treatLinuxChar();
	//!lista ligada com todas as imagens do arquivo lido
	PCXDATAMap PCXList;
	//TODO Tirar a spritelista daqui e colocála no CResourceManager
	//Mugen::SpriteMap  SpriteList;
	private:
	int error;
	bool mask;  //mask to use with CMugenSprite
/* ------------------------------------------------------------------------- */
/* Variables definition */

	char _my_dir_prefix[_MAX_DRIVE + _MAX_DIR - 13];

	/* Some variables that control the extractor's behaviour */
	bool my_force;
	bool my_create_pcx;
	bool my_display_header;
	bool my_display_options;
	bool my_display_contents;
	bool my_display_outfile; /* Little note: This refers to Sprmaker's
					output SFF filename, not any of Sffextract's output files. */
	bool my_debug;
	bool my_subdirectory;
	bool my_absolute_paths;
	bool my_use_act;
	/* new , by [E] 13/08/2003 */
	bool my_hex_output;
	/* ends, by [E] 13/08/2003 */
	bool my_short_output;
	bool my_invert_shared;
	bool my_linux_character;         /* Indicator of whether to treat the SFF as being
								 for a character in-game in versions of Mugen
								 after 2001.04.14. */
	/* Delimiter characters for strtok calls: */
	char *seps;
	FILE * _my_sff_file;
	const char * _my_file;
	SFF_HEADER my_header;
	unsigned long my_sff_length; /* Length of SFF file. */
	unsigned char *palsaveD; /* PCX 256-color palette (default one to use) */
	unsigned char *palsave1; /* PCX 256-color palette of 1st image (Linux
											   mode) or of specified palette file */
	unsigned long *offset; /* offset table for reading images data */
	unsigned char *dupcheck; /* table for indicating duplicate group+image numbers */
	unsigned long *imglist; /* list of group+image numbers */
	char *palselect;

	string my_act_path;



    };
} //end SGF
#endif
