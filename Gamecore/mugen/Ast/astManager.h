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
#ifndef _SGF_parser_ast_manager_h
#define _SGF_parser_ast_manager_h

#include "all.h"
#include "../gc.h"
#include "../../resource/SGF_ResourceManager.h"
#include <vector>

using namespace std;
namespace SGF {
namespace Ast {
	typedef struct my_key_modifier
{
	my_key_modifier():ticks(0){}
	int ticks;
	Ast::CKeyModifier::ModifierType modifier;
} my_key_modifier;

class  SGE_API  CParseException: ::std::exception {
public:
	typedef Ast::CValue valorteste;
    CParseException(const string & reason):
    ::std::exception(),
    message(reason){
    }

	string getReason() const{
	return message;
	}


    virtual ~CParseException() throw(){
    }

protected:
    string message;


};


class  SGE_API CAstManager {
public:
	typedef list<CSection*>::iterator section_iterator;
	//! Construtor
	CAstManager();
	CAstManager(list<CSection*> * sections);
	CAstManager(Token * token);
	//CAstManager(CAstManager &copy);
	CAstManager & operator=( const CAstManager &copy );
	list<Ast::CSection*> * copy(list<Ast::CSection*> * input);
	list<Ast::CSection*> * copyFrom(Ast::CAstManager * input);
	void debugExplain();

	//! Cria uma lista de seções
	std::list<Ast::CSection*> * makeSectionList();
	//! Cria um objeto Ast::CSection
	Ast::CSection * makeSection( string * str);
	Ast::CSection * makeSection(CString * str);
	Ast::CSection * makeSection(double number);
	//! Adiciona um objeto CSection na lista de Seções
	void addSection( Ast::CSection * section_value);
	//! Adiciona um valor na seção atual
	void addValueToSection(Ast::CValue * object);
	Ast::CAttribute * makeAttributeArray(const CKeyword * name, const CValue * index, const CValue * value);
	//! Cria um atributo: atributo é aquilo que vem antes do sinal de igual, dentro de uma seção
	Ast::CAttribute * makeAttribute(string * id);
	Ast::CAttribute * makeAttribute(Ast::CIdentifier * id, Ast::CValue * data);
	Ast::CAttribute * makeAttribute(CIdentifier *id);
	Ast::CAttribute * makeAttributeKeyword(CKeyword *id);
	Ast::CAttribute * makeAttributeKeyword( CKeyword *id, Ast::CValue * data);
	Ast::CAttribute * makeIndexAttribute( CIdentifier *id,CValue *index,CValue *valor);
    Ast::CAttribute * makeIndexAttribute( CIdentifier *id,CValue *index);
	string * makeHeader( string * begin,  string * action, double number);
	//! Adiciona um atributo a uma seção
	void addAttribute(Ast::CAttribute * object);
	//! Adiciona uma Valor ao atributo atual
	void addValueToAttribute(Ast::CValue * object);
	//! Adiciona um valor ao atributo referenciado
	void addValueToAttribute(Ast::CAttribute *atributo,Ast::CValue * object);

	string * addStrings(string *str1,string *str2);
	string * addStrings(string *str1,double number);
	string * addStrings(double number, string *str1);
	//! Cria um identificador de atributo
    void makeIdentifier(string *str);
	Ast::CIdentifier * makeIdentifierSimple(string *str);
	Ast::CIdentifier * makeIdentifierSimple(string str);
	Ast::CIdentifier * makeIdentifierSimple(double number);
	Ast::CIdentifier * makeIdentifierSimple(Ast::CValue *);
	Ast::CIdentifier * makeIdentifier(string *str1,string *str2);
	Ast::CIdentifier * makeIdentifier(string *str1,double number);
	Ast::CIdentifier * makeIdentifier(double number, string *str1);
	Ast::CIdentifier * makeIdentifier(CIdentifier *identificador,string *str1);
	Ast::CIdentifier * addToIdentifier(Ast::CIdentifier *id,string *str1);
	Ast::CIdentifier * addToIdentifier(Ast::CIdentifier *id,double number);
	Ast::CIdentifier * addToIdentifier(Ast::CIdentifier *id,CValue *value);

	Ast::CIdentifier * makeIdentifier(Ast::CIdentifier *id,double number);
	//! Cria um  objeto CFunction
	Ast::CFunction * makeFunction(string *str, CValue *value);
	Ast::CFunction * makeFunctionif(CValue *value1, CValue *value2,CValue *value3);
	Ast::CFunction * makeFunction(string *str, CValue *value1,CValue *value2);
	Ast::CFunction * makeFunction(string *str, CValue *value1,CValue *value2,CValue *value3);

	//! transform a positive number into negative
	Ast::CValue * makeNegative(CValue *value);

	Ast::CValue * makeProjectileExpression(string * name, CNumber * id, CValue * arg1, CValue  * compare, CValue  * ticks);
	//! cria uma cópia do CValue
	Ast::CValue * makeCValueCopy(CValue *valor);
	//! Cria um  objeto COperand
	Ast::CValue * makeOperand(string  operando);

	//! return a CNumber of the last statedef section
	Ast::CValue * getLastStatedefNumber();
	//!Cria um identificador através de uma lista de strings
	Ast::CIdentifier * addIdentifier();

	//! Cria um objeto CString
	Ast::CValue * makeString();
	Ast::CValue * makeString(string *str); //! conver a strint to a CString and return a CValue
	Ast::CValue * makeString(string str);
	Ast::CValue * makeString(double number, string *str);
	Ast::CValue * makeString(double number);
	Ast::CValue * makeStringSpace(Ast::CString * value1, Ast::CString * value2);
	Ast::CValue * makeStringSpace(Ast::CValue * value1, Ast::CValue * value2);
	Ast::CValue * makeStringSpace(string *str1, string *str2);
	Ast::CValue * makeStringSpace(string *str1, double Number);
    Ast::CValue * makeStringSpace(double Number, string *str1);
	Ast::CValue * makeStringDot(string *str1, string *str2);
	Ast::CValue * makeStringDot(string *str1, double Number);
    Ast::CValue * makeStringDot(double Number, string *str1);
	Ast::CValue * makeStringFromKey(Ast::CKey * key);
	void addToString(string *str);
    Ast::CValue * addToStringSpace(Ast::CString * value, string *str1);
	Ast::CValue * addToStringSpace(Ast::CString * value, double number);
	Ast::CValue * addToStringDot(Ast::CString * value, string *str1);
	Ast::CValue * addToStringDot(Ast::CString * value, double number);

	Ast::CValue * makeValue();
	Ast::CValue * makeValueString();
	//! Cria um objeto CNumber
	Ast::CValue * makeNumber(double number);
	Ast::CValue * makeNumber(char & sign, double & number);

    //! Cria um objeto CPostfixExpression
	Ast::CValue * makePostfixExpression(CStack *nodes);
	Ast::CValue * makeUnaryExpression(CValue *value, const string & operando);
	Ast::CValue * makeExpressionEquals(CValue *left,CValue *right);
	Ast::CValue *makeExpressionAnd(const CValue * left, const CValue * right);
	Ast::CKey * makeKey(const char * value);
	Ast::CKey * makeKey(string * value);

	//! Cria um objeto CValueList
	Ast::CValueList * makeValueList(CValue *str1,CValue *str2);
	Ast::CValueList * makeValueList(CValue *valor1);
	Ast::CValueList * addToValueList(CValueList *list,CValue *value);
	Ast::CValueList * addToValueListFront(CValueList *list,CValue *value);
	Ast::CValueList * concatenateValueLists(CValueList *list1,CValueList *list2);
	//! Cria um objeto CRange
	Ast::CValue * makeRange(int type, double valor1, double valor2);

	//! Cria um objeto CArgument
	Ast::CValue * makeArgument(int line, int column, int index);

	//! Cria um objeto CResource
	Ast::CValue * makeResource(CValue * value, bool fight, bool own);
	Ast::CValue * makeOwnResource(CValue * number);
 	Ast::CValue * makeFightResource(CValue * number);

	//Cria um objeto CKeyword
	Ast::CKeyword * makeKeyword(string *str);
	Ast::CKeyword * makeKeyword(char & value);
	Ast::CValue * makeKeywordArray(string * id, CValue *index);

	//Cria um Objeto Helper
	//old
	Ast::CValue * makeHelper(const string *name, CValue *id);
	//new
	Ast::CValue * makeHelper(const string *name, CValue * expression, CValue * id);

	//! métodos relacionados ao manuseio de teclas
	Ast::CKey * makeKeyModifier(Ast::CKey * in, Ast::CKeyModifier::ModifierType type, int ticks = 0);
	Ast::CKey * makeKeyCombined(string *str1, string *str2);
	Ast::CKey * addCombinedKey(Ast::CKey *key1, string *str2);
	Ast::CValue * makeKeyList();
	Ast::CKey * applyKeyModifiers( Ast::CKey * key);
	void addHeldDownKeyModifier(int ticks=0);
	void addDirectionKeyModifier(int ticks=0);
	void addReleaseKeyModifier(int ticks=0);
	void addOnlyKeyModifier(int ticks=0);
	void addKeyToList(Ast::CKey *key);
	void iskey() { thisiskey = true;}
	void isnotkey() { thisiskey = false;}
	void setValidSection() { my_bValid_section = true;}
	void setInvalidSection() { my_bValid_section=false;}
	bool isValidSection() {return my_bValid_section;}
	//HitDef
	Ast::CValue * makeHitDefAttribute(string * atribute);
	Ast::CHitDefAttackAttribute * makeHitDefAttackAttribute();

    bool operator!=(const CAstManager & him) const {
        return !(*this == him);
    }
    bool operator==(const CAstManager & him) const {
		return this->pConfiguration == him.pConfiguration;
	}

    /* useful stuff */

    //inline list<CSection*> * getSections() {
	//	return & this->pConfiguration.sections;
    //}
	section_iterator getBeginIterator() {
		return pConfiguration.sections.begin();
	}
	section_iterator getEndIterator() {
		return pConfiguration.sections.end();
	}
	int getNumSections() {
	return pConfiguration.sections.size();
	}
    CSection* getFirstSection() {
	return pConfiguration.sections.front();
	}
	CSection* getLastSection() {
		return pConfiguration.sections.back();
	}


	CSection * findSection(const string & find) const{
		return this->pConfiguration.findSection(find);
	}
	CSection * findSection(const string & find){
		return this->pConfiguration.findSection(find);
	}
//! Destrutor: Todo: O que fazer aqui para destruir todos os ponteiros criados

virtual ~CAstManager();



protected:

    Ast::CConfiguration pConfiguration;

private:

	Ast::CAttribute *pCurrentAttribute;
	list<string > CurIdentifier;  // Lista de strings que formam o identificador atual
	vector<my_key_modifier> CurrentModifiers;  //!lista com os modificadores que devem ser aplicados a uma tecla
	vector<CKey *> CurrentKeys;  //! lista de teclas a adicionar a um comando
	void clearAtributeLists(); //! limpa listas utilizadas na formação do atributo
	string *pCurString;
	bool thisiskey; // indica se é ou nao uma lista de keys
	bool my_bValid_section; //! indica se é uma sessão válida para adicionar comandos

};  //end class CAstManager

}
} //end SGF

#endif
