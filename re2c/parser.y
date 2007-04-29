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
%type	<str>		CONFIG	VALUE
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
	|	'<' cond '>' expr look CODE
		{
			if (!cFlag)
			{
				delete $2;
				in->fatal("conditions are only allowed when using -c switch");
			}
			for(CondList::const_iterator it = $2->begin(); it != $2->end(); ++it)
			{
				// Duplicating stuff, slow but safe
				$$ = new RuleOp($4, $5, new Token(*$6), accept++);

				RegExpMap::iterator itRE = specMap.find(*it);

				if (itRE != specMap.end())
				{
					itRE->second.second = mkAlt(itRE->second.second, $$);
				}
				else
				{
					size_t nIndex = specMap.size() + 1; // 0 is reserved for "0"-spec
					specMap[*it] = std::make_pair(nIndex, $$);
				}
				
			}
			delete $2;
			delete $6;
		}
	|	'<' cond '>' look CODE
		{
			delete $2;
			if (!cFlag)
			{
				in->fatal("conditions are only allowed when using -c switch");
			}
			in->fatal("no expression specified");
		}
	|	'<' STAR '>' expr look CODE
		{
			if (!cFlag)
			{
				in->fatal("conditions are only allowed when using -c switch");
			}
			specStar.push_back(new RuleOp($4, $5, $6, accept++));
		}
	|	'<' STAR '>' look CODE
		{
			if (!cFlag)
			{
				in->fatal("conditions are only allowed when using -c switch");
			}
			in->fatal("no expression specified");
		}
	|	NOCOND CODE
		{
			if (!cFlag)
			{
				in->fatal("conditions are only allowed when using -c switch");
			}
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			$$ = specNone = new RuleOp(new NullOp(), new NullOp(), $2, accept++);
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
				// We reserved 0 for specNone but is isn't present,
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
				genCode(o, topIndent, it->second.second, &specMap, it->first, !--nCount);
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
			genCode(o, topIndent, spec, NULL, "", 0);
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
