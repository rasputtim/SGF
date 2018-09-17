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

#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <iostream>

#include "util/SGF_Token.h"
#include "exceptions/all.h"
#include "util/SGF_Debug.h"
#include "SGF_Global.h"
//#include "graphics/all.h"
#include "util/XmlNode/XmlNode.h"

using namespace std;


static bool needQuotes(const std::string & what){

    /* if it begins with a " and ends with " then it doesnt need more quotes */
    if (what.size() > 0 && what[0] == '"' && what[what.size() - 1] == '"'){
        return false;
    }

    /* ripped from tokenreader.cpp, maybe use a variable for nice sharing.. */
    const char * alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_!:";
    for (unsigned int position = 0; position < what.size(); position++){
        if (strchr(alpha, what[position]) == NULL){
            return true;
        }

        /*
        if (what[position] == '"' ||
            what[position] == ' ' ||
            (unsigned char) what[position] > 127){
            return true;
        }
        */
    }

    return false;
}

/* put quotes around a string if there are spaces in it */
static string quoteify(const string & rhs){
    if (needQuotes(rhs)){
        return string("\"") + rhs + string("\"");
    }

    return rhs;
}


SGF::Token::Token():
num_token(1),
parent( NULL ),
own(true){
	Debug::debug(2700,__FUNCTION__) << "Construtor // " << "name: HEAD" << endl;

	name = "HEAD";
}

SGF::Token::Token( string tok, bool parse ):
num_token( 1 ),
parent( NULL ),
own(true){
	Debug::debug(2700,__FUNCTION__) << "// Construtor // PARAMS:" << "string: " << tok << "Parse: " << parse << endl;

	/* legacy code, not used much */
	if ( !parse ){
		name = tok;
		Debug::debug(2700,__FUNCTION__) << "( string tok, bool parse ) // name:" << name << endl;

		while ( name.find(' ' ) == 0 )
			name.erase( 0, 1 );
		// lowerCase( name );
		return;
	}

}

SGF::Token::Token(Token const & copy):
num_token(1),
parent(copy.parent),
own(false){
Debug::debug(2700,__FUNCTION__) << "(Token const & copy) // Construtor // PARAMS:" << "Copy: " << copy.name  << endl;

	this->tokens = copy.tokens;
    this->name = copy.name;
    this->filename = copy.filename;
}

/* Dump token to the screen */
void SGF::Token::print( const string space )const {
	cout<<space<<"Token: "<< getName() << endl;
	for ( signed int i = 0; i < numTokens(); i++ ){
		Token * x = getToken( i );
		x->print( space + " |--" );
	}
}

//! print the token into XML Format
void SGF::Token::toString( ofstream & stream, const string & space )const {
	// considerar usar http://xerces.apache.org/xerces-c/domprint-3.html
 
	XmlTools::UTL_PutXmlHeader(stream);
	printNodes(stream, space);
	
}

void SGF::Token::toString(ostream & stream, const string & space) const {
    if (numTokens() == -1){
        stream << quoteify(getName());
    } else {
        stream << endl;
        stream << space << "(" << quoteify(getName());
        for ( signed int i = 0; i < numTokens(); i++ ){
            Token * x = getToken(i);
            stream << " ";
            x->toString( stream, space + "  " );
        }
        stream << ")";
    }
}


std::string SGF::Token::toString() const {
    std::ostringstream out;
    toString(out, "");
    return out.str();
}
    
std::string SGF::Token::toStringCompact() const {
    std::ostringstream out;
    toStringCompact(out);
    return out.str();
}

void SGF::Token::toStringCompact(ostream & stream) const {
    if (numTokens() == -1){
        stream << quoteify(getName());
    } else {
        stream << "(" << quoteify(getName());
        for (signed int i = 0; i < numTokens(); i++){
            Token * x = getToken(i);
            stream << " ";
            x->toStringCompact(stream);
        }
        stream << ")";
    }
}
void SGF::Token::printNodes( ofstream & stream, const string & space )const {
	if ( numTokens() == -1 ){
		// Imprime o Valor final do Token
		stream << " "+getName() << endl;
	}else {
	START_NODE(stream, getName().c_str());
	for ( signed int i = 0; i < numTokens(); i++ ){
			Token * x = getToken( i );
			x->printNodes( stream, space );
		}

   CLOSE_NODE

  }
}

/* helper function */
string SGF::Token::lowerCase( const string & s ) const {
    string ret = s;
    for ( unsigned int q = 0; q < s.length(); q++ ){
        if ( s[q] >= 'A' && s[q] <= 'Z' ){
            ret[q] = s[q] - 'A' + 'a';
        } else {
            // ret[q] = s[q];
        }
    }
    return ret;
}
/* Return next token and increment the internal position
 * of the current token
 */

SGF::Token * SGF::Token::readToken(){
	if ( num_token < tokens.size() ){
		return tokens[ num_token++ ];
	}
	return NULL;
}

bool SGF::Token::hasTokens()const {
	return num_token < tokens.size();
}



vector<const SGF::Token *> SGF::Token::findTokens(const string & path)const {
    vector<const Token *> found;
    if (path == ""){
        return found;
    }

    size_t find = path.find('/');
    string self;
    if (find == string::npos){
        self = path;
    } else {
        self = path.substr(0, find);
    }

    /* a name of `_' means succeed with the current token no matter
     * what its called.
     * `*' means test all children. this is useful if you dont know where in the
     * tree a given node lives.
     * (... (... (... (foo ...))))
     * *\foo would find the foo token (I used backslash because forward slash will
     * kill the current c++ comment)
     */
    if (self == "*"){
        /* `*' and 'blah/stuff', test the current token for 'blah/stuff' */
        string rest = path.substr(find+1);
        vector<const Token*> more = findTokens(rest);
        found.insert(found.end(), more.begin(), more.end());
        /* then test all children for the original path */
        for (int i = 0; i < numTokens(); i++){
            Token * next = getToken(i);
            if (next != NULL){
                vector<const Token *> more = next->findTokens(path);
                found.insert(found.end(), more.begin(), more.end());
            }
        }
    } else if (self == "_" || *this == self){
        if (find == string::npos){
            found.push_back(this);
            if (found[0] != this){
                cout << "internal consistency error!!!!" << endl;
                throw exception();
            }
        } else {
            string rest = path.substr(find+1);
            for (int i = 0; i < numTokens(); i++){
                Token * next = getToken(i);
                if (next != NULL){
                    vector<const Token *> more = next->findTokens(rest);
                    found.insert(found.end(), more.begin(), more.end());
                }
            }
        }
    }

    return found;
}

SGF::TokenMatcher & SGF::Token::getMatcher(const string & subject)const {
    //inicializa a classe TokenMatcher com um vector<Token *> retornado por findtokens
	// ind tokens retorna um vector<Token *>
	Debug::debug(3) <<"Token::getMatcher(const string & subject)// inicializa a classe TokenMatcher com um vector<Token *> retornado por findtokens" <<endl;
	
	TokenMatcher matcher(findTokens(subject));
    Debug::debug(3) <<"Token::getMatcher(const string & subject)// matcher= "<< &matcher <<endl;
	
	Debug::debug(3) <<"Token::getMatcher(const string & subject)// matcher= "<< (*matcher.current)->getName() <<endl;
	//retorna a classe criada
	return matcher;
}

SGF::Token * SGF::Token::findToken(const string & path){
    vector<const Token *> all = findTokens(path);
    if (all.size() == 0){
        return NULL;
    }
    return (Token*) all[0];

}

namespace SGF {
const Token * Token::findToken(const string & path)const {
    vector<const Token *> all = findTokens(path);
    if (all.size() == 0){
        return NULL;
    }
    return all[0];
}



Token * SGF::Token::getToken( unsigned int n ) const {
	int q = numTokens();
	if ( q == -1 ) return NULL;
	if ( n >= 0 && (signed int)n < q )
		return tokens[n+1];
	return NULL;
}

/* If the token has children then the name of this token
 * is the name of the first child token.
 * Otherwise, the name is this token's name
 */
const string & Token::getName() const {
	if ( numTokens() != -1 ){
		return tokens[0]->_getName();
	}
	// cout<<"No tokens!!"<<endl;
	return name;
}

const Token * Token::getParent() const {
	return this->parent;
}
Token * Token::getParent(){
    return parent;
}
const string Token::getLineage() const {
	if ( getParent() != NULL ){
		return getParent()->getLineage() + " -> " + getName();
	}

	return getName();
}

/* A token's identity is its name
 */
bool Token::operator== ( const string & rhs ){
	return lowerCase( getName() )  == lowerCase( rhs );
}

bool Token::operator== ( const string & rhs ) const{
	return lowerCase( getName() )  == lowerCase( rhs );
}

bool Token::operator!= ( const string & rhs )const {
	return !( *this == rhs );
}
/*
// extracting operators 
Token & Token::operator>>( Token * & rhs ) throw( CTokenException ){
	Token * x = readToken();
	if ( x == NULL ){
		throw CTokenException(__FILE__, __LINE__, getFileName() + ": " + string("Tried to read a token from ") + this->getName() + string(" but there are no more elements") );
	}
	rhs = x;
	return *this;
}

Token & Token::operator>>( string & rhs ) throw( CTokenException ){
	Token * l = readToken();
	if (l == NULL){
		throw CTokenException(__FILE__, __LINE__, getFileName() + ":" + string("Tried to read a string from '") + this->getLineage() + string("' but there no more elements") );
	}
        if (!l->isData()){
            throw CTokenException(__FILE__, __LINE__,getFileName() + ":" + string(" Element is not a string"));
        }
	rhs = l->getName();

	// rhs = getName();

	return *this;
}

Token & Token::operator>>( int & rhs ) throw( CTokenException ){
	Token * l = readToken();
	if ( l == NULL ){
		throw CTokenException(__FILE__, __LINE__, getFileName() + ": " + string("Tried to read an int from ") + this->getLineage() + string(" but there are no more elements") );
	}
        if (!l->isData()){
            throw CTokenException(__FILE__, __LINE__,getFileName() + ":" + string(" Element is not a string"));
        }
	istringstream is ( l->getName() );
	is >> rhs;
	return *this;
}

Token & Token::operator>>( double & rhs ) throw( CTokenException ){
	Token * l = readToken();
	if ( l == NULL ){
		throw CTokenException(__FILE__, __LINE__, getFileName() + ": " + string("Tried to read a double from ") + this->getLineage() + string(" but there no more elements") );
	}
        if (!l->isData()){
            throw CTokenException(__FILE__, __LINE__,getFileName() + ":" + string(" Element is not a string"));
        }
	istringstream is ( l->getName() );
	is >> rhs;
	return *this;
}

Token & Token::operator>>( bool & rhs ) throw( CTokenException ){
	Token * l = readToken();
	if ( l == NULL ){
		throw CTokenException(__FILE__, __LINE__, getFileName() + ": " + string("Tried to read a bool from ") + this->getLineage() + string(" but there no more elements") );
	}
        if (!l->isData()){
            throw CTokenException(__FILE__, __LINE__,getFileName() + ":" + string(" Element is not a string"));
        }
	istringstream is ( l->getName() );
	is >> rhs;
	return *this;
}

*/
void Token::setFile( const string & s ){
	filename = s;
}

const string Token::getFileName() const {
	if ( parent ){
		return parent->getFileName();
	} else {
		return filename;
	}
}


void Token::addToken(Token * t) throw (CTokenException){
Debug::debug(2700,__FUNCTION__) << "Token::addToken(Token * t) // BEGIN // PARAMS:" << "Token: " << t  << endl;

	if (!own){
        throw CTokenException(__FILE__, __LINE__,"This token does not own its own tokens, so you cannot add tokens to it");
    }
    tokens.push_back( t );
}

/* put quotes around a string if there are spaces in it */
static string quoteify(const string & rhs){
    if (rhs.find(' ') != string::npos){
        return "\"" + rhs + "\"";
    }
    return rhs;
}

Token & Token::operator<<( const string rhs ){
	Token * n = new Token(quoteify(rhs), false );
	this->addToken(n);
	return *this;
}

Token & Token::operator<<( const int rhs ){
	ostringstream o;
	o << rhs;
	return *this << o.str();
}

Token & Token::operator<<( const double rhs ){
	ostringstream o;
	o << rhs;
	return *this << o.str();
}

Token * Token::copy(){
    Token * token = new Token();
    token->filename = this->filename;
    token->name = this->name;
    for (vector<Token *>::iterator it = this->tokens.begin(); it != this->tokens.end(); it++){
        Token * him = (*it)->copy();
        him->setParent(token);
        token->addToken(him);
    }
    return token;
}

/* Delete tokens that are commented.
 * A commented token has a '!' character as the first
 * character in the name, e.g:
 * (!a_token (child_token 2))
 */
void Token::finalize(){
	for ( vector< Token * >::iterator it = tokens.begin(); it != tokens.end(); ){
		Token * t = *it;
		if ( t->getName().find('!') == 0 ){
			delete t;
			it = tokens.erase( it );
		} else {
			t->finalize();
			it++;
		}
	}
}

//======================NEW ===============

Token * Token::newToken(){
    Token * token = new Token();
    addToken(token);
    return token;
}

TokenView Token::view() const {
    vector<const Token*> out;
    out.insert(out.end(), tokens.begin(), tokens.end());
    return TokenView(out);
}

static bool needQuotes(const string & what){
    /* ripped from tokenreader.cpp, maybe use a variable for nice sharing.. */
    const char * alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_!:";
    for (unsigned int position = 0; position < what.size(); position++){
        if (strchr(alpha, what[position]) == NULL){
            return true;
        }

        /*
        if (what[position] == '"' ||
            what[position] == ' ' ||
            (unsigned char) what[position] > 127){
            return true;
        }
        */
    }

    return false;
}


Token & Token::operator<<(Token * token){
    if (!own){
        throw CTokenException(__FILE__, __LINE__, "Cannot add tokens to a token you don't own");
    }
    this->addToken(token);
    return *this;
}


// =============  TokenView  ===================
TokenView::TokenView(vector<const Token *> tokens):
tokens(tokens){
    current = this->tokens.begin();
    if (current != this->tokens.end()){
        current++;
    }
}

TokenView::TokenView(const TokenView & view):
tokens(view.tokens){
    current = this->tokens.begin();
    if (current != this->tokens.end()){
        current++;
    }
}
    
bool TokenView::hasMore() const {
    return current != tokens.end();
}
    
TokenView & TokenView::operator=(const TokenView & view){
    tokens = view.tokens;
    current = tokens.begin();
    if (current != tokens.end()){
        current++;
    }
    return *this;
}

TokenView & TokenView::operator>>(string & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(string & item) // No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(string & item) // Token is not a datum");
    }
    item = child->getName();
    current++;
    return *this;
}

TokenView & TokenView::operator>>(int & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(int & item) // No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(int & item) // Token is not a datum");
    }
    istringstream out(child->getName());
    out >> item;
    current++;
    return *this;
}

TokenView & TokenView::operator>>(Uint8 & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(int & item) // No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(int & item) // Token is not a datum");
    }
    istringstream out(child->getName());
    out >> item;
    current++;
    return *this;
}

TokenView & TokenView::operator>>(unsigned int & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(int & item) // No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(int & item) // Token is not a datum");
    }
    istringstream out(child->getName());
    out >> item;
    current++;
    return *this;
}

TokenView & TokenView::operator>>(double & item){
    if (current == tokens.end()){
       throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(double & item) //  No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(double & item) //  Token is not a datum");
    }
    istringstream out(child->getName());
    out >> item;
    current++;
    return *this;
}

TokenView & TokenView::operator>>(bool & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(bool & item) // No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(bool & item) // Token is not a datum");
    }
    istringstream out(child->getName());
    out >> item;
    current++;
    return *this;
}

    
TokenView & TokenView::operator>>(const Token* & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "TokenView::operator>>(const Token* & item) // No more elements");
    }
    const Token * child = *current;
    /*
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__,__FILE__, __LINE__, "Token is not a datum");
    }
    */
    item = child;
    current++;
    return *this;
}
//new ones

TokenView & TokenView::operator>>(uint64_t & item){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "No more elements");
    }
    const Token * child = *current;
    if (!child->isData()){
        throw CTokenException(__FILE__, __LINE__, "Token is not a datum");
    }
    istringstream out(child->getName());
    out >> item;
    current++;
    return *this;
}


const Token * TokenView::next(){
    if (current == tokens.end()){
        throw CTokenException(__FILE__, __LINE__, "No more elements");
    }
    const Token * child = *current;
    current++;
    return child;
}

void Token::removeToken(Token * token){
    for (vector<Token*>::iterator it = tokens.begin(); it != tokens.end(); it++){
        Token * what = *it;
        if (token == what){
            /* Found the token. If we own it then delete it, otherwise just
             * remove it from the list and return.
             */
            if (own){
                delete what;
            }
            it = tokens.erase(it);
            return;
        }
    }
}

//==========================================


Token::~Token(){
    if (own){
        for ( vector< Token * >::iterator it = tokens.begin(); it != tokens.end(); it++ ){
            delete *it;
        }
    }
}

TokenMatcher::TokenMatcher(){
    Debug::debug(3) <<"TokenMatcher Constructor "<<endl;
	throw std::exception();
}
/*
TokenMatcher & TokenMatcher::operator=(const TokenMatcher & matcher){
	Debug::debug(3) <<"TokenMatcher::operator= - defining current: " <<  &matcher.tokens<<endl;
	//Global::PrintMessage("TokenMatcher & TokenMatcher tokens = %s",matcher.tokens);

	tokens = matcher.tokens;
    current = tokens.begin();
    return *this;
}*/
TokenMatcher & TokenMatcher::operator=(const TokenMatcher & matcher){
	Debug::debug(3) <<"TokenMatcher::operator= - defining current: " <<  &matcher.tokens<<endl;
	//Global::PrintMessage("TokenMatcher & TokenMatcher tokens = %s",matcher.tokens);

	tokens = matcher.tokens;
    current = tokens.begin();
    return *this;
}
TokenMatcher::TokenMatcher(vector<const Token*> tokens):
tokens(tokens){
	Debug::debug(3) <<"TokenMatcher::TokenMatcher(vector<const Token*> tokens): "<< &tokens <<endl;
	
	current = this->tokens.begin();
	Debug::debug(3) <<"TokenMatcher::TokenMatcher(vector<const Token*> tokens)// current:" << (*current)->getName() <<endl;
	
}

} //end SGF