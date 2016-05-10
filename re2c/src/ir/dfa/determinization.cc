#include <algorithm>
#include <limits>
#include <vector>

#include "src/conf/warn.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"
#include "src/globals.h"

namespace re2c
{

const size_t dfa_t::NIL = std::numeric_limits<size_t>::max();

static void merge_tags(bool *oldtags, const bool *newtags,
	bool *badtags, size_t ntags)
{
	for (size_t i = 0; i < ntags; ++i) {
		badtags[i] |= oldtags[i] ^ newtags[i];
		oldtags[i] |= newtags[i];
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

struct kitem_t
{
	nfa_state_t *state;
	union
	{
		bool *tagptr;
		size_t tagidx;
	};

	static bool compare(const kitem_t &k1, const kitem_t &k2)
	{
		return k1.state < k2.state
			|| (k1.state == k2.state && k1.tagidx < k2.tagidx);
	}
};

/* note [epsilon-closures in tagged NFA]
 *
 * DFA state is a set of NFA states.
 * However, DFA state includes not all NFA states that are in
 * epsilon-closure (NFA states that have only epsilon-transitions
 * and are not final states are omitted).
 * The included states are called 'kernel' states.
 *
 * For tagged NFA we have to trace all epsilon-paths to each
 * kernel state, accumulate tags along the way and compare
 * resulting tag sets: if they differ, then NFA is tagwise
 * ambiguous. All tags are merged together; ambiguity is reported.
 */
static void closure(kitem_t *const kernel, kitem_t *&kend,
	nfa_state_t *n, bool *tags, bool *badtags, size_t ntags)
{
	if (n->mark) {
		return;
	}

	n->mark = true;
	switch (n->type) {
		case nfa_state_t::ALT:
			closure(kernel, kend, n->value.alt.out2, tags, badtags, ntags);
			closure(kernel, kend, n->value.alt.out1, tags, badtags, ntags);
			break;
		case nfa_state_t::TAG: {
			const size_t t = n->value.tag.info;
			const bool old = tags[t];
			tags[t] = true;
			closure(kernel, kend, n->value.tag.out, tags, badtags, ntags);
			tags[t] = old;
			break;
		}
		case nfa_state_t::RAN:
		case nfa_state_t::FIN: {
			kitem_t *k = kernel;
			while (k != kend && k->state != n) ++k;
			if (k == kend) {
				kend->state = n;
				kend->tagptr = new bool[ntags];
				memcpy(kend->tagptr, tags, ntags * sizeof(bool));
				++kend;
			} else {
				// it is impossible to reach the same NFA state from
				// different rules, so no need to mess with masks here
				merge_tags(k->tagptr, tags, badtags, ntags);
			}
			break;
		}
	}
	n->mark = false;
}

static size_t find_state(kitem_t *kernel, kitem_t *kend,
	ord_hash_set_t &kernels, Tagpool &tagpool)
{
	const size_t kcount = static_cast<size_t>(kend - kernel);

	// zero-sized kernel corresponds to default state
	if (kcount == 0) {
		return dfa_t::NIL;
	}

	// dump tagsets to tagpool and address them by index:
	// this simpifies storing and comparing kernels
	for (kitem_t *k = kernel; k != kend; ++k) {
		bool *tags = k->tagptr;
		k->tagidx = tagpool.insert(tags);
		delete[] tags;
	}

	// sort kernel items to allow comparison by hash and 'memcmp'
	std::sort(kernel, kend, kitem_t::compare);

	return kernels.insert(kernel, kcount * sizeof(kitem_t));
}

dfa_t::dfa_t(const nfa_t &nfa,
	const charset_t &charset,
	const std::string &cond)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
	, rules(nfa.rules)
	, tags(*nfa.tags)
	, tagpool(*new Tagpool(tags.size()))
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
					nfa_state_t *m = n->value.ran.out;
					size_t c = 0;
					for (const Range *r = n->value.ran.ran; r; r = r->next ()) {
						for (; charset[c] != r->lower(); ++c);
						for (; charset[c] != r->upper(); ++c) {
							merge_tags_with_mask(&arctags[c * ntags], newtags,
								&mask[c * ntags], rules[m->rule].tags,
								badtags, ntags);
							arcs[c].push_back(m);
						}
					}
					break;
				}
				case nfa_state_t::FIN:
					merge_tags_with_mask(&arctags[nchars * ntags], newtags,
						&mask[nchars * ntags], rules[n->rule].tags,
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

