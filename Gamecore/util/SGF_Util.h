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
#ifndef _S_G_F_funcs_h
#define _S_G_F_funcs_h

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
#include "../SGF_Config.h"
#include "SGF_Regex.h"
//#include "../graphics/SGF_Bitmap.h"
//#include <SDL.h>
#include "SGF_Path.h"
#include "SGF_Displayable.h"



#ifndef MIN
#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))
#endif
#ifndef MID
#define MID(x,y,z)   MAX((x), MIN((y), (z)))
#endif
#ifndef MEDIA
#define MEDIA(x,y)   ( ((x) + (y)) /2)
#endif

using namespace std;
namespace SGF {
class CConfiguration;
class CFont;
class CBitmap;
namespace Util{
extern const SGF_Word DigitOutputPrecision ;
extern const string HexDigits;

/**
 * @brief controlthespeed of the game
 * @param ticks
 * @param gameSpeed the desired speed
 * @return
 */
double gameTicks(double ticks, double gameSpeed=0.1);
extern const double pi;
bool isWindows();
bool isLinux();
bool isAndroid();
bool isOSX();


int clamp(int value, int min, int max);
/* returns a number between 0 and q-1. you will never get `q'. if
 * you wanted to get `q' then pass in q+1
 */
//int clamp(SGF_Byte value, SGF_Byte min, SGF_Byte max);

int rnd( int q );



double radians(double degree);

string getDataPath3();
 SGE_API  Filesystem::CAbsolutePath getDataPath2();
 SGE_API  Filesystem::CAbsolutePath getGamePath();
void setDataPath( const string & str );

 SGE_API  bool exists( const string & file );
 SGE_API  void limitPrintf(char * buffer, int size, const char * format, va_list args);
/* check that `version' is compatible with this program, mostly used
 * for network clients.
 */
 SGE_API  bool checkVersion(int version);

 SGE_API  int max(int a, int b);
 SGE_API  int min(int a, int b);
 SGE_API  int min(int a,int b,int c);
 SGE_API  double max(double a, double b);
 SGE_API  double min(double a, double b);



/* return a number between min/max */
int rnd( int min, int max );
//! return de ptsize of a truetype font;
int getPtSize(int width,int height);
/* rest in miliseconds */
void rest( int x );
/* rest in seconds */
void restSeconds(double x);

string trim(const string & str);
/* only upper cases the first letter of a string */
string upcase(string str);

/* lower cases the entire string */
string lowerCaseAll(string str);

/* upper cases the entire string */
string upperCaseAll(string str);

/* conta o n�mero de ocorrencias do caracter c na string passada */
int countChar(string string, char c);
/* retorna o tamanho em pixels da maior linha na string passada
*/
int messageSize(const CFont & font,string string);

/* convert a size in bytes into human readable form.
 * 234823592 = 223.94m
 */
string niceSize(unsigned long size);

//!strip out the string qhotes (")
string withoutQuote(string &str);
//!strip out the string qhotes (")
string * withoutQuote(string *str);

//! update de renderer and blit it to screen
 SGE_API void renderToScreen(CBitmap &work, double fps, bool show_fps=true, bool stretched=true);

int levenshtein(const string & str1, const string & str2);

int getPipe(int files[2]);

void showError(const CBitmap & screen, const Exception::CBase & exception, const string & info);
/* will create a screen of size GFX_X, GFX_Y */
void showError(const Exception::CBase & exception, const string & info);
/** \brief mostra um popup na tela com a mensagem passada
* \param font: fonte a ser utilizada
* \param message: mensagem
*/
void popup(const CFont & font, const string & message );

/**
 * \class CTextDisplayable
 *
 * \ingroup SGF_Util
 *
 * \brief Interface que todo objeto que puder mostrar texto na janela deve implementar
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * \note adaptado do Ceylan:http://ceylan.sourceforge.net/
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class SGE_API CTextDisplayable : public CDisplayable
     {


         public:



             CTextDisplayable()
             {};
             virtual ~CTextDisplayable() throw()
             {};

             //!Returns an user-friendly description of the state of this object.
             virtual const string toString( VerbosityLevels level= high ) const = 0 ;

            // Static section.
            //!Returns an user-friendly description of the state of this object.
            static const string ToString(list<CTextDisplayable*> displayables, VerbosityLevels level = high ) ;
			/**Defines what text output formats for TextDisplayable instances are available.
            */
			enum TextOutputFormat { rawText, html } ;
			//!Returns the current overall text format to be used by TextDisplayable instances.
            static TextOutputFormat GetOutputFormat() ;
            //!Sets the current overall text format to be used by TextDisplayable instances.
            static void SetOutputFormat( TextOutputFormat newOutputFormat ) ;



         protected:

			//!The text format to be used currently by TextDisplayable instances.
             static TextOutputFormat _OutputFormat ;



         private:


     } ;


::std::ostream & operator << ( ::std::ostream & os, const CTextDisplayable & textDisplayable ) ;


/** converte um n�mero numa string */

string toNumericalString( SGF_Byte number );
string toString( SGF_Dword value, bool bitField );
string toHexString( unsigned long value, bool prefix, SGF_Byte minDigits );
/**Returns the reversed source string, as read from right to left.
Example: "Marcio" becomes "oicraM"
*/
string reverse( const string & source );

// Container formatting section.
/*
 Formats the specified list of strings, according to the specified format.

Text output format is determined from overall settings: the list will be output with HTML tags, or use raw formatting, accordingly.
Parameters:	stringList 	the list of strings to format.
	targetFormat 	the format (ex: raw text, HTML, etc.) that should be used to encode the returned string
	surroundByTicks 	tells whether each entry of the list should be surrounded by ticks on output.
	indentationLevel 	the desired level of indentation, starting at 1 (used for raw text output).

Note:
if the STL was smarter, it would have allowed arguments whose type is list<string> in list<const string>. However no parameter of type 'const list<const string> &' can be used, since list elements have to be able to be assigned, hence 'stdlist<const X>' cannot be used.
  */
string formatStringList(
         const list<string> & stringList,
         bool surroundByTicks = false, SGF_Byte indentationLevel = 1 ) ;

 /*Formats the specified list of strings, according to the specified format.

Text output format is determined from overall settings: the list will be output with HTML tags, or use raw formatting, accordingly.
Parameters:	stringList 	the list of strings to format.
	surroundByTicks 	tells whether each entry of the list should be surrounded by ticks on output.
	indentationLevel 	the desired level of indentation, starting at 1 (used for raw text output).

Note:
if the STL was smarter, it would have allowed arguments whose type is list<string> in list<const string>. However no parameter of type 'const list<const string> &' can be used, since list elements have to be able to be assigned, hence 'stdlist<const X>' cannot be used.
*/

string formatStringList(
         const list<string> & stringList,
         CTextDisplayable::TextOutputFormat targetFormat,
         bool surroundByTicks = false, SGF_Byte indentationLevel = 1 ) ;

string join(const vector<string> & list, const string & middle);
} //end Util
} //end SGF


#endif
