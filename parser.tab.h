#ifndef BISON_PARSER_TAB_H
# define BISON_PARSER_TAB_H

#ifndef YYSTYPE
typedef union {
	re2c::Symbol	*symbol;
	re2c::RegExp	*regexp;
	re2c::Token	*token;
	char	op;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	CLOSE	257
# define	ID	258
# define	CODE	259
# define	RANGE	260
# define	STRING	261


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_TAB_H */
