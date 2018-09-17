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


#include <exception>
#include <string>
#include "exceptions/SGF_TokenException.h"
	
using namespace std;
namespace SGF {
CTokenException::CTokenException(const string & file, int line, const string reason):
Exception::CBase(file, line),
reason(reason){
}

CTokenException::CTokenException(const CTokenException & copy):
Exception::CBase(copy),
reason(copy.reason){
}
 
CTokenException::CTokenException(const Exception::CBase & copy):
Exception::CBase(copy),
reason("unknown"){
}

Exception::CBase * CTokenException::copy() const {
    return new CTokenException(*this);
}

CTokenException::~CTokenException() throw() {
}
} //end SGF