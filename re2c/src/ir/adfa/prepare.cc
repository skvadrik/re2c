#include "src/util/c99_stdint.h"
#include <string.h>
#include <map>

#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/globals.h"
#include "src/ir/adfa/action.h"
#include "src/ir/adfa/adfa.h"
#include "src/util/allocate.h"

namespace re2c {

void DFA::split(State *s)
{
	State *move = new State;
	addState(move, s);
	move->action.set_move ();
	move->rule = s->rule;
	move->fill = s->fill;
	move->go = s->go;
	s->rule = Rule::NONE;
	s->go.nSpans = 1;
	s->go.span = allocate<Span> (1);
	s->go.span[0].ub = ubChar;
	s->go.span[0].to = move;
}

static uint32_t merge(Span *x, State *fg, State *bg)
{
	Span *f = fg->go.span;
	Span *b = bg->go.span;
	Span *const fe = f + fg->go.nSpans;
	Span *const be = b + bg->go.nSpans;
	Span *const x0 = x;

	for (;!(f == fe && b == be);) {
		if (f->to == b->to) {
			x->to = bg;
		} else {
			x->to = f->to;
		}
		if (x == x0
			|| x[-1].to != x->to) {
			++x;
		}
		x[-1].ub = std::min(f->ub, b->ub);

		if (f->ub < b->ub) {
			++f;
		} else if (f->ub > b->ub) {
			++b;
		} else {
			++f;
			++b;
		}
	}

	return static_cast<uint32_t>(x - x0);
}

void DFA::findBaseState()
{
	Span *span = allocate<Span> (ubChar - lbChar);

	for (State *s = head; s; s = s->next)
	{
		if (s->fill == 0)
		{
			for (uint32_t i = 0; i < s->go.nSpans; ++i)
			{
				State *to = s->go.span[i].to;

				if (to->isBase)
				{
					to = to->go.span[0].to;
					uint32_t nSpans = merge(span, s, to);

					if (nSpans < s->go.nSpans)
					{
						operator delete (s->go.span);
						s->go.nSpans = nSpans;
						s->go.span = allocate<Span> (nSpans);
						memcpy(s->go.span, span, nSpans*sizeof(Span));
					}

					break;
				}
			}
		}
	}

	operator delete (span);
}

void DFA::prepare ()
{
	bUsedYYBitmap = false;

	// create rule states
	std::vector<State*> rule2state(rules.size());
	for (State *s = head; s; s = s->next) {
		if (s->rule != Rule::NONE) {
			if (!rule2state[s->rule]) {
				State *n = new State;
				n->action.set_rule(s->rule);
				rule2state[s->rule] = n;
				addState(n, s);
			}
			for (uint32_t i = 0; i < s->go.nSpans; ++i) {
				if (!s->go.span[i].to) {
					s->go.span[i].to = rule2state[s->rule];
				}
			}
		}
	}

	// create default state (if needed)
	State * default_state = NULL;
	for (State * s = head; s; s = s->next)
	{
		for (uint32_t i = 0; i < s->go.nSpans; ++i)
		{
			if (!s->go.span[i].to)
			{
				if (!default_state)
				{
					default_state = new State;
					addState(default_state, s);
				}
				s->go.span[i].to = default_state;
			}
		}
	}

	// bind save actions to fallback states and create accept state (if needed)
	if (default_state) {
		for (State *s = head; s; s = s->next) {
			if (s->fallback) {
				const size_t accept = accepts.find_or_add(rule2state[s->rule]);
				s->action.set_save(accept);
			}
		}
		default_state->action.set_accept(&accepts);
	}

	// split ``base'' states into two parts
	for (State * s = head; s; s = s->next)
	{
		s->isBase = false;

		if (s->fill != 0)
		{
			for (uint32_t i = 0; i < s->go.nSpans; ++i)
			{
				if (s->go.span[i].to == s)
				{
					s->isBase = true;
					split(s);

					if (opts->bFlag)
					{
						BitMap::find(&s->next->go, s);
					}

					s = s->next;
					break;
				}
			}
		}
	}

	// find ``base'' state, if possible
	findBaseState();

	for (State * s = head; s; s = s->next)
	{
		s->go.init (s);
	}
}

void DFA::calc_stats ()
{
	// calculate 'YYMAXFILL'
	max_fill = 0;
	for (State * s = head; s; s = s->next)
	{
		if (max_fill < s->fill)
		{
			max_fill = s->fill;
		}
	}

	// determine if 'YYMARKER' or 'YYBACKUP'/'YYRESTORE' pair is used
	need_backup = accepts.size () > 0;

	// determine if 'yyaccept' variable is used
	need_accept = accepts.size () > 1;
}

} // namespace re2c
