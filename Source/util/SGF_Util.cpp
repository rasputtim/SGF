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

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <algorithm>
#include <sstream>
#include "SGF_Global.h"
#include "util/SGF_Util.h"
#include "configuration/SGF_Configuration.h"



#ifndef _WIN32
#include <unistd.h>
#endif
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

/* remove this once cmake and scons properly set DATA_PATH */
#ifndef DATA_PATH
#define DATA_PATH "data"
#endif

#if defined vsnprintf
#undef vsnprintf
#endif

using namespace ::std;

namespace SGF {

const Uint16 Util::DigitOutputPrecision = 40 ;

const string Util::HexDigits = "0123456789ABCDEF" ;


/** @fn Util::isWindows()
@brief Metodo que retorna verdadeiro caso o ambiente de compilacao
@return true: caso o ambiente de compilacao seja windows
	    false: qualquer outro ambiente
@warning nenhum aviso
**/
bool Util::isWindows(){
#ifdef _WIN32
    return true;
#else
    return false;
#endif
}

bool Util::isLinux(){
#if defined(LINUX)
    return true;
#else
    return false;
#endif
}

bool Util::isAndroid(){
#if defined(ANDROID)
    return true;
#else
    return false;
#endif
}



/**
@brief Metodo que retorna verdadeiro caso o ambiente de compilacao seja MAC
@return true: caso o ambiente de compilacao seja OSX
	    false: qualquer outro ambiente
@warning nenhum aviso
**/
bool Util::isOSX(){
#ifdef MACOSX
    return true;
#else
    return false;
#endif
}

/* the build system should define DATA_PATH */
static string dataPath = DATA_PATH;

double Util::gameTicks(double ticks, double gameSpeed){
	Debug::debug(Debug::input,__FUNCTION__) << "Global::Speed Counter: " << ticks <<  " SDL ticks (ms): " << SDL_GetTicks() << endl;

	Debug::debug(Debug::input,__FUNCTION__) << "Global::gamespeed: " << gameSpeed << endl;
	int TheSpeed = 60;  //uma velocidade de gamespeed = 0.1  e ticks por segund = 60
    double valor = ticks * gameSpeed * TheSpeed / Global::TICS_PER_SECOND;
	Debug::debug(Debug::input,__FUNCTION__) << "Conta: ( " << ticks << " * "<<gameSpeed <<" * "<< " 60 ) / "<< Global::TICS_PER_SECOND << " = " << valor<< endl;

	Debug::debug(Debug::input,__FUNCTION__) << "New gameticks: " << valor << endl;
	return valor;
}

const double Util::pi = 3.14159265;
/** @fn Util::radians(double degree)
@brief Metodo que converte graus em radianos
@param degree: graus a serem convertidos para radianos
@return radianos correspondentes ao graus passado como parametro
@warning nenhum aviso
**/
double Util::radians(double degree){
    return degree * pi / 180.0;
}
/** @fn Util::getPtSize(int width,int height)
@brief Metodo que converte altura e largura de uma Fonte True Type em ptsize
@param	width: largura da fonte
@param	height: altura da fonte
@return o tamanho da fonte em ptsize
@warning nenhum aviso
**/
int Util::getPtSize(int width,int height) {
	return MEDIA( width,height);
}

/** @fn Util::clamp(int value, int min, int max)
@brief Metodo que coloca o valor entre um mínimo e um máximo
@param value: o valor que se deseja padronizar
@param min: o mínimo que valor pode ser
@param max: o máximo que valor pode ser
@return inteiro randomico no range 0-max
@warning nenhum aviso
**/
int Util::clamp(int value, int min, int max){
    return MIN(MAX(value, min), max);
}
/** @fn int rnd( int max )
@brief Metodo que retorna um numero inteiro randomico no range de zero a max
@param max: valor maximo que rnd pode chegar
@return inteiro randomico no range 0-max
@warning nenhum aviso
**/
inline int rnd( int max ){
	if ( max <= 0 ) return 0;
	return (int)( rand() % (max+1) );
}

/** @fn Util::max(int a, int b)
@brief Metodo que retorna o maior entre dois números inteiros
@param	a: o primeiro inteiro a ser comparado
@param	b: o segundo inteiro a ser comparado
@return o maior inteiro
**/
int Util::max(int a, int b){
     return MAX(a,b);
}
/** @fn Util::min(int a, int b)
@brief Metodo que retorna o menor entre dois números inteiros
@param	a: o primeiro inteiro a ser comparado
@param	b: o segundo inteiro a ser comparado
@return o menor inteiro
**/
int Util::min(int a, int b){
    return MIN(a,b);
}



/** @fn Util::max(double a, double b)
@brief Metodo que retorna o maior entre dois números double
@param	a: o primeiro double a ser comparado
@param	b: o segundo double a ser comparado
@return o maior double
**/
double Util::max(double a, double b){
     return MAX(a,b);
}
/** @fn Util::min(double a, double b)
@brief Metodo que retorna o menor entre dois números doubles
@param	a: o primeiro double a ser comparado
@param	b: o segundo double a ser comparado
@return o menor double
**/
double Util::min(double a, double b){
    return MIN(a,b);
}





/** @fn int rnd( int nim , int max )
@brief Metodo que retorna um numero inteiro randomico no range de min a max
@param min: valor minimo que rnd pode chegar
@param max: valor maximo que rnd pode chegar
@return inteiro randomico no range min-max
@warning nenhum aviso
**/
int Util::rnd( int min, int max ){
	if ( max <= min ) return min;
	return (int)( (rand() % (max+1)) + min );
}
/** @fn Util::rest( int x )
@brief Metodo que espera x milisegundos
@param x: quantidade de milisegundos a esperar
@return nada
@warning The delay granularity is at least 10 ms (SDL delay...)
**/
void Util::rest( int x ){
	SDL_Delay( x );
}
/** @fn Util::restSeconds(double x)
@brief Metodo que espera x segundos
@param x: quantidade de segundos a esperar
@return nada
**/
void Util::restSeconds(double x){
    Util::rest((int)(x * 1000));
}

bool Util::checkVersion(int version){
    if (version == Global::getVersion()){
        return true;
    }

    /* when an incompatible version is made, add a check here, like
     *  version < getVersion(3, 5)
     * would mean any client below version 3.5 is incompatible.
     *
     * assume versions of client's greater than ourself is compatible, but
     * this may not be true. There is no way to check this.
     */
    if (version < 0){
        return false;
    }

    return true;
}

void Util::setDataPath( const string & str ){
    dataPath = str;
}

string Util::getDataPath3(){
	return dataPath + "/";
}

Filesystem::CAbsolutePath Util::getDataPath2(){
	// DO NOT USE CRelative Path Here. cause a loop
	// Todo: Fix this
	Debug::debug(Debug::filesystem,__FUNCTION__) << " BEGIN GET DATA PATH" << endl;
	Filesystem::CAbsolutePath tempPath=Filesystem::CAbsolutePath();
	string realpath=tempPath.path() + "data" + DIR_SEPARATOR;
	Debug::debug(Debug::filesystem,__FUNCTION__) <<  " END GET DATA PATH BASEPATH: "<<realpath << endl;
	Filesystem::CAbsolutePath realPath = Filesystem::CAbsolutePath(realpath);
	Debug::debug(Debug::filesystem,__FUNCTION__) <<  " END GET DATA PATH REALPATH: "<< realPath.path() << endl;
	return realPath;

	//	Debug::debug(Debug::filesystem,__FUNCTION__) << <<  " END GET DATA PATH CURRENTPATH: "<< tempPath.path() << endl;
	//	return tempPath;
	//}
/*	Filesystem::CRelativePath temp2(dataPath + "/");

	if(temp2.isComplete && temp2.exist()) {
		Filesystem::CAbsolutePath temp(temp2);
		Debug::debug(Debug::filesystem,__FUNCTION__) << <<  " END GET DATA PATH: "<< temp.path() << endl;
		return temp;
	}else if(!temp2.isComplete && temp2.exist()) {
		Filesystem::CAbsolutePath temp;
		temp.localJoin(temp2);
		Debug::debug(Debug::filesystem,__FUNCTION__) << <<  " END GET DATA PATH: "<< temp.path() << endl;
		return temp;
	} */
	}

Filesystem::CAbsolutePath Util::getGamePath(){

	// DO NOT USE CRelative Path Here. cause a loop
	// Todo: Fix this
	Debug::debug(Debug::filesystem,__FUNCTION__) << " BEGIN GET GAME PATH" << endl;
	Filesystem::CAbsolutePath tempPath=Filesystem::CAbsolutePath();
	string realpath=tempPath.path()+CConfiguration::gameModDir.getString() + DIR_SEPARATOR;
	Debug::debug(Debug::filesystem,__FUNCTION__) <<  " END GET GAME PATH BASEPATH: "<< realpath << endl;
	Filesystem::CAbsolutePath realPath = Filesystem::CAbsolutePath( realpath);

	//if (realPath.exist()) {
		Debug::debug(Debug::filesystem,__FUNCTION__) << " END GET GAME PATH REALPATH: "<< realPath.path() << endl;
		return realPath;
	//}else {
	//	Debug::debug(Debug::filesystem,__FUNCTION__) << <<  " END GET GAME PATH CURRENTPATH: "<< tempPath.path() << endl;
	//	return tempPath;
	//}

	/*
	Debug::debug(Debug::filesystem,__FUNCTION__) << << " BEGIN GET GAME PATH" << endl;
	Filesystem::CRelativePath temp2();

	if(temp2.isComplete && temp2.exist()) {
		Filesystem::CAbsolutePath temp(temp2);
		Debug::debug(Debug::filesystem,__FUNCTION__) << <<  " END GET GAME PATH: "<< temp.path() << endl;
		return temp;
	}else if(!temp2.isComplete && temp2.exist()) {
		Filesystem::CAbsolutePath temp;
		temp.localJoin(temp2);
		Debug::debug(Debug::filesystem,__FUNCTION__) << <<  " END GET GAME PATH: "<< temp.path() << endl;
		return temp;
	} */

}
#include <sys/stat.h>
bool Util::exists( const string & file ){

    struct stat stFileInfo;

	 bool blnReturn;
	 int intStat;

  // Attempt to get the file attributes

        intStat = stat(file.c_str(),&stFileInfo);


  if(intStat == 0) {
    // We were able to get the file attributes
    // so the file obviously exists.
    blnReturn = true;
  } else {
    // We were not able to get the file attributes.
    // This may mean that we don't have permission to
    // access the folder which contains this file. If you
    // need to do that level of checking, lookup the
    // return values of stat which will give you
    // more details on why stat failed.
    blnReturn = false;
  }
  Debug::debug(1,__FUNCTION__) << "Util::exists: " << blnReturn << endl;
  return(blnReturn);
}


/** @fn Util::trim(const string & str)
@brief Retira espaço no ínicio e final de uma string
@param	const string str: uma referência da string na qual se deseja retirar os espaços
@return a string sem os espaços
**/
string Util::trim(const string & str){
    size_t startpos = str.find_first_not_of(" \t");
    size_t endpos = str.find_last_not_of(" \t");
    // if all spaces or empty return an empty string
    if ((string::npos == startpos) ||
        (string::npos == endpos)){
        return "";
    } else {
        return str.substr(startpos, endpos-startpos+1);
    }
    return str;
}

/** @fn upperCase(int c)
@brief Converte o parâmetro c para o seu equivalente em caixa baixa se c for uma letra em caixa alta e tiver uma equivalente em caixa baixa.
       Se a conversão não for possível, o valor retornado é o valor de c inalterado.
@param	c: uma letra em caixa-alta para ser convertica, "casted" para int, ou EOF.
@return o valor de c no formato caixa baixa ou inalterado
@warning  O que deve ser considerado letra depende do locale sendo utilizado; No locale padrão C, uma letra caixa-baixa é: a b c d e f g h i j k l m n o p q r s t u v w x y z, which translate respectively to: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z.
**/
static int lowerCase(int c){
    return tolower(c);
}

/** @fn upperCase(int c)
@brief Converte o parâmetro c para o seu equivalente em caixa alta se c for uma letra em caixa baixa e tiver uma equivalente em caixa alta.
       Se a conversão não for possível, o valor retornado é o valor de c inalterado.
@param	c: uma letra em caixa-baixa para ser convertica, "casted" para int, ou EOF.
@return o valor de c no formato caixa alta ou inalterado
@warning  O que deve ser considerado letra depende do locale sendo utilizado; No locale padrão C, uma letra caixa-baixa é: a b c d e f g h i j k l m n o p q r s t u v w x y z, which translate respectively to: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z.
**/
static int upperCase(int c){
    return toupper(c);
}
/* makes the first letter of a string upper case */
string Util::upcase(string str){
    if ( str.length() > 0 && (str[0] >= 'a' && str[0] <= 'z') ){
        str[0] = str[0] - 'a' + 'A';
    }
    return str;
}
string Util::upperCaseAll(string str){
    ::std::transform(str.begin(), str.end(), str.begin(), upperCase);
    return str;
}

string Util::lowerCaseAll(string str){
    ::std::transform(str.begin(), str.end(), str.begin(), lowerCase);
    /*
    for (unsigned int i = 0; i < str.length(); i++){
        if (str[0] >= 'A' && str[0] <= 'Z'){
            str[0] = str[0] - 'A' + 'a';
        }
    }
    */
    return str;
}
string Util::withoutQuote(string &str){
    //verificar se tem aspasna string  e retirá-las

	size_t found;
    string::iterator it;

	while(str.find('"')!=string::npos){
   	   //apaga o caracter
       found=str.find('"');
	   Debug::debug(Debug::resources,__FUNCTION__) << "Util::withoutQuote // QuoteFound Pos: " << int(found) << endl;
	   it=str.begin()+found;
       str.erase (it);
       Debug::debug(Debug::resources,__FUNCTION__) << "Util::withoutQuote // New String : " << str << endl;

	}
	return str;
}

string * Util::withoutQuote(string *str){
    //verificar se tem aspasna string  e retirá-las

	size_t found;
    string::iterator it;

	while(str->find('"')!=string::npos){
   	   //apaga o caracter
       found=str->find('"');
	   Debug::debug(Debug::resources,__FUNCTION__) << "Util::withoutQuote // QuoteFound Pos: " << int(found) << endl;
	   it=str->begin()+found;
       str->erase (it);
       Debug::debug(Debug::resources,__FUNCTION__) << "Util::withoutQuote // New String : " << str << endl;

	}
	return str;
}

/** @fn minimum(int a,int b,int c)
@brief retorna o menor entre 3 numeros
@param	a: primeiro inteiro a ser comparado
@param	b: segundo inteiro a ser comparado
@param	c: terceiro inteiro a ser comparado
@return   o menor dos tres inteiros passados
**/
int min(int a,int b,int c){
  int min=a;
  if(b<min)
    min=b;
  if(c<min)
    min=c;
  return min;
}


/** @fn levenshtein_distance(const char *s, const char *t)
@brief retorna a distancia de levenshtein entre duas strings
@param str1: string que será comparada com str2
@param str2: string que será comparada com str1
@return   the  distance
@warning from: http://www.merriampark.com/ldc.htm
**/
static int levenshtein_distance(const char *s, const char *t){
  //Step 1
  int k,i,j,n,m,cost,distance;
  int * d;
  n=strlen(s);
  m=strlen(t);
  if(n!=0&&m!=0){
    d = (int*) malloc((sizeof(int))*(m+1)*(n+1));
    m++;
    n++;
    //Step 2
    for(k=0;k<n;k++)
	d[k]=k;
    for(k=0;k<m;k++)
      d[k*n]=k;
    //Step 3 and 4
    for(i=1;i<n;i++)
      for(j=1;j<m;j++)
	{
        //Step 5
        if(s[i-1]==t[j-1])
          cost=0;
        else
          cost=1;
        //Step 6
        d[j*n+i]=min(d[(j-1)*n+i]+1,d[j*n+i-1]+1,d[(j-1)*n+i-1]+cost);
      }
    distance=d[n*m-1];
	Debug::debug(Debug::font,__FUNCTION__) << "Freeing "<<endl;

    free(d);
    return distance;
  } else {
    return -1; //a negative return value means that one or both strings are empty.
  }
}

void Util::renderToScreen(CBitmap & buffer, double fps, bool show_fps, bool stretched) {
	Colors::ColorDefinition textColor = { 255, 255, 255 };

      // Finally render to screen
        buffer.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);

		buffer.updateTexture(); //update texture with the work done on the bitmap
		if(!stretched ) buffer.Blit();
		else buffer.BlitStretched(); //put the work from texture to the render
		if (show_fps){
				CResource::getDefaultFont()->DrawTextNew(0,300,textColor, buffer,"%2.2f FPS",fps);
        }
		buffer.BlitToScreen();  //put the render on the screen
		buffer.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
	}

// http://pt.wikipedia.org/wiki/Distância_Levenshtein
/** @fn Util::levenshtein(const string & str1, const string & str2)
@brief retorna a distancia de levenshtein entre duas strings
@param str1: string que serah comparada com str2
@param str2: string que serah comparada com str1
@return   the distance
@warning util para determinar quao semelhantes sao duas strings
**/
int Util::levenshtein(const string & str1, const string & str2){
    return levenshtein_distance(str1.c_str(), str2.c_str());
}

#ifdef _WIN32

#include <windows.h>
#include <io.h>
#include <fcntl.h>

//http://msdn.microsoft.com/en-us/library/windows/desktop/aa365780(v=vs.85).aspx
//http://msdn.microsoft.com/en-us/library/windows/desktop/aa365152(v=vs.85).aspx
/** @fn Util::getPipe(int files[2])
@brief Cria um pipe
@param int files[2]:
@return   0: ok
		 -1: error
@warning nao eh muito comum no ambiente windows
**/
int Util::getPipe(int files[2]){
    HANDLE read_in, write_in;
    int ok = CreatePipe(&read_in, &write_in, NULL, 0);
    if (ok == 0){
        return -1;
    }
    // files[0] = _open_osfhandle(read_in, O_RDONLY | O_BINARY);
    // files[1] = _open_osfhandle(write_in, O_WRONLY | O_BINARY);
    files[0] = _open_osfhandle((intptr_t) read_in, _O_RDONLY);
    files[1] = _open_osfhandle((intptr_t) write_in, _O_WRONLY);
    return 0;
}
#endif

//todo: corrigir. não está fuincionando. sempre retorna o tamanho da primeira linha
int Util::messageSize(const CFont & font, ::std::string string){
	int size = 0;
	int lines = countChar(string,'\n');
	if (lines<=1) return font.getTextLength(string.c_str());
	else if(lines == 2 ) {
		::std::string temp = string.substr(1,string.find_first_of('\n'));
		size = font.getTextLength(temp.c_str());
		temp = string.substr(string.find('\n'));
		int tempsize = font.getTextLength(temp.c_str());
		size = (tempsize > size?  tempsize : size );
		return size;
	}else if ( lines > 2) {
		size_t pos1 = string.find_first_of('\n');
		size_t pos2;
		::std::string temp = string.substr(1,pos1);
		size = font.getTextLength(temp.c_str());
		for (int i = 1; i <=lines; i++) {
			pos2 = string.find_first_of('\n',pos1);
			::std::string temp = string.substr(pos1,pos2);
			int tempsize = font.getTextLength(temp.c_str());
			size = (tempsize > size?  tempsize : size );
			pos1=pos2;
		}
		return size;
	}

}



void Util::limitPrintf(char * buffer, int size, const char * format, va_list args){

    vsnprintf(buffer, size, format, args);

}



void Util::showError(const CBitmap & screen, const Exception::CBase & exception, const string & info){
    screen.BlitFromScreen(0, 0);
    CBitmap error(screen.getWidth() - 100, screen.getHeight() - 100);
	error.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);

    error.fill(Colors::darken(Colors::makeColor(160, 0, 0), 3));
    error.border(1, 2, Colors::makeColor(240, 0, 0));
	//CResource::getDefaultFont()->printf( 400, 480 - CResource::getDefaultFont()->getHeight() * 5 / 2 - CResource::getDefaultFont()->getHeight(), tempcolor2, background, "SGF Version %s", 0, Global::getVersionString().c_str());

	const CFont * font = CResource::getDefaultFont();//getFont(string(Global::DEFAULT_FONT), 17, 17);
    //int y = 10;
    std::ostringstream out;
    out << info;
    out << " " << exception.getTrace();
	 Debug::debug(1) << out.str() << endl;

    CBitmap::transBlender(0, 0, 0, 220);
    error.translucent().draw(50, 50, screen);
	error.updateTexture();
	error.Blit();
    //font->printf( 10,10,  Colors::makeColor(240, 240, 240),screen,out.str(), 0);
    font->printfWrap(10, 10, Colors::makeColor(240, 240, 240), screen, error.getWidth() - 20, out.str(), 0);

	screen.BlitToScreen();
}

void Util::showError(const Exception::CBase & exception, const string & info){
    CBitmap screen(CConfiguration::screenWidth.getInteger(),CConfiguration::screenHeight.getInteger());

    showError(screen, exception, info);
}

int  Util::countChar(string s, char c){
  int count = 0;
  for (unsigned int i = 0; i < s.size(); i++)
    if (s[i] == c) count++;

  return count;
}


void Util::popup(const CFont & font, const string & message ){
	// verificar quantas linhas tem a mensagen
	int linhas = countChar(message, '\n');
	if (linhas ==0) linhas =1;
	const CBitmap & work = *CBitmap::_my_state->Screen[0];
	int fontsize = font.getHeight();
    int length = messageSize( font, message ) + 20;
    // Bitmap area( *Bitmap::Screen, GFX_X / 2 - length / 2, 220, length, font.getHeight() * 3 );
	CBitmap area( work, CConfiguration::screenWidth.getInteger() / 2 - length / 2, 220, length, ((fontsize+(fontsize/1.5)) * (linhas)) );
    CBitmap::transBlender( 0, 0, 0, 128 );
	// area.drawingMode( Bitmap::MODE_TRANS );
    area.translucent().rectangleFill( 0, 0, area.getWidth(), area.getHeight(), Colors::makeColor( 64, 0, 0 ) );
    // area.drawingMode( Bitmap::MODE_SOLID );
    int color = Colors::makeColor( 255, 255, 255 );
    area.polygon().rectangle( 0, 0, area.getWidth() - 1, area.getHeight() - 1, color );
    //font.printf( 10, area.getHeight() / 2, Colors::makeColor( 255, 255, 255 ), area, message, 0 );
    font.printfWrap(10, fontsize, Colors::makeColor(240, 240, 240), area, area.getWidth() - 5, message, 0);

	work.BlitToScreen();
}

/** @fn Util::niceSize(unsigned long size)
@brief Metodo que retorna o numero de bytes numa forma legivel para humanos
@param size: quantidade de bytes
@return string contendo o nr de bytes numa forma legivel
**/
string Util::niceSize(unsigned long size){
    const char sizes[] = {'b', 'k', 'm', 'g', 't'};
    double real = size;
    for (unsigned int i = 0; i < sizeof(sizes) / sizeof(const char); i++){
        if (real > 1024){
            real /= 1024.0;
        } else {
            ostringstream in;
            in << real << sizes[i];
            return in.str();
        }
    }
    ostringstream in;
    in << real << "t";
    return in.str();
}

string  Util::toNumericalString( SGF_Byte number )
{

     ostringstream oss ;

     oss.precision(Util::DigitOutputPrecision ) ;

     string res ;

    oss << static_cast<Uint16>( number ) ;
     res = oss.str() ;

 //debug
     if ( oss.fail() )
        throw CGeneralError( "Conversion error in method "
             "SGF_Byte -> string.",__FUNCTION__,__LINE__ ) ;


    return ( res ) ;

}

string  Util::toString(SGF_Dword value, bool bitField )
 {

     if ( bitField )
         return toString(
             static_cast<unsigned long >( value ), true ) ;

     ostringstream oss ;

     oss.precision(Util::DigitOutputPrecision ) ;

     string res ;

     oss << value ;
     res = oss.str() ;


     if ( oss.fail() )
         throw CGeneralError( "Conversion error  "
             "Uint32 -> string.",__FUNCTION__,__LINE__ ) ;



     return ( res ) ;

 }

string  Util::toHexString( unsigned long value, bool prefix,
    SGF_Byte minDigits )
 {

     string res ;

     /*

     bool inverted = false ;

     if ( value < 0 )
     {
         value = - value ;
         inverted = true ;
     }

     */

     while ( value )
     {
         res += Util::HexDigits[ value % 16 ] ;
         value /= 16 ;
     }

     while ( res.size() < minDigits )
         res += "0" ;

     return /* ( inverted ? string( "-" ) : string( "" ) ) + */
         ( prefix ? "0x" : "" ) + Util::reverse( res ) ;

 }

string  Util::reverse( const string & source )
 {

     string::size_type count = source.size() ;

     if ( count == 0 )
         return "" ;

     string result ;

     do
     {
         count-- ;
         result += source[count] ;

     }
     while ( count > 0 ) ;

     return result ;

 }

string  Util::formatStringList( const list<string> & stringList,
     bool surroundByTicks,SGF_Byte indentationLevel )
 {

     return Util::formatStringList( stringList, Util::CTextDisplayable::GetOutputFormat(),
         surroundByTicks, indentationLevel ) ;

 }



 string  Util::formatStringList( const list<string> & stringList,
     Util::CTextDisplayable::TextOutputFormat targetFormat,
     bool surroundByTicks,SGF_Byte indentationLevel )
 {

     if ( stringList.empty() )
         return "(empty list)" ;

     string res ;

     if ( targetFormat == Util::CTextDisplayable::html )
     {

         res = "<ul>" ;

         for ( list<string>::const_iterator it = stringList.begin();
                 it != stringList.end(); it++ )
             if ( surroundByTicks )
                 res += "<li>'" + ( *it ) + "'</li>" ;
            else
                 res += "<li>" + ( *it ) + "</li>" ;

         res += "</ul>" ;

     }
     else
     {

         // Raw text:

         res = '\n' ;

         string prefix ;

         // Two space offset for each indentation level:
         for ( SGF_Byte i = 0; i < indentationLevel; i++ )
             prefix += "  " ;

         switch ( indentationLevel )
         {

             case 1:
                 prefix += '-' ;
                break ;

             case 2:
                 prefix += '*' ;
                 break ;

             case 3:
                 prefix += '.' ;
                 break ;

             case 4:
                 prefix += '+' ;
                 break ;

             default:
                 prefix += '-' ;
                 break ;

         }

         prefix += " " ;

         for ( list<string>::const_iterator it = stringList.begin();
                 it != stringList.end(); it++ )
             if ( surroundByTicks )
                 res += prefix + "'" + ( *it ) + "'\n" ;
             else
                 res += prefix + ( *it ) + '\n' ;

     }

     return res ;

 }

 string Util::join(const vector<string> & list, const string & middle){
    ostringstream out;

    bool first = true;
    for (vector<string>::const_iterator it = list.begin(); it != list.end(); it++){
        if (!first){
            out << middle;
        }

        out << *it;
        first = false;
    }

    return out.str();
}


 // Output format defaults to raw text.
 Util::CTextDisplayable::TextOutputFormat Util::CTextDisplayable::_OutputFormat = rawText ;



 const string Util::CTextDisplayable::ToString(
     list<CTextDisplayable*> displayables, VerbosityLevels level )
 {

     string res = "Description of TextDisplayable list is: " ;

     list<string> descriptionList ;

     for( list<CTextDisplayable*>::const_iterator it = displayables.begin();
             it != displayables.end(); it++ )
         descriptionList.push_back( (*it)->toString( level ) ) ;

     return res + formatStringList( descriptionList ) ;

 }



 Util::CTextDisplayable::TextOutputFormat Util::CTextDisplayable::GetOutputFormat()
 {

     return _OutputFormat ;

 }



 void Util::CTextDisplayable::SetOutputFormat( TextOutputFormat newOutputFormat )
 {

     _OutputFormat = newOutputFormat ;

 }



 std::ostream & operator << ( std::ostream & os,
     const Util::CTextDisplayable & textDisplayable )
 {

     return os << textDisplayable.toString( high ) ;

 }
 } //end SGF
