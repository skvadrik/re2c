#include <assert.h>
#include "src/util/c99_stdint.h"
#include <string.h>
#include <algorithm>
#include <limits>
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/dfa/closure.h"
#include "src/dfa/dfa.h"
#include "src/dfa/dump.h"
#include "src/dfa/find_state.h"
#include "src/dfa/tagpool.h"
#include "src/dfa/tagtree.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/re/rule.h"
#include "src/re/tag.h"
#include "src/util/range.h"

namespace re2c
{

static nfa_state_t *transition(nfa_state_t *state, uint32_t symbol);
static void reach(const kernel_t *kernel, closure_t &clos, uint32_t symbol);
static void warn_nondeterministic_tags(const kernels_t &kernels,
	const Tagpool &tagpool, const std::vector<Tag> &tags,
	const std::valarray<Rule> &rules, const std::string &cond, Warn &warn);

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

void reach(const kernel_t *kernel, closure_t &clos, uint32_t symbol)
{
	clos.clear();
	for (size_t i = 0; i < kernel->size; ++i) {
		nfa_state_t *s1 = kernel->state[i],
			*s2 = transition(s1, symbol);
		if (s2) {
			clos_t c = {s1, s2, kernel->order[i], kernel->tvers[i],
				kernel->tlook[i], HROOT};
			clos.push_back(c);
		}
	}
}

dfa_t::dfa_t(const nfa_t &nfa, const opt_t *opts,
	const std::string &cond, Warn &warn)
	: states()
	, nchars(nfa.charset.size() - 1) // (n + 1) bounds for n ranges
	, charset(nfa.charset)
	, rules(nfa.rules)
	, tags(nfa.tags)
	, mtagvers(*new std::set<tagver_t>)
	, finvers(NULL)
	, tcpool(*new tcpool_t)
	, maxtagver(0)
	, tcmd0(NULL)
	, tcid0(TCID0)
{
	const size_t ntag = tags.size();
	Tagpool tagpool(opts, ntag);
	kernels_t kernels(tagpool, tcpool, tags);
	closure_t clos1, clos2;
	newver_cmp_t newvers_cmp = {tagpool.history};
	newvers_t newvers(newvers_cmp);
	tcmd_t *acts;
	dump_dfa_t dump(*this, tagpool, nfa);

	// all-zero tag configuration must have static number zero
	assert(ZERO_TAGS == tagpool.insert_const(TAGVER_ZERO));
	// initial tag versions: [1 .. N]
	const size_t INITIAL_TAGS = tagpool.insert_succ(1);
	// other versions: [ .. -(N + 1)] and [N + 1 .. ]
	maxtagver = static_cast<tagver_t>(ntag);

	// final/fallback versions will be assigned on the go
	finvers = new tagver_t[ntag];
	for (size_t i = 0; i < ntag; ++i) {
		finvers[i] = fixed(tags[i]) ? TAGVER_ZERO : ++maxtagver;
	}

	// mark tags with history (initial and final)
	for (size_t i = 0; i < ntag; ++i) {
		if (history(tags[i])) {
			tagver_t v = static_cast<tagver_t>(i) + 1, f = finvers[i];
			if (f != TAGVER_ZERO) mtagvers.insert(f);
			mtagvers.insert(v);
		}
	}

	// iterate while new kernels are added: for each alphabet symbol,
	// build tagged epsilon-closure of all reachable NFA states,
	// then find identical or mappable DFA state or add a new one

	clos_t c0 = {NULL, nfa.root, ZERO_TAGS, INITIAL_TAGS, HROOT, HROOT};
	clos1.push_back(c0);
	acts = closure(*this, clos1, clos2, tagpool, newvers, dump.shadow);
	find_state(*this, dfa_t::NIL, 0/* any */, kernels, clos2, acts, dump);

	for (size_t i = 0; i < kernels.size(); ++i) {
		newvers.clear();
		for (size_t c = 0; c < nchars; ++c) {
			reach(kernels[i], clos1, charset[c]);
			acts = closure(*this, clos1, clos2, tagpool, newvers, dump.shadow);
			find_state(*this, i, c, kernels, clos2, acts, dump);
		}
	}

	if (!opts->posix_captures) {
		warn_nondeterministic_tags(kernels, tagpool, tags, rules, cond, warn);
	}
}

/*
 * For each tag, find maximal number of parallel versions of this tag
 * used in each kernel (degree of non-determinism) and warn about tags with
 * maximum degree two or more.
 *
 * WARNING: this function assumes that kernel items are grouped by rule
 */
void warn_nondeterministic_tags(const kernels_t &kernels,
	const Tagpool &tagpool, const std::vector<Tag> &tags,
	const std::valarray<Rule> &rules, const std::string &cond, Warn &warn)
{
	const size_t
		ntag = tagpool.ntags,
		nkrn = kernels.size();
	std::vector<size_t> maxv(ntag, 0);
	std::set<tagver_t> uniq;

	for (size_t i = 0; i < nkrn; ++i) {
		const kernel_t *k = kernels[i];
		nfa_state_t **s = k->state;
		const size_t n = k->size, *v = k->tvers;

		for (size_t u = 0; u < n;) {
			const size_t r = s[u]->rule;
			const Rule &rule = rules[r];

			const size_t l = u;
			for (; ++u < n && s[u]->rule == r;);
			for (size_t t = rule.ltag; t < rule.htag; ++t) {
				uniq.clear();
				for (size_t m = l; m < u; ++m) {
					uniq.insert(tagpool[v[m]][t]);
				}
				maxv[t] = std::max(maxv[t], uniq.size());
			}
		}
	}

	const size_t nrule = rules.size();
	for (size_t r = 0; r < nrule; ++r) {
		const Rule &rule = rules[r];
		for (size_t t = rule.ltag; t < rule.htag; ++t) {
			const size_t m = maxv[t];
			if (m > 1) {
				const uint32_t line = rule.code->fline;
				warn.nondeterministic_tags(line, cond, tags[t].name, m);
			}
		}
	}
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

