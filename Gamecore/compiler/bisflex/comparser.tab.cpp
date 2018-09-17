
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
#define yylex   ComCompilerlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 6 "..\\comcompiler\\comparser.y"
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

#include "com_driver.h"

#define bugon(a) if ((a)){ printf("parsing bug at %s:%d\n", __FILE__, __LINE__); }




/* Line 311 of lalr1.cc  */
#line 66 "comparser.tab.c"


#include "comparser.tab.h"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 365 "..\\comcompiler\\comparser.y"


#include "com_driver.h"
#include "scanner.h"
#include "../../util/SGF_Debug.h"
/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 89 "comparser.tab.c"

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

namespace ComCompiler {

/* Line 380 of lalr1.cc  */
#line 158 "comparser.tab.c"
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
        case 33: /* "KEY_TIME" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 265 "comparser.tab.c"
	break;
      case 34: /* "KEY_BUFFERTIME" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 274 "comparser.tab.c"
	break;
      case 35: /* "KEY_NAME" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 283 "comparser.tab.c"
	break;
      case 36: /* "KEYWORD" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 292 "comparser.tab.c"
	break;
      case 37: /* "KEY_IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 301 "comparser.tab.c"
	break;
      case 38: /* "FUNC_GETHITVAR" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 310 "comparser.tab.c"
	break;
      case 39: /* "FUNC_IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 319 "comparser.tab.c"
	break;
      case 47: /* "FUNC_FVAR" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 328 "comparser.tab.c"
	break;
      case 48: /* "FUNC_VAR" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 337 "comparser.tab.c"
	break;
      case 49: /* "FUNC_SYSVAR" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 346 "comparser.tab.c"
	break;
      case 50: /* "FUNC_CONST" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 355 "comparser.tab.c"
	break;
      case 51: /* "FUNC_LOG" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 364 "comparser.tab.c"
	break;
      case 57: /* "KEY_TRIGGER" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 373 "comparser.tab.c"
	break;
      case 60: /* "QUOTESTRING" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 382 "comparser.tab.c"
	break;
      case 113: /* "KEY_TRIGGERALL" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 391 "comparser.tab.c"
	break;
      case 114: /* "IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 400 "comparser.tab.c"
	break;
      case 115: /* "CMD_STATEDEF" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 409 "comparser.tab.c"
	break;
      case 116: /* "KEY_PHYSICS" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 418 "comparser.tab.c"
	break;
      case 117: /* "CMD_STATE" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 427 "comparser.tab.c"
	break;
      case 121: /* "HITDEFATTR" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 436 "comparser.tab.c"
	break;
      case 160: /* "KEY_HITDEF" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 445 "comparser.tab.c"
	break;
      case 252: /* "CMD_KEY_DOWN" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 454 "comparser.tab.c"
	break;
      case 253: /* "CMD_KEY_FORWARD" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 463 "comparser.tab.c"
	break;
      case 254: /* "CMD_KEY_DOWN_FORWARD" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 472 "comparser.tab.c"
	break;
      case 255: /* "CMD_KEY_BACK" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 481 "comparser.tab.c"
	break;
      case 256: /* "CMD_KEY_DOWN_BACK" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 490 "comparser.tab.c"
	break;
      case 257: /* "CMD_KEY_UP_FORWARD" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 499 "comparser.tab.c"
	break;
      case 258: /* "CMD_KEY_UP" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 508 "comparser.tab.c"
	break;
      case 259: /* "CMD_KEY_UP_BACK" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 517 "comparser.tab.c"
	break;
      case 260: /* "CMD_BUTTON_A" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 526 "comparser.tab.c"
	break;
      case 261: /* "CMD_BUTTON_B" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 535 "comparser.tab.c"
	break;
      case 262: /* "CMD_BUTTON_C" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 544 "comparser.tab.c"
	break;
      case 263: /* "CMD_BUTTON_X" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 553 "comparser.tab.c"
	break;
      case 264: /* "CMD_BUTTON_Y" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 562 "comparser.tab.c"
	break;
      case 265: /* "CMD_BUTTON_Z" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 571 "comparser.tab.c"
	break;
      case 266: /* "CMD_BUTTON_S" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 580 "comparser.tab.c"
	break;
      case 267: /* "KEY_COMMAND" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 589 "comparser.tab.c"
	break;
      case 268: /* "KEY_DEFAULTS" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 598 "comparser.tab.c"
	break;
      case 269: /* "KEY_STATETYPE" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 607 "comparser.tab.c"
	break;
      case 270: /* "KEY_TYPE" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 616 "comparser.tab.c"
	break;
      case 271: /* "KEY_ANIM" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 625 "comparser.tab.c"
	break;
      case 272: /* "HELPER_IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 634 "comparser.tab.c"
	break;
      case 273: /* "CONST_PARAM" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 643 "comparser.tab.c"
	break;
      case 274: /* "COMMENT" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 652 "comparser.tab.c"
	break;
      case 292: /* "key_modifier" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 661 "comparser.tab.c"
	break;
      case 294: /* "plain_key" */

/* Line 480 of lalr1.cc  */
#line 361 "..\\comcompiler\\comparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 670 "comparser.tab.c"
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
#line 46 "..\\comcompiler\\comparser.y"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 756 "comparser.tab.c"

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
#line 382 "..\\comcompiler\\comparser.y"
    {driver.clear_stack ();}
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 383 "..\\comcompiler\\comparser.y"
    {driver.clear_stack ();}
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 384 "..\\comcompiler\\comparser.y"
    {driver.clear_stack ();}
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 385 "..\\comcompiler\\comparser.y"
    {}
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 386 "..\\comcompiler\\comparser.y"
    {/*yyclearin;*/ driver.clear_stack (); SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 395 "..\\comcompiler\\comparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(1, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 396 "..\\comcompiler\\comparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(2, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 397 "..\\comcompiler\\comparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(3, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 398 "..\\comcompiler\\comparser.y"
    {(yyval.cvalue)=driver.Ast->makeRange(4, (yysemantic_stack_[(5) - (2)].doubleVal),(yysemantic_stack_[(5) - (4)].doubleVal));}
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 403 "..\\comcompiler\\comparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *)(yyval.cvalue)); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 404 "..\\comcompiler\\comparser.y"
    {driver.cvalues->push(driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal))); /*colocar o hitflag depois do quotestring como value */}
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 405 "..\\comcompiler\\comparser.y"
    {driver.cvalues->push(driver.Ast->makeNumber((yysemantic_stack_[(1) - (1)].doubleVal)));}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 406 "..\\comcompiler\\comparser.y"
    {driver.cvalues->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal))); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 407 "..\\comcompiler\\comparser.y"
    {driver.cvalues->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal))); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 408 "..\\comcompiler\\comparser.y"
    {driver.cvalues->push(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal))); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 419 "..\\comcompiler\\comparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].stringVal)); driver.Ast->iskey(); }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 420 "..\\comcompiler\\comparser.y"
    { driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 425 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: KeyCommand=Keylist: address[ "<<(yysemantic_stack_[(3) - (3)].cvalue)<< " ]"<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.Ast->makeKeyList());}
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 428 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: TIME: "<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.cvalues->pop());}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 431 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: BUFFERTIME "<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.cvalues->pop());}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 434 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "BISON: NAME "<<endl;
								driver.Ast->makeAttribute(driver.Ast->makeIdentifierSimple((yysemantic_stack_[(3) - (1)].stringVal)),driver.cvalues->pop());
								}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 446 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Super key: WILL add modified key to vector "<<endl;
								(yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue);driver.Ast->addKeyToList((SGF::Ast::CKey *)(yyval.cvalue));  
								}
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 450 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Super key: WILL add combined key to vector "<<endl;
								(yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue); driver.Ast->addKeyToList((SGF::Ast::CKey *)(yyval.cvalue)) ; }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 453 "..\\comcompiler\\comparser.y"
    {
								SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Super key: WILL MAKE CKey and add to vector "<<endl;
								(yyval.cvalue)=driver.Ast->makeKey((yysemantic_stack_[(1) - (1)].stringVal));driver.Ast->addKeyToList((SGF::Ast::CKey *)(yyval.cvalue));  
								}
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 461 "..\\comcompiler\\comparser.y"
    { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Apply modifier to key " <<endl;
											(yyval.cvalue)=	driver.Ast->applyKeyModifiers(driver.Ast->makeKey((yysemantic_stack_[(2) - (2)].stringVal)));}
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 466 "..\\comcompiler\\comparser.y"
    { SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "rule super key modifier "<<endl;}
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 467 "..\\comcompiler\\comparser.y"
    {
														SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "More than one key modifier "<<endl;
														}
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 473 "..\\comcompiler\\comparser.y"
    { driver.Ast->addReleaseKeyModifier(); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 474 "..\\comcompiler\\comparser.y"
    { driver.Ast->addReleaseKeyModifier((yysemantic_stack_[(2) - (2)].doubleVal)); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 475 "..\\comcompiler\\comparser.y"
    { driver.Ast->addHeldDownKeyModifier(); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 476 "..\\comcompiler\\comparser.y"
    { driver.Ast->addDirectionKeyModifier(); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 477 "..\\comcompiler\\comparser.y"
    { driver.Ast->addOnlyKeyModifier(); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 482 "..\\comcompiler\\comparser.y"
    { 
								(yyval.cvalue)=driver.Ast->makeKeyCombined((yysemantic_stack_[(3) - (1)].stringVal),(yysemantic_stack_[(3) - (3)].stringVal));
								}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 485 "..\\comcompiler\\comparser.y"
    { (yyval.cvalue)=driver.Ast->addCombinedKey((SGF::Ast::CKey *)(yysemantic_stack_[(3) - (1)].cvalue),(yysemantic_stack_[(3) - (3)].stringVal));}
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 488 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 489 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 490 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 491 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 492 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 493 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 494 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 495 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 496 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 497 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 498 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 499 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 500 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 501 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 502 "..\\comcompiler\\comparser.y"
    { (yyval.stringVal)=(yysemantic_stack_[(1) - (1)].stringVal); driver.Ast->iskey();}
    break;



/* Line 678 of lalr1.cc  */
#line 1240 "comparser.tab.c"
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
  const short int Parser::yypact_ninf_ = -271;
  const short int
  Parser::yypact_[] =
  {
         5,  -271,  -271,     0,  -270,  -271,    -1,     4,     6,     7,
    -255,   -56,  -271,  -271,     1,     1,     1,    -5,  -253,  -252,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,    21,    22,
    -271,  -271,  -271,  -271,    23,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,    25,  -271,    -5,  -271,     8,     9,
    -271,  -271,    26,    29,  -271,    -5,  -271,  -271,  -213,  -213,
      32,    33,  -271,  -271,  -271,  -269,  -268,  -271,  -271,  -271,
    -271
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     6,     4,    22,     0,     1,     0,     0,     0,     0,
       0,     0,    21,     3,     0,     0,     0,     0,     0,     0,
       7,     8,     5,    15,    16,    14,    17,    18,     0,     0,
      13,    24,    25,    26,    35,    39,    37,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    38,    23,    27,    29,     0,    33,    30,    31,
      19,    20,     0,     0,    36,     0,    34,    32,     0,     0,
       0,     0,    28,    41,    40,     0,     0,     9,    11,    12,
      10
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -271,  -271,  -271,  -271,  -271,     2,  -271,  -271,   -11,  -271,
    -271,  -271,     3,  -271,   -53
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,    22,    30,    31,    11,    12,    53,    54,
      55,    56,    57,    58,    59
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -3;
  const signed char
  Parser::yytable_[] =
  {
         5,    34,    20,    67,    13,    23,     1,    77,    79,    78,
      80,    35,    18,    19,    14,    73,    74,    32,    33,    15,
      36,    16,    17,    60,    61,    62,    63,    64,    65,    70,
      68,    69,    71,     6,     7,     8,    75,    76,    24,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    72,     0,     0,     0,     0,    66,
       0,    25,     0,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,     0,     0,     0,     9,     0,     0,
       0,     0,    27,     0,    52,    10,    28,     0,    29,    -2
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         0,     6,    58,    56,   274,     4,     1,   276,   276,   278,
     278,    16,   267,   268,    15,    68,    69,    15,    16,    15,
      25,    15,    15,   276,   276,     4,     4,     4,     3,     3,
      22,    22,     3,    33,    34,    35,     4,     4,    37,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,    65,    -1,    -1,    -1,    -1,    56,
      -1,    60,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,
      -1,    -1,   271,    -1,   279,   275,   275,    -1,   277,   274
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned short int
  Parser::yystos_[] =
  {
         0,     1,    58,   281,   282,     0,    33,    34,    35,   267,
     275,   286,   287,   274,    15,    15,    15,    15,   267,   268,
      58,   274,   283,     4,    37,    60,   114,   271,   275,   277,
     284,   285,   285,   285,     6,    16,    25,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   279,   288,   289,   290,   291,   292,   293,   294,
     276,   276,     4,     4,     4,     3,   292,   294,    22,    22,
       3,     3,   288,   294,   294,     4,     4,   276,   278,   276,
     278
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,    44,   258,   259,   126,    33,    38,   124,
     260,   261,   262,   263,   264,    61,    62,    60,   265,   266,
     267,   268,    43,    45,    42,    47,    37,   269,   270,   271,
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
     512,   513,   514,   515,   516,    91,    93,    40,    41,    36
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned short int
  Parser::yyr1_[] =
  {
         0,   280,   282,   281,   281,   281,   281,   283,   283,   284,
     284,   284,   284,   285,   285,   285,   285,   285,   285,   286,
     286,   286,   287,   287,   287,   287,   287,   288,   288,   289,
     289,   289,   290,   291,   291,   292,   292,   292,   292,   292,
     293,   293,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     1,     3,     1,     1,     1,     5,
       5,     5,     5,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     0,     3,     3,     3,     3,     1,     3,     1,
       1,     1,     2,     1,     2,     1,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "','", "NUMBER",
  "LOGICAL_OPERATORS", "'~'", "'!'", "'&'", "'|'", "CMD_XOR", "CMD_LOGXOR",
  "CMD_LOGOR", "CMD_LOGAND", "COMP_OPERATORS", "'='", "'>'", "'<'",
  "CMD_GREATERTHANEQ", "CMD_LESSTHANEQ", "CMD_NOTEQ", "MATH_OPERATORS",
  "'+'", "'-'", "'*'", "'/'", "'%'", "CMD_SQUARE", "LN", "FLOOR", "EXP",
  "UPLUS", "UMINUS", "KEY_TIME", "KEY_BUFFERTIME", "KEY_NAME", "KEYWORD",
  "KEY_IDENTIFIER", "FUNC_GETHITVAR", "FUNC_IDENTIFIER", "SELFANIMEXIST",
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
  "KEY_COMMAND", "KEY_DEFAULTS", "KEY_STATETYPE", "KEY_TYPE", "KEY_ANIM",
  "HELPER_IDENTIFIER", "CONST_PARAM", "COMMENT", "'['", "']'", "'('",
  "')'", "'$'", "$accept", "lines", "$@1", "end_or_comment", "range",
  "simple_value", "COMMANDSECTION", "command_identifier", "keylist",
  "super_key", "key_modified", "super_key_modifier", "key_modifier",
  "combined_key", "plain_key", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
       281,     0,    -1,    -1,   282,   274,    -1,    58,    -1,   281,
     286,   283,    -1,     1,    -1,    58,    -1,   274,    -1,   275,
       4,     3,     4,   276,    -1,   277,     4,     3,     4,   278,
      -1,   275,     4,     3,     4,   278,    -1,   277,     4,     3,
       4,   276,    -1,   284,    -1,    60,    -1,     4,    -1,    37,
      -1,   114,    -1,   271,    -1,   275,   267,   276,    -1,   275,
     268,   276,    -1,   287,    -1,    -1,   267,    15,   288,    -1,
      33,    15,   285,    -1,    34,    15,   285,    -1,    35,    15,
     285,    -1,   289,    -1,   289,     3,   288,    -1,   290,    -1,
     293,    -1,   294,    -1,   291,   294,    -1,   292,    -1,   291,
     292,    -1,     6,    -1,     6,     4,    -1,    25,    -1,   279,
      -1,    16,    -1,   294,    22,   294,    -1,   293,    22,   294,
      -1,   252,    -1,   253,    -1,   254,    -1,   255,    -1,   256,
      -1,   257,    -1,   258,    -1,   259,    -1,   260,    -1,   261,
      -1,   262,    -1,   263,    -1,   264,    -1,   265,    -1,   266,
      -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     9,    13,    15,    17,    19,
      25,    31,    37,    43,    45,    47,    49,    51,    53,    55,
      59,    63,    65,    66,    70,    74,    78,    82,    84,    88,
      90,    92,    94,    97,    99,   102,   104,   107,   109,   111,
     113,   117,   121,   123,   125,   127,   129,   131,   133,   135,
     137,   139,   141,   143,   145,   147,   149
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   382,   382,   382,   384,   385,   386,   390,   391,   395,
     396,   397,   398,   403,   404,   405,   406,   407,   408,   419,
     420,   421,   424,   425,   428,   431,   434,   442,   443,   446,
     450,   453,   461,   466,   467,   473,   474,   475,   476,   477,
     482,   485,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502
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
       2,     2,     2,     7,     2,     2,   279,    26,     8,     2,
     277,   278,    24,    22,     3,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      17,    15,    16,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   275,     2,   276,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     9,     2,     6,     2,     2,     2,
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
      10,    11,    12,    13,    14,    18,    19,    20,    21,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
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
     268,   269,   270,   271,   272,   273,   274
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 279;
  const int Parser::yynnts_ = 15;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 5;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 280;

  const unsigned int Parser::yyuser_token_number_max_ = 516;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // ComCompiler

/* Line 1054 of lalr1.cc  */
#line 1871 "comparser.tab.c"


/* Line 1056 of lalr1.cc  */
#line 504 "..\\comcompiler\\comparser.y"

// Error function throws an exception (string) with the location and error message
void ComCompiler::Parser::error(const Parser::location_type& l,
			    const string& m)
{
    driver.error(l, m);
}


#undef bugon



