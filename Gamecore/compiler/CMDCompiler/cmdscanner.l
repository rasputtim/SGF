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
	#include "cmdScanner.h"
	
	/* import the parser's token type into a local typedef */
	
	typedef CmdCompiler::Parser::token token;
	typedef CmdCompiler::Parser::token_type token_type;
    /* By default yylex returns int, we use token_type. Unfortunately yyterminate
    * by default returns 0, which is not of token_type. */
    #define yyterminate() return token::END

	//To use in lexer to parse trigger redirection
	
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
%option prefix="Cmd"
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

{STR}[a-zA-Z_\'][a-zA-Z\'\-0-9_.]*{STR} { yylval->stringVal = new string(yytext, yyleng); 
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

 /* =============  FUNCTIONS ========================= */
 
(a|A)(c|C)(o|O)(s|S)  { yylval->stringVal = new string("acos"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(a|A)(s|S)(i|I)(n|N)  { yylval->stringVal = new string("asin"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(a|A)(t|T)(a|A)(n|N)  { yylval->stringVal = new string("atan"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
 
(a|A)(n|N)(i|I)(m|M)(e|E)(l|L)(e|E)(m|M)  { yylval->stringVal = new string("animelem"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}

(a|A)(b|B)(s|S)  { yylval->stringVal = new string("abs"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(a|A)(n|N)(i|I)(m|M)(e|E)(l|L)(e|E)(m|M)(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("animelemtime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(a|A)(n|N)(i|I)(m|M)(e|E)(l|L)(e|E)(m|M)(n|N)(o|O)  { yylval->stringVal = new string("animelemno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(a|A)(n|N)(i|I)(m|M)(e|E)(x|X)(i|I)(s|S)(t|T)  { yylval->stringVal = new string("animexist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}



(c|C)(o|O)(s|S)  { yylval->stringVal = new string("cos"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}

(c|C)(e|E)(i|I)(l|L)  { yylval->stringVal = new string("ceil"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(c|C)(o|O)(n|N)(s|S)(t|T)(2)(4)(0)(P|p)  { yylval->stringVal = new string("const240p"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_CONST: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(c|C)(o|O)(n|N)(s|S)(t|T)(4)(8)(0)(P|p)  { yylval->stringVal = new string("const480p"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_CONST: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(c|C)(o|O)(n|N)(s|S)(t|T)(7)(2)(0)(P|p)  { yylval->stringVal = new string("const720p"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_CONST: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}

(c|C)(o|O)(n|N)(s|S)(t|T)  { yylval->stringVal = new string("const"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_CONST: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_CONST;}


(e|E)(x|X)(p|P)  { yylval->stringVal = new string("exp"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}



(f|F)(l|L)(o|O)(o|O)(r|R)  { yylval->stringVal = new string("floor"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(f|F)(v|V)(a|A)(r|R)  { yylval->stringVal = new string("fvar"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_FVAR: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_FVAR;}


(g|G)(e|E)(t|T)(h|H)(i|I)(t|T)(v|V)(a|A)(r|R)  { yylval->stringVal = new string("gethitvar"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}



(i|F)(f|F)(e|E)(l|L)(s|S)(e|E)  { yylval->stringVal = new string("ifelse"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IFELSE: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IFELSE;}
(i|I)(s|S)(h|H)(e|E)(l|L)(p|P)(e|E)(r|R)  { yylval->stringVal = new string("ishelper"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str() <<endl; 
	return token::FUNC_IDENTIFIER;}


(l|L)(n|N)  { yylval->stringVal = new string("ln"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(l|O)(o|O)(g|G)  { yylval->stringVal = new string("log"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_LOG: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_LOG;}




(n|N)(u|U)(m|M)(p|P)(r|R)(o|O)(j|J)(i|I)(d|D)  { yylval->stringVal = new string("numprojid"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}
(n|N)(u|U)(m|M)(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)  { yylval->stringVal = new string("numtarget"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER; }                             
(n|N)(u|U)(m|M)(e|E)(x|X)(p|P)(l|L)(o|O)(d|D) { yylval->stringVal = new string("numexplod");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER; }                              
(n|N)(u|U)(m|M)(h|H)(e|E)(l|L)(p|P)(e|E)(r|R) { yylval->stringVal = new string("numhelper");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER; }                              


(p|P)(r|R)(o|O)(j|J)(g|G)(u|U)(a|A)(r|R)(d|D)(e|E)(d|D)(t|T)(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("projguardedtime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::FUNC_IDENTIFIER;}

(p|P)(r|R)(o|O)(j|J)(h|H)(i|I)(t|T){digit}+ { yylval->doubleVal = toFloatX(); /* sscanf(yytext,"%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_PROJHIT: " << yylval->doubleVal  <<endl; 
	return token::FUNC_PROJHIT;}
(p|P)(r|R)(o|O)(j|J)(h|H)(i|I)(t|T) { yylval->doubleVal = 0; /* sscanf(yytext,"%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_PROJHIT: " << yylval->doubleVal  <<endl; 
	return token::FUNC_PROJHIT;}
	
(p|P)(r|R)(o|O)(j|J)(g|G)(u|U)(a|A)(r|R)(d|D)(e|E)(d|D){digit}+ { yylval->doubleVal = toFloatX(); /* sscanf(yytext,"F%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_PROJGUARDED: " << yylval->doubleVal  <<endl; 
	return token::FUNC_PROJGUARDED;}
(p|P)(r|R)(o|O)(j|J)(g|G)(u|U)(a|A)(r|R)(d|D)(e|E)(d|D) { yylval->doubleVal = 0; /* sscanf(yytext,"%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_PROJGUARDED: " << yylval->doubleVal  <<endl; 
	return token::FUNC_PROJGUARDED;}
(p|P)(r|R)(o|O)(j|J)(h|H)(i|I)(t|T)(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("projhittime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}
(p|P)(r|R)(o|O)(j|J)(c|C)(o|O)(n|N)(t|T)(a|A)(c|C)(t|T){digit}+ { yylval->doubleVal = toFloatX(); /* sscanf(yytext,"%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_PROJCONTACT: " << yylval->doubleVal  <<endl; 
	return token::FUNC_PROJCONTACT;}
(p|P)(r|R)(o|O)(j|J)(c|C)(o|O)(n|N)(t|T)(a|A)(c|C)(t|T)  { yylval->doubleVal = 0; /* sscanf(yytext,"F%d",&yylval->doubleVal); */SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_PROJCONTACT: " << yylval->doubleVal  <<endl; 
	return token::FUNC_PROJCONTACT;}
(p|P)(r|R)(o|O)(j|J)(c|C)(o|O)(n|N)(t|T)(a|A)(c|C)(t|T)(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("projcontacttime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}
(p|P)(r|R)(o|O)(j|J)(c|C)(a|A)(n|N)(c|C)(e|E)(l|L)(t|T)(i|I)(m|M)(e|E)    { yylval->stringVal = new string("projcanceltime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}
(p|P)(l|L)(a|A)(y|Y)(e|E)(r|R)(i|I)(d|D)(e|E)(x|X)(i|I)(s|S)(t|T)    { yylval->stringVal = new string("playeridexist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}


(s|S)(e|E)(l|L)(f|F)(a|A)(n|N)(i|I)(m|M)(e|E)(x|X)(i|I)(s|S)(t|T)  { yylval->stringVal = new string("selfanimexist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}
(s|S)(y|Y)(s|S)(f|F)(v|V)(a|A)(r|R)  { yylval->stringVal = new string("sysfvar"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}
(s|S)(i|I)(n|N)  { yylval->stringVal = new string("sin"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}

(s|S)(y|Y)(s|S)(v|V)(a|A)(r|R)  { yylval->stringVal = new string("sysvar"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_SYSVAR" <<endl; 
	return token::FUNC_SYSVAR;}




(t|T)(a|A)(n|N)  { yylval->stringVal = new string("tan"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}

(t|T)(i|I)(m|M)(e|E)(m|M)(o|O)(d|D)  { yylval->stringVal = new string("timemod"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}

[tT][eE][aA][mM][mM][oO][dD][eE] { yylval->stringVal = new string("teammode"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_IDENTIFIER" <<endl; 
	return token::FUNC_IDENTIFIER;}   

(v|V)(a|A)(r|R) { yylval->stringVal = new string("var"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "FUNC_VAR" <<endl; 
	return token::FUNC_VAR;}

  /* =============  ESPECIAL COMMANDS ========================= */
 
(c|C)(o|O)(m|M)(m|M)(a|A)(n|N)(d|D).(b|B)(u|U)(f|F)(f|F)(e|E)(r|R).(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("command.buffer.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str() <<endl; 
	return token::KEY_IDENTIFIER;}

(c|C)(o|O)(m|M)(m|M)(a|A)(n|N)(d|D).(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("command.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str() <<endl; 
	return token::KEY_IDENTIFIER;}

(c|C)(o|O)(m|M)(m|M)(a|A)(n|N)(d|D)  { yylval->stringVal = new string("command"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str() <<endl; 
	return token::KEY_IDENTIFIER;}

(s|S)(t|T)(a|A)(t|T)(e|E)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("statetype");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATETYPE" <<endl; 
	return token::KEY_STATETYPE; }

(p|P)(h|H)(y|Y)(s|S)(i|I)(c|C)(s|S) { yylval->stringVal = new string("physics");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_PHYSICS" <<endl; 
	return token::KEY_PHYSICS; }

		  


(S|s)(T|t)(a|A)(T|t)(e|E) { yylval->stringVal = new string("state"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: CMD_STATE" <<endl; 
	return token::CMD_STATE;}
(S|s)(T|t)(a|A)(T|t)(e|E)(D|d)(E|e)(F|f) { yylval->stringVal = new string("statedef");	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: CMD_STATEDEF" <<endl; 
		  return token::CMD_STATEDEF;}			  
			  
 /* =============  KEY_IDENTIFIER ========================= */

(a|A)(c|C)(c|C)(e|E)(l|L)  { yylval->stringVal = new string("accel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(d|D)(d|D)  { yylval->stringVal = new string("add"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(m|M)(p|P)(l|L) { yylval->stringVal = new string("ampl"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(n|N)(i|I)(m|M) { yylval->stringVal = new string("anim"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_ANIM: "<< yylval->stringVal->c_str() <<endl; 
	return token::KEY_ANIM;}
(a|A)(t|T)(t|T)(a|A)(c|C)(k|K) { yylval->stringVal = new string("attack"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
	

(a|A)(f|F)(f|F)(e|E)(c|C)(t|T)(t|T)(e|E)(a|A)(m|M)   { yylval->stringVal = new string("affectteam"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}


(a|A)(i|I)(r|R).(b|B)(a|A)(c|C)(k|K)  { yylval->stringVal = new string("air.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(f|F)(r|R)(o|O)(n|N)(t|T) { yylval->stringVal = new string("air.front"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R) { yylval->stringVal = new string("air.gethit.groundrecover"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(m|M)(u|U)(l|L) { yylval->stringVal = new string("air.gethit.airrecover.mul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(a|A)(d|D)(d|D) { yylval->stringVal = new string("air.gethit.airrecover.add"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("air.gethit.airrecover.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(f|F)(w|W)(d|D) { yylval->stringVal = new string("air.gethit.airrecover.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(u|U)(p|P) {  yylval->stringVal = new string("air.gethit.airrecover.up");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(d|D)(o|O)(w|W)(n|N) { yylval->stringVal = new string("air.gethit.airrecover.down"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("air.gethit.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("air.gethit.groundrecover.ground.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("air.gethit.groundrecover.groundlevel");  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("air.gethit.airrecover.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(y|Y)(a|A)(c|C)(c|C)(e|E)(l|L) { yylval->stringVal = new string("air.gethit.airrecover.yaccel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(t|T)(r|R)(i|I)(p|P).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("air.gethit.trip.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(n|N)(u|U)(m|M) { yylval->stringVal = new string("airjump.num"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(h|H)(e|E)(i|I)(g|G)(h|H)(t|T) { yylval->stringVal = new string("airjump.height"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(n|N)(e|E)(u|U) { yylval->stringVal = new string("airjump.neu"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("airjump.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(f|F)(w|W)(d|D) { yylval->stringVal = new string("airjump.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
	
(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P)   { yylval->stringVal = new string("airjump"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(i|I)(r|R)(j|J)(u|U)(g|G)(g|G)(l|L)(e|E)  { yylval->stringVal = new string("airjuggle"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R)  { yylval->stringVal = new string("air"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(l|L)(i|I)(v|V)(e|E) { yylval->stringVal = new string("alive");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }

(a|A)(n|N)(i|I)(m|M)(t|T)(i|I)(m|M)(e|E)      {yylval->stringVal = new string("animtime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                          
(a|A)(t|T)(t|T)(a|A)(c|C)(k|K).(d|D)(i|I)(s|S)(t|T) {yylval->stringVal = new string("attack.dist");  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(t|T)(t|T)(r|R) { yylval->stringVal = new string("attr"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(a|A)(u|U)(t|T)(h|H)(o|O)(r|R)(n|N)(a|A)(m|M)(e|E)   {yylval->stringVal = new string("authorname"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                          

(b|B)(a|A)(c|C)(k|K)(e|E)(e|E)(d|D)(g|G)(e|E)(b|B)(o|O)(d|D)(y|Y)(d|D)(i|I)(s|S)(t|T)  { yylval->stringVal = new string("backedgebodydist");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                     
(b|B)(a|A)(c|C)(k|K)(e|E)(d|D)(g|G)(e|E)(d|D)(i|I)(s|S)(t|T)   {yylval->stringVal = new string("backedgedist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                         

(b|B)(i|I)(n|N)(d|D)(t|T)(i|I)(m|M)(e|E)   { yylval->stringVal = new string("bindtime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(b|B)(u|U)(f|F)(f|F)(e|E)(r|R).(t|T)(i|I)(m|M)(e|E)   { yylval->stringVal = new string("buffer.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
	
(b|B)(u|U)(f|F)(f|F)(e|E)(r|R)   { yylval->stringVal = new string("buffer"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}




(c|C)(o|O)(l|L)(o|O)(r|R)  { yylval->stringVal = new string("color");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               

(c|C)(t|T)(r|R)(l|L)     {yylval->stringVal = new string("ctrl"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               
(c|C)(r|R)(o|O)(u|U)(c|C)(h|H).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("crouch.friction.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER;}" <<endl; 
	return token::KEY_IDENTIFIER;}
(c|C)(r|R)(o|O)(u|U)(c|C)(h|H).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N) { yylval->stringVal = new string("crouch.friction"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER;}" <<endl; 
	return token::KEY_IDENTIFIER;}

(c|C)(r|R)(o|O)(u|U)(c|C)(h|H)  { yylval->stringVal = new string("crouch"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(c|C)(a|A)(n|N)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R)  { yylval->stringVal = new string("canrecover");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                                             
 

(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E) { yylval->stringVal = new string("defence"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;} 

(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(o|O)(f|F)(f|F)(s|S)(e|E)(t|T) { yylval->stringVal = new string("down.bounce.offset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(y|Y)(a|A)(c|C)(c|C)(e|E)(l|L) { yylval->stringVal = new string("down.bounce.yaccel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("down.bounce.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(d|D)(o|O)(w|W)(n|N).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("down.friction.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(d|D)(r|R)(a|A)(w|W)(g|G)(a|A)(m|M)(e|E) { yylval->stringVal = new string("drawgame");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; } 

(d|D)(r|R)(a|A)(w|W).(o|O)(f|F)(f|F)(s|S)(e|E)(t|T) { yylval->stringVal = new string("draw.offset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(d|D)(r|R)(a|A)(w|W) {yylval->stringVal = new string("draw"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; } 

(f|F)(a|A)(c|C)(i|I)(n|N)(g|G)  { yylval->stringVal = new string("facing");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                
(f|F)(a|A)(l|L)(l|L).(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E)_(u|U)(p|P) { yylval->stringVal = new string("fall.defence_up"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;} 
(f|F)(a|A)(l|L)(l|L).(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E)_(m|M)(u|U)(l|L) { yylval->stringVal = new string("fall.defence_mul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(f|F)(a|A)(l|L)(l|L).(x|X)(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("fall.xvelocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(f|F)(a|A)(l|L)(l|L).(y|Y)(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("fall.yvelocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L)  { yylval->stringVal = new string("fall"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(o|O)(r|R)(c|C)(e|E)(s|S)(t|T)(a|A)(n|N)(d|D) { yylval->stringVal = new string("forcestand"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(o|O)(r|R)(c|C)(e|E)(n|N)(o|O)(f|F)(a|A)(l|L)(l|L) { yylval->stringVal = new string("forcenofall"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(c|C)(e|E)(p|P)(2)  { yylval->stringVal = new string("facep2"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(l|L)(o|O)(a|A)(t|T)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)(i|I)(n|N)(d|D)(e|E)(x|X) { yylval->stringVal = new string("floatpersistindex"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}	
(f|F)(r|R)(o|O)(n|N)(t|T)(e|E)(d|D)(g|G)(e|E)(b|B)(o|O)(d|D)(y|Y)(d|D)(i|I)(s|S)(t|T)  {yylval->stringVal = new string("frontedgebodydist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                     
(f|F)(r|R)(o|O)(n|N)(t|T)(e|E)(d|D)(g|G)(e|E)(d|D)(i|I)(s|S)(t|T)      { yylval->stringVal = new string("frontedgedist");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                     
(f|F)(v|V)(a|A)(l|L)(u|U)(e|E) { yylval->stringVal = new string("fvalue"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(f|F)(r|R)(e|E)(q|Q)  { yylval->stringVal = new string("freq"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}



(g|G)(a|A)(m|M)(e|E)(t|T)(i|I)(m|M)(e|E)   { yylval->stringVal = new string("gametime");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }    
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(b|B)(a|A)(c|C)(k|K) {yylval->stringVal = new string("ground.back");  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(f|F)(r|R)(o|O)(n|N)(t|T)  { yylval->stringVal = new string("ground.front"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)  { yylval->stringVal = new string("ground"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(g|G)(u|U)(a|A)(r|R)(d|D).(s|S)(p|P)(a|A)(r|R)(k|K)(n|N)(o|O) { yylval->stringVal = new string("guard.sparkno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(g|G)(u|U)(a|A)(r|R)(d|D)(f|F)(l|L)(a|A)(g|G) { yylval->stringVal = new string("guardflag"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(g|G)(u|U)(a|A)(r|R)(d|D).(p|P)(a|A)(u|U)(s|S)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("guard.pausetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(u|U)(a|A)(r|R)(d|D)(s|S)(o|O)(u|U)(n|N)(d|D) { yylval->stringVal = new string("guardsound"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("ground.type"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
         
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(s|S)(l|L)(i|I)(d|D)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("ground.slidetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(g|G)(u|U)(a|A)(r|R)(d|D).(s|S)(l|L)(i|I)(d|D)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("guard.slidetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(h|H)(i|I)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("ground.hittime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(u|U)(a|A)(r|R)(d|D).(h|H)(i|I)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("guard.hittime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(e|E)(t|T)(p|P)(o|O)(w|W)(e|E)(r|R) { yylval->stringVal = new string("getpower "); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(g|G)(i|I)(v|V)(e|E)(p|P)(o|O)(w|W)(e|E)(r|R) { yylval->stringVal = new string("givepower"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
     
(g|G)(u|U)(a|A)(r|R)(d|D).(c|C)(t|T)(r|R)(l|L)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("guard.ctrltime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(u|U)(a|A)(r|R)(d|D).(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("guard.dist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("ground.velocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(u|U)(a|A)(r|R)(d|D).(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("guard.velocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(g|G)(u|U)(a|A)(r|R)(d|D).(k|K)(i|I)(l|L)(l|L) { yylval->stringVal = new string("guard.kill"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
	
(g|G)(u|U)(a|A)(r|R)(d|D)  { yylval->stringVal = new string("guard"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

	
(h|H)(e|E)(i|I)(g|G)(h|H)(t|T)  { yylval->stringVal = new string("height"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(h|H)(e|E)(a|A)(d|D).(p|P)(o|O)(s|S) { yylval->stringVal = new string("head.pos"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

	
(h|H)(e|E)(a|A)(d|D)  { yylval->stringVal = new string("head"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(h|H)(i|I)(t|T)(o|O)(n|N)(c|C)(e|E) { yylval->stringVal = new string("hitonce"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(h|H)(i|I)(t|T)(c|C)(o|O)(u|U)(n|N)(t|T)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)  { yylval->stringVal = new string("hitcountpersist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(h|H)(i|I)(t|T)(d|D)(e|E)(f|F)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)  { yylval->stringVal = new string("hitdefpersist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(h|H)(i|I)(t|T)(c|C)(o|O)(u|U)(n|N)(t|T) {yylval->stringVal = new string("hitcount"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                
(h|H)(i|I)(t|T)(f|F)(a|A)(l|L)(l|L)  { yylval->stringVal = new string("hitfall");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               
(h|H)(i|I)(t|T)(f|F)(l|L)(a|A)(g|G) { yylval->stringVal = new string("hitflag");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }
	(h|H)(i|I)(t|T)(o|O)(v|V)(e|E)(r|R)  {yylval->stringVal = new string("hitover"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               
(h|H)(i|I)(t|T)(p|P)(a|A)(u|U)(s|S)(e|E)(t|T)(i|I)(m|M)(e|E)  {yylval->stringVal = new string("hitpausetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                          
(h|H)(i|I)(t|T)(s|S)(h|H)(a|A)(k|K)(e|E)(o|O)(v|V)(e|E)(r|R)  {yylval->stringVal = new string("hitshakeover"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                          
(h|H)(i|I)(t|T)(s|S)(o|O)(u|U)(n|N)(d|D) { yylval->stringVal = new string("hitsound"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(h|H)(i|I)(t|T)(v|V)(e|E)(l|L)  {yylval->stringVal = new string("hitvel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                          

(i|I)(d|D)  { yylval->stringVal = new string("id"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(i|I)(n|N)(g|G)(u|U)(a|A)(r|R)(d|D)(d|D)(i|I)(s|S)(t|T)  { yylval->stringVal = new string("inguarddist");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }

(i|I)(n|N)(t|T)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)(i|I)(n|N)(d|D)(e|E)(x|X)  { yylval->stringVal = new string("intpersistindex"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(i|I)(g|G)(n|N)(o|O)(r|R)(e|E)(h|H)(i|I)(t|T)(p|P)(a|A)(u|U)(s|S)(e|E) { yylval->stringVal = new string("ignorehitpause"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(i|I)(n|N)(t|T)(e|E)(r|R)(v|V)(a|A)(l|L)(l|L) { yylval->stringVal = new string("interval"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(i|I)(s|S)(h|H)(o|O)(m|M)(e|E)(t|T)(e|E)(a|A)(m|M)   { yylval->stringVal = new string("ishometeam");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                           


(j|J)(u|U)(g|G)(g|G)(l|L)(e|E) { yylval->stringVal = new string("juggle"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(j|J)(u|U)(m|M)(p|P).(c|C)(h|H)(a|A)(n|N)(g|G)(e|E)(a|A)(n|N)(i|I)(m|M).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("jump.changeanim.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::KEY_IDENTIFIER;}

(j|J)(u|U)(m|M)(p|P).(n|N)(e|E)(u|U) { yylval->stringVal = new string("jump.neu"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(j|J)(u|U)(m|M)(p|P).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("jump.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(j|J)(u|U)(m|M)(p|P).(f|F)(w|W)(d|D) { yylval->stringVal = new string("jump.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(j|J)(u|U)(m|M)(p|P)  { yylval->stringVal = new string("jump"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(k|K)(i|I)(l|L)(l|L) { yylval->stringVal = new string("kill"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(k|K)(o|O).(e|E)(c|C)(h|H)(o|O) { yylval->stringVal = new string("KO.echo"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(k|K)(o|O)  { yylval->stringVal = new string("ko"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

	
(l|L)(i|I)(e|E)(d|D)(o|O)(w|W)(n|N).(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("liedown.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(l|L)(i|I)(e|E)(d|D)(o|O)(w|W)(n|N)  { yylval->stringVal = new string("liedown"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(l|L)(i|I)(f|F)(e|E)(m|M)(a|A)(x|X) { yylval->stringVal = new string("lifemax");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                
(l|L)(i|I)(f|F)(e|E)   {yylval->stringVal = new string("life"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                   
(l|L)(o|O)(s|S)(e|E)(k|K)(o|O)  { yylval->stringVal = new string("loseko");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               
(l|L)(o|O)(s|S)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("losetime");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               
(l|L)(o|O)(s|S)(e|E)   { yylval->stringVal = new string("lose");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                 



(m|M)(a|A)(t|T)(c|C)(h|H)(n|N)(o|O) { yylval->stringVal = new string("matchno");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                
(m|M)(a|A)(t|T)(c|C)(h|H)(o|O)(v|V)(e|E)(r|R) {yylval->stringVal = new string("matchover"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                              
(m|M)(a|A)(x|X)(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("maxdist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(m|M)(i|I)(n|N)(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("mindist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(m|M)(i|I)(d|D).(p|P)(o|O)(s|S) { yylval->stringVal = new string("mid.pos"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(m|M)(i|I)(d|D)  { yylval->stringVal = new string("mid"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(m|M)(o|O)(v|V)(e|E)(h|H)(i|I)(t|T)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T) { yylval->stringVal = new string("movehitpersist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(m|M)(o|O)(v|V)(e|E)(g|G)(u|U)(a|A)(r|R)(d|D)(e|E)(d|D) { yylval->stringVal = new string("moveguarded");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                            
(m|M)(o|O)(v|V)(e|E)(h|H)(i|I)(t|T)    { yylval->stringVal = new string("movehit");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                             
(m|M)(o|O)(v|V)(e|E)(r|R)(e|E)(v|V)(e|E)(r|R)(s|S)(e|E)(d|D)  { yylval->stringVal = new string("movereversed");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                           
(m|M)(o|O)(v|V)(e|E)(c|C)(o|O)(n|N)(t|T)(a|A)(c|C)(t|T)  { yylval->stringVal = new string("movecontact"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(m|M)(o|O)(v|V)(e|E)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("movetype");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }

(m|M)(u|U)(l|L)  { yylval->stringVal = new string("mul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
	

	
(n|N)(a|A)(m|M)(e|E)  { yylval->stringVal = new string("name"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(n|N)(o|O)(c|C)(h|H)(a|A)(i|I)(n|N)(i|I)(d|D) { yylval->stringVal = new string("nochainID"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(n|N)(u|U)(m|M)(e|E)(n|N)(e|E)(m|M)(y|Y) {yylval->stringVal = new string("numenemy"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               
(n|N)(u|U)(m|M)(h|H)(i|I)(t|T)(s|S) { yylval->stringVal = new string("numhits"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(n|N)(u|U)(m|M)(p|P)(a|A)(r|R)(t|T)(n|N)(e|E)(r|R) {yylval->stringVal = new string("numpartner"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                             
(n|N)(u|U)(m|M)(p|P)(r|R)(o|O)(j|J)  { yylval->stringVal = new string("numproj");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                               

(p|P)(a|A)(u|U)(s|S)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("pausetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)(e|E)(n|N)(t|T)  { yylval->stringVal = new string("persistent"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
	
(p|P)(o|O)(s|S)(t|T)(y|Y)(p|P)(e|E)  { yylval->stringVal = new string("postype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(p|P)(o|O)(s|S)  { yylval->stringVal = new string("pos"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(p|P)(r|R)(i|I)(o|O)(r|R)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("priority"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(p|P)(r|R)(o|O)(j|J) { yylval->stringVal = new string("proj"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(p|P)(r|R)(o|O)(j|J).(a|A)(t|T)(t|T)(a|A)(c|C)(k|K).(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("proj.attack.dist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(p|P)(r|R)(o|O)(j|J).(d|D)(o|O)(s|S)(c|C)(a|A)(l|L)(e|E) { yylval->stringVal = new string("proj.doscale"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(p|P)(1)(i|I)(d|D)  { yylval->stringVal = new string("p1id"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                  
(p|P)(1)(n|N)(a|A)(m|M)(e|E) { yylval->stringVal = new string("p1name"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;} 
(p|P)(2)(b|B)(o|O)(d|D)(y|Y)(d|D)(i|I)(s|S)(t|T)   { yylval->stringVal = new string("p2bodydist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                               

(p|P)(2)(d|D)(i|I)(s|S)(t|T)   { yylval->stringVal = new string("p2dist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                               
(p|P)(2)(l|L)(i|I)(f|F)(e|E)   { yylval->stringVal = new string("p2life"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                               
(p|P)(2)(n|N)(a|A)(m|M)(e|E)  { yylval->stringVal = new string("p2name"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                
(p|P)(2)(s|S)(t|T)(a|A)(t|T)(e|E)(n|N)(o|O)  { yylval->stringVal = new string("p2stateno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                             
(p|P)(3)(n|N)(a|A)(m|M)(e|E)      { yylval->stringVal = new string("p3name"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                            
(p|P)(4)(n|N)(a|A)(m|M)(e|E)   { yylval->stringVal = new string("p4name"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                               
(p|P)(1)(s|S)(p|P)(r|R)(p|P)(r|R)(i|I)(o|O)(r|R)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("p1sprpriority"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(p|P)(2)(s|S)(p|P)(r|R)(p|P)(r|R)(i|I)(o|O)(r|R)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("p2sprpriority"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
  
(p|P)(1)(f|F)(a|A)(c|C)(i|I)(n|N)(g|G) { yylval->stringVal = new string("p1facing"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(p|P)(1)(g|G)(e|E)(t|T)(p|P)2(f|F)(a|A)(c|C)(i|I)(n|N)(g|G) { yylval->stringVal = new string("p1getp2facing"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(p|P)(2)(f|F)(a|A)(c|C)(i|I)(n|N)(g|G) { yylval->stringVal = new string("p2facing"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(p|P)(1)(s|S)(t|T)(a|A)(t|T)(e|E)(n|N)(o|O) { yylval->stringVal = new string("p1stateno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(p|P)(2)(g|G)(e|E)(t|T)(p|P)(1)(s|S)(t|T)(a|A)(t|T)(e|E) { yylval->stringVal = new string("p2getp1state"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(p|P)(a|A)(l|L)(n|N)(o|O)   { yylval->stringVal = new string("palno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                
(p|P)(i|I) { yylval->stringVal = new string("pi"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                     
(p|P)(r|R)(e|E)(v|V)(s|S)(t|T)(a|A)(t|T)(e|E)(n|N)(o|O) { yylval->stringVal = new string("prevstateno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                            
(p|P)(o|O)(w|W)(e|E)(r|R)(m|M)(a|A)(x|X) { yylval->stringVal = new string("powermax"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                               

(p|P)(o|O)(w|W)(e|E)(r|R)  {yylval->stringVal = new string("power"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }

(p|P)(2)(s|S)(t|T)(a|A)(t|T)(e|E)(t|T)(y|Y)(p|P)(e|E) {yylval->stringVal = new string("p2statetype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }
(p|P)(2)(b|B)(o|O)(d|D)(y|Y)(t|T)(y|Y)(p|P)(e|E)  {yylval->stringVal = new string("p2bodytype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(p|P)(2)(m|M)(o|O)(v|V)(e|E)(t|T)(y|Y)(p|P)(e|E)  { yylval->stringVal = new string("p2movetype");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}



(r|R)(a|A)(n|N)(d|D)(o|O)(m|M) { yylval->stringVal = new string("random");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                 

(r|R)(e|E)(m|M)(o|O)(v|V)(e|E)(t|T)(y|Y)(m|M)(e|E) {yylval->stringVal = new string("removetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                 

(r|R)(u|U)(n|N).(f|F)(w|W)(d|D) { yylval->stringVal = new string("run.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(r|R)(u|U)(n|N).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("run.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(r|R)(u|U)(n|N) { yylval->stringVal = new string("run"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P) { yylval->stringVal = new string("runjump"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(r|R)(o|O)(u|U)(n|N)(d|D)(n|N)(o|O) {yylval->stringVal = new string("roundno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                                
(r|R)(o|O)(u|U)(n|N)(d|D)(s|S)(e|E)(x|X)(i|I)(s|S)(t|T)(e|E)(d|D)  {yylval->stringVal = new string("roundsexisted"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                         
(r|R)(o|O)(u|U)(n|N)(d|D)(s|S)(t|T)(a|A)(t|T)(e|E) {yylval->stringVal = new string("roundstate"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                             

(r|R)(o|O)(o|O)(t|T)(d|D)(i|I)(s|S)(t|T) {yylval->stringVal = new string("rootdist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER; }                             

(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P).(n|N)(e|E)(u|U) { yylval->stringVal = new string("runjump.neu"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("runjump.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P).(f|F)(w|W)(d|D) { yylval->stringVal = new string("runjump.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

			  

(s|S)(c|C)(e|E)(e|E)(n|N)(p|P)(o|O)(s|S) { yylval->stringVal = new string("screenpos"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(s|S)(h|H)(a|A)(d|D)(o|O)(w|W)(o|O)(f|F)(f|F)(s|S)(e|E)(t|T) { yylval->stringVal = new string("shadowoffset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(i|I)(m|M)(u|U)(l|L) { yylval->stringVal = new string("simul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(s|S)(i|I)(n|N)(a|A)(d|D)(d|D) { yylval->stringVal = new string("sinadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(i|I)(n|N)(g|G)(l|L)(e|E) { yylval->stringVal = new string("single"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(n|N)(a|A)(p|P) { yylval->stringVal = new string("snap"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(p|P)(a|A)(r|R)(k|K)(n|N)(o|O) { yylval->stringVal = new string("sparkno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(t|T)(a|A)(t|T)(e|E)(n|N)(o|O)  { yylval->stringVal = new string("stateno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(s|S)(p|P)(a|A)(c|C)(i|I)(n|N)(g|G) { yylval->stringVal = new string("spacing"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(s|S)(p|P)(a|A)(r|R)(k|K)(x|X)(y|Y) { yylval->stringVal = new string("sparkxy"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(s|S)(t|T)(a|A)(t|T)(e|E)(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("statetime");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(t|T)(a|A)(n|N)(d|D).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N) { yylval->stringVal = new string("stand.friction"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER;}" <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(t|T)(a|A)(n|N)(d|D).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("stand.friction.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER;}" <<endl; 
	return token::KEY_IDENTIFIER;}

(s|S)(t|T)(a|A)(n|N)(d|D) { yylval->stringVal = new string("stand"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}
	
(t|T)(i|I)(m|M)(e|E)  { yylval->stringVal = new string("time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(1)  { yylval->stringVal = new string("trigger1"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(2)  { yylval->stringVal = new string("trigger2"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(3)  { yylval->stringVal = new string("trigger3"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(4)  { yylval->stringVal = new string("trigger4"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(5)  { yylval->stringVal = new string("trigger5"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(6)  { yylval->stringVal = new string("trigger6"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(7)  { yylval->stringVal = new string("trigger7"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(8)  { yylval->stringVal = new string("trigger8"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}
(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(9)  { yylval->stringVal = new string("trigger9"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGER: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGER;}

(t|T)(r|R)(i|I)(g|G)(g|G)(e|E)(r|R)(a|A)(l|L)(l|L)  { yylval->stringVal = new string("triggerall"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_TRIGGERALL: " << *yylval->stringVal <<endl; 
	return token::KEY_TRIGGERALL;}

(t|T)(y|Y)(p|P)(e|E)  { yylval->stringVal = new string("type"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal<<endl; 
	return token::KEY_IDENTIFIER;}
(t|T)(e|E)(a|A)(m|M)(s|S)(i|I)(d|D)(e|E)  { yylval->stringVal = new string("teamside"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}                              
(t|T)(i|I)(c|C)(k|K)(s|S)(p|P)(e|E)(r|R)(s|S)(e|E)(c|C)(o|O)(n|N)(d|D)  { yylval->stringVal = new string("tickspersecond"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}                        
(t|T)(i|I)(m|M)(e|E)(m|M)(o|O)(d|D)(e|E)  { yylval->stringVal = new string("timemode"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}                              
(t|T)(u|U)(r|R)(n|N)(s|S)  { yylval->stringVal = new string("turns"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}                              


(u|U)(n|N)(i|I)(q|Q)(h|H)(i|I)(t|T)(c|C)(o|O)(u|U)(n|N)(t|T)   { yylval->stringVal = new string("uniqhitcount"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: " << *yylval->stringVal <<endl; 
	return token::KEY_IDENTIFIER;}

(u|U)(n|N)(d|D)(e|E)(r|R) { yylval->stringVal = new string("under"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}





(v|V)(a|A)(l|L)(u|U)(e|E)(2)  { yylval->stringVal = new string("value2"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(v|V)(a|A)(l|L)(u|U)(e|E)  { yylval->stringVal = new string("value"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(v|V)(o|O)(l|L)(u|U)(m|M)(e|E) { yylval->stringVal = new string("volume"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}


(w|W)(a|A)(l|L)(k|K).(f|F)(w|W)(d|D) { yylval->stringVal = new string("walk.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(w|W)(a|A)(l|L)(k|K).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("walk.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(w|W)(a|A)(l|L)(k|K) { yylval->stringVal = new string("walk"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(w|W)(a|A)(v|V)(e|E)(f|F)(o|O)(r|R)(m|M) { yylval->stringVal = new string("waveform"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(w|W)(i|I)(n|N) { yylval->stringVal = new string("win"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                    
(w|W)(i|I)(n|N)(k|K)(o|O)  { yylval->stringVal = new string("winko"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                 

(w|W)(i|I)(n|N)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("wintime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                    
(w|W)(i|I)(n|N)(k|K)(o|O)(p|P)(e|E)(r|R)(f|F)(e|E)(c|C)(t|T)  { yylval->stringVal = new string("winperfect"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}                                 


(x|X)(s|S)(c|C)(a|A)(l|L)(e|E) { yylval->stringVal = new string("xscale"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}


(y|Y)(a|A)(c|C)(c|C)(e|E)(l|L) { yylval->stringVal = new string("yaccel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(y|Y)(s|S)(c|C)(a|A)(l|L)(e|E) { yylval->stringVal = new string("yscale"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_IDENTIFIER: "<< yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;} 
 
 /* =============  KEYWORD ========================= */


(h|H)(i|I)(t|T)(v|V)(e|E)(l|L)" "(x|X)  { yylval->stringVal = new string("hitvelx");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }                               
(h|H)(i|I)(t|T)(v|V)(e|E)(l|L)" "(y|Y)  {yylval->stringVal = new string("hitvely"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }                               



(p|P)(2)(d|D)(i|I)(s|S)(t|T)" "(x|X)  { yylval->stringVal = new string("p2distx"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}
(p|P)(2)(d|D)(i|I)(s|S)(t|T)" "(y|Y)  { yylval->stringVal = new string("p2disty"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}

[pP][2][bB][oO][dD][yY][dD][iI][sS][tT][ ][yY] {yylval->stringVal = new string("p2bodydisty"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }

[pP][2][bB][oO][dD][yY][dD][iI][sS][tT][ ][xX] { yylval->stringVal = new string("p2bodydistx");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }


[pP][aA][rR][eE][nN][tT][dD][iI][sS][tT][ ][yY] {yylval->stringVal = new string("parentdisty"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }

[pP][aA][rR][eE][nN][tT][dD][iI][sS][tT][ ][xX] { yylval->stringVal = new string("parentdistx");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }


(p|P)(o|O)(s|S)" "(x|X)  { yylval->stringVal = new string("posx"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}
(p|P)(o|O)(s|S)" "(y|Y)  { yylval->stringVal = new string("posy"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}

(r|R)(o|O)(o|O)(t|T)(d|D)(i|I)(s|S)(t|T)" "(x|X)	{ yylval->stringVal = new string("rootdistx");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }
(r|R)(o|O)(o|O)(t|T)(d|D)(i|I)(s|S)(t|T)" "(y|Y)	{ yylval->stringVal = new string("rootdisty");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }



(s|S)(c|C)(r|R)(e|E)(e|E)(n|N)(p|P)(o|O)(s|S)" "(x|X) { yylval->stringVal = new string("screenposx");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }

(s|S)(c|C)(r|R)(e|E)(e|E)(n|N)(p|P)(o|O)(s|S)" "(y|Y) { yylval->stringVal = new string("screenposy");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD; }



(V|v)(E|e)(l|L)" "(x|X)  { yylval->stringVal = new string("velx"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}
(V|v)(E|e)(l|L)" "(y|Y)  { yylval->stringVal = new string("vely"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}
(V|v)(E|e)(l|L)  { yylval->stringVal = new string("vel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEYWORD" <<endl; 
	return token::KEYWORD;}			  
			 
 /* =============  CONSTPARAM ========================= */



(d|D)(a|A)(t|T)(a|A).(l|L)(i|I)(f|F)(e|E)  {yylval->stringVal = new string("data.life");  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(p|P)(o|O)(w|W)(e|E)(r|R) { yylval->stringVal = new string("data.power"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(a|A)(t|T)(t|T)(a|A)(c|C)(k|K) { yylval->stringVal = new string("data.attack"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E) { yylval->stringVal = new string("data.defence"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;} 
(d|D)(a|A)(t|T)(a|A).(f|F)(a|A)(l|L)(l|L).(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E)_(u|U)(p|P) { yylval->stringVal = new string("data.fall.defence_up"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(f|F)(a|A)(l|L)(l|L).(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E)_(m|M)(u|U)(l|L) { yylval->stringVal = new string("data.fall.defence_mul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(l|L)(i|I)(e|E)(d|D)(o|O)(w|W)(n|N).(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("data.liedown.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(a|A)(i|I)(r|R)(j|J)(u|U)(g|G)(g|G)(l|L)(e|E) { yylval->stringVal = new string("data.airjuggle"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(s|S)(p|P)(a|A)(r|R)(k|K)(n|N)(o|O) { yylval->stringVal = new string("data.sparkno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(g|G)(u|U)(a|A)(r|R)(d|D).(s|S)(p|P)(a|A)(r|R)(k|K)(n|N)(o|O) { yylval->stringVal = new string("data.guard.sparkno"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(k|K)(o|O).(e|E)(c|C)(h|H)(o|O) { yylval->stringVal = new string("data.KO.echo"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(i|I)(n|N)(t|T)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)(i|I)(n|N)(d|D)(e|E)(x|X) { yylval->stringVal = new string("data.IntPersistIndex"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(f|F)(l|L)(o|O)(a|A)(t|T)(p|P)(e|E)(r|R)(s|S)(i|I)(s|S)(t|T)(i|I)(n|N)(d|D)(e|E)(x|X) { yylval->stringVal = new string("data.FloatPersistIndex"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(d|D)(a|A)(t|T)(a|A).(v|V)(o|O)(l|L)(u|U)(m|M)(e|E) { yylval->stringVal = new string("data.volume"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}

	
	
	
(s|S)(i|I)(z|Z)(e|E).(x|X)(s|S)(c|C)(a|A)(l|L)(e|E) { yylval->stringVal = new string("size.xscale"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(y|Y)(s|S)(c|C)(a|A)(l|L)(e|E) { yylval->stringVal = new string("size.yscale"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("size.ground.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(f|F)(r|R)(o|O)(n|N)(t|T)  { yylval->stringVal = new string("size.ground.front"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(a|A)(i|I)(r|R).(b|B)(a|A)(c|C)(k|K)  { yylval->stringVal = new string("size.air.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(a|A)(i|I)(r|R).(f|F)(r|R)(o|O)(n|N)(t|T) { yylval->stringVal = new string("size.air.front"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(h|H)(e|E)(i|I)(g|G)(h|H)(t|T) { yylval->stringVal = new string("size.height"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(a|A)(t|T)(t|T)(a|A)(c|C)(k|K).(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("size.attack.dist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(p|P)(r|R)(o|O)(j|J).(a|A)(t|T)(t|T)(a|A)(c|C)(k|K).(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("size.proj.attack.dist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(p|P)(r|R)(o|O)(j|J).(d|D)(o|O)(s|S)(c|C)(a|A)(l|L)(e|E) { yylval->stringVal = new string("size.proj.doscale"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(h|H)(e|E)(a|A)(d|D).(p|P)(o|O)(s|S).(x|X) { yylval->stringVal = new string("size.head.pos.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(h|H)(e|E)(a|A)(d|D).(p|P)(o|O)(s|S).(y|Y) { yylval->stringVal = new string("size.head.pos.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(m|M)(i|I)(d|D).(p|P)(o|O)(s|S).(x|X) { yylval->stringVal = new string("size.mid.pos.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(m|M)(i|I)(d|D).(p|P)(o|O)(s|S).(y|Y) { yylval->stringVal = new string("size.mid.pos.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(s|S)(h|H)(a|A)(d|D)(o|O)(w|W)(o|O)(f|F)(f|F)(s|S)(e|E)(t|T) { yylval->stringVal = new string("size.shadowoffset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(d|D)(r|R)(a|A)(w|W).(o|O)(f|F)(f|F)(s|S)(e|E)(t|T).(x|X) { yylval->stringVal = new string("size.draw.offset.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(s|S)(i|I)(z|Z)(e|E).(d|D)(r|R)(a|A)(w|W).(o|O)(f|F)(f|F)(s|S)(e|E)(t|T).(y|Y) { yylval->stringVal = new string("size.draw.offset.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}


(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(w|W)(a|A)(l|L)(k|K).(f|F)(w|W)(d|D).(x|X) { yylval->stringVal = new string("velocity.walk.fwd.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(w|W)(a|A)(l|L)(k|K).(b|B)(a|A)(c|C)(k|K).(x|X) { yylval->stringVal = new string("velocity.walk.back.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N).(f|F)(w|W)(d|D).(x|X) { yylval->stringVal = new string("velocity.run.fwd.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N).(f|F)(w|W)(d|D).(y|Y) { yylval->stringVal = new string("velocity.run.fwd.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N).(b|B)(a|A)(c|C)(k|K).(x|X) { yylval->stringVal = new string("velocity.run.back.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N).(b|B)(a|A)(c|C)(k|K).(y|Y) { yylval->stringVal = new string("velocity.run.back.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(j|J)(u|U)(m|M)(p|P).(y|Y) { yylval->stringVal = new string("velocity.jump.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P).(y|Y) { yylval->stringVal = new string("velocity.runjump.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(j|J)(u|U)(m|M)(p|P).(n|N)(e|E)(u|U).(x|X) { yylval->stringVal = new string("velocity.jump.neu.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(j|J)(u|U)(m|M)(p|P).(b|B)(a|A)(c|C)(k|K).(x|X) { yylval->stringVal = new string("velocity.jump.back.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(j|J)(u|U)(m|M)(p|P).(f|F)(w|W)(d|D).(x|X) { yylval->stringVal = new string("velocity.jump.fwd.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P).(b|B)(a|A)(c|C)(k|K).(x|X) { yylval->stringVal = new string("velocity.runjump.back.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(r|R)(u|U)(n|N)(j|J)(u|U)(m|M)(p|P).(f|F)(w|W)(d|D).(x|X) { yylval->stringVal = new string("velocity.runjump.fwd.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(y|Y) { yylval->stringVal = new string("velocity.airjump.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(n|N)(e|E)(u|U).(x|X) { yylval->stringVal = new string("velocity.airjump.neu.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(b|B)(a|A)(c|C)(k|K).(x|X) { yylval->stringVal = new string("velocity.airjump.back.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(f|F)(w|W)(d|D).(x|X) { yylval->stringVal = new string("velocity.airjump.fwd.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(x|X) { yylval->stringVal = new string("velocity.air.gethit.groundrecover.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(y|Y) { yylval->stringVal = new string("velocity.air.gethit.groundrecover.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(m|M)(u|U)(l|L).(x|X) { yylval->stringVal = new string("velocity.air.gethit.airrecover.mul.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(m|M)(u|U)(l|L).(y|Y) { yylval->stringVal = new string("velocity.air.gethit.airrecover.mul.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(a|A)(d|D)(d|D).(x|X) { yylval->stringVal = new string("velocity.air.gethit.airrecover.add.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(a|A)(d|D)(d|D).(y|Y) { yylval->stringVal = new string("velocity.air.gethit.airrecover.add.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("velocity.air.gethit.airrecover.back"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(f|F)(w|W)(d|D) { yylval->stringVal = new string("velocity.air.gethit.airrecover.fwd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(u|U)(p|P) { yylval->stringVal = new string("velocity.air.gethit.airrecover.up"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(d|D)(o|O)(w|W)(n|N) { yylval->stringVal = new string("velocity.air.gethit.airrecover.down"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}

(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(n|N)(u|U)(m|M) { yylval->stringVal = new string("movement.airjump.num"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R)(j|J)(u|U)(m|M)(p|P).(h|H)(e|E)(i|I)(g|G)(h|H)(t|T) { yylval->stringVal = new string("movement.airjump.height"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(y|Y)(a|A)(c|C)(c|C)(e|E)(l|L) { yylval->stringVal = new string("movement.yaccel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(s|S)(t|T)(a|A)(n|N)(d|D).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N) { yylval->stringVal = new string("movement.stand.friction"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(c|C)(r|R)(o|O)(u|U)(c|C)(h|H).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N) { yylval->stringVal = new string("movement.crouch.friction"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(s|S)(t|T)(a|A)(n|N)(d|D).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("movement.stand.friction.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(c|C)(r|R)(o|O)(u|U)(c|C)(h|H).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("movement.crouch.friction.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(j|J)(u|U)(m|M)(p|P).(c|C)(h|H)(a|A)(n|N)(g|G)(e|E)(a|A)(n|N)(i|I)(m|M).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("movement.jump.changeanim.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("movement.air.gethit.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("movement.air.gethit.groundrecover.ground.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("movement.air.gethit.groundrecover.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("movement.air.gethit.airrecover.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(a|A)(i|I)(r|R)(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R).(y|Y)(a|A)(c|C)(c|C)(e|E)(l|L) { yylval->stringVal = new string("movement.air.gethit.airrecover.yaccel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(a|A)(i|I)(r|R).(g|G)(e|E)(t|T)(h|H)(i|I)(t|T).(t|T)(r|R)(i|I)(p|P).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("movement.air.gethit.trip.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(o|O)(f|F)(f|F)(s|S)(e|E)(t|T).(x|X) { yylval->stringVal = new string("movement.down.bounce.offset.x"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(o|O)(f|F)(f|F)(s|S)(e|E)(t|T).(y|Y) { yylval->stringVal = new string("movement.down.bounce.offset.y"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(y|Y)(a|A)(c|C)(c|C)(e|E)(l|L) { yylval->stringVal = new string("movement.down.bounce.yaccel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E).(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(l|L)(e|E)(v|V)(e|E)(l|L) { yylval->stringVal = new string("movement.down.bounce.groundlevel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
(m|M)(o|O)(v|V)(e|E)(m|M)(e|E)(n|N)(t|T).(d|D)(o|O)(w|W)(n|N).(f|F)(r|R)(i|I)(c|C)(t|T)(i|I)(o|O)(n|N).(t|T)(h|H)(r|R)(e|E)(s|S)(h|H)(o|O)(l|L)(d|D) { yylval->stringVal = new string("movement.down.friction.threshold"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CONST_PARAM" <<endl; 
	return token::CONST_PARAM;}
 /* =============  HITDEFATTR AND PARAMS ========================= */

(h|H)(i|I)(t|T)(d|D)(e|E)(f|F)(a|A)(t|T)(t|T)(r|R)  { yylval->stringVal = new string("hitdefattr"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_HITDEF: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_HITDEF;}


  /* =============  GETHITVAR PARAM ========================= */


(a|A)(n|N)(i|I)(m|M)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("animtype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("airtype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(c|C)(t|T)(r|R)(l|L)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("ctrltime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(c|C)(h|H)(a|A)(i|I)(n|N)(i|I)(d|D) { yylval->stringVal = new string("chainid"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(d|D)(a|A)(m|M)(a|A)(g|G)(e|E) { yylval->stringVal = new string("damage"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L)(c|C)(o|O)(u|U)(n|N)(t|T) { yylval->stringVal = new string("fallcount"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(d|D)(a|A)(m|M)(a|A)(g|G)(e|E) { yylval->stringVal = new string("fall.damage"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(x|X)(v|V)(e|E)(l|L) { yylval->stringVal = new string("fall.xvel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(y|Y)(v|V)(e|E)(l|L) { yylval->stringVal = new string("fall.yvel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R) { yylval->stringVal = new string("fall.recover"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("fall.recovertime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("fall.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(k|K)(i|I)(l|L)(l|L) { yylval->stringVal = new string("fall.kill"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("fall.envshake.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(f|F)(r|R)(e|E)(q|Q) { yylval->stringVal = new string("fall.envshake.freq"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(a|A)(m|M)(p|P)(l|L) { yylval->stringVal = new string("fall.envshake.ampl"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(f|F)(a|A)(l|L)(l|L).(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(p|P)(h|H)(a|A)(s|S)(e|E) { yylval->stringVal = new string("fall.envshake.phase"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("groundtype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(g|G)(u|U)(a|A)(r|R)(d|D)(e|E)(d|D) { yylval->stringVal = new string("guarded"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(h|H)(i|I)(t|T)(s|S)(h|H)(a|A)(k|K)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("hitshaketime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "GETHIT_PARAM" <<endl; 
	return token::KEY_IDENTIFIER;}
(h|H)(i|I)(t|T)(i|I)(d|D) { yylval->stringVal = new string("hitid"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(h|H)(i|I)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("hittime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(i|I)(s|S)(b|B)(o|O)(u|U)(n|N)(d|D) { yylval->stringVal = new string("isbound"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(r|R)(e|E)(c|C)(o|O)(v|V)(e|E)(r|R)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("recovertime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(s|S)(l|L)(i|I)(d|D)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("slidetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(x|X)(o|O)(f|F)(f|F) { yylval->stringVal = new string("xoff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(z|Z)(o|O)(f|F)(f|F) { yylval->stringVal = new string("zoff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(x|X)(v|V)(e|E)(l|L) { yylval->stringVal = new string("xvel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(x|X)(v|V)(e|E)(l|L)(a|A)(d|D)(d|D) { yylval->stringVal = new string("xveladd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(y|Y)(o|O)(f|F)(f|F) { yylval->stringVal = new string("yoff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(y|Y)(v|V)(e|E)(l|L) { yylval->stringVal = new string("yvel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}
(y|Y)(v|V)(e|E)(l|L)(a|A)(d|D)(d|D) { yylval->stringVal = new string("yveladd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "(KEY_IDENTIFIER do tipo GETHIT_PARAM)" <<endl; 
	return token::KEY_IDENTIFIER;}




 /* =============  STATE CONTROLLERS ========================= */
(a|A)(f|F)(t|T)(e|E)(r|R)(i|I)(m|M)(a|A)(g|G)(e|E) { yylval->stringVal = new string("afterimage"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
 
(a|A)(f|F)(t|T)(e|E)(r|R)(i|I)(m|M)(a|A)(g|G)(e|E)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("afterimagetime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

        

(a|A)(l|L)(l|L)(p|P)(a|A)(l|L)(f|F)(x|X) { yylval->stringVal = new string("allpalfx"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(n|N)(g|G)(l|L)(e|E)(a|A)(d|D)(d|D) { yylval->stringVal = new string("angleadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
       
(a|A)(n|N)(g|G)(l|L)(e|E)(d|D)(r|R)(a|A)(w|W) { yylval->stringVal = new string("angledraw"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(n|N)(g|G)(l|L)(e|E)(m|M)(u|U)(l|L) { yylval->stringVal = new string("anglemul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(n|N)(g|G)(l|L)(e|E)(s|S)(e|E)(t|T) { yylval->stringVal = new string("angleset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(p|P)(p|P)(e|E)(n|N)(d|D)(t|T)(o|O)(c|C)(l|L)(i|I)(p|P)(b|B)(o|O)(a|A)(r|R)(d|D) { yylval->stringVal = new string("appendtoclipboard"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(s|S)(s|S)(e|E)(r|R)(t|T)(s|S)(p|P)(e|E)(c|C)(i|I)(a|A)(l|L) { yylval->stringVal = new string("assertspecial"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(t|T)(t|T)(a|A)(c|C)(k|K)(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("attackdist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(a|A)(t|T)(t|T)(a|A)(c|C)(k|K)(m|M)(u|U)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("attackmulset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(b|B)(g|G)(p|P)(a|A)(l|L)(f|F)(x|X) { yylval->stringVal = new string("bgpalfx"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(b|B)(i|I)(n|N)(d|D)(t|T)(o|O)(p|P)(a|A)(r|R)(e|E)(n|N)(t|T) { yylval->stringVal = new string("bindtoparent"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(b|B)(i|I)(n|N)(d|D)(t|T)(o|O)(r|R)(o|O)(o|O)(t|T) { yylval->stringVal = new string("bindtoroot"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(b|B)(i|I)(n|N)(d|D)(t|T)(o|O)(t|T)(a|A)(r|R)(g|G)(e|E)(t|T) { yylval->stringVal = new string("bindtotarget"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(c|C)(h|H)(a|A)(n|N)(g|G)(e|E)(a|A)(n|N)(i|I)(m|M) { yylval->stringVal = new string("changeanim"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(c|C)(h|H)(a|A)(n|N)(g|G)(e|E)(a|A)(n|N)(i|I)(m|M)2 { yylval->stringVal = new string("changeanim2"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(c|C)(h|H)(a|A)(n|N)(g|G)(e|E)(S|s)(T|t)(a|A)(T|t)(e|E) { yylval->stringVal = new string("changestate"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(c|C)(l|L)(e|E)(a|A)(r|R)(c|C)(l|L)(i|I)(p|P)(b|B)(o|O)(a|A)(r|R)(d|D) { yylval->stringVal = new string("clearclipboard"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(c|C)(t|T)(r|R)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("ctrlset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(d|D)(e|E)(f|F)(e|E)(n|N)(c|C)(e|E)(m|M)(u|U)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("defencemulset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(d|D)(e|E)(s|S)(t|T)(r|R)(o|O)(y|Y)(s|S)(e|E)(l|L)(f|F) { yylval->stringVal = new string("destroyself"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(d|D)(i|I)(s|S)(p|P)(l|L)(a|A)(y|Y)(t|T)(o|O)(c|C)(l|L)(i|I)(p|P)(b|B)(o|O)(a|A)(r|R)(d|D) { yylval->stringVal = new string("displaytoclipboard"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(e|E)(n|N)(v|V)(c|C)(o|O)(l|L)(o|O)(r|R) { yylval->stringVal = new string("envcolor"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E) { yylval->stringVal = new string("envshake"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(e|E)(x|X)(p|P)(l|L)(o|O)(d|D) { yylval->stringVal = new string("explod"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(e|E)(x|X)(p|P)(l|L)(o|O)(d|D)(b|B)(i|I)(n|N)(d|D)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("explodbindtime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(f|F)(o|O)(r|R)(c|C)(e|E)(f|F)(e|E)(e|E)(d|D)(b|B)(a|A)(c|C)(k|K) { yylval->stringVal = new string("forcefeedback"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(f|F)(a|A)(l|L)(l|L)(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E) { yylval->stringVal = new string("fallenvshake"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(g|G)(a|A)(m|M)(e|E)(m|M)(a|A)(k|K)(e|E)(a|A)(n|N)(i|I)(m|M) { yylval->stringVal = new string("gamemakeanim"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(g|G)(r|R)(a|A)(v|V)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("gravity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(a|A)(d|D)(d|D) { yylval->stringVal = new string("hitadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(b|B)(y|Y) { yylval->stringVal = new string("hitby"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(d|D)(e|E)(f|F) { yylval->stringVal = new string("hitdef"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(f|F)(a|A)(l|L)(l|L)(d|D)(a|A)(m|M)(a|A)(g|G)(e|E) { yylval->stringVal = new string("hitfalldamage"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(f|F)(a|A)(l|L)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("hitfallset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(f|F)(a|A)(l|L)(l|L)(v|V)(e|E)(l|L) { yylval->stringVal = new string("hitfallvel"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(o|O)(v|V)(e|E)(r|R)(r|R)(i|I)(d|D)(e|E) { yylval->stringVal = new string("hitoverride"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(h|H)(i|I)(t|T)(v|V)(e|E)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("hitvelset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(l|L)(i|I)(f|F)(e|E)(a|A)(d|D)(d|D) { yylval->stringVal = new string("lifeadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(l|L)(i|I)(f|F)(e|E)(s|S)(e|E)(t|T) { yylval->stringVal = new string("lifeset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(m|M)(a|A)(k|K)(e|E)(d|D)(u|U)(s|S)(t|T) { yylval->stringVal = new string("makedust"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(m|M)(o|O)(d|D)(i|I)(f|F)(y|Y)(e|E)(x|X)(p|P)(l|L)(o|O)(d|D) { yylval->stringVal = new string("modifyexplod"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(m|M)(o|O)(v|V)(e|E)(h|H)(i|I)(t|T)(r|R)(e|E)(s|S)(e|E)(t|T) { yylval->stringVal = new string("movehitreset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(n|N)(o|O)(t|T)(h|H)(i|I)(t|T)(b|B)(y|Y) { yylval->stringVal = new string("nothitby"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(n|N)(u|U)(l|L)(l|L) { yylval->stringVal = new string("null"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(o|O)(f|F)(f|F)(s|S)(e|E)(t|T) { yylval->stringVal = new string("offset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(a|A)(l|L)(f|F)(x|X) { yylval->stringVal = new string("palfx"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(p|P)(a|A)(r|R)(e|E)(n|N)(t|T)(v|V)(d|D)(i|I)(s|S)(t|T) { yylval->stringVal = new string("parentdist"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(a|A)(r|R)(e|E)(n|N)(t|T)(v|V)(a|A)(r|R)(a|A)(d|D)(d|D) { yylval->stringVal = new string("parentvaradd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(a|A)(r|R)(e|E)(n|N)(t|T)(v|V)(a|A)(r|R)(s|S)(e|E)(t|T) { yylval->stringVal = new string("parentvarset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(a|A)(u|U)(s|S)(e|E) { yylval->stringVal = new string("pause"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(l|L)(a|A)(y|Y)(e|E)(r|R)(p|P)(u|U)(s|S)(h|H) { yylval->stringVal = new string("playerpush"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(l|L)(a|A)(y|Y)(s|S)(n|N)(d|D) { yylval->stringVal = new string("playsnd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(o|O)(s|S)(a|A)(d|D)(d|D) { yylval->stringVal = new string("posadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(o|O)(s|S)(f|F)(r|R)(e|E)(e|E)(z|Z)(e|E) { yylval->stringVal = new string("posfreeze"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(o|O)(s|S)(s|S)(e|E)(t|T) { yylval->stringVal = new string("posset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(o|O)(w|W)(e|E)(r|R)(a|A)(d|D)(d|D) { yylval->stringVal = new string("poweradd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

(p|P)(o|O)(w|W)(e|E)(r|R)(s|S)(e|E)(t|T) { yylval->stringVal = new string("powerset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(p|P)(r|R)(o|O)(j|J)(e|E)(c|C)(t|T)(i|I)(l|L)(e|E) { yylval->stringVal = new string("projectile"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(r|R)(e|E)(m|M)(o|O)(v|V)(e|E)(e|E)(x|X)(p|P)(l|L)(o|O)(d|D) { yylval->stringVal = new string("removeexplod"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(r|R)(e|E)(v|V)(e|E)(r|R)(s|S)(a|A)(l|L)(d|D)(e|E)(f|F) { yylval->stringVal = new string("reversaldef"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(s|S)(c|C)(r|R)(e|E)(e|E)(n|N)(b|B)(o|O)(u|U)(n|N)(d|D) { yylval->stringVal = new string("screenbound"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(s|S)(e|E)(l|L)(f|F)(S|s)(T|t)(a|A)(T|t)(e|E) { yylval->stringVal = new string("selfstate"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(s|S)(p|P)(r|R)(p|P)(r|R)(i|I)(o|O)(r|R)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("sprpriority"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: " <<  yylval->stringVal->c_str() <<endl; 
	return token::KEY_IDENTIFIER;}

(S|s)(T|t)(a|A)(T|t)(e|E)(T|t)(y|Y)(p|P)(e|E)(s|S)(e|E)(t|T) { yylval->stringVal = new string("statetypeset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(S|s)(n|N)(d|D)(p|P)(a|A)(n|N) { yylval->stringVal = new string("sndpan"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(S|s)(T|t)(o|O)(p|P)(S|s)(n|N)(d|D) { yylval->stringVal = new string("stopsnd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(s|S)(u|U)(p|P)(e|E)(r|R)(p|P)(a|A)(u|U)(s|S)(e|E) { yylval->stringVal = new string("superpause"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(b|B)(i|I)(n|N)(d|D) { yylval->stringVal = new string("targetbind"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(d|D)(r|R)(o|O)(p|P) { yylval->stringVal = new string("targetdrop"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(f|F)(a|A)(c|C)(i|I)(n|N)(g|G) { yylval->stringVal = new string("targetfacing"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(l|L)(i|I)(f|F)(e|E)(a|A)(d|D)(d|D) { yylval->stringVal = new string("targetlifeadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(p|P)(o|O)(w|W)(e|E)(r|R)(a|A)(d|D)(d|D) { yylval->stringVal = new string("targetpoweradd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(S|s)(T|t)(a|A)(T|t)(e|E) { yylval->stringVal = new string("targetstate"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(v|V)(e|E)(l|L)(a|A)(d|D)(d|D) { yylval->stringVal = new string("targetveladd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)(v|V)(e|E)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("targetvelset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(r|R)(a|A)(n|N)(S|s) { yylval->stringVal = new string("trans"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(t|T)(u|U)(r|R)(n|N) { yylval->stringVal = new string("turn"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(a|A)(r|R)(a|A)(d|D)(d|D) { yylval->stringVal = new string("varadd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(a|A)(r|R)(r|R)(a|A)(n|N)(d|D)(o|O)(m|M)  { yylval->stringVal = new string("varrandom");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(a|A)(r|R)(r|R)(a|A)(n|N)(g|G)(e|E)(s|S)(e|E)(t|T) { yylval->stringVal = new string("varrangeset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(a|A)(r|R)(s|S)(e|E)(t|T) { yylval->stringVal = new string("varset"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(e|E)(l|L)(a|A)(d|D)(d|D) { yylval->stringVal = new string("veladd"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(e|E)(l|L)(m|M)(u|U)(l|L) { yylval->stringVal = new string("velmul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(v|V)(e|E)(l|L)(s|S)(e|E)(t|T) { yylval->stringVal = new string("velset");  SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: KEY_STATE_CONTROLER: " <<  yylval->stringVal->c_str()  <<endl; return token::KEY_IDENTIFIER; }
        
(w|W)(i|I)(d|D)(t|T)(h|H) { yylval->stringVal = new string("width"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(z|Z)(o|O)(o|O)(m|M) { yylval->stringVal = new string("zoom"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
        
(u|U)(n|N)(k|K)(n|N)(o|O)(w|W)(n|N) { yylval->stringVal = new string("unknown"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; return token::KEY_IDENTIFIER;}
		
(d|D)(e|E)(b|B)(u|U)(g|G) { yylval->stringVal = new string("debug"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: KEY_STATE_CONTROLER: "<<  yylval->stringVal->c_str()  <<endl; return token::KEY_IDENTIFIER;}
	
	 /* =============  STATE CONTROLLERS ========================= */

	/*================   TRIGGER REDIRECTION   ===================
The complete list of redirection keywords is the following:

-) parent
    Redirects the trigger to the player's parent. (Player must be a helper.)
-) root
    Redirects the trigger to the root.
-) helper
    Redirects the trigger to the first helper found. See the related trigger "NumHelper" in the trigger documentation.
-) helper(ID)
    ID should be a well-formed expression that evaluates to a positive integer. The trigger is then redirected to a helper with the corresponding ID number.
-) target
    Redirects the trigger to the first target found.
-) target(ID)
    ID should be a well-formed expression that evaluates to a non- negative integer. The trigger is then redirected to a target with the corresponding targetID. The targetID is specified in the "ID" parameter of a HitDef controller.
-) partner
    Redirects the trigger to the player's partner. Normal helpers and neutral players are not considered opponents. See the related trigger "numpartner" in the trigger documentation.
-) enemy
    Redirects the trigger to the first opponent found. Normal helpers and neutral players are not considered opponents. See the related trigger "numenemy" in the trigger documentation.
-) enemy(n)
    n should be a well-formed expression that evaluates to a non- negative integer. The trigger is redirected to the n'th opponent.
-) enemyNear
    Redirects the trigger to the nearest opponent.
-) enemyNear(n)
    n should be a well-formed expression that evaluates to a non- negative integer. The trigger is redirected to the n'th-nearest opponent.
-) playerID(ID)
    n should be a well-formed expression that evaluates to a non- negative integer. The trigger is redirected to the player with unique ID equal to ID. See the "ID" and "PlayerExistID" triggers in the trigger documentation.

If the trigger is redirected to an invalid destination (for instance, if it is retargeted to a helper when none exist), then an error is returned. See the section on SC values.

Note: multiple redirection (e.g., root,target,time) is not currently supported.

	*/


(e|E)(n|N)(e|E)(m|M)(y|Y)(n|N)(e|E)(a|A)(r|R)  { yylval->stringVal = new string("enemynear"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str()  <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER;}

(h|H)(e|E)(l|L)(p|P)(e|E)(r|R) {  yylval->stringVal = new string("helper"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER;}

(t|T)(a|A)(r|R)(g|G)(e|E)(t|T)  {  yylval->stringVal = new string("target"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER;}
	
(e|E)(n|N)(e|E)(m|M)(y|Y) { yylval->stringVal = new string("enemy"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER; }

[pP][aA][rR][tT][nN][eE][rR] { yylval->stringVal = new string("partner"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER; }

[pP][lL][aA][yY][eE][rR][iI][dD] {  yylval->stringVal = new string("playerid");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER; }

[rR][oO][oO][tT] { yylval->stringVal = new string("root"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER; }

[pP][aA][rR][eE][nN][tT] { yylval->stringVal = new string("parent"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "TRIGGER_REDIRECTION_IDENTIFIER: " << yylval->stringVal->c_str() <<endl; 
	return token::TRIGGER_REDIRECTION_IDENTIFIER; }

	
[a-z\'A-Z_][\'a-zA-Z0-9_.]* { yylval->stringVal = new string(yytext, yyleng); 
SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer IDENTIFIER= "<<  yylval->stringVal->c_str() <<endl;
return token::IDENTIFIER; }



	/*  HIT DEF PARAMETERS ==================  */


 
	/*    yaccel ok  */
    
	/*     hitflag ok  */
    
	/*	  affectteam  ok  */
    
	/*    animtype ok gethitparam  */
(a|A)(i|I)(r|R).(a|A)(n|N)(i|I)(m|M)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("air.animtype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
(f|F)(a|A)(l|L)(l|L).(a|A)(n|N)(i|I)(m|M)(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("fall.animtype"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
    
	/*    damage ok gethitparam  */
    
    
	/*    sparkno ok   */
	/*    guard.sparkno ok   */

(a|A)(i|I)(r|R).(t|T)(y|Y)(p|P)(e|E) { yylval->stringVal = new string("air.type"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(a|A)(i|I)(r|R).(h|H)(i|I)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("air.hittime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(a|A)(i|I)(r|R).(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("air.velocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(a|A)(i|I)(r|R)(g|G)(u|U)(a|A)(r|R)(d|D).(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("airguard.velocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(r|R)(o|O)(u|U)(n|N)(d|D).(c|C)(o|O)(r|R)(n|N)(e|E)(r|R)(p|P)(u|U)(s|S)(h|H).(v|V)(e|E)(l|L)(o|O)(f|F)(f|F) { yylval->stringVal = new string("ground.cornerpush.veloff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(a|A)(i|I)(r|R).(c|C)(o|O)(r|R)(n|N)(e|E)(r|R)(p|P)(u|U)(s|S)(h|H).(v|V)(e|E)(l|L)(o|O)(f|F)(f|F) { yylval->stringVal = new string("air.cornerpush.veloff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(d|D)(o|O)(w|W)(n|N).(c|C)(o|O)(r|R)(n|N)(e|E)(r|R)(p|P)(u|U)(s|S)(h|H).(v|V)(e|E)(l|L)(o|O)(f|F)(f|F) { yylval->stringVal = new string("down.cornerpush.veloff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(g|G)(u|U)(a|A)(r|R)(d|D).(c|C)(o|O)(r|R)(n|N)(e|E)(r|R)(p|P)(u|U)(s|S)(h|H).(v|V)(e|E)(l|L)(o|O)(f|F)(f|F) { yylval->stringVal = new string("guard.cornerpush.veloff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(a|A)(i|I)(r|R)(g|G)(u|U)(a|A)(r|R)(d|D).(c|C)(o|O)(r|R)(n|N)(e|E)(r|R)(p|P)(u|U)(s|S)(h|H).(v|V)(e|E)(l|L)(o|O)(f|F)(f|F) { yylval->stringVal = new string("airguard.cornerpush.veloff"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
      
(a|A)(i|I)(r|R)(g|G)(u|U)(a|A)(r|R)(d|D).(c|C)(t|T)(r|R)(l|L)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("airguard.ctrltime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(a|A)(i|I)(r|R).(j|J)(u|U)(g|G)(g|G)(l|L)(e|E) { yylval->stringVal = new string("air.juggle"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}

 	/*    p2stateno ok     */
	/*    fall ok    */
	/*    fall.recover ok gethitparam             */
	/*    fall.recovertime ok gethitparam         */
	/*    fall.damage ok gethitparam              */
(a|A)(i|I)(r|R).(f|F)(a|A)(l|L)(l|L) { yylval->stringVal = new string("air.fall"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
(d|D)(o|O)(w|W)(n|N).(v|V)(e|E)(l|L)(o|O)(c|C)(i|I)(t|T)(y|Y) { yylval->stringVal = new string("down.velocity"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(d|D)(o|O)(w|W)(n|N).(h|H)(i|I)(t|T)(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("down.hittime"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(d|D)(o|O)(w|W)(n|N).(b|B)(o|O)(u|U)(n|N)(c|C)(e|E) { yylval->stringVal = new string("down.bounce"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
	/*    id ok    */
	/*    chainID  ok gethitparam          */
	/*    fall.kill OK   */
     
(p|P)(a|A)(l|L)(f|F)(x|X).(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("palfx.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(p|P)(a|A)(l|L)(f|F)(x|X).(m|M)(u|U)(l|L) { yylval->stringVal = new string("palfx.mul"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(p|P)(a|A)(l|L)(f|F)(x|X).(a|A)(d|D)(d|D) { yylval->stringVal = new string("palfx.add"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(t|T)(i|I)(m|M)(e|E) { yylval->stringVal = new string("envshake.time"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(f|F)(r|R)(e|E)(q|Q) { yylval->stringVal = new string("envshake.freq"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(a|A)(m|M)(p|P)(l|L) { yylval->stringVal = new string("envshake.ampl"); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
     
(e|E)(n|N)(v|V)(s|S)(h|H)(a|A)(k|K)(e|E).(p|P)(h|H)(a|A)(s|S)(e|E) { yylval->stringVal = new string("envshake.phase "); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< " ( HitDef controller identifier) KEY_IDENTIFIER: "<<  yylval->stringVal->c_str()  <<endl; 
	return token::KEY_IDENTIFIER;}
    
	/*    fall.envshake.time OK   */
	/*    fall.envshake.freq OK   */
	/*    fall.envshake.ampl OK   */
	/*    fall.envshake.phase OK   */

	/*  TRIGGERS   
	
	AILevel
Abs - done - FUNC_IDENTIFIER
Acos - done - FUNC_IDENTIFIER
Alive - done - KEY_IDENTIFIER
Anim - done - KEY_ANIM
AnimElem - done -  FUNC_IDENTIFIER
AnimElemNo - done - FUNC_IDENTIFIER
AnimElemTime - done - FUNC_IDENTIFIER
AnimExist - done - FUNC_IDENTIFIER
AnimTime - done - KEY_IDENTIFIER
Asin - done - FUNC_IDENTIFIER
Atan - done - FUNC_IDENTIFIER
AuthorName - done - KEY_IDENTIFIER

B
-----------------------
BackEdgeBodyDist - done - KEY_IDENTIFIER
BackEdgeDist - done - KEY_IDENTIFIER

C
-----------------------
CanRecover - done  - KEY_IDENTIFIER
Ceil - done - FUNC_IDENTIFIER
Command - done - KEY_IDENTIFIER
Const - done - FUNC_CONST
Const240p - FUNC_IDENTIFIER
Const480p - FUNC_IDENTIFIER
Const720p - FUNC_IDENTIFIER
Cos - done - FUNC_IDENTIFIER
Ctrl - done - KEY_IDENTIFIER

D
-----------------------
DrawGame - KEY_IDENTIFIER

E
-----------------------
E - NOT DEFINED - WILL COMPILE LIKE IDENTIFIER
Exp - done - FUNC_IDENTIFIER

F
-----------------------
FVar - done - FUNC_FVAR
Facing - done - KEY_IDENTIFIER
Floor - done - FUNC_IDENTIFIER
FrontEdgeBodyDist - done - KEY_IDENTIFIER
FrontEdgeDist - done - KEY_IDENTIFIER

G
-----------------------
GameTime - done - KEY_IDENTIFIER
GetHitVar - DONE - FUNC_GETHITVAR

H
-----------------------
HitCount - done - KEY_IDENTIFIER
HitDefAttr - DONE - KEY_HITDEF
HitFall - done - KEY_IDENTIFIER
HitOver - done - KEY_IDENTIFIER
HitPauseTime - done - KEY_IDENTIFIER
HitShakeOver - done - KEY_IDENTIFIER
HitVel - done - KEY_IDENTIFIER

I
-----------------------
ID - done - KEY_IDENTIFIER
IfElse - done - FUNC_IFELSE
InGuardDist - done - KEY_IDENTIFIER
IsHelper - done - FUNC_IDENTIFIER
IsHomeTeam - DONE - KEY_IDENTIFIER

L
-----------------------
Life - done - KEY_IDENTIFIER
LifeMax - done - KEY_IDENTIFIER
Ln - done - FUNC_IDENTIFIER
Log - done - FUNC_LOG
Lose DONE -  - KEY_IDENTIFIER

M
-----------------------
MatchNo - done - KEY_IDENTIFIER
MatchOver - done - KEY_IDENTIFIER
MoveContact - DONE - KEY_IDENTIFIER
MoveGuarded - done - KEY_IDENTIFIER
MoveHit - DONE - KEY_IDENTIFIER
MoveReversed - DONE - KEY_IDENTIFIER
MoveType - done - KEY_IDENTIFIER

N
-----------------------
Name - done - KEY_IDENTIFIER
NumEnemy - DONE - KEY_IDENTIFIER
NumExplod - done - FUNC_IDENTIFIER
NumHelper - DONE - FUNC_IDENTIFIER
NumPartner - DONE - KEY_IDENTIFIER
NumProj - DONE - KEY_IDENTIFIER
NumProjID - DONE - FUNC_IDENTIFIER
NumTarget - DONE - FUNC_IDENTIFIER

P
-----------------------
P1Name - done - KEY_IDENTIFIER
P2BodyDist - done - KEY_IDENTIFIER
P2Dist - done - KEY_IDENTIFIER
P2Life - done - KEY_IDENTIFIER
P2MoveType - done - KEY_IDENTIFIER
P2Name - done - KEY_IDENTIFIER
P2StateNo - done - KEY_IDENTIFIER
P2StateType - done - KEY_IDENTIFIER
P3Name - done - KEY_IDENTIFIER
P4Name - done - KEY_IDENTIFIER
PalNo - done - KEY_IDENTIFIER
ParentDist - done - KEY_IDENTIFIER
Pi - done - KEY_IDENTIFIER
PlayerIDExist - done - FUNC_IDENTIFIER
Pos - done - KEY_IDENTIFIER
Power - done - KEY_IDENTIFIER
PowerMax - done - KEY_IDENTIFIER
PrevStateNo - done - KEY_IDENTIFIER
ProjCancelTime - DONE - FUNC_IDENTIFIER
ProjContact - DONE - FUNC_PROJCONTACT
ProjContactTime - DONE - FUNC_IDENTIFIER
ProjGuarded - DONE - FUNC_IDENTIFIER
ProjGuardedTime - DONE - FUNC_IDENTIFIER
ProjHit - DONE -FUNC_IDENTIFIER
ProjHitTime - DONE - FUNC_IDENTIFIER

R
-----------------------
Random - done - KEY_IDENTIFIER
RootDist - done - KEY_IDENTIFIER
RoundNo - done - KEY_IDENTIFIER
RoundState - done - KEY_IDENTIFIER
RoundsExisted - done - KEY_IDENTIFIER

S
-----------------------
ScreenPos - done - KEY_IDENTIFIER
SelfAnimExist - done - FUNC_IDENTIFIER
Sin - done - FUNC_IDENTIFIER
StateNo - DONE - KEY_IDENTIFIER
StateType - done - KEY_STATETYPE
SysFVar - donE - FUNC_IDENTIFIER
SysVar - done - FUNC_SYSVAR

T
-----------------------
Tan - done - FUNC_IDENTIFIER
TeamMode - DONE - FUNC_IDENTIFIER
TeamSide - DONE - KEY_IDENTIFIER
TicksPerSecond - DONE - KEY_IDENTIFIER
Time - DONE - KEY_IDENTIFIER
TimeMod - DONE - FUNC_IDENTIFIER

U
-----------------------
UniqHitCount - DONE - KEY_IDENTIFIER

V
-----------------------
Var - done - FUNC_VAR
Vel - done - KEYWORD

W
-----------------------
Win - DONE - KEY_IDENTIFIER


Keywords

"vel" - DONE - KEYWORD
"velx" - DONE - KEYWORD
"vely" - DONE - KEYWORD
"hitvelx" - DONE - KEYWORD
"hitvely" - DONE - KEYWORD
"screenposy" - DONE - KEYWORD
"screenposx" - DONE - KEYWORD
"posy" - DONE - KEYWORD
"posx" - DONE - KEYWORD
"p2bodydistx" - DONE - KEYWORD
"p2bodydisty" - DONE - KEYWORD
"parentdistx" - DONE - KEYWORD
"parentdisty" - DONE - KEYWORD
"p2distx" - DONE - KEYWORD
"p2disty" - DONE - KEYWORD
"rootdistx" - DONE - KEYWORD
"rootdisty" - DONE - KEYWORD
	*/
			  

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


":=" { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"Lexer Token: "<< "CMD_ASSIGN" <<endl; 
	return token::CMD_ASSIGN; }
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
namespace CmdCompiler {

CScanner::CScanner(std::istream* in,
		 std::ostream* out)
    : CmdFlexLexer(in, out)
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
int CmdFlexLexer::yylex()
{
    std::cerr << "in CmdFlexLexer::yylex() !" << endl;
    return 0;
}  
*/
/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */
/*
int CmdFlexLexer::Cmdwrap()
{
    return 1;
}
*/