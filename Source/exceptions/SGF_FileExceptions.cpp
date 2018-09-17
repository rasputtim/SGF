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

#include <string>
#include "exceptions/SGF_FileExceptions.h"

using namespace std;
namespace SGF {
namespace Exception{
namespace Filesystem {

CException::CException(const string & where, int line, const string & file):
Exception::CBase(where, line),
reason(file){
}

CException::CException(const string & where, int line, const Exception::CBase & nested, const string & file):
Exception::CBase(where, line, nested),
reason(file){
}

CException::CException(const CException & copy):
Exception::CBase(copy),
reason(copy.reason){
}

CException::~CException() throw (){
}

const string CException::getReason() const {
    return reason;
}

CNotFound::CNotFound(const string & where, int line, const string & file):
CException(where, line, file + string(" was not found")){
}

CNotFound::CNotFound(const string & where, int line, const Exception::CBase & nested, const string & file):
CException(where, line, nested, file + string(" was not found")){
}

CNotFound::CNotFound(const CNotFound & copy):
CException(copy){
}

CNotFound::~CNotFound() throw (){
}


} //end filesystem
} // end Exceptions
} //end SGF