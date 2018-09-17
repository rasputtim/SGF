/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
%{ /*** C/C++ Declarations ***/

	#include <string>
    #include "../../util/debug.h"
	#include "scanner.h"
	
	/* import the parser's token type into a local typedef */
	
	typedef AirCompilerOld::Parser::token token;
	typedef AirCompilerOld::Parser::token_type token_type;
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

digit	[-0123456789]
STR      \"[^\"]*\"
CHAR	[a-zA-z_]
blank   [\t]

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */


%{
    // reset location
    yylloc->step();
%}



{digit}+ {
    yylval->integerVal = atoi(yytext);
    Debug::debug(603) <<"Lexer INTEGER= "<<  yylval->integerVal <<endl;
    return token::INTEGER;
}

{digit}+"."{digit}* {
    yylval->doubleVal = atof(yytext);
    Debug::debug(603) <<"Lexer DOUBLE= "<<  yylval->doubleVal <<endl;
    return token::DOUBLE;
}


","		{Debug::debug(603) <<"Lexer = "<<  *yytext <<endl;
         return token_type (yytext[0]);}
"H"     {Debug::debug(603) <<"Lexer = "<<  "HORIZONTALFLIP" <<endl;
         return token::HORIZONTALFLIP;}
"V"     {Debug::debug(603) <<"Lexer = "<<  "VERTIKALFLIP" <<endl;
         return token::VERTIKALFLIP;}
"HV"    {Debug::debug(603) <<"Lexer = "<<  "HVFLIP" <<endl;
         return token::HVFLIP;}
"VH"    {Debug::debug(603) <<"Lexer = "<<  "HVFLIP" <<endl;
         return token::HVFLIP;}
"A"     {Debug::debug(603) <<"Lexer = "<<  "ALPHA" <<endl;
         return token::ALPHA;}
"A"{digit}+   {Debug::debug(603) <<"Lexer = "<<  "ALPHA" <<endl;
               return token::ALPHA;} 
"AS"{digit}+"D"{digit}+ {Debug::debug(603) <<"Lexer = "<<  "ALPHA" <<endl;
                         return token::ALPHA;}

"Begin"		{Debug::debug(603) <<"Lexer = "<<  "BEGIN" <<endl;
              return token::ACBEGIN;}
"Action"	{Debug::debug(603) <<"Lexer = "<<  "ACTION" <<endl;
             return token::ACTION;}
"Loopstart"	{Debug::debug(603) <<"Lexer = "<<  "LOOPSTART" <<endl;
             return token::LOOPSTART;}
"Clsn2Default"	{Debug::debug(603) <<"Lexer = "<<  "CLSN2DEFAULT" <<endl;
                 return token::CLSN2DEFAULT; }
"Clsn1Default"	{Debug::debug(603) <<"Lexer = "<<  "CLSN1DEFAULT" <<endl;
                 return token::CLSN1DEFAULT; }
"Clsn2"		{Debug::debug(603) <<"Lexer = "<<  "CLNS2" <<endl;
              return token::CLSN2;}
"Clsn1"		{Debug::debug(603) <<"Lexer = "<<  "CLNS1" <<endl;
             return token::CLSN1; }

";"		{  char c;
		  c= yyinput();
			while (c != '\n' && c != 0)
			{	
			c=yyinput();
			}
         Debug::debug(603) <<"Lexer Coment ;= "<<  *yytext <<endl;
         yylloc->lines(yyleng);yylloc->step();}
[+*/]     {Debug::debug(603) <<"Lexer Operation= "<<  *yytext <<endl;
           return token_type (yytext[0]);}
"-"     {Debug::debug(603) <<"Lexer = "<<  *yytext <<endl;
         return token_type (yytext[0]);}
"("		{Debug::debug(603) <<"Lexer = "<<  yytext[0] <<endl;
         return token_type (yytext[0]);}
")"		{Debug::debug(603) <<"Lexer = "<< yytext[0] <<endl;
         return token_type (yytext[0]);}
":"     {Debug::debug(603) <<"Lexer = "<<  *yytext <<endl;
         return token::COLON;}
"="      {Debug::debug(603) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }

"["	     {	Debug::debug(603) <<"Lexer = "<<  yytext[0] <<endl;
            return token_type (yytext[0]);  }
"]"	     {	Debug::debug(603) <<"Lexer = "<<  yytext[0] <<endl;
            return token_type (yytext[0]);  }

{STR}		{yylval->stringVal = new std::string(yytext, yyleng);
              Debug::debug(603) <<"Lexer string= "<< yylval->stringVal <<endl; }
 

 /* gobble up white-spaces */
{blank}+ {
    Debug::debug(603) <<"Lexer blank= "<< *yytext <<endl;
    yylloc->step();
}


[\n]+        { yylloc->lines(yyleng); yylloc->step();
				Debug::debug(603) <<"Lexer string EOL= "<< "EOL" <<endl;
				return token::EOL;
				}

 /* discard all other characters */
. {
    yylloc->step();
    Debug::debug(10,__FUNCTION__) <<"Lexer Unknow caracter= "<< *yytext <<endl;
    
} 
 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace AirCompilerOld {

CScanner::CScanner(std::istream* in,
		 std::ostream* out)
    : OldAirFlexLexer(in, out)
{
}

CScanner::~CScanner()
{
}

void CScanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif
/*
int OldAirFlexLexer::yylex()
{
    std::cerr << "in OldAirFlexLexer::yylex() !" << std::endl;
    return 0;
}  
*/
/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */
/*
int OldAirFlexLexer::Airwrap()
{
    return 1;
}
*/