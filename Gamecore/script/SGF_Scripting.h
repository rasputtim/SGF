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



#ifndef _S_G_F_SCRIPTING_h
#define _S_G_F_SCRIPTING_h

#include "../SGF_Config.h"

#ifdef SGF_SCRIPTING
#include <string>
#include "../util/SGF_FileSystem.h"
using namespace std;
namespace SGF {

namespace Script {

/**
 * \class CEngine
 *
 * \ingroup SGF_Scripting
 * 
 * \brief Classe Base para  Script com outras linguagens interppretadas (Perl, Ruby, Çua, etc)
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de abril de 2012
 */
class SGE_API CEngine{
    private:
        /* there is one global engine in existence at any time */
        static CEngine * theEngine;
    public:
        CEngine();

        static CEngine * getEngine();

        virtual void init() = 0;
        //virtual void shutdown() = 0;
        virtual void tick() = 0;
        virtual ~CEngine();
    };
    

    CEngine * getEngine();
    /* name : name of the library to use (python, lua, ruby, etc)
     * path : path to script to load
     */
    void newEngine(const string name, const Filesystem::CRelativePath path);

    class SGE_API CNoSuchEngine: public std::exception {
    public:
        CNoSuchEngine(const string & s){
        }
    };


}

} //end SGF
#endif

#endif