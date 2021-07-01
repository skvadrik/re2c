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

struct CodeTags {
    const char    *fmt;
    const char    *sep;
    BlockNameList *block_names;
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
    enum Kind {
        EMPTY,
        IF_THEN_ELSE,
        SWITCH,
        BLOCK,
        FUNC,
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
        STMT,
        TEXT,
        TEXT_RAW,
        RAW,
        LABEL
    } kind;

    union {
        const char    *text;
        BlockNameList *block_names;
        CodeIfTE       ifte;
        CodeSwitch     swch;
        CodeBlock      block;
        CodeFunc       func;
        CodeRaw        raw;
        CodeVar        var;
        CodeTags       tags;
        CodeLabel      label;
        loc_t          loc;
    };

    Code *next;
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

inline Code *new_code(code_alc_t &alc, Code::Kind kind)
{
    Code *x = alc.alloct<Code>(1);
    x->kind = kind;
    x->next = NULL;
    return x;
}

inline Code *code_stmt(code_alc_t &alc, const char *text)
{
    Code *x = new_code(alc, Code::STMT);
    x->text = text;
    return x;
}

inline Code *code_text(code_alc_t &alc, const char *text)
{
    Code *x = new_code(alc, Code::TEXT);
    x->text = text;
    return x;
}

inline Code *code_raw(code_alc_t &alc, const char *data, size_t size)
{
    Code *x = new_code(alc, Code::RAW);
    char *copy = alc.alloct<char>(size);
    memcpy(copy, data, size);
    x->raw.size = size;
    x->raw.data = copy;
    return x;
}

inline Code *code_textraw(code_alc_t &alc, const char *text)
{
    Code *x = new_code(alc, Code::TEXT_RAW);
    x->text = text;
    return x;
}

inline Code *code_newline(code_alc_t &alc)
{
    return code_textraw(alc, "");
}

inline Code *code_nlabel(code_alc_t &alc, Label *label)
{
    Code *x = new_code(alc, Code::LABEL);
    x->label.kind = CodeLabel::NLABEL;
    x->label.nlabel = label;
    return x;
}

inline Code *code_slabel(code_alc_t &alc, const char *label)
{
    Code *x = new_code(alc, Code::LABEL);
    x->label.kind = CodeLabel::SLABEL;
    x->label.slabel = label;
    return x;
}

inline Code *code_tags(code_alc_t &alc, const std::string &fmt, const std::string &sep,
    BlockNameList *blocks, bool mtags)
{
    Code *x = new_code(alc, mtags ? Code::MTAGS : Code::STAGS);
    x->tags.fmt = copystr(fmt, alc);
    x->tags.sep = copystr(sep, alc);
    x->tags.block_names = blocks;
    return x;
}

inline Code *code_yymaxfill(code_alc_t &alc, BlockNameList *blocks)
{
    Code *x = new_code(alc, Code::YYMAXFILL);
    x->block_names = blocks;
    return x;
}

inline Code *code_yymaxnmatch(code_alc_t &alc, BlockNameList *blocks)
{
    Code *x = new_code(alc, Code::YYMAXNMATCH);
    x->block_names = blocks;
    return x;
}

inline Code *code_cond_enum(code_alc_t &alc, BlockNameList *blocks)
{
    Code *x = new_code(alc, Code::COND_ENUM);
    x->block_names = blocks;
    return x;
}

inline Code *code_cond_table(code_alc_t &alc)
{
    return new_code(alc, Code::COND_TABLE);
}

inline Code *code_cond_goto(code_alc_t &alc)
{
    return new_code(alc, Code::COND_GOTO);
}

inline Code *code_state_goto(code_alc_t &alc, BlockNameList *blocks)
{
    Code *x = new_code(alc, Code::STATE_GOTO);
    x->block_names = blocks;
    return x;
}

inline Code *code_line_info_input(code_alc_t &alc, const loc_t &loc)
{
    Code *x = new_code(alc, Code::LINE_INFO_INPUT);
    x->loc = loc;
    return x;
}

inline Code *code_yych_decl(code_alc_t &alc)
{
    return new_code(alc, Code::YYCH);
}

inline Code *code_yyaccept_def(code_alc_t &alc)
{
    return new_code(alc, Code::YYACCEPT);
}

inline Code *code_line_info_output(code_alc_t &alc)
{
    return new_code(alc, Code::LINE_INFO_OUTPUT);
}

inline Code *code_skip(code_alc_t &alc)
{
    return new_code(alc, Code::SKIP);
}

inline Code *code_peek(code_alc_t &alc)
{
    return new_code(alc, Code::PEEK);
}

inline Code *code_backup(code_alc_t &alc)
{
    return new_code(alc, Code::BACKUP);
}

inline Code *code_block(code_alc_t &alc, CodeList *stmts, CodeBlock::Fmt fmt)
{
    Code *x = new_code(alc, Code::BLOCK);
    x->block.stmts = stmts;
    x->block.fmt   = fmt;
    return x;
}

inline Code *code_if_then_else(code_alc_t &alc, const char *if_cond, CodeList *if_code,
    CodeList *else_code, bool oneline = true)
{
    Code *x = new_code(alc, Code::IF_THEN_ELSE);
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
    Code *x = new_code(alc, Code::FUNC);
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
    Code *x = new_code(alc, Code::SWITCH);
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
    const bool used_yyaccept;
    const bool warn_cond_ord;
    const uint32_t fill_index;
    const std::vector<CodeList*> &fill_goto;
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
    const loc_t loc;
    std::vector<OutputFragment> fragments;
    bool used_yyaccept;
    bool have_user_code;
    bool is_reuse_block;
    std::vector<std::string> types;
    std::set<std::string> stags;
    std::set<std::string> mtags;
    const opt_t *opts;

    // used in state dispatch
    uint32_t fill_index;              // upper bound of YYFILL state index
    std::vector<CodeList*> fill_goto; // transitions to YYFILL states

    OutputBlock(const loc_t &loc, bool reuse);
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
    uint32_t label_counter;
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

    // used in state dispatch (accumulated for all non-reuse blocks)
    uint32_t total_fill_index;              // upper bound of YYFILL state index
    std::vector<CodeList*> total_fill_goto; // transitions to YYFILL states

    // "final" options accumulated for all non-reuse blocks
    const opt_t *total_opts;

    explicit Output(Msg &msg);
    ~Output();
    OutputBlock &block();
    size_t blockid() const;
    bool open ();
    void new_block(Opt &opts, const loc_t &loc, bool reuse);
    void gather_info_from_block();
    void header_mode(bool on);
    bool in_header() const;
    void wraw (const char *s, const char *e);
    void wversion_time ();
    void wdelay_stmt(uint32_t ind, Code *code);
    bool emit();
    bool emit_blocks(const std::string &fname, blocks_t &blocks,
        const uniq_vector_t<std::string> &global_types,
        const std::set<std::string> &global_stags,
        const std::set<std::string> &global_mtags);
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
void gen_tags(Scratchbuf &o, const opt_t *opts, Code *code,
    const std::set<std::string> &tags);
void emit_action(Output &output, const DFA &dfa, const State *s, CodeList *stmts);
void gen_settags(Output &output, CodeList *tag_actions, const DFA &dfa, tcid_t tcid,
    bool delayed);
void gen_goto(Output &output, const DFA &dfa, CodeList *stmts, const State *from,
    const CodeJump &jump);
const char *gen_lessthan(Scratchbuf &o, const opt_t *opts, size_t n);
void gen_code(Output &output, dfas_t &dfas);

void expand(CodegenContext &ctx, Code *code);
void combine(CodegenContext &ctx, Code *code);
void render(RenderContext &rctx, const Code *code);

bool consume(const State *s);
void expand_fintags(const Tag &tag, std::vector<std::string> &fintags);
std::string vartag_name(tagver_t ver, const std::string &prefix);
std::string vartag_expr(tagver_t ver, const opt_t *opts);
void output_version_time(std::ostream &os, const opt_t *opts);

} // namespace re2c

#endif // _RE2C_CODEGEN_CODE_
