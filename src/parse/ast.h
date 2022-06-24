#ifndef _RE2C_AST_AST_
#define _RE2C_AST_AST_

#include <stdint.h>
#include <set>
#include <vector>

#include "src/msg/location.h"
#include "src/regexp/rule.h"
#include "src/util/allocator.h"
#include "src/util/containers.h"

namespace re2c {

// AST node kinds.
enum class AstKind: uint32_t {
    NIL,  // empty (nil) node
    STR,  // character string, like "abc" or 'abc'
    CLS,  // character class, like [a-z] or [^a-z]
    DOT,  // any character except newline
    DEF,  // default rule *, matches any code unit, see note [default regexp]
    ALT,  // alternative of two nodes: x | y
    CAT,  // concatenation of two nodes: x y
    ITER, // generalized repetition of two nodes: x{n,m} or x{n,} or x{n} or x* or x+
    DIFF, // difference of two node (only applies to character classes)
    TAG,  // a tag, like @t (s-tag, single-valued tag) or #t (m-tag. multi-valued tag)
    CAP,  // capturing group (submatch group)
    REF   // non-capturing group
};

struct AstChar {
    uint32_t chr;
    loc_t loc;
};

struct AstRange {
    uint32_t lower;
    uint32_t upper;
    loc_t loc;

    AstRange(uint32_t low, uint32_t upp, const loc_t& loc)
        : lower(low), upper(upp), loc(loc) {}
};

struct AstBounds {
    uint32_t min;
    uint32_t max;
};

// AST nodes must be immutable and independent of block options, as they may be shared by different
// rules in blocks with different options.
struct AstNode {
    AstKind kind;
    union {
        struct {
            array_t<AstChar> chars;
            bool icase;
        } str;
        struct {
            array_t<AstRange> ranges;
            bool negated;
        } cls;
        struct {
            const AstNode* ast1;
            const AstNode* ast2;
        } alt;
        struct {
            const AstNode* ast1;
            const AstNode* ast2;
        } cat;
        struct {
            const AstNode* ast;
            uint32_t min;
            uint32_t max;
        } iter;
        struct {
            const AstNode* ast1;
            const AstNode* ast2;
        } diff;
        struct {
            const char* name;
            bool history;
        } tag;
        const AstNode* cap;
        struct {
            const AstNode* ast;
            const char* name;
        } ref;
    };
    loc_t loc;
};

struct AstRule {
    const AstNode* ast;
    const SemAct* semact;

    AstRule(const AstNode* a, const SemAct* s): ast(a), semact(s) {}
};

// Abstract Syntax Tree.
class Ast {
  private:
    // Allocator used for allocating AST nodes. All memory is freed when the allocator is destroyed
    // (which happens after parsing and processing the whole translation unit, but before codegen).
    using alc_t = slab_allocator_t</*SLAB_SIZE*/ 1024 * 1024, /*ALIGN*/ sizeof(void*)>;
    alc_t allocator;

    AstNode* make(const loc_t& loc, AstKind lind);

  public:
    // Temporary buffers for constructing character strings and classes in lexer/parser. Generally
    // LALR(1) parser requires a stack of nonterminals (a single value is insufficient) but these
    // nonterminals cannot occur twice on the parser stack before a reduction happens (which we
    // ensure by checking that a buffer is empty before using it).
    std::vector<AstChar> temp_chars;
    std::vector<AstRange> temp_ranges;
    std::set<std::string> temp_condlist; // must be ordered, as condition order matters
    std::string temp_blockname;

    // Used to denote unbounded repetition (iteration, Kleene star).
    static constexpr uint32_t MANY = std::numeric_limits<uint32_t>::max();

    Ast(): allocator(), temp_chars(), temp_ranges(), temp_condlist(), temp_blockname() {}

    // Methods for constructing individual AST nodes.
    const AstNode* nil(const loc_t& loc);
    const AstNode* str(const loc_t& loc, bool icase);
    const AstNode* cls(const loc_t& loc, bool negated);
    const AstNode* dot(const loc_t& loc);
    const AstNode* def(const loc_t& loc);
    const AstNode* alt(const AstNode* a1, const AstNode* a2);
    const AstNode* cat(const AstNode* a1, const AstNode* a2);
    const AstNode* iter(const AstNode* a, uint32_t n, uint32_t m);
    const AstNode* diff(const AstNode* a1, const AstNode* a2);
    const AstNode* tag(const loc_t& loc, const char* n, bool h);
    const AstNode* cap(const AstNode* a);
    const AstNode* ref(const AstNode* a, const char* n);
    const SemAct* sem_act(const loc_t& loc, const char* text, const char* cond, bool autogen);
    const char* cstr(const char* s, const char* e);

    // Whether this AST node must be wrapped in implicit parentheses to ensure correct operator
    // precedence. This happens with named definitions, for example `x = "a"|"aa"` used in `x "b"`
    // is parsed as `("a"|"aa")"b"`, not `"a"|"aab"`. However, such implicit groups do no exist in
    // POSIX regular expressions, so re2c warns if the user accidentally creates one.
    static bool needs_wrap(const AstNode* a);
};

} // namespace re2c

#endif // _RE2C_AST_AST_
