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

#ifndef YY_RE2C_SRC_PARSE_PARSER_H_INCLUDED
# define YY_RE2C_SRC_PARSE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef RE2C_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define RE2C_DEBUG 1
#  else
#   define RE2C_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define RE2C_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined RE2C_DEBUG */
#if RE2C_DEBUG
extern int re2c_debug;
#endif
/* "%code requires" blocks.  */
#line 1 "../src/parse/parser.ypp"

/* pull in types to populate YYSTYPE: */
#include "src/parse/ast.h"
namespace re2c {
    struct AstNode;
    struct SemAct;
}

#line 66 "src/parse/parser.h"

/* Token kinds.  */
#ifndef RE2C_TOKENTYPE
# define RE2C_TOKENTYPE
  enum re2c_tokentype
  {
    RE2C_EMPTY = -2,
    RE2C_EOF = 0,                  /* "end of file"  */
    RE2C_error = 256,              /* error  */
    RE2C_UNDEF = 257,              /* "invalid token"  */
    TOKEN_CJUMP = 258,             /* TOKEN_CJUMP  */
    TOKEN_CNEXT = 259,             /* TOKEN_CNEXT  */
    TOKEN_CLIST = 260,             /* TOKEN_CLIST  */
    TOKEN_CSETUP = 261,            /* TOKEN_CSETUP  */
    TOKEN_CZERO = 262,             /* TOKEN_CZERO  */
    TOKEN_CLOSESIZE = 263,         /* TOKEN_CLOSESIZE  */
    TOKEN_CODE = 264,              /* TOKEN_CODE  */
    TOKEN_CONF = 265,              /* TOKEN_CONF  */
    TOKEN_ID = 266,                /* TOKEN_ID  */
    TOKEN_FID = 267,               /* TOKEN_FID  */
    TOKEN_FID_END = 268,           /* TOKEN_FID_END  */
    TOKEN_LINE_INFO = 269,         /* TOKEN_LINE_INFO  */
    TOKEN_REGEXP = 270,            /* TOKEN_REGEXP  */
    TOKEN_BLOCK = 271,             /* TOKEN_BLOCK  */
    TOKEN_ERROR = 272              /* TOKEN_ERROR  */
  };
  typedef enum re2c_tokentype re2c_token_kind_t;
#endif

/* Value type.  */
#if ! defined RE2C_STYPE && ! defined RE2C_STYPE_IS_DECLARED
union RE2C_STYPE
{
#line 43 "../src/parse/parser.ypp"

    const re2c::AstNode* regexp;
    const re2c::SemAct* semact;
    char op;
    re2c::AstBounds bounds;
    const char* cstr;
    std::string* str;

#line 109 "src/parse/parser.h"

};
typedef union RE2C_STYPE RE2C_STYPE;
# define RE2C_STYPE_IS_TRIVIAL 1
# define RE2C_STYPE_IS_DECLARED 1
#endif




int re2c_parse (re2c::Input& input, re2c::Ast& ast, re2c::Opt& opts, re2c::AstGrams& grams);


#endif /* !YY_RE2C_SRC_PARSE_PARSER_H_INCLUDED  */
