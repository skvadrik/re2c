#ifndef _RE2C_CODEGEN_CODE_
#define _RE2C_CODEGEN_CODE_

#include <stdint.h>
#include <string.h>

#include "src/constants.h"
#include "src/dfa/tcmd.h"
#include "src/msg/location.h"
#include "src/util/allocator.h"
#include "src/util/check.h"
#include "src/util/containers.h"
#include "src/util/string_utils.h"

namespace re2c {

// forward decls
struct Code;
struct CodeGo;
struct CodeGoIf;
struct State;

struct Label {
    static constexpr uint32_t NONE = ~0u;

    uint32_t index;
    bool used;
};

inline Label* new_label(OutAllocator& alc, uint32_t index) {
    Label* l = alc.alloct<Label>(1);
    l->index = index;
    l->used = false;
    return l;
}

using CodeList = list_t<Code>;

struct CodeJump {
    const State* to;
    tcid_t tags;
    bool skip;
    bool eof;
    bool elide;
};

struct CodeBmState {
    const CodeGo* go;
    const State* state; // destination DFA state
    uint32_t offset;    // start offset in the 'yybm' buffer
    uint32_t mask;      // bit mask
    CodeBmState* next;
};

using CodeBmStates = list_t<CodeBmState>;

struct CodeBitmap {
    CodeBmStates* states;
    uint32_t nchars;
    bool used;
};

struct Span {
    uint32_t ub;
    State* to;
    tcid_t tags;
};

struct CodeRanges {
    VarType type;
    uint32_t size;
    int64_t* elems;
};

struct CodeGoCase {
    const CodeRanges* ranges;
    CodeJump jump;
};

struct CodeGoSw {
    CodeGoCase* cases;
    CodeGoCase* defcase;
    uint32_t ncases;
};

struct CodeCmp {
    const char* cmp;
    uint32_t val;
};

// binary if
struct CodeGoIfB {
    const CodeCmp* cond;
    CodeGoIf* gothen;
    CodeGoIf* goelse;
};

// linear if
struct CodeGoIfL {
    struct Branch {
        const CodeCmp* cond;
        CodeJump jump;
    };

    size_t nbranches;
    Branch* branches;
    State* def;
};

struct CodeGoIf {
    enum class Kind: uint32_t {
        BINARY,
        LINEAR
    };

    Kind kind;
    union {
        CodeGoIfB* goifb;
        CodeGoIfL* goifl;
    };
};

struct CodeGoSwIf {
    enum class Kind: uint32_t {
        SWITCH,
        IF
    };

    Kind kind;
    union {
        CodeGoSw* gosw;
        CodeGoIf* goif;
    };
};

struct CodeGoBm {
    const CodeBmState* bitmap;
    CodeGoSwIf* hgo;
    CodeGoSwIf* lgo;
};

struct CodeGoCpTable {
    static constexpr uint32_t TABLE_SIZE = 0x100;

    State** table;
};

struct CodeGoCp {
    CodeGoSwIf* hgo;
    CodeGoCpTable* table;
};

struct CodeGo {
    enum class Kind: uint32_t {
        EMPTY,
        SWITCH_IF,
        BITMAP,
        CPGOTO,
        DOT
    };

    Kind kind;
    uint32_t span_count;
    Span* span;
    tcid_t tags;
    bool skip;
    union {
        CodeGoSwIf* goswif;
        CodeGoBm* gobm;
        CodeGoCp* gocp;
        CodeGoSw* godot;
    };
};

struct CodeIfTE {
    const char* if_cond;
    const char* else_cond;
    CodeList* if_code;
    CodeList* else_code;
    bool oneline;
};

struct CodeCase {
    enum class Kind: uint32_t {
        RANGES,
        NUMBER,
        STRING,
        DEFAULT
    } kind;

    union {
        const CodeRanges* ranges;
        int32_t number;
        const char* string;
    };
    CodeList* body;
    CodeCase* next;
};

using CodeCases = list_t<CodeCase>;

struct CodeSwitch {
    const char* expr;
    CodeCases* cases;
};

struct CodeBlock {
    enum class Kind: uint32_t {
        WRAPPED,
        INDENTED,
        RAW
    };

    Kind kind;
    CodeList* stmts;
};

struct CodeVar {
    VarType type;
    const char* name;
    const char* init;
};

struct BlockNameList {
    const char* name;
    BlockNameList* next;
};

struct CodeFmt {
    BlockNameList* block_names;
    const char* format;
    const char* separator;
};

struct CodeRaw {
    const char* data;
    size_t size;
};

struct CodeArg {
    const char* arg;
    CodeArg* next;
};

using CodeArgs = list_t<CodeArg>;

struct CodeFunc {
    CodeArgs* args;
    const char* name;
    const char* semi;
};

struct CodeLabel {
    enum class Kind: uint32_t {
        NLABEL,
        SLABEL
    } kind;

    union {
        Label* nlabel;
        const char* slabel;
    };
};

struct CodeTable {
    const char* name;
    const char* type;
    const char** elems;
    size_t size;
    bool tabulate;
};

struct Code {
    union {
        const char* text;
        BlockNameList* block_names;
        CodeIfTE ifte;
        CodeSwitch swch;
        CodeBlock block;
        CodeFunc func;
        CodeRaw raw;
        CodeVar var;
        CodeFmt fmt;
        CodeLabel label;
        CodeList* loop;
        CodeTable* table;
        loc_t loc;
    };

    CodeKind kind;
    Code* next;
};

inline Code* new_code(OutAllocator& alc, CodeKind kind) {
    Code* x = alc.alloct<Code>(1);
    x->kind = kind;
    x->next = nullptr;
    return x;
}

inline Code* code_stmt(OutAllocator& alc, const char* text) {
    Code* x = new_code(alc, CodeKind::STMT);
    x->text = text;
    return x;
}

inline Code* code_loop(OutAllocator& alc, CodeList* loop) {
    Code* x = new_code(alc, CodeKind::LOOP);
    x->loop = loop;
    return x;
}

inline Code* code_text(OutAllocator& alc, const char* text) {
    Code* x = new_code(alc, CodeKind::TEXT);
    x->text = text;
    return x;
}

inline Code* code_raw(OutAllocator& alc, const uint8_t* data, size_t size) {
    Code* x = new_code(alc, CodeKind::RAW);
    char* copy = alc.alloct<char>(size);
    memcpy(copy, data, size);
    x->raw.size = size;
    x->raw.data = copy;
    return x;
}

inline Code* code_textraw(OutAllocator& alc, const char* text) {
    Code* x = new_code(alc, CodeKind::TEXT_RAW);
    x->text = text;
    return x;
}

inline Code* code_abort(OutAllocator& alc) {
    return new_code(alc, CodeKind::ABORT);
}

inline Code* code_newline(OutAllocator& alc) {
    return code_textraw(alc, "");
}

inline Code* code_nlabel(OutAllocator& alc, Label* label) {
    Code* x = new_code(alc, CodeKind::LABEL);
    x->label.kind = CodeLabel::Kind::NLABEL;
    x->label.nlabel = label;
    return x;
}

inline Code* code_slabel(OutAllocator& alc, const char* label) {
    Code* x = new_code(alc, CodeKind::LABEL);
    x->label.kind = CodeLabel::Kind::SLABEL;
    x->label.slabel = label;
    return x;
}

inline Code* code_fmt(OutAllocator& alc,
                      CodeKind kind,
                      BlockNameList* blocks,
                      const char* format,
                      const char* separator) {
    Code* x = new_code(alc, kind);
    x->fmt.block_names = blocks;
    x->fmt.format = format;
    x->fmt.separator = separator;
    return x;
}

inline Code* code_state_goto(OutAllocator& alc, BlockNameList* blocks) {
    Code* x = new_code(alc, CodeKind::STATE_GOTO);
    x->block_names = blocks;
    return x;
}

inline Code* code_line_info_input(OutAllocator& alc, Lang lang, const loc_t& loc) {
    // Rust has no line directives.
    if (lang == Lang::RUST) return nullptr;

    Code* x = new_code(alc, CodeKind::LINE_INFO_INPUT);
    x->loc = loc;
    return x;
}

inline Code* code_var(OutAllocator& alc, VarType type, const std::string& name, const char* init) {
    Code* x = new_code(alc, CodeKind::VAR);
    x->var.type = type;
    x->var.name = copystr(name, alc);
    x->var.init = init;
    return x;
}

inline Code* code_line_info_output(OutAllocator& alc, Lang lang) {
    // Rust has no line directives.
    if (lang == Lang::RUST) return nullptr;

    return new_code(alc, CodeKind::LINE_INFO_OUTPUT);
}

inline Code* code_skip(OutAllocator& alc) {
    return new_code(alc, CodeKind::SKIP);
}

inline Code* code_peek(OutAllocator& alc) {
    return new_code(alc, CodeKind::PEEK);
}

inline Code* code_backup(OutAllocator& alc) {
    return new_code(alc, CodeKind::BACKUP);
}

inline Code* code_dfas(OutAllocator& alc) {
    return new_code(alc, CodeKind::DFAS);
}

inline Code* code_block(OutAllocator& alc, CodeList* stmts, CodeBlock::Kind kind) {
    Code* x = new_code(alc, CodeKind::BLOCK);
    x->block.kind = kind;
    x->block.stmts = stmts;
    return x;
}

inline Code* code_if_then_else(OutAllocator& alc,
                               const char* if_cond,
                               CodeList* if_code,
                               CodeList* else_code,
                               bool oneline = true) {
    Code* x = new_code(alc, CodeKind::IF_THEN_ELSE);
    x->ifte.if_cond = if_cond;
    x->ifte.else_cond = nullptr;
    x->ifte.if_code = if_code;
    x->ifte.else_code = else_code;
    x->ifte.oneline = oneline;
    return x;
}

inline Code* code_if_then_elif(OutAllocator& alc,
                               const char* if_cond,
                               CodeList* if_code,
                               const char* else_cond,
                               CodeList* else_code) {
    Code* x = code_if_then_else(alc, if_cond, if_code, else_code, false);
    x->ifte.else_cond = else_cond;
    return x;
}

inline CodeCase* code_case(OutAllocator& alc, CodeList* body, CodeCase::Kind kind) {
    CodeCase* x = alc.alloct<CodeCase>(1);
    x->kind = kind;
    x->body = body;
    x->next = nullptr;
    return x;
}

inline CodeCase* code_case_default(OutAllocator& alc, CodeList* body) {
    return code_case(alc, body, CodeCase::Kind::DEFAULT);
}

inline CodeCase* code_case_number(OutAllocator& alc, CodeList* body, int32_t number) {
    CodeCase* x = code_case(alc, body, CodeCase::Kind::NUMBER);
    x->number = number;
    return x;
}

inline CodeCase* code_case_string(OutAllocator& alc, CodeList* body, const char* string) {
    CodeCase* x = code_case(alc, body, CodeCase::Kind::STRING);
    x->string = string;
    return x;
}

inline CodeCase* code_case_ranges(
    OutAllocator& alc, CodeList* body, const CodeRanges* ranges) {
    CodeCase* x = code_case(alc, body, CodeCase::Kind::RANGES);
    x->ranges = ranges;
    return x;
}

inline CodeRanges* code_ranges(
    OutAllocator& alc, VarType type, int64_t* start, int64_t* end) {
    CodeRanges* x = alc.alloct<CodeRanges>(1);
    x->size = static_cast<uint32_t>(end - start) / 2;
    x->type = type;
    x->elems = start;
    return x;
}

inline CodeCases* code_cases(OutAllocator& alc) {
    return new_list<CodeCase>(alc);
}

inline CodeArg* code_arg(OutAllocator& alc, const char* arg) {
    CodeArg* x = alc.alloct<CodeArg>(1);
    x->arg = arg;
    x->next = nullptr;
    return x;
}

inline CodeArgs* code_args(OutAllocator& alc) {
    return new_list<CodeArg>(alc);
}

inline Code* code_func(OutAllocator& alc, const char* name, CodeArgs* args, const char* semi) {
    Code* x = new_code(alc, CodeKind::FUNC);
    x->func.args = args;
    x->func.name = name;
    x->func.semi = semi;
    return x;
}

inline Code* code_fdecl(OutAllocator& alc, const char* name, CodeArgs* args) {
    return code_func(alc, name, args, "");
}

inline Code* code_fcall(OutAllocator& alc, const char* name, CodeArgs* args, const char* semi) {
    return code_func(alc, name, args, semi);
}

inline Code* code_switch(OutAllocator& alc, const char* expr, CodeCases* cases) {
    Code* x = new_code(alc, CodeKind::SWITCH);
    x->swch.expr = expr;
    x->swch.cases = cases;
    return x;
}

inline CodeList* code_list(OutAllocator& alc) {
    return new_list<Code>(alc);
}

inline CodeBmState* code_bmstate(OutAllocator& alc, const CodeGo* go, const State* s) {
    CodeBmState* x = alc.alloct<CodeBmState>(1);
    x->go = go;
    x->state = s;
    x->offset = 0;
    x->mask = 0;
    x->next = nullptr;
    return x;
}

inline CodeBitmap* code_bitmap(OutAllocator& alc, uint32_t nchars) {
    CodeBitmap* x = alc.alloct<CodeBitmap>(1);
    x->states = new_list<CodeBmState>(alc);
    x->nchars = nchars;
    x->used = false;
    return x;
}

inline CodeCmp* code_cmp(OutAllocator& alc, const char* cmp, uint32_t val) {
    CodeCmp* x = alc.alloct<CodeCmp>(1);
    x->cmp = cmp;
    x->val = val;
    return x;
}

inline Code* code_table(
        OutAllocator& alc,
        const char* name,
        const char* type,
        const char** elems,
        size_t size,
        bool tabulate = false) {
    Code* x = new_code(alc, CodeKind::TABLE);
    CodeTable* t = x->table = alc.alloct<CodeTable>(1);
    t->name = name;
    t->type = type;
    t->elems = elems;
    t->size = size;
    t->tabulate = tabulate;
    return x;
}

} // namespace re2c

#endif // _RE2C_CODEGEN_CODE_
