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


class Global{
    
static int major_version;
static int minor_version;
static int micro_version;
static int do_shutdown;
public:    
//contador de segundos
static volatile unsigned int second_counter;
static volatile unsigned int speed_counter;

static const char * DEFAULT_FONT;
static const int BUILD_NUMBER;
static const Filesystem::CAbsolutePath DEFAULT_FONT2;


static const unsigned int MagicId;

static int TICS_PER_SECOND;
static int FRAMES_PER_SECOND;
static const int SKIP_TICKS;
static Uint32 nGameTicks;
static FILE * pLogFile;
static const double LOGIC_MULTIPLIER;



static int getVersion();

/* Turn some major.minor.micro into a single version number for comparisons */
static int getVersion(int major, int minor, int micro);


static string getVersionString();
static bool shutdown();
static const string titleScreen();
static void InitLogFile();
static void PrintMessage(char *str,...);
static void PrintConsole(char *strText);
static void ResetGameTimer();
static int GetGameTicks();
static void UpdateTimer();

/*
objetivo:    Função utilizada para settar variáveis de ambiente do sistema operacional
parâmetros:  name = nome da variável a set settada
             value = valor da variável
Comentários: Esta função funciona independentemente do sistema opracional utilizado for linux ou windows
*/
static void ExcecaoInesperada();
static int InitExceptions();
static void Encerra();

static void TrataFalhaNoNew();
// retorna 0 se sucesso
// retorna -1 se ocorreu erro
//int InitGettext();
//void Command_Handler(ConsoleInformation *console, char* command);
//void InitApp();
//void CloseGame();
//int my_setenv (const char * name, const char * value);
//static void showTitleScreen();


};
} // end sgf
#endif
