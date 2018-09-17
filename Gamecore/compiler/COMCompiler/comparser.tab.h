
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



#include <string>
#include <iostream>
#include "stack.hh"


/* Line 35 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace ComCompiler {

/* Line 35 of lalr1.cc  */
#line 54 "comparser.tab.h"
  class position;
  class location;

/* Line 35 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // ComCompiler

/* Line 35 of lalr1.cc  */
#line 64 "comparser.tab.h"

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

namespace ComCompiler {

/* Line 35 of lalr1.cc  */
#line 112 "comparser.tab.h"

  /// A Bison parser.
  class Parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 35 of lalr1.cc  */
#line 61 "..\\comcompiler\\comparser.y"

    int  			integerVal;
    double 			doubleVal;
    string*	stringVal;
    void*			cvalue;
    


/* Line 35 of lalr1.cc  */
#line 134 "comparser.tab.h"
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
     CMD_XOR = 260,
     CMD_LOGXOR = 261,
     CMD_LOGOR = 262,
     CMD_LOGAND = 263,
     COMP_OPERATORS = 264,
     CMD_GREATERTHANEQ = 265,
     CMD_LESSTHANEQ = 266,
     CMD_NOTEQ = 267,
     MATH_OPERATORS = 268,
     CMD_SQUARE = 269,
     LN = 270,
     FLOOR = 271,
     EXP = 272,
     UPLUS = 273,
     UMINUS = 274,
     KEY_TIME = 275,
     KEY_BUFFERTIME = 276,
     KEY_NAME = 277,
     KEYWORD = 278,
     KEY_IDENTIFIER = 279,
     FUNC_GETHITVAR = 280,
     FUNC_IDENTIFIER = 281,
     SELFANIMEXIST = 282,
     PROJCANCELTIME = 283,
     PLAYERIDEXIST = 284,
     PROJGUARDEDTIME = 285,
     PROJCONTACTTIME = 286,
     VAR = 287,
     TAN = 288,
     FUNC_FVAR = 289,
     FUNC_VAR = 290,
     FUNC_SYSVAR = 291,
     FUNC_CONST = 292,
     FUNC_LOG = 293,
     FUNC_PROJGUARDED = 294,
     FUNC_PROJHIT = 295,
     FUNC_PROJCONTACT = 296,
     KANIM = 297,
     FUNC_IFELSE = 298,
     KEY_TRIGGER = 299,
     EOL = 300,
     ID = 301,
     QUOTESTRING = 302,
     NEGONE = 303,
     DATA = 304,
     ATTACK = 305,
     DEFENCE = 306,
     FALLDEFUP = 307,
     LIEDOWTIME = 308,
     AIRJUGGLE = 309,
     SPARKNO = 310,
     GUARDSPARKNO = 311,
     KOECHO = 312,
     VOLUME = 313,
     INTEGERINDEX = 314,
     FLOATINDEX = 315,
     SIZE = 316,
     XSCALE = 317,
     YSCALE = 318,
     GROUNDBACK = 319,
     GROUNDFRONT = 320,
     AIRBACK = 321,
     AIRFRONT = 322,
     HEIGHT = 323,
     ATTACKDIST = 324,
     PROJATTDIST = 325,
     PROJDOSCALE = 326,
     HEADPOSX = 327,
     HEADPOSY = 328,
     MIDPOSX = 329,
     MIDPOSY = 330,
     SHADOWOFFSET = 331,
     DRAWOFFSETX = 332,
     DRAWOFFSETY = 333,
     VELOCITY = 334,
     WALKFWD = 335,
     WALKBACK = 336,
     RUNFWDX = 337,
     RUNFWDY = 338,
     RUNBACKX = 339,
     RUNBACKY = 340,
     JUMPNEU = 341,
     JUMPBACK = 342,
     JUMPFWD = 343,
     RUNJUMPBACK = 344,
     RUNJUMPFWD = 345,
     AIRJUMPNEU = 346,
     AIRJUMPBACK = 347,
     AIRJUMPFWD = 348,
     MOVEMENT = 349,
     AIRJUMPNUM = 350,
     AIRJUMPHEIGHT = 351,
     YACCEL = 352,
     STANDFRICTION = 353,
     CROUCHFRICTION = 354,
     KEY_TRIGGERALL = 355,
     IDENTIFIER = 356,
     CMD_STATEDEF = 357,
     KEY_PHYSICS = 358,
     CMD_STATE = 359,
     ANIMELEM = 360,
     FVAR = 361,
     HITCOUNT = 362,
     HITDEFATTR = 363,
     ISHELPER = 364,
     MOVECONTACT = 365,
     PROJGUARDED = 366,
     PROJHITTIME = 367,
     STATENO = 368,
     TNULL = 369,
     AFTERIMAGE = 370,
     AFTERIMAGETIME = 371,
     ALLPALFX = 372,
     ANGLEADD = 373,
     ANGLEDRAW = 374,
     ANGLEMUL = 375,
     ANGLESET = 376,
     APPENDTOCLIPBOARD = 377,
     ASSERTSPECIAL = 378,
     ATTACKMULSET = 379,
     BGPALFX = 380,
     BINDTOPARENT = 381,
     BINDTOROOT = 382,
     BINDTOTARGET = 383,
     CHANGEANIME = 384,
     CHANGEANIME2 = 385,
     CHANGESTATE = 386,
     CLEARCLIPBOARD = 387,
     CTRLSET = 388,
     DEFENCEMULSET = 389,
     DESTROYSELF = 390,
     DISPLAYTOCLIPBOARD = 391,
     ENVSHAKE = 392,
     EXPLOD = 393,
     EXPLODBINDTIME = 394,
     FALLENVSHAKE = 395,
     FORCEFEDDBACK = 396,
     GAMEMAKEANIM = 397,
     GRAVITY = 398,
     HELPER = 399,
     HITADD = 400,
     HITBY = 401,
     KEY_HITDEF = 402,
     HITFALLDAMAGE = 403,
     HITFALLSET = 404,
     HITFALLVEL = 405,
     HITOVERRIDE = 406,
     HITVELSET = 407,
     LIFEADD = 408,
     LIFESET = 409,
     MAKEDUST = 410,
     MODIFYEXPLOD = 411,
     MOVEHITRESET = 412,
     NOTHITBY = 413,
     NUL = 414,
     OFFSET = 415,
     PALFX = 416,
     PARENTVARADD = 417,
     PARENTVARSET = 418,
     PAUSE = 419,
     PLAYERPUSH = 420,
     PLAYSND = 421,
     POSADD = 422,
     POSFREEZ = 423,
     POSSET = 424,
     POWERSET = 425,
     PROJECTILE = 426,
     REMOVEEXPLOD = 427,
     REVERSALDEF = 428,
     SCREENBOUND = 429,
     SELFSTATE = 430,
     SNDPAN = 431,
     STATETYPESET = 432,
     STOPSND = 433,
     SUPERPAUSE = 434,
     TARGETBIND = 435,
     TARGETDROP = 436,
     TARGETFACING = 437,
     TARGETLIFEADD = 438,
     TARGETPOWERADD = 439,
     TARGETSTATE = 440,
     TARGETVELADD = 441,
     TARGETVELSET = 442,
     TURN = 443,
     VARADD = 444,
     VARRANDOM = 445,
     VARRANGESET = 446,
     VARSET = 447,
     VELADD = 448,
     VELMUL = 449,
     WIDTH = 450,
     LENGTH = 451,
     PALCOLOR = 452,
     PALINVERTALL = 453,
     PALBRIGHT = 454,
     PALCONTRAST = 455,
     PALPOSTBRIGHT = 456,
     PALADD = 457,
     PALMUL = 458,
     TIMEGAP = 459,
     FRAMEGAP = 460,
     TRANS = 461,
     ACBEGIN = 462,
     ACTION = 463,
     LOOPSTART = 464,
     CLSN2DEFAULT = 465,
     CLSN1DEFAULT = 466,
     CLSN2 = 467,
     CLSN1 = 468,
     HORIZONTALFLIP = 469,
     VERTIKALFLIP = 470,
     HVFLIP = 471,
     ALPHA = 472,
     INFO = 473,
     DISPLAYNAME = 474,
     VERSIONSDATA = 475,
     MUGENVERSION = 476,
     AUTHOR = 477,
     FILES = 478,
     CMD = 479,
     CNS = 480,
     ST = 481,
     STCOMMON = 482,
     SPRITE = 483,
     SOUND = 484,
     PAL = 485,
     PALDEF = 486,
     ARCADE = 487,
     INTROSTORYBOARD = 488,
     ENDINGSTORYBOARD = 489,
     JUMPNEUY = 490,
     AIRJUMPNEUY = 491,
     KEY_FX = 492,
     KEY_SX = 493,
     CMD_KEY_DOWN = 494,
     CMD_KEY_FORWARD = 495,
     CMD_KEY_DOWN_FORWARD = 496,
     CMD_KEY_BACK = 497,
     CMD_KEY_DOWN_BACK = 498,
     CMD_KEY_UP_FORWARD = 499,
     CMD_KEY_UP = 500,
     CMD_KEY_UP_BACK = 501,
     CMD_BUTTON_A = 502,
     CMD_BUTTON_B = 503,
     CMD_BUTTON_C = 504,
     CMD_BUTTON_X = 505,
     CMD_BUTTON_Y = 506,
     CMD_BUTTON_Z = 507,
     CMD_BUTTON_S = 508,
     KEY_COMMAND = 509,
     KEY_DEFAULTS = 510,
     KEY_STATETYPE = 511,
     KEY_TYPE = 512,
     KEY_ANIM = 513,
     HELPER_IDENTIFIER = 514,
     CONST_PARAM = 515,
     COMMENT = 516
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
    static const signed char yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const signed char yytable_[];
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
    static const unsigned char yyprhs_[];
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

} // ComCompiler

/* Line 35 of lalr1.cc  */
#line 582 "comparser.tab.h"



#endif /* ! defined PARSER_HEADER_H */
