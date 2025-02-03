/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         CONF_STYPE
/* Substitute the variable and function names.  */
#define yyparse         conf_parse
#define yylex           conf_lex
#define yyerror         conf_error
#define yydebug         conf_debug
#define yynerrs         conf_nerrs

/* First part of user prologue.  */
#line 20 "../src/parse/conf_parser.ypp"


#pragma GCC diagnostic push
#include "src/util/nowarn_in_bison.h"

#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/input.h"
#include "src/parse/conf_parser.h"

using namespace re2c;

extern "C" {
    static void yyerror(Input& in, Opt& opts, const char* s);
    static int yylex(CONF_STYPE* yylval, Input& in, Opt& opts);
}


#line 96 "src/parse/conf_parser.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "conf_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONF_NUMBER = 3,                /* CONF_NUMBER  */
  YYSYMBOL_CONF_STRING = 4,                /* CONF_STRING  */
  YYSYMBOL_CONF_COND = 5,                  /* CONF_COND  */
  YYSYMBOL_CONF_VAR = 6,                   /* CONF_VAR  */
  YYSYMBOL_CONF_CODE = 7,                  /* CONF_CODE  */
  YYSYMBOL_CONF_GOPT = 8,                  /* CONF_GOPT  */
  YYSYMBOL_CONF_LOPT = 9,                  /* CONF_LOPT  */
  YYSYMBOL_CONF_UD = 10,                   /* CONF_UD  */
  YYSYMBOL_11_ = 11,                       /* '='  */
  YYSYMBOL_12_ = 12,                       /* '('  */
  YYSYMBOL_13_ = 13,                       /* '?'  */
  YYSYMBOL_14_ = 14,                       /* ':'  */
  YYSYMBOL_15_ = 15,                       /* ')'  */
  YYSYMBOL_16_ = 16,                       /* '['  */
  YYSYMBOL_17_ = 17,                       /* ']'  */
  YYSYMBOL_18_ = 18,                       /* ','  */
  YYSYMBOL_19_ = 19,                       /* '|'  */
  YYSYMBOL_20_ = 20,                       /* '&'  */
  YYSYMBOL_21_ = 21,                       /* '!'  */
  YYSYMBOL_22_ = 22,                       /* '{'  */
  YYSYMBOL_23_ = 23,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 24,                  /* $accept  */
  YYSYMBOL_conf = 25,                      /* conf  */
  YYSYMBOL_num = 26,                       /* num  */
  YYSYMBOL_str = 27,                       /* str  */
  YYSYMBOL_list = 28,                      /* list  */
  YYSYMBOL_elems = 29,                     /* elems  */
  YYSYMBOL_code_exprs = 30,                /* code_exprs  */
  YYSYMBOL_code_expr = 31,                 /* code_expr  */
  YYSYMBOL_code_opt = 32,                  /* code_opt  */
  YYSYMBOL_opt_or = 33,                    /* opt_or  */
  YYSYMBOL_opt_and = 34,                   /* opt_and  */
  YYSYMBOL_opt_neg = 35,                   /* opt_neg  */
  YYSYMBOL_opt = 36,                       /* opt  */
  YYSYMBOL_code_list = 37                  /* code_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined CONF_STYPE_IS_TRIVIAL && CONF_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   99

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   265


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,     2,     2,     2,    20,     2,
      12,    15,     2,     2,    18,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    14,     2,
       2,    11,     2,    13,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    16,     2,    17,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,    19,    23,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10
};

#if CONF_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    86,    86,    87,    88,    89,    90,    91,    94,    95,
     104,   105,   114,   115,   118,   121,   127,   129,   135,   136,
     137,   138,   141,   143,   148,   149,   152,   153,   156,   157,
     160,   161,   162,   163,   166,   168,   170
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if CONF_DEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONF_NUMBER",
  "CONF_STRING", "CONF_COND", "CONF_VAR", "CONF_CODE", "CONF_GOPT",
  "CONF_LOPT", "CONF_UD", "'='", "'('", "'?'", "':'", "')'", "'['", "']'",
  "','", "'|'", "'&'", "'!'", "'{'", "'}'", "$accept", "conf", "num",
  "str", "list", "elems", "code_exprs", "code_expr", "code_opt", "opt_or",
  "opt_and", "opt_neg", "opt", "code_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      37,    -4,    43,    17,    77,   -48,   -48,     1,     4,   -48,
     -48,   -48,   -48,   -48,   -48,    64,   -48,   -48,   -48,     1,
      73,    14,    22,    13,   -48,   -48,   -48,    40,   -48,   -48,
       1,    45,   -48,   -48,   -48,    52,   -48,    71,     1,     1,
     -48,    56,    58,    -3,   -48,    63,    65,   -48,   -48,   -48,
     -48,   -48,    83,     2,    26,    50,    12,    20,     1,    74,
       1,    75,   -48,   -48,   -48,    85,    78,    80,   -48,    81,
     -48,    57,    68,   -48,     2,    26,   -48,    82,    19,   -48,
     -48,    33,   -48
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,    16,     8,    10,     0,     0,     2,
       3,     4,     1,     6,     7,     5,    30,    31,    32,     0,
       0,     0,    24,    26,    28,    14,    12,     0,    18,    19,
       0,     0,    17,    20,    21,     0,    29,     0,     0,     0,
      13,     0,     0,     0,    33,     0,     0,    25,    27,    15,
      16,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    22,    34,     0,     0,     0,     9,     0,
      11,     0,     0,    16,     0,     0,    23,     0,     0,    16,
      35,     0,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,     0,    -2,   -48,   -48,   -47,   -48,   -48,   -18,
      59,   -48,    79,   -48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,    45,    46,    11,    27,    15,    32,    33,    21,
      22,    23,    24,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      10,    35,     9,    55,    56,     5,    16,     4,    25,    17,
      18,    51,    42,    19,    58,    71,    28,    12,    29,    52,
      47,    26,    20,    28,    30,    29,    78,    37,    31,    64,
       6,    30,    81,    39,    65,    31,    80,    28,    60,    29,
      67,    38,    69,    66,     1,    30,     5,     6,     2,    31,
      82,    43,    61,    59,    28,     7,    29,    40,    41,     8,
      49,    28,    30,    29,    62,    63,    31,    44,    28,    30,
      29,    50,    76,    31,     5,     6,    30,    53,    16,    54,
      31,    17,    18,     7,    13,    19,    57,    14,    72,    68,
      70,    77,    73,    74,    75,     0,    79,     0,    48,    36
};

static const yytype_int8 yycheck[] =
{
       2,    19,     2,    50,    51,     3,     5,    11,     4,     8,
       9,    14,    30,    12,    12,    62,     4,     0,     6,    22,
      38,    17,    21,     4,    12,     6,    73,    13,    16,    17,
       4,    12,    79,    20,    14,    16,    17,     4,    12,     6,
      58,    19,    60,    23,     7,    12,     3,     4,    11,    16,
      17,     6,    54,    53,     4,    12,     6,    17,    18,    16,
       4,     4,    12,     6,    14,    15,    16,    15,     4,    12,
       6,    13,    15,    16,     3,     4,    12,    14,     5,    14,
      16,     8,     9,    12,     7,    12,     3,    10,     3,    15,
      15,    23,    14,    13,    13,    -1,    14,    -1,    39,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    11,    25,    11,     3,     4,    12,    16,    26,
      27,    28,     0,     7,    10,    30,     5,     8,     9,    12,
      21,    33,    34,    35,    36,     4,    17,    29,     4,     6,
      12,    16,    31,    32,    37,    33,    36,    13,    19,    20,
      17,    18,    33,     6,    15,    26,    27,    33,    34,     4,
      13,    14,    22,    14,    14,    30,    30,     3,    12,    26,
      12,    27,    14,    15,    17,    14,    23,    33,    15,    33,
      15,    30,     3,    14,    13,    13,    15,    23,    30,    14,
      17,    30,    17
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    24,    25,    25,    25,    25,    25,    25,    26,    26,
      27,    27,    28,    28,    29,    29,    30,    30,    31,    31,
      31,    31,    32,    32,    33,    33,    34,    34,    35,    35,
      36,    36,    36,    36,    37,    37,    37
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     3,     3,     3,     1,     7,
       1,     7,     2,     3,     1,     3,     0,     2,     1,     1,
       1,     1,     5,     7,     1,     3,     1,     3,     1,     2,
       1,     1,     1,     3,     5,     8,    10
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = CONF_EMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == CONF_EMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (in, opts, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use CONF_error or CONF_UNDEF. */
#define YYERRCODE CONF_UNDEF


/* Enable debugging if requested.  */
#if CONF_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, in, opts); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, re2c::Input& in, re2c::Opt& opts)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (in);
  YY_USE (opts);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, re2c::Input& in, re2c::Opt& opts)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, in, opts);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, re2c::Input& in, re2c::Opt& opts)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], in, opts);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, in, opts); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !CONF_DEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !CONF_DEBUG */


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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, re2c::Input& in, re2c::Opt& opts)
{
  YY_USE (yyvaluep);
  YY_USE (in);
  YY_USE (opts);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (re2c::Input& in, re2c::Opt& opts)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = CONF_EMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == CONF_EMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, in, opts);
    }

  if (yychar <= CONF_EOF)
    {
      yychar = CONF_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == CONF_error)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = CONF_UNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = CONF_EMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* conf: '=' num  */
#line 86 "../src/parse/conf_parser.ypp"
           { in.save_conf_num((yyvsp[0].num)); }
#line 1174 "src/parse/conf_parser.cc"
    break;

  case 3: /* conf: '=' str  */
#line 87 "../src/parse/conf_parser.ypp"
           { in.save_conf_str((yyvsp[0].str)); }
#line 1180 "src/parse/conf_parser.cc"
    break;

  case 4: /* conf: '=' list  */
#line 88 "../src/parse/conf_parser.ypp"
           { in.save_conf_list((yyvsp[0].list)); }
#line 1186 "src/parse/conf_parser.cc"
    break;

  case 5: /* conf: CONF_CODE '=' code_exprs  */
#line 89 "../src/parse/conf_parser.ypp"
                           { *(yyvsp[-2].codeptr) = (yyvsp[0].codes); }
#line 1192 "src/parse/conf_parser.cc"
    break;

  case 6: /* conf: CONF_CODE '=' CONF_CODE  */
#line 90 "../src/parse/conf_parser.ypp"
                           { *(yyvsp[-2].codeptr) = *(yyvsp[0].codeptr); }
#line 1198 "src/parse/conf_parser.cc"
    break;

  case 7: /* conf: CONF_CODE '=' CONF_UD  */
#line 91 "../src/parse/conf_parser.ypp"
                           { *(yyvsp[-2].codeptr) = opts.make_code_undefined(); }
#line 1204 "src/parse/conf_parser.cc"
    break;

  case 9: /* num: '(' opt_or '?' num ':' num ')'  */
#line 95 "../src/parse/conf_parser.ypp"
                                 {
    if ((yyvsp[-5].opt)->kind != StxOptKind::IMM) {
        in.error_at_cur("mutable predicate is not allowed in numeric configuration");
        YYABORT;
    }
    (yyval.num) = (yyvsp[-5].opt)->imm ? (yyvsp[-3].num) : (yyvsp[-1].num);
}
#line 1216 "src/parse/conf_parser.cc"
    break;

  case 11: /* str: '(' opt_or '?' str ':' str ')'  */
#line 105 "../src/parse/conf_parser.ypp"
                                 {
    if ((yyvsp[-5].opt)->kind != StxOptKind::IMM) {
        in.error_at_cur("mutable predicate is not allowed in string configuration");
        YYABORT;
    }
    (yyval.str) = (yyvsp[-5].opt)->imm ? (yyvsp[-3].str) : (yyvsp[-1].str);
}
#line 1228 "src/parse/conf_parser.cc"
    break;

  case 12: /* list: '[' ']'  */
#line 114 "../src/parse/conf_parser.ypp"
                { (yyval.list) = in.get_tmp_list(); }
#line 1234 "src/parse/conf_parser.cc"
    break;

  case 13: /* list: '[' elems ']'  */
#line 115 "../src/parse/conf_parser.ypp"
                { (yyval.list) = (yyvsp[-1].list); }
#line 1240 "src/parse/conf_parser.cc"
    break;

  case 14: /* elems: CONF_STRING  */
#line 118 "../src/parse/conf_parser.ypp"
              {
    (yyval.list) = in.get_tmp_list();
    (yyval.list)->push_back((yyvsp[0].str));
}
#line 1249 "src/parse/conf_parser.cc"
    break;

  case 15: /* elems: elems ',' CONF_STRING  */
#line 121 "../src/parse/conf_parser.ypp"
                          {
    (yyval.list) = (yyvsp[-2].list);
    (yyval.list)->push_back((yyvsp[0].str));
}
#line 1258 "src/parse/conf_parser.cc"
    break;

  case 16: /* code_exprs: %empty  */
#line 127 "../src/parse/conf_parser.ypp"
         {
    (yyval.codes) = opts.new_code_list();
}
#line 1266 "src/parse/conf_parser.cc"
    break;

  case 17: /* code_exprs: code_exprs code_expr  */
#line 129 "../src/parse/conf_parser.ypp"
                         {
    (yyval.codes) = (yyvsp[-1].codes);
    append((yyvsp[-1].codes), (yyvsp[0].code));
}
#line 1275 "src/parse/conf_parser.cc"
    break;

  case 18: /* code_expr: CONF_STRING  */
#line 135 "../src/parse/conf_parser.ypp"
              { (yyval.code) = opts.make_code_str((yyvsp[0].str)); }
#line 1281 "src/parse/conf_parser.cc"
    break;

  case 19: /* code_expr: CONF_VAR  */
#line 136 "../src/parse/conf_parser.ypp"
              { (yyval.code) = opts.make_code_var((yyvsp[0].var)); }
#line 1287 "src/parse/conf_parser.cc"
    break;

  case 22: /* code_opt: '(' opt_or '?' code_exprs ')'  */
#line 141 "../src/parse/conf_parser.ypp"
                                {
    (yyval.code) = opts.make_code_cond((yyvsp[-3].opt), (yyvsp[-1].codes), nullptr);
}
#line 1295 "src/parse/conf_parser.cc"
    break;

  case 23: /* code_opt: '(' opt_or '?' code_exprs ':' code_exprs ')'  */
#line 143 "../src/parse/conf_parser.ypp"
                                                 {
    (yyval.code) = opts.make_code_cond((yyvsp[-5].opt), (yyvsp[-3].codes), (yyvsp[-1].codes));
}
#line 1303 "src/parse/conf_parser.cc"
    break;

  case 25: /* opt_or: opt_and '|' opt_or  */
#line 149 "../src/parse/conf_parser.ypp"
                     { (yyval.opt) = opts.make_opt_or((yyvsp[-2].opt), (yyvsp[0].opt)); }
#line 1309 "src/parse/conf_parser.cc"
    break;

  case 27: /* opt_and: opt_neg '&' opt_and  */
#line 153 "../src/parse/conf_parser.ypp"
                      { (yyval.opt) = opts.make_opt_and((yyvsp[-2].opt), (yyvsp[0].opt)); }
#line 1315 "src/parse/conf_parser.cc"
    break;

  case 29: /* opt_neg: '!' opt  */
#line 157 "../src/parse/conf_parser.ypp"
          { (yyval.opt) = opts.make_opt_neg((yyvsp[0].opt)); }
#line 1321 "src/parse/conf_parser.cc"
    break;

  case 30: /* opt: CONF_COND  */
#line 160 "../src/parse/conf_parser.ypp"
            { (yyval.opt) = opts.make_opt_imm((yyvsp[0].cond)); }
#line 1327 "src/parse/conf_parser.cc"
    break;

  case 31: /* opt: CONF_GOPT  */
#line 161 "../src/parse/conf_parser.ypp"
            { (yyval.opt) = opts.make_opt_global((yyvsp[0].gopt)); }
#line 1333 "src/parse/conf_parser.cc"
    break;

  case 32: /* opt: CONF_LOPT  */
#line 162 "../src/parse/conf_parser.ypp"
            { (yyval.opt) = opts.make_opt_local((yyvsp[0].lopt)); }
#line 1339 "src/parse/conf_parser.cc"
    break;

  case 33: /* opt: '(' opt_or ')'  */
#line 163 "../src/parse/conf_parser.ypp"
                 { (yyval.opt) = (yyvsp[-1].opt); }
#line 1345 "src/parse/conf_parser.cc"
    break;

  case 34: /* code_list: '[' CONF_VAR ':' code_exprs ']'  */
#line 166 "../src/parse/conf_parser.ypp"
                                  {
    (yyval.code) = opts.make_code_list((yyvsp[-3].var), 0, -1, (yyvsp[-1].codes));
}
#line 1353 "src/parse/conf_parser.cc"
    break;

  case 35: /* code_list: '[' CONF_VAR '{' CONF_NUMBER '}' ':' code_exprs ']'  */
#line 168 "../src/parse/conf_parser.ypp"
                                                        {
    (yyval.code) = opts.make_code_list((yyvsp[-6].var), (yyvsp[-4].num), (yyvsp[-4].num), (yyvsp[-1].codes));
}
#line 1361 "src/parse/conf_parser.cc"
    break;

  case 36: /* code_list: '[' CONF_VAR '{' CONF_NUMBER ':' CONF_NUMBER '}' ':' code_exprs ']'  */
#line 170 "../src/parse/conf_parser.ypp"
                                                                        {
    (yyval.code) = opts.make_code_list((yyvsp[-8].var), (yyvsp[-6].num), (yyvsp[-4].num), (yyvsp[-1].codes));
}
#line 1369 "src/parse/conf_parser.cc"
    break;


#line 1373 "src/parse/conf_parser.cc"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == CONF_EMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (in, opts, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= CONF_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == CONF_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, in, opts);
          yychar = CONF_EMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, in, opts);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (in, opts, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != CONF_EMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, in, opts);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, in, opts);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 174 "../src/parse/conf_parser.ypp"


#pragma GCC diagnostic pop

extern "C" {
    static void yyerror(re2c::Input& in, Opt&, const char* s) {
        in.error_at_tok("%s", s);
    }

    static int yylex(CONF_STYPE* yylval, re2c::Input& in, Opt& opts) {
        int token;
        return in.lex_conf_token(yylval, token, opts) == Ret::OK ? token : CONF_error;
    }
}

namespace re2c {

Ret Input::load_syntax_config(Opt& opts, Lang lang) {
    in_syntax_file = true;

    // First, apply the default syntax config that is provided as a string.
    InputFile* in = new InputFile(0);
    files.push_back(in);
    msg.filenames.push_back("<default syntax file>");

    const char* src = nullptr;
    switch (lang) {
        case Lang::C: src = DEFAULT_SYNTAX_C; break;
        case Lang::D: src = DEFAULT_SYNTAX_D; break;
        case Lang::GO: src = DEFAULT_SYNTAX_GO; break;
        case Lang::HASKELL: src = DEFAULT_SYNTAX_HASKELL; break;
        case Lang::JAVA: src = DEFAULT_SYNTAX_JAVA; break;
        case Lang::JS: src = DEFAULT_SYNTAX_JS; break;
        case Lang::OCAML: src = DEFAULT_SYNTAX_OCAML; break;
        case Lang::PYTHON: src = DEFAULT_SYNTAX_PYTHON; break;
        case Lang::RUST: src = DEFAULT_SYNTAX_RUST; break;
        case Lang::V: src = DEFAULT_SYNTAX_V; break;
        case Lang::ZIG: src = DEFAULT_SYNTAX_ZIG; break;
        case Lang::NONE: break; // no language => no default syntax config
    }

    if (src != nullptr) {
        size_t flen = strlen(src);

        if (flen + maxfill() > BSIZE) {
            delete[] bot;
            BSIZE = flen;
            bot = new uint8_t[BSIZE + maxfill()];
        }

        // fill in buffer from the config string
        memcpy(bot, src, flen);
        memset(bot + flen, 0, maxfill());

        cur = mar = ctx = tok = ptr = pos = bot;
        lim = bot + flen + maxfill();

        CHECK_RET(lex_syntax_file(opts));
    }

    // Second, apply user-supplied syntax config (if any).
    // This order gives the user an opportunity to overrided only some configurations.
    if (!globopts->syntax_file.empty()) {
        reset_lexer();
        // Pass ./ as parent path to enable search in the current directory.
        std::string path = "./";
        CHECK_RET(open(globopts->syntax_file, &path));
        CHECK_RET(lex_syntax_file(opts));
    }

#define CODE_TEMPLATE(name, vars, list_vars, conds) \
    CHECK_RET(opts.check_code_##name(msg.warn));
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE

    // Reset should happen after the check, as warnings may need use config filename.
    reset_lexer();
    in_syntax_file = false;
    return Ret::OK;
}

Ret Input::parse_conf(Opt& opts) {
    return conf_parse(*this, opts) == 0 ? Ret::OK : Ret::FAIL;
}

} // namespace re2c
