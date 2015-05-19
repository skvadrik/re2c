#ifndef __STATE__
#define __STATE__

#include "src/codegen/go.h"
#include "src/dfa/action.h"
#include "src/dfa/re.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class State
{
public:
	uint32_t label;
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

	State ();
	~State ();
	void emit (Output &, uint32_t, bool &, const std::string &) const;
	friend std::ostream& operator << (std::ostream &, const State &);

	FORBID_COPY (State);
};

} // namespace re2c

#endif // __STATE__
