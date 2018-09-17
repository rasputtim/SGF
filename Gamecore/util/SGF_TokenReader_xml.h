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
#ifndef _S_G_F_tokenreader_xml_h
#define _S_G_F_tokenreader_xml_h

#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <malloc.h>
#include "../SGF_Config.h"
#include "../../ExternalLibs/expat-2.1.0/lib/expat.h"
#include "SGF_Token.h"
#include "../exceptions/all.h"
namespace SGF {

class Token;
/**
 * \class CTokenReaderXML
 *
 * \ingroup SGF_Util
 * 
 * \brief Lê um arquivo XML e transforma en Tokens
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CTokenReaderXML{
public:
	CTokenReaderXML( const string & s );
	CTokenReaderXML( const char * filename );
	virtual Token * readToken() throw (CTokenException);
	virtual ~CTokenReaderXML();
    
	
protected:
        
		static void Wrap_charData (void *userData, const XML_Char *s, int len);
		static void Wrap_startElement(void *userData, const char *name, const char **atts);
		static void Wrap_endElement(void *userData, const char *name);
        void charData (void *userData, const XML_Char *s, int len);
		void startElement(void *userData, const char *name, const char **atts);
		void endElement(void *userData, const char *name);

		//ifstream ifile;
        string myfile;
        vector< Token * > my_tokens;
        vector< Token * > xmltoken_stack;
        
		FILE * in;
		Token * cur_token;
	    Token * first;
	
};
} //end SGF
#endif
