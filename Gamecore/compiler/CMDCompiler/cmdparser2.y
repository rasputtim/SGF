/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 %{ /*** C/C++ Declarations ***/

#include <list>
#include <stdio.h>
#include <string.h>
#include <string>
#include <queue>
#include "../../mugen/ast/all.h"
#include "../../global.h"
#define YYDEBUG 1


#define bugon(a) if ((a)){ printf("parsing bug at %s:%d\n", __FILE__, __LINE__); }

static Ast::CConfiguration *configuration=NULL;
static Ast::CSection *currentSection=NULL;
static Ast::CVariable *currentLhs=NULL;
static std::list<Ast::CValue *> *currentRhs;
static Ast::CValue *currentValue;
static std::list<Ast::CModifier *> *currentModifiers;
%}

/*** yacc/bison Declarations ***/

%require "2.4.1"
/* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* write out a header file containing the token defines */
%defines
/* add debug output code to generated parser. disable this for release
 * versions. */
%debug
/* start symbol is named "start" */
%start file
%name-prefix="CmdCompiler"

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
    std::string*		stringVal;
    class CalcNode*		calcnode;
}
%type <stringVal> identificadores
%type <stringVal> plain_key
%type <stringVal> keyidentifier


%left ','
%left '%' '!' CMD_LOGAND CMD_LOGOR CMD_LOGXOR '~' '&' '|' CMD_XOR
%left '=' CMD_NOTEQ '>' '<' CMD_LESSTHANEQ CMD_GREATERTHANEQ
%left '+' '-'
%left '*' CMD_SQUARE '/' 
%left KEY_IDENTIFIER

%left ACOS ABS ANIMELEMNO ANIMELEMTIME ANIMEXIST ASIN ATAN CEIL COS EXP FLOOR GETHITVAR LN
%left NUMEXPLOD NUMHELPER NUMPROJID NUMTARGET PLAYERIDEXIST PROJCANCLETIME SELFANIMEXIST SIN SYSFVAR SYSVAR
%left TAN VAR PROJCONTACTTIME PROJGUARDEDTIME
%right IFELSE LOG CONST


%token			END	     0	"end of file"
%token			EOL		"end of line"

%token <stringVal> QUOTESTRING 
%token <doubleVal> NUMBER "double"
%token <stringVal> IDENTIFIER "string"
%token <stringVal> KEY_IDENTIFIER 
%token <stringVal> KEY_TRIGGERALL
%token <doubleVal> KEY_TRIGGER
%token <stringVal> KEY_PARAM
%token <stringVal> KEY_TYPE
%token <stringVal> KEY_COMMAND

%token '['
%token ']'

%token CMD_DATA
       CMD_STATEDEF
       CMD_STATE


%token <stringVal> CMD_KEY_DOWN
       <stringVal> CMD_KEY_FORWARD
       <stringVal> CMD_KEY_DOWN_FORWARD
       <stringVal> CMD_KEY_BACK
       <stringVal> CMD_KEY_DOWN_BACK
       <stringVal> CMD_KEY_UP_FORWARD
       <stringVal> CMD_KEY_UP
       <stringVal> CMD_KEY_UP_BACK

%token <stringVal> CMD_BUTTON_A
       <stringVal> CMD_BUTTON_B
       <stringVal> CMD_BUTTON_C
       <stringVal> CMD_BUTTON_X
       <stringVal> CMD_BUTTON_Y
       <stringVal> CMD_BUTTON_Z
	   <stringVal> CMD_BUTTON_S

%token  <stringVal> 		KEYWORD
%token COMMENT

%token ID_STRING

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "driver.h"
#include "scanner.h"
#include "../../util/debug.h"
/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

file: 
    line file
    | line

line:
    COMMENT 
    | EOL
	| identsection end_or_comment {}
    | error {yyclearin;}
    ;

identsection:
	| '[' IDENTIFIER ']' {driver.Ast->makeSection($2);};    
	| ident_identifier
	| commandsection
    ;
ident_identifier:
	identificadores '=' identificadores
	;
	
commandsection: 
	'[' KEY_COMMAND ']' {driver.Ast->makeSection(&string("Command"));}; 
    | command_identifier
    | statedef_section
    ;
    
command_identifier:
	KEY_COMMAND '=' expression
	| KEY_COMMAND '=' keylist
	| keyidentifier '=' expression
	;

statedef_section:
    '[' CMD_STATEDEF NUMBER ']' {driver.Ast->makeSection(&string("Statedef"));};
    | statedef_identifier
    | state_section
    ;
    
state_section:
    | '[' CMD_STATE NUMBER ',' identificadores ']' {driver.Ast->makeSection(&string("State")); driver.Ast->addValueToSection(driver.Ast->makeString());driver.Ast->addValueToSection(driver.Ast->makeNumber($3)); };
    | '[' CMD_STATE NUMBER ',' QUOTESTRING ']'					{driver.Ast->makeSection(&string("State"));driver.Ast->addValueToSection(driver.Ast->makeNumber($3)); driver.Ast->addValueToSection(driver.Ast->makeString($5));/*myStateManager->AddState((int)$3.nFloat,"Var" );*/}
    | '[' CMD_STATE NUMBER ',' QUOTESTRING expression ']'	    {driver.Ast->makeSection(&string("State"));driver.Ast->addValueToSection(driver.Ast->makeNumber($3)); driver.Ast->addValueToSection(driver.Ast->makeString($5));/*myStateManager->AddState((int)$3.nFloat,$5.str);*/} 
	| '[' CMD_STATE NUMBER ',' error ']'						{driver.Ast->makeSection(&string("State"));driver.Ast->addValueToSection(driver.Ast->makeNumber($3));/*myStateManager->AddState((int)$3.nFloat,"Nothing");*/}
    | trigger_section
    | param_sectiom
    | type_section
    ;
    
identificadores:
		IDENTIFIER { driver.Ast->addToString($1);}
		| identificadores IDENTIFIER { driver.Ast->addToString($2);}
		;

statedef_identifier:

trigger_section:
			KEY_TRIGGER '=' expression
			| KEY_TRIGGERALL '=' expression
			;

param_sectiom:
		 KEY_PARAM '=' expression
		;	

type_section:
	  KEY_TYPE '=' identificadores
	  | KEY_TYPE '=' QUOTESTRING
	  ;

		
keyidentifier:
	KEY_IDENTIFIER 
	| keyidentifier '.' KEY_IDENTIFIER
	| keyidentifier '(' NUMBER ')'  { /*driver.Ast->addAttribute(driver.Ast->makeIndexAttribute($4,driver.Ast->addIdentifier()));*/}
	;

	
expression:
	| multiple_values
	| function expression
	| expression operator expression
	| expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression '/' expression
	| expression '|' expression
	| expression '&' expression
	| expression '%' expression
	| expression '=' range
	| expression CMD_SQUARE expression
	| expression CMD_LOGAND expression
	| expression CMD_LOGOR expression
	| expression CMD_LOGXOR expression
	| '(' expression ')'
	| '(' expression error
	| expression ',' operator expression
	;

multiple_values:
    value
    | value multiple_values
    | value ',' multiple_values
	;
value:
		NUMBER  {driver.Ast->addValueToAttribute(driver.Ast->makeNumber($1));}
		| QUOTESTRING  {driver.Ast->addValueToAttribute(driver.Ast->makeString($1));}
		| range
		| identificadores
		;


range:
    '[' NUMBER ',' NUMBER ']'
    | '[' NUMBER ',' NUMBER ')'
    | '(' NUMBER ',' NUMBER ']'
    | '(' NUMBER ',' NUMBER ')'

function:
	

keylist:
      key  {driver.Ast->addValueToAttribute(driver.Ast->makeKeyList());/*talvez mudar aqui para adicionar um keysingle ao invez de uma keylist*/}
      | key ',' keylist {driver.Ast->addValueToAttribute(driver.Ast->makeKeyList());}
      ;
key:
   key_modifiers plain_key  {driver.Ast->iskey();}

key_modifiers:
   key_modifier key_modifiers
   |
   ;

key_modifier:
   '~'   { driver.Ast->addReleaseKeyModifier(); }
   | '/'  { driver.Ast->addHeldDownKeyModifier(); }
   | '$'  { driver.Ast->addDirectionKeyModifier(); }
   | '>'  { driver.Ast->addOnlyKeyModifier(); }
   ;

plain_key:
    plain_key '+' plain_key { driver.Ast->makeKeyCombined($1,$3); }
   | CMD_KEY_DOWN           { driver.Ast->makeKey($1); }
   | CMD_KEY_FORWARD		{ driver.Ast->makeKey($1); }
   | CMD_KEY_DOWN_FORWARD   { driver.Ast->makeKey($1); }
   | CMD_KEY_BACK			{ driver.Ast->makeKey($1); }
   | CMD_KEY_DOWN_BACK		{ driver.Ast->makeKey($1); }
   | CMD_KEY_UP_FORWARD		{ driver.Ast->makeKey($1); }
   | CMD_KEY_UP				{ driver.Ast->makeKey($1); }
   | CMD_KEY_UP_BACK		{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_A			{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_B			{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_C			{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_X			{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_Y			{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_Z			{ driver.Ast->makeKey($1); }
   | CMD_BUTTON_S			{ driver.Ast->makeKey($1); }
	;

keyword:	
	KEYWORD IDENTIFIER operator NUMBER {driver.Ast->makeNumber($4); }
	;
operator:
		'>'
		| '<'
		| '='
		| '!'
		| CMD_GREATERTHANEQ
		| CMD_LESSTHANEQ
		;

end_or_comment:
    EOL 
  | COMMENT;

%%

// Error function throws an exception (std::string) with the location and error message
void CmdCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}


#undef bugon


