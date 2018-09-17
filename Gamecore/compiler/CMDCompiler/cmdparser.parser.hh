
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
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

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

/* "%code requires" blocks.  */

/* Line 35 of lalr1.cc  */
#line 60 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"

typedef struct  triggerRedir
	{
	triggerRedir():identifier(""),id(0){};
	std::string identifier;
	int id;
	}triggerRedirtype;



/* Line 35 of lalr1.cc  */
#line 56 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.hh"


#include <string>
#include <iostream>
#include "stack.hh"


/* Line 35 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace CmdCompiler {

/* Line 35 of lalr1.cc  */
#line 70 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.hh"
  class position;
  class location;

/* Line 35 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // CmdCompiler

/* Line 35 of lalr1.cc  */
#line 80 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.hh"

#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
do {							\
  if (N)						\
    {							\
      (Current).begin = (Rhs)[1].begin;			\
      (Current).end   = (Rhs)[N].end;			\
    }							\
  else							\
    {							\
      (Current).begin = (Current).end = (Rhs)[0].end;	\
    }							\
} while (false)
#endif


/* Line 35 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace CmdCompiler {

/* Line 35 of lalr1.cc  */
#line 128 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.hh"

  /// A Bison parser.
  class Parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 35 of lalr1.cc  */
#line 68 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler\\cmdparser.y"

    int  			integerVal;
    double 			doubleVal;
    std::string*	stringVal;
    void*			cvalue;
	triggerRedirtype * redirValue;
    


/* Line 35 of lalr1.cc  */
#line 151 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.hh"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     END = 0,
     NUMBER = 258,
     LOGICAL_OPERATORS = 259,
     CMD_LOGXOR = 260,
     CMD_LOGAND = 261,
     CMD_LOGOR = 262,
     CMD_XOR = 263,
     CMD_ASSIGN = 264,
     CMD_NOTEQ = 265,
     CMD_GREATERTHANEQ = 266,
     CMD_LESSTHANEQ = 267,
     COMP_OPERATORS = 268,
     MATH_OPERATORS = 269,
     CMD_SQUARE = 270,
     UPLUS = 271,
     UMINUS = 272,
     LN = 273,
     FLOOR = 274,
     EXP = 275,
     KEYWORD = 276,
     KEY_IDENTIFIER = 277,
     FUNC_IDENTIFIER = 278,
     EXPRESSIONLIST = 279,
     SELFANIMEXIST = 280,
     PROJCANCELTIME = 281,
     PLAYERIDEXIST = 282,
     PROJGUARDEDTIME = 283,
     PROJCONTACTTIME = 284,
     VAR = 285,
     TAN = 286,
     FUNC_FVAR = 287,
     FUNC_VAR = 288,
     FUNC_SYSVAR = 289,
     FUNC_CONST = 290,
     FUNC_LOG = 291,
     FUNC_PROJGUARDED = 292,
     FUNC_PROJHIT = 293,
     FUNC_PROJCONTACT = 294,
     KANIM = 295,
     FUNC_IFELSE = 296,
     KEY_TRIGGER = 297,
     EOL = 298,
     ID = 299,
     QUOTESTRING = 300,
     NEGONE = 301,
     DATA = 302,
     ATTACK = 303,
     DEFENCE = 304,
     FALLDEFUP = 305,
     LIEDOWTIME = 306,
     AIRJUGGLE = 307,
     SPARKNO = 308,
     GUARDSPARKNO = 309,
     KOECHO = 310,
     VOLUME = 311,
     INTEGERINDEX = 312,
     FLOATINDEX = 313,
     SIZE = 314,
     XSCALE = 315,
     YSCALE = 316,
     GROUNDBACK = 317,
     GROUNDFRONT = 318,
     AIRBACK = 319,
     AIRFRONT = 320,
     HEIGHT = 321,
     ATTACKDIST = 322,
     PROJATTDIST = 323,
     PROJDOSCALE = 324,
     HEADPOSX = 325,
     HEADPOSY = 326,
     MIDPOSX = 327,
     MIDPOSY = 328,
     SHADOWOFFSET = 329,
     DRAWOFFSETX = 330,
     DRAWOFFSETY = 331,
     VELOCITY = 332,
     WALKFWD = 333,
     WALKBACK = 334,
     RUNFWDX = 335,
     RUNFWDY = 336,
     RUNBACKX = 337,
     RUNBACKY = 338,
     JUMPNEU = 339,
     JUMPBACK = 340,
     JUMPFWD = 341,
     RUNJUMPBACK = 342,
     RUNJUMPFWD = 343,
     AIRJUMPNEU = 344,
     AIRJUMPBACK = 345,
     AIRJUMPFWD = 346,
     MOVEMENT = 347,
     AIRJUMPNUM = 348,
     AIRJUMPHEIGHT = 349,
     YACCEL = 350,
     STANDFRICTION = 351,
     CROUCHFRICTION = 352,
     KEY_TRIGGERALL = 353,
     IDENTIFIER = 354,
     CMD_STATEDEF = 355,
     KEY_PHYSICS = 356,
     CMD_STATE = 357,
     ANIMELEM = 358,
     FVAR = 359,
     HITCOUNT = 360,
     HITDEFATTR = 361,
     ISHELPER = 362,
     MOVECONTACT = 363,
     PROJGUARDED = 364,
     PROJHITTIME = 365,
     STATENO = 366,
     TNULL = 367,
     AFTERIMAGE = 368,
     AFTERIMAGETIME = 369,
     ALLPALFX = 370,
     ANGLEADD = 371,
     ANGLEDRAW = 372,
     ANGLEMUL = 373,
     ANGLESET = 374,
     APPENDTOCLIPBOARD = 375,
     ASSERTSPECIAL = 376,
     ATTACKMULSET = 377,
     BGPALFX = 378,
     BINDTOPARENT = 379,
     BINDTOROOT = 380,
     BINDTOTARGET = 381,
     CHANGEANIME = 382,
     CHANGEANIME2 = 383,
     CHANGESTATE = 384,
     CLEARCLIPBOARD = 385,
     CTRLSET = 386,
     DEFENCEMULSET = 387,
     DESTROYSELF = 388,
     DISPLAYTOCLIPBOARD = 389,
     ENVSHAKE = 390,
     EXPLOD = 391,
     EXPLODBINDTIME = 392,
     FALLENVSHAKE = 393,
     FORCEFEDDBACK = 394,
     GAMEMAKEANIM = 395,
     GRAVITY = 396,
     HELPER = 397,
     HITADD = 398,
     HITBY = 399,
     KEY_HITDEF = 400,
     HITFALLDAMAGE = 401,
     HITFALLSET = 402,
     HITFALLVEL = 403,
     HITOVERRIDE = 404,
     HITVELSET = 405,
     LIFEADD = 406,
     LIFESET = 407,
     MAKEDUST = 408,
     MODIFYEXPLOD = 409,
     MOVEHITRESET = 410,
     NOTHITBY = 411,
     NUL = 412,
     OFFSET = 413,
     PALFX = 414,
     PARENTVARADD = 415,
     PARENTVARSET = 416,
     PAUSE = 417,
     PLAYERPUSH = 418,
     PLAYSND = 419,
     POSADD = 420,
     POSFREEZ = 421,
     POSSET = 422,
     POWERSET = 423,
     PROJECTILE = 424,
     REMOVEEXPLOD = 425,
     REVERSALDEF = 426,
     SCREENBOUND = 427,
     SELFSTATE = 428,
     SNDPAN = 429,
     STATETYPESET = 430,
     STOPSND = 431,
     SUPERPAUSE = 432,
     TARGETBIND = 433,
     TARGETDROP = 434,
     TARGETFACING = 435,
     TARGETLIFEADD = 436,
     TARGETPOWERADD = 437,
     TARGETSTATE = 438,
     TARGETVELADD = 439,
     TARGETVELSET = 440,
     TURN = 441,
     VARADD = 442,
     VARRANDOM = 443,
     VARRANGESET = 444,
     VARSET = 445,
     VELADD = 446,
     VELMUL = 447,
     WIDTH = 448,
     LENGTH = 449,
     PALCOLOR = 450,
     PALINVERTALL = 451,
     PALBRIGHT = 452,
     PALCONTRAST = 453,
     PALPOSTBRIGHT = 454,
     PALADD = 455,
     PALMUL = 456,
     TIMEGAP = 457,
     FRAMEGAP = 458,
     TRANS = 459,
     ACBEGIN = 460,
     ACTION = 461,
     LOOPSTART = 462,
     CLSN2DEFAULT = 463,
     CLSN1DEFAULT = 464,
     CLSN2 = 465,
     CLSN1 = 466,
     HORIZONTALFLIP = 467,
     VERTIKALFLIP = 468,
     HVFLIP = 469,
     ALPHA = 470,
     INFO = 471,
     DISPLAYNAME = 472,
     VERSIONSDATA = 473,
     MUGENVERSION = 474,
     AUTHOR = 475,
     FILES = 476,
     CMD = 477,
     CNS = 478,
     ST = 479,
     STCOMMON = 480,
     SPRITE = 481,
     SOUND = 482,
     PAL = 483,
     PALDEF = 484,
     ARCADE = 485,
     INTROSTORYBOARD = 486,
     ENDINGSTORYBOARD = 487,
     JUMPNEUY = 488,
     AIRJUMPNEUY = 489,
     KEY_FX = 490,
     KEY_SX = 491,
     CMD_KEY_DOWN = 492,
     CMD_KEY_FORWARD = 493,
     CMD_KEY_DOWN_FORWARD = 494,
     CMD_KEY_BACK = 495,
     CMD_KEY_DOWN_BACK = 496,
     CMD_KEY_UP_FORWARD = 497,
     CMD_KEY_UP = 498,
     CMD_KEY_UP_BACK = 499,
     CMD_BUTTON_A = 500,
     CMD_BUTTON_B = 501,
     CMD_BUTTON_C = 502,
     CMD_BUTTON_X = 503,
     CMD_BUTTON_Y = 504,
     CMD_BUTTON_Z = 505,
     CMD_BUTTON_S = 506,
     KEY_STATETYPE = 507,
     KEY_TYPE = 508,
     KEY_ANIM = 509,
     TRIGGER_REDIRECTION_IDENTIFIER = 510,
     CONST_PARAM = 511,
     COMMENT = 512
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    Parser (class Driver& driver_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Internal symbol numbers.
    typedef unsigned short int token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default rule to reduce.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned char yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const short int yytable_[];
    static const signed char yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned short int yystos_[];

    /// For a rule, its LHS.
    static const unsigned short int yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif

#if YYERROR_VERBOSE
    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    virtual std::string yytnamerr_ (const char *n);
#endif

#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    class Driver& driver;
  };

/* Line 35 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // CmdCompiler

/* Line 35 of lalr1.cc  */
#line 595 "D:\\Projetos\\c++\\GameEngine\\sgf\\Gamecore\\compiler\\CMDCompiler/cmdparser.parser.hh"



#endif /* ! defined PARSER_HEADER_H */
