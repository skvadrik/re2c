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

const size_t dfa_t::NIL = std::numeric_limits<size_t>::max();

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
	const size_t mask_size = (nchars + 1) * ntags;

	ord_hash_set_t kernels;
	kitem_t *kstart = new kitem_t[nfa.size], *kend = kstart;
	bool *ktags = new bool[ntags]();
	bool *badtags = new bool[ntags]();
	bool *arctags = new bool[mask_size];
	bool *mask = new bool[mask_size];
	bool *fin = new bool[nrules];
	std::vector<nfa_state_t*> *arcs = new std::vector<nfa_state_t*>[nchars];

	closure(kstart, kend, nfa.root, ktags, badtags, ntags);
	find_state(kstart, kend, kernels, tagpool);
	for (size_t i = 0; i < kernels.size(); ++i) {
		memset(fin, 0, nrules * sizeof(bool));
		memset(arctags, 0, mask_size * sizeof(bool));
		memset(mask, 0, mask_size * sizeof(bool));
		for(size_t c = 0; c < nchars; ++c) {
			arcs[c].clear();
		}

		dfa_state_t *s = new dfa_state_t(nchars);
		states.push_back(s);

		const kitem_t *kernel;
		const size_t kcount = kernels.deref<const kitem_t>(i, kernel);
		for (size_t j = 0; j < kcount; ++j) {
			nfa_state_t *n = kernel[j].state;
			const bool *newtags = tagpool[kernel[j].tagidx];
			switch (n->type) {
				case nfa_state_t::RAN: {
					nfa_state_t *m = n->ran.out;
					size_t c = 0;
					for (const Range *r = n->ran.ran; r; r = r->next ()) {
						for (; charset[c] != r->lower(); ++c);
						for (; charset[c] != r->upper(); ++c) {
							merge_tags_with_mask(&arctags[c * ntags], newtags,
								&mask[c * ntags], tagpool[rules[m->rule].tags],
								badtags, ntags);
							arcs[c].push_back(m);
						}
					}
					break;
				}
				case nfa_state_t::FIN:
					merge_tags_with_mask(&arctags[nchars * ntags], newtags,
						&mask[nchars * ntags], tagpool[rules[n->rule].tags],
						badtags, ntags);
					fin[n->rule] = true;
					break;
				default:
					assert(false);
					break;
			}
		}

		for (size_t c = 0; c < nchars; ++c) {
			kend = kstart;
			const std::vector<nfa_state_t*> &a = arcs[c];
			for (size_t j = 0; j < a.size(); ++j) {
				closure(kstart, kend, a[j], ktags, badtags, ntags);
			}
			s->arcs[c] = find_state(kstart, kend, kernels, tagpool);
			s->tags[c] = tagpool.insert(&arctags[c * ntags]);
		}
		s->rule_tags = tagpool.insert(&arctags[nchars * ntags]);

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

	delete[] kstart;
	delete[] ktags;
	delete[] badtags;
	delete[] arctags;
	delete[] mask;
	delete[] fin;
	delete[] arcs;
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

