#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static void rename_rule(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new);
static void rename_save(tagsave_t **psave, const tagver_t *ver2new);
static void rename_copy(tagcopy_t **pcopy, const tagver_t *ver2new);

void tag_renaming(cfg_t &cfg, const tagver_t *ver2new, tagver_t maxver)
{
	tagver_t &oldmax = cfg.dfa.maxtagver;
	if (maxver >= oldmax) {
		assert(maxver == oldmax);
		return;
	}
	oldmax = maxver;

	cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbblock;
	for (; b < e; ++b) {
		rename_save(&b->cmd->save, ver2new);
		rename_copy(&b->cmd->copy, ver2new);
	}

	std::valarray<Rule> &rules = cfg.dfa.rules;
	Tagpool &tagpool = cfg.dfa.tagpool;
	for (size_t i = 0; i < rules.size(); ++i) {
		rename_rule(tagpool, rules[i].tags, ver2new);
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

