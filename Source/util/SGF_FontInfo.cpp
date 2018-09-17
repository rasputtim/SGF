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

#include "util/SGF_FontInfo.h"
#include "util/SGF_FileSystem.h"
#include "util/SGF_FontSystem.h"
#include "configuration/SGF_Configuration.h"
#include "exceptions/all.h"

namespace SGF {


CFontInfo::CFontInfo(fonttype typeOfFont):
typeOfFont(typeOfFont){
}

CFontInfo::~CFontInfo(){
}

static bool menuFontAvailable(){
    return CConfiguration::getMenuFont_v2() != NULL;  //! v2
	
}

bool CRelativeFontInfo::operator==(const CFontInfo & who) const {
    return who == *this;
}

bool CRelativeFontInfo::operator==(const CAbsoluteFontInfo & who) const {
    return getName() == who.getName();
}

bool CRelativeFontInfo::operator==(const CRelativeFontInfo & who) const {
    return path == who.path;
}

bool CAbsoluteFontInfo::operator==(const CFontInfo & who) const {
    return who == *this;
}

bool CAbsoluteFontInfo::operator==(const CAbsoluteFontInfo & who) const {
    return path == who.path;
}

bool CAbsoluteFontInfo::operator==(const CRelativeFontInfo & who) const {
    return getName() == who.getName();
}



} //end SGF