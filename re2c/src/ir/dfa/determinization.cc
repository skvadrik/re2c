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
static void reach(const kernel_t *kernel, closure_t &clos, uint32_t symbol);
static void warn_bad_tags(const bool *badtags, const std::vector<VarTag> &tags,
	const std::valarray<Rule> &rules, const std::string &cond);

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
		nfa_state_t *s = transition(kernel->state[i], symbol);
		if (s) {
			clos.push_back(clos_t(s, kernel->tlook[i]));
		}
	}
}

dfa_t::dfa_t(const nfa_t &nfa,
	const charset_t &charset,
	const std::string &cond)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
	, rules(nfa.rules)
	, vartags(nfa.vartags)
	, fixtags(nfa.fixtags)
	, finvers(NULL)
	, tcpool(*new tcpool_t)
	, maxtagver(0)
{
	const size_t ntag = vartags.size();
	Tagpool tagpool(ntag);
	kernels_t kernels;
	closure_t clos1, clos2;
	bool *badtags = new bool[ntag]();

	finvers = new tagver_t[ntag];
	for (size_t t = 0; t < ntag; ++t) {
		finvers[t] = ++maxtagver;
	}
	maxtagver *= 2;
	clos1.push_back(clos_t(nfa.root, ZERO_TAGS));
	closure(clos1, clos2, tagpool, tcpool, rules, badtags);
	kernels.insert(clos2);

	// closure kernels are in sync with DFA states
	for (size_t i = 0; i < kernels.size(); ++i) {
		const kernel_t *kernel = kernels[i];

		// create new DFA state
		dfa_state_t *s = new dfa_state_t(nchars);
		states.push_back(s);

		// check if the new state is final
		// see note [at most one final item per closure]
		for (size_t i = 0; i < kernel->size; ++i) {
			const nfa_state_t *f = kernel->state[i];
			if (f->type == nfa_state_t::FIN) {
				s->rule = f->rule;
				const Rule &rule = rules[s->rule];
				s->tcmd[nchars] = tcpool.conv_to_tcmd(tagpool[kernel->tlook[i]],
					finvers, rule.lvar, rule.hvar, ntag);
				break;
			}
		}

		// for each alphabet symbol, build tagged epsilon-closure
		// of all NFA states reachable on that symbol, then try to
		// find identical closure or add the new one
		for (size_t c = 0; c < nchars; ++c) {
			reach(kernel, clos1, charset[c]);
			s->tcmd[c].save = closure(clos1, clos2, tagpool, tcpool, rules, badtags);
			s->arcs[c] = kernels.insert(clos2);
		}
	}

	warn_bad_tags(badtags, vartags, rules, cond);
	delete[] badtags;
}

void warn_bad_tags(const bool *badtags,
	const std::vector<VarTag> &tags,
	const std::valarray<Rule> &rules,
	const std::string &cond)
{
	const size_t ntags = tags.size();
	for (size_t i = 0; i < ntags; ++i) {
		if (badtags[i]) {
			const VarTag &tag = tags[i];
			const uint32_t line = rules[tag.rule].info->loc.line;
			warn.nondeterministic_tags(line, cond, tag.name);
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

