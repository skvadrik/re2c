#include <string.h>

#include "src/ir/dfa/dfa.h"
#include "src/ir/regexp/regexp_rule.h"
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

struct GoTo
{
	Char	ch;
	void	*to;
};

DFA::DFA(Ins *ins, uint32_t ni, uint32_t lb, uint32_t ub, const Char *rep)
	: lbChar(lb)
	, ubChar(ub)
	, nStates(0)
	, head(NULL)
	, tail(&head)
	, toDo(NULL)
	, free_ins(ins)
	, free_rep(rep)
	, accepts ()

{
	Ins **work = new Ins * [ni + 1];
	uint32_t nc = ub - lb;
	GoTo *goTo = new GoTo[nc];
	Span *span = allocate<Span> (nc);
	memset((char*) goTo, 0, nc*sizeof(GoTo));
	findState(work, closure(work, &ins[0]) - work);

	while (toDo)
	{
		State *s = toDo;
		toDo = s->link;

		Ins **cP, **iP, *i;
		uint32_t nGoTos = 0;

		s->rule = NULL;

		for (iP = s->kernel; (i = *iP); ++iP)
		{
			if (i->i.tag == CHAR)
			{
				for (Ins *j = i + 1; j < (Ins*) i->i.link; ++j)
				{
					if (!(j->c.link = goTo[j->c.value - lb].to))
						goTo[nGoTos++].ch = j->c.value;

					goTo[j->c.value - lb].to = j;
				}
			}
			else if (i->i.tag == TERM)
			{
				if (!s->rule || ((RuleOp*) i->i.link)->rank < s->rule->rank)
					s->rule = (RuleOp*) i->i.link;
			}
			else if (i->i.tag == CTXT)
			{
				s->isPreCtxt = true;
			}
		}

		for (uint32_t j = 0; j < nGoTos; ++j)
		{
			GoTo *go = &goTo[goTo[j].ch - lb];
			i = (Ins*) go->to;

			for (cP = work; i; i = (Ins*) i->c.link)
				cP = closure(cP, i + i->c.bump);

			go->to = findState(work, cP - work);
		}

		s->go.nSpans = 0;

		for (uint32_t j = 0; j < nc;)
		{
			State *to = (State*) goTo[rep[j]].to;

			while (++j < nc && goTo[rep[j]].to == to) ;

			span[s->go.nSpans].ub = lb + j;

			span[s->go.nSpans].to = to;

			s->go.nSpans++;
		}

		for (uint32_t j = nGoTos; j-- > 0;)
			goTo[goTo[j].ch - lb].to = NULL;

		s->go.span = allocate<Span> (s->go.nSpans);

		memcpy((char*) s->go.span, (char*) span, s->go.nSpans*sizeof(Span));
	}

	delete [] work;
	delete [] goTo;
	operator delete (span);
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
	delete [] free_rep;
}

void DFA::addState(State **a, State *s)
{
	++nStates;
	s->next = *a;
	*a = s;

	if (a == tail)
		tail = &s->next;
}

State *DFA::findState(Ins **kernel, ptrdiff_t kCount)
{
	Ins **cP, **iP, *i;
	State *s;

	kernel[kCount] = NULL;

	cP = kernel;

	for (iP = kernel; (i = *iP); ++iP)
	{
		if (i->i.tag == CHAR || i->i.tag == TERM || i->i.tag == CTXT)
		{
			*cP++ = i;
		}
		else
		{
			unmark(i);
		}
	}

	kCount = cP - kernel;
	kernel[kCount] = NULL;

	for (s = head; s; s = s->next)
	{
		if (s->kCount == kCount)
		{
			for (iP = s->kernel; (i = *iP); ++iP)
				if (!isMarked(i))
					goto nextState;

			goto unmarkAll;
		}

nextState:
		;
	}

	s = new State;
	addState(tail, s);
	s->kCount = kCount;
	s->kernel = new Ins * [kCount + 1];
	memcpy(s->kernel, kernel, (kCount + 1)*sizeof(Ins*));
	s->link = toDo;
	toDo = s;

unmarkAll:

	for (iP = kernel; (i = *iP); ++iP)
		unmark(i);

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

