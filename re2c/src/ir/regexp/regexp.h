#ifndef _RE2C_IR_REGEXP_REGEXP_
#define _RE2C_IR_REGEXP_REGEXP_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <vector>

#include "src/ir/rule.h"
#include "src/util/free_list.h"
#include "src/util/range.h"

namespace re2c
{

struct nfa_state_t;
struct nfa_t;

typedef std::vector<uint32_t> charset_t;

struct RegExp
{
	enum tag_t
	{
		NIL,
		SYM,
		ALT,
		CAT,
		ITER,
		TAG
	};
	union payload_t
	{
		struct
		{
			const Range *range;
		} sym;
		struct
		{
			const RegExp *re1;
			const RegExp *re2;
		} alt;
		struct
		{
			const RegExp *re1;
			const RegExp *re2;
		} cat;
		struct
		{
			const RegExp *re;
		} iter;
		struct
		{
			const std::string *name;
			size_t idx;
		} ctx;
	};

	static free_list<RegExp*> flist;

	tag_t tag;
	payload_t pld;

	static const RegExp *nil()
	{
		return new RegExp(NIL);
	}
	static const RegExp *sym(const Range *r)
	{
		RegExp *re = new RegExp(SYM);
		re->pld.sym.range = r;
		return re;
	}
	static const RegExp *alt(const RegExp *r1, const RegExp *r2)
	{
		RegExp *re = new RegExp(ALT);
		re->pld.alt.re1 = r1;
		re->pld.alt.re2 = r2;
		return re;
	}
	static const RegExp *cat(const RegExp *r1, const RegExp *r2)
	{
		RegExp *re = new RegExp(CAT);
		re->pld.cat.re1 = r1;
		re->pld.cat.re2 = r2;
		return re;
	}
	static const RegExp *iter(const RegExp *r)
	{
		RegExp *re = new RegExp(ITER);
		re->pld.iter.re = r;
		return re;
	}
	static const RegExp *ctx(const std::string *n)
	{
		RegExp *re = new RegExp(TAG);
		re->pld.ctx.name = n;
		re->pld.ctx.idx = ~0u;
		return re;
	}
	inline ~RegExp()
	{
		flist.erase(this);
	}

private:
	inline RegExp(tag_t t) : tag(t), pld()
	{
		flist.insert(this);
	}
};

struct RegExpRule
{
	static free_list<RegExpRule*> flist;

	const RegExp *re;
	RuleInfo *info;

	RegExpRule(const RegExp* r)
		: re(r)
		, info(NULL)
	{
		flist.insert(this);
	}
	~RegExpRule()
	{
		delete info;
		flist.erase(this);
	}

	FORBID_COPY(RegExpRule);
};

void split(const std::vector<const RegExpRule*> &rs, std::set<uint32_t> &cs);
const RegExp *mkAlt(const RegExp *re1, const RegExp *re2);
const RegExp *doAlt(const RegExp *re1, const RegExp *re2);
const RegExp *doCat(const RegExp *re1, const RegExp *re2);
const RegExp *repeat(const RegExp *re, uint32_t n);
const RegExp *repeat_from_to(const RegExp *re, uint32_t n, uint32_t m);
const RegExp *repeat_from(const RegExp *re, uint32_t n);

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_
