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

#ifndef YY_STX_SRC_PARSE_SYNTAX_PARSER_H_INCLUDED
# define YY_STX_SRC_PARSE_SYNTAX_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef STX_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define STX_DEBUG 1
#  else
#   define STX_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define STX_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined STX_DEBUG */
#if STX_DEBUG
extern int stx_debug;
#endif
/* "%code requires" blocks.  */
#line 1 "../src/parse/syntax_parser.ypp"


#include "src/constants.h"
#include "src/options/syntax.h"


#line 64 "src/parse/syntax_parser.h"

/* Token kinds.  */
#ifndef STX_TOKENTYPE
# define STX_TOKENTYPE
  enum stx_tokentype
  {
    STX_EMPTY = -2,
    STX_EOF = 0,                   /* "end of file"  */
    STX_error = 256,               /* error  */
    STX_UNDEF = 257,               /* "invalid token"  */
    STX_NAME = 258,                /* STX_NAME  */
    STX_NUMBER = 259,              /* STX_NUMBER  */
    STX_STRING = 260,              /* STX_STRING  */
    STX_GOPT = 261,                /* STX_GOPT  */
    STX_LOPT = 262,                /* STX_LOPT  */
    STX_CONF = 263,                /* STX_CONF  */
    STX_CONF_CODE = 264            /* STX_CONF_CODE  */
  };
  typedef enum stx_tokentype stx_token_kind_t;
#endif

/* Value type.  */
#if ! defined STX_STYPE && ! defined STX_STYPE_IS_DECLARED
union STX_STYPE
{
#line 33 "../src/parse/syntax_parser.ypp"

    const char* str;
    int32_t num;
    re2c::StxConf* conf;
    re2c::StxList* list;
    re2c::StxCode* code;
    re2c::StxCodes* codes;
    re2c::StxOpt* opt;
    re2c::StxGOpt gopt;
    re2c::StxLOpt lopt;

#line 102 "src/parse/syntax_parser.h"

};
typedef union STX_STYPE STX_STYPE;
# define STX_STYPE_IS_TRIVIAL 1
# define STX_STYPE_IS_DECLARED 1
#endif




int stx_parse (re2c::Input& in, re2c::Opt& opts, re2c::Stx& stx);


#endif /* !YY_STX_SRC_PARSE_SYNTAX_PARSER_H_INCLUDED  */
