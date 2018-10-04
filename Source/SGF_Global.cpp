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


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
//#include <iostream>
//#include <sstream>
//#include <streambuf>
//#include <fstream>
#include <stdlib.h>
#include "SGF_Global.h"
#include "util/SGF_Debug.h"

#if defined _WIN32
# include <windows.h>
#endif

using namespace std;


static int major_version = 1;
static int minor_version = 2;
static int micro_version = 0;

const int SGF::Global::BUILD_NUMBER = major_version * 1000 + minor_version * 100 + micro_version;


 

const int ALLIANCE_NONE = 0;
const int ALLIANCE_PLAYER = 1;
const int ALLIANCE_ENEMY = 2;
const int ALLIANCE_FREE_FOR_ALL = 1000;

#if defined(WINDOWS)
static string Fontcaminho= string(DEF_FONT_PATH)+string("arial.ttf");
#elif defined(ANDROID)
//todo: treat fonts in the Android: https://stackoverflow.com/questions/38126207/how-do-i-include-a-font-file-ttf-in-my-android-ndk-project
static string Fontcaminho= string(DEF_FONT_PATH)+string("truetype/msttcorefonts/arial.ttf");
#elif defined(LINUX)
static string Fontcaminho= string(DEF_FONT_PATH)+string("truetype/msttcorefonts/arial.ttf");
#endif
const char * SGF::Global::DEFAULT_FONT = Fontcaminho.c_str();//(string(DEF_FONT_PATH) + "arial.ttf").c_str();
const SGF::Filesystem::CAbsolutePath SGF::Global::DEFAULT_FONT2 = SGF::Filesystem::CAbsolutePath(Fontcaminho);


volatile unsigned int SGF::Global::second_counter=0;

// contadores incrementados a cada millisegundo
volatile unsigned int SGF::Global::speed_counter=0;

namespace SGF{
namespace Global{
int do_shutdown = 0;
int FRAMES_PER_SECOND = 40;
int TICS_PER_SECOND = FRAMES_PER_SECOND;
const int SKIP_TICKS = 1000 /TICS_PER_SECOND;





bool shutdown(){
    return do_shutdown > 0;
}

int getVersion(int major, int minor, int micro){
    return major * 1000 + minor * 100 + micro;
}

int getVersion(){
    return getVersion(major_version, minor_version, micro_version);
}





string getVersionString(){
    ostringstream str;
    str << major_version << "." << minor_version << "." << micro_version;
    return str.str();
}


/*void showTitleScreen(){
    CBitmap s( Global::titleScreen() );
    s.BlitToScreen();
}
*/
const string titleScreen(){
	Filesystem::CRelativePath titleScreenPath("/menu/background.png");
	if (titleScreenPath.exist()){
		return  titleScreenPath.completePath();
	}else return "";
}

/* just some random number I picked out of thin air */
const unsigned int MagicId = 0x0dff2110;

FILE *pLogFile=NULL;
Uint32 nGameTicks;

void InitLogFile()
{
   // usado no sistema de printmessage
   #ifdef _XBOX
		pLogFile=fopen("d:\\log.txt","w");
   #else
	pLogFile=fopen("log.txt","w");
   //code to redirect cout to file
   #endif
   fclose(pLogFile);

}

void PrintConsole(char *strText)
{
	//CON_Out(Global::mMainConsole,strText);

}

//Prints a formated string to the log file and to the console
void PrintMessage(char *str,...)
{
  char string[255];                  // Temporary string

  va_list ap;                // Pointer To List Of Arguments
  va_start(ap, str);         // Parses The String For Variables
  std::vsprintf(string, str, ap); // Converts Symbols To Actual Numbers
  va_end(ap);

#ifdef _XBOX
 // pLogFile=fopen("d:\\log.txt","a+");
#else
  pLogFile=fopen("log.txt","a+");
#endif

 // fprintf(pLogFile,string);
 // fprintf(pLogFile,"\n");
 // fclose(pLogFile);

//PrintConsole(string);

  //printf(string);
  //printf("\n");

}


//extern ConsoleInformation *mMainConsole;

void ResetGameTimer()
{
    nGameTicks=0;
}

int GetGameTicks()
{
    return nGameTicks;
}

void UpdateTimer()
{
    nGameTicks++;
}
/*
void Command_Handler(ConsoleInformation *console, char* command)
{

}
*/



void ExcecaoInesperada()
{
Debug::debug(Debug::error) << "Encerrando por na tratar uma excessao inesperada\n";
exit(1);
}
void TrataFalhaNoNew() {
Debug::debug(Debug::error) << "Falta de Memoria";
Debug::debug(Debug::error) << "Fim...Saindo!!!" << endl;
//pode tentar liberar memoria aqui se for o caso e depois retornar
//system("pause");
 //throw bad_alloc( );
//   return;

exit(1);

}
void Encerra() {
Debug::debug(Debug::error) << "Encerrando por um motivo inesperado\n";
exit(1);
}
// retorna 0 se sucesso
// retorna -1 se ocorreu erro


int InitExceptions() {
    //gerenciadores de excessoes padrao
	//set_unexpected(Global::ExcecaoInesperada); // trata excecao inesperada
    set_new_handler(Global::TrataFalhaNoNew); // Isto impede o lancamento da
                                              // excecao bad_alloc, na falha do new
    //set_terminate(Global::Encerra); // se ela existe, somente ela e executada
	return 0;
}

} //end GLOBAL
} //end SGF
