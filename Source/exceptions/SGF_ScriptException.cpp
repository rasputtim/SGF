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
#include "exceptions/SGF_ScriptException.h"
#include "util/SGF_Debug.h"

using namespace std;
namespace SGF {
namespace Exception {
CScriptException::CScriptException():
Exception::CBase("", -1),
_my_reason("unspecified"),
_my_file("?"),
_my_function("?"),
_my_line(0){
}

CScriptException::CScriptException( const string & file, const string function, int line, const string & reason):
Exception::CBase("", line),
_my_reason(reason),
_my_file(file),
_my_function(function),
_my_line(line){
	//Debug::CInformation::resetContext();
}
        
Exception::CBase * CScriptException::copy() const {
    return new CScriptException( _my_file,_my_function ,_my_line, _my_reason);
}
        
const string CScriptException::getFullReason() const {
    ::std::ostringstream out;
    out << _my_file<<": "<<"[ " <<_my_function << "- line: " << _my_line << "] : " << _my_reason;
    return out.str();
}
	
CScriptException::~CScriptException() throw() {
}


} //end Exception
} //end SGF