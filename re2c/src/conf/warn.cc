#include <iostream>
#include <sstream>

#include "src/codegen/print.h"
#include "src/conf/msg.h"
#include "src/conf/warn.h"

namespace re2c {

Warn warn;

const uint8_t Warn::SILENT  = 0;
const uint8_t Warn::WARNING = 1u << 0;
const uint8_t Warn::ERROR   = 1u << 1;

const char * Warn::names [TYPES] =
{
#define W(x, y) y
	RE2C_WARNING_TYPES
#undef W
};

Warn::Warn ()
	: mask ()
	, error (false)
{
	for (uint32_t i = 0; i < TYPES; ++i)
	{
		mask[i] = SILENT;
	}
}

uint32_t Warn::error_code () const
{
	return error;
}

void Warn::set (type_t t, option_t o)
{
	switch (o)
	{
		case W:
			mask[t] |= WARNING;
			break;
		case WNO:
			mask[t] &= ~WARNING;
			break;
		case WERROR:
			mask[t] |= ERROR;
			break;
		case WNOERROR:
			mask[t] &= ~ERROR;
			break;
	}
}

void Warn::set_all (option_t o)
{
	for (uint32_t i = 0; i < TYPES; ++i)
	{
		set (static_cast<type_t> (i), o);
	}
}

void Warn::empty_class (uint32_t line)
{
	if (mask[EMPTY_CHARACTER_CLASS] & WARNING)
	{
		if (mask[EMPTY_CHARACTER_CLASS] & ERROR)
		{
			error = true;
		}
		warning (names[EMPTY_CHARACTER_CLASS], "empty character class at line %u", line);
	}
}

void Warn::empty_rule (uint32_t line)
{
	if (mask[EMPTY_RULE] & WARNING)
	{
		if (mask[EMPTY_RULE] & ERROR)
		{
			error = true;
		}
		warning (names[EMPTY_RULE], "empty rule at line %u", line);
	}
}

void Warn::naked_default (const std::vector<std::pair<uint32_t, uint32_t> > & stray_cunits)
{
	if (mask[NAKED_DEFAULT] & WARNING)
	{
		if (mask[NAKED_DEFAULT] & ERROR)
		{
			error = true;
		}
		std::ostringstream s;
		for (uint32_t i = 0; i < stray_cunits.size (); ++i)
		{
			printSpan (s, stray_cunits[i].first, stray_cunits[i].second);
		}
		warning (names[NAKED_DEFAULT], "naked default case (stray code units: %s), better add default rule *", s.str ().c_str ());
	}
}

} // namespace re2c
