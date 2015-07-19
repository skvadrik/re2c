#ifndef _RE2C_CONF_OPT_
#define _RE2C_CONF_OPT_

#include <string>

#include "src/codegen/input_api.h"
#include "src/globals.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/regexp/empty_class_policy.h"

namespace re2c
{

struct Opt
{
	const char * source_file;
	const char * output_file;
	const char * header_file;

	Opt ()
		: source_file (NULL)
		, output_file ("<stdout>")
		, header_file (NULL)
	{}

	void bit_vectors ();
	void start_conditions ();
	void debug_output ();
	void emit_dot ();
	void storable_state ();
	void flex_syntax ();
	void computed_gotos ();
	void no_debug_info ();
	void reusable ();
	void nested_ifs ();
	void no_generation_date ();
	void case_insensitive ();
	void case_inverted ();
	void skeleton ();
	void source (const char * s);
	void output (const char * s);
	void type_header (const char * s);
	void encoding_policy (Enc::policy_t);
	void input (InputAPI::type_t);
	void empty_class (empty_class_policy_t);
	bool ecb ();
	bool unicode ();
	bool wide_chars ();
	bool utf_16 ();
	bool utf_8 ();
};

enum parse_opts_t
{
	OK,
	EXIT_OK,
	EXIT_FAIL
};

parse_opts_t parse_opts (int argc, char ** argv, Opt & opts);

} // namespace re2c

#endif // _RE2C_CONF_OPT_
