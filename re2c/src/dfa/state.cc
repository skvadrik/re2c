#include "src/dfa/action.h"
#include "src/dfa/state.h"

namespace re2c
{

State::State ()
	: label (0)
	, rule (NULL)
	, next (0)
	, link (NULL)
	, depth (0)
	, kCount (0)
	, kernel (NULL)
	, isPreCtxt (false)
	, isBase (false)
	, go ()
	, action (NULL)
{}

State::~State ()
{
	delete action;
	delete [] kernel;
	delete [] go.span;
}

std::ostream & operator << (std::ostream & o, const State & s)
{
	o << "state " << s.label;
	if (s.rule)
	{
		o << " accepts " << s.rule->accept;
	}
	o << "\n";
	uint32_t lb = 0;
	for (uint32_t i = 0; i < s.go.nSpans; ++i)
	{
		lb = s.go.span[i].show(o, lb);
	}
	return o;
}

} // namespace re2c

