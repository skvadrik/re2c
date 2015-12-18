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

static nfa_state_t **closure(nfa_state_t **cP, nfa_state_t *n)
{
	if (!n->mark)
	{
		n->mark = true;
		*(cP++) = n;
		switch (n->type)
		{
			case nfa_state_t::ALT:
				cP = closure(cP, n->value.alt.out2);
				cP = closure(cP, n->value.alt.out1);
				break;
			case nfa_state_t::CTX:
				cP = closure(cP, n->value.ctx.out);
				break;
			default:
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
	uint32_t kCount = 0;
	for (nfa_state_t ** pn = kernel; pn < kernel_end; ++pn)
	{
		nfa_state_t *n = *pn;
		switch (n->type)
		{
//			case nfa_state_t::CHR:
			case nfa_state_t::RAN:
			case nfa_state_t::CTX:
			case nfa_state_t::FIN:
				kernel[kCount++] = n;
				break;
			default:
				n->mark = false;
				break;
		}
	}

	State * s;
	for (s = head; s; s = s->next)
	{
		if (s->kCount == kCount)
		{
			bool marked = true;
			for (uint32_t i = 0; marked && i < s->kCount; ++i)
			{
				marked = s->kernel[i]->mark;
			}
			if (marked)
			{
				break;
			}
		}
	}

	if (!s)
	{
		s = new State;
		addState(tail, s);
		s->kCount = kCount;
		s->kernel = new nfa_state_t* [kCount];
		memcpy(s->kernel, kernel, kCount * sizeof(nfa_state_t*));
		s->link = toDo;
		toDo = s;
	}

	for (uint32_t i = 0; i < kCount; ++i)
	{
		kernel[i]->mark = false;
	}

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

