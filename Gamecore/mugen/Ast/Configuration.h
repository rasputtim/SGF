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
#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <list>
#include <stdio.h>
#include "Section.h"

using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CConfiguration {
public: // constructors and destructors
	CConfiguration() {
	}
	~CConfiguration(){
			
            for (list<CSection*>::iterator section_it = sections.begin(); section_it != sections.end(); section_it++){
                delete (*section_it);
            }
        
	}

    friend class CAstManager;
	list<CSection *> * getSections() { return &sections; }


	void setSections(list<CSection *> *address){
		list<CSection *> *temp= &sections;
		for (list<CSection*>::iterator section_it = sections.begin(); section_it != sections.end(); section_it++){
                delete (*section_it);
            }
		sections=*address;
		//delete temp;
	}

	 bool operator!=(const CConfiguration & him) const {
        return !(*this == him);
    }
    bool operator==(const CConfiguration & him) const {
        
		//same object
        if (&sections ==  &him.sections ){
            return true;
        }

        list<CSection*>::const_iterator my_it = sections.begin();
        list<CSection*>::const_iterator him_it = him.sections.begin();
        while (true){
            if (my_it == sections.end()){
                break;
            }

            if (him_it == him.sections.end()){
                break;
            }

            const CSection * mine = *my_it;
            const CSection * him = *him_it;
            if (*mine != *him){
                return false;
            }

            my_it++;
            him_it++;
        }

        return my_it == sections.end() && him_it == him.sections.end();
    }


	void debugExplain() {
		for (list<CSection *>::iterator iter = sections.begin();
			iter != sections.end();
			iter++) {
			(*iter)->debugExplain();
		}
	}

Token * serialize() const {
        return NULL; //serialize(sections);
}

    static Token * serialize(list<CSection*> & sections){
        Token * token = new Token();
        *token << "mugen";
        *(token->newToken()) << "version" << CElement::SERIAL_VERSION;
        for (list<CSection*>::const_iterator section_it = sections.begin(); section_it != sections.end(); section_it++){
            CSection * section = *section_it;
            *token << section->serialize();
        }
        return token;
    }

    static int lowerCase( int c ){ return tolower(c); }

    string downcase(string str){
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }
	string downcase(string str) const{
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }
    CSection * findSection(const string & find){
        for (list<CSection*>::iterator section_it = sections.begin(); section_it != sections.end(); section_it++){
            CSection * section = *section_it;
            if (downcase(section->getName()) == downcase(find)){
                return section;
            }
        }
        throw CException("Could not find section " + find);
    }

	 CSection * findSection(const string & find) const {
       
            for (list<CSection*>::const_iterator section_it = sections.begin(); section_it != sections.end(); section_it++){
                CSection * section = *section_it;
                if (downcase(section->getName()) == downcase(find)){
                    return section;
                }
            }
        
        throw CException("Could not find section '" + find + "'");
    }
    static void checkVersion(Token * token){
        const Token * version = token->findToken("mugen/version");
        if (version != NULL){
            int what;
            version->view() >> what;
            if (what != CElement::SERIAL_VERSION){
                throw CException("Mistmatch between serial versions");
            }
        } else {
            throw CException("No version specified in the serialized stream");
        }
    }

    static list<CSection*> * deserialize(Token * token){
        checkVersion(token);
        ::std::ostringstream find;
        find << "mugen/" << CElement::SERIAL_SECTION_LIST;
        vector<const Token*> tokens = token->findTokens(find.str());
        list<CSection*> * out = new list<CSection*>();
        for (vector<const Token*>::iterator it = tokens.begin(); it != tokens.end(); it++){
            out->push_back(CSection::deserialize(*it));
        }

        return out;
    }


private: // data

	list<CSection *> sections;
};

} // end AST
}//end SGF

#endif
