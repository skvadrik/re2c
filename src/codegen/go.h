#ifndef _RE2C_CODE_GO_
#define _RE2C_CODE_GO_

#include "src/codegen/output.h"
#include "src/dfa/tcmd.h"
#include "src/util/c99_stdint.h"


namespace re2c {

struct DFA;
struct bitmap_t;
class bitmaps_t;
struct State;
struct CodeGoIf;

struct Span {
    uint32_t  ub;
    State    *to;
    tcid_t    tags;
};

struct CodeGoCase {
    uint32_t  nranges;
    uint32_t *ranges;
    State    *to;
    tcid_t    tags;
    bool      skip;
    bool      eof;
};

struct CodeGoCases {
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
        State         *to;
        tcid_t        tags;
        bool          skip;
        bool          eof;
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
        CodeGoCases *gosw;
        CodeGoIf    *goif;
    };
};

struct CodeGoBm {
    const bitmap_t *bitmap;
    State          *bitmap_state;
    CodeGoSwIf     *hgo;
    CodeGoSwIf     *lgo;
};

struct CodeGoCpTable {
    static const uint32_t TABLE_SIZE;

    State **table;
};

struct CodeGoCp {
    CodeGoSwIf    *hgo;
    CodeGoCpTable *table;
};

struct CodeGoDot {
    CodeGoCases *cases;
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
    uint32_t  nSpans; // number of spans
    Span     *span;
    tcid_t    tags;
    bool      skip;
    union {
        CodeGoSwIf *goswif;
        CodeGoBm   *gobm;
        CodeGoCp   *gocp;
        CodeGoDot  *godot;
    };
};

void init_go(CodeGo *go);

// generate goto structures
void code_go(code_alc_t &alc, CodeGo *go, const State *from, const opt_t *opts,
    bitmaps_t &bitmaps);
CodeGoDot *code_godot(code_alc_t &alc, const Span *sp, uint32_t nsp, uint32_t eof);
CodeGoCp *code_gocp(code_alc_t &alc, const Span *span, uint32_t nSpans, const Span *hspan,
    uint32_t hSpans, State *next, bool sflag, uint32_t eof);
CodeGoCpTable *code_gocp_table(code_alc_t &alc, const Span *span, uint32_t nSpans);
CodeGoBm *code_gobm(code_alc_t &alc, const Span *span, uint32_t nSpans, const Span *hspan,
    uint32_t hSpans, const bitmap_t *bm, State *bm_state, State *next, bool sflag,
    uint32_t eof);
CodeGoSwIf *code_goswif(code_alc_t &alc, const Span *sp, uint32_t nsp, State *next,
    bool sflag, bool skip, uint32_t eof);
CodeGoIf *code_goif(code_alc_t &alc, CodeGoIf::Kind kind, const Span *sp, uint32_t nsp,
    State *next, bool skip, uint32_t eof);
CodeGoIfB *code_goifb(code_alc_t &alc, const Span *s, uint32_t n, State *next, bool skip,
    uint32_t eof);
CodeGoIfL *code_goifl(code_alc_t &alc, const Span *s, uint32_t n, State *next, bool skip,
    uint32_t eof);
CodeCmp *code_cmp(code_alc_t &alc, const char *cmp, uint32_t val);
CodeGoCases *code_gocases(code_alc_t &alc, const Span *spans, uint32_t nspans, bool skip,
    uint32_t eof);

// generate code for goto statements
void gen_go(Output &output, const DFA &dfa, const CodeGo *go, const State *from,
    CodeList *stmts);
void gen_godot(Output &output, const DFA &dfa, const CodeGoDot *go, const State *from,
    CodeList *stmts);
CodeList *gen_gocp(Output &output, const DFA &dfa, const CodeGoCp *go, const State *from);
CodeList *gen_gocp_table(Output &output, const CodeGoCpTable *go);
CodeList *gen_gobm(Output &output, const DFA &dfa, const CodeGoBm *go, const State *from);
CodeList *gen_goswif(Output &output, const DFA &dfa, const CodeGoSwIf *go,
    const State *from);
CodeList *gen_goif(Output &output, const DFA &dfa, const CodeGoIf *go, const State *from);
CodeList *gen_goifl(Output &output, const DFA &dfa, const CodeGoIfL *go,
    const State *from);
CodeList *gen_goifb(Output &output, const DFA &dfa, const CodeGoIfB *go,
    const State *from);
CodeList *gen_gocases(Output &output, const DFA &dfa, const CodeGoCases *go,
    const State *from);

bool consume(const State *s);

} // namespace re2c

#endif // _RE2C_CODE_GO_
