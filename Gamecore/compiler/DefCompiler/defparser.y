/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 TODO: %i , indexed attribute, maybe flip, correct rule (lhs= ) that sends crap to the program instead of sending null and others */
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

#include "driver.h"

#define bugon(a) if ((a)){ printf("parsing bug at %s:%d\n", __FILE__, __LINE__); }

// stack class that takes care of all the driver.nodes that were allocated
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
%name-prefix="DefCompiler"

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

%right UMINUS

%type <cvalue> variable
%type <cvalue> identificator_list
%type <cvalue> identificator_lhs_list
%type <cvalue> variable_rhs
%type <cvalue> string_value
%type <cvalue> multiple_str_values
%type <cvalue> multiple_num_values
%type <cvalue> multiple_num_comma_values
%type <cvalue> value
%type <cvalue> lhs
%type <cvalue> data
%type <cvalue> data_list
%type <cvalue> flip
%type <cvalue> color_sub
%type <cvalue> maybe_flip
%type <stringVal> pontuation

%token			END	     0	"end of file"
%token			EOL		"end of line"
%token <stringVal> QUOTESTRING 
%token <doubleVal> NUMBER 
%token <stringVal> IDENTIFIER
%token '['
%token ']'



%token DEF_TEXT
       DEF_BLANK
       <stringVal> DEF_LOOPSTART
       <stringVal> DEF_VERTICAL_HORIZONTAL
       <stringVal> DEF_ALPHA_BLEND
       <stringVal>  DEF_ALPHA_BLEND_SHORTHAND
       <stringVal> DEF_COLOR_ADDITION
       <stringVal> DEF_COLOR_SUBTRACT
	   <stringVal> DEF_HORIZONTAL
       <stringVal> DEF_VERTICAL
	  
       
%token <stringVal> DEF_BG
%token <stringVal> DEF_BGCTRL
%token <stringVal> DEF_SELECTBG
%token <stringVal> DEF_SELECTBGCTRL
%token <stringVal> DEF_FILENAME
%token <stringVal> DEF_FILENAME_2
%token <stringVal> DATE
 
%token COMMENT
%destructor { delete $$; } <stringVal>



 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "driver.h"
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


lines : /* empty */ {driver.clear_stack ();}
        ends {driver.clear_stack ();}
		| lines {}
		| section {}
		| error {/*yyclearin;*/ driver.clear_stack (); Debug::debug(30,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
        ;

ends:
	end_or_comment
	| ends  end_or_comment
	;
end_or_comment:
    EOL 
  | COMMENT;


line:
    unquoted_text
    | DEF_BLANK
    | bg
    | bgctrl
    | data_list    {Debug::debug(730,__FUNCTION__) << "BISON: DATA_LIST" <<endl; driver.Ast->addValueToSection((Ast::CValue *)$1);}
    | data         {Debug::debug(730,__FUNCTION__) << "BISON: DATA ONLY" <<endl; driver.Ast->addValueToSection((Ast::CValue *)$1);}
    | selectbg
    | selectbgctrl
    | maybe_flip {Debug::debug(730,__FUNCTION__) << "BISON: ADD VALUE FOR ACTION" <<endl; driver.Ast->addValueToSection((Ast::CValue *)$1);}
    | DEF_LOOPSTART
    ;

assignment: 
    lhs '='    {/*driver.Ast->addValueToAttribute((Ast::CAttribute *) $1, driver.Ast->makeString(new string("Not Defined")));*/ }
    | lhs '=' rhs  {driver.Ast->addValueToAttribute((Ast::CAttribute *) $1, driver.cvalues->pop()); }
	| line 
	;
lhs:
    variable   {Debug::debug(730,__FUNCTION__) << "BISON: Attribute: "<<endl;$$=driver.Ast->makeAttribute((Ast::CIdentifier *)$1);}
    | variable '(' value ')'   {Debug::debug(730,__FUNCTION__) << "BISON: Indexed Attribute : "<<endl;$$=driver.Ast->makeIndexAttribute((Ast::CIdentifier *)$1, (Ast::CValue *)($1));}
	;
rhs:
   expression_list 

expression_list:
    expression maybe_comma
    | expression_list ',' expression {driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop());  } 
	;
	
maybe_comma:
    ','
    |
    ;   

expression:
    variable_rhs '=' value   {Debug::debug(730,__FUNCTION__) << "BISON: variable_rhs '=' value: "<<  endl; driver.nodes=new Ast::CStack(string("nodes_=")); driver.nodes->push((Ast::CValue *)$3);driver.nodes->push((Ast::CValue *)$1);driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));Debug::debug(730,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(Ast::CValue *)$1<< "expression2: "<<(Ast::CValue *)$3<< endl;}
    | expression1  {/* Push já foi feito */Debug::debug(730,__FUNCTION__) << "BISON: expression: // = // expression1: "<<  endl;}

expression1:
    '(' expression ')' { /* Push já foi feito */}
    | '!' value {driver.cvalues->push((Ast::CValue *) $2);}
    | multiple_str_values {driver.cvalues->push((Ast::CValue *) $1);}
    | multiple_num_values {driver.cvalues->push((Ast::CValue *) $1);}
    | multiple_num_comma_values {driver.cvalues->push((Ast::CValue *) $1);}
    | data_list  {Debug::debug(730,__FUNCTION__) << "BISON: rhs = DATA_LIST :"<<endl; driver.cvalues->push((Ast::CValue *) $1);}
	| string_value {Debug::debug(730,__FUNCTION__) << "BISON: rhs = STRING_VALUE :"<<endl; driver.cvalues->push((Ast::CValue *) $1);}
	;
	


multiple_str_values:
	NUMBER	IDENTIFIER { $$=driver.Ast->makeString(driver.Ast->addStrings( $1, $2));	}
	|string_value string_value { $$=driver.Ast->makeStringSpace((Ast::CString*) $1,(Ast::CString*) $2 ); }
    | multiple_str_values string_value {  Debug::debug(730,__FUNCTION__) << "BISON: STRING VALUELIST : "<<endl; $$=driver.Ast->makeStringSpace((Ast::CString*) $1,(Ast::CString*) $2 );} 
    ;
    
multiple_num_comma_values:
    value ',' value {$$=driver.Ast->makeValueList((Ast::CValue *) $1,(Ast::CValue *) $3);  } 
    | multiple_num_comma_values ',' value {  Debug::debug(730,__FUNCTION__) << "BISON: MULTIPLE_NUM_COMMA_VALUES : "<<endl; $$=driver.Ast->addToValueList((Ast::CValueList *)$1,(Ast::CValue *)$3 );} 
    ;
    
    
multiple_num_values:
    value { $$=$1; }
    | value multiple_num_values {  Debug::debug(730,__FUNCTION__) << "BISON: MULTIPLE_NUM_VALUES : "<<endl; $$=driver.Ast->makeValueList((Ast::CValue *)$1,(Ast::CValue *)$2 );} 
    ;
value:
    NUMBER {Debug::debug(730,__FUNCTION__) << "BISON: VALUE : "<<endl;$$=driver.Ast->makeNumber($1);  }
    ;

string_value:
	 data  { $$=$1;}
    | variable_rhs '(' expression_list ')' 
    | variable_rhs { $$=$1;}
     ;
     
  

variable:
      identificator_lhs_list {$$=driver.Ast->makeIdentifierSimple((string *)$1);}
     | DEF_FILENAME { $$=driver.Ast->makeIdentifierSimple($1);}
     | DEF_FILENAME_2 { $$=driver.Ast->makeIdentifierSimple($1);}
     | variable '.' IDENTIFIER {$$=driver.Ast->addToIdentifier((Ast::CIdentifier*) $$,$3); }
     | variable '.' DEF_FILENAME {$$=driver.Ast->addToIdentifier((Ast::CIdentifier*) $$,$3); }
     | variable '.' DEF_FILENAME_2 {$$=driver.Ast->addToIdentifier((Ast::CIdentifier*) $$,$3); }
     | variable '.' NUMBER {$$=driver.Ast->addToIdentifier((Ast::CIdentifier*) $$,$3); }
     ;
     
identificator_lhs_list:

IDENTIFIER { $$=$1;}
| DEF_COLOR_ADDITION { $$=$1;}
| DEF_COLOR_SUBTRACT { $$=$1;}
| DEF_HORIZONTAL { $$=$1;}
| DEF_VERTICAL { $$=$1;}
| identificator_lhs_list NUMBER  { $$=driver.Ast->addStrings((string *)$1,$2);}
| identificator_lhs_list IDENTIFIER  {$$=driver.Ast->addStrings((string *)$1,$2);}
;
variable_rhs:
      data  '.' IDENTIFIER  { $$=driver.Ast->addToStringDot((Ast::CString*)$$,$3); }
     | data  '.' NUMBER		{ $$=driver.Ast->addToStringDot((Ast::CString*) $$,$3); }
     | variable_rhs '.' IDENTIFIER { $$=driver.Ast->addToStringDot((Ast::CString*)$$,$3); }
     | variable_rhs '.' NUMBER { $$=driver.Ast->addToStringDot((Ast::CString*)$$,$3); }
     ;

identificator_list:
		 DEF_SELECTBG IDENTIFIER  {  $$=driver.Ast->makeStringSpace($1,$2);}
		| DEF_SELECTBGCTRL IDENTIFIER  {  $$=driver.Ast->makeStringSpace($1,$2);}
		| IDENTIFIER IDENTIFIER {$$=driver.Ast->makeStringSpace($1,$2);}
		| identificator_list IDENTIFIER  { $$=driver.Ast->addToStringSpace((Ast::CString *)$1, $2);}
		| identificator_list NUMBER  { $$=driver.Ast->addToStringSpace((Ast::CString *)$1, $2);}
		;

data_list:   
	  data ',' data  {$$=driver.Ast->makeValueList((Ast::CValue *)$1,(Ast::CValue *)$3);}
     | data_list ',' data   {$$=driver.Ast->addToValueList((Ast::CValueList*)$1,(Ast::CValue *)$3);}
    ;

data:
     DEF_FILENAME { $$=driver.Ast->makeString($1); }
    | DEF_FILENAME_2 { $$=driver.Ast->makeString($1); }
    | QUOTESTRING {$$ = driver.Ast->makeString($1);  }
    | IDENTIFIER pontuation {$$=driver.Ast->makeString(driver.Ast->addStrings($1,$2));}
    | DATE {$$=driver.Ast->makeString($1); Debug::debug(730,__FUNCTION__) << "BISON: DATE : "<< $1->c_str()<<endl;  }
    | IDENTIFIER			{ $$=driver.Ast->makeString($1);}
   ;
pontuation:
        '!' {$$=new string("!");}
        | '?' {$$=new string("?");}
		| pontuation '!'  { $$=driver.Ast->addStrings((string *)$1,new string("!")); }
        | pontuation '?'  { $$=driver.Ast->addStrings((string *)$1,new string("?")); }
		;
unquoted_text:
    DEF_TEXT;
    
section:
    '[' IDENTIFIER ']' {driver.Ast->makeSection($2); }
    | '[' IDENTIFIER NUMBER ']' {driver.Ast->makeSection($2); driver.Ast->addValueToSection(driver.Ast->makeNumber($3));}
    | '[' identificator_list ',' IDENTIFIER ']' {driver.Ast->makeSection((Ast::CString *)$2); driver.Ast->addValueToSection(driver.Ast->makeString($4));}
    | '[' identificator_list ',' NUMBER ']' {driver.Ast->makeSection((Ast::CString *)$2); driver.Ast->addValueToSection(driver.Ast->makeNumber($4));}
    | '[' NUMBER ']' {driver.Ast->makeSection($2); }
    | '[' NUMBER NUMBER ']' { driver.Ast->makeSection($2); driver.Ast->addValueToSection(driver.Ast->makeNumber($3)); }
    | '[' NUMBER NUMBER NUMBER ']' {driver.Ast->makeSection($2); }
    | '[' identificator_list ']' {driver.Ast->makeSection((Ast::CString *)$2);  }
    
    | '[' DEF_SELECTBG NUMBER ']' {  driver.Ast->makeSection($2); driver.Ast->addValueToSection(driver.Ast->makeNumber($3));}
	| '[' DEF_SELECTBG NUMBER '.' IDENTIFIER ']' {  driver.Ast->makeSection($2); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot($3,$5));}
	| '[' DEF_SELECTBG NUMBER '.' DEF_COLOR_ADDITION ']' {  driver.Ast->makeSection($2); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot($3,$5));}
	| '[' DEF_SELECTBG NUMBER '.' DEF_COLOR_SUBTRACT ']' {  driver.Ast->makeSection($2); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot($3,$5));}
	| '[' DEF_SELECTBGCTRL NUMBER ']' {  driver.Ast->makeSection($2); ;driver.Ast->addValueToSection(driver.Ast->makeNumber($3));}
	| '[' DEF_SELECTBGCTRL NUMBER '.' IDENTIFIER ']' {  driver.Ast->makeSection($2); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot($3,$5));}
	| assignment  {Debug::debug(730,__FUNCTION__) << "BISON: ASSIGNMENT" <<endl;}
    | 
    ;
maybe_flip:
      multiple_num_comma_values {$$ = $1;}
   |  multiple_num_comma_values ',' flip {$$=driver.Ast->addToValueList((Ast::CValueList*) $1,(Ast::CValue *)$3);}
   |  multiple_num_comma_values ',' flip ',' color_sub {$$=driver.Ast->addToValueList((Ast::CValueList*) driver.Ast->addToValueList((Ast::CValueList*) $1,(Ast::CValue *)$3),(Ast::CValue *)$5);}
   |  multiple_num_comma_values ',' ','  color_sub  { $$=driver.Ast->addToValueList((Ast::CValueList*) driver.Ast->addToValueList((Ast::CValueList*) $1,driver.Ast->makeString(new string(""))),(Ast::CValue *)$4);}
   ;
	
flip:
    DEF_HORIZONTAL {$$=driver.Ast->makeKeyword($1);}
	| IDENTIFIER {$$=driver.Ast->makeKeyword($1);}
    | DEF_VERTICAL {$$=driver.Ast->makeKeyword($1);}
    | DEF_VERTICAL_HORIZONTAL {$$=driver.Ast->makeKeyword($1);}
    ;
    
color_sub:
    DEF_COLOR_ADDITION {$$=driver.Ast->makeKeyword($1);}
	| IDENTIFIER {$$=driver.Ast->makeKeyword($1);}
	| DEF_COLOR_SUBTRACT  {$$=driver.Ast->makeKeyword($1);}
    | DEF_ALPHA_BLEND {$$=driver.Ast->makeKeyword($1);}
    | DEF_ALPHA_BLEND_SHORTHAND {$$=driver.Ast->makeKeyword($1);}
    ;

/* Implement properly later */
bg:
    DEF_BG {
	Debug::debug(1,__FUNCTION__) << "Got Bg: " << ($1)->c_str() << std::endl;
	driver.Ast->makeSection($1);
    };
    
selectbg:
    DEF_SELECTBG {
	Debug::debug(1,__FUNCTION__) << "Got Select Bg: " << $1 << std::endl;
	driver.Ast->makeSection($1);
    };

bgctrl:
     DEF_BGCTRL  {
	Debug::debug(1,__FUNCTION__) << "Got BgCtrl: " << $1 << std::endl;
	driver.Ast->makeSection($1);
    };
    
selectbgctrl:
    DEF_SELECTBGCTRL {
	Debug::debug(1,__FUNCTION__) << "Got Select BgCtrl: " << $1 << std::endl;
	driver.Ast->makeSection($1);
    };
%%
// Error function throws an exception (std::string) with the location and error message
void DefCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}



#undef bugon


