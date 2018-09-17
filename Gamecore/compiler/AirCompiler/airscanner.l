/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
%{ /*** C/C++ Declarations ***/

	#include <string>
    #include "../../util/SGF_Debug.h"
	#include "scanner.h"
	
	/* import the parser's token type into a local typedef */
	
	typedef AirCompiler::Parser::token token;
	typedef AirCompiler::Parser::token_type token_type;
    /* By default yylex returns int, we use token_type. Unfortunately yyterminate
    * by default returns 0, which is not of token_type. */
    #define yyterminate() return token::END

	
      // used to keep track of location
   	/* The following paragraph suffices to track locations accurately. Each time
 	* yylex is invoked, the begin position is moved onto the end position. */

	#define YY_USER_ACTION yylloc->columns(yyleng);
	/* This disables inclusion of unistd.h, which is not available under Visual C++
 	* on Win32. The C++ scanner uses STL streams instead. */

	#define YY_NO_UNISTD_H


%}
/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}
/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="Air"
%option nodefault noyywrap yyclass="CScanner" c++
%option caseless

DIGIT	[0123456789]
STR		\"[^\"]*\"
CHAR	[a-zA-z_]
blank   [\t]

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */


%{
    // reset location
    yylloc->step();
%}


([-+])?({DIGIT}+|{DIGIT}*\.{DIGIT}+) {  yylval->doubleVal = atof(yytext);
    SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer DOUBLE= "<<  yylval->doubleVal <<endl;
    return token::DOUBLE; }


\; { DestroyComment(); SGF::Debug::debug(703) <<"Lexer Token: "<< "COMMENT" <<endl; }
	       


"Begin"			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Begin= "<<  "BEGIN" <<endl;
				yylval->stringVal = new std::string("Begin");
				return token::ACBEGIN;}
"Action"		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Action= "<<  "ACTION" <<endl;
				yylval->stringVal = new std::string("Action");
				return token::ACTION;}
"Loopstart"		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Loopstart= "<<  "LOOPSTART" <<endl;
				yylval->stringVal = new std::string("loopstart");
				return token::LOOPSTART;}
"Clsn2Default"	{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Clns2Default= "<<  "COLLISION_DEFENSE_DEFAULT" <<endl;
				yylval->stringVal = new std::string("clsn2default");
				return token::COLLISION_DEFENSE_DEFAULT; }
"Clsn1Default"	{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Clns1Default= "<<  "COLLISION_ATTACK_DEFAULT" <<endl;
				yylval->stringVal = new std::string("clsn1default");
				return token::COLLISION_ATTACK_DEFAULT; }
"Clsn2"			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Clns2= "<<  "COLLISION_DEFENSE" <<endl;
				yylval->stringVal = new std::string("clsn2");
				return token::COLLISION_DEFENSE;}
"Clsn1"			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Clns1= "<<  "COLLISION_ATTACK" <<endl;
				yylval->stringVal = new std::string("clsn1");
				return token::COLLISION_ATTACK; }

"h"				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer H= "<<  "HORIZONTALFLIP" <<endl;
				yylval->stringVal = new std::string("h");
				return token::HORIZONTALFLIP;}

"v"				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer V= "<<  "VERTIKALFLIP" <<endl;
				yylval->stringVal = new std::string("v");
				return token::VERTIKALFLIP;}

"hv"|"vh"		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer HV= "<<  "HVFLIP" <<endl;
				yylval->stringVal = new std::string("hv");
				return token::HVFLIP;}

"a"				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer A= "<<  "COLOR_ADDITION" <<endl;
				yylval->stringVal = new std::string("a");
				return token::COLOR_ADDITION;}

"s"				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer S= "<<  "COLOR_SUBTRACT" <<endl;
				yylval->stringVal = new std::string("s");
				return token::COLOR_SUBTRACT;}

"a"{DIGIT}+		{
				yylval->stringVal = new std::string(yytext, yyleng);
				SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer A+Digit= "<<  "ALPHA_BLEND_SHORTHAND: "<< yylval->stringVal->c_str() <<endl;
				return token::ALPHA_BLEND_SHORTHAND;} 

"as"{DIGIT}+"d"{DIGIT}+ {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer AS+Digit = "<<  "ALPHA_BLEND" <<endl;
                yylval->stringVal = new std::string(yytext, yyleng);
				return token::ALPHA_BLEND;}

","				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer ;= "<<   yytext[0] <<endl;
				 return token_type (yytext[0]);}

[+*/]			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Operation= "<<  *yytext <<endl;
				return token_type (yytext[0]);}
"-"				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer -= "<<  *yytext <<endl;
				 return token_type (yytext[0]);}
"("				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer (= "<<  yytext[0] <<endl;
				return token_type (yytext[0]);}
")"				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer )= "<< yytext[0] <<endl;
				return token_type (yytext[0]);}
":"				 {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer := "<<  yytext[0] <<endl;
				return token_type (yytext[0]); }
"="				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = = "<<  yytext[0] <<endl;
				 return token_type (yytext[0]); }

"["				{	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer[ = "<<  yytext[0] <<endl;
				return token_type (yytext[0]);  }
"]"				{	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer ]= "<<  yytext[0] <<endl;
				return token_type (yytext[0]);  }

{STR}			{yylval->stringVal = new std::string(yytext, yyleng);
				SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer string= "<< yylval->stringVal <<endl; }


 /* gobble up white-spaces */
{blank}+ {
    SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer blank= "<< *yytext <<endl;
    yylloc->step();
}


[\n\r]+        { yylloc->lines(yyleng); yylloc->step();
				SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer string EOL= "<< "EOL" <<endl;
				return token::EOL;
				}

[ \t]* { ; }

 /* discard all other characters */
. {
    yylloc->step();
    SGF::Debug::debug(10,__FUNCTION__) <<"Lexer Unknow caracter= "<< *yytext <<endl;
    
}
 
 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace AirCompiler {

CScanner::CScanner(std::istream* in,
		 std::ostream* out)
    : AirFlexLexer(in, out)
{
}

CScanner::~CScanner()
{
}

void CScanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

void CScanner::DestroyComment()
{
char c;
   SGF::Debug::debug(1,__FUNCTION__) << "Destroing Comment" << endl;
   c= AirFlexLexer::yyinput();
   while (c != '\n' && c != 0)
   {	
	c=AirFlexLexer::yyinput();

   }
    
}

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif
/*
int AirFlexLexer::yylex()
{
    std::cerr << "in AirFlexLexer::yylex() !" << std::endl;
    return 0;
}  
*/
/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */
/*
int AirFlexLexer::Cmdwrap()
{
    return 1;
}
*/