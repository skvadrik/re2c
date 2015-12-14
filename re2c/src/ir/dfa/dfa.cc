#include <assert.h>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <ostream>

#include "src/codegen/go.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/bytecode/ins.h"
#include "src/ir/dfa/state.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/ir/rule_rank.h"
#include "src/util/allocate.h"

namespace re2c
{

static Ins **closure(Ins **cP, Ins *i)
{
	while (!isMarked(i))
	{
		mark(i);
		*(cP++) = i;

		if (i->i.tag == FORK)
		{
			cP = closure(cP, i + 1);
			i = (Ins*) i->i.link;
		}
		else if (i->i.tag == GOTO || i->i.tag == CTXT)
		{
			i = (Ins*) i->i.link;
		}
		else
			break;
	}

	return cP;
}

DFA::DFA
	( const std::string & c
	, uint32_t l
	, Ins * ins
	, uint32_t ni
	, uint32_t lb
	, uint32_t ub
	, const charset_t & cs
	, rules_t rules
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
	, free_ins(ins)

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

	Ins **work = new Ins * [ni + 1];
	findState(work, closure(work, &ins[0]));

	const size_t nc = cs.size() - 1; // (n + 1) bounds for n ranges
	void **goTo = new void*[nc];
	Span *span = allocate<Span> (nc);

	while (toDo)
	{
		State *s = toDo;
		toDo = s->link;

		std::vector<uint32_t> preserved_order;

		memset(goTo, 0, nc * sizeof(void*));

		s->rule = NULL;
		for (uint32_t k = 0; k < s->kCount; ++k)
		{
			Ins * i = s->kernel[k];
			if (i->i.tag == CHAR)
			{
				for (Ins *j = i + 1; j < (Ins*) i->i.link; ++j)
				{
					if (!(j->c.link = goTo[j->c.value]))
					{
						preserved_order.push_back(j->c.value);
					}
					goTo[j->c.value] = j;
				}
			}
			else if (i->i.tag == TERM)
			{
				RuleOp * rule = static_cast<RuleOp *> (i->i.link);
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
			}
			else if (i->i.tag == CTXT)
			{
				s->isPreCtxt = true;
			}
		}

		for (uint32_t j = 0; j < preserved_order.size(); ++j)
		{
			Ins **cP = work;
			for (Ins *i = (Ins*)goTo[preserved_order[j]]; i; i = (Ins*) i->c.link)
			{
				cP = closure(cP, i + i->c.bump);
			}
			goTo[preserved_order[j]] = findState(work, cP);
		}

		s->go.nSpans = 0;
		for (uint32_t j = 0; j < nc;)
		{
			State *to = (State*) goTo[j];
			while (++j < nc && goTo[j] == to) ;
			span[s->go.nSpans].ub = cs[j];
			span[s->go.nSpans].to = to;
			s->go.nSpans++;
		}
		s->go.span = allocate<Span> (s->go.nSpans);
		memcpy((char*) s->go.span, (char*) span, s->go.nSpans*sizeof(Span));
	}

	delete [] work;
	delete [] goTo;
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
	delete [] free_ins;

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

State *DFA::findState(Ins **kernel, Ins ** kernel_end)
{
	uint32_t kCount = 0;
	for (Ins ** i = kernel; i < kernel_end; ++i)
	{
		Ins * ins = *i;
		if (ins->i.tag == CHAR || ins->i.tag == TERM || ins->i.tag == CTXT)
		{
			kernel[kCount++] = ins;
		}
		else
		{
			unmark (ins);
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
				marked = isMarked (s->kernel[i]);
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
		s->kernel = new Ins * [kCount];
		memcpy(s->kernel, kernel, kCount * sizeof (Ins *));
		s->link = toDo;
		toDo = s;
	}

	for (uint32_t i = 0; i < kCount; ++i)
	{
		unmark (kernel[i]);
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

