#include <algorithm>
#include <limits>
#include <vector>

#include "src/conf/warn.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/dfa/closure.h"
#include "src/ir/dfa/find_state.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"
#include "src/globals.h"

namespace re2c
{

static nfa_state_t *transition(nfa_state_t *state, uint32_t symbol);
static void reach(const closure_t &clos1, closure_t &clos2, uint32_t symbol);

const size_t dfa_t::NIL = std::numeric_limits<size_t>::max();

nfa_state_t *transition(nfa_state_t *state, uint32_t symbol)
{
	if (state->type != nfa_state_t::RAN) {
		return NULL;
	}
	for (const Range *r = state->ran.ran; r; r = r->next()) {
		if ((r->lower() <= symbol) && (symbol < r->upper())) {
			return state->ran.out;
		}
	}
	return NULL;
}

void reach(const closure_t &clos1, closure_t &clos2, uint32_t symbol)
{
	clos2.clear();
	for (cclositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		nfa_state_t
			*s1 = c->state,
			*s2 = transition(s1, symbol);
		if (s2) {
			clos2.push_back(clos_t(s2, c->tagidx));
		}
	}
}

static void merge_tags_with_mask(bool *oldtags, const bool *newtags,
	bool *oldmask, const bool *newmask,
	bool *badtags, size_t ntags)
{
	for (size_t i = 0; i < ntags; ++i) {
		badtags[i] |= oldmask[i] & newmask[i] & (oldtags[i] ^ newtags[i]);
		oldtags[i] |= newtags[i];
		oldmask[i] |= newmask[i];
	}
}

dfa_t::dfa_t(const nfa_t &nfa,
	const charset_t &charset,
	const std::string &cond)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
	, rules(nfa.rules)
	, tags(*nfa.tags)
	, tagpool(*nfa.tagpool)
{
	clospool_t clospool;
	closure_t clos1, clos2;
	const size_t ntags = tags.size();
	const size_t nrules = rules.size();
	bool *ktags = new bool[ntags]();
	bool *badtags = new bool[ntags]();
	bool *arctags = new bool[ntags];
	bool *mask = new bool[ntags];
	bool *fin = new bool[nrules];

	clos1.push_back(clos_t(nfa.root, static_cast<size_t>(0)));
	closure(clos1, clos2, ktags, badtags, ntags);
	find_state(clos2, clospool, tagpool);

	for (size_t i = 0; i < clospool.size(); ++i) {
		const closure_t &clos0 = clospool[i];
		dfa_state_t *s = new dfa_state_t(nchars);
		states.push_back(s);

		for (size_t c = 0; c < nchars; ++c) {
			reach(clos0, clos1, charset[c]);
			closure(clos1, clos2, ktags, badtags, ntags);
			s->arcs[c] = find_state(clos2, clospool, tagpool);

			memset(arctags, 0, ntags * sizeof(bool));
			memset(mask, 0, ntags * sizeof(bool));
			for (cclositer_t p = clos1.begin(); p != clos1.end(); ++p) {
				merge_tags_with_mask(arctags, tagpool[p->tagidx], mask,
					tagpool[rules[p->state->rule].tags], badtags, ntags);
			}
			s->tags[c] = tagpool.insert(arctags);
		}

		memset(fin, 0, nrules * sizeof(bool));
		memset(arctags, 0, ntags * sizeof(bool));
		memset(mask, 0, ntags * sizeof(bool));
		for (cclositer_t p = clos0.begin(); p != clos0.end(); ++p) {
			nfa_state_t *n = p->state;
			if (n->type == nfa_state_t::FIN) {
				merge_tags_with_mask(arctags, tagpool[p->tagidx], mask,
					tagpool[rules[n->rule].tags], badtags, ntags);
				fin[n->rule] = true;
			}
		}
		s->rule_tags = tagpool.insert(arctags);
		// choose the first rule (the one with smallest rank)
		size_t r;
		for (r = 0; r < nrules; ++r) {
			if (fin[r]) {
				s->rule = r;
				break;
			}
		}
		// mark other rules as shadowed by this one
		for (++r; r < nrules; ++r) {
			if (fin[r]) {
				rules[r].shadow.insert(rules[s->rule].info->loc.line);
			}
		}
	}

	for (size_t i = 0; i < ntags; ++i) {
		if (badtags[i]) {
			warn.nondeterministic_tags(rules[tags[i].rule].info->loc.line,
				cond, tags[i].name);
		}
	}

	delete[] ktags;
	delete[] badtags;
	delete[] arctags;
	delete[] mask;
	delete[] fin;
}

dfa_t::~dfa_t()
{
	std::vector<dfa_state_t*>::iterator
		i = states.begin(),
		e = states.end();
	for (; i != e; ++i)
	{
		delete *i;
	}
}

} // namespace re2c

