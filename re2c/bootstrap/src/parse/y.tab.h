/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
     CONF_DEFINE_YYSETSTATE = 290,
     CONF_DEFINE_YYSETSTATE_NAKED = 291,
     CONF_DEFINE_YYSETSTATE_STATE = 292,
     CONF_DEFINE_YYSKIP = 293,
     CONF_FLAGS = 294,
     CONF_INDENT_STRING = 295,
     CONF_INDENT_TOP = 296,
     CONF_LABEL_YYFILLLABEL = 297,
     CONF_LABEL_YYNEXT = 298,
     CONF_LABELPREFIX = 299,
     CONF_STARTLABEL = 300,
     CONF_STATE_ABORT = 301,
     CONF_STATE_NEXTLABEL = 302,
     CONF_VARIABLE_YYACCEPT = 303,
     CONF_VARIABLE_YYBM = 304,
     CONF_VARIABLE_YYCH = 305,
     CONF_VARIABLE_YYCTABLE = 306,
     CONF_VARIABLE_YYSTABLE = 307,
     CONF_VARIABLE_YYTARGET = 308,
     CONF_YYBM_HEX = 309,
     CONF_YYCH_CONVERSION = 310,
     CONF_YYCH_EMIT = 311,
     CONF_YYFILL_CHECK = 312,
     CONF_YYFILL_ENABLE = 313,
     CONF_YYFILL_PARAMETER = 314,
     ID = 315,
     FID = 316,
     FID_END = 317,
     NOCOND = 318,
     NUM = 319,
     REGEXP = 320,
     SETUP = 321,
     STAR = 322,
     STRING = 323
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

extern YYSTYPE yylval;


