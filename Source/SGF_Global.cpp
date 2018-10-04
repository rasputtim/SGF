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






 

const int ALLIANCE_NONE = 0;
const int ALLIANCE_PLAYER = 1;
const int ALLIANCE_ENEMY = 2;
const int ALLIANCE_FREE_FOR_ALL = 1000;

#if defined(WINDOWS)
static string Fontcaminho= string(DEF_FONT_PATH)+string(WORKFONT);
#elif defined(ANDROID)
//todo: treat fonts in the Android: https://stackoverflow.com/questions/38126207/how-do-i-include-a-font-file-ttf-in-my-android-ndk-project
static string Fontcaminho= string(DEF_FONT_PATH)+string(WORKFONT);
#elif defined(LINUX)
static string Fontcaminho= string(DEF_FONT_PATH)+string(WORKFONT);
#endif


namespace SGF{
//class  Global{

int Global::major_version = 1;
int Global::minor_version = 2;
int Global::micro_version = 0;
const int Global::BUILD_NUMBER = major_version * 1000 + minor_version * 100 + micro_version;


const char * Global::DEFAULT_FONT = Fontcaminho.c_str();//(string(DEF_FONT_PATH) + "arial.ttf").c_str();
const Filesystem::CAbsolutePath Global::DEFAULT_FONT2 = Filesystem::CAbsolutePath(Fontcaminho);


volatile unsigned int Global::second_counter=0;

// contadores incrementados a cada millisegundo
volatile unsigned int Global::speed_counter=0;



int Global::do_shutdown = 0;
int Global::FRAMES_PER_SECOND = 40;
int Global::TICS_PER_SECOND = FRAMES_PER_SECOND;
const int Global::SKIP_TICKS = 1000 /TICS_PER_SECOND;
const double Global::LOGIC_MULTIPLIER = (double) 90 / (double) Global::TICS_PER_SECOND;


/* just some random number I picked out of thin air */
const unsigned int MagicId = 0x0dff2110;

FILE * Global::pLogFile=NULL;
Uint32 Global::nGameTicks=0;


bool Global::shutdown(){
    return do_shutdown > 0;
}

int Global::getVersion(int major, int minor, int micro){
    return major * 1000 + minor * 100 + micro;
}

int Global::getVersion(){
    return getVersion(major_version, minor_version, micro_version);
}





string Global::getVersionString(){
    ostringstream str;
    str << major_version << "." << minor_version << "." << micro_version;
    return str.str();
}


/*void showTitleScreen(){
    CBitmap s( Global::titleScreen() );
    s.BlitToScreen();
}
*/
const string Global::titleScreen(){
	Filesystem::CRelativePath titleScreenPath("/menu/background.png");
	if (titleScreenPath.exist()){
		return  titleScreenPath.completePath();
	}else return "";
}





void Global::InitLogFile()
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

void Global::PrintConsole(char *strText)
{
	//CON_Out(Global::mMainConsole,strText);

}

//Prints a formated string to the log file and to the console
void Global::PrintMessage(char *str,...)
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

void Global::ResetGameTimer()
{
    nGameTicks=0;
}

int Global::GetGameTicks()
{
    return nGameTicks;
}

void Global::UpdateTimer()
{
    nGameTicks++;
}
/*
void Command_Handler(ConsoleInformation *console, char* command)
{

}
*/



void Global::ExcecaoInesperada()
{
Debug::debug(Debug::error) << "Encerrando por na tratar uma excessao inesperada\n";
exit(1);
}

void Global::TrataFalhaNoNew() {
Debug::debug(Debug::error) << "Falta de Memoria";
Debug::debug(Debug::error) << "Fim...Saindo!!!" << endl;
//pode tentar liberar memoria aqui se for o caso e depois retornar
//system("pause");
 //throw bad_alloc( );
//   return;

exit(1);

}
void Global::Encerra() {
Debug::debug(Debug::error) << "Encerrando por um motivo inesperado\n";
exit(1);
}
// retorna 0 se sucesso
// retorna -1 se ocorreu erro


int Global::InitExceptions() {
    //gerenciadores de excessoes padrao
	//set_unexpected(Global::ExcecaoInesperada); // trata excecao inesperada
    set_new_handler(Global::TrataFalhaNoNew); // Isto impede o lancamento da
                                              // excecao bad_alloc, na falha do new
    //set_terminate(Global::Encerra); // se ela existe, somente ela e executada
	return 0;
}

//} //end GLOBAL
} //end SGF
