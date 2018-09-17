
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
#define yylex   DefCompilerlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 7 "..\\defcompiler\\defparser.y"
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

#include "def_driver.h"

#define bugon(a) if ((a)){ printf("parsing bug at %s:%d\n", __FILE__, __LINE__); }

// stack class that takes care of all the driver.nodes that were allocated


/* Line 311 of lalr1.cc  */
#line 66 "defparser.tab.c"


#include "defparser.tab.h"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 125 "..\\defcompiler\\defparser.y"


#include "def_driver.h"
#include "scanner.h"
#include "../../util/SGF_Debug.h"
/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 89 "defparser.tab.c"

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

namespace DefCompiler {

/* Line 380 of lalr1.cc  */
#line 158 "defparser.tab.c"
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
        case 5: /* "QUOTESTRING" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 265 "defparser.tab.c"
	break;
      case 7: /* "IDENTIFIER" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 274 "defparser.tab.c"
	break;
      case 12: /* "DEF_LOOPSTART" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 283 "defparser.tab.c"
	break;
      case 13: /* "DEF_VERTICAL_HORIZONTAL" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 292 "defparser.tab.c"
	break;
      case 14: /* "DEF_ALPHA_BLEND" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 301 "defparser.tab.c"
	break;
      case 15: /* "DEF_ALPHA_BLEND_SHORTHAND" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 310 "defparser.tab.c"
	break;
      case 16: /* "DEF_COLOR_ADDITION" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 319 "defparser.tab.c"
	break;
      case 17: /* "DEF_COLOR_SUBTRACT" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 328 "defparser.tab.c"
	break;
      case 18: /* "DEF_HORIZONTAL" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 337 "defparser.tab.c"
	break;
      case 19: /* "DEF_VERTICAL" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 346 "defparser.tab.c"
	break;
      case 20: /* "DEF_BG" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 355 "defparser.tab.c"
	break;
      case 21: /* "DEF_BGCTRL" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 364 "defparser.tab.c"
	break;
      case 22: /* "DEF_SELECTBG" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 373 "defparser.tab.c"
	break;
      case 23: /* "DEF_SELECTBGCTRL" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 382 "defparser.tab.c"
	break;
      case 24: /* "DEF_FILENAME" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 391 "defparser.tab.c"
	break;
      case 25: /* "DEF_FILENAME_2" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 400 "defparser.tab.c"
	break;
      case 26: /* "DATE" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 409 "defparser.tab.c"
	break;
      case 59: /* "pontuation" */

/* Line 480 of lalr1.cc  */
#line 119 "..\\defcompiler\\defparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 418 "defparser.tab.c"
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
#line 47 "..\\defcompiler\\defparser.y"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 504 "defparser.tab.c"

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
#line 143 "..\\defcompiler\\defparser.y"
    {driver.clear_stack ();}
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 144 "..\\defcompiler\\defparser.y"
    {driver.clear_stack ();}
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 145 "..\\defcompiler\\defparser.y"
    {driver.clear_stack ();}
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 146 "..\\defcompiler\\defparser.y"
    {}
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 147 "..\\defcompiler\\defparser.y"
    {}
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 148 "..\\defcompiler\\defparser.y"
    {/*yyclearin;*/ driver.clear_stack (); SGF::Debug::debug(SGF::Debug::error,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 166 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: DATA_LIST" <<endl; driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 167 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: DATA ONLY" <<endl; driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 170 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: ADD VALUE FOR ACTION" <<endl; driver.Ast->addValueToSection((SGF::Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 175 "..\\defcompiler\\defparser.y"
    {/*driver.Ast->addValueToAttribute((SGF::Ast::CAttribute *) $1, driver.Ast->makeString(new string("Not Defined")));*/ }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 176 "..\\defcompiler\\defparser.y"
    {driver.Ast->addValueToAttribute((SGF::Ast::CAttribute *) (yysemantic_stack_[(3) - (1)].cvalue), driver.cvalues->pop()); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 180 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: Attribute: "<<endl;(yyval.cvalue)=driver.Ast->makeAttribute((SGF::Ast::CIdentifier *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 181 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: Indexed Attribute : "<<endl;(yyval.cvalue)=driver.Ast->makeIndexAttribute((SGF::Ast::CIdentifier *)(yysemantic_stack_[(4) - (1)].cvalue), (SGF::Ast::CValue *)((yysemantic_stack_[(4) - (1)].cvalue)));}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 188 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop());  }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 197 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: variable_rhs '=' value: "<<  endl; driver.nodes=new SGF::Ast::CStack(string("nodes_=")); driver.nodes->push((SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));driver.nodes->push((SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));SGF::Debug::debug(730,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< "expression2: "<<(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 198 "..\\defcompiler\\defparser.y"
    {/* Push já foi feito */SGF::Debug::debug(730,__FUNCTION__) << "BISON: expression: // = // expression1: "<<  endl;}
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 201 "..\\defcompiler\\defparser.y"
    { /* Push já foi feito */}
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 202 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *) (yysemantic_stack_[(2) - (2)].cvalue));}
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 203 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 204 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 205 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((SGF::Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 206 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: rhs = DATA_LIST :"<<endl; driver.cvalues->push((SGF::Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 207 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: rhs = STRING_VALUE :"<<endl; driver.cvalues->push((SGF::Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 213 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString(driver.Ast->addStrings( (yysemantic_stack_[(2) - (1)].doubleVal), (yysemantic_stack_[(2) - (2)].stringVal)));	}
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 214 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeStringSpace((SGF::Ast::CString*) (yysemantic_stack_[(2) - (1)].cvalue),(SGF::Ast::CString*) (yysemantic_stack_[(2) - (2)].cvalue) ); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 215 "..\\defcompiler\\defparser.y"
    {  SGF::Debug::debug(730,__FUNCTION__) << "BISON: STRING VALUELIST : "<<endl; (yyval.cvalue)=driver.Ast->makeStringSpace((SGF::Ast::CString*) (yysemantic_stack_[(2) - (1)].cvalue),(SGF::Ast::CString*) (yysemantic_stack_[(2) - (2)].cvalue) );}
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 219 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList((SGF::Ast::CValue *) (yysemantic_stack_[(3) - (1)].cvalue),(SGF::Ast::CValue *) (yysemantic_stack_[(3) - (3)].cvalue));  }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 220 "..\\defcompiler\\defparser.y"
    {  SGF::Debug::debug(730,__FUNCTION__) << "BISON: MULTIPLE_NUM_COMMA_VALUES : "<<endl; (yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList *)(yysemantic_stack_[(3) - (1)].cvalue),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue) );}
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 225 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 226 "..\\defcompiler\\defparser.y"
    {  SGF::Debug::debug(730,__FUNCTION__) << "BISON: MULTIPLE_NUM_VALUES : "<<endl; (yyval.cvalue)=driver.Ast->makeValueList((SGF::Ast::CValue *)(yysemantic_stack_[(2) - (1)].cvalue),(SGF::Ast::CValue *)(yysemantic_stack_[(2) - (2)].cvalue) );}
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 229 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: VALUE : "<<endl;(yyval.cvalue)=driver.Ast->makeNumber((yysemantic_stack_[(1) - (1)].doubleVal));  }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 233 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue);}
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 235 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue);}
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 241 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeIdentifierSimple((string *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 242 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 243 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 244 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 245 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 246 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 247 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((SGF::Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].doubleVal)); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 252 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 253 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 254 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 255 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 256 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 257 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].cvalue),(yysemantic_stack_[(2) - (2)].doubleVal));}
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 258 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].cvalue),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 261 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((SGF::Ast::CString*)(yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 262 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((SGF::Ast::CString*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].doubleVal)); }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 263 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((SGF::Ast::CString*)(yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 264 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((SGF::Ast::CString*)(yyval.cvalue),(yysemantic_stack_[(3) - (3)].doubleVal)); }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 268 "..\\defcompiler\\defparser.y"
    {  (yyval.cvalue)=driver.Ast->makeStringSpace((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 269 "..\\defcompiler\\defparser.y"
    {  (yyval.cvalue)=driver.Ast->makeStringSpace((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 270 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeStringSpace((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 271 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringSpace((SGF::Ast::CString *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 272 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringSpace((SGF::Ast::CString *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].doubleVal));}
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 276 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList((SGF::Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 277 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList*)(yysemantic_stack_[(3) - (1)].cvalue),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 281 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 282 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 283 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue) = driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 284 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeString(driver.Ast->addStrings((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal)));}
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 285 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal)); SGF::Debug::debug(730,__FUNCTION__) << "BISON: DATE : "<< (yysemantic_stack_[(1) - (1)].stringVal)->c_str()<<endl;  }
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 286 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 289 "..\\defcompiler\\defparser.y"
    {(yyval.stringVal)=new string("!");}
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 290 "..\\defcompiler\\defparser.y"
    {(yyval.stringVal)=new string("?");}
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 291 "..\\defcompiler\\defparser.y"
    { (yyval.stringVal)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].stringVal),new string("!")); }
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 292 "..\\defcompiler\\defparser.y"
    { (yyval.stringVal)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].stringVal),new string("?")); }
    break;

  case 88:

/* Line 678 of lalr1.cc  */
#line 298 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 89:

/* Line 678 of lalr1.cc  */
#line 299 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 90:

/* Line 678 of lalr1.cc  */
#line 300 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((SGF::Ast::CString *)(yysemantic_stack_[(5) - (2)].cvalue)); driver.Ast->addValueToSection(driver.Ast->makeString((yysemantic_stack_[(5) - (4)].stringVal)));}
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 301 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((SGF::Ast::CString *)(yysemantic_stack_[(5) - (2)].cvalue)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(5) - (4)].doubleVal)));}
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 302 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].doubleVal)); }
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 303 "..\\defcompiler\\defparser.y"
    { driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].doubleVal)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal))); }
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 304 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(5) - (2)].doubleVal)); }
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 305 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((SGF::Ast::CString *)(yysemantic_stack_[(3) - (2)].cvalue));  }
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 307 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 308 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 309 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 310 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 100:

/* Line 678 of lalr1.cc  */
#line 311 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 101:

/* Line 678 of lalr1.cc  */
#line 312 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 102:

/* Line 678 of lalr1.cc  */
#line 313 "..\\defcompiler\\defparser.y"
    {SGF::Debug::debug(730,__FUNCTION__) << "BISON: ASSIGNMENT" <<endl;}
    break;

  case 104:

/* Line 678 of lalr1.cc  */
#line 317 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue) = (yysemantic_stack_[(1) - (1)].cvalue);}
    break;

  case 105:

/* Line 678 of lalr1.cc  */
#line 318 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList*) (yysemantic_stack_[(3) - (1)].cvalue),(SGF::Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 106:

/* Line 678 of lalr1.cc  */
#line 319 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList*) driver.Ast->addToValueList((SGF::Ast::CValueList*) (yysemantic_stack_[(5) - (1)].cvalue),(SGF::Ast::CValue *)(yysemantic_stack_[(5) - (3)].cvalue)),(SGF::Ast::CValue *)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 107:

/* Line 678 of lalr1.cc  */
#line 320 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToValueList((SGF::Ast::CValueList*) driver.Ast->addToValueList((SGF::Ast::CValueList*) (yysemantic_stack_[(4) - (1)].cvalue),driver.Ast->makeString(new string(""))),(SGF::Ast::CValue *)(yysemantic_stack_[(4) - (4)].cvalue));}
    break;

  case 108:

/* Line 678 of lalr1.cc  */
#line 324 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 109:

/* Line 678 of lalr1.cc  */
#line 325 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 110:

/* Line 678 of lalr1.cc  */
#line 326 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 111:

/* Line 678 of lalr1.cc  */
#line 327 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 112:

/* Line 678 of lalr1.cc  */
#line 331 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 113:

/* Line 678 of lalr1.cc  */
#line 332 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 114:

/* Line 678 of lalr1.cc  */
#line 333 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 115:

/* Line 678 of lalr1.cc  */
#line 334 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 116:

/* Line 678 of lalr1.cc  */
#line 335 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 117:

/* Line 678 of lalr1.cc  */
#line 340 "..\\defcompiler\\defparser.y"
    {
	SGF::Debug::debug(1,__FUNCTION__) << "Got Bg: " << ((yysemantic_stack_[(1) - (1)].stringVal))->c_str() << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;

  case 118:

/* Line 678 of lalr1.cc  */
#line 346 "..\\defcompiler\\defparser.y"
    {
	SGF::Debug::debug(1,__FUNCTION__) << "Got Select Bg: " << (yysemantic_stack_[(1) - (1)].stringVal) << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;

  case 119:

/* Line 678 of lalr1.cc  */
#line 352 "..\\defcompiler\\defparser.y"
    {
	SGF::Debug::debug(1,__FUNCTION__) << "Got BgCtrl: " << (yysemantic_stack_[(1) - (1)].stringVal) << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;

  case 120:

/* Line 678 of lalr1.cc  */
#line 358 "..\\defcompiler\\defparser.y"
    {
	SGF::Debug::debug(1,__FUNCTION__) << "Got Select BgCtrl: " << (yysemantic_stack_[(1) - (1)].stringVal) << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;



/* Line 678 of lalr1.cc  */
#line 1335 "defparser.tab.c"
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
  const signed char Parser::yypact_ninf_ = -87;
  const short int
  Parser::yypact_[] =
  {
        93,   -87,   -87,   -87,   -87,     3,     9,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,     5,     7,
     -87,    13,    -8,    25,   -87,   -87,    18,    40,    65,    36,
     100,    71,    77,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -22,   115,    80,   120,   127,     2,   -87,   -87,
      29,   -87,    16,    44,   117,   117,    52,   -87,   -87,    42,
      42,   -87,   -87,   116,   -87,   122,   -87,   -87,    -3,   -87,
      19,   -87,   -87,   -87,   -87,   129,   -87,   136,   -14,   -87,
     -87,    16,   117,   -87,    98,   113,   -87,    42,   114,   -87,
       8,    42,    50,   118,    39,   -87,   -87,   -87,   -87,    10,
     -87,   119,   -87,   121,   -87,   -87,   -87,   -87,   -87,   -87,
     137,   -87,   -87,   -87,    57,   -87,   140,   139,   143,   -87,
     123,   -87,    16,   -87,   -87,   -87,    51,   124,   117,   -87,
     117,   -87,   117,    16,   131,   133,   -87,   -87,   -87,   -87,
     -87,   -87,    10,   -87,   -87,   145,   146,   147,   149,   -87,
     -87,   -87,   -87,   -87,   111,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     7,    10,    79,    48,    59,     0,    87,    13,    21,
      60,    61,    62,    63,   117,   119,   118,   120,    53,    54,
      81,     0,     0,     4,    24,   102,     0,   104,     0,    25,
      52,    16,    17,    12,     6,    20,    14,    18,    15,    19,
      83,    84,    80,     0,     0,     0,     0,     0,     1,     8,
       3,    11,    22,     0,     0,     0,     0,    64,    65,     0,
       0,    85,    86,     0,    92,     0,    72,    88,     0,    70,
       0,    71,    74,    73,    95,     0,     9,    48,    82,    77,
      78,     0,     0,    23,    27,    31,    33,    36,    38,    37,
      46,    40,    51,    39,    49,   109,   111,   108,   110,     0,
      45,   105,    44,     0,    58,    55,    56,    57,    76,    75,
       0,    93,    89,    96,     0,   100,     0,     0,     0,    41,
       0,    35,     0,    30,    28,    43,    51,    49,     0,    47,
      46,    42,     0,     0,     0,     0,   113,   115,   116,   112,
     114,   107,     0,    26,    94,     0,     0,     0,     0,    91,
      90,    34,    29,    32,     0,    69,    68,    67,    66,   106,
      97,    98,    99,   101,    50
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,    26,
     -87,   -79,   -87,   -87,   160,   -86,     0,    -6,   -87,   -87,
       4,   -87,   161,     1,   -87,   -87,   -87,   -87,   -87,    20,
     -87,   -87,   -87,   -87
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,    21,    22,    50,    23,    24,    25,    26,    83,    84,
     124,    85,    86,    87,    88,    89,    90,    91,    29,    30,
      92,    47,    93,    94,    42,    33,    34,    35,   101,   141,
      36,    37,    38,    39
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -104;
  const short int
  Parser::yytable_[] =
  {
        28,    32,   120,   -82,   129,   -77,   113,   -78,    72,    73,
      61,    74,    62,    48,     4,    43,    44,   136,    40,    49,
      41,     3,    77,    78,   137,   138,   139,   140,   115,    51,
     114,    45,    46,    75,   -82,    40,   -77,    41,   -78,    54,
      79,    80,    20,   152,   129,    81,    52,     3,    82,    78,
       4,    95,   116,   100,   102,   103,    76,    96,   104,   105,
     108,   109,    97,    98,   145,    55,    79,    80,    20,    56,
      60,    53,   135,   146,   147,    99,   106,   107,   132,   133,
     133,   125,   121,   134,   134,   131,    65,    66,   127,    67,
     130,   126,   127,  -103,     1,   126,    54,     2,     3,     4,
       5,     6,    59,     7,     8,     9,    57,    58,    60,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -2,    63,   110,     4,    64,   111,    68,    69,   100,   122,
     130,   112,   153,    70,    71,   117,   118,   155,   156,   157,
     158,   164,   122,   119,   123,   128,   144,   148,   149,    59,
     142,   143,   150,   151,   160,   161,   162,   135,   163,   154,
      27,    31,   159
  };

  /* YYCHECK.  */
  const unsigned char
  Parser::yycheck_[] =
  {
         0,     0,    81,     0,    90,     0,     9,     0,     6,     7,
      32,     9,    34,     0,     6,     6,     7,     7,    32,    27,
      34,     5,     6,     7,    14,    15,    16,    17,     9,     4,
      33,    22,    23,    31,    31,    32,    31,    34,    31,    31,
      24,    25,    26,   122,   130,    29,    28,     5,    32,     7,
       6,     7,    33,    53,    54,    55,    27,    13,     6,     7,
      59,    60,    18,    19,     7,    29,    24,    25,    26,    33,
      31,    31,    33,    16,    17,    31,    24,    25,    28,    29,
      29,    87,    82,    33,    33,    91,     6,     7,    87,     9,
      90,    87,    91,     0,     1,    91,    31,     4,     5,     6,
       7,     8,    31,    10,    11,    12,     6,     7,    31,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,     6,     6,     6,     9,     9,     6,     7,   128,    31,
     130,     9,   132,     6,     7,     6,     7,     6,     7,     6,
       7,    30,    31,     7,    31,    31,     9,     7,     9,    31,
      31,    30,     9,    30,     9,     9,     9,    33,     9,   133,
       0,     0,   142
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     1,     4,     5,     6,     7,     8,    10,    11,    12,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    36,    37,    39,    40,    41,    42,    49,    51,    53,
      54,    57,    58,    60,    61,    62,    65,    66,    67,    68,
      32,    34,    59,     6,     7,    22,    23,    56,     0,    27,
      38,     4,    28,    31,    31,    29,    33,     6,     7,    31,
      31,    32,    34,     6,     9,     6,     7,     9,     6,     7,
       6,     7,     6,     7,     9,    31,    27,     6,     7,    24,
      25,    29,    32,    43,    44,    46,    47,    48,    49,    50,
      51,    52,    55,    57,    58,     7,    13,    18,    19,    31,
      51,    63,    51,    51,     6,     7,    24,    25,    58,    58,
       6,     9,     9,     9,    33,     9,    33,     6,     7,     7,
      46,    51,    31,    31,    45,    52,    55,    58,    31,    50,
      51,    52,    28,    29,    33,    33,     7,    14,    15,    16,
      17,    64,    31,    30,     9,     7,    16,    17,     7,     9,
       9,    30,    46,    51,    44,     6,     7,     6,     7,    64,
       9,     9,     9,     9,    30
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,    91,    93,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,    61,    40,
      41,    44,    33,    46,    63
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    35,    37,    36,    36,    36,    36,    36,    38,    38,
      39,    39,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    41,    41,    41,    42,    42,    43,    44,    44,
      45,    45,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    48,    48,    48,    49,    49,    50,    50,    51,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    53,    54,
      54,    54,    54,    54,    54,    54,    55,    55,    55,    55,
      56,    56,    56,    56,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    59,    59,    59,    59,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    62,    62,    63,    63,
      63,    63,    64,    64,    64,    64,    64,    65,    66,    67,
      68
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     1,     1,     4,     1,     2,     3,
       1,     0,     3,     1,     3,     2,     1,     1,     1,     1,
       1,     2,     2,     2,     3,     3,     1,     2,     1,     1,
       4,     1,     1,     1,     1,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     3,     3,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     2,     1,     3,     4,
       5,     5,     3,     4,     5,     3,     4,     6,     6,     6,
       4,     6,     1,     0,     1,     3,     5,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "UMINUS", "\"end of line\"",
  "QUOTESTRING", "NUMBER", "IDENTIFIER", "'['", "']'", "DEF_TEXT",
  "DEF_BLANK", "DEF_LOOPSTART", "DEF_VERTICAL_HORIZONTAL",
  "DEF_ALPHA_BLEND", "DEF_ALPHA_BLEND_SHORTHAND", "DEF_COLOR_ADDITION",
  "DEF_COLOR_SUBTRACT", "DEF_HORIZONTAL", "DEF_VERTICAL", "DEF_BG",
  "DEF_BGCTRL", "DEF_SELECTBG", "DEF_SELECTBGCTRL", "DEF_FILENAME",
  "DEF_FILENAME_2", "DATE", "COMMENT", "'='", "'('", "')'", "','", "'!'",
  "'.'", "'?'", "$accept", "lines", "$@1", "coments", "ends", "line",
  "assignment", "lhs", "rhs", "expression_list", "maybe_comma",
  "expression", "expression1", "multiple_str_values",
  "multiple_num_comma_values", "multiple_num_values", "value",
  "string_value", "variable", "identificator_lhs_list", "variable_rhs",
  "identificator_list", "data_list", "data", "pontuation", "unquoted_text",
  "section", "maybe_flip", "flip", "color_sub", "bg", "selectbg", "bgctrl",
  "selectbgctrl", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        36,     0,    -1,    -1,    37,    38,    -1,    39,    -1,    36,
      -1,    61,    -1,     1,    -1,    27,    -1,    38,    27,    -1,
       4,    -1,    39,     4,    -1,    60,    -1,    11,    -1,    65,
      -1,    67,    -1,    57,    -1,    58,    -1,    66,    -1,    68,
      -1,    62,    -1,    12,    -1,    42,    28,    -1,    42,    28,
      43,    -1,    40,    -1,    53,    -1,    53,    29,    51,    30,
      -1,    44,    -1,    46,    45,    -1,    44,    31,    46,    -1,
      31,    -1,    -1,    55,    28,    51,    -1,    47,    -1,    29,
      46,    30,    -1,    32,    51,    -1,    48,    -1,    50,    -1,
      49,    -1,    57,    -1,    52,    -1,     6,     7,    -1,    52,
      52,    -1,    48,    52,    -1,    51,    31,    51,    -1,    49,
      31,    51,    -1,    51,    -1,    51,    50,    -1,     6,    -1,
      58,    -1,    55,    29,    44,    30,    -1,    55,    -1,    54,
      -1,    24,    -1,    25,    -1,    53,    33,     7,    -1,    53,
      33,    24,    -1,    53,    33,    25,    -1,    53,    33,     6,
      -1,     7,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
      -1,    54,     6,    -1,    54,     7,    -1,    58,    33,     7,
      -1,    58,    33,     6,    -1,    55,    33,     7,    -1,    55,
      33,     6,    -1,    22,     7,    -1,    23,     7,    -1,     7,
       7,    -1,    56,     7,    -1,    56,     6,    -1,    58,    31,
      58,    -1,    57,    31,    58,    -1,    24,    -1,    25,    -1,
       5,    -1,     7,    59,    -1,    26,    -1,     7,    -1,    32,
      -1,    34,    -1,    59,    32,    -1,    59,    34,    -1,    10,
      -1,     8,     7,     9,    -1,     8,     7,     6,     9,    -1,
       8,    56,    31,     7,     9,    -1,     8,    56,    31,     6,
       9,    -1,     8,     6,     9,    -1,     8,     6,     6,     9,
      -1,     8,     6,     6,     6,     9,    -1,     8,    56,     9,
      -1,     8,    22,     6,     9,    -1,     8,    22,     6,    33,
       7,     9,    -1,     8,    22,     6,    33,    16,     9,    -1,
       8,    22,     6,    33,    17,     9,    -1,     8,    23,     6,
       9,    -1,     8,    23,     6,    33,     7,     9,    -1,    41,
      -1,    -1,    49,    -1,    49,    31,    63,    -1,    49,    31,
      63,    31,    64,    -1,    49,    31,    31,    64,    -1,    18,
      -1,     7,    -1,    19,    -1,    13,    -1,    16,    -1,     7,
      -1,    17,    -1,    14,    -1,    15,    -1,    20,    -1,    22,
      -1,    21,    -1,    23,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      20,    22,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    48,    52,    54,    56,    61,    63,    66,
      70,    72,    73,    77,    79,    83,    86,    88,    90,    92,
      94,    96,    99,   102,   105,   109,   113,   115,   118,   120,
     122,   127,   129,   131,   133,   135,   139,   143,   147,   151,
     153,   155,   157,   159,   161,   164,   167,   171,   175,   179,
     183,   186,   189,   192,   195,   198,   202,   206,   208,   210,
     212,   215,   217,   219,   221,   223,   226,   229,   231,   235,
     240,   246,   252,   256,   261,   267,   271,   276,   283,   290,
     297,   302,   309,   311,   312,   314,   318,   324,   329,   331,
     333,   335,   337,   339,   341,   343,   345,   347,   349,   351,
     353
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   143,   143,   143,   145,   146,   147,   148,   153,   154,
     157,   158,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   175,   176,   177,   180,   181,   184,   187,   188,
     192,   193,   197,   198,   201,   202,   203,   204,   205,   206,
     207,   213,   214,   215,   219,   220,   225,   226,   229,   233,
     234,   235,   241,   242,   243,   244,   245,   246,   247,   252,
     253,   254,   255,   256,   257,   258,   261,   262,   263,   264,
     268,   269,   270,   271,   272,   276,   277,   281,   282,   283,
     284,   285,   286,   289,   290,   291,   292,   295,   298,   299,
     300,   301,   302,   303,   304,   305,   307,   308,   309,   310,
     311,   312,   313,   314,   317,   318,   319,   320,   324,   325,
     326,   327,   331,   332,   333,   334,   335,   340,   346,   352,
     358
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
       2,     2,     2,    32,     2,     2,     2,     2,     2,     2,
      29,    30,     2,     2,    31,     2,    33,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     8,     2,     9,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 162;
  const int Parser::yynnts_ = 34;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 48;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 35;

  const unsigned int Parser::yyuser_token_number_max_ = 280;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // DefCompiler

/* Line 1054 of lalr1.cc  */
#line 1930 "defparser.tab.c"


/* Line 1056 of lalr1.cc  */
#line 362 "..\\defcompiler\\defparser.y"

// Error function throws an exception (std::string) with the location and error message
void DefCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    
    driver.error(l, m);
	driver.clear_stack ();
}



#undef bugon



