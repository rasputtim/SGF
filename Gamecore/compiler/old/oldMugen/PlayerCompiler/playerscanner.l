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
	
	typedef PlayerCompiler::Parser::token token;
	typedef PlayerCompiler::Parser::token_type token_type;
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
%option prefix="Player"
%option nodefault noyywrap yyclass="CScanner" c++
%option caseless

digit	[0123456789]
STR      \"[^\"]*\"
CHAR    [A-Za-z_]
blank   [ \t]

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */


%{
    // reset location
    yylloc->step();
%}



{digit}+ {
    yylval->integerVal = atoi(yytext);
    Debug::debug(602) <<"Lexer INTEGER= "<<  yylval->integerVal <<endl;
    return token::INTEGER;
}

{digit}+"."{digit}* {
    yylval->doubleVal = atof(yytext);
    Debug::debug(602) <<"Lexer DOUBLE= "<<  yylval->doubleVal <<endl;
    return token::DOUBLE;
}

";"		{  char c;
		  c= yyinput();
			while (c != '\n' && c != 0)
			{	
			yylloc->step();
			c=yyinput();
			}
         Debug::debug(602,__FUNCTION__) <<"Lexer Coment = "<<  "COMENT" <<endl;
         yylloc->lines(yyleng);yylloc->step();
         return token::EOL;}
         
         
[+*/]     {Debug::debug(602) <<"Lexer Operation= "<<  *yytext <<endl;
           return token_type (yytext[0]);}
"-"     {Debug::debug(602) <<"Lexer = "<<  *yytext <<endl;
         return token_type (yytext[0]);}
"("		{Debug::debug(602) <<"Lexer = "<<  yytext[0] <<endl;
         return token_type (yytext[0]);}
")"		{Debug::debug(602) <<"Lexer = "<< yytext[0] <<endl;
         return token_type (yytext[0]);}
","     {Debug::debug(602) <<"Lexer = "<<  yytext[0] <<endl;
         return token_type (yytext[0]);}
"["	     {	Debug::debug(602) <<"Lexer = "<<  yytext[0] <<endl;
            return token_type (yytext[0]);  }
"]"	     {	Debug::debug(602) <<"Lexer = "<<  yytext[0] <<endl;
            return token_type (yytext[0]);  }

"[data]" {/**/}     

"cmd"               {Debug::debug(602) <<"Lexer = "<<  "COMAND" <<endl;
					return token::COMAND;}     
"cns"               {Debug::debug(602) <<"Lexer = "<<  "CNS" <<endl;
					return token::CNS;}
"st"                {Debug::debug(602) <<"Lexer = "<<  "STATES" <<endl;
					return token::STATES;}
"stcommon"          {Debug::debug(602) <<"Lexer = "<<  "COMESTATES" <<endl;
					return token::COMESTATES;}
"sprite"            {Debug::debug(602) <<"Lexer = "<<  "SPRITES" <<endl;
					return token::SPRITES;}
"anim"              {Debug::debug(602) <<"Lexer = "<<  "ANIMATION" <<endl;
					return token::ANIMATION;}
"sound"             {Debug::debug(602) <<"Lexer = "<<  "SOUNDS" <<endl;
					return token::SOUNDS;}
"pal1"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE1" <<endl;
					return token::PALLETE1; }
"pal2"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE2" <<endl;
					return token::PALLETE2;}
"pal3"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE3" <<endl;
					return token::PALLETE3;}
"pal4"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE4" <<endl;
					return token::PALLETE4;}
"pal5"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE5" <<endl;
					return token::PALLETE5;}
"pal6"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE6" <<endl;
					return token::PALLETE6;}
"pal7"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE7" <<endl;
					return token::PALLETE7;}
"pal8"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE8" <<endl;
					return token::PALLETE8;}
"pal9"              {Debug::debug(602) <<"Lexer = "<<  "PALLETE9" <<endl;
					return token::PALLETE9;}
"pal10"             {Debug::debug(602) <<"Lexer = "<<  "PALLETE10" <<endl;
					return token::PALLETE10;}
"pal11"             {Debug::debug(602) <<"Lexer = "<<  "PALLETE11" <<endl;
					return token::PALLETE11;}
"pal12"             {Debug::debug(602) <<"Lexer = "<<  "PALLETE12" <<endl;
					return token::PALLETE12; }


"**"    {Debug::debug(602) <<"Lexer = "<<  "SQUARE" <<endl;
         return token::SQUARE;}
"!"     {Debug::debug(602) <<"Lexer = "<<  "LOGNOT" <<endl;
         return token::LOGNOT;}
"&&"    {Debug::debug(602) <<"Lexer = "<<  "LOGAND" <<endl;
         return token::LOGAND;}
"||"    {Debug::debug(602) <<"Lexer = "<<  "LOGOR" <<endl;
         return token::LOGOR; }
"^^"    {Debug::debug(602) <<"Lexer = "<<  "LOGXOR" <<endl;
         return token::LOGXOR; }
"~"     {Debug::debug(602) <<"Lexer = "<<  "NOT" <<endl;
         return token::NOT; }
"&"     {Debug::debug(602) <<"Lexer = "<<  "AND" <<endl;
         return token::AND; }
"|"     {Debug::debug(602) <<"Lexer = "<<  "OR" <<endl;
         return token::OR; }
"^"     {Debug::debug(602) <<"Lexer = "<<  "XOR" <<endl;
         return token::XOR;}


"="			{Debug::debug(602) <<"Lexer = "<<  "EQUAL" <<endl;
         return token::EQUAL; }
"!="		{Debug::debug(602) <<"Lexer = "<<  "NOTEQUAL" <<endl;
         return token::NOTEQUAL; }
">"			{Debug::debug(602) <<"Lexer = "<<  "GREATER" <<endl;
         return token::GREATER; }
"<"			{Debug::debug(602) <<"Lexer = "<<  "LESS" <<endl;
         return token::LESS; }
"<="	{Debug::debug(602) <<"Lexer = "<<  "LESSEQUAL" <<endl;
         return token::LESSEQUAL; }
">="	{Debug::debug(602) <<"Lexer = "<<  "GREATEREQUAL" <<endl;
         return token::GREATEREQUAL;}


"Info"   {Debug::debug(602) <<"Lexer = "<<  "INFO" <<endl;
         return token::INFO;}
"Name"       {Debug::debug(602) <<"Lexer = "<<  "NAME" <<endl;
         return token::NAME;}
"displayname"       {Debug::debug(602) <<"Lexer = "<<  "DISPLAYNAME" <<endl;
         return token::DISPLAYNAME;} 
"versiondate"       {Debug::debug(602) <<"Lexer = "<<  "VERSIONDATE" <<endl;
         return token::VERSIONDATE;}
"mugenversion"      {Debug::debug(602) <<"Lexer = "<<  "MUGENVERSION" <<endl;
         return token::MUGENVERSION;}
"author"            {Debug::debug(602) <<"Lexer = "<<  "AUTHOR" <<endl;
         return token::AUTHOR; }
"pal.defaults"      {Debug::debug(602) <<"Lexer = "<<  "PALDEFAULTS" <<endl;
                     return token::PALDEFAULTS;}

"Files"             {Debug::debug(602) <<"Lexer = "<<  "FILES" <<endl;
					return token::FILES; }


"Arcade"            {Debug::debug(602) <<"Lexer = "<<  "ARCADE" <<endl;
					return token::ARCADE; }
"intro.storyboard"  {Debug::debug(602) <<"Lexer = "<<  "INTRO" <<endl;
					return token::INTRO;}
"ending.storyboard" {Debug::debug(602) <<"Lexer = "<<  "ENDING" <<endl;
					return token::ENDING;}


{STR}		{  yylval->stringVal = new std::string(yytext, yyleng);
              Debug::debug(602) <<"Lexer string= "<< yylval->stringVal <<endl;
              return token::STRING; }

[0-9A-Za-z_]+(\.[sS][fF][fF]|\.[sS][nN][dD]|\.[aA][iI][rR]|\.[cC][mM][dD]|\.[cC][nN][sS]|.[aA][cC][tT]|\.[dD][eE][fF]) { Debug::debug(602) <<"Lexer = "<<  "FILENAME" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::FILENAME; }

 /* gobble up white-spaces */
{blank}+ {
    //Debug::debug(602) <<"Lexer blank= "<< *yytext <<endl;
    yylloc->step();
}


[\n]+        { yylloc->lines(yyleng); yylloc->step();
				Debug::debug(602) <<"Lexer string EOL= "<< "EOL" <<endl;
				return token::EOL;
				}

 /* discard all other characters */
. {
    yylloc->step();
    Debug::debug(10,__FUNCTION__) <<"Lexer Unknow caracter= "<< (int)*yytext <<endl;
    
} 
 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace PlayerCompiler {

CScanner::CScanner(std::istream* in,
		 std::ostream* out)
    : PlayerFlexLexer(in, out)
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
int AirFlexLexer::Airwrap()
{
    return 1;
}
*/