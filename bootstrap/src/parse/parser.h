/* A Bison parser, made by GNU Bison 3.7.6.  */

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

#ifndef YY_YY_SRC_PARSE_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
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
    TOKEN_BLOCK = 271              /* TOKEN_BLOCK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "../src/parse/parser.ypp"

    const re2c::AST *regexp;
    re2c::SemAct    *semact;
    char             op;
    re2c::ASTBounds  bounds;
    std::string     *str;
    re2c::CondList  *clist;

#line 89 "src/parse/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (re2c::context_t &context);

#endif /* !YY_YY_SRC_PARSE_PARSER_H_INCLUDED  */
