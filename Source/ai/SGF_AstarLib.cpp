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

#include "ai/SGF_AstarLib.h"

//====CaStarData===============================
namespace SGF {
CAStarData::CAStarData():
Fcost(0),

openX(0),
openY(0)
{};

CAStarData::CAStarData( const CAStarData & b ){
	this->Fcost = b.Fcost;
	this->openX = b.openX;
	this->openY = b.openY;
}

CAStarData & CAStarData::operator=( const CAStarData &copy ){
    // Check for self-assignment!
	//Debug::debug(Debug::error,__FUNCTION__) << " CAstManager::Operator = copy // BEGIN" << endl;
	if (this == &copy)      // Same object?
      return *this;
	this->Fcost = copy.Fcost;
	this->openX = copy.openX;
	this->openY = copy.openY;

}

bool CAStarData::operator==(const CAStarData & who) const {
    return who == *this;
}

bool CAStarData::operator==(unsigned int value) const {
	return(Fcost==0) && (openX==0) && (openY==0);
}
bool CAStarData::operator!=(unsigned int value) const {
	return (Fcost!=0) || (openX!=0) || (openY!=0);
}

CAStarData::~CAStarData(){
	//cout <<"myclass destroyed\n";
}

} //end SGF
