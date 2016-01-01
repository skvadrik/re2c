#include <algorithm>
#include <assert.h>
#include <list>
#include <set>
#include <string.h>
#include <queue>

#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/ir/rule_rank.h"
#include "src/util/range.h"

namespace re2c
{

/*
 * note [marking DFA states]
 *
 * DFA state is a set of NFA states.
 * However, DFA state includes not all NFA states that are in
 * epsilon-closure (NFA states that have only epsilon-transitions
 * and are not context of final states are omitted).
 * The included states are called 'kernel' states.
 *
 * We mark visited NFA states during closure construction.
 * These marks serve two purposes:
 *   - avoid loops in NFA
 *   - avoid duplication of NFA states in kernel
 *
 * Note that after closure construction:
 *   - all non-kernel states must be unmarked (these states are
 *     not stored in kernel and it is impossible to unmark them
 *     afterwards)
 *   - all kernel states must be marked (because we may later
 *     extend this kernel with epsilon-closure of another NFA
 *     state). Kernel states are unmarked later (before finding
 *     or adding DFA state).
 */
static nfa_state_t **closure(nfa_state_t **cP, nfa_state_t *n)
{
	if (!n->mark)
	{
		n->mark = true;
		switch (n->type)
		{
			case nfa_state_t::ALT:
				cP = closure(cP, n->value.alt.out2);
				cP = closure(cP, n->value.alt.out1);
				n->mark = false;
				break;
			case nfa_state_t::CTX:
				*(cP++) = n;
				cP = closure(cP, n->value.ctx.out);
				break;
			default:
				*(cP++) = n;
				break;
		}
	}

	return cP;
}

static size_t findState
	( nfa_state_t **kernel
	, nfa_state_t **kernel_end
	, std::vector<dfa_state_t*> &states
	, std::map<uintptr_t, std::list<size_t> > &kernels
	)
{
	const size_t kCount = static_cast<size_t>(kernel_end - kernel);

	// see note [marking DFA states]
	for (size_t i = 0; i < kCount; ++i)
	{
		kernel[i]->mark = false;
	}

	// sort kernel states: we need this to get stable hash
	// and to compare states with simple 'memcmp'
	std::sort(kernel, kernel_end);

	// get hash of the new DFA state
	uintptr_t hash = kCount; // seed
	for (size_t i = 0; i < kCount; ++i)
	{
		hash = hash ^ ((hash << 5) + (hash >> 2) + (uintptr_t)kernel[i]);
	}

	// try to find an existing DFA state identical to the new state
	std::map<uintptr_t, std::list<size_t> >::const_iterator i = kernels.find(hash);
	if (i != kernels.end())
	{
		std::list<size_t>::const_iterator
			j = i->second.begin(),
			e = i->second.end();
		for (; j != e; ++j)
		{
			const size_t k = *j;
			if (states[k]->kCount == kCount
				&& memcmp(states[k]->kernel, kernel, kCount * sizeof(nfa_state_t*)) == 0)
			{
				return k;
			}
		}
	}

	// no identical DFA state was found; add new state
	dfa_state_t *s = new dfa_state_t;
	s->kCount = kCount;
	s->kernel = new nfa_state_t* [kCount];
	memcpy(s->kernel, kernel, kCount * sizeof(nfa_state_t*));
	const size_t k = states.size();
	states.push_back(s);
	kernels[hash].push_back(k);
	return k;
}

dfa_t::dfa_t(const nfa_t &nfa, const charset_t &charset, rules_t &rules)
	: states()
	, nchars(charset.size() - 1) // (n + 1) bounds for n ranges
{
	std::map<uintptr_t, std::list<size_t> > kernels;
	nfa_state_t **work = new nfa_state_t* [nfa.size];
	std::vector<nfa_state_t*> *go = new std::vector<nfa_state_t*>[nchars];

	findState(work, closure(work, nfa.root), states, kernels);
	for (size_t k = 0; k < states.size(); ++k)
	{
		dfa_state_t *s = states[k];

		for(size_t i = 0; i < nchars; ++i)
		{
			go[i].clear();
		}

		s->rule = NULL;
		for (size_t k = 0; k < s->kCount; ++k)
		{
			nfa_state_t *n = s->kernel[k];
			switch (n->type)
			{
				case nfa_state_t::RAN:
				{
					nfa_state_t *n2 = n->value.ran.out;
					size_t j = 0;
					for (Range *r = n->value.ran.ran; r; r = r->next ())
					{
						for (; charset[j] != r->lower(); ++j);
						for (; charset[j] != r->upper(); ++j)
						{
							go[j].push_back(n2);
						}
					}
					break;
				}
				case nfa_state_t::CTX:
					s->ctx = true;
					break;
				case nfa_state_t::FIN:
				{
					RuleOp *rule = n->value.fin.rule;
					if (!s->rule)
					{
						s->rule = rule;
					}
					else
					{
						const rule_rank_t r1 = s->rule->rank;
						const rule_rank_t r2 = rule->rank;
						if (r2 < r1)
						{
							rules[r1].shadow.insert (r2);
							s->rule = rule;
						}
						else if (r1 < r2)
						{
							rules[r2].shadow.insert (r1);
						}
					}
					break;
				}
				default:
					break;
			}
		}

		s->arcs = new size_t[nchars];
		for(size_t i = 0; i < nchars; ++i)
		{
			if(!go[i].empty())
			{
				nfa_state_t **cP = work;
				for (std::vector<nfa_state_t*>::const_iterator j = go[i].begin(); j != go[i].end(); ++j)
				{
					cP = closure(cP, *j);
				}
				s->arcs[i] = findState(work, cP, states, kernels);
			}
			else
			{
				s->arcs[i] = ~0u;
			}
		}
	}
	delete [] work;
	delete [] go;

	const size_t count = states.size();
	for (size_t i = 0; i < count; ++i)
	{
		for (size_t c = 0; c < nchars; ++c)
		{
			if (states[i]->arcs[c] == ~0u)
			{
				states[i]->arcs[c] = count;
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

