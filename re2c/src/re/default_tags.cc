#include <stddef.h>
#include <vector>

#include "src/re/re.h"

namespace re2c {

// Fictive tags do not really need default counterparts:
// maximization can work without them based on version numbers.
// For now it does not seem like a useful optimization, but some day
// in future it might change.
static void insert_default_tags(RESpec &spec, RE *re, size_t *&tidx)
{
	RE::alc_t &alc = spec.alc;
	switch (re->type) {
		case RE::NIL: break;
		case RE::SYM: break;
		case RE::ALT: {
			size_t *i = tidx;
			RE *x = NULL, *y = NULL;
			insert_default_tags(spec, re->alt.re1, tidx);
			for (; i < tidx; ++i) {
				x = re_cat(alc, x, re_tag(alc, *i, true));
			}
			insert_default_tags(spec, re->alt.re2, tidx);
			for (; i < tidx; ++i) {
				y = re_cat(alc, y, re_tag(alc, *i, true));
			}
			re->alt.re1 = re_cat(alc, re->alt.re1, y);
			re->alt.re2 = spec.opts->posix_captures
				? re_cat(alc, x, re->alt.re2)
				: re_cat(alc, re->alt.re2, x);
			break;
		}
		case RE::CAT:
			insert_default_tags(spec, re->cat.re1, tidx);
			insert_default_tags(spec, re->cat.re2, tidx);
			break;
		case RE::ITER:
			insert_default_tags(spec, re->iter.re, tidx);
			break;
		case RE::TAG:
			*tidx++ = re->tag.idx;
			break;
	}
}

void insert_default_tags(RESpec &spec)
{
	size_t *tidx0 = new size_t[spec.tags.size()], *tidx = tidx0;
	std::vector<RE*>::iterator
		i = spec.res.begin(),
		e = spec.res.end();
	for (; i != e; ++i) {
		insert_default_tags(spec, *i, tidx);
	}
	delete[] tidx0;
}

} // namespace re2c
