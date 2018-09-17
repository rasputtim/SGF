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
/**
* \file menu_option.cpp
* \brief Funções do Menu
**
Descricao mais detalhada do arquivo .
* Em geral tem mais de uma l i n h a .
**
 \sa menu_option.h
**/
#include "graphics/all.h"
#include "menu/SGF_MenuOption.h"
#include "util/SGF_Token.h"
#include "util/SGF_LanguageString.h"
#include "SGF_Global.h"
#include "menu/SGF_MenuAnimation.h"

using namespace std;using namespace std;
namespace SGF {
namespace Menu {
/** @fn CMenuOption::CMenuOption(const Token *token, const OptionType type, const string xmlDefinitionFile)
@brief Construtor da Classe CMenuOption
O Objetivo é receber um token de opção e Criar uma Classe para
esta nova opção
@param *Token: Ponteiro para um Token que já foi carregado previamente na memória
         type:
@return nenhum. Construtores não retornam valores
@warning nenhum aviso
**/
/*CMenuOption::CMenuOption(const Token *token, const OptionType type, const string xmlDefinitionFile) throw(CLoadException):
//Gui::CContextItem("", *this),
xmlDefFile(xmlDefinitionFile),
parent(0),
currentState(Deselected),
text(""),
infoText(""),
bmp(0),
adjustLeftColor(Colors::makeColor( 255, 255, 255 )),
adjustRightColor(Colors::makeColor( 255, 255, 255 )),
runnable(true),
forRemoval(false){
    Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN CONSTRUCTOR // CMenuOption //" << endl;
	setType(type);

    if(token){
      const Token tok(*token);
	  TokenView view = tok.view();
      while ( view.hasMore()){
	  try{
	      const Token * token;
	      view >> token;
	      if ( *token == "info" ){
                  readInfo(token);
          // get info text add to option
		  //string temp;
		  // *token >> temp;
		  //setInfoText(temp);

	      } else if( *token == "option-anim" ) {

	      }
	      else {
			  Debug::debug(Debug::menu,__FUNCTION__) << "CMenuOption::CMenuOption - Unhandled menu attribute: "<< token->getName()<<endl;
		 // if (Debug::getDebug() >= 3){
		 //     token->print(" ");
		 // }
	      }
	  } catch ( const CTokenException & ex ) {

	      string m( " Menu::CMenu parse error: " );
	      m += ex.getTrace();
	      throw CLoadException(__FILE__, __LINE__, m);
	  } catch ( const CLoadException & ex ) {

	      throw ex;
	  }
      }
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END CONSTRUCTOR // CMenuOption //" << endl;
}

*/
CMenuOption::CMenuOption(const Gui::CContextBox & parent, const Token *token, const string xmlDefinitionFile) throw(CLoadException):
Gui::CContextItem("", parent),
currentState(Deselected),
text(""),
infoText(""),
runnable(true),
xmlDefFile(xmlDefinitionFile){
    Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN CONSTRUCTOR // CMenuOption //" << endl;

    if (token){
      const Token & tok = *token;

      TokenView view = tok.view();
      while (view.hasMore()){
	  try{
	      const Token * token;
	      view >> token;
	      if ( *token == "info" ){
                  readInfo(token);
                  /*
		  // get info text add to option
		  string temp;
		  *token >> temp;
		  setInfoText(temp);
                  */
	      } else if( *token == "option-anim" ) {
	      } else {
		  Debug::debug(Debug::error,__FUNCTION__ ) << "Unhandled menu attribute: "<<endl;
		  //if (Global::getDebug() >= 3){
		  //    token->print(" ");
		  //}
	      }
	  } catch ( const CTokenException & ex ) {
	      throw CLoadException(__FILE__, __LINE__, ex, "Menu option parse error");
	  } catch ( const CLoadException & ex ) {
	      throw ex;
	  }
      }
    }
		Debug::debug(Debug::menu,__FUNCTION__) << "END CONSTRUCTOR // CMenuOption //" << endl;

}

/* tries to read the name for the option. Either use
 *  - legacy way: (name "foobar") which sets the name to "foobar
 *  in english
 *  - new way: (name (language "english" "foobar") ...) which adds
 *  "foobar" as a name in "english". further uses of `language'
 *  add new languages for the name.
 *
 *  Using both style is actually allowed but a (language "english" "foo")
 *  will override the legacy definition.
 *
 *  Expects the parent token to be passed in:
 *  (whatever (name ...))
 */
/*
void CMenuOption::readName(Token * token){

	try{
        CLanguageString name;
        string temp;
		Token *achou = token->findToken("_/name");
	    //achou->print("ACHOU");
	    for ( signed int i = 0; i < achou->numTokens(); i++ ){
            Token *tokx;
		    *achou >> tokx;
			  //cout<<"FOR-"<<"Token: "<< tokx->getName() << endl;
			 if (*tokx =="language") {
		      Token *toky;
			  *tokx >> toky;
			  if (*toky == "english") {
                  Token *toky;
					*tokx >> toky;
                    name.add(toky->getName());
					//cout<<"TOK -"<<"Token: "<< toky->getName() << endl;
			  }
			 }else {

             name.add(tokx->getName());
			 }
		}

		//bool teste2=token->match("_/name", temp);
		//if (token->match("_/name", temp)){
        //    name.add(temp);
        //}

        string language, words;
        //Token::Matcher matcher = token->getMatcher("_/name/language");
        //while (matcher.match(language, words)){
          //  name.add(words, language);
        //}
        // name.add("words","language");
        this->setText(name);

        if (getText().empty()){
            throw CLoadException(__FILE__, __LINE__,"CMenuOption::readName - No name set, this option should have a name!");
        }
    } catch (const CTokenException & ex){
        string m( "CMenuOption::readName - Menu::CMenu_v1 parse error: " );
        m += ex.getTrace();
        throw CLoadException(__FILE__, __LINE__,m);
    }
} */


/* tries to read the name for the option. Either use
 *  - legacy way: (name "foobar") which sets the name to "foobar
 *  in english
 *  - new way: (name (language "english" "foobar") ...) which adds
 *  "foobar" as a name in "english". further uses of `language'
 *  add new languages for the name.
 *
 *  Using both style is actually allowed but a (language "english" "foo")
 *  will override the legacy definition.
 *
 *  Expects the parent token to be passed in:
 *  (whatever (name ...))
 */
void CMenuOption::readName(const Token * token) throw(CLoadException){
    try{
        CLanguageString name;
        string temp;
        if (token->match("_/name", temp)){
            name.add(temp);
        }

        string language, words;
		vector<const Token *> found = token->findTokens("_/name/language");
		if (!found.empty()) {
		Token::Matcher matcher(found);
        //Token::Matcher matcher = token->getMatcher("_/name/language");
        while (matcher.match(language, words)){
            name.add(words, language);
        }
		}

        this->setText(name);

        if (getText().empty()){
            throw CLoadException(__FILE__, __LINE__, "No name set, this option should have a name!");
        }
    } catch (const CTokenException & ex){
        throw CLoadException(__FILE__, __LINE__, ex, "Menu option parse error");
    }
}


/* same deal as readName, except this excepts just the info token:
 * (info ...)
 */
/*
void CMenuOption::readInfo(const Token * token){

	try{
        const Token *achou = token->findToken("info");
	    //achou->print("ACHOU");

		CLanguageString name;
		for ( signed int i = 0; i < achou->numTokens(); i++ ){
            Token *tokx;

		    achou->view()  >> tokx;
			  //cout<<"FOR-"<<"Token: "<< tokx->getName() << endl;
			  if (*tokx =="language") {
			  Token *toky;
			  tokx->view()  >> toky;
			  if (*toky == "english") {
                  Token *toky;
					tokx->view()  >> toky;
                    name.add(toky->getName());
					//cout<<"TOK -"<<"Token: "<< toky->getName() << endl;
			  }
			  }else {

                name.add(tokx->getName());
			  }

		}
        string temp;
		//string teste="teste";
        //if (token->match("info", temp)){
        //    name.add(temp);
        //}
        //name.add(teste);
        string language, words;
        //Token::Matcher matcher = token->getMatcher("info/language");
        //while (matcher.match(language, words)){
         //   name.add(words, language);
        //}
        //name.add("english","paalavras");
        this->setInfoText(name);
    } catch (const CTokenException & ex){
        string m( "CMenuOption::readInfo - Menu::CMenu_v1 parse error: " );
        m += ex.getTrace();
        throw LoadException(__FILE__, __LINE__,m);
    }
} */

void CMenuOption::readInfo(const Token * token) throw (CLoadException){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin " << endl;
    try{
        CLanguageString name;
        string temp;
        if (token->match("info", temp)){
			Debug::debug(Debug::menu,__FUNCTION__) << "Adding Info Text: "<< temp << endl;
            name.add(temp);
        }

        string language, words;
		vector<const Token *> found = token->findTokens("info/language");
		if (!found.empty()) {
		Token::Matcher matcher(found);
        //Token::Matcher matcher = token->getMatcher("info/language");
        while (matcher.match(language, words)){
			Debug::debug(Debug::menu,__FUNCTION__) << "Adding Info Text ( "<<language<< " ): "<< words << endl;
            name.add(words, language);
        }
		}
		Debug::debug(Debug::menu,__FUNCTION__) << "Setting Info Text: "<< name << endl;
        this->setInfoText(name);
		Debug::debug(Debug::menu,__FUNCTION__) << "End " << endl;
    } catch (const CTokenException & ex){
        throw CLoadException(__FILE__, __LINE__, ex, "Menu option parse error");
    }
}

CMenuOption::~CMenuOption(){
    // Kill all animations
/*    for (vector<CMenuAnimation *>::iterator i = backgroundAnimations.begin(); i != backgroundAnimations.end(); ++i){
	if (*i){
	    delete *i;
	}
    }
    for (vector<CMenuAnimation *>::iterator i = foregroundAnimations.begin(); i != foregroundAnimations.end(); ++i){
	if (*i){
	    delete *i;
	}
    }*/
}
/*
void CMenuOption::drawBelow(CBitmap *work){
    for (vector<CMenuAnimation *>::iterator i = backgroundAnimations.begin(); i != backgroundAnimations.end(); ++i){
	if (*i){
	    (*i)->draw(work);
	}
    }
}

void CMenuOption::drawAbove(CBitmap *work){
    for (vector<CMenuAnimation *>::iterator i = foregroundAnimations.begin(); i != foregroundAnimations.end(); ++i){
	if (*i){
	    (*i)->draw(work);
	}
    }
}
*/
// This is to pass paramaters to an option ie a bar or something
bool CMenuOption::leftKey(){
    return false;
}

bool CMenuOption::rightKey(){
    return false;
}

const string CMenuOption::getName() const {
    return getText();
}
/*
void CMenuOption::resetAnimations(){
    for (vector<CMenuAnimation *>::iterator i = backgroundAnimations.begin(); i != backgroundAnimations.end(); ++i){
	if (*i){
	    (*i)->reset();
	}
    }
    for (vector<CMenuAnimation *>::iterator i = foregroundAnimations.begin(); i != foregroundAnimations.end(); ++i){
	if (*i){
	    (*i)->reset();
	}
    }
}
x
void CMenuOption::updateAnimations(){
    for (vector<CMenuAnimation *>::iterator i = backgroundAnimations.begin(); i != backgroundAnimations.end(); ++i){
	if (*i){
	    (*i)->act();
	}
    }
    for (vector<CMenuAnimation *>::iterator i = foregroundAnimations.begin(); i != foregroundAnimations.end(); ++i){
	if (*i){
	    (*i)->act();
	}
    }
}
*/
void CMenuOption::setParent(Menu::CMenu *menu){
    this->parent = menu;
}

/* subclasses can lazily load stuff by overriding this method */
void CMenuOption::open(){
}

/* do any dynamic cleanup here */
void CMenuOption::close(){
}
}
} //end SGF