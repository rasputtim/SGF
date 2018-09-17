%{
#include <string.h>
#include "parse-cmd.hh"

// #define yydebug printf("yytext is %s at %d\n", yytext, __LINE__);
#define yydebug ;

#define LEX_PREFIX cmd
// #define LEX_VAL(p) LEX_PREFIX##p
#define LEX_VAL(p) cmd##p

// (d|D)(a|A)(t|T)(a|A) { return CMD_DATA; }
// (s|S)(t|T)(a|A)(t|T)(e|E)(d|D)(e|E)(f|F) { return CMD_STATEDEF; }
// (s|S)(t|T)(a|A)(t|T)(e|E) { return CMD_STATE; }

// \[\s*(s|S)(t|T)(a|A)(t|T)(e|E)\s+\d+\s*(,[^\]]*)?\] {

%}

%option yylineno

%%



. { return yytext[0]; }
%%
