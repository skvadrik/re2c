#include <iostream>

#include "src/ir/bytecode/ins.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/ir/rule_rank.h"

namespace re2c {

const Ins * showIns (std::ostream & o, const Ins & i, const Ins & base)
{
	o.width (3);
	o << &i - &base << ": ";
	const Ins * ret = &(&i)[1];
	switch (i.i.tag)
	{
		case CHAR:
		{
			o << "match ";
			for (; ret < (Ins *) i.i.link; ++ret)
			{
				o << "\\x" << std::hex << ret->c.value;
			}
			break;
		}
		case GOTO:
			o << "goto " << ((Ins *) i.i.link - &base);
			break;
		case FORK:
			o << "fork " << ((Ins *) i.i.link - &base);
			break;
		case CTXT:
			o << "ctxt";
			break;
		case TERM:
			o << "term " << ((RuleOp *) i.i.link)->rank;
			break;
	}
	o << "\n";
	return ret;
}

} // namespace re2c
