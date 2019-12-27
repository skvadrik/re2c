#include <stddef.h>
#include <algorithm>
#include <string>
#include <vector>

#include "src/codegen/input_api.h"
#include "src/dfa/dfa.h"
#include "src/encoding/enc.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/regexp/empty_class_policy.h"


namespace re2c {

static inline bool next (char * & arg, char ** & argv)
{
    arg = *++argv;
    return arg != NULL;
}

parse_opts_t parse_opts(char **argv, conopt_t &globopts, Opt &opts, Msg &msg)
{
#define YYCTYPE unsigned char

#define NEXT_ARG(option, label) do { \
    if (next (YYCURSOR, argv)) goto label; \
    else { error_arg(option); return EXIT_FAIL; } \
} while(0)

#define ERROR(msg, arg) do { \
    error(msg, arg); \
    return EXIT_FAIL; \
} while(0)

#define ERRARG(opt, exp, arg) do { \
    error("bad argument '%s' to option %s <%s>", arg, opt, exp); \
    return EXIT_FAIL; \
} while(0)

    char *YYCURSOR, *YYMARKER;
    Warn::option_t option;

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:yych:conversion = 1;

    end = "\x00";
    filename = [^\x00-] [^\x00]*;
*/

opt:
    if (!next (YYCURSOR, argv)) goto end;
/*!re2c
    * { ERROR("bad option: %s", *argv); }

    "--" end {
        // remaining args are non-options, so they must be input files
        // re2c expects exactly one input file
        for (char * f; next (f, argv);) {
            if (!opts.source (f)) return EXIT_FAIL;
        }
        goto end;
    }

    "-"      end { if (!opts.source ("<stdin>")) return EXIT_FAIL; goto opt; }
    filename end { if (!opts.source (*argv))     return EXIT_FAIL; goto opt; }

    "-"  { goto opt_short; }
    "--" { goto opt_long; }

    "-W"      end { msg.warn.set_all ();       goto opt; }
    "-Werror" end { msg.warn.set_all_error (); goto opt; }
    "-W"          { option = Warn::W;        goto opt_warn; }
    "-Wno-"       { option = Warn::WNO;      goto opt_warn; }
    "-Werror-"    { option = Warn::WERROR;   goto opt_warn; }
    "-Wno-error-" { option = Warn::WNOERROR; goto opt_warn; }
*/

opt_warn:
/*!re2c
    * { ERROR("bad warning: %s", *argv); }

    "condition-order"          end { msg.warn.set (Warn::CONDITION_ORDER,        option); goto opt; }
    "empty-character-class"    end { msg.warn.set (Warn::EMPTY_CHARACTER_CLASS,  option); goto opt; }
    "match-empty-string"       end { msg.warn.set (Warn::MATCH_EMPTY_STRING,     option); goto opt; }
    "nondeterministic-tags"    end { msg.warn.set (Warn::NONDETERMINISTIC_TAGS,  option); goto opt; }
    "swapped-range"            end { msg.warn.set (Warn::SWAPPED_RANGE,          option); goto opt; }
    "undefined-control-flow"   end { msg.warn.set (Warn::UNDEFINED_CONTROL_FLOW, option); goto opt; }
    "unreachable-rules"        end { msg.warn.set (Warn::UNREACHABLE_RULES,      option); goto opt; }
    "useless-escape"           end { msg.warn.set (Warn::USELESS_ESCAPE,         option); goto opt; }
    "sentinel-in-midrule"      end { msg.warn.set (Warn::SENTINEL_IN_MIDRULE,    option); goto opt; }
*/

opt_short:
/*!re2c
    * { ERROR("bad short option: %s", *argv); }

    end { goto opt; }
    [?h] { usage ();   return EXIT_OK; }
    "v"  { version (); return EXIT_OK; }
    "V"  { vernum ();  return EXIT_OK; }

    "c" { globopts.cFlag = true;             goto opt_short; }
    "D" { globopts.target = TARGET_DOT;      goto opt_short; }
    "f" { globopts.fFlag = true;             goto opt_short; }
    "F" { globopts.FFlag = true;             goto opt_short; }
    "r" { globopts.rFlag = true;             goto opt_short; }
    "S" { globopts.target = TARGET_SKELETON; goto opt_short; }

    "b" { opts.set_bFlag(true);           goto opt_short; }
    "d" { opts.set_dFlag(true);           goto opt_short; }
    "g" { opts.set_gFlag(true);           goto opt_short; }
    "i" { opts.set_iFlag(true);           goto opt_short; }
    "s" { opts.set_sFlag(true);           goto opt_short; }
    "T" { opts.set_tags(true);            goto opt_short; }
    "e" { opts.set_encoding(Enc::EBCDIC); goto opt_short; }
    "u" { opts.set_encoding(Enc::UTF32);  goto opt_short; }
    "w" { opts.set_encoding(Enc::UCS2);   goto opt_short; }
    "x" { opts.set_encoding(Enc::UTF16);  goto opt_short; }
    "8" { opts.set_encoding(Enc::UTF8);   goto opt_short; }

    "P" {
        opts.set_posix_syntax(true);
        opts.set_posix_semantics(true);
        goto opt_short;
    }

    "I" end { NEXT_ARG("-I", opt_incpath); }
    "I"     { *argv = YYCURSOR; goto opt_incpath; }

    "o" end { NEXT_ARG("-o, --output", opt_output); }
    "o"     { *argv = YYCURSOR; goto opt_output; }

    "t" end { NEXT_ARG("-t, --type-header", opt_header); }
    "t"     { *argv = YYCURSOR; goto opt_header; }

    "1" { goto opt_short; } // deprecated
*/

opt_long:
/*!re2c
    * { ERROR("bad long option: %s", *argv); }

    "help"                  end { usage ();   return EXIT_OK; }
    "version"               end { version (); return EXIT_OK; }
    "vernum"                end { vernum ();  return EXIT_OK; }

    "start-"? "conditions"  end { globopts.cFlag = true;             goto opt; }
    "emit-dot"              end { globopts.target = TARGET_DOT;      goto opt; }
    "storable-state"        end { globopts.fFlag = true;             goto opt; }
    "flex-syntax"           end { globopts.FFlag = true;             goto opt; }
    "reusable"              end { globopts.rFlag = true;             goto opt; }
    "verbose"               end { globopts.verbose = true;           goto opt; }
    "no-generation-date"    end { globopts.bNoGenerationDate = true; goto opt; }
    "no-version"            end { globopts.version = false;          goto opt; }
    "skeleton"              end { globopts.target = TARGET_SKELETON; goto opt; }

    "bit-vectors"           end { opts.set_bFlag (true);             goto opt; }
    "debug-output"          end { opts.set_dFlag (true);             goto opt; }
    "computed-gotos"        end { opts.set_gFlag (true);             goto opt; }
    "no-debug-info"         end { opts.set_iFlag (true);             goto opt; }
    "nested-ifs"            end { opts.set_sFlag (true);             goto opt; }
    "case-insensitive"      end { opts.set_bCaseInsensitive (true);  goto opt; }
    "case-inverted"         end { opts.set_bCaseInverted (true);     goto opt; }
    "tags"                  end { opts.set_tags (true);              goto opt; }
    "ecb"                   end { opts.set_encoding(Enc::EBCDIC);    goto opt; }
    "unicode"               end { opts.set_encoding(Enc::UTF32);     goto opt; }
    "wide-chars"            end { opts.set_encoding(Enc::UCS2);      goto opt; }
    "utf-16"                end { opts.set_encoding(Enc::UTF16);     goto opt; }
    "utf-8"                 end { opts.set_encoding(Enc::UTF8);      goto opt; }

    "posix-captures" end {
        opts.set_posix_syntax(true);
        opts.set_posix_semantics(true);
        goto opt;
    }

    "output"                end { NEXT_ARG("-o, --output",       opt_output); }
    "type-header"           end { NEXT_ARG("-t, --type-header",  opt_header); }
    "encoding-policy"       end { NEXT_ARG("--encoding-policy",  opt_encoding_policy); }
    "input"                 end { NEXT_ARG("--input",            opt_input); }
    "empty-class"           end { NEXT_ARG("--empty-class",      opt_empty_class); }
    "location-format"       end { NEXT_ARG("--location-format",  opt_location_format); }
    "input-encoding"        end { NEXT_ARG("--input-encoding",   opt_input_encoding); }

    "single-pass"           end { goto opt; } // deprecated

    // internals
    "dfa-minimization"      end { NEXT_ARG("--dfa-minimization", opt_dfa_minimization); }
    "posix-closure"         end { NEXT_ARG("--posix-closure",    opt_posix_closure); }
    "posix-prectable"       end { NEXT_ARG("--posix-prectable",  opt_posix_prectable); }
    "no-lookahead"          end { globopts.lookahead = false;     goto opt; }
    "no-optimize-tags"      end { globopts.optimize_tags = false; goto opt; }
    "eager-skip"            end { globopts.eager_skip = true;     goto opt; }
    "stadfa"                end { globopts.stadfa = true;         goto opt; }

    // debug options
    "dump-nfa"              end { globopts.dump_nfa = true;           goto opt; }
    "dump-dfa-tree"         end { globopts.dump_dfa_tree = true;      goto opt; }
    "dump-dfa-raw"          end { globopts.dump_dfa_raw = true;       goto opt; }
    "dump-dfa-det"          end { globopts.dump_dfa_det = true;       goto opt; }
    "dump-dfa-tagopt"       end { globopts.dump_dfa_tagopt = true;    goto opt; }
    "dump-dfa-min"          end { globopts.dump_dfa_min = true;       goto opt; }
    "dump-adfa"             end { globopts.dump_adfa = true;          goto opt; }
    "dump-cfg"              end { globopts.dump_cfg = true;           goto opt; }
    "dump-interf"           end { globopts.dump_interf = true;        goto opt; }
    "dump-closure-stats"    end { globopts.dump_closure_stats = true; goto opt; }
*/

opt_output:
/*!re2c
    * { ERRARG("-o, --output", "filename", *argv); }
    filename end { opts.set_output_file (*argv); goto opt; }
*/

opt_header:
/*!re2c
    * { ERRARG("-t, --type-header", "filename", *argv); }
    filename end { opts.set_header_file (*argv); goto opt; }
*/

opt_incpath:
/*!re2c
    * { ERRARG("-I", "filename", *argv); }
    filename end { globopts.incpaths.push_back(*argv); goto opt; }
*/

opt_encoding_policy:
/*!re2c
    * { ERRARG("--encoding-policy", "ignore | substitute | fail", *argv); }
    "ignore"     end { opts.set_encoding_policy (Enc::POLICY_IGNORE);     goto opt; }
    "substitute" end { opts.set_encoding_policy (Enc::POLICY_SUBSTITUTE); goto opt; }
    "fail"       end { opts.set_encoding_policy (Enc::POLICY_FAIL);       goto opt; }
*/

opt_input:
/*!re2c
    * { ERRARG("--input", "default | custom", *argv); }
    "default" end { opts.set_input_api(INPUT_DEFAULT); goto opt; }
    "custom"  end { opts.set_input_api(INPUT_CUSTOM);  goto opt; }
*/

opt_empty_class:
/*!re2c
    * { ERRARG("--empty-class", "match-empty | match-none | error", *argv); }
    "match-empty" end { opts.set_empty_class_policy (EMPTY_CLASS_MATCH_EMPTY); goto opt; }
    "match-none"  end { opts.set_empty_class_policy (EMPTY_CLASS_MATCH_NONE);  goto opt; }
    "error"       end { opts.set_empty_class_policy (EMPTY_CLASS_ERROR);       goto opt; }
*/

opt_location_format:
/*!re2c
    * { ERRARG("--location-format", "gnu | msvc", *argv); }
    "gnu"  end { msg.locfmt = LOCFMT_GNU;  goto opt; }
    "msvc" end { msg.locfmt = LOCFMT_MSVC; goto opt; }
*/

opt_input_encoding:
/*!re2c
    * { ERRARG("--input-encoding", "ascii | utf8", *argv); }
    "ascii" end { globopts.input_encoding = Enc::ASCII; goto opt; }
    "utf8"  end { globopts.input_encoding = Enc::UTF8;  goto opt; }
*/

opt_dfa_minimization:
/*!re2c
    * { ERRARG("--dfa-minimization", "table | moore", *argv); }
    "table" end { globopts.dfa_minimization = DFA_MINIMIZATION_TABLE; goto opt; }
    "moore" end { globopts.dfa_minimization = DFA_MINIMIZATION_MOORE; goto opt; }
*/

opt_posix_closure:
/*!re2c
    * { ERRARG("--posix-closure", "gor1 | gtop", *argv); }
    "gor1" end { globopts.posix_closure = POSIX_CLOSURE_GOR1; goto opt; }
    "gtop" end { globopts.posix_closure = POSIX_CLOSURE_GTOP; goto opt; }
*/

opt_posix_prectable:
/*!re2c
    * { ERRARG("--posix-prectable", "naive | complex", *argv); }
    "naive"   end { globopts.posix_prectable = POSIX_PRECTABLE_NAIVE;   goto opt; }
    "complex" end { globopts.posix_prectable = POSIX_PRECTABLE_COMPLEX; goto opt; }
*/

end:
    if (!opts.source_file) {
        error ("no source file");
        return EXIT_FAIL;
    }
    globopts.fix();

    return OK;

#undef NEXT_ARG
#undef ERROR
#undef ERRARG
#undef YYCTYPE
}

} // namespace re2c
