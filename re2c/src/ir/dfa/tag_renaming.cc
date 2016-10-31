#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static void rename_rule(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new);
static void rename_save(tagsave_t **psave, const tagver_t *ver2new);
static void rename_copy(tagcopy_t **pcopy, const tagver_t *ver2new);

void tag_renaming(dfa_t &dfa, const tagver_t *ver2new, tagver_t maxver)
{
	tagver_t &oldmax = dfa.maxtagver;
	if (maxver >= oldmax) {
		assert(maxver == oldmax);
		return;
	}
	oldmax = maxver;

	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars,
		nrule = dfa.rules.size();

	for (size_t i = 0; i < nstate; ++i) {
		dfa_state_t *s = dfa.states[i];

		for (size_t c = 0; c < nsym; ++c) {
			tagcmd_t &cmd = s->tags[c];
			rename_save(&cmd.save, ver2new);
			rename_copy(&cmd.copy, ver2new);
		}

		tagcmd_t &cmd = s->rule_tags;
		rename_save(&cmd.save, ver2new);
		rename_copy(&cmd.copy, ver2new);
	}

	for (size_t i = 0; i < nrule; ++i) {
		rename_rule(dfa.tagpool, dfa.rules[i].tags, ver2new);
	}
}

void rename_rule(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new)
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

	tags = tagpool.insert(newver);
}

void rename_save(tagsave_t **psave, const tagver_t *ver2new)
{
	for (tagsave_t *p = *psave; p; p = p->next) {
		p->ver = ver2new[p->ver];
	}
}

void rename_copy(tagcopy_t **pcopy, const tagver_t *ver2new)
{
	for (tagcopy_t *c, **pc = pcopy; (c = *pc);) {
		c->lhs = ver2new[c->lhs];
		c->rhs = ver2new[c->rhs];
		if (c->lhs == c->rhs) {
			*pc = c->next;
		} else {
			pc = &c->next;
		}
	}
}

} // namespace re2c

