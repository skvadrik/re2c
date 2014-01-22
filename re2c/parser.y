%{

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>

#include "globals.h"
#include "parser.h"
#include "basics.h"
#include "dfa.h"
#include "smart_ptr.h"

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
static RegExp           *spec = NULL, *specNone = NULL;
static RuleOpList       specStar;
static Scanner          *in = NULL;
static Scanner::ParseMode  parseMode;
static SetupMap            ruleSetupMap;
static Token               *ruleDefault = NULL;
static DefaultMap          ruleDefaultMap;
static bool                foundRules;

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
	const RegExp::InsAccess ins_access = clist->size() > 1
		? RegExp::PRIVATE
		: RegExp::SHARED;
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		//Str *condcpy = newcond ? new Str(*newcond) : newcond;
		Token *token = new Token(code, sourceFileInfo, newcond);//condcpy);
		RuleOp *rule = new RuleOp(expr, look, token, accept++, ins_access);

		RegExpMap::iterator itRE = specMap.find(*it);

		if (itRE != specMap.end())
		{
			itRE->second.second = mkAlt(itRE->second.second, rule);
		}
		else
		{
			size_t nIndex = specMap.size() + 1; // 0 is reserved for "0"-spec
			assert( nIndex < 1u << 31);
			specMap[*it] = std::make_pair(int(nIndex), rule);
		}
		
	}
	delete clist;
	delete newcond;
	delete code;
}

void setup_rule(CondList *clist, Token *code)
{
	assert(clist);
	assert(code);
	context_check(clist);
	if (bFirstPass)
	{
		for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
		{
			if (ruleSetupMap.find(*it) != ruleSetupMap.end())
			{
				in->fatalf_at(code->line, "code to setup rule '%s' is already defined", it->c_str());
			}
			ruleSetupMap[*it] = std::make_pair(code->line, code->text.to_string());
		}
	}
	delete clist;
	delete code;
}

void default_rule(CondList *clist, Token *code)
{
	assert(clist);
	assert(code);
	context_check(clist);
	if (bFirstPass)
	{
		for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
		{
			if (ruleDefaultMap.find(*it) != ruleDefaultMap.end())
			{
				in->fatalf_at(code->line, "code to default rule '%s' is already defined", it->c_str());
			}
			ruleDefaultMap[*it] = code;
		}
	}
	delete clist;
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
%token		CONFIG		VALUE	NUMBER	SETUP	FID

%type	<op>		CLOSE	STAR	SETUP
%type	<op>		close
%type	<extop>		CLOSESIZE
%type	<symbol>	ID	FID
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
		}
	|	spec rule
		{
			foundRules = true;
		}
	|	spec decl
;

decl:
		ID '=' expr ';'
		{
			if ($1->re)
			{
				in->fatal("sym already defined");
			}
			$3->ins_access = RegExp::PRIVATE;
			$1->re = $3;
		}
	|	FID expr
		{
			if ($1->re)
			{
				in->fatal("sym already defined");
			}
			$2->ins_access = RegExp::PRIVATE;
			$1->re = $2;
		}
	|	ID '=' expr '/'
		{
			in->fatal("trailing contexts are not allowed in named definitions");
		}
	|	FID expr '/'
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
			$$ = new RuleOp($1, $2, $3, accept++, RegExp::SHARED);
			spec = spec? mkAlt(spec, $$) : $$;
		}
	|	STAR CODE /* default rule */
		{
			if (cFlag)
				in->fatal("condition or '<*>' required when using -c switch");
			if (ruleDefault != NULL)
				in->fatal("code to default rule is already defined");
			else
				ruleDefault = $2;
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
			delete $5;
		}
	|	'<' cond '>' look ':' newcond
		{
			assert($6);
			context_none($2);
			delete $6;
		}
	|	'<' cond '>' STAR CODE /* default rule for conditions */
		{
			default_rule($2, $5);
		}
	|	'<' STAR '>' expr look newcond CODE
		{
			context_check(NULL);
			Token *token = new Token($7, $7->source, $7->line, $6);
			delete $7;
			delete $6;
			specStar.push_back(new RuleOp($4, $5, token, accept++, RegExp::PRIVATE));
		}
	|	'<' STAR '>' expr look ':' newcond
		{
			assert($7);
			context_check(NULL);
			Token *token = new Token(NULL, sourceFileInfo, $7);
			delete $7;
			specStar.push_back(new RuleOp($4, $5, token, accept++, RegExp::PRIVATE));
		}
	|	'<' STAR '>' look newcond CODE
		{
			context_none(NULL);
			delete $5;
		}
	|	'<' STAR '>' look ':' newcond
		{
			assert($6);
			context_none(NULL);
			delete $6;
		}
	|	'<' STAR '>' STAR CODE /* default rule for all conditions */
		{
			CondList *clist = new CondList();
			clist->insert("*");
			default_rule(clist, $5);
		}
	|	NOCOND newcond CODE
		{
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			Token *token = new Token($3, $3->source, $3->line, $2);
			delete $2;
			delete $3;
			$$ = specNone = new RuleOp(new NullOp(), new NullOp(), token, accept++, RegExp::SHARED);
		}
	|	NOCOND ':' newcond
		{
			assert($3);
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			Token *token = new Token(NULL, sourceFileInfo, $3);
			delete $3;
			$$ = specNone = new RuleOp(new NullOp(), new NullOp(), token, accept++, RegExp::SHARED);
		}
	|	SETUP STAR '>' CODE
		{
			CondList *clist = new CondList();
			clist->insert("*");
			setup_rule(clist, $4);
		}
	|	SETUP cond '>' CODE
		{
			setup_rule($2, $4);
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
	std::map<std::string, smart_ptr<DFA> >  dfa_map;
	ScannerState rules_state;

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
	
	Enc encodingOld = encoding;
	
	while ((parseMode = i.echo()) != Scanner::Stop)
	{
		bool bPrologBrace = false;
		ScannerState curr_state;

		i.save_state(curr_state);
		foundRules = false;

		if (rFlag && parseMode == Scanner::Rules && dfa_map.size())
		{
			in->fatal("cannot have a second 'rules:re2c' block");
		}
		if (parseMode == Scanner::Reuse)
		{
			if (dfa_map.empty())
			{
				in->fatal("got 'use:re2c' without 'rules:re2c'");
			}
		}
		else if (parseMode == Scanner::Rules)
		{
			i.save_state(rules_state);
		}
		else
		{
			dfa_map.clear();
		}
		accept = 0;
		spec = NULL;
		ruleDefault = NULL;
		in->set_in_parse(true);
		yyparse();
		in->set_in_parse(false);
		if (rFlag && parseMode == Scanner::Reuse)
		{
			if (foundRules || encoding != encodingOld)
			{
				// Re-parse rules
				parseMode = Scanner::Parse;
				i.restore_state(rules_state);
				i.reuse();
				dfa_map.clear();
				parse_cleanup();
				spec = NULL;
				accept = 0;
				ruleDefault = NULL;
				in->set_in_parse(true);
				yyparse();
				in->set_in_parse(false);

				// Now append potential new rules
				i.restore_state(curr_state);
				parseMode = Scanner::Parse;
				in->set_in_parse(true);
				yyparse();
				in->set_in_parse(false);
			}
			encodingOld = encoding;
		}
		if (cFlag)
		{
			RegExpMap::iterator it;
			SetupMap::const_iterator itRuleSetup;
			DefaultMap::const_iterator itRuleDefault;

			if (parseMode != Scanner::Reuse)
			{
				if (!specStar.empty())
				{
					for (it = specMap.begin(); it != specMap.end(); ++it)
					{
						assert(it->second.second);
						for (RuleOpList::const_iterator itOp = specStar.begin(); itOp != specStar.end(); ++itOp)
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
					for (it = specMap.begin(); it != specMap.end(); ++it)
					{
						it->second.first--;
					}
				}
			}

			size_t nCount = specMap.size();

			for (it = specMap.begin(); it != specMap.end(); ++it)
			{
				assert(it->second.second);

				if (parseMode != Scanner::Reuse)
				{
					itRuleSetup = ruleSetupMap.find(it->first);				
					if (itRuleSetup != ruleSetupMap.end())
					{
						yySetupRule = itRuleSetup->second.second;
					}
					else
					{
						itRuleSetup = ruleSetupMap.find("*");
						if (itRuleSetup != ruleSetupMap.end())
						{
							yySetupRule = itRuleSetup->second.second;
						}
						else
						{
							yySetupRule = "";
						}
					}
					itRuleDefault = ruleDefaultMap.find(it->first);
					if (itRuleDefault != ruleDefaultMap.end())
					{
						RuleOp * def = new RuleOp(in->mkDefault(), new NullOp(), itRuleDefault->second, accept++, RegExp::SHARED);
						it->second.second = it->second.second ? mkAlt(def, it->second.second) : def;
					}
					else
					{
						itRuleDefault = ruleDefaultMap.find("*");
						if (itRuleDefault != ruleDefaultMap.end())
						{
							RuleOp * def = new RuleOp(in->mkDefault(), new NullOp(), itRuleDefault->second, accept++, RegExp::SHARED);
							it->second.second = it->second.second ? mkAlt(def, it->second.second) : def;
						}
					}
					dfa_map[it->first] = genCode(it->second.second);
					dfa_map[it->first]->prepare();
				}
				if (parseMode != Scanner::Rules && dfa_map.find(it->first) != dfa_map.end())
				{
					dfa_map[it->first]->emit(o, topIndent, &specMap, it->first, !--nCount, bPrologBrace);
				}
			}
			if (!h && !bTypesDone)
			{
				genTypes(typesInline, 0, specMap);
			}
		}
		else
		{
			if (ruleDefault != NULL && parseMode != Scanner::Reuse)
			{
				RuleOp * def = new RuleOp(in->mkDefault(), new NullOp(), ruleDefault, accept++, RegExp::SHARED);
				spec = spec ? mkAlt(def, spec) : def;
			}
			if (spec || !dfa_map.empty())
			{
				if (parseMode != Scanner::Reuse)
				{
					dfa_map[""] = genCode(spec);
					dfa_map[""]->prepare();
				}
				if (parseMode != Scanner::Rules && dfa_map.find("") != dfa_map.end())
				{
					dfa_map[""]->emit(o, topIndent, NULL, "", 0, bPrologBrace);
				}
			}
		}
		o << sourceFileInfo;
		/* restore original char handling mode*/
		encoding = encodingOld;
	}

	if (cFlag)
	{
		SetupMap::const_iterator itRuleSetup;
		for (itRuleSetup = ruleSetupMap.begin(); itRuleSetup != ruleSetupMap.end(); ++itRuleSetup)
		{
			if (itRuleSetup->first != "*" && specMap.find(itRuleSetup->first) == specMap.end())
			{
				in->fatalf_at(itRuleSetup->second.first, "setup for non existing rule '%s' found", itRuleSetup->first.c_str());
			}
		}
		if (specMap.size() < ruleSetupMap.size())
		{
			uint line = in->get_cline();
			itRuleSetup = ruleSetupMap.find("*");
			if (itRuleSetup != ruleSetupMap.end())
			{
				line = itRuleSetup->second.first;
			}
			in->fatalf_at(line, "setup for all rules with '*' not possible when all rules are setup explicitly");
		}
	}

	if (h)
	{
		genHeader(*h, 0, specMap);
	}
	
	parse_cleanup();
	in = NULL;
}

void parse_cleanup()
{
	RegExp::vFreeList.clear();
	Range::vFreeList.clear();
	Symbol::ClearTable();
	specMap.clear();
	specStar.clear();
	specNone = NULL;
}

} // end namespace re2c
