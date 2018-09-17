/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
%{ /*** C/C++ Declarations ***/

	#include <string>
	#include <iostream>
	#include <iomanip>
    #include "../../util/SGF_Debug.h"
	#include "scanner.h"
	
	/* import the parser's token type into a local typedef */
	
	typedef ComCompiler::Parser::token token;
	typedef ComCompiler::Parser::token_type token_type;
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
%option prefix="Com"
%option nodefault noyywrap yyclass="CScanner" c++


digit	[0123456789]
STR		\"[^\"]*\"
CHAR	[a-zA-z_]
FILENAME_CHAR [^\\\/,=;\n\r ]
blank   [\t]

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */


%{
    // reset location
    yylloc->step();
%}

D { yylval->stringVal = new string("D"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_DOWN" <<endl; 
	return token::CMD_KEY_DOWN; }
F { yylval->stringVal = new string("F");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_FORWARD" <<endl; 
	return token::CMD_KEY_FORWARD; }
DF { yylval->stringVal = new string("DF");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_DOWN_FORWARD" <<endl; 
	return token::CMD_KEY_DOWN_FORWARD; }
B { yylval->stringVal = new string("B");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_BACK" <<endl; 
	return token::CMD_KEY_BACK; }
DB { yylval->stringVal = new string("DB");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_DOWN_BACK" <<endl; 
	return token::CMD_KEY_DOWN_BACK; }
UF { yylval->stringVal = new string("UF");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_UP_FORWARD" <<endl; 
	return token::CMD_KEY_UP_FORWARD; }
U { yylval->stringVal = new string("U");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_UP" <<endl; 
	return token::CMD_KEY_UP; }
UB { yylval->stringVal = new string("UB");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_KEY_UP_BACK" <<endl; 
	return token::CMD_KEY_UP_BACK; }

a { yylval->stringVal = new string("a");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_A" <<endl; 
	return token::CMD_BUTTON_A; }
b { yylval->stringVal = new string("b");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_B" <<endl; 
	return token::CMD_BUTTON_B; }
c { yylval->stringVal = new string("c");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_C" <<endl; 
	return token::CMD_BUTTON_C; }
x { yylval->stringVal = new string("x");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_X" <<endl; 
	return token::CMD_BUTTON_X; }
y { yylval->stringVal = new string("y");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_Y" <<endl; 
	return token::CMD_BUTTON_Y; }
z { yylval->stringVal = new string("z");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_Z" <<endl; 
	 return token::CMD_BUTTON_Z; }
s { yylval->stringVal = new string("s"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_BUTTON_S" <<endl; 
	 return token::CMD_BUTTON_S; }

(F|f){digit}+ { yylval->doubleVal = toFloatX(); /* sscanf(yytext,"F%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_FX: " << yylval->doubleVal  <<endl; 
	return token::KEY_FX;}

(s|S){digit}+ { yylval->doubleVal = toFloatX(); /*sscanf(yytext,"S%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_SX: " << yylval->doubleVal  <<endl; 
	return token::KEY_SX;}


{digit}+"."{digit}+	|
"."{digit}+		|
{digit}+ 		{ yylval->doubleVal = toFloat();
				  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer NUMBER= "<< *yytext <<" lenght: "<< yyleng <<" doubleval: "<< setiosflags(ios::fixed) <<setprecision(4) << yylval->doubleVal <<endl;
				 return token::NUMBER;}
\-"."{digit}+	{ yylval->doubleVal = toFloat();
				  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer NUMBER= "<< *yytext <<" lenght: "<< yyleng <<" doubleval: "<< setiosflags(ios::fixed) <<setprecision(4) << yylval->doubleVal <<endl;
				 return token::NUMBER;}

{STR}[a-zA-Z_][a-zA-Z\-0-9_.]* { yylval->stringVal = new string(yytext, yyleng); 
SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer QUOTESTRING 3= "<<  yylval->stringVal->c_str() <<endl;
return token::QUOTESTRING; }			  

{STR}[a-zA-Z_][a-zA-Z\-0-9_.]*{STR} { yylval->stringVal = new string(yytext, yyleng); 
SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer QUOTESTRING 2= "<<  yylval->stringVal->c_str() <<endl;
return token::QUOTESTRING; }			  

{STR}		{yylval->stringVal = new string(yytext, yyleng);
			  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer QUOTESTRING= "<< yylval->stringVal->c_str() <<endl; 
			  return token::QUOTESTRING;}

         
"("		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
         return token_type (yytext[0]);}
")"		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<< yytext[0] <<endl;
         return token_type (yytext[0]);}
":"     {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  *yytext <<endl;
         return token_type (yytext[0]);}
"="      {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }
"."		 {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }
","		 {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }
\[	     {	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
            return token_type (yytext[0]);  }
\]     {	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
            return token_type (yytext[0]);  }
\/		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }

\~		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }
\$		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }
\+		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }  
\-		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }		 
\*		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }         
\>		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }  
\<		{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }  
\% {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }
\! {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }    
"&" {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }  
"|" {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer = "<<  yytext[0] <<endl;
           return token_type (yytext[0]); }      
"^" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_XOR" <<endl; 
	return token::CMD_XOR; }

(c|C)(o|O)(m|M)(m|M)(a|A)(n|N)(d|D).(t|T)(i|I)(m|M)(e|E)   { yylval->stringVal = new string("command.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TIME" <<endl; 
	return token::KEY_TIME;}
(c|C)(o|O)(m|M)(m|M)(a|A)(n|N)(d|D).(b|B)(u|U)(f|F)(f|F)(e|E)(r|R).(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("command.buffer.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_BUFFERTIME" <<endl; 
	return token::KEY_BUFFERTIME;}
 
(c|C)(o|O)(m|M)(m|M)(a|A)(n|N)(d|D)  { yylval->stringVal = new string("command"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_COMMAND" <<endl; 
	return token::KEY_COMMAND;}

(b|B)(u|U)(f|F)(f|F)(e|E)(r|R).(t|T)(i|I)(m|M)(e|E)   { yylval->stringVal = new string("buffer.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_BUFFERTIME" <<endl; 
	return token::KEY_BUFFERTIME;}
(n|N)(a|A)(m|M)(e|E)  { yylval->stringVal = new string("name"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_NAME" <<endl; 
	return token::KEY_NAME;}
	
(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TIME: " << *yylval->stringVal <<endl; 
	return token::KEY_TIME;}

(D|d)(E|e)(F|f)(a|A)(U|u)(l|L)(t|T)(s|S)   { yylval->stringVal = new string("defaults"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_DEFAULTS" <<endl; 
	return token::KEY_DEFAULTS;}

			  

			  

	/* gobble up white-spaces */
{blank}+ {
    //SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer blank= "<< *yytext <<endl;
    yylloc->step();
}

;[^\n\r]*[\n\r] {//SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "COMMENT" <<endl; 
	return token::COMMENT; }        

[\n\r]+        { yylloc->lines(yyleng); yylloc->step();
				SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer EOL= "<< "EOL" <<endl;
				return token::EOL;
				}



"!=" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_NOTEQ" <<endl; 
	return token::CMD_NOTEQ; }
">=" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_GREATERTHANEQ" <<endl; 
	return token::CMD_GREATERTHANEQ; }
"<=" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_LESSTHANEQ" <<endl; 
	return token::CMD_LESSTHANEQ; }
"&&" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_LOGAND" <<endl; 
	return token::CMD_LOGAND; }
"||" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_LOGOR" <<endl; 
	return token::CMD_LOGOR; }
"**" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_SQUARE" <<endl; 
	return token::CMD_SQUARE; }
"^^" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_LOGXOR" <<endl; 
	return token::CMD_LOGXOR; }


[ \t]* { ; }


	/* discard all other characters */
. {
    yylloc->step();
    SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Unknow caracter= "<< *yytext <<endl;
  
}			  
%% 
	/*** END EXAMPLE - Change the example lexer rules above ***/
	/*** Additional Code bellow ***/
namespace ComCompiler {

CScanner::CScanner(std::istream* in,
		 std::ostream* out)
    : ComFlexLexer(in, out)
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

float CScanner::toFloatX() {
char *tempNumber=new char[yyleng+2];
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

void CScanner::destroyComment()
{
char c;

   c= yyinput();
   while (c != '\n' && c != 0)
   {	
	c=yyinput();

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
int ComFlexLexer::yylex()
{
    std::cerr << "in ComFlexLexer::yylex() !" << endl;
    return 0;
}  
*/
/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */
/*
int ComFlexLexer::Comwrap()
{
    return 1;
}
*/