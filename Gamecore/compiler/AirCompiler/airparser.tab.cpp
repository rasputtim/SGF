
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
#define yylex   AirCompilerlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 6 "..\\aircompiler\\airparser.y"
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

#include "air_driver.h"

#define bugon(a) if ((a)){ printf("parsing bug at %s:%d\n", __FILE__, __LINE__); }




/* Line 311 of lalr1.cc  */
#line 66 "airparser.tab.c"


#include "airparser.tab.h"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 99 "..\\aircompiler\\airparser.y"


#include "air_driver.h"
#include "airScanner.h"
#include "../../util/SGF_Debug.h"
/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 89 "airparser.tab.c"

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

namespace AirCompiler {

/* Line 380 of lalr1.cc  */
#line 158 "airparser.tab.c"
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
        case 6: /* "\"string\"" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 265 "airparser.tab.c"
	break;
      case 7: /* "ACBEGIN" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 274 "airparser.tab.c"
	break;
      case 8: /* "ACTION" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 283 "airparser.tab.c"
	break;
      case 9: /* "LOOPSTART" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 292 "airparser.tab.c"
	break;
      case 10: /* "COLLISION_DEFENSE_DEFAULT" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 301 "airparser.tab.c"
	break;
      case 11: /* "COLLISION_ATTACK_DEFAULT" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 310 "airparser.tab.c"
	break;
      case 12: /* "COLLISION_DEFENSE" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 319 "airparser.tab.c"
	break;
      case 13: /* "COLLISION_ATTACK" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 328 "airparser.tab.c"
	break;
      case 14: /* "HORIZONTALFLIP" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 337 "airparser.tab.c"
	break;
      case 15: /* "VERTIKALFLIP" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 346 "airparser.tab.c"
	break;
      case 16: /* "HVFLIP" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 355 "airparser.tab.c"
	break;
      case 17: /* "ALPHA_BLEND" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 364 "airparser.tab.c"
	break;
      case 18: /* "ALPHA_BLEND_SHORTHAND" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 373 "airparser.tab.c"
	break;
      case 19: /* "COLOR_SUBTRACT" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 382 "airparser.tab.c"
	break;
      case 20: /* "COLOR_ADDITION" */

/* Line 480 of lalr1.cc  */
#line 95 "..\\aircompiler\\airparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 391 "airparser.tab.c"
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
#line 46 "..\\aircompiler\\airparser.y"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 477 "airparser.tab.c"

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
	  case 6:

/* Line 678 of lalr1.cc  */
#line 123 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeSection(driver.Ast->makeHeader((yysemantic_stack_[(5) - (2)].stringVal), (yysemantic_stack_[(5) - (3)].stringVal), (yysemantic_stack_[(5) - (4)].doubleVal)));}
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 124 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword((yysemantic_stack_[(4) - (1)].stringVal)),driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 125 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword((yysemantic_stack_[(4) - (1)].stringVal)), driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 126 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword((yysemantic_stack_[(4) - (1)].stringVal)), driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 127 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword((yysemantic_stack_[(4) - (1)].stringVal)), driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 128 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeArray(driver.Ast->makeKeyword((yysemantic_stack_[(7) - (1)].stringVal)), driver.Ast->makeNumber((yysemantic_stack_[(7) - (3)].doubleVal)), (SGF::Ast::CValueList *)((yysemantic_stack_[(7) - (6)].cvalue)));}
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 129 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeArray(driver.Ast->makeKeyword((yysemantic_stack_[(7) - (1)].stringVal)), driver.Ast->makeNumber((yysemantic_stack_[(7) - (3)].doubleVal)), (SGF::Ast::CValueList *)((yysemantic_stack_[(7) - (6)].cvalue)));}
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 131 "..\\aircompiler\\airparser.y"
    { driver.Ast->addValueToSection((SGF::Ast::CValue*)((yysemantic_stack_[(2) - (1)].cvalue))); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 132 "..\\aircompiler\\airparser.y"
    { driver.Ast->addValueToSection((SGF::Ast::CValue*)((yysemantic_stack_[(3) - (1)].cvalue))); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 133 "..\\aircompiler\\airparser.y"
    {SGF::Ast::CValueList *id=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(5) - (1)].cvalue),driver.Ast->makeValueString()); id=driver.Ast->addToValueList(id,(SGF::Ast::CValue*)(yysemantic_stack_[(5) - (4)].cvalue));driver.Ast->addValueToSection((SGF::Ast::CValue*)(id));}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 134 "..\\aircompiler\\airparser.y"
    {SGF::Ast::CValueList *id=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(4) - (1)].cvalue),(SGF::Ast::CValue*)(yysemantic_stack_[(4) - (3)].cvalue)); driver.Ast->addValueToSection((SGF::Ast::CValue*)(id));}
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 135 "..\\aircompiler\\airparser.y"
    {SGF::Ast::CValueList *id=driver.Ast->addToValueList((SGF::Ast::CValueList *) (yysemantic_stack_[(6) - (1)].cvalue),(SGF::Ast::CValue*)(yysemantic_stack_[(6) - (3)].cvalue)); id=driver.Ast->addToValueList(id,(SGF::Ast::CValue*)(yysemantic_stack_[(6) - (5)].cvalue));driver.Ast->addValueToSection((SGF::Ast::CValue*)(id));}
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 136 "..\\aircompiler\\airparser.y"
    {driver.Ast->makeAttributeKeyword(driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal)));}
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 142 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeValueList(driver.Ast->makeNumber((yysemantic_stack_[(3) - (1)].doubleVal)),driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)));}
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 143 "..\\aircompiler\\airparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(3) - (1)].cvalue), driver.Ast->makeNumber((yysemantic_stack_[(3) - (3)].doubleVal)));}
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 146 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 147 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 148 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 152 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 153 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 154 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 155 "..\\aircompiler\\airparser.y"
    { (yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;



/* Line 678 of lalr1.cc  */
#line 750 "airparser.tab.c"
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
  const signed char Parser::yypact_ninf_ = -37;
  const signed char
  Parser::yypact_[] =
  {
        29,   -37,   -37,    43,   -37,   -37,   -37,   -16,   -37,    -6,
       7,    -8,    -5,    15,   -37,    -2,    20,    28,    30,    31,
      32,    40,    42,    41,   -37,    -3,   -37,    47,    54,    35,
      56,    37,    58,    57,   -37,   -37,   -37,   -37,   -37,   -11,
       0,   -37,   -37,    38,   -37,    39,   -37,    44,   -37,   -37,
     -37,   -37,   -37,    63,   -37,   -11,    64,    64,   -37,   -37,
      65,     1,     2,   -37,   -37,    66,   -37
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     5,     4,     0,     1,    20,    19,     0,    18,     0,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,    21,     0,     0,     0,
       0,     0,     0,     0,    14,    22,    23,    24,    25,     0,
       0,     8,     7,     0,    10,     0,     9,     0,    28,    29,
      27,    26,    30,     0,    16,     0,     0,     0,     6,    15,
       0,     0,     0,    17,    12,     0,    11
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -37,   -37,   -37,   -36,   -37,    17
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     3,    14,    15,    40,    53
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -3;
  const signed char
  Parser::yytable_[] =
  {
        34,    24,    35,    54,    64,    66,    48,    49,    50,    51,
      16,    36,    37,    38,    19,    52,    20,    21,    17,    22,
      61,    62,    23,    39,    25,    26,    55,    65,    65,    -2,
       1,    18,     2,    27,    -2,    28,    29,    30,    -2,    -2,
      -2,    -2,    -2,     4,     5,    31,     6,    32,     7,    33,
      41,    -2,     8,     9,    10,    11,    12,    42,    43,    44,
      45,    46,    47,    56,    57,    13,    59,    58,    63,     7,
       0,    35,    60
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         3,     3,     5,     3,     3,     3,    17,    18,    19,    20,
      26,    14,    15,    16,    22,    26,    24,    22,    24,    24,
      56,    57,     7,    26,    26,     5,    26,    26,    26,     0,
       1,    24,     3,     5,     5,     5,     5,     5,     9,    10,
      11,    12,    13,     0,     1,     5,     3,     5,     5,     8,
       3,    22,     9,    10,    11,    12,    13,     3,    23,     3,
      23,     3,     5,    25,    25,    22,     3,    23,     3,     5,
      -1,     5,    55
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     1,     3,    28,     0,     1,     3,     5,     9,    10,
      11,    12,    13,    22,    29,    30,    26,    24,    24,    22,
      24,    22,    24,     7,     3,    26,     5,     5,     5,     5,
       5,     5,     5,     8,     3,     5,    14,    15,    16,    26,
      31,     3,     3,    23,     3,    23,     3,     5,    17,    18,
      19,    20,    26,    32,     3,    26,    25,    25,    23,     3,
      32,    30,    30,     3,     3,    26,     3
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    91,    93,    58,    61,    44
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    27,    28,    28,    28,    28,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    30,    30,    31,    31,    31,    32,    32,    32,    32,
      32
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     1,     1,     5,     4,     4,     4,
       4,     7,     7,     2,     3,     5,     4,     6,     1,     1,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"integer\"", "\"double\"", "\"string\"", "ACBEGIN", "ACTION",
  "LOOPSTART", "COLLISION_DEFENSE_DEFAULT", "COLLISION_ATTACK_DEFAULT",
  "COLLISION_DEFENSE", "COLLISION_ATTACK", "HORIZONTALFLIP",
  "VERTIKALFLIP", "HVFLIP", "ALPHA_BLEND", "ALPHA_BLEND_SHORTHAND",
  "COLOR_SUBTRACT", "COLOR_ADDITION", "COMMENT", "'['", "']'", "':'",
  "'='", "','", "$accept", "lines", "AIRFILE", "double_list", "flip",
  "color_sub", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        28,     0,    -1,    -1,    28,    29,    -1,     3,    -1,     1,
      -1,    22,     7,     8,     5,    23,    -1,    11,    24,     5,
       3,    -1,    10,    24,     5,     3,    -1,    13,    24,     5,
       3,    -1,    12,    24,     5,     3,    -1,    13,    22,     5,
      23,    25,    30,     3,    -1,    12,    22,     5,    23,    25,
      30,     3,    -1,    30,     3,    -1,    30,    26,     3,    -1,
      30,    26,    26,    32,     3,    -1,    30,    26,    31,     3,
      -1,    30,    26,    31,    26,    32,     3,    -1,     9,    -1,
       3,    -1,     1,    -1,     5,    26,     5,    -1,    30,    26,
       5,    -1,    14,    -1,    15,    -1,    16,    -1,    20,    -1,
      19,    -1,    17,    -1,    18,    -1,    26,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     9,    11,    17,    22,    27,
      32,    37,    45,    53,    56,    60,    66,    71,    78,    80,
      82,    84,    88,    92,    94,    96,    98,   100,   102,   104,
     106
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,   116,   116,   117,   118,   119,   123,   124,   125,   126,
     127,   128,   129,   131,   132,   133,   134,   135,   136,   137,
     138,   142,   143,   146,   147,   148,   152,   153,   154,   155,
     156
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    24,     2,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 72;
  const int Parser::yynnts_ = 6;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 4;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 27;

  const unsigned int Parser::yyuser_token_number_max_ = 276;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // AirCompiler

/* Line 1054 of lalr1.cc  */
#line 1221 "airparser.tab.c"


/* Line 1056 of lalr1.cc  */
#line 158 "..\\aircompiler\\airparser.y"

// Error function throws an exception (std::string) with the location and error message
void AirCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}


#undef bugon



