%{

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "globals.h"
#include "parser.h"
#include "basics.h"

#define YYMALLOC malloc
#define YYFREE free

using namespace re2c;

extern "C"
{
int yylex();
void yyerror(const char*);
}

static re2c::uint       accept;
static re2c::RegExpMap  specMap;
static RegExp           *spec, *specNone = NULL;
static RuleOpList       specStar;
static Scanner          *in = NULL;

/* Bison version 1.875 emits a definition that is not working
 * with several g++ version. Hence we disable it here.
 */
#if defined(__GNUC__)
#define __attribute__(x)
#endif

/* strdup() isn't standard C, so if we don't have it, we'll create our
 * own version
 */
#if !defined(HAVE_STRDUP)
static char* strdup(const char* s)
{
	char* rv = (char*)malloc(strlen(s) + 1);

	if (rv == NULL)
	{
		return NULL;
	}
	strcpy(rv, s);
	return rv;
}
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

void context_rule(CondList *clist, RegExp *expr, RegExp *look, Str *newcond, Token *code)
{
	context_check(clist);
	bool condchange = !newcond || clist->size() > 1
	                || clist->find(newcond->to_string()) == clist->end();
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		Str *condcpy = newcond ? new Str(*newcond) : newcond;
		Token *token = new Token(code, in->get_line(), condcpy, condchange);
		RuleOp *rule = new RuleOp(expr, look, token, accept++);

		RegExpMap::iterator itRE = specMap.find(*it);

		if (itRE != specMap.end())
		{
			itRE->second.second = mkAlt(itRE->second.second, rule);
		}
		else
		{
			size_t nIndex = specMap.size() + 1; // 0 is reserved for "0"-spec
			specMap[*it] = std::make_pair(nIndex, rule);
		}
		
	}
	delete clist;
	delete code;
}

%}

%start	spec

%union {
	re2c::Symbol	*symbol;
	re2c::RegExp	*regexp;
	re2c::Token 	*token;
	char        	op;
	int         	number;
	re2c::ExtOp 	extop;
	re2c::Str   	*str;
	re2c::CondList	*clist;
};

%token		CLOSESIZE	CLOSE	STAR	NOCOND	ID	CODE	RANGE	STRING
%token		CONFIG	VALUE	NUMBER

%type	<op>		CLOSE	STAR
%type	<op>		close
%type	<extop>		CLOSESIZE
%type	<symbol>	ID
%type	<token>		CODE
%type	<regexp>	RANGE	STRING
%type	<regexp>	rule	look	expr	diff	term	factor	primary
%type	<str>		CONFIG	VALUE	newcond
%type	<clist>		cond	clist
%type	<number>	NUMBER

%%

spec:
		/* empty */
		{
			accept = 0;
			spec = NULL;
		}
	|	spec rule
	|	spec decl
;

decl:
		ID '=' expr ';'
		{
			if($1->re)
			{
				in->fatal("sym already defined");
			}
			$1->re = $3;
		}
	|	ID '=' expr '/'
		{
			in->fatal("trailing contexts are not allowed in named definitions");
		}
	|	CONFIG '=' VALUE ';'
		{
			in->config(*$1, *$3);
			delete $1;
			delete $3;
		}
	|	CONFIG '=' NUMBER ';'
		{
			in->config(*$1, $3);
			delete $1;
		}
;

rule:
		expr look CODE
		{
			if (cFlag)
			{
				in->fatal("condition or '<*>' required when using -c switch");
			}
			$$ = new RuleOp($1, $2, $3, accept++);
			spec = spec? mkAlt(spec, $$) : $$;
		}
	|	'<' cond '>' expr look newcond CODE
		{
			context_rule($2, $4, $5, $6, $7);
		}
	|	'<' cond '>' expr look ':' newcond
		{
			assert($7);
			context_rule($2, $4, $5, $7, NULL);
		}
	|	'<' cond '>' look newcond CODE
		{
			context_none($2);
		}
	|	'<' cond '>' look ':' newcond
		{
			assert($6);
			context_none($2);
		}
	|	'<' STAR '>' expr look newcond CODE
		{
			context_check(NULL);
			$7->newcond = $6;
			specStar.push_back(new RuleOp($4, $5, $7, accept++));
		}
	|	'<' STAR '>' expr look ':' newcond
		{
			assert($7);
			context_check(NULL);
			Token *token = new Token(NULL, in->get_line(), $7, true);
			specStar.push_back(new RuleOp($4, $5, token, accept++));
		}
	|	'<' STAR '>' look newcond CODE
		{
			context_none(NULL);
		}
	|	'<' STAR '>' look ':' newcond
		{
			assert($6);
			context_none(NULL);
		}
	|	NOCOND newcond CODE
		{
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			$3->newcond = $2;
			$$ = specNone = new RuleOp(new NullOp(), new NullOp(), $3, accept++);
		}
	|	NOCOND ':' newcond
		{
			assert($3);
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			Token *token = new Token(NULL, in->get_line(), $3, true);
			$$ = specNone = new RuleOp(new NullOp(), new NullOp(), token, accept++);
		}
;

cond:
		/* empty */
		{
			in->fatal("unnamed condition not supported");
		}
	|	clist
		{
			$$ = $1;
		}
	;

clist:
		ID
		{
			$$ = new CondList();
			$$->insert($1->GetName().to_string());
		}
	|	clist ',' ID
		{
			$1->insert($3->GetName().to_string());
			$$ = $1;
		}
;

newcond:
		/* empty */
		{
			$$ = NULL;
		}
	|	'=' '>' ID
		{
			$$ = new Str($3->GetName().to_string().c_str());
		}
;

look:
		/* empty */
		{
			$$ = new NullOp;
		}
	|	'/' expr
		{
			$$ = $2;
		}
;

expr:
		diff
		{
			$$ = $1;
		}
	|	expr '|' diff
		{
			$$ = mkAlt($1, $3);
		}
;

diff:
		term
		{
			$$ = $1;
		}
	|	diff '\\' term
		{
			$$ = mkDiff($1, $3);
			if(!$$)
			{
				in->fatal("can only difference char sets");
			}
		}
;

term:
		factor
		{
			$$ = $1;
		}
	|	term factor
		{
			$$ = new CatOp($1, $2);
		}
;

factor:
		primary
		{
			$$ = $1;
		}
	|	primary close
		{
			switch($2)
			{
			case '*':
				$$ = mkAlt(new CloseOp($1), new NullOp());
				break;
			case '+':
				$$ = new CloseOp($1);
				break;
			case '?':
				$$ = mkAlt($1, new NullOp());
				break;
			}
		}
	|	primary CLOSESIZE
		{
			$$ = new CloseVOp($1, $2.minsize, $2.maxsize);
		}
;

close:
		CLOSE
		{
			$$ = $1;
		}
	|	STAR
		{
			$$ = $1;
		}
	|	close CLOSE
		{
			$$ = ($1 == $2) ? $1 : '*';
		}
	|	close STAR
		{
			$$ = ($1 == $2) ? $1 : '*';
		}
;

primary:
		ID
		{
			if(!$1->re)
			{
				in->fatal("can't find symbol");
			}
			$$ = $1->re;
		}
	|	RANGE
		{
			$$ = $1;
		}
	|	STRING
		{
			$$ = $1;
		}
	|	'(' expr ')'
		{
			$$ = $2;
		}
;

%%

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

void parse(Scanner& i, std::ostream& o, std::ostream* h)
{
	in = &i;

	o << "/* Generated by re2c " PACKAGE_VERSION;
	if (!bNoGenerationDate)
	{
		o << " on ";
		time_t now = time(&now);
		o.write(ctime(&now), 24);
	}
	o << " */\n";
	o << sourceFileInfo;
	
	while(i.echo())
	{
		bool bPrologBrace = false;
		yyparse();
		if (cFlag)
		{
			RegExpMap::iterator it;

			if (!specStar.empty())
			{
				for(it = specMap.begin(); it != specMap.end(); ++it)
				{
					assert(it->second.second);
					for(RuleOpList::const_iterator itOp = specStar.begin(); itOp != specStar.end(); ++itOp)
					{
						it->second.second = mkAlt((*itOp)->copy(accept++), it->second.second);
					}
				}
			}

			if (specNone)
			{
				// After merging star rules merge none code to specmap
				// this simplifies some stuff.
				// Note that "0" inserts first, which is important.
				specMap["0"] = std::make_pair(0, specNone);
			}
			else
			{
				// We reserved 0 for specNone but it is not present,
				// so we can decrease all specs.
				for(it = specMap.begin(); it != specMap.end(); ++it)
				{
					it->second.first--;
				}
			}

			size_t nCount = specMap.size();
			for(it = specMap.begin(); it != specMap.end(); ++it)
			{
				assert(it->second.second);
				genCode(o, topIndent, it->second.second, &specMap, it->first, !--nCount, bPrologBrace);
			}
			if (h)
			{
				genHeader(*h, 0, specMap);
			}
			else
			{
				genTypes(typesInline, 0, specMap);
			}
		}
		else if(spec)
		{
			genCode(o, topIndent, spec, NULL, "", 0, bPrologBrace);
		}
		o << sourceFileInfo;
	}

	RegExp::vFreeList.clear();
	Range::vFreeList.clear();
	Symbol::ClearTable();
	specMap.clear();
	specStar.clear();
	specNone = NULL;
	in = NULL;
}

} // end namespace re2c
