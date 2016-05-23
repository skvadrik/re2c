#include "src/conf/opt.h"
#include "src/ir/dfa/dfa.h"
#include "src/util/forbid_copy.h"
#include "src/globals.h"

namespace re2c
{

/* note [unreachable rules]
 *
 * DFA may contain useless final states. Such states may
 * appear as a result of:
 *   - (part of) one rule being shadowed by another rule,
 *     e.g. rule [ab] partially shadows [ac] and completely
 *     shadows [a]
 *
 *   - infinite rules that greedily eat all input characters
 *     and never stop (they either fail on YYFILL or crash),
 *     e.g. [^]*
 *
 *   - rules that contain never-matching link, e.g. '[]'
 *     with option '--empty-class match-none'
 *
 * Useless final states should be eliminated so that they
 * don't interfere with further analyses and optimizations.
 * If all final states of a rule are useless, then the whole
 * rule is unreachable and should be reported.
 *
 * In order to find out if a given final state is useless,
 * we have to find out if all outgoing paths from this state
 * match longer rules (otherwise, some paths go to default
 * state and fallback to this state). We do this by finding
 * all states that have transitions to default state and back
 * propagation of "none-rule" from these states. As the back
 * propagation meets the first final state on its way, it
 * substitutes "none-rule" with the corresponding rule,
 * which is further propagated back to the start state of DFA.
 */

// reversed DFA
struct rdfa_t
{
	struct arc_t
	{
		size_t dest;
		arc_t *next;
	};

	struct state_t
	{
		arc_t *arcs;
		size_t rule;
		bool fallthru;
	};

	size_t nstates;
	size_t nrules;
	state_t *states;
	arc_t *arcs;

	explicit rdfa_t(const dfa_t &dfa)
		: nstates(dfa.states.size())
		, nrules(dfa.rules.size())
		, states(new state_t[nstates]())
		, arcs(new arc_t[nstates * dfa.nchars])
	{
		// init states
		for (size_t i = 0; i < nstates; ++i) {
			state_t &s = states[i];
			s.arcs = NULL;
			const size_t r = dfa.states[i]->rule;
			s.rule = r == Rule::NONE ? nrules : r;
			s.fallthru = false;
		}
		// init arcs
		arc_t *a = arcs;
		for (size_t i = 0; i < nstates; ++i) {
			dfa_state_t *s = dfa.states[i];
			for (size_t c = 0; c < dfa.nchars; ++c) {
				const size_t j = s->arcs[c];
				if (j != dfa_t::NIL) {
					a->dest = i;
					a->next = states[j].arcs;
					states[j].arcs = a++;
				} else {
					states[i].fallthru = true;
				}
			}
		}
	}

	~rdfa_t()
	{
		delete[] states;
		delete[] arcs;
	}

	FORBID_COPY(rdfa_t);
};

static void backprop(const rdfa_t &rdfa,
	bool *reachable,
	size_t rule,
	size_t state)
{
	// "none-rule" is unreachable from final states:
	// be careful to mask it before propagating
	const rdfa_t::state_t &s = rdfa.states[state];
	if (rule == rdfa.nrules) {
		rule = s.rule;
	}

	// if the rule has already been set, than either it's a loop
	// or another branch of back propagation has already been here,
	// in both cases we should stop: there's nothing new to propagate
	bool &reach = reachable[state * (rdfa.nrules + 1) + rule];
	if (reach) return;
	reach = true;

	for (const rdfa_t::arc_t *a = s.arcs; a; a = a->next) {
		backprop(rdfa, reachable, rule, a->dest);
	}
}

static void calc_reachable(const rdfa_t &rdfa, bool *reachable)
{
	for (size_t i = 0; i < rdfa.nstates; ++i) {
		const rdfa_t::state_t &s = rdfa.states[i];
		if (s.fallthru) {
			backprop(rdfa, reachable, s.rule, i);
		}
	}
}

static void warn_unreachable(const dfa_t &dfa, size_t defrule,
	const std::string &cond, const bool *reachable)
{
	const size_t nstates = dfa.states.size();
	const size_t nrules = dfa.rules.size();

	for (size_t i = 0; i < nstates; ++i) {
		const bool *reach = &reachable[i * (nrules + 1)];
		const size_t r = dfa.states[i]->rule;
		if (r != Rule::NONE && !reach[r]) {
			// skip last rule (it's the NONE-rule)
			for (size_t j = 0; j < nrules; ++j) {
				if (reach[j]) {
					dfa.rules[r].shadow.insert(dfa.rules[j].info->loc.line);
				}
			}
		}
	}

	for (size_t i = 0; i < nrules; ++i) {
		// default rule '*' should not be reported
		if (i != defrule && !reachable[i]) {
			warn.unreachable_rule(cond, dfa.rules[i]);
		}
	}
}

static void mask_dead(dfa_t &dfa, const bool *live)
{
	const size_t nstates = dfa.states.size();
	const size_t nrules = dfa.rules.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (s->rule != Rule::NONE
			&& !live[i * (nrules + 1) + s->rule]) {
			s->rule = Rule::NONE;
			s->rule_tags = 0;
		}
	}
}

/* note [fallback states]
 *
 * Find states that are accepting, but may be shadowed
 * by other accepting states: when the short rule matches,
 * lexer must try to match longer rules; if this attempt is
 * unsuccessful it must fallback to the short match.
 *
 * In order to find fallback states we need to know if
 * "none-rule" is reachable from the given state, the information
 * we have after rule liveness analyses. Fallback states are
 * needed at different points in time (both before and after
 * certain transformations on DFA). Fortunately, fallback states
 * are not affected by these transformations, so we can calculate
 * them here and save for future use.
 */
static void find_fallback_states(dfa_t &dfa, const bool *live)
{
	const size_t nstates = dfa.states.size();
	const size_t nrules = dfa.rules.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (s->rule != Rule::NONE) {
			for (size_t c = 0; c < dfa.nchars; ++c) {
				const size_t j = s->arcs[c];
				if (j != dfa_t::NIL
					&& live[j * (nrules + 1) + nrules]) {
					s->fallback = true;
					break;
				}
			}
		}
	}
}

void cutoff_dead_rules(dfa_t &dfa, size_t defrule, const std::string &cond)
{
	const rdfa_t rdfa(dfa);
	bool *reachable = new bool[rdfa.nstates * (rdfa.nrules + 1)]();

	calc_reachable(rdfa, reachable);
	warn_unreachable(dfa, defrule, cond, reachable);
	mask_dead(dfa, reachable);
	find_fallback_states(dfa, reachable);

	delete[] reachable;
}

} // namespace re2c

