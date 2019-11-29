
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
#line 1 "lrparser.y"

  #include"ast.h"
  //int yydebug=1;
  extern struct AST *astRoot;


/* Line 189 of yacc.c  */
#line 80 "lrparser.tab.c"

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
     NUMBER = 258,
     WHILE = 259,
     STRING = 260,
     ID = 261,
     INT = 262,
     STR = 263,
     VOID = 264,
     IF = 265,
     ELSE = 266,
     RETURN = 267,
     PRINT = 268,
     SCAN = 269,
     CMP = 270,
     ASSIGN = 271,
     EOP = 272
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 7 "lrparser.y"

  struct AST *ast_node;
  char *save_yytext;



/* Line 214 of yacc.c  */
#line 140 "lrparser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 152 "lrparser.tab.c"

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   173

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNRULES -- Number of states.  */
#define YYNSTATES  135

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   272

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    31,     2,     2,
      23,    24,    29,    27,    19,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    18,
       2,    20,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,    22,     2,     2,     2,     2,
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
      15,    16,    17
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    19,    23,
      25,    29,    31,    35,    41,    43,    47,    49,    51,    53,
      55,    60,    64,    69,    73,    75,    79,    82,    84,    86,
      88,    90,    92,    94,    96,    98,   100,   102,   104,   107,
     111,   113,   115,   117,   120,   122,   125,   131,   139,   145,
     148,   152,   155,   159,   163,   165,   167,   171,   175,   182,
     184,   188,   190,   194,   198,   200,   204,   208,   212,   215,
     220,   224,   228,   230,   232,   237,   239,   243,   245
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    33,    34,    -1,    33,    17,
      -1,    35,    -1,    36,    -1,    45,     6,    47,    -1,    45,
      37,    18,    -1,    38,    -1,    37,    19,    38,    -1,    41,
      -1,    41,    20,    60,    -1,    41,    20,    21,    39,    22,
      -1,    40,    -1,    39,    19,    40,    -1,     3,    -1,     5,
      -1,    42,    -1,     6,    -1,    42,    23,    43,    24,    -1,
      42,    23,    24,    -1,     6,    25,    57,    26,    -1,     6,
      25,    26,    -1,    44,    -1,    43,    19,    44,    -1,    45,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    47,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    36,    -1,    48,    49,    -1,    48,    50,    49,
      -1,    21,    -1,    22,    -1,    46,    -1,    50,    46,    -1,
      18,    -1,    57,    18,    -1,    10,    23,    57,    24,    46,
      -1,    10,    23,    57,    24,    46,    11,    46,    -1,     4,
      23,    57,    24,    46,    -1,    12,    18,    -1,    12,    57,
      18,    -1,    13,    18,    -1,    13,    63,    18,    -1,    14,
      64,    18,    -1,    58,    -1,    59,    -1,     6,    16,    58,
      -1,     6,    20,    58,    -1,     6,    25,    57,    26,    20,
      58,    -1,    60,    -1,    59,    15,    60,    -1,    61,    -1,
      60,    27,    61,    -1,    60,    28,    61,    -1,    62,    -1,
      61,    29,    62,    -1,    61,    30,    62,    -1,    61,    31,
      62,    -1,    28,    62,    -1,     6,    23,    63,    24,    -1,
       6,    23,    24,    -1,    23,    57,    24,    -1,     6,    -1,
      40,    -1,     6,    25,    57,    26,    -1,    57,    -1,    63,
      19,    57,    -1,     6,    -1,    64,    19,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    34,    34,    35,    36,    38,    39,    41,    43,    45,
      46,    48,    49,    50,    52,    53,    55,    56,    58,    60,
      61,    62,    63,    64,    66,    67,    69,    71,    72,    73,
      75,    76,    77,    78,    79,    80,    81,    82,    84,    85,
      87,    89,    91,    92,    94,    95,    97,    98,   100,   102,
     103,   105,   106,   108,   110,   112,   113,   114,   115,   117,
     118,   120,   121,   122,   124,   125,   126,   127,   128,   130,
     131,   132,   133,   134,   135,   137,   138,   140,   141
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "WHILE", "STRING", "ID", "INT",
  "STR", "VOID", "IF", "ELSE", "RETURN", "PRINT", "SCAN", "CMP", "ASSIGN",
  "EOP", "';'", "','", "'='", "'{'", "'}'", "'('", "')'", "'['", "']'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "$accept", "program",
  "external_declaration", "function_definition", "declaration",
  "init_declarator_list", "init_declarator", "intstr_list", "initializer",
  "declarator", "direct_declarator", "parameter_list", "parameter", "type",
  "statement", "compound_statement", "begin_scope", "end_scope",
  "statement_list", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "print_statement",
  "scan_statement", "expr", "assign_expr", "cmp_expr", "add_expr",
  "mul_expr", "primary_expr", "expr_list", "id_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    59,    44,
      61,   123,   125,    40,    41,    91,    93,    43,    45,    42,
      47,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    33,    34,    34,    35,    36,    37,
      37,    38,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    42,    42,    42,    43,    43,    44,    45,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    47,    47,
      48,    49,    50,    50,    51,    51,    52,    52,    53,    54,
      54,    55,    55,    56,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    60,    61,    61,    61,    61,    61,    62,
      62,    62,    62,    62,    62,    63,    63,    64,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     3,     3,     1,
       3,     1,     3,     5,     1,     3,     1,     1,     1,     1,
       4,     3,     4,     3,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     1,     1,     2,     1,     2,     5,     7,     5,     2,
       3,     2,     3,     3,     1,     1,     3,     3,     6,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     2,     4,
       3,     3,     1,     1,     4,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    27,    28,    29,     0,     2,     5,     6,     0,     1,
       4,     3,    19,     0,     9,    11,    18,    40,     0,     7,
       0,     8,     0,     0,     0,    16,    17,    72,     0,    23,
       0,    73,     0,    54,    55,    59,    61,    64,     0,     0,
       0,     0,     0,    44,    41,    37,     0,    42,    30,    38,
       0,    31,    32,    33,    34,    35,    36,     0,    19,    10,
      72,     0,    12,    21,     0,    24,     0,     0,     0,     0,
       0,     0,    68,    22,     0,     0,     0,     0,     0,     0,
       0,     0,    49,     0,    51,    75,     0,    77,     0,    43,
      39,    45,     0,     0,    14,     0,    20,    26,    56,    57,
      70,     0,     0,    71,    60,    62,    63,    65,    66,    67,
       0,     0,    50,    52,     0,    53,     0,     0,     0,    13,
      25,    69,    74,     0,     0,    76,    78,    74,    15,     0,
      48,    46,    58,     0,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    45,    13,    14,    93,    31,    15,
      16,    64,    65,    46,    47,    48,    20,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    33,    34,    35,    36,
      37,    86,    88
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -64
static const yytype_int16 yypact[] =
{
     147,   -64,   -64,   -64,    75,   -64,   -64,   -64,     7,   -64,
     -64,   -64,    -1,    31,   -64,     1,    17,   -64,    62,   -64,
      25,   -64,    38,    66,    71,   -64,   -64,   125,    13,   -64,
     137,   -64,    44,   -64,    42,    33,   132,   -64,    41,    50,
     109,   116,   100,   -64,   -64,   -64,    38,   -64,   -64,   -64,
      25,   -64,   -64,   -64,   -64,   -64,   -64,    63,   113,   -64,
      68,    22,    33,   -64,   -10,   -64,   111,    13,    13,   123,
      13,    96,   -64,   -64,   130,   130,   130,   137,   137,   137,
      13,    13,   -64,   131,   -64,   -64,    92,   -64,   106,   -64,
     -64,   -64,    13,    23,   -64,   147,   -64,   -64,   -64,   -64,
     -64,    -7,   126,   -64,    33,   132,   132,   -64,   -64,   -64,
     133,   135,   -64,   -64,    13,   -64,   158,   139,    22,   -64,
     -64,   -64,   146,    95,    95,   -64,   -64,   -64,   -64,    13,
     -64,   156,   -64,    95,   -64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -64,   -64,   164,   -64,    11,   -64,   148,   -64,   -60,   -64,
     -64,   -64,    74,     2,   -47,   159,   -64,   122,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -18,   -63,   -64,   -15,    55,
     -23,   104,   -64
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      32,    94,     8,    89,    98,    99,     8,    72,    62,    95,
      71,     7,   114,    12,    96,     7,    25,   121,    26,    27,
      17,    23,    83,    85,    18,    25,    66,    26,    25,    38,
      26,    27,     1,     2,     3,    39,    28,    40,    41,    42,
      24,    30,   118,    43,    58,   119,    17,    44,    28,    21,
      22,    85,   102,    30,   107,   108,   109,    74,   128,   104,
      75,    76,   110,   111,    80,    25,   132,    26,    27,    25,
      73,    26,    60,    81,   117,     9,   130,   131,     1,     2,
       3,    91,     1,     2,     3,    28,   134,    61,    29,    28,
      30,    69,    10,    92,    30,    63,   125,    66,    25,    38,
      26,    27,     1,     2,     3,    39,    87,    40,    41,    42,
     113,   114,    25,    43,    26,    27,    17,    97,    28,    25,
     103,    26,    27,    30,   115,   116,    25,    82,    26,    27,
     105,   106,    28,    25,    84,    26,    60,    30,    18,    28,
      25,    67,    26,    60,    30,    68,    28,   100,    69,   112,
      70,    30,   122,    28,     1,     2,     3,   123,    30,   124,
      28,    77,    78,    79,   126,   127,   129,   133,    11,   120,
      59,    19,    90,   101
};

static const yytype_uint8 yycheck[] =
{
      18,    61,     0,    50,    67,    68,     4,    30,    23,    19,
      28,     0,    19,     6,    24,     4,     3,    24,     5,     6,
      21,    20,    40,    41,    25,     3,    24,     5,     3,     4,
       5,     6,     7,     8,     9,    10,    23,    12,    13,    14,
      23,    28,    19,    18,     6,    22,    21,    22,    23,    18,
      19,    69,    70,    28,    77,    78,    79,    15,   118,    74,
      27,    28,    80,    81,    23,     3,   129,     5,     6,     3,
      26,     5,     6,    23,    92,     0,   123,   124,     7,     8,
       9,    18,     7,     8,     9,    23,   133,    21,    26,    23,
      28,    23,    17,    25,    28,    24,   114,    95,     3,     4,
       5,     6,     7,     8,     9,    10,     6,    12,    13,    14,
      18,    19,     3,    18,     5,     6,    21,     6,    23,     3,
      24,     5,     6,    28,    18,    19,     3,    18,     5,     6,
      75,    76,    23,     3,    18,     5,     6,    28,    25,    23,
       3,    16,     5,     6,    28,    20,    23,    24,    23,    18,
      25,    28,    26,    23,     7,     8,     9,    24,    28,    24,
      23,    29,    30,    31,     6,    26,    20,    11,     4,    95,
      22,    12,    50,    69
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    33,    34,    35,    36,    45,     0,
      17,    34,     6,    37,    38,    41,    42,    21,    25,    47,
      48,    18,    19,    20,    23,     3,     5,     6,    23,    26,
      28,    40,    57,    58,    59,    60,    61,    62,     4,    10,
      12,    13,    14,    18,    22,    36,    45,    46,    47,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     6,    38,
       6,    21,    60,    24,    43,    44,    45,    16,    20,    23,
      25,    57,    62,    26,    15,    27,    28,    29,    30,    31,
      23,    23,    18,    57,    18,    57,    63,     6,    64,    46,
      49,    18,    25,    39,    40,    19,    24,     6,    58,    58,
      24,    63,    57,    24,    60,    61,    61,    62,    62,    62,
      57,    57,    18,    18,    19,    18,    19,    57,    19,    22,
      44,    24,    26,    24,    24,    57,     6,    26,    40,    20,
      46,    46,    58,    11,    46
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
        case 2:

/* Line 1455 of yacc.c  */
#line 34 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 35 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (2)].ast_node),(yyvsp[(2) - (2)].ast_node));;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 36 "lrparser.y"
    {astRoot = (yyvsp[(1) - (2)].ast_node);return 1;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 38 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 39 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 41 "lrparser.y"
    {(yyval.ast_node) = newAstNode("FunctionDef",strdup((yyvsp[(2) - (3)].save_yytext)),0,(yyvsp[(3) - (3)].ast_node),newAstNode("ReturnType",strdup((yyvsp[(1) - (3)].char *)),0,NULL,NULL));;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 43 "lrparser.y"
    {(yyval.ast_node) = newAstNode("VariableDec",strdup((yyvsp[(1) - (3)].char *)),0,(yyvsp[(2) - (3)].ast_node),NULL);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 45 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 46 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 48 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 49 "lrparser.y"
    {(yyval.ast_node) = newAstNode("VariableInit",NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 50 "lrparser.y"
    {(yyval.ast_node) = newAstNode("ListInit",NULL,0,(yyvsp[(1) - (5)].ast_node),(yyvsp[(4) - (5)].ast_node));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 52 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 53 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 55 "lrparser.y"
    {(yyval.ast_node) = newAstNode("Number",NULL,atof((yyvsp[(1) - (1)].save_yytext)),NULL,NULL);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 56 "lrparser.y"
    {(yyval.ast_node) = newAstNode("String",strdup((yyvsp[(1) - (1)].save_yytext)),0,NULL,NULL);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 58 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 60 "lrparser.y"
    {(yyval.ast_node) = newAstNode("VariableName",strdup((yyvsp[(1) - (1)].save_yytext)),0,NULL,NULL);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 61 "lrparser.y"
    {(yyval.ast_node) = newAstNode("FunctionDec",NULL,0,(yyvsp[(1) - (4)].ast_node),(yyvsp[(3) - (4)].ast_node));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 62 "lrparser.y"
    {(yyval.ast_node) = newAstNode("FunctionDec",NULL,0,(yyvsp[(1) - (3)].ast_node),NULL);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 63 "lrparser.y"
    {(yyval.ast_node) = newAstNode("ListDec",strdup((yyvsp[(1) - (4)].save_yytext)),0,(yyvsp[(3) - (4)].ast_node),NULL);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 64 "lrparser.y"
    {(yyval.ast_node) = newAstNode("ListDec",strdup((yyvsp[(1) - (3)].save_yytext)),0,NULL,NULL);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 66 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 67 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 69 "lrparser.y"
    {(yyval.ast_node) = newAstNode((yyvsp[(1) - (2)].char *),strdup((yyvsp[(2) - (2)].save_yytext)),0,NULL,NULL);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 71 "lrparser.y"
    {(yyval.char *) = "INT";;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 72 "lrparser.y"
    {(yyval.char *) = "STR";;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 73 "lrparser.y"
    {(yyval.char *) = "VOID";;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 75 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 76 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 77 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 78 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 79 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 80 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 81 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 82 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 84 "lrparser.y"
    {(yyval.ast_node) = NULL;;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 85 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 87 "lrparser.y"
    {(yyval.int) = '{';;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 89 "lrparser.y"
    {(yyval.int) = '}';;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 91 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 92 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (2)].ast_node),(yyvsp[(2) - (2)].ast_node));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 94 "lrparser.y"
    {(yyval.ast_node)=NULL;;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 95 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 97 "lrparser.y"
    {(yyval.ast_node) = newIfNode("IF_Stmt",(yyvsp[(3) - (5)].ast_node),(yyvsp[(5) - (5)].ast_node),NULL);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 98 "lrparser.y"
    {(yyval.ast_node) = newIfNode("IF_Stmt",(yyvsp[(3) - (7)].ast_node),(yyvsp[(5) - (7)].ast_node),(yyvsp[(7) - (7)].ast_node));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 100 "lrparser.y"
    {(yyval.ast_node) = newAstNode("WhileStmt",NULL,0,(yyvsp[(3) - (5)].ast_node),(yyvsp[(5) - (5)].ast_node));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 102 "lrparser.y"
    {(yyval.ast_node) = NULL;;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 103 "lrparser.y"
    {(yyval.ast_node) = newAstNode("ReturnStmt",NULL,0,(yyvsp[(2) - (3)].ast_node),NULL);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 105 "lrparser.y"
    {(yyval.ast_node) = NULL;;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 106 "lrparser.y"
    {(yyval.ast_node) = newAstNode("PrintStmt",NULL,0,(yyvsp[(2) - (3)].ast_node),NULL);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 108 "lrparser.y"
    {(yyval.ast_node) = newAstNode("ScanStmt",NULL,0,(yyvsp[(2) - (3)].ast_node),NULL);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 110 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 112 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 113 "lrparser.y"
    {(yyval.ast_node) = newAstNode(strdup((yyvsp[(2) - (3)].save_yytext)),strdup((yyvsp[(1) - (3)].save_yytext)),0,(yyvsp[(3) - (3)].ast_node),NULL);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 114 "lrparser.y"
    {(yyval.ast_node) = newAstNode("=","strdup($1)",0,(yyvsp[(3) - (3)].ast_node),NULL);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 115 "lrparser.y"
    {(yyval.ast_node) = newAstNode("=",strdup((yyvsp[(1) - (6)].save_yytext)),0,(yyvsp[(3) - (6)].ast_node),(yyvsp[(6) - (6)].ast_node));;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 117 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 118 "lrparser.y"
    {(yyval.ast_node) = newAstNode(strdup((yyvsp[(2) - (3)].save_yytext)),NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 120 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 121 "lrparser.y"
    {(yyval.ast_node) = newAstNode("+",NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 122 "lrparser.y"
    {(yyval.ast_node) = newAstNode("-",NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 124 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 125 "lrparser.y"
    {(yyval.ast_node) = newAstNode("*",NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 126 "lrparser.y"
    {(yyval.ast_node) = newAstNode("/",NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 127 "lrparser.y"
    {(yyval.ast_node) = newAstNode("%",NULL,0,(yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 128 "lrparser.y"
    {(yyval.ast_node) = newAstNode("-","Minus",0,(yyvsp[(2) - (2)].ast_node),NULL);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 130 "lrparser.y"
    {(yyval.ast_node) = newAstNode("FunctionRef",strdup((yyvsp[(1) - (4)].save_yytext)),0,(yyvsp[(3) - (4)].ast_node),NULL);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 131 "lrparser.y"
    {(yyval.ast_node) = newAstNode("FunctionRef",strdup((yyvsp[(1) - (3)].save_yytext)),0,NULL,NULL);;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 132 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 133 "lrparser.y"
    {(yyval.ast_node) = newAstNode("VariableRef",strdup((yyvsp[(1) - (1)].save_yytext)),0,NULL,NULL);;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 134 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 135 "lrparser.y"
    {(yyval.ast_node) = newAstNode("ListRef",strdup((yyvsp[(1) - (4)].save_yytext)),0,(yyvsp[(3) - (4)].ast_node),NULL);;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 137 "lrparser.y"
    {(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 138 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].ast_node));;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 140 "lrparser.y"
    {(yyval.ast_node) = newAstNode("VariableName",strdup((yyvsp[(1) - (1)].save_yytext)),0,NULL,NULL);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 141 "lrparser.y"
    {(yyval.ast_node) = newListNode((yyvsp[(1) - (3)].ast_node),(yyvsp[(3) - (3)].save_yytext));;}
    break;



/* Line 1455 of yacc.c  */
#line 2014 "lrparser.tab.c"
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
#line 143 "lrparser.y"

