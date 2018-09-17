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

#include "../../objects/player.h"
#include "../../util/debug.h"
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
%name-prefix="PlayerCompiler"

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
}

%token			END	     0	"end of file"
%token			EOL		"end of line"
%token <integerVal> INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING		"string"

%destructor { delete $$; } STRING

//Player File tokens
%left ','
%left EQUAL NOTEQUAL GREATER LESS LESSEQUAL GREATEREQUAL
%left MOD LOGNOT LOGAND LOGOR LOGXOR NOT AND OR XOR
%left '+' '-'
%left '*' SQUARE '/' 

%token INFO
%token NAME
%token DISPLAYNAME 
%token VERSIONDATE
%token MUGENVERSION
%token AUTHOR
%token PALDEFAULTS

%token FILES
%token COMAND     
%token CNS
%token STATES
%token COMESTATES
%token SPRITES
%token ANIMATION
%token SOUNDS
%token PALLETE1 
%token PALLETE2
%token PALLETE3
%token PALLETE4
%token PALLETE5
%token PALLETE6
%token PALLETE7
%token PALLETE8
%token PALLETE9
%token PALLETE10
%token PALLETE11
%token PALLETE12

%token ARCADE
%token INTRO
%token ENDING
%token <stringVal> FILENAME


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

lines: /* empty */
     | lines INFOSECTION
     | EOL
     | error EOL
     ;	


INFOSECTION:'[' INFO ']' EOL						{/**/}
	| NAME EQUAL STRING  EOL          {driver.Player->myPlayerDataPlus.strName=*$3;/*Debug::debug(10,__FUNCTION__) <<"NAME= "<<$3<<endl;*/}
    | DISPLAYNAME EQUAL STRING EOL    {driver.Player->myPlayerDataPlus.strDisplayName=*$3;/*Debug::debug(10,__FUNCTION__) <<"Displayname= "<<$3<<endl;*/}
    | VERSIONDATE EQUAL INTEGER '-' INTEGER '-' INTEGER EOL{driver.Player->myPlayerDataPlus.CharVersion.Days=$3; 
                                                 driver.Player->myPlayerDataPlus.CharVersion.Month=$5;
                                                 driver.Player->myPlayerDataPlus.CharVersion.Years=$7;/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    | VERSIONDATE EQUAL INTEGER '/' INTEGER '/' INTEGER EOL{driver.Player->myPlayerDataPlus.CharVersion.Days=$3; 
                                                 driver.Player->myPlayerDataPlus.CharVersion.Month=$5;
                                                 driver.Player->myPlayerDataPlus.CharVersion.Years=$7;/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
     | VERSIONDATE EQUAL INTEGER ',' INTEGER ',' INTEGER EOL{driver.Player->myPlayerDataPlus.CharVersion.Days=$3; 
                                                 driver.Player->myPlayerDataPlus.CharVersion.Month=$5;
                                                 driver.Player->myPlayerDataPlus.CharVersion.Years=$7;/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
   
    | MUGENVERSION EQUAL INTEGER','INTEGER','INTEGER EOL {driver.Player->myPlayerDataPlus.MugenVersion.Days=$3; 
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Month=$5;
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Years=$7;/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    | MUGENVERSION EQUAL INTEGER'/'INTEGER'/'INTEGER EOL {driver.Player->myPlayerDataPlus.MugenVersion.Days=$3; 
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Month=$5;
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Years=$7;/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    | MUGENVERSION EQUAL INTEGER'-'INTEGER'-'INTEGER EOL {driver.Player->myPlayerDataPlus.MugenVersion.Days=$3; 
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Month=$5;
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Years=$7;/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
   
    | AUTHOR EQUAL STRING EOL {/*Debug::debug(10,__FUNCTION__) <<"Author= "<<$3<<endl);*/driver.Player->myPlayerDataPlus.strAuthor=*$3;}
    | AUTHOR EQUAL EOL {}
    | PALDEFAULTS EQUAL expression {}
    | PALDEFAULTS EQUAL EOL {}
    | FILESSECTION 
	| ARCADESECTION
    ;

FILESSECTION: '[' FILES ']'	EOL					{/*Check Files CSection*/}
	| COMAND     EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strCmdFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
	| CNS        EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strCnsFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | STATES     EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strSttFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | COMESTATES EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strComFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | SPRITES    EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strSffFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | ANIMATION  EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strAirFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | SOUNDS     EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strSndFile=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/} 
    | PALLETE1 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[0]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE2 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[1]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE3 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[2]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE4 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[3]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE5 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[4]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE6 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[5]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE7 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[6]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE8 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[7]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE9 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[8]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE10 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[9]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE11 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[10]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    | PALLETE12 EQUAL FILENAME EOL {driver.Player->myPlayerDataPlus.strPalFile[11]=*$3;/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    
    ;

ARCADESECTION: '[' ARCADE ']' EOL					{/*Check Arcade CSection*/}
		| INTRO EQUAL FILENAME {/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
		| INTRO EQUAL EOL {}
		| ENDING EQUAL FILENAME {/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
        | ENDING EQUAL EOL {}
        ;

expression: INTEGER   EOL          {Debug::debug(10,__FUNCTION__) <<"PalNumber= "<<$1<< endl;}
    | INTEGER ',' expression EOL        {Debug::debug(10,__FUNCTION__) <<"PalNumber= "<<$1<< endl;}
   ;

   
        

%%

// Error function throws an exception (std::string) with the location and error message
void PlayerCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}




