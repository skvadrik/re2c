#include "src/code/input_api.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/re/empty_class_policy.h"
#include "src/re/encoding/enc.h"

namespace re2c
{

static inline bool next (char * & arg, char ** & argv)
{
    arg = *++argv;
    return arg != NULL;
}

parse_opts_t parse_opts(char **argv, conopt_t &globopts, Opt &opts, Warn &warn)
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
    "condition-order"          end { warn.set (Warn::CONDITION_ORDER,          option); goto opt; }
    "empty-character-class"    end { warn.set (Warn::EMPTY_CHARACTER_CLASS,    option); goto opt; }
    "match-empty-string"       end { warn.set (Warn::MATCH_EMPTY_STRING,       option); goto opt; }
    "nondeterministic-tags"    end { warn.set (Warn::NONDETERMINISTIC_TAGS,    option); goto opt; }
    "swapped-range"            end { warn.set (Warn::SWAPPED_RANGE,            option); goto opt; }
    "undefined-control-flow"   end { warn.set (Warn::UNDEFINED_CONTROL_FLOW,   option); goto opt; }
    "unreachable-rules"        end { warn.set (Warn::UNREACHABLE_RULES,        option); goto opt; }
    "useless-escape"           end { warn.set (Warn::USELESS_ESCAPE,           option); goto opt; }
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
    "P" { opts.set_posix_captures(true);  goto opt_short; }
    "e" { opts.set_encoding(Enc::EBCDIC); goto opt_short; }
    "u" { opts.set_encoding(Enc::UTF32);  goto opt_short; }
    "w" { opts.set_encoding(Enc::UCS2);   goto opt_short; }
    "x" { opts.set_encoding(Enc::UTF16);  goto opt_short; }
    "8" { opts.set_encoding(Enc::UTF8);   goto opt_short; }
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
    "help"                  end { usage ();   return EXIT_OK; }
    "version"               end { version (); return EXIT_OK; }
    "vernum"                end { vernum ();  return EXIT_OK; }

    "start-"? "conditions"  end { globopts.cFlag = true;             goto opt; }
    "emit-dot"              end { globopts.target = TARGET_DOT;      goto opt; }
    "storable-state"        end { globopts.fFlag = true;             goto opt; }
    "flex-syntax"           end { globopts.FFlag = true;             goto opt; }
    "reusable"              end { globopts.rFlag = true;             goto opt; }
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
    "posix-captures"        end { opts.set_posix_captures(true);     goto opt; }
    "no-lookahead"          end { opts.set_lookahead(false);         goto opt; }
    "no-optimize-tags"      end { opts.set_optimize_tags(false);     goto opt; }
    "eager-skip"            end { opts.set_eager_skip(true);         goto opt; }
    "ecb"                   end { opts.set_encoding(Enc::EBCDIC);    goto opt; }
    "unicode"               end { opts.set_encoding(Enc::UTF32);     goto opt; }
    "wide-chars"            end { opts.set_encoding(Enc::UCS2);      goto opt; }
    "utf-16"                end { opts.set_encoding(Enc::UTF16);     goto opt; }
    "utf-8"                 end { opts.set_encoding(Enc::UTF8);      goto opt; }
    "output"                end { if (!next (YYCURSOR, argv)) { error_arg ("-o, --output"); return EXIT_FAIL; } goto opt_output; }
    "type-header"           end { if (!next (YYCURSOR, argv)) { error_arg ("-t, --type-header"); return EXIT_FAIL; } goto opt_header; }
    "encoding-policy"       end { goto opt_encoding_policy; }
    "input"                 end { goto opt_input; }
    "empty-class"           end { goto opt_empty_class; }
    "dfa-minimization"      end { goto opt_dfa_minimization; }
    "single-pass"           end { goto opt; } // deprecated

    "dump-nfa"              end { globopts.dump_nfa = true;        goto opt; }
    "dump-dfa-raw"          end { globopts.dump_dfa_raw = true;    goto opt; }
    "dump-dfa-det"          end { globopts.dump_dfa_det = true;    goto opt; }
    "dump-dfa-tagopt"       end { globopts.dump_dfa_tagopt = true; goto opt; }
    "dump-dfa-min"          end { globopts.dump_dfa_min = true;    goto opt; }
    "dump-adfa"             end { globopts.dump_adfa = true;       goto opt; }
*/

opt_output:
/*!re2c
    *
    {
        error ("bad argument to option -o, --output: %s", *argv);
        return EXIT_FAIL;
    }
    filename end { globopts.output_file = *argv; goto opt; }
*/

opt_header:
/*!re2c
    *
    {
        error ("bad argument to option -t, --type-header: %s", *argv);
        return EXIT_FAIL;
    }
    filename end { globopts.header_file = *argv; goto opt; }
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
    "ignore"     end { opts.set_encoding_policy (Enc::POLICY_IGNORE);     goto opt; }
    "substitute" end { opts.set_encoding_policy (Enc::POLICY_SUBSTITUTE); goto opt; }
    "fail"       end { opts.set_encoding_policy (Enc::POLICY_FAIL);       goto opt; }
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
    "default" end { opts.set_input_api(INPUT_DEFAULT); goto opt; }
    "custom"  end { opts.set_input_api(INPUT_CUSTOM);  goto opt; }
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
    "match-empty" end { opts.set_empty_class_policy (EMPTY_CLASS_MATCH_EMPTY); goto opt; }
    "match-none"  end { opts.set_empty_class_policy (EMPTY_CLASS_MATCH_NONE);  goto opt; }
    "error"       end { opts.set_empty_class_policy (EMPTY_CLASS_ERROR);       goto opt; }
*/

opt_dfa_minimization:
    if (!next (YYCURSOR, argv))
    {
        error_arg ("--minimization");
        return EXIT_FAIL;
    }
/*!re2c
    *
    {
        error ("bad argument to option --dfa-minimization (expected: table | moore): %s", *argv);
        return EXIT_FAIL;
    }
    "table" end { opts.set_dfa_minimization (DFA_MINIMIZATION_TABLE); goto opt; }
    "moore" end { opts.set_dfa_minimization (DFA_MINIMIZATION_MOORE); goto opt; }
*/

end:
    if (!opts.source_file)
    {
        error ("no source file");
        return EXIT_FAIL;
    }
    globopts.fix();

    return OK;

#undef YYCTYPE
}

} // namespace re2c
