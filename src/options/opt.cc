#include "src/codegen/output.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/input.h"
#include "src/util/string_utils.h"

namespace re2c {

static const char* code_model_name(CodeModel model) {
    switch (model) {
        case CodeModel::GOTO_LABEL: return "goto-label";
        case CodeModel::LOOP_SWITCH: return "loop-switch";
        case CodeModel::REC_FUNC: return "recursive-functions";
    }
    UNREACHABLE();
    return nullptr;
}

// This function should only change global options.
LOCAL_NODISCARD(Ret fix_conopt(conopt_t& glob)) {
    if (glob.target == Target::DOT) {
        glob.set_line_dirs(false);
    } else if (glob.target == Target::SKELETON) {
        glob.set_storable_state(false);
        glob.set_line_dirs(false);
    }

    if (!glob.dep_file.empty() && glob.output_file.empty()) {
        RET_FAIL(error("cannot generate dep file, output file not specified"));
    }

    // Check that the chosen code model is supported for the given backend.
    if (!glob.supported_code_models_contains(code_model_name(glob.code_model))) {
        RET_FAIL(error("code model is not supported for this backend"));
    }

    if (glob.code_model != CodeModel::GOTO_LABEL) {
        // In loop/switch or rec/func mode enable eager-skip always (not only in cases when YYFILL
        // labels are used) to avoid special handling of initial state when there are transitions
        // into it.
        glob.set_eager_skip(true);
    }

    if (glob.target == Target::SKELETON) {
        if (!glob.supported_targets_contains("skeleton")) {
            RET_FAIL(error("skeleton is not supported for this backend"));
        } else if (glob.code_model == CodeModel::REC_FUNC) {
            RET_FAIL(error("skeleton is not supported for --recursive-functions model"));
        }
    }

    return Ret::OK;
}

// This function should only change real mutable options (based on the global options, default
// mutable options and default flags). User-defined options are intentionally not passed to prevent
// accidental change, and default flags are passed as read-only.
LOCAL_NODISCARD(Ret fix_mutopt(
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
        real.api_input = defaults.api_input;
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
        real.api_stag_copy = defaults.api_stag_copy;
        real.api_mtag_copy = defaults.api_mtag_copy;
        real.api_shift = defaults.api_shift;
        real.api_stag_shift = defaults.api_stag_shift;
        real.api_mtag_shift = defaults.api_mtag_shift;
        real.api_fill = defaults.api_fill;
        real.api_less_than = defaults.api_less_than;
        real.api_cond_type = defaults.api_cond_type;
        real.api_cond_get = defaults.api_cond_get;
        real.api_cond_set = defaults.api_cond_set;
        real.api_state_get = defaults.api_state_get;
        real.api_state_set = defaults.api_state_set;
        real.api_accept_get = defaults.api_accept_get;
        real.api_accept_set = defaults.api_accept_set;
        real.api_maxfill = defaults.api_maxfill;
        real.api_maxnmatch = defaults.api_maxnmatch;
        real.api_debug = defaults.api_debug;
        real.var_accept = defaults.var_accept;
        real.var_bitmaps = defaults.var_bitmaps;
        real.var_char = defaults.var_char;
        real.var_cond = defaults.var_cond;
        real.var_cond_table = defaults.var_cond_table;
        real.var_computed_gotos_table = defaults.var_computed_gotos_table;
        real.var_fill = defaults.var_fill;
        real.var_state = defaults.var_state;
        real.var_nmatch = defaults.var_nmatch;
        real.var_pmatch = defaults.var_pmatch;
        real.var_record = defaults.var_record;
        real.fill_enable = defaults.fill_enable;
        real.fill_check = defaults.fill_check;
        real.fill_param = defaults.fill_param;
        real.fill_param_enable = defaults.fill_param_enable;
        real.fill_naked = defaults.fill_naked;
        real.cond_abort = defaults.cond_abort;
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
        real.tags_negative = defaults.tags_negative;
        real.char_emit = defaults.char_emit;
        real.char_conv = defaults.char_conv;
        real.char_literals = defaults.char_literals;
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
        real.var_cond = defaults.var_cond;
        real.var_cond_table = defaults.var_cond_table;
        real.cond_abort = defaults.cond_abort;
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
        real.state_next = defaults.state_next;
        real.state_get_naked = defaults.state_get_naked;
        real.state_set_param = defaults.state_set_param;
        real.state_set_naked = defaults.state_set_naked;
        real.label_fill = defaults.label_fill;
        real.label_next = defaults.label_next;
    }
    if (!glob.storable_state && glob.code_model == CodeModel::GOTO_LABEL) {
        real.state_abort = defaults.state_abort;
    }
    if (real.captures) {
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
    if (!real.computed_gotos) {
        real.computed_gotos_threshold = defaults.computed_gotos_threshold;
        real.var_computed_gotos_table = defaults.var_computed_gotos_table;
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
        real.var_fill = defaults.var_fill;
    }

    // set implied options
    if (glob.target == Target::SKELETON) {
        real.api = Api::GENERIC;
        real.indent_str = "    ";
        real.indent_top = 0;
    }
    if (real.api == Api::RECORD && is_default.api_style) {
        real.api_style = ApiStyle::FREEFORM;
    }
    if (real.bitmaps || real.encoding.multibyte_cunit()) {
        real.nested_ifs = true;
    }
    if (real.computed_gotos) {
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
    if (!is_default.api_sigil) {
        if (is_default.fill_param)       real.fill_param      = real.api_sigil;
        if (is_default.cond_set_param)   real.cond_set_param  = real.api_sigil;
        if (is_default.cond_div_param)   real.cond_div_param  = real.api_sigil;
        if (is_default.cond_goto_param)  real.cond_goto_param = real.api_sigil;
        if (is_default.state_set_param)  real.state_set_param = real.api_sigil;
    }
    // "startlabel" configuration exists in two variants: string and boolean, and the string one
    // overrides the boolean one
    if (!is_default.label_start) {
        real.label_start_force = defaults.label_start_force;
    }
    if (real.fill_naked) {
        real.fill_param_enable = false;
    }
    if (glob.code_model != CodeModel::GOTO_LABEL) {
        // In code models other than goto/label there is no `goto`.
        real.var_cond_table = defaults.var_cond_table;
        real.cond_div = defaults.cond_div;
        real.cond_div_param = defaults.cond_div_param;
        real.cond_goto = defaults.cond_goto;
        real.cond_goto_param = defaults.cond_goto_param;
    }

    // errors
    if (real.api == Api::SIMPLE && !glob.supported_apis_contains("simple")) {
        RET_FAIL(error("simple API is not supported for this backend"));
    }
    if (real.api_style == ApiStyle::FUNCTIONS && !glob.supported_api_styles_contains("functions")) {
        RET_FAIL(error("function-like API style is not supported for this backend"));
    }
    if (real.api_style == ApiStyle::FREEFORM && !glob.supported_api_styles_contains("free-form")) {
        RET_FAIL(error("free-form API style is not supported for this backend"));
    }
    if (!is_default.computed_gotos && !glob.supported_features_contains("computed-gotos")) {
        RET_FAIL(error("`computed-gotos` feature is not supported for this backend"));
    }
    if (!is_default.bitmaps && !glob.supported_features_contains("bitmaps")) {
        RET_FAIL(error("`bitmaps` feature is not supported for this backend"));
    }
    if (!is_default.nested_ifs && !glob.supported_features_contains("nested-ifs")) {
        RET_FAIL(error("`nested-ifs` feature is not supported for this backend"));
    }
    if (!is_default.case_ranges && !glob.supported_features_contains("case-ranges")) {
        RET_FAIL(error("`case-ranges` feature is not supported for this backend"));
    }
    if (!is_default.unsafe && !glob.supported_features_contains("unsafe")) {
        RET_FAIL(error("`unsafe` feature is not supported for this backend"));
    }
    if (!is_default.monadic && !glob.supported_features_contains("monadic")) {
        RET_FAIL(error("`monadic` feature is not supported for this backend"));
    }
    if (!is_default.tags && !glob.supported_features_contains("tags")) {
        RET_FAIL(error("`tags` feature is not supported for this backend"));
    }
    if (!is_default.captures && !is_default.captures_array && real.captures_array
            && !glob.supported_features_contains("captures")) {
        RET_FAIL(error("`captures` feature is not supported for this backend"));
    }
    if (!is_default.captures && !is_default.captures_array && !real.captures_array
            && !glob.supported_features_contains("captvars")) {
        RET_FAIL(error("`captvars` feature is not supported for this backend"));
    }
    if (real.fill_eof != NOEOF) {
        if (real.bitmaps || real.computed_gotos) {
            RET_FAIL(error("`re2c:eof` configuration cannot be used with options --bit-vectors "
                           "and --computed gotos"));
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
            RET_FAIL(error("`re2c:sentinel` configuration is not needed in the presence of bounds "
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
    if (glob.code_model != CodeModel::GOTO_LABEL) {
        if (real.computed_gotos) {
            RET_FAIL(error("computed gotos are not supported in this code model"));
        }
    }

    return Ret::OK;
}

Opt::Opt(OutAllocator& alc, Msg& msg)
    : glob()
    , symtab()
    , msg(msg)
    , alc(alc)
    , defaults()
    , is_default()
    , user()
    , real()
    , diverge(true)
    , stack_code()
    , stack_code_list()
    {}

Ret Opt::fix_global_and_defaults() {
    // Allow to modify only the global options.
    CHECK_RET(fix_conopt(const_cast<conopt_t&>(glob)));

    // Apply new defaults to all mutable options except those that have been explicitly defined by
    // the user.
#define MUTOPT(type, name, value) if (is_default.name) user.name = defaults.name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) if (is_default.name) user.name = defaults.name;
    RE2C_MUTCODES
#undef MUTCODE
    diverge = true;

    return Ret::OK;
}

Ret Opt::sync() {
    if (!diverge) return Ret::OK;

    // Copy user-defined options to real options.
#define MUTOPT(type, name, value) real.name = user.name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) real.name = user.name;
    RE2C_MUTCODES
#undef MUTCODE

    // Fix the real mutable options (based on the global options, mutable option defaults and
    // default flags), but do not change user-defined options or default flags.
    CHECK_RET(fix_mutopt(glob, defaults, is_default, real));

    diverge = false;

    return Ret::OK;
}

Ret Opt::snapshot(const opt_t** opts) {
    CHECK_RET(sync());
    *opts = new opt_t(glob, real, is_default, symtab);
    return Ret::OK;
}

Ret Opt::restore(const opt_t* opts) {
#define MUTOPT(type, name, value) \
    user.name = opts->name; \
    is_default.name = opts->is_default_##name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) \
    user.name = opts->code_##name; \
    is_default.name = opts->is_default_##name;
    RE2C_MUTCODES
#undef MUTCODE

    symtab = opts->symtab;

    diverge = true;
    return sync();
}

Ret Opt::merge(const opt_t* opts, Input& input) {
#define MUTOPT(type, name, value) \
    if (!opts->is_default_##name) { \
        user.name = opts->name; \
        is_default.name = false; \
    }
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) \
    if (!opts->is_default_##name) { \
        user.name = opts->code_##name; \
        is_default.name = false; \
    }
    RE2C_MUTCODES
#undef MUTCODE

    CHECK_RET(merge_symtab(symtab, opts->symtab, input));

    diverge = true;
    return sync();
}

#define MUTOPT(type, name, value) \
void Opt::init_##name(const type &arg) { \
    if (is_default.name) { \
        user.name = arg; \
        const_cast<mutopt_t&>(defaults).name = arg; \
    } \
    diverge = true; \
} \
void Opt::set_##name(const type &arg) { \
    user.name = arg; \
    is_default.name = false; \
    diverge = true; \
} \
void Opt::reset_##name() { \
    user.name = defaults.name; \
    is_default.name = true; \
    diverge = true; \
}
RE2C_MUTOPTS
#undef MUTOPT

#define MUTCODE(name) \
void Opt::init_##name(const StxCodes* arg) { \
    if (is_default.name) { \
        user.name = arg; \
        const_cast<mutopt_t&>(defaults).name = arg; \
    } \
    diverge = true; \
} \
void Opt::set_##name(const StxCodes* arg) { \
    user.name = arg; \
    is_default.name = false; \
    diverge = true; \
}
RE2C_MUTCODES
#undef MUTCODE

#define CHECKED_LIST(name, allowed) \
void Opt::set_##name(const std::vector<std::string>& list) { \
    const_cast<std::vector<std::string>&>(glob.name) = list; \
} \
Ret Opt::check_##name() { \
    static const std::unordered_set<std::string> alw allowed; \
    for (const std::string& elem : glob.name) { \
        if (std::find(alw.begin(), alw.end(), elem) == alw.end()) { \
            RET_FAIL(error("unknown element `%s` in list `%s`", elem.c_str(), #name)); \
        } \
    } \
    return Ret::OK; \
}
RE2C_CHECKED_LISTS
#undef CHECKED_LIST

#define STX_OPT(type, name, value) \
void Opt::set_##name(const type & val) { \
    const_cast<type&>(glob.name) = val; \
}
RE2C_STX_OPTS
#undef STX_OPT

#define CODE_TEMPLATE(name, vars, list_vars, conds) \
/* void Opt::set_code_##name(const StxCodes* code) { \
    const_cast<conopt_t&>(glob).code_##name = code; \
} */ \
Ret Opt::check_code_##name(Warn& warn) { \
    if (glob.code_##name == nullptr) { \
        /* we don't have a specific location => start of the current of syntax file */ \
        warn.undefined_syntax_config(ATSTART, "code:" #name); \
        const_cast<conopt_t&>(glob).code_##name = make_code_undefined(); \
    } \
    static const std::unordered_set<StxVarId> vs vars; \
    static const std::unordered_set<StxVarId> lvs list_vars; \
    static const std::unordered_set<StxLOpt> cs conds; \
    return validate_conf_code(glob.code_##name, "code:" #name, vs, lvs, cs); \
}
RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE

void Opt::init_encoding(Enc::Type type, bool on) {
    if (is_default.encoding) {
        if (on) {
            user.encoding.set(type);
        } else {
            user.encoding.unset(type);
        }
    }
    diverge = true;
}

void Opt::set_encoding(Enc::Type type, bool on) {
    if (on) {
        user.encoding.set(type);
    } else {
        user.encoding.unset(type);
    }
    is_default.encoding = false;
    diverge = true;
}

void Opt::init_encoding_policy(Enc::Policy p) {
    if (is_default.encoding) {
        user.encoding.set_policy(p);
    }
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

const char* Opt::var_name(StxVarId id) {
#define STX_LOCAL_VAR(id, name) name,
#define STX_GLOBAL_VAR(id, name) name,
    static const char* names[] = {
        RE2C_STX_LOCAL_VARS
        RE2C_STX_GLOBAL_VARS
    };
#undef STX_LOCAL_VAR
#undef STX_GLOBAL_VAR
    return names[static_cast<uint32_t>(id)];
}

// is this a known configuration-specific conditional?
Ret Opt::check_cond(StxLOpt opt, const char* conf, const std::unordered_set<StxLOpt>& conds) const {
    if (conds.find(opt) != conds.end()) return Ret::OK;
    RET_FAIL(error("unknown conditional in configuration `%s`", conf));
}

Ret Opt::check_var(
        StxVarId var,
        const char* conf,
        const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars) const {
    // is this a global variable?
    static const std::unordered_set<StxVarId> global_vars({
#define STX_GLOBAL_VAR(id, name) StxVarId:: id,
    RE2C_STX_GLOBAL_VARS
#undef STX_GLOBAL_VAR
    });
    if (global_vars.find(var) != global_vars.end()) return Ret::OK;

    // this may be a list var; in that case it must be on the list stack
    bool is_list_var = std::find_if(stack_code_list.begin(), stack_code_list.end(),
            [var](const StxCode* x) { return var == x->list.var; })
        != stack_code_list.end();

    // is this a known configuration-specific variable?
    const std::unordered_set<StxVarId>& v = is_list_var ? list_vars : vars;
    if (std::find(v.begin(), v.end(), var) != v.end()) return Ret::OK;

    RET_FAIL(error("unknown variable `%s` in configuration `%s`", var_name(var), conf));
}

// validate that all option and variable names used in the given code do exist
Ret Opt::validate_conf_code(
        const StxCodes* code,
        const char* conf,
        const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars,
        const std::unordered_set<StxLOpt>& conds) {
    stack_code_list.clear();
    stack_code_t& stack = stack_code;
    stack.clear();
    for (const StxCode* x = code->head; x != nullptr; x = x->next) {
        stack.push_back({x, 0});
    }

    static const std::unordered_set<std::string> oneliners {
#define ONELINE_CODE(name, kind) name,
        RE2C_ONELINE_CODES
#undef ONELINE_CODE
    };
    bool oneline = oneliners.find(conf) != oneliners.end();
    uint32_t newlines = 0;

    while (!stack.empty()) {
        const StxCode* x = stack.back().first;
        uint8_t n = stack.back().second;
        stack.pop_back();

        switch (x->type) {
        case StxCodeType::STR:
        case StxCodeType::UD:
            // no option names to check here
            break;
        case StxCodeType::VAR:
            if (oneline && x->var == StxVarId::NEWLINE && ++newlines > 1) {
                RET_FAIL(error("`%s` should be a one-line configuration", conf));
            }
            CHECK_RET(check_var(x->var, conf, vars, list_vars));
            break;
        case StxCodeType::COND:
            if (n == 0) { // recurse into branches
                stack.push_back({x, 1});
                for (const StxCode* y = x->cond.then_code->head; y != nullptr; y = y->next) {
                    stack.push_back({y, 0});
                }
                if (x->cond.else_code != nullptr) {
                    for (const StxCode* y = x->cond.else_code->head; y != nullptr; y = y->next) {
                        stack.push_back({y, 0});
                    }
                }
            } else if (x->cond.opt->kind == StxOptKind::LOC) {
                // no need to check global conditionals, as they are filtered in the lexer
                CHECK_RET(check_cond(x->cond.opt->lopt, conf, conds));
            }
            break;
        case StxCodeType::LIST:
            if (n == 0) { // recurse into list body
                stack_code_list.push_back(x);
                CHECK_RET(check_var(x->list.var, conf, vars, list_vars));
                stack.push_back({x, 1});
                for (const StxCode* y = x->list.code->head; y != nullptr; y = y->next) {
                    stack.push_back({y, 0});
                }
            } else { // check variable name and return
                stack_code_list.pop_back();
            }
            break;
        }
    }

    return Ret::OK;
}

StxCodes* Opt::new_code_list() {
    return new_list<StxCode, OutAllocator>(alc);
}

StxCode* Opt::make_code(StxCodeType type) {
    StxCode* x = alc.alloct<StxCode>(1);
    x->type = type;
    x->next = nullptr;
    return x;
}

StxCode* Opt::make_code_str(const char* str) {
    StxCode* x = make_code(StxCodeType::STR);
    x->str = str;
    return x;
}

StxCode* Opt::make_code_var(StxVarId var) {
    StxCode* x = make_code(StxCodeType::VAR);
    x->var = var;
    return x;
}

StxCodes* Opt::make_code_undefined() {
    StxCodes* x = new_code_list();
    append(x, make_code(StxCodeType::UD));
    return x;
}

StxOpt* Opt::make_opt_global(StxGOpt opt) {
    StxOpt* x = alc.alloct<StxOpt>(1);
    x->kind = StxOptKind::GLOB;
    x->gopt = opt;
    return x;
}

StxOpt* Opt::make_opt_local(StxLOpt opt) {
    StxOpt* x = alc.alloct<StxOpt>(1);
    x->kind = StxOptKind::LOC;
    x->lopt = opt;
    return x;
}

StxOpt* Opt::make_opt_imm(bool b) {
    StxOpt* x = alc.alloct<StxOpt>(1);
    x->kind = StxOptKind::IMM;
    x->imm = b;
    return x;
}

StxOpt* Opt::make_opt_neg(StxOpt* x) {
    if (x->kind == StxOptKind::IMM) {
        x->imm = !x->imm;
        return x;
    } else {
        StxOpt* y = alc.alloct<StxOpt>(1);
        y->kind = StxOptKind::NEG;
        y->neg = x;
        return y;
    }
}

StxOpt* Opt::make_opt_and(StxOpt* x, StxOpt* y) {
    if (x->kind == StxOptKind::IMM) {
        return x->imm ? y : x;
    } else if (y->kind == StxOptKind::IMM) {
        return y->imm ? x : y;
    } else {
        StxOpt* z = alc.alloct<StxOpt>(1);
        z->kind = StxOptKind::AND;
        z->op.lhs = x;
        z->op.rhs = y;
        return z;
    }
}

StxOpt* Opt::make_opt_or(StxOpt* x, StxOpt* y) {
    if (x->kind == StxOptKind::IMM) {
        return x->imm ? x : y;
    } else if (y->kind == StxOptKind::IMM) {
        return y->imm ? y : x;
    } else {
        StxOpt* z = alc.alloct<StxOpt>(1);
        z->kind = StxOptKind::OR;
        z->op.lhs = x;
        z->op.rhs = y;
        return z;
    }
}

StxCode* Opt::make_code_cond(StxOpt* opt, StxCodes* then_code, StxCodes* else_code) {
    StxCode* x = make_code(StxCodeType::COND);
    x->cond.opt = opt;
    x->cond.then_code = then_code;
    x->cond.else_code = else_code;
    return x;
}

StxCode* Opt::make_code_list(StxVarId var, int32_t lbound, int32_t rbound, StxCodes* code) {
    StxCode* x = make_code(StxCodeType::LIST);
    x->list.var = var;
    x->list.lbound = lbound;
    x->list.rbound = rbound;
    x->list.code = code;
    return x;
}

StxCodes* Opt::make_api(const std::string& str) {
    StxCodes* x = new_code_list();
    append(x, make_code_str(copystr(str, alc)));
    return x;
}

void opt_t::push_list_on_stack(const StxCode* x) const {
    if (x == nullptr) return;
    push_list_on_stack(x->next);
    stack_code.push_back({x, 0});
}

static bool eval_cond(
        StxCodeId id, const StxOpt* cond, const opt_t* opts, RenderCallback* callback) {
    switch (cond->kind) {
    case StxOptKind::IMM:
        return cond->imm;
    case StxOptKind::NEG:
        return !eval_cond(id, cond->neg, opts, callback);
    case StxOptKind::AND:
        return eval_cond(id, cond->op.lhs, opts, callback)
            && eval_cond(id, cond->op.rhs, opts, callback);
    case StxOptKind::OR:
        return eval_cond(id, cond->op.lhs, opts, callback)
            || eval_cond(id, cond->op.rhs, opts, callback);
    case StxOptKind::LOC:
        DCHECK(callback != nullptr);
        return callback->eval_cond(cond->lopt);
    case StxOptKind::GLOB:
        switch (cond->gopt) {
        case StxGOpt::API_SIMPLE:
            return opts->api == Api::SIMPLE;
        case StxGOpt::API_GENERIC:
            return opts->api == Api::GENERIC;
        case StxGOpt::API_RECORD:
            return opts->api == Api::RECORD;
        case StxGOpt::API_STYLE_FUNCTIONS:
            switch (id) {
                case StxCodeId::STX_yygetcond: return !opts->cond_get_naked;
                case StxCodeId::STX_yysetcond: return !opts->cond_set_naked;
                case StxCodeId::STX_yygetstate: return !opts->state_get_naked;
                case StxCodeId::STX_yysetstate: return !opts->state_set_naked;
                default: return opts->api_style == ApiStyle::FUNCTIONS;
            }
        case StxGOpt::API_STYLE_FREEFORM:
            switch (id) {
                case StxCodeId::STX_yygetcond: return opts->cond_get_naked;
                case StxCodeId::STX_yysetcond: return opts->cond_set_naked;
                case StxCodeId::STX_yygetstate: return opts->state_get_naked;
                case StxCodeId::STX_yysetstate: return opts->state_set_naked;
                default: return opts->api_style == ApiStyle::FREEFORM;
            }
        case StxGOpt::CODE_MODEL_GOTO_LABEL:
            return opts->code_model == CodeModel::GOTO_LABEL;
        case StxGOpt::CODE_MODEL_LOOP_SWITCH:
            return opts->code_model == CodeModel::LOOP_SWITCH;
        case StxGOpt::CODE_MODEL_REC_FUNC:
            return opts->code_model == CodeModel::REC_FUNC;
        case StxGOpt::START_CONDITIONS:
            return opts->start_conditions;
        case StxGOpt::STORABLE_STATE:
            return opts->storable_state;
        case StxGOpt::DATE:
            return opts->date;
        case StxGOpt::VER:
            return opts->version;
        case StxGOpt::CASE_RANGES:
            return opts->case_ranges;
        case StxGOpt::UNSAFE:
            return opts->unsafe;
        case StxGOpt::MONADIC:
            return opts->monadic;
        case StxGOpt::LOOP_LABEL:
            return !opts->label_loop.empty();
        }
    }
    UNREACHABLE();
    return false;
}

static inline bool eval_list_bounds(size_t size, int32_t& lbound, int32_t& rbound) {
    lbound = lbound >= 0 ? lbound : (std::max(0, static_cast<int32_t>(size) + lbound));
    rbound = rbound >= 0 ? rbound : (static_cast<int32_t>(size) + rbound);
    return lbound <= rbound && rbound >= 0;
}

#define CODE_TEMPLATE(name, vars, list_vars, conds) \
const char* opt_t::gen_code_##name(Scratchbuf& buf, RenderCallback& callback) const { \
    eval_code_conf(StxCodeId::STX_##name, #name, code_##name, buf.stream(), callback); \
    return buf.flush(); \
} \
const char* opt_t::gen_code_##name(Scratchbuf& buf) const { \
    eval_code_conf(StxCodeId::STX_##name, #name, code_##name, buf.stream()); \
    return buf.flush(); \
} \
void opt_t::render_code_##name(std::ostream& os, RenderCallback& callback) const { \
    eval_code_conf(StxCodeId::STX_##name, #name, code_##name, os, callback); \
} \
void opt_t::render_code_##name(std::ostream& os) const { \
    eval_code_conf(StxCodeId::STX_##name, #name, code_##name, os); \
}
RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE

namespace  {

class GenOpt : public RenderCallback {
    std::ostringstream &os;
    const opt_t* opts;
    StxCodeId id;

  public:
    GenOpt(std::ostringstream& os, const opt_t* opts, StxCodeId id)
        : os(os), opts(opts), id(id) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::SIGIL:
            switch (id) {
                case StxCodeId::STX_api_fill: os << opts->fill_param; break;
                case StxCodeId::STX_api_cond_set: os << opts->cond_set_param; break;
                case StxCodeId::STX_api_state_set: os << opts->state_set_param; break;
                case StxCodeId::STX_cond_div: os << opts->cond_div_param; break;
                case StxCodeId::STX_cond_goto: os << opts->cond_goto_param; break;
                default: os << opts->api_sigil; break;
            }
            break;
        case StxVarId::RECORD:
            os << opts->var_record;
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    FORBID_COPY(GenOpt);
};

} // anonymous namespace

#define MUTCODE(name) \
std::string opt_t::gen_##name(const StxCodes* code) const { \
    if (code == nullptr) return "<undefined code:" #name ">"; \
    std::ostringstream os; \
    GenOpt callback(os, this, StxCodeId::STX_##name); \
    eval_code_conf(StxCodeId::STX_##name, #name, code, os, callback); \
    return os.str(); \
}
RE2C_MUTCODES
#undef MUTCODE

void opt_t::eval_code_conf(StxCodeId id, const char* name, const StxCodes* code, std::ostream& os,
        RenderCallback& callback) const {
    CHECK(code != nullptr);

    stack_code_t& stack = stack_code;
    size_t bottom = stack.size();
    push_list_on_stack(code->head);

    while (stack.size() != bottom) {
        const StxCode* x = stack.back().first;
        int32_t n = stack.back().second;
        stack.pop_back();

        switch (x->type) {
        case StxCodeType::STR:
            os << x->str;
            break;
        case StxCodeType::VAR:
            callback.render_var(x->var);
            break;
        case StxCodeType::COND:
            if (eval_cond(id, x->cond.opt, this, &callback)) {
                push_list_on_stack(x->cond.then_code->head);
            } else if (x->cond.else_code != nullptr) {
                push_list_on_stack(x->cond.else_code->head);
            }
            break;
        case StxCodeType::LIST:
            if (n == 0) {
                int32_t lbound = x->list.lbound;
                int32_t rbound = x->list.rbound;
                if (eval_list_bounds(callback.get_list_size(x->list.var), lbound, rbound)) {
                    callback.start_list(
                            x->list.var, static_cast<size_t>(lbound), static_cast<size_t>(rbound));
                    stack.push_back({x, 1});
                    push_list_on_stack(x->list.code->head);
                }
            } else if (callback.next_in_list(x->list.var)) {
                stack.push_back({x, 1});
                push_list_on_stack(x->list.code->head);
            }
            break;
        case StxCodeType::UD:
            os << "<undefined code:" << name << ">";
            break;
        }
    }
}

void opt_t::eval_code_conf(StxCodeId id, const char* name, const StxCodes* code,
        std::ostream& os) const {
    RenderCallback dummy;
    eval_code_conf(id, name, code, os, dummy);
}

bool is_undefined(const StxCodes* code) {
    CHECK(code != nullptr);
    return code->head != nullptr
        && code->head->next == nullptr
        && code->head->type == StxCodeType::UD;
}

void RenderCallback::render_var(StxVarId /*var*/) {
    UNREACHABLE();
}

size_t RenderCallback::get_list_size(StxVarId /*var*/) const {
    UNREACHABLE();
    return 0;
}

void RenderCallback::start_list(StxVarId /*var*/, size_t /*lbound*/, size_t /*rbound*/) {
    UNREACHABLE();
}

bool RenderCallback::next_in_list(StxVarId /*var*/) {
    UNREACHABLE();
    return false;
}

bool RenderCallback::eval_cond(StxLOpt /*opt*/) {
    UNREACHABLE();
    return false;
}

} // namespace re2c
