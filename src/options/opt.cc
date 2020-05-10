#include "src/msg/msg.h"
#include "src/options/opt.h"


namespace re2c {

void conopt_t::fix()
{
    if (target == TARGET_SKELETON) {
        fFlag = false;
    }

    if (!lookahead) {
        eager_skip = true;
    }

    // append directory separator '/' to all paths that do not have it
    for (size_t i = 0; i < incpaths.size(); ++i) {
        std::string &p = incpaths[i];
        const char c = p.empty() ? 0 : *p.rbegin();
        if (c != '/' && c != '\\') {
            p.push_back('/');
        }
    }
}

void mutopt_t::fix(const conopt_t *globopts, const mutopt_t &defaults)
{
    // some options either make no sense or must have fixed value
    // with current target: reset them to default
    switch (globopts->target) {
        case TARGET_DOT:
            // default code generation options
            sFlag = defaults.sFlag;
            bFlag = defaults.bFlag;
            gFlag = defaults.gFlag;
            cGotoThreshold = defaults.cGotoThreshold;
            eof = defaults.eof;
            sentinel = defaults.sentinel;
            // default environment-insensitive formatting
            yybmHexTable = defaults.yybmHexTable;
            // fallthrough
        case TARGET_SKELETON:
            // output files
            header_file = "";
            // default line information
            iFlag = defaults.iFlag;
            // default EOF mode
            eof = defaults.eof;
            sentinel = defaults.sentinel;
            // default environment-sensitive formatting
            topIndent = defaults.topIndent;
            indString = defaults.indString;
            condDivider = defaults.condDivider;
            condDividerParam = defaults.condDividerParam;
            // default environment bindings
            yycondtype = defaults.yycondtype;
            cond_get = defaults.cond_get;
            cond_get_naked = defaults.cond_get_naked;
            cond_set = defaults.cond_set;
            cond_set_arg = defaults.cond_set_arg;
            cond_set_naked = defaults.cond_set_naked;
            yyctable = defaults.yyctable;
            condPrefix = defaults.condPrefix;
            condEnumPrefix = defaults.condEnumPrefix;
            condGoto = defaults.condGoto;
            condGotoParam = defaults.condGotoParam;
            state_get = defaults.state_get;
            state_get_naked = defaults.state_get_naked;
            state_set = defaults.state_set;
            state_set_arg = defaults.state_set_arg;
            state_set_naked = defaults.state_set_naked;
            tags_prefix = defaults.tags_prefix;
            tags_expression = defaults.tags_expression;
            yyfilllabel = defaults.yyfilllabel;
            yynext = defaults.yynext;
            yyaccept = defaults.yyaccept;
            bUseStateAbort = defaults.bUseStateAbort;
            bUseStateNext = defaults.bUseStateNext;
            yybm = defaults.yybm;
            yytarget = defaults.yytarget;
            input_api = defaults.input_api;
            decorate = defaults.decorate;
            yycursor = defaults.yycursor;
            yymarker = defaults.yymarker;
            yyctxmarker = defaults.yyctxmarker;
            yylimit = defaults.yylimit;
            yypeek = defaults.yypeek;
            yyskip = defaults.yyskip;
            yybackup = defaults.yybackup;
            yybackupctx = defaults.yybackupctx;
            yyrestore = defaults.yyrestore;
            yyrestorectx = defaults.yyrestorectx;
            yyrestoretag = defaults.yyrestoretag;
            yystagn = defaults.yystagn;
            yystagp = defaults.yystagp;
            yystagpd = defaults.yystagpd;
            yymtagn = defaults.yymtagn;
            yymtagp = defaults.yymtagp;
            yymtagpd = defaults.yymtagpd;
            yylessthan = defaults.yylessthan;
            dFlag = defaults.dFlag;
            yydebug = defaults.yydebug;
            yyctype = defaults.yyctype;
            yych = defaults.yych;
            bEmitYYCh = defaults.bEmitYYCh;
            yychConversion = defaults.yychConversion;
            fill = defaults.fill;
            fill_use = defaults.fill_use;
            fill_check = defaults.fill_check;
            fill_arg = defaults.fill_arg;
            fill_arg_use = defaults.fill_arg_use;
            fill_naked = defaults.fill_naked;
            labelPrefix = defaults.labelPrefix;
            startlabel = defaults.startlabel;
            startlabel_force = defaults.startlabel_force;
            break;
        case TARGET_CODE:
            break;
    }

    if (bCaseInsensitive) {
        bCaseInverted = defaults.bCaseInverted;
    }

    // respect hierarchy
    if (!globopts->cFlag) {
        yycondtype = defaults.yycondtype;
        cond_get = defaults.cond_get;
        cond_get_naked = defaults.cond_get_naked;
        cond_set = defaults.cond_set;
        cond_set_arg = defaults.cond_set_arg;
        cond_set_naked = defaults.cond_set_naked;
        yyctable = defaults.yyctable;
        condPrefix = defaults.condPrefix;
        condEnumPrefix = defaults.condEnumPrefix;
        condDivider = defaults.condDivider;
        condDividerParam = defaults.condDividerParam;
        condGoto = defaults.condGoto;
        condGotoParam = defaults.condGotoParam;
    }
    if (!globopts->fFlag) {
        state_get = defaults.state_get;
        state_get_naked = defaults.state_get_naked;
        state_set = defaults.state_set;
        state_set_arg = defaults.state_set_arg;
        state_set_naked = defaults.state_set_naked;
        yyfilllabel = defaults.yyfilllabel;
        yynext = defaults.yynext;
        yyaccept = defaults.yyaccept;
        bUseStateAbort = defaults.bUseStateAbort;
        bUseStateNext = defaults.bUseStateNext;
    }
    if (posix_semantics) {
        posix_syntax = true;
    }
    if (posix_syntax) {
        tags = true;
    }
    if (!tags) {
        tags_prefix = defaults.tags_prefix;
        tags_expression = defaults.tags_expression;
    }
    if (!bFlag) {
        yybmHexTable = defaults.yybmHexTable;
        yybm = defaults.yybm;
    }
    if (!gFlag) {
        cGotoThreshold = defaults.cGotoThreshold;
        yytarget = defaults.yytarget;
    }
    if (input_api != INPUT_DEFAULT) {
        yycursor = defaults.yycursor;
        yymarker = defaults.yymarker;
        yyctxmarker = defaults.yyctxmarker;
        yylimit = defaults.yylimit;
    }
    if (input_api != INPUT_CUSTOM) {
        decorate = defaults.decorate;
        yypeek = defaults.yypeek;
        yyskip = defaults.yyskip;
        yybackup = defaults.yybackup;
        yybackupctx = defaults.yybackupctx;
        yyrestore = defaults.yyrestore;
        yyrestorectx = defaults.yyrestorectx;
        yyrestoretag = defaults.yyrestoretag;
        yystagn = defaults.yystagn;
        yystagp = defaults.yystagp;
        yystagpd = defaults.yystagpd;
        yymtagn = defaults.yymtagn;
        yymtagp = defaults.yymtagp;
        yymtagpd = defaults.yymtagpd;
    }
    if (!dFlag) {
        yydebug = defaults.yydebug;
    }
    if (!fill_use) {
        fill = defaults.fill;
        fill_check = defaults.fill_check;
        fill_arg = defaults.fill_arg;
        fill_arg_use = defaults.fill_arg_use;
        fill_naked = defaults.fill_naked;
    }

    // force individual options
    if (globopts->target == TARGET_DOT) {
        iFlag = true;
    }
    else if (globopts->target == TARGET_SKELETON) {
        if (globopts->lang != LANG_C) {
            fatal("skeleton is not supported for non-C language backends");
        }
        iFlag = true;
        input_api = INPUT_CUSTOM;
        indString = "    ";
        topIndent = 2;
    }
    switch (encoding.type()) {
        case Enc::UCS2:
        case Enc::UTF16:
        case Enc::UTF32:
            sFlag = true;
            break;
        case Enc::ASCII:
        case Enc::EBCDIC:
        case Enc::UTF8:
            break;
    }
    if (bFlag) {
        sFlag = true;
    }
    if (gFlag) {
        bFlag = true;
        sFlag = true;
    }
    if (globopts->lang == LANG_GO && input_api == INPUT_DEFAULT) {
        fatal("default C API is not supported for the Go backend,"
            " as Go has no pointer arithmetics");
    }
    if (eof != NOEOF) {
        if (bFlag || gFlag) {
            fatal ("configuration 're2c:eof' cannot be used with options "
                "-b, --bit-vectors and -g, --computed gotos");
        }
        if (eof >= encoding.nCodeUnits()) {
            fatal ("EOF exceeds maximum code unit value for given encoding");
        }
    }
    if (sentinel != NOEOF) {
        if (sentinel >= encoding.nCodeUnits()) {
            fatal("sentinel exceeds maximum code unit value for given encoding");
        }
        if (fill_use || eof != NOEOF) {
            fatal("re2c:sentinel configuration is not needed"
                " in the presence of bounds checking or EOF rule");
        }
    }
    if (!globopts->lookahead && globopts->stadfa) {
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

void Opt::fix_defaults()
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

void Opt::sync()
{
    if (!diverge) return;

#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) real.name = user.name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    real.fix(&glob, defaults);
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
