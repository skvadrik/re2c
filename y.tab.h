#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
    Symbol	*symbol;
    RegExp	*regexp;
    Token	*token;
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

#endif /* not BISON_Y_TAB_H */
