#include <stdio.h>

#include "src/conf/msg.h"
#include "src/conf/opt.h"

namespace re2c
{

static inline bool next (char * & arg, char ** & argv)
{
	arg = *++argv;
	return arg != NULL;
}

parse_opts_t parse_opts (char ** argv, Opt & opts)
{
#define YYCTYPE unsigned char
	char * YYCURSOR;
	char * YYMARKER;
	Warn::option_t option;

/*!re2c
	re2c:yyfill:enable = 0;
	re2c:yych:conversion = 1;

	end = "\x00";
	filename = [^\x00-] [^\x00]*;
*/

opt:
	if (!next (YYCURSOR, argv))
	{
		goto end;
	}
/*!re2c
	*
	{
		error ("bad option: %s", *argv);
		return EXIT_FAIL;
	}

	"--" end
	{
		// all remaining arguments are non-options
		// so they must be input files
		// re2c expects exactly one input file
		for (char * f; next (f, argv);)
		{
			if (!opts.source (f))
			{
				return EXIT_FAIL;
			}
		}
		goto end;
	}

	"-"      end { if (!opts.source ("<stdin>")) return EXIT_FAIL; goto opt; }
	filename end { if (!opts.source (*argv))     return EXIT_FAIL; goto opt; }

	"-"  { goto opt_short; }
	"--" { goto opt_long; }

	"-W"      end { warn.set_all ();       goto opt; }
	"-Werror" end { warn.set_all_error (); goto opt; }
	"-W"          { option = Warn::W;        goto opt_warn; }
	"-Wno-"       { option = Warn::WNO;      goto opt_warn; }
	"-Werror-"    { option = Warn::WERROR;   goto opt_warn; }
	"-Wno-error-" { option = Warn::WNOERROR; goto opt_warn; }
*/

opt_warn:
/*!re2c
	*
	{
		error ("bad warning: %s", *argv);
		return EXIT_FAIL;
	}
	"condition-order"        end { warn.set (Warn::CONDITION_ORDER,        option); goto opt; }
	"empty-character-class"  end { warn.set (Warn::EMPTY_CHARACTER_CLASS,  option); goto opt; }
	"match-empty-string"     end { warn.set (Warn::MATCH_EMPTY_STRING,     option); goto opt; }
	"swapped-range"          end { warn.set (Warn::SWAPPED_RANGE,          option); goto opt; }
	"undefined-control-flow" end { warn.set (Warn::UNDEFINED_CONTROL_FLOW, option); goto opt; }
	"useless-escape"         end { warn.set (Warn::USELESS_ESCAPE,         option); goto opt; }
*/

opt_short:
/*!re2c
	*
	{
		error ("bad short option: %s", *argv);
		return EXIT_FAIL;
	}
	end { goto opt; }
	[?h] { usage ();   return EXIT_OK; }
	"v"  { version (); return EXIT_OK; }
	"V"  { vernum ();  return EXIT_OK; }
	"b" { opts.bit_vectors ();      goto opt_short; }
	"c" { opts.start_conditions (); goto opt_short; }
	"d" { opts.debug_output ();     goto opt_short; }
	"D" { opts.emit_dot ();         goto opt_short; }
	"f" { opts.storable_state ();   goto opt_short; }
	"F" { opts.flex_syntax ();      goto opt_short; }
	"g" { opts.computed_gotos ();   goto opt_short; }
	"i" { opts.no_debug_info ();    goto opt_short; }
	"r" { opts.reusable ();         goto opt_short; }
	"s" { opts.nested_ifs ();       goto opt_short; }
	"e" { if (!opts.ecb ())        { error_encoding (); return EXIT_FAIL; } goto opt_short; }
	"u" { if (!opts.unicode ())    { error_encoding (); return EXIT_FAIL; } goto opt_short; }
	"w" { if (!opts.wide_chars ()) { error_encoding (); return EXIT_FAIL; } goto opt_short; }
	"x" { if (!opts.utf_16 ())     { error_encoding (); return EXIT_FAIL; } goto opt_short; }
	"8" { if (!opts.utf_8 ())      { error_encoding (); return EXIT_FAIL; } goto opt_short; }
	"o" end { if (!next (YYCURSOR, argv)) { error_arg ("-o, --output"); return EXIT_FAIL; } goto opt_output; }
	"o"     { *argv = YYCURSOR;                                                             goto opt_output; }
	"t" end { if (!next (YYCURSOR, argv)) { error_arg ("-t, --type-header"); return EXIT_FAIL; } goto opt_header; }
	"t"     { *argv = YYCURSOR;                                                                  goto opt_header; }
	"1" { goto opt_short; } // deprecated
*/

opt_long:
/*!re2c
	*
	{
		error ("bad long option: %s", *argv);
		return EXIT_FAIL;
	}
	"help"               end { usage ();   return EXIT_OK; }
	"version"            end { version (); return EXIT_OK; }
	"vernum"             end { vernum ();  return EXIT_OK; }
	"bit-vectors"        end { opts.bit_vectors ();        goto opt; }
	"start-conditions"   end { opts.start_conditions ();   goto opt; }
	"debug-output"       end { opts.debug_output ();       goto opt; }
	"emit-dot"           end { opts.emit_dot ();           goto opt; }
	"storable-state"     end { opts.storable_state ();     goto opt; }
	"flex-syntax"        end { opts.flex_syntax ();        goto opt; }
	"computed-gotos"     end { opts.computed_gotos ();     goto opt; }
	"no-debug-info"      end { opts.no_debug_info ();      goto opt; }
	"reusable"           end { opts.reusable ();           goto opt; }
	"nested-ifs"         end { opts.nested_ifs ();         goto opt; }
	"no-generation-date" end { opts.no_generation_date (); goto opt; }
	"case-insensitive"   end { opts.case_insensitive ();   goto opt; }
	"case-inverted"      end { opts.case_inverted ();      goto opt; }
	"skeleton"           end { opts.skeleton ();           goto opt; }
	"ecb"                end { if (!opts.ecb ())        { error_encoding (); return EXIT_FAIL; } goto opt; }
	"unicode"            end { if (!opts.unicode ())    { error_encoding (); return EXIT_FAIL; } goto opt; }
	"wide-chars"         end { if (!opts.wide_chars ()) { error_encoding (); return EXIT_FAIL; } goto opt; }
	"utf-16"             end { if (!opts.utf_16 ())     { error_encoding (); return EXIT_FAIL; } goto opt; }
	"utf-8"              end { if (!opts.utf_8 ())      { error_encoding (); return EXIT_FAIL; } goto opt; }
	"output"             end { if (!next (YYCURSOR, argv)) { error_arg ("-o, --output"); return EXIT_FAIL; } goto opt_output; }
	"type-header"        end { if (!next (YYCURSOR, argv)) { error_arg ("-t, --type-header"); return EXIT_FAIL; } goto opt_header; }
	"encoding-policy"    end { goto opt_encoding_policy; }
	"input"              end { goto opt_input; }
	"empty-class"        end { goto opt_empty_class; }
	"single-pass"        end { goto opt; } // deprecated
*/

opt_output:
/*!re2c
	*
	{
		error ("bad argument to option -o, --output: %s", *argv);
		return EXIT_FAIL;
	}
	filename end { if (!opts.output (*argv)) return EXIT_FAIL; goto opt; }
*/

opt_header:
/*!re2c
	*
	{
		error ("bad argument to option -t, --type-header: %s", *argv);
		return EXIT_FAIL;
	}
	filename end { if (!opts.type_header (*argv)) return EXIT_FAIL; goto opt; }
*/

opt_encoding_policy:
	if (!next (YYCURSOR, argv))
	{
		error_arg ("--encoding-policy");
		return EXIT_FAIL;
	}
/*!re2c
	*
	{
		error ("bad argument to option --encoding-policy (expected: ignore | substitute | fail): %s", *argv);
		return EXIT_FAIL;
	}
	"ignore"     end { opts.encoding_policy (Enc::POLICY_IGNORE);     goto opt; }
	"substitute" end { opts.encoding_policy (Enc::POLICY_SUBSTITUTE); goto opt; }
	"fail"       end { opts.encoding_policy (Enc::POLICY_FAIL);       goto opt; }
*/

opt_input:
	if (!next (YYCURSOR, argv))
	{
		error_arg ("--input");
		return EXIT_FAIL;
	}
/*!re2c
	*
	{
		error ("bad argument to option --input (expected: default | custom): %s", *argv);
		return EXIT_FAIL;
	}
	"default" end { opts.input (InputAPI::DEFAULT); goto opt; }
	"custom"  end { opts.input (InputAPI::CUSTOM);  goto opt; }
*/

opt_empty_class:
	if (!next (YYCURSOR, argv))
	{
		error_arg ("--empty-class");
		return EXIT_FAIL;
	}
/*!re2c
	*
	{
		error ("bad argument to option --empty-class (expected: match-empty | match-none | error): %s", *argv);
		return EXIT_FAIL;
	}
	"match-empty" end { opts.empty_class (EMPTY_CLASS_MATCH_EMPTY); goto opt; }
	"match-none"  end { opts.empty_class (EMPTY_CLASS_MATCH_NONE);  goto opt; }
	"error"       end { opts.empty_class (EMPTY_CLASS_ERROR);       goto opt; }
*/

end:
	if (!opts.source_file)
	{
		error ("no source file");
		return EXIT_FAIL;
	}
	if (!cFlag && opts.header_file)
	{
		error ("can only output a header file when using -c switch");
		return EXIT_FAIL;
	}
	if (DFlag && (bFlag || dFlag || sFlag || flag_skeleton))
	{
		error ("cannot combine -D with -b, -d, -s or --skeleton switches");
		return EXIT_FAIL;
	}

	return OK;

#undef YYCTYPE
}

} // namespace re2c
