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

#include "com_driver.h"

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
%name-prefix="ComCompiler"

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
    string*	stringVal;
    void*			cvalue;
    }


%type <stringVal> plain_key
%type <cvalue> simple_value
%type <cvalue> range
%type <cvalue> keylist
%type <cvalue> super_key
%type <cvalue> combined_key
%type <cvalue> key_modified


%left ','
%left <doubleVal> NUMBER
%left LOGICAL_OPERATORS
%left '~' CMD_LOGAND CMD_LOGOR CMD_LOGXOR '!' '&' '|' CMD_XOR
%left COMP_OPERATORS
%left '=' CMD_NOTEQ '>' '<' CMD_LESSTHANEQ CMD_GREATERTHANEQ
%left MATH_OPERATORS
%left '+' '-'
%left '*' '/' '%' CMD_SQUARE
%left EXP FLOOR LN

%left UMINUS UPLUS
%left <stringVal> FUNC_GETHITVAR  KEY_IDENTIFIER KEYWORD KEY_NAME KEY_BUFFERTIME KEY_TIME
%token <stringVal> FUNC_IDENTIFIER
%left  PLAYERIDEXIST PROJCANCELTIME SELFANIMEXIST
%left TAN VAR PROJCONTACTTIME PROJGUARDEDTIME
%left <stringVal> FUNC_LOG FUNC_CONST FUNC_SYSVAR FUNC_VAR FUNC_FVAR
%left <doubleVal> FUNC_PROJCONTACT FUNC_PROJHIT FUNC_PROJGUARDED
%right FUNC_IFELSE  KANIM
%right KEY_TRIGGER
%right  FUNC_IDENTIFIER
%token			END	     0	"end of file"
%token			EOL		"end of line"


%token ID
%token <stringVal> QUOTESTRING
%type <stringVal> key_modifier
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
%token <stringVal> KEY_COMMAND
%token <stringVal> KEY_DEFAULTS
%token <stringVal> KEY_STATETYPE

%token <stringVal> KEY_TYPE
%token <stringVal> KEY_ANIM
%token <stringVal> HELPER_IDENTIFIER
%token <stringVal> CONST_PARAM
%token <stringVal> COMMENT
%destructor { delete $$; } <stringVal>

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "com_driver.h"
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
        COMMENT {driver.clear_stack ();}
		| EOL   {driver.clear_stack ();}
		| lines COMMANDSECTION end_or_comment {}
        | error {/*yyclearin;*/ driver.clear_stack (); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
        ;

end_or_comment:
    EOL
  | COMMENT;


range:
    '[' NUMBER ',' NUMBER ']'   {$$=driver.Ast->makeRange(1, $2,$4);}
    | '(' NUMBER ',' NUMBER ')' {$$=driver.Ast->makeRange(2, $2,$4);}
	| '[' NUMBER ',' NUMBER ')' {$$=driver.Ast->makeRange(3, $2,$4);}
    | '(' NUMBER ',' NUMBER ']' {$$=driver.Ast->makeRange(4, $2,$4);}
    ;


simple_value:
		range					{driver.cvalues->push((SGF::Ast::CValue *)$$); }
	    | QUOTESTRING			{driver.cvalues->push(driver.Ast->makeString($1)); /*colocar o hitflag depois do quotestring como value */}
		| NUMBER				{driver.cvalues->push(driver.Ast->makeNumber($1));}
		| KEY_IDENTIFIER		{driver.cvalues->push(driver.Ast->makeIdentifierSimple($1)); }
		| IDENTIFIER			{driver.cvalues->push(driver.Ast->makeIdentifierSimple($1)); }
		| KEY_ANIM				{driver.cvalues->push(driver.Ast->makeIdentifierSimple($1)); }

		;







COMMANDSECTION:
	'[' KEY_COMMAND ']' {driver.Ast->makeSection($2); driver.Ast->iskey(); }
	| '[' KEY_DEFAULTS ']' { driver.Ast->makeSection($2); }
    | command_identifier 
    ;

command_identifier:
	| KEY_COMMAND '=' keylist {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyCommand=Keylist: address[ "<<$3<< " ]"<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.Ast->makeKeyList());}
	| KEY_TIME '=' simple_value {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TIME: "<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.cvalues->pop());}
	| KEY_BUFFERTIME '=' simple_value {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: BUFFERTIME "<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.cvalues->pop());}
	| KEY_NAME '=' simple_value {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: NAME "<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple($1),driver.cvalues->pop());
								}
	;


keylist:
      super_key  
      | super_key ',' keylist 
      ;

super_key: 	key_modified 			{
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Super key: WILL add modified key to vector "<<endl;
								$$=$1;driver.Ast->addKeyToList((SGF::Ast::CKey *)$$);  
								}
			| combined_key		{
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Super key: WILL add combined key to vector "<<endl;
								$$=$1; driver.Ast->addKeyToList((SGF::Ast::CKey *)$$) ; }
			| plain_key       	{
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Super key: WILL MAKE CKey and add to vector "<<endl;
								$$=driver.Ast->makeKey($1);driver.Ast->addKeyToList((SGF::Ast::CKey *)$$);  
								}
			;


key_modified:
			super_key_modifier plain_key  { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Apply modifier to key " <<endl;
											$$=	driver.Ast->applyKeyModifiers(driver.Ast->makeKey($2));}
			;
   
super_key_modifier:
					key_modifier 						{ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "rule super key modifier "<<endl;}
					| super_key_modifier key_modifier 	{
														SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "More than one key modifier "<<endl;
														}
					;
   
key_modifier:
   '~'   { driver.Ast->addReleaseKeyModifier(); }
   | '~' NUMBER  { driver.Ast->addReleaseKeyModifier($2); }
   | '/'  { driver.Ast->addHeldDownKeyModifier(); }
   | '$'  { driver.Ast->addDirectionKeyModifier(); }
   | '>'  { driver.Ast->addOnlyKeyModifier(); }
   ;

 
combined_key:
		plain_key '+' plain_key { 
								$$=driver.Ast->makeKeyCombined($1,$3);
								}
        | combined_key '+' plain_key { $$=driver.Ast->addCombinedKey((SGF::Ast::CKey *)$1,$3);}
		; 
plain_key:
   CMD_KEY_DOWN           	{ $$=$1; driver.Ast->iskey();}
   | CMD_KEY_FORWARD		{ $$=$1; driver.Ast->iskey();}
   | CMD_KEY_DOWN_FORWARD   { $$=$1; driver.Ast->iskey();}
   | CMD_KEY_BACK			{ $$=$1; driver.Ast->iskey();}
   | CMD_KEY_DOWN_BACK		{ $$=$1; driver.Ast->iskey();}
   | CMD_KEY_UP_FORWARD		{ $$=$1; driver.Ast->iskey();}
   | CMD_KEY_UP				{ $$=$1; driver.Ast->iskey();}
   | CMD_KEY_UP_BACK		{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_A			{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_B			{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_C			{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_X			{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_Y			{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_Z			{ $$=$1; driver.Ast->iskey();}
   | CMD_BUTTON_S			{ $$=$1; driver.Ast->iskey();}
	;
%%
// Error function throws an exception (string) with the location and error message
void ComCompiler::Parser::error(const Parser::location_type& l,
			    const string& m)
{
    driver.error(l, m);
}


#undef bugon


