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
	static free_list<RegExp*> flist;
	static const size_t NO_TAG;

	enum type_t {NIL, SYM, ALT, CAT, ITER, TAG} type;
	union
	{
		const Range *sym;
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
		const RegExp *iter;
		const std::string *tag;
	};

	static const RegExp *make_nil()
	{
		return new RegExp(NIL);
	}
	static const RegExp *make_sym(const Range *r)
	{
		RegExp *re = new RegExp(SYM);
		re->sym = r;
		return re;
	}
	static const RegExp *make_alt(const RegExp *r1, const RegExp *r2)
	{
		RegExp *re = new RegExp(ALT);
		re->alt.re1 = r1;
		re->alt.re2 = r2;
		return re;
	}
	static const RegExp *make_cat(const RegExp *r1, const RegExp *r2)
	{
		RegExp *re = new RegExp(CAT);
		re->cat.re1 = r1;
		re->cat.re2 = r2;
		return re;
	}
	static const RegExp *make_iter(const RegExp *r)
	{
		RegExp *re = new RegExp(ITER);
		re->iter = r;
		return re;
	}
	static const RegExp *make_tag(const std::string *t)
	{
		RegExp *re = new RegExp(TAG);
		re->tag = t;
		return re;
	}
	inline ~RegExp()
	{
		flist.erase(this);
		if (type == TAG) {
			delete tag;
		}
	}

private:
	inline RegExp(type_t t) : type(t)
	{
		flist.insert(this);
	}
};

struct RegExpRule
{
	static free_list<RegExpRule*> flist;

	const RegExp *re;
	RuleInfo *info;

	explicit RegExpRule(const RegExp *r): re(r), info(NULL)
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
