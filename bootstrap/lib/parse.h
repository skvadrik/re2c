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

#ifndef YY_RE2C_LIB_LIB_PARSE_H_INCLUDED
# define YY_RE2C_LIB_LIB_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef RE2C_LIB_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define RE2C_LIB_DEBUG 1
#  else
#   define RE2C_LIB_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define RE2C_LIB_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined RE2C_LIB_DEBUG */
#if RE2C_LIB_DEBUG
extern int re2c_lib_debug;
#endif
/* "%code requires" blocks.  */
#line 1 "../lib/parse.ypp"

/* pull in types to populate YYSTYPE: */
#include "src/parse/ast.h"
namespace re2c {
    struct AstNode;
}

#line 65 "lib/parse.h"

/* Token kinds.  */
#ifndef RE2C_LIB_TOKENTYPE
# define RE2C_LIB_TOKENTYPE
  enum re2c_lib_tokentype
  {
    RE2C_LIB_EMPTY = -2,
    RE2C_LIB_EOF = 0,              /* "end of file"  */
    RE2C_LIB_error = 256,          /* error  */
    RE2C_LIB_UNDEF = 257,          /* "invalid token"  */
    TOKEN_COUNT = 258,             /* TOKEN_COUNT  */
    TOKEN_ERROR = 259,             /* TOKEN_ERROR  */
    TOKEN_REGEXP = 260             /* TOKEN_REGEXP  */
  };
  typedef enum re2c_lib_tokentype re2c_lib_token_kind_t;
#endif

/* Value type.  */
#if ! defined RE2C_LIB_STYPE && ! defined RE2C_LIB_STYPE_IS_DECLARED
union RE2C_LIB_STYPE
{
#line 34 "../lib/parse.ypp"

    const re2c::AstNode* regexp;
    re2c::AstBounds bounds;

#line 92 "lib/parse.h"

};
typedef union RE2C_LIB_STYPE RE2C_LIB_STYPE;
# define RE2C_LIB_STYPE_IS_TRIVIAL 1
# define RE2C_LIB_STYPE_IS_DECLARED 1
#endif




int re2c_lib_parse (const uint8_t*& pattern, re2c::Ast& ast);


#endif /* !YY_RE2C_LIB_LIB_PARSE_H_INCLUDED  */
