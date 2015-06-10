#ifndef _RE2C_IR_DFA_STATE_
#define _RE2C_IR_DFA_STATE_

#include "src/codegen/go.h"
#include "src/ir/dfa/action.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class State
{
public:
	label_t label;
	RuleOp * rule;
	State * next;
	State * link;
	uint32_t depth; // for finding SCCs
	uint32_t kCount;
	Ins ** kernel;

	bool isPreCtxt;
	bool isBase;
	Go go;
	Action action;

	State ()
		: label (label_t::first ())
		, rule (NULL)
		, next (0)
		, link (NULL)
		, depth (0)
		, kCount (0)
		, kernel (NULL)
		, isPreCtxt (false)
		, isBase (false)
		, go ()
		, action ()
	{}
	~State ()
	{
		delete [] kernel;
		operator delete (go.span);
	}

	FORBID_COPY (State);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_STATE_
