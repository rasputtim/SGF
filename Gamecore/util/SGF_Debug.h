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
#ifndef _SGF__DEBUG_H_
#define _SGF__DEBUG_H_


#include <string>
#include <map>
#include <vector>
#include <string>
#include <ostream>
#include "../SGF_Config.h"
#include "SGF_DebugDefs.h"


using namespace std;
namespace SGF {
namespace Debug
{

class CLog
{
public:
    CLog();
    ~CLog();

    bool setFilename(string fn, string contex);

    bool print(string txt);
private:
    string
            filename;
};


void setFilename(string file);


stream_type & debug(int i, const string & context = "SGF");

enum Type {
    Default,
    File
};

void setDebugMethod(Type t);

struct DebugModule{
DebugModule():bitmap(0),
font(0),
gui(0),
input(0),
compilers(0),
configuration(0),
parsers(0),
lists(0),
menu(0),
network(0),
resources(0),
objects(0),
exceptions(0),
environment(0),
filesystem(0),
sound(0),
console(0),
gameEngine(0),
sdlmanager(0),
xml(0),
gameObject(0),
gameStage(0),
gameStateMachine(0),
gameStory(0),
gameConfiguration(0),
heap(0),
math(0),
structures(0),
error(0)
{}

bool bitmap;
bool font;
bool gui;
bool input;
bool compilers;
bool configuration;
bool parsers;
bool lists;
bool menu;
bool network;
bool resources;
bool objects;
bool exceptions;
bool environment;
bool filesystem;
bool sound;
bool console;
bool gameEngine;
bool sdlmanager;
bool xml;
bool gameObject;
bool gameStage;
bool gameStateMachine;
bool gameStory;
bool gameConfiguration;
bool heap;
bool math;
bool structures;
bool error;
};

typedef enum {
MIN = 100,
error = MIN,
bitmap,
font,
gui,
input,
compilers,
configuration,
parsers,
lists,
menu,
network,
resources,
objects,
exceptions,
environment,
filesystem,
sound,
console,
gameEngine,
gameStage,
gameObject,
gameStateMachine,
gameStory,
gameConfiguration,
sdlmanager,
xml,
heap,
math,
structures,
MAX=structures
}Modules;

/** metodo que inicializa o debug no me?dulo especificado
* \parameter i: m?dulo do debug que se deseja habilitar
*/
void setDebug( Modules i );
/** m?todo que inicializa o debug no m?dulo especificado
* \parameter i: m?dulo do debug que se deseja habilitar
*/
void setDebug( int i );

/** m?todo que retorna se um m?dulo do debug est? habilitado ou n?o
* \parameter i: m?dulo do debug que se deseja verificar
* \return true: se o m?dulo est? ativo
* \return false: se o m?dulo est? inativo
*/
bool getDebug( Modules i );

/** m?todo que inicializa o debug em todos os m?dulos
*/
void setDebugAll();
/** m?todo que desabilita o debug em todos os m?dulos
*/
void resetDebug( int i );
void resetDebug( Modules i );
//void setDebug( int i, int b );
int getDebug();


}
} //end SGF
#endif
