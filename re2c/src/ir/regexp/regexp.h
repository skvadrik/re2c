#ifndef _RE2C_IR_REGEXP_REGEXP_
#define _RE2C_IR_REGEXP_REGEXP_

#include "src/util/c99_stdint.h"
#include <set>
#include <vector>

#include "src/parse/rules.h"
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
		RULE
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
			const RegExp *re;
			const RegExp *ctx;
			RuleInfo *info;
		} rule;
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
	static const RegExp *rule(const Loc &loc, const RegExp *r1, const RegExp *r2,
		rule_rank_t rank, const Code *code, const std::string *newcond);
	static const RegExp *rule_copy(const RegExp *rule, rule_rank_t rank);
	inline ~RegExp()
	{
		if (tag == RULE) {
			delete pld.rule.info;
		}
		flist.erase(this);
	}

private:
	inline RegExp(tag_t t) : tag(t), pld()
	{
		flist.insert(this);
	}
};

void split(const RegExp *re, std::set<uint32_t> &cs);
void nullable_rules(const RegExp *re, std::vector<RuleInfo*> &rs);

const RegExp *mkAlt(const RegExp *re1, const RegExp *re2);
const RegExp *doAlt(const RegExp *re1, const RegExp *re2);
const RegExp *doCat(const RegExp *re1, const RegExp *re2);
const RegExp *repeat(const RegExp *re, uint32_t n);
const RegExp *repeat_from_to(const RegExp *re, uint32_t n, uint32_t m);
const RegExp *repeat_from(const RegExp *re, uint32_t n);

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_
