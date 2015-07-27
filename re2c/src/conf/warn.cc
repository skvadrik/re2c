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
	, error_accuml (false)
{
	for (uint32_t i = 0; i < TYPES; ++i)
	{
		mask[i] = SILENT;
	}
}

bool Warn::error () const
{
	return error_accuml;
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
		const bool e = mask[EMPTY_CHARACTER_CLASS] & ERROR;
		error_accuml |= e;
		warning (names[EMPTY_CHARACTER_CLASS], line, e, "empty character class");
	}
}

void Warn::match_empty_string (uint32_t line)
{
	if (mask[MATCH_EMPTY_STRING] & WARNING)
	{
		const bool e = mask[MATCH_EMPTY_STRING] & ERROR;
		error_accuml |= e;
		warning (names[MATCH_EMPTY_STRING], line, e, "rule matches empty string");
	}
}

void Warn::naked_default (uint32_t line, const std::vector<std::pair<uint32_t, uint32_t> > & stray_cunits, const std::string & cond)
{
	if (mask[NAKED_DEFAULT] & WARNING)
	{
		const bool e = mask[NAKED_DEFAULT] & ERROR;
		error_accuml |= e;
		std::ostringstream cunits;
		for (uint32_t i = 0; i < stray_cunits.size (); ++i)
		{
			printSpan (cunits, stray_cunits[i].first, stray_cunits[i].second);
		}
		const char * cond_prefix = cond == ""
			? ""
			: " in condition ";
		warning
			( names[NAKED_DEFAULT]
			, line
			, e
			, "naked default case%s%s (stray code units: %s), better add default rule *"
			, cond_prefix
			, cond.c_str ()
			, cunits.str ().c_str ()
			);
	}
}

} // namespace re2c
