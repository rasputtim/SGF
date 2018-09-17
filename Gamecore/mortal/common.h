/***************************************************************************
                          common.h  -  description
                             -------------------
    begin                : Fri Aug 24 2001
    copyright            : (C) 2001 by upi
    email                : upi@apocalypse.rulez.org
 ***************************************************************************/

#ifndef ___COMMON_H
#define ___COMMON_H

#include "SGF.h"

#ifndef _SDL_types_h
#include "../../ExternalLibs/SDL2-2.0.3/include/SDL_types.h"

#endif

struct SDL_Surface;
#define MAXPLAYERS 4
#define VERSION  "0.7"
#define PACKAGE  "OPenMortal"
#ifdef _WIN32

#undef DATADIR                // GRRR.. windows keyword...
#include <windows.h>
#define DATADIR "C:\\Projetos\\c++\\GameEngine\\OpenMortal\\Debug\\bin\\data"

#endif
void debug( const char* format, ... );
#ifndef ABS
#define ABS(A) ( (A>=0) ? (A) : -(A) )
#endif
#ifndef MAX
#define MAX(A,B) ( (A) > (B) ? (A) : (B) )
#endif
#ifndef MIN
#define MIN(A,B) ( (A) < (B) ? (A) : (B) )
#endif

class CMortalGameControl;
class Backend;

void DoMenu(CMortalGameControl &game);
void GameOver(CMortalGameControl &game, int a_iPlayerWon );
void DoDemos(CMortalGameControl &game);
void DoOnlineChat(CMortalGameControl &game);
bool Connect(CMortalGameControl &game, const char* a_pcHostname );

const char* Translate( const char* a_pcText );
const char* TranslateUTF8( const char* a_pcText );


extern Uint32 C_BLACK;
extern Uint32 C_BLUE;
extern Uint32 C_GREEN;
extern Uint32 C_CYAN;

extern Uint32 C_RED;
extern Uint32 C_MAGENTA;
extern Uint32 C_ORANGE;
extern Uint32 C_LIGHTGRAY;

extern Uint32 C_DARKGRAY;
extern Uint32 C_LIGHTBLUE;
extern Uint32 C_LIGHTGREEN;
extern Uint32 C_LIGHTCYAN;

extern Uint32 C_LIGHTRED;
extern Uint32 C_LIGHTMAGENTA;
extern Uint32 C_YELLOW;
extern Uint32 C_WHITE;


enum TMortalEventEnum
{
	Me_NOTHING,
	Me_QUIT,
	Me_MENU,
	Me_SKIP,
	Me_PLAYERKEYDOWN,
	Me_PLAYERKEYUP,
	Me_SELECT,
};

enum TMortalChatEnum
{
	Ch_PGUP,
	Ch_PGDN,
	Ch_ENTER,
	Ch_TAB,
	Ch_QUIT,
	Ch_RIGHT,
	Ch_LEFT,
	Ch_DEL,
};
enum TMortalKeysEnum
{
	Mk_MIN      = 0,
	Mk_UP		= 0,
	Mk_DOWN		= 1,
	Mk_LEFT		= 2,
	Mk_RIGHT	= 3,
	Mk_BLOCK	= 4,
	Mk_LPUNCH	= 5,
	Mk_HPUNCH	= 6,
	Mk_LKICK	= 7,
	Mk_HKICK	= 8,
	MK_MAX      = 8,
};

enum GFX_Constants {
	AlignHCenter	= 1,
	AlignVCenter	= 2,
	AlignCenter		= 3,
	UseTilde		= 4,
	UseShadow		= 8,
};

#endif
