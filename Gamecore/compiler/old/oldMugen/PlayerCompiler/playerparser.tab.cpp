
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
#define yylex   PlayerCompilerlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 6 "..\\playercompiler\\playerparser.y"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <queue>

#include "../../objects/player.h"
#include "../../util/debug.h"


/* Line 311 of lalr1.cc  */
#line 55 "playerparser.tab.c"


#include "playerparser.tab.h"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 107 "..\\playercompiler\\playerparser.y"


#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 78 "playerparser.tab.c"

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

namespace PlayerCompiler {

/* Line 380 of lalr1.cc  */
#line 147 "playerparser.tab.c"
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
#line 61 "..\\playercompiler\\playerparser.y"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 254 "playerparser.tab.c"
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
#line 34 "..\\playercompiler\\playerparser.y"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 340 "playerparser.tab.c"

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
#line 131 "..\\playercompiler\\playerparser.y"
    {/**/}
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 132 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strName=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"NAME= "<<$3<<endl;*/}
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 133 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strDisplayName=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Displayname= "<<$3<<endl;*/}
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 134 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.CharVersion.Days=(yysemantic_stack_[(8) - (3)].integerVal); 
                                                 driver.Player->myPlayerDataPlus.CharVersion.Month=(yysemantic_stack_[(8) - (5)].integerVal);
                                                 driver.Player->myPlayerDataPlus.CharVersion.Years=(yysemantic_stack_[(8) - (7)].integerVal);/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 137 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.CharVersion.Days=(yysemantic_stack_[(8) - (3)].integerVal); 
                                                 driver.Player->myPlayerDataPlus.CharVersion.Month=(yysemantic_stack_[(8) - (5)].integerVal);
                                                 driver.Player->myPlayerDataPlus.CharVersion.Years=(yysemantic_stack_[(8) - (7)].integerVal);/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 140 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.CharVersion.Days=(yysemantic_stack_[(8) - (3)].integerVal); 
                                                 driver.Player->myPlayerDataPlus.CharVersion.Month=(yysemantic_stack_[(8) - (5)].integerVal);
                                                 driver.Player->myPlayerDataPlus.CharVersion.Years=(yysemantic_stack_[(8) - (7)].integerVal);/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 144 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.MugenVersion.Days=(yysemantic_stack_[(8) - (3)].integerVal); 
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Month=(yysemantic_stack_[(8) - (5)].integerVal);
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Years=(yysemantic_stack_[(8) - (7)].integerVal);/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 147 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.MugenVersion.Days=(yysemantic_stack_[(8) - (3)].integerVal); 
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Month=(yysemantic_stack_[(8) - (5)].integerVal);
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Years=(yysemantic_stack_[(8) - (7)].integerVal);/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 150 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.MugenVersion.Days=(yysemantic_stack_[(8) - (3)].integerVal); 
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Month=(yysemantic_stack_[(8) - (5)].integerVal);
                                                 driver.Player->myPlayerDataPlus.MugenVersion.Years=(yysemantic_stack_[(8) - (7)].integerVal);/*Debug::debug(10,__FUNCTION__) <<"Versiondate (MM-DD-YYYY)= "<<$3 <<" - "<< $5 <<" - " <<$7<< endl;*/}
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 154 "..\\playercompiler\\playerparser.y"
    {/*Debug::debug(10,__FUNCTION__) <<"Author= "<<$3<<endl);*/driver.Player->myPlayerDataPlus.strAuthor=*(yysemantic_stack_[(4) - (3)].stringVal);}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 155 "..\\playercompiler\\playerparser.y"
    {}
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 156 "..\\playercompiler\\playerparser.y"
    {}
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 157 "..\\playercompiler\\playerparser.y"
    {}
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 162 "..\\playercompiler\\playerparser.y"
    {/*Check Files CSection*/}
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 163 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strCmdFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 164 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strCnsFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 165 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strSttFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 166 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strComFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 167 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strSffFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 168 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strAirFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 169 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strSndFile=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 170 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[0]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 171 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[1]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 172 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[2]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 173 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[3]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 174 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[4]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 175 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[5]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 176 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[6]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 177 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[7]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 178 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[8]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 179 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[9]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 180 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[10]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 181 "..\\playercompiler\\playerparser.y"
    {driver.Player->myPlayerDataPlus.strPalFile[11]=*(yysemantic_stack_[(4) - (3)].stringVal);/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 185 "..\\playercompiler\\playerparser.y"
    {/*Check Arcade CSection*/}
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 186 "..\\playercompiler\\playerparser.y"
    {/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 187 "..\\playercompiler\\playerparser.y"
    {}
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 188 "..\\playercompiler\\playerparser.y"
    {/*Debug::debug(10,__FUNCTION__) <<"Filename= "<<$3<< endl;*/}
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 189 "..\\playercompiler\\playerparser.y"
    {}
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 192 "..\\playercompiler\\playerparser.y"
    {Debug::debug(10,__FUNCTION__) <<"PalNumber= "<<(yysemantic_stack_[(2) - (1)].integerVal)<< endl;}
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 193 "..\\playercompiler\\playerparser.y"
    {Debug::debug(10,__FUNCTION__) <<"PalNumber= "<<(yysemantic_stack_[(4) - (1)].integerVal)<< endl;}
    break;



/* Line 678 of lalr1.cc  */
#line 751 "playerparser.tab.c"
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
  const signed char Parser::yypact_ninf_ = -44;
  const short int
  Parser::yypact_[] =
  {
         0,     7,   -44,    35,   -44,   -44,    -9,     5,     9,    11,
      13,    15,    42,    45,    49,    50,    57,    80,    82,    83,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    62,   -44,   -44,   -44,    14,    17,    12,
     107,     6,    10,   -43,   -41,    54,    55,    56,    58,    60,
      61,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     2,     3,    74,    75,    76,   112,   117,    -5,
       1,   -44,   129,   -44,     4,   -44,   130,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   -44,   -44,   -44,   -44,   152,
     153,   154,   -44,   -44,   155,   156,   157,   158,   159,   160,
     -44,   -44,   161,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   162,   163,   132,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   -44,   175,
     176,   177,   178,   179,   180,   -44,   -44,   -44,   -44,   -44,
     -44
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     4,     0,     5,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,    19,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     0,    18,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    42,    45,    44,     0,
       0,     0,     7,     8,     0,     0,     0,     0,     0,     0,
      15,    46,     0,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     6,    21,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       0,     0,     0,     0,     0,    11,     9,    10,    12,    14,
      13
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -44,   -44,   -44,   -44,   -44,    78
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     3,    34,    35,    36,    75
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -3;
  const short int
  Parser::yytable_[] =
  {
        -2,     1,   104,     2,    37,    95,    97,   111,   107,    71,
       4,   112,    72,    73,    74,    76,    69,    77,    38,   105,
      67,   106,    39,    68,    40,   108,    41,   109,    42,    -2,
      -2,    -2,    -2,    -2,    -2,     5,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    43,    -2,    -2,    44,    -2,
      96,    98,    45,    46,     6,     7,     8,     9,    10,    11,
      47,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      64,    31,    32,    48,    33,    49,    50,    65,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    70,    78,    79,    80,   102,    81,    66,    82,    83,
     103,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,   110,   113,    99,   100,   101,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   144,   135,
     136,   137,   138,   139,   140,    74,     0,     0,     0,   142,
     148,   145,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,     0,     0,     0,   143,     0,   146,
     141,     0,   147
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         0,     1,     7,     3,    13,     3,     3,     3,     7,     3,
       3,     7,     6,     3,     4,    58,     4,    58,    13,    24,
       6,    26,    13,     6,    13,    24,    13,    26,    13,    29,
      30,    31,    32,    33,    34,     0,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    13,    56,    57,    13,    59,
      58,    58,    13,    13,    29,    30,    31,    32,    33,    34,
      13,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      28,    56,    57,    13,    59,    13,    13,    35,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,     4,    58,    58,    58,     3,    58,    55,    58,    58,
       3,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,     3,     3,    60,    60,    60,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,    26,     4,
       4,     4,     4,     4,     4,     4,    -1,    -1,    -1,     7,
       3,     7,     4,     4,     4,     4,     4,     4,     3,     3,
       3,     3,     3,     3,    -1,    -1,    -1,    24,    -1,    24,
     112,    -1,    26
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     1,     3,    62,     3,     0,    29,    30,    31,    32,
      33,    34,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    56,    57,    59,    63,    64,    65,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    28,    35,    55,     6,     6,     4,
       4,     3,     6,     3,     4,    66,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,     3,    58,     3,    58,    60,
      60,    60,     3,     3,     7,    24,    26,     7,    24,    26,
       3,     3,     7,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     4,     4,     4,
       4,    66,     7,    24,    26,     7,    24,    26,     3,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,    44,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,    43,    45,    42,    47,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,    91,
      93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    65,    65,    65,    66,    66
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     1,     2,     4,     4,     4,     8,
       8,     8,     8,     8,     8,     4,     3,     3,     3,     1,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     3,     3,     3,     2,     4
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"integer\"", "\"double\"", "\"string\"", "','", "GREATEREQUAL",
  "LESSEQUAL", "LESS", "GREATER", "NOTEQUAL", "EQUAL", "XOR", "OR", "AND",
  "NOT", "LOGXOR", "LOGOR", "LOGAND", "LOGNOT", "MOD", "'+'", "'-'", "'*'",
  "'/'", "SQUARE", "INFO", "NAME", "DISPLAYNAME", "VERSIONDATE",
  "MUGENVERSION", "AUTHOR", "PALDEFAULTS", "FILES", "COMAND", "CNS",
  "STATES", "COMESTATES", "SPRITES", "ANIMATION", "SOUNDS", "PALLETE1",
  "PALLETE2", "PALLETE3", "PALLETE4", "PALLETE5", "PALLETE6", "PALLETE7",
  "PALLETE8", "PALLETE9", "PALLETE10", "PALLETE11", "PALLETE12", "ARCADE",
  "INTRO", "ENDING", "FILENAME", "'['", "']'", "$accept", "lines",
  "INFOSECTION", "FILESSECTION", "ARCADESECTION", "expression", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        62,     0,    -1,    -1,    62,    63,    -1,     3,    -1,     1,
       3,    -1,    59,    28,    60,     3,    -1,    29,    13,     6,
       3,    -1,    30,    13,     6,     3,    -1,    31,    13,     4,
      24,     4,    24,     4,     3,    -1,    31,    13,     4,    26,
       4,    26,     4,     3,    -1,    31,    13,     4,     7,     4,
       7,     4,     3,    -1,    32,    13,     4,     7,     4,     7,
       4,     3,    -1,    32,    13,     4,    26,     4,    26,     4,
       3,    -1,    32,    13,     4,    24,     4,    24,     4,     3,
      -1,    33,    13,     6,     3,    -1,    33,    13,     3,    -1,
      34,    13,    66,    -1,    34,    13,     3,    -1,    64,    -1,
      65,    -1,    59,    35,    60,     3,    -1,    36,    13,    58,
       3,    -1,    37,    13,    58,     3,    -1,    38,    13,    58,
       3,    -1,    39,    13,    58,     3,    -1,    40,    13,    58,
       3,    -1,    41,    13,    58,     3,    -1,    42,    13,    58,
       3,    -1,    43,    13,    58,     3,    -1,    44,    13,    58,
       3,    -1,    45,    13,    58,     3,    -1,    46,    13,    58,
       3,    -1,    47,    13,    58,     3,    -1,    48,    13,    58,
       3,    -1,    49,    13,    58,     3,    -1,    50,    13,    58,
       3,    -1,    51,    13,    58,     3,    -1,    52,    13,    58,
       3,    -1,    53,    13,    58,     3,    -1,    54,    13,    58,
       3,    -1,    59,    55,    60,     3,    -1,    56,    13,    58,
      -1,    56,    13,     3,    -1,    57,    13,    58,    -1,    57,
      13,     3,    -1,     4,     3,    -1,     4,     7,    66,     3,
      -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     9,    12,    17,    22,    27,
      36,    45,    54,    63,    72,    81,    86,    90,    94,    98,
     100,   102,   107,   112,   117,   122,   127,   132,   137,   142,
     147,   152,   157,   162,   167,   172,   177,   182,   187,   192,
     197,   202,   207,   211,   215,   219,   223,   226
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,   124,   124,   125,   126,   127,   131,   132,   133,   134,
     137,   140,   144,   147,   150,   154,   155,   156,   157,   158,
     159,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   185,   186,   187,   188,   189,   192,   193
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
       2,     2,    25,    23,     7,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,     2,     2,     2,     2,     2,     2,
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
       5,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 192;
  const int Parser::yynnts_ = 6;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 5;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 61;

  const unsigned int Parser::yyuser_token_number_max_ = 308;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // PlayerCompiler

/* Line 1054 of lalr1.cc  */
#line 1303 "playerparser.tab.c"


/* Line 1056 of lalr1.cc  */
#line 199 "..\\playercompiler\\playerparser.y"


// Error function throws an exception (std::string) with the location and error message
void PlayerCompiler::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}





