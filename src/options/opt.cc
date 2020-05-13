#include "src/msg/msg.h"
#include "src/options/opt.h"


namespace re2c {

Opt::Opt(const conopt_t &globopts)
    : source_file(NULL)
    , glob(globopts)
    , defaults()
    , is_default()
    , user()
    , real()
    , diverge(true)
{}

void Opt::fix_mutopt_defaults()
{
    // Adjust default mutable options based on the global options.
    mutopt_t &def = const_cast<mutopt_t&>(defaults);

    // For the Go backend, generic API is set by default, because "default" C
    // API with pointers doesn't work (there is no pointer arithmetics in Go).
    // To make the default Go API less restrictive, decorations are disabled.
    if (glob.lang == LANG_GO) {
        def.input_api = INPUT_CUSTOM;
        def.decorate = false;
    }

    // Apply new defaults to all mutable options except those that have been
    // explicitly set by the user.
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) if (is_default.name) user.name = defaults.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    diverge = true;
}

void Opt::fix_conopt()
{
    conopt_t &g = const_cast<conopt_t&>(glob);

    if (g.target == TARGET_SKELETON) {
        g.fFlag = false;
    }

    if (!g.lookahead) {
        g.eager_skip = true;
    }

    // append directory separator '/' to all paths that do not have it
    for (size_t i = 0; i < g.incpaths.size(); ++i) {
        std::string &p = g.incpaths[i];
        const char c = p.empty() ? 0 : *p.rbegin();
        if (c != '/' && c != '\\') {
            p.push_back('/');
        }
    }
}

void Opt::fix_mutopt()
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

    if (real.bCaseInsensitive) {
        real.bCaseInverted = defaults.bCaseInverted;
    }

    // "naked" options, unless explicitly set, inherit "decorate"
    if (is_default.fill_naked) real.fill_naked = !real.decorate;
    if (is_default.cond_get_naked) real.cond_get_naked = !real.decorate;
    if (is_default.cond_set_naked) real.cond_set_naked = !real.decorate;
    if (is_default.state_get_naked) real.state_get_naked = !real.decorate;
    if (is_default.state_set_naked) real.state_set_naked = !real.decorate;

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
        real.decorate = defaults.decorate;
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

    // force individual options
    if (glob.target == TARGET_DOT) {
        real.iFlag = true;
    }
    else if (glob.target == TARGET_SKELETON) {
        if (glob.lang != LANG_C) {
            fatal("skeleton is not supported for non-C language backends");
        }
        real.iFlag = true;
        real.input_api = INPUT_CUSTOM;
        real.indString = "    ";
        real.topIndent = 2;
    }
    switch (real.encoding.type()) {
        case Enc::UCS2:
        case Enc::UTF16:
        case Enc::UTF32:
            real.sFlag = true;
            break;
        case Enc::ASCII:
        case Enc::EBCDIC:
        case Enc::UTF8:
            break;
    }
    if (real.bFlag) {
        real.sFlag = true;
    }
    if (real.gFlag) {
        real.bFlag = true;
        real.sFlag = true;
    }

    if (glob.lang == LANG_GO && real.input_api == INPUT_DEFAULT) {
        fatal("default C API is not supported for the Go backend,"
            " as Go has no pointer arithmetics");
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

void Opt::sync()
{
    if (!diverge) return;

    // copy user-defined options to real options
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) real.name = user.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    fix_mutopt();
    diverge = false;
}

const opt_t *Opt::snapshot()
{
    sync();
    return new opt_t(glob, real);
}

void Opt::restore(const opt_t *opts)
{
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) user.name = opts->name;
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

void Opt::reset_startlabel()
{
    set_startlabel(defaults.startlabel);
    set_startlabel_force(defaults.startlabel_force);
}

void Opt::reset_mapCodeName ()
{
    // historically arranged set of names
    // no actual reason why these particular options should be reset
    set_cond_get(defaults.cond_get);
    set_cond_set(defaults.cond_set);
    set_fill(defaults.fill);
    set_state_get(defaults.state_get);
    set_state_set(defaults.state_set);
    set_yybackup(defaults.yybackup);
    set_yybackupctx(defaults.yybackupctx);
    set_yycondtype(defaults.yycondtype);
    set_yyctxmarker(defaults.yyctxmarker);
    set_yyctype(defaults.yyctype);
    set_yycursor(defaults.yycursor);
    set_yydebug(defaults.yydebug);
    set_yylessthan(defaults.yylessthan);
    set_yylimit(defaults.yylimit);
    set_yymarker(defaults.yymarker);
    set_yypeek(defaults.yypeek);
    set_yyrestore(defaults.yyrestore);
    set_yyrestorectx(defaults.yyrestorectx);
    set_yyrestoretag(defaults.yyrestoretag);
    set_yystagn(defaults.yystagn);
    set_yystagp(defaults.yystagp);
    set_yystagpd(defaults.yystagpd);
    set_yymtagn(defaults.yymtagn);
    set_yymtagp(defaults.yymtagp);
    set_yymtagpd(defaults.yymtagpd);
    set_yyskip(defaults.yyskip);
    set_yyfilllabel(defaults.yyfilllabel);
    set_yynext(defaults.yynext);
    set_yyaccept(defaults.yyaccept);
    set_yybm(defaults.yybm);
    set_yych(defaults.yych);
    set_yyctable(defaults.yyctable);
    set_yytarget(defaults.yytarget);
}

} // namespace re2c
