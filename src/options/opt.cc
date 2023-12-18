#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/options/syntax.h"
#include "src/parse/input.h"
#include "src/util/string_utils.h"

namespace re2c {

// This function should only change global options.
LOCAL_NODISCARD(Ret fix_conopt(conopt_t& glob, Stx& stx)) {
    if (glob.target == Target::DOT) {
        glob.line_dirs = false;
    } else if (glob.target == Target::SKELETON) {
        glob.storable_state = false;
        glob.line_dirs = false;
    }

    if (!stx.have_conf("code:line_info")) glob.line_dirs = false;

    if (strcmp(stx.list_conf_head("jump_model"), "loop_switch") == 0) glob.loop_switch = true;

    // append directory separator '/' to all paths that do not have it
    for (std::string& p : glob.include_paths) {
        const char c = p.empty() ? 0 : *p.rbegin();
        if (c != '/' && c != '\\') {
            p.push_back('/');
        }
    }

    if (glob.loop_switch) {
        // for loop-switch enable eager-skip always (not only in cases when YYFILL labels are used)
        // to avoid special handling of initial state when there are transitions into it.
        glob.eager_skip = true;
    }

    if (!glob.dep_file.empty() && glob.output_file.empty()) {
        RET_FAIL(error("cannot generate dep file, output file not specified"));
    }

    if (glob.target == Target::SKELETON && !stx.list_conf_find("target", "skeleton")) {
        RET_FAIL(error("skeleton is not supported for this backend"));
    }

    return Ret::OK;
}

// This should only change mutable option defaults (based on the global options / syntax file).
LOCAL_NODISCARD(Ret fix_mutopt_defaults(mutopt_t& defaults, Stx& stx)) {
    defaults.api = strcmp(stx.list_conf_head("api"), "default") == 0 ? Api::DEFAULT : Api::CUSTOM;
    defaults.api_style = strcmp(stx.list_conf_head("api_style"), "functions") == 0
            ? ApiStyle::FUNCTIONS : ApiStyle::FREEFORM;

    if (strcmp(stx.eval_word_conf("constants"), "upper_case") == 0) {
        defaults.cond_enum_prefix = "YYC_";
    }

    CHECK_RET(stx.eval_str_conf("code:loop_label", defaults.label_loop));

    const char* semi = stx.eval_bool_conf("semicolons") ? ";" : "";
    defaults.cond_goto = "goto " + defaults.api_sigil + semi;

    return Ret::OK;
}

// This function should only change real mutable options (based on the global options, default
// mutable options and default flags). User-defined options are intentionally not passed to prevent
// accidental change, and default flags are passed as read-only.
LOCAL_NODISCARD(Ret fix_mutopt(const Stx& stx,
                               const conopt_t& glob,
                               const mutopt_t& defaults,
                               const mutdef_t& is_default,
                               mutopt_t& real)) {
    // For skeleton target interface options must have default values (because skeleton programs
    // assume certain interface). For DOT target most of the options are unused.
    if (glob.target != Target::CODE) {
        // output files
        real.header_file = "";
        // default environment-sensitive formatting
        real.cond_div = defaults.cond_div;
        real.cond_div_param = defaults.cond_div_param;
        real.indent_top = defaults.indent_top;
        real.indent_str = defaults.indent_str;
        // default environment bindings
        real.api = defaults.api;
        real.api_style = defaults.api_style;
        real.api_sigil = defaults.api_sigil;
        real.api_char_type = defaults.api_char_type;
        real.api_cursor = defaults.api_cursor;
        real.api_marker = defaults.api_marker;
        real.api_ctxmarker = defaults.api_ctxmarker;
        real.api_limit = defaults.api_limit;
        real.api_peek = defaults.api_peek;
        real.api_skip = defaults.api_skip;
        real.api_backup = defaults.api_backup;
        real.api_backup_ctx = defaults.api_backup_ctx;
        real.api_restore = defaults.api_restore;
        real.api_restore_ctx = defaults.api_restore_ctx;
        real.api_restore_tag = defaults.api_restore_tag;
        real.api_stag_neg = defaults.api_stag_neg;
        real.api_stag_pos = defaults.api_stag_pos;
        real.api_mtag_neg = defaults.api_mtag_neg;
        real.api_mtag_pos = defaults.api_mtag_pos;
        real.api_shift = defaults.api_shift;
        real.api_shift_stag = defaults.api_shift_stag;
        real.api_shift_mtag = defaults.api_shift_mtag;
        real.api_fill = defaults.api_fill;
        real.api_less_than = defaults.api_less_than;
        real.api_cond_type = defaults.api_cond_type;
        real.api_cond_get = defaults.api_cond_get;
        real.api_cond_set = defaults.api_cond_set;
        real.api_state_get = defaults.api_state_get;
        real.api_state_set = defaults.api_state_set;
        real.api_debug = defaults.api_debug;
        real.var_accept = defaults.var_accept;
        real.var_bitmaps = defaults.var_bitmaps;
        real.var_char = defaults.var_char;
        real.var_cond_table = defaults.var_cond_table;
        real.var_cgoto_table = defaults.var_cgoto_table;
        real.var_state = defaults.var_state;
        real.fill_enable = defaults.fill_enable;
        real.fill_check = defaults.fill_check;
        real.fill_param = defaults.fill_param;
        real.fill_param_enable = defaults.fill_param_enable;
        real.fill_naked = defaults.fill_naked;
        real.cond_get_naked = defaults.cond_get_naked;
        real.cond_set_param = defaults.cond_set_param;
        real.cond_set_naked = defaults.cond_set_naked;
        real.cond_label_prefix = defaults.cond_label_prefix;
        real.cond_enum_prefix = defaults.cond_enum_prefix;
        real.cond_goto = defaults.cond_goto;
        real.cond_goto_param = defaults.cond_goto_param;
        real.state_abort = defaults.state_abort;
        real.state_next = defaults.state_next;
        real.state_get_naked = defaults.state_get_naked;
        real.state_set_param = defaults.state_set_param;
        real.state_set_naked = defaults.state_set_naked;
        real.tags_prefix = defaults.tags_prefix;
        real.tags_expression = defaults.tags_expression;
        real.char_emit = defaults.char_emit;
        real.char_conv = defaults.char_conv;
        real.label_loop = defaults.label_loop;
        real.label_fill = defaults.label_fill;
        real.label_next = defaults.label_next;
        real.label_prefix = defaults.label_prefix;
        real.label_start = defaults.label_start;
        real.label_start_force = defaults.label_start_force;
        real.debug = defaults.debug;
    }

    // respect hierarchy
    if (!glob.start_conditions) {
        real.api_cond_type = defaults.api_cond_type;
        real.api_cond_get = defaults.api_cond_get;
        real.api_cond_set = defaults.api_cond_set;
        real.var_cond_table = defaults.var_cond_table;
        real.cond_get_naked = defaults.cond_get_naked;
        real.cond_set_param = defaults.cond_set_param;
        real.cond_set_naked = defaults.cond_set_naked;
        real.cond_label_prefix = defaults.cond_label_prefix;
        real.cond_enum_prefix = defaults.cond_enum_prefix;
        real.cond_div = defaults.cond_div;
        real.cond_div_param = defaults.cond_div_param;
        real.cond_goto = defaults.cond_goto;
        real.cond_goto_param = defaults.cond_goto_param;
    }
    if (!glob.storable_state) {
        real.api_state_get = defaults.api_state_get;
        real.api_state_set = defaults.api_state_set;
        real.var_accept = defaults.var_accept;
        real.state_next = defaults.state_next;
        real.state_get_naked = defaults.state_get_naked;
        real.state_set_param = defaults.state_set_param;
        real.state_set_naked = defaults.state_set_naked;
        real.label_fill = defaults.label_fill;
        real.label_next = defaults.label_next;
    }
    if (!glob.storable_state && !glob.loop_switch) {
        real.state_abort = defaults.state_abort;
    }
    if (real.tags_posix_semantics) {
        real.tags_posix_syntax = true;
    }
    if (real.tags_posix_syntax) {
        real.tags = true;
    }
    if (!real.tags) {
        real.tags_prefix = defaults.tags_prefix;
        real.tags_expression = defaults.tags_expression;
    }
    if (!real.bitmaps) {
        real.bitmaps_hex = defaults.bitmaps_hex;
        real.var_bitmaps = defaults.var_bitmaps;
    }
    if (!real.cgoto) {
        real.cgoto_threshold = defaults.cgoto_threshold;
        real.var_cgoto_table = defaults.var_cgoto_table;
    }
    if (real.api != Api::DEFAULT) {
        real.api_cursor = defaults.api_cursor;
        real.api_marker = defaults.api_marker;
        real.api_ctxmarker = defaults.api_ctxmarker;
        real.api_limit = defaults.api_limit;
    }
    if (real.api != Api::CUSTOM) {
        real.api_peek = defaults.api_peek;
        real.api_skip = defaults.api_skip;
        real.api_backup = defaults.api_backup;
        real.api_backup_ctx = defaults.api_backup_ctx;
        real.api_restore = defaults.api_restore;
        real.api_restore_ctx = defaults.api_restore_ctx;
        real.api_restore_tag = defaults.api_restore_tag;
        real.api_stag_neg = defaults.api_stag_neg;
        real.api_stag_pos = defaults.api_stag_pos;
        real.api_shift = defaults.api_shift;
        real.api_shift_stag = defaults.api_shift_stag;
        // for mtags there are no sensible defaults
    }
    if (!real.debug) {
        real.api_debug = defaults.api_debug;
    }
    if (!real.fill_enable) {
        real.api_fill = defaults.api_fill;
        real.fill_check = defaults.fill_check;
        real.fill_param = defaults.fill_param;
        real.fill_param_enable = defaults.fill_param_enable;
        real.fill_naked = defaults.fill_naked;
    }

    // set implied options
    if (glob.target == Target::SKELETON) {
        real.api = Api::CUSTOM;
        real.indent_str = "    ";
        real.indent_top = 0;
    }
    if (real.bitmaps || real.encoding.multibyte_cunit()) {
        real.nested_ifs = true;
    }
    if (real.cgoto) {
        real.bitmaps = true;
        real.nested_ifs = true;
    }
    if (real.case_insensitive) {
        real.case_inverted = defaults.case_inverted;
    }
    // individual "naked" options, unless explicitly set, inherit "api:style"
    if (is_default.fill_naked)      real.fill_naked      = real.api_style == ApiStyle::FREEFORM;
    if (is_default.cond_get_naked)  real.cond_get_naked  = real.api_style == ApiStyle::FREEFORM;
    if (is_default.cond_set_naked)  real.cond_set_naked  = real.api_style == ApiStyle::FREEFORM;
    if (is_default.state_get_naked) real.state_get_naked = real.api_style == ApiStyle::FREEFORM;
    if (is_default.state_set_naked) real.state_set_naked = real.api_style == ApiStyle::FREEFORM;
    // individual template options, unless explicitly set, inherit "api:sigil"
    if (is_default.fill_param)       real.fill_param       = real.api_sigil;
    if (is_default.cond_set_param)   real.cond_set_param   = real.api_sigil;
    if (is_default.cond_div_param)   real.cond_div_param   = real.api_sigil;
    if (is_default.cond_goto_param)  real.cond_goto_param  = real.api_sigil;
    if (is_default.state_set_param)  real.state_set_param  = real.api_sigil;
    if (is_default.tags_expression)  real.tags_expression  = real.api_sigil;
    if (is_default.cond_goto) {
        real.cond_goto = defaults.cond_goto;
        strrreplace(real.cond_goto, defaults.cond_goto_param, real.cond_goto_param);
    }
    // "startlabel" configuration exists in two variants: string and boolean, and the string one
    // overrides the boolean one
    if (!is_default.label_start) {
        real.label_start_force = defaults.label_start_force;
    }
    if (real.fill_naked) {
        real.fill_param_enable = false;
    }
    if (glob.loop_switch) {
        // With --loop-switch there is no `goto`.
        real.var_cond_table = defaults.var_cond_table;
        real.cond_div = defaults.cond_div;
        real.cond_div_param = defaults.cond_div_param;
        real.cond_goto = defaults.cond_goto;
        real.cond_goto_param = defaults.cond_goto_param;
    }

    // errors
    if (real.api == Api::DEFAULT && !stx.list_conf_find("api", "default")) {
        RET_FAIL(error("default API is not supported for this backend"));
    }
    if (real.cgoto && strcmp(stx.eval_word_conf("computed_goto"), "unsupported") == 0) {
        RET_FAIL(error("-g, --computed-gotos option is not supported for this backend"));
    }
    if (real.case_ranges && strcmp(stx.eval_word_conf("case_ranges"), "unsupported") == 0) {
        RET_FAIL(error("--case-ranges option is not supported for this backend"));
    }
    // TODO: check bitmaps and other optional features
    if (real.fill_eof != NOEOF) {
        if (real.bitmaps || real.cgoto) {
            RET_FAIL(error("configuration 're2c:eof' cannot be used with options -b, --bit-vectors "
                           "and -g, --computed gotos"));
        }
        if (real.fill_eof >= real.encoding.cunit_count()) {
            RET_FAIL(error("EOF exceeds maximum code unit value for given encoding"));
        }
        if (!real.fill_check) {
            RET_FAIL(error("YYFILL check is necessary if EOF rule is used"));
        }
    }
    if (real.fill_sentinel != NOEOF) {
        if (real.fill_sentinel >= real.encoding.cunit_count()) {
            RET_FAIL(error("sentinel exceeds maximum code unit value for given encoding"));
        }
        if (real.fill_enable || real.fill_eof != NOEOF) {
            RET_FAIL(error("re2c:sentinel configuration is not needed in the presence of bounds "
                           "checking or EOF rule"));
        }
    }
    if (glob.storable_state && !real.fill_enable) {
        // -f, --storable-state option should not be used if YYFILL is disabled, because without
        // YYFILL the interrupt points do not necessarily correspond to storable state labels (with
        // generic API interrupts can happen on any API invocation). This may cause subtle bugs when
        // the lexer is resumed from the wrong program point.
        RET_FAIL(error("storable state requires YYFILL to be enabled"));
    }
    if (glob.loop_switch) {
        if (real.cgoto) {
            RET_FAIL(error("cannot combine loop switch and computed gotos"));
        }
        if (real.bitmaps) {
            // TODO: generate bitmaps before the joined loop/switch for all conditions.
            RET_FAIL(error("bitmaps with loop switch are not supported"));
        }
    }

    return Ret::OK;
}

Opt::Opt(OutAllocator& alc, Msg& msg)
    : stx(alc),
      glob(stx),
      symtab(),
      msg(msg),
      defaults(),
      is_default(),
      user(),
      real(),
      diverge(true) {}

Ret Opt::fix_global_and_defaults() {
    // Allow to modify only the global options.
    CHECK_RET(fix_conopt(const_cast<conopt_t&>(glob), stx));

    // Allow to modify only the mutable option defaults (based on the global options / syntax file).
    CHECK_RET(fix_mutopt_defaults(const_cast<mutopt_t&>(defaults), stx));

    // Apply new defaults to all mutable options except those that have been explicitly defined by
    // the user.
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    if (is_default.name) user.name = defaults.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    diverge = true;

    return Ret::OK;
}

Ret Opt::sync() {
    if (!diverge) return Ret::OK;

    // Copy user-defined options to real options.
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    real.name = user.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    // Fix the real mutable options (based on the global options, mutable option defaults and
    // default flags), but do not change user-defined options or default flags.
    CHECK_RET(fix_mutopt(stx, glob, defaults, is_default, real));

    diverge = false;

    return Ret::OK;
}

Ret Opt::snapshot(const opt_t** opts) {
    CHECK_RET(sync());
    *opts = new opt_t(stx, glob, real, is_default, symtab);
    return Ret::OK;
}

Ret Opt::restore(const opt_t* opts) {
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    user.name = opts->name; \
    is_default.name = opts->is_default_##name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    symtab = opts->symtab;

    diverge = true;
    return sync();
}

Ret Opt::merge(const opt_t* opts, Input& input) {
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    if (!opts->is_default_##name) { \
        user.name = opts->name; \
        is_default.name = false; \
    }
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    CHECK_RET(merge_symtab(symtab, opts->symtab, input));

    diverge = true;
    return sync();
}

#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
void Opt::set_##name(const type &arg) \
{ \
    user.name = arg; \
    is_default.name = false; \
    diverge = true; \
} \
void Opt::reset_##name() \
{ \
    user.name = defaults.name; \
    is_default.name = true; \
    diverge = true; \
}
RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

void Opt::set_encoding(Enc::Type type, bool on) {
    if (on) {
        user.encoding.set(type);
    } else {
        user.encoding.unset(type);
    }
    is_default.encoding = false;
    diverge = true;
}

void Opt::set_encoding_policy(Enc::Policy p) {
    user.encoding.set_policy(p);
    is_default.encoding = false;
    diverge = true;
}

void Opt::reset_group_label_start() {
    reset_label_start();
    reset_label_start_force();
    diverge = true;
}

} // namespace re2c
