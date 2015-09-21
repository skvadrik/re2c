#include "src/conf/msg.h"
#include "src/conf/opt.h"

namespace re2c
{

Opt opts;

void Opt::bit_vectors ()
{
	bFlag = true;
	sFlag = true;
}

void Opt::start_conditions ()
{
	cFlag = true;
}

void Opt::debug_output ()
{
	dFlag = true;
}

void Opt::emit_dot ()
{
	DFlag = true;
	iFlag = true;
}

void Opt::storable_state ()
{
	fFlag = true;
}

void Opt::flex_syntax ()
{
	FFlag = true;
}

void Opt::computed_gotos ()
{
	gFlag = true;
	bFlag = true;
	sFlag = true;
}

void Opt::no_debug_info ()
{
	iFlag = true;
}

void Opt::reusable ()
{
	rFlag = true;
}

void Opt::nested_ifs ()
{
	sFlag = true;
}

void Opt::no_generation_date ()
{
	bNoGenerationDate = true;
}

void Opt::case_insensitive ()
{
	bCaseInsensitive = true;
}

void Opt::case_inverted ()
{
	bCaseInverted = true;
}

void Opt::skeleton ()
{
	flag_skeleton = true;
	input_api.set (InputAPI::CUSTOM);
}

void Opt::encoding_policy (Enc::policy_t p)
{
	encoding.setPolicy (p);
}

void Opt::input (InputAPI::type_t i)
{
	input_api.set (i);
}

void Opt::empty_class (empty_class_policy_t p)
{
	empty_class_policy = p;
}

bool Opt::source (const char * s)
{
	if (source_file)
	{
		error ("multiple source files: %s, %s", source_file, s);
		return false;
	}
	else
	{
		source_file = s;
		return true;
	}
}

bool Opt::output (const char * s)
{
	if (output_file)
	{
		error ("multiple output files: %s, %s", output_file, s);
		return false;
	}
	else
	{
		output_file = s;
		return true;
	}
}

bool Opt::type_header (const char * s)
{
	if (header_file)
	{
		error ("multiple header files: %s, %s", header_file, s);
		return false;
	}
	else
	{
		tFlag = true;
		header_file = s;
		return true;
	}
}

bool Opt::ecb ()
{
	return encoding.set (Enc::EBCDIC);
}

bool Opt::unicode ()
{
	sFlag = true;
	return encoding.set(Enc::UTF32);
}

bool Opt::wide_chars ()
{
	sFlag = true;
	return encoding.set(Enc::UCS2);
}

bool Opt::utf_16 ()
{
	sFlag = true;
	return encoding.set(Enc::UTF16);
}

bool Opt::utf_8 ()
{
	return encoding.set(Enc::UTF8);
}

} // namespace re2c
