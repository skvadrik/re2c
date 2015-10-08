/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

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



#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>

#include "config.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/ir/bytecode/bytecode.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/regexp/encoding/range_suffix.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/globals.h"
#include "src/parse/code.h"
#include "src/parse/extop.h"
#include "src/parse/parser.h"
#include "src/util/c99_stdint.h"
#include "src/util/smart_ptr.h"

#define YYMALLOC malloc
#define YYFREE free

using namespace re2c;

extern "C"
{
int yylex();
void yyerror(const char*);
}

static counter_t<rule_rank_t> rank_counter;
static std::vector<std::string> condnames;
static re2c::SpecMap  specMap;
static Spec spec;
static RuleOp *specNone = NULL;
static RuleOpList       specStar;
static RuleOp * star_default = NULL;
static Scanner          *in = NULL;
static Scanner::ParseMode  parseMode;
static SetupMap            ruleSetupMap;
static bool                foundRules;
static symbol_table_t symbol_table;

/* Bison version 1.875 emits a definition that is not working
 * with several g++ version. Hence we disable it here.
 */
#if defined(__GNUC__)
#define __attribute__(x)
#endif

void context_check(CondList *clist)
{
	if (!opts->cFlag)
	{
		delete clist;
		in->fatal("conditions are only allowed when using -c switch");
	}
}

void context_none(CondList *clist)
{
	delete clist;
	context_check(NULL);
	in->fatal("no expression specified");
}

void context_rule
	( CondList * clist
	, const Loc & loc
	, RegExp * expr
	, RegExp * look
	, const Code * code
	, const std::string * newcond
	)
{
	context_check(clist);
	const RegExp::InsAccess ins_access = clist->size() > 1
		? RegExp::PRIVATE
		: RegExp::SHARED;
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		if (specMap.find(*it) == specMap.end())
		{
			condnames.push_back (*it);
		}

		RuleOp * rule = new RuleOp
			( loc
			, expr
			, look
			, rank_counter.next ()
			, ins_access
			, code
			, newcond
			);
		specMap[*it].add (rule);
	}
	delete clist;
	delete newcond;
}

void setup_rule(CondList *clist, const Code * code)
{
	assert(clist);
	assert(code);
	context_check(clist);
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		if (ruleSetupMap.find(*it) != ruleSetupMap.end())
		{
			in->fatalf_at(code->loc.line, "code to setup rule '%s' is already defined", it->c_str());
		}
		ruleSetupMap[*it] = std::make_pair(code->loc.line, code->text);
	}
	delete clist;
}

void default_rule(CondList *clist, const Code * code)
{
	assert(clist);
	assert(code);
	context_check(clist);
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		RuleOp * def = new RuleOp
			( code->loc
			, in->mkDefault ()
			, new NullOp
			, rule_rank_t::def ()
			, RegExp::SHARED
			, code
			, NULL
			);
		if (!specMap[*it].add_def (def))
		{
			in->fatalf_at(code->loc.line, "code to default rule '%s' is already defined", it->c_str());
		}
	}
	delete clist;
}




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
     CLOSE = 258,
     CLOSESIZE = 259,
     CODE = 260,
     CONF_CONDPREFIX = 261,
     CONF_CONDENUMPREFIX = 262,
     CONF_COND_DIVIDER = 263,
     CONF_COND_DIVIDER_COND = 264,
     CONF_COND_GOTO = 265,
     CONF_COND_GOTO_COND = 266,
     CONF_CGOTO_THRESHOLD = 267,
     CONF_DEFINE_YYBACKUP = 268,
     CONF_DEFINE_YYBACKUPCTX = 269,
     CONF_DEFINE_YYCONDTYPE = 270,
     CONF_DEFINE_YYCTXMARKER = 271,
     CONF_DEFINE_YYCTYPE = 272,
     CONF_DEFINE_YYCURSOR = 273,
     CONF_DEFINE_YYDEBUG = 274,
     CONF_DEFINE_YYFILL = 275,
     CONF_DEFINE_YYFILL_NAKED = 276,
     CONF_DEFINE_YYFILL_LEN = 277,
     CONF_DEFINE_YYGETCONDITION = 278,
     CONF_DEFINE_YYGETCONDITION_NAKED = 279,
     CONF_DEFINE_YYGETSTATE = 280,
     CONF_DEFINE_YYGETSTATE_NAKED = 281,
     CONF_DEFINE_YYLESSTHAN = 282,
     CONF_DEFINE_YYLIMIT = 283,
     CONF_DEFINE_YYMARKER = 284,
     CONF_DEFINE_YYPEEK = 285,
     CONF_DEFINE_YYRESTORE = 286,
     CONF_DEFINE_YYRESTORECTX = 287,
     CONF_DEFINE_YYSETCONDITION = 288,
     CONF_DEFINE_YYSETCONDITION_COND = 289,
     CONF_DEFINE_YYSETCONDITION_NAKED = 290,
     CONF_DEFINE_YYSETSTATE = 291,
     CONF_DEFINE_YYSETSTATE_NAKED = 292,
     CONF_DEFINE_YYSETSTATE_STATE = 293,
     CONF_DEFINE_YYSKIP = 294,
     CONF_FLAGS = 295,
     CONF_INDENT_STRING = 296,
     CONF_INDENT_TOP = 297,
     CONF_LABEL_YYFILLLABEL = 298,
     CONF_LABEL_YYNEXT = 299,
     CONF_LABELPREFIX = 300,
     CONF_STARTLABEL = 301,
     CONF_STATE_ABORT = 302,
     CONF_STATE_NEXTLABEL = 303,
     CONF_VARIABLE_YYACCEPT = 304,
     CONF_VARIABLE_YYBM = 305,
     CONF_VARIABLE_YYCH = 306,
     CONF_VARIABLE_YYCTABLE = 307,
     CONF_VARIABLE_YYSTABLE = 308,
     CONF_VARIABLE_YYTARGET = 309,
     CONF_YYBM_HEX = 310,
     CONF_YYCH_CONVERSION = 311,
     CONF_YYCH_EMIT = 312,
     CONF_YYFILL_CHECK = 313,
     CONF_YYFILL_ENABLE = 314,
     CONF_YYFILL_PARAMETER = 315,
     ID = 316,
     FID = 317,
     FID_END = 318,
     NOCOND = 319,
     NUM = 320,
     REGEXP = 321,
     SETUP = 322,
     STAR = 323,
     STRING = 324
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


	re2c::RegExp * regexp;
	const re2c::Code * code;
	char op;
	int32_t num;
	re2c::ExtOp extop;
	std::string * str;
	re2c::CondList * clist;
	re2c::Enc::type_t enc;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */



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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   336

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNRULES -- Number of states.  */
#define YYNSTATES  258

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      79,    80,     2,     2,    76,     2,     2,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    75,    71,
      73,    70,    74,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    78,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    77,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    15,    19,    24,    28,
      32,    36,    40,    44,    48,    52,    56,    60,    64,    68,
      72,    76,    80,    84,    88,    92,    96,   100,   104,   108,
     112,   116,   120,   124,   128,   132,   136,   140,   144,   148,
     152,   156,   160,   164,   168,   172,   176,   180,   184,   188,
     192,   196,   200,   204,   208,   212,   216,   220,   224,   228,
     232,   236,   240,   244,   248,   252,   256,   259,   267,   275,
     282,   289,   295,   303,   311,   318,   325,   331,   335,   339,
     344,   349,   350,   352,   354,   358,   359,   363,   364,   367,
     369,   373,   375,   379,   381,   384,   386,   389,   392,   394,
     396,   399,   402,   404,   406
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      82,     0,    -1,    -1,    82,    84,    -1,    82,    83,    -1,
      61,    70,    89,    71,    -1,    62,    89,    63,    -1,    61,
      70,    89,    72,    -1,    62,    89,    72,    -1,     6,    69,
      71,    -1,     7,    69,    71,    -1,     8,    69,    71,    -1,
       9,    69,    71,    -1,    10,    69,    71,    -1,    11,    69,
      71,    -1,    12,    65,    71,    -1,    13,    69,    71,    -1,
      14,    69,    71,    -1,    15,    69,    71,    -1,    16,    69,
      71,    -1,    17,    69,    71,    -1,    18,    69,    71,    -1,
      19,    69,    71,    -1,    20,    69,    71,    -1,    23,    69,
      71,    -1,    25,    69,    71,    -1,    27,    69,    71,    -1,
      28,    69,    71,    -1,    29,    69,    71,    -1,    30,    69,
      71,    -1,    31,    69,    71,    -1,    32,    69,    71,    -1,
      33,    69,    71,    -1,    35,    65,    71,    -1,    36,    69,
      71,    -1,    39,    69,    71,    -1,    21,    65,    71,    -1,
      22,    69,    71,    -1,    24,    65,    71,    -1,    26,    65,
      71,    -1,    34,    69,    71,    -1,    37,    65,    71,    -1,
      38,    69,    71,    -1,    40,    65,    71,    -1,    41,    69,
      71,    -1,    42,    65,    71,    -1,    43,    69,    71,    -1,
      44,    69,    71,    -1,    45,    69,    71,    -1,    46,    65,
      71,    -1,    46,    69,    71,    -1,    47,    65,    71,    -1,
      48,    65,    71,    -1,    49,    69,    71,    -1,    50,    69,
      71,    -1,    51,    69,    71,    -1,    52,    69,    71,    -1,
      53,    69,    71,    -1,    54,    69,    71,    -1,    55,    65,
      71,    -1,    56,    65,    71,    -1,    57,    65,    71,    -1,
      58,    65,    71,    -1,    59,    65,    71,    -1,    60,    65,
      71,    -1,    89,    88,     5,    -1,    68,     5,    -1,    73,
      85,    74,    89,    88,    87,     5,    -1,    73,    85,    74,
      89,    88,    75,    87,    -1,    73,    85,    74,    88,    87,
       5,    -1,    73,    85,    74,    88,    75,    87,    -1,    73,
      85,    74,    68,     5,    -1,    73,    68,    74,    89,    88,
      87,     5,    -1,    73,    68,    74,    89,    88,    75,    87,
      -1,    73,    68,    74,    88,    87,     5,    -1,    73,    68,
      74,    88,    75,    87,    -1,    73,    68,    74,    68,     5,
      -1,    64,    87,     5,    -1,    64,    75,    87,    -1,    67,
      68,    74,     5,    -1,    67,    85,    74,     5,    -1,    -1,
      86,    -1,    61,    -1,    86,    76,    61,    -1,    -1,    70,
      74,    61,    -1,    -1,    72,    89,    -1,    90,    -1,    89,
      77,    90,    -1,    91,    -1,    90,    78,    91,    -1,    92,
      -1,    91,    92,    -1,    94,    -1,    94,    93,    -1,    94,
       4,    -1,     3,    -1,    68,    -1,    93,     3,    -1,    93,
      68,    -1,    61,    -1,    66,    -1,    79,    89,    80,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   243,   243,   245,   249,   253,   262,   271,   275,   279,
     284,   289,   294,   299,   304,   309,   317,   322,   327,   332,
     337,   342,   347,   352,   357,   362,   367,   372,   377,   382,
     387,   392,   397,   402,   406,   411,   416,   420,   425,   429,
     433,   438,   442,   447,   460,   465,   473,   478,   483,   488,
     492,   497,   501,   505,   510,   515,   520,   525,   530,   535,
     539,   543,   547,   551,   555,   562,   579,   597,   601,   607,
     612,   618,   622,   637,   654,   659,   665,   681,   699,   719,
     725,   733,   736,   743,   749,   759,   762,   770,   773,   780,
     784,   791,   795,   802,   806,   813,   817,   832,   852,   856,
     860,   864,   871,   881,   885
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLOSE", "CLOSESIZE", "CODE",
  "CONF_CONDPREFIX", "CONF_CONDENUMPREFIX", "CONF_COND_DIVIDER",
  "CONF_COND_DIVIDER_COND", "CONF_COND_GOTO", "CONF_COND_GOTO_COND",
  "CONF_CGOTO_THRESHOLD", "CONF_DEFINE_YYBACKUP",
  "CONF_DEFINE_YYBACKUPCTX", "CONF_DEFINE_YYCONDTYPE",
  "CONF_DEFINE_YYCTXMARKER", "CONF_DEFINE_YYCTYPE", "CONF_DEFINE_YYCURSOR",
  "CONF_DEFINE_YYDEBUG", "CONF_DEFINE_YYFILL", "CONF_DEFINE_YYFILL_NAKED",
  "CONF_DEFINE_YYFILL_LEN", "CONF_DEFINE_YYGETCONDITION",
  "CONF_DEFINE_YYGETCONDITION_NAKED", "CONF_DEFINE_YYGETSTATE",
  "CONF_DEFINE_YYGETSTATE_NAKED", "CONF_DEFINE_YYLESSTHAN",
  "CONF_DEFINE_YYLIMIT", "CONF_DEFINE_YYMARKER", "CONF_DEFINE_YYPEEK",
  "CONF_DEFINE_YYRESTORE", "CONF_DEFINE_YYRESTORECTX",
  "CONF_DEFINE_YYSETCONDITION", "CONF_DEFINE_YYSETCONDITION_COND",
  "CONF_DEFINE_YYSETCONDITION_NAKED", "CONF_DEFINE_YYSETSTATE",
  "CONF_DEFINE_YYSETSTATE_NAKED", "CONF_DEFINE_YYSETSTATE_STATE",
  "CONF_DEFINE_YYSKIP", "CONF_FLAGS", "CONF_INDENT_STRING",
  "CONF_INDENT_TOP", "CONF_LABEL_YYFILLLABEL", "CONF_LABEL_YYNEXT",
  "CONF_LABELPREFIX", "CONF_STARTLABEL", "CONF_STATE_ABORT",
  "CONF_STATE_NEXTLABEL", "CONF_VARIABLE_YYACCEPT", "CONF_VARIABLE_YYBM",
  "CONF_VARIABLE_YYCH", "CONF_VARIABLE_YYCTABLE", "CONF_VARIABLE_YYSTABLE",
  "CONF_VARIABLE_YYTARGET", "CONF_YYBM_HEX", "CONF_YYCH_CONVERSION",
  "CONF_YYCH_EMIT", "CONF_YYFILL_CHECK", "CONF_YYFILL_ENABLE",
  "CONF_YYFILL_PARAMETER", "ID", "FID", "FID_END", "NOCOND", "NUM",
  "REGEXP", "SETUP", "STAR", "STRING", "'='", "';'", "'/'", "'<'", "'>'",
  "':'", "','", "'|'", "'\\\\'", "'('", "')'", "$accept", "spec", "decl",
  "rule", "cond", "clist", "newcond", "look", "expr", "diff", "term",
  "factor", "close", "primary", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      61,    59,    47,    60,    62,    58,    44,   124,    92,    40,
      41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    92,    92,    92,    93,    93,
      93,    93,    94,    94,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     7,     7,     6,
       6,     5,     7,     7,     6,     6,     5,     3,     3,     4,
       4,     0,     1,     1,     3,     0,     3,     0,     2,     1,
       3,     1,     3,     1,     2,     1,     2,     2,     1,     1,
       2,     2,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,     0,
      85,   103,    81,     0,    81,     0,     4,     3,    87,    89,
      91,    93,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102,     0,     0,    85,     0,    83,     0,     0,    82,    66,
       0,     0,     0,     0,     0,     0,     0,    94,    98,    97,
      99,    96,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    36,    37,    24,
      38,    25,    39,    26,    27,    28,    29,    30,    31,    32,
      40,    33,    34,    41,    42,    35,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,     0,     6,
       8,     0,    78,    77,     0,     0,     0,    87,    87,   104,
      88,    90,    65,    92,   100,   101,     5,     7,    86,    79,
      80,    84,     0,    85,    87,     0,    85,    87,    76,    85,
       0,    85,    71,    85,     0,    85,    75,    74,    85,     0,
      70,    69,    85,     0,    73,    72,    68,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    66,    67,   137,   138,   134,   145,    68,    69,
      70,    71,   151,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -141
static const yytype_int16 yypact[] =
{
    -141,     7,  -141,    10,    12,    38,    44,    57,    62,    51,
      63,    65,    66,    67,    70,    71,    72,    73,    78,    75,
      76,    81,    79,    82,    80,    83,    84,    86,    87,    88,
      91,    92,    85,    93,    98,    95,    96,   101,    99,   102,
     100,   103,   104,    64,   105,   106,   107,   108,   109,   110,
     111,   112,   117,   118,   119,   120,   121,   122,    29,    22,
     -66,  -141,   -58,   133,    30,    22,  -141,  -141,    34,    97,
      22,  -141,     8,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,    22,
    -141,    32,    77,   181,   183,  -141,   115,   116,   180,  -141,
     184,   185,   -72,    22,    22,   186,    22,  -141,  -141,  -141,
    -141,    69,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,    47,  -141,
    -141,   113,  -141,  -141,   187,   188,   191,    21,    24,  -141,
     189,    97,  -141,    22,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,   199,    45,    34,   248,    52,    34,  -141,   181,
     249,    53,  -141,   181,   250,    55,  -141,  -141,   181,   252,
    -141,  -141,   181,   255,  -141,  -141,  -141,  -141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,  -141,  -141,   197,  -141,  -131,  -140,   -59,   182,
     190,   -69,  -141,  -141
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     131,   147,   212,   135,   132,   144,   142,     2,   219,   133,
     136,   148,   149,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
     208,    60,   224,    61,    62,    63,   150,   233,   236,    73,
      64,    74,   130,   130,   220,   130,    65,    61,    61,   232,
      61,   135,   235,   143,   241,   209,   143,   245,   140,   129,
      65,    65,   240,    65,   210,   244,   143,    75,   246,   144,
     249,   144,   250,    76,   253,   132,    79,   254,   226,   227,
     239,   256,   132,   132,   144,   132,    77,   243,   248,   113,
     252,    78,    80,   114,    81,    82,    83,   225,   139,    84,
      85,    86,    87,    88,    89,    90,    91,    93,    92,    94,
     102,   211,    95,    96,   147,    97,    98,    99,   234,   237,
     100,   101,   103,   104,   105,   106,   107,   109,   108,   110,
     115,   116,   111,   112,   228,   146,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   213,   214,
     215,   222,   229,   230,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   238,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   132,   231,   242,   247,   251,   216,   255,   217,   218,
     257,   141,     0,     0,     0,     0,   144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   221,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   223
};

static const yytype_int16 yycheck[] =
{
      59,    70,   133,    61,    70,    77,    65,     0,    80,    75,
      68,     3,     4,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
     129,    64,     3,    66,    67,    68,    68,   217,   218,    69,
      73,    69,    61,    61,   143,    61,    79,    66,    66,    68,
      66,    61,    68,    72,   234,    63,    72,   237,    68,    70,
      79,    79,   233,    79,    72,   236,    72,    69,   239,    77,
     241,    77,   243,    69,   245,    70,    65,   248,    71,    72,
      75,   252,    70,    70,    77,    70,    69,    75,    75,    65,
      75,    69,    69,    69,    69,    69,    69,    68,     5,    69,
      69,    69,    69,    65,    69,    69,    65,    65,    69,    69,
      65,    74,    69,    69,   223,    69,    69,    69,   217,   218,
      69,    69,    69,    65,    69,    69,    65,    65,    69,    69,
      65,    65,    69,    69,    61,    78,    69,    69,    69,    69,
      69,    69,    65,    65,    65,    65,    65,    65,     5,    74,
      74,     5,     5,     5,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,     5,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    70,    61,     5,     5,     5,    76,     5,    74,    74,
       5,    64,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   146
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      64,    66,    67,    68,    73,    79,    83,    84,    89,    90,
      91,    92,    94,    69,    69,    69,    69,    69,    69,    65,
      69,    69,    69,    69,    69,    69,    69,    69,    65,    69,
      69,    65,    69,    65,    69,    69,    69,    69,    69,    69,
      69,    69,    65,    69,    65,    69,    69,    65,    69,    65,
      69,    69,    69,    65,    69,    65,    65,    69,    69,    69,
      69,    69,    69,    65,    65,    65,    65,    65,    65,    70,
      61,    89,    70,    75,    87,    61,    68,    85,    86,     5,
      68,    85,    89,    72,    77,    88,    78,    92,     3,     4,
      68,    93,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    89,    63,
      72,    74,    87,     5,    74,    74,    76,    74,    74,    80,
      89,    90,     5,    91,     3,    68,    71,    72,    61,     5,
       5,    61,    68,    88,    89,    68,    88,    89,     5,    75,
      87,    88,     5,    75,    87,    88,    87,     5,    75,    87,
      87,     5,    75,    87,    87,     5,    87,     5
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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

    {
		;}
    break;

  case 3:

    {
			foundRules = true;
		;}
    break;

  case 5:

    {
			if (!symbol_table.insert (std::make_pair (* (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].regexp))).second)
			{
				in->fatal("sym already defined");
			}
			delete (yyvsp[(1) - (4)].str);
			(yyvsp[(3) - (4)].regexp)->ins_access = RegExp::PRIVATE;
		;}
    break;

  case 6:

    {
			if (!symbol_table.insert (std::make_pair (* (yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].regexp))).second)
			{
				in->fatal("sym already defined");
			}
			delete (yyvsp[(1) - (3)].str);
			(yyvsp[(2) - (3)].regexp)->ins_access = RegExp::PRIVATE;
		;}
    break;

  case 7:

    {
			in->fatal("trailing contexts are not allowed in named definitions");
		;}
    break;

  case 8:

    {
			in->fatal("trailing contexts are not allowed in named definitions");
		;}
    break;

  case 9:

    {
		opts.set_condPrefix (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 10:

    {
		opts.set_condEnumPrefix (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 11:

    {
		opts.set_condDivider (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 12:

    {
		opts.set_condDividerParam (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 13:

    {
		opts.set_condGoto (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 14:

    {
		opts.set_condGotoParam (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 15:

    {
		if ((yyvsp[(2) - (3)].num) < 0)
		{
			in->fatal ("configuration 'cgoto:threshold' must be nonnegative");
		}
		opts.set_cGotoThreshold (static_cast<uint32_t> ((yyvsp[(2) - (3)].num)));
	;}
    break;

  case 16:

    {
		opts.set_yybackup (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 17:

    {
		opts.set_yybackupctx (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 18:

    {
		opts.set_yycondtype (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 19:

    {
		opts.set_yyctxmarker (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 20:

    {
		opts.set_yyctype (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 21:

    {
		opts.set_yycursor (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 22:

    {
		opts.set_yydebug (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 23:

    {
		opts.set_fill (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 24:

    {
		opts.set_cond_get (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 25:

    {
		opts.set_state_get (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 26:

    {
		opts.set_yylessthan (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 27:

    {
		opts.set_yylimit (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 28:

    {
		opts.set_yymarker (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 29:

    {
		opts.set_yypeek (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 30:

    {
		opts.set_yyrestore (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 31:

    {
		opts.set_yyrestorectx (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 32:

    {
		opts.set_cond_set (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 33:

    {
		opts.set_cond_set_naked ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 34:

    {
		opts.set_state_set (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 35:

    {
		opts.set_yyskip (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 36:

    {
		opts.set_fill_naked ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 37:

    {
		opts.set_fill_arg (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 38:

    {
		opts.set_cond_get_naked ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 39:

    {
		opts.set_state_get_naked ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 40:

    {
		opts.set_cond_set_arg (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 41:

    {
		opts.set_state_set_naked ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 42:

    {
		opts.set_state_set_arg (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 43:

    {
		if ((yyvsp[(2) - (3)].num) == 0)
		{
			opts.unset_encoding ((yyvsp[(1) - (3)].enc));
		}
		else if (!opts.set_encoding ((yyvsp[(1) - (3)].enc)))
		{
			in->fatalf ("Cannot set %s encoding: please reset %s encoding first"
				, Enc::name ((yyvsp[(1) - (3)].enc))
				, Enc::name (opts->encoding.type ()));
		}
	;}
    break;

  case 44:

    {
		opts.set_indString (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 45:

    {
		if ((yyvsp[(2) - (3)].num) < 0)
		{
			in->fatal ("configuration 'indent:top' must be nonnegative");
		}
		opts.set_topIndent (static_cast<uint32_t> ((yyvsp[(2) - (3)].num)));
	;}
    break;

  case 46:

    {
		opts.set_yyfilllabel (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 47:

    {
		opts.set_yynext (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 48:

    {
		opts.set_labelPrefix (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 49:

    {
		in->out.set_force_start_label ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 50:

    {
		in->out.set_user_start_label (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 51:

    {
		opts.set_bUseStateAbort ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 52:

    {
		opts.set_bUseStateNext ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 53:

    {
		opts.set_yyaccept (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 54:

    {
		opts.set_yybm (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 55:

    {
		opts.set_yych (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 56:

    {
		opts.set_yyctable (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 57:

    {
		// deprecated
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 58:

    {
		opts.set_yytarget (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 59:

    {
		opts.set_yybmHexTable ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 60:

    {
		opts.set_yychConversion ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 61:

    {
		opts.set_bEmitYYCh ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 62:

    {
		opts.set_fill_check ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 63:

    {
		opts.set_fill_use ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 64:

    {
		opts.set_fill_arg_use ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 65:

    {
			if (opts->cFlag)
			{
				in->fatal("condition or '<*>' required when using -c switch");
			}
			RuleOp * rule = new RuleOp
				( (yyvsp[(3) - (3)].code)->loc
				, (yyvsp[(1) - (3)].regexp)
				, (yyvsp[(2) - (3)].regexp)
				, rank_counter.next ()
				, RegExp::SHARED
				, (yyvsp[(3) - (3)].code)
				, NULL
				);
			spec.add (rule);
		;}
    break;

  case 66:

    {
			if (opts->cFlag)
				in->fatal("condition or '<*>' required when using -c switch");
			RuleOp * def = new RuleOp
				( (yyvsp[(2) - (2)].code)->loc
				, in->mkDefault ()
				, new NullOp
				, rule_rank_t::def ()
				, RegExp::SHARED
				, (yyvsp[(2) - (2)].code)
				, NULL
				);
			if (!spec.add_def (def))
			{
				in->fatal("code to default rule is already defined");
			}
		;}
    break;

  case 67:

    {
			context_rule ((yyvsp[(2) - (7)].clist), (yyvsp[(7) - (7)].code)->loc, (yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), (yyvsp[(7) - (7)].code), (yyvsp[(6) - (7)].str));
		;}
    break;

  case 68:

    {
			assert((yyvsp[(7) - (7)].str));
			Loc loc (in->get_fname (), in->get_cline ());
			context_rule ((yyvsp[(2) - (7)].clist), loc, (yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), NULL, (yyvsp[(7) - (7)].str));
		;}
    break;

  case 69:

    {
			context_none((yyvsp[(2) - (6)].clist));
			delete (yyvsp[(5) - (6)].str);
		;}
    break;

  case 70:

    {
			assert((yyvsp[(6) - (6)].str));
			context_none((yyvsp[(2) - (6)].clist));
			delete (yyvsp[(6) - (6)].str);
		;}
    break;

  case 71:

    {
			default_rule((yyvsp[(2) - (5)].clist), (yyvsp[(5) - (5)].code));
		;}
    break;

  case 72:

    {
			context_check(NULL);
			RuleOp * rule = new RuleOp
				( (yyvsp[(7) - (7)].code)->loc
				, (yyvsp[(4) - (7)].regexp)
				, (yyvsp[(5) - (7)].regexp)
				, rank_counter.next ()
				, RegExp::PRIVATE
				, (yyvsp[(7) - (7)].code)
				, (yyvsp[(6) - (7)].str)
				);
			specStar.push_back (rule);
			delete (yyvsp[(6) - (7)].str);
		;}
    break;

  case 73:

    {
			assert((yyvsp[(7) - (7)].str));
			context_check(NULL);
			Loc loc (in->get_fname (), in->get_cline ());
			RuleOp * rule = new RuleOp
				( loc
				, (yyvsp[(4) - (7)].regexp)
				, (yyvsp[(5) - (7)].regexp)
				, rank_counter.next ()
				, RegExp::PRIVATE
				, NULL
				, (yyvsp[(7) - (7)].str)
				);
			specStar.push_back (rule);
			delete (yyvsp[(7) - (7)].str);
		;}
    break;

  case 74:

    {
			context_none(NULL);
			delete (yyvsp[(5) - (6)].str);
		;}
    break;

  case 75:

    {
			assert((yyvsp[(6) - (6)].str));
			context_none(NULL);
			delete (yyvsp[(6) - (6)].str);
		;}
    break;

  case 76:

    {
			if (star_default)
			{
				in->fatal ("code to default rule '*' is already defined");
			}
			star_default = new RuleOp
				( (yyvsp[(5) - (5)].code)->loc
				, in->mkDefault ()
				, new NullOp
				, rule_rank_t::def ()
				, RegExp::PRIVATE
				, (yyvsp[(5) - (5)].code)
				, NULL
				);
		;}
    break;

  case 77:

    {
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			(yyval.regexp) = specNone = new RuleOp
				( (yyvsp[(3) - (3)].code)->loc
				, new NullOp
				, new NullOp
				, rank_counter.next ()
				, RegExp::SHARED
				, (yyvsp[(3) - (3)].code)
				, (yyvsp[(2) - (3)].str)
				);
			delete (yyvsp[(2) - (3)].str);
		;}
    break;

  case 78:

    {
			assert((yyvsp[(3) - (3)].str));
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			Loc loc (in->get_fname (), in->get_cline ());
			(yyval.regexp) = specNone = new RuleOp
				( loc
				, new NullOp
				, new NullOp
				, rank_counter.next ()
				, RegExp::SHARED
				, NULL
				, (yyvsp[(3) - (3)].str)
				);
			delete (yyvsp[(3) - (3)].str);
		;}
    break;

  case 79:

    {
			CondList *clist = new CondList();
			clist->insert("*");
			setup_rule(clist, (yyvsp[(4) - (4)].code));
		;}
    break;

  case 80:

    {
			setup_rule((yyvsp[(2) - (4)].clist), (yyvsp[(4) - (4)].code));
		;}
    break;

  case 81:

    {
			in->fatal("unnamed condition not supported");
		;}
    break;

  case 82:

    {
			(yyval.clist) = (yyvsp[(1) - (1)].clist);
		;}
    break;

  case 83:

    {
			(yyval.clist) = new CondList();
			(yyval.clist)->insert(* (yyvsp[(1) - (1)].str));
			delete (yyvsp[(1) - (1)].str);
		;}
    break;

  case 84:

    {
			(yyvsp[(1) - (3)].clist)->insert(* (yyvsp[(3) - (3)].str));
			delete (yyvsp[(3) - (3)].str);
			(yyval.clist) = (yyvsp[(1) - (3)].clist);
		;}
    break;

  case 85:

    {
			(yyval.str) = NULL;
		;}
    break;

  case 86:

    {
			(yyval.str) = (yyvsp[(3) - (3)].str);
		;}
    break;

  case 87:

    {
			(yyval.regexp) = new NullOp;
		;}
    break;

  case 88:

    {
			(yyval.regexp) = (yyvsp[(2) - (2)].regexp);
		;}
    break;

  case 89:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 90:

    {
			(yyval.regexp) = mkAlt((yyvsp[(1) - (3)].regexp), (yyvsp[(3) - (3)].regexp));
		;}
    break;

  case 91:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 92:

    {
			(yyval.regexp) = in->mkDiff((yyvsp[(1) - (3)].regexp), (yyvsp[(3) - (3)].regexp));
		;}
    break;

  case 93:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 94:

    {
			(yyval.regexp) = new CatOp((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].regexp));
		;}
    break;

  case 95:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 96:

    {
			switch((yyvsp[(2) - (2)].op))
			{
			case '*':
				(yyval.regexp) = mkAlt(new CloseOp((yyvsp[(1) - (2)].regexp)), new NullOp());
				break;
			case '+':
				(yyval.regexp) = new CloseOp((yyvsp[(1) - (2)].regexp));
				break;
			case '?':
				(yyval.regexp) = mkAlt((yyvsp[(1) - (2)].regexp), new NullOp());
				break;
			}
		;}
    break;

  case 97:

    {
			(yyvsp[(1) - (2)].regexp)->ins_access = RegExp::PRIVATE;
			if ((yyvsp[(2) - (2)].extop).max == UINT32_MAX)
			{
				(yyval.regexp) = repeat_from ((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].extop).min);
			}
			else if ((yyvsp[(2) - (2)].extop).min == (yyvsp[(2) - (2)].extop).max)
			{
				(yyval.regexp) = repeat ((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].extop).min);
			}
			else
			{
				(yyval.regexp) = repeat_from_to ((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].extop).min, (yyvsp[(2) - (2)].extop).max);
			}
			(yyval.regexp) = (yyval.regexp) ? (yyval.regexp) : new NullOp;
		;}
    break;

  case 98:

    {
			(yyval.op) = (yyvsp[(1) - (1)].op);
		;}
    break;

  case 99:

    {
			(yyval.op) = (yyvsp[(1) - (1)].op);
		;}
    break;

  case 100:

    {
			(yyval.op) = ((yyvsp[(1) - (2)].op) == (yyvsp[(2) - (2)].op)) ? (yyvsp[(1) - (2)].op) : '*';
		;}
    break;

  case 101:

    {
			(yyval.op) = ((yyvsp[(1) - (2)].op) == (yyvsp[(2) - (2)].op)) ? (yyvsp[(1) - (2)].op) : '*';
		;}
    break;

  case 102:

    {
			symbol_table_t::iterator i = symbol_table.find (* (yyvsp[(1) - (1)].str));
			delete (yyvsp[(1) - (1)].str);
			if (i == symbol_table.end ())
			{
				in->fatal("can't find symbol");
			}
			(yyval.regexp) = i->second;
		;}
    break;

  case 103:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 104:

    {
			(yyval.regexp) = (yyvsp[(2) - (3)].regexp);
		;}
    break;



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





extern "C" {
void yyerror(const char* s)
{
	in->fatal(s);
}

int yylex(){
	return in ? in->scan() : 0;
}
} // end extern "C"

namespace re2c
{

void parse(Scanner& i, Output & o)
{
	std::map<std::string, smart_ptr<DFA> >  dfa_map;
	ScannerState rules_state;

	in = &i;

	o.source.write_version_time ();
	o.source.write_line_info (in->get_cline (), in->get_fname ().c_str ());
	if (opts->target == opt_t::SKELETON)
	{
		Skeleton::emit_prolog (o.source);
	}

	Enc encodingOld = opts->encoding;
	
	while ((parseMode = i.echo()) != Scanner::Stop)
	{
		o.source.new_block ();
		bool bPrologBrace = false;
		ScannerState curr_state;

		i.save_state(curr_state);
		foundRules = false;

		if (opts->rFlag && parseMode == Scanner::Rules && dfa_map.size())
		{
			in->fatal("cannot have a second 'rules:re2c' block");
		}
		if (parseMode == Scanner::Reuse)
		{
			if (dfa_map.empty())
			{
				in->fatal("got 'use:re2c' without 'rules:re2c'");
			}
		}
		else if (parseMode == Scanner::Rules)
		{
			i.save_state(rules_state);
		}
		else
		{
			dfa_map.clear();
		}
		rank_counter.reset ();
		spec.clear ();
		in->set_in_parse(true);
		yyparse();
		in->set_in_parse(false);
		if (opts->rFlag && parseMode == Scanner::Reuse)
		{
			if (foundRules || opts->encoding != encodingOld)
			{
				// Re-parse rules
				parseMode = Scanner::Parse;
				i.restore_state(rules_state);
				i.reuse();
				dfa_map.clear();
				parse_cleanup();
				spec.clear ();
				rank_counter.reset ();
				in->set_in_parse(true);
				yyparse();
				in->set_in_parse(false);

				// Now append potential new rules
				i.restore_state(curr_state);
				parseMode = Scanner::Parse;
				in->set_in_parse(true);
				yyparse();
				in->set_in_parse(false);
			}
			encodingOld = opts->encoding;
		}
		o.source.set_block_line (in->get_cline ());
		uint32_t ind = opts->topIndent;
		if (opts->cFlag)
		{
			SpecMap::iterator it;
			SetupMap::const_iterator itRuleSetup;

			if (parseMode != Scanner::Reuse)
			{
				// <*> rules must have the lowest priority
				// now that all rules have been parsed, we can fix it
				for (RuleOpList::const_iterator itOp = specStar.begin(); itOp != specStar.end(); ++itOp)
				{
					(*itOp)->rank = rank_counter.next ();
				}
				// merge <*> rules to all conditions
				// note that all conditions use the same regexp for <*> rules,
				// but compile it separately because of RegExp::PRIVATE attribute
				for (it = specMap.begin(); it != specMap.end(); ++it)
				{
					for (RuleOpList::const_iterator itOp = specStar.begin(); itOp != specStar.end(); ++itOp)
					{
						it->second.addl (*itOp);
					}
					if (star_default)
					{
						it->second.addl (star_default);
					}
				}

				if (specNone)
				{
					specMap["0"].add (specNone);
					// Note that "0" inserts first, which is important.
					condnames.insert (condnames.begin (), "0");
				}
				o.types = condnames;
			}

			size_t nCount = specMap.size();

			for (it = specMap.begin(); it != specMap.end(); ++it)
			{
				if (parseMode != Scanner::Reuse)
				{
					itRuleSetup = ruleSetupMap.find(it->first);				
					if (itRuleSetup != ruleSetupMap.end())
					{
						yySetupRule = itRuleSetup->second.second;
					}
					else
					{
						itRuleSetup = ruleSetupMap.find("*");
						if (itRuleSetup != ruleSetupMap.end())
						{
							yySetupRule = itRuleSetup->second.second;
						}
						else
						{
							yySetupRule = "";
						}
					}

					dfa_map[it->first] = genCode(it->second, o, it->first, opts->encoding.nCodeUnits ());
				}
				if (parseMode != Scanner::Rules && dfa_map.find(it->first) != dfa_map.end())
				{
					dfa_map[it->first]->emit(o, ind, !--nCount, bPrologBrace);
				}
			}
		}
		else
		{
			if (spec.re || !dfa_map.empty())
			{
				if (parseMode != Scanner::Reuse)
				{
					dfa_map[""] = genCode(spec, o, "", opts->encoding.nCodeUnits ());
				}
				if (parseMode != Scanner::Rules && dfa_map.find("") != dfa_map.end())
				{
					dfa_map[""]->emit(o, ind, 0, bPrologBrace);
				}
			}
		}
		o.source.write_line_info (in->get_cline (), in->get_fname ().c_str ());
		/* restore original char handling mode*/
		opts.reset_encoding (encodingOld);
	}

	if (opts->cFlag)
	{
		SetupMap::const_iterator itRuleSetup;
		for (itRuleSetup = ruleSetupMap.begin(); itRuleSetup != ruleSetupMap.end(); ++itRuleSetup)
		{
			if (itRuleSetup->first != "*" && specMap.find(itRuleSetup->first) == specMap.end())
			{
				in->fatalf_at(itRuleSetup->second.first, "setup for non existing rule '%s' found", itRuleSetup->first.c_str());
			}
		}
		if (specMap.size() < ruleSetupMap.size())
		{
			uint32_t line = in->get_cline();
			itRuleSetup = ruleSetupMap.find("*");
			if (itRuleSetup != ruleSetupMap.end())
			{
				line = itRuleSetup->second.first;
			}
			in->fatalf_at(line, "setup for all rules with '*' not possible when all rules are setup explicitly");
		}
	}

	if (opts->target == opt_t::SKELETON)
	{
		Skeleton::emit_epilog (o.source, o.skeletons);
	}

	parse_cleanup();
	in = NULL;
}

void parse_cleanup()
{
	RegExp::vFreeList.clear();
	Range::vFreeList.clear();
	RangeSuffix::freeList.clear();
	Code::freelist.clear();
	symbol_table.clear ();
	condnames.clear ();
	specMap.clear();
	specStar.clear();
	star_default = NULL;
	specNone = NULL;
}

} // end namespace re2c

