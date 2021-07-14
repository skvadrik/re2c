#ifndef _RE2C_CODEGEN_CODE_
#define _RE2C_CODEGEN_CODE_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string.h>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "src/constants.h"
#include "src/dfa/tcmd.h"
#include "src/debug/debug.h"
#include "src/msg/location.h"
#include "src/util/forbid_copy.h"
#include "src/util/slab_allocator.h"
#include "src/util/uniq_vector.h"
#include "src/util/smart_ptr.h"
#include "src/util/string_utils.h"


namespace re2c {

// forward decls
class Msg;
struct Opt;
struct opt_t;
struct Code;
struct CodeGo;
struct CodeGoIf;
class Output;
class OutputBlock;
struct State;
struct DFA;
typedef std::vector<smart_ptr<DFA> > dfas_t;
template <typename value_t> class uniq_vector_t;

// need 8-byte alignment to allocate structs with pointers and 64-bit integers
typedef slab_allocator_t<1024 * 1024, 8> code_alc_t;

struct Label {
    uint32_t index;
    bool     used;
};

inline Label *new_label(code_alc_t &alc, uint32_t index)
{
    Label *l = alc.alloct<Label>(1);
    l->index = index;
    l->used = false;
    return l;
}

class Scratchbuf {
    code_alc_t &alc;
    std::ostringstream os;

public:
    explicit Scratchbuf(code_alc_t &alc): alc(alc), os() {}
    bool empty() const { return os.str().empty(); }
    std::ostringstream &stream() { return os; }
    const char *flush();
    Scratchbuf& i32(int32_t u) { os << u; return *this; }
    Scratchbuf& u32(uint32_t u) { os << u; return *this; }
    Scratchbuf& u64(uint64_t u) { os << u; return *this; }
    Scratchbuf& str(const std::string &s) { os << s; return *this; }
    Scratchbuf& cstr(const char *s) { os << s; return *this; }
    Scratchbuf& label(const Label &l) { os << l.index; return *this; }
    Scratchbuf& u32_width(uint32_t u, int width);
    Scratchbuf& yybm_char(uint32_t u, const opt_t *opts, int width);
    Scratchbuf& exact_uint(size_t width);
};

template<typename T>
struct code_list_t {
    T  *head;
    T **ptail;
};

typedef code_list_t<Code> CodeList;

struct CodeJump {
    const State *to;
    tcid_t       tags;
    bool         skip;
    bool         eof;
    bool         elide;
};

struct CodeBmState {
    const CodeGo *go;
    const State  *state;  // destination DFA state
    uint32_t      offset; // start offset in the 'yybm' buffer
    uint32_t      mask;   // bit mask
    CodeBmState  *next;
};

typedef code_list_t<CodeBmState> CodeBmStates;

struct CodeBitmap {
    CodeBmStates *states;
    uint32_t      nchars;
    bool          used;
};

struct Span {
    uint32_t  ub;
    State    *to;
    tcid_t    tags;
};

struct CodeGoCase {
    uint32_t  nranges;
    uint32_t *ranges;
    CodeJump  jump;
};

struct CodeGoSw {
    CodeGoCase *cases;
    CodeGoCase *defcase;
    uint32_t    ncases;
};

struct CodeCmp {
    const char *cmp;
    uint32_t    val;
};

// binary if
struct CodeGoIfB
{
    const CodeCmp *cond;
    CodeGoIf      *gothen;
    CodeGoIf      *goelse;
};

// linear if
struct CodeGoIfL {
    struct Branch {
        const CodeCmp *cond;
        CodeJump       jump;
    };

    size_t  nbranches;
    Branch *branches;
    State  *def;
};

struct CodeGoIf {
    enum Kind {
        BINARY,
        LINEAR
    };

    Kind kind;
    union {
        CodeGoIfB *goifb;
        CodeGoIfL *goifl;
    };
};

struct CodeGoSwIf {
    enum Kind{
        SWITCH,
        IF
    };

    Kind kind;
    union {
        CodeGoSw *gosw;
        CodeGoIf *goif;
    };
};

struct CodeGoBm {
    const CodeBmState *bitmap;
    CodeGoSwIf        *hgo;
    CodeGoSwIf        *lgo;
};

struct CodeGoCpTable {
    static const uint32_t TABLE_SIZE;

    State **table;
};

struct CodeGoCp {
    CodeGoSwIf    *hgo;
    CodeGoCpTable *table;
};

struct CodeGo {
    enum Kind {
        EMPTY,
        SWITCH_IF,
        BITMAP,
        CPGOTO,
        DOT
    };

    Kind      kind;
    uint32_t  nspans;
    Span     *span;
    tcid_t    tags;
    bool      skip;
    union {
        CodeGoSwIf *goswif;
        CodeGoBm   *gobm;
        CodeGoCp   *gocp;
        CodeGoSw   *godot;
    };
};

struct CodeIfTE {
    const char *if_cond;
    const char *else_cond;
    CodeList   *if_code;
    CodeList   *else_code;
    bool        oneline;
};

struct CodeCase {
    enum Kind {
        RANGES,
        NUMBER,
        STRING,
        DEFAULT
    } kind;

    union {
        const CodeGoCase *gocase;
        int32_t           number;
        const char       *string;
    };
    CodeList *body;
    CodeCase *next;
};

typedef code_list_t<CodeCase> CodeCases;

struct CodeSwitch {
    const char *expr;
    CodeCases  *cases;
};

struct CodeBlock {
    enum Fmt {
        WRAPPED,
        INDENTED,
        RAW
    };

    CodeList *stmts;
    Fmt       fmt;
};

struct CodeVar {
    const char *type;
    const char *name;
    const char *init;
};

struct BlockNameList {
    const char    *name;
    BlockNameList *next;
};

struct CodeFmt {
    BlockNameList *block_names;
    const char    *format;
    const char    *separator;
};

struct CodeRaw {
    const char *data;
    size_t      size;
};

struct CodeArg {
    const char *arg;
    CodeArg    *next;
};

typedef code_list_t<CodeArg> CodeArgs;

struct CodeFunc {
    CodeArgs   *args;
    const char *name;
    const char *semi;
};

struct CodeLabel {
    enum Kind {
        NLABEL,
        SLABEL
    } kind;

    union {
        Label      *nlabel;
        const char *slabel;
    };
};

struct Code {
    union {
        const char    *text;
        BlockNameList *block_names;
        CodeIfTE       ifte;
        CodeSwitch     swch;
        CodeBlock      block;
        CodeFunc       func;
        CodeRaw        raw;
        CodeVar        var;
        CodeFmt        fmt;
        CodeLabel      label;
        loc_t          loc;
    };

    CodeKind  kind;
    Code     *next;
};

template<typename T>
inline code_list_t<T> *new_code_list(code_alc_t &alc)
{
    code_list_t<T> *x = alc.alloct<code_list_t<T> >(1);
    x->head = NULL;
    x->ptail = &x->head;
    return x;
}

template<typename T>
inline void append(code_list_t<T> *list, T *elem)
{
    DASSERT(elem);
    *list->ptail = elem;
    list->ptail  = &elem->next;
}

template<typename T>
inline void prepend(code_list_t<T> *list, T *elem)
{
    DASSERT(elem);
    if (!list->head) {
        list->ptail = &elem->next;
    }
    elem->next = list->head;
    list->head = elem;
}

template<typename T>
inline void append(code_list_t<T> *list1, code_list_t<T> *list2)
{
    if (list2 && list2->head) {
        *list1->ptail = list2->head;
        for (; *(list1->ptail); list1->ptail = &(*list1->ptail)->next);
    }
}

inline Code *new_code(code_alc_t &alc, CodeKind kind)
{
    Code *x = alc.alloct<Code>(1);
    x->kind = kind;
    x->next = NULL;
    return x;
}

inline Code *code_stmt(code_alc_t &alc, const char *text)
{
    Code *x = new_code(alc, CODE_STMT);
    x->text = text;
    return x;
}

inline Code *code_text(code_alc_t &alc, const char *text)
{
    Code *x = new_code(alc, CODE_TEXT);
    x->text = text;
    return x;
}

inline Code *code_raw(code_alc_t &alc, const char *data, size_t size)
{
    Code *x = new_code(alc, CODE_RAW);
    char *copy = alc.alloct<char>(size);
    memcpy(copy, data, size);
    x->raw.size = size;
    x->raw.data = copy;
    return x;
}

inline Code *code_textraw(code_alc_t &alc, const char *text)
{
    Code *x = new_code(alc, CODE_TEXT_RAW);
    x->text = text;
    return x;
}

inline Code *code_newline(code_alc_t &alc)
{
    return code_textraw(alc, "");
}

inline Code *code_nlabel(code_alc_t &alc, Label *label)
{
    Code *x = new_code(alc, CODE_LABEL);
    x->label.kind = CodeLabel::NLABEL;
    x->label.nlabel = label;
    return x;
}

inline Code *code_slabel(code_alc_t &alc, const char *label)
{
    Code *x = new_code(alc, CODE_LABEL);
    x->label.kind = CodeLabel::SLABEL;
    x->label.slabel = label;
    return x;
}

inline Code *code_fmt(code_alc_t &alc, CodeKind kind, BlockNameList *blocks,
    const char *format, const char *separator)
{
    Code *x = new_code(alc, kind);
    x->fmt.block_names = blocks;
    x->fmt.format      = format;
    x->fmt.separator   = separator;
    return x;
}

inline Code *code_cond_table(code_alc_t &alc)
{
    return new_code(alc, CODE_COND_TABLE);
}

inline Code *code_cond_goto(code_alc_t &alc)
{
    return new_code(alc, CODE_COND_GOTO);
}

inline Code *code_state_goto(code_alc_t &alc, BlockNameList *blocks)
{
    Code *x = new_code(alc, CODE_STATE_GOTO);
    x->block_names = blocks;
    return x;
}

inline Code *code_line_info_input(code_alc_t &alc, const loc_t &loc)
{
    Code *x = new_code(alc, CODE_LINE_INFO_INPUT);
    x->loc = loc;
    return x;
}

inline Code *code_yych_decl(code_alc_t &alc)
{
    return new_code(alc, CODE_YYCH);
}

inline Code *code_yyaccept_def(code_alc_t &alc)
{
    return new_code(alc, CODE_YYACCEPT);
}

inline Code *code_line_info_output(code_alc_t &alc)
{
    return new_code(alc, CODE_LINE_INFO_OUTPUT);
}

inline Code *code_skip(code_alc_t &alc)
{
    return new_code(alc, CODE_SKIP);
}

inline Code *code_peek(code_alc_t &alc)
{
    return new_code(alc, CODE_PEEK);
}

inline Code *code_backup(code_alc_t &alc)
{
    return new_code(alc, CODE_BACKUP);
}

inline Code *code_block(code_alc_t &alc, CodeList *stmts, CodeBlock::Fmt fmt)
{
    Code *x = new_code(alc, CODE_BLOCK);
    x->block.stmts = stmts;
    x->block.fmt   = fmt;
    return x;
}

inline Code *code_if_then_else(code_alc_t &alc, const char *if_cond, CodeList *if_code,
    CodeList *else_code, bool oneline = true)
{
    Code *x = new_code(alc, CODE_IF_THEN_ELSE);
    x->ifte.if_cond   = if_cond;
    x->ifte.else_cond = NULL;
    x->ifte.if_code   = if_code;
    x->ifte.else_code = else_code;
    x->ifte.oneline   = oneline;
    return x;
}

inline Code *code_if_then_elif(code_alc_t &alc, const char *if_cond, CodeList *if_code,
    const char *else_cond, CodeList *else_code)
{
    Code *x = code_if_then_else(alc, if_cond, if_code, else_code, false);
    x->ifte.else_cond = else_cond;
    return x;
}

inline CodeCase *code_case(code_alc_t &alc, CodeList *body, CodeCase::Kind kind)
{
    CodeCase *x = alc.alloct<CodeCase>(1);
    x->kind = kind;
    x->body = body;
    x->next = NULL;
    return x;
}

inline CodeCase *code_case_default(code_alc_t &alc, CodeList *body)
{
    return code_case(alc, body, CodeCase::DEFAULT);
}

inline CodeCase *code_case_number(code_alc_t &alc, CodeList *body, int32_t number)
{
    CodeCase *x = code_case(alc, body, CodeCase::NUMBER);
    x->number = number;
    return x;
}

inline CodeCase *code_case_string(code_alc_t &alc, CodeList *body, const char *string)
{
    CodeCase *x = code_case(alc, body, CodeCase::STRING);
    x->string = string;
    return x;
}

inline CodeCase *code_case_ranges(code_alc_t &alc, CodeList *body,
    const CodeGoCase *gocase)
{
    CodeCase *x = code_case(alc, body, CodeCase::RANGES);
    x->gocase = gocase;
    return x;
}

inline CodeCases *code_cases(code_alc_t &alc)
{
    return new_code_list<CodeCase>(alc);
}

inline CodeArg *code_arg(code_alc_t &alc, const char *arg)
{
    CodeArg *x = alc.alloct<CodeArg>(1);
    x->arg = arg;
    x->next = NULL;
    return x;
}

inline CodeArgs *code_args(code_alc_t &alc)
{
    return new_code_list<CodeArg>(alc);
}

inline Code *code_func(code_alc_t &alc, const char *name, CodeArgs *args,
    const char *semi)
{
    Code *x = new_code(alc, CODE_FUNC);
    x->func.args = args;
    x->func.name = name;
    x->func.semi = semi;
    return x;
}

inline Code *code_fdecl(code_alc_t &alc, const char *name, CodeArgs *args)
{
    return code_func(alc, name, args, "");
}

inline Code *code_fcall(code_alc_t &alc, const char *name, CodeArgs *args,
    const char *semi)
{
    return code_func(alc, name, args, semi);
}

inline Code *code_switch(code_alc_t &alc, const char *expr, CodeCases *cases)
{
    Code *x = new_code(alc, CODE_SWITCH);
    x->swch.expr   = expr;
    x->swch.cases  = cases;
    return x;
}

inline CodeList *code_list(code_alc_t &alc)
{
    return new_code_list<Code>(alc);
}

inline CodeBmState *code_bmstate(code_alc_t &alc, const CodeGo *go, const State *s)
{
    CodeBmState *x = alc.alloct<CodeBmState>(1);
    x->go     = go;
    x->state  = s;
    x->offset = 0;
    x->mask   = 0;
    x->next   = NULL;
    return x;
}

inline CodeBitmap *code_bitmap(code_alc_t &alc, uint32_t nchars)
{
    CodeBitmap *x = alc.alloct<CodeBitmap>(1);
    x->states = new_code_list<CodeBmState>(alc);
    x->nchars = nchars;
    x->used   = false;
    return x;
}

typedef std::vector<OutputBlock *> blocks_t;
typedef blocks_t::const_iterator blocks_citer_t;
typedef std::set<std::string> tagnames_t;

struct CodegenCtxGlobal {
    code_alc_t &allocator;
    Scratchbuf &scratchbuf;
    Msg &msg;
    const opt_t *opts;
    const blocks_t *pblocks;
    uniq_vector_t<std::string> conds;
    tagnames_t stags;
    tagnames_t mtags;
    size_t max_fill;
    size_t max_nmatch;
    const bool warn_cond_ord;
};

struct CodegenCtxPass1 {
    const CodegenCtxGlobal *global; // global part
    const OutputBlock *block;       // block-local part
};

struct CodegenCtxPass2 {
    code_alc_t &allocator;
    Scratchbuf &scratchbuf;
    const opt_t *opts;
};

struct RenderContext {
    std::ostringstream &os;
    const opt_t *opts;
    const Msg &msg;
    uint32_t ind;
    const char *file;
    uint32_t &line;
};

struct OutputFragment {
    Code     *code;
    uint32_t  indent;
};

struct OutputBlock {
    InputBlockKind kind;
    std::string name;
    const loc_t loc;
    std::vector<OutputFragment> fragments;
    bool used_yyaccept;
    bool have_user_code;
    std::vector<std::string> conds;
    tagnames_t stags;
    tagnames_t mtags;
    const opt_t *opts;

    size_t max_fill;   // YYMAXFILL
    size_t max_nmatch; // YYMAXNMATCH

    // Used in the state switch (with `-f --storable-state` option).
    Label *start_label;        // label of the DFA start state
    uint32_t fill_index_start; // start of YYFILL index range
    uint32_t fill_index_end;   // end of YYFILL index range (not included)
    std::vector<CodeList*> fill_goto; // transitions to YYFILL states

    OutputBlock(InputBlockKind kind, const std::string &name, const loc_t &loc);
    ~OutputBlock();
    FORBID_COPY(OutputBlock);
};

class Output {
    blocks_t cblocks; /* .c file */
    blocks_t hblocks; /* .h file */
    blocks_t *pblocks; /* selector */

public:
    uint32_t label_counter;
    bool state_goto;
    bool cond_enum_in_hdr;
    bool cond_goto;
    bool warn_condition_order;
    bool need_header;
    bool done_mtag_defs;
    Msg &msg;
    std::set<std::string> skeletons;
    code_alc_t allocator;
    Scratchbuf scratchbuf;

    // YYFILL state index accumulated for all non-reuse blocks
    uint32_t total_fill_index;

    // "final" options accumulated for all non-reuse blocks
    const opt_t *total_opts;

    explicit Output(Msg &msg);
    ~Output();
    OutputBlock &block();
    bool open ();
    void new_block(Opt &opts, InputBlockKind kind, const std::string &name,
        const loc_t &loc);
    void gather_info_from_block();
    void header_mode(bool on);
    bool in_header() const;
    void wraw(const char *s, const char *e, bool newline = false);
    void wversion_time ();
    void wdelay_stmt(uint32_t ind, Code *code);
    bool emit();
    bool emit_blocks(const std::string &fname, const CodegenCtxGlobal &globalctx);
    FORBID_COPY (Output);
};

void init_go(CodeGo *go);
void code_go(code_alc_t &alc, CodeGo *go, const State *from, const opt_t *opts,
    CodeBitmap *bitmap);
CodeBmState *find_bitmap(const CodeBitmap *bitmap, const CodeGo *go, const State *s);
void insert_bitmap(code_alc_t &alc, CodeBitmap *bitmap, const CodeGo *go, const State *s);
CodeList *gen_bitmap(Output &output, const CodeBitmap *bitmap);

void gen_go(Output &output, const DFA &dfa, const CodeGo *go, const State *from,
    CodeList *stmts);
void gen_tags(Scratchbuf &buf, const opt_t *opts, Code *code, const tagnames_t &tags);
void emit_action(Output &output, const DFA &dfa, const State *s, CodeList *stmts);
void gen_settags(Output &output, CodeList *tag_actions, const DFA &dfa, tcid_t tcid,
    bool delayed);
void gen_goto(Output &output, const DFA &dfa, CodeList *stmts, const State *from,
    const CodeJump &jump);
const char *gen_lessthan(Scratchbuf &o, const opt_t *opts, size_t n);
void gen_code(Output &output, dfas_t &dfas);

void expand_pass_1(CodegenCtxPass1 &ctx, Code *code);
void expand_pass_2(CodegenCtxPass2 &ctx, Code *code);
void combine(CodegenCtxPass2 &ctx, Code *code);
void render(RenderContext &rctx, const Code *code);

bool consume(const State *s);
void expand_fintags(const Tag &tag, std::vector<std::string> &fintags);
std::string vartag_name(tagver_t ver, const std::string &prefix);
std::string vartag_expr(tagver_t ver, const opt_t *opts);
void output_version_time(std::ostream &os, const opt_t *opts);

} // namespace re2c

#endif // _RE2C_CODEGEN_CODE_
