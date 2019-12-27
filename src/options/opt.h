#ifndef _RE2C_CONF_OPT_
#define _RE2C_CONF_OPT_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <vector>

#include "src/codegen/input_api.h"
#include "src/dfa/dfa.h"
#include "src/regexp/empty_class_policy.h"
#include "src/encoding/enc.h"
#include "src/util/forbid_copy.h"


namespace re2c {

class Msg;

enum target_t
{
    TARGET_CODE,
    TARGET_DOT,
    TARGET_SKELETON
};

const uint32_t NOEOF = ~0u - 1;

/* note [constant and mutable options]
 *
 * Some options are immutable (target, output files; global switches like
 * conditions, reuse mode, storable states; support of flex syntax, etc.).
 * These options are passed as command-line arguments and never change.
 * It is safe to read them from any program point after parsing command-line
 * arguments.
 *
 * Other options are configurable; they have block scope (may be specified
 * anywhere inside of the block and still affect the whole block).
 * Reading mutable options of yet unparsed block is not allowed because
 * they may affect the way RE2C parses current block (RE2C would be tempted
 * to base decisions on the latest option value, which may not be the final
 * one).
 */

#define RE2C_CONSTOPTS \
    CONSTOPT1 (target_t, target, TARGET_CODE) \
    CONSTOPT (bool, bNoGenerationDate, false) \
    CONSTOPT (bool, version, true) \
    CONSTOPT (bool, cFlag, false) \
    CONSTOPT (bool, fFlag, false) \
    CONSTOPT (bool, rFlag, false) \
    CONSTOPT (bool, FFlag, false) \
    CONSTOPT (bool, verbose, false) \
    /* include paths */ \
    CONSTOPT (std::vector<std::string>, incpaths, std::vector<std::string>()) \
    /* input encoding */ \
    CONSTOPT (Enc::type_t, input_encoding, Enc::ASCII) \
    /* internals */ \
    CONSTOPT (bool, dfa, true) \
    CONSTOPT (dfa_minimization_t, dfa_minimization, DFA_MINIMIZATION_MOORE) \
    CONSTOPT (posix_closure_t, posix_closure, POSIX_CLOSURE_GOR1) \
    CONSTOPT (posix_prectable_alg_t, posix_prectable, POSIX_PRECTABLE_COMPLEX) \
    CONSTOPT (bool, lookahead, true) \
    CONSTOPT (bool, eager_skip, false) \
    CONSTOPT (bool, optimize_tags, true) \
    CONSTOPT (bool, backward, false) \
    CONSTOPT (bool, stadfa, false) \
    /* debug */ \
    CONSTOPT (bool, dump_nfa, false) \
    CONSTOPT (bool, dump_dfa_raw, false) \
    CONSTOPT (bool, dump_dfa_det, false) \
    CONSTOPT (bool, dump_dfa_tagopt, false) \
    CONSTOPT (bool, dump_dfa_min, false) \
    CONSTOPT (bool, dump_adfa, false) \
    CONSTOPT (bool, dump_cfg, false) \
    CONSTOPT (bool, dump_interf, false) \
    CONSTOPT (bool, dump_closure_stats, false) \
    CONSTOPT (bool, dump_dfa_tree, false) \
    /* end */

#define RE2C_MUTOPTS \
    /* output files */ \
    MUTOPT1 (std::string, output_file, "") \
    MUTOPT (std::string, header_file, "") \
    /* regular expressions */ \
    MUTOPT (Enc, encoding, Enc ()) \
    MUTOPT (bool, bCaseInsensitive, false) \
    MUTOPT (bool, bCaseInverted, false) \
    MUTOPT (empty_class_policy_t, empty_class_policy, EMPTY_CLASS_MATCH_EMPTY) \
    /* conditions */ \
    MUTOPT (std::string, yycondtype, "YYCONDTYPE") \
    MUTOPT (std::string, cond_get, "YYGETCONDITION") \
    MUTOPT (bool, cond_get_naked, false) \
    MUTOPT (std::string, cond_set, "YYSETCONDITION" ) \
    MUTOPT (std::string, cond_set_arg, "@@" ) \
    MUTOPT (bool, cond_set_naked, false ) \
    MUTOPT (std::string, yyctable, "yyctable") \
    MUTOPT (std::string, condPrefix, "yyc_") \
    MUTOPT (std::string, condEnumPrefix, "yyc") \
    MUTOPT (std::string, condDivider, "/* *********************************** */") \
    MUTOPT (std::string, condDividerParam, "@@") \
    MUTOPT (std::string, condGoto, "goto @@;") \
    MUTOPT (std::string, condGotoParam, "@@") \
    /* states */ \
    MUTOPT (std::string, state_get, "YYGETSTATE") \
    MUTOPT (bool, state_get_naked, false) \
    MUTOPT (std::string, state_set, "YYSETSTATE") \
    MUTOPT (std::string, state_set_arg, "@@") \
    MUTOPT (bool, state_set_naked, false) \
    MUTOPT (std::string, yyfilllabel, "yyFillLabel") \
    MUTOPT (std::string, yynext, "yyNext") \
    MUTOPT (std::string, yyaccept, "yyaccept") \
    MUTOPT (bool, bUseStateAbort, false) \
    MUTOPT (bool, bUseStateNext, false) \
    /* tags */ \
    MUTOPT (bool, tags, false) \
    MUTOPT (std::string, tags_prefix, "yyt") \
    MUTOPT (std::string, tags_expression, "@@") \
    MUTOPT (bool, posix_syntax, false) \
    MUTOPT (bool, posix_semantics, false) \
    /* code generation */ \
    MUTOPT (bool, sFlag, false) \
    MUTOPT (bool, bFlag, false) \
    MUTOPT (std::string, yybm, "yybm") \
    MUTOPT (bool, yybmHexTable, false) \
    MUTOPT (bool, gFlag, false) \
    MUTOPT (std::string, yytarget, "yytarget") \
    MUTOPT (uint32_t, cGotoThreshold, 9) \
    MUTOPT (uint32_t, eof, NOEOF) \
    MUTOPT (uint32_t, sentinel, NOEOF) \
    /* formatting */ \
    MUTOPT (uint32_t, topIndent, 0) \
    MUTOPT (std::string, indString, "\t") \
    /* input API */ \
    MUTOPT (input_api_t, input_api, INPUT_DEFAULT) \
    MUTOPT (std::string, yycursor, "YYCURSOR") \
    MUTOPT (std::string, yymarker, "YYMARKER") \
    MUTOPT (std::string, yyctxmarker, "YYCTXMARKER") \
    MUTOPT (std::string, yylimit, "YYLIMIT") \
    MUTOPT (std::string, yypeek, "YYPEEK") \
    MUTOPT (std::string, yyskip, "YYSKIP") \
    MUTOPT (std::string, yybackup, "YYBACKUP") \
    MUTOPT (std::string, yybackupctx, "YYBACKUPCTX") \
    MUTOPT (std::string, yyrestore, "YYRESTORE") \
    MUTOPT (std::string, yyrestorectx, "YYRESTORECTX") \
    MUTOPT (std::string, yyrestoretag, "YYRESTORETAG") \
    MUTOPT (std::string, yylessthan, "YYLESSTHAN") \
    MUTOPT (std::string, yystagn, "YYSTAGN") \
    MUTOPT (std::string, yystagp, "YYSTAGP") \
    MUTOPT (std::string, yystagpd, "YYSTAGPD") \
    MUTOPT (std::string, yymtagn, "YYMTAGN") \
    MUTOPT (std::string, yymtagp, "YYMTAGP") \
    MUTOPT (std::string, yymtagpd, "YYMTAGPD") \
    /* #line directives */ \
    MUTOPT (bool, iFlag, false) \
    /* debug */ \
    MUTOPT (bool, dFlag, false) \
    MUTOPT (std::string, yydebug, "YYDEBUG") \
    /* yych */ \
    MUTOPT (std::string, yyctype, "YYCTYPE") \
    MUTOPT (std::string, yych, "yych") \
    MUTOPT (bool, bEmitYYCh, true) \
    MUTOPT (bool, yychConversion, false) \
    /* YYFILL */ \
    MUTOPT (std::string, fill, "YYFILL") \
    MUTOPT (bool, fill_use, true) \
    MUTOPT (bool, fill_check, true) \
    MUTOPT (std::string, fill_arg, "@@") \
    MUTOPT (bool, fill_arg_use, true) \
    MUTOPT (bool, fill_naked, false) \
    /* labels */ \
    MUTOPT (std::string, labelPrefix, "yy") \
    MUTOPT (std::string, startlabel, "") \
    MUTOPT (bool, startlabel_force, false) \
    /* end */

struct conopt_t
{
#    define CONSTOPT1 CONSTOPT
#    define CONSTOPT(type, name, value) type name;
    RE2C_CONSTOPTS
#    undef CONSTOPT1
#    undef CONSTOPT

    conopt_t()
#        define CONSTOPT1(type, name, value) : name(value)
#        define CONSTOPT(type, name, value)  , name(value)
        RE2C_CONSTOPTS
#        undef CONSTOPT1
#        undef CONSTOPT
    {}
    void fix();
    FORBID_COPY(conopt_t);
};

struct mutopt_t
{
#    define MUTOPT1 MUTOPT
#    define MUTOPT(type, name, value) type name;
    RE2C_MUTOPTS
#    undef MUTOPT1
#    undef MUTOPT

    mutopt_t()
#        define MUTOPT1(type, name, value) : name(value)
#        define MUTOPT(type, name, value)  , name(value)
        RE2C_MUTOPTS
#        undef MUTOPT1
#        undef MUTOPT
    {}
    void fix(const conopt_t *globopts);
    FORBID_COPY(mutopt_t);
};

struct opt_t
{
#    define CONSTOPT1 CONSTOPT
#    define CONSTOPT(type, name, value) type name;
    RE2C_CONSTOPTS
#    undef CONSTOPT1
#    undef CONSTOPT

#    define MUTOPT1 MUTOPT
#    define MUTOPT(type, name, value) type name;
    RE2C_MUTOPTS
#    undef MUTOPT1
#    undef MUTOPT

    opt_t(const conopt_t &con, const mutopt_t &mut)
#        define CONSTOPT1(type, name, value) : name(con.name)
#        define CONSTOPT(type, name, value)  , name(con.name)
        RE2C_CONSTOPTS
#        undef CONSTOPT1
#        undef CONSTOPT
#        define MUTOPT1 MUTOPT
#        define MUTOPT(type, name, value) , name(mut.name)
        RE2C_MUTOPTS
#        undef MUTOPT1
#        undef MUTOPT
    {}
};

// see note [constant and mutable options]
struct Opt
{
    static const mutopt_t baseopt;

    const char *source_file;
    const conopt_t &glob;

private:
    mutopt_t user;
    mutopt_t real;
    bool diverge;

    void sync()
    {
        if (!diverge) return;
#        define MUTOPT1 MUTOPT
#        define MUTOPT(type, name, value) real.name = user.name;
        RE2C_MUTOPTS
#        undef MUTOPT1
#        undef MUTOPT
        real.fix(&glob);
        diverge = false;
    }

public:
    explicit Opt(const conopt_t &globopts)
        : source_file(NULL)
        , glob(globopts)
        , user()
        , real()
        , diverge(true)
    {}

    const opt_t *snapshot()
    {
        sync();
        return new opt_t(glob, real);
    }

    void restore(const opt_t *opts)
    {
#        define MUTOPT1 MUTOPT
#        define MUTOPT(type, name, value) user.name = opts->name;
        RE2C_MUTOPTS
#        undef MUTOPT1
#        undef MUTOPT
        diverge = true;
        sync();
    }

    bool source (const char *s);

    // RE2C allows to set configurations anywhere inside of a block
    // (in the beginning, intermixed with rules, in the end): they will
    // affect the whole block anyway. Thus one is not allowed to read
    // configurations until the whole block has been parsed. Immutable
    // options, on the contrary, are accessible for reading all the time
    // (the parser itself depends on them).
    void set_encoding(Enc::type_t t)          { user.encoding.set(t); }
    void unset_encoding(Enc::type_t t)        { user.encoding.unset(t); }
    void set_encoding_policy(Enc::policy_t p) { user.encoding.setPolicy(p); }
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) void set_##name (const type &arg) { user.name = arg; diverge = true; }
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    // bad temporary hacks, should be fixed by proper scoping of config (parts).
    void reset_startlabel();
    void reset_mapCodeName ();

    FORBID_COPY (Opt);
};

enum parse_opts_t
{
    OK,
    EXIT_OK,
    EXIT_FAIL
};

parse_opts_t parse_opts(char **argv, conopt_t &globopts, Opt &opts, Msg &msg);

} // namespace re2c

#endif // _RE2C_CONF_OPT_
