#ifndef _RE2C_CODE_OUTPUT_
#define _RE2C_CODE_OUTPUT_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string.h>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "src/codegen/label.h"
#include "src/debug/debug.h"
#include "src/msg/location.h"
#include "src/util/counter.h"
#include "src/util/forbid_copy.h"
#include "src/util/slab_allocator.h"
#include "src/util/uniq_vector.h"


namespace re2c {

class Msg;
struct Opt;
struct opt_t;
template <typename value_t> class uniq_vector_t;

// need 8-byte alignment to allocate structs with pointers and 64-bit integers
typedef slab_allocator_t<1024 * 1024, 8> code_alc_t;

class Scratchbuf {
    code_alc_t &alc;
    std::ostringstream os;

public:
    explicit Scratchbuf(code_alc_t &alc): alc(alc), os() {}
    bool empty() const { return os.str().empty(); }
    std::ostringstream &stream() { return os; }
    const char *flush();
    Scratchbuf& u32(uint32_t u) { os << u; return *this; }
    Scratchbuf& u64(uint64_t u) { os << u; return *this; }
    Scratchbuf& str(const std::string &s) { os << s; return *this; }
    Scratchbuf& cstr(const char *s) { os << s; return *this; }
    Scratchbuf& label(const label_t &l) { os << l; return *this; }
    Scratchbuf& u32_hex(uint32_t u, const opt_t *opts);
    Scratchbuf& u32_width(uint32_t u, int width);
};

// forward decls
struct CodeStmt;
struct CodeCase;

typedef const char *CodeText;

struct CodeStmts {
    CodeStmt *head;
    CodeStmt **ptail;
};

struct CodeIfTE {
    CodeText   if_cond;
    CodeText   else_cond;
    CodeStmts *if_code;
    CodeStmts *else_code;
    bool       oneline;
};

struct CodeCase {
    enum Kind {
        CHARS,
        NUMBER,
        STRING,
        DEFAULT
    } kind;

    struct Chars {
        size_t     nranges;
        uint32_t  *ranges;
    };

    union {
        Chars       chars;
        int32_t     number;
        const char *string;
    };
    CodeStmts *body;
    CodeCase  *next;
};

struct CodeCases {
    CodeCase  *head;
    CodeCase **ptail;
};

struct CodeSwitch {
    CodeText   expr;
    CodeCases *cases;
    bool       impdef;
};

struct CodeBlock {
    enum Fmt {
        WRAPPED,
        INDENTED,
        RAW
    };

    CodeStmts *stmts;
    Fmt        fmt;
};

struct CodeVar {
    const char *type;
    const char *name;
    const char *init;
};

struct CodeTags {
    const char *fmt;
    const char *sep;
};

struct CodeRaw {
    const char *data;
    size_t      size;
};

struct CodeStmt {
    enum Kind {
        EMPTY,
        IF_THEN_ELSE,
        SWITCH,
        BLOCK,
        SKIP,
        PEEK,
        BACKUP,
        PEEK_SKIP,
        SKIP_PEEK,
        SKIP_BACKUP,
        BACKUP_SKIP,
        BACKUP_PEEK,
        BACKUP_PEEK_SKIP,
        SKIP_BACKUP_PEEK,
        LINE_INFO_INPUT,
        LINE_INFO_OUTPUT,
        COND_ENUM,
        COND_GOTO,
        COND_TABLE,
        STATE_GOTO,
        STAGS,
        MTAGS,
        YYMAXFILL,
        YYMAXNMATCH,
        YYCH,
        YYACCEPT,
        VAR,
        TEXT,
        TEXT_RAW,
        VERBATIM,
        RAW
    } kind;

    union {
        CodeIfTE   ifte;
        CodeSwitch swch;
        CodeBlock  block;
        CodeText   text;
        CodeRaw    raw;
        CodeVar    var;
        CodeTags   tags;
        loc_t      loc;
    };

    CodeStmt *next;
};

inline CodeStmt *code_stmt(code_alc_t &alc, CodeStmt::Kind kind)
{
    CodeStmt *s = alc.alloct<CodeStmt>(1);
    s->kind = kind;
    s->next = NULL;
    return s;
}

inline CodeStmt *code_stmt_text(code_alc_t &alc, CodeText text)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::TEXT);
    s->text = text;
    return s;
}

inline CodeStmt *code_verbatim(code_alc_t &alc, CodeText text)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::VERBATIM);
    s->text = text;
    return s;
}

inline CodeStmt *code_raw(code_alc_t &alc, const char *data, size_t size)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::RAW);
    char *copy = alc.alloct<char>(size);
    memcpy(copy, data, size);
    s->raw.size = size;
    s->raw.data = copy;
    return s;
}

inline CodeStmt *code_stmt_textraw(code_alc_t &alc, CodeText text)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::TEXT_RAW);
    s->text = text;
    return s;
}

inline CodeStmt *code_tags(code_alc_t &alc,
    const std::string &fmt, const std::string &sep, bool mtags)
{
    CodeStmt *s = code_stmt(alc, mtags ? CodeStmt::MTAGS : CodeStmt::STAGS);

    char *fmt_copy = alc.alloct<char>(fmt.length() + 1);
    strcpy(fmt_copy, fmt.c_str());
    s->tags.fmt = fmt_copy;

    char *sep_copy = alc.alloct<char>(sep.length() + 1);
    strcpy(sep_copy, sep.c_str());
    s->tags.sep = sep_copy;

    return s;
}

inline CodeStmt *code_yymaxfill(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::YYMAXFILL);
}

inline CodeStmt *code_yymaxnmatch(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::YYMAXNMATCH);
}

inline CodeStmt *code_cond_enum(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::COND_ENUM);
}

inline CodeStmt *code_cond_table(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::COND_TABLE);
}

inline CodeStmt *code_cond_goto(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::COND_GOTO);
}

inline CodeStmt *code_state_goto(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::STATE_GOTO);
}

inline CodeStmt *code_line_info_input(code_alc_t &alc, const loc_t &loc)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::LINE_INFO_INPUT);
    s->loc = loc;
    return s;
}

inline CodeStmt *code_yych_decl(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::YYCH);
}

inline CodeStmt *code_yyaccept_def(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::YYACCEPT);
}

inline CodeStmt *code_line_info_output(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::LINE_INFO_OUTPUT);
}

inline CodeStmt *code_stmt_skip(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::SKIP);
}

inline CodeStmt *code_stmt_peek(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::PEEK);
}

inline CodeStmt *code_stmt_backup(code_alc_t &alc)
{
    return code_stmt(alc, CodeStmt::BACKUP);
}

inline CodeStmt *code_block(code_alc_t &alc, CodeStmts *stmts, CodeBlock::Fmt fmt)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::BLOCK);
    s->block.stmts = stmts;
    s->block.fmt   = fmt;
    return s;
}

inline CodeStmt *code_stmt_if_then_else(code_alc_t &alc, CodeText if_cond,
    CodeStmts *if_code, CodeStmts *else_code, bool oneline = true)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::IF_THEN_ELSE);
    s->ifte.if_cond   = if_cond;
    s->ifte.else_cond = NULL;
    s->ifte.if_code   = if_code;
    s->ifte.else_code = else_code;
    s->ifte.oneline   = oneline;
    return s;
}

inline CodeStmt *code_stmt_if_then_elif(code_alc_t &alc, CodeText if_cond,
    CodeStmts *if_code, CodeText else_cond, CodeStmts *else_code)
{
    CodeStmt *s = code_stmt_if_then_else(alc, if_cond, if_code, else_code, false);
    s->ifte.else_cond = else_cond;
    return s;
}

inline CodeCase *code_case_default(code_alc_t &alc, CodeStmts *body)
{
    CodeCase *s = alc.alloct<CodeCase>(1);
    s->kind = CodeCase::DEFAULT;
    s->body = body;
    s->next = NULL;
    return s;
}

inline CodeCase *code_case_number(code_alc_t &alc, CodeStmts *body, int32_t number)
{
    CodeCase *s = alc.alloct<CodeCase>(1);
    s->kind = CodeCase::NUMBER;
    s->number = number;
    s->body = body;
    s->next = NULL;
    return s;
}

inline CodeCase *code_case_string(code_alc_t &alc, CodeStmts *body, const char *string)
{
    CodeCase *s = alc.alloct<CodeCase>(1);
    s->kind = CodeCase::STRING;
    s->string = string;
    s->body = body;
    s->next = NULL;
    return s;
}

inline CodeCase *code_case_chars(code_alc_t &alc, CodeStmts *body,
    const std::vector<std::pair<uint32_t, uint32_t> > &ranges)
{
    CodeCase *s = alc.alloct<CodeCase>(1);
    s->kind = CodeCase::CHARS;

    const size_t n = ranges.size();
    uint32_t *rs = alc.alloct<uint32_t>(2 * n);
    for (uint32_t i = 0; i < n; ++i) {
        rs[2 * i]     = ranges[i].first;
        rs[2 * i + 1] = ranges[i].second;
    }
    s->chars.nranges = n;
    s->chars.ranges  = rs;

    s->body = body;
    s->next = NULL;
    return s;
}

inline CodeCases *code_cases(code_alc_t &alc)
{
    CodeCases *c = alc.alloct<CodeCases>(1);
    c->head  = NULL;
    c->ptail = &c->head;
    return c;
}

inline void append_case(CodeCases *cases, CodeCase *ccase)
{
    DASSERT(ccase);
    *cases->ptail = ccase;
    cases->ptail  = &ccase->next;
}

inline CodeStmt *code_switch(code_alc_t &alc, CodeText expr, CodeCases *cases,
    bool impdef)
{
    CodeStmt *s = code_stmt(alc, CodeStmt::SWITCH);
    s->swch.expr   = expr;
    s->swch.cases  = cases;
    s->swch.impdef = impdef;
    return s;
}

inline CodeStmts *code_stmts(code_alc_t &alc)
{
    CodeStmts *s = alc.alloct<CodeStmts>(1);
    s->head = NULL;
    s->ptail = &s->head;
    return s;
}

inline void append_stmt(CodeStmts *stmts, CodeStmt *stmt)
{
    DASSERT(stmt);
    *stmts->ptail = stmt;
    stmts->ptail = &stmt->next;
}

inline void prepend_stmt(CodeStmts *stmts, CodeStmt *stmt)
{
    DASSERT(stmt);
    stmt->next = stmts->head;
    stmts->head = stmt;
}

inline void append_stmts(CodeStmts *stmts1, CodeStmts *stmts2)
{
    if (stmts2 && stmts2->head) {
        *stmts1->ptail = stmts2->head;
        for (; *(stmts1->ptail); stmts1->ptail = &(*stmts1->ptail)->next);
    }
}

struct CodegenContext {
    code_alc_t &allocator;
    Scratchbuf &scratchbuf;
    const opt_t *globopts;
    const opt_t *opts;
    Msg &msg;
    const loc_t &loc;
    const uniq_vector_t<std::string> &allcondnames;
    const std::set<std::string> &allstags;
    const std::set<std::string> &allmtags;
    const std::vector<std::string> &condnames;
    const size_t maxfill;
    const size_t maxnmatch;
    const uint32_t fillidx;
    const bool used_yyaccept;
    const bool warn_cond_ord;
};

struct RenderContext {
    std::ostringstream &os;
    const opt_t *opts;
    const Msg &msg;
    uint32_t ind;
    const char *file;
    uint32_t &line;
};

void gen_tags(Scratchbuf &o, CodeStmt *code, const std::set<std::string> &tags);
void combine_stmt(CodegenContext &ctx, CodeStmt *code);
void combine_stmts(CodegenContext &ctx, CodeStmts *stmts);
void render_code_stmt(RenderContext &rctx, const CodeStmt *code);
void render_code_stmts(RenderContext &rctx, const CodeStmts *code);
void render_code_if_then_else(RenderContext &rctx, const CodeIfTE *code);
void render_code_case(RenderContext &rctx, const CodeCase *code, bool defcase,
    bool noindent);
void render_code_switch(RenderContext &rctx, const CodeSwitch *code);
void render_code_block(RenderContext &rctx, const CodeBlock *code);

struct OutputFragment {
    CodeStmt *stmt;
    uint32_t  indent;
};

struct OutputBlock {
    const loc_t loc;
    std::vector<OutputFragment> fragments;
    bool used_yyaccept;
    bool have_user_code;
    std::vector<std::string> types;
    std::set<std::string> stags;
    std::set<std::string> mtags;
    const opt_t *opts;

    explicit OutputBlock(const loc_t &loc);
    ~OutputBlock();
    FORBID_COPY(OutputBlock);
};

typedef std::vector<OutputBlock *> blocks_t;
typedef blocks_t::const_iterator blocks_citer_t;

class Output {
    blocks_t cblocks; /* .c file */
    blocks_t hblocks; /* .h file */
    blocks_t *pblocks; /* selector */

public:
    counter_t<label_t> label_counter;
    uint32_t fill_index;
    bool state_goto;
    bool cond_enum_in_hdr;
    bool cond_goto;
    bool warn_condition_order;
    bool need_header;
    Msg &msg;
    std::set<std::string> skeletons;
    size_t max_fill;
    size_t max_nmatch;
    code_alc_t allocator;
    Scratchbuf scratchbuf;

    explicit Output(Msg &msg);
    ~Output();
    OutputBlock &block();
    size_t blockid() const;
    bool open ();
    void new_block(Opt &opts, const loc_t &loc);
    void header_mode(bool on);
    bool in_header() const;
    void wraw (const char *s, const char *e);
    void wversion_time ();
    void wdelay_stmt(uint32_t ind, CodeStmt *stmt);
    bool emit();
    bool emit_blocks(const std::string &fname, blocks_t &blocks,
        const uniq_vector_t<std::string> &global_types,
        const std::set<std::string> &global_stags,
        const std::set<std::string> &global_mtags);
    FORBID_COPY (Output);
};

void output_version_time(std::ostream &o, bool version, bool date);

} // namespace re2c

#endif // _RE2C_CODE_OUTPUT_
