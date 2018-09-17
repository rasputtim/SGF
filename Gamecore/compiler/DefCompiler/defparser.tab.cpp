
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
#include "defScanner.h"
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
    {}
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 146 "..\\defcompiler\\defparser.y"
    {}
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 147 "..\\defcompiler\\defparser.y"
    {/*yyclearin;*/ driver.clear_stack (); Debug::debug(30,__FUNCTION__) << "Bison::error // erro: "<<"erro"<<  endl;}
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 164 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: DATA_LIST" <<endl; driver.Ast->addValueToSection((Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 165 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: DATA ONLY" <<endl; driver.Ast->addValueToSection((Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 168 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: ADD VALUE FOR ACTION" <<endl; driver.Ast->addValueToSection((Ast::CValue *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 173 "..\\defcompiler\\defparser.y"
    {/*driver.Ast->addValueToAttribute((Ast::CAttribute *) $1, driver.Ast->makeString(new string("Not Defined")));*/ }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 174 "..\\defcompiler\\defparser.y"
    {driver.Ast->addValueToAttribute((Ast::CAttribute *) (yysemantic_stack_[(3) - (1)].cvalue), driver.cvalues->pop()); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 178 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: Attribute: "<<endl;(yyval.cvalue)=driver.Ast->makeAttribute((Ast::CIdentifier *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 179 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: Indexed Attribute : "<<endl;(yyval.cvalue)=driver.Ast->makeIndexAttribute((Ast::CIdentifier *)(yysemantic_stack_[(4) - (1)].cvalue), (Ast::CValue *)((yysemantic_stack_[(4) - (1)].cvalue)));}
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 186 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeValueList(driver.cvalues->pop(),driver.cvalues->pop());  }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 195 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: variable_rhs '=' value: "<<  endl; driver.nodes=new Ast::CStack(string("nodes_=")); driver.nodes->push((Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));driver.nodes->push((Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue));driver.nodes->push(driver.Ast->makeOperand(string("EQUAL")));driver.cvalues->push(driver.Ast->makePostfixExpression(driver.nodes));Debug::debug(730,__FUNCTION__) << "BISON: compare expression: // = // expression1: "<<(Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue)<< "expression2: "<<(Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue)<< endl;}
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 196 "..\\defcompiler\\defparser.y"
    {/* Push já foi feito */Debug::debug(730,__FUNCTION__) << "BISON: expression: // = // expression1: "<<  endl;}
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 199 "..\\defcompiler\\defparser.y"
    { /* Push já foi feito */}
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 200 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((Ast::CValue *) (yysemantic_stack_[(2) - (2)].cvalue));}
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 201 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 202 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 203 "..\\defcompiler\\defparser.y"
    {driver.cvalues->push((Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 204 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: rhs = DATA_LIST :"<<endl; driver.cvalues->push((Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 205 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: rhs = STRING_VALUE :"<<endl; driver.cvalues->push((Ast::CValue *) (yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 211 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString(driver.Ast->addStrings( (yysemantic_stack_[(2) - (1)].doubleVal), (yysemantic_stack_[(2) - (2)].stringVal)));	}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 212 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeStringSpace((Ast::CString*) (yysemantic_stack_[(2) - (1)].cvalue),(Ast::CString*) (yysemantic_stack_[(2) - (2)].cvalue) ); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 213 "..\\defcompiler\\defparser.y"
    {  Debug::debug(730,__FUNCTION__) << "BISON: STRING VALUELIST : "<<endl; (yyval.cvalue)=driver.Ast->makeStringSpace((Ast::CString*) (yysemantic_stack_[(2) - (1)].cvalue),(Ast::CString*) (yysemantic_stack_[(2) - (2)].cvalue) );}
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 217 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList((Ast::CValue *) (yysemantic_stack_[(3) - (1)].cvalue),(Ast::CValue *) (yysemantic_stack_[(3) - (3)].cvalue));  }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 218 "..\\defcompiler\\defparser.y"
    {  Debug::debug(730,__FUNCTION__) << "BISON: MULTIPLE_NUM_COMMA_VALUES : "<<endl; (yyval.cvalue)=driver.Ast->addToValueList((Ast::CValueList *)(yysemantic_stack_[(3) - (1)].cvalue),(Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue) );}
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 223 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 224 "..\\defcompiler\\defparser.y"
    {  Debug::debug(730,__FUNCTION__) << "BISON: MULTIPLE_NUM_VALUES : "<<endl; (yyval.cvalue)=driver.Ast->makeValueList((Ast::CValue *)(yysemantic_stack_[(2) - (1)].cvalue),(Ast::CValue *)(yysemantic_stack_[(2) - (2)].cvalue) );}
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 227 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: VALUE : "<<endl;(yyval.cvalue)=driver.Ast->makeNumber((yysemantic_stack_[(1) - (1)].doubleVal));  }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 231 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue);}
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 233 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].cvalue);}
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 239 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeIdentifierSimple((string *)(yysemantic_stack_[(1) - (1)].cvalue));}
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 240 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 241 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeIdentifierSimple((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 242 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 243 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 244 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 245 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToIdentifier((Ast::CIdentifier*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].doubleVal)); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 250 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 251 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 252 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 253 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 254 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=(yysemantic_stack_[(1) - (1)].stringVal);}
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 255 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].cvalue),(yysemantic_stack_[(2) - (2)].doubleVal));}
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 256 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].cvalue),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 259 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((Ast::CString*)(yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 260 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((Ast::CString*) (yyval.cvalue),(yysemantic_stack_[(3) - (3)].doubleVal)); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 261 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((Ast::CString*)(yyval.cvalue),(yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 262 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringDot((Ast::CString*)(yyval.cvalue),(yysemantic_stack_[(3) - (3)].doubleVal)); }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 266 "..\\defcompiler\\defparser.y"
    {  (yyval.cvalue)=driver.Ast->makeStringSpace((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 267 "..\\defcompiler\\defparser.y"
    {  (yyval.cvalue)=driver.Ast->makeStringSpace((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 268 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeStringSpace((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 269 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringSpace((Ast::CString *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 270 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToStringSpace((Ast::CString *)(yysemantic_stack_[(2) - (1)].cvalue), (yysemantic_stack_[(2) - (2)].doubleVal));}
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 274 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeValueList((Ast::CValue *)(yysemantic_stack_[(3) - (1)].cvalue),(Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 275 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((Ast::CValueList*)(yysemantic_stack_[(3) - (1)].cvalue),(Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 279 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 280 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 281 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue) = driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 282 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeString(driver.Ast->addStrings((yysemantic_stack_[(2) - (1)].stringVal),(yysemantic_stack_[(2) - (2)].stringVal)));}
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 283 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal)); Debug::debug(730,__FUNCTION__) << "BISON: DATE : "<< (yysemantic_stack_[(1) - (1)].stringVal)->c_str()<<endl;  }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 284 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->makeString((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 287 "..\\defcompiler\\defparser.y"
    {(yyval.stringVal)=new string("!");}
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 288 "..\\defcompiler\\defparser.y"
    {(yyval.stringVal)=new string("?");}
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 289 "..\\defcompiler\\defparser.y"
    { (yyval.stringVal)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].stringVal),new string("!")); }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 290 "..\\defcompiler\\defparser.y"
    { (yyval.stringVal)=driver.Ast->addStrings((string *)(yysemantic_stack_[(2) - (1)].stringVal),new string("?")); }
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 296 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 88:

/* Line 678 of lalr1.cc  */
#line 297 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 89:

/* Line 678 of lalr1.cc  */
#line 298 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((Ast::CString *)(yysemantic_stack_[(5) - (2)].cvalue)); driver.Ast->addValueToSection(driver.Ast->makeString((yysemantic_stack_[(5) - (4)].stringVal)));}
    break;

  case 90:

/* Line 678 of lalr1.cc  */
#line 299 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((Ast::CString *)(yysemantic_stack_[(5) - (2)].cvalue)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(5) - (4)].doubleVal)));}
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 300 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(3) - (2)].doubleVal)); }
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 301 "..\\defcompiler\\defparser.y"
    { driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].doubleVal)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal))); }
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 302 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((yysemantic_stack_[(5) - (2)].doubleVal)); }
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 303 "..\\defcompiler\\defparser.y"
    {driver.Ast->makeSection((Ast::CString *)(yysemantic_stack_[(3) - (2)].cvalue));  }
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 305 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal)); driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 306 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 307 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 308 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 309 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(4) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeNumber((yysemantic_stack_[(4) - (3)].doubleVal)));}
    break;

  case 100:

/* Line 678 of lalr1.cc  */
#line 310 "..\\defcompiler\\defparser.y"
    {  driver.Ast->makeSection((yysemantic_stack_[(6) - (2)].stringVal)); ;driver.Ast->addValueToSection(driver.Ast->makeStringDot((yysemantic_stack_[(6) - (3)].doubleVal),(yysemantic_stack_[(6) - (5)].stringVal)));}
    break;

  case 101:

/* Line 678 of lalr1.cc  */
#line 311 "..\\defcompiler\\defparser.y"
    {Debug::debug(730,__FUNCTION__) << "BISON: ASSIGNMENT" <<endl;}
    break;

  case 103:

/* Line 678 of lalr1.cc  */
#line 315 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue) = (yysemantic_stack_[(1) - (1)].cvalue);}
    break;

  case 104:

/* Line 678 of lalr1.cc  */
#line 316 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((Ast::CValueList*) (yysemantic_stack_[(3) - (1)].cvalue),(Ast::CValue *)(yysemantic_stack_[(3) - (3)].cvalue));}
    break;

  case 105:

/* Line 678 of lalr1.cc  */
#line 317 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->addToValueList((Ast::CValueList*) driver.Ast->addToValueList((Ast::CValueList*) (yysemantic_stack_[(5) - (1)].cvalue),(Ast::CValue *)(yysemantic_stack_[(5) - (3)].cvalue)),(Ast::CValue *)(yysemantic_stack_[(5) - (5)].cvalue));}
    break;

  case 106:

/* Line 678 of lalr1.cc  */
#line 318 "..\\defcompiler\\defparser.y"
    { (yyval.cvalue)=driver.Ast->addToValueList((Ast::CValueList*) driver.Ast->addToValueList((Ast::CValueList*) (yysemantic_stack_[(4) - (1)].cvalue),driver.Ast->makeString(new string(""))),(Ast::CValue *)(yysemantic_stack_[(4) - (4)].cvalue));}
    break;

  case 107:

/* Line 678 of lalr1.cc  */
#line 322 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 108:

/* Line 678 of lalr1.cc  */
#line 323 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 109:

/* Line 678 of lalr1.cc  */
#line 324 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 110:

/* Line 678 of lalr1.cc  */
#line 328 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 111:

/* Line 678 of lalr1.cc  */
#line 329 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 112:

/* Line 678 of lalr1.cc  */
#line 330 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 113:

/* Line 678 of lalr1.cc  */
#line 331 "..\\defcompiler\\defparser.y"
    {(yyval.cvalue)=driver.Ast->makeKeyword((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 114:

/* Line 678 of lalr1.cc  */
#line 336 "..\\defcompiler\\defparser.y"
    {
	Debug::debug(1,__FUNCTION__) << "Got Bg: " << ((yysemantic_stack_[(1) - (1)].stringVal))->c_str() << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;

  case 115:

/* Line 678 of lalr1.cc  */
#line 342 "..\\defcompiler\\defparser.y"
    {
	Debug::debug(1,__FUNCTION__) << "Got Select Bg: " << (yysemantic_stack_[(1) - (1)].stringVal) << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;

  case 116:

/* Line 678 of lalr1.cc  */
#line 348 "..\\defcompiler\\defparser.y"
    {
	Debug::debug(1,__FUNCTION__) << "Got BgCtrl: " << (yysemantic_stack_[(1) - (1)].stringVal) << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;

  case 117:

/* Line 678 of lalr1.cc  */
#line 354 "..\\defcompiler\\defparser.y"
    {
	Debug::debug(1,__FUNCTION__) << "Got Select BgCtrl: " << (yysemantic_stack_[(1) - (1)].stringVal) << std::endl;
	driver.Ast->makeSection((yysemantic_stack_[(1) - (1)].stringVal));
    }
    break;



/* Line 678 of lalr1.cc  */
#line 1314 "defparser.tab.c"
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
  const signed char Parser::yypact_ninf_ = -89;
  const short int
  Parser::yypact_[] =
  {
        92,   -89,   -89,   -89,    -1,   131,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,     7,     9,   -89,
      57,    45,   -89,   -89,   -13,     6,    14,   -15,   165,    19,
      27,   -89,    45,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     100,    79,   158,   167,   169,    10,   -89,    45,   -89,   -89,
      62,   -89,     3,   117,    89,    89,   119,   -89,   -89,   115,
     115,    97,   -89,   -89,   141,   -89,    98,   -89,   -89,    15,
     -89,    37,   -89,   -89,   -89,   -89,   171,   101,   -89,    99,
     124,   -89,   -89,     3,    89,   -89,    90,    96,   -89,   115,
     126,   -89,    16,   115,    58,   138,   137,   -89,   -89,   -89,
     146,   -89,   152,   -89,   116,   -89,   -89,   -89,   -89,   -89,
     -89,   157,   -89,   -89,   -89,   135,   -89,   177,   176,   178,
     -89,   156,   -89,     3,   -89,   -89,   -89,    23,   155,    89,
     -89,    89,   -89,    89,     3,   173,   175,   -89,   -89,   -89,
     -89,   -89,   146,   -89,   -89,   180,   181,   182,   183,   -89,
     -89,   -89,   -89,   -89,   -24,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     6,    78,    47,    58,     0,    86,    12,    20,    59,
      60,    61,    62,   114,   116,   115,   117,    52,    53,    80,
     102,     0,    23,   101,     0,   103,     0,    24,    51,    15,
      16,    11,     0,    19,    13,    17,    14,    18,    82,    83,
      79,     0,     0,     0,     0,     0,     1,     0,     9,    10,
       3,     7,    21,     0,     0,     0,     0,    63,    64,     0,
       0,     5,    84,    85,     0,    91,     0,    71,    87,     0,
      69,     0,    70,    73,    72,    94,     0,     4,     8,    47,
      81,    76,    77,     0,     0,    22,    26,    30,    32,    35,
      37,    36,    45,    39,    50,    38,    48,   109,   107,   108,
       0,    44,   104,    43,     0,    57,    54,    55,    56,    75,
      74,     0,    92,    88,    95,     0,    99,     0,     0,     0,
      40,     0,    34,     0,    29,    27,    42,    50,    48,     0,
      46,    45,    41,     0,     0,     0,     0,   112,   113,   110,
     111,   106,     0,    25,    93,     0,     0,     0,     0,    90,
      89,    33,    28,    31,     0,    68,    67,    66,    65,   105,
      96,    97,    98,   100,    49
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -89,   -89,   -89,    12,   -38,   -89,   -89,   -89,   -89,    59,
     -89,   -81,   -89,   -89,     5,   -88,     0,    56,   -89,   -89,
      66,   -89,    51,     1,   -89,   -89,   174,   -89,   -89,    53,
     -89,   -89,   -89,   -89
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,    20,    21,    50,    51,    22,    23,    24,    85,    86,
     125,    87,    88,    89,    90,    91,    92,    93,    27,    28,
      94,    45,    95,    96,    40,    31,    32,    33,   102,   141,
      34,    35,    36,    37
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -82;
  const short int
  Parser::yytable_[] =
  {
        26,    30,   121,   -81,   130,    25,   164,   123,     2,    79,
      80,   -76,    78,   -77,    55,    52,    73,    74,    56,    75,
      26,    30,     3,    78,   114,    25,   -81,    81,    82,    19,
     -81,    38,    83,    39,   -76,    84,   -77,    53,   -76,    78,
     -77,    76,   152,   130,    61,    54,   116,    54,   115,    48,
      59,    29,   134,   101,   103,   104,   135,    46,    60,    77,
     109,   110,     2,     3,     4,     5,    48,     6,     7,     8,
     117,    29,    49,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,   122,    64,   133,   134,    65,    49,
     128,   135,   131,     1,   128,     3,    -2,     2,     3,     4,
       5,    48,     6,     7,     8,    48,   120,   113,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -2,
       2,   123,    80,     3,    49,   105,   106,   124,    49,   101,
      97,   131,    62,   153,    63,    98,    99,    41,    42,    81,
      82,    19,   145,   107,   108,   126,   143,   111,   100,   132,
     112,   146,   147,    43,    44,   127,    38,   129,    39,   127,
     137,   138,   139,   140,    66,    67,   144,    68,    60,    59,
     136,    57,    58,    69,    70,    71,    72,   118,   119,   155,
     156,   157,   158,   142,   148,   149,   151,   150,   136,   160,
     161,   162,   163,   154,    47,   159
  };

  /* YYCHECK.  */
  const unsigned char
  Parser::yycheck_[] =
  {
         0,     0,    83,     4,    92,     0,    30,    31,     5,     6,
       7,     4,    50,     4,    29,    28,     6,     7,    33,     9,
      20,    20,     6,    61,     9,    20,    27,    24,    25,    26,
      31,    32,    29,    34,    27,    32,    27,    31,    31,    77,
      31,    31,   123,   131,    32,    31,     9,    31,    33,     4,
      31,     0,    29,    53,    54,    55,    33,     0,    31,    47,
      59,    60,     5,     6,     7,     8,     4,    10,    11,    12,
      33,    20,    27,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    84,     6,    28,    29,     9,    27,
      89,    33,    92,     1,    93,     6,     4,     5,     6,     7,
       8,     4,    10,    11,    12,     4,     7,     9,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       5,    31,     7,     6,    27,     6,     7,    31,    27,   129,
      13,   131,    32,   133,    34,    18,    19,     6,     7,    24,
      25,    26,     7,    24,    25,    89,    30,     6,    31,    93,
       9,    16,    17,    22,    23,    89,    32,    31,    34,    93,
      14,    15,    16,    17,     6,     7,     9,     9,    31,    31,
      33,     6,     7,     6,     7,     6,     7,     6,     7,     6,
       7,     6,     7,    31,     7,     9,    30,     9,    33,     9,
       9,     9,     9,   134,    20,   142
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     1,     5,     6,     7,     8,    10,    11,    12,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      36,    37,    40,    41,    42,    49,    51,    53,    54,    57,
      58,    60,    61,    62,    65,    66,    67,    68,    32,    34,
      59,     6,     7,    22,    23,    56,     0,    61,     4,    27,
      38,    39,    28,    31,    31,    29,    33,     6,     7,    31,
      31,    38,    32,    34,     6,     9,     6,     7,     9,     6,
       7,     6,     7,     6,     7,     9,    31,    38,    39,     6,
       7,    24,    25,    29,    32,    43,    44,    46,    47,    48,
      49,    50,    51,    52,    55,    57,    58,    13,    18,    19,
      31,    51,    63,    51,    51,     6,     7,    24,    25,    58,
      58,     6,     9,     9,     9,    33,     9,    33,     6,     7,
       7,    46,    51,    31,    31,    45,    52,    55,    58,    31,
      50,    51,    52,    28,    29,    33,    33,    14,    15,    16,
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
         0,    35,    37,    36,    36,    36,    36,    38,    38,    39,
      39,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    41,    41,    41,    42,    42,    43,    44,    44,    45,
      45,    46,    46,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    48,    49,    49,    50,    50,    51,    52,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    56,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    59,    59,    59,    59,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    64,    64,    65,    66,    67,    68
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     3,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     1,     4,     1,     2,     3,     1,
       0,     3,     1,     3,     2,     1,     1,     1,     1,     1,
       2,     2,     2,     3,     3,     1,     2,     1,     1,     4,
       1,     1,     1,     1,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     2,     2,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     3,     3,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     2,     1,     3,     4,     5,
       5,     3,     4,     5,     3,     4,     6,     6,     6,     4,
       6,     1,     0,     1,     3,     5,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
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
  "'.'", "'?'", "$accept", "lines", "$@1", "ends", "end_or_comment",
  "line", "assignment", "lhs", "rhs", "expression_list", "maybe_comma",
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
        36,     0,    -1,    -1,    37,    38,    -1,    36,    61,    38,
      -1,    61,    38,    -1,     1,    -1,    39,    -1,    38,    39,
      -1,     4,    -1,    27,    -1,    60,    -1,    11,    -1,    65,
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
      -1,    19,    -1,    13,    -1,    16,    -1,    17,    -1,    14,
      -1,    15,    -1,    20,    -1,    22,    -1,    21,    -1,    23,
      -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,    11,    14,    16,    18,    21,
      23,    25,    27,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    48,    52,    54,    56,    61,    63,    66,    70,
      72,    73,    77,    79,    83,    86,    88,    90,    92,    94,
      96,    99,   102,   105,   109,   113,   115,   118,   120,   122,
     127,   129,   131,   133,   135,   139,   143,   147,   151,   153,
     155,   157,   159,   161,   164,   167,   171,   175,   179,   183,
     186,   189,   192,   195,   198,   202,   206,   208,   210,   212,
     215,   217,   219,   221,   223,   226,   229,   231,   235,   240,
     246,   252,   256,   261,   267,   271,   276,   283,   290,   297,
     302,   309,   311,   312,   314,   318,   324,   329,   331,   333,
     335,   337,   339,   341,   343,   345,   347,   349
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   143,   143,   143,   145,   146,   147,   151,   152,   155,
     156,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   173,   174,   175,   178,   179,   182,   185,   186,   190,
     191,   195,   196,   199,   200,   201,   202,   203,   204,   205,
     211,   212,   213,   217,   218,   223,   224,   227,   231,   232,
     233,   239,   240,   241,   242,   243,   244,   245,   250,   251,
     252,   253,   254,   255,   256,   259,   260,   261,   262,   266,
     267,   268,   269,   270,   274,   275,   279,   280,   281,   282,
     283,   284,   287,   288,   289,   290,   293,   296,   297,   298,
     299,   300,   301,   302,   303,   305,   306,   307,   308,   309,
     310,   311,   312,   315,   316,   317,   318,   322,   323,   324,
     328,   329,   330,   331,   336,   342,   348,   354
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
  const int Parser::yylast_ = 195;
  const int Parser::yynnts_ = 34;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 46;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 35;

  const unsigned int Parser::yyuser_token_number_max_ = 280;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // DefCompiler

/* Line 1054 of lalr1.cc  */
#line 1911 "defparser.tab.c"


/* Line 1056 of lalr1.cc  */
#line 358 "..\\defcompiler\\defparser.y"

// Error function throws an exception (std::string) with the location and error message
void DefCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}



#undef bugon



