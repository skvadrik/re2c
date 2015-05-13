#ifndef __ACTION__
#define __ACTION__

#include <map>

#include "src/dfa/state.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class Action
{
public:
	State * state;
	enum type_t
	{
		NONE,
		MATCH,
		INITIAL,
		SAVE,
		MOVE,
		ACCEPT,
		RULE
	} type;

	explicit inline Action (State * s)
		: state (s)
		, type (NONE)
	{
		delete s->action;
		s->action = this;
	}
	virtual ~Action () {}
	inline bool readAhead () const
	{
		return (type != MATCH)
			|| (state && state->next
				&& state->next->action
				&& (state->next->action->type != RULE));
	}
	virtual void emit (Output &, uint32_t, bool &, const std::string &) const = 0;

	FORBID_COPY (Action);
};

class Match: public Action
{
public:
	explicit inline Match (State * s)
		: Action (s)
	{
		type = MATCH;
	}
	void emit (Output &, uint32_t, bool &, const std::string &) const;
};

class Initial: public Action
{
public:
	uint32_t label;
	bool setMarker;

	inline Initial (State * s, uint32_t l, bool b)
		: Action (s)
		, label (l)
		, setMarker (b)
	{
		type = INITIAL;
	}
	void emit (Output &, uint32_t, bool &, const std::string &) const;
};

class Save: public Match
{
public:
	uint32_t selector;

	inline Save (State * s, uint32_t i)
		: Match (s)
		, selector (i)
	{
		type = SAVE;
	}
	void emit (Output &, uint32_t, bool &, const std::string &) const;
};

class Move: public Action
{
public:
	explicit inline Move (State * s)
		: Action (s)
	{
		type = MOVE;
	}
	void emit (Output &, uint32_t, bool &, const std::string &) const;
};

class Accept: public Action
{
public:
	typedef std::map<uint32_t, State *> RuleMap;

	uint32_t nRules;
	uint32_t * saves;
	State ** rules;
	RuleMap mapRules;

	inline Accept (State * x, uint32_t n, uint32_t * s, State ** r)
		: Action (x)
		, nRules (n)
		, saves (s)
		, rules (r)
		, mapRules ()
	{
		type = ACCEPT;
	}
	void emit (Output &, uint32_t, bool &, const std::string &) const;
	void emitBinary (OutputFile & o, uint32_t ind, uint32_t l, uint32_t r, bool & readCh) const;
	void genRuleMap ();

	FORBID_COPY (Accept);
};

class Rule: public Action
{
public:
	RuleOp * rule;

	inline Rule (State * s, RuleOp * r)
		: Action(s)
		, rule(r)
	{
		type = RULE;
	}
	void emit (Output &, uint32_t, bool &, const std::string &) const;

	FORBID_COPY (Rule);
};

} // namespace re2c

#endif // __ACTION__
