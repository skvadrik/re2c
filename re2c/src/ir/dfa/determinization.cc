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
static void warn_bad_tags(const bool *badtags, const std::valarray<Tag> &tags,
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

dfa_t::dfa_t(const nfa_t &nfa,
	const charset_t &charset,
	const std::string &cond)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
	, rules(nfa.rules)
	, tags(*nfa.tags)
	, tagpool(*nfa.tagpool)
	, copy_tags(ZERO_TAGS)
{
	clospool_t clospool;
	closure_t clos1, clos2;
	bool *badtags = new bool[tags.size()]();

	clos1.push_back(clos_t(nfa.root, ZERO_TAGS));
	closure(clos1, clos2, tagpool, rules, badtags);
	clospool.insert(clos2);

	// closures are in sync with DFA states
	for (size_t i = 0; i < clospool.size(); ++i) {
		const closure_t &clos0 = clospool[i];

		// create new DFA state
		dfa_state_t *s = new dfa_state_t(nchars);
		states.push_back(s);

		// check if the new state is final
		// see note [at most one final item per closure]
		cclositer_t e = clos0.end(),
			f = std::find_if(clos0.begin(), e, clos_t::final);
		if (f != e) {
			s->rule = f->state->rule;
			s->rule_tags.set = f->tagidx;
		}

		// for each alphabet symbol, build tagged epsilon-closure
		// of all NFA states reachable on that symbol, then try to
		// find identical closure or add the new one
		for (size_t c = 0; c < nchars; ++c) {
			reach(clos0, clos1, charset[c]);
			s->tags[c].set = closure(clos1, clos2, tagpool, rules, badtags);
			s->arcs[c] = clospool.insert(clos2);
		}
	}

	warn_bad_tags(badtags, tags, rules, cond);
	delete[] badtags;
}

void warn_bad_tags(const bool *badtags,
	const std::valarray<Tag> &tags,
	const std::valarray<Rule> &rules,
	const std::string &cond)
{
	const size_t ntags = tags.size();
	for (size_t i = 0; i < ntags; ++i) {
		if (badtags[i]) {
			const Tag &tag = tags[i];
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

