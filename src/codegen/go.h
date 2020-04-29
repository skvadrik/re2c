#ifndef _RE2C_CODE_GO_
#define _RE2C_CODE_GO_

#include <iostream>
#include <vector>

#include "src/codegen/output.h"
#include "src/dfa/tcmd.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"


namespace re2c {

struct DFA;
struct bitmap_t;
class bitmaps_t;
struct State;
struct If;

struct Span
{
    uint32_t ub;
    State * to;
    tcid_t tags;
};

struct Case
{
    std::vector<std::pair<uint32_t, uint32_t> > ranges;
    State *to;
    tcid_t tags;
    bool skip;
    bool eof;

    void emit(Output &o, uint32_t ind) const;
    inline Case(): ranges(), to(NULL), tags(TCID0), skip(false), eof(false) {}
    FORBID_COPY(Case);
};

struct Cases
{
    Case *cases;
    uint32_t cases_size;

    void add_case(uint32_t lb, const Span &sp, bool skip, uint32_t eof);
    Cases(const Span *spans, uint32_t nspans, bool skip, uint32_t eof);
    ~Cases();
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
    FORBID_COPY(Cases);
};

struct Cond
{
    std::string compare;
    uint32_t value;
    Cond (const std::string & cmp, uint32_t val);
};

struct Binary
{
    Cond * cond;
    If * thn;
    If * els;
    Binary(const Span *s, uint32_t n, State *next, bool skip, uint32_t eof);
    ~Binary ();
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
    FORBID_COPY (Binary);
};

struct Linear
{
    struct Branch
    {
        const Cond *cond;
        State *to;
        tcid_t tags;
        bool skip;
        bool eof;
    };

    size_t nbranches;
    Branch *branches;
    State *def;

    Linear(const Span *s, uint32_t n, State *next, bool skip, uint32_t eof);
    ~Linear();
    void add_branch(const Cond *cond, State *to, const Span &sp, bool skip, uint32_t eof);
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
    FORBID_COPY(Linear);
};

struct If
{
    enum type_t
    {
        BINARY,
        LINEAR
    } type;
    union
    {
        Binary * binary;
        Linear * linear;
    } info;
    If(type_t t, const Span *sp, uint32_t nsp, State *next, bool skip, uint32_t eof);
    ~If ();
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
};

struct SwitchIf
{
    enum
    {
        SWITCH,
        IF
    } type;
    union
    {
        Cases * cases;
        If * ifs;
    } info;
    SwitchIf(const Span *sp, uint32_t nsp, State *next, bool sflag, bool skip,
        uint32_t eof);
    ~SwitchIf ();
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
};

struct GoBitmap
{
    const bitmap_t * bitmap;
    State * bitmap_state;
    SwitchIf * hgo;
    SwitchIf * lgo;
    GoBitmap(const Span *span, uint32_t nSpans, const Span *hspan, uint32_t hSpans,
        const bitmap_t *bm, State *bm_state, State *next, bool sflag, uint32_t eof);
    ~GoBitmap ();
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
    FORBID_COPY (GoBitmap);
};

struct CpgotoTable
{
    static const uint32_t TABLE_SIZE;
    State **table;
    CpgotoTable (const Span * span, uint32_t nSpans);
    ~CpgotoTable ();
    CodeList *emit(Output &output) const;

private:
    uint32_t max_label() const;
    FORBID_COPY (CpgotoTable);
};

struct Cpgoto
{
    SwitchIf * hgo;
    CpgotoTable * table;
    Cpgoto (const Span *span, uint32_t nSpans, const Span *hspan, uint32_t hSpans,
        State *next, bool sflag, uint32_t eof);
    ~Cpgoto ();
    CodeList *emit(Output &output, const DFA &dfa, const State *from) const;
    FORBID_COPY (Cpgoto);
};

struct Dot
{
    Cases * cases;
    Dot(const Span *sp, uint32_t nsp, uint32_t eof);
    ~Dot ();
    void emit(Output &output, const DFA &dfa, const State *from, CodeList *stmts) const;
    FORBID_COPY (Dot);
};

struct Go
{
    uint32_t nSpans; // number of spans
    Span * span;
    tcid_t tags;
    bool skip;
    enum
    {
        EMPTY,
        SWITCH_IF,
        BITMAP,
        CPGOTO,
        DOT
    } type;
    union
    {
        SwitchIf * switchif;
        GoBitmap * bitmap;
        Cpgoto * cpgoto;
        Dot * dot;
    } info;

    Go ();
    ~Go ();
    void init(const State* from, const opt_t *opts, bitmaps_t &bitmaps);
    void emit (Output &output, const DFA &dfa, const State *from, CodeList *stmts) const;

    Go (const Go & g)
        : nSpans (g.nSpans)
        , span (g.span)
        , tags (g.tags)
        , skip (g.skip)
        , type (g.type)
        , info (g.info)
    {}
    Go & operator = (const Go & g)
    {
        nSpans = g.nSpans;
        span = g.span;
        tags = g.tags;
        skip = g.skip;
        type = g.type;
        info = g.info;
        return * this;
    }
};

bool consume(const State *s);

} // namespace re2c

#endif // _RE2C_CODE_GO_
