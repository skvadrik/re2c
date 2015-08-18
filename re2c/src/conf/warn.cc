#include <iostream>
#include <sstream>

#include "src/codegen/print.h"
#include "src/conf/msg.h"
#include "src/conf/warn.h"

namespace re2c {

Warn warn;

const uint32_t Warn::SILENT  = 0;
const uint32_t Warn::WARNING = 1u << 0;
const uint32_t Warn::ERROR   = 1u << 1;

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
			// unlike -Werror, -Werror-<warning> implies -W<warning>
			mask[t] |= (WARNING | ERROR);
			break;
		case WNOERROR:
			mask[t] &= ~ERROR;
			break;
	}
}

void Warn::set_all ()
{
	for (uint32_t i = 0; i < TYPES; ++i)
	{
		mask[i] |= WARNING;
	}
}

// -Werror doesn't set any warnings: it only guarantees that if a warning
// has been set by now or will be set later then it will result into error.
void Warn::set_all_error ()
{
	for (uint32_t i = 0; i < TYPES; ++i)
	{
		mask[i] |= ERROR;
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

void Warn::swapped_range (uint32_t line, uint32_t l, uint32_t u)
{
	if (mask[SWAPPED_RANGE] & WARNING)
	{
		const bool e = mask[SWAPPED_RANGE] & ERROR;
		error_accuml |= e;
		warning (names[SWAPPED_RANGE], line, e, "range lower bound (0x%X) is greater than upper bound (0x%X), swapping", l, u);
	}
}

void Warn::useless_escape (uint32_t line, uint32_t col, char c)
{
	if (mask[USELESS_ESCAPE] & WARNING)
	{
		const bool e = mask[USELESS_ESCAPE] & ERROR;
		error_accuml |= e;
		warning (names[USELESS_ESCAPE], line, e, "column %u: escape has no effect: '\\%c'", col, c);
	}
}

} // namespace re2c
