/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "src/parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.y" /* yacc.c:355  */

	#include "topLevel.h"
	#include <string>

	//matched below context-free grammar
	 extern const Node *g_root;
	 extern FILE *yyin; // Lexer input file

	int yylex(void);
  	void yyerror(const char *);

#line 109 "src/parser.tab.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    CONSTANT = 259,
    STRING_LITERAL = 260,
    SIZEOF = 261,
    PTR_OP = 262,
    INC_OP = 263,
    DEC_OP = 264,
    LEFT_OP = 265,
    RIGHT_OP = 266,
    LE_OP = 267,
    GE_OP = 268,
    EQ_OP = 269,
    NE_OP = 270,
    AND_OP = 271,
    OR_OP = 272,
    ASSIGN = 273,
    TYPE_NAME = 274,
    TYPEDEF = 275,
    STATIC = 276,
    CHAR = 277,
    SHORT = 278,
    INT = 279,
    LONG = 280,
    SIGNED = 281,
    UNSIGNED = 282,
    FLOAT = 283,
    DOUBLE = 284,
    CONST = 285,
    VOID = 286,
    CASE = 287,
    DEFAULT = 288,
    IF = 289,
    ELSE = 290,
    SWITCH = 291,
    WHILE = 292,
    DO = 293,
    FOR = 294,
    GOTO = 295,
    CONTINUE = 296,
    BREAK = 297,
    RETURN = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "src/parser.y" /* yacc.c:355  */

	std::string * str;
	double num;

	List * listPtr; // not const to allow adding items
	ParameterList * paramListPtr;
	InitDeclaratorList * initDeclaratorListPtr;

	const Node * nodePtr;
	const Declarator* declaratorPtr;
	InitDeclarator * initDeclaratorPtr; // not const since type is set later
	const ParameterDeclaration * paramDeclPtr;
	//const Identifier * identifierPtr;

#line 180 "src/parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 197 "src/parser.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   492

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,     2,     2,    56,    49,     2,
      45,    44,    50,    51,    48,    52,     2,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    65,    62,
      57,    61,    58,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,    60,    64,    53,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,    95,    97,   101,   102,   103,   104,   107,
     108,   112,   113,   117,   118,   119,   120,   126,   127,   128,
     129,   130,   131,   135,   140,   141,   142,   143,   147,   148,
     149,   153,   154,   155,   159,   160,   161,   162,   163,   167,
     168,   169,   173,   174,   178,   179,   183,   184,   188,   189,
     193,   194,   199,   204,   205,   209,   213,   220,   225,   302,
     303,   307,   308,   314,   315,   318,   320,   325,   337,   341,
     344,   357,   361,   362,   366,   368,   372,   373,   382,   383,
     384,   385,   391,   392,   398,   399,   400,   407,   408,   409,
     410,   418,   419,   420,   421,   427,   428,   432,   433,   434,
     435,   436,   437,   441,   442,   451,   459,   460,   464,   465,
     468
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "ASSIGN", "TYPE_NAME", "TYPEDEF", "STATIC", "CHAR", "SHORT", "INT",
  "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOID", "CASE",
  "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "')'", "'('", "'['", "']'", "','", "'&'",
  "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'",
  "'|'", "'='", "';'", "'{'", "'}'", "':'", "$accept", "unary_operator",
  "argument_expression_list", "primary_expression", "postfix_expression",
  "unary_expression", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "expression", "constant_expression",
  "initializer", "parameter_list", "declarator", "direct_declarator",
  "declaration_list", "init_declarator_list", "init_declarator",
  "declaration_specifiers", "parameter_declaration", "declaration",
  "selection_statement", "statement_list", "labeled_statement",
  "compound_statement", "expression_statement", "iteration_statement",
  "jump_statement", "statement", "function_definition",
  "external_declaration", "translation_unit", "type_specifier", "root", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    41,    40,    91,    93,    44,    38,
      42,    43,    45,   126,    33,    47,    37,    60,    62,    94,
     124,    61,    59,   123,   125,    58
};
# endif

#define YYPACT_NINF -114

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,  -114,  -114,     7,  -114,  -114,  -114,    -4,  -114,    14,
    -114,     7,   -33,    13,   -36,  -114,  -114,  -114,   -15,   398,
     169,  -114,   -13,     7,  -114,  -114,  -114,  -114,   398,   398,
     398,  -114,  -114,  -114,  -114,  -114,  -114,   398,  -114,    25,
       3,  -114,   -31,    -5,    12,     4,    24,   -17,     1,     6,
      59,    46,  -114,  -114,  -114,   398,     8,    37,    38,    42,
     429,    43,    31,    33,    47,  -114,  -114,  -114,    40,   221,
       7,  -114,  -114,   273,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,    -8,     7,  -114,    44,  -114,  -114,  -114,    60,  -114,
    -114,  -114,  -114,   294,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,  -114,    41,   429,   398,   398,
     398,    70,   134,  -114,  -114,  -114,    48,  -114,  -114,  -114,
     325,  -114,  -114,  -114,    -4,  -114,  -114,  -114,    -7,  -114,
      61,  -114,  -114,  -114,  -114,  -114,   -31,   -31,    -5,    -5,
      12,    12,    12,    12,     4,     4,    24,   -17,     1,     6,
      59,   429,  -114,    67,    69,    71,    75,   134,  -114,  -114,
    -114,  -114,   398,  -114,  -114,   429,    51,   429,   398,   346,
    -114,    86,   429,  -114,    78,   429,    79,   429,   377,    62,
    -114,   429,  -114,  -114,  -114,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    70,    69,     0,   107,   106,   108,   110,    68,     0,
      63,     0,    59,    67,     0,    61,   109,     1,     0,     0,
       0,   105,     0,     0,    71,    64,     2,     3,     0,     0,
       0,    17,    18,    19,    20,    21,    22,     0,     5,    13,
      23,    24,    28,    31,    34,    39,    42,    44,    46,    48,
      50,    52,    53,    58,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    78,    56,     0,     0,
       0,    72,   100,     0,    97,    98,    99,   101,   102,   103,
      66,     0,    75,    76,    59,    62,    14,    15,     0,    23,
      16,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,     0,
       0,     0,     0,    91,    92,    93,     0,    83,    80,    73,
       0,    79,   104,    65,     0,    74,     4,     7,     0,    11,
       0,    55,    54,    25,    26,    27,    29,    30,    32,    33,
      37,    38,    35,    36,    40,    41,    43,    45,    47,    49,
      51,     0,    96,     0,     0,     0,     0,     0,    94,    81,
      77,     8,     0,     6,    95,     0,     0,     0,     0,     0,
      12,    84,     0,    87,     0,     0,     0,     0,     0,     0,
      89,     0,    85,    86,    88,    90
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,  -114,  -114,    57,   -30,   -52,   -24,   -62,
     -28,    15,    17,    19,    21,    18,  -114,    80,   -19,   -29,
    -114,  -114,  -114,     2,  -114,  -114,  -114,   103,   -16,     5,
     -12,  -114,   -66,  -114,   124,  -113,  -114,  -114,   -58,  -114,
     133,  -114,  -114,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    37,   138,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    67,    68,
     116,    54,    81,    84,    13,    69,    14,    15,     3,    83,
       4,    72,    73,    74,    75,    76,    77,    78,    79,     5,
       6,     7,     8,     9
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    88,   121,   130,    70,    12,    82,    90,    71,   167,
      10,     1,    23,    18,    17,   132,   104,   105,     2,    97,
       1,    95,   102,   103,    98,    99,    24,     2,    19,    25,
      20,    80,   110,    91,    92,   126,   133,   171,   108,   109,
     134,   172,   150,   151,   152,   153,   100,   101,   146,   147,
      26,    27,    11,    70,   179,    28,    29,   129,    22,   162,
     111,   106,   107,   114,    96,   140,   112,   143,   144,   145,
      93,    94,   132,   117,   139,   113,   141,   142,   148,   149,
     154,   155,   118,   119,   135,    86,    87,   120,   122,   163,
     164,   165,    30,   123,    89,   124,    31,    32,    33,    34,
      35,    36,   127,   174,   136,    19,   161,   166,   173,   125,
     168,   175,    89,   176,   182,   177,   188,   181,    82,   183,
     178,   187,   189,   191,   194,   156,    85,   190,   157,   192,
     132,   158,   160,   195,   159,   115,    21,    26,    27,   170,
      16,     0,    28,    29,     0,     0,     0,     0,     0,   184,
     186,     0,     0,   180,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    26,    27,     0,     0,     0,    28,    29,    30,
       0,     0,     0,    31,    32,    33,    34,    35,    36,     0,
       0,     0,     0,     1,     0,     0,    65,     0,     0,     0,
       2,    55,    56,    57,     0,    58,    59,    60,    61,     0,
      62,    63,    64,     0,    30,     0,     0,     0,    31,    32,
      33,    34,    35,    36,    26,    27,     0,     0,     0,    28,
      29,    65,    20,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     2,    55,    56,    57,     0,    58,    59,    60,
      61,     0,    62,    63,    64,     0,    30,     0,     0,     0,
      31,    32,    33,    34,    35,    36,    26,    27,     0,     0,
       0,    28,    29,    65,    20,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    27,     0,
       0,     0,    28,    29,     0,    55,    56,    57,     0,    58,
      59,    60,    61,     0,    62,    63,    64,     0,    30,     0,
       0,     0,    31,    32,    33,    34,    35,    36,    26,    27,
       0,     0,     0,    28,    29,    65,    20,   131,   137,    30,
       0,     0,     0,    31,    32,    33,    34,    35,    36,    26,
      27,     0,     0,     0,    28,    29,     0,    55,    56,    57,
       0,    58,    59,    60,    61,     0,    62,    63,    64,     0,
      30,     0,     0,     0,    31,    32,    33,    34,    35,    36,
      26,    27,     0,     0,     0,    28,    29,    65,    20,   169,
     185,    30,     0,     0,     0,    31,    32,    33,    34,    35,
      36,    26,    27,     0,     0,     0,    28,    29,     0,    55,
      56,    57,     0,    58,    59,    60,    61,     0,    62,    63,
      64,     0,    30,     0,     0,     0,    31,    32,    33,    34,
      35,    36,    26,    27,     0,     0,     0,    28,    29,    65,
      20,   193,     0,    30,     0,     0,     0,    31,    32,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
       0,    55,    56,    57,     0,    58,    59,    60,    61,     0,
      62,    63,    64,     0,    30,     0,     0,     0,    31,    32,
      33,    34,    35,    36,     0,     0,     0,     0,     0,     0,
       0,    65,    20
};

static const yytype_int16 yycheck[] =
{
      19,    30,    60,    69,    20,     3,    22,    37,    20,   122,
       3,    24,    48,    11,     0,    73,    12,    13,    31,    50,
      24,    18,    10,    11,    55,    56,    62,    31,    61,    44,
      63,    44,    49,     8,     9,    64,    44,    44,    14,    15,
      48,    48,   104,   105,   106,   107,    51,    52,   100,   101,
       3,     4,    45,    69,   167,     8,     9,    69,    45,   117,
      59,    57,    58,    17,    61,    94,    60,    97,    98,    99,
      45,    46,   130,    65,    93,    16,    95,    96,   102,   103,
     108,   109,    45,    45,    82,    28,    29,    45,    45,   118,
     119,   120,    45,    62,    37,    62,    49,    50,    51,    52,
      53,    54,    62,   161,    44,    61,    65,    37,    47,    62,
      62,    44,    55,    44,    63,    44,   182,   175,   134,   177,
      45,    35,    44,    44,    62,   110,    23,   185,   111,   187,
     188,   112,   114,   191,   113,    55,    12,     3,     4,   134,
       7,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,   178,
     179,    -1,    -1,   172,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     3,     4,    -1,    -1,    -1,     8,     9,    45,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    62,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,     3,     4,    -1,    -1,    -1,     8,
       9,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,     3,     4,    -1,    -1,
      -1,     8,     9,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
      -1,    -1,     8,     9,    -1,    32,    33,    34,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,     3,     4,
      -1,    -1,    -1,     8,     9,    62,    63,    64,    44,    45,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,     3,
       4,    -1,    -1,    -1,     8,     9,    -1,    32,    33,    34,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
       3,     4,    -1,    -1,    -1,     8,     9,    62,    63,    64,
      44,    45,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,     3,     4,    -1,    -1,    -1,     8,     9,    -1,    32,
      33,    34,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,     3,     4,    -1,    -1,    -1,     8,     9,    62,
      63,    64,    -1,    45,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    31,    94,    96,   105,   106,   107,   108,   109,
       3,    45,    89,    90,    92,    93,   106,     0,    89,    61,
      63,   100,    45,    48,    62,    44,     3,     4,     8,     9,
      45,    49,    50,    51,    52,    53,    54,    67,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    87,    32,    33,    34,    36,    37,
      38,    39,    41,    42,    43,    62,    64,    84,    85,    91,
      94,    96,    97,    98,    99,   100,   101,   102,   103,   104,
      44,    88,    94,    95,    89,    93,    71,    71,    85,    71,
      72,     8,     9,    45,    46,    18,    61,    50,    55,    56,
      51,    52,    10,    11,    12,    13,    57,    58,    14,    15,
      49,    59,    60,    16,    17,    83,    86,    65,    45,    45,
      45,   104,    45,    62,    62,    62,    85,    62,    64,    96,
      98,    64,   104,    44,    48,    89,    44,    44,    68,    84,
      85,    84,    84,    72,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    76,    76,    77,    78,    79,    80,
      81,    65,   104,    85,    85,    85,    37,   101,    62,    64,
      95,    44,    48,    47,   104,    44,    44,    44,    45,   101,
      84,   104,    63,   104,    85,    44,    85,    35,    98,    44,
     104,    44,   104,    64,    62,   104
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    69,    69,    69,    70,    70,    70,    70,    70,
      70,    68,    68,    71,    71,    71,    71,    67,    67,    67,
      67,    67,    67,    72,    73,    73,    73,    73,    74,    74,
      74,    75,    75,    75,    76,    76,    76,    76,    76,    77,
      77,    77,    78,    78,    79,    79,    80,    80,    81,    81,
      82,    82,    83,    84,    84,    84,    85,    86,    87,    93,
      93,    92,    92,    90,    90,    90,    90,    89,    94,   108,
     108,    96,    91,    91,    95,    95,    88,    88,   100,   100,
     100,   100,   101,   101,    97,    97,    97,   102,   102,   102,
     102,   103,   103,   103,   103,    99,    99,   104,   104,   104,
     104,   104,   104,    98,    98,   105,   106,   106,   107,   107,
     109
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     4,     3,     4,     2,
       2,     1,     3,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     3,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     4,     3,     1,     1,     1,
       1,     3,     1,     2,     2,     1,     1,     3,     2,     3,
       3,     4,     1,     2,     5,     7,     7,     5,     7,     6,
       7,     2,     2,     2,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     1,     1,     1,     2,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 94 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new Identifier(*(yyvsp[0].str)); }
#line 1489 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 95 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new Constant((yyvsp[0].num)); }
#line 1495 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 97 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1501 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 101 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1507 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 102 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "\n ARRAY ACCESS not implemented\n"); }
#line 1513 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 103 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new FnCall((yyvsp[-2].nodePtr)); }
#line 1519 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "FnCall\n"); (yyval.nodePtr) = new FnCall((yyvsp[-3].nodePtr), (yyvsp[-1].listPtr)); }
#line 1525 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 107 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new PostOperation('+', (yyvsp[-1].nodePtr)); }
#line 1531 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new PostOperation('-', (yyvsp[-1].nodePtr)); }
#line 1537 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 112 "src/parser.y" /* yacc.c:1646  */
    { (yyval.listPtr) = new List((yyvsp[0].nodePtr)); }
#line 1543 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 113 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].listPtr)->add((yyvsp[0].nodePtr)); (yyval.listPtr) = (yyvsp[-2].listPtr); }
#line 1549 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1555 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 118 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new PreOperation((yyvsp[0].nodePtr), '+'); }
#line 1561 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 119 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new PreOperation((yyvsp[0].nodePtr), '-'); }
#line 1567 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 120 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new UnaryOperation(*(yyvsp[-1].str), (yyvsp[0].nodePtr)); }
#line 1573 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 126 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("&"); }
#line 1579 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 127 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("*"); }
#line 1585 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 128 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("+"); }
#line 1591 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 129 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("-"); }
#line 1597 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 130 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("~"); }
#line 1603 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 131 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("!"); }
#line 1609 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 135 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1615 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 140 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1621 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 141 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ArithmeticOperation((yyvsp[-2].nodePtr),"*", (yyvsp[0].nodePtr)); }
#line 1627 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 142 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ArithmeticOperation((yyvsp[-2].nodePtr), "/", (yyvsp[0].nodePtr)); }
#line 1633 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 143 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ArithmeticOperation((yyvsp[-2].nodePtr), "%", (yyvsp[0].nodePtr)); }
#line 1639 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 147 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1645 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 148 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "ArithmeticOperation\n"); (yyval.nodePtr) = new ArithmeticOperation((yyvsp[-2].nodePtr), "+", (yyvsp[0].nodePtr)); }
#line 1651 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 149 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ArithmeticOperation((yyvsp[-2].nodePtr), "-", (yyvsp[0].nodePtr)); }
#line 1657 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 153 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1663 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 154 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BitwiseOperation((yyvsp[-2].nodePtr), "<<", (yyvsp[0].nodePtr)); }
#line 1669 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 155 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BitwiseOperation((yyvsp[-2].nodePtr), ">>", (yyvsp[0].nodePtr)); }
#line 1675 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 159 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1681 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 160 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BooleanOperation((yyvsp[-2].nodePtr), "<", (yyvsp[0].nodePtr)); }
#line 1687 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 161 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BooleanOperation((yyvsp[-2].nodePtr), ">", (yyvsp[0].nodePtr)); }
#line 1693 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 162 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BooleanOperation((yyvsp[-2].nodePtr), "<=", (yyvsp[0].nodePtr)); }
#line 1699 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 163 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BooleanOperation((yyvsp[-2].nodePtr), ">=", (yyvsp[0].nodePtr)); }
#line 1705 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 167 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1711 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 168 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BooleanOperation((yyvsp[-2].nodePtr), "==", (yyvsp[0].nodePtr)); }
#line 1717 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 169 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BooleanOperation((yyvsp[-2].nodePtr), "!=", (yyvsp[0].nodePtr)); }
#line 1723 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 173 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1729 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 174 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BitwiseOperation((yyvsp[-2].nodePtr), "&", (yyvsp[0].nodePtr)); }
#line 1735 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 178 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1741 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 179 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BitwiseOperation((yyvsp[-2].nodePtr), "^", (yyvsp[0].nodePtr)); }
#line 1747 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 183 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1753 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 184 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BitwiseOperation((yyvsp[-2].nodePtr), "|", (yyvsp[0].nodePtr)); }
#line 1759 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 188 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1765 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 189 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "logical_and_expression\n"); (yyval.nodePtr) = new LogicalAnd((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1771 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 193 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1777 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 194 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "logical_or_expression\n"); (yyval.nodePtr) = new LogicalOr((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1783 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 199 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1789 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 204 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1795 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 205 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new AssignmentExpression((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1801 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 209 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].str)->pop_back(); (yyval.nodePtr) = new AssignmentExpression((yyvsp[-2].nodePtr), new ArithmeticOperation((yyvsp[-2].nodePtr), *(yyvsp[-1].str), (yyvsp[0].nodePtr))); }
#line 1807 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 213 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1813 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 220 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1819 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 225 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1825 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 302 "src/parser.y" /* yacc.c:1646  */
    { (yyval.initDeclaratorPtr) = new InitDeclarator((yyvsp[0].declaratorPtr)); }
#line 1831 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 303 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "init_declarator w initializer \n");(yyval.initDeclaratorPtr) = new InitDeclarator((yyvsp[-2].declaratorPtr), (yyvsp[0].nodePtr)); }
#line 1837 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 307 "src/parser.y" /* yacc.c:1646  */
    { (yyval.initDeclaratorListPtr) = new InitDeclaratorList((yyvsp[0].initDeclaratorPtr)); }
#line 1843 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 308 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].initDeclaratorListPtr)->add((yyvsp[0].initDeclaratorPtr)); (yyval.initDeclaratorListPtr) = (yyvsp[-2].initDeclaratorListPtr); }
#line 1849 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 314 "src/parser.y" /* yacc.c:1646  */
    { (yyval.declaratorPtr) = new Declarator(new Identifier(*(yyvsp[0].str)), false); }
#line 1855 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 315 "src/parser.y" /* yacc.c:1646  */
    { (yyval.declaratorPtr) = (yyvsp[-1].declaratorPtr); }
#line 1861 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 318 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "direct_declarator\n"); (yyval.declaratorPtr) = new FnDeclarator((yyvsp[-3].declaratorPtr), (yyvsp[-1].paramListPtr)); }
#line 1867 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 320 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "FnDeclarator\n"); (yyval.declaratorPtr) = new FnDeclarator((yyvsp[-2].declaratorPtr)); }
#line 1873 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 325 "src/parser.y" /* yacc.c:1646  */
    { (yyval.declaratorPtr) = (yyvsp[0].declaratorPtr); }
#line 1879 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 337 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 1885 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 341 "src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("void"); }
#line 1891 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 344 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "typeSpecifier\n"); (yyval.str) = new std::string("int"); }
#line 1897 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 357 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].initDeclaratorListPtr)->setType(*(yyvsp[-2].str)); (yyval.nodePtr) = (yyvsp[-1].initDeclaratorListPtr); }
#line 1903 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 361 "src/parser.y" /* yacc.c:1646  */
    { (yyval.listPtr) = new List((yyvsp[0].nodePtr)); }
#line 1909 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 362 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].listPtr)->add((yyvsp[0].nodePtr)); (yyval.listPtr) = (yyvsp[-1].listPtr); }
#line 1915 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 366 "src/parser.y" /* yacc.c:1646  */
    { (yyval.paramDeclPtr) = new ParameterDeclaration(*(yyvsp[-1].str), (yyvsp[0].declaratorPtr)); }
#line 1921 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 368 "src/parser.y" /* yacc.c:1646  */
    { (yyval.paramDeclPtr) = new ParameterDeclaration(*(yyvsp[0].str)); }
#line 1927 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 372 "src/parser.y" /* yacc.c:1646  */
    { (yyval.paramListPtr) = new ParameterList((yyvsp[0].paramDeclPtr)); }
#line 1933 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 373 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].paramListPtr)->add((yyvsp[0].paramDeclPtr)); (yyval.paramListPtr) = (yyvsp[-2].paramListPtr); }
#line 1939 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 382 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = nullptr; }
#line 1945 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 383 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "stmt Compound\n"); (yyval.nodePtr) = new Compound(nullptr, (yyvsp[-1].listPtr)); }
#line 1951 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 384 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "dclr Compound\n");(yyval.nodePtr) = new Compound((yyvsp[-1].listPtr), nullptr); }
#line 1957 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 385 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "dclr stmt Compound\n");(yyval.nodePtr) = new Compound((yyvsp[-2].listPtr), (yyvsp[-1].listPtr)); }
#line 1963 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 391 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "Empty Semicolon"); (yyval.nodePtr) = nullptr; }
#line 1969 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 392 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1975 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 398 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new IfElseStatement((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1981 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 399 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new IfElseStatement((yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1987 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 400 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new SwitchStatement((yyvsp[-4].nodePtr), (yyvsp[-1].listPtr)); }
#line 1993 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 407 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new WhileStatement((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1999 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 408 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "\n DO-WHILE not implemented\n"); }
#line 2005 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 409 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "2arg ForStatement\n"); (yyval.nodePtr) = new ForStatement((yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 2011 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 410 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "3arg ForStatement\n"); (yyval.nodePtr) = new ForStatement((yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 2017 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 418 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ContinueStatement(); }
#line 2023 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 419 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new BreakStatement(); }
#line 2029 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 420 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ReturnStatement();	}
#line 2035 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 421 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = new ReturnStatement((yyvsp[-1].nodePtr)); }
#line 2041 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 427 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "CASE\n"); (yyval.nodePtr) = new LabeledStatement((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 2047 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 428 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "DEFAULT\n");(yyval.nodePtr) = new LabeledStatement((yyvsp[0].nodePtr)); }
#line 2053 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 432 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "labeled_statement\n"); (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2059 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 433 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2065 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 434 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2071 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 435 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2077 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 436 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2083 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 437 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2089 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 441 "src/parser.y" /* yacc.c:1646  */
    { (yyval.listPtr) = new List((yyvsp[0].nodePtr)); }
#line 2095 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 442 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].listPtr)->add((yyvsp[0].nodePtr)); (yyval.listPtr) = (yyvsp[-1].listPtr); }
#line 2101 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 451 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "FnDefinition\n"); (yyval.nodePtr) = new FnDefinition(*(yyvsp[-2].str), (yyvsp[-1].declaratorPtr), (yyvsp[0].nodePtr)); }
#line 2107 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 459 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "external fn definition\n"); (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2113 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 460 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "external fn definition\n"); (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2119 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 464 "src/parser.y" /* yacc.c:1646  */
    { fprintf(stderr, "translation_unit item\n");(yyval.listPtr) = new List((yyvsp[0].nodePtr)); }
#line 2125 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 465 "src/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].listPtr)->add((yyvsp[0].nodePtr)); (yyval.listPtr) = (yyvsp[-1].listPtr); }
#line 2131 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 468 "src/parser.y" /* yacc.c:1646  */
    { g_root = (yyvsp[0].listPtr); }
#line 2137 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2141 "src/parser.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 470 "src/parser.y" /* yacc.c:1906  */


// REDUNDANT GRAMMAR:
// parameter_type_list
// ELLIPSE, VOLATILE; EXTERN; AUTO; REGISTER; UNION



//// Later -------------------------------------------------------------
/// Struct -------------------------------------------------------------
// struct_specifier //no union needed
// 	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
// 	| STRUCT '{' struct_declaration_list '}'
// 	| STRUCT IDENTIFIER
// 	;

// struct_declaration_list
// 	: struct_declaration
// 	| struct_declaration_list struct_declaration
// 	;

// struct_declaration
// 	: specifier_qualifier_list struct_declarator_list ';'
// 	;

// struct_declarator_list
// 	: struct_declarator
// 	| struct_declarator_list ',' struct_declarator
// 	;

// struct_declarator
// 	: declarator
// 	| ':' constant_expression
// 	| declarator ':' constant_expression
// 	;


/// Enum -------------------------------------------------------------

// enum_specifier
// 	: ENUM '{' enumerator_list '}'
// 	| ENUM IDENTIFIER '{' enumerator_list '}'
// 	| ENUM IDENTIFIER
// 	;

// enumerator_list
// 	: enumerator
// 	| enumerator_list ',' enumerator
// 	;

// enumerator
// 	: IDENTIFIER
// 	| IDENTIFIER '=' constant_expression
// 	;

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

//#include <stdio.h>

//  char yytext[];
//  int column;

// yyerror(s)
// char *s;
// {
// 	fflush(stdout);
// 	printf("\n%*s\n%*s\n", column, "^", column, s);
// }

// Definition of root ptr (to match declaration earlier)
const Node *g_root;

// Function to parse AST to main (to match declaration in main.cpp)
const Node *parseAST(const char *input)
{
	yyin = fopen(input, "r");
	if (!yyin)
	 {
		fprintf(stderr, "(%s) could not be opened", input);
		return nullptr;
	}

	g_root=NULL;
    yyparse();

	fclose(yyin);

	if(!g_root)
		fprintf(stderr, "Error while parsing! No root pointer passed.");
	return g_root;
}
