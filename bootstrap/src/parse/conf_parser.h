/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_CONF_SRC_PARSE_CONF_PARSER_H_INCLUDED
# define YY_CONF_SRC_PARSE_CONF_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef CONF_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define CONF_DEBUG 1
#  else
#   define CONF_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CONF_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CONF_DEBUG */
#if CONF_DEBUG
extern int conf_debug;
#endif
/* "%code requires" blocks.  */
#line 1 "../src/parse/conf_parser.ypp"


#include "src/constants.h"
#include "src/options/opt.h"

#include "src/default_syntax_c.h"
#include "src/default_syntax_d.h"
#include "src/default_syntax_go.h"
#include "src/default_syntax_haskell.h"
#include "src/default_syntax_java.h"
#include "src/default_syntax_js.h"
#include "src/default_syntax_ocaml.h"
#include "src/default_syntax_python.h"
#include "src/default_syntax_rust.h"
#include "src/default_syntax_v.h"
#include "src/default_syntax_zig.h"


#line 76 "src/parse/conf_parser.h"

/* Token kinds.  */
#ifndef CONF_TOKENTYPE
# define CONF_TOKENTYPE
  enum conf_tokentype
  {
    CONF_EMPTY = -2,
    CONF_EOF = 0,                  /* "end of file"  */
    CONF_error = 256,              /* error  */
    CONF_UNDEF = 257,              /* "invalid token"  */
    CONF_NUMBER = 258,             /* CONF_NUMBER  */
    CONF_STRING = 259,             /* CONF_STRING  */
    CONF_COND = 260,               /* CONF_COND  */
    CONF_VAR = 261,                /* CONF_VAR  */
    CONF_CODE = 262,               /* CONF_CODE  */
    CONF_GOPT = 263,               /* CONF_GOPT  */
    CONF_LOPT = 264,               /* CONF_LOPT  */
    CONF_UD = 265                  /* CONF_UD  */
  };
  typedef enum conf_tokentype conf_token_kind_t;
#endif

/* Value type.  */
#if ! defined CONF_STYPE && ! defined CONF_STYPE_IS_DECLARED
union CONF_STYPE
{
#line 48 "../src/parse/conf_parser.ypp"

    const char* str;
    int32_t num;
    bool cond;
    std::vector<std::string>* list;
    re2c::StxVarId var;
    re2c::StxCode* code;
    re2c::StxCodes* codes;
    const re2c::StxCodes** codeptr;
    re2c::StxOpt* opt;
    re2c::StxGOpt gopt;
    re2c::StxLOpt lopt;

#line 117 "src/parse/conf_parser.h"

};
typedef union CONF_STYPE CONF_STYPE;
# define CONF_STYPE_IS_TRIVIAL 1
# define CONF_STYPE_IS_DECLARED 1
#endif




int conf_parse (re2c::Input& in, re2c::Opt& opts);


#endif /* !YY_CONF_SRC_PARSE_CONF_PARSER_H_INCLUDED  */
