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
#ifndef _SGF_mod_h
#define _SGF_mod_h

#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "../util/SGF_Path.h"
#include "../exceptions/SGF_LoadException.h"

using namespace std;
namespace SGF {

namespace Level{
    class CLevelInfo;
}
class CBitmap;
class CInputSource;
/* encapsulates a configuration for a game */

/**
 * \class Mod
 *
 * \ingroup SGF_Game
 *
 * \brief Controla e gerencia os Mods
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API Mod{
public:
	Mod(const string & name, const Filesystem::CAbsolutePath & path)throw (CLoadException);


    const string & getMenu();
	/* use the heap */
    virtual CBitmap * createBitmap(const Filesystem::CRelativePath & path);

    /* use the stack */
    virtual CBitmap makeBitmap(const Filesystem::CRelativePath & path);


	virtual vector<Level::CLevelInfo> & getLevels();

    virtual ~Mod();
	//tODO
	//virtual Filesystem::CAbsolutePath selectPlayer(const string & message, const Level::CLevelInfo & info, int & remap, const CInputSource & source);

    /* tries to find files in the mod path first and then the regular
     * places next.
     */
    virtual Filesystem::CAbsolutePath find(const Filesystem::CRelativePath & path);


	static void loadMugenMod(const string & path);
    static void loadOpenborMod(const Filesystem::CAbsolutePath & path);

    static void loadMod(const string & path) throw (CLoadException, Exception::Filesystem::CNotFound);
    static Mod * getCurrentMod();
    static void loadDefaultMod();
protected:
	Mod();
	static void setMod(Mod * mod);
    vector<Level::CLevelInfo> levels;
    string menu;
	string name;
    static Mod * currentMod;
};


} //end SGF
#endif
