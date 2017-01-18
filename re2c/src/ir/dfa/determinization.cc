#include <limits>
#include <string.h>
#include <vector>

#include "src/conf/opt.h"
#include "src/ir/dfa/closure.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/dfa/dump.h"
#include "src/ir/dfa/find_state.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c
{

static nfa_state_t *transition(nfa_state_t *state, uint32_t symbol);
static void reach(const kernel_t *kernel, closure_t &clos, uint32_t symbol);
static void warn_nondeterministic_tags(const kernels_t &kernels,
	const Tagpool &tagpool, const std::vector<VarTag> &tags,
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
			clos_t c = {s1, s2, kernel->tvers[i], kernel->tlook[i], ZERO_TAGS};
			clos.push_back(c);
		}
	}
}

dfa_t::dfa_t(const nfa_t &nfa, const charset_t &charset, const opt_t *opts,
	const std::string &cond, Warn &warn)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
	, rules(nfa.rules)
	, vartags(nfa.vartags)
	, fixtags(nfa.fixtags)
	, finvers(NULL)
	, tcpool(*new tcpool_t)
	, maxtagver(0)
	, tcmd0(new tcmd_t)
	, tcid0(NULL)
{
	const bool lookahead = opts->lookahead;
	const size_t ntag = vartags.size();
	Tagpool tagpool(ntag);
	kernels_t kernels(tagpool, opts->bijective_mapping);
	closure_t clos1, clos2;
	dump_dfa_t dump(*this, tagpool, nfa, opts->dump_dfa_raw);

	// all-zero tag configuration must have static number zero
	assert(ZERO_TAGS == tagpool.insert_const(TAGVER_ZERO));
	// final tag versions: [1 .. N], also used for fallback tags
	const size_t FINAL_TAGS = tagpool.insert_succ(1);
	finvers = new tagver_t[ntag];
	memcpy(finvers, tagpool[FINAL_TAGS], ntag * sizeof(tagver_t));
	// initial tag versions: [N+1 .. 2*N]
	const size_t INITIAL_TAGS = tagpool.insert_succ(static_cast<tagver_t>(ntag) + 1);
	// other versions: [ .. -(2*N+1)] and [2*N+1 .. ]
	maxtagver = static_cast<tagver_t>(ntag) * 2;

	// iterate while new kernels are added: for each alphabet symbol,
	// build tagged epsilon-closure of all reachable NFA states,
	// then find identical or mappable DFA state or add a new one

	clos_t c0 = {NULL, nfa.root, INITIAL_TAGS, ZERO_TAGS, ZERO_TAGS};
	clos1.push_back(c0);
	closure(clos1, clos2, tagpool, rules, maxtagver, lookahead);
	find_state(*this, dfa_t::NIL, 0/* any */, tagpool, kernels, clos2, dump);

	for (size_t i = 0; i < kernels.size(); ++i) {
		for (size_t c = 0; c < nchars; ++c) {
			reach(kernels[i], clos1, charset[c]);
			closure(clos1, clos2, tagpool, rules, maxtagver, lookahead);
			find_state(*this, i, c, tagpool, kernels, clos2, dump);
		}
	}

	warn_nondeterministic_tags(kernels, tagpool, vartags, rules, cond, warn);
}

/*
 * For each tag, find maximal number of parallel versions of this tag
 * used in each kernel (degree of non-determinism) and warn about tags with
 * maximum degree two or more.
 *
 * WARNING: this function assumes that kernel items are grouped by rule
 */
void warn_nondeterministic_tags(const kernels_t &kernels,
	const Tagpool &tagpool, const std::vector<VarTag> &tags,
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

			for (size_t t = rule.lvar; t < rule.hvar; ++t) {
				uniq.clear();
				for (size_t m = l; m < u; ++m) {
					uniq.insert(tagpool[v[m]][t]);
				}
				maxv[t] = std::max(maxv[t], uniq.size());
			}
		}
	}

	for (size_t t = 0; t < ntag; ++t) {
		const size_t m = maxv[t];
		if (m > 1) {
			const VarTag &tag = tags[t];
			const uint32_t line = rules[tag.rule].code->fline;
			warn.nondeterministic_tags(line, cond, tag.name, m);
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
	delete tcmd0;
	delete tcid0;
}

} // namespace re2c

