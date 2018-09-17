
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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




