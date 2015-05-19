#ifndef __ACTION__
#define __ACTION__

#include <map>
#include <string>

#include "src/util/c99_stdint.h"

namespace re2c
{

struct OutputFile;
class RuleOp;
class State;

struct Initial
{
	uint32_t label;
	bool setMarker;

	inline Initial (uint32_t l, bool b)
		: label (l)
		, setMarker (b)
	{}
};

typedef std::map<uint32_t, const State *> accept_t;

class Action
{
public:
	enum type_t
	{
		MATCH,
		INITIAL,
		SAVE,
		MOVE,
		ACCEPT,
		RULE
	} type;

private:
	union
	{
		Initial * initial;
		uint32_t save;
		accept_t * accept;
		const RuleOp * rule;
	} info;

public:
	inline Action ()
		: type (MATCH)
		, info ()
	{}
	~Action ()
	{
		clear ();
	}
	void set_initial (uint32_t label, bool used_marker)
	{
		clear ();
		type = INITIAL;
		info.initial = new Initial (label, used_marker);
	}
	void set_save (uint32_t save)
	{
		clear ();
		type = SAVE;
		info.save = save;
	}
	void set_move ()
	{
		clear ();
		type = MOVE;
	}
	void set_accept (uint32_t rules_count, uint32_t * saves, State * const * rules)
	{
		clear ();
		type = ACCEPT;
		info.accept = new accept_t ();
		for (uint32_t i = 0; i < rules_count; ++i)
		{
			if (saves[i] != ~0u)
			{
				(* info.accept)[saves[i]] = rules[i];
			}
		}
	}
	void set_rule (const RuleOp * const rule)
	{
		clear ();
		type = RULE;
		info.rule = rule;
	}
	friend void emit_action (const Action & action, OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const std::string & condName);

private:
	void clear ()
	{
		switch (type)
		{
			case INITIAL:
				delete info.initial;
				break;
			case ACCEPT:
				delete info.accept;
				break;
			case MATCH:
			case SAVE:
			case MOVE:
			case RULE:
				break;
		}
	}
};

} // namespace re2c

#endif // __ACTION__
