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


#if defined(_MSC_VER)
#include <direct.h>
#elif defined(__BORLANDC__)  /* DS modification 1 */
#include <dir.h>
#else
#include <unistd.h>  /* ifdef __GCC__, __MWERKS__, maybe others */
#include <stdio.h>
#include <sys/stat.h>
#endif
#if defined(__MWERKS__)
#include <stat.h>
#include <extras.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sprite/SGF_SffManager.h"
#include "sprite/SGF_MugenSprite.h"
#include "util/SGF_Debug.h"

namespace SGF {


CSFFManager::CSFFManager():
error(0),
mask(false),
my_force(FALSE),
my_create_pcx(FALSE),
my_display_header(FALSE),
my_display_options(TRUE),
my_display_contents(FALSE),
my_display_outfile(FALSE),
my_debug(FALSE),
my_subdirectory(FALSE),
my_absolute_paths(FALSE),
my_use_act(FALSE),
my_hex_output(FALSE),
my_short_output(FALSE),
my_invert_shared(FALSE),
my_linux_character(FALSE),
seps((char *) "\a\b\n\v\f\r\x11\x12\x13\x14\x1a\x1b\x7f"),
_my_sff_file(NULL),
_my_file(""),
//my_header(new SFF_HEADER),
my_sff_length(0),
palsaveD((unsigned char*) calloc (768,sizeof(unsigned char))),
palsave1((unsigned char*) calloc (768,sizeof(unsigned char))),
offset(NULL),
dupcheck(NULL),
imglist(NULL),
palselect(NULL),
my_act_path("")
{
}


/** @fn CSFFManager::CSFFManager(char * filename,BEHAVIOR *behavior)
@brief Construtor da Classe CSFFManager. cria um objeto a partir do nome de um arquivo SFF
@param const char * filename: nome do arquivo contendo as imagens
@param SFFBEHAVIOR *behavior: estrutura contendo uma série de variáveis que controlam o comportamento do objeto criado. Se for NULL utiliza o comportamento padrão
@return construtores não retornam
@warning  se ocorrer algum erro, seta a variaval error
**/
CSFFManager::CSFFManager(const char * filename,SFFBEHAVIOR *behavior):
error(0),
mask(false),
my_force(FALSE),
my_create_pcx(FALSE),
my_display_header(FALSE),
my_display_options(TRUE),
my_display_contents(FALSE),
my_display_outfile(FALSE),
my_debug(FALSE),
my_subdirectory(FALSE),
my_absolute_paths(FALSE),
my_use_act(FALSE),
my_hex_output(FALSE),
my_short_output(FALSE),
my_invert_shared(FALSE),
my_linux_character(FALSE),
seps((char *) "\a\b\n\v\f\r\x11\x12\x13\x14\x1a\x1b\x7f"),
_my_sff_file(NULL),
_my_file(filename),
//my_header(new SFF_HEADER),
my_sff_length(0),
palsaveD(NULL),
palsave1(NULL),
offset(NULL),
dupcheck(NULL),
imglist(NULL),
palselect(NULL),
my_act_path("")

{
my_act_path="";

	if(behavior!=NULL)
		setBehavior(behavior);

	palsaveD=(unsigned char*) calloc (768,sizeof(unsigned char));
	palsave1=(unsigned char*) calloc (768,sizeof(unsigned char));

	if (palsave1 ==NULL || palsaveD == NULL) {
		Debug::debug(Debug::error,__FUNCTION__) << "Error while allocating Memory for PalsaveD and palsave1. "  <<endl;
        error=1;

	}

	_my_sff_file = fopen( filename, "rb" );
    if( !_my_sff_file ) {
		Debug::debug(Debug::error,__FUNCTION__) << "File does not exist: " << filename <<endl;
        error= 1;
    }
    fseek( _my_sff_file, 0, SEEK_END );
    my_sff_length = ftell( _my_sff_file );
    fseek( _my_sff_file, 0, SEEK_SET );
	if( extract_header() ) { //preenche _myheader antes de alocar memórias
 		Debug::debug(Debug::error,__FUNCTION__) << "Error while extracting header. Aborting. "  <<endl;
        error=1;
	}
	
	/* Creates offset table */
    offset = (unsigned long *) malloc( (my_header.nb_imgs+1)*sizeof(unsigned long) );
    if( offset == NULL){
       Debug::debug(Debug::error,__FUNCTION__) << "Error: Can't allocate memory for offset table. "  <<endl;
       error=1;
	}

    // Create table for checking whether linked images are linked to duplicately numbered images.
	// Cria uma tabela para checar se a imagem lincada está ligada a imagens numeriacamente duplicadas

    dupcheck = (unsigned char *) calloc( (my_header.nb_imgs+1), sizeof(char) );
    if( dupcheck == NULL){
        Debug::debug(Debug::error,__FUNCTION__) << "Error: Can't allocate memory for duplicity table. "  <<endl;
        free( offset );
        error=1;
	}

    /* Create table for concatenated group+image numbers. */
    imglist = (unsigned long *) malloc( (my_header.nb_imgs+1)*sizeof(unsigned long) );
    if( imglist == NULL){
        Debug::debug(Debug::error,__FUNCTION__) << "Error: Can't allocate memory for image number table. "  <<endl;
        free( offset );
        free( dupcheck );
        error=1;
	}

    /* Create table for new-Mugen mode palette selection. */
    palselect = (char *) calloc( (my_header.nb_imgs+1), sizeof(char) );
    if( palselect == NULL){
        Debug::debug(Debug::error,__FUNCTION__) << "Error: Can't allocate memory for palette selection table. "  <<endl;
        free( offset );
        free( dupcheck );
        free( imglist );
       error=1;
	}

}
CSFFManager::~CSFFManager() {
	Debug::debug(Debug::font,__FUNCTION__) << "Freeing everything"<<endl;

	if (seps) delete seps;
	//if (my_header) delete my_header;
	if (palsaveD) free (palsaveD);
	if (palsave1) free (palsave1);
	if (offset) free ( offset );
    if (dupcheck) free ( dupcheck );
    if (imglist) free ( imglist );
    if (palselect) free ( palselect );
	if (_my_sff_file) fclose(_my_sff_file);

}
/** @fn CSFFManager::setBehavior(BEHAVIOR *behavior)
@brief ajusta  as variáveis de comportamento da classe
@param BEHAVIOR *behavior: estrutura contendo uma série de variáveis que controlam o comportamento do objeto criado. Se for NULL utiliza o comportamento padrão
@return nada
@warning
**/
void CSFFManager::setBehavior(SFFBEHAVIOR *behavior){

	set_force(behavior->force);
	set_create_pcx(behavior->create_pcx);
	set_display_header(behavior->display_header);
	set_display_options(behavior->display_options);
	set_display_contents(behavior->display_contents);
	set_display_outfile(behavior->display_outfile);
	set_debug(behavior->debug);
	set_subdirectory(behavior->subdirectory);
	set_absolute_paths(behavior->absolute_paths);
	set_hex_output(behavior->hex_output);
	set_short_output(behavior->short_output);
	set_invert_shared(behavior->invert_shared);
	set_linux_character(behavior->linux_character);
	set_use_act(behavior->use_act);


}

/** @fn CSFFManager::extract_header()
@brief extrai o cabeçalho do arquivo ssf para a extrutura header
@return 1 se falhar e 0 se tiver sucesso
@warning  se ocorrer algum erro, seta a variaval error
**/
int CSFFManager::extract_header() {
    if (error)
        return 1;
    FILE *sff_file=_my_sff_file;
	//SFF_HEADER *header=my_header;
	char * token;
    char comment[477] = "\0"; /* Winane added this because the string needs to
                        be null-terminated, and direct access to the header
                        doesn't guarantee a null character. But perhaps there's
                        a better solution.*/

    //! Lê as informações do cabeçalho
    if( !fread( &my_header, sizeof(SFF_HEADER), 1, sff_file ) ){
		Debug::debug(Debug::error,__FUNCTION__) << "Error: Couldn't read complete header. "  <<endl;
        error = true;
        return 1;
    }

    //! checa se a assinatura do arquivo está certa
    if( strcmp( my_header.signature, SFF_SIGNATURE ) ) {
        if( !my_force ) {
            Debug::debug(Debug::error,__FUNCTION__) << "Error: Specified file is not a SFF file."  <<endl;
            fclose(sff_file);
            error = true;
			return 1;
        }
        Debug::debug(Debug::error,__FUNCTION__) << "Error: Specified file is not a SFF file.  \nAttempting to go on with extraction anyway."  <<endl;
      }

    //! mostra o cabeçalho
    if( my_display_header ) {
    Debug::debug(Debug::resources,__FUNCTION__) << my_header.nb_imgs <<" images" << endl;
        Debug::debug(Debug::resources,__FUNCTION__) << my_header.signature<< " , " << my_header.verhi<< " , " << my_header.verlo<< " , " <<  my_header.verlo2 << " , " <<my_header.verlo3 <<endl;
        Debug::debug(Debug::resources,__FUNCTION__) << my_header.nb_groups << "li groups" <<endl;
		Debug::debug(Debug::resources,__FUNCTION__) << my_header.nb_imgs << "Images" <<endl;



    strncpy(comment, my_header.comments, 476);
    token = strtok( comment, seps );
    if(token != NULL) Debug::debug(Debug::error,__FUNCTION__) <<token <<endl;
    while( (token = strtok(NULL, seps)) != NULL ){
		Debug::debug(Debug::resources,__FUNCTION__) << token << endl;

        }
    }

    if( !my_header.nb_groups || (my_header.nb_groups > 65536) || (my_header.nb_groups > my_header.nb_imgs) )
		Debug::debug(Debug::error,__FUNCTION__) << "Warning: Invalid number of groups specified in header. Ignoring." << endl;
                   /* Both M.C.M. and Z-CharCAD are frequently guilty of causing this.
                      Doesn't really affect anything, though. */

    if( !my_header.nb_imgs || my_header.nb_imgs > 134217683){ /* 2147483647 is impossible */
        Debug::debug(Debug::resources,__FUNCTION__) << "Error: Invalid number of images specified in header." << endl;
        error = true;
		return 1;
    }

    if( my_header.sub_size !=32 )

		Debug::debug(Debug::resources,__FUNCTION__) << "Warning: Nonstandard subheader size specified in header. Ignoring." << endl;

         /* It's probably just M.C.M.'s fault.  Mugen ignores it, so we'll just ignore it too.*/


    if( (my_header.palette_type != SPRPALTYPE_INDIV) && (my_header.palette_type != SPRPALTYPE_SHARED) ){

		Debug::debug(Debug::resources,__FUNCTION__) << "Warning: Unknown palette type: "<< my_header.palette_type <<endl;
		Debug::debug(Debug::resources,__FUNCTION__) << "Treating as if individual type. "<< endl;

    }

    /* Display palette option */
    if( my_display_options ) {
        if( my_header.palette_type == my_invert_shared )
            Debug::debug(Debug::resources,__FUNCTION__) << " \n; Options\n#\n; Palette\n1\n; Individual palette\n1\n "<< endl;
		else if( my_header.palette_type == !my_invert_shared )
            Debug::debug(Debug::resources,__FUNCTION__) << ";\n; Options\n#\n; Palette\n1\n; Shared palette\n2\n"<< endl;
		else if( my_force )
            Debug::debug(Debug::resources,__FUNCTION__) << ";\n; Options\n; Palette\n; (Palette type had originally been specified as unknown type %d.)\n"<<  my_header.palette_type << endl;

        if( my_invert_shared )
            Debug::debug(Debug::resources,__FUNCTION__) << "; (Palette type reversed from original.)\n"<<  endl;

		Debug::debug(Debug::resources,__FUNCTION__) << " End of options "<< endl;
		Debug::debug(Debug::resources,__FUNCTION__) << "------------------------------- "<< endl;

    }
	my_header.extracted = true;
    return 0;
}

/** @fn CSFFManager::extract()
@brief Extrai as imagens PCX do arquivo SFF de acordo com o comportamento definido na construção do objeto.
@return 1 se falhar e 0 se tiver sucesso
@warning
**/
int CSFFManager::extract() {
    if (error)
        return 1;
	//const char * filename = _my_file;
    FILE *sff_file;//, *act_file;
    FILE *pcxfile, *linked_pcx;
    //SFF_HEADER header=my_header;
	if (!my_header.extracted) {
		Debug::debug(Debug::resources,__FUNCTION__) << "Error: Header not extracted." << endl;
        return 1;
		
	}
    SFF_SUBHEADER sub, sub2;
    PCX_HEADER pcxhead; /* Used by both the -a option code and by the PCX
                           extraction code. */
    char *token = NULL; /* For strtok function. */
    unsigned char *pcxdata = NULL;
	unsigned char *pcxlistdata = NULL;
    char comment[14] = "\0"; /* Winane added this because the string needs to
                        be null-terminated, and direct access to the subheader
                        doesn't guarantee a null character. But perhaps there's
                        a better solution.*/
    char pcxname[FILENAME_MAX] = "\0";
    char linked_name[FILENAME_MAX] = "\0";


    unsigned long i, j; /* "For" loop indices. */
    unsigned long imgnum; /* For storing group+image number. */
    unsigned long reallength; /* Because sub.length is unreliable. -Winane */
    signed char is_8bitpal;
    signed char is_linked;
    char found_1st = 0; /* Indicator of whether we've found a 768-byte palette yet. */
    sff_file = _my_sff_file;
    treatACT();
    treatFilesystem();

    char dirprefix[_MAX_DRIVE + _MAX_DIR - 13] ="\0";
	strcpy ( dirprefix,_my_dir_prefix );

    // o cabeçalho já foi extraído pelo construtor da classe
    /* 1 = SPRPALTPYE_SHARED ou 0 = SPRPALTYPE_INDIV */
    if(my_header.palette_type && my_header.palette_type != 1 ) my_header.palette_type = 0;

    /* Displays output SFF file, same name as input SFF file */
    if( my_display_outfile ) {
    //fprintf( of, "; Output file\n%s%s.sff\n", dirprefix, fname );
    }

    /* Seeks on first subheader */
    if( my_header.sub_offset < 512 || my_header.sub_offset > 2147482717 ){
        if( !my_force ){
            Debug::debug(Debug::resources,__FUNCTION__) << "Error: Header specifies invalid initial offset. Aborting." << endl;
            return 1;
        }
        Debug::debug(Debug::resources,__FUNCTION__) << "Error: Header specifies invalid initial offset.\nUsing default offset instead." << endl;
        sub.next_offset = 512;
    }
    else sub.next_offset = my_header.sub_offset;
	/* sub.next_offset=> File offset where next subfile in the "linked
                                  list" is located. Null if last subfile. */

	// Preenche as tabelas de offset e palete para a condição linux_character
	if( my_linux_character ){

      /* Values in the final palselect table have these meanings:
         0 = keep own palette
         1 = use previous palette
         2 = use first palette or specified ACT file
      */

      for( i = 0 ; i < my_header.nb_imgs ; i++ ) {

        /* get subfile header */
		// Le os Subheaders e preenche a tabela de offsets
        offset[i] = sub.next_offset;
        if( sub.next_offset > my_sff_length ) break;
        fseek( sff_file, sub.next_offset, SEEK_SET );
        if( !fread( &sub, sizeof(SFF_SUBHEADER), 1, sff_file ) ) break;

		// Le os Subheaders e preenche a tabela de PALETTES
        if( sub.same_pal ){
            if( i > 0 && palselect[i-1] == 2 ) palselect[i] = 2;
            else palselect[i] = 1;
        }

        if( (sub.group == 0 || sub.group == 9000) && sub.img == 0 ){
            if( sub.same_pal ){
                for( j = i; j > 0 && palselect[j] == 1; j-- ){
                    palselect[j] = 2;
                    if( palselect[j-1] == 0 ) palselect[j-1] = 2;
                }
            }
            else palselect[i] = 2;
        }


        if( sub.next_offset == 0 ){ /* Just in case any SFFs actually conform to formats.txt. */
          break;
        }
        else if( sub.next_offset < (offset[i]+32) || sub.next_offset > 2147483615 ){
          break;
        }
      }

      /* Seek back to first subheader */
      if( my_header.sub_offset < 512 || my_header.sub_offset > 2147482717 ){
          sub.next_offset = 512;
      }
      else sub.next_offset = my_header.sub_offset;

	}  // END lINUX CHARACTER






    /* Read and display file contents, except image data which is saved into a
       file */
	//executa este for para cada uma das imagens PCX
    for( i = 0 ; i < my_header.nb_imgs ; i++ ) {
		pcxdata = NULL;
		pcxlistdata = NULL;

        // será deletada através da deleção do CMUgenSprite???
		PCXDATA *tempPCXDATA = new PCXDATA;
		//vector<PCXDATA*> PCXVector;
		if (tempPCXDATA==NULL) {
			//mensagem de falta de memoria
			return 1;
		}
		/* get subfile header */
        offset[i] = sub.next_offset;
        if( sub.next_offset > my_sff_length ){
            Debug::debug(Debug::resources,__FUNCTION__) <<  "Error: Offset of image "<< i<<" is beyond the end of the file. SFF file appears to be truncated. Aborting."<< endl;
			return 1;
        }
		// coloca o arquivo no inicio da sub file (dados da imagem PCX)
        fseek( sff_file, sub.next_offset, SEEK_SET );
		// Lê o cabeçalho sff da imagem
        if( !fread( &sub, sizeof(SFF_SUBHEADER), 1, sff_file ) ){
            Debug::debug(Debug::resources,__FUNCTION__) <<  "Error: SFF file seems to be truncated. Aborting."<< endl;
			return 1;
        }
		//preenche os campos image num e groupnum da lista

		tempPCXDATA->GroupNumber=sub.group;
		tempPCXDATA->ImageNumber=sub.img;
		tempPCXDATA->bPalletSame=sub.same_pal;
		tempPCXDATA->x=sub.xcoord;
		tempPCXDATA->y=sub.ycoord;
		memcpy(tempPCXDATA->comments,sub.comments,sizeof(sub.comments));

		// Determina o nome da imagem
		// %s = String of characters
		// *X = Unsigned hexadecimal integer (capital letters)
		// *  = The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted
        // %0 = Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier).
		/* modified to allow hexadecimal output, by [E] 13/08/2003 */
        if( my_hex_output )
            std::sprintf( pcxname, "%s%0*X%0*X.pcx", dirprefix, 4, sub.group, 4, sub.img );
        /* (and to allow selection of decimal output width, by Winane 16/08/2003) */
        else if( my_short_output )
            std::sprintf( pcxname, "%s%0*d%0*d.pcx", dirprefix, 4, sub.group, 4, sub.img );
        else
            std::sprintf( pcxname, "%s%0*d%0*d.pcx", dirprefix, 5, sub.group, 5, sub.img );
		strcpy(tempPCXDATA->Name,pcxname);
		//strcpy(tempPCX->pcxdata.Name,pcxname);
		/* ends, by [E] 13/08/2003 */
		// Determina o tamanho da subfile
        /* This should be a more reliable way to determine the length of the PCX data. -Winane */
        reallength = sub.next_offset-offset[i]-32;
       /* This might often not be sufficient, but is it necessary?
           Actual SFFs seem to disagree with formats.txt. -Winane */
        //determina o tamanho para o últimko subfile
		if( sub.next_offset == 0 ) {
            if( sub.same_pal ) reallength = sub.length-768;
            else reallength = sub.length;
        }
        tempPCXDATA->RealLenght=reallength;


        /* Check to see if previous image had same group + image number. */
        /* This part is nice and simple, but makes the complexity of the program O(n^2).
           We'd best implement a better algorithm in a future version,
           in case any SFFs have very large numbers of images. */

        imgnum = sub.group;
        imgnum = ( imgnum << 16 ) + sub.img;
        imglist[i] = imgnum;

        for( j = 0; j < i; j++ ){
            if( imglist[j] == imgnum ){
                if( dupcheck[i] < 255 ) ++dupcheck[i];
            }
        }

        if( dupcheck[i] ){
			// determina o nome do arquivo
            std::sprintf( pcxname, "%sx%05lu.pcx", dirprefix, i );
			strcpy(tempPCXDATA->Name,pcxname);
            if( !my_create_pcx ){
                if( sub.group == 9000 && (sub.img == 0 || sub.img == 1) )
					Debug::debug(Debug::resources,__FUNCTION__) << "Warning: "  ;
                else Debug::debug(Debug::resources,__FUNCTION__) << "Notice: " ;
                Debug::debug(Debug::resources,__FUNCTION__) << " Extra image: " << sub.group<< " , "<< sub.img << " Named as: " <<pcxname+strlen(dirprefix) <<endl;
            }
        }





        if( sub.length == 0 ){  // a imagem é linkada
          is_linked = 1;
		  tempPCXDATA->bIsLinked=true;
		  //tempPCX->pcxdata.bIsLinked=true;
          if( sub.prev >= i ){
            if( !my_force ){
                Debug::debug(Debug::error,__FUNCTION__) <<  "Error in image "<< i<<" Invalid linked sprite index. Aborting"<< endl;
			    return 1;
            }
            Debug::debug(Debug::error,__FUNCTION__) <<  "Error: Invalid linked sprite index. Skipping image "<< i<<": " <<sub.group<< ","<< sub.img <<". Ignoring error.\n"<< endl;
			continue;
          }
          if( sub.prev > 32767 ){
            if( !my_force ){
                 Debug::debug(Debug::error,__FUNCTION__) <<  "Error: Linked sprite index too large in image "<< i<<": " <<sub.group<< ","<< sub.img <<". Ignoring error.\n"<< endl;
			  return 1;
            }
             Debug::debug(Debug::error,__FUNCTION__) <<  "Error: Linked sprite index too large in image "<< i<<": " <<sub.group<< ","<< sub.img <<". Ignoring error.\n"<< endl;
		}

		  if( my_debug ) Debug::debug(Debug::resources,__FUNCTION__) <<  "Image lu "<< i << endl;

          while( sub.length == 0 ) {
            if( my_debug ) Debug::debug(Debug::resources,__FUNCTION__) <<  " -> "<< sub.prev<< endl;


            fseek( sff_file, offset[sub.prev], SEEK_SET );
            fread( &sub2, sizeof(SFF_SUBHEADER), 1, sff_file );
            sub.length = sub2.next_offset-offset[sub.prev]-32;
            if( (sub.prev <= sub2.prev) && ((sub.prev != 0) || (i == 0)) && sub2.length==0 ) {
                if( !my_force ) {
                    Debug::debug(Debug::resources,__FUNCTION__) <<  "Image: " <<i<<"lu ("<<sub.group<<" , "<<sub.img << ") : circular definition or forward linking. Aborting."<<endl;
					return 1;
                }
                Debug::debug(Debug::resources,__FUNCTION__) <<  " Circular definition or forward linking error. Skipping Image: " <<i<<"lu ("<<sub.group<<" , "<<sub.img << ") "<<endl;
				is_linked = -1;
                break; /* Hmm, better take a closer look at this part later. */
            }
            else{
                if(sub.length == 0) sub.prev = sub2.prev;
                else reallength = sub2.next_offset-offset[sub.prev]-32;
            }
          }
          if( is_linked == -1 ) continue;
          else if( my_debug ) Debug::debug(Debug::resources,__FUNCTION__) <<endl;




          /* Check whether image is linked to a duplicately numbered image: */
          if( dupcheck[sub.prev] ){
              std::sprintf( linked_name, "%sx%05hu.pcx", dirprefix, sub.prev );
				//strcpy(tempPCX->pcxdata.Name,linked_name);
				strcpy(tempPCXDATA->Name,linked_name);
#ifdef _DEBUG
          /* Temporary addition, to check whether errors would have occurred in pre-0.8 versions of Sffextract: */
          /* (Hm, can't decide whether to leave this enabled in the release.)  - Winane */
              Debug::debug(Debug::resources,__FUNCTION__) << i <<" ("<< sub.group <<","<< sub.img << ") linked to "<< linked_name<< endl;
				//fprintf( ef, "%lu (%d,%d) linked to %s\n", i, sub.group, sub.img, linked_name );
#endif
          }
		  // Determina o nome da imagem
		// %s = String of characters
		// *X = Unsigned hexadecimal integer (capital letters)
		// *  = The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted
        // %0 = Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier).

          else if( my_hex_output )
			  std::sprintf( linked_name, "%s%0*X%0*X.pcx", dirprefix, 4, sub2.group, 4, sub2.img );
          else if( my_short_output )
              std::sprintf( linked_name, "%s%0*d%0*d.pcx", dirprefix, 4, sub2.group, 4, sub2.img );
          else
              std::sprintf( linked_name, "%s%0*d%0*d.pcx", dirprefix, 5, sub2.group, 5, sub2.img );

		//strcpy(tempPCX->pcxdata.Name,linked_name);
		  strcpy( tempPCXDATA->Name,linked_name);
          if( sub.group == 9000 && (sub.img == 0 || sub.img == 1) )
			  Debug::debug(Debug::resources,__FUNCTION__) << "Warning: Image "<<sub.group<< " , "<< sub.img << " (at index "<< i<<"" " ) is a linked sprite.\n"<< endl;
			 //fprintf( ef, "Warning: Image %d,%d (at index %lu) is a linked sprite.\n", sub.group, sub.img, i );
        }
		else {
			is_linked = 0;
			tempPCXDATA->bIsLinked=false;
			//tempPCX->pcxdata.bIsLinked=false;
		}





        /* Read in PCX header data. */
        j = fread( &pcxhead, 1, sizeof(PCX_HEADER), sff_file ); /* May as well re-use j for this. */
        fseek( sff_file, 0-j, SEEK_CUR );
		memcpy(&tempPCXDATA->PcxHeader,&pcxhead,sizeof(PCX_HEADER));
        /* Get image data. */
        pcxdata = (unsigned char *) realloc( pcxdata, reallength );
		pcxlistdata = (unsigned char *) realloc( pcxdata, reallength );
        if( pcxdata == NULL ){
             Debug::debug(Debug::resources,__FUNCTION__) << "Error: Can't reallocate memory for PCX data, or PCX data is zero-length. Aborting.\n"<< endl;
			//fprintf( ef, "Error: Can't reallocate memory for PCX data, or PCX data is zero-length. Aborting.\n" );
            free( offset );
            free( dupcheck );
            free( imglist );
            free( palselect );
            return 1;
        }
        if( !fread( pcxdata, reallength, 1, sff_file ) ){
            Debug::debug(Debug::resources,__FUNCTION__) << "Error: Couldn't read entire PCX data of image "<< i <<".\nSFF file seems to be truncated. Aborting.\n"<< endl;
			//fprintf( ef, "Error: Couldn't read entire PCX data of image %lu.\nSFF file seems to be truncated. Aborting.\n", i );
            return 1;
        }
		memcpy(pcxlistdata,pcxdata,reallength);

		tempPCXDATA->Lenght=reallength;
		tempPCXDATA->pImageData=pcxlistdata;

		/* Check to see if the PCX file uses an 8-bit palette. */
        if( (reallength < 129) || (pcxhead.version < 5) || (pcxhead.BitsPerPixel != 8) || (pcxhead.NPlanes != 1) )
            is_8bitpal = 0;
        else if( (!is_linked && !sub.same_pal) || (is_linked && !sub2.same_pal) ){
            if( (reallength < 897) || *(pcxdata+reallength-769) != 12 ){
              /*
                If a palettized 8-bit image's subheader claims it's got an individual
                palette, but in fact its palette was removed, then Mugen will just use
                the next 768 bytes in the SFF file instead (filling in with 0xFF if the
                image is at the end of the file (only tested once)), if not a character
                in DOS Mugen.  Emulating that interpretation isn't entirely desirable,
                so let's just give such images the first or user-specified palette
                instead, as I assume would happen if it's a DOS character (too lazy to
                verify =P ).  We'll indicate such images with is_8bitpal = 2.  -Winane
              */
                if( *(pcxdata+reallength-1) != 12 ) is_8bitpal = 0;
                else is_8bitpal = 2;
            }
            else is_8bitpal = 1;
        }
        else if( *(pcxdata+reallength-1) != 12 ){
            if( (reallength < 897) || *(pcxdata+reallength-769) != 12 )
                is_8bitpal = 0;
            else is_8bitpal = -1; /* Means that the subheader indicates shared palette,
                                     but the palette apparently wasn't removed.
                                     Probably caused by CharSffDtoW, or Sprmaker if i==0. */
        }
        else is_8bitpal = 1;

        /* The language here isn't entirely accurate when the image being processed is a linked image.
           But we'll worry about that later, if ever.  Doesn't seem too significant to me (Winane).*/
        if( !is_8bitpal )
            Debug::debug(Debug::resources,__FUNCTION__) << "Notice: Image "<< i <<" ( "<<sub.group<<","<< sub.img<<" ) is not in 256-color PCX format: "<<pcxname+strlen(dirprefix) <<".\nSFF file seems to be truncated. Aborting.\n"<< endl;
			//fprintf( ef, "Notice: Image %lu (%d,%d) is not in 256-color PCX format: %s\n", i, sub.group, sub.img, pcxname+strlen(dirprefix) );
                       /* Assuming there's no other way for a PCX file to be 256-color.  I'm not 100% sure about that.  -Winane */

        else if( is_8bitpal==-1 && (!is_linked || sub.same_pal) ){
           Debug::debug(Debug::resources,__FUNCTION__) << "Notice: Image "<< i <<" ( "<<sub.group<<","<< sub.img<<" ) kept own palette despite subheader: "<< pcxname+strlen(dirprefix)<< endl;

            if( !(!is_linked && sub.group==9000 && sub.img==1) && !(is_linked && sub2.group==9000 && sub2.group==1) ){
                if( my_use_act && (!my_linux_character || palselect[i]==2) ){
                    Debug::debug(Debug::resources,__FUNCTION__) << "But sffextract will now replace its palette with the specified ACT palette.\n"<< endl;
			       }
                else if( my_create_pcx && palselect[i]==2 && i!=0 ){
                   Debug::debug(Debug::resources,__FUNCTION__) << "But sffextract will now replace its palette with the 1st palette in the SFF.\n"<< endl;
			      }
            }
        }

        else if( is_8bitpal==2 && !(is_linked && sub.same_pal) ){

			   Debug::debug(Debug::resources,__FUNCTION__) <<  "Notice: Image: " <<i<<"lu ("<<sub.group<<" , "<<sub.img << ") : has no palette despite subheader: "<<  pcxname+strlen(dirprefix)<<endl;
			if( my_use_act )
               Debug::debug(Debug::resources,__FUNCTION__) <<  "Sffextract will now replace its missing palette with the palette you specified."<< endl;
            else if( my_create_pcx ){
                if( found_1st )
                    Debug::debug(Debug::resources,__FUNCTION__) <<  "Sffextract will now give it the first palette in the SFF file."<< endl;
            else Debug::debug(Debug::resources,__FUNCTION__) <<  "Sffextract will have to give it a blank palette."<< endl;
			}
        }

	    //adiciona o palette nas imagens da lista
		if (is_linked) {
			/* ainda não sei o que fazer aqui....
			//deve achar a imagem na lista pelo nome, em caso dela não ter sido criada no siatema de arquivo...????
			//linked_pcx = fopen( linked_name, "rb" );
			if( linked_pcx == NULL ) {
              if( !my_force ){
                fprintf( ef, "Error: Failed to open linked-to PCX file %s,\nlinked to from image %lu (%d,%d). Aborting.\n",
                    linked_name, i, sub.group, sub.img );
                return 1;
              }
              fprintf( ef, "Error: Failed to open linked-to PCX file %s\nSkipping image %lu (%d,%d).\n", linked_name, i, sub.group, sub.img );
          }
          else {
              // Copy previous PCX file and save as the new one:
              fseek( linked_pcx, 0, SEEK_END );
              reallength = ftell( linked_pcx );
              pcxdata = (char *) realloc( pcxdata, reallength );
              if( pcxdata == NULL ){
                  fprintf( ef, "Error: Can't reallocate memory for PCX data, or PCX data is zero-length. Aborting.\n" );
                  free( offset );
                  free( dupcheck );
                  free( imglist );
                  free( palselect );
                  return 1;
              }
              fseek( linked_pcx, 0, SEEK_SET );
              fread( pcxdata, reallength, 1, linked_pcx );
              fclose( linked_pcx );
              if( (pcxfile = fopen( pcxname, "wb" )) == NULL ){
                  fprintf( ef, "Error: Couldn't create PCX file %s for writing. Aborting.\n", pcxname );
                  return 1;
              }
              fwrite( pcxdata, reallength, 1, pcxfile );
              fclose( pcxfile );
          } */
		}else { // não é uma imagem linkada
		if( is_8bitpal ){ // na primeira imagem ele entra aqui. isso retira a necessidade dessa parte na fase de criação do PCX
              if( !found_1st && !my_use_act && is_8bitpal!=2 ){
                  memcpy( palsaveD, pcxdata+reallength-768, 768 );
                  memcpy( palsave1, palsaveD, 768 );
				  memcpy(tempPCXDATA->ColorPallet,palsaveD,768);
                  found_1st = 1;
                  Debug::debug(Debug::resources,__FUNCTION__) <<  "First palette. "<<endl;
              }

              else if( palselect[i]==2 || (my_use_act && !my_linux_character) || is_8bitpal==2 ){
                  if( !(sub.group==9000 && sub.img==1 && (!sub.same_pal || is_8bitpal==-1)) || is_8bitpal==2 )
                      {
						tempPCXDATA->pImageData= (unsigned char *) realloc(tempPCXDATA->pImageData,tempPCXDATA->Lenght+768 );
						// copiar o pallete para o final da posição de memória imagePCX
						void *address =tempPCXDATA->pImageData + tempPCXDATA->Lenght;
						memcpy(address,palsave1,768);
						memcpy( tempPCXDATA->ColorPallet,palsave1,768);
						//atualiza o tamanho do bloco de memória
						tempPCXDATA->Lenght = tempPCXDATA->Lenght+768;

			  	  }

			  }

              else if( palselect[i]==1 && found_1st ){
				  if( is_8bitpal==1 || (my_use_act && !(sub.group==9000 && sub.img==1)) ) {
                     tempPCXDATA->pImageData= (unsigned char *) realloc( tempPCXDATA->pImageData, tempPCXDATA->Lenght+768 );
					  // copiar o pallete para o final da posição de memória imagePCX
					  void *address = tempPCXDATA->pImageData +tempPCXDATA->Lenght;
					  memcpy(address,palsaveD,768);
					  memcpy(tempPCXDATA->ColorPallet,palsaveD,768);
					  //atualiza o tamanho do bloco de memória
					 tempPCXDATA->Lenght = tempPCXDATA->Lenght+768;

				  }
			  }

              else if( my_linux_character ){
                  if( is_8bitpal==1 || !found_1st ){
                      memcpy( palsaveD, pcxdata+reallength-768, 768 );
					  memcpy(tempPCXDATA->ColorPallet,palsaveD,768);
                      if( my_debug ){
                          if( !found_1st ) Debug::debug(Debug::resources,__FUNCTION__) <<  "First palette. "<<endl;
                           else Debug::debug(Debug::resources,__FUNCTION__) <<  "Individual palette. "<<endl;

                      }
                      found_1st = 1;
                  }
              }

              else if( !my_use_act && is_8bitpal==1 ){  //entrou aqui na terceira imagem grupo 0 imagem 0
                  if( sub.same_pal ) {
                       tempPCXDATA->pImageData= (unsigned char *) realloc(tempPCXDATA->pImageData, tempPCXDATA->Lenght+768 );
					  // copiar o pallete para o final da posição de memória imagePCX
					  void *address = tempPCXDATA->pImageData + tempPCXDATA->Lenght;
					  memcpy(address,palsaveD,768);
					  memcpy( tempPCXDATA->ColorPallet,palsaveD,768);
					  //atualiza o tamanho do bloco de memória
					  tempPCXDATA->Lenght = tempPCXDATA->Lenght+768;

				  }

                  else if( my_header.palette_type == my_invert_shared ){
                       memcpy( palsaveD, pcxdata+reallength-768, 768 );
					   memcpy( tempPCXDATA->ColorPallet,palsaveD,768);
                      if( my_debug ) Debug::debug(Debug::resources,__FUNCTION__) <<  "Individual palette. "<<endl;
                  }
              }
          }

		} // fim da adição do pallete na Lista ligada


		if( my_create_pcx ){

            if( is_linked == 1 ){

          linked_pcx = fopen( linked_name, "rb" );
          if( linked_pcx == NULL ) {
              if( !my_force ){
                Debug::debug(Debug::error,__FUNCTION__) <<  "Error: Failed to open linked-to PCX file: "<<  linked_name <<"linked to from image: " <<i<<"lu (" <<sub.group<<" , "<<sub.img<<")"<<endl;
				error = true;
                return 1;
              }
              Debug::debug(Debug::error,__FUNCTION__) <<  "Error: Failed to open linked-to PCX file: "<<  linked_name <<"Skipping image: " <<i<<"lu (" <<sub.group<<" , "<<sub.img<<")"<<endl;

          }
          else {
              /* Copy previous PCX file and save as the new one: */
              fseek( linked_pcx, 0, SEEK_END );
              reallength = ftell( linked_pcx );
              pcxdata = (unsigned char *) realloc( pcxdata, reallength );
              if( pcxdata == NULL ){
                  Debug::debug(Debug::error,__FUNCTION__) <<  "Error: Can't reallocate memory for PCX data, or PCX data is zero-length. Aborting." <<endl;
                  free( offset );
                  free( dupcheck );
                  free( imglist );
                  free( palselect );
				  error = true;
                  return 1;
              }
              fseek( linked_pcx, 0, SEEK_SET );
              fread( pcxdata, reallength, 1, linked_pcx );
              fclose( linked_pcx );
              if( (pcxfile = fopen( pcxname, "wb" )) == NULL ){
                   Debug::debug(Debug::error,__FUNCTION__) << "Error: Couldn't create PCX file: "<< pcxname << " for writing. Aborting. "<<  endl;
					error = true;
				   return 1;
              }
              fwrite( pcxdata, reallength, 1, pcxfile );
              fclose( pcxfile );
          }
		} else { // image não é linkada

          if( my_debug ) Debug::debug(Debug::resources,__FUNCTION__) << "Image: "<<i<<"lu"<<endl;

          /* Save image data to a file */
          if( (pcxfile = fopen( pcxname, "wb" )) == NULL ){
              Debug::debug(Debug::resources,__FUNCTION__) << "Error: Couldn't create PCX file : "<< pcxname << "  for writing. Aborting. "<<  endl;
				error = true;
			  //fprintf( ef, "Error: Couldn't create PCX file %s for writing. Aborting.\n", pcxname );
              return 1;
          }
          /* Skip last 768 bytes if we're about to replace the palette. */
          if( is_8bitpal%2 && (!sub.same_pal || is_8bitpal==-1) && !(sub.group==9000 && sub.img==1) && ((my_use_act && !my_linux_character) || (palselect[i]==2 && i!=0)) ){
              fwrite( pcxdata, reallength-768, 1, pcxfile );
          }
          /* Otherwise, save the whole thing. */
          else fwrite( pcxdata, reallength, 1, pcxfile );

          /* (Yes, much of this code was written while using a 1600x1200 LCD screen.
             My apologies for not making it more readable on smaller displays.  -Winane) */


          /* I'll explain the logic used here later, if I'm feeling ambitious. =P  -Winane */
			// copia o palette da 1a imagem, o qual será utilizado nas imagens posteriores que utilizam o palette compartilhado
		  if( is_8bitpal ){
              if( !found_1st && !my_use_act && is_8bitpal!=2 ){
                  memcpy( palsaveD, pcxdata+reallength-768, 768 );
                  memcpy( palsave1, palsaveD, 768 );
                  found_1st = 1;
                  if( my_debug ) Debug::debug(Debug::resources,__FUNCTION__) << "First palette. " <<endl;
              }

              else if( palselect[i]==2 || (my_use_act && !my_linux_character) || is_8bitpal==2 ){
                  if( !(sub.group==9000 && sub.img==1 && (!sub.same_pal || is_8bitpal==-1)) || is_8bitpal==2 )
                      fwrite( palsave1, 768, 1, pcxfile );
              }

              else if( palselect[i]==1 && found_1st ){
                  if( is_8bitpal==1 || (my_use_act && !(sub.group==9000 && sub.img==1)) )
                      fwrite( palsaveD, 768, 1, pcxfile );
              }

              else if( my_linux_character ){
                  if( is_8bitpal==1 || !found_1st ){
                      memcpy( palsaveD, pcxdata+reallength-768, 768 );
                      if( my_debug ){
                          if( !found_1st ) Debug::debug(Debug::resources,__FUNCTION__) << "First palette. " <<endl;
                          else Debug::debug(Debug::resources,__FUNCTION__) << "Individual palette. " <<endl;
                      }
                      found_1st = 1;
                  }
              }

              else if( !my_use_act && is_8bitpal==1 ){  //entrou aqui na terceira imagem grupo 0 imagem 0
                  if( sub.same_pal )
                      fwrite( palsaveD, 768, 1, pcxfile );

                  else if( my_header.palette_type == my_invert_shared ){
                      memcpy( palsaveD, pcxdata+reallength-768, 768 );
                      Debug::debug(Debug::resources,__FUNCTION__) << "Individual palette. " <<endl;
                  }
              }
          }

          fclose( pcxfile );
        }

        if( dupcheck[i] ){
            if( sub.group == 9000 && (sub.img == 0 || sub.img == 1) )
                 Debug::debug(Debug::resources,__FUNCTION__) << "Warning:" ;
            else Debug::debug(Debug::resources,__FUNCTION__) << " Notice:" ;
            Debug::debug(Debug::resources,__FUNCTION__) << " Extra image: "<< sub.group<<" , "<<sub.img<<" Saved as: "<< pcxname+strlen(dirprefix) <<endl;
        }
        else Debug::debug(Debug::resources,__FUNCTION__) << "Saved as: "<< pcxname+strlen(dirprefix) <<endl;

     }

    /* Output to stdout. */
     if( my_display_contents ) {

        /* comments (if any) */
        if( strcmp("", sub.comments) ) {
            strncpy(comment, sub.comments, 13);
            token = strtok( comment, seps );
            if(token != NULL) Debug::debug(Debug::resources,__FUNCTION__) << token <<endl;
            while( (token = strtok(NULL, seps)) != NULL ){
                Debug::debug(Debug::resources,__FUNCTION__) << token <<endl;
            }
        }

        /* individual palette while default is shared */
        if( my_header.palette_type == !my_invert_shared && sub.same_pal == FALSE && my_display_options )
            Debug::debug(Debug::resources,__FUNCTION__) <<" Individual palette\n#\n1\n1"<<endl;
        /* shared palette while default is individual */
        if( my_header.palette_type == my_invert_shared && sub.same_pal == TRUE && my_display_options )
             Debug::debug(Debug::resources,__FUNCTION__) << "; Shared palette\n#\n1\n2\n" <<endl;

        /* pcx filename, group, image & coords */
        Debug::debug(Debug::resources,__FUNCTION__) << pcxname <<endl;
		Debug::debug(Debug::resources,__FUNCTION__) << "Group: "<< sub.group<<"Image: "<< sub.img <<" -> x: "<< sub.xcoord<< " ->y: "<< sub.ycoord <<endl;
     }

     if( sub.next_offset == 0 ){ /* Just in case any SFFs actually conform to formats.txt. */
        if (i<my_header.nb_imgs-1)
           Debug::debug(Debug::resources,__FUNCTION__) <<  "Warning: Subheader indicates End Of File but not all images (as indicated by SFF header) were processed.\n" <<endl;
        break;
     }
     else if( sub.next_offset < (offset[i]+32) || sub.next_offset > 2147483615 ){
        Debug::debug(Debug::resources,__FUNCTION__) << "Error: Subheader of image " << i <<" ( "<< sub.group <<","<<sub.img<<") specifies invalid next offset.\nAborting." <<  endl;
	    error = true;
		return 1;
     }
	 if (!error) {
	 Debug::debug(Debug::resources,__FUNCTION__) << "Create Mugen Sprite "<<sub.group<< " , "<< sub.img <<  endl;
	 //Adiciona o Arquivo PCX À lista ligada
	 tempPCXDATA->setLoaded();
	 PCXList[sub.group][sub.img]=tempPCXDATA;
	 //SpriteList[sub.group][sub.img] =  new CMugenSpriteV1(tempPCXDATA,mask);

	 }else {
	 Debug::debug(Debug::resources,__FUNCTION__) << "Skeeping image cause of errors " <<  endl;
	 error = false;
	 }
	
	} //end loop for

    fclose( sff_file );
    //free( pcxdata );

    return 0;
}

/** @fn CSFFManager::treatFilesystem()
@brief verifica as questões do sistema de arquivos
@return 1 se falhar e 0 se tiver sucesso
@warning
**/
int	 CSFFManager::treatFilesystem() {
if (error) return 1;
char dirprefix[_MAX_DRIVE + _MAX_DIR - 13] = "\0"; /* current directory */
const char*  filename=_my_file;
//char fname[_MAX_FNAME] = "\0"; /* filename without directory */
string fname="";
//unsigned long i, j; /* "For" loop indices. */

/*  char drive[_MAX_DRIVE] = "\0";
    char dir[_MAX_DIR] = "\0";
 */
//char ext[_MAX_EXT] = "\0";
string ext="";

    /* Sets directory prefix for filenames */
    if( my_absolute_paths ) {
      if( !getcwd(dirprefix, _MAX_DRIVE + _MAX_DIR - 16) ) {
        Debug::debug(Debug::resources,__FUNCTION__) <<"sffextract.c: fixme: not enough memory for dirprefix\n" <<endl;
		error = true;
        return 1;
      }
#if defined(__MSDOS) || defined(_WIN32)
#if !defined(_MSC_VER) && !defined(__MINGW32__) && !defined(__BORLANDC__)
      /* For some reason, DJGPP's getcwd uses / instead of \. */
      /* Ugly fix. Have a look at this later. */
      for (i=0 ; i<strlen(dirprefix) ; i++)
        if (dirprefix[i] == '/') dirprefix[i] = '\\';
#endif
#endif
      /* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( dirprefix[strlen(dirprefix)-1] != DIR_SEPARATOR ){
          dirprefix[strlen(dirprefix)+1] = '\0';
          dirprefix[strlen(dirprefix)] = DIR_SEPARATOR;
      }
    }
    else {
      dirprefix[0] = '\0'; /* no prefix => current directory */
    }

#if defined(__MSDOS) || defined(_WIN32)
 //   for (i=0 ; i<strlen(filename) ; i++)
   //     if (filename[i] == '/') filename[i] = '\\';
#endif

#if 0
/*  _splitpath( filename, drive, dir, fname, ext ); */
#if defined(_MSC_VER)
   // _splitpath( filename, NULL, NULL, fname, ext );
#else
    fname = basename (filename);
#endif
#endif
	fname = Filesystem::stripDir(string(filename));

	if( fname.empty() ){
        Debug::debug(Debug::resources,__FUNCTION__) << "Error splitting SFF file name from extension.\nEither the file name starts with a period, or the file name is too long.\n" <<endl;
        /* I haven't overlooked any other possible explanations for such an error, have I?  -Winane */
        error = true;
		return 1;
    }else {
		ext = Filesystem::checkExtension(fname);
		if( ext.length() > _MAX_EXT ){
        Debug::debug(Debug::resources,__FUNCTION__) << "The file extension is too long.\n" <<endl;
        /* I haven't overlooked any other possible explanations for such an error, have I?  -Winane */
        error = true;
		return 1;
    }
	}

	if( fname.length() > _MAX_FNAME ){
        Debug::debug(Debug::resources,__FUNCTION__) << "The file name is too long.\n" <<endl;
        /* I haven't overlooked any other possible explanations for such an error, have I?  -Winane */
        error = true;
		return 1;
    }

    if( my_subdirectory ) {
    /* Create a subdirectory whose name is the same as the input file, but without
       the extension .sff */
      if( ext[0] == '\0' ){
          Debug::debug(Debug::resources,__FUNCTION__) << "Error: Sorry, the -d option is not designed to work with SFF files lacking a\nfile extension.  Please rename the file and try again.\n" <<endl;
          error = true;
		  return 1;
      }
	  if( strlen(dirprefix) + fname.length() > _MAX_DRIVE + _MAX_DIR - 16 ){
          Debug::debug(Debug::resources,__FUNCTION__) << "Error: Specified destination path is too long.\n" <<endl;
          error = true;
		  return 1;
      }
	  strcat( dirprefix, fname.c_str() );

      /* create subdirectory, with drwxr-xr-x permissions if the file system supports that. */
#if (defined(__MSDOS) || defined(_WIN32)) && !defined(__DJGPP__)
      if( (mkdir(dirprefix) == -1) && (errno != EEXIST) ) {
#else
      if( (mkdir(dirprefix,493) == -1) && (errno != EEXIST) ) {
#endif
        Debug::debug(Debug::resources,__FUNCTION__) << "Error: Unable to create directory: "<< dirprefix <<endl;
        error = true;
		return 1;
      }
      dirprefix[strlen(dirprefix)+1] = '\0';
      dirprefix[strlen(dirprefix)] = DIR_SEPARATOR;
    }

    Debug::debug(Debug::resources,__FUNCTION__) << "Directory prefix : " << dirprefix <<endl;




    strcpy ( _my_dir_prefix, dirprefix );


	 }

/** @fn CSFFManager::treatACT()
@brief carrefga os dados de Palettas auxiliares
@return 0 se sucesso e 1 se falha
@warning
**/
int CSFFManager::treatACT() {
if (error) return 1;
FILE  *act_file;
PCX_HEADER pcxhead; /* Used by both the -a option code and by the PCX extraction code. */

unsigned char colorsave[3] = "\0"; /* For RGB palette entry storage. */

unsigned long i;//, j; /* "For" loop indices. */


if(my_use_act){
		act_file = fopen( my_act_path.c_str(), "rb" );
        if( !act_file ){
            set_use_act( FALSE );
			Debug::debug(Debug::resources,__FUNCTION__) << "Palette file does not exist"<<my_act_path.c_str()<< endl;
		    Debug::debug(Debug::resources,__FUNCTION__) << "TODO: Load Another pallete or verify this befora call SffManager"<< endl;
           // fprintf( ef, "Palette file %s does not exist.\n", act_path.c_str() );
            //error = true;
			return 1;
        }
        fseek( act_file, 0, SEEK_END );
        if( ftell(act_file) == 768 ){ /* then it must be an ACT file. */
            for( i=0; i<256; i++ ){
                fseek( act_file, -3*(i+1), SEEK_END );
                fread( colorsave, 3, 1, act_file );
                palsave1[3*i]=colorsave[0];
                palsave1[3*i+1]=colorsave[1];
                palsave1[3*i+2]=colorsave[2];
            }
			Debug::debug(Debug::resources,__FUNCTION__) << "Applying palette from ACT file: "<<my_act_path.c_str()<< endl;
            //fprintf( ef, "Applying palette from ACT file: %s\n", act_path.c_str() );
            fclose( act_file );

        }
        else if( ftell(act_file) < 897 ){ /* 128-byte header + 768-byte palette + 0x0C byte = minimum 8-bit PCX file size. */
            set_use_act( FALSE );
            Debug::debug(Debug::resources,__FUNCTION__) << "File %s is not a valid palette file: " << my_act_path.c_str() <<endl;
			//fprintf( ef, "File %s is not a valid palette file.\n", act_path.c_str() );
            //error = true;
			return 1;
        }
        else{ /* we'll assume it's a PCX file, for now. */
            fseek( act_file, 0, SEEK_SET );
            fread( &pcxhead, sizeof(PCX_HEADER), 1, act_file );
            /* Check to see if the PCX file uses an 8-bit palette. */
            if( (pcxhead.manufacturer == 10) && (pcxhead.version >= 5) && (pcxhead.BitsPerPixel == 8) && (pcxhead.NPlanes == 1) ){
                fseek( act_file, -769, SEEK_END);
                fread( colorsave, 1, 1, act_file ); /* No need to define another variable; colorsave will do just fine. */
                if( colorsave[0] == 12 ){
                    fseek( act_file, -768, SEEK_END );
                    fread( palsave1, 768, 1, act_file );
                    Debug::debug(Debug::resources,__FUNCTION__) << "Applying palette from PCX file: "<< my_act_path.c_str() <<endl;
                    fclose( act_file );
                }
                else{
                    set_use_act( FALSE );
                    Debug::debug(Debug::resources,__FUNCTION__) << "File: "<<  my_act_path.c_str()<< " is not a valid palette file. (Must be ACT or 8-bit PCX.)" <<endl;
                    //error = true;
					return 1;
                }
            }
            /* Add support for JASC and RIFF palette files later... */
            /* Minimum JASC PAL size = 1,813 bytes (carriage returns are necessary). */
            else{
                set_use_act( FALSE );
                Debug::debug(Debug::resources,__FUNCTION__) <<"File: " <<  my_act_path.c_str() <<" is not a valid palette file. (Must be ACT or 8-bit PCX.)"<<endl;
                //error = true;
				return 1;
            }
        }
    }

}

/** @fn CSFFManager::saveImage(int imageNumber,int group)
@brief cria um arquivo PCX da imagem selecionada
@param imageNumber: numero da imagem
@param group: grupo da imagem
@return 1 se falhar e 0 (zero) se sucesso
@warning
**/
int CSFFManager::saveImage(unsigned int imageNumber,unsigned int group){
	if (error) return 1;
	PCXDATA *image;
	image=PCXList[group][imageNumber];

	if(image==NULL){
		// mensagem não achou a imagem
		return 1;
	}
	FILE *pcxfile;
	char * pcxname=image->Name;
	if( (pcxfile = fopen(pcxname, "wb" )) == NULL ){
		 Debug::debug(Debug::error,__FUNCTION__) << "Error: Couldn't create PCX file: "<< pcxname <<" for writing. Aborting." <<endl;
                  return 1;
     }
	fwrite( image->pImageData, image->Lenght, 1, pcxfile );
    fclose( pcxfile );

}

/** @fn CSFFManager::saveImageList()
@brief cria arquivos PCX de todas as imagens da lista
@return 1 se falhar e 0 (zero) se sucesso
@warning
**/
int CSFFManager::saveImageList(){
	if (error) return 1;
	//PCXLinkedList *image;

	 for (PCXDATAMap::iterator first_it = PCXList.begin(); first_it != PCXList.end(); first_it++){
		for(map<unsigned int, PCXDATA*>::iterator it = first_it->second.begin();it != first_it->second.end();it++){
            FILE *pcxfile;
			char * pcxname= (*it).second->Name;
	if( (pcxfile = fopen(pcxname, "wb" )) == NULL ){
		Debug::debug(Debug::error,__FUNCTION__) << "Error: Couldn't create PCX file: "<<  pcxname<<" for writing. Aborting."<< endl;
                  return 1;
     }
	fwrite( (*it).second->pImageData, (*it).second->Lenght, 1, pcxfile );
    fclose( pcxfile );

		}
    }
	return 0;
}

} //end SGF