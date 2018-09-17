
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   CmdCompilerlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 6 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
 /*** C/C++ Declarations ***/

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




/* Line 311 of lalr1.cc  */
#line 66 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"


#include "cmdparser.parser.hh"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 395 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"


#include "cmd_driver.h"
#include "cmdScanner.h"
#include "../../util/SGF_Debug.h"
/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 89 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace CmdCompiler {

/* Line 380 of lalr1.cc  */
#line 158 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 34: /* "KEYWORD" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 265 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 35: /* "KEY_IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 274 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 36: /* "FUNC_IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 283 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 45: /* "FUNC_FVAR" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 292 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 46: /* "FUNC_VAR" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 301 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 47: /* "FUNC_SYSVAR" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 310 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 48: /* "FUNC_CONST" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 319 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 49: /* "FUNC_LOG" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 328 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 55: /* "KEY_TRIGGER" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 337 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 58: /* "QUOTESTRING" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 346 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 111: /* "KEY_TRIGGERALL" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 355 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 112: /* "IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 364 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 113: /* "CMD_STATEDEF" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 373 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 114: /* "KEY_PHYSICS" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 382 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 115: /* "CMD_STATE" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 391 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 119: /* "HITDEFATTR" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 400 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 158: /* "KEY_HITDEF" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 409 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 250: /* "CMD_KEY_DOWN" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 418 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 251: /* "CMD_KEY_FORWARD" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 427 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 252: /* "CMD_KEY_DOWN_FORWARD" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 436 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 253: /* "CMD_KEY_BACK" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 445 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 254: /* "CMD_KEY_DOWN_BACK" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 454 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 255: /* "CMD_KEY_UP_FORWARD" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 463 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 256: /* "CMD_KEY_UP" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 472 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 257: /* "CMD_KEY_UP_BACK" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 481 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 258: /* "CMD_BUTTON_A" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 490 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 259: /* "CMD_BUTTON_B" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 499 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 260: /* "CMD_BUTTON_C" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 508 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 261: /* "CMD_BUTTON_X" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 517 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 262: /* "CMD_BUTTON_Y" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 526 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 263: /* "CMD_BUTTON_Z" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 535 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 264: /* "CMD_BUTTON_S" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 544 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 265: /* "KEY_STATETYPE" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 553 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 266: /* "KEY_TYPE" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 562 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 267: /* "KEY_ANIM" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 571 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 268: /* "TRIGGER_REDIRECTION_IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 580 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 269: /* "CONST_PARAM" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 589 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 270: /* "COMMENT" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 598 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 293: /* "common_names" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 607 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 301: /* "compare_operators" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 616 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 302: /* "math_operators" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 625 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 306: /* "func_comparator" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 634 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;
      case 308: /* "func_identifiers" */

/* Line 480 of lalr1.cc  */
#line 392 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 643 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 46 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 729 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 412 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.clear_stack ();}
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 413 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.clear_stack ();}
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 414 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.clear_stack ();}
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 415 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->setValidSection();}
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 416 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/*yyclearin;*/ driver.clear_stack (); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 424 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 425 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.cvalues->pop()); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 426 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection((SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 427 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (5)].cvalue));}
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 428 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.Ast->makeString((yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 429 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));}
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 430 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(4) - (3)].cvalue));}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 431 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection(driver.cvalues->pop()); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 432 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection((SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 433 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (5)].cvalue));}
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 434 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection(driver.Ast->makeString((yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 435 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));}
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 436 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->setValidSection(); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 439 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.cvalues->pop()); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 440 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (5)].cvalue));}
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 441 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (5)].cvalue));}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 442 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(5) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(5) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.Ast->makeString((yysemantic_stack_[(5) - (4)].doubleVal)));}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 443 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 444 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(5) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(5) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 445 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 446 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection(driver.cvalues->pop()); }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 447 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (5)].cvalue));}
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 448 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (5)].cvalue));}
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 449 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(5) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(5) - (3)].cvalue));driver.Ast->addValueToSection(driver.Ast->makeString((yysemantic_stack_[(5) - (4)].doubleVal)));}
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 450 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(4) - (3)].cvalue));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 451 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(5) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(5) - (3)].cvalue));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 452 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal));driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(6) - (3)].cvalue));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 453 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal));driver.Ast->addValueToSection(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(4) - (3)].stringVal)));driver.Ast->addValueToSection(driver.Ast->makeString(new string("not identified")));}
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 456 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  /* anim as a command identifier for superpouse and explod state controllers*/ }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 462 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=(SGF::Ast::CValue *)driver.cvalues->pop();}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 463 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 464 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 465 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 466 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 467 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 468 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 469 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 471 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].doubleVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 472 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].doubleVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 474 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 475 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 476 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { std::string * temp=new string(((SGF::Ast::CValue *)driver.cvalues->pop())->toString()); (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(2) - (1)].stringVal),temp);}
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 478 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 479 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 480 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 481 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].doubleVal));}
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 482 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 483 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 487 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeNumber((yysemantic_stack_[(2) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(2) - (2)].doubleVal)));}
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 488 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(2) - (1)].cvalue), driver.Ast->makeNumber((yysemantic_stack_[(2) - (2)].doubleVal)));}
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 493 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)));}
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 494 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)),driver.Ast->makeString((yysemantic_stack_[(3) - (3)].stringVal)));}
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 495 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(3) - (1)].cvalue), driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)));}
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 496 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(3) - (1)].cvalue), driver.Ast->makeString((yysemantic_stack_[(3) - (3)].stringVal)));}
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 500 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeString((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeString((yysemantic_stack_[(3) - (3)].stringVal)));}
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 501 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeString((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeString((yysemantic_stack_[(3) - (3)].stringVal)));}
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 502 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeString((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)));}
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 503 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueListFront((SGF::Ast::CValueList*)(yysemantic_stack_[(3) - (3)].cvalue),driver.Ast->makeString((yysemantic_stack_[(3) - (1)].stringVal)));}
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 504 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueListFront((SGF::Ast::CValueList*)(yysemantic_stack_[(3) - (3)].cvalue),driver.Ast->makeString((yysemantic_stack_[(3) - (1)].stringVal)));}
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 505 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueListFront((SGF::Ast::CValueList*)(yysemantic_stack_[(3) - (3)].cvalue),driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)));}
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 509 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(3) - (1)].stringVal),(yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 510 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(3) - (1)].stringVal),(yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 511 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(3) - (1)].stringVal),(yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 512 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {  (yyval.cvalue)=driver.Ast->makeIdentifier((yysemantic_stack_[(3) - (1)].stringVal),(yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 513 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(3) - (1)].cvalue), (yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 514 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(3) - (1)].cvalue), (yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 517 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGER = Expression // BEGIN //"<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.cvalues->pop());}
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 518 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGERALL = Expression // BEGIN //"<<endl; driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.cvalues->pop());}
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 519 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGER = Expression // BEGIN //"<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(5) - (1)].stringVal)),driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop()));}
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 520 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TRIGGERALL = Expression // BEGIN //"<<endl; driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(5) - (1)].stringVal)),driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop()));}
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 523 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												
												/*	if (*$3 == "F" || *$3 == "f") */
													SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyAnim = super_simple_value expression "<<endl;
													driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(4) - (1)].stringVal)),driver.Ast->makeFightResource((SGF::Ast::CValue *)driver.cvalues->pop()));
												
												
											}
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 531 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
											SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = expressioipconfign: "<<endl;
												driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeOwnResource((SGF::Ast::CValue *)driver.cvalues->pop()));
											}
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 544 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
													SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = KEY_ANIM: "<<endl;
													driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (3)].stringVal)));
												
									}
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 549 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(6) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),driver.cvalues->pop());}
    break;

  case 88:

/* Line 678 of lalr1.cc  */
#line 550 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EMPTY: "<<endl;
									SGF::Ast::CValue * number;
									if (*(yysemantic_stack_[(1) - (1)].stringVal)=="ignorehitpause") { 
									    number=driver.Ast->makeNumber(1);
										}
									driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal)),number); 
									}
    break;

  case 89:

/* Line 678 of lalr1.cc  */
#line 557 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EMPTY: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(2) - (1)].stringVal))); }
    break;

  case 90:

/* Line 678 of lalr1.cc  */
#line 558 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
													SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyIdentifier = EXPRESSION: "<<endl;
													driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)driver.cvalues->pop());
												
											}
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 563 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
											SGF::Ast::CValue *tempValue= (SGF::Ast::CValue *)driver.cvalues->pop();
											if (tempValue->getType()=="identifier"){
											driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*)tempValue,new string("-"));
											}
											SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyIdentifier = EXPRESSION - "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(4) - (1)].stringVal)),tempValue);
											}
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 570 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
											SGF::Ast::CValue *tempValue= (SGF::Ast::CValue *)driver.cvalues->pop();
											if (tempValue->getType()=="identifier"){
											driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*)tempValue,new string("+"));
											}
											SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EXPRESSION +: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(4) - (1)].stringVal)),tempValue);
											}
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 577 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyIdentifier = EXPRESSIONLIST: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 578 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=KeyType: "<<endl;driver.nodes=new SGF::Ast::CStack(string("key_type"));driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeKeyword((yysemantic_stack_[(3) - (3)].stringVal)));}
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 580 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)));driver.Ast->addValueToAttribute(driver.cvalues->pop());SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Bison::DOT LIST IDENTIFIER "<<  endl;}
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 581 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)),(SGF::Ast::CValue*)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 583 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(5) - (3)].cvalue),(yysemantic_stack_[(5) - (1)].stringVal)),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 584 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(5) - (3)].cvalue),(yysemantic_stack_[(5) - (1)].stringVal)), (SGF::Ast::CValue*)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 587 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)),driver.cvalues->pop());}
    break;

  case 100:

/* Line 678 of lalr1.cc  */
#line 588 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)),(SGF::Ast::CValue *)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 101:

/* Line 678 of lalr1.cc  */
#line 592 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(6) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),driver.cvalues->pop());}
    break;

  case 102:

/* Line 678 of lalr1.cc  */
#line 594 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Identifier = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 103:

/* Line 678 of lalr1.cc  */
#line 595 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Identifier = EXPRESSIONLIST: "<<endl;}
    break;

  case 104:

/* Line 678 of lalr1.cc  */
#line 597 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 105:

/* Line 678 of lalr1.cc  */
#line 598 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 106:

/* Line 678 of lalr1.cc  */
#line 600 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 107:

/* Line 678 of lalr1.cc  */
#line 601 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((yysemantic_stack_[(5) - (1)].stringVal),(yysemantic_stack_[(5) - (3)].stringVal)));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 108:

/* Line 678 of lalr1.cc  */
#line 604 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(5) - (3)].cvalue),(yysemantic_stack_[(5) - (1)].stringVal)));driver.Ast->addValueToAttribute(driver.cvalues->pop());}
    break;

  case 109:

/* Line 678 of lalr1.cc  */
#line 605 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifier((SGF::Ast::CIdentifier *)(yysemantic_stack_[(5) - (3)].cvalue),(yysemantic_stack_[(5) - (1)].stringVal)));driver.Ast->addValueToAttribute((SGF::Ast::CValue *)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 110:

/* Line 678 of lalr1.cc  */
#line 608 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 111:

/* Line 678 of lalr1.cc  */
#line 609 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 112:

/* Line 678 of lalr1.cc  */
#line 611 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(6) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),(SGF::Ast::CValue *) driver.cvalues->pop());}
    break;

  case 113:

/* Line 678 of lalr1.cc  */
#line 612 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(6) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),(SGF::Ast::CValue *) driver.cvalues->pop());}
    break;

  case 114:

/* Line 678 of lalr1.cc  */
#line 613 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeIndexAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(6) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),(SGF::Ast::CValue *) driver.cvalues->pop());}
    break;

  case 115:

/* Line 678 of lalr1.cc  */
#line 615 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Keyword = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 116:

/* Line 678 of lalr1.cc  */
#line 616 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=Keyword = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 117:

/* Line 678 of lalr1.cc  */
#line 618 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=>Const_param = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 118:

/* Line 678 of lalr1.cc  */
#line 619 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Attribute=>Const_param = expression: "<<endl;driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 119:

/* Line 678 of lalr1.cc  */
#line 624 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeStringSpace((SGF::Ast::CValue *)driver.cvalues->pop(),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 120:

/* Line 678 of lalr1.cc  */
#line 625 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=(yyval.cvalue)=driver.Ast->makeStringSpace(((SGF::Ast::CValue *)(yysemantic_stack_[(2) - (1)].cvalue)),(SGF::Ast::CValue *)driver.cvalues->pop());}
    break;

  case 121:

/* Line 678 of lalr1.cc  */
#line 629 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->makeValueList((SGF::Ast::CValue *)driver.cvalues->pop(),(SGF::Ast::CValue *)driver.cvalues->pop());SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Creating EXPRESSIONLIST : "<<endl;}
    break;

  case 122:

/* Line 678 of lalr1.cc  */
#line 630 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList *) (yysemantic_stack_[(3) - (1)].cvalue) ,(SGF::Ast::CValue *)driver.cvalues->pop() );SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:Adding To EXPRESSIONLIST: "<<endl;}
    break;

  case 123:

/* Line 678 of lalr1.cc  */
#line 633 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 124:

/* Line 678 of lalr1.cc  */
#line 634 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 125:

/* Line 678 of lalr1.cc  */
#line 637 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].stringVal));}
    break;

  case 126:

/* Line 678 of lalr1.cc  */
#line 638 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.Ast->setInvalidSection();}
    break;

  case 127:

/* Line 678 of lalr1.cc  */
#line 642 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Add Hitdef made in another rule to Stack // "<<endl;}
    break;

  case 128:

/* Line 678 of lalr1.cc  */
#line 643 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Add Function Made in another rule to Stack // "<<endl;}
    break;

  case 130:

/* Line 678 of lalr1.cc  */
#line 645 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 131:

/* Line 678 of lalr1.cc  */
#line 646 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/*Já faz push da expressão*/ }
    break;

  case 132:

/* Line 678 of lalr1.cc  */
#line 647 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/*Já faz push da expressão*/ }
    break;

  case 133:

/* Line 678 of lalr1.cc  */
#line 648 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/*Já faz push da expressão*/ }
    break;

  case 134:

/* Line 678 of lalr1.cc  */
#line 649 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: identificator comma list // "<<endl;}
    break;

  case 135:

/* Line 678 of lalr1.cc  */
#line 650 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=(yysemantic_stack_[(3) - (2)].cvalue);/*Já faz push da expressão*/SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: (expression) // TODO: oque fazer aqui"<<endl;}
    break;

  case 136:

/* Line 678 of lalr1.cc  */
#line 651 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=(yysemantic_stack_[(3) - (2)].cvalue);/*yyclearin;*/ /*Já faz push da expressão*/SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: :error // erro: "<<"TODO: oque fazer aqui"<<  endl;}
    break;

  case 137:

/* Line 678 of lalr1.cc  */
#line 652 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeUnaryExpression(driver.cvalues->pop(),string("MINUS")));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:  MINUS expression"<< endl;}
    break;

  case 138:

/* Line 678 of lalr1.cc  */
#line 653 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Expression List // "<<endl;}
    break;

  case 139:

/* Line 678 of lalr1.cc  */
#line 654 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/*Já faz push da expressão*/}
    break;

  case 140:

/* Line 678 of lalr1.cc  */
#line 655 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 141:

/* Line 678 of lalr1.cc  */
#line 656 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
							SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: , expression / Verificar se é uma valuelist e adicionar valor em branco"<< endl;
							SGF::Ast::CValue * tempValue= (SGF::Ast::CValue *)(yysemantic_stack_[(2) - (2)].cvalue);
							if(tempValue->getType()=="list of values") {
							SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Adding empty value to begginning of list" << endl;
							SGF::Ast::CValue *valueString = driver.Ast->makeString(new string("."));
							((SGF::Ast::CValueList*) tempValue)->addValuetoFront(valueString);
							}
							}
    break;

  case 142:

/* Line 678 of lalr1.cc  */
#line 665 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { 
																							SGF::Ast::CValue *expression2 = driver.cvalues->pop();
																							SGF::Ast::CValue *expression1 = driver.cvalues->pop();
																							driver.cvalues->push(driver.Ast->makeHelper((yysemantic_stack_[(6) - (1)].stringVal),expression1,expression2));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:HELPER - , TRIGGER_REDIRECTION_IDENTIFIER"<< endl;}
    break;

  case 143:

/* Line 678 of lalr1.cc  */
#line 669 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeHelper((yysemantic_stack_[(3) - (1)].stringVal),driver.cvalues->pop()));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:HELPER - , TRIGGER_REDIRECTION_IDENTIFIER"<< endl;}
    break;

  case 144:

/* Line 678 of lalr1.cc  */
#line 671 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
													driver.nodes=new SGF::Ast::CStack(string("sparknoResource"));
													driver.nodes->push(driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)));
													driver.nodes->push(driver.cvalues->pop());
													driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));
													
													driver.cvalues->push(driver.Ast->makeFightResource(driver.Ast->makePostfixExpression(driver.nodes))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeyFX expression /TODO do not ignoreit on ANIM  "<<endl; 
													}
    break;

  case 145:

/* Line 678 of lalr1.cc  */
#line 679 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
													driver.nodes=new SGF::Ast::CStack(string("sparknoResource"));driver.nodes->push(driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)));driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));
													driver.cvalues->push(driver.Ast->makeOwnResource(driver.Ast->makePostfixExpression(driver.nodes))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeyFX expression /TODO do not ignoreit on ANIM  "<<endl; 
													}
    break;

  case 146:

/* Line 678 of lalr1.cc  */
#line 683 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeFightResource(driver.Ast->makeNumber((yysemantic_stack_[(1) - (1)].doubleVal)))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeyFX expression /TODO do not ignoreit on ANIM  "<<endl; }
    break;

  case 147:

/* Line 678 of lalr1.cc  */
#line 684 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeOwnResource(driver.Ast->makeNumber((yysemantic_stack_[(1) - (1)].doubleVal)))); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:KeySX expression "<<endl; }
    break;

  case 148:

/* Line 678 of lalr1.cc  */
#line 685 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("anim+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Expression Anim = espression  //END Rule 22//"<<endl;}
    break;

  case 149:

/* Line 678 of lalr1.cc  */
#line 688 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop())); }
    break;

  case 150:

/* Line 678 of lalr1.cc  */
#line 689 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) (yysemantic_stack_[(8) - (3)].cvalue), (SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop())); }
    break;

  case 151:

/* Line 678 of lalr1.cc  */
#line 690 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) (yysemantic_stack_[(8) - (3)].cvalue), (SGF::Ast::CValue *) driver.cvalues->pop(), (SGF::Ast::CValue *) driver.cvalues->pop())); }
    break;

  case 152:

/* Line 678 of lalr1.cc  */
#line 691 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { driver.cvalues->push((SGF::Ast::CValue *) driver.Ast->makeFunctionif((SGF::Ast::CValue *) (yysemantic_stack_[(8) - (3)].cvalue),(SGF::Ast::CValue *) (yysemantic_stack_[(8) - (5)].cvalue) , (SGF::Ast::CValue *) (yysemantic_stack_[(8) - (7)].cvalue))); }
    break;

  case 153:

/* Line 678 of lalr1.cc  */
#line 695 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("anim+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Key_Anim + espression  //END //"<<endl;}
    break;

  case 154:

/* Line 678 of lalr1.cc  */
#line 696 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("anim+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Key_Anim + espression  //END //"<<endl;}
    break;

  case 155:

/* Line 678 of lalr1.cc  */
#line 703 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeUnaryExpression(driver.cvalues->pop(),string("NEGATION")));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Logical NOT "<< endl;}
    break;

  case 156:

/* Line 678 of lalr1.cc  */
#line 704 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeUnaryExpression(driver.cvalues->pop(),string("NOT")));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: Logical Negation "<< endl;}
    break;

  case 157:

/* Line 678 of lalr1.cc  */
#line 705 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_&")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("BITAND")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 158:

/* Line 678 of lalr1.cc  */
#line 706 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_|")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("BITOR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 159:

/* Line 678 of lalr1.cc  */
#line 707 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_^")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("BITXOR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 160:

/* Line 678 of lalr1.cc  */
#line 708 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_&&")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("AND")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 161:

/* Line 678 of lalr1.cc  */
#line 709 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_||")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("OR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 162:

/* Line 678 of lalr1.cc  */
#line 710 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_^^")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("XOR")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 163:

/* Line 678 of lalr1.cc  */
#line 715 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_math_operator")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math expression: // math operator // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 164:

/* Line 678 of lalr1.cc  */
#line 719 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( = ) expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 165:

/* Line 678 of lalr1.cc  */
#line 720 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_!=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( != ) expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 166:

/* Line 678 of lalr1.cc  */
#line 721 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_>")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("GREATER")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( > ) expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 167:

/* Line 678 of lalr1.cc  */
#line 722 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_<")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("LESS")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( < ) expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 168:

/* Line 678 of lalr1.cc  */
#line 723 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_<=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("LESSTHANEQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( <= ) expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 169:

/* Line 678 of lalr1.cc  */
#line 724 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("nodes_>=")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeOperand(string("GREATERTHANEQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare expression: ( >= ) expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<<  " expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 170:

/* Line 678 of lalr1.cc  */
#line 728 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)= new string("EQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // = // "<< endl;}
    break;

  case 171:

/* Line 678 of lalr1.cc  */
#line 729 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)= new string("NOTEQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // != // "<< endl;}
    break;

  case 172:

/* Line 678 of lalr1.cc  */
#line 730 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("GREATER");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON:compare operator: // > // "<< endl;}
    break;

  case 173:

/* Line 678 of lalr1.cc  */
#line 731 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("LESS");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // < // "<< endl;}
    break;

  case 174:

/* Line 678 of lalr1.cc  */
#line 732 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("LESSTHANEQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // <= // "<< endl;}
    break;

  case 175:

/* Line 678 of lalr1.cc  */
#line 733 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("GREATERTHANEQUAL");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: compare operator: // >= // "<< endl;}
    break;

  case 176:

/* Line 678 of lalr1.cc  */
#line 735 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("ADD");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // + // "<< endl;}
    break;

  case 177:

/* Line 678 of lalr1.cc  */
#line 736 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("SUB");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // - // "<< endl;}
    break;

  case 178:

/* Line 678 of lalr1.cc  */
#line 737 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("DIV");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // / // "<< endl;}
    break;

  case 179:

/* Line 678 of lalr1.cc  */
#line 738 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("MULTIPLY");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // * // "<< endl;}
    break;

  case 180:

/* Line 678 of lalr1.cc  */
#line 739 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("MOD");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // % // "<< endl;}
    break;

  case 181:

/* Line 678 of lalr1.cc  */
#line 740 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.stringVal)=new string("POWER");SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: math operator: // ** // "<< endl;}
    break;

  case 182:

/* Line 678 of lalr1.cc  */
#line 744 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {{  (yyval.cvalue)=driver.Ast->makeValueList((SGF::Ast::CValue *)((yysemantic_stack_[(3) - (1)].cvalue)),(SGF::Ast::CValue *)((yysemantic_stack_[(3) - (3)].cvalue)));}  }
    break;

  case 183:

/* Line 678 of lalr1.cc  */
#line 748 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword: "<<  endl;}
    break;

  case 184:

/* Line 678 of lalr1.cc  */
#line 749 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("keyword+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeKeyword((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword + espression //END //"<<endl;}
    break;

  case 185:

/* Line 678 of lalr1.cc  */
#line 750 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)((yysemantic_stack_[(3) - (3)].cvalue)));driver.nodes->push(driver.Ast->makeKeyword((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 186:

/* Line 678 of lalr1.cc  */
#line 752 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("statetype+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 187:

/* Line 678 of lalr1.cc  */
#line 753 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)((yysemantic_stack_[(3) - (3)].cvalue)));driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 188:

/* Line 678 of lalr1.cc  */
#line 755 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(4) - (1)].stringVal));/*FIX MAKEINDEXKEYWORD $$=driver.Ast->makeKeywordArray($1,driver.Ast->makeNumber($3));;SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Array  //END //"<<endl;*/}
    break;

  case 189:

/* Line 678 of lalr1.cc  */
#line 756 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)((yysemantic_stack_[(3) - (3)].cvalue)));driver.nodes->push(driver.Ast->makeKeyword((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 190:

/* Line 678 of lalr1.cc  */
#line 757 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 191:

/* Line 678 of lalr1.cc  */
#line 758 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 192:

/* Line 678 of lalr1.cc  */
#line 760 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("command+comp+expression")); driver.nodes->push(driver.cvalues->pop());driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword CommonName + espression  //END //"<<endl;}
    break;

  case 193:

/* Line 678 of lalr1.cc  */
#line 761 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.nodes=new SGF::Ast::CStack(string("key_Identifier+comp+numberCommaList")); driver.nodes->push((SGF::Ast::CValue*)((yysemantic_stack_[(3) - (3)].cvalue)));driver.nodes->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));(yyval.cvalue)=(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: make Keyword Command + espression  //END //"<<endl;}
    break;

  case 194:

/* Line 678 of lalr1.cc  */
#line 765 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(1, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 195:

/* Line 678 of lalr1.cc  */
#line 766 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(2, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 196:

/* Line 678 of lalr1.cc  */
#line 767 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(3, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 197:

/* Line 678 of lalr1.cc  */
#line 768 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(4, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 198:

/* Line 678 of lalr1.cc  */
#line 773 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
																		/* make string animelem */
																		(yyval.stringVal)=(yysemantic_stack_[(3) - (1)].stringVal);
																		/* make operand */
																		driver.cvalues->push(driver.Ast->makeOperand(*(yysemantic_stack_[(3) - (2)].stringVal)));
																		/* make index */
																		driver.cvalues->push((SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));
																		
																		}
    break;

  case 199:

/* Line 678 of lalr1.cc  */
#line 786 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { /* used by gethitvar */ 
														SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 2"<< endl;  
														(yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) ,(SGF::Ast::CValue *) driver.cvalues->pop()); 
														}
    break;

  case 200:

/* Line 678 of lalr1.cc  */
#line 790 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 3"<< endl; (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) , driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal))); }
    break;

  case 201:

/* Line 678 of lalr1.cc  */
#line 791 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 8"<< endl; (yyval.cvalue)=driver.Ast->makeFunction((yysemantic_stack_[(4) - (1)].stringVal),driver.Ast->makeString((yysemantic_stack_[(4) - (3)].stringVal))); }
    break;

  case 202:

/* Line 678 of lalr1.cc  */
#line 792 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 9 - BISON:NOT IMPLEMENTED YET "<< endl;}
    break;

  case 203:

/* Line 678 of lalr1.cc  */
#line 793 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
																/* pop index */
																SGF::Ast::CValue * index = driver.cvalues->pop();
																/* pop operand */
																SGF::Ast::CValue * operand =driver.cvalues->pop();
																SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << (yysemantic_stack_[(1) - (1)].stringVal)->c_str() << endl;		
																string str1((yysemantic_stack_[(1) - (1)].stringVal)->c_str());
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
																			(yyval.cvalue) = driver.Ast->makePostfixExpression(firstExpression);
																		}else {
																		(yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(1) - (1)].stringVal) ,index,operand);
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << " Making Function (FUNCTION=NUMBER) Rule 11"<< endl;
																		}
				
				
				}
    break;

  case 204:

/* Line 678 of lalr1.cc  */
#line 819 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << (yysemantic_stack_[(4) - (1)].stringVal)->c_str() << endl;		
															string str1((yysemantic_stack_[(4) - (1)].stringVal)->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)(yysemantic_stack_[(4) - (4)].cvalue));
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(*(yysemantic_stack_[(4) - (3)].stringVal)));
																			(yyval.cvalue) = driver.Ast->makePostfixExpression(firstExpression);
																			
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		(yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) ,index,operand);
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << " Making Function (FUNCTION=NUMBER) Rule 11"<< endl;
																		}
															
															}
    break;

  case 205:

/* Line 678 of lalr1.cc  */
#line 848 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << (yysemantic_stack_[(3) - (1)].stringVal)->c_str() << endl;		
															string str1((yysemantic_stack_[(3) - (1)].stringVal)->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)(yysemantic_stack_[(3) - (3)].cvalue));
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(string("EQUAL")));
																			(yyval.cvalue) = driver.Ast->makePostfixExpression(firstExpression);
																			
																			
																		
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		(yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(3) - (1)].stringVal) ,index,operand);
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << " Making Function (FUNCTION=NUMBER) Rule 11"<< endl;
																		}
															
															}
    break;

  case 206:

/* Line 678 of lalr1.cc  */
#line 879 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << (yysemantic_stack_[(4) - (1)].stringVal)->c_str() << endl;		
															string str1((yysemantic_stack_[(4) - (1)].stringVal)->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)(yysemantic_stack_[(4) - (4)].cvalue));
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(*(yysemantic_stack_[(4) - (3)].stringVal)));
																			(yyval.cvalue) = driver.Ast->makePostfixExpression(firstExpression);
																			
																		
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		}
															
															}
    break;

  case 207:

/* Line 678 of lalr1.cc  */
#line 907 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - BISON: animelemen "<< endl;
															/* pop index */
															SGF::Ast::CValue * index = driver.cvalues->pop();
															/* pop operand */
															SGF::Ast::CValue * operand =driver.cvalues->pop();
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "function Name: " << (yysemantic_stack_[(3) - (1)].stringVal)->c_str() << endl;		
															string str1((yysemantic_stack_[(3) - (1)].stringVal)->c_str());
															string str2("animelem");
															/*SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str1: "<< str1.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "str2: "<< str2.c_str() << endl;
															SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "comp: "<< str1.compare(str2) << endl;
															*/
															if (str1.compare(str2)==0 ){
																			SGF::Ast::CStack * firstExpression=new SGF::Ast::CStack(string("function animelemtime"));
																			SGF::Ast::CValue * function2=driver.Ast->makeFunction( new string("animelemtime"),index);
																			firstExpression->push((SGF::Ast::CValue*)(yysemantic_stack_[(3) - (3)].cvalue));
																			firstExpression->push(function2);
																			firstExpression->push(driver.Ast->makeOperand(string("EQUAL")));
																			(yyval.cvalue) = driver.Ast->makePostfixExpression(firstExpression);
																			
																			
																		
																		}else {
																		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 10 - ERROR SHOULD NOT GO HERE "<< endl;
															
																		}
															
															}
    break;

  case 208:

/* Line 678 of lalr1.cc  */
#line 936 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 12"<< endl;(yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(3) - (1)].stringVal) , (SGF::Ast::CValue *)((yysemantic_stack_[(3) - (3)].cvalue)));}
    break;

  case 209:

/* Line 678 of lalr1.cc  */
#line 937 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 13"<< endl;(yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(3) - (1)].stringVal) , (SGF::Ast::CValue *)((yysemantic_stack_[(3) - (3)].cvalue)));}
    break;

  case 210:

/* Line 678 of lalr1.cc  */
#line 938 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												(yyval.cvalue)=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)),NULL,NULL);
												}
    break;

  case 211:

/* Line 678 of lalr1.cc  */
#line 942 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												
												(yyval.cvalue)=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber((yysemantic_stack_[(6) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),driver.Ast->makeOperand(*(yysemantic_stack_[(6) - (5)].stringVal)),(SGF::Ast::CValue *) driver.cvalues->pop());
												}
    break;

  case 212:

/* Line 678 of lalr1.cc  */
#line 947 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												(yyval.cvalue)=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)),NULL,NULL);
												}
    break;

  case 213:

/* Line 678 of lalr1.cc  */
#line 951 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												
												(yyval.cvalue)=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber((yysemantic_stack_[(6) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),driver.Ast->makeOperand(*(yysemantic_stack_[(6) - (5)].stringVal)),(SGF::Ast::CValue *) driver.cvalues->pop());
												}
    break;

  case 214:

/* Line 678 of lalr1.cc  */
#line 956 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												(yyval.cvalue)=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)),NULL,NULL);
												}
    break;

  case 215:

/* Line 678 of lalr1.cc  */
#line 960 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {
												SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Function rule ProjContact"<< endl;
												
												(yyval.cvalue)=driver.Ast->makeProjectileExpression(new string("projcontact"),(SGF::Ast::CNumber *)driver.Ast->makeNumber((yysemantic_stack_[(6) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),driver.Ast->makeOperand(*(yysemantic_stack_[(6) - (5)].stringVal)),(SGF::Ast::CValue *) driver.cvalues->pop());
												}
    break;

  case 216:

/* Line 678 of lalr1.cc  */
#line 965 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 16"<< endl; (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(6) - (1)].stringVal) ,driver.Ast->makeNumber((yysemantic_stack_[(6) - (3)].doubleVal)),(SGF::Ast::CValue *) driver.cvalues->pop()); }
    break;

  case 217:

/* Line 678 of lalr1.cc  */
#line 966 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 17"<< endl;  (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) ,driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal))); }
    break;

  case 218:

/* Line 678 of lalr1.cc  */
#line 967 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 18"<< endl; (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) ,(SGF::Ast::CValue *) driver.cvalues->pop()); }
    break;

  case 219:

/* Line 678 of lalr1.cc  */
#line 968 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 19"<< endl;  (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) , driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal))); }
    break;

  case 220:

/* Line 678 of lalr1.cc  */
#line 969 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 20"<< endl; (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) ,(SGF::Ast::CValue *) driver.cvalues->pop()); }
    break;

  case 221:

/* Line 678 of lalr1.cc  */
#line 970 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {/* TODO MAKE INDEX FUNCTION */ SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Functin rule 21"<< endl; (yyval.cvalue)=driver.Ast->makeFunction( (yysemantic_stack_[(4) - (1)].stringVal) , driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal))); }
    break;

  case 222:

/* Line 678 of lalr1.cc  */
#line 973 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 223:

/* Line 678 of lalr1.cc  */
#line 974 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 224:

/* Line 678 of lalr1.cc  */
#line 975 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 225:

/* Line 678 of lalr1.cc  */
#line 976 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=new string("projcontact");}
    break;

  case 226:

/* Line 678 of lalr1.cc  */
#line 977 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=new string("projguarded");}
    break;

  case 227:

/* Line 678 of lalr1.cc  */
#line 978 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=new string("projhit");}
    break;

  case 228:

/* Line 678 of lalr1.cc  */
#line 979 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 229:

/* Line 678 of lalr1.cc  */
#line 980 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 230:

/* Line 678 of lalr1.cc  */
#line 981 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 231:

/* Line 678 of lalr1.cc  */
#line 985 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "  Teste KEY_HITDEF regra 1";(yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 232:

/* Line 678 of lalr1.cc  */
#line 986 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state"));driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute((yysemantic_stack_[(3) - (3)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));(yyval.cvalue)=driver.Ast->makePostfixExpression(driver.nodes);}
    break;

  case 233:

/* Line 678 of lalr1.cc  */
#line 988 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { 
					std::string *tempState = new string;
					SGF::Ast::CHitDefAttackAttribute *teste= driver.Ast->makeHitDefAttackAttribute();
							
					try {
					    SGF::Ast::CValueList* list = (SGF::Ast::CValueList*) (yysemantic_stack_[(3) - (3)].cvalue);
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
						(yyval.cvalue)=driver.Ast->makeExpressionAnd(node1,node2);	
						
						
				}
    break;

  case 234:

/* Line 678 of lalr1.cc  */
#line 1019 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 (NEG) ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state")); driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute((yysemantic_stack_[(4) - (4)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));(yyval.cvalue)=driver.Ast->makePostfixExpression(driver.nodes);}
    break;

  case 235:

/* Line 678 of lalr1.cc  */
#line 1021 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    { 
					std::string *tempState = new string;
					SGF::Ast::CHitDefAttackAttribute *teste= driver.Ast->makeHitDefAttackAttribute();
							
					try {
					    SGF::Ast::CValueList* list = (SGF::Ast::CValueList*) (yysemantic_stack_[(4) - (4)].cvalue);
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
						(yyval.cvalue)=driver.Ast->makeExpressionAnd(node1,node2);	
						
						
				}
    break;

  case 236:

/* Line 678 of lalr1.cc  */
#line 1052 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state"));driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute((yysemantic_stack_[(3) - (3)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));(yyval.cvalue)=driver.Ast->makePostfixExpression(driver.nodes);}
    break;

  case 237:

/* Line 678 of lalr1.cc  */
#line 1053 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) <<" Teste KEY_HITDEF regra 2 (NEG) ";  driver.nodes=new SGF::Ast::CStack(string("hitdefattr+comp+hitdef:state")); driver.nodes->push(driver.Ast->makeIdentifierSimple(string("hitdefattr:state"))); driver.nodes->push(driver.Ast->makeHitDefAttribute((yysemantic_stack_[(4) - (4)].stringVal)));driver.nodes->push(driver.Ast->makeOperand(string("NOTEQUAL")));(yyval.cvalue)=driver.Ast->makePostfixExpression(driver.nodes);}
    break;

  case 238:

/* Line 678 of lalr1.cc  */
#line 1057 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yyval.cvalue)); }
    break;

  case 239:

/* Line 678 of lalr1.cc  */
#line 1058 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yyval.cvalue)); }
    break;

  case 240:

/* Line 678 of lalr1.cc  */
#line 1059 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yyval.cvalue)); }
    break;

  case 241:

/* Line 678 of lalr1.cc  */
#line 1060 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {driver.cvalues->push(driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal))); /*colocar o hitflag depois do quotestring como value */}
    break;

  case 242:

/* Line 678 of lalr1.cc  */
#line 1063 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeNumber((yysemantic_stack_[(1) - (1)].doubleVal)); }
    break;

  case 243:

/* Line 678 of lalr1.cc  */
#line 1064 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 244:

/* Line 678 of lalr1.cc  */
#line 1065 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 245:

/* Line 678 of lalr1.cc  */
#line 1068 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"
    {(yyval.cvalue)=driver.Ast->makeNumber(-(yysemantic_stack_[(2) - (2)].doubleVal));}
    break;



/* Line 678 of lalr1.cc  */
#line 2787 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int Parser::yypact_ninf_ = -241;
  const short int
  Parser::yypact_[] =
  {
        22,  -241,  -241,   766,  -240,  -241,    29,    21,  -228,  -222,
    -206,    82,    93,    32,  -241,  -241,    99,   118,   154,   -17,
    -241,  -241,  -241,  -241,  -241,   124,  -241,  -241,  1037,  1072,
      61,   163,   164,   165,   172,  1037,  1037,  1037,   159,   175,
    1037,  1037,   -67,   -44,   110,   106,  -241,  -241,  -241,  1037,
    1037,  -241,  1037,  1037,  1037,  -241,   -45,   102,   -39,   -38,
     -36,   -35,   -23,   247,   249,   250,   -10,  -241,   262,   112,
     336,   427,   267,   462,   733,    16,   268,  1125,   273,  -241,
     276,   516,  2161,  -241,  -241,  -241,  -241,  -241,  -241,   288,
    -241,   295,  -241,  -241,  -241,  -241,   733,    16,   276,  2213,
      35,    38,    64,    44,    45,    47,    48,  2237,  2320,   276,
    2161,    66,    67,    68,    57,  2437,  1570,   276,  2161,  -241,
    -241,    25,   299,    30,    11,    59,    28,   276,  2161,  2437,
      23,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  1213,  -241,  -241,  -241,  -241,  -241,  -241,   300,  1213,
    1037,   -92,  1314,   206,  1384,  1455,   329,    74,  1037,   340,
     342,   348,  1037,   119,   181,   341,  1037,  1037,   202,  1213,
    1037,  1037,  1037,  1037,   387,   144,    49,  -241,  1037,  1213,
    1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,
    1037,  1037,  1037,  1037,   143,   759,   -16,   -15,  1037,   168,
    1037,   195,  1037,   224,   385,   393,   394,   397,  1037,  1037,
    1037,  1037,  1037,   399,  2437,   522,  -241,  -241,   595,  -241,
     198,   141,  -241,  -241,   470,   142,  -241,   413,   415,  -241,
    -241,  -241,  -241,   145,  -241,  -241,  -241,  -241,  -241,    -1,
      76,  -241,  -241,  -241,  -241,     1,   357,     7,  1849,   147,
     156,  2344,  -241,  -241,  -241,  2368,   416,  -241,   418,  -241,
     435,   451,  -241,   203,  2458,  2479,   452,  -241,   454,  -241,
    -241,  -241,  -241,  1916,   455,   204,  -241,  -241,  2437,   461,
    -241,  2437,  2541,  2112,  1000,  1535,  1120,   833,   886,   886,
     538,   538,   538,   538,   538,   699,  -241,   205,  -241,  -241,
     276,  2161,  -241,  -241,   276,  2161,  -241,  -241,   276,  2161,
    -241,  -241,  1037,  1037,  1037,  1037,  2437,  2437,   276,  2161,
     276,  2161,   276,  2161,  1037,   186,    -4,  2030,  1647,   102,
     -39,   -38,   -36,   -35,   -23,   247,   249,   250,   146,  -241,
      16,  1242,   378,   196,  -241,  -241,  -241,   209,  1739,  1418,
     419,   210,   217,  2051,  -241,  1621,   781,   648,  -241,   218,
    -241,  1775,   954,   920,  -241,    34,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,   487,  -241,  1037,  1037,  1037,   464,   499,
    -241,   504,  -139,     3,  -241,  -241,  2437,  2437,  2437,  2437,
    2437,  -241,  -241,  -241,   837,  -241,  -241,  1489,  2437,  2004,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  2500,  -241,
    2521,  -241,  -241,  -241,  -241,  -241,  -241,  1037,  1937,  2392,
    2416,  -241,  -241,  1037,  -241,  -241,  -241,  -241,    14,   886,
    -241,  1037,  1037,  -241,  1958,  2008,  -241,  -241
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     6,     4,    85,     0,     1,     0,    88,     0,     0,
       0,     0,     0,     0,   123,   124,     0,     0,     0,     0,
      21,    38,    39,    37,    83,     0,    84,     3,     0,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     5,     0,
       0,   242,     0,     0,     0,   183,   243,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   241,   244,   231,
     146,   147,     0,     0,     0,     0,     0,     0,   138,   134,
     116,     0,   115,   129,   130,   133,   131,   132,   239,   238,
     240,   203,   128,   127,   139,   140,    86,    94,    93,    90,
       0,     0,     0,     0,     0,     0,     0,    77,    78,   103,
     102,     0,     0,     0,     0,    82,   140,   118,   117,   126,
     125,     0,     0,     0,     0,     0,     0,   111,   110,   141,
       0,    59,   137,   155,   156,   170,   171,   172,   173,   175,
     174,     0,   176,   177,   179,   178,   180,   181,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   242,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     9,   245,     0,    15,
       0,     0,    26,    36,     0,     0,    33,     0,     0,    70,
     242,   185,   184,     0,   189,   190,   191,   208,   209,   242,
       0,   242,   243,   244,   198,   242,     0,   242,     0,     0,
       0,     0,   212,   214,   210,     0,   130,    67,    66,    69,
     232,   236,   233,     0,   144,   145,    65,    68,   187,   186,
     153,   154,   143,     0,     0,     0,   136,   135,   122,   193,
     192,   121,   162,   160,   161,   158,   159,   157,   164,   165,
     166,   167,   169,   168,   163,     0,   182,     0,   205,   207,
      96,    95,    73,    74,   100,    99,    72,    71,    98,    97,
      76,    75,     0,     0,     0,     0,    79,    80,   107,   106,
     105,   104,   109,   108,     0,     0,   242,   177,   243,   222,
     229,   230,   228,   223,   224,   226,   227,   225,   244,    43,
      41,     0,    40,   131,    45,    42,    44,     0,   243,     0,
      40,   131,     0,   243,    27,     0,     0,    40,    25,     0,
      34,     0,     0,    40,    32,     0,   188,   200,   199,   219,
     218,   221,   220,   217,   201,     0,     0,     0,   234,   237,
     235,     0,     0,     0,   204,   206,    87,   114,   113,   112,
     101,    14,    48,    49,   244,    51,    13,     0,     0,   131,
      46,    47,    56,    57,   222,   229,   230,   228,   223,   224,
     226,   227,   225,    54,    53,    58,    12,    55,    10,    11,
      20,    19,    18,    16,    17,    28,    23,    24,   120,    22,
     119,    35,    30,    31,    29,    63,    64,     0,     0,     0,
       0,   139,   140,     0,   194,   196,   197,   195,   242,   216,
     202,     0,     0,   142,     0,     0,   149,   150
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -241,  -241,  -241,  -241,  -241,  -241,  -115,  -241,   176,   601,
     471,  -241,  -241,  -241,  -241,   284,   301,   507,  -241,   -28,
    -241,   352,  -241,  -111,  -241,   -20,   -27,  -241,   333,  -241,
    -241,  -241,    56,  -241,   174,   -24,    -9
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,    48,    19,    20,   341,    78,   231,    79,
     102,    21,    22,    23,    24,   356,    80,    81,    26,   398,
      83,    84,    85,    86,    87,   149,   193,    88,    89,    90,
      91,    92,   346,    93,    94,    95,   123
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -93;
  const short int
  Parser::yytable_[] =
  {
        82,    99,   130,   131,   130,   131,   130,   107,   108,   110,
     130,   131,   115,   118,   220,   221,   116,   275,   131,   172,
     228,   128,   129,     1,   132,   133,   134,   227,   215,   150,
      27,   224,   225,   218,    29,   141,   126,   153,   435,    46,
     -92,   -91,    28,   166,   167,    37,    32,   171,   198,   176,
     276,   200,    33,   169,   170,   181,   182,   183,   184,   185,
     186,   179,   187,   188,   189,   190,   191,   192,    34,   171,
     142,   143,   144,   145,   146,   147,   170,   202,     2,   210,
     211,   212,   181,   182,   183,   184,   185,   186,   214,   187,
     188,   189,   190,   191,   192,    35,   100,   142,   143,   144,
     145,   146,   147,   349,   343,   355,    36,   351,   392,   361,
     124,   393,    40,   232,   121,   151,   136,   137,   138,   139,
     140,   235,   236,   257,   240,   164,   246,   248,   122,   244,
     251,    41,   122,   444,   255,   228,   445,    49,   264,   265,
     165,   269,   270,   271,   272,   273,   436,   275,   131,   163,
     278,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,    72,   103,   104,   105,
     301,   298,   305,   101,   309,   297,   106,    55,   295,   114,
     316,   317,   319,   321,   323,   227,   299,   342,   345,    42,
     350,   345,   357,   345,   111,   344,   363,   345,   344,   352,
     344,    50,   326,   302,   344,   119,   227,   227,   383,   241,
     241,   135,   136,   137,   138,   139,   140,   399,   125,   142,
     327,   144,   145,   146,   147,    53,    54,   122,   120,   148,
     306,   258,    55,   353,   329,   154,   155,   399,   156,   157,
     242,   242,   399,   330,   331,   332,   333,   334,   335,   336,
     337,   158,    66,    47,   -92,   -91,    67,    14,   400,   310,
     159,   401,   160,   161,   162,   163,    43,    44,   150,    45,
     168,   112,   174,   384,   367,   446,   369,   177,   447,   178,
     303,    72,   371,   222,   386,   387,   388,   389,   385,   366,
     173,   194,    -2,   260,    30,    31,   390,   216,   195,   132,
     226,   150,   219,   217,   233,    38,    39,   307,   199,   153,
     338,   201,    14,   339,   266,   378,   228,   243,   243,   204,
     205,   150,   206,   207,   277,   234,   150,   237,   428,   430,
      98,   223,   213,   249,   428,   430,   311,   203,   109,   199,
     201,   203,   117,   250,   252,   268,   253,   438,   439,   440,
     127,   368,   254,   442,   263,   279,    69,   142,   143,   144,
     145,   146,   147,   181,   182,   183,   184,   185,   186,   176,
     187,   188,   189,   190,   191,   192,   152,    72,   142,   143,
     144,   145,   146,   147,   181,   182,   183,   184,   185,   186,
     274,   187,   188,   189,   190,   191,   192,   417,   312,   142,
     143,   144,   145,   146,   147,   417,   313,   314,    73,   449,
     315,   417,   324,   358,   364,   453,   130,   417,   163,   377,
     366,   163,   373,   454,   455,   181,   182,   183,   184,   185,
     186,   374,   187,   188,   189,   190,   191,   192,   163,   261,
     142,   143,   144,   145,   146,   147,    70,    71,   142,   143,
     144,   145,   146,   147,   168,   163,    72,   365,   391,   382,
      72,   379,    72,    73,   365,    74,   340,   163,   419,    76,
     354,   359,    77,    50,   326,   135,   136,   137,   138,   139,
     140,   420,   424,   135,   136,   137,   138,   139,   140,   425,
     431,   142,   327,   144,   145,   146,   147,    53,    54,   300,
     437,   304,   168,   308,    55,   353,   329,   443,   362,   113,
      25,   318,   320,   322,   256,   330,   331,   332,   333,   334,
     335,   336,   337,   325,    66,    50,   326,   296,    67,   135,
     136,   137,   138,   139,   140,   135,   136,   137,   138,   139,
     140,     0,     0,   142,   327,   144,   145,   146,   147,    53,
      54,   441,     0,     0,     0,     0,    55,   328,   329,   142,
     143,   144,   145,   146,   147,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,     0,    66,     0,     0,     0,
      67,     0,   338,     0,    14,   339,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   347,     0,    50,   326,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
     137,   138,   139,   140,     0,     0,   142,   327,   144,   145,
     146,   147,    53,    54,     0,     0,     0,     0,    69,    55,
     348,   329,   370,     0,   338,     0,    14,   339,     0,     0,
     330,   331,   332,   333,   334,   335,   336,   337,     0,    66,
     418,    50,    51,    67,   181,   182,   183,   184,   185,   186,
       0,   187,   188,   189,   190,   191,   192,     0,     0,   142,
     327,   144,   145,   146,   147,    53,    54,     0,     0,     0,
      69,     0,    55,    56,    57,     0,     0,     0,     0,     0,
       0,   423,     0,    58,    59,    60,    61,    62,    63,    64,
      65,     0,    66,     0,     0,     0,    67,   338,     0,    14,
     339,     0,   135,   136,   137,   138,   139,   140,    70,    71,
     142,   143,   144,   145,   146,   147,     0,     0,    72,     0,
       0,   229,     0,     0,     0,    73,     0,    74,   340,     0,
       0,    76,   360,     0,    77,     0,   135,   136,   137,   138,
     139,   140,   238,    69,   142,   143,   144,   145,   146,   147,
      68,     0,    14,   241,   259,   262,     5,     0,     0,   267,
      70,    71,   135,   136,   137,   138,   139,   140,     0,     0,
      72,   122,     0,     0,    50,    51,     0,    73,     0,    74,
     340,     0,     0,    76,   242,     0,    77,     0,     0,     0,
       6,     7,     0,    52,     0,     0,    69,     0,    53,    54,
       0,     8,     9,    10,     0,    55,    56,    57,     0,     0,
       0,    11,     0,     0,     0,     0,    58,    59,    60,    61,
      62,    63,    64,    65,     0,    66,     0,     0,     0,    67,
     163,   -50,     0,    70,    71,     0,   187,   188,   189,   190,
     191,   192,     0,    72,   142,   143,   144,   145,   146,   147,
      73,     0,    74,   340,   380,     0,    76,     0,     0,    77,
       0,   243,   -50,   -50,     0,     0,   229,    12,    13,     0,
      14,     0,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
       0,     0,     0,    68,     0,    14,    70,    71,     0,     0,
       0,   189,   190,   191,   192,     0,    72,   142,   143,   144,
     145,   146,   147,    73,     0,    74,    75,     0,     0,    76,
     429,     0,    77,    50,    51,     0,   181,   182,   183,   184,
     185,   186,     0,   187,   188,   189,   190,   191,   192,    69,
       0,   142,   327,   144,   145,   146,   147,    53,    54,   -50,
       0,     0,   -50,     0,    55,    56,    57,    50,    51,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    64,    65,   148,    66,     0,    52,     0,    67,     0,
       0,    53,    54,     0,     0,     0,     0,     0,    55,    56,
      57,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      59,    60,    61,    62,    63,    64,    65,     0,    66,   184,
     185,   186,    67,   187,   188,   189,   190,   191,   192,     0,
       0,   142,   143,   144,   145,   146,   147,     0,     0,    70,
      71,    15,    68,    16,    14,    17,     0,    18,     0,    72,
      50,    51,     0,     0,     0,     0,    73,     0,    74,    75,
       0,     0,    76,   427,     0,    77,     0,     0,     0,    52,
       0,     0,     0,     0,    53,    54,    68,     0,    14,     0,
       0,    55,    56,    57,     0,    50,    51,     0,    69,     0,
       0,     0,    58,    59,    60,    61,    62,    63,    64,    65,
       0,    66,     0,     0,    52,    67,     0,     0,     0,    53,
      54,     0,     0,     0,     0,   -50,    55,    56,    57,   -50,
       0,     0,    69,     0,     0,     0,     0,    58,    59,    60,
      61,    62,    63,    64,    65,     0,    66,     0,    50,   175,
      67,   186,     0,   187,   188,   189,   190,   191,   192,     0,
       0,   142,   143,   144,   145,   146,   147,    52,     0,    68,
       0,    14,    53,    54,     0,     0,     0,     0,     0,    55,
      56,    57,     0,     0,     0,     0,     0,     0,    70,    71,
      58,    59,    60,    61,    62,    63,    64,    65,    72,    66,
       0,     0,     0,    67,    68,    73,    14,    74,    75,     0,
       0,    76,   434,     0,    77,    69,     0,     0,     0,     0,
       0,     0,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,    72,     0,     0,     0,    50,   230,     0,    73,
       0,    74,    75,     0,     0,    76,   433,     0,    77,     0,
      69,     0,     0,     0,     0,    52,     0,    68,     0,    14,
      53,    54,     0,     0,     0,     0,   402,    55,    56,    57,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    59,
      60,    61,    62,    63,    64,    65,     0,    66,     0,     0,
       0,    67,     0,     0,     0,     0,     0,   403,   404,     0,
       0,     0,     0,    69,     0,    70,    71,   405,   406,   407,
     408,   409,   410,   411,   412,    72,     0,     0,     0,     0,
       0,     0,    73,     0,    74,    75,     0,     0,    76,     0,
       0,    77,     0,     0,     0,     0,     0,    50,   239,     0,
      70,    71,     0,     0,     0,    68,     0,    14,     0,     0,
      72,     0,     0,     0,     0,     0,    52,    73,     0,    96,
      97,    53,    54,    76,     0,     0,    77,     0,    55,    56,
      57,     0,     0,     0,   413,     0,     0,   414,     0,    58,
      59,    60,    61,    62,    63,    64,    65,     0,    66,     0,
       0,    69,    67,    70,    71,     0,     0,     0,     0,     0,
       0,     0,     0,    72,     0,     0,     0,    50,   245,     0,
      73,     0,    74,    75,     0,     0,    76,     0,     0,    77,
       0,     0,     0,     0,     0,     0,    52,     0,     0,     0,
       0,    53,    54,     0,     0,     0,     0,     0,    55,    56,
      57,     0,   402,     0,     0,     0,    68,     0,    14,    58,
      59,    60,    61,    62,    63,    64,    65,     0,    66,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   403,   404,     0,     0,     0,    50,   247,
       0,    70,    71,   405,   406,   407,   408,   409,   410,   411,
     412,    72,    69,     0,     0,     0,     0,    52,    73,     0,
      74,    75,    53,    54,    76,     0,     0,    77,     0,    55,
      56,    57,    50,   448,     0,     0,    68,     0,    14,     0,
      58,    59,    60,    61,    62,    63,    64,    65,     0,    66,
     415,    52,     0,    67,   416,     0,    53,    54,     0,     0,
       0,     0,     0,    55,    56,    57,     0,     0,     0,     0,
     413,     0,     0,   414,    58,    59,    60,    61,    62,    63,
      64,    65,    69,    66,     0,   185,   186,    67,   187,   188,
     189,   190,   191,   192,     0,     0,   142,   143,   144,   145,
     146,   147,    70,    71,     0,     0,     0,    68,     0,    14,
       0,     0,    72,    50,    51,     0,     0,     0,     0,    73,
       0,    74,    75,     0,     0,    76,     0,     0,    77,     0,
       0,     0,     0,     0,     0,     0,     0,    53,    54,     0,
       0,    68,     0,    14,    55,    56,    57,     0,     0,     0,
       0,     0,     0,    69,     0,    58,    59,    60,    61,    62,
      63,    64,    65,     0,    66,   402,     0,     0,    67,     0,
       0,     0,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,    69,     0,    73,
      50,    74,    75,     0,     0,    76,   403,   404,    77,     0,
       0,     0,     0,     0,     0,     0,   405,   406,   407,   408,
     409,   410,   411,   412,    53,    54,     0,     0,     0,     0,
       0,    55,    68,    57,    14,     0,   415,     0,     0,     0,
     422,     0,    58,    59,    60,    61,    62,    63,    64,    65,
       0,    66,     0,    70,    71,    67,     0,     0,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,     0,     0,
      73,     0,    74,    75,     0,     0,    76,     0,    69,    77,
       0,     0,     0,   413,     0,     0,   414,    70,    71,     0,
       0,     0,    50,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,    73,     0,    74,    75,     0,   394,
      76,    14,   395,    77,     0,     0,    53,    54,     0,     0,
       0,     0,     0,    55,     0,    57,     0,     0,     0,   402,
       0,     0,     0,     0,    58,    59,    60,    61,    62,    63,
      64,    65,     0,    66,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
     403,   404,     0,     0,     0,     0,     0,     0,    70,    71,
     405,   406,   407,   408,   409,   410,   411,   412,    72,     0,
       0,     0,     0,     0,     0,    73,     0,    74,    75,     0,
       0,    76,     0,     0,    77,     0,     0,     0,     0,     0,
       0,   394,     0,    14,   395,   181,   182,   183,   184,   185,
     186,     0,   187,   188,   189,   190,   191,   192,     0,     0,
     142,   143,   144,   145,   146,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   413,     0,   415,
     414,     0,     0,   426,     0,    70,    71,    69,     0,     0,
       0,     0,     0,     0,     0,    72,     0,     0,     0,     0,
       0,     0,    73,     0,    74,    75,     0,     0,    76,   396,
       0,   397,   181,   182,   183,   184,   185,   186,     0,   187,
     188,   189,   190,   191,   192,     0,     0,   142,   143,   144,
     145,   146,   147,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   189,   190,   191,   192,     0,     0,   142,   143,
     144,   145,   146,   147,   181,   182,   183,   184,   185,   186,
       0,   187,   188,   189,   190,   191,   192,     0,     0,   142,
     143,   144,   145,   146,   147,     0,     0,    70,    71,     0,
       0,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,    73,     0,    74,    75,   -52,     0,
      76,   421,     0,   397,   181,   182,   183,   184,   185,   186,
       0,   187,   188,   189,   190,   191,   192,     0,     0,   142,
     143,   144,   145,   146,   147,     0,     0,     0,     0,   -52,
     -52,     0,     0,   415,     0,     0,     0,   432,     0,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,    53,    54,     0,
       0,     0,     0,     0,    55,    56,    57,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    64,    65,     0,    66,     0,     0,    57,    67,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,    61,
      62,    63,    64,    65,     0,    66,     0,     0,     0,    67,
       0,     0,     0,     0,     0,     0,   -52,     0,     0,   -52,
     183,   184,   185,   186,   372,   187,   188,   189,   190,   191,
     192,     0,     0,   142,   143,   144,   145,   146,   147,     0,
       0,     0,    68,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   394,   180,    14,   395,   181,   182,   183,
     184,   185,   186,     0,   187,   188,   189,   190,   191,   192,
       0,     0,   142,   143,   144,   145,   146,   147,    69,     0,
       0,   381,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,   450,     0,     0,     0,   180,     0,     0,   181,
     182,   183,   184,   185,   186,     0,   187,   188,   189,   190,
     191,   192,     0,   456,   196,   197,   144,   145,   146,   147,
     208,     0,     0,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   189,   190,   191,   192,     0,     0,   142,   143,
     144,   145,   146,   147,     0,     0,     0,     0,     0,     0,
       0,     0,   -52,     0,     0,     0,   -52,     0,    70,    71,
       0,     0,     0,   457,     0,     0,     0,     0,    72,     0,
       0,     0,     0,     0,     0,    73,     0,    74,    75,    70,
      71,    76,     0,     0,    77,     0,     0,     0,     0,    72,
       0,     0,     0,     0,     0,     0,    73,     0,    74,    75,
       0,     0,    76,   209,     0,   397,   181,   182,   183,   184,
     185,   186,     0,   187,   188,   189,   190,   191,   192,     0,
       0,   142,   143,   144,   145,   146,   147,   375,     0,     0,
     181,   182,   183,   184,   185,   186,     0,   187,   188,   189,
     190,   191,   192,     0,     0,   142,   143,   144,   145,   146,
     147,   376,     0,     0,   181,   182,   183,   184,   185,   186,
       0,   187,   188,   189,   190,   191,   192,     0,     0,   142,
     143,   144,   145,   146,   147,   451,     0,     0,   181,   182,
     183,   184,   185,   186,     0,   187,   188,   189,   190,   191,
     192,     0,     0,   142,   143,   144,   145,   146,   147,   452,
       0,     0,   181,   182,   183,   184,   185,   186,     0,   187,
     188,   189,   190,   191,   192,     0,     0,   142,   143,   144,
     145,   146,   147,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   189,   190,   191,   192,     0,     0,   142,   143,
     144,   145,   146,   147,   181,   182,   183,   184,   185,   186,
       0,   187,   188,   189,   190,   191,   192,     0,     0,   142,
     143,   144,   145,   146,   147,   181,   182,   183,   184,   185,
     186,     0,   187,   188,   189,   190,   191,   192,     0,     0,
     142,   143,   144,   145,   146,   147,   181,   182,   183,   184,
     185,   186,     0,   187,   188,   189,   190,   191,   192,     0,
       0,   142,   143,   144,   145,   146,   147,   181,   182,   183,
     184,   185,   186,     0,   187,   188,   189,   190,   191,   192,
       0,     0,   142,   143,   144,   145,   146,   147,   182,   183,
     184,   185,   186,     0,   187,   188,   189,   190,   191,   192,
       0,     0,   142,   143,   144,   145,   146,   147
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        28,    29,     3,     4,     3,     4,     3,    35,    36,    37,
       3,     4,    40,    41,     3,     4,    40,     3,     4,     3,
     112,    49,    50,     1,    52,    53,    54,     4,     3,    56,
     270,     3,     4,     3,    13,    55,    45,    57,     4,    56,
      56,    56,    13,    70,    71,    13,   274,    74,    13,    77,
       1,    13,   274,    73,    74,     6,     7,     8,     9,    10,
      11,    81,    13,    14,    15,    16,    17,    18,   274,    96,
      21,    22,    23,    24,    25,    26,    96,    13,    56,    13,
      13,    13,     6,     7,     8,     9,    10,    11,   116,    13,
      14,    15,    16,    17,    18,    13,    35,    21,    22,    23,
      24,    25,    26,   218,   215,   220,    13,   218,   112,   224,
       4,   115,    13,   141,     4,    13,    14,    15,    16,    17,
      18,   149,   150,     4,   152,    13,   154,   155,    22,   153,
     158,    13,    22,   272,   162,   112,   275,    13,   166,   167,
      28,   169,   170,   171,   172,   173,   112,     3,     4,     3,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   258,     4,     4,     4,
     198,   195,   200,   112,   202,   195,     4,    34,    35,     4,
     208,   209,   210,   211,   212,     4,   195,   215,   215,    35,
     218,   218,   220,   220,    35,   215,   224,   224,   218,     1,
     220,     3,     4,    35,   224,   272,     4,     4,     4,     4,
       4,    13,    14,    15,    16,    17,    18,   328,   112,    21,
      22,    23,    24,    25,    26,    27,    28,    22,   272,   274,
      35,   112,    34,    35,    36,   274,   274,   348,   274,   274,
      35,    35,   353,    45,    46,    47,    48,    49,    50,    51,
      52,   274,    54,   270,   270,   270,    58,   114,   112,    35,
      13,   115,    13,    13,   274,     3,   112,   113,   295,   115,
       3,   112,     4,   297,   275,   272,   275,     4,   275,     3,
     112,   258,   275,   272,   312,   313,   314,   315,   297,   275,
     274,     3,   270,   112,   273,   274,   324,   272,     3,   327,
     272,   328,   272,     4,     4,   273,   274,   112,   273,   329,
     112,   273,   114,   115,   112,   112,   112,   112,   112,   275,
     275,   348,   275,   275,   275,   149,   353,   151,   356,   357,
      29,   272,   275,     4,   362,   363,   112,   273,    37,   273,
     273,   273,    41,   269,     4,   169,     4,   375,   376,   377,
      49,   275,     4,   377,    13,   179,   158,    21,    22,    23,
      24,    25,    26,     6,     7,     8,     9,    10,    11,   397,
      13,    14,    15,    16,    17,    18,   274,   258,    21,    22,
      23,    24,    25,    26,     6,     7,     8,     9,    10,    11,
       3,    13,    14,    15,    16,    17,    18,   341,    13,    21,
      22,    23,    24,    25,    26,   349,    13,    13,   265,   437,
      13,   355,    13,   272,   272,   443,     3,   361,     3,     3,
     275,     3,   275,   451,   452,     6,     7,     8,     9,    10,
      11,   275,    13,    14,    15,    16,    17,    18,     3,   258,
      21,    22,    23,    24,    25,    26,   248,   249,    21,    22,
      23,    24,    25,    26,     3,     3,   258,     3,   272,     4,
     258,   258,   258,   265,     3,   267,   268,     3,   272,   271,
     272,     1,   274,     3,     4,    13,    14,    15,    16,    17,
      18,   272,   272,    13,    14,    15,    16,    17,    18,   272,
     272,    21,    22,    23,    24,    25,    26,    27,    28,   198,
      13,   200,     3,   202,    34,    35,    36,     3,   224,    38,
       3,   210,   211,   212,   162,    45,    46,    47,    48,    49,
      50,    51,    52,     1,    54,     3,     4,   194,    58,    13,
      14,    15,    16,    17,    18,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,   377,    -1,    -1,    -1,    -1,    34,    35,    36,    21,
      22,    23,    24,    25,    26,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    54,    -1,    -1,    -1,
      58,    -1,   112,    -1,   114,   115,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,   158,    34,
      35,    36,   275,    -1,   112,    -1,   114,   115,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
     272,     3,     4,    58,     6,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
     158,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,   272,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    58,   112,    -1,   114,
     115,    -1,    13,    14,    15,    16,    17,    18,   248,   249,
      21,    22,    23,    24,    25,    26,    -1,    -1,   258,    -1,
      -1,   130,    -1,    -1,    -1,   265,    -1,   267,   268,    -1,
      -1,   271,   272,    -1,   274,    -1,    13,    14,    15,    16,
      17,    18,   151,   158,    21,    22,    23,    24,    25,    26,
     112,    -1,   114,     4,   163,   164,     0,    -1,    -1,   168,
     248,   249,    13,    14,    15,    16,    17,    18,    -1,    -1,
     258,    22,    -1,    -1,     3,     4,    -1,   265,    -1,   267,
     268,    -1,    -1,   271,    35,    -1,   274,    -1,    -1,    -1,
      34,    35,    -1,    22,    -1,    -1,   158,    -1,    27,    28,
      -1,    45,    46,    47,    -1,    34,    35,    36,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    -1,    -1,    -1,    58,
       3,     4,    -1,   248,   249,    -1,    13,    14,    15,    16,
      17,    18,    -1,   258,    21,    22,    23,    24,    25,    26,
     265,    -1,   267,   268,   263,    -1,   271,    -1,    -1,   274,
      -1,   112,    35,    36,    -1,    -1,   275,   111,   112,    -1,
     114,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    -1,   112,    -1,   114,   248,   249,    -1,    -1,
      -1,    15,    16,    17,    18,    -1,   258,    21,    22,    23,
      24,    25,    26,   265,    -1,   267,   268,    -1,    -1,   271,
     272,    -1,   274,     3,     4,    -1,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,   158,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,   112,
      -1,    -1,   115,    -1,    34,    35,    36,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,   274,    54,    -1,    22,    -1,    58,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    54,     9,
      10,    11,    58,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    -1,    -1,   248,
     249,   265,   112,   267,   114,   269,    -1,   271,    -1,   258,
       3,     4,    -1,    -1,    -1,    -1,   265,    -1,   267,   268,
      -1,    -1,   271,   272,    -1,   274,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    27,    28,   112,    -1,   114,    -1,
      -1,    34,    35,    36,    -1,     3,     4,    -1,   158,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    54,    -1,    -1,    22,    58,    -1,    -1,    -1,    27,
      28,    -1,    -1,    -1,    -1,   268,    34,    35,    36,   272,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    54,    -1,     3,     4,
      58,    11,    -1,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    22,    -1,   112,
      -1,   114,    27,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,   248,   249,
      45,    46,    47,    48,    49,    50,    51,    52,   258,    54,
      -1,    -1,    -1,    58,   112,   265,   114,   267,   268,    -1,
      -1,   271,   272,    -1,   274,   158,    -1,    -1,    -1,    -1,
      -1,    -1,   248,   249,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   258,    -1,    -1,    -1,     3,     4,    -1,   265,
      -1,   267,   268,    -1,    -1,   271,   272,    -1,   274,    -1,
     158,    -1,    -1,    -1,    -1,    22,    -1,   112,    -1,   114,
      27,    28,    -1,    -1,    -1,    -1,     4,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,
      -1,    -1,    -1,   158,    -1,   248,   249,    45,    46,    47,
      48,    49,    50,    51,    52,   258,    -1,    -1,    -1,    -1,
      -1,    -1,   265,    -1,   267,   268,    -1,    -1,   271,    -1,
      -1,   274,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
     248,   249,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,
     258,    -1,    -1,    -1,    -1,    -1,    22,   265,    -1,   267,
     268,    27,    28,   271,    -1,    -1,   274,    -1,    34,    35,
      36,    -1,    -1,    -1,   112,    -1,    -1,   115,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    54,    -1,
      -1,   158,    58,   248,   249,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   258,    -1,    -1,    -1,     3,     4,    -1,
     265,    -1,   267,   268,    -1,    -1,   271,    -1,    -1,   274,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    -1,     4,    -1,    -1,    -1,   112,    -1,   114,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    -1,    -1,     3,     4,
      -1,   248,   249,    45,    46,    47,    48,    49,    50,    51,
      52,   258,   158,    -1,    -1,    -1,    -1,    22,   265,    -1,
     267,   268,    27,    28,   271,    -1,    -1,   274,    -1,    34,
      35,    36,     3,     4,    -1,    -1,   112,    -1,   114,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
     268,    22,    -1,    58,   272,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
     112,    -1,    -1,   115,    45,    46,    47,    48,    49,    50,
      51,    52,   158,    54,    -1,    10,    11,    58,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    22,    23,    24,
      25,    26,   248,   249,    -1,    -1,    -1,   112,    -1,   114,
      -1,    -1,   258,     3,     4,    -1,    -1,    -1,    -1,   265,
      -1,   267,   268,    -1,    -1,   271,    -1,    -1,   274,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
      -1,   112,    -1,   114,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,   158,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,     4,    -1,    -1,    58,    -1,
      -1,    -1,   248,   249,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   258,    -1,    -1,    -1,    -1,   158,    -1,   265,
       3,   267,   268,    -1,    -1,   271,    35,    36,   274,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    27,    28,    -1,    -1,    -1,    -1,
      -1,    34,   112,    36,   114,    -1,   268,    -1,    -1,    -1,
     272,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    54,    -1,   248,   249,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   258,    -1,    -1,    -1,    -1,    -1,    -1,
     265,    -1,   267,   268,    -1,    -1,   271,    -1,   158,   274,
      -1,    -1,    -1,   112,    -1,    -1,   115,   248,   249,    -1,
      -1,    -1,     3,    -1,    -1,    -1,    -1,   258,    -1,    -1,
      -1,    -1,    -1,    -1,   265,    -1,   267,   268,    -1,   112,
     271,   114,   115,   274,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,     4,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,   248,   249,
      45,    46,    47,    48,    49,    50,    51,    52,   258,    -1,
      -1,    -1,    -1,    -1,    -1,   265,    -1,   267,   268,    -1,
      -1,   271,    -1,    -1,   274,    -1,    -1,    -1,    -1,    -1,
      -1,   112,    -1,   114,   115,     6,     7,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   268,
     115,    -1,    -1,   272,    -1,   248,   249,   158,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   258,    -1,    -1,    -1,    -1,
      -1,    -1,   265,    -1,   267,   268,    -1,    -1,   271,   272,
      -1,   274,     6,     7,     8,     9,    10,    11,    -1,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    22,    23,
      24,    25,    26,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,     6,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    -1,    -1,   248,   249,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,    -1,    -1,
      -1,    -1,    -1,    -1,   265,    -1,   267,   268,     4,    -1,
     271,   272,    -1,   274,     6,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    35,
      36,    -1,    -1,   268,    -1,    -1,    -1,   272,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    27,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    -1,    -1,    36,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,   115,
       8,     9,    10,    11,   275,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   112,     3,   114,   115,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26,   158,    -1,
      -1,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,
      -1,    -1,   275,    -1,    -1,    -1,     3,    -1,    -1,     6,
       7,     8,     9,    10,    11,    -1,    13,    14,    15,    16,
      17,    18,    -1,   275,    21,    22,    23,    24,    25,    26,
       3,    -1,    -1,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   268,    -1,    -1,    -1,   272,    -1,   248,   249,
      -1,    -1,    -1,   275,    -1,    -1,    -1,    -1,   258,    -1,
      -1,    -1,    -1,    -1,    -1,   265,    -1,   267,   268,   248,
     249,   271,    -1,    -1,   274,    -1,    -1,    -1,    -1,   258,
      -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,   267,   268,
      -1,    -1,   271,     3,    -1,   274,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,     3,    -1,    -1,
       6,     7,     8,     9,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      26,     3,    -1,    -1,     6,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,     3,    -1,    -1,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    22,    23,    24,    25,    26,     3,
      -1,    -1,     6,     7,     8,     9,    10,    11,    -1,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    22,    23,
      24,    25,    26,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,     6,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,     6,     7,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    22,    23,    24,    25,    26,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned short int
  Parser::yystos_[] =
  {
         0,     1,    56,   277,   278,     0,    34,    35,    45,    46,
      47,    55,   111,   112,   114,   265,   267,   269,   271,   280,
     281,   287,   288,   289,   290,   293,   294,   270,    13,    13,
     273,   274,   274,   274,   274,    13,    13,    13,   273,   274,
      13,    13,    35,   112,   113,   115,    56,   270,   279,    13,
       3,     4,    22,    27,    28,    34,    35,    36,    45,    46,
      47,    48,    49,    50,    51,    52,    54,    58,   112,   158,
     248,   249,   258,   265,   267,   268,   271,   274,   283,   285,
     292,   293,   295,   296,   297,   298,   299,   300,   303,   304,
     305,   306,   307,   309,   310,   311,   267,   268,   292,   295,
      35,   112,   286,     4,     4,     4,     4,   295,   295,   292,
     295,    35,   112,   286,     4,   295,   311,   292,   295,   272,
     272,     4,    22,   312,     4,   112,   312,   292,   295,   295,
       3,     4,   295,   295,   295,    13,    14,    15,    16,    17,
      18,   301,    21,    22,    23,    24,    25,    26,   274,   301,
     302,    13,   274,   301,   274,   274,   274,   274,   274,    13,
      13,    13,   274,     3,    13,    28,   302,   302,     3,   301,
     301,   302,     3,   274,     4,     4,   295,     4,     3,   301,
       3,     6,     7,     8,     9,    10,    11,    13,    14,    15,
      16,    17,    18,   302,     3,     3,    21,    22,    13,   273,
      13,   273,    13,   273,   275,   275,   275,   275,     3,     3,
      13,    13,    13,   275,   295,     3,   272,     4,     3,   272,
       3,     4,   272,   272,     3,     4,   272,     4,   112,   285,
       4,   284,   295,     4,   284,   295,   295,   284,   285,     4,
     295,     4,    35,   112,   311,     4,   295,     4,   295,     4,
     269,   295,     4,     4,     4,   295,   297,     4,   112,   285,
     112,   258,   285,    13,   295,   295,   112,   285,   284,   295,
     295,   295,   295,   295,     3,     3,     1,   275,   295,   284,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,    35,   304,   301,   311,   312,
     292,   295,    35,   112,   292,   295,    35,   112,   292,   295,
      35,   112,    13,    13,    13,    13,   295,   295,   292,   295,
     292,   295,   292,   295,    13,     1,     4,    22,    35,    36,
      45,    46,    47,    48,    49,    50,    51,    52,   112,   115,
     268,   282,   295,   299,   301,   302,   308,     1,    35,   282,
     295,   299,     1,    35,   272,   282,   291,   295,   272,     1,
     272,   282,   291,   295,   272,     3,   275,   275,   275,   275,
     275,   275,   275,   275,   275,     3,     3,     3,   112,   258,
     285,   275,     4,     4,   311,   312,   295,   295,   295,   295,
     295,   272,   112,   115,   112,   115,   272,   274,   295,   299,
     112,   115,     4,    35,    36,    45,    46,    47,    48,    49,
      50,    51,    52,   112,   115,   268,   272,   308,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   295,   272,
     295,   272,   272,   272,   272,     4,   112,    13,   295,   295,
     295,   310,   311,     3,   272,   275,   272,   275,     4,   295,
     275,     3,     3,   295,   295,   295,   275,   275
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,    44,   258,   259,   260,   261,   262,   124,
     263,    38,   264,    61,   265,    62,    60,   266,   267,   268,
     269,    43,    45,    42,    47,    37,   270,   126,    33,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,    91,    93,    46,    40,    41
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned short int
  Parser::yyr1_[] =
  {
         0,   276,   278,   277,   277,   277,   277,   279,   279,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   283,
     283,   284,   284,   284,   284,   285,   285,   285,   285,   285,
     285,   286,   286,   286,   286,   286,   286,   287,   287,   287,
     287,   288,   288,   289,   289,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   291,
     291,   292,   292,   293,   293,   294,   294,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   296,
     296,   296,   296,   297,   297,   298,   298,   298,   298,   298,
     298,   298,   298,   299,   300,   300,   300,   300,   300,   300,
     301,   301,   301,   301,   301,   301,   302,   302,   302,   302,
     302,   302,   303,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   305,   305,   305,   305,   306,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   309,   309,   309,   309,   309,   309,   309,   310,   310,
     310,   310,   311,   311,   311,   312
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     1,     3,     1,     1,     1,     4,
       6,     6,     6,     6,     6,     4,     6,     6,     6,     6,
       6,     1,     6,     6,     6,     5,     4,     5,     6,     6,
       6,     6,     5,     4,     5,     6,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       5,     4,     3,     1,     1,     0,     3,     6,     1,     2,
       3,     4,     4,     3,     3,     5,     5,     5,     5,     5,
       5,     6,     3,     3,     5,     5,     5,     5,     5,     5,
       3,     3,     6,     6,     6,     3,     3,     3,     3,     2,
       2,     3,     3,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     2,     1,     1,
       1,     2,     6,     3,     3,     3,     1,     1,     3,     8,
       8,     8,     8,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     3,     3,     3,     4,     3,
       3,     3,     3,     3,     5,     5,     5,     5,     3,     4,
       4,     4,     6,     1,     4,     3,     4,     3,     3,     3,
       3,     6,     3,     6,     3,     6,     6,     4,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     4,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "','", "NUMBER",
  "LOGICAL_OPERATORS", "CMD_LOGXOR", "CMD_LOGAND", "CMD_LOGOR", "'|'",
  "CMD_XOR", "'&'", "CMD_ASSIGN", "'='", "CMD_NOTEQ", "'>'", "'<'",
  "CMD_GREATERTHANEQ", "CMD_LESSTHANEQ", "COMP_OPERATORS",
  "MATH_OPERATORS", "'+'", "'-'", "'*'", "'/'", "'%'", "CMD_SQUARE", "'~'",
  "'!'", "UPLUS", "UMINUS", "LN", "FLOOR", "EXP", "KEYWORD",
  "KEY_IDENTIFIER", "FUNC_IDENTIFIER", "EXPRESSIONLIST", "SELFANIMEXIST",
  "PROJCANCELTIME", "PLAYERIDEXIST", "PROJGUARDEDTIME", "PROJCONTACTTIME",
  "VAR", "TAN", "FUNC_FVAR", "FUNC_VAR", "FUNC_SYSVAR", "FUNC_CONST",
  "FUNC_LOG", "FUNC_PROJGUARDED", "FUNC_PROJHIT", "FUNC_PROJCONTACT",
  "KANIM", "FUNC_IFELSE", "KEY_TRIGGER", "\"end of line\"", "ID",
  "QUOTESTRING", "NEGONE", "DATA", "ATTACK", "DEFENCE", "FALLDEFUP",
  "LIEDOWTIME", "AIRJUGGLE", "SPARKNO", "GUARDSPARKNO", "KOECHO", "VOLUME",
  "INTEGERINDEX", "FLOATINDEX", "SIZE", "XSCALE", "YSCALE", "GROUNDBACK",
  "GROUNDFRONT", "AIRBACK", "AIRFRONT", "HEIGHT", "ATTACKDIST",
  "PROJATTDIST", "PROJDOSCALE", "HEADPOSX", "HEADPOSY", "MIDPOSX",
  "MIDPOSY", "SHADOWOFFSET", "DRAWOFFSETX", "DRAWOFFSETY", "VELOCITY",
  "WALKFWD", "WALKBACK", "RUNFWDX", "RUNFWDY", "RUNBACKX", "RUNBACKY",
  "JUMPNEU", "JUMPBACK", "JUMPFWD", "RUNJUMPBACK", "RUNJUMPFWD",
  "AIRJUMPNEU", "AIRJUMPBACK", "AIRJUMPFWD", "MOVEMENT", "AIRJUMPNUM",
  "AIRJUMPHEIGHT", "YACCEL", "STANDFRICTION", "CROUCHFRICTION",
  "KEY_TRIGGERALL", "IDENTIFIER", "CMD_STATEDEF", "KEY_PHYSICS",
  "CMD_STATE", "ANIMELEM", "FVAR", "HITCOUNT", "HITDEFATTR", "ISHELPER",
  "MOVECONTACT", "PROJGUARDED", "PROJHITTIME", "STATENO", "TNULL",
  "AFTERIMAGE", "AFTERIMAGETIME", "ALLPALFX", "ANGLEADD", "ANGLEDRAW",
  "ANGLEMUL", "ANGLESET", "APPENDTOCLIPBOARD", "ASSERTSPECIAL",
  "ATTACKMULSET", "BGPALFX", "BINDTOPARENT", "BINDTOROOT", "BINDTOTARGET",
  "CHANGEANIME", "CHANGEANIME2", "CHANGESTATE", "CLEARCLIPBOARD",
  "CTRLSET", "DEFENCEMULSET", "DESTROYSELF", "DISPLAYTOCLIPBOARD",
  "ENVSHAKE", "EXPLOD", "EXPLODBINDTIME", "FALLENVSHAKE", "FORCEFEDDBACK",
  "GAMEMAKEANIM", "GRAVITY", "HELPER", "HITADD", "HITBY", "KEY_HITDEF",
  "HITFALLDAMAGE", "HITFALLSET", "HITFALLVEL", "HITOVERRIDE", "HITVELSET",
  "LIFEADD", "LIFESET", "MAKEDUST", "MODIFYEXPLOD", "MOVEHITRESET",
  "NOTHITBY", "NUL", "OFFSET", "PALFX", "PARENTVARADD", "PARENTVARSET",
  "PAUSE", "PLAYERPUSH", "PLAYSND", "POSADD", "POSFREEZ", "POSSET",
  "POWERSET", "PROJECTILE", "REMOVEEXPLOD", "REVERSALDEF", "SCREENBOUND",
  "SELFSTATE", "SNDPAN", "STATETYPESET", "STOPSND", "SUPERPAUSE",
  "TARGETBIND", "TARGETDROP", "TARGETFACING", "TARGETLIFEADD",
  "TARGETPOWERADD", "TARGETSTATE", "TARGETVELADD", "TARGETVELSET", "TURN",
  "VARADD", "VARRANDOM", "VARRANGESET", "VARSET", "VELADD", "VELMUL",
  "WIDTH", "LENGTH", "PALCOLOR", "PALINVERTALL", "PALBRIGHT",
  "PALCONTRAST", "PALPOSTBRIGHT", "PALADD", "PALMUL", "TIMEGAP",
  "FRAMEGAP", "TRANS", "ACBEGIN", "ACTION", "LOOPSTART", "CLSN2DEFAULT",
  "CLSN1DEFAULT", "CLSN2", "CLSN1", "HORIZONTALFLIP", "VERTIKALFLIP",
  "HVFLIP", "ALPHA", "INFO", "DISPLAYNAME", "VERSIONSDATA", "MUGENVERSION",
  "AUTHOR", "FILES", "CMD", "CNS", "ST", "STCOMMON", "SPRITE", "SOUND",
  "PAL", "PALDEF", "ARCADE", "INTROSTORYBOARD", "ENDINGSTORYBOARD",
  "JUMPNEUY", "AIRJUMPNEUY", "KEY_FX", "KEY_SX", "CMD_KEY_DOWN",
  "CMD_KEY_FORWARD", "CMD_KEY_DOWN_FORWARD", "CMD_KEY_BACK",
  "CMD_KEY_DOWN_BACK", "CMD_KEY_UP_FORWARD", "CMD_KEY_UP",
  "CMD_KEY_UP_BACK", "CMD_BUTTON_A", "CMD_BUTTON_B", "CMD_BUTTON_C",
  "CMD_BUTTON_X", "CMD_BUTTON_Y", "CMD_BUTTON_Z", "CMD_BUTTON_S",
  "KEY_STATETYPE", "KEY_TYPE", "KEY_ANIM",
  "TRIGGER_REDIRECTION_IDENTIFIER", "CONST_PARAM", "COMMENT", "'['", "']'",
  "'.'", "'('", "')'", "$accept", "lines", "$@1", "end_or_comment",
  "STATEDEFSECTION", "STATESECTION", "identificator_list", "number_list",
  "number_comma_list", "identificator_comma_list",
  "identificator_dot_list", "TRIGGERSECTION", "ANIMSECTION",
  "COMMANDSECTION", "command_identifier", "expression_list",
  "expression_comma_list", "common_names", "ident_section", "expression",
  "function_if_else", "key_anim_expression", "logical_expression",
  "math_expression", "compare_expression", "compare_operators",
  "math_operators", "keyword_comma_list", "keywords", "range",
  "func_comparator", "functions", "func_identifiers", "hitdef",
  "simple_value", "super_simple_value", "negative_number", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
       277,     0,    -1,    -1,   278,   270,    -1,    56,    -1,   277,
     280,   279,    -1,     1,    -1,    56,    -1,   270,    -1,   271,
     113,     4,   272,    -1,   271,   113,     4,     3,   295,   272,
      -1,   271,   113,     4,     3,   299,   272,    -1,   271,   113,
       4,     3,   282,   272,    -1,   271,   113,     4,     3,    35,
     272,    -1,   271,   113,     4,     3,     1,   272,    -1,   271,
     113,   312,   272,    -1,   271,   113,   312,     3,   295,   272,
      -1,   271,   113,   312,     3,   299,   272,    -1,   271,   113,
     312,     3,   282,   272,    -1,   271,   113,   312,     3,    35,
     272,    -1,   271,   113,   312,     3,     1,   272,    -1,   281,
      -1,   271,   115,     4,     3,   295,   272,    -1,   271,   115,
       4,     3,   282,   272,    -1,   271,   115,     4,     3,   291,
     272,    -1,   271,   115,     4,     4,   272,    -1,   271,   115,
       4,   272,    -1,   271,   115,     4,     3,   272,    -1,   271,
     115,     4,     3,     1,   272,    -1,   271,   115,   312,     3,
     295,   272,    -1,   271,   115,   312,     3,   282,   272,    -1,
     271,   115,   312,     3,   291,   272,    -1,   271,   115,   312,
       4,   272,    -1,   271,   115,   312,   272,    -1,   271,   115,
     312,     3,   272,    -1,   271,   115,   312,     3,     1,   272,
      -1,   271,   115,   112,   272,    -1,   289,    -1,   287,    -1,
     288,    -1,   295,    -1,   268,    -1,   302,    -1,   115,    -1,
     308,    -1,   301,    -1,   112,   112,    -1,   112,   115,    -1,
       4,   112,    -1,     4,   115,    -1,    35,   112,    -1,    35,
     115,    -1,    35,   299,    -1,   282,   115,    -1,   282,   112,
      -1,   282,   308,    -1,   282,     4,    -1,   282,    35,    -1,
     282,   268,    -1,     4,     4,    -1,   283,     4,    -1,     4,
       3,     4,    -1,     4,     3,   112,    -1,   284,     3,     4,
      -1,   284,     3,   112,    -1,   258,     3,   112,    -1,   112,
       3,   112,    -1,   112,     3,     4,    -1,   258,     3,   285,
      -1,   112,     3,   285,    -1,     4,     3,   285,    -1,   112,
     273,   112,    -1,   112,   273,    35,    -1,    35,   273,    35,
      -1,    35,   273,   112,    -1,   286,   273,   112,    -1,   286,
     273,    35,    -1,    55,    13,   295,    -1,   111,    13,   295,
      -1,    55,    13,   295,     3,   295,    -1,   111,    13,   295,
       3,   295,    -1,   267,    13,   311,   295,    -1,   267,    13,
     295,    -1,   290,    -1,   294,    -1,    -1,    35,    13,   267,
      -1,    35,   274,     4,   275,    13,   295,    -1,    35,    -1,
      35,    13,    -1,    35,    13,   295,    -1,    35,    13,   295,
      22,    -1,    35,    13,   295,    21,    -1,    35,    13,   292,
      -1,    35,    13,   268,    -1,    35,   273,    35,    13,   295,
      -1,    35,   273,    35,    13,   292,    -1,    35,   273,   286,
      13,   295,    -1,    35,   273,   286,    13,   292,    -1,    35,
     273,   112,    13,   295,    -1,    35,   273,   112,    13,   292,
      -1,   112,   274,     4,   275,    13,   295,    -1,   112,    13,
     295,    -1,   112,    13,   292,    -1,   112,   273,   112,    13,
     295,    -1,   112,   273,   112,    13,   292,    -1,   112,   273,
      35,    13,   295,    -1,   112,   273,    35,    13,   292,    -1,
     112,   273,   286,    13,   295,    -1,   112,   273,   286,    13,
     292,    -1,   293,    13,   295,    -1,   293,    13,   292,    -1,
      47,   274,     4,   275,    13,   295,    -1,    46,   274,     4,
     275,    13,   295,    -1,    45,   274,     4,   275,    13,   295,
      -1,    34,    13,   295,    -1,    34,    13,   292,    -1,   269,
      13,   295,    -1,   269,    13,   292,    -1,   295,   295,    -1,
     291,   295,    -1,   295,     3,   295,    -1,   292,     3,   295,
      -1,   114,    -1,   265,    -1,   271,   112,   272,    -1,   271,
      35,   272,    -1,   309,    -1,   307,    -1,   296,    -1,   297,
      -1,   299,    -1,   300,    -1,   298,    -1,   285,    -1,   274,
     295,   275,    -1,   274,   295,     1,    -1,    22,   295,    -1,
     283,    -1,   310,    -1,   311,    -1,     3,   295,    -1,   268,
     274,   295,   275,     3,   295,    -1,   268,     3,   295,    -1,
     248,   302,   295,    -1,   249,   302,   295,    -1,   248,    -1,
     249,    -1,    35,    13,   295,    -1,    54,   274,   295,     3,
     295,     3,   295,   275,    -1,    54,   274,   297,     3,   295,
       3,   295,   275,    -1,    54,   274,   297,     3,   310,     3,
     310,   275,    -1,    54,   274,   297,     3,   311,     3,   311,
     275,    -1,   267,   301,   295,    -1,   267,   302,   295,    -1,
      27,   295,    -1,    28,   295,    -1,   295,    11,   295,    -1,
     295,     9,   295,    -1,   295,    10,   295,    -1,   295,     7,
     295,    -1,   295,     8,   295,    -1,   295,     6,   295,    -1,
     295,   302,   295,    -1,   295,    13,   295,    -1,   295,    14,
     295,    -1,   295,    15,   295,    -1,   295,    16,   295,    -1,
     295,    18,   295,    -1,   295,    17,   295,    -1,    13,    -1,
      14,    -1,    15,    -1,    16,    -1,    18,    -1,    17,    -1,
      21,    -1,    22,    -1,    24,    -1,    23,    -1,    25,    -1,
      26,    -1,   304,     3,   304,    -1,    34,    -1,    34,   301,
     295,    -1,    34,   301,   284,    -1,   265,   301,   295,    -1,
     265,   301,   284,    -1,    35,   274,     4,   275,    -1,    35,
     301,   284,    -1,    35,   301,   295,    -1,    35,   302,   295,
      -1,   293,   301,   295,    -1,   293,   301,   284,    -1,   271,
       4,     3,     4,   272,    -1,   274,     4,     3,     4,   275,
      -1,   271,     4,     3,     4,   275,    -1,   274,     4,     3,
       4,   272,    -1,    36,   301,   311,    -1,    36,   274,   295,
     275,    -1,    36,   274,     4,   275,    -1,    48,   274,   269,
     275,    -1,    49,   274,   295,     3,   295,   275,    -1,   306,
      -1,   306,     3,   301,   311,    -1,   306,     3,   311,    -1,
     306,     3,   301,   312,    -1,   306,     3,   312,    -1,    36,
      13,   284,    -1,    36,    13,   285,    -1,    52,    13,     4,
      -1,    52,    13,     4,     3,   301,   295,    -1,    50,    13,
       4,    -1,    50,    13,     4,     3,   301,   295,    -1,    51,
      13,     4,    -1,    51,    13,     4,     3,   301,   295,    -1,
      47,   274,     4,   275,    13,   295,    -1,    47,   274,     4,
     275,    -1,    45,   274,   295,   275,    -1,    45,   274,     4,
     275,    -1,    46,   274,   295,   275,    -1,    46,   274,     4,
     275,    -1,    36,    -1,    48,    -1,    49,    -1,    52,    -1,
      50,    -1,    51,    -1,    47,    -1,    45,    -1,    46,    -1,
     158,    -1,   158,    13,   112,    -1,   158,    13,   285,    -1,
     158,    28,    13,   112,    -1,   158,    28,    13,   285,    -1,
     158,    13,   258,    -1,   158,    28,    13,   258,    -1,   304,
      -1,   303,    -1,   305,    -1,    58,    -1,     4,    -1,    35,
      -1,   112,    -1,    22,     4,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     9,    13,    15,    17,    19,
      24,    31,    38,    45,    52,    59,    64,    71,    78,    85,
      92,    99,   101,   108,   115,   122,   128,   133,   139,   146,
     153,   160,   167,   173,   178,   184,   191,   196,   198,   200,
     202,   204,   206,   208,   210,   212,   214,   217,   220,   223,
     226,   229,   232,   235,   238,   241,   244,   247,   250,   253,
     256,   259,   263,   267,   271,   275,   279,   283,   287,   291,
     295,   299,   303,   307,   311,   315,   319,   323,   327,   331,
     337,   343,   348,   352,   354,   356,   357,   361,   368,   370,
     373,   377,   382,   387,   391,   395,   401,   407,   413,   419,
     425,   431,   438,   442,   446,   452,   458,   464,   470,   476,
     482,   486,   490,   497,   504,   511,   515,   519,   523,   527,
     530,   533,   537,   541,   543,   545,   549,   553,   555,   557,
     559,   561,   563,   565,   567,   569,   573,   577,   580,   582,
     584,   586,   589,   596,   600,   604,   608,   610,   612,   616,
     625,   634,   643,   652,   656,   660,   663,   666,   670,   674,
     678,   682,   686,   690,   694,   698,   702,   706,   710,   714,
     718,   720,   722,   724,   726,   728,   730,   732,   734,   736,
     738,   740,   742,   746,   748,   752,   756,   760,   764,   769,
     773,   777,   781,   785,   789,   795,   801,   807,   813,   817,
     822,   827,   832,   839,   841,   846,   850,   855,   859,   863,
     867,   871,   878,   882,   889,   893,   900,   907,   912,   917,
     922,   927,   932,   934,   936,   938,   940,   942,   944,   946,
     948,   950,   952,   956,   960,   965,   970,   974,   979,   981,
     983,   985,   987,   989,   991,   993
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   412,   412,   412,   414,   415,   416,   420,   421,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     462,   463,   464,   465,   466,   467,   468,   469,   471,   472,
     474,   475,   476,   478,   479,   480,   481,   482,   483,   487,
     488,   493,   494,   495,   496,   500,   501,   502,   503,   504,
     505,   509,   510,   511,   512,   513,   514,   517,   518,   519,
     520,   523,   531,   539,   540,   543,   544,   549,   550,   557,
     558,   563,   570,   577,   578,   580,   581,   583,   584,   587,
     588,   592,   594,   595,   597,   598,   600,   601,   604,   605,
     608,   609,   611,   612,   613,   615,   616,   618,   619,   624,
     625,   629,   630,   633,   634,   637,   638,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   665,   669,   671,   679,   683,   684,   685,   688,
     689,   690,   691,   695,   696,   703,   704,   705,   706,   707,
     708,   709,   710,   715,   719,   720,   721,   722,   723,   724,
     728,   729,   730,   731,   732,   733,   735,   736,   737,   738,
     739,   740,   744,   748,   749,   750,   752,   753,   755,   756,
     757,   758,   760,   761,   765,   766,   767,   768,   773,   786,
     790,   791,   792,   793,   819,   848,   879,   907,   936,   937,
     938,   942,   947,   951,   956,   960,   965,   966,   967,   968,
     969,   970,   973,   974,   975,   976,   977,   978,   979,   980,
     981,   985,   986,   987,  1019,  1020,  1052,  1053,  1057,  1058,
    1059,  1060,  1063,  1064,  1065,  1068
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,     2,     2,    25,    11,     2,
     274,   275,    23,    21,     3,    22,   273,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      16,    13,    15,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   271,     2,   272,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     9,     2,    27,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,     7,     8,    10,    12,    14,    17,    18,    19,    20,
      26,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 2567;
  const int Parser::yynnts_ = 37;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 5;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 276;

  const unsigned int Parser::yyuser_token_number_max_ = 512;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // CmdCompiler

/* Line 1054 of lalr1.cc  */
#line 4158 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.cc"


/* Line 1056 of lalr1.cc  */
#line 1077 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"

// Error function throws an exception (string) with the location and error message
void CmdCompiler::Parser::error(const Parser::location_type& l,
			    const string& m)
{
    driver.error(l, m);
}


#undef bugon



