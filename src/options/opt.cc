#include <stdlib.h>

#include "src/msg/msg.h"
#include "src/options/opt.h"


namespace re2c {

// This function should only change global options.
static void fix_conopt(conopt_t &glob)
{
    if (glob.target == TARGET_DOT) {
        glob.iFlag = true;
    } else if (glob.target == TARGET_SKELETON) {
        glob.fFlag = false;
        glob.iFlag = true;
    }

    if (!glob.lookahead) {
        glob.eager_skip = true;
    }

    // append directory separator '/' to all paths that do not have it
    for (size_t i = 0; i < glob.incpaths.size(); ++i) {
        std::string &p = glob.incpaths[i];
        const char c = p.empty() ? 0 : *p.rbegin();
        if (c != '/' && c != '\\') {
            p.push_back('/');
        }
    }

    if (!glob.dep_file.empty() && glob.output_file.empty()) {
        error("cannot generate dep file, output file not specified");
        exit(1);
    }
}

// This function should only change mutable option defaults (based on the global
// options).
static void fix_mutopt_defaults(const conopt_t &glob, mutopt_t &defaults)
{
    // For the Go backend, generic API is set by default, because "default" C
    // API with pointers doesn't work (there is no pointer arithmetics in Go).
    // To make the default Go API less restrictive, decorations are disabled.
    if (glob.lang == LANG_GO) {
        defaults.input_api = INPUT_CUSTOM;
        defaults.api_style = API_FREEFORM;
    }
}

// This function should only change real mutable options (based on the global
// options, default mutable options and default flags). User-defined options are
// intentionally not passed to prevent accidental change, and default flags are
// passed as read-only.
static void fix_mutopt(const conopt_t &glob, const mutopt_t &defaults,
    const mutdef_t &is_default, mutopt_t &real)
{
    // For skeleton target interface options must have default values (because
    // skeleton programs assume certain interface). For DOT target most of the
    // options are unused.
    if (glob.target != TARGET_CODE) {
        // output files
        real.header_file = "";
        // default environment-sensitive formatting
        real.topIndent = defaults.topIndent;
        real.indString = defaults.indString;
        real.condDivider = defaults.condDivider;
        real.condDividerParam = defaults.condDividerParam;
        // default environment bindings
        real.yycondtype = defaults.yycondtype;
        real.cond_get = defaults.cond_get;
        real.cond_get_naked = defaults.cond_get_naked;
        real.cond_set = defaults.cond_set;
        real.cond_set_arg = defaults.cond_set_arg;
        real.cond_set_naked = defaults.cond_set_naked;
        real.yyctable = defaults.yyctable;
        real.condPrefix = defaults.condPrefix;
        real.condEnumPrefix = defaults.condEnumPrefix;
        real.condGoto = defaults.condGoto;
        real.condGotoParam = defaults.condGotoParam;
        real.state_get = defaults.state_get;
        real.state_get_naked = defaults.state_get_naked;
        real.state_set = defaults.state_set;
        real.state_set_arg = defaults.state_set_arg;
        real.state_set_naked = defaults.state_set_naked;
        real.tags_prefix = defaults.tags_prefix;
        real.tags_expression = defaults.tags_expression;
        real.yyfilllabel = defaults.yyfilllabel;
        real.yynext = defaults.yynext;
        real.yyaccept = defaults.yyaccept;
        real.bUseStateAbort = defaults.bUseStateAbort;
        real.bUseStateNext = defaults.bUseStateNext;
        real.yybm = defaults.yybm;
        real.yytarget = defaults.yytarget;
        real.input_api = defaults.input_api;
        real.api_style = defaults.api_style;
        real.api_sigil = defaults.api_sigil;
        real.yycursor = defaults.yycursor;
        real.yymarker = defaults.yymarker;
        real.yyctxmarker = defaults.yyctxmarker;
        real.yylimit = defaults.yylimit;
        real.yypeek = defaults.yypeek;
        real.yyskip = defaults.yyskip;
        real.yybackup = defaults.yybackup;
        real.yybackupctx = defaults.yybackupctx;
        real.yyrestore = defaults.yyrestore;
        real.yyrestorectx = defaults.yyrestorectx;
        real.yyrestoretag = defaults.yyrestoretag;
        real.yystagn = defaults.yystagn;
        real.yystagp = defaults.yystagp;
        real.yymtagn = defaults.yymtagn;
        real.yymtagp = defaults.yymtagp;
        real.yyshift = defaults.yyshift;
        real.yyshiftstag = defaults.yyshiftstag;
        real.yyshiftmtag = defaults.yyshiftmtag;
        real.yylessthan = defaults.yylessthan;
        real.dFlag = defaults.dFlag;
        real.yydebug = defaults.yydebug;
        real.yyctype = defaults.yyctype;
        real.yych = defaults.yych;
        real.bEmitYYCh = defaults.bEmitYYCh;
        real.yychConversion = defaults.yychConversion;
        real.fill = defaults.fill;
        real.fill_use = defaults.fill_use;
        real.fill_check = defaults.fill_check;
        real.fill_arg = defaults.fill_arg;
        real.fill_arg_use = defaults.fill_arg_use;
        real.fill_naked = defaults.fill_naked;
        real.labelPrefix = defaults.labelPrefix;
        real.startlabel = defaults.startlabel;
        real.startlabel_force = defaults.startlabel_force;
    }

    // respect hierarchy
    if (!glob.cFlag) {
        real.yycondtype = defaults.yycondtype;
        real.cond_get = defaults.cond_get;
        real.cond_get_naked = defaults.cond_get_naked;
        real.cond_set = defaults.cond_set;
        real.cond_set_arg = defaults.cond_set_arg;
        real.cond_set_naked = defaults.cond_set_naked;
        real.yyctable = defaults.yyctable;
        real.condPrefix = defaults.condPrefix;
        real.condEnumPrefix = defaults.condEnumPrefix;
        real.condDivider = defaults.condDivider;
        real.condDividerParam = defaults.condDividerParam;
        real.condGoto = defaults.condGoto;
        real.condGotoParam = defaults.condGotoParam;
    }
    if (!glob.fFlag) {
        real.state_get = defaults.state_get;
        real.state_get_naked = defaults.state_get_naked;
        real.state_set = defaults.state_set;
        real.state_set_arg = defaults.state_set_arg;
        real.state_set_naked = defaults.state_set_naked;
        real.yyfilllabel = defaults.yyfilllabel;
        real.yynext = defaults.yynext;
        real.yyaccept = defaults.yyaccept;
        real.bUseStateAbort = defaults.bUseStateAbort;
        real.bUseStateNext = defaults.bUseStateNext;
    }
    if (real.posix_semantics) {
        real.posix_syntax = true;
    }
    if (real.posix_syntax) {
        real.tags = true;
    }
    if (!real.tags) {
        real.tags_prefix = defaults.tags_prefix;
        real.tags_expression = defaults.tags_expression;
    }
    if (!real.bFlag) {
        real.yybmHexTable = defaults.yybmHexTable;
        real.yybm = defaults.yybm;
    }
    if (!real.gFlag) {
        real.cGotoThreshold = defaults.cGotoThreshold;
        real.yytarget = defaults.yytarget;
    }
    if (real.input_api != INPUT_DEFAULT) {
        real.yycursor = defaults.yycursor;
        real.yymarker = defaults.yymarker;
        real.yyctxmarker = defaults.yyctxmarker;
        real.yylimit = defaults.yylimit;
    }
    if (real.input_api != INPUT_CUSTOM) {
        real.yypeek = defaults.yypeek;
        real.yyskip = defaults.yyskip;
        real.yybackup = defaults.yybackup;
        real.yybackupctx = defaults.yybackupctx;
        real.yyrestore = defaults.yyrestore;
        real.yyrestorectx = defaults.yyrestorectx;
        real.yyrestoretag = defaults.yyrestoretag;
        real.yystagn = defaults.yystagn;
        real.yystagp = defaults.yystagp;
        real.yyshift = defaults.yyshift;
        real.yyshiftstag = defaults.yyshiftstag;
        // for mtags there are no sensible defaults
    }
    if (!real.dFlag) {
        real.yydebug = defaults.yydebug;
    }
    if (!real.fill_use) {
        real.fill = defaults.fill;
        real.fill_check = defaults.fill_check;
        real.fill_arg = defaults.fill_arg;
        real.fill_arg_use = defaults.fill_arg_use;
        real.fill_naked = defaults.fill_naked;
    }

    // set implied options
    if (glob.target == TARGET_SKELETON) {
        real.input_api = INPUT_CUSTOM;
        real.indString = "    ";
        real.topIndent = 2;
    }
    if (real.bFlag || real.encoding.multibyte_cunit()) {
        real.sFlag = true;
    }
    if (real.gFlag) {
        real.bFlag = true;
        real.sFlag = true;
    }
    if (real.bCaseInsensitive) {
        real.bCaseInverted = defaults.bCaseInverted;
    }
    // individual "naked" options, unless explicitly set, inherit "api:style"
    if (is_default.fill_naked)      real.fill_naked      = real.api_style == API_FREEFORM;
    if (is_default.cond_get_naked)  real.cond_get_naked  = real.api_style == API_FREEFORM;
    if (is_default.cond_set_naked)  real.cond_set_naked  = real.api_style == API_FREEFORM;
    if (is_default.state_get_naked) real.state_get_naked = real.api_style == API_FREEFORM;
    if (is_default.state_set_naked) real.state_set_naked = real.api_style == API_FREEFORM;
    // individual template options, unless explicitly set, inherit "api:sigil"
    if (is_default.fill_arg)         real.fill_arg         = real.api_sigil;
    if (is_default.cond_set_arg)     real.cond_set_arg     = real.api_sigil;
    if (is_default.condDividerParam) real.condDividerParam = real.api_sigil;
    if (is_default.condGotoParam)    real.condGotoParam    = real.api_sigil;
    if (is_default.state_set_arg)    real.state_set_arg    = real.api_sigil;
    if (is_default.tags_expression)  real.tags_expression  = real.api_sigil;
    if (is_default.condGoto) {
        real.condGoto = "goto " + real.condGotoParam + (glob.lang == LANG_C ? ";" : "");
    }
    // "startlabel" configuration exists in two variants: string and boolean,
    // and the string one overrides the boolean one
    if (!is_default.startlabel) {
        real.startlabel_force = defaults.startlabel_force;
    }
    if (real.fill_naked) {
        real.fill_arg_use = false;
    }

    // errors
    if (glob.target == TARGET_SKELETON && glob.lang != LANG_C) {
        error("skeleton is not supported for non-C language backends");
        exit(1);
    }
    if (glob.lang == LANG_GO) {
        if (real.input_api == INPUT_DEFAULT) {
            error("default C API is not supported for the Go backend,"
                " as Go has no pointer arithmetics");
            exit(1);
        }
        if (real.gFlag) {
            error("-g, --computed-gotos option is not supported for the Go backend,"
                " as Go does not have computed goto");
            exit(1);
        }
        if (real.case_ranges) {
            error("--case-ranges option is not supported for the Go backend,"
                " as Go has no case ranges");
            exit(1);
        }
    }
    if (real.eof != NOEOF) {
        if (real.bFlag || real.gFlag) {
            error("configuration 're2c:eof' cannot be used with options "
                "-b, --bit-vectors and -g, --computed gotos");
            exit(1);
        }
        if (real.eof >= real.encoding.nCodeUnits()) {
            error("EOF exceeds maximum code unit value for given encoding");
            exit(1);
        }
        if (!real.fill_check) {
            error("YYFILL check is necessary if EOF rule is used");
            exit(1);
        }
    }
    if (real.sentinel != NOEOF) {
        if (real.sentinel >= real.encoding.nCodeUnits()) {
            error("sentinel exceeds maximum code unit value for given encoding");
            exit(1);
        }
        if (real.fill_use || real.eof != NOEOF) {
            error("re2c:sentinel configuration is not needed"
                " in the presence of bounds checking or EOF rule");
            exit(1);
        }
    }
    if (!glob.lookahead && glob.stadfa) {
        error("cannot combine TDFA(0) and staDFA");
        exit(1);
    }
    if (glob.fFlag && !real.fill_use) {
        // -f, --storable-state option should not be used if YYFILL is disabled,
        // because without YYFILL the interrupt points do not necessarily
        // correspond to storable state labels (with generic API interrupts can
        // happen on any API invocation). This may cause subtle bugs when the
        // lexer is resumed from the wrong program point.
        error("storable state requires YYFILL to be enabled");
        exit(1);
    }
}

Opt::Opt(const conopt_t &globopts)
    : glob(globopts)
    , symtab()
    , defaults()
    , is_default()
    , user()
    , real()
    , diverge(true)
{}

void Opt::fix_global_and_defaults()
{
    // Allow to modify only the global options.
    fix_conopt(const_cast<conopt_t&>(glob));

    // Allow to modify only the mutable option defaults (based on the global
    // options).
    fix_mutopt_defaults(glob, const_cast<mutopt_t&>(defaults));

    // Apply new defaults to all mutable options except those that have been
    // explicitly defined by the user.
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    if (is_default.name) user.name = defaults.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    diverge = true;
}

void Opt::sync()
{
    if (!diverge) return;

    // Copy user-defined options to real options.
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    real.name = user.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    // Fix the real mutable options (based on the global options, mutable option
    // defaults and default flags), but do not change user-defined options or
    // default flags.
    fix_mutopt(glob, defaults, is_default, real);

    diverge = false;
}

const opt_t *Opt::snapshot()
{
    sync();
    return new opt_t(glob, real, is_default, symtab);
}

void Opt::restore(const opt_t *opts)
{
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    user.name = opts->name; \
    is_default.name = opts->is_default_##name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    symtab = opts->symtab;

    diverge = true;
    sync();
}

void Opt::merge(const opt_t *opts, const loc_t &loc, Msg &msg)
{
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    if (!opts->is_default_##name) { \
        user.name = opts->name; \
        is_default.name = false; \
    }
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    merge_symtab(symtab, opts->symtab, loc, msg);

    diverge = true;
    sync();
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

void Opt::set_encoding(Enc::type_t t)
{
    user.encoding.set(t);
    is_default.encoding = false;
    diverge = true;
}

void Opt::unset_encoding(Enc::type_t t)
{
    user.encoding.unset(t);
    is_default.encoding = false; // explicitly unset by the user => not default
    diverge = true;
}

void Opt::set_encoding_policy(Enc::policy_t p)
{
    user.encoding.setPolicy(p);
    is_default.encoding = false;
    diverge = true;
}

void Opt::reset_group_startlabel()
{
    reset_startlabel();
    reset_startlabel_force();
    diverge = true;
}

} // namespace re2c
