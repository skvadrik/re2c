#include <string.h>

#include "src/codegen/skeleton/skeleton.h"
#include "src/ir/bytecode/bytecode.h"
#include "src/globals.h"

namespace re2c {

static void optimize (Ins * i);

smart_ptr<DFA> genCode (RegExp *re, Output & output, uint32_t ind, const std::string & cond)
{
	CharSet cs;
	re->split(cs);

	Char *rep = new Char[encoding.nCodeUnits()];

	for (uint32_t j = 0; j < encoding.nCodeUnits(); ++j)
	{
		if (!cs.rep[j]->nxt)
			cs.rep[j]->nxt = &cs.ptn[j];

		rep[j] = cs.rep[j]->nxt - &cs.ptn[0];
	}

	re->calcSize(rep);
	Ins *ins = new Ins[re->size + 1];
	memset(ins, 0, (re->size + 1)*sizeof(Ins));
	const uint32_t size = re->compile(rep, ins);
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

	smart_ptr<DFA> dfa = make_smart_ptr(new DFA(ins, size, 0, encoding.nCodeUnits(), rep));
	if (flag_skeleton)
	{
		skeleton::Skeleton skeleton (*dfa);
		skeleton.emit_data (output.data);
		skeleton::emit_prolog (output.source, ind, output.data.file_name.c_str ());
	}
	dfa->prepare (output.source, output.max_fill, cond);

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
