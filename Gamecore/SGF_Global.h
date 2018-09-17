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




#ifndef __SGF_GLOBAL_H
#define __SGF_GLOBAL_H



#include "SGF_Config.h"


#include <ostream>
#include <string>
//#include "../ExternalLibs/SDL2-2.0.3/include/SDL_main.h"
#include "util/SGF_FileSystem.h"

#define STAMP __FILE__,__LINE__
#ifndef _XBOX
#define VER "Beta FSM"
#else
#define VER "XBOX Beta FSM"
#endif
#define OMTITLE "SGF Version "


using namespace std;

namespace SGF {
class MessageQueue;

/* put this in an enum */
extern const int ALLIANCE_NONE;
extern const int ALLIANCE_PLAYER;
extern const int ALLIANCE_ENEMY;
extern const int ALLIANCE_FREE_FOR_ALL;


namespace Global{
//contador de segundos
extern volatile unsigned int second_counter;
extern volatile unsigned int speed_counter;
extern const unsigned int MagicId;
extern const char * DEFAULT_FONT;
extern const int BUILD_NUMBER;
extern const Filesystem::CAbsolutePath DEFAULT_FONT2;

extern int TICS_PER_SECOND;
extern int FRAMES_PER_SECOND;
extern const int SKIP_TICKS;

const double LOGIC_MULTIPLIER = (double) 90 / (double) TICS_PER_SECOND;
int getVersion();

/* Turn some major.minor.micro into a single version number for comparisons */
int getVersion(int major, int minor, int micro);


string getVersionString();
bool shutdown();
void showTitleScreen();
const string titleScreen();
void InitLogFile();
void PrintMessage(char *str,...);
void PrintConsole(char *strText);
//void Command_Handler(ConsoleInformation *console, char* command);
void InitApp();
void CloseGame();
void ResetGameTimer();
int GetGameTicks();
void UpdateTimer();
/*
objetivo:    Função utilizada para settar variáveis de ambiente do sistema operacional
parâmetros:  name = nome da variável a set settada
             value = valor da variável
Comentários: Esta função funciona independentemente do sistema opracional utilizado for linux ou windows
*/
int my_setenv (const char * name, const char * value);
void ExcecaoInesperada();
void TrataFalhaNoNew();
void Encerra();
// retorna 0 se sucesso
// retorna -1 se ocorreu erro
int InitGettext();

int InitExceptions();

}
} // end sgf
#endif
