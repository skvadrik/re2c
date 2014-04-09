/* $Id$ */
#ifndef _re_h
#define _re_h

#include <iostream>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>
#include "token.h"
#include "ins.h"
#include "free_list.h"
#include "globals.h"
#include "range.h"
#include "smart_ptr.h"

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
	uint	card;
	CharPtn	*fix;
	CharPtn	*nxt;
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
};

class RegExp
{

public:
	uint	size;

	/*
	 * There're several different cases when the same regexp
	 * can be used multiple times:
	 * 	1) named definitions, e.g. digit = [0-9];
	 * 	2) counted repetition, e.g. "a"{3}, "a"{3,}, "a"{3,5}
	 * 	3) multiple DFA's sharing the same regexp , e.g. <c1, c2> "abc" { }
	 * 	3) common suffixes, e.g. suffix [\x80-\xBF] in UTF-8 ranges
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

	virtual const char *typeOf() = 0;
	RegExp *isA(const char *t)
	{
		return typeOf() == t ? this : NULL;
	}

	virtual void split(CharSet&) = 0;
	virtual void calcSize(Char*) = 0;
	virtual uint fixedLength();
	virtual uint compile(Char*, Ins*) = 0;
	virtual void decompile() = 0;
	virtual void display(std::ostream&) const = 0;
	friend std::ostream& operator<<(std::ostream&, const RegExp&);
	friend std::ostream& operator<<(std::ostream&, const RegExp*);
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
	static const char *type;

public:
	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint fixedLength();
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << "_";
	}
};

class MatchOp: public RegExp
{

public:
	static const char *type;
	Range	*match;

public:
	MatchOp(Range *m) : match(m)
	{
	}

	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint fixedLength();
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream&) const;

#ifdef PEDANTIC
private:
	MatchOp(const MatchOp& oth)
		: RegExp(oth)
		, match(oth.match)
	{
	}
	
	MatchOp& operator = (const MatchOp& oth)
	{
		new(this) MatchOp(oth);
		return *this;
	}
#endif
};

class RuleOp: public RegExp
{
public:
	static const char *type;

private:
	RegExp   *exp;

public:
	RegExp   *ctx;
	Ins      *ins;
	uint     accept;
	Token    *code;
	uint     line;

public:
	RuleOp(RegExp*, RegExp*, Token*, uint, InsAccess);

	~RuleOp()
	{
		delete code;
	}

	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp << "/" << ctx << ";";
	}
	RuleOp* copy(uint) const;

#ifdef PEDANTIC
private:
	RuleOp(const RuleOp& oth)
		: RegExp(oth)
		, exp(oth.exp)
		, ctx(oth.ctx)
		, ins(oth.ins)
		, accept(oth.accept)
		, code(oth.code)
		, line(oth.line)
	{
	}

	RuleOp& operator = (const RuleOp& oth)
	{
		new(this) RuleOp(oth);
		return *this;
	}
#endif
};

class RuleLine: public line_number
{
public:

	RuleLine(const RuleOp& _op)
		: op(_op)
	{
	}

	uint get_line() const
	{
		return op.code->line;
	}

	const RuleOp& op;
};

RegExp *doAlt(RegExp*, RegExp*);
RegExp *mkAlt(RegExp*, RegExp*);

class AltOp: public RegExp
{

private:
	RegExp	*exp1, *exp2;

public:
	static const char *type;

public:
	AltOp(RegExp *e1, RegExp *e2)
		: exp1(e1)
		, exp2(e2)
	{
	}

	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint fixedLength();
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp1 << "|" << exp2;
	}

	friend RegExp *mkAlt(RegExp*, RegExp*);

#ifdef PEDANTIC
private:
	AltOp(const AltOp& oth)
		: RegExp(oth)
		, exp1(oth.exp1)
		, exp2(oth.exp2)
	{
	}
	AltOp& operator = (const AltOp& oth)
	{
		new(this) AltOp(oth);
		return *this;
	}
#endif
};

RegExp *doCat(RegExp*, RegExp*);
RegExp *mkCat(RegExp*, RegExp*);

class CatOp: public RegExp
{

private:
	RegExp	*exp1, *exp2;

public:
	static const char *type;

public:
	CatOp(RegExp *e1, RegExp *e2)
		: exp1(e1)
		, exp2(e2)
	{
	}

	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint fixedLength();
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp1 << exp2;
	}

#ifdef PEDANTIC
private:
	CatOp(const CatOp& oth)
		: RegExp(oth)
		, exp1(oth.exp1)
		, exp2(oth.exp2)
	{
	}
	CatOp& operator = (const CatOp& oth)
	{
		new(this) CatOp(oth);
		return *this;
	}
#endif
};

class CloseOp: public RegExp
{

private:
	RegExp	*exp;

public:
	static const char *type;

public:
	CloseOp(RegExp *e)
		: exp(e)
	{
	}

	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp << "+";
	}

#ifdef PEDANTIC
private:
	CloseOp(const CloseOp& oth)
		: RegExp(oth)
		, exp(oth.exp)
	{
	}
	CloseOp& operator = (const CloseOp& oth)
	{
		new(this) CloseOp(oth);
		return *this;
	}
#endif
};

class CloseVOp: public RegExp
{

private:
	RegExp	*exp;
	int	min;
	int	max;

public:
	static const char *type;

public:
	CloseVOp(RegExp *e, int lb, int ub)
		: exp(e)
		, min(lb)
		, max(ub)
	{
		exp->ins_access = PRIVATE;
	}

	const char *typeOf()
	{
		return type;
	}

	void split(CharSet&);
	void calcSize(Char*);
	uint compile(Char*, Ins*);
	void decompile();
	void display(std::ostream &o) const
	{
		o << exp << "+";
	}
#ifdef PEDANTIC
private:
	CloseVOp(const CloseVOp& oth)
		: RegExp(oth)
		, exp(oth.exp)
		, min(oth.min)
		, max(oth.max)
	{
	}
	CloseVOp& operator = (const CloseVOp& oth)
	{
		new(this) CloseVOp(oth);
		return *this;
	}
#endif
};

typedef std::set<std::string>           CondList;
typedef std::pair<int, RegExp*>         NRegExp;
typedef std::map<std::string, NRegExp>  RegExpMap;
typedef std::vector<std::string>        RegExpIndices;
typedef std::list<RuleOp*>              RuleOpList;
typedef std::pair<uint, std::string>    LineCode;
typedef std::map<std::string, LineCode> SetupMap;
typedef std::map<std::string, Token*>   DefaultMap;

class DFA;

extern smart_ptr<DFA> genCode(RegExp*);
extern void genGetStateGoto(std::ostream&, uint&, uint);
extern void genCondTable(std::ostream&, uint, const RegExpMap&);
extern void genCondGoto(std::ostream&, uint, const RegExpMap&);
extern void genTypes(std::string&, uint, const RegExpMap&);
extern void genHeader(std::ostream&, uint, const RegExpMap&);

extern RegExp *mkDiff(RegExp*, RegExp*);
extern RegExp *mkAlt(RegExp*, RegExp*);

} // end namespace re2c

#endif
