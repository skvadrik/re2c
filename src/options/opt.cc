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

void mutopt_t::fix(const conopt_t *globopts)
{
    // some options either make no sense or must have fixed value
    // with current target: reset them to default
    switch (globopts->target) {
        case TARGET_DOT:
            // default code generation options
            sFlag = Opt::baseopt.sFlag;
            bFlag = Opt::baseopt.bFlag;
            gFlag = Opt::baseopt.gFlag;
            cGotoThreshold = Opt::baseopt.cGotoThreshold;
            eof = Opt::baseopt.eof;
            sentinel = Opt::baseopt.sentinel;
            // default environment-insensitive formatting
            yybmHexTable = Opt::baseopt.yybmHexTable;
            // fallthrough
        case TARGET_SKELETON:
            // output files
            header_file = "";
            // default line information
            iFlag = Opt::baseopt.iFlag;
            // default EOF mode
            eof = Opt::baseopt.eof;
            sentinel = Opt::baseopt.sentinel;
            // default environment-sensitive formatting
            topIndent = Opt::baseopt.topIndent;
            indString = Opt::baseopt.indString;
            condDivider = Opt::baseopt.condDivider;
            condDividerParam = Opt::baseopt.condDividerParam;
            // default environment bindings
            yycondtype = Opt::baseopt.yycondtype;
            cond_get = Opt::baseopt.cond_get;
            cond_get_naked = Opt::baseopt.cond_get_naked;
            cond_set = Opt::baseopt.cond_set;
            cond_set_arg = Opt::baseopt.cond_set_arg;
            cond_set_naked = Opt::baseopt.cond_set_naked;
            yyctable = Opt::baseopt.yyctable;
            condPrefix = Opt::baseopt.condPrefix;
            condEnumPrefix = Opt::baseopt.condEnumPrefix;
            condGoto = Opt::baseopt.condGoto;
            condGotoParam = Opt::baseopt.condGotoParam;
            state_get = Opt::baseopt.state_get;
            state_get_naked = Opt::baseopt.state_get_naked;
            state_set = Opt::baseopt.state_set;
            state_set_arg = Opt::baseopt.state_set_arg;
            state_set_naked = Opt::baseopt.state_set_naked;
            tags_prefix = Opt::baseopt.tags_prefix;
            tags_expression = Opt::baseopt.tags_expression;
            yyfilllabel = Opt::baseopt.yyfilllabel;
            yynext = Opt::baseopt.yynext;
            yyaccept = Opt::baseopt.yyaccept;
            bUseStateAbort = Opt::baseopt.bUseStateAbort;
            bUseStateNext = Opt::baseopt.bUseStateNext;
            yybm = Opt::baseopt.yybm;
            yytarget = Opt::baseopt.yytarget;
            input_api = Opt::baseopt.input_api;
            yycursor = Opt::baseopt.yycursor;
            yymarker = Opt::baseopt.yymarker;
            yyctxmarker = Opt::baseopt.yyctxmarker;
            yylimit = Opt::baseopt.yylimit;
            yypeek = Opt::baseopt.yypeek;
            yyskip = Opt::baseopt.yyskip;
            yybackup = Opt::baseopt.yybackup;
            yybackupctx = Opt::baseopt.yybackupctx;
            yyrestore = Opt::baseopt.yyrestore;
            yyrestorectx = Opt::baseopt.yyrestorectx;
            yyrestoretag = Opt::baseopt.yyrestoretag;
            yystagn = Opt::baseopt.yystagn;
            yystagp = Opt::baseopt.yystagp;
            yystagpd = Opt::baseopt.yystagpd;
            yymtagn = Opt::baseopt.yymtagn;
            yymtagp = Opt::baseopt.yymtagp;
            yymtagpd = Opt::baseopt.yymtagpd;
            yylessthan = Opt::baseopt.yylessthan;
            dFlag = Opt::baseopt.dFlag;
            yydebug = Opt::baseopt.yydebug;
            yyctype = Opt::baseopt.yyctype;
            yych = Opt::baseopt.yych;
            bEmitYYCh = Opt::baseopt.bEmitYYCh;
            yychConversion = Opt::baseopt.yychConversion;
            fill = Opt::baseopt.fill;
            fill_use = Opt::baseopt.fill_use;
            fill_check = Opt::baseopt.fill_check;
            fill_arg = Opt::baseopt.fill_arg;
            fill_arg_use = Opt::baseopt.fill_arg_use;
            fill_naked = Opt::baseopt.fill_naked;
            labelPrefix = Opt::baseopt.labelPrefix;
            startlabel = Opt::baseopt.startlabel;
            startlabel_force = Opt::baseopt.startlabel_force;
            break;
        case TARGET_CODE:
            break;
    }

    if (bCaseInsensitive)
    {
        bCaseInverted = Opt::baseopt.bCaseInverted;
    }

    // respect hierarchy
    if (!globopts->cFlag) {
        yycondtype = Opt::baseopt.yycondtype;
        cond_get = Opt::baseopt.cond_get;
        cond_get_naked = Opt::baseopt.cond_get_naked;
        cond_set = Opt::baseopt.cond_set;
        cond_set_arg = Opt::baseopt.cond_set_arg;
        cond_set_naked = Opt::baseopt.cond_set_naked;
        yyctable = Opt::baseopt.yyctable;
        condPrefix = Opt::baseopt.condPrefix;
        condEnumPrefix = Opt::baseopt.condEnumPrefix;
        condDivider = Opt::baseopt.condDivider;
        condDividerParam = Opt::baseopt.condDividerParam;
        condGoto = Opt::baseopt.condGoto;
        condGotoParam = Opt::baseopt.condGotoParam;
    }
    if (!globopts->fFlag) {
        state_get = Opt::baseopt.state_get;
        state_get_naked = Opt::baseopt.state_get_naked;
        state_set = Opt::baseopt.state_set;
        state_set_arg = Opt::baseopt.state_set_arg;
        state_set_naked = Opt::baseopt.state_set_naked;
        yyfilllabel = Opt::baseopt.yyfilllabel;
        yynext = Opt::baseopt.yynext;
        yyaccept = Opt::baseopt.yyaccept;
        bUseStateAbort = Opt::baseopt.bUseStateAbort;
        bUseStateNext = Opt::baseopt.bUseStateNext;
    }
    if (posix_semantics) {
        posix_syntax = true;
    }
    if (posix_syntax) {
        tags = true;
    }
    if (!tags)
    {
        tags_prefix = Opt::baseopt.tags_prefix;
        tags_expression = Opt::baseopt.tags_expression;
    }
    if (!bFlag)
    {
        yybmHexTable = Opt::baseopt.yybmHexTable;
        yybm = Opt::baseopt.yybm;
    }
    if (!gFlag)
    {
        cGotoThreshold = Opt::baseopt.cGotoThreshold;
        yytarget = Opt::baseopt.yytarget;
    }
    if (input_api != INPUT_DEFAULT)
    {
        yycursor = Opt::baseopt.yycursor;
        yymarker = Opt::baseopt.yymarker;
        yyctxmarker = Opt::baseopt.yyctxmarker;
        yylimit = Opt::baseopt.yylimit;
    }
    if (input_api != INPUT_CUSTOM)
    {
        yypeek = Opt::baseopt.yypeek;
        yyskip = Opt::baseopt.yyskip;
        yybackup = Opt::baseopt.yybackup;
        yybackupctx = Opt::baseopt.yybackupctx;
        yyrestore = Opt::baseopt.yyrestore;
        yyrestorectx = Opt::baseopt.yyrestorectx;
        yyrestoretag = Opt::baseopt.yyrestoretag;
        yystagn = Opt::baseopt.yystagn;
        yystagp = Opt::baseopt.yystagp;
        yystagpd = Opt::baseopt.yystagpd;
        yymtagn = Opt::baseopt.yymtagn;
        yymtagp = Opt::baseopt.yymtagp;
        yymtagpd = Opt::baseopt.yymtagpd;
    }
    if (!dFlag)
    {
        yydebug = Opt::baseopt.yydebug;
    }
    if (!fill_use)
    {
        fill = Opt::baseopt.fill;
        fill_check = Opt::baseopt.fill_check;
        fill_arg = Opt::baseopt.fill_arg;
        fill_arg_use = Opt::baseopt.fill_arg_use;
        fill_naked = Opt::baseopt.fill_naked;
    }

    // force individual options
    switch (globopts->target) {
        case TARGET_DOT:
            iFlag = true;
            break;
        case TARGET_SKELETON:
            iFlag = true;
            input_api = INPUT_CUSTOM;
            indString = "    ";
            topIndent = 2;
            break;
        case TARGET_CODE:
            break;
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
    if (bFlag)
    {
        sFlag = true;
    }
    if (gFlag)
    {
        bFlag = true;
        sFlag = true;
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

const mutopt_t Opt::baseopt;

bool Opt::source (const char *s)
{
    if (source_file)
    {
        error ("multiple source files: %s, %s", source_file, s);
        return false;
    }
    else
    {
        source_file = s;
        return true;
    }
}

void Opt::reset_startlabel()
{
    set_startlabel(Opt::baseopt.startlabel);
    set_startlabel_force(Opt::baseopt.startlabel_force);
}

void Opt::reset_mapCodeName ()
{
    // historically arranged set of names
    // no actual reason why these particular options should be reset
    set_cond_get(Opt::baseopt.cond_get);
    set_cond_set(Opt::baseopt.cond_set);
    set_fill(Opt::baseopt.fill);
    set_state_get(Opt::baseopt.state_get);
    set_state_set(Opt::baseopt.state_set);
    set_yybackup(Opt::baseopt.yybackup);
    set_yybackupctx(Opt::baseopt.yybackupctx);
    set_yycondtype(Opt::baseopt.yycondtype);
    set_yyctxmarker(Opt::baseopt.yyctxmarker);
    set_yyctype(Opt::baseopt.yyctype);
    set_yycursor(Opt::baseopt.yycursor);
    set_yydebug(Opt::baseopt.yydebug);
    set_yylessthan(Opt::baseopt.yylessthan);
    set_yylimit(Opt::baseopt.yylimit);
    set_yymarker(Opt::baseopt.yymarker);
    set_yypeek(Opt::baseopt.yypeek);
    set_yyrestore(Opt::baseopt.yyrestore);
    set_yyrestorectx(Opt::baseopt.yyrestorectx);
    set_yyrestoretag(Opt::baseopt.yyrestoretag);
    set_yystagn(Opt::baseopt.yystagn);
    set_yystagp(Opt::baseopt.yystagp);
    set_yystagpd(Opt::baseopt.yystagpd);
    set_yymtagn(Opt::baseopt.yymtagn);
    set_yymtagp(Opt::baseopt.yymtagp);
    set_yymtagpd(Opt::baseopt.yymtagpd);
    set_yyskip(Opt::baseopt.yyskip);
    set_yyfilllabel(Opt::baseopt.yyfilllabel);
    set_yynext(Opt::baseopt.yynext);
    set_yyaccept(Opt::baseopt.yyaccept);
    set_yybm(Opt::baseopt.yybm);
    set_yych(Opt::baseopt.yych);
    set_yyctable(Opt::baseopt.yyctable);
    set_yytarget(Opt::baseopt.yytarget);
}

} // namespace re2c
