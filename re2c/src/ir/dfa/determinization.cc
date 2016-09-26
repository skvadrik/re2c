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
static void reach(const kitem_t *kernel, size_t kcount, kitem_t *&r, uint32_t symbol);

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

void reach(const kitem_t *kernel, size_t kcount, kitem_t *&r, uint32_t symbol)
{
	for (size_t i = 0; i < kcount; ++i) {
		nfa_state_t
			*s = kernel[i].state,
			*t = transition(s, symbol);
		if (t) {
			r->state = t;
			r->tagidx = kernel[i].tagidx;
			++r;
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
	const size_t ntags = tags.size();
	const size_t nrules = rules.size();

	ord_hash_set_t kernels;
	kitem_t *rstart = new kitem_t[nfa.size], *rend = rstart;
	kitem_t *kstart = new kitem_t[nfa.size], *kend = kstart;
	bool *ktags = new bool[ntags]();
	bool *badtags = new bool[ntags]();
	bool *arctags = new bool[ntags];
	bool *mask = new bool[ntags];
	bool *fin = new bool[nrules];

	closure(kstart, kend, nfa.root, ktags, badtags, ntags);
	find_state(kstart, kend, kernels, tagpool);
	for (size_t i = 0; i < kernels.size(); ++i) {
		dfa_state_t *s = new dfa_state_t(nchars);
		states.push_back(s);

		const kitem_t *kernel;
		const size_t kcount = kernels.deref<const kitem_t>(i, kernel);

		for (size_t c = 0; c < nchars; ++c) {
			rend = rstart;
			reach(kernel, kcount, rend, charset[c]);

			kend = kstart;
			for (const kitem_t *r = rstart; r != rend; ++r) {
				closure(kstart, kend, r->state, ktags, badtags, ntags);
			}
			s->arcs[c] = find_state(kstart, kend, kernels, tagpool);

			memset(arctags, 0, ntags * sizeof(bool));
			memset(mask, 0, ntags * sizeof(bool));
			for (const kitem_t *r = rstart; r != rend; ++r) {
				merge_tags_with_mask(arctags, tagpool[r->tagidx], mask,
					tagpool[rules[r->state->rule].tags], badtags, ntags);
			}
			s->tags[c] = tagpool.insert(arctags);
		}

		memset(fin, 0, nrules * sizeof(bool));
		memset(arctags, 0, ntags * sizeof(bool));
		memset(mask, 0, ntags * sizeof(bool));
		for (size_t j = 0; j < kcount; ++j) {
			nfa_state_t *n = kernel[j].state;
			if (n->type == nfa_state_t::FIN) {
				merge_tags_with_mask(arctags, tagpool[kernel[j].tagidx], mask,
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

	delete[] rstart;
	delete[] kstart;
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

