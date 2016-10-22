#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static void rename(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new, bool unify);

void tag_renaming(dfa_t &dfa, const tagver_t *ver2new, tagver_t maxver)
{
	const tagver_t oldmax = static_cast<tagver_t>(dfa.tags.size());
	if (maxver >= oldmax) {
		assert(maxver == oldmax);
		return;
	}

	Tagpool &tagpool = dfa.tagpool;
	const size_t
		nstates = dfa.states.size(),
		nrule = dfa.rules.size();

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			rename(tagpool, s->tags[c].set, ver2new, true);
			rename(tagpool, s->tags[c].copy, ver2new, true);
		}
		rename(tagpool, s->rule_tags.set, ver2new, true);
		rename(tagpool, s->rule_tags.copy, ver2new, true);
	}
	rename(dfa.tagpool, dfa.copy_tags, ver2new, true);
	for (size_t i = 0; i < nrule; ++i) {
		rename(tagpool, dfa.rules[i].tags, ver2new, false);
	}
}

void rename(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new,
	bool unify)
{
	if (tags == ZERO_TAGS) return;

	const tagver_t *oldver = tagpool[tags];
	tagver_t *newver = tagpool.buffer1;
	const size_t ntag = tagpool.ntags;

	for (size_t t = 0; t < ntag; ++t) {
		const tagver_t v = oldver[t];
		newver[t] = v != TAGVER_ZERO
			? ver2new[v]
			: v;
	}

	// for transition tags, we don't care how versions map to
	// tags: identical sets of versions should compare equal
	// this doesn't apply to final tag versions in rules
	if (unify) {
		tagver_t *e = newver + ntag;
		std::sort(newver, e);
		std::fill(std::unique(newver, e), e, TAGVER_ZERO);
	}

	tags = tagpool.insert(newver);
}

} // namespace re2c

