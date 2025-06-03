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
#define YYSTYPE         RE2C_STYPE
/* Substitute the variable and function names.  */
#define yyparse         re2c_parse
#define yylex           re2c_lex
#define yyerror         re2c_error
#define yydebug         re2c_debug
#define yynerrs         re2c_nerrs

/* First part of user prologue.  */
#line 10 "../src/parse/parser.ypp"


#pragma GCC diagnostic push
#include "src/util/nowarn_in_bison.h"

#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/input.h"
#include "src/parse/parser.h"
#include "src/regexp/rule.h"

using namespace re2c;

extern "C" {
    static void yyerror(Input& input, Ast&, Opt&, AstGrams&, const char* s);
    static int yylex(YYSTYPE* yylval, Input& input, Ast& ast, Opt&, AstGrams&);
}


#line 97 "src/parse/parser.cc"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_CJUMP = 3,                /* TOKEN_CJUMP  */
  YYSYMBOL_TOKEN_CNEXT = 4,                /* TOKEN_CNEXT  */
  YYSYMBOL_TOKEN_CLIST = 5,                /* TOKEN_CLIST  */
  YYSYMBOL_TOKEN_CPRE_RULE = 6,            /* TOKEN_CPRE_RULE  */
  YYSYMBOL_TOKEN_CZERO = 7,                /* TOKEN_CZERO  */
  YYSYMBOL_TOKEN_CLOSESIZE = 8,            /* TOKEN_CLOSESIZE  */
  YYSYMBOL_TOKEN_CODE = 9,                 /* TOKEN_CODE  */
  YYSYMBOL_TOKEN_CONF = 10,                /* TOKEN_CONF  */
  YYSYMBOL_TOKEN_ID = 11,                  /* TOKEN_ID  */
  YYSYMBOL_TOKEN_FID = 12,                 /* TOKEN_FID  */
  YYSYMBOL_TOKEN_FID_END = 13,             /* TOKEN_FID_END  */
  YYSYMBOL_TOKEN_LINE_INFO = 14,           /* TOKEN_LINE_INFO  */
  YYSYMBOL_TOKEN_REGEXP = 15,              /* TOKEN_REGEXP  */
  YYSYMBOL_TOKEN_BLOCK = 16,               /* TOKEN_BLOCK  */
  YYSYMBOL_TOKEN_ENTRY = 17,               /* TOKEN_ENTRY  */
  YYSYMBOL_TOKEN_PRE_RULE = 18,            /* TOKEN_PRE_RULE  */
  YYSYMBOL_TOKEN_POST_RULE = 19,           /* TOKEN_POST_RULE  */
  YYSYMBOL_TOKEN_LPAREN_NEG = 20,          /* TOKEN_LPAREN_NEG  */
  YYSYMBOL_TOKEN_ERROR = 21,               /* TOKEN_ERROR  */
  YYSYMBOL_22_ = 22,                       /* '/'  */
  YYSYMBOL_23_ = 23,                       /* '='  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* '*'  */
  YYSYMBOL_26_ = 26,                       /* '$'  */
  YYSYMBOL_27_ = 27,                       /* '|'  */
  YYSYMBOL_28_ = 28,                       /* '\\'  */
  YYSYMBOL_29_ = 29,                       /* '+'  */
  YYSYMBOL_30_ = 30,                       /* '?'  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_spec = 34,                      /* spec  */
  YYSYMBOL_def = 35,                       /* def  */
  YYSYMBOL_name = 36,                      /* name  */
  YYSYMBOL_enddef = 37,                    /* enddef  */
  YYSYMBOL_rule = 38,                      /* rule  */
  YYSYMBOL_ccode = 39,                     /* ccode  */
  YYSYMBOL_trailexpr = 40,                 /* trailexpr  */
  YYSYMBOL_expr = 41,                      /* expr  */
  YYSYMBOL_diff = 42,                      /* diff  */
  YYSYMBOL_term = 43,                      /* term  */
  YYSYMBOL_factor = 44,                    /* factor  */
  YYSYMBOL_closes = 45,                    /* closes  */
  YYSYMBOL_close = 46,                     /* close  */
  YYSYMBOL_primary = 47                    /* primary  */
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
         || (defined RE2C_STYPE_IS_TRIVIAL && RE2C_STYPE_IS_TRIVIAL)))

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   75

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  77

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,     2,     2,     2,    26,     2,     2,     2,
      31,    32,    25,    29,     2,     2,     2,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
       2,    23,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    27,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if RE2C_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    81,    81,    82,    86,    90,    91,    92,    96,    99,
     105,   106,   109,   109,   112,   115,   118,   121,   124,   127,
     130,   136,   142,   148,   154,   160,   166,   172,   179,   180,
     185,   190,   191,   197,   198,   202,   203,   207,   209,   213,
     214,   227,   233,   234,   238,   239,   240,   244,   245,   254,
     255
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if RE2C_DEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_CJUMP",
  "TOKEN_CNEXT", "TOKEN_CLIST", "TOKEN_CPRE_RULE", "TOKEN_CZERO",
  "TOKEN_CLOSESIZE", "TOKEN_CODE", "TOKEN_CONF", "TOKEN_ID", "TOKEN_FID",
  "TOKEN_FID_END", "TOKEN_LINE_INFO", "TOKEN_REGEXP", "TOKEN_BLOCK",
  "TOKEN_ENTRY", "TOKEN_PRE_RULE", "TOKEN_POST_RULE", "TOKEN_LPAREN_NEG",
  "TOKEN_ERROR", "'/'", "'='", "';'", "'*'", "'$'", "'|'", "'\\\\'", "'+'",
  "'?'", "'('", "')'", "$accept", "spec", "def", "name", "enddef", "rule",
  "ccode", "trailexpr", "expr", "diff", "term", "factor", "closes",
  "close", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-25)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -25,     1,   -25,    30,     5,    20,   -25,   -13,   -25,   -25,
     -25,   -25,    25,    31,    43,    22,    48,    54,    22,   -25,
      22,   -25,    55,   -18,    10,   -25,    22,    14,   -25,    20,
      20,    20,    20,    20,    20,   -25,   -25,    63,   -25,   -25,
     -25,   -25,   -25,   -25,    -2,   -25,   -25,     4,    38,   -25,
      22,    22,    22,   -25,   -25,   -25,   -25,   -25,    29,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,    19,    10,   -25,   -25
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     4,    48,    11,     7,
      47,     3,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     6,     0,    31,    33,    35,    37,    39,    48,     0,
       0,     0,     0,     0,     0,    26,    30,     0,    28,    27,
      10,    17,    18,    19,     0,    15,    16,     0,     0,    14,
       0,     0,     0,    38,    41,    44,    45,    46,    40,    42,
      23,    24,    25,    21,    22,    20,    29,    50,    49,    13,
       9,    12,     8,    32,    34,    36,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -25,   -25,   -25,   -25,   -25,   -25,    37,    70,   -15,    23,
     -24,   -25,   -25,    17,   -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    19,    20,    72,    21,    39,    22,    23,    24,
      25,    26,    58,    59,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,     2,    53,    47,    50,    48,     3,     4,     5,    51,
      40,     6,     7,     8,    35,     9,    10,    11,    12,    13,
      14,    15,    54,    36,    37,    51,    16,    17,    75,    38,
      67,    51,    18,    28,    41,    73,    68,    10,    52,    55,
      42,    28,    15,    56,    57,    10,    51,    29,    30,    31,
      15,    69,    43,    18,    55,    32,    33,    45,    56,    57,
      70,    18,    71,    46,    49,    51,    60,    61,    62,    63,
      64,    65,    66,    34,    74,    76
};

static const yytype_int8 yycheck[] =
{
      15,     0,    26,    18,    22,    20,     5,     6,     7,    27,
      23,    10,    11,    12,     9,    14,    15,    16,    17,    18,
      19,    20,     8,     3,     4,    27,    25,    26,    52,     9,
      32,    27,    31,    11,     9,    50,    32,    15,    28,    25,
       9,    11,    20,    29,    30,    15,    27,    17,    18,    19,
      20,    13,     9,    31,    25,    25,    26,     9,    29,    30,
      22,    31,    24,     9,     9,    27,    29,    30,    31,    32,
      33,    34,     9,     3,    51,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    34,     0,     5,     6,     7,    10,    11,    12,    14,
      15,    16,    17,    18,    19,    20,    25,    26,    31,    35,
      36,    38,    40,    41,    42,    43,    44,    47,    11,    17,
      18,    19,    25,    26,    40,     9,     3,     4,     9,    39,
      23,     9,     9,     9,    41,     9,     9,    41,    41,     9,
      22,    27,    28,    43,     8,    25,    29,    30,    45,    46,
      39,    39,    39,    39,    39,    39,     9,    32,    32,    13,
      22,    24,    37,    41,    42,    43,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    34,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    44,    45,    45,    46,    46,    46,    47,    47,    47,
      47
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     3,     3,
       2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     2,
       1,     1,     3,     1,     3,     1,     3,     1,     2,     1,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     3,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = RE2C_EMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == RE2C_EMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (input, ast, opts, grams, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use RE2C_error or RE2C_UNDEF. */
#define YYERRCODE RE2C_UNDEF


/* Enable debugging if requested.  */
#if RE2C_DEBUG

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
                  Kind, Value, input, ast, opts, grams); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, re2c::Input& input, re2c::Ast& ast, re2c::Opt& opts, re2c::AstGrams& grams)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (input);
  YY_USE (ast);
  YY_USE (opts);
  YY_USE (grams);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, re2c::Input& input, re2c::Ast& ast, re2c::Opt& opts, re2c::AstGrams& grams)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, input, ast, opts, grams);
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
                 int yyrule, re2c::Input& input, re2c::Ast& ast, re2c::Opt& opts, re2c::AstGrams& grams)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], input, ast, opts, grams);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, input, ast, opts, grams); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !RE2C_DEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !RE2C_DEBUG */


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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, re2c::Input& input, re2c::Ast& ast, re2c::Opt& opts, re2c::AstGrams& grams)
{
  YY_USE (yyvaluep);
  YY_USE (input);
  YY_USE (ast);
  YY_USE (opts);
  YY_USE (grams);
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
yyparse (re2c::Input& input, re2c::Ast& ast, re2c::Opt& opts, re2c::AstGrams& grams)
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

  yychar = RE2C_EMPTY; /* Cause a token to be read.  */

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
  if (yychar == RE2C_EMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, input, ast, opts, grams);
    }

  if (yychar <= RE2C_EOF)
    {
      yychar = RE2C_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == RE2C_error)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = RE2C_UNDEF;
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
  yychar = RE2C_EMPTY;
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
  case 3: /* spec: spec TOKEN_BLOCK  */
#line 82 "../src/parse/parser.ypp"
                   {
    if (use_block(input, ast, opts, grams, ast.temp_blockname) != Ret::OK) YYABORT;
    ast.temp_blockname.clear();
}
#line 1195 "src/parse/parser.cc"
    break;

  case 4: /* spec: spec TOKEN_CONF  */
#line 86 "../src/parse/parser.ypp"
                  {
    // Handled here, as the main lexer should not get access to opts under construction.
    if (input.lex_conf(opts) != Ret::OK) YYABORT;
}
#line 1204 "src/parse/parser.cc"
    break;

  case 8: /* def: name expr enddef  */
#line 96 "../src/parse/parser.ypp"
                   {
    if (add_named_def(opts.symtab, (yyvsp[-2].cstr), (yyvsp[-1].regexp), input) != Ret::OK) YYABORT;
}
#line 1212 "src/parse/parser.cc"
    break;

  case 9: /* def: name expr '/'  */
#line 99 "../src/parse/parser.ypp"
                {
    input.error_at_tok("trailing contexts are not allowed in named definitions");
    YYABORT;
}
#line 1221 "src/parse/parser.cc"
    break;

  case 10: /* name: TOKEN_ID '='  */
#line 105 "../src/parse/parser.ypp"
               { (yyval.cstr) = (yyvsp[-1].cstr); }
#line 1227 "src/parse/parser.cc"
    break;

  case 14: /* rule: trailexpr TOKEN_CODE  */
#line 112 "../src/parse/parser.ypp"
                       {
    find_or_add_gram(grams, "").rules.push_back({(yyvsp[-1].regexp), (yyvsp[0].semact)});
}
#line 1235 "src/parse/parser.cc"
    break;

  case 15: /* rule: '*' TOKEN_CODE  */
#line 115 "../src/parse/parser.ypp"
                 {
    find_or_add_gram(grams, "").defs.push_back((yyvsp[0].semact));
}
#line 1243 "src/parse/parser.cc"
    break;

  case 16: /* rule: '$' TOKEN_CODE  */
#line 118 "../src/parse/parser.ypp"
                 {
    find_or_add_gram(grams, "").eofs.push_back((yyvsp[0].semact));
}
#line 1251 "src/parse/parser.cc"
    break;

  case 17: /* rule: TOKEN_ENTRY TOKEN_CODE  */
#line 121 "../src/parse/parser.ypp"
                         {
    find_or_add_gram(grams, "").entry.push_back((yyvsp[0].semact));
}
#line 1259 "src/parse/parser.cc"
    break;

  case 18: /* rule: TOKEN_PRE_RULE TOKEN_CODE  */
#line 124 "../src/parse/parser.ypp"
                            {
    find_or_add_gram(grams, "").pre_rule.push_back((yyvsp[0].semact));
}
#line 1267 "src/parse/parser.cc"
    break;

  case 19: /* rule: TOKEN_POST_RULE TOKEN_CODE  */
#line 127 "../src/parse/parser.ypp"
                             {
    find_or_add_gram(grams, "").post_rule.push_back((yyvsp[0].semact));
}
#line 1275 "src/parse/parser.cc"
    break;

  case 20: /* rule: TOKEN_CLIST trailexpr ccode  */
#line 130 "../src/parse/parser.ypp"
                              {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).rules.push_back({(yyvsp[-1].regexp), (yyvsp[0].semact)});
    }
    ast.temp_condlist.clear();
}
#line 1286 "src/parse/parser.cc"
    break;

  case 21: /* rule: TOKEN_CLIST '*' ccode  */
#line 136 "../src/parse/parser.ypp"
                        {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).defs.push_back((yyvsp[0].semact));
    }
    ast.temp_condlist.clear();
}
#line 1297 "src/parse/parser.cc"
    break;

  case 22: /* rule: TOKEN_CLIST '$' ccode  */
#line 142 "../src/parse/parser.ypp"
                        {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).eofs.push_back((yyvsp[0].semact));
    }
    ast.temp_condlist.clear();
}
#line 1308 "src/parse/parser.cc"
    break;

  case 23: /* rule: TOKEN_CLIST TOKEN_ENTRY ccode  */
#line 148 "../src/parse/parser.ypp"
                                {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).entry.push_back((yyvsp[0].semact));
    }
    ast.temp_condlist.clear();
}
#line 1319 "src/parse/parser.cc"
    break;

  case 24: /* rule: TOKEN_CLIST TOKEN_PRE_RULE ccode  */
#line 154 "../src/parse/parser.ypp"
                                   {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).pre_rule.push_back((yyvsp[0].semact));
    }
    ast.temp_condlist.clear();
}
#line 1330 "src/parse/parser.cc"
    break;

  case 25: /* rule: TOKEN_CLIST TOKEN_POST_RULE ccode  */
#line 160 "../src/parse/parser.ypp"
                                    {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).post_rule.push_back((yyvsp[0].semact));
    }
    ast.temp_condlist.clear();
}
#line 1341 "src/parse/parser.cc"
    break;

  case 26: /* rule: TOKEN_CPRE_RULE TOKEN_CODE  */
#line 166 "../src/parse/parser.ypp"
                             {
    for (const std::string& cond : ast.temp_condlist) {
        find_or_add_gram(grams, cond).pre_rule.push_back((yyvsp[0].semact));
    }
    ast.temp_condlist.clear();
}
#line 1352 "src/parse/parser.cc"
    break;

  case 27: /* rule: TOKEN_CZERO ccode  */
#line 172 "../src/parse/parser.ypp"
                    {
    const AstNode* r = ast.nil(input.tok_loc());
    find_or_add_gram(grams, ZERO_COND).rules.push_back({r, (yyvsp[0].semact)});
    ast.temp_condlist.clear();
}
#line 1362 "src/parse/parser.cc"
    break;

  case 29: /* ccode: TOKEN_CNEXT TOKEN_CODE  */
#line 180 "../src/parse/parser.ypp"
                         {
    (yyval.semact) = (yyvsp[0].semact);
    // parser needs to to update condition, but for the rest of the code actions are immutable
    const_cast<SemAct*>((yyval.semact))->cond = (yyvsp[-1].cstr); 
}
#line 1372 "src/parse/parser.cc"
    break;

  case 30: /* ccode: TOKEN_CJUMP  */
#line 185 "../src/parse/parser.ypp"
              {
    (yyval.semact) = ast.sem_act(input.tok_loc(), nullptr, (yyvsp[0].cstr), true);
}
#line 1380 "src/parse/parser.cc"
    break;

  case 31: /* trailexpr: expr  */
#line 190 "../src/parse/parser.ypp"
       { (yyval.regexp) = ast.cap((yyvsp[0].regexp), CAPTURE_IF_NOT_INVERTED); }
#line 1386 "src/parse/parser.cc"
    break;

  case 32: /* trailexpr: expr '/' expr  */
#line 191 "../src/parse/parser.ypp"
                {
    (yyval.regexp) = ast.cat(ast.cap((yyvsp[-2].regexp), CAPTURE_IF_NOT_INVERTED),
                 ast.cat(ast.tag(input.tok_loc(), nullptr, false), (yyvsp[0].regexp)));
}
#line 1395 "src/parse/parser.cc"
    break;

  case 34: /* expr: expr '|' diff  */
#line 198 "../src/parse/parser.ypp"
                { (yyval.regexp) = ast.alt((yyvsp[-2].regexp), (yyvsp[0].regexp)); }
#line 1401 "src/parse/parser.cc"
    break;

  case 36: /* diff: diff '\\' term  */
#line 203 "../src/parse/parser.ypp"
                 { (yyval.regexp) = ast.diff((yyvsp[-2].regexp), (yyvsp[0].regexp)); }
#line 1407 "src/parse/parser.cc"
    break;

  case 38: /* term: factor term  */
#line 209 "../src/parse/parser.ypp"
              { (yyval.regexp) = ast.cat((yyvsp[-1].regexp), (yyvsp[0].regexp)); }
#line 1413 "src/parse/parser.cc"
    break;

  case 40: /* factor: primary closes  */
#line 214 "../src/parse/parser.ypp"
                 {
    switch((yyvsp[0].op)) {
    case '*':
        (yyval.regexp) = ast.iter((yyvsp[-1].regexp), 0, Ast::MANY);
        break;
    case '+':
        (yyval.regexp) = ast.iter((yyvsp[-1].regexp), 1, Ast::MANY);
        break;
    case '?':
        (yyval.regexp) = ast.iter((yyvsp[-1].regexp), 0, 1);
        break;
    }
}
#line 1431 "src/parse/parser.cc"
    break;

  case 41: /* factor: primary TOKEN_CLOSESIZE  */
#line 227 "../src/parse/parser.ypp"
                          {
    (yyval.regexp) = ast.iter((yyvsp[-1].regexp), (yyvsp[0].bounds).min, (yyvsp[0].bounds).max);
}
#line 1439 "src/parse/parser.cc"
    break;

  case 43: /* closes: closes close  */
#line 234 "../src/parse/parser.ypp"
               { (yyval.op) = ((yyvsp[-1].op) == (yyvsp[0].op)) ? (yyvsp[-1].op) : '*'; }
#line 1445 "src/parse/parser.cc"
    break;

  case 44: /* close: '*'  */
#line 238 "../src/parse/parser.ypp"
      { (yyval.op) = '*'; }
#line 1451 "src/parse/parser.cc"
    break;

  case 45: /* close: '+'  */
#line 239 "../src/parse/parser.ypp"
      { (yyval.op) = '+'; }
#line 1457 "src/parse/parser.cc"
    break;

  case 46: /* close: '?'  */
#line 240 "../src/parse/parser.ypp"
      { (yyval.op) = '?'; }
#line 1463 "src/parse/parser.cc"
    break;

  case 48: /* primary: TOKEN_ID  */
#line 245 "../src/parse/parser.ypp"
           {
    (yyval.regexp) = find_def(opts.symtab, (yyvsp[0].cstr));
    if ((yyval.regexp) == nullptr) {
        input.error_at_tok("undefined symbol '%s'", (yyvsp[0].cstr));
        YYABORT;
    } else if (Ast::needs_wrap((yyval.regexp))) {
        (yyval.regexp) = ast.cap((yyval.regexp), NO_CAPTURE);
    }
}
#line 1477 "src/parse/parser.cc"
    break;

  case 49: /* primary: '(' expr ')'  */
#line 254 "../src/parse/parser.ypp"
                            { (yyval.regexp) = ast.cap((yyvsp[-1].regexp), CAPTURE_IF_NOT_INVERTED); }
#line 1483 "src/parse/parser.cc"
    break;

  case 50: /* primary: TOKEN_LPAREN_NEG expr ')'  */
#line 255 "../src/parse/parser.ypp"
                            { (yyval.regexp) = ast.cap((yyvsp[-1].regexp), CAPTURE_IF_INVERTED); }
#line 1489 "src/parse/parser.cc"
    break;


#line 1493 "src/parse/parser.cc"

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
  yytoken = yychar == RE2C_EMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (input, ast, opts, grams, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= RE2C_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == RE2C_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, input, ast, opts, grams);
          yychar = RE2C_EMPTY;
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, input, ast, opts, grams);
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
  yyerror (input, ast, opts, grams, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != RE2C_EMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, input, ast, opts, grams);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, input, ast, opts, grams);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 258 "../src/parse/parser.ypp"


#pragma GCC diagnostic pop

extern "C" {
    static void yyerror(Input& input, Ast&, Opt&, AstGrams&, const char* s) {
        input.error_at_cur("%s", s);
    }

    static int yylex(YYSTYPE* yylval, Input& input, Ast& ast, Opt&, AstGrams&) {
        int token;
        return input.lex_block(yylval, ast, token) == Ret::OK ? token : TOKEN_ERROR;
    }
}

namespace re2c {

Ret parse(Input& input, Ast& ast, Opt& opts, AstGrams& grams) {
    return yyparse(input, ast, opts, grams) == 0 ? Ret::OK : Ret::FAIL;
}

} // namespace re2c
