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
#include "exceptions/SGF_NetException.h"
#include <string>
#include <sstream>

using namespace std;
namespace SGF {

namespace Exception{

CNetworkException::~CNetworkException() throw (){
}
    
CMessageEndException::CMessageEndException(){
}
	
CInvalidPortException::CInvalidPortException( int port, const string message ):
CNetworkException(""){
	::std::ostringstream num;
	num << port;
	num << ". ";
	num << message;
	this->setMessage( "Invalid port " + num.str() );
}

}
} //end SGF