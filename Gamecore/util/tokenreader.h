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
#ifndef _SGF___tokenreader_h
#define _SGF___tokenreader_h

#include <fstream>
#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "../exceptions/SGF_TokenException.h"
#include "SGF_FileSystem.h"

using namespace ::std;

namespace SGF {
class Token;

class  SGE_API TokenReader{
public:

	TokenReader();
	// OldOnes
	TokenReader( const string & s );
	TokenReader( const char * filename );

	virtual Token * readToken() throw (CTokenException);
	//new ones
	virtual Token * readToken(const std::string & path);
    virtual Token * readToken(const char * path);
    virtual Token * readTokenFromString(const std::string & stuff);
    virtual Token * readTokenFromFile(const std::string & path);
    virtual Token * readTokenFromFile(Filesystem::File & file);

    virtual ~TokenReader();

	
protected:
        virtual void readTokens(Filesystem::File & stream);
 
        ifstream ifile;
        string myfile;
        vector< Token * > my_tokens;
};
} //end SGF
#endif
