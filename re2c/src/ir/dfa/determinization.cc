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
static void warn_nondeterministic_tags(const size_t *nondet,
	const std::vector<Tag> &tags, const std::valarray<Rule> &rules,
	const std::string &cond, Warn &warn);

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
			clos_t c = {s1, s2, kernel->tvers[i], ZERO_TAGS};
			clos.push_back(c);
		}
	}
}

dfa_t::dfa_t(const nfa_t &nfa, const charset_t &charset, const opt_t *opts,
	const std::string &cond, Warn &warn)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
	, rules(nfa.rules)
	, tags(nfa.tags)
	, finvers(NULL)
	, tcpool(*new tcpool_t)
	, maxtagver(0)
	, tcmd0(new tcmd_t)
	, tcid0(NULL)
{
	const bool lookahead = opts->lookahead;
	const size_t ntag = tags.size();
	Tagpool tagpool(ntag);
	kernels_t kernels(tagpool, tcpool);
	closure_t clos1, clos2;
	tagver_t *newvers = new tagver_t[ntag * 2];
	size_t *nondet = new size_t[ntag]();
	dump_dfa_t dump(*this, tagpool, nfa, opts->dump_dfa_raw);

	// all-zero tag configuration must have static number zero
	assert(ZERO_TAGS == tagpool.insert_const(TAGVER_ZERO));
	// initial tag versions: [1 .. N]
	const size_t INITIAL_TAGS = tagpool.insert_succ(1);
	// other versions: [ .. -(N + 1)] and [N + 1 .. ]
	maxtagver = static_cast<tagver_t>(ntag);

	// final/fallback versions will be assigned on the go
	finvers = new tagver_t[ntag];
	std::fill(finvers, finvers + ntag, TAGVER_ZERO);

	// iterate while new kernels are added: for each alphabet symbol,
	// build tagged epsilon-closure of all reachable NFA states,
	// then find identical or mappable DFA state or add a new one

	clos_t c0 = {NULL, nfa.root, INITIAL_TAGS, ZERO_TAGS};
	clos1.push_back(c0);
	std::fill(newvers, newvers + ntag * 2, TAGVER_ZERO);
	closure(clos1, clos2, tagpool, rules, maxtagver, newvers, nondet, lookahead, dump.shadow);
	find_state(*this, dfa_t::NIL, 0/* any */, kernels, clos2, dump);

	for (size_t i = 0; i < kernels.size(); ++i) {
		std::fill(newvers, newvers + ntag * 2, TAGVER_ZERO);
		for (size_t c = 0; c < nchars; ++c) {
			reach(kernels[i], clos1, charset[c]);
			closure(clos1, clos2, tagpool, rules, maxtagver, newvers, nondet, lookahead, dump.shadow);
			find_state(*this, i, c, kernels, clos2, dump);
		}
	}

	warn_nondeterministic_tags(nondet, tags, rules, cond, warn);

	delete[] newvers;
	delete[] nondet;
}

void warn_nondeterministic_tags(const size_t *nondet,
	const std::vector<Tag> &tags, const std::valarray<Rule> &rules,
	const std::string &cond, Warn &warn)
{
	const size_t nrule = rules.size();
	for (size_t r = 0; r < nrule; ++r) {
		const Rule &rule = rules[r];
		for (size_t t = rule.ltag; t < rule.htag; ++t) {
			const size_t m = nondet[t];
			if (m > 1) {
				const Tag &tag = tags[t];
				const uint32_t line = rule.code->fline;
				warn.nondeterministic_tags(line, cond, tag.name, m);
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
	delete tcmd0;
	delete tcid0;
}

} // namespace re2c

