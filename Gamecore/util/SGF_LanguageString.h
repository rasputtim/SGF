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
#ifndef _S_G_F_language_string_h
#define _S_G_F_language_string_h

#include <string>
#include <map>
#include "../SGF_Config.h"

using namespace std;
namespace SGF {

/**
 * \class CLanguageString
 *
 * \ingroup SGF_Util
 * 
 * \brief ...
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CLanguageString: public string {
public:
	//!CONSTRUTORES
    CLanguageString();
    CLanguageString(const char * stuff);
    CLanguageString(const string & stuff);
    CLanguageString(const string & stuff, const string & language);
    CLanguageString(const CLanguageString & language);  //!construtor de cópia
    CLanguageString & operator=(const CLanguageString & obj); 

    static const string defaultLanguage(){
        return "English";
    }

    const string currentLanguage() const ;

    /* add a new language translation */
    void add(const string & stuff, const string & language);

    /* adds with the default language */
    void add(const string & stuff);

    const string & get() const;

	inline const map<string, string> & getLanguages() const {
        return languages;
    }
protected:
    map<string, string> languages;  //mapa de string por linguagem
};
} //endSGF
#endif
