/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
%{ /*** C/C++ Declarations ***/

	#include <string>

	#include <iomanip>
    #include "../../util/SGF_Debug.h"
	#include "scanner.h"
	
	/* import the parser's token type into a local typedef */
	
	typedef DefCompiler::Parser::token token;
	typedef DefCompiler::Parser::token_type token_type;
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
%option prefix="Def"
%option nodefault noyywrap yyclass="CScanner" c++


digit	[0-9]
STR		\"[^\"]*\"
blank   [\t]
TEXT (t|T)(e|E)(x|X)(t|T)
FILENAME_CHAR [^\\\/,=;\n\r ]
FILENAME_CHAR2 [^\\\/, \t\n\r ]

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */


%{
    // reset location
    yylloc->step();
%}

\; {DestroyComment(); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "COMMENT" <<endl; 
	return token::COMMENT; }        

{STR}		{yylval->stringVal = new std::string(yytext, yyleng);
			  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer QUOTESTRING= "<< yylval->stringVal->c_str() <<endl; 
			  return token::QUOTESTRING;}

 /* =============  ESPECIAL COMMANDS ========================= */
 
"%"(i|I) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer DEF_PERC_I "<<  endl;
yylval->stringVal = new std::string(yytext, yyleng); return token::IDENTIFIER; }
"%"(s|S) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer DEF_PERC_I "<<  endl;
yylval->stringVal = new std::string(yytext, yyleng); return token::IDENTIFIER; }

\[(b|B)(g|G)(c|C)(t|T)(r|R)(l|L).*\]  { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_BGCTRL" <<endl; 
	yylval->stringVal = new std::string("bgctrl");return token::DEF_BGCTRL; }
\[(b|B)(g|G).*\]  { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_BG" <<endl; 
	yylval->stringVal = new std::string(yytext, yyleng); return token::DEF_BG; }
	

(s|S)(e|E)(l|L)(e|E)(c|C)(t|T)(b|B)(g|G)(c|C)(t|T)(r|R)(l|L)" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_SELECTBGCTRL" <<endl; 
	yylval->stringVal = new std::string("selectbgctrl");return token::DEF_SELECTBGCTRL; }
	
(s|S)(e|E)(l|L)(e|E)(c|C)(t|T)(b|B)(g|G)" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_SELECTBG" <<endl; 
	yylval->stringVal = new std::string("selectbg");return token::DEF_SELECTBG; }

	
	
(h|H)" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_HORIZONTAL" <<endl; 
	yylval->stringVal = new std::string("h");return token::DEF_HORIZONTAL; }
(v|V)" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_VERTICAL" <<endl; 
	yylval->stringVal = new std::string("v");return token::DEF_VERTICAL; }
((v|V)(h|H))|((h|H)(v|V))" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_VERTICAL_HORIZONTAL" <<endl; 
	yylval->stringVal = new std::string("hv");return token::DEF_VERTICAL_HORIZONTAL; }

(a|A)(s|S){digit}+(d|D){digit}+ { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_ALPHA_BLEND" <<endl; 
	return token::DEF_ALPHA_BLEND; }
(a{digit}|A{digit}) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_ALPHA_BLEND_SHORTHAND" <<endl; 
	yylval->stringVal = new std::string(yytext, yyleng);
	return token::DEF_ALPHA_BLEND_SHORTHAND; }

(l|L)(o|O)(o|O)(p|P)(s|S)(t|T)(a|A)(r|R)(t|T)" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_LOOPSTART" <<endl; 
	yylval->stringVal = new std::string("loopstart");return token::DEF_LOOPSTART; }

(b|B)(l|L)(a|A)(n|N)(k|K)" " { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_BLANK" <<endl; 
	yylval->stringVal = new std::string("blank");return token::DEF_BLANK; }
	

(a|A)[ ]* { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_COLOR_ADDITION" <<endl; 
	yylval->stringVal = new std::string("a");return token::DEF_COLOR_ADDITION; }
(s|S)[ ]* { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_COLOR_SUBTRACT" <<endl; 
	yylval->stringVal = new std::string("s");return token::DEF_COLOR_SUBTRACT; }

^.*{TEXT}{blank}*=.*$ { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "DEF_TEXT" <<endl; 
	yylval->stringVal = new std::string(yytext, yyleng);return token::DEF_TEXT; }

({digit}+\.{digit}+\.{digit}+)|({digit}+\/{digit}+\/{digit}+)|({digit}+\-{digit}{digit}\-{digit}+)  {
    yylval->stringVal = new std::string(yytext, yyleng);
    SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer DATE= "<<  yylval->stringVal->c_str() <<endl;
    return token::DATE;
}
{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.](c|C)(n|N)(s|S) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }
{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.](c|C)(m|M)(d|D) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }

{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.](s|S)(f|F)(f|F) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }
{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.](s|S)(n|N)(d|D) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }

{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.](a|A)(i|I)(r|R) { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }

{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.][dD][eE][fF] { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }

{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.][fF][nN][tT] { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }

{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.][aA][cC][tT] { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  "DEF_FILENAME_1" <<endl;
             yylval->stringVal = new std::string(yytext, yyleng);
             return token::DEF_FILENAME; }

{FILENAME_CHAR}*([\/\\]{FILENAME_CHAR}+)+[\.]{FILENAME_CHAR}+ { yylval->stringVal = new std::string(yytext, yyleng); 
SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer DEF_FILENAME_3= "<<  yylval->stringVal->c_str() <<endl;
return token::DEF_FILENAME; }

([-+])?(\.{digit}+|{digit}+|{digit}*\.{digit}+) {

yylval->doubleVal = toFloat();
SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer NUMBER= "<< *yytext <<" lenght: "<< yyleng <<" doubleval"<< setiosflags(ios::fixed) <<setprecision(4) << yylval->doubleVal <<endl;
return token::NUMBER;}

[a-zA-Z_\\-][a-zA-Z\-0-9_\.\:]* { yylval->stringVal = new std::string(yytext, yyleng); 
SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer IDENTIFIER= "<<  yylval->stringVal->c_str() <<endl;
return token::IDENTIFIER; }

[ \t]* { ; }


 /* gobble up white-spaces */


[\n\r]+        { yylloc->lines(yyleng); yylloc->step();
				SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer EOL= "<< "EOL" <<endl;
				return token::EOL;
				}


 /* sending all other characters */
. {
    //yylloc->step();
   //Debug::debug(10,__FUNCTION__) <<"Lexer Unknow caracter= "<< *yytext <<endl;
   yylval->stringVal = new std::string(yytext, yyleng);
   return token_type (yytext[0]);
    
} 
 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace DefCompiler {

CScanner::CScanner(std::istream* in, std::ostream* out)
    : DefFlexLexer(in, out)
{
}

CScanner::~CScanner()
{
}

void CScanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

float CScanner::toFloat() {
char *tempNumber=new char[yyleng+1];
for (int i = 0; i < yyleng ; i++)
{
//SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer number[" <<i<<"] = " << yytext[i] << endl;
tempNumber[i]=yytext[i];

}
tempNumber[yyleng]='\0';
float rez = 0, fact =1;
if (*tempNumber == '-') {
tempNumber++;
fact = -1;
}
int point_seen =0;
for (int j =0; j < yyleng; j++) {
//SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer number[" <<j<<"] = " << tempNumber[j] << endl;
	if (tempNumber[j] == '.'){
	point_seen =1;
	}else{
	int d = tempNumber[j] - '0';
	if (d >=0 && d <=9) {
		if (point_seen) fact /= 10.0f;
		rez = rez * 10.0f + (float)d;
		//SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer rez = " << rez << endl;

		}
	}
}
//delete tempNumber;
return rez * fact;
}

void CScanner::DestroyComment()
{
char c;

   c= DefFlexLexer::yyinput();
   while (c != '\n' && c != 0)
   {	
	c=DefFlexLexer::yyinput();

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
int DefFlexLexer::yylex()
{
    std::cerr << "in DefFlexLexer::yylex() !" << std::endl;
    return 0;
}  
*/
/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */
/*
int DefFlexLexer::Defwrap()
{
    return 1;
}
*/

