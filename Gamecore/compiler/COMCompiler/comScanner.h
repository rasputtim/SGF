/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
#ifndef COM_SCANNER_H
#define COM_SCANNER_H


//#ifndef __FLEX_LEXER_H
//#define yyFlexLexer ComFlexLexer
#include "SGF_COMFlexLexer.h"
//#undef yyFlexLexer
//#endif


// Override the interface for yylex since we namespaced it

#undef YY_DECL
#define YY_DECL    ComCompiler::Parser::token_type				\
    ComCompiler::CScanner::lex(				\
	ComCompiler::Parser::semantic_type* yylval,		\
	ComCompiler::Parser::location_type* yylloc		\
    )



// Include Bison for types / tokens
// A classe Parser � criada pelo Bison no arquivo parser.tab.h
// os tipos s�o definidos na union criada pelo BISON
#include "comparser.tab.h"


namespace ComCompiler {
	
		
class CScanner : public ComFlexLexer {
/** Scanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to ExampleFlexLexer. However we change the context of the generated
 * yylex() function to be contained within the Scanner class. This is required
 * because the yylex() defined in ExampleFlexLexer has no parameters. */
//class Scanner : public ExampleFlexLexer {

public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    CScanner(std::istream* arg_yyin = 0,
	    std::ostream* arg_yyout = 0);

    /** Required for virtual functions */
    virtual ~CScanner();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated bison parser then
     * calls this virtual function to fetch new tokens. */
    virtual Parser::token_type lex(
	Parser::semantic_type* yylval,
	Parser::location_type* yylloc
	);

    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);
	float toFloat();
	float toFloatX();
	void destroyComment();
};


}
#endif