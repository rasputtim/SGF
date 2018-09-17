
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "PraserRules.txt"

#include <malloc.h>  /// _alloca is used by the parser
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "../Structs.h"
#include "../objects/Player.h"
//#include "StateManager.h"


CPlayer *m_pPlayer;
CStateManager *myStateManager;

void yyerror(char *msg);
void SetPlayer(CPlayer *p);
void SetStateManager(CStateManager *p);


#define YYSTYPE myType



/* Line 189 of yacc.c  */
#line 98 "yacc.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     XOR = 258,
     OR = 259,
     AND = 260,
     NOT = 261,
     LOGXOR = 262,
     LOGOR = 263,
     LOGAND = 264,
     LOGNOT = 265,
     MOD = 266,
     GREATEREQUAL = 267,
     LESSEQUAL = 268,
     LESS = 269,
     GREATER = 270,
     NOTEQUAL = 271,
     EQUAL = 272,
     SQUARE = 273,
     LN = 274,
     GETHITVAR = 275,
     FLOOR = 276,
     EXP = 277,
     COS = 278,
     CEIL = 279,
     ATAN = 280,
     ASIN = 281,
     ANIMEXIST = 282,
     ANIMELEMTIME = 283,
     ANIMELEMNO = 284,
     ABS = 285,
     ACOS = 286,
     SYSVAR = 287,
     SYSFVAR = 288,
     SIN = 289,
     SELFANIMEXIST = 290,
     PROJCANCLETIME = 291,
     PLAYERIDEXIST = 292,
     NUMTARGET = 293,
     NUMPROJID = 294,
     NUMHELPER = 295,
     NUMEXPLOD = 296,
     PROJGUARDEDTIME = 297,
     PROJCONTACTTIME = 298,
     VAR = 299,
     TAN = 300,
     CONST = 301,
     LOG = 302,
     IFELSE = 303,
     UMINUS = 304,
     UPLUS = 305,
     ID = 306,
     STRING = 307,
     NEGONE = 308,
     DATA = 309,
     ATTACK = 310,
     DEFENCE = 311,
     FALLDEFUP = 312,
     LIEDOWTIME = 313,
     AIRJUGGLE = 314,
     SPARKNO = 315,
     GUARDSPARKNO = 316,
     KOECHO = 317,
     VOLUME = 318,
     INTEGERINDEX = 319,
     FLOATINDEX = 320,
     SIZE = 321,
     XSCALE = 322,
     YSCALE = 323,
     GROUNDBACK = 324,
     GROUNDFRONT = 325,
     AIRBACK = 326,
     AIRFRONT = 327,
     HEIGHT = 328,
     ATTACKDIST = 329,
     PROJATTDIST = 330,
     PROJDOSCALE = 331,
     HEADPOSX = 332,
     HEADPOSY = 333,
     MIDPOSX = 334,
     MIDPOSY = 335,
     SHADOWOFFSET = 336,
     DRAWOFFSETX = 337,
     DRAWOFFSETY = 338,
     VELOCITY = 339,
     WALKFWD = 340,
     WALKBACK = 341,
     RUNFWDX = 342,
     RUNFWDY = 343,
     RUNBACKX = 344,
     RUNBACKY = 345,
     JUMPNEU = 346,
     JUMPBACK = 347,
     JUMPFWD = 348,
     RUNJUMPBACK = 349,
     RUNJUMPFWD = 350,
     AIRJUMPNEU = 351,
     AIRJUMPBACK = 352,
     AIRJUMPFWD = 353,
     MOVEMENT = 354,
     AIRJUMPNUM = 355,
     AIRJUMPHEIGHT = 356,
     YACCEL = 357,
     STANDFRICTION = 358,
     CROUCHFRICTION = 359,
     NUMBER = 360,
     TRIGGER = 361,
     TRIGGERALL = 362,
     STATEDEF = 363,
     TYPE = 364,
     MOVETYPE = 365,
     PHYSICS = 366,
     ANIM = 367,
     JUGGLE = 368,
     FACEP2 = 369,
     HITDEFPERSIST = 370,
     MOVEHITPERSIST = 371,
     HITCOUNTPERSIST = 372,
     STATE = 373,
     ALIVE = 374,
     ANIMELEM = 375,
     ANIMTIME = 376,
     AUTHORNAME = 377,
     BACKEEDGEBODYDIST = 378,
     BACKEDGEDIST = 379,
     CANRECOVER = 380,
     COMMAND = 381,
     CTRL = 382,
     DRAWGAME = 383,
     FACING = 384,
     FRONTEDGEBODYDIST = 385,
     FRONTEDGEDIST = 386,
     FVAR = 387,
     GAMETIME = 388,
     HITCOUNT = 389,
     HITDEFATTR = 390,
     HITFALL = 391,
     HITOVER = 392,
     HITPAUSETIME = 393,
     HITSHAKEOVER = 394,
     HITVELX = 395,
     HITVELY = 396,
     PLID = 397,
     INGUARDDIST = 398,
     ISHELPER = 399,
     ISHOMETEAM = 400,
     LIFE = 401,
     LIFEMAX = 402,
     LOSE = 403,
     LOSEKO = 404,
     LOSETIME = 405,
     MATCHNO = 406,
     MATCHOVER = 407,
     MOVECONTACT = 408,
     MOVEGUARDED = 409,
     MOVEHIT = 410,
     MOVEREVERSED = 411,
     NAME = 412,
     NUMENEMY = 413,
     NUMPARTNER = 414,
     NUMPROJ = 415,
     P1NAME = 416,
     P2BODYDISTX = 417,
     P2BODYDISTY = 418,
     P2DISTX = 419,
     P2DISTY = 420,
     P2LIFE = 421,
     P2MOVETYPE = 422,
     P2NAME = 423,
     P2STATENO = 424,
     P2STATETYP = 425,
     P3NAME = 426,
     P4NAME = 427,
     PALNO = 428,
     PARENTDISTX = 429,
     PARENTDISTY = 430,
     PI = 431,
     PREVSTATENO = 432,
     POSX = 433,
     POSY = 434,
     POWER = 435,
     POWERMAX = 436,
     PROJCONTACT = 437,
     PROJGUARDED = 438,
     PROJHIT = 439,
     PROJHITTIME = 440,
     RANDOM = 441,
     ROOTDISTX = 442,
     ROOTDISTY = 443,
     ROUNDNO = 444,
     ROUNDSEXISTED = 445,
     ROUNDSTATE = 446,
     SCREENPOSX = 447,
     SCREENPOSY = 448,
     STATENO = 449,
     STATETYPE = 450,
     TEAMMODE = 451,
     TEAMSIDE = 452,
     TICKSPERSECOND = 453,
     TIME = 454,
     TIMEMODE = 455,
     UNIQHITCOUNT = 456,
     VELX = 457,
     VELY = 458,
     WIN = 459,
     WINKO = 460,
     WINTIME = 461,
     WINPERFECT = 462,
     TNULL = 463,
     AFTERIMAGE = 464,
     AFTERIMAGETIME = 465,
     ALLPALFX = 466,
     ANGLEADD = 467,
     ANGLEDRAW = 468,
     ANGLEMUL = 469,
     ANGLESET = 470,
     APPENDTOCLIPBOARD = 471,
     ASSERTSPECIAL = 472,
     ATTACKMULSET = 473,
     BGPALFX = 474,
     BINDTOPARENT = 475,
     BINDTOROOT = 476,
     BINDTOTARGET = 477,
     CHANGEANIME = 478,
     CHANGEANIME2 = 479,
     CHANGESTATE = 480,
     CLEARCLIPBOARD = 481,
     CTRLSET = 482,
     DEFENCEMULSET = 483,
     DESTROYSELF = 484,
     DISPLAYTOCLIPBOARD = 485,
     ENVSHAKE = 486,
     EXPLOD = 487,
     EXPLODBINDTIME = 488,
     FALLENVSHAKE = 489,
     FORCEFEDDBACK = 490,
     GAMEMAKEANIM = 491,
     GRAVITY = 492,
     HELPER = 493,
     HITADD = 494,
     HITBY = 495,
     HITDEF = 496,
     HITFALLDAMAGE = 497,
     HITFALLSET = 498,
     HITFALLVEL = 499,
     HITOVERRIDE = 500,
     HITVELSET = 501,
     LIFEADD = 502,
     LIFESET = 503,
     MAKEDUST = 504,
     MODIFYEXPLOD = 505,
     MOVEHITRESET = 506,
     NOTHITBY = 507,
     NUL = 508,
     OFFSET = 509,
     PALFX = 510,
     PARENTVARADD = 511,
     PARENTVARSET = 512,
     PAUSE = 513,
     PLAYERPUSH = 514,
     PLAYSND = 515,
     POSADD = 516,
     POSFREEZ = 517,
     POSSET = 518,
     POWERADD = 519,
     POWERSET = 520,
     PROJECTILE = 521,
     REMOVEEXPLOD = 522,
     REVERSALDEF = 523,
     SCREENBOUND = 524,
     SELFSTATE = 525,
     SNDPAN = 526,
     SPRPRIORITY = 527,
     STATETYPESET = 528,
     STOPSND = 529,
     SUPERPAUSE = 530,
     TARGETBIND = 531,
     TARGETDROP = 532,
     TARGETFACING = 533,
     TARGETLIFEADD = 534,
     TARGETPOWERADD = 535,
     TARGETSTATE = 536,
     TARGETVELADD = 537,
     TARGETVELSET = 538,
     TURN = 539,
     VARADD = 540,
     VARRANDOM = 541,
     VARRANGESET = 542,
     VARSET = 543,
     VELADD = 544,
     VELMUL = 545,
     VELSET = 546,
     WIDTH = 547,
     LENGTH = 548,
     PALCOLOR = 549,
     PALINVERTALL = 550,
     PALBRIGHT = 551,
     PALCONTRAST = 552,
     PALPOSTBRIGHT = 553,
     PALADD = 554,
     PALMUL = 555,
     TIMEGAP = 556,
     FRAMEGAP = 557,
     TRANS = 558,
     FVALUE = 559,
     ACBEGIN = 560,
     ACTION = 561,
     LOOPSTART = 562,
     CLSN2DEFAULT = 563,
     CLSN1DEFAULT = 564,
     CLSN2 = 565,
     CLSN1 = 566,
     HORIZONTALFLIP = 567,
     VERTIKALFLIP = 568,
     HVFLIP = 569,
     ALPHA = 570,
     INFO = 571,
     DISPLAYNAME = 572,
     VERSIONSDATA = 573,
     MUGENVERSION = 574,
     AUTHOR = 575,
     FILES = 576,
     CMD = 577,
     CNS = 578,
     ST = 579,
     STCOMMON = 580,
     SPRITE = 581,
     SOUND = 582,
     PAL = 583,
     PALDEF = 584,
     ARCADE = 585,
     INTROSTORYBOARD = 586,
     ENDINGSTORYBOARD = 587,
     VALUE = 588,
     VALUE2 = 589,
     XVALUE = 590,
     YVALUE = 591,
     ZVALUE = 592,
     JUMPNEUY = 593,
     AIRJUMPNEUY = 594,
     PERSISTENT = 595,
     IGNOREHITPAUSE = 596,
     SPACING = 597,
     POSXY = 598,
     WAVEFORM = 599,
     AMPL = 600,
     FREQ = 601,
     XVELADD = 602,
     YVELADD = 603,
     ANIMTYME = 604,
     AIRTYPE = 605,
     GROUNDTYPE = 606,
     DAMAGE = 607,
     FALLCOUNT = 608,
     HITSHAKETIME = 609,
     HITTIME = 610,
     SLIDETIME = 611,
     CTRLTIME = 612,
     RECOVERTIME = 613,
     XOFF = 614,
     YOFF = 615,
     ZOFF = 616,
     XVEL = 617,
     YVEL = 618,
     YACELL = 619,
     HITID = 620,
     CHAINID = 621,
     GUARDED = 622,
     FALL = 623,
     FALLDAMAGE = 624,
     FALLXVEL = 625,
     FALLYVEL = 626,
     FALLRECOVER = 627,
     FALLTIME = 628,
     FALLRECOVERTIME = 629,
     FALLKILL = 630,
     FALLENVTIME = 631,
     FALLENVFREQ = 632,
     FALLENVAMPL = 633,
     FALLENVDIR = 634,
     FALLENVPHASE = 635,
     FX = 636,
     ADD = 637,
     MUL = 638,
     SINADD = 639,
     INTERVALL = 640,
     COLOR = 641,
     UNDER = 642
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 527 "yacc.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3725

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  397
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  396
/* YYNRULES -- Number of states.  */
#define YYNSTATES  577

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   642

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     395,   396,    21,    19,     3,    20,     2,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   393,     2,   394,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    14,    18,    22,    26,
      30,    34,    38,    42,    46,    50,    54,    58,    62,    68,
      70,    77,    84,    91,    98,   106,   113,   115,   117,   119,
     123,   127,   131,   135,   139,   143,   147,   151,   155,   159,
     163,   167,   171,   175,   179,   183,   187,   191,   195,   199,
     203,   207,   211,   215,   219,   223,   227,   231,   235,   239,
     243,   247,   251,   255,   259,   263,   267,   271,   275,   279,
     283,   287,   291,   295,   299,   303,   307,   311,   315,   319,
     323,   327,   331,   335,   339,   343,   347,   351,   355,   359,
     363,   367,   371,   375,   379,   383,   387,   391,   395,   399,
     403,   407,   411,   415,   419,   423,   427,   431,   435,   439,
     443,   447,   451,   455,   459,   463,   467,   471,   474,   478,
     480,   482,   486,   489,   492,   494,   496,   498,   501,   504,
     507,   509,   512,   515,   517,   519,   521,   523,   526,   528,
     533,   536,   538,   540,   543,   545,   548,   550,   552,   554,
     556,   561,   563,   565,   567,   569,   571,   573,   575,   577,
     579,   588,   590,   592,   594,   596,   598,   601,   608,   610,
     612,   614,   616,   618,   620,   622,   624,   626,   628,   630,
     632,   635,   637,   640,   642,   644,   646,   649,   652,   654,
     656,   658,   660,   662,   664,   666,   668,   670,   672,   674,
     676,   678,   680,   682,   684,   686,   689,   691,   693,   695,
     697,   699,   702,   704,   707,   709,   712,   714,   716,   718,
     720,   722,   724,   726,   728,   730,   732,   735,   738,   740,
     742,   745,   748,   751,   753,   755,   757,   759,   761,   763,
     766,   768,   770,   772,   774,   776,   778,   781,   785,   789,
     793,   796,   800,   804,   808,   812,   816,   820,   824,   828,
     832,   840,   848,   856,   864,   868,   876,   884,   892,   900,
     904,   908,   912,   916,   920,   924,   929,   934,   939,   944,
     949,   954,   958,   961,   963,   965,   967,   969,   971,   973,
     975,   977,   979,   981,   983,   985,   987,   989,   991,   993,
     995,   997,   999,  1001,  1003,  1005,  1007,  1009,  1011,  1013,
    1015,  1017,  1019,  1021,  1023,  1025,  1027,  1029,  1031,  1033,
    1035,  1037,  1039,  1041,  1043,  1045,  1047,  1049,  1051,  1053,
    1055,  1057,  1061,  1065,  1069,  1073,  1077,  1080,  1084,  1088,
    1092,  1096,  1100,  1104,  1108,  1112,  1116,  1120,  1124,  1128,
    1132,  1136,  1140,  1144,  1148,  1152,  1156,  1158,  1160,  1162,
    1164,  1166,  1168,  1170,  1172,  1174,  1176,  1178,  1180,  1182,
    1184,  1186,  1188,  1190,  1192,  1194,  1196,  1198,  1200,  1202,
    1204,  1206,  1208,  1210,  1212,  1214,  1216,  1218,  1220,  1222,
    1224,  1226,  1228,  1231,  1239,  1245,  1249
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     398,     0,    -1,    -1,   398,   399,    -1,     1,    -1,   393,
     113,   403,   394,    -1,   114,    18,   403,    -1,   115,    18,
     403,    -1,   116,    18,   403,    -1,   117,    18,   403,    -1,
     132,    18,   403,    -1,   269,    18,   403,    -1,   118,    18,
     403,    -1,   120,    18,   403,    -1,   121,    18,   403,    -1,
     122,    18,   403,    -1,   277,    18,   403,    -1,   119,    18,
     403,    -1,   296,    18,   403,     3,   403,    -1,   400,    -1,
     393,   123,   403,     3,   403,   394,    -1,   393,   123,   403,
       3,    49,   394,    -1,   393,   123,   403,     3,   236,   394,
      -1,   393,   123,   403,     3,    56,   394,    -1,   393,   123,
     403,     3,    56,   403,   394,    -1,   393,   123,   403,     3,
       1,   394,    -1,   401,    -1,   402,    -1,   405,    -1,   114,
      18,   213,    -1,   114,    18,   214,    -1,   114,    18,   215,
      -1,   114,    18,   216,    -1,   114,    18,   217,    -1,   114,
      18,   218,    -1,   114,    18,   219,    -1,   114,    18,   220,
      -1,   114,    18,   221,    -1,   114,    18,   222,    -1,   114,
      18,    79,    -1,   114,    18,   223,    -1,   114,    18,   224,
      -1,   114,    18,   225,    -1,   114,    18,   226,    -1,   114,
      18,   227,    -1,   114,    18,   228,    -1,   114,    18,   229,
      -1,   114,    18,   230,    -1,   114,    18,   231,    -1,   114,
      18,   232,    -1,   114,    18,   233,    -1,   114,    18,   234,
      -1,   114,    18,   235,    -1,   114,    18,   236,    -1,   114,
      18,   237,    -1,   114,    18,   238,    -1,   114,    18,   239,
      -1,   114,    18,   240,    -1,   114,    18,   241,    -1,   114,
      18,   242,    -1,   114,    18,   243,    -1,   114,    18,   244,
      -1,   114,    18,   245,    -1,   114,    18,   246,    -1,   114,
      18,   247,    -1,   114,    18,   248,    -1,   114,    18,   249,
      -1,   114,    18,   250,    -1,   114,    18,   251,    -1,   114,
      18,   252,    -1,   114,    18,   253,    -1,   114,    18,   254,
      -1,   114,    18,   255,    -1,   114,    18,   256,    -1,   114,
      18,   257,    -1,   114,    18,   258,    -1,   114,    18,   259,
      -1,   114,    18,   260,    -1,   114,    18,   261,    -1,   114,
      18,   262,    -1,   114,    18,   263,    -1,   114,    18,   264,
      -1,   114,    18,   265,    -1,   114,    18,   266,    -1,   114,
      18,   267,    -1,   114,    18,   268,    -1,   114,    18,   269,
      -1,   114,    18,   270,    -1,   114,    18,   271,    -1,   114,
      18,   272,    -1,   114,    18,   273,    -1,   114,    18,   274,
      -1,   114,    18,   275,    -1,   114,    18,   276,    -1,   114,
      18,   277,    -1,   114,    18,   278,    -1,   114,    18,   279,
      -1,   114,    18,   280,    -1,   114,    18,   281,    -1,   114,
      18,   282,    -1,   114,    18,   283,    -1,   114,    18,   284,
      -1,   114,    18,   285,    -1,   114,    18,   286,    -1,   114,
      18,   287,    -1,   114,    18,   288,    -1,   114,    18,   289,
      -1,   114,    18,   290,    -1,   114,    18,   291,    -1,   114,
      18,   292,    -1,   114,    18,   293,    -1,   114,    18,   294,
      -1,   114,    18,   295,    -1,   114,    18,   296,    -1,   114,
      18,   297,    -1,   111,    18,   403,    -1,   112,    18,   403,
      -1,   110,   110,    -1,   110,   110,   110,    -1,   110,    -1,
      57,    -1,   386,     3,   403,    -1,    35,   403,    -1,    36,
     403,    -1,   124,    -1,   117,    -1,   125,    -1,    34,   403,
      -1,    33,   403,    -1,    32,   403,    -1,   126,    -1,    31,
     403,    -1,    30,   403,    -1,   127,    -1,   128,    -1,   129,
      -1,   130,    -1,    29,   403,    -1,   131,    -1,    51,   395,
     404,   396,    -1,    28,   403,    -1,   132,    -1,   133,    -1,
      27,   403,    -1,   134,    -1,    26,   403,    -1,   135,    -1,
     136,    -1,   137,    -1,   138,    -1,    25,   395,   406,   396,
      -1,   139,    -1,   140,    -1,   141,    -1,   142,    -1,   143,
      -1,   144,    -1,   145,    -1,   146,    -1,   147,    -1,    53,
     395,   403,     3,   403,     3,   403,   396,    -1,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,    24,   403,
      -1,    52,   395,   403,     3,   403,   396,    -1,   153,    -1,
     154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,   115,    -1,   161,    -1,   162,    -1,
     163,    -1,    46,   403,    -1,    46,    -1,    45,   403,    -1,
      45,    -1,   164,    -1,   165,    -1,    44,   403,    -1,    43,
     403,    -1,    43,    -1,   166,    -1,   167,    -1,   168,    -1,
     169,    -1,   170,    -1,   171,    -1,   172,    -1,   173,    -1,
     174,    -1,   175,    -1,   176,    -1,   177,    -1,   178,    -1,
     179,    -1,   180,    -1,   181,    -1,    42,   403,    -1,   182,
      -1,   183,    -1,   184,    -1,   185,    -1,   186,    -1,    41,
     403,    -1,   187,    -1,    48,   403,    -1,   188,    -1,    47,
     403,    -1,   189,    -1,   190,    -1,   191,    -1,   192,    -1,
     193,    -1,   194,    -1,   195,    -1,   196,    -1,   197,    -1,
     198,    -1,    40,   403,    -1,    39,   403,    -1,   199,    -1,
     200,    -1,    38,   403,    -1,    37,   403,    -1,    50,   403,
      -1,   201,    -1,   202,    -1,   203,    -1,   204,    -1,   205,
      -1,   206,    -1,    49,   403,    -1,   207,    -1,   208,    -1,
     209,    -1,   210,    -1,   211,    -1,   212,    -1,     7,   403,
      -1,   403,     6,   403,    -1,   403,     5,   403,    -1,   403,
       4,   403,    -1,    11,   403,    -1,   403,    10,   403,    -1,
     403,     9,   403,    -1,   403,     8,   403,    -1,   403,    19,
     403,    -1,   403,    20,   403,    -1,   403,    21,   403,    -1,
     403,    22,   403,    -1,   403,    23,   403,    -1,   403,    18,
     403,    -1,   403,    18,   393,   403,     3,   403,   394,    -1,
     403,    18,   393,   403,     3,   403,   396,    -1,   403,    18,
     395,   403,     3,   403,   394,    -1,   403,    18,   395,   403,
       3,   403,   396,    -1,   403,    17,   403,    -1,   403,    17,
     393,   403,     3,   403,   394,    -1,   403,    17,   393,   403,
       3,   403,   396,    -1,   403,    17,   395,   403,     3,   403,
     394,    -1,   403,    17,   395,   403,     3,   403,   396,    -1,
     403,    16,   403,    -1,   403,    15,   403,    -1,   403,    14,
     403,    -1,   403,    13,   403,    -1,   395,   403,   396,    -1,
     395,   403,     1,    -1,   403,     3,    18,   403,    -1,   403,
       3,    17,   403,    -1,   403,     3,    16,   403,    -1,   403,
       3,    15,   403,    -1,   403,     3,    14,   403,    -1,   403,
       3,    13,   403,    -1,   403,    12,   403,    -1,    20,   403,
      -1,   151,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,    69,
      -1,    70,    -1,    72,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,    -1,    79,    -1,    80,    -1,    81,
      -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,
      -1,    87,    -1,    88,    -1,    90,    -1,    91,    -1,    92,
      -1,    93,    -1,    94,    -1,    95,    -1,    96,    -1,    97,
      -1,    98,    -1,    99,    -1,   100,    -1,   101,    -1,   102,
      -1,   103,    -1,   105,    -1,   106,    -1,   107,    -1,   108,
      -1,   109,    -1,   344,    -1,   343,    -1,   338,    18,   407,
      -1,   339,    18,   407,    -1,   340,    18,   403,    -1,   341,
      18,   403,    -1,   342,    18,   403,    -1,    37,   403,    -1,
     345,    18,   110,    -1,   346,    18,   110,    -1,   348,    18,
     407,    -1,   347,    18,   403,    -1,   200,    18,   403,    -1,
     115,    18,   403,    -1,   116,    18,   403,    -1,   349,    18,
     403,    -1,   204,    18,   403,    -1,   350,    18,   407,    -1,
     351,    18,   403,    -1,   309,    18,   403,    -1,   387,    18,
     407,    -1,   388,    18,   407,    -1,   389,    18,   403,    -1,
     391,    18,   403,    -1,   390,    18,   403,    -1,   392,    18,
     403,    -1,   191,    18,   403,    -1,   352,    -1,   353,    -1,
     114,    -1,   354,    -1,   355,    -1,   356,    -1,   357,    -1,
     139,    -1,   358,    -1,   359,    -1,   360,    -1,   361,    -1,
     362,    -1,   363,    -1,   364,    -1,   365,    -1,   366,    -1,
     367,    -1,   368,    -1,   369,    -1,   370,    -1,   371,    -1,
     372,    -1,   373,    -1,   374,    -1,   375,    -1,   376,    -1,
     377,    -1,   378,    -1,   379,    -1,   380,    -1,   381,    -1,
     382,    -1,   383,    -1,   384,    -1,   385,    -1,     3,   407,
      -1,   403,     3,   403,     3,   403,     3,   403,    -1,   403,
       3,   403,     3,   403,    -1,   403,     3,   403,    -1,   403,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   442,   442,   443,   444,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   463,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   567,   568,   574,   577,   581,
     583,   584,   589,   590,   591,   592,   594,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,   625,   627,   630,   632,
     634,   636,   637,   638,   639,   640,   641,   642,   644,   647,
     650,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     663,   666,   669,   672,   674,   675,   676,   678,   680,   683,
     685,   688,   691,   694,   696,   698,   699,   700,   701,   702,
     703,   704,   706,   708,   711,   712,   713,   715,   717,   719,
     720,   721,   722,   723,   724,   725,   726,   727,   728,   730,
     733,   736,   737,   738,   740,   742,   745,   746,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     760,   763,   766,   767,   768,   769,   771,   772,   773,   774,
     776,   777,   778,   779,   783,   784,   785,   786,   788,   790,
     791,   792,   793,   794,   796,   797,   798,   799,   800,   802,
     803,   804,   805,   807,   809,   812,   819,   826,   833,   840,
     847,   854,   855,   859,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   873,   874,   875,
     876,   877,   878,   879,   880,   881,   882,   883,   884,   885,
     886,   887,   888,   889,   890,   891,   892,   893,   894,   895,
     896,   897,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   909,   910,   911,   912,   913,   914,   915,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   925,   926,   927,
     928,   929,   930,   931,   932,   933,   938,   939,   940,   941,
     942,   943,   944,   945,   946,   947,   948,   949,   950,   951,
     952,   953,   954,   955,   956,   957,   958,   959,   960,   961,
     962,   963,   964,   965,   966,   967,   968,   969,   970,   971,
     972,   973,   977,   979,   980,   981,   982
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "','", "XOR", "OR", "AND", "NOT",
  "LOGXOR", "LOGOR", "LOGAND", "LOGNOT", "MOD", "GREATEREQUAL",
  "LESSEQUAL", "LESS", "GREATER", "NOTEQUAL", "EQUAL", "'+'", "'-'", "'*'",
  "'/'", "SQUARE", "LN", "GETHITVAR", "FLOOR", "EXP", "COS", "CEIL",
  "ATAN", "ASIN", "ANIMEXIST", "ANIMELEMTIME", "ANIMELEMNO", "ABS", "ACOS",
  "SYSVAR", "SYSFVAR", "SIN", "SELFANIMEXIST", "PROJCANCLETIME",
  "PLAYERIDEXIST", "NUMTARGET", "NUMPROJID", "NUMHELPER", "NUMEXPLOD",
  "PROJGUARDEDTIME", "PROJCONTACTTIME", "VAR", "TAN", "CONST", "LOG",
  "IFELSE", "UMINUS", "UPLUS", "ID", "STRING", "NEGONE", "DATA", "ATTACK",
  "DEFENCE", "FALLDEFUP", "LIEDOWTIME", "AIRJUGGLE", "SPARKNO",
  "GUARDSPARKNO", "KOECHO", "VOLUME", "INTEGERINDEX", "FLOATINDEX", "SIZE",
  "XSCALE", "YSCALE", "GROUNDBACK", "GROUNDFRONT", "AIRBACK", "AIRFRONT",
  "HEIGHT", "ATTACKDIST", "PROJATTDIST", "PROJDOSCALE", "HEADPOSX",
  "HEADPOSY", "MIDPOSX", "MIDPOSY", "SHADOWOFFSET", "DRAWOFFSETX",
  "DRAWOFFSETY", "VELOCITY", "WALKFWD", "WALKBACK", "RUNFWDX", "RUNFWDY",
  "RUNBACKX", "RUNBACKY", "JUMPNEU", "JUMPBACK", "JUMPFWD", "RUNJUMPBACK",
  "RUNJUMPFWD", "AIRJUMPNEU", "AIRJUMPBACK", "AIRJUMPFWD", "MOVEMENT",
  "AIRJUMPNUM", "AIRJUMPHEIGHT", "YACCEL", "STANDFRICTION",
  "CROUCHFRICTION", "NUMBER", "TRIGGER", "TRIGGERALL", "STATEDEF", "TYPE",
  "MOVETYPE", "PHYSICS", "ANIM", "JUGGLE", "FACEP2", "HITDEFPERSIST",
  "MOVEHITPERSIST", "HITCOUNTPERSIST", "STATE", "ALIVE", "ANIMELEM",
  "ANIMTIME", "AUTHORNAME", "BACKEEDGEBODYDIST", "BACKEDGEDIST",
  "CANRECOVER", "COMMAND", "CTRL", "DRAWGAME", "FACING",
  "FRONTEDGEBODYDIST", "FRONTEDGEDIST", "FVAR", "GAMETIME", "HITCOUNT",
  "HITDEFATTR", "HITFALL", "HITOVER", "HITPAUSETIME", "HITSHAKEOVER",
  "HITVELX", "HITVELY", "PLID", "INGUARDDIST", "ISHELPER", "ISHOMETEAM",
  "LIFE", "LIFEMAX", "LOSE", "LOSEKO", "LOSETIME", "MATCHNO", "MATCHOVER",
  "MOVECONTACT", "MOVEGUARDED", "MOVEHIT", "MOVEREVERSED", "NAME",
  "NUMENEMY", "NUMPARTNER", "NUMPROJ", "P1NAME", "P2BODYDISTX",
  "P2BODYDISTY", "P2DISTX", "P2DISTY", "P2LIFE", "P2MOVETYPE", "P2NAME",
  "P2STATENO", "P2STATETYP", "P3NAME", "P4NAME", "PALNO", "PARENTDISTX",
  "PARENTDISTY", "PI", "PREVSTATENO", "POSX", "POSY", "POWER", "POWERMAX",
  "PROJCONTACT", "PROJGUARDED", "PROJHIT", "PROJHITTIME", "RANDOM",
  "ROOTDISTX", "ROOTDISTY", "ROUNDNO", "ROUNDSEXISTED", "ROUNDSTATE",
  "SCREENPOSX", "SCREENPOSY", "STATENO", "STATETYPE", "TEAMMODE",
  "TEAMSIDE", "TICKSPERSECOND", "TIME", "TIMEMODE", "UNIQHITCOUNT", "VELX",
  "VELY", "WIN", "WINKO", "WINTIME", "WINPERFECT", "TNULL", "AFTERIMAGE",
  "AFTERIMAGETIME", "ALLPALFX", "ANGLEADD", "ANGLEDRAW", "ANGLEMUL",
  "ANGLESET", "APPENDTOCLIPBOARD", "ASSERTSPECIAL", "ATTACKMULSET",
  "BGPALFX", "BINDTOPARENT", "BINDTOROOT", "BINDTOTARGET", "CHANGEANIME",
  "CHANGEANIME2", "CHANGESTATE", "CLEARCLIPBOARD", "CTRLSET",
  "DEFENCEMULSET", "DESTROYSELF", "DISPLAYTOCLIPBOARD", "ENVSHAKE",
  "EXPLOD", "EXPLODBINDTIME", "FALLENVSHAKE", "FORCEFEDDBACK",
  "GAMEMAKEANIM", "GRAVITY", "HELPER", "HITADD", "HITBY", "HITDEF",
  "HITFALLDAMAGE", "HITFALLSET", "HITFALLVEL", "HITOVERRIDE", "HITVELSET",
  "LIFEADD", "LIFESET", "MAKEDUST", "MODIFYEXPLOD", "MOVEHITRESET",
  "NOTHITBY", "NUL", "OFFSET", "PALFX", "PARENTVARADD", "PARENTVARSET",
  "PAUSE", "PLAYERPUSH", "PLAYSND", "POSADD", "POSFREEZ", "POSSET",
  "POWERADD", "POWERSET", "PROJECTILE", "REMOVEEXPLOD", "REVERSALDEF",
  "SCREENBOUND", "SELFSTATE", "SNDPAN", "SPRPRIORITY", "STATETYPESET",
  "STOPSND", "SUPERPAUSE", "TARGETBIND", "TARGETDROP", "TARGETFACING",
  "TARGETLIFEADD", "TARGETPOWERADD", "TARGETSTATE", "TARGETVELADD",
  "TARGETVELSET", "TURN", "VARADD", "VARRANDOM", "VARRANGESET", "VARSET",
  "VELADD", "VELMUL", "VELSET", "WIDTH", "LENGTH", "PALCOLOR",
  "PALINVERTALL", "PALBRIGHT", "PALCONTRAST", "PALPOSTBRIGHT", "PALADD",
  "PALMUL", "TIMEGAP", "FRAMEGAP", "TRANS", "FVALUE", "ACBEGIN", "ACTION",
  "LOOPSTART", "CLSN2DEFAULT", "CLSN1DEFAULT", "CLSN2", "CLSN1",
  "HORIZONTALFLIP", "VERTIKALFLIP", "HVFLIP", "ALPHA", "INFO",
  "DISPLAYNAME", "VERSIONSDATA", "MUGENVERSION", "AUTHOR", "FILES", "CMD",
  "CNS", "ST", "STCOMMON", "SPRITE", "SOUND", "PAL", "PALDEF", "ARCADE",
  "INTROSTORYBOARD", "ENDINGSTORYBOARD", "VALUE", "VALUE2", "XVALUE",
  "YVALUE", "ZVALUE", "JUMPNEUY", "AIRJUMPNEUY", "PERSISTENT",
  "IGNOREHITPAUSE", "SPACING", "POSXY", "WAVEFORM", "AMPL", "FREQ",
  "XVELADD", "YVELADD", "ANIMTYME", "AIRTYPE", "GROUNDTYPE", "DAMAGE",
  "FALLCOUNT", "HITSHAKETIME", "HITTIME", "SLIDETIME", "CTRLTIME",
  "RECOVERTIME", "XOFF", "YOFF", "ZOFF", "XVEL", "YVEL", "YACELL", "HITID",
  "CHAINID", "GUARDED", "FALL", "FALLDAMAGE", "FALLXVEL", "FALLYVEL",
  "FALLRECOVER", "FALLTIME", "FALLRECOVERTIME", "FALLKILL", "FALLENVTIME",
  "FALLENVFREQ", "FALLENVAMPL", "FALLENVDIR", "FALLENVPHASE", "FX", "ADD",
  "MUL", "SINADD", "INTERVALL", "COLOR", "UNDER", "'['", "']'", "'('",
  "')'", "$accept", "lines", "STATEDEFSECTION", "STATESECTION",
  "TYPESECTION", "TRIGGERSECTION", "expression", "CONSTPARAM",
  "PARAMSECTION", "GETHITPARAM", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    44,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,    43,
      45,    42,    47,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   566,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   612,   613,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   627,   628,   629,
     630,   631,   632,   633,   634,   635,   636,   637,   638,   639,
     640,   641,   642,    91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   397,   398,   398,   398,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   402,   402,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   407,   407,   407,   407,   407
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     1,
       6,     6,     6,     6,     7,     6,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     1,
       1,     3,     2,     2,     1,     1,     1,     2,     2,     2,
       1,     2,     2,     1,     1,     1,     1,     2,     1,     4,
       2,     1,     1,     2,     1,     2,     1,     1,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       8,     1,     1,     1,     1,     1,     2,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       7,     7,     7,     7,     3,     7,     7,     7,     7,     3,
       3,     3,     3,     3,     3,     4,     4,     4,     4,     4,
       4,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     7,     5,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     4,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,    19,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,     0,   183,   181,     0,     0,     0,     0,     0,     0,
       0,   120,   119,   176,   125,   124,   126,   130,   133,   134,
     135,   136,   138,   141,   142,   144,   146,   147,   148,   149,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   161,
     162,   163,   164,   165,   168,   169,   170,   171,   172,   173,
     174,   175,   177,   178,   179,   184,   185,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   206,   207,   208,   209,   210,   212,   214,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     228,   229,   233,   234,   235,   236,   237,   238,   240,   241,
     242,   243,   244,   245,     0,     0,   336,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   246,   250,   282,   166,
       0,   145,   143,   140,   137,   132,   131,   129,   128,   127,
     122,   123,   231,   230,   227,   226,   211,   205,   187,   186,
     182,   180,   215,   213,   239,   232,     0,     0,     0,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,    39,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,     6,
       7,     8,     9,    12,    17,    13,    14,    15,    10,   355,
     341,   345,    11,    16,     0,   348,     0,   396,   331,   332,
     333,   334,   335,   337,   338,   340,   339,   344,   346,   347,
     349,   350,   351,   353,   352,   354,     0,     0,   358,   363,
     356,   357,   359,   360,   361,   362,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,     0,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     283,   330,   329,     0,     0,     0,   118,   121,   274,   273,
       0,     0,     0,     0,     0,     0,   249,   248,   247,   253,
     252,   251,   281,   272,   271,   270,   269,     0,     0,   264,
       0,     0,   259,   254,   255,   256,   257,   258,     0,   392,
       0,     5,     0,   150,   139,     0,     0,   280,   279,   278,
     277,   276,   275,     0,     0,     0,     0,    18,   395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    21,    23,     0,    22,    20,   167,     0,     0,
       0,     0,     0,   394,    24,     0,   265,   266,   267,   268,
     260,   261,   262,   263,     0,   160,   393
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    43,    44,    45,    46,   377,   483,    47,   434,
     378
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -173
static const yytype_int16 yypact[] =
{
      38,  -173,   761,  -173,  3058,   -16,   -11,    -7,     6,    11,
      13,    15,    17,    23,    24,    25,    30,    62,    66,    80,
      85,    89,   106,   110,   129,   130,   133,   148,   149,   150,
     151,   154,   174,   175,   179,   180,   182,   184,   187,   205,
     206,   207,   -83,  -173,  -173,  -173,  -173,  -173,  3058,  3058,
    3058,  3058,  -169,  3058,  3058,  3058,  3058,  3058,  3058,  3058,
    3058,  3058,  3058,  3058,  3058,  3058,  3058,  3058,  3058,  3058,
    3330,  3058,  3330,  3330,  3058,  3058,  3058,  3058,  -168,  -167,
    -165,  -173,   121,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,   229,  3058,   308,  3058,  3058,  1407,
    3058,  3058,  3058,  3058,  3058,  3058,  3058,  3058,  3058,  3058,
    3058,  3058,  3058,  3058,  3058,  3058,  1135,  1135,  3058,  3058,
    3058,   123,   124,  3058,  1135,  3058,  1135,  3058,  1135,  1135,
    3058,  3058,  3058,  3058,  3058,  3058,   199,   199,  -173,  -173,
    1000,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  3216,  3058,  3058,   125,
    3058,     0,   128,  3058,  3058,  3058,  3058,  3058,  3058,  3058,
    3058,  3058,  3058,  3058,  1970,  2242,  3058,  3058,  3058,  3058,
    3058,   308,   308,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   336,   308,  1135,   759,  -173,  -173,
     308,   308,   308,  -173,  -173,   308,  -173,   308,  -173,   308,
    -173,  -173,   308,   308,   308,   308,   624,   847,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -160,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -159,   882,   903,  -173,  1189,  -173,  -173,
    3058,  3058,  3058,  3058,  3058,  3058,   199,   199,   199,   199,
     199,   199,   199,   142,   142,   142,   142,  3058,  3058,   142,
    3058,  3058,   142,     5,     5,  -173,  -173,  -173,  1698,  -173,
    1698,  -173,   548,  -173,  -173,  1698,  1698,   142,   142,   142,
     142,   142,   142,   954,    73,   975,    96,   308,  1031,  -155,
    2514,  2786,  -154,   796,   458,  1059,  1698,  1698,  1698,  1698,
    1698,  -173,  -173,  -173,   823,  -173,  -173,  -173,  1698,   117,
     265,   389,   429,  1112,  -173,   603,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  1698,  -173,   308
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,  -173,  -173,  -173,  -173,    -4,  -173,  -173,  -173,
    -172
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     176,   488,   177,   252,   253,   254,   255,   178,   256,   257,
     258,   179,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   180,   379,   268,   269,   270,   181,
     214,   182,   386,   183,   388,   184,   390,   391,    -2,     1,
     215,   185,   186,   187,   216,   217,   218,   219,   188,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   488,    -2,   547,   253,   254,   255,
     189,   256,   257,   258,   190,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   488,   191,   549,
     253,   254,   255,   192,   256,   257,   258,   193,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     252,   253,   254,   255,   194,   256,   257,   258,   195,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   490,   491,   492,   493,   494,   495,   196,   197,    -2,
      -2,   198,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,   266,   267,   268,   269,   270,   199,   200,   201,   202,
      -2,   251,   203,   271,   272,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   204,   205,   380,   381,   382,   206,   207,   385,
     208,   387,   209,   389,   519,   210,   392,   393,   394,   395,
     396,   397,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   211,   212,   213,   220,   246,   247,    -2,
     248,   249,   250,   383,   384,   486,   523,   524,    -2,   551,
     555,     0,    -2,   484,   485,     0,   487,     0,     0,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     509,   512,   513,   514,   515,   516,   517,     0,   252,   253,
     254,   255,     0,   256,   257,   258,     0,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    -2,     0,     0,
       0,   252,   253,   254,   255,    -2,   256,   257,   258,     0,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,     0,     0,    -2,     0,     0,     0,     0,   518,
     253,   254,   255,     0,   256,   257,   258,    -2,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -2,    -2,    -2,    -2,
      -2,     0,     0,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
       0,     0,   252,   253,   254,   255,   489,   256,   257,   258,
       0,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,   252,   253,   254,   255,     0,   256,   257,   258,
       0,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,     0,     0,     0,     0,     0,     0,     0,
       0,   252,   253,   254,   255,     0,   256,   257,   258,   489,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,     0,     0,     0,     0,   527,   528,   529,   530,
     531,   532,   489,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   533,   534,     0,   535,   536,     0,     0,
       0,   566,     0,   567,   537,     0,   538,     0,   543,     0,
       0,   544,   545,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   244,   554,     0,     0,
       0,     0,   559,   560,   561,   562,   563,     0,     0,   539,
       0,     0,     0,     0,   565,    48,     0,     0,     0,    49,
       0,   490,   491,   492,   493,   494,   495,     0,    50,     0,
     576,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,   540,    77,    78,
      79,    80,     0,     0,   541,    81,   252,   253,   254,   255,
       0,   256,   257,   258,     0,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   252,   253,   254,
     255,     0,   256,   257,   258,     0,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,   568,
       0,   569,     0,    83,     0,    84,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     3,   520,   253,   254,   255,     0,   256,   257,   258,
       0,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   570,   542,   571,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,   252,
     253,   254,   255,     0,   256,   257,   258,     0,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
       0,     0,     0,   572,     0,   573,   252,   253,   254,   255,
       0,   256,   257,   258,     0,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,     0,     0,     0,
     522,   253,   254,   255,   557,   256,   257,   258,     0,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,     0,     5,     6,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,     0,   525,   253,   254,   255,     0,
     256,   257,   258,    16,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   526,   253,   254,   255,
       0,   256,   257,   258,     0,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,     0,     0,     0,
       0,     0,     0,     0,   174,     0,     0,     0,     0,     0,
       0,     0,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,   546,   253,   254,
     255,    18,   256,   257,   258,    19,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   548,   253,
     254,   255,     0,   256,   257,   258,     0,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   575,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   521,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,     0,   550,   253,   254,   255,    21,   256,
     257,   258,     0,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,     0,     0,    22,     0,     0,
       0,     0,   558,   253,   254,   255,     0,   256,   257,   258,
      23,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,    29,    30,    31,    32,
      33,    34,    35,     0,   398,   574,   253,   254,   255,     0,
     256,   257,   258,     0,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,     0,     0,   376,   399,
       0,     0,    48,     0,     0,     0,    49,     0,    36,    37,
      38,    39,    40,    41,    42,    50,     0,     0,     0,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
     556,     0,    81,   253,   254,   255,     0,   256,   257,   258,
       0,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,     0,     0,     0,     0,   564,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,     0,    84,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
       0,     0,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,     0,     0,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   273,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,     0,
       0,   174,    83,     0,    84,     0,     0,     0,     0,     0,
     175,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,    48,     0,     0,     0,    49,
       0,   490,   491,   492,   493,   494,   495,     0,    50,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   174,     0,     0,     0,     0,     0,     0,
       0,     0,   175,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,    83,     0,    84,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,     0,     0,   174,    83,     0,    84,     0,     0,
       0,     0,     0,   175,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
       0,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     0,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,     0,     0,   174,    83,     0,    84,
       0,     0,     0,   507,     0,   508,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,     0,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     0,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,     0,   174,    83,
       0,    84,     0,     0,     0,   510,     0,   511,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
     174,    83,     0,    84,     0,     0,     0,     0,   552,   175,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,     0,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,     0,   174,    83,     0,    84,     0,     0,     0,     0,
     553,   175,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,     0,     0,     0,   435,   436,   437,   438,
     439,   440,   441,   442,     0,   443,   444,     0,   445,   446,
     447,   448,   449,   450,     0,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,     0,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
       0,   475,   476,   477,   478,   479,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,   480,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,     0,     0,   174,    83,     0,    84,     0,     0,
       0,     0,     0,   175,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   481,
     482,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   174,     0,     0,     0,
       0,     0,     0,     0,     0,   175
};

static const yytype_int16 yycheck[] =
{
       4,     1,    18,     3,     4,     5,     6,    18,     8,     9,
      10,    18,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    18,   197,    21,    22,    23,    18,
     113,    18,   204,    18,   206,    18,   208,   209,     0,     1,
     123,    18,    18,    18,    48,    49,    50,    51,    18,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,     1,    37,     3,     4,     5,     6,
      18,     8,     9,    10,    18,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     1,    18,     3,
       4,     5,     6,    18,     8,     9,    10,    18,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       3,     4,     5,     6,    18,     8,     9,    10,    18,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    13,    14,    15,    16,    17,    18,    18,    18,   111,
     112,    18,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    19,    20,    21,    22,    23,    18,    18,    18,    18,
     132,   175,    18,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,    18,    18,   198,   199,   200,    18,    18,   203,
      18,   205,    18,   207,   376,    18,   210,   211,   212,   213,
     214,   215,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    18,    18,    18,   395,   395,   395,   191,
     395,   110,     3,   110,   110,   110,   396,   396,   200,   394,
     394,    -1,   204,   247,   248,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,    -1,     3,     4,
       5,     6,    -1,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,    -1,
      -1,     3,     4,     5,     6,   277,     8,     9,    10,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,   296,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    10,   309,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   338,   339,   340,   341,
     342,    -1,    -1,   345,   346,   347,   348,   349,   350,   351,
      -1,    -1,     3,     4,     5,     6,   396,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,   389,   390,   391,
     392,   393,     3,     4,     5,     6,    -1,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,   396,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    -1,   490,   491,   492,   493,
     494,   495,   396,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   507,   508,    -1,   510,   511,    -1,    -1,
      -1,   394,    -1,   396,   518,    -1,   520,    -1,   522,    -1,
      -1,   525,   526,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   540,   541,    -1,    -1,
      -1,    -1,   546,   547,   548,   549,   550,    -1,    -1,     1,
      -1,    -1,    -1,    -1,   558,     7,    -1,    -1,    -1,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    20,    -1,
     574,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    -1,    -1,    56,    57,     3,     4,     5,     6,
      -1,     8,     9,    10,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     3,     4,     5,
       6,    -1,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,   394,
      -1,   396,    -1,   115,    -1,   117,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     3,     4,     5,     6,    -1,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,   394,   236,   396,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,     3,
       4,     5,     6,    -1,     8,     9,    10,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,   394,    -1,   396,     3,     4,     5,     6,
      -1,     8,     9,    10,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
       3,     4,     5,     6,   396,     8,     9,    10,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,   111,   112,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,   132,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,     3,     4,     5,     6,
      -1,     8,     9,    10,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   386,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   395,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   191,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,   200,     8,     9,    10,   204,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     3,     4,
       5,     6,    -1,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,   396,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     269,    -1,    -1,    -1,     3,     4,     5,     6,   277,     8,
       9,    10,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,   296,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,     8,     9,    10,
     309,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   338,
     339,   340,   341,   342,    -1,    -1,   345,   346,   347,   348,
     349,   350,   351,    -1,   114,     3,     4,     5,     6,    -1,
       8,     9,    10,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,     3,   139,
      -1,    -1,     7,    -1,    -1,    -1,    11,    -1,   387,   388,
     389,   390,   391,   392,   393,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
     394,    -1,    57,     4,     5,     6,    -1,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,   394,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
     115,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,    -1,    -1,
      -1,    -1,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,   386,   115,    -1,   117,    -1,    -1,    -1,    -1,    -1,
     395,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,     7,    -1,    -1,    -1,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   386,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   395,    -1,    -1,    -1,    -1,    -1,   110,    -1,
      -1,    -1,    -1,   115,    -1,   117,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,   386,   115,    -1,   117,    -1,    -1,
      -1,    -1,    -1,   395,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,   386,   115,    -1,   117,
      -1,    -1,    -1,   393,    -1,   395,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,   386,   115,
      -1,   117,    -1,    -1,    -1,   393,    -1,   395,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
     386,   115,    -1,   117,    -1,    -1,    -1,    -1,   394,   395,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,
      -1,    -1,   386,   115,    -1,   117,    -1,    -1,    -1,    -1,
     394,   395,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    72,    73,
      74,    75,    76,    77,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,   105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   151,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,   386,   115,    -1,   117,    -1,    -1,
      -1,    -1,    -1,   395,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   343,
     344,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   386,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   395
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,   398,     0,    37,   111,   112,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   132,   191,   200,   204,
     269,   277,   296,   309,   338,   339,   340,   341,   342,   345,
     346,   347,   348,   349,   350,   351,   387,   388,   389,   390,
     391,   392,   393,   399,   400,   401,   402,   405,     7,    11,
      20,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    57,   110,   115,   117,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   386,   395,   403,    18,    18,    18,
      18,    18,    18,    18,    18,    18,    18,    18,    18,    18,
      18,    18,    18,    18,    18,    18,    18,    18,    18,    18,
      18,    18,    18,    18,    18,    18,    18,    18,    18,    18,
      18,    18,    18,    18,   113,   123,   403,   403,   403,   403,
     395,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   395,   395,   395,   110,
       3,   403,     3,     4,     5,     6,     8,     9,    10,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,   403,   403,    79,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,     3,   403,   407,   407,
     403,   403,   403,   110,   110,   403,   407,   403,   407,   403,
     407,   407,   403,   403,   403,   403,   403,   403,   114,   139,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   406,    60,    61,    62,    63,    64,
      65,    66,    67,    69,    70,    72,    73,    74,    75,    76,
      77,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   105,   106,   107,   108,   109,
     151,   343,   344,   404,   403,   403,   110,   403,     1,   396,
      13,    14,    15,    16,    17,    18,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   393,   395,   403,
     393,   395,   403,   403,   403,   403,   403,   403,     3,   407,
       3,   394,     3,   396,   396,     3,     3,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,     1,
      49,    56,   236,   403,   403,   403,     3,     3,     3,     3,
       3,   394,   394,   394,   403,   394,   394,   396,     3,   403,
     403,   403,   403,   403,   394,   403,   394,   396,   394,   396,
     394,   396,   394,   396,     3,   396,   403
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1455 of yacc.c  */
#line 444 "PraserRules.txt"
    {yyclearin;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 448 "PraserRules.txt"
    {myStateManager->AddStateDef((int)(yyvsp[(3) - (4)]).nFloat);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 449 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->type=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 450 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->movetype=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 451 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->physics=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 452 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->nAnim=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 453 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->bCtrl=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 454 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->nPoweradd=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 455 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->nJuggle=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 456 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->bHitdefpersist=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 457 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->bMovehitpersist=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 458 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->bHitcountpersist=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 459 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->nSprpriority=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 460 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->bFacep2=(int)(yyvsp[(3) - (3)]).nFloat;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 461 "PraserRules.txt"
    {myStateManager->GetCurrStateDef()->Velset.x=(yyvsp[(3) - (5)]).nFloat;
                                                         myStateManager->GetCurrStateDef()->Velset.y=(yyvsp[(5) - (5)]).nFloat;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 466 "PraserRules.txt"
    {myStateManager->AddState((int)(yyvsp[(3) - (6)]).nFloat,(int)(yyvsp[(5) - (6)]).nFloat );;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 467 "PraserRules.txt"
    {myStateManager->AddState((int)(yyvsp[(3) - (6)]).nFloat,"Var" );;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 468 "PraserRules.txt"
    {myStateManager->AddState((int)(yyvsp[(3) - (6)]).nFloat,"EnvShake" );;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 469 "PraserRules.txt"
    {myStateManager->AddState((int)(yyvsp[(3) - (6)]).nFloat,(yyvsp[(5) - (6)]).str);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 470 "PraserRules.txt"
    {myStateManager->AddState((int)(yyvsp[(3) - (7)]).nFloat,(yyvsp[(5) - (7)]).str);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 471 "PraserRules.txt"
    {myStateManager->AddState((int)(yyvsp[(3) - (6)]).nFloat,"Nothing");;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 478 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TNULL);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 479 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_AFTERIMAGE);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 480 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_AFTERIMAGETIME);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 481 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ALLPALFX);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 482 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ANGLEADD);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 483 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ANGLEDRAW);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 484 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ANGLEMUL);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 485 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ANGLESET);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 486 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_APPENDTOCLIPBOARD);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 487 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ASSERTSPECIAL);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 488 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ATTACKDIST);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 489 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ATTACKMULSET);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 490 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_BGPALFX);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 491 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_BINDTOPARENT);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 492 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_BINDTOROOT);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 493 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_BINDTOTARGET);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 494 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_CHANGEANIME);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 495 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_CHANGEANIME2);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 496 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_CHANGESTATE);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 497 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_CLEARCLIPBOARD);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 498 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_CTRLSET);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 499 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_DEFENCEMULSET);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 500 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_DESTROYSELF);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 501 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_DISPLAYTOCLIPBOARD);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 502 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_ENVSHAKE);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 503 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_EXPLOD);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 504 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_EXPLODBINDTIME);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 505 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_FALLENVSHAKE);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 506 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_FORCEFEDDBACK);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 507 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_GAMEMAKEANIM);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 508 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_GRAVITY);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 509 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HELPER);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 510 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITADD);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 511 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITBY);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 512 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITDEF);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 513 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITFALLDAMAGE);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 514 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITFALLSET);;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 515 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITFALLVEL);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 516 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITOVERRIDE);;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 517 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_HITVELSET);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 518 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_LIFEADD);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 519 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_LIFESET);;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 520 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_MAKEDUST);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 521 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_MODIFYEXPLOD);;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 522 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_MOVEHITRESET);;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 523 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_NOTHITBY);;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 524 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_NUL);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 525 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_OFFSET);;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 526 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PALFX);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 527 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PARENTVARADD);;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 528 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PARENTVARSET);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 529 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PAUSE);;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 530 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PLAYERPUSH);;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 531 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PLAYSND);;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 532 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_POSADD);;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 533 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_POSFREEZ);;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 534 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_POSSET);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 535 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_POWERADD);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 536 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_POWERSET);;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 537 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_PROJECTILE);;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 538 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_REMOVEEXPLOD);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 539 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_REVERSALDEF);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 540 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_SCREENBOUND);;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 541 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_SELFSTATE);;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 542 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_SNDPAN);;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 543 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_SPRPRIORITY);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 544 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_STATETYPESET);;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 545 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_STOPSND);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 546 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_SUPERPAUSE);;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 547 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETBIND);;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 548 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETDROP);;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 549 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETFACING);;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 550 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETLIFEADD);;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 551 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETPOWERADD);;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 552 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETSTATE);;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 553 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETVELADD);;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 554 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TARGETVELSET);;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 555 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_TURN);;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 556 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VARADD);;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 557 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VARRANDOM);;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 558 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VARRANGESET);;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 559 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VARSET);;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 560 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VELADD);;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 561 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VELMUL);;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 562 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_VELSET);;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 563 "PraserRules.txt"
    {myStateManager->AddTypeToState(CT_WIDTH);;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 567 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->AddTriggerToState((int)(yyvsp[(1) - (3)]).nFloat);;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 568 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->AddTriggerToState(192);;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 574 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,(yyvsp[(1) - (2)]).nFloat,"#");
                                  myStateManager->AddInstruction(OP_PUSH,(yyvsp[(2) - (2)]).nFloat,"#");
                                  myStateManager->AddInstruction(OP_JOIN,0,"#");;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 577 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,(yyvsp[(1) - (3)]).nFloat,"#");
                                        myStateManager->AddInstruction(OP_PUSH,(yyvsp[(2) - (3)]).nFloat,"#");
                                        myStateManager->AddInstruction(OP_PUSH,(yyvsp[(3) - (3)]).nFloat,"#");
                                        myStateManager->AddInstruction(OP_JOIN,0,"#");;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 581 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,(yyvsp[(1) - (1)]).nFloat,"#");/*printf("%f\n",$1.nFloat);*/;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 583 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,(yyvsp[(1) - (1)]).str);;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 584 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");
                                         myStateManager->AddInstruction(OP_PUSH,70,"#");
                                         myStateManager->AddInstruction(OP_PUSH,(yyvsp[(1) - (3)]).nFloat,"#");
                                         myStateManager->AddInstruction(OP_GROUP,0,"#");;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 589 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ABS,0,"#");;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 590 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ACOS,0,"#");;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 591 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ALIVE,0,"#");;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 592 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ANIM,0,"#");;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 594 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ANIMELEM,0,"#");;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 596 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ANIMELEMNO,0,"#");;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 597 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ANIMELEMTIME,0,"#");;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 598 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ANIMEXIST,0,"#");;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 599 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ANIMTIME,0,"#");;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 600 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ASIN,0,"#");;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 601 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ATAN,0,"#");;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 602 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_AUTHORNAME,0,"#");;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 603 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_BACKEDGEBODY,0,"#");;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 604 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_BACKEDGE,0,"#");;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 605 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_CANRECOVER,0,"#");;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 606 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_CEIL,0,"#");;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 607 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_COMMAND,0,"#");;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 608 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_CONST,0,"#");;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 609 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_COS,0,"#");;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 610 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_CTRL,0,"#");;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 611 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_DRAWGAME,0,"#");;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 612 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_EXP,0,"#");;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 613 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_FACING,0,"#");;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 614 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_FLOOR,0,"#");;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 615 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_FEBD,0,"#");;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 616 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_FED,0,"#");;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 617 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_FVAR,0,"#");;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 618 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_GAMETIME,0,"#");;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 619 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_GETHITVAR,0,"#");;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 620 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_HITCOUNT,0,"#");;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 621 "PraserRules.txt"
    {;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 622 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_HITFALL,0,"#");;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 623 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_HITOVER,0,"#");;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 624 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_HITPAUSETIME,0,"#");;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 625 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_HITSHAKEOVER,0,"#");;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 627 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                myStateManager->AddInstruction(OP_HITVAL,0,"#");;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 630 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,2,"#");
                                                myStateManager->AddInstruction(OP_HITVAL,0,"#");;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 632 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ID,0,"#");;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 634 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_IFELSE,0,"#");;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 636 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INGUARDDIST,0,"#");;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 637 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ISHELPER,0,"#");;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 638 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ISHOMETEAM,0,"#");;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 639 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LIFE,0,"#");;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 640 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LIFEMAX,0,"#");;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 641 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LN,0,"#");;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 642 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LOG,0,"#");;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 644 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_LOSE,0,"#");;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 647 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,2,"#");
                                                           myStateManager->AddInstruction(OP_LOSE,0,"#");;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 650 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,3,"#");
                                                           myStateManager->AddInstruction(OP_LOSE,0,"#");;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 653 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MATCHNO,0,"#");;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 654 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MATCHOVER,0,"#");;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 655 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MOVECONTACT,0,"#");;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 656 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MOVEGUARDED,0,"#");;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 657 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MOVEHIT,0,"#");;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 658 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MOVETYPE,0,"#");;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 659 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MOVEREVERSED,0,"#");;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 660 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NAME,0,"#");;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 661 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NUMENEMY,0,"#");;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 663 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_NUMEXPLOD,0,"#");;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 666 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_NUMEXPLOD,0,"#");;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 669 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_NUMHELPER,0,"#");;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 672 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_NUMHELPER,0,"#");;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 674 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NUMPARTNER,0,"#");;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 675 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NUMPROJ,0,"#");;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 676 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NUMPROJID,0,"#");;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 678 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_NUMTARGET,1,"#");;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 680 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_NUMTARGET,1,"#");;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 683 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NAME,0,"#");;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 685 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_P2BODYDIST,0,"#");;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 688 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_P2BODYDIST,0,"#");;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 691 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_P2DIST,1,"#");;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 694 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
	                                                       myStateManager->AddInstruction(OP_P2DIST,0,"#");;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 696 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P2LIFE,0,"#");;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 698 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P2MOVETYPE,0,"#");;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 699 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P2NAME,0,"#");;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 700 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P2STATENO,0,"#");;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 701 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P2STATETYPE,0,"#");;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 702 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P3NAME,0,"#");;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 703 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_P4NAME,0,"#");;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 704 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PALNO,0,"#");;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 706 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_PARENTDIST,0,"#");;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 708 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_PARENTDIST,0,"#");;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 711 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PI,0,"#");;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 712 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PLAYERIDEXIST,0,"#");;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 713 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PREVSTATENO,0,"#");;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 715 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_POS,0,"#");;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 717 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_POS,0,"#");;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 719 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_POWER,0,"#");;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 720 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_POWERMAX,0,"#");;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 721 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PROJCANCTIME,0,"#");;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 722 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PROJCONTACT,0,"#");;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 723 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PROJCONTACTTIME,0,"#");;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 724 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PROJGUARDED,0,"#");;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 725 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PROJGUARDEDTIME,0,"#");;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 726 "PraserRules.txt"
    {;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 727 "PraserRules.txt"
    {;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 728 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_RANDOM,0,"#");;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 730 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_ROOTDIST,0,"#");;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 733 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_ROOTDIST,0,"#");;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 736 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ROUNDNO,0,"#");;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 737 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ROUNDSEXISTED,0,"#");;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 738 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ROUNDSTATE,0,"#");;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 740 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_SCREENPOS,0,"#");;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 742 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_SCREENPOS,0,"#");;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 745 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SELFANIMEXIST,0,"#");;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 746 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SIN,0,"#");;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 747 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STAGENO,0,"#");;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 748 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STATETYPE,0,"#");;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 749 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SYSFVAR,0,"#");;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 750 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SYSVAR,0,"#");;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 751 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_TAN,0,"#");;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 752 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_TEAMMODE,0,"#");;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 753 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_TEAMSIDE,0,"#");;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 754 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_TICKSPERSCOND,0,"#");;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 755 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_TIME,0,"#");;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 756 "PraserRules.txt"
    {;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 757 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_UNIQHITCOUNT,0,"#");;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 758 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_VAR,0,"#");;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 760 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_VEL,0,"#");;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 763 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_VEL,0,"#");;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 766 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");myStateManager->AddInstruction(OP_WIN,0,"#");}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 767 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,2,"#");myStateManager->AddInstruction(OP_WIN,0,"#");}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 768 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,3,"#");myStateManager->AddInstruction(OP_WIN,0,"#");}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 769 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,4,"#");myStateManager->AddInstruction(OP_WIN,0,"#");}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 771 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NOT,0,"#");;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 772 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_AND,0,"#");;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 773 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_OR,0,"#");;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 774 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_XOR,0,"#");;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 776 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LOGNOT,0,"#");;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 777 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LOGAND,0,"#");;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 778 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LOGOR,0,"#");;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 779 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LOGXOR,0,"#");;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 783 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_ADD,0,"#");;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 784 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SUB,0,"#");;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 785 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MUL,0,"#");;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 786 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_DIV,0,"#");;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 788 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SQUARE,0,"#");;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 790 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_EQUAL,0,"#");/*printf("=\n");*/;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 791 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP1,0,"#");;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 792 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP2,0,"#");;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 793 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP3,0,"#");;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 794 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP4,0,"#");;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 796 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_NOTEQUAL,0,"#");;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 797 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP5,0,"#");;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 798 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP6,0,"#");;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 799 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP7,0,"#");;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 800 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_INTERVALOP8,0,"#");;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 802 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_GREATER,0,"#");;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 803 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LESS,0,"#");;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 804 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_LESSEQUAL,0,"#");;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 805 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_GRAETEREQUAL,0,"#");;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 807 "PraserRules.txt"
    {/*expression Add*/;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 809 "PraserRules.txt"
    {/*expression Add*/;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 812 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_EQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 819 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_NOTEQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 826 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_GREATER,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 833 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_LESS,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 840 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_LESSEQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 847 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_GRAETEREQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 854 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_MOD,0,"#");;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 855 "PraserRules.txt"
    {(yyval).nFloat=-(yyvsp[(2) - (2)]).nFloat;myStateManager->AddInstruction(OP_NEG,0,"#");;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 859 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 860 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 861 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,2,"#");;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 862 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,3,"#");;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 863 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,4,"#");;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 864 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,5,"#");;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 865 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,6,"#");;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 866 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,7,"#");;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 867 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,8,"#");;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 868 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,9,"#");;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 869 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,10,"#");;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 870 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,11,"#");;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 871 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,12,"#");;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 872 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,13,"#");;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 873 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,14,"#");;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 874 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,15,"#");;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 875 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,16,"#");;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 876 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,17,"#");;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 877 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,18,"#");;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 878 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,19,"#");;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 879 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,20,"#");;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 880 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,21,"#");;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 881 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,22,"#");;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 882 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,23,"#");;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 883 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,24,"#");;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 884 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,25,"#");;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 885 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,26,"#");;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 886 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,27,"#");;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 887 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,28,"#");;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 888 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,29,"#");;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 889 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,30,"#");;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 890 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,31,"#");;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 891 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,32,"#");;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 892 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,33,"#");;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 893 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,34,"#");;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 894 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,35,"#");;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 895 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,36,"#");;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 896 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,37,"#");;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 897 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,38,"#");;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 898 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,39,"#");;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 899 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,40,"#");;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 900 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,41,"#");;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 901 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,42,"#");;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 902 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,43,"#");;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 903 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,44,"#");;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 904 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,45,"#");;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 905 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,46,"#");;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 906 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,47,"#");;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 909 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_VALUE);;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 910 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_VALUE2);;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 911 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_XVALUE);;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 912 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_YVALUE);;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 913 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_ZVALUE);;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 914 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_SYSVAR);;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 915 "PraserRules.txt"
    {myStateManager->AddPersistanceToState((int)(yyvsp[(3) - (3)]).nFloat);;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 916 "PraserRules.txt"
    {myStateManager->AddIgnoreHitPauseToState((int)(yyvsp[(3) - (3)]).nFloat);;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 917 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_POS);;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 918 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_SPACING);;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 919 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_STATETYPE);;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 920 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_MOVETYPE);;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 921 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_PHYSICS);;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 922 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_WAVEFORM);;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 923 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_TIME);;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 924 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_AMPL);;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 925 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_FREQ);;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 926 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_FVALUE);;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 927 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_ADD);;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 928 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_MUL);;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 929 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_SINADD);;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 930 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_COLOR);;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 931 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_INTERVALL);;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 932 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_UNDER);;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 933 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_RANDOM);;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 938 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");;}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 939 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,1,"#");;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 940 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,2,"#");;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 941 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,3,"#");;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 942 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,4,"#");;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 943 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,5,"#");;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 944 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,6,"#");;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 945 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,7,"#");;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 946 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,8,"#");;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 947 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,9,"#");;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 948 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,10,"#");;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 949 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,11,"#");;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 950 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,12,"#");;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 951 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,13,"#");;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 952 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,14,"#");;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 953 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,15,"#");;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 954 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,16,"#");;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 955 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,17,"#");;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 956 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,18,"#");;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 957 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,19,"#");;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 958 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,20,"#");;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 959 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,21,"#");;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 960 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,22,"#");;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 961 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,23,"#");;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 962 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,24,"#");;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 963 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,25,"#");;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 964 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,26,"#");;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 965 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,27,"#");;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 966 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,28,"#");;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 967 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,29,"#");;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 968 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,30,"#");;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 969 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,31,"#");;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 970 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,32,"#");;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 971 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,33,"#");;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 972 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,34,"#");;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 973 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,35,"#");;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 977 "PraserRules.txt"
    {myStateManager->AddInstruction(OP_PUSH,0,"#");
                  myStateManager->AddInstruction(OP_JOIN,0,"#");;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 979 "PraserRules.txt"
    {;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 980 "PraserRules.txt"
    {;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 981 "PraserRules.txt"
    {;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 982 "PraserRules.txt"
    {;}
    break;



/* Line 1455 of yacc.c  */
#line 5839 "yacc.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
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
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 984 "PraserRules.txt"


