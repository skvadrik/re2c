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
    uint32_t nelems;
    const char** elems;
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

struct CodeGoSwIf {
    union {
        CodeGoSw* gosw;
        CodeGoIf* goif;
    };
    enum class Kind: uint32_t {
        SWITCH,
        IF
    } kind;
};

// Binary IF (used for many branches).
struct CodeGoIfB {
    const char* cond;
    CodeGoIf* gothen;
    CodeGoIf* goelse;
};

struct CodeGoBranch {
    const char* cond;
    union {
        CodeJump jump;
        CodeGoSwIf* swif;
    };
    enum class Kind: uint32_t {
        JUMP,
        SWIF
    } kind;
};

// Linear IF (used for few branches).
struct CodeGoIfL {
    size_t nbranches;
    CodeGoBranch* branches;
    State* def;
};

struct CodeGoIf {
    union {
        CodeGoIfB* goifb;
        CodeGoIfL* goifl;
    };
    enum class Kind: uint32_t {
        BINARY,
        LINEAR
    } kind;
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
        LINEAR_IF,
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
        CodeGoCp* gocp;
        CodeGoSw* godot;
        CodeGoIfL* goifl;
    };
};

struct CodeBranch {
    const char* cond;
    CodeList* code;
    CodeBranch* next;
};

using CodeBranches = list_t<CodeBranch>;

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
    bool is_default;
    const char* name;
    const char* init;
};

// TODO: merge `BlockNameList` and `CodeExpr`?
struct BlockNameList {
    const char* name;
    BlockNameList* next;
};

struct CodeAssign {
    const char* lhs;
    const char* rhs;
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

struct CodeParam {
    const char* name;
    const char* type;
    CodeParam* next;
};

using CodeParams = list_t<CodeParam>;

struct CodeArg {
    const char* arg;
    CodeArg* next;
};

using CodeArgs = list_t<CodeArg>;

struct CodeFnDef {
    const char* name;
    const char* type;
    const CodeParams* params; // shared between different function definitions
    CodeList* body;
};

struct CodeFnCall {
    const char* name;
    const char* retval;
    const CodeArgs* args; // shared between different function calls
    bool tailcall;
};

struct CodeLabel {
    enum class Kind: uint32_t {
        NLABEL,
        SLABEL
    } kind;

    union {
        const Label* nlabel;
        const char* slabel;
    };
};

struct CodeArray {
    const char* name;
    const char* type;
    const char** elems;
    size_t size;
    bool local;
    bool tabulate;
};

struct CodeEnum {
    const char* type;
    size_t size;
    const char** elem_ids;
    const uint32_t* elem_nums;
};

struct CodeDebug {
    uint32_t state;
};

struct CodeTag {
    const char* tag1;
    const char* tag2;
    int32_t dist;
};

struct Code {
    union {
        const char* text;
        const char* target;
        const char* cond;
        const char* state;
        BlockNameList* block_names;
        CodeBranches* ifte;
        CodeSwitch swch;
        CodeBlock block;
        CodeFnDef fndef;
        CodeFnCall fncall;
        CodeRaw raw;
        CodeVar var;
        CodeArray array;
        CodeEnum enumr;
        CodeFmt fmt;
        CodeAssign assign;
        CodeLabel label;
        CodeDebug debug;
        CodeTag tag;
        CodeList* loop;
        CodeList* rfuncs;
        loc_t loc;
        size_t accept;
    };

    CodeKind kind;
    Code* next;
};

// YYFN name, type, attributes and params/args (they are common for all function definitions/calls,
// so they can be precomputed for each block options and once for whole-program options).
struct CodeFnCommon {
    const char* name;
    const char* type;
    CodeParams* params = nullptr;
    CodeParams* params_yych = nullptr; // same as `params`, but with `yych` at the end
    CodeArgs* args = nullptr;
    CodeArgs* args_yych = nullptr; // same as `args`, but with `yych` at the end
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

inline Code* code_goto(OutAllocator& alc, const char* target) {
    Code* x = new_code(alc, CodeKind::GOTO);
    x->target = target;
    return x;
}

inline Code* code_continue(OutAllocator& alc, const char* target) {
    Code* x = new_code(alc, CodeKind::CONTINUE);
    x->target = target;
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

inline Code* code_nlabel(OutAllocator& alc, const Label* label) {
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

inline Code* code_line_info_input(OutAllocator& alc, const loc_t& loc) {
    Code* x = new_code(alc, CodeKind::LINE_INFO_INPUT);
    x->loc = loc;
    return x;
}

inline Code* code_var(
        OutAllocator& alc, VarType type, bool is_default, const char* name, const char* init) {
    Code* x = new_code(alc, CodeKind::VAR);
    x->var.type = type;
    x->var.is_default = is_default;
    x->var.name = copystr(name, alc);
    x->var.init = init;
    return x;
}

inline void init_code_const(Code* x, VarType type, const char* name, const char* init) {
    x->kind = CodeKind::CONST;
    x->var.type = type;
    x->var.name = name;
    x->var.init = init;
}

inline Code* code_assign(OutAllocator& alc, const char* lhs, const char* rhs) {
    Code* x = new_code(alc, CodeKind::ASSIGN);
    x->assign.lhs = lhs;
    x->assign.rhs = rhs;
    return x;
}

inline Code* code_line_info_output(OutAllocator& alc) {
    return new_code(alc, CodeKind::LINE_INFO_OUTPUT);
}

inline Code* code_debug(OutAllocator& alc, uint32_t state) {
    Code* x = new_code(alc, CodeKind::DEBUG);
    x->debug.state = state;
    return x;
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

inline Code* code_backupctx(OutAllocator& alc) {
    return new_code(alc, CodeKind::BACKUPCTX);
}

inline Code* code_restore(OutAllocator& alc) {
    return new_code(alc, CodeKind::RESTORE);
}

inline Code* code_restore_ctx(OutAllocator& alc) {
    return new_code(alc, CodeKind::RESTORECTX);
}

inline Code* code_restore_tag(OutAllocator& alc, const char* tag) {
    Code* x = new_code(alc, CodeKind::RESTORETAG);
    x->tag.tag1 = tag;
    x->tag.tag2 = nullptr;
    x->tag.dist = 0;
    return x;
}

inline Code* code_shift(OutAllocator& alc, int32_t dist) {
    Code* x = new_code(alc, CodeKind::SHIFT);
    x->tag.tag1 = nullptr;
    x->tag.tag2 = nullptr;
    x->tag.dist = dist;
    return x;
}

inline Code* code_shift_tag(
        OutAllocator& alc, const char* tag, const char* neg, int32_t dist, bool is_mtag) {
    Code* x = new_code(alc, is_mtag ? CodeKind::SHIFTMTAG : CodeKind::SHIFTSTAG);
    x->tag.tag1 = tag;
    x->tag.tag2 = neg;
    x->tag.dist = dist;
    return x;
}

inline Code* code_set_tag(OutAllocator& alc, const char* tag, bool is_mtag, bool is_negative) {
    Code* x = new_code(alc, is_mtag
        ? (is_negative ? CodeKind::MTAGN : CodeKind::MTAGP)
        : (is_negative ? CodeKind::STAGN : CodeKind::STAGP));
    x->tag.tag1 = tag;
    x->tag.tag2 = nullptr;
    x->tag.dist = 0;
    return x;
}

inline Code* code_copy_tag(OutAllocator& alc, const char* lhs, const char* rhs, bool is_mtag) {
    Code* x = new_code(alc, is_mtag ? CodeKind::COPYMTAG : CodeKind::COPYSTAG);
    x->tag.tag1 = lhs;
    x->tag.tag2 = rhs;
    x->tag.dist = 0;
    return x;
}

inline Code* code_set_accept(OutAllocator& alc, size_t accept) {
    Code* x = new_code(alc, CodeKind::SETACCEPT);
    x->accept = accept;
    return x;
}

inline Code* code_set_cond(OutAllocator& alc, const char* cond) {
    Code* x = new_code(alc, CodeKind::SETCOND);
    x->cond = cond;
    return x;
}

inline Code* code_set_state(OutAllocator& alc, const char* state) {
    Code* x = new_code(alc, CodeKind::SETSTATE);
    x->state = state;
    return x;
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

inline CodeBranch* code_branch(OutAllocator& alc, const char* cond, CodeList* code) {
    CodeBranch* x = alc.alloct<CodeBranch>(1);
    x->cond = cond;
    x->code = code;
    x->next = nullptr;
    return x;
}

inline CodeBranches* code_branches(OutAllocator& alc) {
    return new_list<CodeBranch>(alc);
}

inline Code* code_if_then_else(OutAllocator& alc) {
    Code* x = new_code(alc, CodeKind::IF_THEN_ELSE);
    x->ifte = code_branches(alc);
    return x;
}

inline Code* code_if_then_else(
        OutAllocator& alc, const char* if_cond, CodeList* if_code, CodeList* else_code) {
    Code* x = new_code(alc, CodeKind::IF_THEN_ELSE);
    x->ifte = code_branches(alc);
    append(x->ifte, code_branch(alc, if_cond, if_code));
    if (else_code) append(x->ifte, code_branch(alc, nullptr, else_code));
    return x;
}

inline Code* code_if_then_elif(OutAllocator& alc,
                               const char* if_cond,
                               CodeList* if_code,
                               const char* else_cond,
                               CodeList* else_code) {
    Code* x = new_code(alc, CodeKind::IF_THEN_ELSE);
    x->ifte = code_branches(alc);
    append(x->ifte, code_branch(alc, if_cond, if_code));
    append(x->ifte, code_branch(alc, else_cond, else_code));
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

inline CodeCase* code_case_ranges(OutAllocator& alc, CodeList* body, const CodeRanges* ranges) {
    CodeCase* x = code_case(alc, body, CodeCase::Kind::RANGES);
    x->ranges = ranges;
    return x;
}

inline CodeRanges* code_ranges(OutAllocator& alc, VarType type, int64_t* start, int64_t* end) {
    CodeRanges* x = alc.alloct<CodeRanges>(1);
    x->size = static_cast<uint32_t>(end - start) / 2;
    x->type = type;
    x->elems = start;
    return x;
}

inline CodeCases* code_cases(OutAllocator& alc) {
    return new_list<CodeCase>(alc);
}

inline CodeParam* code_param(OutAllocator& alc, const char* name, const char* type) {
    CodeParam* x = alc.alloct<CodeParam>(1);
    x->name = name;
    x->type = type;
    x->next = nullptr;
    return x;
}

inline CodeParams* code_params(OutAllocator& alc) {
    return new_list<CodeParam>(alc);
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

inline void init_code_fndef(
        Code* x, const char* name, const char* type, CodeParams* params, CodeList* body) {
    x->kind = CodeKind::FNDEF;
    x->fndef.name = name;
    x->fndef.type = type;
    x->fndef.params = params;
    x->fndef.body = body;
}

inline Code* code_fndef(
        OutAllocator& alc, const char* name, const char* type, CodeParams* params, CodeList* body) {
    Code* x = new_code(alc, CodeKind::FNDEF);
    x->fndef.name = name;
    x->fndef.type = type;
    x->fndef.params = params;
    x->fndef.body = body;
    return x;
}

inline Code* code_fncall(
        OutAllocator& alc,
        const char* name,
        const char* retval,
        CodeArgs* args,
        bool tailcall = false) {
    Code* x = new_code(alc, CodeKind::FNCALL);
    x->fncall.name = name;
    x->fncall.retval = retval;
    x->fncall.args = args;
    x->fncall.tailcall = tailcall;
    return x;
}

inline Code* code_tailcall(OutAllocator& alc, const char* name, CodeArgs* args, bool have_retval) {
    // tailcall returns immediately so the `retval` string won't be used
    const char* retval = have_retval ? "<unused-retval>" : nullptr;
    return code_fncall(alc, name, retval, args, true);
}

inline Code* code_recursive_functions(OutAllocator& alc, CodeList* fndefs) {
    Code* x = new_code(alc, CodeKind::REC_FUNCS);
    x->rfuncs = fndefs;
    return x;
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
    x->nelems = 0;
    x->elems = nullptr;
    x->used = false;
    return x;
}

inline Code* code_array(
        OutAllocator& alc,
        const char* name,
        const char* type,
        const char** elems,
        size_t size,
        bool local,
        bool tabulate = false) {
    Code* x = new_code(alc, CodeKind::ARRAY);
    x->array.name = name;
    x->array.type = type;
    x->array.elems = elems;
    x->array.size = size;
    x->array.local = local;
    x->array.tabulate = tabulate;
    return x;
}

inline void init_code_enum(
        Code* x, const char* type, size_t size, const char** elem_ids, uint32_t* elem_nums) {
    x->kind = CodeKind::ENUM;
    x->enumr.type = type;
    x->enumr.size = size;
    x->enumr.elem_ids = elem_ids;
    x->enumr.elem_nums = elem_nums;
}

inline Code* code_fingerprint(OutAllocator& alc) {
    return new_code(alc, CodeKind::FINGERPRINT);
}

} // namespace re2c

#endif // _RE2C_CODEGEN_CODE_
