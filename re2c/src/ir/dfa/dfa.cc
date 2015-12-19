#include <algorithm>
#include <assert.h>
#include <ostream>
#include <set>
#include <string.h>
#include <queue>

#include "src/codegen/go.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/dfa/state.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/ir/rule_rank.h"
#include "src/util/allocate.h"
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

DFA::DFA
	( const std::string & c
	, uint32_t l
	, uint32_t lb
	, uint32_t ub
	, const charset_t & cs
	, rules_t & rules
	, nfa_t & nfa
	)
	: accepts ()
	, skeleton (NULL)
	, name ()
	, cond (c)
	, line (l)
	, lbChar(lb)
	, ubChar(ub)
	, nStates(0)
	, head(NULL)
	, tail(&head)
	, toDo(NULL)
	, kernels()

	// statistics
	, max_fill (0)
	, need_backup (false)
	, need_backupctx (false)
	, need_accept (false)
{
	std::ostringstream s;
	s << "line" << line;
	name = s.str ();
	if (!cond.empty ())
	{
		name += "_";
		name += cond;
	}

	const size_t nc = cs.size() - 1; // (n + 1) bounds for n ranges

	nfa_state_t **work = new nfa_state_t* [nfa.size];
	findState(work, closure(work, nfa.root));

	std::vector<nfa_state_t*> *go = new std::vector<nfa_state_t*>[nc];
	Span *span = allocate<Span> (nc);

	while (toDo)
	{
		State *s = toDo;
		toDo = s->link;

		for(uint32_t i = 0; i < nc; ++i)
		{
			go[i].clear();
		}
		memset(span, 0, sizeof(Span)*nc);

		s->rule = NULL;
		for (uint32_t k = 0; k < s->kCount; ++k)
		{
			nfa_state_t *n = s->kernel[k];
			switch (n->type)
			{
//				case nfa_state_t::CHR:
//					go[n->value.chr.chr].push_back(n->value.chr.out);
//					break;
				case nfa_state_t::RAN:
				{
					nfa_state_t *n2 = n->value.ran.out;
					uint32_t j = 0;
					for (Range *r = n->value.ran.ran; r; r = r->next ())
					{
						for (; cs[j] != r->lower(); ++j);
						for (; cs[j] != r->upper(); ++j)
						{
							go[j].push_back(n2);
						}
					}
					break;
				}
				case nfa_state_t::CTX:
					s->isPreCtxt = true;
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

		for(uint32_t i = 0; i < nc; ++i)
		{
			if(!go[i].empty())
			{
				nfa_state_t **cP = work;
				for (std::vector<nfa_state_t*>::const_iterator j = go[i].begin(); j != go[i].end(); ++j)
				{
					cP = closure(cP, *j);
				}
				span[i].to = findState(work, cP);
			}
		}

		s->go.nSpans = 0;
		for (uint32_t j = 0; j < nc;)
		{
			State *to = span[j].to;
			while (++j < nc && span[j].to == to) ;
			span[s->go.nSpans].ub = cs[j];
			span[s->go.nSpans].to = to;
			s->go.nSpans++;
		}
		s->go.span = allocate<Span> (s->go.nSpans);
		memcpy((char*) s->go.span, (char*) span, s->go.nSpans*sizeof(Span));
	}

	delete [] work;
	delete [] go;
	operator delete (span);

	/*
	 * note [reordering DFA states]
	 *
	 * re2c-generated code depends on the order of states in DFA: simply
	 * flipping two states may change the output significantly.
	 * The order of states is affected by many factors, e.g.:
	 *   - flipping left and right subtrees of alternative when constructing
	 *     AST (also applies to iteration and counted repetition)
	 *   - changing the order in which graph nodes are visited (applies to
	 *     any intermediate representation: bytecode, NFA, DFA, etc.)
	 *
	 * To make the resulting code independent of such changes, we hereby
	 * reorder DFA states. The ordering scheme is very simple:
	 *
	 * Starting with DFA root, walk DFA nodes in breadth-first order.
	 * Child nodes are ordered accoding to the (alphabetically) first symbol
	 * leading to each node. Each node must be visited exactly once.
	 * Default state (NULL) is always the last state.
	 */
	reorder();

	// skeleton must be constructed after DFA construction
	// but prior to any other DFA transformations
	skeleton = new Skeleton (*this, rules);

	// skeleton is constructed, do further DFA transformations
	prepare ();

	// finally gather overall DFA statistics
	calc_stats ();
}

void DFA::reorder()
{
	std::vector<State*> ord;
	ord.reserve(nStates);

	std::queue<State*> todo;
	todo.push(head);

	std::set<State*> done;
	done.insert(head);

	for(;!todo.empty();)
	{
		State *s = todo.front();
		todo.pop();
		ord.push_back(s);
		for(uint32_t i = 0; i < s->go.nSpans; ++i)
		{
			State *q = s->go.span[i].to;
			if(q && done.insert(q).second)
			{
				todo.push(q);
			}
		}
	}

	assert(nStates == ord.size());

	ord.push_back(NULL);
	for(uint32_t i = 0; i < nStates; ++i)
	{
		ord[i]->next = ord[i + 1];
	}
}

DFA::~DFA()
{
	State *s;

	while ((s = head))
	{
		head = s->next;
		delete s;
	}

	delete skeleton;
}

void DFA::addState(State **a, State *s)
{
	++nStates;
	s->next = *a;
	*a = s;

	if (a == tail)
		tail = &s->next;
}

State *DFA::findState(nfa_state_t **kernel, nfa_state_t ** kernel_end)
{
	const uint32_t kCount = static_cast<uint32_t>(kernel_end - kernel);

	// see note [marking DFA states]
	for (uint32_t i = 0; i < kCount; ++i)
	{
		kernel[i]->mark = false;
	}

	// sort kernel states: we need this to get stable hash
	// and to compare states with simple 'memcmp'
	std::sort(kernel, kernel_end);

	// get hash of the new DFA state
	uintptr_t hash = kCount; // seed
	for (uint32_t i = 0; i < kCount; ++i)
	{
		hash = hash ^ ((hash << 5) + (hash >> 2) + (uintptr_t)kernel[i]);
	}

	// try to find an existing DFA state identical to the new state
	std::map<uintptr_t, std::list<State*> >::const_iterator i = kernels.find(hash);
	if (i != kernels.end())
	{
		std::list<State*>::const_iterator
			j = i->second.begin(),
			e = i->second.end();
		for (; j != e; ++j)
		{
			State *s = *j;
			if (s->kCount == kCount
				&& memcmp(s->kernel, kernel, kCount * sizeof(nfa_state_t*)) == 0)
			{
				return s;
			}
		}
	}

	// no identical DFA state was found; add new state
	State *s = new State;
	addState(tail, s);
	kernels[hash].push_back(s);
	s->kCount = kCount;
	s->kernel = new nfa_state_t* [kCount];
	memcpy(s->kernel, kernel, kCount * sizeof(nfa_state_t*));
	s->link = toDo;
	toDo = s;
	return s;
}

std::ostream& operator<<(std::ostream &o, const DFA &dfa)
{
	for (State *s = dfa.head; s; s = s->next)
	{
		o << s << "\n\n";
	}

	return o;
}

} // namespace re2c

