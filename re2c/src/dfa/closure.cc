#include <assert.h>
#include "src/util/c99_stdint.h"
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <stack>
#include <utility>
#include <valarray>

#include "src/conf/opt.h"
#include "src/dfa/closure.h"
#include "src/dfa/determinization.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tagpool.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/re/rule.h"

namespace re2c
{

/* note [epsilon-closures in tagged NFA]
 *
 * The closure includes all NFA states that are reachable by epsilon-paths
 * from the given set of states and either are final or have non-epsilon
 * transitions. Note that by construction NFA states cannot have both
 * epsilon and non-epsilon transitions.
 *
 * Each closure state might be reachable by multiple epsilon-paths with
 * different tags: this means that the regular expression is ambiguous
 * and can be parsed in different ways. Which parse to choose depends on the
 * disambiguation policy. RE2C supports two policies: leftmost greedy and
 * POSIX.
 *
 * We use Goldber-Radzik algorithm to find the "shortest path".
 * Both disambiguation policies forbid epsilon-cycles with negative weight.
 */


/* note [at most one final item per closure]
 *
 * By construction NFA has exactly one final state per rule. Thus closure
 * has at most one final item per rule (in other words, all final items
 * in closure belong to different rules). The rule with the highest priority
 * shadowes all other rules. Final items that correspond to shadowed rules
 * are useless and should be removed as early as possible.
 *
 * If we let such items remain in closure, they may prevent the new DFA
 * state from being merged with other states. This won't affect the final
 * program: meaningless finalizing tags will be removed by dead code
 * elimination and subsequent minimization will merge equivalent final
 * states. However, it's better not to add useless final items at all.
 *
 * Note that the first final item reached by the epsilon-closure it the one
 * with the highest priority (see note [closure items are sorted by rule]).
 */


/* note [the difference between TDFA(0) and TDFA(1)]
 *
 * TDFA(0) performs epsilon-closure after transition on symbol,
 * while TDFA(1) performs it before the transition and uses the lookahead
 * symbol to filter the closure.
 *
 * TDFA(0) is one step ahead of TDFA(1): it consumes a symol, then builds
 * epsilon-closure, eagerly applies all tags reachable by it and goes to
 * the next state.
 *
 * TDFA(1) is more lazy: it builds epsilon-closure, then filters it with
 * respect to the current symbol (uses only those states which have outgoing
 * transitions on this symbol), then applies corresponding tags (probably
 * not all tags applied by TDFA(0)) and then consumes the symbol and goes
 * to the next state.
 *
 * Thus in general TDFA(1) raises less conflicts than TDFA(0).
 */


static void closure_posix(determ_context_t &);
static nfa_state_t *relax(determ_context_t &, clos_t);
static nfa_state_t *explore(determ_context_t &, nfa_state_t *);
static void closure_leftmost(determ_context_t &);
static void prune(closure_t &, std::valarray<Rule> &);
static void lower_lookahead_to_transition(closure_t &);
static void generate_versions(determ_context_t &);
static void orders(determ_context_t &);
static bool cmpby_rule_state(const clos_t &, const clos_t &);
static int32_t pack(int32_t, int32_t);


void tagged_epsilon_closure(determ_context_t &ctx)
{
	closure_t &closure = ctx.dc_closure;

	// build tagged epsilon-closure of the given set of NFA states
	if (ctx.dc_opts->posix_captures) {
		closure_posix(ctx);
		prune(closure, ctx.dc_nfa.rules);
		std::sort(closure.begin(), closure.end(), cmpby_rule_state);
		orders(ctx);
	} else {
		closure_leftmost(ctx);
		prune(closure, ctx.dc_nfa.rules);
	}

	// see note [the difference between TDFA(0) and TDFA(1)]
	if (!ctx.dc_opts->lookahead) {
		lower_lookahead_to_transition(closure);
	}

	// merge tags from different rules, find nondeterministic tags
	generate_versions(ctx);
}


bool cmpby_rule_state(const clos_t &x, const clos_t &y)
{
	const nfa_state_t *sx = x.state, *sy = y.state;
	const size_t rx = sx->rule, ry = sy->rule;
	if (rx < ry) return true;
	if (rx > ry) return false;
	if (sx < sy) return true;
	if (sx > sy) return false;
	// all items in closute have different states
	return false;
}


nfa_state_t *relax(determ_context_t &ctx, clos_t x)
{
	closure_t &done = ctx.dc_closure;
	nfa_state_t *q = x.state;
	const uint32_t idx = q->clos;
	int32_t h1, h2;

	// first time we see this state
	if (idx == NOCLOS) {
		q->clos = static_cast<uint32_t>(done.size());
		done.push_back(x);
	}

	// States of in-degree less than 2 are not joint points;
	// the fact that we are re-scanning this state means that we found
	// a better path to some previous state. Due to the right distributivity
	// of path comparison over path concatenation (X < Y => XZ < YZ) we
	// can just propagate the new path up to the next join point.
	else if (q->indeg < 2) {
		done[idx] = x;
	}

	// join point; compare the new path and the old path
	else if (precedence(ctx, x, done[idx], h1, h2) < 0) {
		done[idx] = x;
	}

	// the previous path was better, discard the new one
	else {
		q = NULL;
	}

	return q;
}


nfa_state_t *explore(determ_context_t &ctx, nfa_state_t *q)
{
	// find the next admissible transition, adjust the index
	// of the next transition and return the to-state
	nfa_state_t *p = NULL;
	clos_t x = ctx.dc_closure[q->clos];
	switch (q->type) {
		case nfa_state_t::NIL:
			if (q->arcidx == 0) {
				x.state = q->nil.out;
				p = relax(ctx, x);
				++q->arcidx;
			}
			break;
		case nfa_state_t::ALT:
			if (q->arcidx == 0) {
				x.state = q->alt.out1;
				p = relax(ctx, x);
				++q->arcidx;
			}
			if (q->arcidx == 1 && !p) {
				x.state = q->alt.out2;
				p = relax(ctx, x);
				++q->arcidx;
			}
			break;
		case nfa_state_t::TAG:
			if (q->arcidx == 0) {
				x.state = q->tag.out;
				x.tlook = ctx.dc_tagtrie.push(x.tlook, q->tag.info);
				p = relax(ctx, x);
				++q->arcidx;
			}
			break;
		case nfa_state_t::RAN:
		case nfa_state_t::FIN:
			break;
	}
	return p;
}


void closure_posix(determ_context_t &ctx)
{
	const closure_t &init = ctx.dc_reached;
	closure_t &done = ctx.dc_closure;
	std::stack<nfa_state_t*>
		&topsort = ctx.dc_tagpool.astack,
		&linear = ctx.dc_tagpool.bstack;
	nfa_state_t *q, *p;

	done.clear();

	// enqueue all initial states (there might be duplicates)
	for (cclositer_t c = init.begin(); c != init.end(); ++c) {
		q = relax(ctx, *c);
		if (q) {
			topsort.push(q);
			q->status = GOR_TOPSORT;
		}
	}

	// Gordberg-Radzik 'shortest path' algorithm.
	// Papers: 1993, "A heuristic improvement of the Bellman-Ford
	// algorithm" by Goldberg, Radzik and 1996, Shortest paths algorithms:
	// Theory and experimental evaluation" by Cherkassky, Goldberg, Radzik.
	// Complexity for digraph G=(V,E) is O(|V|*|E|).
	for (; !topsort.empty(); ) {

		// 1st pass: scan admissible subgraph reachable from B-stack
		// and topologically sort it (this can be done by a single
		// depth-first postorder traversal)
		for (; !topsort.empty(); ) {
			q = topsort.top();
			topsort.pop();

			if (q->status != GOR_LINEAR) {
				q->status = GOR_TOPSORT;

				// find next admissible transition
				while ((p = explore(ctx, q))
					&& p->status != GOR_NOPASS) {
					p->active = 1;
				}

				// follow the admissible transition
				if (p) {
					topsort.push(q);
					topsort.push(p);
					p->arcidx = 0;
				}
				// done with this state: all deps visited
				else {
					q->status = GOR_LINEAR;
					linear.push(q);
				}
			}
		}

		// 2nd pass: scan topologically ordered states from A-stack
		// and push head states of relaxed transitions to B-stack
		for (; !linear.empty(); ) {
			q = linear.top();
			linear.pop();

			if (q->active) {
				// scan admissible transitions
				q->arcidx = 0;
				while ((p = explore(ctx, q))) {
					if (p->status == GOR_NOPASS) {
						topsort.push(p);
						p->arcidx = 0;
					}
					else if (p->status == GOR_LINEAR) {
						p->active = 1;
					}
				}
			}

			q->status = GOR_NOPASS;
			q->active = 0;
		}
	}

	// clean up (do this before removing any states from closure)
	for (clositer_t i = done.begin(); i != done.end(); ++i) {
		q = i->state;
		q->clos = NOCLOS;
		q->arcidx = 0;
		assert(q->status == GOR_NOPASS && q->active == 0);
	}
}


void closure_leftmost(determ_context_t &ctx)
{
	const closure_t &init = ctx.dc_reached;
	closure_t &done = ctx.dc_closure;
	std::stack<clos_t> &todo = ctx.dc_tagpool.cstack;

	// enqueue all initial states
	done.clear();
	for (rcclositer_t c = init.rbegin(); c != init.rend(); ++c) {
		todo.push(*c);
	}

	// DFS; linear complexity
	for (; !todo.empty(); ) {
		clos_t x = todo.top();
		todo.pop();
		nfa_state_t *n = x.state;

		if (n->clos == NOCLOS) {
			n->clos = static_cast<uint32_t>(done.size());
			done.push_back(x);

			switch (n->type) {
				case nfa_state_t::NIL:
					x.state = n->nil.out;
					todo.push(x);
					break;
				case nfa_state_t::ALT:
					x.state = n->alt.out2;
					todo.push(x);
					x.state = n->alt.out1;
					todo.push(x);
					break;
				case nfa_state_t::TAG:
					x.state = n->tag.out;
					x.tlook = ctx.dc_tagtrie.push(x.tlook, n->tag.info);
					todo.push(x);
					break;
				case nfa_state_t::RAN:
				case nfa_state_t::FIN:
					break;
			}
		}
	}

	// reset associated closure items 
	// (do this before removing any states from closure)
	for (clositer_t i = done.begin(); i != done.end(); ++i) {
		i->state->clos = NOCLOS;
	}
}


void prune(closure_t &closure, std::valarray<Rule> &rules)
{
	clositer_t b = closure.begin(), e = closure.end(), i, j;

	// drop "inner" states (non-final without outgoing non-epsilon transitions)
	j = std::stable_partition(b, e, clos_t::ran);
	e = std::stable_partition(j, e, clos_t::fin);
	size_t n = static_cast<size_t>(e - b);

	// drop all final states except one; mark dropped rules as shadowed
	// see note [at most one final item per closure]
	if (j != e) {
		std::sort(j, e, cmpby_rule_state);
		const uint32_t l = rules[j->state->rule].code->fline;
		for (i = j; ++i < e;) {
			rules[i->state->rule].shadow.insert(l);
		}
		n = static_cast<size_t>(j - b) + 1;
	}

	closure.resize(n);
}


void lower_lookahead_to_transition(closure_t &closure)
{
	for (clositer_t c = closure.begin(); c != closure.end(); ++c) {
		c->ttran = c->tlook;
		c->tlook = HROOT;
	}
}


void generate_versions(determ_context_t &ctx)
{
	dfa_t &dfa = ctx.dc_dfa;
	const std::vector<Tag> &tags = dfa.tags;
	const size_t ntag = tags.size();
	tagver_t &maxver = dfa.maxtagver;
	Tagpool &tagpool = ctx.dc_tagpool;
	tagver_t *vers = tagpool.buffer;
	closure_t &clos = ctx.dc_closure;
	tagtree_t &tagtree = ctx.dc_tagtrie;
	newvers_t &newvers = ctx.dc_newvers;

	clositer_t b = clos.begin(), e = clos.end(), c;
	newver_cmp_t cmp(tagtree);
	newvers_t newacts(cmp);
	tcmd_t *cmd = NULL;

	// for each tag, if there is at least one tagged transition,
	// allocate new version (negative for bottom and positive for
	// normal transition, however absolute value should be unique
	// among all versions of all tags)
	for (c = b; c != e; ++c) {
		const hidx_t l = c->tlook, h = c->ttran;
		if (h == HROOT) continue;

		const tagver_t *vs = tagpool[c->tvers];
		for (size_t t = 0; t < ntag; ++t) {
			const Tag &tag = tags[t];
			const tagver_t
				h0 = tagtree.last(h, t),
				l0 = tagtree.last(l, t);

			if (h0 == TAGVER_ZERO) continue;

			const tagver_t v = history(tag) ? vs[t] : TAGVER_ZERO;
			newver_t x = {t, v, h};
			const tagver_t
				n = (maxver + 1) * (h0 == TAGVER_BOTTOM ? -1 : 1),
				m = newvers.insert(std::make_pair(x, n)).first->second;
			if (n == m) ++maxver;

			if (!fixed(tag) && (l0 == TAGVER_ZERO || history(tag))) {
				newacts.insert(std::make_pair(x, m));
			}
		}
	}

	// actions
	for (newvers_t::iterator i = newacts.begin(); i != newacts.end(); ++i) {
		const tagver_t m = i->second, v = i->first.base;
		const hidx_t h = i->first.history;
		const size_t t = i->first.tag;
		if (history(tags[t])) {
			cmd = dfa.tcpool.make_add(cmd, abs(m), abs(v), tagtree, h, t);
		} else {
			cmd = dfa.tcpool.make_set(cmd, abs(m), tagtree.last(h, t));
		}
	}

	// mark tags with history
	for (newvers_t::iterator j = newvers.begin(); j != newvers.end(); ++j) {
		if (history(tags[j->first.tag])) dfa.mtagvers.insert(abs(j->second));
	}

	// update tag versions in closure
	for (c = b; c != e; ++c) {
		const hidx_t h = c->ttran;
		if (h == HROOT) continue;

		const tagver_t *vs = tagpool[c->tvers];
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t
				v0 = vs[t],
				h0 = tagtree.last(h, t),
				v = history(tags[t]) ? v0 : TAGVER_ZERO;
			if (h0 == TAGVER_ZERO) {
				vers[t] = v0;
			} else {
				newver_t x = {t, v, h};
				vers[t] = newvers[x];
			}
		}
		c->tvers = tagpool.insert(vers);
	}

	ctx.dc_actions = cmd;
}


int32_t pack(int32_t longest, int32_t leftmost)
{
	// leftmost: higher 2 bits, longest: lower 30 bits
	return longest | (leftmost << 30);
}


void orders(determ_context_t &ctx)
{
	closure_t &closure = ctx.dc_closure;
	const size_t nclos = closure.size();

	prectable_t *prectbl = ctx.dc_allocator.alloct<prectable_t>(nclos * nclos);

	for (size_t i = 0; i < nclos; ++i) {
		for (size_t j = i + 1; j < nclos; ++j) {
			int32_t rho1, rho2, l;
			l = precedence (ctx, closure[i], closure[j], rho1, rho2);
			prectbl[i * nclos + j] = pack(rho1, l);
			prectbl[j * nclos + i] = pack(rho2, -l);
		}
		prectbl[i * nclos + i] = 0;
	}

	ctx.dc_prectbl = prectbl;
}

} // namespace re2c
