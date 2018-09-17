
/*  A Bison parser, made from praserrules.txt with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	MOD	258
#define	LOGNOT	259
#define	LOGAND	260
#define	LOGOR	261
#define	LOGXOR	262
#define	NOT	263
#define	AND	264
#define	OR	265
#define	XOR	266
#define	EQUAL	267
#define	NOTEQUAL	268
#define	GREATER	269
#define	LESS	270
#define	LESSEQUAL	271
#define	GREATEREQUAL	272
#define	SQUARE	273
#define	ACOS	274
#define	ABS	275
#define	ANIMELEMNO	276
#define	ANIMELEMTIME	277
#define	ANIMEXIST	278
#define	ASIN	279
#define	ATAN	280
#define	CEIL	281
#define	COS	282
#define	EXP	283
#define	FLOOR	284
#define	GETHITVAR	285
#define	LN	286
#define	NUMEXPLOD	287
#define	NUMHELPER	288
#define	NUMPROJID	289
#define	NUMTARGET	290
#define	PLAYERIDEXIST	291
#define	PROJCANCLETIME	292
#define	SELFANIMEXIST	293
#define	SIN	294
#define	SYSFVAR	295
#define	SYSVAR	296
#define	TAN	297
#define	VAR	298
#define	PROJCONTACTTIME	299
#define	PROJGUARDEDTIME	300
#define	IFELSE	301
#define	LOG	302
#define	CONST	303
#define	UMINUS	304
#define	UPLUS	305
#define	ID	306
#define	STRING	307
#define	NEGONE	308
#define	DATA	309
#define	ATTACK	310
#define	DEFENCE	311
#define	FALLDEFUP	312
#define	LIEDOWTIME	313
#define	AIRJUGGLE	314
#define	SPARKNO	315
#define	GUARDSPARKNO	316
#define	KOECHO	317
#define	VOLUME	318
#define	INTEGERINDEX	319
#define	FLOATINDEX	320
#define	SIZE	321
#define	XSCALE	322
#define	YSCALE	323
#define	GROUNDBACK	324
#define	GROUNDFRONT	325
#define	AIRBACK	326
#define	AIRFRONT	327
#define	HEIGHT	328
#define	ATTACKDIST	329
#define	PROJATTDIST	330
#define	PROJDOSCALE	331
#define	HEADPOSX	332
#define	HEADPOSY	333
#define	MIDPOSX	334
#define	MIDPOSY	335
#define	SHADOWOFFSET	336
#define	DRAWOFFSETX	337
#define	DRAWOFFSETY	338
#define	VELOCITY	339
#define	WALKFWD	340
#define	WALKBACK	341
#define	RUNFWDX	342
#define	RUNFWDY	343
#define	RUNBACKX	344
#define	RUNBACKY	345
#define	JUMPNEU	346
#define	JUMPBACK	347
#define	JUMPFWD	348
#define	RUNJUMPBACK	349
#define	RUNJUMPFWD	350
#define	AIRJUMPNEU	351
#define	AIRJUMPBACK	352
#define	AIRJUMPFWD	353
#define	MOVEMENT	354
#define	AIRJUMPNUM	355
#define	AIRJUMPHEIGHT	356
#define	YACCEL	357
#define	STANDFRICTION	358
#define	CROUCHFRICTION	359
#define	NUMBER	360
#define	TRIGGER	361
#define	TRIGGERALL	362
#define	STATEDEF	363
#define	TYPE	364
#define	MOVETYPE	365
#define	PHYSICS	366
#define	ANIM	367
#define	JUGGLE	368
#define	FACEP2	369
#define	HITDEFPERSIST	370
#define	MOVEHITPERSIST	371
#define	HITCOUNTPERSIST	372
#define	STATE	373
#define	ALIVE	374
#define	ANIMELEM	375
#define	ANIMTIME	376
#define	AUTHORNAME	377
#define	BACKEEDGEBODYDIST	378
#define	BACKEDGEDIST	379
#define	CANRECOVER	380
#define	COMMAND	381
#define	CTRL	382
#define	DRAWGAME	383
#define	FACING	384
#define	FRONTEDGEBODYDIST	385
#define	FRONTEDGEDIST	386
#define	FVAR	387
#define	GAMETIME	388
#define	HITCOUNT	389
#define	HITDEFATTR	390
#define	HITFALL	391
#define	HITOVER	392
#define	HITPAUSETIME	393
#define	HITSHAKEOVER	394
#define	HITVELX	395
#define	HITVELY	396
#define	PLID	397
#define	INGUARDDIST	398
#define	ISHELPER	399
#define	ISHOMETEAM	400
#define	LIFE	401
#define	LIFEMAX	402
#define	LOSE	403
#define	LOSEKO	404
#define	LOSETIME	405
#define	MATCHNO	406
#define	MATCHOVER	407
#define	MOVECONTACT	408
#define	MOVEGUARDED	409
#define	MOVEHIT	410
#define	MOVEREVERSED	411
#define	NAME	412
#define	NUMENEMY	413
#define	NUMPARTNER	414
#define	NUMPROJ	415
#define	P1NAME	416
#define	P2BODYDISTX	417
#define	P2BODYDISTY	418
#define	P2DISTX	419
#define	P2DISTY	420
#define	P2LIFE	421
#define	P2MOVETYPE	422
#define	P2NAME	423
#define	P2STATENO	424
#define	P2STATETYP	425
#define	P3NAME	426
#define	P4NAME	427
#define	PALNO	428
#define	PARENTDISTX	429
#define	PARENTDISTY	430
#define	PI	431
#define	PREVSTATENO	432
#define	POSX	433
#define	POSY	434
#define	POWER	435
#define	POWERMAX	436
#define	PROJCONTACT	437
#define	PROJGUARDED	438
#define	PROJHIT	439
#define	PROJHITTIME	440
#define	RANDOM	441
#define	ROOTDISTX	442
#define	ROOTDISTY	443
#define	ROUNDNO	444
#define	ROUNDSEXISTED	445
#define	ROUNDSTATE	446
#define	SCREENPOSX	447
#define	SCREENPOSY	448
#define	STATENO	449
#define	STATETYPE	450
#define	TEAMMODE	451
#define	TEAMSIDE	452
#define	TICKSPERSECOND	453
#define	TIME	454
#define	TIMEMODE	455
#define	UNIQHITCOUNT	456
#define	VELX	457
#define	VELY	458
#define	WIN	459
#define	WINKO	460
#define	WINTIME	461
#define	WINPERFECT	462
#define	TNULL	463
#define	AFTERIMAGE	464
#define	AFTERIMAGETIME	465
#define	ALLPALFX	466
#define	ANGLEADD	467
#define	ANGLEDRAW	468
#define	ANGLEMUL	469
#define	ANGLESET	470
#define	APPENDTOCLIPBOARD	471
#define	ASSERTSPECIAL	472
#define	ATTACKMULSET	473
#define	BGPALFX	474
#define	BINDTOPARENT	475
#define	BINDTOROOT	476
#define	BINDTOTARGET	477
#define	CHANGEANIME	478
#define	CHANGEANIME2	479
#define	CHANGESTATE	480
#define	CLEARCLIPBOARD	481
#define	CTRLSET	482
#define	DEFENCEMULSET	483
#define	DESTROYSELF	484
#define	DISPLAYTOCLIPBOARD	485
#define	ENVSHAKE	486
#define	EXPLOD	487
#define	EXPLODBINDTIME	488
#define	FALLENVSHAKE	489
#define	FORCEFEDDBACK	490
#define	GAMEMAKEANIM	491
#define	GRAVITY	492
#define	HELPER	493
#define	HITADD	494
#define	HITBY	495
#define	HITDEF	496
#define	HITFALLDAMAGE	497
#define	HITFALLSET	498
#define	HITFALLVEL	499
#define	HITOVERRIDE	500
#define	HITVELSET	501
#define	LIFEADD	502
#define	LIFESET	503
#define	MAKEDUST	504
#define	MODIFYEXPLOD	505
#define	MOVEHITRESET	506
#define	NOTHITBY	507
#define	NUL	508
#define	OFFSET	509
#define	PALFX	510
#define	PARENTVARADD	511
#define	PARENTVARSET	512
#define	PAUSE	513
#define	PLAYERPUSH	514
#define	PLAYSND	515
#define	POSADD	516
#define	POSFREEZ	517
#define	POSSET	518
#define	POWERADD	519
#define	POWERSET	520
#define	PROJECTILE	521
#define	REMOVEEXPLOD	522
#define	REVERSALDEF	523
#define	SCREENBOUND	524
#define	SELFSTATE	525
#define	SNDPAN	526
#define	SPRPRIORITY	527
#define	STATETYPESET	528
#define	STOPSND	529
#define	SUPERPAUSE	530
#define	TARGETBIND	531
#define	TARGETDROP	532
#define	TARGETFACING	533
#define	TARGETLIFEADD	534
#define	TARGETPOWERADD	535
#define	TARGETSTATE	536
#define	TARGETVELADD	537
#define	TARGETVELSET	538
#define	TURN	539
#define	VARADD	540
#define	VARRANDOM	541
#define	VARRANGESET	542
#define	VARSET	543
#define	VELADD	544
#define	VELMUL	545
#define	VELSET	546
#define	WIDTH	547
#define	LENGTH	548
#define	PALCOLOR	549
#define	PALINVERTALL	550
#define	PALBRIGHT	551
#define	PALCONTRAST	552
#define	PALPOSTBRIGHT	553
#define	PALADD	554
#define	PALMUL	555
#define	TIMEGAP	556
#define	FRAMEGAP	557
#define	TRANS	558
#define	FVALUE	559
#define	ACBEGIN	560
#define	ACTION	561
#define	LOOPSTART	562
#define	CLSN2DEFAULT	563
#define	CLSN1DEFAULT	564
#define	CLSN2	565
#define	CLSN1	566
#define	HORIZONTALFLIP	567
#define	VERTIKALFLIP	568
#define	HVFLIP	569
#define	ALPHA	570
#define	INFO	571
#define	DISPLAYNAME	572
#define	VERSIONSDATA	573
#define	MUGENVERSION	574
#define	AUTHOR	575
#define	FILES	576
#define	CMD	577
#define	CNS	578
#define	ST	579
#define	STCOMMON	580
#define	SPRITE	581
#define	SOUND	582
#define	PAL	583
#define	PALDEF	584
#define	ARCADE	585
#define	INTROSTORYBOARD	586
#define	ENDINGSTORYBOARD	587
#define	VALUE	588
#define	VALUE2	589
#define	XVALUE	590
#define	YVALUE	591
#define	ZVALUE	592
#define	JUMPNEUY	593
#define	AIRJUMPNEUY	594
#define	PERSISTENT	595
#define	IGNOREHITPAUSE	596
#define	SPACING	597
#define	POSXY	598
#define	WAVEFORM	599
#define	AMPL	600
#define	FREQ	601
#define	XVELADD	602
#define	YVELADD	603
#define	ANIMTYME	604
#define	AIRTYPE	605
#define	GROUNDTYPE	606
#define	DAMAGE	607
#define	FALLCOUNT	608
#define	HITSHAKETIME	609
#define	HITTIME	610
#define	SLIDETIME	611
#define	CTRLTIME	612
#define	RECOVERTIME	613
#define	XOFF	614
#define	YOFF	615
#define	ZOFF	616
#define	XVEL	617
#define	YVEL	618
#define	YACELL	619
#define	HITID	620
#define	CHAINID	621
#define	GUARDED	622
#define	FALL	623
#define	FALLDAMAGE	624
#define	FALLXVEL	625
#define	FALLYVEL	626
#define	FALLRECOVER	627
#define	FALLTIME	628
#define	FALLRECOVERTIME	629
#define	FALLKILL	630
#define	FALLENVTIME	631
#define	FALLENVFREQ	632
#define	FALLENVAMPL	633
#define	FALLENVDIR	634
#define	FALLENVPHASE	635
#define	FX	636
#define	ADD	637
#define	MUL	638
#define	SINADD	639
#define	INTERVALL	640
#define	COLOR	641
#define	UNDER	642

#line 1 "praserrules.txt"

#include <malloc.h>  // _alloca is used by the parser
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


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		577
#define	YYFLAG		-32768
#define	YYNTBASE	397

#define YYTRANSLATE(x) ((unsigned)(x) <= 642 ? yytranslate[x] : 407)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,   395,
   396,    21,    19,     3,    20,     2,    23,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
   393,     2,   394,     2,     2,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    22,    24,    25,    26,    27,    28,    29,    30,
    31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
   101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
   111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
   121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
   131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
   141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
   151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
   191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
   201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
   211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
   221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
   231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
   241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
   251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
   261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
   271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
   281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
   291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
   301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
   311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
   321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
   331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
   341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
   351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
   361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
   371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
   381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
   391,   392
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     6,    11,    15,    19,    23,    27,    31,
    35,    39,    43,    47,    51,    55,    59,    65,    67,    74,
    81,    88,    95,   103,   110,   112,   114,   116,   120,   124,
   128,   132,   136,   140,   144,   148,   152,   156,   160,   164,
   168,   172,   176,   180,   184,   188,   192,   196,   200,   204,
   208,   212,   216,   220,   224,   228,   232,   236,   240,   244,
   248,   252,   256,   260,   264,   268,   272,   276,   280,   284,
   288,   292,   296,   300,   304,   308,   312,   316,   320,   324,
   328,   332,   336,   340,   344,   348,   352,   356,   360,   364,
   368,   372,   376,   380,   384,   388,   392,   396,   400,   404,
   408,   412,   416,   420,   424,   428,   432,   436,   440,   444,
   448,   452,   456,   460,   464,   468,   471,   475,   477,   479,
   483,   486,   489,   491,   493,   495,   498,   501,   504,   506,
   509,   512,   514,   516,   518,   520,   523,   525,   530,   533,
   535,   537,   540,   542,   545,   547,   549,   551,   553,   558,
   560,   562,   564,   566,   568,   570,   572,   574,   576,   585,
   587,   589,   591,   593,   595,   598,   605,   607,   609,   611,
   613,   615,   617,   619,   621,   623,   625,   627,   629,   632,
   634,   637,   639,   641,   643,   646,   649,   651,   653,   655,
   657,   659,   661,   663,   665,   667,   669,   671,   673,   675,
   677,   679,   681,   683,   686,   688,   690,   692,   694,   696,
   699,   701,   704,   706,   709,   711,   713,   715,   717,   719,
   721,   723,   725,   727,   729,   732,   735,   737,   739,   742,
   745,   748,   750,   752,   754,   756,   758,   760,   763,   765,
   767,   769,   771,   773,   775,   778,   782,   786,   790,   793,
   797,   801,   805,   809,   813,   817,   821,   825,   829,   837,
   845,   853,   861,   865,   873,   881,   889,   897,   901,   905,
   909,   913,   917,   921,   926,   931,   936,   941,   946,   951,
   955,   958,   960,   962,   964,   966,   968,   970,   972,   974,
   976,   978,   980,   982,   984,   986,   988,   990,   992,   994,
   996,   998,  1000,  1002,  1004,  1006,  1008,  1010,  1012,  1014,
  1016,  1018,  1020,  1022,  1024,  1026,  1028,  1030,  1032,  1034,
  1036,  1038,  1040,  1042,  1044,  1046,  1048,  1050,  1052,  1054,
  1058,  1062,  1066,  1070,  1074,  1077,  1081,  1085,  1089,  1093,
  1097,  1101,  1105,  1109,  1113,  1117,  1121,  1125,  1129,  1133,
  1137,  1141,  1145,  1149,  1153,  1155,  1157,  1159,  1161,  1163,
  1165,  1167,  1169,  1171,  1173,  1175,  1177,  1179,  1181,  1183,
  1185,  1187,  1189,  1191,  1193,  1195,  1197,  1199,  1201,  1203,
  1205,  1207,  1209,  1211,  1213,  1215,  1217,  1219,  1221,  1223,
  1225,  1228,  1236,  1242,  1246
};

static const short yyrhs[] = {    -1,
   397,   398,     0,     1,     0,   393,   113,   402,   394,     0,
   114,    13,   402,     0,   115,    13,   402,     0,   116,    13,
   402,     0,   117,    13,   402,     0,   132,    13,   402,     0,
   269,    13,   402,     0,   118,    13,   402,     0,   120,    13,
   402,     0,   121,    13,   402,     0,   122,    13,   402,     0,
   277,    13,   402,     0,   119,    13,   402,     0,   296,    13,
   402,     3,   402,     0,   399,     0,   393,   123,   402,     3,
   402,   394,     0,   393,   123,   402,     3,    48,   394,     0,
   393,   123,   402,     3,   236,   394,     0,   393,   123,   402,
     3,    56,   394,     0,   393,   123,   402,     3,    56,   402,
   394,     0,   393,   123,   402,     3,     1,   394,     0,   400,
     0,   401,     0,   404,     0,   114,    13,   213,     0,   114,
    13,   214,     0,   114,    13,   215,     0,   114,    13,   216,
     0,   114,    13,   217,     0,   114,    13,   218,     0,   114,
    13,   219,     0,   114,    13,   220,     0,   114,    13,   221,
     0,   114,    13,   222,     0,   114,    13,    79,     0,   114,
    13,   223,     0,   114,    13,   224,     0,   114,    13,   225,
     0,   114,    13,   226,     0,   114,    13,   227,     0,   114,
    13,   228,     0,   114,    13,   229,     0,   114,    13,   230,
     0,   114,    13,   231,     0,   114,    13,   232,     0,   114,
    13,   233,     0,   114,    13,   234,     0,   114,    13,   235,
     0,   114,    13,   236,     0,   114,    13,   237,     0,   114,
    13,   238,     0,   114,    13,   239,     0,   114,    13,   240,
     0,   114,    13,   241,     0,   114,    13,   242,     0,   114,
    13,   243,     0,   114,    13,   244,     0,   114,    13,   245,
     0,   114,    13,   246,     0,   114,    13,   247,     0,   114,
    13,   248,     0,   114,    13,   249,     0,   114,    13,   250,
     0,   114,    13,   251,     0,   114,    13,   252,     0,   114,
    13,   253,     0,   114,    13,   254,     0,   114,    13,   255,
     0,   114,    13,   256,     0,   114,    13,   257,     0,   114,
    13,   258,     0,   114,    13,   259,     0,   114,    13,   260,
     0,   114,    13,   261,     0,   114,    13,   262,     0,   114,
    13,   263,     0,   114,    13,   264,     0,   114,    13,   265,
     0,   114,    13,   266,     0,   114,    13,   267,     0,   114,
    13,   268,     0,   114,    13,   269,     0,   114,    13,   270,
     0,   114,    13,   271,     0,   114,    13,   272,     0,   114,
    13,   273,     0,   114,    13,   274,     0,   114,    13,   275,
     0,   114,    13,   276,     0,   114,    13,   277,     0,   114,
    13,   278,     0,   114,    13,   279,     0,   114,    13,   280,
     0,   114,    13,   281,     0,   114,    13,   282,     0,   114,
    13,   283,     0,   114,    13,   284,     0,   114,    13,   285,
     0,   114,    13,   286,     0,   114,    13,   287,     0,   114,
    13,   288,     0,   114,    13,   289,     0,   114,    13,   290,
     0,   114,    13,   291,     0,   114,    13,   292,     0,   114,
    13,   293,     0,   114,    13,   294,     0,   114,    13,   295,
     0,   114,    13,   296,     0,   114,    13,   297,     0,   111,
    13,   402,     0,   112,    13,   402,     0,   110,   110,     0,
   110,   110,   110,     0,   110,     0,    57,     0,   386,     3,
   402,     0,    25,   402,     0,    24,   402,     0,   124,     0,
   117,     0,   125,     0,    26,   402,     0,    27,   402,     0,
    28,   402,     0,   126,     0,    29,   402,     0,    30,   402,
     0,   127,     0,   128,     0,   129,     0,   130,     0,    31,
   402,     0,   131,     0,    53,   395,   403,   396,     0,    32,
   402,     0,   132,     0,   133,     0,    33,   402,     0,   134,
     0,    34,   402,     0,   135,     0,   136,     0,   137,     0,
   138,     0,    35,   395,   405,   396,     0,   139,     0,   140,
     0,   141,     0,   142,     0,   143,     0,   144,     0,   145,
     0,   146,     0,   147,     0,    51,   395,   402,     3,   402,
     3,   402,   396,     0,   148,     0,   149,     0,   150,     0,
   151,     0,   152,     0,    36,   402,     0,    52,   395,   402,
     3,   402,   396,     0,   153,     0,   154,     0,   155,     0,
   156,     0,   157,     0,   158,     0,   159,     0,   160,     0,
   115,     0,   161,     0,   162,     0,   163,     0,    37,   402,
     0,    37,     0,    38,   402,     0,    38,     0,   164,     0,
   165,     0,    39,   402,     0,    40,   402,     0,    40,     0,
   166,     0,   167,     0,   168,     0,   169,     0,   170,     0,
   171,     0,   172,     0,   173,     0,   174,     0,   175,     0,
   176,     0,   177,     0,   178,     0,   179,     0,   180,     0,
   181,     0,    41,   402,     0,   182,     0,   183,     0,   184,
     0,   185,     0,   186,     0,    42,   402,     0,   187,     0,
    49,   402,     0,   188,     0,    50,   402,     0,   189,     0,
   190,     0,   191,     0,   192,     0,   193,     0,   194,     0,
   195,     0,   196,     0,   197,     0,   198,     0,    43,   402,
     0,    44,   402,     0,   199,     0,   200,     0,    45,   402,
     0,    46,   402,     0,    47,   402,     0,   201,     0,   202,
     0,   203,     0,   204,     0,   205,     0,   206,     0,    48,
   402,     0,   207,     0,   208,     0,   209,     0,   210,     0,
   211,     0,   212,     0,     9,   402,     0,   402,    10,   402,
     0,   402,    11,   402,     0,   402,    12,   402,     0,     5,
   402,     0,   402,     6,   402,     0,   402,     7,   402,     0,
   402,     8,   402,     0,   402,    19,   402,     0,   402,    20,
   402,     0,   402,    21,   402,     0,   402,    23,   402,     0,
   402,    22,   402,     0,   402,    13,   402,     0,   402,    13,
   393,   402,     3,   402,   394,     0,   402,    13,   393,   402,
     3,   402,   396,     0,   402,    13,   395,   402,     3,   402,
   394,     0,   402,    13,   395,   402,     3,   402,   396,     0,
   402,    14,   402,     0,   402,    14,   393,   402,     3,   402,
   394,     0,   402,    14,   393,   402,     3,   402,   396,     0,
   402,    14,   395,   402,     3,   402,   394,     0,   402,    14,
   395,   402,     3,   402,   396,     0,   402,    15,   402,     0,
   402,    16,   402,     0,   402,    17,   402,     0,   402,    18,
   402,     0,   395,   402,   396,     0,   395,   402,     1,     0,
   402,     3,    13,   402,     0,   402,     3,    14,   402,     0,
   402,     3,    15,   402,     0,   402,     3,    16,   402,     0,
   402,     3,    17,   402,     0,   402,     3,    18,   402,     0,
   402,     4,   402,     0,    20,   402,     0,   151,     0,    60,
     0,    61,     0,    62,     0,    63,     0,    64,     0,    65,
     0,    66,     0,    67,     0,    69,     0,    70,     0,    72,
     0,    73,     0,    74,     0,    75,     0,    76,     0,    77,
     0,    79,     0,    80,     0,    81,     0,    82,     0,    83,
     0,    84,     0,    85,     0,    86,     0,    87,     0,    88,
     0,    90,     0,    91,     0,    92,     0,    93,     0,    94,
     0,    95,     0,    96,     0,    97,     0,    98,     0,    99,
     0,   100,     0,   101,     0,   102,     0,   103,     0,   105,
     0,   106,     0,   107,     0,   108,     0,   109,     0,   344,
     0,   343,     0,   338,    13,   406,     0,   339,    13,   406,
     0,   340,    13,   402,     0,   341,    13,   402,     0,   342,
    13,   402,     0,    46,   402,     0,   345,    13,   110,     0,
   346,    13,   110,     0,   348,    13,   406,     0,   347,    13,
   402,     0,   200,    13,   402,     0,   115,    13,   402,     0,
   116,    13,   402,     0,   349,    13,   402,     0,   204,    13,
   402,     0,   350,    13,   406,     0,   351,    13,   402,     0,
   309,    13,   402,     0,   387,    13,   406,     0,   388,    13,
   406,     0,   389,    13,   402,     0,   391,    13,   402,     0,
   390,    13,   402,     0,   392,    13,   402,     0,   191,    13,
   402,     0,   352,     0,   353,     0,   114,     0,   354,     0,
   355,     0,   356,     0,   357,     0,   139,     0,   358,     0,
   359,     0,   360,     0,   361,     0,   362,     0,   363,     0,
   364,     0,   365,     0,   366,     0,   367,     0,   368,     0,
   369,     0,   370,     0,   371,     0,   372,     0,   373,     0,
   374,     0,   375,     0,   376,     0,   377,     0,   378,     0,
   379,     0,   380,     0,   381,     0,   382,     0,   383,     0,
   384,     0,   385,     0,     3,   406,     0,   402,     3,   402,
     3,   402,     3,   402,     0,   402,     3,   402,     3,   402,
     0,   402,     3,   402,     0,   402,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   442,   443,   444,   448,   449,   450,   451,   452,   453,   454,
   455,   456,   457,   458,   459,   460,   461,   463,   466,   467,
   468,   469,   470,   471,   472,   473,   474,   478,   479,   480,
   481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
   491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
   501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
   511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
   521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
   531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
   541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
   551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
   561,   562,   563,   567,   568,   574,   577,   581,   583,   584,
   589,   590,   591,   592,   594,   596,   597,   598,   599,   600,
   601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
   611,   612,   613,   614,   615,   616,   617,   618,   619,   620,
   621,   622,   623,   624,   625,   627,   630,   632,   634,   636,
   637,   638,   639,   640,   641,   642,   644,   647,   650,   653,
   654,   655,   656,   657,   658,   659,   660,   661,   663,   666,
   669,   672,   674,   675,   676,   678,   680,   683,   685,   688,
   691,   694,   696,   698,   699,   700,   701,   702,   703,   704,
   706,   708,   711,   712,   713,   715,   717,   719,   720,   721,
   722,   723,   724,   725,   726,   727,   728,   730,   733,   736,
   737,   738,   740,   742,   745,   746,   747,   748,   749,   750,
   751,   752,   753,   754,   755,   756,   757,   758,   760,   763,
   766,   767,   768,   769,   771,   772,   773,   774,   776,   777,
   778,   779,   783,   784,   785,   786,   788,   790,   791,   792,
   793,   794,   796,   797,   798,   799,   800,   802,   803,   804,
   805,   807,   809,   812,   819,   826,   833,   840,   847,   854,
   855,   859,   860,   861,   862,   863,   864,   865,   866,   867,
   868,   869,   870,   871,   872,   873,   874,   875,   876,   877,
   878,   879,   880,   881,   882,   883,   884,   885,   886,   887,
   888,   889,   890,   891,   892,   893,   894,   895,   896,   897,
   898,   899,   900,   901,   902,   903,   904,   905,   906,   909,
   910,   911,   912,   913,   914,   915,   916,   917,   918,   919,
   920,   921,   922,   923,   924,   925,   926,   927,   928,   929,
   930,   931,   932,   933,   938,   939,   940,   941,   942,   943,
   944,   945,   946,   947,   948,   949,   950,   951,   952,   953,
   954,   955,   956,   957,   958,   959,   960,   961,   962,   963,
   964,   965,   966,   967,   968,   969,   970,   971,   972,   973,
   977,   979,   980,   981,   982
};

static const char * const yytname[] = {   "$","error","$undefined.","','","MOD",
"LOGNOT","LOGAND","LOGOR","LOGXOR","NOT","AND","OR","XOR","EQUAL","NOTEQUAL",
"GREATER","LESS","LESSEQUAL","GREATEREQUAL","'+'","'-'","'*'","SQUARE","'/'",
"ACOS","ABS","ANIMELEMNO","ANIMELEMTIME","ANIMEXIST","ASIN","ATAN","CEIL","COS",
"EXP","FLOOR","GETHITVAR","LN","NUMEXPLOD","NUMHELPER","NUMPROJID","NUMTARGET",
"PLAYERIDEXIST","PROJCANCLETIME","SELFANIMEXIST","SIN","SYSFVAR","SYSVAR","TAN",
"VAR","PROJCONTACTTIME","PROJGUARDEDTIME","IFELSE","LOG","CONST","UMINUS","UPLUS",
"ID","STRING","NEGONE","DATA","ATTACK","DEFENCE","FALLDEFUP","LIEDOWTIME","AIRJUGGLE",
"SPARKNO","GUARDSPARKNO","KOECHO","VOLUME","INTEGERINDEX","FLOATINDEX","SIZE",
"XSCALE","YSCALE","GROUNDBACK","GROUNDFRONT","AIRBACK","AIRFRONT","HEIGHT","ATTACKDIST",
"PROJATTDIST","PROJDOSCALE","HEADPOSX","HEADPOSY","MIDPOSX","MIDPOSY","SHADOWOFFSET",
"DRAWOFFSETX","DRAWOFFSETY","VELOCITY","WALKFWD","WALKBACK","RUNFWDX","RUNFWDY",
"RUNBACKX","RUNBACKY","JUMPNEU","JUMPBACK","JUMPFWD","RUNJUMPBACK","RUNJUMPFWD",
"AIRJUMPNEU","AIRJUMPBACK","AIRJUMPFWD","MOVEMENT","AIRJUMPNUM","AIRJUMPHEIGHT",
"YACCEL","STANDFRICTION","CROUCHFRICTION","NUMBER","TRIGGER","TRIGGERALL","STATEDEF",
"TYPE","MOVETYPE","PHYSICS","ANIM","JUGGLE","FACEP2","HITDEFPERSIST","MOVEHITPERSIST",
"HITCOUNTPERSIST","STATE","ALIVE","ANIMELEM","ANIMTIME","AUTHORNAME","BACKEEDGEBODYDIST",
"BACKEDGEDIST","CANRECOVER","COMMAND","CTRL","DRAWGAME","FACING","FRONTEDGEBODYDIST",
"FRONTEDGEDIST","FVAR","GAMETIME","HITCOUNT","HITDEFATTR","HITFALL","HITOVER",
"HITPAUSETIME","HITSHAKEOVER","HITVELX","HITVELY","PLID","INGUARDDIST","ISHELPER",
"ISHOMETEAM","LIFE","LIFEMAX","LOSE","LOSEKO","LOSETIME","MATCHNO","MATCHOVER",
"MOVECONTACT","MOVEGUARDED","MOVEHIT","MOVEREVERSED","NAME","NUMENEMY","NUMPARTNER",
"NUMPROJ","P1NAME","P2BODYDISTX","P2BODYDISTY","P2DISTX","P2DISTY","P2LIFE",
"P2MOVETYPE","P2NAME","P2STATENO","P2STATETYP","P3NAME","P4NAME","PALNO","PARENTDISTX",
"PARENTDISTY","PI","PREVSTATENO","POSX","POSY","POWER","POWERMAX","PROJCONTACT",
"PROJGUARDED","PROJHIT","PROJHITTIME","RANDOM","ROOTDISTX","ROOTDISTY","ROUNDNO",
"ROUNDSEXISTED","ROUNDSTATE","SCREENPOSX","SCREENPOSY","STATENO","STATETYPE",
"TEAMMODE","TEAMSIDE","TICKSPERSECOND","TIME","TIMEMODE","UNIQHITCOUNT","VELX",
"VELY","WIN","WINKO","WINTIME","WINPERFECT","TNULL","AFTERIMAGE","AFTERIMAGETIME",
"ALLPALFX","ANGLEADD","ANGLEDRAW","ANGLEMUL","ANGLESET","APPENDTOCLIPBOARD",
"ASSERTSPECIAL","ATTACKMULSET","BGPALFX","BINDTOPARENT","BINDTOROOT","BINDTOTARGET",
"CHANGEANIME","CHANGEANIME2","CHANGESTATE","CLEARCLIPBOARD","CTRLSET","DEFENCEMULSET",
"DESTROYSELF","DISPLAYTOCLIPBOARD","ENVSHAKE","EXPLOD","EXPLODBINDTIME","FALLENVSHAKE",
"FORCEFEDDBACK","GAMEMAKEANIM","GRAVITY","HELPER","HITADD","HITBY","HITDEF",
"HITFALLDAMAGE","HITFALLSET","HITFALLVEL","HITOVERRIDE","HITVELSET","LIFEADD",
"LIFESET","MAKEDUST","MODIFYEXPLOD","MOVEHITRESET","NOTHITBY","NUL","OFFSET",
"PALFX","PARENTVARADD","PARENTVARSET","PAUSE","PLAYERPUSH","PLAYSND","POSADD",
"POSFREEZ","POSSET","POWERADD","POWERSET","PROJECTILE","REMOVEEXPLOD","REVERSALDEF",
"SCREENBOUND","SELFSTATE","SNDPAN","SPRPRIORITY","STATETYPESET","STOPSND","SUPERPAUSE",
"TARGETBIND","TARGETDROP","TARGETFACING","TARGETLIFEADD","TARGETPOWERADD","TARGETSTATE",
"TARGETVELADD","TARGETVELSET","TURN","VARADD","VARRANDOM","VARRANGESET","VARSET",
"VELADD","VELMUL","VELSET","WIDTH","LENGTH","PALCOLOR","PALINVERTALL","PALBRIGHT",
"PALCONTRAST","PALPOSTBRIGHT","PALADD","PALMUL","TIMEGAP","FRAMEGAP","TRANS",
"FVALUE","ACBEGIN","ACTION","LOOPSTART","CLSN2DEFAULT","CLSN1DEFAULT","CLSN2",
"CLSN1","HORIZONTALFLIP","VERTIKALFLIP","HVFLIP","ALPHA","INFO","DISPLAYNAME",
"VERSIONSDATA","MUGENVERSION","AUTHOR","FILES","CMD","CNS","ST","STCOMMON","SPRITE",
"SOUND","PAL","PALDEF","ARCADE","INTROSTORYBOARD","ENDINGSTORYBOARD","VALUE",
"VALUE2","XVALUE","YVALUE","ZVALUE","JUMPNEUY","AIRJUMPNEUY","PERSISTENT","IGNOREHITPAUSE",
"SPACING","POSXY","WAVEFORM","AMPL","FREQ","XVELADD","YVELADD","ANIMTYME","AIRTYPE",
"GROUNDTYPE","DAMAGE","FALLCOUNT","HITSHAKETIME","HITTIME","SLIDETIME","CTRLTIME",
"RECOVERTIME","XOFF","YOFF","ZOFF","XVEL","YVEL","YACELL","HITID","CHAINID",
"GUARDED","FALL","FALLDAMAGE","FALLXVEL","FALLYVEL","FALLRECOVER","FALLTIME",
"FALLRECOVERTIME","FALLKILL","FALLENVTIME","FALLENVFREQ","FALLENVAMPL","FALLENVDIR",
"FALLENVPHASE","FX","ADD","MUL","SINADD","INTERVALL","COLOR","UNDER","'['","']'",
"'('","')'","lines","STATEDEFSECTION","STATESECTION","TYPESECTION","TRIGGERSECTION",
"expression","CONSTPARAM","PARAMSECTION","GETHITPARAM","expr",""
};
#endif

static const short yyr1[] = {     0,
   397,   397,   397,   398,   398,   398,   398,   398,   398,   398,
   398,   398,   398,   398,   398,   398,   398,   398,   399,   399,
   399,   399,   399,   399,   399,   399,   399,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
   400,   400,   400,   401,   401,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
   402,   403,   403,   403,   403,   403,   403,   403,   403,   403,
   403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
   403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
   403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
   403,   403,   403,   403,   403,   403,   403,   403,   403,   404,
   404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
   404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
   404,   404,   404,   404,   405,   405,   405,   405,   405,   405,
   405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
   405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
   405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
   406,   406,   406,   406,   406
};

static const short yyr2[] = {     0,
     0,     2,     1,     4,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     5,     1,     6,     6,
     6,     6,     7,     6,     1,     1,     1,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     2,     3,     1,     1,     3,
     2,     2,     1,     1,     1,     2,     2,     2,     1,     2,
     2,     1,     1,     1,     1,     2,     1,     4,     2,     1,
     1,     2,     1,     2,     1,     1,     1,     1,     4,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     8,     1,
     1,     1,     1,     1,     2,     6,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
     2,     1,     1,     1,     2,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
     1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     2,     2,     1,     1,     2,     2,
     2,     1,     1,     1,     1,     1,     1,     2,     1,     1,
     1,     1,     1,     1,     2,     3,     3,     3,     2,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     7,     7,
     7,     7,     3,     7,     7,     7,     7,     3,     3,     3,
     3,     3,     3,     4,     4,     4,     4,     4,     4,     3,
     2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
     3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2,     7,     5,     3,     1
};

static const short yydefact[] = {     0,
     3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     2,    18,    25,    26,    27,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   180,   182,     0,   187,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
   118,   175,   124,   123,   125,   129,   132,   133,   134,   135,
   137,   140,   141,   143,   145,   146,   147,   148,   150,   151,
   152,   153,   154,   155,   156,   157,   158,   160,   161,   162,
   163,   164,   167,   168,   169,   170,   171,   172,   173,   174,
   176,   177,   178,   183,   184,   188,   189,   190,   191,   192,
   193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
   203,   205,   206,   207,   208,   209,   211,   213,   215,   216,
   217,   218,   219,   220,   221,   222,   223,   224,   227,   228,
   232,   233,   234,   235,   236,   237,   239,   240,   241,   242,
   243,   244,     0,     0,   335,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   249,   245,   281,   122,   121,   126,
   127,   128,   130,   131,   136,   139,   142,   144,     0,   165,
   179,   181,   185,   186,   204,   210,   225,   226,   229,   230,
   231,   238,   212,   214,     0,     0,     0,   116,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
   115,    38,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,     5,     6,     7,
     8,    11,    16,    12,    13,    14,     9,   354,   340,   344,
    10,    15,     0,   347,     0,   395,   330,   331,   332,   333,
   334,   336,   337,   339,   338,   343,   345,   346,   348,   349,
   350,   352,   351,   353,     0,     0,   357,   362,   355,   356,
   358,   359,   360,   361,   363,   364,   365,   366,   367,   368,
   369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
   379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
   389,   390,     0,     0,     0,   283,   284,   285,   286,   287,
   288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
   298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
   308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
   318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
   282,   329,   328,     0,   117,   120,   273,   272,     0,     0,
     0,     0,     0,     0,   280,   250,   251,   252,   246,   247,
   248,     0,     0,   258,     0,     0,   263,   268,   269,   270,
   271,   253,   254,   255,   257,   256,     0,   391,     0,     4,
     0,   149,     0,     0,   138,   274,   275,   276,   277,   278,
   279,     0,     0,     0,     0,    17,   394,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
    20,    22,     0,    21,    19,     0,   166,     0,     0,     0,
     0,   393,    23,     0,   259,   260,   261,   262,   264,   265,
   266,   267,     0,   159,   392,     0,     0
};

static const short yydefgoto[] = {     2,
    42,    43,    44,    45,   376,   484,    46,   433,   377
};

static const short yypact[] = {    29,
-32768,   760,  3059,   -11,    -8,    -4,    11,    13,    14,    18,
    22,    45,    65,    69,    85,    88,    92,   108,   112,   129,
   149,   150,   151,   152,   153,   154,   155,   156,   157,   159,
   179,   180,   184,   185,   187,   189,   192,   199,   200,   201,
   -85,-32768,-32768,-32768,-32768,-32768,  3059,  3059,  3059,  3059,
  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,
  -362,  3059,  3331,  3331,  3059,  3331,  3059,  3059,  3059,  3059,
  3059,  3059,  3059,  3059,  3059,  3059,  -180,  -179,  -178,-32768,
   109,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   215,  3059,   297,  3059,  3059,  1406,  3059,  3059,
  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,
  3059,  3059,  3059,  3059,  1134,  1134,  3059,  3059,  3059,   111,
   113,  3059,  1134,  3059,  1134,  3059,  1134,  1134,  3059,  3059,
  3059,  3059,  3059,  3059,   340,   340,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   840,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,  3059,  3059,  3226,   114,  3059,     0,
   139,  3059,  3059,  3059,  3059,  3059,  3059,  3059,  1971,  2243,
  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,  3059,   297,
   297,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   297,   297,   297,
   297,   297,   297,   297,   297,   297,   297,   297,   297,   297,
   297,   297,   329,   297,  1134,   758,-32768,-32768,   297,   297,
   297,-32768,-32768,   297,-32768,   297,-32768,   297,-32768,-32768,
   297,   297,   297,   297,   835,   883,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,  -174,   904,  1028,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,  -170,-32768,   116,-32768,-32768,  3059,  3059,
  3059,  3059,  3059,  3059,   340,   340,   340,   340,   340,   340,
   340,  3059,  3059,    20,  3059,  3059,    20,    20,    20,    20,
    20,   137,   137,-32768,-32768,-32768,  1699,-32768,  1699,-32768,
   547,-32768,  1699,  1699,-32768,    20,    20,    20,    20,    20,
    20,  1060,    73,  1109,    96,   297,  1344,  -169,  2515,  2787,
  -167,   955,  1374,   602,  1699,  1699,  1699,  1699,  1699,-32768,
-32768,-32768,   989,-32768,-32768,  1699,-32768,   264,   391,   420,
   441,  1458,-32768,   623,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,  1699,-32768,   297,   228,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,    -3,-32768,-32768,-32768,  -171
};


#define	YYLAST		3726


static const short yytable[] = {   175,
   487,   176,   251,   252,   177,   253,   254,   255,   178,   256,
   257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
   267,   268,   269,   179,   378,   180,   181,   213,    -1,     1,
   182,   385,   229,   387,   183,   389,   390,   214,   265,   266,
   267,   268,   269,   215,   216,   217,   218,   219,   220,   221,
   222,   223,   224,   225,   226,   227,   228,   184,   230,   231,
   232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
   242,   243,   244,   487,    -1,   546,   252,   185,   253,   254,
   255,   186,   256,   257,   258,   259,   260,   261,   262,   263,
   264,   265,   266,   267,   268,   269,   487,   187,   548,   252,
   188,   253,   254,   255,   189,   256,   257,   258,   259,   260,
   261,   262,   263,   264,   265,   266,   267,   268,   269,   252,
   190,   253,   254,   255,   191,   256,   257,   258,   259,   260,
   261,   262,   263,   264,   265,   266,   267,   268,   269,    -1,
    -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   489,   490,   491,   492,   493,   494,   267,   268,   269,
    -1,   193,   194,   195,   196,   197,   198,   199,   200,   201,
   250,   202,   270,   271,   358,   359,   360,   361,   362,   363,
   364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
   374,   203,   204,   379,   380,   381,   205,   206,   384,   207,
   386,   208,   388,   518,   209,   391,   392,   393,   394,   395,
   396,   210,   211,   212,   245,   246,   247,   249,   248,    -1,
   382,   522,   383,   485,   550,   525,   554,   577,    -1,     0,
     0,     0,    -1,     0,     0,     0,     0,     0,     0,     0,
     0,   434,   435,     0,     0,   486,     0,     0,   495,   496,
   497,   498,   499,   500,   501,   504,   507,   508,   509,   510,
   511,   512,   513,   514,   515,   516,   251,   252,     0,   253,
   254,   255,     0,   256,   257,   258,   259,   260,   261,   262,
   263,   264,   265,   266,   267,   268,   269,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    -1,     0,   251,
   252,     0,   253,   254,   255,    -1,   256,   257,   258,   259,
   260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     0,     0,     0,     0,    -1,     0,     0,     0,     0,     0,
     0,   517,   252,     0,   253,   254,   255,    -1,   256,   257,
   258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
   268,   269,   259,   260,   261,   262,   263,   264,   265,   266,
   267,   268,   269,     0,     0,     0,    -1,    -1,    -1,    -1,
    -1,     0,     0,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   251,   252,   488,   253,   254,   255,     0,
   256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
   266,   267,   268,   269,     0,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   251,   252,     0,   253,   254,   255,     0,   256,
   257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
   267,   268,   269,   251,   252,     0,   253,   254,   255,     0,
   256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
   266,   267,   268,   269,     0,     0,     0,     0,   488,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   526,   527,   528,   529,   530,
   531,   488,     0,     0,     0,     0,     0,     0,   532,   533,
     0,   534,   535,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   536,     0,   537,     0,   542,     0,   543,
   544,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   242,   553,     0,     0,     0,
     0,   558,   559,   560,   561,   562,     0,   538,     0,     0,
     0,    47,   564,     0,     0,    48,     0,     0,     0,   489,
   490,   491,   492,   493,   494,     0,    49,     0,     0,   575,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
    60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
    70,    71,    72,    73,   539,    75,    76,    77,    78,    79,
     0,     0,   540,    80,   251,   252,     0,   253,   254,   255,
     0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
   265,   266,   267,   268,   269,   251,   252,     0,   253,   254,
   255,     0,   256,   257,   258,   259,   260,   261,   262,   263,
   264,   265,   266,   267,   268,   269,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    81,   565,     0,   566,
     0,    82,     0,    83,     0,     0,     0,     0,     0,     0,
    84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
    94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
   104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
   114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
   124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
   134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
   144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
   154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
   164,   165,   166,   167,   168,   169,   170,   171,   172,   576,
   519,   252,     0,   253,   254,   255,     0,   256,   257,   258,
   259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
   269,     0,   541,     0,   567,     0,   568,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
     0,     0,     0,   569,     0,   570,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   571,     0,   572,   251,   252,     0,
   253,   254,   255,     0,   256,   257,   258,   259,   260,   261,
   262,   263,   264,   265,   266,   267,   268,   269,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     4,     5,     0,     6,     7,     8,     9,    10,    11,    12,
    13,    14,     0,     0,     0,   521,   252,     0,   253,   254,
   255,    15,   256,   257,   258,   259,   260,   261,   262,   263,
   264,   265,   266,   267,   268,   269,   523,   252,     0,   253,
   254,   255,     0,   256,   257,   258,   259,   260,   261,   262,
   263,   264,   265,   266,   267,   268,   269,     0,     0,     0,
     0,     0,   173,     0,     0,     0,     0,     0,     0,     0,
     0,   174,     0,     0,     0,     0,     0,     0,     0,     0,
    16,     0,     0,   397,     0,     0,     0,   251,   252,    17,
   253,   254,   255,    18,   256,   257,   258,   259,   260,   261,
   262,   263,   264,   265,   266,   267,   268,   269,   398,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   251,   252,     0,   253,   254,   255,   557,   256,   257,
   258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
   268,   269,     0,     0,     0,     0,     0,     0,   574,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
   524,   252,     0,   253,   254,   255,    20,   256,   257,   258,
   259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
   269,     0,     0,     0,     0,    21,     0,     0,     0,     0,
     0,     0,   545,   252,     0,   253,   254,   255,    22,   256,
   257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
   267,   268,   269,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    23,    24,    25,
    26,    27,     0,     0,    28,    29,    30,    31,    32,    33,
    34,   547,   252,     0,   253,   254,   255,     0,   256,   257,
   258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
   268,   269,     0,     0,     0,     0,   375,     0,    47,     0,
     0,     0,    48,     0,     0,     0,    35,    36,    37,    38,
    39,    40,    41,    49,     0,     0,     0,    50,    51,    52,
    53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
    63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
    73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
    80,   399,   400,   401,   402,   403,   404,   405,   406,   407,
   408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
   418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
   428,   429,   430,   431,   432,     0,     0,     0,   520,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    81,     0,     0,     0,     0,    82,     0,
    83,     0,     0,     0,     0,     0,     0,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
   147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   549,   252,   555,   253,
   254,   255,     0,   256,   257,   258,   259,   260,   261,   262,
   263,   264,   265,   266,   267,   268,   269,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   556,   252,     0,   253,
   254,   255,   563,   256,   257,   258,   259,   260,   261,   262,
   263,   264,   265,   266,   267,   268,   269,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    47,     0,     0,     0,    48,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    49,     0,     0,     0,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
   573,   252,    80,   253,   254,   255,     0,   256,   257,   258,
   259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
   269,     0,     0,     0,   272,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    81,     0,     0,     0,   173,
    82,     0,    83,     0,     0,     0,     0,     0,   174,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
   105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
   115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
   125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
   135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
   145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
   155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   273,   274,
   275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
   285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
   295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
   305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
   315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
   325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
   335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
   345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
   355,   356,   357,    47,     0,     0,     0,    48,     0,     0,
     0,   489,   490,   491,   492,   493,   494,     0,    49,     0,
     0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
    68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
    78,    79,     0,     0,     0,    80,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   173,     0,     0,     0,     0,     0,     0,     0,     0,
   174,     0,     0,     0,     0,     0,     0,     0,    81,     0,
     0,     0,     0,    82,     0,    83,     0,     0,     0,     0,
     0,     0,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
   102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
   132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
   142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
   152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
   162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
   172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    47,     0,     0,     0,    48,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    49,     0,     0,     0,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,     0,     0,     0,    80,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    81,     0,     0,     0,   173,    82,     0,    83,     0,     0,
     0,     0,     0,   174,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
   100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
   110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
   120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
   130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
   140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
   150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
   160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
   170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    47,     0,     0,
     0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    49,     0,     0,     0,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
    74,    75,    76,    77,    78,    79,     0,     0,     0,    80,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    81,     0,     0,     0,   173,    82,     0,    83,
     0,     0,     0,   502,     0,   503,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
    98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
   108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
   118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
   128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
   138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
   148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
   158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
   168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
     0,     0,     0,    48,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
    72,    73,    74,    75,    76,    77,    78,    79,     0,     0,
     0,    80,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    81,     0,     0,     0,   173,    82,
     0,    83,     0,     0,     0,   505,     0,   506,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
   126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
   136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
   146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
   156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    47,     0,     0,     0,    48,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
    60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
    70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
     0,     0,     0,    80,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    81,     0,     0,     0,
   173,    82,     0,    83,     0,     0,     0,     0,   551,   174,
    84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
    94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
   104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
   114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
   124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
   134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
   144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
   154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
   164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    47,     0,     0,     0,    48,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    49,     0,
     0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
    68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
    78,    79,     0,     0,     0,    80,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    81,     0,
     0,     0,   173,    82,     0,    83,     0,     0,     0,     0,
   552,   174,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
   102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
   132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
   142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
   152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
   162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
   172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   436,   437,   438,   439,   440,
   441,   442,   443,     0,   444,   445,     0,   446,   447,   448,
   449,   450,   451,     0,   452,   453,   454,   455,   456,   457,
   458,   459,   460,   461,     0,   462,   463,   464,   465,   466,
   467,   468,   469,   470,   471,   472,   473,   474,   475,     0,
   476,   477,   478,   479,   480,    47,     0,     0,     0,    48,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,   481,    73,    74,    75,
    76,    77,    78,    79,     0,     0,     0,    80,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    81,     0,     0,     0,   173,    82,     0,    83,     0,     0,
     0,     0,     0,   174,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
   100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
   110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
   120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
   130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
   140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
   150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
   160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
   170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   482,   483,
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
     0,     0,     0,     0,     0,     0,   173,     0,     0,     0,
     0,     0,     0,     0,     0,   174
};

static const short yycheck[] = {     3,
     1,    13,     3,     4,    13,     6,     7,     8,    13,    10,
    11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    13,   196,    13,    13,   113,     0,     1,
    13,   203,   395,   205,    13,   207,   208,   123,    19,    20,
    21,    22,    23,    47,    48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    13,    62,    63,
    64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
    74,    75,    76,     1,    46,     3,     4,    13,     6,     7,
     8,    13,    10,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    21,    22,    23,     1,    13,     3,     4,
    13,     6,     7,     8,    13,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,     4,
    13,     6,     7,     8,    13,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,   111,
   112,    13,   114,   115,   116,   117,   118,   119,   120,   121,
   122,    13,    14,    15,    16,    17,    18,    21,    22,    23,
   132,    13,    13,    13,    13,    13,    13,    13,    13,    13,
   174,    13,   176,   177,   178,   179,   180,   181,   182,   183,
   184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
   194,    13,    13,   197,   198,   199,    13,    13,   202,    13,
   204,    13,   206,   375,    13,   209,   210,   211,   212,   213,
   214,    13,    13,    13,   395,   395,   395,     3,   110,   191,
   110,   396,   110,   110,   394,   396,   394,     0,   200,    -1,
    -1,    -1,   204,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   245,   246,    -1,    -1,   249,    -1,    -1,   252,   253,
   254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
   264,   265,   266,   267,   268,   269,     3,     4,    -1,     6,
     7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,     3,
     4,    -1,     6,     7,     8,   277,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,
    -1,     3,     4,    -1,     6,     7,     8,   309,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    13,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    -1,    -1,    -1,   338,   339,   340,   341,
   342,    -1,    -1,   345,   346,   347,   348,   349,   350,   351,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,     3,     4,   396,     6,     7,     8,    -1,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    -1,   387,   388,   389,   390,   391,
   392,   393,     3,     4,    -1,     6,     7,     8,    -1,    10,
    11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,     3,     4,    -1,     6,     7,     8,    -1,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    -1,    -1,    -1,    -1,   396,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   489,   490,   491,   492,   493,
   494,   396,    -1,    -1,    -1,    -1,    -1,    -1,   502,   503,
    -1,   505,   506,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   517,    -1,   519,    -1,   521,    -1,   523,
   524,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   539,   540,    -1,    -1,    -1,
    -1,   545,   546,   547,   548,   549,    -1,     1,    -1,    -1,
    -1,     5,   556,    -1,    -1,     9,    -1,    -1,    -1,    13,
    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,   573,
    24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
    44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
    -1,    -1,    56,    57,     3,     4,    -1,     6,     7,     8,
    -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
    19,    20,    21,    22,    23,     3,     4,    -1,     6,     7,
     8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   110,   394,    -1,   396,
    -1,   115,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,
   124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
   134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
   144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
   154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
   164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
   174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
   184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
   194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
   204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     3,     4,    -1,     6,     7,     8,    -1,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    -1,   236,    -1,   394,    -1,   396,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   394,    -1,   396,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   394,    -1,   396,     3,     4,    -1,
     6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
   121,   122,    -1,    -1,    -1,     3,     4,    -1,     6,     7,
     8,   132,    10,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    21,    22,    23,     3,     4,    -1,     6,
     7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
    -1,    -1,   386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   395,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   191,    -1,    -1,   114,    -1,    -1,    -1,     3,     4,   200,
     6,     7,     8,   204,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,   139,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,     3,     4,    -1,     6,     7,     8,   396,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,   396,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,
     3,     4,    -1,     6,     7,     8,   277,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
    -1,    -1,     3,     4,    -1,     6,     7,     8,   309,    10,
    11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   338,   339,   340,
   341,   342,    -1,    -1,   345,   346,   347,   348,   349,   350,
   351,     3,     4,    -1,     6,     7,     8,    -1,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    -1,    -1,    -1,    -1,     3,    -1,     5,    -1,
    -1,    -1,     9,    -1,    -1,    -1,   387,   388,   389,   390,
   391,   392,   393,    20,    -1,    -1,    -1,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
    57,   352,   353,   354,   355,   356,   357,   358,   359,   360,
   361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
   371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
   381,   382,   383,   384,   385,    -1,    -1,    -1,   394,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,   115,    -1,
   117,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
   147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
   197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
   207,   208,   209,   210,   211,   212,     3,     4,   394,     6,
     7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,     6,
     7,     8,   394,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
     3,     4,    57,     6,     7,     8,    -1,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,   386,
   115,    -1,   117,    -1,    -1,    -1,    -1,    -1,   395,   124,
   125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
   135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
   145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
   155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
   185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
   195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
   205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
   215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
   225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
   235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
   245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
   255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
   265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
   275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
   285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
   295,   296,   297,     5,    -1,    -1,    -1,     9,    -1,    -1,
    -1,    13,    14,    15,    16,    17,    18,    -1,    20,    -1,
    -1,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   395,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,
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
    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
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
    -1,     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
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
    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,    -1,    -1,
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
   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
    65,    66,    67,    -1,    69,    70,    -1,    72,    73,    74,
    75,    76,    77,    -1,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    -1,    90,    91,    92,    93,    94,
    95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
   105,   106,   107,   108,   109,     5,    -1,    -1,    -1,     9,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    41,    42,    43,    44,    45,   151,    47,    48,    49,
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
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   343,   344,
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
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
    printf("Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
	printf("Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
    printf("Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
	printf("Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
	printf("Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
  	  printf("Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
    printf("Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);
	       
      printf ("Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
      {
	      fprintf (stderr, "%s ", yytname[yyrhs[i]]);
          printf ("%s ", yytname[yyrhs[i]]);
	  }
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
      printf (" -> %s\n", yytname[yyr1[yyn]]);
      
    }
#endif


  switch (yyn) {

case 3:
#line 444 "praserrules.txt"
{yyclearin;;
    break;}
case 4:
#line 448 "praserrules.txt"
{myStateManager->AddStateDef((int)yyvsp[-1].nFloat);;
    break;}
case 5:
#line 449 "praserrules.txt"
{myStateManager->GetCurrStateDef()->type=(int)yyvsp[0].nFloat;;
    break;}
case 6:
#line 450 "praserrules.txt"
{myStateManager->GetCurrStateDef()->movetype=(int)yyvsp[0].nFloat;;
    break;}
case 7:
#line 451 "praserrules.txt"
{myStateManager->GetCurrStateDef()->physics=(int)yyvsp[0].nFloat;;
    break;}
case 8:
#line 452 "praserrules.txt"
{myStateManager->GetCurrStateDef()->nAnim=(int)yyvsp[0].nFloat;;
    break;}
case 9:
#line 453 "praserrules.txt"
{myStateManager->GetCurrStateDef()->bCtrl=(int)yyvsp[0].nFloat;;
    break;}
case 10:
#line 454 "praserrules.txt"
{myStateManager->GetCurrStateDef()->nPoweradd=(int)yyvsp[0].nFloat;;
    break;}
case 11:
#line 455 "praserrules.txt"
{myStateManager->GetCurrStateDef()->nJuggle=(int)yyvsp[0].nFloat;;
    break;}
case 12:
#line 456 "praserrules.txt"
{myStateManager->GetCurrStateDef()->bHitdefpersist=(int)yyvsp[0].nFloat;;
    break;}
case 13:
#line 457 "praserrules.txt"
{myStateManager->GetCurrStateDef()->bMovehitpersist=(int)yyvsp[0].nFloat;;
    break;}
case 14:
#line 458 "praserrules.txt"
{myStateManager->GetCurrStateDef()->bHitcountpersist=(int)yyvsp[0].nFloat;;
    break;}
case 15:
#line 459 "praserrules.txt"
{myStateManager->GetCurrStateDef()->nSprpriority=(int)yyvsp[0].nFloat;;
    break;}
case 16:
#line 460 "praserrules.txt"
{myStateManager->GetCurrStateDef()->bFacep2=(int)yyvsp[0].nFloat;;
    break;}
case 17:
#line 461 "praserrules.txt"
{myStateManager->GetCurrStateDef()->Velset.x=yyvsp[-2].nFloat;
                                                         myStateManager->GetCurrStateDef()->Velset.y=yyvsp[0].nFloat;;
    break;}
case 19:
#line 466 "praserrules.txt"
{myStateManager->AddState((int)yyvsp[-3].nFloat,(int)yyvsp[-1].nFloat );;
    break;}
case 20:
#line 467 "praserrules.txt"
{myStateManager->AddState((int)yyvsp[-3].nFloat,"Var" );;
    break;}
case 21:
#line 468 "praserrules.txt"
{myStateManager->AddState((int)yyvsp[-3].nFloat,"EnvShake" );;
    break;}
case 22:
#line 469 "praserrules.txt"
{myStateManager->AddState((int)yyvsp[-3].nFloat,yyvsp[-1].str);;
    break;}
case 23:
#line 470 "praserrules.txt"
{myStateManager->AddState((int)yyvsp[-4].nFloat,yyvsp[-2].str);;
    break;}
case 24:
#line 471 "praserrules.txt"
{myStateManager->AddState((int)yyvsp[-3].nFloat,"Nothing");;
    break;}
case 28:
#line 478 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TNULL);;
    break;}
case 29:
#line 479 "praserrules.txt"
{myStateManager->AddTypeToState(CT_AFTERIMAGE);;
    break;}
case 30:
#line 480 "praserrules.txt"
{myStateManager->AddTypeToState(CT_AFTERIMAGETIME);;
    break;}
case 31:
#line 481 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ALLPALFX);;
    break;}
case 32:
#line 482 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ANGLEADD);;
    break;}
case 33:
#line 483 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ANGLEDRAW);;
    break;}
case 34:
#line 484 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ANGLEMUL);;
    break;}
case 35:
#line 485 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ANGLESET);;
    break;}
case 36:
#line 486 "praserrules.txt"
{myStateManager->AddTypeToState(CT_APPENDTOCLIPBOARD);;
    break;}
case 37:
#line 487 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ASSERTSPECIAL);;
    break;}
case 38:
#line 488 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ATTACKDIST);;
    break;}
case 39:
#line 489 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ATTACKMULSET);;
    break;}
case 40:
#line 490 "praserrules.txt"
{myStateManager->AddTypeToState(CT_BGPALFX);;
    break;}
case 41:
#line 491 "praserrules.txt"
{myStateManager->AddTypeToState(CT_BINDTOPARENT);;
    break;}
case 42:
#line 492 "praserrules.txt"
{myStateManager->AddTypeToState(CT_BINDTOROOT);;
    break;}
case 43:
#line 493 "praserrules.txt"
{myStateManager->AddTypeToState(CT_BINDTOTARGET);;
    break;}
case 44:
#line 494 "praserrules.txt"
{myStateManager->AddTypeToState(CT_CHANGEANIME);;
    break;}
case 45:
#line 495 "praserrules.txt"
{myStateManager->AddTypeToState(CT_CHANGEANIME2);;
    break;}
case 46:
#line 496 "praserrules.txt"
{myStateManager->AddTypeToState(CT_CHANGESTATE);;
    break;}
case 47:
#line 497 "praserrules.txt"
{myStateManager->AddTypeToState(CT_CLEARCLIPBOARD);;
    break;}
case 48:
#line 498 "praserrules.txt"
{myStateManager->AddTypeToState(CT_CTRLSET);;
    break;}
case 49:
#line 499 "praserrules.txt"
{myStateManager->AddTypeToState(CT_DEFENCEMULSET);;
    break;}
case 50:
#line 500 "praserrules.txt"
{myStateManager->AddTypeToState(CT_DESTROYSELF);;
    break;}
case 51:
#line 501 "praserrules.txt"
{myStateManager->AddTypeToState(CT_DISPLAYTOCLIPBOARD);;
    break;}
case 52:
#line 502 "praserrules.txt"
{myStateManager->AddTypeToState(CT_ENVSHAKE);;
    break;}
case 53:
#line 503 "praserrules.txt"
{myStateManager->AddTypeToState(CT_EXPLOD);;
    break;}
case 54:
#line 504 "praserrules.txt"
{myStateManager->AddTypeToState(CT_EXPLODBINDTIME);;
    break;}
case 55:
#line 505 "praserrules.txt"
{myStateManager->AddTypeToState(CT_FALLENVSHAKE);;
    break;}
case 56:
#line 506 "praserrules.txt"
{myStateManager->AddTypeToState(CT_FORCEFEDDBACK);;
    break;}
case 57:
#line 507 "praserrules.txt"
{myStateManager->AddTypeToState(CT_GAMEMAKEANIM);;
    break;}
case 58:
#line 508 "praserrules.txt"
{myStateManager->AddTypeToState(CT_GRAVITY);;
    break;}
case 59:
#line 509 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HELPER);;
    break;}
case 60:
#line 510 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITADD);;
    break;}
case 61:
#line 511 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITBY);;
    break;}
case 62:
#line 512 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITDEF);;
    break;}
case 63:
#line 513 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITFALLDAMAGE);;
    break;}
case 64:
#line 514 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITFALLSET);;
    break;}
case 65:
#line 515 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITFALLVEL);;
    break;}
case 66:
#line 516 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITOVERRIDE);;
    break;}
case 67:
#line 517 "praserrules.txt"
{myStateManager->AddTypeToState(CT_HITVELSET);;
    break;}
case 68:
#line 518 "praserrules.txt"
{myStateManager->AddTypeToState(CT_LIFEADD);;
    break;}
case 69:
#line 519 "praserrules.txt"
{myStateManager->AddTypeToState(CT_LIFESET);;
    break;}
case 70:
#line 520 "praserrules.txt"
{myStateManager->AddTypeToState(CT_MAKEDUST);;
    break;}
case 71:
#line 521 "praserrules.txt"
{myStateManager->AddTypeToState(CT_MODIFYEXPLOD);;
    break;}
case 72:
#line 522 "praserrules.txt"
{myStateManager->AddTypeToState(CT_MOVEHITRESET);;
    break;}
case 73:
#line 523 "praserrules.txt"
{myStateManager->AddTypeToState(CT_NOTHITBY);;
    break;}
case 74:
#line 524 "praserrules.txt"
{myStateManager->AddTypeToState(CT_NUL);;
    break;}
case 75:
#line 525 "praserrules.txt"
{myStateManager->AddTypeToState(CT_OFFSET);;
    break;}
case 76:
#line 526 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PALFX);;
    break;}
case 77:
#line 527 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PARENTVARADD);;
    break;}
case 78:
#line 528 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PARENTVARSET);;
    break;}
case 79:
#line 529 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PAUSE);;
    break;}
case 80:
#line 530 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PLAYERPUSH);;
    break;}
case 81:
#line 531 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PLAYSND);;
    break;}
case 82:
#line 532 "praserrules.txt"
{myStateManager->AddTypeToState(CT_POSADD);;
    break;}
case 83:
#line 533 "praserrules.txt"
{myStateManager->AddTypeToState(CT_POSFREEZ);;
    break;}
case 84:
#line 534 "praserrules.txt"
{myStateManager->AddTypeToState(CT_POSSET);;
    break;}
case 85:
#line 535 "praserrules.txt"
{myStateManager->AddTypeToState(CT_POWERADD);;
    break;}
case 86:
#line 536 "praserrules.txt"
{myStateManager->AddTypeToState(CT_POWERSET);;
    break;}
case 87:
#line 537 "praserrules.txt"
{myStateManager->AddTypeToState(CT_PROJECTILE);;
    break;}
case 88:
#line 538 "praserrules.txt"
{myStateManager->AddTypeToState(CT_REMOVEEXPLOD);;
    break;}
case 89:
#line 539 "praserrules.txt"
{myStateManager->AddTypeToState(CT_REVERSALDEF);;
    break;}
case 90:
#line 540 "praserrules.txt"
{myStateManager->AddTypeToState(CT_SCREENBOUND);;
    break;}
case 91:
#line 541 "praserrules.txt"
{myStateManager->AddTypeToState(CT_SELFSTATE);;
    break;}
case 92:
#line 542 "praserrules.txt"
{myStateManager->AddTypeToState(CT_SNDPAN);;
    break;}
case 93:
#line 543 "praserrules.txt"
{myStateManager->AddTypeToState(CT_SPRPRIORITY);;
    break;}
case 94:
#line 544 "praserrules.txt"
{myStateManager->AddTypeToState(CT_STATETYPESET);;
    break;}
case 95:
#line 545 "praserrules.txt"
{myStateManager->AddTypeToState(CT_STOPSND);;
    break;}
case 96:
#line 546 "praserrules.txt"
{myStateManager->AddTypeToState(CT_SUPERPAUSE);;
    break;}
case 97:
#line 547 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETBIND);;
    break;}
case 98:
#line 548 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETDROP);;
    break;}
case 99:
#line 549 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETFACING);;
    break;}
case 100:
#line 550 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETLIFEADD);;
    break;}
case 101:
#line 551 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETPOWERADD);;
    break;}
case 102:
#line 552 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETSTATE);;
    break;}
case 103:
#line 553 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETVELADD);;
    break;}
case 104:
#line 554 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TARGETVELSET);;
    break;}
case 105:
#line 555 "praserrules.txt"
{myStateManager->AddTypeToState(CT_TURN);;
    break;}
case 106:
#line 556 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VARADD);;
    break;}
case 107:
#line 557 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VARRANDOM);;
    break;}
case 108:
#line 558 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VARRANGESET);;
    break;}
case 109:
#line 559 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VARSET);;
    break;}
case 110:
#line 560 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VELADD);;
    break;}
case 111:
#line 561 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VELMUL);;
    break;}
case 112:
#line 562 "praserrules.txt"
{myStateManager->AddTypeToState(CT_VELSET);;
    break;}
case 113:
#line 563 "praserrules.txt"
{myStateManager->AddTypeToState(CT_WIDTH);;
    break;}
case 114:
#line 567 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->AddTriggerToState((int)yyvsp[-2].nFloat);;
    break;}
case 115:
#line 568 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->AddTriggerToState(192);;
    break;}
case 116:
#line 574 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,yyvsp[-1].nFloat,"#");
                                  myStateManager->AddInstruction(OP_PUSH,yyvsp[0].nFloat,"#");
                                  myStateManager->AddInstruction(OP_JOIN,0,"#");;
    break;}
case 117:
#line 577 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,yyvsp[-2].nFloat,"#");
                                        myStateManager->AddInstruction(OP_PUSH,yyvsp[-1].nFloat,"#");
                                        myStateManager->AddInstruction(OP_PUSH,yyvsp[0].nFloat,"#");
                                        myStateManager->AddInstruction(OP_JOIN,0,"#");;
    break;}
case 118:
#line 581 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,yyvsp[0].nFloat,"#");/*printf("%f\n",$1.nFloat);*/;
    break;}
case 119:
#line 583 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,yyvsp[0].str);;
    break;}
case 120:
#line 584 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");
                                         myStateManager->AddInstruction(OP_PUSH,70,"#");
                                         myStateManager->AddInstruction(OP_PUSH,yyvsp[-2].nFloat,"#");
                                         myStateManager->AddInstruction(OP_GROUP,0,"#");;
    break;}
case 121:
#line 589 "praserrules.txt"
{myStateManager->AddInstruction(OP_ABS,0,"#");;
    break;}
case 122:
#line 590 "praserrules.txt"
{myStateManager->AddInstruction(OP_ACOS,0,"#");;
    break;}
case 123:
#line 591 "praserrules.txt"
{myStateManager->AddInstruction(OP_ALIVE,0,"#");;
    break;}
case 124:
#line 592 "praserrules.txt"
{myStateManager->AddInstruction(OP_ANIM,0,"#");;
    break;}
case 125:
#line 594 "praserrules.txt"
{myStateManager->AddInstruction(OP_ANIMELEM,0,"#");;
    break;}
case 126:
#line 596 "praserrules.txt"
{myStateManager->AddInstruction(OP_ANIMELEMNO,0,"#");;
    break;}
case 127:
#line 597 "praserrules.txt"
{myStateManager->AddInstruction(OP_ANIMELEMTIME,0,"#");;
    break;}
case 128:
#line 598 "praserrules.txt"
{myStateManager->AddInstruction(OP_ANIMEXIST,0,"#");;
    break;}
case 129:
#line 599 "praserrules.txt"
{myStateManager->AddInstruction(OP_ANIMTIME,0,"#");;
    break;}
case 130:
#line 600 "praserrules.txt"
{myStateManager->AddInstruction(OP_ASIN,0,"#");;
    break;}
case 131:
#line 601 "praserrules.txt"
{myStateManager->AddInstruction(OP_ATAN,0,"#");;
    break;}
case 132:
#line 602 "praserrules.txt"
{myStateManager->AddInstruction(OP_AUTHORNAME,0,"#");;
    break;}
case 133:
#line 603 "praserrules.txt"
{myStateManager->AddInstruction(OP_BACKEDGEBODY,0,"#");;
    break;}
case 134:
#line 604 "praserrules.txt"
{myStateManager->AddInstruction(OP_BACKEDGE,0,"#");;
    break;}
case 135:
#line 605 "praserrules.txt"
{myStateManager->AddInstruction(OP_CANRECOVER,0,"#");;
    break;}
case 136:
#line 606 "praserrules.txt"
{myStateManager->AddInstruction(OP_CEIL,0,"#");;
    break;}
case 137:
#line 607 "praserrules.txt"
{myStateManager->AddInstruction(OP_COMMAND,0,"#");;
    break;}
case 138:
#line 608 "praserrules.txt"
{myStateManager->AddInstruction(OP_CONST,0,"#");;
    break;}
case 139:
#line 609 "praserrules.txt"
{myStateManager->AddInstruction(OP_COS,0,"#");;
    break;}
case 140:
#line 610 "praserrules.txt"
{myStateManager->AddInstruction(OP_CTRL,0,"#");;
    break;}
case 141:
#line 611 "praserrules.txt"
{myStateManager->AddInstruction(OP_DRAWGAME,0,"#");;
    break;}
case 142:
#line 612 "praserrules.txt"
{myStateManager->AddInstruction(OP_EXP,0,"#");;
    break;}
case 143:
#line 613 "praserrules.txt"
{myStateManager->AddInstruction(OP_FACING,0,"#");;
    break;}
case 144:
#line 614 "praserrules.txt"
{myStateManager->AddInstruction(OP_FLOOR,0,"#");;
    break;}
case 145:
#line 615 "praserrules.txt"
{myStateManager->AddInstruction(OP_FEBD,0,"#");;
    break;}
case 146:
#line 616 "praserrules.txt"
{myStateManager->AddInstruction(OP_FED,0,"#");;
    break;}
case 147:
#line 617 "praserrules.txt"
{myStateManager->AddInstruction(OP_FVAR,0,"#");;
    break;}
case 148:
#line 618 "praserrules.txt"
{myStateManager->AddInstruction(OP_GAMETIME,0,"#");;
    break;}
case 149:
#line 619 "praserrules.txt"
{myStateManager->AddInstruction(OP_GETHITVAR,0,"#");;
    break;}
case 150:
#line 620 "praserrules.txt"
{myStateManager->AddInstruction(OP_HITCOUNT,0,"#");;
    break;}
case 151:
#line 621 "praserrules.txt"
{;
    break;}
case 152:
#line 622 "praserrules.txt"
{myStateManager->AddInstruction(OP_HITFALL,0,"#");;
    break;}
case 153:
#line 623 "praserrules.txt"
{myStateManager->AddInstruction(OP_HITOVER,0,"#");;
    break;}
case 154:
#line 624 "praserrules.txt"
{myStateManager->AddInstruction(OP_HITPAUSETIME,0,"#");;
    break;}
case 155:
#line 625 "praserrules.txt"
{myStateManager->AddInstruction(OP_HITSHAKEOVER,0,"#");;
    break;}
case 156:
#line 627 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                myStateManager->AddInstruction(OP_HITVAL,0,"#");;
    break;}
case 157:
#line 630 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,2,"#");
                                                myStateManager->AddInstruction(OP_HITVAL,0,"#");;
    break;}
case 158:
#line 632 "praserrules.txt"
{myStateManager->AddInstruction(OP_ID,0,"#");;
    break;}
case 159:
#line 634 "praserrules.txt"
{myStateManager->AddInstruction(OP_IFELSE,0,"#");;
    break;}
case 160:
#line 636 "praserrules.txt"
{myStateManager->AddInstruction(OP_INGUARDDIST,0,"#");;
    break;}
case 161:
#line 637 "praserrules.txt"
{myStateManager->AddInstruction(OP_ISHELPER,0,"#");;
    break;}
case 162:
#line 638 "praserrules.txt"
{myStateManager->AddInstruction(OP_ISHOMETEAM,0,"#");;
    break;}
case 163:
#line 639 "praserrules.txt"
{myStateManager->AddInstruction(OP_LIFE,0,"#");;
    break;}
case 164:
#line 640 "praserrules.txt"
{myStateManager->AddInstruction(OP_LIFEMAX,0,"#");;
    break;}
case 165:
#line 641 "praserrules.txt"
{myStateManager->AddInstruction(OP_LN,0,"#");;
    break;}
case 166:
#line 642 "praserrules.txt"
{myStateManager->AddInstruction(OP_LOG,0,"#");;
    break;}
case 167:
#line 644 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_LOSE,0,"#");;
    break;}
case 168:
#line 647 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,2,"#");
                                                           myStateManager->AddInstruction(OP_LOSE,0,"#");;
    break;}
case 169:
#line 650 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,3,"#");
                                                           myStateManager->AddInstruction(OP_LOSE,0,"#");;
    break;}
case 170:
#line 653 "praserrules.txt"
{myStateManager->AddInstruction(OP_MATCHNO,0,"#");;
    break;}
case 171:
#line 654 "praserrules.txt"
{myStateManager->AddInstruction(OP_MATCHOVER,0,"#");;
    break;}
case 172:
#line 655 "praserrules.txt"
{myStateManager->AddInstruction(OP_MOVECONTACT,0,"#");;
    break;}
case 173:
#line 656 "praserrules.txt"
{myStateManager->AddInstruction(OP_MOVEGUARDED,0,"#");;
    break;}
case 174:
#line 657 "praserrules.txt"
{myStateManager->AddInstruction(OP_MOVEHIT,0,"#");;
    break;}
case 175:
#line 658 "praserrules.txt"
{myStateManager->AddInstruction(OP_MOVETYPE,0,"#");;
    break;}
case 176:
#line 659 "praserrules.txt"
{myStateManager->AddInstruction(OP_MOVEREVERSED,0,"#");;
    break;}
case 177:
#line 660 "praserrules.txt"
{myStateManager->AddInstruction(OP_NAME,0,"#");;
    break;}
case 178:
#line 661 "praserrules.txt"
{myStateManager->AddInstruction(OP_NUMENEMY,0,"#");;
    break;}
case 179:
#line 663 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_NUMEXPLOD,0,"#");;
    break;}
case 180:
#line 666 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_NUMEXPLOD,0,"#");;
    break;}
case 181:
#line 669 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_NUMHELPER,0,"#");;
    break;}
case 182:
#line 672 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_NUMHELPER,0,"#");;
    break;}
case 183:
#line 674 "praserrules.txt"
{myStateManager->AddInstruction(OP_NUMPARTNER,0,"#");;
    break;}
case 184:
#line 675 "praserrules.txt"
{myStateManager->AddInstruction(OP_NUMPROJ,0,"#");;
    break;}
case 185:
#line 676 "praserrules.txt"
{myStateManager->AddInstruction(OP_NUMPROJID,0,"#");;
    break;}
case 186:
#line 678 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_NUMTARGET,1,"#");;
    break;}
case 187:
#line 680 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_NUMTARGET,1,"#");;
    break;}
case 188:
#line 683 "praserrules.txt"
{myStateManager->AddInstruction(OP_NAME,0,"#");;
    break;}
case 189:
#line 685 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_P2BODYDIST,0,"#");;
    break;}
case 190:
#line 688 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_P2BODYDIST,0,"#");;
    break;}
case 191:
#line 691 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_P2DIST,1,"#");;
    break;}
case 192:
#line 694 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
	                                                       myStateManager->AddInstruction(OP_P2DIST,0,"#");;
    break;}
case 193:
#line 696 "praserrules.txt"
{myStateManager->AddInstruction(OP_P2LIFE,0,"#");;
    break;}
case 194:
#line 698 "praserrules.txt"
{myStateManager->AddInstruction(OP_P2MOVETYPE,0,"#");;
    break;}
case 195:
#line 699 "praserrules.txt"
{myStateManager->AddInstruction(OP_P2NAME,0,"#");;
    break;}
case 196:
#line 700 "praserrules.txt"
{myStateManager->AddInstruction(OP_P2STATENO,0,"#");;
    break;}
case 197:
#line 701 "praserrules.txt"
{myStateManager->AddInstruction(OP_P2STATETYPE,0,"#");;
    break;}
case 198:
#line 702 "praserrules.txt"
{myStateManager->AddInstruction(OP_P3NAME,0,"#");;
    break;}
case 199:
#line 703 "praserrules.txt"
{myStateManager->AddInstruction(OP_P4NAME,0,"#");;
    break;}
case 200:
#line 704 "praserrules.txt"
{myStateManager->AddInstruction(OP_PALNO,0,"#");;
    break;}
case 201:
#line 706 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_PARENTDIST,0,"#");;
    break;}
case 202:
#line 708 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_PARENTDIST,0,"#");;
    break;}
case 203:
#line 711 "praserrules.txt"
{myStateManager->AddInstruction(OP_PI,0,"#");;
    break;}
case 204:
#line 712 "praserrules.txt"
{myStateManager->AddInstruction(OP_PLAYERIDEXIST,0,"#");;
    break;}
case 205:
#line 713 "praserrules.txt"
{myStateManager->AddInstruction(OP_PREVSTATENO,0,"#");;
    break;}
case 206:
#line 715 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_POS,0,"#");;
    break;}
case 207:
#line 717 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_POS,0,"#");;
    break;}
case 208:
#line 719 "praserrules.txt"
{myStateManager->AddInstruction(OP_POWER,0,"#");;
    break;}
case 209:
#line 720 "praserrules.txt"
{myStateManager->AddInstruction(OP_POWERMAX,0,"#");;
    break;}
case 210:
#line 721 "praserrules.txt"
{myStateManager->AddInstruction(OP_PROJCANCTIME,0,"#");;
    break;}
case 211:
#line 722 "praserrules.txt"
{myStateManager->AddInstruction(OP_PROJCONTACT,0,"#");;
    break;}
case 212:
#line 723 "praserrules.txt"
{myStateManager->AddInstruction(OP_PROJCONTACTTIME,0,"#");;
    break;}
case 213:
#line 724 "praserrules.txt"
{myStateManager->AddInstruction(OP_PROJGUARDED,0,"#");;
    break;}
case 214:
#line 725 "praserrules.txt"
{myStateManager->AddInstruction(OP_PROJGUARDEDTIME,0,"#");;
    break;}
case 215:
#line 726 "praserrules.txt"
{;
    break;}
case 216:
#line 727 "praserrules.txt"
{;
    break;}
case 217:
#line 728 "praserrules.txt"
{myStateManager->AddInstruction(OP_RANDOM,0,"#");;
    break;}
case 218:
#line 730 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_ROOTDIST,0,"#");;
    break;}
case 219:
#line 733 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_ROOTDIST,0,"#");;
    break;}
case 220:
#line 736 "praserrules.txt"
{myStateManager->AddInstruction(OP_ROUNDNO,0,"#");;
    break;}
case 221:
#line 737 "praserrules.txt"
{myStateManager->AddInstruction(OP_ROUNDSEXISTED,0,"#");;
    break;}
case 222:
#line 738 "praserrules.txt"
{myStateManager->AddInstruction(OP_ROUNDSTATE,0,"#");;
    break;}
case 223:
#line 740 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_SCREENPOS,0,"#");;
    break;}
case 224:
#line 742 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_SCREENPOS,0,"#");;
    break;}
case 225:
#line 745 "praserrules.txt"
{myStateManager->AddInstruction(OP_SELFANIMEXIST,0,"#");;
    break;}
case 226:
#line 746 "praserrules.txt"
{myStateManager->AddInstruction(OP_SIN,0,"#");;
    break;}
case 227:
#line 747 "praserrules.txt"
{myStateManager->AddInstruction(OP_STAGENO,0,"#");;
    break;}
case 228:
#line 748 "praserrules.txt"
{myStateManager->AddInstruction(OP_STATETYPE,0,"#");;
    break;}
case 229:
#line 749 "praserrules.txt"
{myStateManager->AddInstruction(OP_SYSFVAR,0,"#");;
    break;}
case 230:
#line 750 "praserrules.txt"
{myStateManager->AddInstruction(OP_SYSVAR,0,"#");;
    break;}
case 231:
#line 751 "praserrules.txt"
{myStateManager->AddInstruction(OP_TAN,0,"#");;
    break;}
case 232:
#line 752 "praserrules.txt"
{myStateManager->AddInstruction(OP_TEAMMODE,0,"#");;
    break;}
case 233:
#line 753 "praserrules.txt"
{myStateManager->AddInstruction(OP_TEAMSIDE,0,"#");;
    break;}
case 234:
#line 754 "praserrules.txt"
{myStateManager->AddInstruction(OP_TICKSPERSCOND,0,"#");;
    break;}
case 235:
#line 755 "praserrules.txt"
{myStateManager->AddInstruction(OP_TIME,0,"#");;
    break;}
case 236:
#line 756 "praserrules.txt"
{;
    break;}
case 237:
#line 757 "praserrules.txt"
{myStateManager->AddInstruction(OP_UNIQHITCOUNT,0,"#");;
    break;}
case 238:
#line 758 "praserrules.txt"
{myStateManager->AddInstruction(OP_VAR,0,"#");;
    break;}
case 239:
#line 760 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");
                                                           myStateManager->AddInstruction(OP_VEL,0,"#");;
    break;}
case 240:
#line 763 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                                                           myStateManager->AddInstruction(OP_VEL,0,"#");;
    break;}
case 241:
#line 766 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");myStateManager->AddInstruction(OP_WIN,0,"#");
    break;}
case 242:
#line 767 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,2,"#");myStateManager->AddInstruction(OP_WIN,0,"#");
    break;}
case 243:
#line 768 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,3,"#");myStateManager->AddInstruction(OP_WIN,0,"#");
    break;}
case 244:
#line 769 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,4,"#");myStateManager->AddInstruction(OP_WIN,0,"#");
    break;}
case 245:
#line 771 "praserrules.txt"
{myStateManager->AddInstruction(OP_NOT,0,"#");;
    break;}
case 246:
#line 772 "praserrules.txt"
{myStateManager->AddInstruction(OP_AND,0,"#");;
    break;}
case 247:
#line 773 "praserrules.txt"
{myStateManager->AddInstruction(OP_OR,0,"#");;
    break;}
case 248:
#line 774 "praserrules.txt"
{myStateManager->AddInstruction(OP_XOR,0,"#");;
    break;}
case 249:
#line 776 "praserrules.txt"
{myStateManager->AddInstruction(OP_LOGNOT,0,"#");;
    break;}
case 250:
#line 777 "praserrules.txt"
{myStateManager->AddInstruction(OP_LOGAND,0,"#");;
    break;}
case 251:
#line 778 "praserrules.txt"
{myStateManager->AddInstruction(OP_LOGOR,0,"#");;
    break;}
case 252:
#line 779 "praserrules.txt"
{myStateManager->AddInstruction(OP_LOGXOR,0,"#");;
    break;}
case 253:
#line 783 "praserrules.txt"
{myStateManager->AddInstruction(OP_ADD,0,"#");;
    break;}
case 254:
#line 784 "praserrules.txt"
{myStateManager->AddInstruction(OP_SUB,0,"#");;
    break;}
case 255:
#line 785 "praserrules.txt"
{myStateManager->AddInstruction(OP_MUL,0,"#");;
    break;}
case 256:
#line 786 "praserrules.txt"
{myStateManager->AddInstruction(OP_DIV,0,"#");;
    break;}
case 257:
#line 788 "praserrules.txt"
{myStateManager->AddInstruction(OP_SQUARE,0,"#");;
    break;}
case 258:
#line 790 "praserrules.txt"
{myStateManager->AddInstruction(OP_EQUAL,0,"#");/*printf("=\n");*/;
    break;}
case 259:
#line 791 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP1,0,"#");;
    break;}
case 260:
#line 792 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP2,0,"#");;
    break;}
case 261:
#line 793 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP3,0,"#");;
    break;}
case 262:
#line 794 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP4,0,"#");;
    break;}
case 263:
#line 796 "praserrules.txt"
{myStateManager->AddInstruction(OP_NOTEQUAL,0,"#");;
    break;}
case 264:
#line 797 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP5,0,"#");;
    break;}
case 265:
#line 798 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP6,0,"#");;
    break;}
case 266:
#line 799 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP7,0,"#");;
    break;}
case 267:
#line 800 "praserrules.txt"
{myStateManager->AddInstruction(OP_INTERVALOP8,0,"#");;
    break;}
case 268:
#line 802 "praserrules.txt"
{myStateManager->AddInstruction(OP_GREATER,0,"#");;
    break;}
case 269:
#line 803 "praserrules.txt"
{myStateManager->AddInstruction(OP_LESS,0,"#");;
    break;}
case 270:
#line 804 "praserrules.txt"
{myStateManager->AddInstruction(OP_LESSEQUAL,0,"#");;
    break;}
case 271:
#line 805 "praserrules.txt"
{myStateManager->AddInstruction(OP_GRAETEREQUAL,0,"#");;
    break;}
case 272:
#line 807 "praserrules.txt"
{/*expression Add*/;
    break;}
case 273:
#line 809 "praserrules.txt"
{/*expression Add*/;
    break;}
case 274:
#line 812 "praserrules.txt"
{myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_EQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;
    break;}
case 275:
#line 819 "praserrules.txt"
{myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_NOTEQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;
    break;}
case 276:
#line 826 "praserrules.txt"
{myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_GREATER,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;
    break;}
case 277:
#line 833 "praserrules.txt"
{myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_LESS,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;
    break;}
case 278:
#line 840 "praserrules.txt"
{myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_LESSEQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;
    break;}
case 279:
#line 847 "praserrules.txt"
{myStateManager->AddInstruction(OP_SAVE,0,"#");
                                          myStateManager->ExchangeIns();
                                          myStateManager->AddInstruction(OP_GRAETEREQUAL,0,"#");printf("=\n");
                                          myStateManager->AddInstruction(OP_RESTORE,0,"#");
                                          myStateManager->AddInstruction(OP_LOGAND,0,"#");
                                          ;
    break;}
case 280:
#line 854 "praserrules.txt"
{myStateManager->AddInstruction(OP_MOD,0,"#");;
    break;}
case 281:
#line 855 "praserrules.txt"
{yyval.nFloat=-yyvsp[0].nFloat;myStateManager->AddInstruction(OP_NEG,0,"#");;
    break;}
case 282:
#line 859 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");;
    break;}
case 283:
#line 860 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");;
    break;}
case 284:
#line 861 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,2,"#");;
    break;}
case 285:
#line 862 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,3,"#");;
    break;}
case 286:
#line 863 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,4,"#");;
    break;}
case 287:
#line 864 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,5,"#");;
    break;}
case 288:
#line 865 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,6,"#");;
    break;}
case 289:
#line 866 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,7,"#");;
    break;}
case 290:
#line 867 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,8,"#");;
    break;}
case 291:
#line 868 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,9,"#");;
    break;}
case 292:
#line 869 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,10,"#");;
    break;}
case 293:
#line 870 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,11,"#");;
    break;}
case 294:
#line 871 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,12,"#");;
    break;}
case 295:
#line 872 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,13,"#");;
    break;}
case 296:
#line 873 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,14,"#");;
    break;}
case 297:
#line 874 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,15,"#");;
    break;}
case 298:
#line 875 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,16,"#");;
    break;}
case 299:
#line 876 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,17,"#");;
    break;}
case 300:
#line 877 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,18,"#");;
    break;}
case 301:
#line 878 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,19,"#");;
    break;}
case 302:
#line 879 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,20,"#");;
    break;}
case 303:
#line 880 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,21,"#");;
    break;}
case 304:
#line 881 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,22,"#");;
    break;}
case 305:
#line 882 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,23,"#");;
    break;}
case 306:
#line 883 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,24,"#");;
    break;}
case 307:
#line 884 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,25,"#");;
    break;}
case 308:
#line 885 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,26,"#");;
    break;}
case 309:
#line 886 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,27,"#");;
    break;}
case 310:
#line 887 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,28,"#");;
    break;}
case 311:
#line 888 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,29,"#");;
    break;}
case 312:
#line 889 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,30,"#");;
    break;}
case 313:
#line 890 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,31,"#");;
    break;}
case 314:
#line 891 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,32,"#");;
    break;}
case 315:
#line 892 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,33,"#");;
    break;}
case 316:
#line 893 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,34,"#");;
    break;}
case 317:
#line 894 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,35,"#");;
    break;}
case 318:
#line 895 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,36,"#");;
    break;}
case 319:
#line 896 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,37,"#");;
    break;}
case 320:
#line 897 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,38,"#");;
    break;}
case 321:
#line 898 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,39,"#");;
    break;}
case 322:
#line 899 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,40,"#");;
    break;}
case 323:
#line 900 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,41,"#");;
    break;}
case 324:
#line 901 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,42,"#");;
    break;}
case 325:
#line 902 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,43,"#");;
    break;}
case 326:
#line 903 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,44,"#");;
    break;}
case 327:
#line 904 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,45,"#");;
    break;}
case 328:
#line 905 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,46,"#");;
    break;}
case 329:
#line 906 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,47,"#");;
    break;}
case 330:
#line 909 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_VALUE);;
    break;}
case 331:
#line 910 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_VALUE2);;
    break;}
case 332:
#line 911 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_XVALUE);;
    break;}
case 333:
#line 912 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_YVALUE);;
    break;}
case 334:
#line 913 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_ZVALUE);;
    break;}
case 335:
#line 914 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_SYSVAR);;
    break;}
case 336:
#line 915 "praserrules.txt"
{myStateManager->AddPersistanceToState((int)yyvsp[0].nFloat);;
    break;}
case 337:
#line 916 "praserrules.txt"
{myStateManager->AddIgnoreHitPauseToState((int)yyvsp[0].nFloat);;
    break;}
case 338:
#line 917 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_POS);;
    break;}
case 339:
#line 918 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_SPACING);;
    break;}
case 340:
#line 919 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_STATETYPE);;
    break;}
case 341:
#line 920 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_MOVETYPE);;
    break;}
case 342:
#line 921 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_PHYSICS);;
    break;}
case 343:
#line 922 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_WAVEFORM);;
    break;}
case 344:
#line 923 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_TIME);;
    break;}
case 345:
#line 924 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_AMPL);;
    break;}
case 346:
#line 925 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_FREQ);;
    break;}
case 347:
#line 926 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_FVALUE);;
    break;}
case 348:
#line 927 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_ADD);;
    break;}
case 349:
#line 928 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_MUL);;
    break;}
case 350:
#line 929 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_SINADD);;
    break;}
case 351:
#line 930 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_COLOR);;
    break;}
case 352:
#line 931 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_INTERVALL);;
    break;}
case 353:
#line 932 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_UNDER);;
    break;}
case 354:
#line 933 "praserrules.txt"
{myStateManager->AddInstruction(OP_STOP,0,"#");myStateManager->SetParam(PA_RANDOM);;
    break;}
case 355:
#line 938 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");;
    break;}
case 356:
#line 939 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,1,"#");;
    break;}
case 357:
#line 940 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,2,"#");;
    break;}
case 358:
#line 941 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,3,"#");;
    break;}
case 359:
#line 942 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,4,"#");;
    break;}
case 360:
#line 943 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,5,"#");;
    break;}
case 361:
#line 944 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,6,"#");;
    break;}
case 362:
#line 945 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,7,"#");;
    break;}
case 363:
#line 946 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,8,"#");;
    break;}
case 364:
#line 947 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,9,"#");;
    break;}
case 365:
#line 948 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,10,"#");;
    break;}
case 366:
#line 949 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,11,"#");;
    break;}
case 367:
#line 950 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,12,"#");;
    break;}
case 368:
#line 951 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,13,"#");;
    break;}
case 369:
#line 952 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,14,"#");;
    break;}
case 370:
#line 953 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,15,"#");;
    break;}
case 371:
#line 954 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,16,"#");;
    break;}
case 372:
#line 955 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,17,"#");;
    break;}
case 373:
#line 956 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,18,"#");;
    break;}
case 374:
#line 957 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,19,"#");;
    break;}
case 375:
#line 958 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,20,"#");;
    break;}
case 376:
#line 959 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,21,"#");;
    break;}
case 377:
#line 960 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,22,"#");;
    break;}
case 378:
#line 961 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,23,"#");;
    break;}
case 379:
#line 962 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,24,"#");;
    break;}
case 380:
#line 963 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,25,"#");;
    break;}
case 381:
#line 964 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,26,"#");;
    break;}
case 382:
#line 965 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,27,"#");;
    break;}
case 383:
#line 966 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,28,"#");;
    break;}
case 384:
#line 967 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,29,"#");;
    break;}
case 385:
#line 968 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,30,"#");;
    break;}
case 386:
#line 969 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,31,"#");;
    break;}
case 387:
#line 970 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,32,"#");;
    break;}
case 388:
#line 971 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,33,"#");;
    break;}
case 389:
#line 972 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,34,"#");;
    break;}
case 390:
#line 973 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,35,"#");;
    break;}
case 391:
#line 977 "praserrules.txt"
{myStateManager->AddInstruction(OP_PUSH,0,"#");
                  myStateManager->AddInstruction(OP_JOIN,0,"#");;
    break;}
case 392:
#line 979 "praserrules.txt"
{;
    break;}
case 393:
#line 980 "praserrules.txt"
{;
    break;}
case 394:
#line 981 "praserrules.txt"
{;
    break;}
case 395:
#line 982 "praserrules.txt"
{;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      printf ("state stack now");
      while (ssp1 != yyssp)
      {
	      fprintf (stderr, " %d", *++ssp1);
	      printf (" %d", *++ssp1);
	  }   
      fprintf (stderr, "\n");
      printf ("\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
	printf("Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      printf ("Error: state stack now");
      while (ssp1 != yyssp)
      {
	      fprintf (stderr, " %d", *++ssp1);
	      printf (" %d", *++ssp1);	  
   	  }
      fprintf (stderr, "\n");
      printf ("\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
    printf("Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 984 "praserrules.txt"

