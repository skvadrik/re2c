#include "src/msg/msg.h"
#include "src/options/opt.h"


namespace re2c {

// This function should only change global options.
static void fix_conopt(conopt_t &glob)
{
    if (glob.target == TARGET_SKELETON) {
        glob.fFlag = false;
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
        defaults.decorate = false;
    }
}

// This function should only change real mutable options (based on the global
// options, default mutable options and default flags). User-defined options are
// intentionally not passed to prevent accidental change, and default flags are
// passed as read-only.
static void fix_mutopt(const conopt_t &glob, const mutopt_t &defaults,
    const mutdef_t &is_default, mutopt_t &real)
{
    // some options either make no sense or must have fixed value
    // with current target: reset them to default
    switch (glob.target) {
        case TARGET_DOT:
            // default code generation options
            real.sFlag = defaults.sFlag;
            real.bFlag = defaults.bFlag;
            real.gFlag = defaults.gFlag;
            real.cGotoThreshold = defaults.cGotoThreshold;
            real.eof = defaults.eof;
            real.sentinel = defaults.sentinel;
            // default environment-insensitive formatting
            real.yybmHexTable = defaults.yybmHexTable;
            // fallthrough
        case TARGET_SKELETON:
            // output files
            real.header_file = "";
            // default line information
            real.iFlag = defaults.iFlag;
            // default EOF mode
            real.eof = defaults.eof;
            real.sentinel = defaults.sentinel;
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
            real.decorate = defaults.decorate;
            real.placeholder = defaults.placeholder;
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
            real.yystagpd = defaults.yystagpd;
            real.yymtagn = defaults.yymtagn;
            real.yymtagp = defaults.yymtagp;
            real.yymtagpd = defaults.yymtagpd;
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
            break;
        case TARGET_CODE:
            break;
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
        real.yystagpd = defaults.yystagpd;
        real.yymtagn = defaults.yymtagn;
        real.yymtagp = defaults.yymtagp;
        real.yymtagpd = defaults.yymtagpd;
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
    if (glob.target == TARGET_DOT) {
        real.iFlag = true;
    }
    else if (glob.target == TARGET_SKELETON) {
        real.iFlag = true;
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
    // individual "naked" options, unless explicitly set, inherit "decorate"
    if (is_default.fill_naked)      real.fill_naked      = !real.decorate;
    if (is_default.cond_get_naked)  real.cond_get_naked  = !real.decorate;
    if (is_default.cond_set_naked)  real.cond_set_naked  = !real.decorate;
    if (is_default.state_get_naked) real.state_get_naked = !real.decorate;
    if (is_default.state_set_naked) real.state_set_naked = !real.decorate;
    // individual template options, unless explicitly set, inherit "placeholder"
    if (is_default.fill_arg)         real.fill_arg         = real.placeholder;
    if (is_default.cond_set_arg)     real.cond_set_arg     = real.placeholder;
    if (is_default.condDividerParam) real.condDividerParam = real.placeholder;
    if (is_default.condGotoParam)    real.condGotoParam    = real.placeholder;
    if (is_default.state_set_arg)    real.state_set_arg    = real.placeholder;
    if (is_default.tags_expression)  real.tags_expression  = real.placeholder;
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
        fatal("skeleton is not supported for non-C language backends");
    }
    if (glob.lang == LANG_GO) {
        if (real.input_api == INPUT_DEFAULT) {
            fatal("default C API is not supported for the Go backend,"
                " as Go has no pointer arithmetics");
        }
        if (real.gFlag) {
            fatal("-g, --computed-gotos option is not supported for the Go backend,"
                " as Go does not have computed goto");
        }
    }
    if (real.eof != NOEOF) {
        if (real.bFlag || real.gFlag) {
            fatal("configuration 're2c:eof' cannot be used with options "
                "-b, --bit-vectors and -g, --computed gotos");
        }
        if (real.eof >= real.encoding.nCodeUnits()) {
            fatal("EOF exceeds maximum code unit value for given encoding");
        }
        if (!real.fill_check) {
            fatal("YYFILL check is necessary if EOF rule is used");
        }
    }
    if (real.sentinel != NOEOF) {
        if (real.sentinel >= real.encoding.nCodeUnits()) {
            fatal("sentinel exceeds maximum code unit value for given encoding");
        }
        if (real.fill_use || real.eof != NOEOF) {
            fatal("re2c:sentinel configuration is not needed"
                " in the presence of bounds checking or EOF rule");
        }
    }
    if (!glob.lookahead && glob.stadfa) {
        fatal("cannot combine TDFA(0) and staDFA");
    }
}

Opt::Opt(const conopt_t &globopts)
    : source_file(NULL)
    , glob(globopts)
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
    return new opt_t(glob, real, is_default);
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
}

void Opt::unset_encoding(Enc::type_t t)
{
    user.encoding.unset(t);
    is_default.encoding = false;
}

void Opt::set_encoding_policy(Enc::policy_t p)
{
    user.encoding.setPolicy(p);
    is_default.encoding = false;
}

bool Opt::source (const char *s)
{
    if (source_file) {
        error ("multiple source files: %s, %s", source_file, s);
        return false;
    }
    else {
        source_file = s;
        return true;
    }
}

void Opt::reset_group_startlabel()
{
    reset_startlabel();
    reset_startlabel_force();
}

void Opt::reset_group_api()
{
    // API-related configurations
    reset_cond_get();
    reset_cond_set();
    reset_fill();
    reset_state_get();
    reset_state_set();
    reset_yybackup();
    reset_yybackupctx();
    reset_yycondtype();
    reset_yyctxmarker();
    reset_yyctype();
    reset_yycursor();
    reset_yydebug();
    reset_yylessthan();
    reset_yylimit();
    reset_yymarker();
    reset_yypeek();
    reset_yyrestore();
    reset_yyrestorectx();
    reset_yyrestoretag();
    reset_yystagn();
    reset_yystagp();
    reset_yystagpd();
    reset_yymtagn();
    reset_yymtagp();
    reset_yymtagpd();
    reset_yyskip();
    reset_yyfilllabel();
    reset_yynext();
    reset_yyaccept();
    reset_yybm();
    reset_yych();
    reset_yyctable();
    reset_yytarget();
}

} // namespace re2c
