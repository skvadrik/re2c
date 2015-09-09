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
static re2c::RegExpMap  specMap;
static RegExp           *spec = NULL, *specNone = NULL;
static RuleOpList       specStar;
static Scanner          *in = NULL;
static Scanner::ParseMode  parseMode;
static SetupMap            ruleSetupMap;
static const Code * ruleDefault = NULL;
static DefaultMap          ruleDefaultMap;
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
	if (!cFlag)
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
		RuleOp * rule = new RuleOp
			( loc
			, expr
			, look
			, rank_counter.next ()
			, ins_access
			, code
			, newcond
			);

		RegExpMap::iterator itRE = specMap.find(*it);

		if (itRE != specMap.end())
		{
			itRE->second = mkAlt(itRE->second, rule);
		}
		else
		{
			specMap[*it] = rule;
			condnames.push_back (*it);
		}
		
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
		if (ruleDefaultMap.find(*it) != ruleDefaultMap.end())
		{
			in->fatalf_at(code->loc.line, "code to default rule '%s' is already defined", it->c_str());
		}
		ruleDefaultMap[*it] = code;
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
     CONF = 261,
     CONF_CONDPREFIX = 262,
     CONF_CONDENUMPREFIX = 263,
     CONF_COND_DIVIDER = 264,
     CONF_COND_DIVIDER_COND = 265,
     CONF_COND_GOTO = 266,
     CONF_COND_GOTO_COND = 267,
     CONF_CGOTO_THRESHOLD = 268,
     CONF_DEFINE_YYBACKUP = 269,
     CONF_DEFINE_YYBACKUPCTX = 270,
     CONF_DEFINE_YYCONDTYPE = 271,
     CONF_DEFINE_YYCTXMARKER = 272,
     CONF_DEFINE_YYCTYPE = 273,
     CONF_DEFINE_YYCURSOR = 274,
     CONF_DEFINE_YYDEBUG = 275,
     CONF_DEFINE_YYFILL = 276,
     CONF_DEFINE_YYFILL_NAKED = 277,
     CONF_DEFINE_YYFILL_LEN = 278,
     CONF_DEFINE_YYGETCONDITION = 279,
     CONF_DEFINE_YYGETCONDITION_NAKED = 280,
     CONF_DEFINE_YYGETSTATE = 281,
     CONF_DEFINE_YYGETSTATE_NAKED = 282,
     CONF_DEFINE_YYLESSTHAN = 283,
     CONF_DEFINE_YYLIMIT = 284,
     CONF_DEFINE_YYMARKER = 285,
     CONF_DEFINE_YYPEEK = 286,
     CONF_DEFINE_YYRESTORE = 287,
     CONF_DEFINE_YYRESTORECTX = 288,
     CONF_DEFINE_YYSETCONDITION = 289,
     CONF_DEFINE_YYSETCONDITION_COND = 290,
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
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  177

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
     151,   159,   167,   174,   181,   187,   195,   203,   210,   217,
     223,   227,   231,   236,   241,   242,   244,   246,   250,   251,
     255,   256,   259,   261,   265,   267,   271,   273,   276,   278,
     281,   284,   286,   288,   291,   294,   296,   298
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      82,     0,    -1,    -1,    82,    84,    -1,    82,    83,    -1,
      61,    70,    89,    71,    -1,    62,    89,    63,    -1,    61,
      70,    89,    72,    -1,    62,    89,    72,    -1,     6,    69,
      71,    -1,     7,    69,    71,    -1,     8,    69,    71,    -1,
       9,    69,    71,    -1,    10,    69,    71,    -1,    11,    69,
      71,    -1,    12,    69,    71,    -1,    13,    65,    71,    -1,
      22,    65,    71,    -1,    23,    69,    71,    -1,    25,    65,
      71,    -1,    27,    65,    71,    -1,    35,    69,    71,    -1,
      37,    65,    71,    -1,    38,    69,    71,    -1,    40,    65,
      71,    -1,    41,    69,    71,    -1,    42,    65,    71,    -1,
      45,    69,    71,    -1,    46,    65,    71,    -1,    46,    69,
      71,    -1,    47,    65,    71,    -1,    48,    65,    71,    -1,
      55,    65,    71,    -1,    56,    65,    71,    -1,    57,    65,
      71,    -1,    58,    65,    71,    -1,    59,    65,    71,    -1,
      60,    65,    71,    -1,    89,    88,     5,    -1,    68,     5,
      -1,    73,    85,    74,    89,    88,    87,     5,    -1,    73,
      85,    74,    89,    88,    75,    87,    -1,    73,    85,    74,
      88,    87,     5,    -1,    73,    85,    74,    88,    75,    87,
      -1,    73,    85,    74,    68,     5,    -1,    73,    68,    74,
      89,    88,    87,     5,    -1,    73,    68,    74,    89,    88,
      75,    87,    -1,    73,    68,    74,    88,    87,     5,    -1,
      73,    68,    74,    88,    75,    87,    -1,    73,    68,    74,
      68,     5,    -1,    64,    87,     5,    -1,    64,    75,    87,
      -1,    67,    68,    74,     5,    -1,    67,    85,    74,     5,
      -1,    -1,    86,    -1,    61,    -1,    86,    76,    61,    -1,
      -1,    70,    74,    61,    -1,    -1,    72,    89,    -1,    90,
      -1,    89,    77,    90,    -1,    91,    -1,    90,    78,    91,
      -1,    92,    -1,    91,    92,    -1,    94,    -1,    94,    93,
      -1,    94,     4,    -1,     3,    -1,    68,    -1,    93,     3,
      -1,    93,    68,    -1,    61,    -1,    66,    -1,    79,    89,
      80,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   241,   241,   243,   247,   251,   260,   269,   273,   277,
     286,   291,   296,   301,   306,   311,   316,   324,   328,   334,
     338,   342,   348,   352,   358,   371,   376,   384,   389,   393,
     398,   402,   406,   410,   416,   420,   424,   428,   435,   452,
     461,   465,   471,   476,   482,   486,   501,   518,   523,   529,
     535,   553,   573,   579,   587,   590,   597,   603,   613,   616,
     624,   627,   634,   638,   645,   649,   656,   660,   667,   671,
     686,   706,   710,   714,   718,   725,   735,   739
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLOSE", "CLOSESIZE", "CODE", "CONF",
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
  "CONF_DEFINE_YYSETSTATE", "CONF_DEFINE_YYSETSTATE_NAKED",
  "CONF_DEFINE_YYSETSTATE_STATE", "CONF_DEFINE_YYSKIP", "CONF_FLAGS",
  "CONF_INDENT_STRING", "CONF_INDENT_TOP", "CONF_LABEL_YYFILLLABEL",
  "CONF_LABEL_YYNEXT", "CONF_LABELPREFIX", "CONF_STARTLABEL",
  "CONF_STATE_ABORT", "CONF_STATE_NEXTLABEL", "CONF_VARIABLE_YYACCEPT",
  "CONF_VARIABLE_YYBM", "CONF_VARIABLE_YYCH", "CONF_VARIABLE_YYCTABLE",
  "CONF_VARIABLE_YYSTABLE", "CONF_VARIABLE_YYTARGET", "CONF_YYBM_HEX",
  "CONF_YYCH_CONVERSION", "CONF_YYCH_EMIT", "CONF_YYFILL_CHECK",
  "CONF_YYFILL_ENABLE", "CONF_YYFILL_PARAMETER", "ID", "FID", "FID_END",
  "NOCOND", "NUM", "REGEXP", "SETUP", "STAR", "STRING", "'='", "';'",
  "'/'", "'<'", "'>'", "':'", "','", "'|'", "'\\\\'", "'('", "')'",
  "$accept", "spec", "decl", "rule", "cond", "clist", "newcond", "look",
  "expr", "diff", "term", "factor", "close", "primary", 0
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
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      92,    93,    93,    93,    93,    94,    94,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       7,     7,     6,     6,     5,     7,     7,     6,     6,     5,
       3,     3,     4,     4,     0,     1,     1,     3,     0,     3,
       0,     2,     1,     3,     1,     3,     1,     2,     1,     2,
       2,     1,     1,     2,     2,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,    58,    76,    54,     0,    54,     0,     4,
       3,    60,    62,    64,    66,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,     0,    58,
       0,    56,     0,     0,    55,    39,     0,     0,     0,     0,
       0,     0,     0,    67,    71,    70,    72,    69,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     0,     6,     8,
       0,    51,    50,     0,     0,     0,    60,    60,    77,    61,
      63,    38,    65,    73,    74,     5,     7,    59,    52,    53,
      57,     0,    58,    60,     0,    58,    60,    49,    58,     0,
      58,    44,    58,     0,    58,    48,    47,    58,     0,    43,
      42,    58,     0,    46,    45,    41,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    39,    40,    83,    84,    80,    91,    41,    42,
      43,    44,    97,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -130
static const yytype_int16 yypact[] =
{
    -130,   101,  -130,   -46,   -31,   -21,   -16,   -15,   -13,   -11,
      -6,    -5,    -8,    -3,    -2,    -4,    -1,     3,     1,     4,
       6,     5,   -14,    11,    12,    14,    15,    17,    19,    21,
      23,    22,   -47,   -33,  -130,   -48,    62,   -35,   -47,  -130,
    -130,   -37,    -9,   -47,  -130,     0,    18,    20,    24,    25,
      26,    27,    28,    31,    32,    35,    44,    45,    46,    47,
      48,    49,    50,    51,    54,    56,    58,    59,    60,    61,
      63,    64,    66,    69,    73,   -47,  -130,   -38,    71,    80,
      88,  -130,    77,    78,    57,  -130,    79,    81,   -68,   -47,
     -47,   149,   -47,  -130,  -130,  -130,  -130,     2,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,   -41,  -130,  -130,
     103,  -130,  -130,   161,   165,   110,   -51,   -50,  -130,    95,
      -9,  -130,   -47,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,   168,   -29,   -37,   170,   -26,   -37,  -130,    80,   171,
     -25,  -130,    80,   172,   -23,  -130,  -130,    80,   173,  -130,
    -130,    80,   174,  -130,  -130,  -130,  -130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,  -130,   144,  -130,   -77,  -129,   -32,    92,
      91,   -42,  -130,  -130
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      77,    93,   131,    94,    95,   143,    88,   152,   155,    90,
      76,    76,   138,    81,    76,    34,    34,   151,   154,    34,
      82,    89,    89,    46,   160,   128,    81,   164,    38,    38,
     145,   146,    38,    86,   129,    89,    90,    78,    47,    90,
      90,    78,    79,   127,    78,    78,   158,    78,    48,   162,
     167,    65,   171,    49,    50,    66,    51,   139,    52,    53,
      54,    55,    56,    57,    59,    58,    61,    85,    96,    92,
     144,    63,    60,    62,    64,   159,    67,    68,   163,    69,
      70,   165,    71,   168,    72,   169,    73,   172,    74,    98,
     173,    99,    75,   132,   175,   100,   101,   102,   103,   104,
      93,     2,   105,   106,   153,   156,   107,     3,     4,     5,
       6,     7,     8,     9,    10,   108,   109,   110,   111,   112,
     113,   114,   115,    11,    12,   116,    13,   117,    14,   118,
     119,   120,   121,   135,   122,   123,    15,   124,    16,    17,
     125,    18,    19,    20,   126,   130,    21,    22,    23,    24,
      78,   133,   134,   136,   141,   137,    25,    26,    27,    28,
      29,    30,    31,    32,   147,    33,   148,    34,    35,    36,
     149,   150,    90,   157,    37,   161,   166,   170,   174,   176,
      38,    87,   140,   142
};

static const yytype_uint8 yycheck[] =
{
      32,    43,    79,     3,     4,     3,    38,   136,   137,    77,
      61,    61,    80,    61,    61,    66,    66,    68,    68,    66,
      68,    72,    72,    69,   153,    63,    61,   156,    79,    79,
      71,    72,    79,    68,    72,    72,    77,    70,    69,    77,
      77,    70,    75,    75,    70,    70,    75,    70,    69,    75,
      75,    65,    75,    69,    69,    69,    69,    89,    69,    65,
      65,    69,    65,    65,    65,    69,    65,     5,    68,    78,
      68,    65,    69,    69,    69,   152,    65,    65,   155,    65,
      65,   158,    65,   160,    65,   162,    65,   164,    65,    71,
     167,    71,    70,     5,   171,    71,    71,    71,    71,    71,
     142,     0,    71,    71,   136,   137,    71,     6,     7,     8,
       9,    10,    11,    12,    13,    71,    71,    71,    71,    71,
      71,    71,    71,    22,    23,    71,    25,    71,    27,    71,
      71,    71,    71,    76,    71,    71,    35,    71,    37,    38,
      71,    40,    41,    42,    71,    74,    45,    46,    47,    48,
      70,    74,    74,    74,     5,    74,    55,    56,    57,    58,
      59,    60,    61,    62,    61,    64,     5,    66,    67,    68,
       5,    61,    77,     5,    73,     5,     5,     5,     5,     5,
      79,    37,    90,    92
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    22,    23,    25,    27,    35,    37,    38,    40,    41,
      42,    45,    46,    47,    48,    55,    56,    57,    58,    59,
      60,    61,    62,    64,    66,    67,    68,    73,    79,    83,
      84,    89,    90,    91,    92,    94,    69,    69,    69,    69,
      69,    69,    69,    65,    65,    69,    65,    65,    69,    65,
      69,    65,    69,    65,    69,    65,    69,    65,    65,    65,
      65,    65,    65,    65,    65,    70,    61,    89,    70,    75,
      87,    61,    68,    85,    86,     5,    68,    85,    89,    72,
      77,    88,    78,    92,     3,     4,    68,    93,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    89,    63,    72,
      74,    87,     5,    74,    74,    76,    74,    74,    80,    89,
      90,     5,    91,     3,    68,    71,    72,    61,     5,     5,
      61,    68,    88,    89,    68,    88,    89,     5,    75,    87,
      88,     5,    75,    87,    88,    87,     5,    75,    87,    87,
       5,    75,    87,    87,     5,    87,     5
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
		if (!mapCodeName.insert (std::make_pair (*(yyvsp[(1) - (3)].str), *(yyvsp[(2) - (3)].str))).second)
		{
			in->fatalf ("configuration '%s' is already set and cannot be changed", (yyvsp[(1) - (3)].str)->c_str ());
		}
		delete (yyvsp[(1) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 10:

    {
		condPrefix = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 11:

    {
		condEnumPrefix = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 12:

    {
		condDivider = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 13:

    {
		condDividerParam = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 14:

    {
		condGoto = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 15:

    {
		condGotoParam = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 16:

    {
		if ((yyvsp[(2) - (3)].num) < 0)
		{
			in->fatal ("configuration 'cgoto:threshold' must be nonnegative");
		}
		cGotoThreshold = static_cast<uint32_t> ((yyvsp[(2) - (3)].num));
	;}
    break;

  case 17:

    {
		bUseYYFillNaked = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 18:

    {
		yyFillLength = *(yyvsp[(2) - (3)].str);
		bUseYYFillParam = false;
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 19:

    {
		bUseYYGetConditionNaked = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 20:

    {
		bUseYYGetStateNaked = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 21:

    {
		yySetConditionParam = *(yyvsp[(2) - (3)].str);
		bUseYYSetConditionParam = false;
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 22:

    {
		bUseYYSetStateNaked = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 23:

    {
		yySetStateParam = *(yyvsp[(2) - (3)].str);
		bUseYYSetStateParam = false;
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 24:

    {
		if ((yyvsp[(2) - (3)].num) == 0)
		{
			encoding.unset ((yyvsp[(1) - (3)].enc));
		}
		else if (!encoding.set ((yyvsp[(1) - (3)].enc)))
		{
			in->fatalf ("Cannot set %s encoding: please reset %s encoding first"
				, Enc::name ((yyvsp[(1) - (3)].enc))
				, Enc::name (encoding.type ()));
		}
	;}
    break;

  case 25:

    {
		indString = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 26:

    {
		if ((yyvsp[(2) - (3)].num) < 0)
		{
			in->fatal ("configuration 'indent:top' must be nonnegative");
		}
		topIndent = static_cast<uint32_t> ((yyvsp[(2) - (3)].num));
	;}
    break;

  case 27:

    {
		labelPrefix = *(yyvsp[(2) - (3)].str);
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 28:

    {
		in->out.set_force_start_label ((yyvsp[(2) - (3)].num) != 0);
	;}
    break;

  case 29:

    {
		in->out.set_user_start_label (*(yyvsp[(2) - (3)].str));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 30:

    {
		bUseStateAbort = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 31:

    {
		bUseStateNext = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 32:

    {
		yybmHexTable = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 33:

    {
		yychConversion = (yyvsp[(2) - (3)].num) == 0
			? ""
			: "(" + mapCodeName["YYCTYPE"] + ")";
	;}
    break;

  case 34:

    {
		bEmitYYCh = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 35:

    {
		bUseYYFillCheck = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 36:

    {
		bUseYYFill = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 37:

    {
		bUseYYFillParam = (yyvsp[(2) - (3)].num) != 0;
	;}
    break;

  case 38:

    {
			if (cFlag)
			{
				in->fatal("condition or '<*>' required when using -c switch");
			}
			(yyval.regexp) = new RuleOp
				( (yyvsp[(3) - (3)].code)->loc
				, (yyvsp[(1) - (3)].regexp)
				, (yyvsp[(2) - (3)].regexp)
				, rank_counter.next ()
				, RegExp::SHARED
				, (yyvsp[(3) - (3)].code)
				, NULL
				);
			spec = spec? mkAlt(spec, (yyval.regexp)) : (yyval.regexp);
		;}
    break;

  case 39:

    {
			if (cFlag)
				in->fatal("condition or '<*>' required when using -c switch");
			if (ruleDefault != NULL)
				in->fatal("code to default rule is already defined");
			else
				ruleDefault = (yyvsp[(2) - (2)].code);
		;}
    break;

  case 40:

    {
			context_rule ((yyvsp[(2) - (7)].clist), (yyvsp[(7) - (7)].code)->loc, (yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), (yyvsp[(7) - (7)].code), (yyvsp[(6) - (7)].str));
		;}
    break;

  case 41:

    {
			assert((yyvsp[(7) - (7)].str));
			Loc loc (in->get_fname (), in->get_cline ());
			context_rule ((yyvsp[(2) - (7)].clist), loc, (yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), NULL, (yyvsp[(7) - (7)].str));
		;}
    break;

  case 42:

    {
			context_none((yyvsp[(2) - (6)].clist));
			delete (yyvsp[(5) - (6)].str);
		;}
    break;

  case 43:

    {
			assert((yyvsp[(6) - (6)].str));
			context_none((yyvsp[(2) - (6)].clist));
			delete (yyvsp[(6) - (6)].str);
		;}
    break;

  case 44:

    {
			default_rule((yyvsp[(2) - (5)].clist), (yyvsp[(5) - (5)].code));
		;}
    break;

  case 45:

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

  case 46:

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

  case 47:

    {
			context_none(NULL);
			delete (yyvsp[(5) - (6)].str);
		;}
    break;

  case 48:

    {
			assert((yyvsp[(6) - (6)].str));
			context_none(NULL);
			delete (yyvsp[(6) - (6)].str);
		;}
    break;

  case 49:

    {
			CondList *clist = new CondList();
			clist->insert("*");
			default_rule(clist, (yyvsp[(5) - (5)].code));
		;}
    break;

  case 50:

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

  case 51:

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

  case 52:

    {
			CondList *clist = new CondList();
			clist->insert("*");
			setup_rule(clist, (yyvsp[(4) - (4)].code));
		;}
    break;

  case 53:

    {
			setup_rule((yyvsp[(2) - (4)].clist), (yyvsp[(4) - (4)].code));
		;}
    break;

  case 54:

    {
			in->fatal("unnamed condition not supported");
		;}
    break;

  case 55:

    {
			(yyval.clist) = (yyvsp[(1) - (1)].clist);
		;}
    break;

  case 56:

    {
			(yyval.clist) = new CondList();
			(yyval.clist)->insert(* (yyvsp[(1) - (1)].str));
			delete (yyvsp[(1) - (1)].str);
		;}
    break;

  case 57:

    {
			(yyvsp[(1) - (3)].clist)->insert(* (yyvsp[(3) - (3)].str));
			delete (yyvsp[(3) - (3)].str);
			(yyval.clist) = (yyvsp[(1) - (3)].clist);
		;}
    break;

  case 58:

    {
			(yyval.str) = NULL;
		;}
    break;

  case 59:

    {
			(yyval.str) = (yyvsp[(3) - (3)].str);
		;}
    break;

  case 60:

    {
			(yyval.regexp) = new NullOp;
		;}
    break;

  case 61:

    {
			(yyval.regexp) = (yyvsp[(2) - (2)].regexp);
		;}
    break;

  case 62:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 63:

    {
			(yyval.regexp) = mkAlt((yyvsp[(1) - (3)].regexp), (yyvsp[(3) - (3)].regexp));
		;}
    break;

  case 64:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 65:

    {
			(yyval.regexp) = in->mkDiff((yyvsp[(1) - (3)].regexp), (yyvsp[(3) - (3)].regexp));
		;}
    break;

  case 66:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 67:

    {
			(yyval.regexp) = new CatOp((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].regexp));
		;}
    break;

  case 68:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 69:

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

  case 70:

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

  case 71:

    {
			(yyval.op) = (yyvsp[(1) - (1)].op);
		;}
    break;

  case 72:

    {
			(yyval.op) = (yyvsp[(1) - (1)].op);
		;}
    break;

  case 73:

    {
			(yyval.op) = ((yyvsp[(1) - (2)].op) == (yyvsp[(2) - (2)].op)) ? (yyvsp[(1) - (2)].op) : '*';
		;}
    break;

  case 74:

    {
			(yyval.op) = ((yyvsp[(1) - (2)].op) == (yyvsp[(2) - (2)].op)) ? (yyvsp[(1) - (2)].op) : '*';
		;}
    break;

  case 75:

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

  case 76:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		;}
    break;

  case 77:

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

	Enc encodingOld = encoding;
	
	while ((parseMode = i.echo()) != Scanner::Stop)
	{
		o.source.new_block ();
		bool bPrologBrace = false;
		ScannerState curr_state;

		i.save_state(curr_state);
		foundRules = false;

		if (rFlag && parseMode == Scanner::Rules && dfa_map.size())
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
		spec = NULL;
		ruleDefault = NULL;
		in->set_in_parse(true);
		yyparse();
		in->set_in_parse(false);
		if (rFlag && parseMode == Scanner::Reuse)
		{
			if (foundRules || encoding != encodingOld)
			{
				// Re-parse rules
				parseMode = Scanner::Parse;
				i.restore_state(rules_state);
				i.reuse();
				dfa_map.clear();
				parse_cleanup();
				spec = NULL;
				rank_counter.reset ();
				ruleDefault = NULL;
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
			encodingOld = encoding;
		}
		o.source.set_block_line (in->get_cline ());
		if (cFlag)
		{
			RegExpMap::iterator it;
			SetupMap::const_iterator itRuleSetup;

			if (parseMode != Scanner::Reuse)
			{
				if (!specStar.empty())
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
						assert(it->second);
						for (RuleOpList::const_iterator itOp = specStar.begin(); itOp != specStar.end(); ++itOp)
						{
							it->second = mkAlt(*itOp, it->second);
						}
					}
				}
	
				if (specNone)
				{
					specMap["0"] = specNone;
					// Note that "0" inserts first, which is important.
					condnames.insert (condnames.begin (), "0");
				}
				o.types = condnames;
			}

			size_t nCount = specMap.size();

			for (it = specMap.begin(); it != specMap.end(); ++it)
			{
				assert(it->second);

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

					DefaultMap::const_iterator def = ruleDefaultMap.find (it->first);
					if (def == ruleDefaultMap.end ())
					{
						def = ruleDefaultMap.find ("*");
					}
					if (def != ruleDefaultMap.end ())
					{
						RuleOp * def_rule = new RuleOp
							( def->second->loc
							, in->mkDefault ()
							, new NullOp
							, rank_counter.next ()
							, RegExp::SHARED
							, def->second
							, NULL
							);
						it->second = it->second ? mkAlt (def_rule, it->second) : def_rule;
					}

					dfa_map[it->first] = genCode(it->second, o);
				}
				if (parseMode != Scanner::Rules && dfa_map.find(it->first) != dfa_map.end())
				{
					dfa_map[it->first]->emit(o, topIndent, it->first, !--nCount, bPrologBrace);
				}
			}
		}
		else
		{
			if (ruleDefault != NULL && parseMode != Scanner::Reuse)
			{
				RuleOp * def = new RuleOp
					( ruleDefault->loc
					, in->mkDefault ()
					, new NullOp
					, rank_counter.next ()
					, RegExp::SHARED
					, ruleDefault
					, NULL
					);
				spec = spec ? mkAlt(def, spec) : def;
			}
			if (spec || !dfa_map.empty())
			{
				if (parseMode != Scanner::Reuse)
				{
					dfa_map[""] = genCode(spec, o);
				}
				if (parseMode != Scanner::Rules && dfa_map.find("") != dfa_map.end())
				{
					dfa_map[""]->emit(o, topIndent, "", 0, bPrologBrace);
				}
			}
		}
		o.source.write_line_info (in->get_cline (), in->get_fname ().c_str ());
		/* restore original char handling mode*/
		encoding = encodingOld;
	}

	if (cFlag)
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
	specNone = NULL;
}

} // end namespace re2c

