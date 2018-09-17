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

//#include "SGF_Global.h"

//#include <fstream>
//#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include "util/SGF_TokenReader_xml.h"
#include "../../ExternalLibs/expat-2.1.0/lib/expat.h"
#include "exceptions/all.h"
#include "util/SGF_Debug.h"

namespace SGF {

void *pObjCurToken=NULL;

using namespace std;


CTokenReaderXML::CTokenReaderXML( const char * file ):
    myfile ( string( file )),
    in (fopen (file, "r")),
    cur_token (NULL),
	first ( NULL)
	{
	Debug::debug(Debug::xml,__FUNCTION__) << "( const char * file ) // Constructor //=> File: " << file << endl;
	pObjCurToken = (CTokenReaderXML *) this;
    Debug::debug(Debug::xml,__FUNCTION__) << "( const char * file ) // Opened //=> File: " << file << endl;

}

CTokenReaderXML::CTokenReaderXML( const string & file ):
    myfile (file),
    in (fopen(file.c_str(), "r")),
    cur_token (NULL),
	first (NULL)
	{
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::CTokenReaderXML( const string * file ) // Constructor //=> File: " << file << endl;
	pObjCurToken = (CTokenReaderXML *) this;
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::CTokenReaderXML( const string * file ) // Opened //=> File: " << file << endl;
}

CTokenReaderXML::~CTokenReaderXML(){
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::~CTokenReaderXML // Destructor //" << endl;
	pObjCurToken = NULL;
	cur_token = NULL;
	first = NULL;
	/* ctokenreaderXML giveth, and tokenreader taketh */
	for ( vector< Token * >::iterator it = my_tokens.begin(); it != my_tokens.end(); it++ ){
		delete *it;
	}
Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::~CTokenReaderXML // Closed File //" << endl;

}


Token * CTokenReaderXML::readToken() throw( CTokenException ){
    Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::readToken() // BEGIN //" << endl;

	char buf[BUFSIZ];

	if ( !in ){
            throw CTokenException(__FILE__, __LINE__, string("Could not open ") + myfile );
        }

  XML_Parser parser = XML_ParserCreate(NULL);

  int done;
  int finished;
  int depth = 0;
  bool result;
  //sets the user data that gets passed to handlers.
  XML_SetUserData(parser, &depth);
  //The XML_Set*Handler calls are where the behavior of the parser is defined. In this case, we only care about the elements themselves, so we only define and install element handlers. There is a corresponding call for each class of XML token
  XML_SetElementHandler(parser, Wrap_startElement, Wrap_endElement);
  //Set the text handler.
  XML_SetCharacterDataHandler(parser, Wrap_charData);

  done = 0;
  finished = 0;

   do {
      size_t len = fread(buf, 1, sizeof(buf), in);
      done = len < sizeof(buf);
      if (!XML_Parse(parser, buf, len, done)) {
         fprintf(stderr,
            "%s at line %ld\n",
            XML_ErrorString(XML_GetErrorCode(parser)),
            XML_GetCurrentLineNumber(parser));
         return NULL;
      }
   } while (!done && !finished);
    //Frees up resources associated with a parser (including all the allocated names and values, so watch out!) 
    XML_ParserFree(parser);
    Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::readToken() // PRINT //" << endl;

	//first->print("");
	first->finalize();
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::readToken() // END //" << endl;
	return first;

}
void CTokenReaderXML::charData (void *userData, const XML_Char *s, int len){
    int spacecount=0;
	//int valuecount=0;
	//int stringposition=0;
	bool in_quote = false;
	string cur_string = "";
	//char n;
	//char * pch=NULL;
	const char * alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_!:";
	//const char * nonalpha = " ;()#\"";

    //char *values[len]= new ;
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData (void *userData, const XML_Char *s, int len) // PROCESS // Cur_token: "  << cur_token << endl;
	CTokenReaderXML* mySelf = (CTokenReaderXML*) pObjCurToken;
    Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData  // PROCESS // Mysel: "  << mySelf << endl;
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData  // PROCESS // This: "  << this << endl;
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData  // PROCESS // Cur_token: "  << cur_token << endl;
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData  // PROCESS // Cur_token: "  <<  mySelf->cur_token << endl;
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData  // PROCESS // Cur_token: "  <<  this->cur_token << endl;
	for (int z=0 ;z <len; z++) {
		Debug::debug(Debug::xml,__FUNCTION__) << (int)s[z] ;
	}
	Debug::debug(Debug::xml,__FUNCTION__) << endl;
	if (len >1) {
    //verificar quantos espaços tem
		for (int i=0; i < len; i++) {
         if ((int) s[i]==32)
			 spacecount++;
			//putchar (s[i]);
		 //Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData XML_Char= " << (int) s[i] <<endl;
      }
	// Todo: reconhecer os valores separados por espaço e abrir um token para cada um deles

	// If parent is still empty, close its tag.
    char* name = new char[len]; // allocate with new
   	name[len]='\0';
    strncpy (name,s,(len));

	if (spacecount!=len) {
		for (int i=0; i < len; i++) {
         Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData New Loop i= " << i <<endl;
         //putchar (name[i]);
		 Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData XML_Char= " << (int) name[i] << " = "<< name[i] <<endl;
         Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData Cur_String= " << cur_string <<endl;
		 if ((int)name[i]==32 && cur_string == "") {
			  Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData space Found position x= " << i <<endl;
			  
		 }else if ((int)name[i]== 34) {
              if ( in_quote ){
			    in_quote = false;
				//cur_string += name[i];
				Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData (void *userData, const XML_Char *s, int len) // BEGIN // Token name: "  << cur_string <<" LEN= "<< len << endl;
				Token * sub = new Token( cur_string, false );
				sub->setParent( cur_token );
				cur_token->addToken( sub );
				Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData (void *userData, const XML_Char *s, int len) // PROCESS // Cur_token: "  << cur_token <<" Sub= "<< sub << endl;
				cur_string = "";

			  } else {
			       Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData Quote Found position x= " << i <<endl;
         	       in_quote=true;
			       //cur_string += name[i];
			  }
		 } else if (strchr( alpha, name[i] ) != NULL ) {
			 if (in_quote) {
			  Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData Caracter Found position x= " << i <<endl;
         	  cur_string += name[i];
			 }else {
				cur_string += name[i];
				if ((int)name[i+1]==0 || (int)name[i+1]==32) {
					Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData Caracter Found position x= " << i <<endl;
         			Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData (void *userData, const XML_Char *s, int len) // BEGIN // Token name: "  << cur_string <<" LEN= "<< len << endl;
					Token * sub = new Token( cur_string, false );
					sub->setParent( cur_token );
					cur_token->addToken( sub );
					Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData (void *userData, const XML_Char *s, int len) // PROCESS // Cur_token: "  << cur_token <<" Sub= "<< sub << endl;
					cur_string = "";
				}
			 }
		 }else if ((int)name[i]==32 && cur_string!="") {
			 if (in_quote) {
				Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::charData Caracter Found position x= " << i <<endl;
         		cur_string += name[i];
			 }
		 }
		}

	}
	}

}


void CTokenReaderXML::startElement(void *userData, const char *name, const char **atts){
	// Token * t;
	// string token_string;
    //cria um objeto da classe token
	if (cur_token ==NULL) {
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement // BEGIN // Token name: " << name << endl;
	cur_token = new Token();
	cur_token->setFile( myfile );
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement  // PROCESS // my_tokens.push_back( " << cur_token << " )" << endl;
	my_tokens.push_back( cur_token );
	first = cur_token;
	Token * sub1 = new Token( name, false );
	sub1->setParent( cur_token );
    cur_token->addToken( sub1 );
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement  // PROCESS // xmltoken_stack.push_back( " << cur_token << " )" << endl;
	xmltoken_stack.push_back( cur_token );
	}else {
	  Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement // BEGIN // Token name: " << name << endl;
		if ( !xmltoken_stack.empty() ){
	        Token *another = new Token();
			another->setParent( cur_token );
            cur_token->addToken(another);
			cur_token = another;
			Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement  // PROCESS // xmltoken_stack.push_back( " << cur_token << " )" << endl;
	  		xmltoken_stack.push_back( cur_token );
			Token * sub = new Token( name, false );
			sub->setParent( cur_token );
            cur_token->addToken( sub );

	  Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement  // PROCESS // This: " << this << " Cur_token: "  << cur_token << endl;
	  Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::startElement // END // Token name: " << name << endl;
	}
   }
}
void CTokenReaderXML::endElement(void *userData, const char *name) {
Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::endElement(void *userData, const char *name) // END // Token name: " << name << endl;


	if ( xmltoken_stack.empty() ){
				//cout<<"Stack is empty"<<endl;
				throw CTokenException(__FILE__, __LINE__,"Stack is empty");
			}
	Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::endElement // PROCESS // xmltoken_stack.pop_back() " << endl;

	xmltoken_stack.pop_back();

	if ( ! xmltoken_stack.empty() ){

		Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::endElement // PROCESS // xmltoken_stack.back() " << endl;

		cur_token = xmltoken_stack.back();
	}

}


//! The text Handler. Will manage the text inside the Elements
void CTokenReaderXML::Wrap_charData (void *userData, const XML_Char *s, int len) {
// explicitly cast global variable <pObjCurToken> to a pointer to TClassB
       // warning: <pObjCurToken> MUST point to an appropriate object!
	   CTokenReaderXML* mySelf = (CTokenReaderXML*) pObjCurToken;
       Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::Wrap_charData // PROCESS // Object: " << mySelf << endl;

       // call member
       mySelf->charData(userData,s,len);

}
void CTokenReaderXML::Wrap_startElement(void *userData, const char *name, const char **atts) {
// explicitly cast global variable <pObjCurToken> to a pointer to TClassB
       // warning: <pObjCurToken> MUST point to an appropriate object!
	   CTokenReaderXML* mySelf = (CTokenReaderXML*) pObjCurToken;
	   Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::Wrap_startElement // PROCESS // Object: " << mySelf << endl;

       // call member
       mySelf->startElement(userData,name,atts);


}

void CTokenReaderXML::Wrap_endElement(void *userData, const char *name) {

// explicitly cast global variable <pObjCurToken> to a pointer to TClassB
       // warning: <pObjCurToken> MUST point to an appropriate object!
	   CTokenReaderXML* mySelf = (CTokenReaderXML*) pObjCurToken;
       Debug::debug(Debug::xml,__FUNCTION__) << "CTokenReaderXML::Wrap_endElement // PROCESS // Object: " << mySelf << endl;
       // call member
       mySelf->endElement(userData,name);


}

} //end SGF
