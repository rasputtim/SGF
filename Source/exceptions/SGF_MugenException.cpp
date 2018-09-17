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
#include <sstream>
#include "exceptions/SGF_MugenException.h"
#include "util/SGF_Debug.h"

using namespace std;
namespace SGF {
CMugenException::CMugenException():
Exception::CBase("", -1),
reason("unspecified"),
where("?"),
line(0){
}

CMugenException::CMugenException(const string & reason, const string & where, int line):
Exception::CBase("", line),
reason(reason),
where(where),
line(line){
	//Debug::CInformation::resetContext();
}
        
Exception::CBase * CMugenException::copy() const {
    return new CMugenException(reason, where, line);
}
        
const string CMugenException::getFullReason() const {
    ::std::ostringstream out;
    out << where << ":" << line << " " << reason;
    return out.str();
}
	
CMugenException::~CMugenException() throw() {
}


CReloadMugenException::CReloadMugenException(){
}

CReloadMugenException::~CReloadMugenException() throw(){
}
    
CMugenRuntimeException::CMugenRuntimeException(){
}

CMugenRuntimeException::CMugenRuntimeException(const string & reason, const string & where, int line):
CMugenException(reason, where, line){
}

CMugenNormalRuntimeException::CMugenNormalRuntimeException(){
}

CMugenNormalRuntimeException::CMugenNormalRuntimeException(const string & reason, const string & where, int line):
CMugenRuntimeException(reason, where, line){
}

CMugenFatalRuntimeException::CMugenFatalRuntimeException(){
}

CMugenFatalRuntimeException::CMugenFatalRuntimeException(const string & reason, const string & where, int line):
CMugenRuntimeException(reason, where, line){
}

} //end SGF