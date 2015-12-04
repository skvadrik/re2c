#include <assert.h>
#include <string.h>
#include <algorithm>

#include "src/codegen/output.h"
#include "src/ir/bytecode/bytecode.h"
#include "src/ir/bytecode/ins.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/spec.h"

namespace re2c {

static void optimize (Ins * i);

smart_ptr<DFA> genCode (Spec & spec, Output & output, const std::string & cond, uint32_t cunits)
{
	RegExp * re = spec.re;

	// The original set of code units (charset) might be very large.
	// A common trick it is to split charset into disjoint character ranges
	// and choose a representative of each range (we choose lower bound).
	// The set of all representatives is the new (compacted) charset.
	// (Don't forget to include zero and exclude upper bound.)
	charset_t cs;
	re->split(cs);
	cs.insert(0);
	cs.erase(cunits);

	re->calcSize(cs);

	Ins *ins = new Ins[re->size + 1];
	memset(ins, 0, (re->size + 1)*sizeof(Ins));
	const uint32_t size = re->compile(cs, ins);
	Ins *eoi = &ins[size];
	eoi->i.tag = GOTO;
	eoi->i.link = eoi;

	optimize(ins);

	/*
	for (const Ins *inst = &ins[0]; inst < &ins[size]; )
	{
		inst = showIns(std::cout, *inst, ins[0]);
	}
	*/

	for (uint32_t j = 0; j < size;)
	{
		unmark(&ins[j]);

		if (ins[j].i.tag == CHAR)
		{
			j = static_cast<uint32_t> ((Ins*) ins[j].i.link - ins);
		}
		else
		{
			j++;
		}
	}

	smart_ptr<DFA> dfa = make_smart_ptr (new DFA
		( cond
		, output.source.get_block_line ()
		, ins
		, size
		, 0
		, cunits
		, cs
		, spec.rules
		));

	// accumulate global statistics from this particular DFA
	output.max_fill = std::max (output.max_fill, dfa->max_fill);
	if (dfa->need_accept)
	{
		output.source.set_used_yyaccept ();
	}

	return dfa;
}

void optimize (Ins * i)
{
	while (!isMarked (i))
	{
		mark (i);
		if (i->i.tag == CHAR)
		{
			i = (Ins *) i->i.link;
		}
		else if (i->i.tag == GOTO || i->i.tag == FORK)
		{
			Ins * target = (Ins *) i->i.link;
			optimize (target);
			if (target->i.tag == GOTO)
			{
				i->i.link = target->i.link == target
					? i
					: target;
			}
			if (i->i.tag == FORK)
			{
				Ins * follow = (Ins *) & i[1];
				optimize (follow);
				if (follow->i.tag == GOTO && follow->i.link == follow)
				{
					i->i.tag = GOTO;
				}
				else if (i->i.link == i)
				{
					i->i.tag = GOTO;
					i->i.link = follow;
				}
			}
			return;
		}
		else
		{
			++i;
		}
	}
}

} // namespace re2c
