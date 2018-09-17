/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 %{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <queue>

#include "../../airmanager.h"
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
%start lines
%name-prefix="AirCompilerOld"

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

%token			END	     0	"end of file"
%token			EOL		"end of line"
%token <integerVal> 	INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING		"string"

%destructor { delete $$; } STRING

//Air File tokens
%token ACBEGIN
%token ACTION
%token LOOPSTART
%token CLSN2DEFAULT
%token CLSN1DEFAULT
%token CLSN2
%token CLSN1
%token HORIZONTALFLIP
%token VERTIKALFLIP
%token HVFLIP
%token ALPHA
%token	COLON


 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "driver.h"
#include "scanner.h"

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


     



AIRFILE: '[' ACBEGIN ACTION INTEGER ']' {driver.Air->AddAction($4); }
        | CLSN1DEFAULT COLON INTEGER  EOL   {driver.Air->CreateClsnBox($3,true,true);}
        | CLSN2DEFAULT COLON INTEGER  EOL   {driver.Air->CreateClsnBox($3,false,true);}    
        | CLSN1 COLON INTEGER EOL           {driver.Air->CreateClsnBox($3,true,false);}
        | CLSN2 COLON INTEGER  EOL          {driver.Air->CreateClsnBox($3,false,false);}
        | CLSN1 '[' INTEGER ']' '='  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER  EOL {driver.Air->AddClsnBox((short)$6,(short)$8,(short)$10,(short)$12,(short)$3);}
        | CLSN2 '[' INTEGER ']' '='  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER  EOL {driver.Air->AddClsnBox((short)$6,(short)$8,(short)$10,(short)$12,(short)$3);}
        |  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER EOL {driver.Air->AddElement($1,$3,$5,$7,$9,0,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' HORIZONTALFLIP EOL {driver.Air->AddElement($1,$3,$5,$7,$9,HFLIPFLAG,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' VERTIKALFLIP EOL {driver.Air->AddElement($1,$3,$5,$7,$9,VFLIPFLAG,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' HVFLIP EOL {driver.Air->AddElement($1,$3,$5,$7,$9,HVFLIPFLAG,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' HORIZONTALFLIP ',' ALPHA EOL {driver.Air->AddElement($1,$3,$5,$7,$9,HFLIPFLAG,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' VERTIKALFLIP  ',' ALPHA EOL {driver.Air->AddElement($1,$3,$5,$7,$9,VFLIPFLAG,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' HVFLIP  ','  ALPHA   EOL    {driver.Air->AddElement($1,$3,$5,$7,$9,HVFLIPFLAG,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ','  ',' ALPHA EOL {driver.Air->AddElement($1,$3,$5,$7,$9,0,0);}
		|  INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER EOL {driver.Air->AddElement($1,$3,$5,$7,$9,0,0);}
		|  LOOPSTART {driver.Air->SetLoop();}
        |  EOL
        |   error
        ;

   
        

%%

// Error function throws an exception (std::string) with the location and error message
void AirCompilerOld::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}




