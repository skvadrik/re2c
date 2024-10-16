#ifndef _RE2C_AST_AST_
#define _RE2C_AST_AST_

#include <stdint.h>
#include <set>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/msg/location.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/containers.h"

namespace re2c {

class Msg;
class Input;
struct Opt;
struct opt_t;
struct SemAct;

// Kinds of abstract syntax tree nodes.
enum class AstKind: uint32_t {
    NIL,  // empty (nil) node
    STR,  // character string, like "abc" (case sensitive) or 'abc' (case insensitive)
    CLS,  // character class, like [ac-z], possibly negated, like [^ac-z]
    DOT,  // any character except newline
    DEF,  // default rule *, matches any code unit, see note [default regexp]
    ALT,  // alternative of two nodes: x | y
    CAT,  // concatenation of two nodes: x y
    ITER, // generalized repetition of two nodes: x{n,m} or x{n,} or x{n} or x* or x+
    DIFF, // difference of two node (only applies to character classes)
    TAG,  // a tag, like @t (s-tag, single-valued tag) or #t (m-tag. multi-valued tag)
    CAP   // capturing or non-capturing group
};

// A character (symbol) in the abstract syntax tree.
struct AstChar {
    uint32_t chr;
    loc_t loc;
};

// A range of characters (symbols) in the abstract syntax tree.
struct AstRange {
    uint32_t lower;
    uint32_t upper;
    loc_t loc;

    AstRange(uint32_t low, uint32_t upp, const loc_t& loc)
        : lower(low), upper(upp), loc(loc) {}
};

// Abstract syntax tree node for counted repetition bounds (upper bound possibly infinite).
struct AstBounds {
    uint32_t min;
    uint32_t max;
};

// Nodes of the abstract syntax tree. Generally AST must be immutable and independent of block
// options, as it may be shared by different rules in blocks with different options.
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
        struct {
            const AstNode* ast;
            CaptureMode mode;
        } cap;
    };
    loc_t loc;

    // Whether this AST has nested capturing groups (a combination of `CaptureMode` bit flags
    // accumulated from the nested regexp).
    uint8_t has_caps;
};

// Semanic action associated with an AST for a regular expression.
struct AstRule {
    const AstNode* ast;
    const SemAct* semact;

    AstRule(const AstNode* a, const SemAct* s): ast(a), semact(s) {}
};

// Regular grammar (a set of rules: regular expressions associated with semantic actions).
struct AstGram {
    std::string name;

    // Normal rules specified in this block or inherited from other blocks.
    std::vector<AstRule> rules;

    // Special rules *, $ and <!> specified in this block.
    std::vector<const SemAct*> defs;
    std::vector<const SemAct*> eofs;
    std::vector<const SemAct*> setup;

    // Special rules *, $ and <!>  inherited from other blocks.
    std::vector<const SemAct*> inherited_defs;
    std::vector<const SemAct*> inherited_eofs;
    std::vector<const SemAct*> inherited_setup;

    size_t def_rule;
    size_t eof_rule;

    explicit AstGram(const std::string& name);
};

using AstGrams = std::vector<AstGram>;

// Input program block (e.g. within `/*!re2c` and `*/` comments). May include one or more grammars.
// Multiple grammars within one block are possible if start conditions are used (in that case each
// grammar has a non-empty name), otherwise there is a single grammar with an empty name.
struct AstBlock {
    std::string name;
    const opt_t* opts;
    AstGrams grams;

    AstBlock(const std::string& name, const opt_t* opts, const AstGrams& grams);
    FORBID_COPY(AstBlock);
};

struct AstBlocks {
    std::vector<AstBlock*> blocks;

  public:
    AstBlocks();
    ~AstBlocks();
    bool empty() const;
    void add(const std::string& name, const opt_t* opts, const AstGrams& grams);
    const AstBlock* find(const std::string& name) const;
    const opt_t* last_opts() const;
};

// Abstract Syntax Tree.
class Ast {
  private:
    // Allocator used for allocating AST nodes. All memory is freed when the allocator is destroyed
    // (which happens after parsing and processing the whole translation unit, but before codegen).
    AstAllocator& ast_alc;
    // Output allocator is needed for long-lived objects that are allocated during parsing and need
    // survive until the main codegen pass (e.g. semantic actions, condition names, tag names).
    OutAllocator& out_alc;

    AstNode* make(const loc_t& loc, AstKind kind, uint8_t has_caps);

  public:
    // Temporary buffers for constructing character strings and classes in lexer/parser. Generally
    // LALR(1) parser requires a stack of nonterminals (a single value is insufficient) but these
    // nonterminals cannot occur twice on the parser stack before a reduction happens (which we
    // ensure by checking that a buffer is empty before using it).
    std::vector<AstChar> temp_chars;
    std::vector<AstRange> temp_ranges;
    std::set<std::string> temp_condlist; // must be ordered, as condition order matters
    std::string temp_blockname;

    // A list of `rules` blocks (other blocks don't need to be stored as they are not reused).
    AstBlocks blocks;

    // Used to denote unbounded repetition (iteration, Kleene star).
    static constexpr uint32_t MANY = std::numeric_limits<uint32_t>::max();

    Ast(AstAllocator& ast_alc, OutAllocator& out_alc);

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
    const AstNode* cap(const AstNode* a, CaptureMode mode);
    const SemAct* sem_act(const loc_t& loc, const char* text, const char* cond, bool autogen);

    // Local and global strings differ in their lifetimes: local ones live during AST construction,
    // while global ones are used much later in codegen (they use a different allocator).
    const char* cstr_local(const uint8_t* s, const uint8_t* e);
    const char* cstr_global(const uint8_t* s, const uint8_t* e);

    // Whether this AST node must be wrapped in implicit parentheses to ensure correct operator
    // precedence. This happens with named definitions, for example `x = "a"|"aa"` used in `x "b"`
    // is parsed as `("a"|"aa")"b"`, not `"a"|"aab"`. However, such implicit groups do no exist in
    // POSIX regular expressions, so re2c warns if the user accidentally creates one.
    static bool needs_wrap(const AstNode* a);
};

AstGram& find_or_add_gram(AstGrams& grams, const std::string& name);
Ret use_block(
    Input& input, const Ast& ast, Opt& opts, AstGrams& grams, const std::string& name) NODISCARD;
Ret check_and_merge_special_rules(AstGrams& grams, const opt_t* opts, Msg& msg, Ast& ast) NODISCARD;
Ret parse(Input& input, Ast& ast, Opt& opts, AstGrams& grams) NODISCARD;

} // namespace re2c

#endif // _RE2C_AST_AST_
