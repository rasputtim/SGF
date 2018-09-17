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

#include "script/SGF_Scripting.h"

#ifdef SGF_PERL_SCRIPTING
#include "script/SGF_Perl.h"
#endif

using namespace std;
namespace SGF {

namespace Script {

    CEngine * CEngine::theEngine = NULL;

    CEngine::CEngine(){
        if (theEngine != NULL){
            delete theEngine;
        }
        theEngine = this;
    }

    CEngine::~CEngine(){
    }

    CEngine * CEngine::getEngine(){
        return theEngine;
    }

    CEngine * getEngine(){
        return CEngine::getEngine();
    }

    /* sets the global engine */
    void newEngine(const string name, const Filesystem::CAbsolutePath path){
#ifdef SGF_PERL_SCRIPTING
        if (name == "perl"){
          //  new CPerlEngine(path.path());
            return;
        }
#endif
#ifdef SGF_PYTHON_SCRIPTING
        if (name == "python"){
            new PythonEngine(path);
            return;
        }
#endif
#ifdef SGF_RUBY_SCRIPTING
        if (name == "ruby"){
            new RubyEngine(path);
            return;
        }
#endif
 /*       if (name == "none"){
            new CNoEngine();
            return;
        }
        Degug::debug(Degug::error, __FUNCTION__) << "*Warning* no such engine '" << name << "' for path " << path.path() << endl;
        new CNoEngine();
        // throw NoSuchEngine(name); 
		*/
    }




}
} //end SGF