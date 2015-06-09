#ifndef _re_h
#define _re_h

#include <iostream>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>

#include "src/dfa/ins.h"
#include "src/dfa/rule_rank.h"
#include "src/globals.h"
#include "src/parse/token.h"
#include "src/util/range.h"
#include "src/util/forbid_copy.h"
#include "src/util/free_list.h"

namespace re2c
{

typedef struct extop
{
	char op;
	int	minsize;
	int	maxsize;
}

ExtOp;

struct CharPtn
{
	uint32_t	card;
	CharPtn	*fix;
	CharPtn	*nxt;

	FORBID_COPY (CharPtn);
};

typedef CharPtn *CharPtr;

struct CharSet
{
	CharSet();
	~CharSet();

	CharPtn	*fix;
	CharPtn	*freeHead, **freeTail;
	CharPtr	*rep;
	CharPtn	*ptn;

	FORBID_COPY (CharSet);
};

class RegExp
{

public:
	uint32_t	size;

	/*
	 * There're several different cases when the same regexp
	 * can be used multiple times:
	 * 	1) named definitions, e.g. digit = [0-9];
	 * 	2) counted repetition, e.g. "a"{3}, "a"{3,}, "a"{3,5}
	 * 	3) multiple DFA's sharing the same regexp , e.g. <c1, c2> "abc" { }
	 * 	4) common suffixes, e.g. suffix [\x80-\xBF] in UTF-8 ranges
	 * In cases 1-3, regexp must be recompiled each time it's reused.
	 * In case 4, regexp should be compiled only once, and instructions
	 * should be shared in order to reduce space.
	 *
	 * Note: if regexp must always be recompiled, it doesn't imply that
	 * parts of this regexp must always be recompiled. It only forces
	 * the compilation function to traverse the regexp after compilation
	 * and reset compilation cache for each sub-regexp. E.g., for a regexp
	 * [^]{3} in UTF-8 mode, each of sub-regexps [^] will have common suffix
	 * [\x80-\xBF] factored out, but they won't share instructions.
	 */
	Ins*	ins_cache; /* if non-NULL, points to compiled instructions */
	enum InsAccess
		{ SHARED
		, PRIVATE
		} ins_access;

	static free_list<RegExp*> vFreeList;

public:
	RegExp()
		: size(0)
		, ins_cache(NULL)
		, ins_access(SHARED)
	{
		vFreeList.insert(this);
	}

	virtual ~RegExp()
	{
		vFreeList.erase(this);
	}

	virtual void split(CharSet&) = 0;
	virtual void calcSize(Char*) = 0;
	virtual uint32_t fixedLength();
	virtual uint32_t compile(Char*, Ins*) = 0;
	virtual void decompile() = 0;
	virtual void display(std::ostream&) const = 0;
	friend std::ostream& operator<<(std::ostream&, const RegExp&);
	friend std::ostream& operator<<(std::ostream&, const RegExp*);

	FORBID_COPY (RegExp);
};

inline std::ostream& operator<<(std::ostream &o, const RegExp &re)
{
	re.display(o);
	return o;
}

inline std::ostream& operator<<(std::ostream &o, const RegExp *re)
{
	return o << *re;
}

class NullOp: public RegExp
{

public:
	void split(CharSet&);
	void calcSize(Char*);
	uint32_t fixedLength();
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << "_";
	}
};

class MatchOp: public RegExp
{

public:
	Range	*match;

public:
	MatchOp(Range *m) : match(m)
	{
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint32_t fixedLength();
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream&) const;

	FORBID_COPY (MatchOp);
};

class RuleOp: public RegExp
{
private:
	RegExp   *exp;

public:
	RegExp   *ctx;
	Ins      *ins;
	rule_rank_t rank;
	Token    *code;
	uint32_t line;

public:
	RuleOp(RegExp*, RegExp*, Token*, rule_rank_t, InsAccess);

	~RuleOp()
	{
		delete code;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp << "/" << ctx << ";";
	}

	FORBID_COPY (RuleOp);
};

RegExp *doAlt(RegExp*, RegExp*);
RegExp *mkAlt(RegExp*, RegExp*);

class AltOp: public RegExp
{

private:
	RegExp	*exp1, *exp2;

public:
	AltOp(RegExp *e1, RegExp *e2)
		: exp1(e1)
		, exp2(e2)
	{
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint32_t fixedLength();
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp1 << "|" << exp2;
	}

	friend RegExp *mkAlt(RegExp*, RegExp*);

	FORBID_COPY (AltOp);
};

RegExp *doCat(RegExp*, RegExp*);
RegExp *mkCat(RegExp*, RegExp*);

class CatOp: public RegExp
{

private:
	RegExp	*exp1, *exp2;

public:
	CatOp(RegExp *e1, RegExp *e2)
		: exp1(e1)
		, exp2(e2)
	{
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint32_t fixedLength();
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp1 << exp2;
	}

	FORBID_COPY (CatOp);
};

class CloseOp: public RegExp
{

private:
	RegExp	*exp;

public:
	CloseOp(RegExp *e)
		: exp(e)
	{
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp << "+";
	}

	FORBID_COPY (CloseOp);
};

class CloseVOp: public RegExp
{

private:
	RegExp	*exp;
	int	min;
	int	max;

public:
	CloseVOp(RegExp *e, int lb, int ub)
		: exp(e)
		, min(lb)
		, max(ub)
	{
		exp->ins_access = PRIVATE;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint32_t compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp << "+";
	}

	FORBID_COPY (CloseVOp);
};

extern RegExp *mkDiff(RegExp*, RegExp*);
extern RegExp *mkAlt(RegExp*, RegExp*);

} // end namespace re2c

#endif
