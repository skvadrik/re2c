#ifndef _RE2C_CONF_OPT_
#define _RE2C_CONF_OPT_

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_set>

#include "src/constants.h"
#include "src/encoding/enc.h"
#include "src/options/symtab.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

// note [constant and mutable options]
//
// Some options are immutable (target, output files; global switches like conditions, reuse mode,
// storable states; support of flex syntax, etc.). These options are passed as command-line
// arguments and never change. It is safe to read them from any program point after parsing
// command-line arguments.
//
// Other options are configurable; they have block scope (may be specified anywhere inside of a
// block and still affect the whole block). Reading mutable options of yet unparsed block is not
// allowed because they may affect the way RE2C parses current block (RE2C would be tempted to base
// decisions on the latest option value, which may not be the final one).
//
// RE2C allows to set configurations anywhere inside of a block (in the beginning, intermixed with
// rules, in the end): they will affect the whole block anyway. Therefore it is not allowed to read
// configurations until the whole block has been parsed. Immutable options, on the other hand, are
// accessible for reading all the time (the parser itself depends on them).

class Input;
class Msg;
class Warn;
class RenderCallback;
class Scratchbuf;
struct StxCode;
using StxCodes = list_t<StxCode>;

#define RE2C_SIGIL "@@"
#define RE2C_YYFN_SEP ";"

// default backend is C

#ifndef RE2C_LANG
#define RE2C_LANG Lang::C
#endif

#ifndef RE2C_PROG
#define RE2C_PROG "re2c"
#endif

#define RE2C_CHECKED_LISTS \
    CHECKED_LIST(supported_apis, \
            ({"simple", "generic", "record"})) \
    CHECKED_LIST(supported_api_styles, \
            ({"free-form", "functions"})) \
    CHECKED_LIST(supported_code_models, \
            ({"goto-label", "loop-switch", "recursive-functions"})) \
    CHECKED_LIST(supported_targets, \
            ({"code", "dot", "skeleton"})) \
    CHECKED_LIST(supported_features, \
            ({"nested-ifs", "bitmaps", "computed-gotos", "case-ranges", "unsafe", "monadic", \
                "tags", "captures", "captvars"}))

#define RE2C_STX_OPTS \
    STX_OPT(bool, semicolons, false) \
    STX_OPT(bool, backtick_quoted_strings, false) \
    STX_OPT(bool, single_quoted_strings, false) \
    STX_OPT(bool, indentation_sensitive, false) \
    STX_OPT(bool, wrap_blocks_in_braces, false)

#define RE2C_CODE_TEMPLATES \
    CODE_TEMPLATE(var_local, \
        ({StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}), ({}), ({StxLOpt::INIT}) \
    ) \
    CODE_TEMPLATE(var_global, \
        ({StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}), ({}), ({StxLOpt::INIT}) \
    ) \
    CODE_TEMPLATE(const_local, \
        ({StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(const_global, \
        ({StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(array_local, \
        ({StxVarId::TYPE, StxVarId::NAME, StxVarId::SIZE}), \
        ({StxVarId::ROW, StxVarId::ELEM}), ({}) \
    ) \
    CODE_TEMPLATE(array_global, \
        ({StxVarId::TYPE, StxVarId::NAME, StxVarId::SIZE}), \
        ({StxVarId::ROW, StxVarId::ELEM}), ({}) \
    ) \
    CODE_TEMPLATE(array_elem, \
        ({StxVarId::ARRAY, StxVarId::INDEX}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(enum, \
        ({StxVarId::TYPE, StxVarId::INIT}), ({StxVarId::ELEM}), ({StxLOpt::INIT}) \
    ) \
    CODE_TEMPLATE(enum_elem, \
        ({StxVarId::NAME, StxVarId::TYPE}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(assign, \
        ({StxVarId::LHS, StxVarId::RHS}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(type_int, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(type_uint, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(type_yybm, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(type_yytarget, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(cmp_eq, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(cmp_ne, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(cmp_lt, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(cmp_gt, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(cmp_le, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(cmp_ge, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(if_then_else, \
        ({StxVarId::COND}), ({StxVarId::BRANCH, StxVarId::STMT}), ({StxLOpt::COND, StxLOpt::MANY}) \
    ) \
    CODE_TEMPLATE(if_then_else_oneline, \
        ({StxVarId::COND}), ({StxVarId::BRANCH, StxVarId::STMT}), ({StxLOpt::COND, StxLOpt::MANY}) \
    ) \
    CODE_TEMPLATE(switch, \
        ({StxVarId::EXPR}), ({StxVarId::CASE}), ({}) \
    ) \
    CODE_TEMPLATE(switch_cases, \
        ({}), ({StxVarId::CASE, StxVarId::STMT}), ({}) \
    ) \
    CODE_TEMPLATE(switch_cases_oneline, \
        ({}), ({StxVarId::CASE, StxVarId::STMT}), ({}) \
    ) \
    CODE_TEMPLATE(switch_case_range, \
        ({}), ({StxVarId::VAL}), ({StxLOpt::MANY, StxLOpt::CHAR_LITERALS}) \
    ) \
    CODE_TEMPLATE(switch_case_default, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(loop, \
        ({StxVarId::LABEL}), ({StxVarId::STMT}), ({}) \
    ) \
    CODE_TEMPLATE(continue, \
        ({StxVarId::LABEL}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(goto, \
        ({StxVarId::LABEL}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(fndecl, \
        ({StxVarId::NAME, StxVarId::TYPE, StxVarId::ARGNAME, StxVarId::ARGTYPE}), \
        ({StxVarId::ARG}), ({StxLOpt::TYPE}) \
    ) \
    CODE_TEMPLATE(fndef, \
        ({StxVarId::NAME, StxVarId::TYPE, StxVarId::ARGNAME, StxVarId::ARGTYPE}), \
        ({StxVarId::ARG, StxVarId::STMT}), ({StxLOpt::TYPE}) \
    ) \
    CODE_TEMPLATE(fncall, \
        ({StxVarId::NAME, StxVarId::RETVAL}), ({StxVarId::ARG}), \
        ({StxLOpt::ARGS, StxLOpt::RETVAL}) \
    ) \
    CODE_TEMPLATE(tailcall, \
        ({StxVarId::NAME}), ({StxVarId::ARG}), ({StxLOpt::ARGS, StxLOpt::RETVAL}) \
    ) \
    CODE_TEMPLATE(recursive_functions, \
        ({StxVarId::FNDECL, StxVarId::FNDEF}), ({StxVarId::FN}), ({}) \
    ) \
    CODE_TEMPLATE(fingerprint, \
        ({StxVarId::VER, StxVarId::DATE}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(line_info, \
        ({StxVarId::LINE, StxVarId::FILE}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(abort, \
        ({}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yydebug, \
        ({StxVarId::DEBUG, StxVarId::STATE, StxVarId::CHAR, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yypeek, \
        ({StxVarId::CHAR, StxVarId::CTYPE, StxVarId::PEEK, StxVarId::INPUT, StxVarId::CURSOR, \
            StxVarId::RECORD}), ({}), ({StxLOpt::CAST}) \
    ) \
    CODE_TEMPLATE(yyskip, \
        ({StxVarId::SKIP, StxVarId::CURSOR, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yybackup, \
        ({StxVarId::BACKUP, StxVarId::CURSOR, StxVarId::MARKER, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yybackupctx, \
        ({StxVarId::BACKUPCTX, StxVarId::CURSOR, StxVarId::CTXMARKER, StxVarId::RECORD}), \
        ({}), ({}) \
    ) \
    CODE_TEMPLATE(yyskip_yypeek, \
        ({StxVarId::CHAR, StxVarId::CTYPE, StxVarId::INPUT, StxVarId::CURSOR, StxVarId::RECORD}), \
        ({}), ({StxLOpt::CAST}) \
    ) \
    CODE_TEMPLATE(yypeek_yyskip, \
        ({StxVarId::CHAR, StxVarId::CTYPE, StxVarId::CURSOR, StxVarId::RECORD}), \
        ({}), ({StxLOpt::CAST}) \
    ) \
    CODE_TEMPLATE(yyskip_yybackup, \
        ({StxVarId::CURSOR, StxVarId::MARKER, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yybackup_yyskip, \
        ({StxVarId::CURSOR, StxVarId::MARKER, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yybackup_yypeek, \
        ({StxVarId::CHAR, StxVarId::CTYPE, StxVarId::INPUT, StxVarId::CURSOR, StxVarId::MARKER, \
            StxVarId::RECORD}), ({}), ({StxLOpt::CAST}) \
    ) \
    CODE_TEMPLATE(yyskip_yybackup_yypeek, \
        ({StxVarId::CHAR, StxVarId::CTYPE, StxVarId::INPUT, StxVarId::CURSOR, StxVarId::MARKER, \
            StxVarId::RECORD}), ({}), ({StxLOpt::CAST}) \
    ) \
    CODE_TEMPLATE(yybackup_yypeek_yyskip, \
        ({StxVarId::CHAR, StxVarId::CTYPE, StxVarId::INPUT, StxVarId::CURSOR, StxVarId::MARKER, \
            StxVarId::RECORD}), ({}), ({StxLOpt::CAST}) \
    ) \
    CODE_TEMPLATE(yyrestore, \
        ({StxVarId::RESTORE, StxVarId::CURSOR, StxVarId::MARKER, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yyrestorectx, \
        ({StxVarId::RESTORECTX, StxVarId::CURSOR, StxVarId::CTXMARKER, StxVarId::RECORD}), \
        ({}), ({}) \
    ) \
    CODE_TEMPLATE(yyrestoretag, \
        ({StxVarId::RESTORETAG, StxVarId::CURSOR, StxVarId::TAG, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yyshift, \
        ({StxVarId::SHIFT, StxVarId::CURSOR, StxVarId::OFFSET, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yyshiftstag, \
        ({StxVarId::SHIFTSTAG, StxVarId::TAG, StxVarId::NEG, StxVarId::OFFSET, StxVarId::RECORD}), \
        ({}), ({StxLOpt::NESTED}) \
    ) \
    CODE_TEMPLATE(yyshiftmtag, \
        ({StxVarId::SHIFTMTAG, StxVarId::TAG, StxVarId::OFFSET}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yystagp, \
        ({StxVarId::STAGP, StxVarId::TAG, StxVarId::CURSOR, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yymtagp, \
        ({StxVarId::MTAGP, StxVarId::TAG}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yystagn, \
        ({StxVarId::STAGN, StxVarId::TAG, StxVarId::NEG, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yymtagn, \
        ({StxVarId::MTAGN, StxVarId::TAG}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yycopystag, \
        ({StxVarId::COPYSTAG, StxVarId::LHS, StxVarId::RHS, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yycopymtag, \
        ({StxVarId::COPYMTAG, StxVarId::LHS, StxVarId::RHS, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yygetaccept, \
        ({StxVarId::GETACCEPT, StxVarId::VAR, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yysetaccept, \
        ({StxVarId::SETACCEPT, StxVarId::VAR, StxVarId::VAL, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yygetcond, \
        ({StxVarId::GETCOND, StxVarId::VAR, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yysetcond, \
        ({StxVarId::SETCOND, StxVarId::VAR, StxVarId::VAL, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yygetstate, \
        ({StxVarId::GETSTATE, StxVarId::VAR, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yysetstate, \
        ({StxVarId::SETSTATE, StxVarId::VAR, StxVarId::VAL, StxVarId::RECORD}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yylessthan, \
        ({StxVarId::LESSTHAN, StxVarId::NEED, StxVarId::CURSOR, StxVarId::LIMIT, \
            StxVarId::RECORD}), ({}), ({StxLOpt::MANY}) \
    ) \
    CODE_TEMPLATE(yybm_filter, \
        ({StxVarId::CHAR}), ({}), ({}) \
    ) \
    CODE_TEMPLATE(yybm_match, \
        ({StxVarId::BITMAP, StxVarId::CHAR, StxVarId::OFFSET, StxVarId::MASK}), ({}), ({}) \
    )

#define RE2C_ONELINE_CODES \
    ONELINE_CODE("code:abort", CodeKind::ABORT) \
    ONELINE_CODE("code:fncall", CodeKind::FNCALL) \
    ONELINE_CODE("code:goto", CodeKind::GOTO) \
    ONELINE_CODE("code:tailcall", CodeKind::FNCALL)

// configuration-local variables in syntax files
#define RE2C_STX_LOCAL_VARS \
    STX_LOCAL_VAR(ARG, "arg") \
    STX_LOCAL_VAR(ARGNAME, "argname") \
    STX_LOCAL_VAR(ARGTYPE, "argtype") \
    STX_LOCAL_VAR(ARRAY, "array") \
    STX_LOCAL_VAR(BRANCH, "branch") \
    STX_LOCAL_VAR(CASE, "case") \
    STX_LOCAL_VAR(COND, "cond") \
    STX_LOCAL_VAR(DATE, "date") \
    STX_LOCAL_VAR(ELEM, "elem") \
    STX_LOCAL_VAR(EXPR, "expr") \
    STX_LOCAL_VAR(FN, "fn") \
    STX_LOCAL_VAR(FILE, "file") \
    STX_LOCAL_VAR(FNDECL, "fndecl") \
    STX_LOCAL_VAR(FNDEF, "fndef") \
    STX_LOCAL_VAR(INDEX, "index") \
    STX_LOCAL_VAR(INIT, "init") \
    STX_LOCAL_VAR(LABEL, "label") \
    STX_LOCAL_VAR(LHS, "lhs") \
    STX_LOCAL_VAR(LINE, "line") \
    STX_LOCAL_VAR(MASK, "mask") \
    STX_LOCAL_VAR(NAME, "name") \
    STX_LOCAL_VAR(NEED, "need") \
    STX_LOCAL_VAR(NEG, "neg") \
    STX_LOCAL_VAR(OFFSET, "offset") \
    STX_LOCAL_VAR(RETVAL, "retval") \
    STX_LOCAL_VAR(RHS, "rhs") \
    STX_LOCAL_VAR(ROW, "row") \
    STX_LOCAL_VAR(SIGIL, "sigil") \
    STX_LOCAL_VAR(SIZE, "size") \
    STX_LOCAL_VAR(STATE, "state") \
    STX_LOCAL_VAR(STMT, "stmt") \
    STX_LOCAL_VAR(TAG, "tag") \
    STX_LOCAL_VAR(TYPE, "type") \
    STX_LOCAL_VAR(VAL, "val") \
    STX_LOCAL_VAR(VAR, "var") \
    STX_LOCAL_VAR(VER, "version") \
    /* vars for API primitives */ \
    STX_LOCAL_VAR(BACKUP, "YYBACKUP") \
    STX_LOCAL_VAR(BACKUPCTX, "YYBACKUPCTX") \
    STX_LOCAL_VAR(BITMAP, "yybm") \
    STX_LOCAL_VAR(CHAR, "yych") \
    STX_LOCAL_VAR(COPYMTAG, "YYCOPYMTAG") \
    STX_LOCAL_VAR(COPYSTAG, "YYCOPYSTAG") \
    STX_LOCAL_VAR(CTYPE, "YYCTYPE") \
    STX_LOCAL_VAR(CTXMARKER, "YYCTXMARKER") \
    STX_LOCAL_VAR(CURSOR, "YYCURSOR") \
    STX_LOCAL_VAR(DEBUG, "YYDEBUG") \
    STX_LOCAL_VAR(GETACCEPT, "YYGETACCEPT") \
    STX_LOCAL_VAR(GETCOND, "YYGETCOND") \
    STX_LOCAL_VAR(GETSTATE, "YYGETSTATE") \
    STX_LOCAL_VAR(INPUT, "YYINPUT") \
    STX_LOCAL_VAR(LESSTHAN, "YYLESSTHAN") \
    STX_LOCAL_VAR(LIMIT, "YYLIMIT") \
    STX_LOCAL_VAR(MARKER, "YYMARKER") \
    STX_LOCAL_VAR(MTAGN, "YYMTAGN") \
    STX_LOCAL_VAR(MTAGP, "YYMTAGP") \
    STX_LOCAL_VAR(PEEK, "YYPEEK") \
    STX_LOCAL_VAR(RECORD, "yyrecord") \
    STX_LOCAL_VAR(RESTORE, "YYRESTORE") \
    STX_LOCAL_VAR(RESTORECTX, "YYRESTORECTX") \
    STX_LOCAL_VAR(RESTORETAG, "YYRESTORETAG") \
    STX_LOCAL_VAR(SETACCEPT, "YYSETACCEPT") \
    STX_LOCAL_VAR(SETCOND, "YYSETCOND") \
    STX_LOCAL_VAR(SETSTATE, "YYSETSTATE") \
    STX_LOCAL_VAR(SHIFT, "YYSHIFT") \
    STX_LOCAL_VAR(SHIFTMTAG, "YYSHIFTMTAG") \
    STX_LOCAL_VAR(SHIFTSTAG, "YYSHIFTSTAG") \
    STX_LOCAL_VAR(SKIP, "YYSKIP") \
    STX_LOCAL_VAR(STAGN, "YYSTAGN") \
    STX_LOCAL_VAR(STAGP, "YYSTAGP")

// global variables in syntax files
#define RE2C_STX_GLOBAL_VARS \
    STX_GLOBAL_VAR(NEWLINE, "nl") \
    STX_GLOBAL_VAR(INDENT, "indent") \
    STX_GLOBAL_VAR(DEDENT, "dedent") \
    STX_GLOBAL_VAR(TOPINDENT, "topindent")

#define STX_LOCAL_VAR(id, name) id,
#define STX_GLOBAL_VAR(id, name) id,
enum class StxVarId : uint32_t {
    RE2C_STX_LOCAL_VARS
    RE2C_STX_GLOBAL_VARS
};
#undef STX_LOCAL_VAR
#undef STX_GLOBAL_VAR

// Immutable options (passed on the command line).
#define RE2C_CONSTOPTS \
    CONSTOPT(Target, target, Target::CODE) \
    CONSTOPT(CodeModel, code_model, CodeModel::GOTO_LABEL) \
    CONSTOPT(Enc::Type, input_encoding, Enc::Type::ASCII) \
    CONSTOPT(bool, date, true) \
    CONSTOPT(bool, version, true) \
    CONSTOPT(bool, start_conditions, false) \
    CONSTOPT(bool, storable_state, false) \
    CONSTOPT(bool, flex_syntax, false) \
    CONSTOPT(bool, verbose, false) \
    CONSTOPT(bool, line_dirs, true) \
    /* files */ \
    CONSTOPT(std::string, source_file, "") \
    CONSTOPT(std::string, output_file, "") \
    CONSTOPT(std::string, dep_file, "") \
    CONSTOPT(std::string, syntax_file, "") \
    CONSTOPT(std::vector<std::string>, include_paths, std::vector<std::string>()) \
    /* internals */ \
    CONSTOPT(Minimization, minimization, Minimization::MOORE) \
    CONSTOPT(PosixPrectable, posix_prectable, PosixPrectable::COMPLEX) \
    CONSTOPT(FixedTags, fixed_tags, FixedTags::ALL) \
    CONSTOPT(bool, optimize_tags, true) \
    CONSTOPT(bool, nested_negative_tags, true) \
    CONSTOPT(bool, eager_skip, false) \
    /* debug */ \
    CONSTOPT(bool, dump_nfa, false) \
    CONSTOPT(bool, dump_dfa_raw, false) \
    CONSTOPT(bool, dump_dfa_det, false) \
    CONSTOPT(bool, dump_dfa_tagopt, false) \
    CONSTOPT(bool, dump_dfa_min, false) \
    CONSTOPT(bool, dump_adfa, false) \
    CONSTOPT(bool, dump_cfg, false) \
    CONSTOPT(bool, dump_interf, false) \
    CONSTOPT(bool, dump_closure_stats, false) \
    CONSTOPT(bool, dump_dfa_tree, false) \
    /* end */

// Mutable options (configurations) can be set anywhere in a block.
// They may depend on immutable options, but not on other mutable options.
#define RE2C_MUTOPTS \
    /* files */ \
    MUTOPT(std::string, header_file, "") \
    /* regular expressions */ \
    MUTOPT(Enc,  encoding, Enc()) \
    MUTOPT(bool, case_insensitive, false) \
    MUTOPT(bool, case_inverted, false) \
    MUTOPT(EmptyClass, empty_class, EmptyClass::MATCH_EMPTY) \
    /* API */ \
    MUTOPT(Api, api, Api::GENERIC) \
    MUTOPT(ApiStyle, api_style, ApiStyle::FUNCTIONS) \
    MUTOPT(std::string, api_sigil, RE2C_SIGIL) \
    /* variables */ \
    MUTOPT(std::string, var_accept, "yyaccept") \
    MUTOPT(std::string, var_bitmaps, "yybm") \
    MUTOPT(std::string, var_computed_gotos_table, "yytarget") \
    MUTOPT(std::string, var_char, "yych") \
    MUTOPT(std::string, var_cond, "yycond") \
    MUTOPT(std::string, var_cond_table, "yyctable") \
    MUTOPT(std::string, var_fill, "") \
    MUTOPT(std::string, var_state, "yystate") \
    MUTOPT(std::string, var_nmatch, "yynmatch") \
    MUTOPT(std::string, var_pmatch, "yypmatch") \
    MUTOPT(std::string, var_record, "yyrecord") \
    /* code generation */ \
    MUTOPT(bool, bitmaps, false) \
    MUTOPT(bool, bitmaps_hex, false) \
    MUTOPT(bool, case_ranges, false) \
    MUTOPT(bool, computed_gotos, false) \
    MUTOPT(uint32_t, computed_gotos_threshold, 9) \
    MUTOPT(bool, nested_ifs, false) \
    MUTOPT(bool, unsafe, true) \
    MUTOPT(bool, monadic, false) \
    /* YYFILL */ \
    MUTOPT(uint32_t, fill_eof, NOEOF) \
    MUTOPT(uint32_t, fill_sentinel, NOEOF) \
    MUTOPT(bool, fill_enable, true) \
    MUTOPT(bool, fill_check, true) \
    MUTOPT(std::string, fill_param, RE2C_SIGIL) \
    MUTOPT(bool, fill_param_enable, true) \
    MUTOPT(bool, fill_naked, false) \
    /* yych */ \
    MUTOPT(bool, char_emit, true) \
    MUTOPT(bool, char_conv, false) \
    MUTOPT(CharLit, char_literals, CharLit::CHAR_OR_HEX) \
    /* conditions */ \
    MUTOPT(bool, cond_abort, false) \
    MUTOPT(bool, cond_get_naked, false) \
    MUTOPT(std::string, cond_set_param, RE2C_SIGIL ) \
    MUTOPT(bool, cond_set_naked, false ) \
    MUTOPT(std::string, cond_label_prefix, "yyc_") \
    MUTOPT(std::string, cond_enum_prefix, "yyc") \
    MUTOPT(std::string, cond_div_param, RE2C_SIGIL) \
    MUTOPT(std::string, cond_goto_param, RE2C_SIGIL) \
    /* states */ \
    MUTOPT(bool, state_get_naked, false) \
    MUTOPT(std::string, state_set_param, RE2C_SIGIL) \
    MUTOPT(bool, state_set_naked, false) \
    MUTOPT(bool, state_abort, false) \
    MUTOPT(bool, state_next, false) \
    /* tags */ \
    MUTOPT(bool, tags, false) \
    MUTOPT(bool, tags_automatic, false) \
    MUTOPT(bool, tags_history, false) \
    MUTOPT(bool, captures, false) \
    MUTOPT(bool, captures_posix, false) \
    MUTOPT(bool, captures_array, false) \
    MUTOPT(bool, captures_invert, false) \
    MUTOPT(std::string, tags_prefix, "yyt") \
    /* functions */ \
    MUTOPT(std::vector<std::string>, api_fn, \
            {"<undefined-fn-name>" RE2C_YYFN_SEP "<undefined-fn-type>"}) \
    MUTOPT(std::string, fn_sep, ";") \
    /* labels */ \
    MUTOPT(std::string, label_fill, "yyFillLabel") \
    MUTOPT(std::string, label_loop, "") \
    MUTOPT(std::string, label_next, "yyNext") \
    MUTOPT(std::string, label_prefix, "yy") \
    MUTOPT(std::string, label_start, "") \
    MUTOPT(bool, label_start_force, false) \
    /* formatting */ \
    MUTOPT(uint32_t, indent_top, 0) \
    MUTOPT(std::string, indent_str, "\t") \
    /* debug */ \
    MUTOPT(bool, debug, false) \
    /* end */

// Mutable code templates may depend on other options (both mutable and immutable ones).
// In source files their value is a string; in syntax files it is a code template (the latter
// allows one to set API defauls conditionally based on the chosen API, style, sigil etc.).
#define RE2C_MUTCODES \
    MUTCODE(api_char_type) \
    MUTCODE(api_cond_type) \
    MUTCODE(api_input) \
    MUTCODE(api_cursor) \
    MUTCODE(api_marker) \
    MUTCODE(api_ctxmarker) \
    MUTCODE(api_limit) \
    MUTCODE(api_maxfill) \
    MUTCODE(api_maxnmatch) \
    MUTCODE(api_peek) \
    MUTCODE(api_skip) \
    MUTCODE(api_backup) \
    MUTCODE(api_backup_ctx) \
    MUTCODE(api_restore) \
    MUTCODE(api_restore_ctx) \
    MUTCODE(api_restore_tag) \
    MUTCODE(api_less_than) \
    MUTCODE(api_stag_neg) \
    MUTCODE(api_stag_pos) \
    MUTCODE(api_mtag_neg) \
    MUTCODE(api_mtag_pos) \
    MUTCODE(api_stag_copy) \
    MUTCODE(api_mtag_copy) \
    MUTCODE(api_shift) \
    MUTCODE(api_stag_shift) \
    MUTCODE(api_mtag_shift) \
    MUTCODE(api_fill) \
    MUTCODE(api_cond_get) \
    MUTCODE(api_cond_set) \
    MUTCODE(api_state_get) \
    MUTCODE(api_state_set) \
    MUTCODE(api_accept_get) \
    MUTCODE(api_accept_set) \
    MUTCODE(api_debug) \
    MUTCODE(tags_expression) \
    MUTCODE(tags_negative) \
    MUTCODE(cond_div) \
    MUTCODE(cond_goto) \
    /* end */

#define CODE_TEMPLATE(name, vars, list_vars, conds) STX_##name,
#define MUTCODE(name) STX_##name,
enum class StxCodeId : uint32_t {
    RE2C_CODE_TEMPLATES
    RE2C_MUTCODES
};
#undef CODE_TEMPLATE
#undef MUTCODE

enum class StxOptKind {GLOB, LOC, IMM, NEG, AND, OR};

struct StxOpt {
    StxOptKind kind;
    union {
        StxGOpt gopt;
        StxLOpt lopt;
        bool imm;
        StxOpt* neg;
        struct {
            StxOpt* lhs;
            StxOpt* rhs;
        } op;
    };
};

struct StxCodeCond {
    StxOpt* opt;
    StxCodes* then_code;
    StxCodes* else_code;
};

struct StxCodeList {
    StxVarId var;
    int32_t lbound;
    int32_t rbound;
    StxCodes* code;
};

enum class StxCodeType {STR, VAR, COND, LIST, UD};

struct StxCode {
    StxCodeType type;
    union {
        const char* str;
        StxVarId var;
        StxCodeCond cond;
        StxCodeList list;
    };
    StxCode* next;
};

bool is_undefined(const StxCodes* code);

// Constant options.
struct conopt_t {
    // Global options are public (for easier read access), but constant (to avoid
    // accidental write access, as this should be done by `set_*` methods that correctly
    // update `is_default_*` status).
#define CONSTOPT(type, name, value) const type name; bool is_default_##name;
    RE2C_CONSTOPTS
#undef CONSTOPT
    // Syntax file options.
#define CHECKED_LIST(name, allowed) const std::vector<std::string> name;
    RE2C_CHECKED_LISTS
#undef CHECKED_LIST
#define STX_OPT(type, name, value) const type name;
    RE2C_STX_OPTS
#undef STX_OPT
#define CODE_TEMPLATE(name, vars, list_vars, conds) const StxCodes* code_##name;
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE
    bool p2067; // until c++ allows trailing comma in macro-expanded ctor-intializer

    conopt_t() :
#define CONSTOPT(type, name, value) name(value), is_default_##name(true),
    RE2C_CONSTOPTS
#undef CONSTOPT
#define CHECKED_LIST(name, allowed) name(),
    RE2C_CHECKED_LISTS
#undef CHECKED_LIST
#define STX_OPT(type, name, value) name(value),
    RE2C_STX_OPTS
#undef STX_OPT
#define CODE_TEMPLATE(name, vars, list_vars, conds) code_##name(nullptr),
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE
    p2067() {}

#define CONSTOPT(type, name, value) \
    void set_##name(const type & val) { \
        const_cast<type&>(name) = val; \
        is_default_##name = false; \
    } \
    void init_##name(const type &arg) { \
        if (is_default_##name) { \
            const_cast<type&>(name) = arg; \
        } \
    }
    RE2C_CONSTOPTS
#undef CONSTOPT
#define CHECKED_LIST(name, allowed) \
    bool name##_contains(const std::string& what) const { \
        return name.end() != std::find(name.begin(), name.end(), what); \
    }
    RE2C_CHECKED_LISTS
#undef CHECKED_LIST
#define CODE_TEMPLATE(name, vars, list_vars, conds) \
    bool have_conf_code_##name() const { \
        return !is_undefined(code_##name); \
    }
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE

    FORBID_COPY(conopt_t);
};

// Mutable options.
struct mutopt_t {
#define MUTOPT(type, name, value) type name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) const StxCodes* name;
    RE2C_MUTCODES
#undef MUTCODE
    bool p2067; // until c++ allows trailing comma in macro-expanded ctor-intializer

    mutopt_t() :
#define MUTOPT(type, name, value) name(value),
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) name(nullptr),
    RE2C_MUTCODES
#undef MUTCODE
    p2067() {}

    FORBID_COPY(mutopt_t);
};

// Boolean flags for mutable options.
struct mutdef_t {
#define MUTOPT(type, name, value) bool name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) bool name;
    RE2C_MUTCODES
#undef MUTCODE
    bool p2067; // until c++ allows trailing comma in macro-expanded ctor-intializer

    mutdef_t() :
#define MUTOPT(type, name, value) name(true),
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) name(true),
    RE2C_MUTCODES
#undef MUTCODE
    p2067() {}
};

// Union of constant and mutable options and default flags.
struct opt_t {
  private:
    using stack_code_t = std::vector<std::pair<const StxCode*, uint8_t>>;

    // stack is placed here to avoid reallocating it every time
    mutable stack_code_t stack_code;

  public:
#define CONSTOPT(type, name, value) type name;
    RE2C_CONSTOPTS
#undef CONSTOPT
#define CHECKED_LIST(name, allowed) const std::vector<std::string> name;
    RE2C_CHECKED_LISTS
#undef CHECKED_LIST
#define STX_OPT(type, name, value) const type name;
    RE2C_STX_OPTS
#undef STX_OPT
#define CODE_TEMPLATE(name, vars, list_vars, conds) const StxCodes* code_##name;
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE
#define MUTOPT(type, name, value) type name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) std::string name; const StxCodes* code_##name;
    RE2C_MUTCODES
#undef MUTCODE
#define MUTOPT(type, name, value) bool is_default_##name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) bool is_default_##name;
    RE2C_MUTCODES
#undef MUTCODE
    symtab_t symtab;

    opt_t(const conopt_t& con, const mutopt_t& mut, const mutdef_t& def, const symtab_t& symtab)
        : stack_code(),
#define CONSTOPT(type, name, value) name(con.name),
    RE2C_CONSTOPTS
#undef CONSTOPT
#define CHECKED_LIST(name, allowed) name(con.name),
    RE2C_CHECKED_LISTS
#undef CHECKED_LIST
#define STX_OPT(type, name, value) name(con.name),
    RE2C_STX_OPTS
#undef STX_OPT
#define CODE_TEMPLATE(name, vars, list_vars, conds) code_##name(con.code_##name),
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE
#define MUTOPT(type, name, value) name(mut.name),
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) name(this->gen_##name(mut.name)), code_##name(mut.name),
    RE2C_MUTCODES
#undef MUTCODE
#define MUTOPT(type, name, value) is_default_##name(def.name),
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) is_default_##name(def.name),
    RE2C_MUTCODES
#undef MUTCODE
    symtab(symtab) {}

#define CODE_TEMPLATE(name, vars, list_vars, conds) \
    const char* gen_code_##name(Scratchbuf& buf, RenderCallback& callback) const; \
    const char* gen_code_##name(Scratchbuf& buf) const; \
    void render_code_##name(std::ostream& os, RenderCallback& callback) const; \
    void render_code_##name(std::ostream& os) const;
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE
#define MUTCODE(name) \
    std::string gen_##name(const StxCodes* code) const;
    RE2C_MUTCODES
#undef MUTCODE
    bool specialize_oneline_if() const {
        return !is_undefined(code_if_then_else_oneline);
    }
    bool specialize_oneline_switch() const {
        return !is_undefined(code_switch_cases_oneline);
    }
    bool specialize_skip_peek_backup() const {
        return !is_undefined(code_yyskip_yypeek)
            && !is_undefined(code_yypeek_yyskip)
            && !is_undefined(code_yyskip_yybackup)
            && !is_undefined(code_yybackup_yyskip)
            && !is_undefined(code_yybackup_yypeek)
            && !is_undefined(code_yyskip_yybackup_yypeek)
            && !is_undefined(code_yybackup_yypeek_yyskip);
    }

  private:
    void eval_code_conf(StxCodeId id, const char* name, const StxCodes* code,
        std::ostream& os) const;
    void eval_code_conf(StxCodeId id, const char* name, const StxCodes* code,
        std::ostream& os, RenderCallback& callback) const;
    void push_list_on_stack(const StxCode* x) const;

    FORBID_COPY(opt_t);
};

// Options management.
struct Opt {
  private:
    using stack_code_t = std::vector<std::pair<const StxCode*, uint8_t>>;
    using stack_code_list_t = std::vector<const StxCode*>;

  public:
    const conopt_t glob;
    symtab_t symtab;
    Msg& msg;

  private:
    OutAllocator& alc;

    // Default mutable options. They depend on the global options, such as the language backend, and
    // are fixed after parsing the global options.
    const mutopt_t defaults;

    // Boolean flags indicating if a mutable option has been set by the user. These are needed to
    // distingush default values from user-set values that coincide with default ones. Constant and
    // mutable options passed on the command line may be intermixed (there is no ordering
    // requirement), so mutable options may be applied before all constant options are known and
    // default values for mutable options are determined. Such user-set mutable options should not
    // be altered by fixing default options.
    mutdef_t is_default;

    // User-set mutable options.
    mutopt_t user;

    // Real mutable options ("fixed" user-set options with various filters and implications that
    // make options consistent).
    mutopt_t real;

    // If user-set options have diverged from the real ones and need syncing.
    bool diverge;

    // stacks are placed here to avoid reallocating them every time
    stack_code_t stack_code;
    stack_code_list_t stack_code_list;

  public:
    Opt(OutAllocator& alc, Msg& msg);
    const conopt_t& global() const { return glob; }
    Ret parse(char** argv, Input& input, Lang lang);
    Ret snapshot(const opt_t** opts) NODISCARD;
    Ret fix_global_and_defaults() NODISCARD;
    Ret restore(const opt_t* opts) NODISCARD;
    Ret merge(const opt_t* opts, Input& input) NODISCARD;

#define MUTOPT(type, name, value) \
    void init_##name(const type &arg); \
    void set_##name(const type &arg); \
    void reset_##name();
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTCODE(name) \
    void init_##name(const StxCodes* arg); \
    void set_##name(const StxCodes* arg);
    RE2C_MUTCODES
#undef MUTCODE
#define CHECKED_LIST(name, allowed) \
    void set_##name(const std::vector<std::string>& list); \
    Ret check_##name() NODISCARD;
    RE2C_CHECKED_LISTS
#undef CHECKED_LIST
#define STX_OPT(type, name, value) \
    void set_##name(const type & val);
    RE2C_STX_OPTS
#undef STX_OPT
#define CODE_TEMPLATE(name, vars, list_vars, conds) \
    /* void set_code_##name(const StxCodes* code); */ \
    Ret check_code_##name(Warn& warn) NODISCARD;
    RE2C_CODE_TEMPLATES
#undef CODE_TEMPLATE
    void init_encoding(Enc::Type type, bool on);
    void init_encoding_policy(Enc::Policy p);
    void set_encoding(Enc::Type type, bool on);
    void set_encoding_policy(Enc::Policy p);

    void reset_group_label_start();

    StxCodes* new_code_list();
    StxCode* make_code_str(const char* str);
    StxCode* make_code_var(StxVarId id);
    StxCode* make_code_cond(StxOpt* opt, StxCodes* code_then, StxCodes* code_else);
    StxCode* make_code_list(StxVarId var, int32_t lbound, int32_t rbound, StxCodes* code);
    StxCodes* make_code_undefined();
    StxOpt* make_opt_global(StxGOpt opt);
    StxOpt* make_opt_local(StxLOpt opt);
    StxOpt* make_opt_imm(bool b);
    StxOpt* make_opt_neg(StxOpt* x);
    StxOpt* make_opt_and(StxOpt* x, StxOpt* y);
    StxOpt* make_opt_or(StxOpt* x, StxOpt* y);
    StxCodes* make_api(const std::string& str);

    Ret validate_conf_code(
        const StxCodes* code,
        const char* conf,
        const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars,
        const std::unordered_set<StxLOpt>& conds) NODISCARD;

  private:
    Ret sync() NODISCARD;

    static const char* var_name(StxVarId id);

    StxCode* make_code(StxCodeType type);

    Ret check_cond(StxLOpt opt, const char* conf, const std::unordered_set<StxLOpt>& conds) const;
    Ret check_var(StxVarId var, const char* conf, const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars) const;

    FORBID_COPY(Opt);
};

Ret parse_opts(char** argv, conopt_t& globopts, Opt& opts, Msg& msg) NODISCARD;

} // namespace re2c

namespace std {

// Some toolchains require `std::hash` specialization for `std::unordered_set`.
#define GEN_STD_HASH(type) \
template<> struct hash<type> { \
    size_t operator()(type v) const { \
        hash<uint32_t> h; \
        return h(static_cast<uint32_t>(v)); \
    } \
}
GEN_STD_HASH(re2c::StxVarId);
GEN_STD_HASH(re2c::StxLOpt);
GEN_STD_HASH(re2c::CodeKind);
#undef GEN_STD_HASH

} // namespace std

#endif // _RE2C_CONF_OPT_
