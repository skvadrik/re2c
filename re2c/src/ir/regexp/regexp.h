#ifndef _RE2C_IR_REGEXP_REGEXP_
#define _RE2C_IR_REGEXP_REGEXP_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <vector>

#include "src/conf/warn.h"
#include "src/ir/rule.h"
#include "src/util/free_list.h"
#include "src/util/range.h"

namespace re2c
{

struct RegExp
{
	static free_list<RegExp*> flist;
	static const uint32_t MANY;

	enum type_t {NIL, SYM, ALT, CAT, ITER, TAG, CAP, REF} type;
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
		struct
		{
			const RegExp *re;
			uint32_t min;
			uint32_t max;
		} iter;
		const std::string *tag;
		const RegExp *cap;
		struct
		{
			const RegExp *re;
			const std::string *name;
		} ref;
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
	static const RegExp *make_iter(const RegExp *r, uint32_t n, uint32_t m)
	{
		RegExp *re = new RegExp(ITER);
		re->iter.re = r;
		re->iter.min = n;
		re->iter.max = m;
		return re;
	}
	static const RegExp *make_tag(const std::string *t)
	{
		RegExp *re = new RegExp(TAG);
		re->tag = t;
		return re;
	}
	static const RegExp *make_cap(const RegExp *r)
	{
		RegExp *re = new RegExp(CAP);
		re->cap = r;
		return re;
	}
	static const RegExp *make_ref(const RegExp *r, const std::string &n)
	{
		RegExp *re = new RegExp(REF);
		re->ref.re = r;
		re->ref.name = new std::string(n);
		return re;
	}
	inline ~RegExp()
	{
		flist.erase(this);
		if (type == TAG) {
			delete tag;
		} else if (type == REF) {
			delete ref.name;
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
	const RegExp *re;
	const Code *code;

	RegExpRule(const RegExp *r, const Code *c)
		: re(r)
		, code(c)
	{}
};

const RegExp *mkAlt(const RegExp *re1, const RegExp *re2);
const RegExp *doAlt(const RegExp *re1, const RegExp *re2);
const RegExp *doCat(const RegExp *re1, const RegExp *re2);
bool need_wrap(const RegExp *re);

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_
