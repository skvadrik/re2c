#include <stddef.h>
#include <algorithm>
#include <string>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/encoding/enc.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/input.h"

namespace re2c {

static inline bool next(char*& arg, char**& argv) {
    arg = *++argv;
    return arg != nullptr;
}

LOCAL_NODISCARD(inline Ret set_source_file(conopt_t& global, const char* source)) {
    if (!global.source_file.empty()) {
        RET_FAIL(error("multiple source files: %s, %s", global.source_file.c_str(), source));
    }
    global.set_source_file(source);
    return Ret::OK;
}

#define NEXT_ARG(option, label) \
    do { if (!next(YYCURSOR, argv)) RET_FAIL(error_arg(option)); goto label; } while(0)

#define ERRARG(opt, exp, arg) \
    RET_FAIL(error("bad argument `%s` to option %s (expected <%s>)", arg, opt, exp))

LOCAL_NODISCARD(Ret parse_opts(Opt& opts, conopt_t& global, char** argv, Msg& msg, Lang* lang)) {
    char* YYCURSOR, *YYMARKER;
    Warn::option_t option;

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = char;

    end = "\x00";
    filename = [^\x00-] [^\x00]*;
*/

opt:
    if (!next (YYCURSOR, argv)) goto end;
/*!local:re2c
    * { RET_FAIL(error("bad option: %s", *argv)); }

    "--" end {
        // the remaining args are non-options, so they must be input files (re2c expects exactly
        // one input file)
        for (char *f; next(f, argv); ) {
            CHECK_RET(set_source_file(global, f));
        }
        goto end;
    }

    "-"      end { CHECK_RET(set_source_file(global, "<stdin>")); goto opt; }
    filename end { CHECK_RET(set_source_file(global, *argv));     goto opt; }

    "-"  { goto opt_short; }
    "--" { goto opt_long; }

    "-W"      end { msg.warn.set_all();       goto opt; }
    "-Werror" end { msg.warn.set_all_error(); goto opt; }
    "-W"          { option = Warn::W;        goto opt_warn; }
    "-Wno-"       { option = Warn::WNO;      goto opt_warn; }
    "-Werror-"    { option = Warn::WERROR;   goto opt_warn; }
    "-Wno-error-" { option = Warn::WNOERROR; goto opt_warn; }
*/

opt_warn: /*!local:re2c
    * { RET_FAIL(error("bad warning: %s", *argv)); }

    "condition-order"        end { msg.warn.set(Warn::CONDITION_ORDER,        option); goto opt; }
    "empty-character-class"  end { msg.warn.set(Warn::EMPTY_CHARACTER_CLASS,  option); goto opt; }
    "match-empty-string"     end { msg.warn.set(Warn::MATCH_EMPTY_STRING,     option); goto opt; }
    "nondeterministic-tags"  end { msg.warn.set(Warn::NONDETERMINISTIC_TAGS,  option); goto opt; }
    "swapped-range"          end { msg.warn.set(Warn::SWAPPED_RANGE,          option); goto opt; }
    "undefined-control-flow" end { msg.warn.set(Warn::UNDEFINED_CONTROL_FLOW, option); goto opt; }
    "unreachable-rules"      end { msg.warn.set(Warn::UNREACHABLE_RULES,      option); goto opt; }
    "useless-escape"         end { msg.warn.set(Warn::USELESS_ESCAPE,         option); goto opt; }
    "sentinel-in-midrule"    end { msg.warn.set(Warn::SENTINEL_IN_MIDRULE,    option); goto opt; }
*/

opt_short: /*!local:re2c
    * { RET_FAIL(error("bad short option: %s", *argv)); }

    end { goto opt; }
    [?h] { return usage(); }
    "v"  { return version(); }
    "V"  { return vernum(); }

    "c" { global.set_start_conditions(true);   goto opt_short; }
    "D" { global.set_target(Target::DOT);      goto opt_short; }
    "f" { global.set_storable_state(true);     goto opt_short; }
    "F" { global.set_flex_syntax(true);        goto opt_short; }
    "i" { global.set_line_dirs(false);         goto opt_short; }
    "S" { global.set_target(Target::SKELETON); goto opt_short; }

    "b" { opts.set_bitmaps(true);         goto opt_short; }
    "d" { opts.set_debug(true);           goto opt_short; }
    "g" { opts.set_computed_gotos(true);  goto opt_short; }
    "s" { opts.set_nested_ifs(true);      goto opt_short; }
    "T" { opts.set_tags(true);            goto opt_short; }

    "e" { opts.set_encoding(Enc::Type::EBCDIC, true); goto opt_short; }
    "u" { opts.set_encoding(Enc::Type::UTF32, true);  goto opt_short; }
    "w" { opts.set_encoding(Enc::Type::UCS2, true);   goto opt_short; }
    "x" { opts.set_encoding(Enc::Type::UTF16, true);  goto opt_short; }
    "8" { opts.set_encoding(Enc::Type::UTF8, true);   goto opt_short; }

    "P" {
        opts.set_captures(true);
        opts.set_captures_posix(true);
        opts.set_captures_array(true);
        goto opt_short;
    }

    "I" end { NEXT_ARG("-I", opt_incpath); }
    "I"     { *argv = YYCURSOR; goto opt_incpath; }

    "o" end { NEXT_ARG("-o, --output", opt_output); }
    "o"     { *argv = YYCURSOR; goto opt_output; }

    "t" end { NEXT_ARG("-t, --type-header", opt_header); }
    "t"     { *argv = YYCURSOR; goto opt_header; }

    // deprecated
    "1" { goto opt_short; }
    "r" { goto opt_short; }
*/

opt_long: /*!local:re2c
    * { RET_FAIL(error("bad long option: %s", *argv)); }

    "help"                  end { return usage(); }
    "version"               end { return version(); }
    "vernum"                end { return vernum(); }

    "start-"? "conditions"  end { global.set_start_conditions(true);   goto opt; }
    "emit-dot"              end { global.set_target(Target::DOT);      goto opt; }
    "storable-state"        end { global.set_storable_state(true);     goto opt; }
    "flex-syntax"           end { global.set_flex_syntax(true);        goto opt; }
    "verbose"               end { global.set_verbose(true);            goto opt; }
    "no-debug-info"         end { global.set_line_dirs(false);         goto opt; }
    "no-generation-date"    end { global.set_date(false);              goto opt; }
    "no-version"            end { global.set_version(false);           goto opt; }
    "skeleton"              end { global.set_target(Target::SKELETON); goto opt; }
    "eager-skip"            end { global.set_eager_skip(true);         goto opt; }
    "goto-label"            end { global.set_code_model(CodeModel::GOTO_LABEL);  goto opt; }
    "loop-switch"           end { global.set_code_model(CodeModel::LOOP_SWITCH); goto opt; }
    "recursive-functions"   end { global.set_code_model(CodeModel::REC_FUNC);    goto opt; }

    "bit-vectors"           end { opts.set_bitmaps(true);            goto opt; }
    "debug-output"          end { opts.set_debug(true);              goto opt; }
    "case-ranges"           end { opts.set_case_ranges(true);        goto opt; }
    "computed-gotos"        end { opts.set_computed_gotos(true);     goto opt; }
    "nested-ifs"            end { opts.set_nested_ifs(true);         goto opt; }
    "case-insensitive"      end { opts.set_case_insensitive(true);   goto opt; }
    "case-inverted"         end { opts.set_case_inverted(true);      goto opt; }
    "tags"                  end { opts.set_tags(true);               goto opt; }
    "no-unsafe"             end { opts.set_unsafe(false);            goto opt; }
    "invert-captures"       end { opts.set_captures_invert(true);    goto opt; }

    "ebcdic" | "ecb"        end { opts.set_encoding(Enc::Type::EBCDIC, true); goto opt; }
    "utf32"  | "unicode"    end { opts.set_encoding(Enc::Type::UTF32, true);  goto opt; }
    "ucs2"   | "wide-chars" end { opts.set_encoding(Enc::Type::UCS2, true);   goto opt; }
    "utf16"  | "utf-16"     end { opts.set_encoding(Enc::Type::UTF16, true);  goto opt; }
    "utf8"   | "utf-8"      end { opts.set_encoding(Enc::Type::UTF8, true);   goto opt; }

    "leftmost-"? "captures" end {
        opts.set_captures(true);
        opts.set_captures_array(true);
        goto opt;
    }
    "posix-captures" end {
        opts.set_captures(true);
        opts.set_captures_posix(true);
        opts.set_captures_array(true);
        goto opt;
    }
    "leftmost-"? "captvars" end {
        opts.set_captures(true);
        opts.set_captures_array(false);
        goto opt;
    }
    "posix-captvars" end {
        opts.set_captures(true);
        opts.set_captures_posix(true);
        opts.set_captures_array(false);
        goto opt;
    }

    "lang"                  end { NEXT_ARG("--lang",             opt_lang); }
    "output"                end { NEXT_ARG("-o, --output",       opt_output); }
    "type-"? "header"       end { NEXT_ARG("-t, --header, --type-header", opt_header); }
    "depfile"               end { NEXT_ARG("--depfile",          opt_depfile); }
    "syntax"                end { NEXT_ARG("--syntax",           opt_syntax); }
    "encoding-policy"       end { NEXT_ARG("--encoding-policy",  opt_encoding_policy); }
    "api" | "input"         end { NEXT_ARG("--api, --input",     opt_input); }
    "empty-class"           end { NEXT_ARG("--empty-class",      opt_empty_class); }
    "location-format"       end { NEXT_ARG("--location-format",  opt_location_format); }
    "input-encoding"        end { NEXT_ARG("--input-encoding",   opt_input_encoding); }

     // deprecated
    "single-pass"           end { goto opt; }
    "reusable"              end { goto opt; }

    // internals
    "dfa-minimization"      end { NEXT_ARG("--dfa-minimization", opt_minimization); }
    "posix-prectable"       end { NEXT_ARG("--posix-prectable",  opt_posix_prectable); }
    "fixed-tags"            end { NEXT_ARG("--fixed-tags",       opt_fixed_tags); }
    "no-optimize-tags"      end { global.set_optimize_tags(false); goto opt; }

    // removed
    "no-lookahead"          end { RET_FAIL(error("TDFA(0) algorithm was deprecated and removed")); }
    "posix-closure"         end { RET_FAIL(error("option --posix-closure was removed")); }
    "stadfa"                end { RET_FAIL(error("staDFA algorithm was deprecated and removed")); }

    // debug options
    "dump-nfa"              end { global.set_dump_nfa(true);           goto opt; }
    "dump-dfa-tree"         end { global.set_dump_dfa_tree(true);      goto opt; }
    "dump-dfa-raw"          end { global.set_dump_dfa_raw(true);       goto opt; }
    "dump-dfa-det"          end { global.set_dump_dfa_det(true);       goto opt; }
    "dump-dfa-tagopt"       end { global.set_dump_dfa_tagopt(true);    goto opt; }
    "dump-dfa-min"          end { global.set_dump_dfa_min(true);       goto opt; }
    "dump-adfa"             end { global.set_dump_adfa(true);          goto opt; }
    "dump-cfg"              end { global.set_dump_cfg(true);           goto opt; }
    "dump-interf"           end { global.set_dump_interf(true);        goto opt; }
    "dump-closure-stats"    end { global.set_dump_closure_stats(true); goto opt; }
*/

opt_lang: /*!local:re2c
    * {
        ERRARG("--lang",
            "c | d | go | haskell | java | js | ocaml | python | rust | v | zig | none",
            *argv);
    }
    "c"       end { *lang = Lang::C;       goto opt; }
    "d"       end { *lang = Lang::D;       goto opt; }
    "go"      end { *lang = Lang::GO;      goto opt; }
    "haskell" end { *lang = Lang::HASKELL; goto opt; }
    "java"    end { *lang = Lang::JAVA;    goto opt; }
    "js"      end { *lang = Lang::JS;      goto opt; }
    "ocaml"   end { *lang = Lang::OCAML;   goto opt; }
    "python"  end { *lang = Lang::PYTHON;  goto opt; }
    "rust"    end { *lang = Lang::RUST;    goto opt; }
    "v"       end { *lang = Lang::V;       goto opt; }
    "zig"     end { *lang = Lang::ZIG;     goto opt; }
    "none"    end { *lang = Lang::NONE;    goto opt; }
*/

opt_output: /*!local:re2c
    * { ERRARG("-o, --output", "filename", *argv); }
    filename end { global.set_output_file(*argv); goto opt; }
*/

opt_header: /*!local:re2c
    * { ERRARG("-t, --header, --type-header", "filename", *argv); }
    filename end { opts.set_header_file(*argv); goto opt; }
*/

opt_depfile: /*!local:re2c
    * { ERRARG("--depfile", "filename", *argv); }
    filename end { global.set_dep_file(*argv); goto opt; }
*/

opt_syntax: /*!local:re2c
    * { ERRARG("--syntax", "filename", *argv); }
    filename end { global.set_syntax_file(*argv); goto opt; }
*/

opt_incpath: /*!local:re2c
    * { ERRARG("-I", "filename", *argv); }
    filename end
        { const_cast<std::vector<std::string>&>(global.include_paths).push_back(*argv); goto opt; }
*/

opt_encoding_policy: /*!local:re2c
    * { ERRARG("--encoding-policy", "ignore | substitute | fail", *argv); }
    "ignore"     end { opts.set_encoding_policy(Enc::Policy::IGNORE);     goto opt; }
    "substitute" end { opts.set_encoding_policy(Enc::Policy::SUBSTITUTE); goto opt; }
    "fail"       end { opts.set_encoding_policy(Enc::Policy::FAIL);       goto opt; }
*/

opt_input: /*!local:re2c
    * { ERRARG("--api, --input", "simple | generic | record", *argv); }
    ("simple" | "default") end { opts.set_api(Api::SIMPLE);  goto opt; }
    ("generic" | "custom") end { opts.set_api(Api::GENERIC); goto opt; }
    "record"               end { opts.set_api(Api::RECORD);  goto opt; }
*/

opt_empty_class: /*!local:re2c
    * { ERRARG("--empty-class", "match-empty | match-none | error", *argv); }
    "match-empty" end { opts.set_empty_class(EmptyClass::MATCH_EMPTY); goto opt; }
    "match-none"  end { opts.set_empty_class(EmptyClass::MATCH_NONE);  goto opt; }
    "error"       end { opts.set_empty_class(EmptyClass::ERROR);       goto opt; }
*/

opt_location_format: /*!local:re2c
    * { ERRARG("--location-format", "gnu | msvc", *argv); }
    "gnu"  end { msg.locfmt = LOCFMT_GNU;  goto opt; }
    "msvc" end { msg.locfmt = LOCFMT_MSVC; goto opt; }
*/

opt_input_encoding: /*!local:re2c
    * { ERRARG("--input-encoding", "ascii | utf8 ", *argv); }
    "ascii" end { global.set_input_encoding(Enc::Type::ASCII); goto opt; }
    "utf8"  end { global.set_input_encoding(Enc::Type::UTF8);  goto opt; }
*/

opt_minimization: /*!local:re2c
    * { ERRARG("--dfa-minimization", "table | moore", *argv); }
    "table" end { global.set_minimization(Minimization::TABLE); goto opt; }
    "moore" end { global.set_minimization(Minimization::MOORE); goto opt; }
*/

opt_posix_prectable: /*!local:re2c
    * { ERRARG("--posix-prectable", "naive | complex", *argv); }
    "naive"   end { global.set_posix_prectable(PosixPrectable::NAIVE);   goto opt; }
    "complex" end { global.set_posix_prectable(PosixPrectable::COMPLEX); goto opt; }
*/

opt_fixed_tags: /*!local:re2c
    * { ERRARG("--fixed-tags", "none | toplevel | all", *argv); }
    "none"     end { global.set_fixed_tags(FixedTags::NONE);     goto opt; }
    "toplevel" end { global.set_fixed_tags(FixedTags::TOPLEVEL); goto opt; }
    "all"      end { global.set_fixed_tags(FixedTags::ALL);      goto opt; }
*/

end:
    if (global.source_file.empty()) {
        RET_FAIL(error("no source file"));
    }

    // Append directory separator '/' to all include paths that don't have it.
    for (std::string& p : const_cast<std::vector<std::string>&>(global.include_paths)) {
        const char c = p.empty() ? 0 : *p.rbegin();
        if (c != '/' && c != '\\') {
            p.push_back('/');
        }
    }

    return Ret::OK;
}

Ret Opt::parse(char** argv, Input& input, Lang lang) {
    CHECK_RET(parse_opts(*this, const_cast<conopt_t&>(glob), argv, msg, &lang));

    // Load syntax file (it must have file index 0).
    CHECK_RET(input.load_syntax_config(*this, lang));

    // Set option defaults.
    CHECK_RET(fix_global_and_defaults());

    return Ret::OK;
}

#undef NEXT_ARG
#undef ERRARG

} // namespace re2c
