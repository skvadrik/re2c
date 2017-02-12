#ifndef _RE2C_IR_ADFA_ACTION_
#define _RE2C_IR_ADFA_ACTION_

#include <assert.h>
#include <vector>

#include "src/codegen/label.h"
#include "src/util/c99_stdint.h"
#include "src/util/uniq_vector.h"

namespace re2c
{

class OutputFile;
struct State;

struct Initial
{
	static const size_t NOSAVE;

	label_t label;
	size_t save;

	inline Initial (label_t l, size_t s)
		: label (l)
		, save (s)
	{}
};

typedef uniq_vector_t<std::pair<const State*, tcid_t> > accept_t;

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
	union
	{
		Initial * initial;
		size_t save;
		const accept_t * accepts;
		size_t rule;
	} info;

public:
	inline Action ()
		: type (MATCH)
		, info ()
	{}
	~Action ()
	{
		if (type == INITIAL) {
			delete info.initial;
		}
	}
	void set_initial (label_t label)
	{
		if (type == MATCH) {
			// ordinary state with no special action
			type = INITIAL;
			info.initial = new Initial(label, Initial::NOSAVE);
		} else if (type == SAVE) {
			// fallback state: do not loose 'yyaccept'
			type = INITIAL;
			info.initial = new Initial(label, info.save);
		} else if (type == INITIAL) {
			// already marked as initial, probably reuse mode
			info.initial->label = label;
		} else {
			assert(false);
		}
	}
	void set_save (size_t save)
	{
		assert(type == MATCH);
		type = SAVE;
		info.save = save;
	}
	void set_move ()
	{
		assert(type == MATCH);
		type = MOVE;
	}
	void set_accept (const accept_t * accepts)
	{
		assert(type == MATCH);
		type = ACCEPT;
		info.accepts = accepts;
	}
	void set_rule (size_t rule)
	{
		assert(type == MATCH);
		type = RULE;
		info.rule = rule;
	}
};

} // namespace re2c

#endif // _RE2C_IR_ADFA_ACTION_
