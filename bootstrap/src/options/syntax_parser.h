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

#ifndef YY_STX_SRC_OPTIONS_SYNTAX_PARSER_H_INCLUDED
# define YY_STX_SRC_OPTIONS_SYNTAX_PARSER_H_INCLUDED
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
#line 1 "../src/options/syntax_parser.ypp"


#include <stdint.h>

#include "src/options/syntax.h"
#include "src/util/allocator.h"
#include "src/util/containers.h"

union STX_STYPE;

namespace re2c {

struct conopt_t;

class StxFile {
    OutAllocator& alc;
    const std::string& fname;
    FILE* file;
    size_t flen;
    uint8_t* buf;
    const uint8_t* cur; // current lexer position
    const uint8_t* tok; // token start
    const uint8_t* pos; // line start (used for error reporting)
    loc_t loc;
    std::string tmp_str;

  public:
    Msg& msg;

  public:
    StxFile(OutAllocator& alc, const std::string& fname, Msg& msg);
    ~StxFile();
    Ret read(Lang lang);
    int lex_token(STX_STYPE* yylval);
    bool check_conf_name(const char* name) const;
    loc_t tok_loc() const;

    FORBID_COPY(StxFile);
};

Ret load_syntax_config(Stx& stx, const std::string& config, Lang& lang, Msg& msg);

} // namespace re2c


#line 103 "src/options/syntax_parser.h"

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
    STX_CONF = 261,                /* STX_CONF  */
    STX_CONF_CODE = 262            /* STX_CONF_CODE  */
  };
  typedef enum stx_tokentype stx_token_kind_t;
#endif

/* Value type.  */
#if ! defined STX_STYPE && ! defined STX_STYPE_IS_DECLARED
union STX_STYPE
{
#line 69 "../src/options/syntax_parser.ypp"

    const char* str;
    int32_t num;
    re2c::StxConf* conf;
    re2c::StxList* list;
    re2c::StxCode* code;
    re2c::StxCodes* codes;

#line 136 "src/options/syntax_parser.h"

};
typedef union STX_STYPE STX_STYPE;
# define STX_STYPE_IS_TRIVIAL 1
# define STX_STYPE_IS_DECLARED 1
#endif




int stx_parse (re2c::StxFile& sf, re2c::Stx& stx);


#endif /* !YY_STX_SRC_OPTIONS_SYNTAX_PARSER_H_INCLUDED  */
