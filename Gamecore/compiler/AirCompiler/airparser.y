/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 %{ /*** C/C++ Declarations ***/

#include <list>
#include <queue>
#include <malloc.h>  // _alloca is used by the parser
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stack>
#include "../../mugen/ast/all.h"
#include "../../SGF_Global.h"
#define YYDEBUG 1

#include "air_driver.h"

#define bugon(a) if ((a)){ printf("parsing bug at %s:%d\n", __FILE__, __LINE__); }


%}
/*** yacc/bison Declarations ***/

%glr-parser
%require "2.4.1"
/* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* write out a header file containing the token defines */
%defines
/* add debug output code to generated parser. disable this for release
 * versions. */
%debug
/* start symbol is named "start" */
%start lines
%name-prefix="AirCompiler"

%define parser_class_name "Parser"
/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
    int  			integerVal;
    double 			doubleVal;
    std::string*	stringVal;
    void*			cvalue;
    }
%type <cvalue> flip
%type <cvalue> color_sub
%type <cvalue> double_list

%token			END	     0	"end of file"
%token			EOL		"end of line"


%token <integerVal> 	INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING		"string"

//Air File tokens
%token  <stringVal> ACBEGIN
%token  <stringVal> ACTION
%token  <stringVal> LOOPSTART
%token  <stringVal> COLLISION_DEFENSE_DEFAULT
%token  <stringVal> COLLISION_ATTACK_DEFAULT
%token  <stringVal> COLLISION_DEFENSE
%token  <stringVal> COLLISION_ATTACK
%token  <stringVal> HORIZONTALFLIP
%token  <stringVal> VERTIKALFLIP
%token  <stringVal> HVFLIP
%token  <stringVal> ALPHA_BLEND
%token  <stringVal> ALPHA_BLEND_SHORTHAND
%token  <stringVal> COLOR_SUBTRACT
%token  <stringVal> COLOR_ADDITION
%token  COMMENT
%destructor { delete $$; } <stringVal>

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "air_driver.h"
#include "scanner.h"
#include "../../util/SGF_Debug.h"
/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

lines :   /* empty */
      |   lines AIRFILE 
      |   EOL
      |   error 
      ;


AIRFILE: '[' ACBEGIN ACTION DOUBLE ']' {driver.Ast->makeSection(driver.Ast->makeHeader($2, $3, $4));}
        | COLLISION_ATTACK_DEFAULT ':' DOUBLE  EOL   {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword($1),driver.Ast->makeNumber($3));}
        | COLLISION_DEFENSE_DEFAULT ':' DOUBLE  EOL  {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword($1), driver.Ast->makeNumber($3));}    
        | COLLISION_ATTACK ':' DOUBLE EOL           {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword($1), driver.Ast->makeNumber($3));}
        | COLLISION_DEFENSE ':' DOUBLE  EOL          {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword($1), driver.Ast->makeNumber($3));}
        | COLLISION_ATTACK  '[' DOUBLE ']' '='  double_list  EOL {driver.Ast->makeAttributeArray(driver.Ast->makeKeyword($1), driver.Ast->makeNumber($3), (SGF::Ast::CValueList *)($6));}
        | COLLISION_DEFENSE '[' DOUBLE ']' '='  double_list  EOL {driver.Ast->makeAttributeArray(driver.Ast->makeKeyword($1), driver.Ast->makeNumber($3), (SGF::Ast::CValueList *)($6));}
        		
		|  double_list EOL { driver.Ast->addValueToSection((SGF::Ast::CValue*)($1)); }
		|  double_list ',' EOL { driver.Ast->addValueToSection((SGF::Ast::CValue*)($1)); }
		|  double_list  ',' ',' color_sub EOL {SGF::Ast::CValueList *id=driver.Ast->addToValueList((SGF::Ast::CValueList *)$1,driver.Ast->makeValueString()); id=driver.Ast->addToValueList(id,(SGF::Ast::CValue*)$4);driver.Ast->addValueToSection((SGF::Ast::CValue*)(id));}
		|  double_list  ',' flip EOL {SGF::Ast::CValueList *id=driver.Ast->addToValueList((SGF::Ast::CValueList *)$1,(SGF::Ast::CValue*)$3); driver.Ast->addValueToSection((SGF::Ast::CValue*)(id));}
		|  double_list  ',' flip ',' color_sub EOL {SGF::Ast::CValueList *id=driver.Ast->addToValueList((SGF::Ast::CValueList *) $1,(SGF::Ast::CValue*)$3); id=driver.Ast->addToValueList(id,(SGF::Ast::CValue*)$5);driver.Ast->addValueToSection((SGF::Ast::CValue*)(id));}
		|  LOOPSTART {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword($1));}
        |  EOL
        |   error
        ;

double_list:
     DOUBLE ',' DOUBLE { $$=driver.Ast->makeValueList(driver.Ast->makeNumber($1),driver.Ast->makeNumber($3));}
	 | double_list ',' DOUBLE   {$$=driver.Ast->addToValueList((SGF::Ast::CValueList *)$1, driver.Ast->makeNumber($3));}
	 ;
flip:
   HORIZONTALFLIP  { $$=driver.Ast->makeKeyword($1);}
    | VERTIKALFLIP { $$=driver.Ast->makeKeyword($1);}
    | HVFLIP       { $$=driver.Ast->makeKeyword($1);}
    ;

color_sub:
    COLOR_ADDITION  { $$=driver.Ast->makeKeyword($1);}
    | COLOR_SUBTRACT  { $$=driver.Ast->makeKeyword($1);}
    | ALPHA_BLEND  { $$=driver.Ast->makeKeyword($1);}
    | ALPHA_BLEND_SHORTHAND  { $$=driver.Ast->makeKeyword($1);}
    | ','
	;
%%
// Error function throws an exception (std::string) with the location and error message
void AirCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}


#undef bugon


