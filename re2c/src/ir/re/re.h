#ifndef _RE2C_IR_RE_RE_
#define _RE2C_IR_RE_RE_

#include "src/util/c99_stdint.h"

#include "src/conf/opt.h"
#include "src/ir/rule.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"
#include "src/util/slab_allocator.h"

namespace re2c
{

struct RE
{
	typedef slab_allocator_t<~0u, 4096> alc_t;
	enum type_t {NIL, SYM, ALT, CAT, ITER, TAG} type;
	union {
		const Range *sym;
		struct {
			RE *re1;
			RE *re2;
		} alt;
		struct {
			RE *re1;
			RE *re2;
		} cat;
		struct {
			RE *re;
			uint32_t min;
			uint32_t max;
		} iter;
		struct {
			size_t idx;
			bool bottom;
		} tag;
	};
};

struct RESpec
{
	RE::alc_t alc;
	std::vector<RE*> res;
	std::vector<uint32_t> &charset;
	std::vector<Tag> &tags;
	std::valarray<Rule> &rules;

	explicit RESpec(const std::vector<RegExpRule> &ast);
};

void split_charset(RESpec &spec, const opt_t *opts);
void find_fixed_tags(RESpec &spec, const opt_t *opts);
void insert_default_tags(RESpec &spec);
void warn_nullable(const RESpec &spec, const std::string &cond, Warn &warn);

inline RE *re_nil(RE::alc_t &alc)
{
	RE *x = alc.alloct<RE>(1);
	x->type = RE::NIL;
	return x;
}

inline RE *re_sym(RE::alc_t &alc, const Range *r)
{
	RE *x = alc.alloct<RE>(1);
	x->type = RE::SYM;
	x->sym = r;
	return x;
}

inline RE *re_alt(RE::alc_t &alc, RE *x, RE *y)
{
	if (!x) return y;
	if (!y) return x;

	RE *z = alc.alloct<RE>(1);
	z->type = RE::ALT;
	z->alt.re1 = x;
	z->alt.re2 = y;
	return z;
}

inline RE *re_cat(RE::alc_t &alc, RE *x, RE *y)
{
	if (!x) return y;
	if (!y) return x;

	RE *z = alc.alloct<RE>(1);
	z->type = RE::CAT;
	z->cat.re1 = x;
	z->cat.re2 = y;
	return z;
}

inline RE *re_iter(RE::alc_t &alc, RE *x, uint32_t n, uint32_t m)
{
	RE *y = alc.alloct<RE>(1);
	y->type = RE::ITER;
	y->iter.re = x;
	y->iter.min = n;
	y->iter.max = m;
	return y;
}

inline RE *re_tag(RE::alc_t &alc, size_t i, bool b)
{
	RE *x = alc.alloct<RE>(1);
	x->type = RE::TAG;
	x->tag.idx = i;
	x->tag.bottom = b;
	return x;
}

} // namespace re2c

#endif // _RE2C_IR_RE_RE_
