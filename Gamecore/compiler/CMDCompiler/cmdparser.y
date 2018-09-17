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

#include "cmd_driver.h"

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
%code requires {
typedef struct  triggerRedir
	{
	triggerRedir():identifier(""),id(0){};
	std::string identifier;
	int id;
	}triggerRedirtype;
}
%union {
    int  			integerVal;
    double 			doubleVal;
    std::string*	stringVal;
    void*			cvalue;
	triggerRedirtype * redirValue;
    }


%type <cvalue> functions
%type <cvalue> hitdef
%type <cvalue> expression
%type <cvalue> compare_expression
%type <cvalue> simple_value
%type <cvalue> super_simple_value
%type <cvalue> identificator_list
%type <cvalue> identificator_dot_list
%type <cvalue> identificator_comma_list
%type <cvalue> number_comma_list
%type <cvalue> range
%type <cvalue> keywords
%type <cvalue> keyword_comma_list
%type <cvalue> number_list
%type <cvalue> math_expression
%type <cvalue> expression_list
%type <cvalue> expression_comma_list
%type <cvalue> function_if_else
%type <stringVal> common_names
%type <stringVal> compare_operators
%type <stringVal> math_operators
%type <stringVal> func_identifiers
%type <stringVal> func_comparator
%type <cvalue> negative_number
%type <cvalue> key_anim_expression
%left ','
%left <doubleVal> NUMBER
%left LOGICAL_OPERATORS
%left CMD_LOGXOR
%left CMD_LOGAND 
%left CMD_LOGOR
%left '|'
%left CMD_XOR
%left '&' 
%left CMD_ASSIGN
%left '=' CMD_NOTEQ 
%left COMP_OPERATORS '>' '<' CMD_LESSTHANEQ CMD_GREATERTHANEQ
%left MATH_OPERATORS
%left '+' '-'
%left '*' '/' '%'
%left CMD_SQUARE
%left '~' '!' 
%left UMINUS UPLUS
%left EXP FLOOR LN
%left <stringVal> KEY_IDENTIFIER KEYWORD
%token <stringVal> FUNC_IDENTIFIER
%right  EXPRESSIONLIST
%left  PLAYERIDEXIST PROJCANCELTIME SELFANIMEXIST
%left TAN VAR PROJCONTACTTIME PROJGUARDEDTIME
%left <stringVal> FUNC_LOG FUNC_CONST FUNC_SYSVAR FUNC_VAR FUNC_FVAR
%left <doubleVal> FUNC_PROJCONTACT FUNC_PROJHIT FUNC_PROJGUARDED
%right FUNC_IFELSE  KANIM
%right KEY_TRIGGER
%right FUNC_IDENTIFIER

%token			END	     0	"end of file"
%token			EOL		"end of line"


%token ID
%token <stringVal> QUOTESTRING

%token NEGONE


%token DATA
%token ATTACK
%token DEFENCE
%token FALLDEFUP
%token LIEDOWTIME
%token AIRJUGGLE
%token SPARKNO
%token GUARDSPARKNO
%token KOECHO
%token VOLUME
%token INTEGERINDEX
%token FLOATINDEX

%token SIZE
%token XSCALE
%token YSCALE
%token GROUNDBACK
%token GROUNDFRONT
%token AIRBACK
%token AIRFRONT
%token HEIGHT
%token ATTACKDIST
%token PROJATTDIST
%token PROJDOSCALE
%token HEADPOSX
%token HEADPOSY
%token MIDPOSX
%token MIDPOSY
%token SHADOWOFFSET
%token DRAWOFFSETX
%token DRAWOFFSETY

%token VELOCITY
%token WALKFWD
%token WALKBACK

%token RUNFWDX
%token RUNFWDY

%token RUNBACKX
%token RUNBACKY



%token JUMPNEU
%token JUMPBACK
%token JUMPFWD
%token RUNJUMPBACK
%token RUNJUMPFWD
%token AIRJUMPNEU
%token AIRJUMPBACK
%token AIRJUMPFWD

%token MOVEMENT
%token AIRJUMPNUM
%token AIRJUMPHEIGHT
%token YACCEL
%token STANDFRICTION
%token CROUCHFRICTION


%token <stringVal> KEY_TRIGGER
%token <stringVal> KEY_TRIGGERALL
%token <stringVal> IDENTIFIER

%token <stringVal> CMD_STATEDEF
%token <stringVal> KEY_PHYSICS
%token <stringVal> CMD_STATE


%token ANIMELEM


%token FVAR

%token HITCOUNT
/* keywords */
%token <stringVal> HITDEFATTR
%token ISHELPER


%token MOVECONTACT


%token PROJGUARDED

%token PROJHITTIME


%token STATENO

%token TNULL
%token AFTERIMAGE
%token AFTERIMAGETIME
%token ALLPALFX
%token ANGLEADD
%token ANGLEDRAW
%token ANGLEMUL
%token ANGLESET
%token APPENDTOCLIPBOARD
%token ASSERTSPECIAL
%token ATTACKMULSET
%token BGPALFX
%token BINDTOPARENT
%token BINDTOROOT
%token BINDTOTARGET
%token CHANGEANIME
%token CHANGEANIME2
%token CHANGESTATE
%token CLEARCLIPBOARD
%token CTRLSET
%token DEFENCEMULSET
%token DESTROYSELF
%token DISPLAYTOCLIPBOARD
%token ENVSHAKE
%token EXPLOD
%token EXPLODBINDTIME
%token FALLENVSHAKE
%token FORCEFEDDBACK
%token GAMEMAKEANIM
%token GRAVITY
%token HELPER
%token HITADD
%token HITBY
%token <stringVal> KEY_HITDEF
%token HITFALLDAMAGE
%token HITFALLSET
%token HITFALLVEL
%token HITOVERRIDE
%token HITVELSET
%token LIFEADD
%token LIFESET
%token MAKEDUST
%token MODIFYEXPLOD
%token MOVEHITRESET
%token NOTHITBY
%token NUL
%token OFFSET
%token PALFX
%token PARENTVARADD
%token PARENTVARSET
%token PAUSE
%token PLAYERPUSH
%token PLAYSND
%token POSADD
%token POSFREEZ
%token POSSET
%token POWERSET
%token PROJECTILE
%token REMOVEEXPLOD
%token REVERSALDEF
%token SCREENBOUND
%token SELFSTATE
%token SNDPAN
%token STATETYPESET
%token STOPSND
%token SUPERPAUSE
%token TARGETBIND
%token TARGETDROP
%token TARGETFACING
%token TARGETLIFEADD
%token TARGETPOWERADD
%token TARGETSTATE
%token TARGETVELADD
%token TARGETVELSET
%token TURN
%token VARADD
%token VARRANDOM
%token VARRANGESET
%token VARSET
%token VELADD
%token VELMUL
%token WIDTH

%token LENGTH
%token PALCOLOR
%token PALINVERTALL
%token PALBRIGHT
%token PALCONTRAST
%token PALPOSTBRIGHT
%token PALADD
%token PALMUL
%token TIMEGAP
%token FRAMEGAP
%token TRANS

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

//Def File Tokens
%token INFO
%token DISPLAYNAME
%token VERSIONSDATA
%token MUGENVERSION
%token AUTHOR
%token FILES
%token CMD
%token CNS
%token ST
%token STCOMMON
%token SPRITE
%token SOUND
%token PAL
%token PALDEF
%token ARCADE
%token INTROSTORYBOARD
%token ENDINGSTORYBOARD



%token JUMPNEUY
%token AIRJUMPNEUY



%token  <doubleVal> KEY_FX
%token  <doubleVal> KEY_SX

%token  <stringVal> CMD_KEY_DOWN
%token  <stringVal> CMD_KEY_FORWARD
%token  <stringVal> CMD_KEY_DOWN_FORWARD
%token  <stringVal> CMD_KEY_BACK
%token  <stringVal> CMD_KEY_DOWN_BACK
%token  <stringVal> CMD_KEY_UP_FORWARD
%token  <stringVal> CMD_KEY_UP
%token  <stringVal> CMD_KEY_UP_BACK
%token  <stringVal> CMD_BUTTON_A
        <stringVal> CMD_BUTTON_B
        <stringVal> CMD_BUTTON_C
        <stringVal> CMD_BUTTON_X
        <stringVal> CMD_BUTTON_Y
        <stringVal> CMD_BUTTON_Z
	    <stringVal> CMD_BUTTON_S
%token <stringVal> KEY_STATETYPE

%token <stringVal> KEY_TYPE
%token <stringVal> KEY_ANIM
%token <stringVal> TRIGGER_REDIRECTION_IDENTIFIER
%token <stringVal> CONST_PARAM
%token <stringVal> COMMENT
%destructor { delete $$; } <stringVal>
 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "cmd_driver.h"
#include "cmdScanner.h"
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
        COMMENT {driver.clear_stack ();}
		| EOL   {driver.clear_stack ();}
		| lines STATEDEFSECTION end_or_comment { driver.Ast->setValidSection();}
        | error {/*yyclearin;*/ driver.clear_stack (); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
        ;

end_or_comment:
    EOL
  | COMMENT;


STATEDEFSECTION: '[' CMD_STATEDEF NUMBER ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));}
		| '[' CMD_STATEDEF NUMBER ',' expression ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.cvalues->pop()); };
	    | '[' CMD_STATEDEF NUMBER ',' math_expression ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection((SGF::Ast::CValue *)driver.cvalues->pop());}
	    | '[' CMD_STATEDEF NUMBER ',' identificator_list ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection((SGF::Ast::CValue *)$5);}
		| '[' CMD_STATEDEF NUMBER ',' KEY_IDENTIFIER ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.Ast->makeString($5));}
		| '[' CMD_STATEDEF NUMBER ',' error ']'                {driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));}
		| '[' CMD_STATEDEF negative_number ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);}
		| '[' CMD_STATEDEF negative_number ',' expression ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.cvalues->pop()); };
	    | '[' CMD_STATEDEF negative_number ',' math_expression ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection((SGF::Ast::CValue *)driver.cvalues->pop());}
	    | '[' CMD_STATEDEF negative_number ',' identificator_list ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection((SGF::Ast::CValue *)$5);}
		| '[' CMD_STATEDEF negative_number ',' KEY_IDENTIFIER ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.Ast->makeString($5));}
		| '[' CMD_STATEDEF negative_number ',' error ']'                {driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);}
		| 	STATESECTION											{ driver.Ast->setValidSection(); }
	;

STATESECTION: '[' CMD_STATE NUMBER ',' expression ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.cvalues->pop()); };
	    | '[' CMD_STATE NUMBER ',' identificator_list ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection((SGF::Ast::CValue *)$5);}
	    | '[' CMD_STATE NUMBER ',' expression_list ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection((SGF::Ast::CValue *)$5);}
		| '[' CMD_STATE NUMBER  NUMBER ']'					{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.Ast->makeString($4));}
		| '[' CMD_STATE NUMBER  ']'							{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | '[' CMD_STATE NUMBER ',' ']'						{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | '[' CMD_STATE NUMBER ',' error ']'                {driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeNumber($3));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | '[' CMD_STATE negative_number ',' expression ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.cvalues->pop()); };
	    | '[' CMD_STATE negative_number ',' identificator_list ']'	{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection((SGF::Ast::CValue *)$5);}
	    | '[' CMD_STATE negative_number ',' expression_list ']'		{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection((SGF::Ast::CValue *)$5);}
		| '[' CMD_STATE negative_number  NUMBER ']'					{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.Ast->makeString($4));}
		| '[' CMD_STATE negative_number  ']'							{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | '[' CMD_STATE negative_number ',' ']'						{driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | '[' CMD_STATE negative_number ',' error ']'                {driver.Ast->makeSection($2);driver.Ast->addValueToSection((SGF::Ast::CValue *)$3);driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | '[' CMD_STATE IDENTIFIER  ']'							{driver.Ast->makeSection($2);driver.Ast->addValueToSection(driver.Ast->makeIdentifierSimple($3));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
        | COMMANDSECTION
        | TRIGGERSECTION
		| ANIMSECTION   {  /* anim as a command identifier for superpouse and explod state controllers*/ }
	    ;

		
		
identificator_list:
        expression					{ $$=(SGF::Ast::CValue *)driver.cvalues->pop();}
		| TRIGGER_REDIRECTION_IDENTIFIER  { $$=driver.Ast->makeIdentifierSimple($1);}
		| math_operators 			{ $$=driver.Ast->makeIdentifierSimple($1);}
		| CMD_STATE    				{ $$=driver.Ast->makeIdentifierSimple($1);}
		| func_identifiers 			{ $$=driver.Ast->makeIdentifierSimple($1);}
		| compare_operators 		{ $$=driver.Ast->makeIdentifierSimple($1);}
		| IDENTIFIER IDENTIFIER 	{ $$=driver.Ast->makeIdentifier($1,$2);}
		| IDENTIFIER CMD_STATE 		{  $$=driver.Ast->makeIdentifier($1,$2);}
		
		| NUMBER IDENTIFIER 		{  $$=driver.Ast->makeIdentifier($1,$2);}
		| NUMBER CMD_STATE 			{  $$=driver.Ast->makeIdentifier($1,$2);}
		
		| KEY_IDENTIFIER IDENTIFIER {  $$=driver.Ast->makeIdentifier($1,$2);}
		| KEY_IDENTIFIER CMD_STATE 	{  $$=driver.Ast->makeIdentifier($1,$2);}
		| KEY_IDENTIFIER math_expression { std::string * temp=new string(((SGF::Ast::CValue *)driver.cvalues->pop())->toString()); $$=driver.Ast->makeIdentifier($1,temp);}
		
		| identificator_list CMD_STATE  { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $2);}
		| identificator_list IDENTIFIER  { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $2);}  //reduce reduce
		| identificator_list func_identifiers { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $2);}
		| identificator_list NUMBER 			{ driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $2);}
		| identificator_list KEY_IDENTIFIER     { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $2);}
		| identificator_list TRIGGER_REDIRECTION_IDENTIFIER { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $2);}
		;

number_list:
     NUMBER NUMBER {  $$=driver.Ast->makeValueList(driver.Ast->makeNumber($1),driver.Ast->makeNumber($2));}
	| number_list NUMBER  { $$=driver.Ast->addToValueList((SGF::Ast::CValueList *)$1, driver.Ast->makeNumber($2));}
	;


number_comma_list:
     NUMBER ',' NUMBER %prec KANIM {  $$=driver.Ast->makeValueList(driver.Ast->makeNumber($1),driver.Ast->makeNumber($3));}
	| NUMBER ',' IDENTIFIER %prec KANIM {  $$=driver.Ast->makeValueList(driver.Ast->makeNumber($1),driver.Ast->makeString($3));}
	| number_comma_list ',' NUMBER  %prec KANIM { $$=driver.Ast->addToValueList((SGF::Ast::CValueList *)$1, driver.Ast->makeNumber($3));}
	| number_comma_list ',' IDENTIFIER  %prec KANIM { $$=driver.Ast->addToValueList((SGF::Ast::CValueList *)$1, driver.Ast->makeString($3));}
	;

identificator_comma_list:
        CMD_BUTTON_A ',' IDENTIFIER  {$$=driver.Ast->makeValueList(driver.Ast->makeString($1),driver.Ast->makeString($3));}
		| IDENTIFIER ',' IDENTIFIER  {$$=driver.Ast->makeValueList(driver.Ast->makeString($1),driver.Ast->makeString($3));}
		| IDENTIFIER ',' NUMBER   {$$=driver.Ast->makeValueList(driver.Ast->makeString($1),driver.Ast->makeNumber($3));}
		| CMD_BUTTON_A ',' identificator_comma_list  {$$=driver.Ast->addToValueListFront((SGF::Ast::CValueList*)$3,driver.Ast->makeString($1));}
		| IDENTIFIER ',' identificator_comma_list  {$$=driver.Ast->addToValueListFront((SGF::Ast::CValueList*)$3,driver.Ast->makeString($1));}
		| NUMBER ',' identificator_comma_list    {$$=driver.Ast->addToValueListFront((SGF::Ast::CValueList*)$3,driver.Ast->makeNumber($1));}
		;
	
identificator_dot_list:
		 IDENTIFIER '.' IDENTIFIER {  $$=driver.Ast->makeIdentifier($1,$3);}
		| IDENTIFIER '.' KEY_IDENTIFIER {  $$=driver.Ast->makeIdentifier($1,$3);}
		| KEY_IDENTIFIER '.' KEY_IDENTIFIER {  $$=driver.Ast->makeIdentifier($1,$3);}
		| KEY_IDENTIFIER '.' IDENTIFIER {  $$=driver.Ast->makeIdentifier($1,$3);}
		| identificator_dot_list '.' IDENTIFIER  { $$=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $3);}
		| identificator_dot_list '.' KEY_IDENTIFIER  { $$=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)$1, $3);}
		;

TRIGGERSECTION: KEY_TRIGGER        '=' expression {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGER = Expression // BEGIN //"<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.cvalues->pop());}
              | KEY_TRIGGERALL     '=' expression {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGERALL = Expression // BEGIN //"<<endl; driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.cvalues->pop());}
              | KEY_TRIGGER        '=' expression ',' expression {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGER = Expression // BEGIN //"<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop()));}
              | KEY_TRIGGERALL     '=' expression ',' expression {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGERALL = Expression // BEGIN //"<<endl; driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop()));}
              ;

ANIMSECTION: KEY_ANIM '=' super_simple_value expression			{
												
												/*	if (*$3 == "F" || *$3 == "f") */
													SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyAnim = super_simple_value expression "<<endl;
													driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeFightResource((SGF::Ast::CValue *)driver.cvalues->pop()));
												
												
											}
			| KEY_ANIM '=' expression		{
											SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = expressioipconfign: "<<endl;
												driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeOwnResource((SGF::Ast::CValue *)driver.cvalues->pop()));
											}
			;


COMMANDSECTION:
	 command_identifier
    | ident_section
    ;

command_identifier:
	| KEY_IDENTIFIER '=' KEY_ANIM  {
													SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = KEY_ANIM: "<<endl;
													driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeIdentifierSimple($3));
												
									}
	| KEY_IDENTIFIER'('NUMBER')' '=' expression {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeNumber($3),driver.cvalues->pop());}
	| KEY_IDENTIFIER  				{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EMPTY: "<<endl;
									SGF::Ast::CValue * number;
									if (*$1=="ignorehitpause") { 
									    number=driver.Ast->makeNumber(1);
										}
									driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),number); 
									}
	| KEY_IDENTIFIER '=' 			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EMPTY: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1)); }
	| KEY_IDENTIFIER '=' expression			{
													SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyIdentifier = EXPRESSION: "<<endl;
													driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)driver.cvalues->pop());
												
											}
	| KEY_IDENTIFIER '=' expression	'-'		{
											SGF::Ast::CValue *tempValue= (SGF::Ast::CValue *)driver.cvalues->pop();
											if (tempValue->getType()=="identifier"){
											driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*)tempValue,new string("-"));
											}
											SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyIdentifier = EXPRESSION - "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),tempValue);
											}
	| KEY_IDENTIFIER '=' expression	'+'		{
											SGF::Ast::CValue *tempValue= (SGF::Ast::CValue *)driver.cvalues->pop();
											if (tempValue->getType()=="identifier"){
											driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*)tempValue,new string("+"));
											}
											SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EXPRESSION +: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),tempValue);
											}
	| KEY_IDENTIFIER '=' expression_comma_list	{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EXPRESSIONLIST: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)$3);}
	| KEY_IDENTIFIER '=' TRIGGER_REDIRECTION_IDENTIFIER     {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyType: "<<endl;driver.nodes=new SGF::Ast::CStack(string("key_type"));driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeKeyword($3));}

	| KEY_IDENTIFIER '.' KEY_IDENTIFIER  '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3));driver.Ast->addValueToAttribute(driver.cvalues->pop());SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Bison::DOT LIST IDENTIFIER "<<  endl;}
	| KEY_IDENTIFIER '.' KEY_IDENTIFIER  '=' expression_comma_list {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3),(SGF::Ast::CValue*)$5);}

	| KEY_IDENTIFIER '.' identificator_dot_list '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)$3,$1),(SGF::Ast::CValue *)driver.cvalues->pop());}
	| KEY_IDENTIFIER '.' identificator_dot_list '=' expression_comma_list {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)$3,$1), (SGF::Ast::CValue*)$5);}


	| KEY_IDENTIFIER '.' IDENTIFIER '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3),driver.cvalues->pop());}
	| KEY_IDENTIFIER '.' IDENTIFIER '=' expression_comma_list {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3),(SGF::Ast::CValue *)$5);}


	
	| IDENTIFIER'('NUMBER')' '=' expression {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeNumber($3),driver.cvalues->pop());}

	| IDENTIFIER '=' expression			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Identifier = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)driver.cvalues->pop());}
	| IDENTIFIER '=' expression_comma_list	{driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)$3);SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Identifier = EXPRESSIONLIST: "<<endl;}

	| IDENTIFIER '.' IDENTIFIER  '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)driver.cvalues->pop());}
	| IDENTIFIER '.' IDENTIFIER  '=' expression_comma_list  {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)$5);}

	| IDENTIFIER '.' KEY_IDENTIFIER  '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)driver.cvalues->pop());}
	| IDENTIFIER '.' KEY_IDENTIFIER  '=' expression_comma_list  {driver.Ast->makeAttribute(driver.Ast->makeIdentifier($1,$3));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)$5);}


	| IDENTIFIER '.' identificator_dot_list '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)$3,$1));driver.Ast->addValueToAttribute(driver.cvalues->pop());}
	| IDENTIFIER '.' identificator_dot_list '=' expression_comma_list {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)$3,$1));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)$5);}


	| common_names '=' expression {driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)driver.cvalues->pop());}
	| common_names '=' expression_comma_list			{driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)$3);}
	
	| FUNC_SYSVAR '(' NUMBER ')' '=' expression  {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeNumber($3),(SGF::Ast::CValue *) driver.cvalues->pop());}
	| FUNC_VAR '(' NUMBER ')' '=' expression  {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeNumber($3),(SGF::Ast::CValue *) driver.cvalues->pop());}
	| FUNC_FVAR '(' NUMBER ')' '=' expression  {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeNumber($3),(SGF::Ast::CValue *) driver.cvalues->pop());}

	| KEYWORD '=' expression			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Keyword = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)driver.cvalues->pop());}
	| KEYWORD '=' expression_comma_list			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Keyword = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)$3);}

	| CONST_PARAM '=' expression			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=>Const_param = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)driver.cvalues->pop());}
	| CONST_PARAM '=' expression_comma_list			{SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=>Const_param = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),(SGF::Ast::CValue *)$3);}
	;


expression_list:
	expression expression  { $$=driver.Ast->makeStringSpace((SGF::Ast::CValue *)driver.cvalues->pop(),(SGF::Ast::CValue *)driver.cvalues->pop());}
	| expression_list expression {$$=$$=driver.Ast->makeStringSpace(((SGF::Ast::CValue *)$1),(SGF::Ast::CValue *)driver.cvalues->pop());}
	;

expression_comma_list:
	expression ',' expression   { $$=driver.Ast->makeValueList((SGF::Ast::CValue *)driver.cvalues->pop(),(SGF::Ast::CValue *)driver.cvalues->pop());SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Creating EXPRESSIONLIST : "<<endl;}
	| expression_comma_list ',' expression   { $$=driver.Ast->addToValueList((SGF::Ast::CValueList *) $1 ,(SGF::Ast::CValue *)driver.cvalues->pop() );SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:Adding To EXPRESSIONLIST: "<<endl;}
	;
common_names:
      KEY_PHYSICS    {$$=$1;}
	| KEY_STATETYPE   {$$=$1;}

 ident_section:
	'[' IDENTIFIER ']' {driver.Ast->makeSection($2);}
	| '[' KEY_IDENTIFIER ']' {driver.Ast->setInvalidSection();}
	;

expression:
    hitdef   {driver.cvalues->push((SGF::Ast::CValue *)$1);SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Add Hitdef made in another rule to Stack // "<<endl;}
	| functions				{driver.cvalues->push((SGF::Ast::CValue *)$1);SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Add Function Made in another rule to Stack // "<<endl;}
	| function_if_else
	| key_anim_expression		{ driver.cvalues->push((SGF::Ast::CValue *)$1);}
	| math_expression		%prec MATH_OPERATORS		{/*Já faz push da expressão*/ }
	| compare_expression	%prec COMP_OPERATORS		{/*Já faz push da expressão*/ }
	| logical_expression	%prec LOGICAL_OPERATORS		{/*Já faz push da expressão*/ }
	| identificator_comma_list		{driver.cvalues->push((SGF::Ast::CValue *)$1);SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: identificator comma list // "<<endl;}
	| '(' expression ')' 			{$$=$2;/*Já faz push da expressão*/SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: (expression) // TODO: oque fazer aqui"<<endl;}
    | '(' expression error			{$$=$2;/*yyclearin;*/ /*Já faz push da expressão*/SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: :error // erro: "<<"TODO: oque fazer aqui"<<  endl;}
	| '-' expression %prec UMINUS	 {driver.cvalues->push(driver.Ast->makeUnaryExpression(driver.cvalues->pop(),string("MINUS")));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:  MINUS expression"<< endl;}
	| number_list 					{driver.cvalues->push((SGF::Ast::CValue *)$1);SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Expression List // "<<endl;}
	| simple_value		%prec UPLUS			{/*Já faz push da expressão*/}
    | super_simple_value %prec UPLUS			{driver.cvalues->push((SGF::Ast::CValue *)$1);}
	| ',' expression     	{
							SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: , expression / Verificar se é uma valuelist e adicionar valor em branco"<< endl;
							SGF::Ast::CValue * tempValue= (SGF::Ast::CValue *)$2;
							if(tempValue->getType()=="list of values") {
							SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Adding empty value to begginning of list" << endl;
							SGF::Ast::CValue *valueString = driver.Ast->makeString(new string("."));
							((SGF::Ast::CValueList*) tempValue)->addValuetoFront(valueString);
							}
							}
	| TRIGGER_REDIRECTION_IDENTIFIER '(' expression	 ')' ',' expression %prec UMINUS		{ 
																							SGF::Ast::CValue *expression2 = driver.cvalues->pop();
																							SGF::Ast::CValue *expression1 = driver.cvalues->pop();
																							driver.cvalues->push(driver.Ast->makeHelper($1,expression1,expression2));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:HELPER - , TRIGGER_REDIRECTION_IDENTIFIER"<< endl;}
    | TRIGGER_REDIRECTION_IDENTIFIER ',' expression	%prec UMINUS		{driver.cvalues->push(driver.Ast->makeHelper($1,driver.cvalues->pop()));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:HELPER - , TRIGGER_REDIRECTION_IDENTIFIER"<< endl;}
    
	| KEY_FX math_operators expression				{
													driver.nodes=new SGF::Ast::CStack(string("sparknoResource"));
													driver.nodes->push(driver.Ast->makeNumber($1));
													driver.nodes->push(driver.cvalues->pop());
													driver.nodes->push(driver.Ast->makeOperand(*$2));
													
													driver.cvalues->push(driver.Ast->makeFightResource(driver.Ast->makePostfixExpression(driver.nodes))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeyFX expression /TODO do not ignoreit on ANIM  "<<endl; 
													}
	| KEY_SX math_operators expression				{
													driver.nodes=new SGF::Ast::CStack(string("sparknoResource"));driver.nodes->push(driver.Ast->makeNumber($1));driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(*$2));
													driver.cvalues->push(driver.Ast->makeOwnResource(driver.Ast->makePostfixExpression(driver.nodes))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeyFX expression /TODO do not ignoreit on ANIM  "<<endl; 
													}
 	| KEY_FX 				{driver.cvalues->push(driver.Ast->makeFightResource(driver.Ast->makeNumber($1))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeyFX expression /TODO do not ignoreit on ANIM  "<<endl; }
	| KEY_SX				{driver.cvalues->push(driver.Ast->makeOwnResource(driver.Ast->makeNumber($1))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeySX expression "<<endl; }
	| KEY_IDENTIFIER '=' expression		{driver.nodes=new SGF::Ast::CStack(string("anim+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Expression Anim = espression  //END Rule 22//"<<endl;}
	;

function_if_else: FUNC_IFELSE '(' expression ',' expression ',' expression  ')' 				%prec UMINUS { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop())); }
				| FUNC_IFELSE '(' key_anim_expression ',' expression ',' expression  ')'  %prec UMINUS { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) $3, (SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop())); }
				| FUNC_IFELSE '(' key_anim_expression ',' simple_value ',' simple_value  ')'  %prec UMINUS { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) $3, (SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop())); }
				| FUNC_IFELSE '(' key_anim_expression ',' super_simple_value ',' super_simple_value  ')'  %prec UMINUS { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) $3,(SGF::Ast::CValue *) $5 , (SGF::Ast::CValue *) $7)); }
				;
	 
key_anim_expression:
KEY_ANIM compare_operators expression %prec KANIM {driver.nodes=new SGF::Ast::CStack(string("anim+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Key_Anim + espression  //END //"<<endl;}
| KEY_ANIM math_operators expression %prec KANIM {driver.nodes=new SGF::Ast::CStack(string("anim+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Key_Anim + espression  //END //"<<endl;}
;
	 



logical_expression:
	'~' expression                             {driver.cvalues->push(driver.Ast->makeUnaryExpression(driver.cvalues->pop(),string("NEGATION")));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Logical NOT "<< endl;}
	| '!' expression                           {driver.cvalues->push(driver.Ast->makeUnaryExpression(driver.cvalues->pop(),string("NOT")));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Logical Negation "<< endl;}
	| expression '&' expression                {driver.nodes=new SGF::Ast::CStack(string("nodes_&")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("BITAND")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	| expression '|' expression                {driver.nodes=new SGF::Ast::CStack(string("nodes_|")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("BITOR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	| expression CMD_XOR expression            {driver.nodes=new SGF::Ast::CStack(string("nodes_^")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("BITXOR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	| expression CMD_LOGAND expression         {driver.nodes=new SGF::Ast::CStack(string("nodes_&&")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("AND")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	| expression CMD_LOGOR  expression         {driver.nodes=new SGF::Ast::CStack(string("nodes_||")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("OR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	| expression CMD_LOGXOR  expression        {driver.nodes=new SGF::Ast::CStack(string("nodes_^^")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("XOR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	;


math_expression:
    expression math_operators expression %prec MATH_OPERATORS			 {driver.nodes=new SGF::Ast::CStack(string("nodes_math_operator")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(*$2));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math expression: // math operator // expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
	;

compare_expression:
				expression '=' expression		           {driver.nodes=new SGF::Ast::CStack(string("nodes_=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( = ) expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
				| expression CMD_NOTEQ   expression         {driver.nodes=new SGF::Ast::CStack(string("nodes_!=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( != ) expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
				| expression '>' expression                   {driver.nodes=new SGF::Ast::CStack(string("nodes_>")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("GREATER")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( > ) expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
				| expression '<' expression                   {driver.nodes=new SGF::Ast::CStack(string("nodes_<")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("LESS")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( < ) expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
				| expression CMD_LESSTHANEQ  expression       {driver.nodes=new SGF::Ast::CStack(string("nodes_<=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("LESSTHANEQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( <= ) expression1: "<<(SGF::Ast::CValue *)$1<< " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
				| expression CMD_GREATERTHANEQ expression     {driver.nodes=new SGF::Ast::CStack(string("nodes_>=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("GREATERTHANEQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( >= ) expression1: "<<(SGF::Ast::CValue *)$1<<  " expression2: "<<(SGF::Ast::CValue *)$3<< endl;}
				;

compare_operators:
					'='                  {$$= new string("EQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // = // "<< endl;}
				|	CMD_NOTEQ            {$$= new string("NOTEQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // != // "<< endl;}
				|	'>'                    {$$=new string("GREATER");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:compare operator: // > // "<< endl;}
				|	'<'                    {$$=new string("LESS");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // < // "<< endl;}
				|	CMD_LESSTHANEQ         {$$=new string("LESSTHANEQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // <= // "<< endl;}
				|	CMD_GREATERTHANEQ      {$$=new string("GREATERTHANEQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // >= // "<< endl;}
				;
math_operators: 	'+'             {$$=new string("ADD");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // + // "<< endl;}
				|	'-'				{$$=new string("SUB");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // - // "<< endl;}
				|	'/'             {$$=new string("DIV");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // / // "<< endl;}
				|	'*'             {$$=new string("MULTIPLY");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // * // "<< endl;}
				|	'%'				{$$=new string("MOD");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // % // "<< endl;}
				|	CMD_SQUARE      {$$=new string("POWER");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // ** // "<< endl;}
				;

keyword_comma_list:
		keywords ',' keywords {{  $$=driver.Ast->makeValueList((SGF::Ast::CValue *)($1),(SGF::Ast::CValue *)($3));}  }
		;

keywords:
		KEYWORD {$$=driver.Ast->makeKeyword($1);SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword: "<<  endl;}
        | KEYWORD compare_operators expression %prec KANIM {driver.nodes=new SGF::Ast::CStack(string("keyword+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeKeyword($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword + espression //END //"<<endl;}
		| KEYWORD compare_operators number_comma_list {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)($3));driver.nodes->push(driver.Ast->makeKeyword($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}

		| KEY_STATETYPE compare_operators expression %prec KANIM {driver.nodes=new SGF::Ast::CStack(string("statetype+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
		| KEY_STATETYPE compare_operators number_comma_list {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)($3));driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}

	    | KEY_IDENTIFIER'('NUMBER')' {$$=driver.Ast->makeKeyword($1);/*FIX MAKEINDEXKEYWORD $$=driver.Ast->makeKeywordArray($1,driver.Ast->makeNumber($3));;SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Array  //END //"<<endl;*/}
		| KEY_IDENTIFIER compare_operators number_comma_list {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)($3));driver.nodes->push(driver.Ast->makeKeyword($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
	    | KEY_IDENTIFIER compare_operators expression %prec KANIM {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
	    | KEY_IDENTIFIER math_operators expression %prec KANIM {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
	    
	    | common_names compare_operators expression %prec KANIM{driver.nodes=new SGF::Ast::CStack(string("command+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword CommonName + espression  //END //"<<endl;}
		| common_names compare_operators number_comma_list {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)($3));driver.nodes->push(driver.Ast->makeIdentifierSimple($1));driver.nodes->push(driver.Ast->makeOperand(*$2));$$=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
	    ;

range:
    '[' NUMBER ',' NUMBER ']'   {$$=driver.Ast->makeRange(1, $2,$4);}
    | '(' NUMBER ',' NUMBER ')' {$$=driver.Ast->makeRange(2, $2,$4);}
	| '[' NUMBER ',' NUMBER ')' {$$=driver.Ast->makeRange(3, $2,$4);}
    | '(' NUMBER ',' NUMBER ']' {$$=driver.Ast->makeRange(4, $2,$4);}
    ;

	
func_comparator:
				FUNC_IDENTIFIER  compare_operators super_simple_value  {
																		/* make string animelem */
																		$$=$1;
																		/* make operand */
																		driver.cvalues->push(driver.Ast->makeOperand(*$2));
																		/* make index */
																		driver.cvalues->push((SGF::Ast::CValue *)$3);
																		
																		}
				
				;
	
functions:
				  FUNC_IDENTIFIER '(' expression ')'  { /* used by gethitvar */ 
														SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 2"<< endl;  
														$$=driver.Ast->makeFunction( $1 ,(SGF::Ast::CValue *) driver.cvalues->pop()); 
														}
	         	| FUNC_IDENTIFIER '(' NUMBER  ')'  { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 3"<< endl; $$=driver.Ast->makeFunction( $1 , driver.Ast->makeNumber($3)); }
	         	| FUNC_CONST  '(' CONST_PARAM  ')' { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 8"<< endl; $$=driver.Ast->makeFunction($1,driver.Ast->makeString($3)); }
		     	| FUNC_LOG   '(' expression ',' expression ')'   {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 9 - BISON:NOT IMPLEMENTED YET "<< endl;}
				| func_comparator		{
																/* pop index */
																SGF::Ast::CValue * index = driver.cvalues->pop();
																/* pop operand */
																SGF::Ast::CValue * operand =driver.cvalues->pop();
																SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << $1->c_str() << endl;		
																string str1($1->c_str());
																string str2("animelem");
																/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
																SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
																SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
																*/
																if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push(driver.Ast->makeNumber(0));
																			firstExpression->push(function);
																			firstExpression->push(driver.Ast->makeOperand(string("EQUAL")));
																			$$ = driver.Ast->makePostfixExpression(firstExpression);
																		}else {
																		$$=driver.Ast->makeFunction( $1 ,index,operand);
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << " Making Function (FUNCTION=NUMBER) Rule 11"<< endl;
																		}
				
				
				}
				| func_comparator ',' compare_operators super_simple_value   %prec KANIM{
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << $1->c_str() << endl;		
															string str1($1->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)$4);
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(*$3));
																			$$ = driver.Ast->makePostfixExpression(firstExpression);
																			
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		$$=driver.Ast->makeFunction( $1 ,index,operand);
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << " Making Function (FUNCTION=NUMBER) Rule 11"<< endl;
																		}
															
															}
 				| func_comparator ',' super_simple_value   %prec KANIM{
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << $1->c_str() << endl;		
															string str1($1->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)$3);
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(string("EQUAL")));
																			$$ = driver.Ast->makePostfixExpression(firstExpression);
																			
																			
																		
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		$$=driver.Ast->makeFunction( $1 ,index,operand);
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << " Making Function (FUNCTION=NUMBER) Rule 11"<< endl;
																		}
															
															}
 				| func_comparator ',' compare_operators negative_number   %prec KANIM{
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << $1->c_str() << endl;		
															string str1($1->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)$4);
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(*$3));
																			$$ = driver.Ast->makePostfixExpression(firstExpression);
																			
																		
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		}
															
															}
 				| func_comparator ',' negative_number   %prec KANIM{
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << $1->c_str() << endl;		
															string str1($1->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)$3);
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(string("EQUAL")));
																			$$ = driver.Ast->makePostfixExpression(firstExpression);
																			
																			
																		
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		}
															
															}
 				| FUNC_IDENTIFIER  '=' number_comma_list {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 12"<< endl;$$=driver.Ast->makeFunction( $1 , (SGF::Ast::CValue *)($3));}
				| FUNC_IDENTIFIER  '=' identificator_comma_list {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 13"<< endl;$$=driver.Ast->makeFunction( $1 , (SGF::Ast::CValue *)($3));}
				| FUNC_PROJCONTACT '=' NUMBER   {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												$$=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber($1),driver.Ast->makeNumber($3),NULL,NULL);
												}
				| FUNC_PROJCONTACT '=' NUMBER ',' compare_operators expression {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												
												$$=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber($1),driver.Ast->makeNumber($3),driver.Ast->makeOperand(*$5),(SGF::Ast::CValue *) driver.cvalues->pop());
												}
				| FUNC_PROJGUARDED '=' NUMBER   {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												$$=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber($1),driver.Ast->makeNumber($3),NULL,NULL);
												}
				| FUNC_PROJGUARDED '=' NUMBER ',' compare_operators expression {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												
												$$=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber($1),driver.Ast->makeNumber($3),driver.Ast->makeOperand(*$5),(SGF::Ast::CValue *) driver.cvalues->pop());
												}
                | FUNC_PROJHIT '=' NUMBER   {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												$$=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber($1),driver.Ast->makeNumber($3),NULL,NULL);
												}
				| FUNC_PROJHIT '=' NUMBER ',' compare_operators expression {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												
												$$=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber($1),driver.Ast->makeNumber($3),driver.Ast->makeOperand(*$5),(SGF::Ast::CValue *) driver.cvalues->pop());
												}												
		     	| FUNC_SYSVAR '(' NUMBER ')' '=' expression  {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 16"<< endl; $$=driver.Ast->makeFunction( $1 ,driver.Ast->makeNumber($3),(SGF::Ast::CValue *) driver.cvalues->pop()); }
				| FUNC_SYSVAR '(' NUMBER ')'  {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 17"<< endl;  $$=driver.Ast->makeFunction( $1 ,driver.Ast->makeNumber($3)); }
				| FUNC_FVAR '(' expression ')'  {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 18"<< endl; $$=driver.Ast->makeFunction( $1 ,(SGF::Ast::CValue *) driver.cvalues->pop()); }
	         	| FUNC_FVAR '(' NUMBER  ')'  {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 19"<< endl;  $$=driver.Ast->makeFunction( $1 , driver.Ast->makeNumber($3)); }
	         	| FUNC_VAR '(' expression ')'  {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 20"<< endl; $$=driver.Ast->makeFunction( $1 ,(SGF::Ast::CValue *) driver.cvalues->pop()); }
	         	| FUNC_VAR '(' NUMBER  ')'  {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 21"<< endl; $$=driver.Ast->makeFunction( $1 , driver.Ast->makeNumber($3)); }
	         	;
func_identifiers:
				FUNC_IDENTIFIER 	{ $$=$1;}
				| FUNC_CONST 		{ $$=$1;}
				| FUNC_LOG 			{ $$=$1;}
				| FUNC_PROJCONTACT	{ $$=new string("projcontact");}
				| FUNC_PROJGUARDED	{ $$=new string("projguarded");}
				| FUNC_PROJHIT		{ $$=new string("projhit");}
				| FUNC_SYSVAR		{ $$=$1;}
				| FUNC_FVAR			{ $$=$1;}
				| FUNC_VAR			{ $$=$1;}
				;

hitdef: 
			KEY_HITDEF  {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "  Teste KEY_HITDEF regra 1";$$=driver.Ast->makeString($1);}
			| KEY_HITDEF  '=' IDENTIFIER  {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state"));driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute($3));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));$$=driver.Ast->makePostfixExpression(driver.nodes);}
			| KEY_HITDEF  '=' identificator_comma_list %prec EXPRESSIONLIST
				{ 
					std::string *tempState = new string;
					SGF::Ast::CHitDefAttackAttribute *teste= driver.Ast->makeHitDefAttackAttribute();
							
					try {
					    SGF::Ast::CValueList* list = (SGF::Ast::CValueList*) $3;
						SGF::Ast::CView view = list->view();
						view >> *tempState;
						  
						SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"  Teste KEY_HITDEF regra 3 "; 
						while(true) {
							std::string *temp = new string;
							view >> *temp;
							teste->addAttribute(temp); 
							} //end while
						} catch (const SGF::Ast::CException & e){
                                SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" END of List iteration";
						}
						driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:attackattribute"));
						driver.nodes->push(teste);driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:attribute")));
						driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));
						SGF::Ast::CValue *node2=driver.Ast->makePostfixExpression(driver.nodes); 
						driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state")); 
						driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state")));
						driver.nodes->push(driver.Ast->makeHitDefAttribute(tempState));
						driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));
						SGF::Ast::CValue *node1=driver.Ast->makePostfixExpression(driver.nodes);
						$$=driver.Ast->makeExpressionAnd(node1,node2);	
						
						
				}	
			| KEY_HITDEF  '!''=' IDENTIFIER  {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 (NEG) ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state")); driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute($4));driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));$$=driver.Ast->makePostfixExpression(driver.nodes);}
			| KEY_HITDEF  '!''=' identificator_comma_list %prec EXPRESSIONLIST
				{ 
					std::string *tempState = new string;
					SGF::Ast::CHitDefAttackAttribute *teste= driver.Ast->makeHitDefAttackAttribute();
							
					try {
					    SGF::Ast::CValueList* list = (SGF::Ast::CValueList*) $4;
						SGF::Ast::CView view = list->view();
						view >> *tempState;
						  
						SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<"  Teste KEY_HITDEF regra 5 "; 
						while(true) {
							std::string *temp = new string;
							view >> *temp;
							teste->addAttribute(temp); 
							} //end while
						} catch (const SGF::Ast::CException & e){
                                SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" END of List iteration";
						}
						driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:attackattribute"));
						driver.nodes->push(teste);driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:attribute")));
						driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));
						SGF::Ast::CValue *node2=driver.Ast->makePostfixExpression(driver.nodes); 
						driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state")); 
						driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state")));
						driver.nodes->push(driver.Ast->makeHitDefAttribute(tempState));
						driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));
						SGF::Ast::CValue *node1=driver.Ast->makePostfixExpression(driver.nodes);
						$$=driver.Ast->makeExpressionAnd(node1,node2);	
						
						
				}
			| KEY_HITDEF  '=' CMD_BUTTON_A  {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state"));driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute($3));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));$$=driver.Ast->makePostfixExpression(driver.nodes);}
			| KEY_HITDEF  '!''=' CMD_BUTTON_A  {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 (NEG) ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state")); driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute($4));driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));$$=driver.Ast->makePostfixExpression(driver.nodes);}
			;

simple_value:
		 keywords				{driver.cvalues->push((SGF::Ast::CValue *)$$); }
		| keyword_comma_list	{driver.cvalues->push((SGF::Ast::CValue *)$$); }
	    | range					{driver.cvalues->push((SGF::Ast::CValue *)$$); }
	    | QUOTESTRING			{driver.cvalues->push(driver.Ast->makeString($1)); /*colocar o hitflag depois do quotestring como value */}
		;
super_simple_value: 
			NUMBER				{$$=driver.Ast->makeNumber($1); }
		| KEY_IDENTIFIER		{$$=driver.Ast->makeIdentifierSimple($1); }
		| IDENTIFIER			{$$=driver.Ast->makeIdentifierSimple($1); }
		;
negative_number:
		'-' NUMBER				{$$=driver.Ast->makeNumber(-$2);}
		;







%%
// Error function throws an exception (string) with the location and error message
void CmdCompiler::Parser::error(const Parser::location_type& l,
			    const string& m)
{
    driver.error(l, m);
}


#undef bugon


