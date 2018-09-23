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



#include "mugen/ast/astManager.h"
#include "mugen/gc.h"
#include "util/SGF_Debug.h"
#include <string>

using namespace std;
namespace SGF{

class CValue;
class CConfiguration;
class CStack;

namespace Ast {


/** @fn CAstManager::CAstManager()
@brief Construtor da Classe CAstManager
@warning nenhum aviso
**/
CAstManager::CAstManager():
//pSection_list_current(NULL),
pCurrentAttribute(NULL),
pCurString(NULL),
thisiskey(false),
//sections(pConfiguration.sections),
my_bValid_section(true)
{
	//sections=pConfiguration.sections;

	CurIdentifier.clear();
	CurrentModifiers.clear();
	CurrentKeys.clear();
}
CAstManager::CAstManager(list<CSection*> * sections):
//pSection_list_current(makeSectionList()),
//pConfiguration(new Ast::CConfiguration()),
pCurrentAttribute(NULL),
pCurString(NULL),
thisiskey(false),
//sections(sections),
my_bValid_section(true){
	//pConfiguration=new Ast::CConfiguration();
	//&pConfiguration.sections=sections; 
	sections=sections;
	}

CAstManager::CAstManager(Token * token):
//pConfiguration(new Ast::CConfiguration()),
pCurrentAttribute(NULL),
pCurString(NULL),
thisiskey(false),
//sections(NULL),
my_bValid_section(true){
	pConfiguration.deserialize(token);
    }

//CAstManager::CAstManager(CAstManager &copy):

//{}

CAstManager::~CAstManager(){
}

/** @fn CAstManager::makeSectionList()
@brief Cria uma lista de Seçoes
@param
@return retorna ponteiro para GC::SectionList()
@warning VERIFICAR... ACHO QUE ESSA LISTA NÃO É UTILIZADA PRA NADA....
**/
GC::SectionList * CAstManager::makeSectionList(){
	GC::SectionList * object = new GC::SectionList();
	SGF::CResource::save(object);
    return object;
}


list<Ast::CSection*> * CAstManager::copy(list<Ast::CSection*> * input){
    list<Ast::CSection*> * output = new list<Ast::CSection*>();

    for (list<Ast::CSection*>::iterator it = input->begin(); it != input->end(); it++){
        output->push_back((Ast::CSection*) (*it)->copy());
    }

    return output;
}

list<Ast::CSection*> * CAstManager::copyFrom(Ast::CAstManager * input){
	Debug::debug(Debug::parsers,__FUNCTION__) << " ------------BEGIN" << endl;
	Debug::debug(Debug::parsers,__FUNCTION__) << "             Input:"<< &input->pConfiguration.sections << endl;
	Debug::debug(Debug::parsers,__FUNCTION__) << "        Input size:"<< input->pConfiguration.sections.size() << endl;
	//input->debugExplain();
	list<Ast::CSection*> * output = new list<Ast::CSection*>();
	Debug::debug(Debug::parsers,__FUNCTION__) << "      Destination:"<< &output << endl;
	Debug::debug(Debug::parsers,__FUNCTION__) << " Destination size:"<< pConfiguration.sections.size() << endl;
    try {
	for (list<Ast::CSection*>::iterator it = input->pConfiguration.sections.begin(); it != input->pConfiguration.sections.end(); it++){
        output->push_back((Ast::CSection*) (*it)->copy());
    }
	this->pConfiguration.setSections(output);
	Debug::debug(Debug::parsers,__FUNCTION__) << " Destination size:"<< pConfiguration.sections.size() << endl;
	}catch(...) {
	Debug::debug(Debug::parsers,__FUNCTION__) << " Destination Error:"<< endl;

	}

    return output;
}
void CAstManager::debugExplain() {
	Debug::debug(Debug::parsers,__FUNCTION__) << " BEGIN" << endl;
	for (list<CSection *>::iterator iter = pConfiguration.sections.begin();
			iter != pConfiguration.sections.end();
			iter++) {
			(*iter)->debugExplain();
		}
	Debug::debug(Debug::parsers,__FUNCTION__) << " END" << endl;
	}
CAstManager & CAstManager::operator=( const CAstManager &copy ){
    // Check for self-assignment!
	Debug::debug(Debug::parsers,__FUNCTION__) << " CAstManager::Operator = copy // BEGIN" << endl;
	if (this == &copy)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.

    //string temp;
	//temp = *copy.pCurString;
	pConfiguration=copy.pConfiguration;
	//CurIdentifier=copy.CurIdentifier;
	//CurrentModifiers=copy.CurrentModifiers;
	//CurrentKeys=copy.CurrentKeys;
	//pSection_list_current=copy.pSection_list_current;
	//pCurString=&temp;
	//pConfiguration=copy.pConfiguration;
	//pCurrentAttribute=copy.pCurrentAttribute;
	thisiskey=copy.thisiskey;
    return *this;
}



/** @fn CAstManager::makeSection(string * str)
@brief Cria um objeto CSection (uma seção)
@param string * str: ponteiro para uma string que contém o nome da Seção
@return retorna ponteiro Ast::CSection para a seção criada
@warning nenhum aviso
**/
Ast::CSection * CAstManager::makeSection(string * str){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "Section: " <<str->c_str() <<endl;

	Ast::CSection * object = new Ast::CSection(str);
	addSection(object);
	SGF::CResource::save(object);
    return object;
	}
	return NULL;
}

/** @fn CAstManager::makeSection(CString * str)
@brief Cria um objeto CSection (uma seção)
@param string * str: ponteiro para uma string que contém o nome da Seção
@return retorna ponteiro Ast::CSection para a seção criada
@warning nenhum aviso
**/
Ast::CSection * CAstManager::makeSection(Ast::CString * str){
	if (this->isValidSection()) {
	string *temp= new string(str->toString2());

	Debug::debug(Debug::parsers,__FUNCTION__) << "makeSection from CString // Section: " <<temp->c_str() <<endl;
	Ast::CSection * object = new Ast::CSection(temp);
	addSection(object);
	// str will be deleted by garbage colector
	SGF::CResource::save(object);
	return object;
	} 
	return NULL;
}
/** @fn CAstManager::makeSection(double number)
@brief Cria um objeto CSection (uma seção)
@param string * str: ponteiro para uma string que contém o nome da Seção
@return retorna ponteiro Ast::CSection para a seção criada
@warning nenhum aviso
**/
Ast::CSection * CAstManager::makeSection(double number) {
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number <<endl;
	//! converte double to string
	::std::ostringstream oss;
	oss << number;
	string *value = new string(oss.str());
	return makeSection(value);
	}
	return NULL;
}
/** @fn CAstManager::addSection(Ast::CSection * section_value)
@brief Adiciona uma seção à lista de seções do objeto CConfiguration
@param Ast::CSection * section_value: Ponteiro para o objeto CSection que será adicionado à lista
@return
@warning nenhum aviso
**/
void CAstManager::addSection(Ast::CSection * section_value){
	if (this->isValidSection()) {
	//add current section list
	Debug::debug(Debug::parsers,__FUNCTION__) << "Section:" <<section_value <<endl;
	
	  if (section_value == 0){
		throw CParseException("Cannot add null section");
	  }

	pConfiguration.sections.push_back(section_value);
  
  }
}

//! Cria um novo atributo baseado num identificador
//! o valor desse atributo será adicionado posteriormente por AddValue toAttribute
Ast::CAttribute * CAstManager::makeAttribute(CIdentifier *id){
	if (this->isValidSection()) {
		if (this->pConfiguration.sections.size() > 0) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "Identifier:" <<id->toString().c_str() <<endl;
			Ast::CAttributeSimple * object = new Ast::CAttributeSimple(id);
			Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
			this->pConfiguration.sections.back()->addAttribute(object);

			pCurrentAttribute = object;
			SGF::CResource::save(object);
   			return object;
		}
	}
	return NULL;
}
//! Cria um novo atributo baseado num identificador e num valor
Ast::CAttribute * CAstManager::makeAttribute(Ast::CIdentifier * id, Ast::CValue * data){
	if (this->isValidSection()) {
	   if (this->pConfiguration.sections.size() > 0) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Identifier:" <<id->toString().c_str() <<" Value: "<< data->toString().c_str() <<endl;
		Ast::CAttributeSimple * object = new Ast::CAttributeSimple(id, data);
		Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<endl;
		object->debugExplain();
	
		this->pConfiguration.sections.back()->addAttribute(object);

		pCurrentAttribute = object;
		SGF::CResource::save(object);
		return object;
	   }
	}
	return NULL;
}
//! Cria um atributo, baseado numa string passada
//! primeiro cria um identificador, depois cria o atributo
Ast::CAttribute * CAstManager::makeAttribute(string * str){
	if (this->isValidSection() ) {
		if (this->pConfiguration.sections.size() > 0) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<*str <<endl;
			//list<string > *Identifier = new list<string >;
			//Identifier->push_back(*str);
			makeIdentifier(str);
			Ast::CIdentifier *tempIdent = addIdentifier();
			//Ast::CIdentifier *tempIdent = new Ast::CIdentifier(*Identifier);
			Ast::CAttributeSimple * object = new Ast::CAttributeSimple(tempIdent);
			Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
			this->pConfiguration.sections.back()->addAttribute(object);

			pCurrentAttribute = object;
			SGF::CResource::save(object);

			return object;
		}
	}
	return NULL;
}
//! Cria um novo atributo baseado num identificador
//! o valor desse atributo será adicionado posteriormente por AddValue toAttribute
Ast::CAttribute * CAstManager::makeIndexAttribute(CIdentifier *id, CValue *index,  CValue *valor){
	if (this->isValidSection()) {
		if (this->pConfiguration.sections.size() > 0) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "index: " <<index <<" Identifier: "<<*id->toString().c_str() <<endl;
			Ast::CAttributeArray * object = new Ast::CAttributeArray(id,index,valor);
			pCurrentAttribute = object;
			Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
			this->pConfiguration.sections.back()->addAttribute(object);

			SGF::CResource::save(object);
			return object;
		}
	}
	return NULL;
}

//! Cria um novo atributo baseado num identificador
//! o valor desse atributo será adicionado posteriormente por AddValue toAttribute
Ast::CAttribute * CAstManager::makeIndexAttribute(CIdentifier *id, CValue *index){
	if (this->isValidSection()) {
		if (this->pConfiguration.sections.size() > 0) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "index: " <<index <<" Identifier: "<<*id->toString().c_str() <<endl;
			Ast::CAttributeArray * object = new Ast::CAttributeArray(id,index);
			pCurrentAttribute = object;
			Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
			this->pConfiguration.sections.back()->addAttribute(object);

			SGF::CResource::save(object);
			return object;
		}
	}
	return NULL;
}
string * CAstManager::makeHeader(string * begin, string * action,  double number){
    ::std::ostringstream oss;
	oss << number;
	//string *value = new string(oss.str());
	string out;
	out = *(begin) + " " + *(action) + " " + oss.str();
    string * object = new string(out);
    SGF::CResource::save(object);
    return object;
}



Ast::CAttribute * CAstManager::makeAttributeKeyword(CKeyword *id){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "keyword:" <<*id->toString().c_str() <<endl;
	Ast::CAttributeKeyword * object = new Ast::CAttributeKeyword(id);
    pCurrentAttribute = object;
	Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
	this->pConfiguration.sections.back()->addAttribute(object);

	SGF::CResource::save(object);
	return object;
	}
	return NULL;
}

Ast::CAttribute * CAstManager::makeAttributeKeyword( CKeyword *id, Ast::CValue * data){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "keyword:" <<*id->toString().c_str()<< " data: "<< data->toString() <<endl;
	Ast::CAttributeKeyword * object = new Ast::CAttributeKeyword(id,data);
    pCurrentAttribute = object;
	Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
	this->pConfiguration.sections.back()->addAttribute(object);

	SGF::CResource::save(object);
	return object;
	}
	return NULL;
}

Ast::CAttribute * CAstManager::makeAttributeArray(const CKeyword * name, const CValue * index, const CValue * value){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "keyword:" << name->toString() << " index: "<< index->toString() <<endl;
		Debug::debug(Debug::parsers,__FUNCTION__) << "value:" << value->toString() << endl;
		Ast::CAttributeArray * object = new Ast::CAttributeArray(name,index,value);
		pCurrentAttribute = object;
		Debug::debug(Debug::parsers,__FUNCTION__) << "Adding Attribute => Object:" <<&object <<endl;
		this->pConfiguration.sections.back()->addAttribute(object);

		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CKeyword * CAstManager::makeKeyword(string *str){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "keyword:" << str->c_str() <<endl;
		Ast::CKeyword * object = new Ast::CKeyword(*str);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}
Ast::CKeyword * CAstManager::makeKeyword(char & value){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "value: "<< value <<endl;
		Ast::CKeyword * object = new Ast::CKeyword(&value);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeKeywordArray(string* id, CValue *index){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "value: "<< id->c_str() <<" index: "<< index->toString().c_str()<< endl;
		Ast::CKeywordArray * object = new Ast::CKeywordArray(*id, index);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CValueList * CAstManager::makeValueList(CValue *valor1, CValue *valor2) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) <<endl;

		list<CValue*> values;
		values.push_back(valor1);
		values.push_back(valor2);
		Ast::CValueList *object = new Ast::CValueList(values);
		SGF::CResource::save(object);

		return object;
	}
	return NULL;

}
Ast::CValueList * CAstManager::makeValueList(CValue *valor1) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "only one value: " <<valor1->toString().c_str()<<endl;
		list<CValue*> values;
		values.push_back(valor1);
		Ast::CValueList *object = new Ast::CValueList(values);
		SGF::CResource::save(object);
   		return object;
	}
	return NULL;

}
Ast::CValueList * CAstManager::addToValueListFront(CValueList *list,CValue *valor){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << " Valor:" <<*valor->toString().c_str() <<endl;

		if (list !=NULL) {
		list->addValuetoFront(valor);
		return list;
		}
	}
	return NULL; 
}
Ast::CValueList * CAstManager::addToValueList(CValueList *list,CValue *valor) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << " Valor:" <<*valor->toString().c_str() <<endl;

		if (list !=NULL) {
		list->addValue(valor);
		return list;
		}
	}
	return NULL; //to avoid compiler complain
}
Ast::CValueList * CAstManager::concatenateValueLists(CValueList *list1,CValueList *list2){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Concatenating to Value Lists on the first list" <<endl;
		int n = list2->getSize();
		int m = list2->getSize();
		Debug::debug(Debug::parsers,__FUNCTION__) << "List 1 size:" <<m <<endl;
		Debug::debug(Debug::parsers,__FUNCTION__) << "List 2 size:" <<n <<endl;
		for (int i=0; i < m ;i++) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "List 1 value( "<<i<<" ):" <<list2->get(i)->toString() <<endl;

		}
		for (int i=0; i < n ;i++) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "List 2 value( "<<i<<" ):" <<list2->get(i)->toString() <<endl;

			list1->addValue((CValue *)list2->get(i)->copy());
		}
		Debug::debug(Debug::parsers,__FUNCTION__) << "Will print the new list:" <<endl;
		list1->toString();
		return list1;
	}
	return NULL;
}
void CAstManager::makeIdentifier(string *str){
	if (this->isValidSection()) {
		if (CurIdentifier.empty()) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<*str <<endl;
			CurIdentifier.push_back(*str);
		} else {
			Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<*str <<endl;

			CurIdentifier.push_back(*str);
		}
	}
	
  }
string * CAstManager::addStrings(string *str1,string *str2){
	string *temp= new string(*str1);
	*temp = *temp+*str2;
	return temp;

}
string * CAstManager::addStrings(string *str1,double number){
	::std::ostringstream oss;
		oss << number;
	string *temp= new string(*str1);
	*temp = *temp+oss.str();
	return temp;
}
string * CAstManager::addStrings(double number,string *str1){
	::std::ostringstream oss;
		oss << number;
	string *temp= new string(*str1);
	*temp = oss.str()+*temp;
	return temp;
}
Ast::CIdentifier * CAstManager::makeIdentifierSimple(string *str1){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<str1->c_str() <<endl;
		//list<string> *temp = new list<string>;
		//temp->clear();
		//temp->push_back(*str1);

		Ast::CSimpleIdentifier * object = new CSimpleIdentifier(*str1);
		SGF::CResource::save(object);
		return object;
		}
	return NULL;
}
Ast::CIdentifier * CAstManager::makeIdentifierSimple(string str1){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<str1.c_str() <<endl;
	//list<string> *temp = new list<string>;
	//temp->clear();
	//temp->push_back(*str1);

	Ast::CSimpleIdentifier * object = new CSimpleIdentifier(str1);
    SGF::CResource::save(object);
	return object;
	}
	return NULL;
}
Ast::CIdentifier * CAstManager::makeIdentifierSimple(Ast::CValue *valor){
	if (this->isValidSection()) {
		
		return makeIdentifierSimple(valor->toString());
		}

	
	return NULL;
}
Ast::CIdentifier * CAstManager::makeIdentifierSimple(double number){
	if (this->isValidSection()) {
		::std::ostringstream oss;
			oss << number;
			string *value = new string(oss.str());
		Debug::debug(Debug::parsers,__FUNCTION__) << "number: "<<number <<endl;
		//list<string> *temp = new list<string>;
		//temp->clear();
		//temp->push_back(*value);
		Ast::CSimpleIdentifier * object = new Ast::CSimpleIdentifier(*value);
		SGF::CResource::save(object);
		return object;
		}
	return NULL;

}

Ast::CIdentifier * CAstManager::makeIdentifier(string *str1,string *str2){
	if (this->isValidSection() ) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<str1->c_str() <<" String2: "<<str2->c_str() <<endl;
		list<string> *temp = new list<string>;
		temp->clear();
		temp->push_back(*str1);
		temp->push_back(*str2);
		Ast::CIdentifier * object = new Ast::CIdentifier(*temp);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}
Ast::CIdentifier * CAstManager::makeIdentifier(string *str1,double number){
	if (this->isValidSection()) {
		::std::ostringstream oss;
			oss << number;
			string *value = new string(oss.str());

		Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<str1->c_str() <<" String2: "<< number <<endl;
		list<string> *temp = new list<string>;
		temp->clear();
		temp->push_back(*str1);
		temp->push_back(*value);
		Ast::CIdentifier * object = new Ast::CIdentifier(*temp);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CIdentifier * CAstManager::makeIdentifier(double number, string *str1){
	if (this->isValidSection()) {
		::std::ostringstream oss;
			oss << number;
			string *value = new string(oss.str());

		Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<number <<" String2: "<< str1->c_str() <<endl;
		list<string> *temp = new list<string>;
		temp->clear();
		temp->push_back(*value);
		temp->push_back(*str1);
		Ast::CIdentifier * object = new Ast::CIdentifier(*temp);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}
//! Cria um identificador baseado numa string e num outro identificador, colocando a string passada no início do identificador
Ast::CIdentifier * CAstManager::makeIdentifier(CIdentifier *identificador, string *str1){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<str1->c_str() <<" Identifier: "<<identificador->toString().c_str() <<endl;
		if (identificador != NULL) {
			identificador->addIdentifierToBegin(*str1);
			return identificador;
		}
	}
	return NULL;
}
//! adiciona ao final do identificador
// Todo verificar se precisa deletar str1
Ast::CIdentifier * CAstManager::addToIdentifier(Ast::CIdentifier *id,string *str1){
	if (this->isValidSection()) {
		if (id!=NULL) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "string1: "<<str1->c_str() <<endl;
		id->addIdentifier(*str1);
		}else {
		Debug::debug(Debug::parsers,__FUNCTION__) << "ERROR // identifier: NULL"<<endl;

		}
		return id;
		}
	return NULL;
}

Ast::CIdentifier * CAstManager::addToIdentifier(Ast::CIdentifier *id,CValue *value){
	if (this->isValidSection()) {
	if (id!=NULL) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Value: "<< value->toString()  <<endl;
		id->addIdentifier(value->toString());
	}else {
	Debug::debug(Debug::parsers,__FUNCTION__) << "ERROR // identifier: NULL"<<endl;

	}
	return id;
	}
	return NULL;
}
//! adiciona ao final do identificador
Ast::CIdentifier * CAstManager::addToIdentifier(Ast::CIdentifier *id,double number){
	if (this->isValidSection()) {
		if (id!=NULL) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number  <<endl;
			//! converte double to string
			::std::ostringstream oss;
			oss << number;
			string *value = new string(oss.str());
			id->addIdentifier(*value);
		}else {
		Debug::debug(Debug::parsers,__FUNCTION__) << "ERROR // identifier: NULL"<<endl;
		}
		return id;
		}
	return NULL;
}

//! Cria um identificador baseado numa string e num outro identificador, colocando o número passada no início do identificador
Ast::CIdentifier * CAstManager::makeIdentifier(Ast::CIdentifier *id,double number)
{
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number  <<endl;
		//! converte double to string
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		return makeIdentifier(id,value);
	}
	return NULL;
}
//! adiciona o atributo criado à Sessão atual
//! relaciona o atributo com a sessão a que ele se refere
void CAstManager::addAttribute(Ast::CAttribute * object){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "Object:" << object->toString() <<endl;
	this->pConfiguration.sections.back()->addAttribute(object);
	}
}
void CAstManager::addValueToSection(Ast::CValue * object){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "Object:" <<object->toString() <<endl;
	this->pConfiguration.sections.back()->addValue(object);
	}
}
void CAstManager::addValueToAttribute(Ast::CValue * object){
	if (this->isValidSection()) {
		if (pCurrentAttribute!=NULL && object !=NULL) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Attibute : " << pCurrentAttribute->toString() <<" // Object:" <<object->toString() <<endl;
		this->pCurrentAttribute->setValue(object);

		clearAtributeLists();
		}
	}
}

void CAstManager::addValueToAttribute(Ast::CAttribute *atributo,Ast::CValue * object){
	if (this->isValidSection()) {
		if (atributo!=NULL) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "Atribute: " << atributo->toString() <<" // Object:" <<object->toString() <<endl;
		atributo->setValue(object);

		}
	}
}
void CAstManager::clearAtributeLists(){
pCurrentAttribute = NULL;
pCurString=NULL;
this->CurrentKeys.clear();
this->CurrentModifiers.clear();
this->CurIdentifier.clear();
this->isnotkey();

}


Ast::CValue * CAstManager::makeValue(){
	if (this->isValidSection()) {
		Ast::CNumber * object = new Ast::CNumber(0);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}
Ast::CValue * CAstManager::makeValueString(){
	if (this->isValidSection()) {
		Ast::CString * object = new Ast::CString(new string(""));
   		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeOperand(string operando) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "operand: " << operando << endl;
		Ast::COperand::OperandType type;
		if(operando=="EQUAL") {
				type = Ast::COperand::Equals;
		}else if(operando=="NOTEQUAL") {
			type = Ast::COperand::NotEquals;
		}else if(operando=="GREATER") {
			type = Ast::COperand::GreaterThan;
		}else if(operando=="LESS") {
			type = Ast::COperand::LessThan;
		}else if(operando=="GREATERTHANEQUAL") {
			type = Ast::COperand::GreaterThanEquals;
		}else if(operando=="LESSTHANEQUAL") {
			type = Ast::COperand::LessThanEquals;
		}else if(operando=="ADD") {
			type = Ast::COperand::Add;
		}else if(operando=="SUB") {
			type = Ast::COperand::Subtract;
		}else if(operando=="MULTIPLY") {
			type = Ast::COperand::Multiply;
		}else if(operando=="DIV") {
			type = Ast::COperand::Divide;
		}else if(operando=="MOD") {
			type = Ast::COperand::Modulo;
		}else if(operando=="POWER") {
			type = Ast::COperand::Power;
		}else if(operando=="NEGATION") {
			type = Ast::COperand::Negation;
		}else if(operando=="NOT") {
			type = Ast::COperand::Not;
		}else if(operando=="AND") {
			type = Ast::COperand::And;
		}else if(operando=="OR") {
			type = Ast::COperand::Or;
		}else if(operando=="XOR") {
			type = Ast::COperand::XOr;
		}else if(operando=="BITAND") {
			type = Ast::COperand::BitwiseAnd;
		}else if(operando=="BITOR") {
			type = Ast::COperand::BitwiseOr;
		}else if(operando=="BITXOR") {
			type = Ast::COperand::BitwiseXOr;
		}
		Debug::debug(Debug::parsers,__FUNCTION__) << "operand Type: " << type << endl;
		Ast::COperand *object = new Ast::COperand(type);

			SGF::CResource::save(object);
			return object;
	}
	return NULL;
}


Ast::CValue * CAstManager::makeNumber(double number){
    if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "number:" <<number <<endl;
		Ast::CNumber * object = new Ast::CNumber(number);
  		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}


Ast::CFunction * CAstManager::makeFunction(string *str, CValue *value){
	if (this->isValidSection()) {
		if(value !=NULL && str !=NULL) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "name: "<< str->c_str() <<endl;
		Ast::CValueList *temp=makeValueList(value);
		Ast::CFunction * object = new Ast::CFunction(*str,temp);
  		SGF::CResource::save(object);
		return object;
		}
		
	}
	return NULL;
}
Ast::CValue * CAstManager::makeCValueCopy(CValue *valor){
	if (valor !=NULL) {
		CElement * temp = valor->copy();
		return (Ast::CValue *) temp;
	}
	return NULL;
}

Ast::CFunction * CAstManager::makeFunction(string *str, CValue *value1, CValue *value2, CValue *value3){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "name: "<< str->c_str() <<endl;
		if(value1 !=NULL && value2 !=NULL && str !=NULL) {
		Ast::CValueList *temp=makeValueList(value1,value2);
		Ast::CValueList *TEMP2= addToValueList(temp,value3);
	
		Ast::CFunction * object = new Ast::CFunction(*str,TEMP2);
  		SGF::CResource::save(object);
		return object;
		}
	}
	return NULL;

}

Ast::CFunction * CAstManager::makeFunction(string *str, CValue *value1, CValue *value2){
	if (this->isValidSection()) {
		if(value1 !=NULL && value2 !=NULL && str !=NULL) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "name: "<< str->c_str() <<endl;
		Ast::CValueList *temp=makeValueList(value1,value2);
		Ast::CFunction * object = new Ast::CFunction(*str,temp);
  		SGF::CResource::save(object);
		return object;
		}
	}
	return NULL;

}
Ast::CFunction * CAstManager::makeFunctionif(CValue *value1, CValue *value2,CValue *value3) {
	if (this->isValidSection()) {
		string str="ifelse";
		if(value1 !=NULL && value2 !=NULL && value3 !=NULL) {
		Ast::CValueList *temp=makeValueList(value1,value2);
		temp=this->addToValueList(temp,value3);
		Ast::CFunction * object = new Ast::CFunction(str,temp);
  		SGF::CResource::save(object);
		return object;
		}
	}
	return NULL;
}

Ast::CValue * CAstManager::makeNegative(CValue *value){
	if (value != NULL) {
	string type = value->getType();
	

		if(type =="number"){
			((CNumber *) value)->changeSignal();
			
		}
		return value;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeProjectileExpression(string * name, CNumber * id, CValue * arg1, CValue * compare, CValue * ticks){
    if (this->isValidSection()) {

		Ast::CValue * comparison = NULL;

		/* comparison will be an infix expression where the left node is an Argument ast class.
		 * The runtime evaluator will fill in the Environment with a value for arg0 so that
		 * when the Argument is evaluated it will pull out arg0.
		 *
		 * For example, for projhit arg0 will be projectile->lastHit - stage->ticks
		 */
		Ast::CStack *newnodes = new Ast::CStack("ProjectilleCompareExpression");
		/* check if the second form is used */
		if (compare != NULL){
			newnodes->push(makeNumber(0));  //this is arg0
			newnodes->push(ticks);
			newnodes->push(compare);
			comparison = makePostfixExpression(newnodes);
		} else {
			Ast::CValue * one = makeNumber(1);
			newnodes->push(makeNumber(0));  //this is arg0
			newnodes->push(one);
			newnodes->push(makeOperand(string("LESSTHANEQUAL")));
			comparison = makePostfixExpression(newnodes);

		}
    
		Ast::CValue * get = makeFunction(name,(Ast::CValue *) id, arg1,comparison);
		return get;
	} 
	return NULL;
}
//!Cria um identificador através de uma lista de strings
Ast::CIdentifier * CAstManager::addIdentifier(){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) <<endl;
		list<string> *temp = new list<string>;
		temp->clear();
		list<string>::iterator it;
		for(it=CurIdentifier.begin(); it!=CurIdentifier.end(); ++it) {
			temp->push_back((*it));
		}
		CurIdentifier.clear();
		Ast::CIdentifier * object = new Ast::CIdentifier(*temp);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
  }
//! Cria um novo objeto CString adicionado a ele uma nova string no final
Ast::CValue * CAstManager::addToStringSpace(Ast::CString * value, string *str1){
	if (this->isValidSection()) {
		string *temp= new string(value->toString2());
		Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<temp->c_str() <<endl;
		temp->append(" ");
		temp->append(*str1);
		Debug::debug(Debug::parsers,__FUNCTION__) << "NEW // String:" <<temp->c_str() <<endl;

		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		pCurString = NULL;
		//value will be deleted by garbage coletor
		delete str1;
		return object;
	}
	return NULL;
}
//! Cria um novo objeto CString adicionado a ele uma nova string no final
Ast::CValue * CAstManager::addToStringSpace(Ast::CString * value, double number){
	if (this->isValidSection()) {
	//! converte double to string
	::std::ostringstream oss;
	oss << number;
	string *temp = new string(value->toString2());
	temp->append(" ");
	temp->append(oss.str());
	Debug::debug(Debug::parsers,__FUNCTION__) << "NEW // String:" <<temp->c_str() <<endl;
	Ast::CString * object = new Ast::CString(temp);
    SGF::CResource::save(object);
	pCurString = NULL;
	return object;
	}
	return NULL;

}
//! Cria um novo objeto CString adicionado a ele uma nova string no final separada por ponto
Ast::CValue * CAstManager::addToStringDot(Ast::CString * value, string *str1){
	if (this->isValidSection()) {
		string *temp= new string(value->toString2());
		Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<temp->c_str() <<endl;
		temp->append(".");
		temp->append(*str1);
		Debug::debug(Debug::parsers,__FUNCTION__) << "NEW // String:" <<temp->c_str() <<endl;

		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete str1;
		return object;
	}
	return NULL;

}
//! Cria um novo objeto CString adicionado a ele uma nova string no final separada por ponto
Ast::CValue * CAstManager::addToStringDot(Ast::CString * value, double number){
	if (this->isValidSection()) {
		//! converte double to string
		::std::ostringstream oss;
		oss << number;
		string *temp = new string(value->toString2());
		temp->append(".");
		temp->append(oss.str());
		Debug::debug(Debug::parsers,__FUNCTION__) << "NEW // String:" <<temp->c_str() <<endl;
		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		pCurString = NULL;
		return object;
	}
	return NULL;

}


void CAstManager::addToString(string *str){
	if (!pCurString) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<*str <<endl;
		pCurString= str;

	} else {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String:" <<*str <<endl;
		string temp=" ";
		pCurString->append(temp);
		pCurString->append(*str);
	}

  }
Ast::CValue * CAstManager::makeString(){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<pCurString->c_str() <<endl;
		Ast::CString * object = new Ast::CString(this->pCurString);
		SGF::CResource::save(object);
		pCurString = NULL;
		return object;
	}
	return NULL;
  }

Ast::CValue * CAstManager::makeHelper(const string *name, CValue *id){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<name->c_str() <<endl;
		Ast::CHelper * object = new Ast::CHelper(-1,-1,*name,NULL,id);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeHelper(const string *name, CValue * expression, CValue * id){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<name->c_str() <<endl;
		Ast::CHelper * object = new Ast::CHelper(-1,-1,*name,expression,id);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeHitDefAttribute(string *atribute){
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << "Atribute: "<<atribute->c_str() <<endl;
	string out;
    out = *atribute;
    Ast::CHitDefAttribute * object = new Ast::CHitDefAttribute(-1, -1, out);
    SGF::CResource::save(object);
    return object;
	}
	return NULL;
}

Ast::CHitDefAttackAttribute * CAstManager::makeHitDefAttackAttribute(){
    if (this->isValidSection()) {
		Ast::CHitDefAttackAttribute * object = new Ast::CHitDefAttackAttribute(-1, -1);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeStringSpace(Ast::CValue * value1, Ast::CValue * value2){
	if (this->isValidSection()) {
		string *temp=new string(value1->toString());
		temp->append(" ");
		temp->append(value2->toString());
		Debug::debug(Debug::parsers,__FUNCTION__) << "NEW // String:" <<temp->c_str() <<endl;
		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		//values will be deletesd by th Garbage collector
		pCurString = NULL;
		return object;
	}
	return NULL;
	
}
	
//! Cria concatena dois objetos CString num terceiro
Ast::CValue * CAstManager::makeStringSpace(Ast::CString * value1, Ast::CString * value2){
	if (this->isValidSection()) {
		string *temp=new string(value1->toString2());
		temp->append(" ");
		temp->append(value2->toString2());
		Debug::debug(Debug::parsers,__FUNCTION__) << "NEW // String:" <<temp->c_str() <<endl;
		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		//values will be deletesd by th Garbage collector
		pCurString = NULL;
		return object;
	}
	return NULL;

}
Ast::CValue * CAstManager::makeString(string *str){
	if (this->isValidSection()) {
		//string temp= ::Util::withoutQuote(*str);
		//!this is because not defined is a string that willbe destructed by bison.
		if(*str=="Not Defined"){
		string *temp=new string("Not Defined");
		str=temp;
		}

		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<str->c_str() <<endl;
		Ast::CString * object = new Ast::CString(Util::withoutQuote(str));
		SGF::CResource::save(object);
		pCurString = NULL;
		return object;
	}
	return NULL;
  }
Ast::CValue * CAstManager::makeString(string str){
	if (this->isValidSection()) {
		//string temp= ::Util::withoutQuote(*str);
		//!this is because not defined is a string that willbe destructed by bison.
		if(str=="Not Defined"){
		//string *temp=new string("Not Defined");
		str="Not Defined";
		}
		string *newstring=new string(str);
		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<str.c_str() <<endl;
		Ast::CString * object = new Ast::CString(Util::withoutQuote(newstring));
		SGF::CResource::save(object);
		pCurString = NULL;
		return object;
	}
	return NULL;
  }
Ast::CValue * CAstManager::makeString(double number){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number <<endl;
		//! converte double to string
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		Ast::CString * object = new Ast::CString(value);
		SGF::CResource::save(object);
		pCurString = NULL;
		return object;
	}
	return NULL;
}
//! concatena duas strings sem nenhum caractere entre elas
Ast::CValue * CAstManager::makeString(double number, string *str) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number <<" + String: "<<str->c_str() <<endl;
		//! converte double to string
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		value->append(*str);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< value->c_str() <<endl;
		Ast::CString * object = new Ast::CString(value);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete str;
		return object;
	}
	return NULL;
}
//! concatena as strings passadas com um espaço e cria um novo objeto CString
Ast::CValue * CAstManager::makeStringSpace(string *str1, string *str2) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String1: "<< str1->c_str() <<" + String2: "<<str2->c_str() <<endl;
		str1->append(" ");
		str1->append(*str2);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< str1->c_str() <<endl;
		Ast::CString * object = new Ast::CString(str1);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete str2;
		return object;
	}
	return NULL;
}
//! concatena as strings passadas com um espaço e cria um novo objeto CString

Ast::CValue * CAstManager::makeStringSpace(string *str1, double number){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<str1->c_str() <<" Number: "<< number<<endl;
		//! converte double to string
		string *temp = new string(str1->c_str());
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		temp->append(" ");
		temp->append(*value);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< temp->c_str() <<endl;
		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete value;
		delete str1;
		return object;
	}
	return NULL;
}
//! concatena as strings passadas com um espaço e cria um novo objeto CString

Ast::CValue * CAstManager::makeStringSpace(double number, string *str1){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number <<" + String: "<<str1->c_str() <<endl;
		//! converte double to string
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		value->append(" ");
		value->append(*str1);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< value->c_str() <<endl;
		Ast::CString * object = new Ast::CString(value);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete str1;
		return object;
	}
	return NULL;
}
//! concatena as strings passadas com um ponto e cria um novo objeto CString
Ast::CValue * CAstManager::makeStringDot(string *str1, string *str2) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String1: "<< str1->c_str() <<" + String2: "<<str2->c_str() <<endl;
		str1->append(".");
		str1->append(*str2);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< str1->c_str() <<endl;
		Ast::CString * object = new Ast::CString(str1);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete str2;
		return object;
	}
	return NULL;
}
//! concatena as strings passadas com um espaço e cria um novo objeto CString

Ast::CValue * CAstManager::makeStringDot(string *str1, double number){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "String: "<<str1->c_str() <<" Number: "<< number<<endl;
		//! converte double to string
		string *temp = new string(str1->c_str());
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		temp->append(".");
		temp->append(*value);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< temp->c_str() <<endl;
		Ast::CString * object = new Ast::CString(temp);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete value;
		delete str1;
		return object;
	}
	return NULL;
}
//! concatena as strings passadas com um espaço e cria um novo objeto CString

Ast::CValue * CAstManager::makeStringDot(double number, string *str1){
if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Number: "<< number <<" + String: "<<str1->c_str() <<endl;
		//! converte double to string
		::std::ostringstream oss;
		oss << number;
		string *value = new string(oss.str());
		value->append(".");
		value->append(*str1);
		Debug::debug(Debug::parsers,__FUNCTION__) << "New String: "<< value->c_str() <<endl;
		Ast::CString * object = new Ast::CString(value);
		SGF::CResource::save(object);
		pCurString = NULL;
		delete str1;
		return object;
	}
	return NULL;
}


//! Cria um objeto de teclas combinadas CKeyCombined
Ast::CKey * CAstManager::makeKeyCombined(string *str1, string *str2){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << " key1: "<< str1->c_str()<<" key 2: "<< str2->c_str()<<endl;
		Ast::CKey * key = new Ast::CKeyCombined(makeKey(str1->c_str()), makeKey(str2->c_str()));
		SGF::CResource::save(key);
		return key;
	}
	return NULL;
}
Ast::CKey * CAstManager::addCombinedKey(Ast::CKey *key1, string *str2){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << " key1: "<< key1->toString() <<" key 2: "<< str2->c_str()<<endl;
		Ast::CKey * key = new Ast::CKeyCombined(key1, makeKey(str2->c_str()));
		SGF::CResource::save(key);
		return key1;
	}
	return NULL;
}
Ast::CValue * CAstManager::makeKeyList(){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << " thisiskey: "<< thisiskey <<" keys vector size: "<< CurrentKeys.size()<<endl;
	
		if (!CurrentKeys.empty() && thisiskey) {
	
		vector<Ast::CKey*> all;
		vector<Ast::CKey*>::iterator it;

		for (it = CurrentKeys.begin(); it != CurrentKeys.end(); it++){
			Ast::CKey * key = (*it);
			all.push_back(key);
		}

		Ast::CKey * object = new Ast::CKeyList(all);
		SGF::CResource::save(object);
		CurrentKeys.clear();
		return object;
		}
	}
	return NULL; //to avoid compiler complain

}

void CAstManager::addKeyToList(Ast::CKey *key){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "Adding key: "<< key->toString()<<" to vector"<< endl;
		this->CurrentKeys.push_back(key);
	}

}


Ast::CValue *CAstManager::makePostfixExpression(CStack *nodes) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) <<  endl;
		//! make a copy of nodes because it will be destroied by bison.
		//Ast::CStack newnodes = *nodes;
		Ast::CExpressionPostfix * expression = new Ast::CExpressionPostfix(nodes);
		SGF::CResource::save(expression);
		return expression;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeUnaryExpression(CValue *value, const string & operando){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "BEGIN" << endl;
		//! make a copy of nodes because it will be destroied by bison.
		Ast::CExpressionUnary::UnaryType type;
		if(operando=="MINUS") {
			type = Ast::CExpressionUnary::Minus;
		}else if(operando=="NEGATION") {
			type =Ast::CExpressionUnary::Negation;
		}else if(operando=="NOT") {
			type = Ast::CExpressionUnary::Not;
		}
		Ast::CExpressionUnary * expression = new Ast::CExpressionUnary(type,value);
		SGF::CResource::save(expression);
		return expression;
	}
	return NULL;
}
Ast::CValue *CAstManager::makeStringFromKey(Ast::CKey *key){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "TODO: Make String from key"<< key->toString()<< endl;
		string *temp = new string(key->toString());
		Ast::CString * expression = new Ast::CString(temp);
		SGF::CResource::save(expression);
		return expression;
	}
	return NULL;
}
Ast::CKey * CAstManager::makeKey(const char * value){
    if (this->isValidSection()) {
		Ast::CKey * key = new Ast::CKeySingle(value);
		SGF::CResource::save(key);
		return key;
	}
	return NULL;
}

Ast::CKey * CAstManager::makeKey(string * value){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "key: "<< value->c_str()<<endl;
		Ast::CKey * key = new Ast::CKeySingle(value->c_str());
		SGF::CResource::save(key);
		return key;
	}
	return NULL;
}



Ast::CKey * CAstManager::applyKeyModifiers( Ast::CKey * key){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "current modifiers size: "<< CurrentModifiers.size()<<  endl;

		vector<my_key_modifier>::iterator it;
		for (it = CurrentModifiers.begin(); it != CurrentModifiers.end(); it++){
			key= makeKeyModifier(key,(*it).modifier,(*it).ticks);

		}
		CurrentModifiers.clear();
		return key;
	}
	return NULL;
}

Ast::CKey * CAstManager::makeKeyModifier(Ast::CKey * in, Ast::CKeyModifier::ModifierType type, int ticks){
    if (this->isValidSection()) {
		Ast::CKey * modded = new Ast::CKeyModifier(type, in, ticks);
		SGF::CResource::save(modded);
		return modded;
	}
	return NULL;
}

void CAstManager::addHeldDownKeyModifier(int ticks) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << endl;
		vector<my_key_modifier>::iterator it;
		my_key_modifier keymodifier;
		keymodifier.modifier=Ast::CKeyModifier::MustBeHeldDown;
		keymodifier.ticks=ticks;
		 it = CurrentModifiers.begin();
		 it = CurrentModifiers.insert ( it , keymodifier );
	}
	
}
void CAstManager::addDirectionKeyModifier(int ticks) {
	if (this->isValidSection()) {
	Debug::debug(Debug::parsers,__FUNCTION__) << endl;
	vector<my_key_modifier>::iterator it;
	my_key_modifier keymodifier;
	keymodifier.modifier=Ast::CKeyModifier::Direction;
	keymodifier.ticks=ticks;
	it = CurrentModifiers.begin();
     it = CurrentModifiers.insert ( it , keymodifier );
	}
}
void CAstManager::addReleaseKeyModifier(int ticks) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << endl;
		vector<my_key_modifier>::iterator it;
		my_key_modifier keymodifier;
		keymodifier.modifier=Ast::CKeyModifier::Release;
		keymodifier.ticks=ticks;
		it = CurrentModifiers.begin();
		it = CurrentModifiers.insert ( it , keymodifier );
	}
}
void CAstManager::addOnlyKeyModifier(int ticks) {
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << endl;
		vector<my_key_modifier>::iterator it;
		my_key_modifier keymodifier;
		keymodifier.modifier=Ast::CKeyModifier::Only;
		keymodifier.ticks=ticks;
		it = CurrentModifiers.begin();
		it = CurrentModifiers.insert ( it , keymodifier );
	}
	
}
//=====================================

Ast::CValue * CAstManager::makeExpressionAnd(const CValue * left, const CValue * right){
   if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "left: " <<left->toString().c_str() <<" right: " <<right->toString().c_str()<<endl;
		Ast::CExpressionInfix * object = new CExpressionInfix(Ast::CExpressionInfix::And, left, right);
		SGF::CResource::save(object);
		return object;
   }
   return NULL;
}
Ast::CValue * CAstManager::makeExpressionEquals(CValue *left,CValue *right){
	if (this->isValidSection()) {
		Debug::debug(Debug::parsers,__FUNCTION__) << "left: " <<left->toString().c_str() <<" right: " <<right->toString().c_str()<<endl;
		Ast::CExpressionInfix * object = new CExpressionInfix(Ast::CExpressionInfix::Equals, left, right);
		SGF::CResource::save(object);
		return object;
	}
	return NULL;
}
/** @fn CAstManager::makeRange(int type, double valor1, double valor2)
@brief Cria um objeto tipo CRange 
@param int type: tipo de range
				 1 - AllInclusive
				 2 - AllExclusive
				 3 - LeftInclusiveRightExclusive
				 4 - LeftExclusiveRightInclusive
@param double valor1: valor inicial do range
@param double valor2: valor final do range
@return ponteiro CValue para o range criado
@warning nenhum aviso
**/
Ast::CValue * CAstManager::makeRange(int type, double valor1, double valor2){
	if (this->isValidSection()) {
	   Debug::debug(Debug::parsers,__FUNCTION__) << "valor1: " <<valor1 <<" valor2: " <<valor2<<endl;
	   Ast::CRange::RangeType rangetype;
	   switch (type) {
			case 1:
					 rangetype=Ast::CRange::AllInclusive;
					 break;
			case 2:
					  rangetype=Ast::CRange::AllExclusive;
					 break;
			case 3:
					 rangetype=Ast::CRange::LeftInclusiveRightExclusive;
					 break;
			case 4:
					 rangetype=Ast::CRange::LeftExclusiveRightInclusive;
					 break;

	   }
    Ast::CNumber * object1 = new Ast::CNumber(valor1);
   	SGF::CResource::save(object1);
    Ast::CNumber * object2 = new Ast::CNumber(valor2);
   	SGF::CResource::save(object2);
	Ast::CRange * object = new Ast::CRange(rangetype,object1,object2);
   	SGF::CResource::save(object);
	return object;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeArgument(int line, int column, int index){
	if (this->isValidSection()) {
	  Ast::CValue * argument = new Ast::CArgument(line, column, index);
	  SGF::CResource::save(argument);
	  return argument;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeResource(CValue * value, bool fight, bool own){
    if (this->isValidSection()) {
		Ast::CResource * resource = new Ast::CResource(-1, -1, value, fight, own);
		SGF::CResource::save(resource);
		return resource;
	}
	return NULL;
}

Ast::CValue * CAstManager::makeOwnResource(CValue * number){
	if (this->isValidSection()) {
    return makeResource(number, false, true);
	}
	return NULL;
}
    
Ast::CValue * CAstManager::makeFightResource(CValue * number){
	if (this->isValidSection()) {
    return makeResource(number, true, false);
	}
	return NULL;
}
}
} //end SGF
