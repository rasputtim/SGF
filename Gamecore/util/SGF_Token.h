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
#ifndef _SGF__token_h
#define _SGF__token_h

#include <string>
#include <vector>
#include <ostream>
#include "../SGF_Config.h"
#include "../util/SGF_Debug.h"
#include "../../ExternalLibs/SDL2/include/SDL.h"  //só está aqui pela definição do Uint8
#include "../exceptions/SGF_TokenException.h"

using namespace std;
namespace SGF {

class CTokenReaderXML;
class CConfiguration;
class Token;

/**
 * \class TokenView
 *
 * \ingroup SGF_Util
 *
 * \brief Visualização de um token
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
class  SGE_API TokenView{
public:
    TokenView(vector<const Token *> tokens);
    TokenView(const TokenView & view);

    bool hasMore() const;

    TokenView & operator=(const TokenView & view);

    TokenView & operator>>(const Token* & item);
    TokenView & operator>>(string & item);
    TokenView & operator>>(int & item);
	TokenView & operator>>(Uint8 & item);
    TokenView & operator>>(unsigned int & item);
	TokenView & operator>>(double & item);
    TokenView & operator>>(bool & item);

	//new ones
	TokenView & operator>>(uint64_t & item);
    
	const Token * next();

protected:
    vector<const Token*> tokens;
    vector<const Token*>::iterator current;
};

/**
 * \class TokenMatcher
 *
 * \ingroup SGF_Util
 *
 * \brief matcher de um Token
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
class  SGE_API TokenMatcher{
public:
    TokenMatcher & operator=(const TokenMatcher & matcher);
	template <typename X1>
    bool match(X1 & obj1);

    template <typename X1, typename X2>
    bool match(X1 & obj1, X2 & obj2);

    TokenMatcher(vector<const Token*> tokens);  // devia ser protected
protected:

    explicit TokenMatcher();
    friend class Token;

    vector<const Token*> tokens;
    vector<const Token*>::iterator current;
};


/**
 * \class Token
 *
 * \ingroup SGF_Util
 *
 * \brief Uma Árvore contendo nós e seus valores
 *
 * \note pode ter 0 ou mais filhos
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
class  SGE_API Token{
public:

    typedef TokenMatcher Matcher;
	Token();
    Token(Token const & copy);
    Token(string tok, bool parse = true);
    virtual ~Token();
    /* add an existing token to the tree */
    void addToken(Token * t) throw (CTokenException);
       /* creates a new empty token and returns it */
    Token * newToken();

    /*
       inline const string & getName(){
       return name;
       }
       */
    const string & getName() const;
    const Token * getParent() const;
	Token * getParent();
    /* get the original parent, the parent with no parents */
    const Token * getRootParent() const;

    void setFile( const string & s );

    const string getFileName() const;

    const string getLineage() const;
	std::string toString() const;
    void print( const string space )const;
    void toString( ofstream & stream, const string & space )const;
	/* a pretty printed s-expression */
    void toString(std::ostream & stream, const std::string & space) const;
    
     /* no extra whitespace */
    void toStringCompact(ostream & stream) const;
	std::string toStringCompact() const;

    bool match(const string & subject)const {
        TokenMatcher matcher = getMatcher(subject);
        return false;
    }

    template <typename X>
    bool match(const string & subject, X & obj)const{
		TokenMatcher matcher(findTokens(subject));
		//TokenMatcher matcher = getMatcher(subject);
		//Debug::debug(Debug::error,__FUNCTION__) << "Template (const string & subject, X & obj) // matcher: "<< &matcher << endl;
		//Debug::debug(Debug::error,__FUNCTION__) << "Template (const string & subject, X & obj) // matcher: "<< (*matcher.current)->getName()<< endl;
		return matcher.match(obj);
    }

 template <typename X1, typename X2>
    bool match(const string & subject, X1 & obj1, X2 & obj2) const {
        //TokenMatcher matcher << getMatcher(subject);
        TokenMatcher matcher(findTokens(subject));
		return matcher.match(obj1) &&
               matcher.match(obj2);
    }

    template <typename X1, typename X2, typename X3>
    bool match(const string & subject, X1 & obj1, X2 & obj2, X3 & obj3) const {
        //TokenMatcher matcher << getMatcher(subject);
        TokenMatcher matcher(findTokens(subject));
		return matcher.match(obj1) &&
               matcher.match(obj2) &&
               matcher.match(obj3);
    }

    template <typename X1, typename X2, typename X3, typename X4>
    bool match(const string & subject, X1 & obj1, X2 & obj2, X3 & obj3, X4 & obj4) const {
        //TokenMatcher matcher << getMatcher(subject);
        TokenMatcher matcher(findTokens(subject));
		return matcher.match(obj1) &&
               matcher.match(obj2) &&
               matcher.match(obj3) &&
               matcher.match(obj4);
    }

    template <typename X1, typename X2, typename X3, typename X4, typename X5>
    bool match(const string & subject, X1 & obj1, X2 & obj2, X3 & obj3, X4 & obj4, X5 & obj5) const {
       // TokenMatcher matcher << getMatcher(subject);
        TokenMatcher matcher(findTokens(subject));
		return matcher.match(obj1) &&
               matcher.match(obj2) &&
               matcher.match(obj3) &&
               matcher.match(obj4) &&
               matcher.match(obj5);
    }

    TokenMatcher & getMatcher(const string & subject)const;

    TokenView view() const;

    Token * getToken( unsigned int n ) const;

    /* xpath-esque searching for tokens
     * '/' delimits tokens
     * <literal> matches a token
     */
    const Token * findToken(const string & path)const ;
	Token * findToken(const string & path);

    /* find all tokens */
    vector<const Token *> findTokens(const string & path)const;

	/* Removes the given token if the current one contains it */
    void removeToken(Token * token);

    inline signed int numTokens() const {
        return tokens.size() - 1;
    }

    inline bool isData() const {
        return numTokens() == -1;
    }

    inline const vector< Token * > * getTokens() const{
        return &tokens;
    }

    inline void resetToken(){
        num_token = 1;
    }

    /* returns a deep copy of this token. the parent field is set to null */
    Token * copy();

    Token * readToken();
    bool hasTokens() const;

    bool operator== ( const string & rhs );
	bool operator== ( const string & rhs )const;
    bool operator!= ( const string & rhs )const;

    //Token & operator>>( string & rhs ) throw( CTokenException );
    //Token & operator>>( int & rhs ) throw( CTokenException );
    //Token & operator>>( double & rhs ) throw( CTokenException );
    //Token & operator>>( Token * & rhs ) throw( CTokenException );
    //Token & operator>>( bool & rhs ) throw( CTokenException );

    Token & operator<<( const string rhs );
    Token & operator<<( const int rhs );
    Token & operator<<( const double rhs );
    Token & operator<<( Token * token);

protected:


    void printNodes( ofstream & stream, const string & space )const;
    friend class TokenReader;
	friend class CTokenReaderXML;
    friend class CConfiguration;



    virtual inline const string & _getName(){
        return name;
    }

    virtual inline void setParent( Token * const parent ){
        this->parent = parent;
    }

    string lowerCase( const string & s ) const;
    void finalize();

    unsigned int num_token;
    vector< Token * > tokens;
    string filename;
    Token * parent;
    string name;
    bool own;



};



template <typename X1>
    bool TokenMatcher::match(X1 & obj1){

		//Debug::debug(Debug::error,__FUNCTION__) << "TokenMatcher::match(X1 & obj1)  " <<  endl;
		if (current == tokens.end()){
        return false;
		}

        const Token * token = *current;
        current++;

        try{
            //*token >> obj1;
			token->view() >> obj1;
            return true;
        } catch (const CTokenException & ex){
//			 Debug::debug(Debug::xml,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
        }

        return false;
    }

    template <typename X1, typename X2>
    bool TokenMatcher::match(X1 & obj1, X2 & obj2){
        if (current == tokens.end()){
            return false;
        }

        const Token * token = *current;
        current++;

        try{
            //*token >> obj1 >> obj2;
			token->view() >> obj1 >> obj2;
            return true;
        } catch (const CTokenException & ex){
			 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
        }

        return false;

    }
} //end SGF
#endif
