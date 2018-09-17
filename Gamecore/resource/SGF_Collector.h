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

#ifndef _collector_h
#define _collector_h
#include "../SGF_Config.h"
#include "all.h"
#include "../graphics/all.h"
#include "../util/SGF_FileSystem.h"
//#include "../util/all.h"
#include <iostream>
namespace SGF{

class CResource;
class CFontList;
/**
 * \class CCollector
 *
 * \ingroup SGF_Resources
 * 
 * \brief Esta Classe chama o destrutor de outras classes estáticas
 *
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CCollector{
public:
    friend class CGame;
	friend class CGameControl;
protected:
	CCollector();
	~CCollector();
private:
    CResource * my_resource;
	CFontList * my_fontlist;
};
} //end SGF
#endif
