#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/encoding/case.h"
#include "src/encoding/enc.h"
#include "src/encoding/ebcdic.h"
#include "src/encoding/utf16.h"
#include "src/encoding/utf8.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/attribute.h"
#include "src/util/check.h"
#include "src/util/range.h"

// note [default regexp]
//
// Create a byte range that includes all possible input characters. This may include characters that
// do not map to any valid symbol in current encoding. For encodings that directly map symbols to
// input characters (ASCII, EBCDIC, UTF-32), it equals `[^]`. For other encodings (UTF-16, UTF-8)
// `[^]` and this range are different.
//
// Also note that default range doesn't respect encoding policy (the way invalid code points are
// treated).

// note [POSIX subexpression hierarchy]
//
// POSIX treats subexpressions with and without captures as equal, therefore we have to insert
// missing captures in subexpressions that influence disambiguation of existing captures. Such cases
// are: left alternative in union (unless it is already a capture) and first operand in
// concatenation (unless it is a capture). Of course, this insertion only applies to subexpressions
// that have nested captures.

namespace re2c {

struct loc_t;

namespace {

// On-stack information for iterative depth-first conversion of AST to RE.
struct DfsAstToRe {
    const AstNode* ast; // current subtree of the AST
    RE *re1;            // first sub-RE under construction
    RE *re2;            // second sub-RE under construction (used for alternative and catenation)
    int32_t height;     // height of the current sub-RE (used in POSIX disambiguation)
    uint8_t succ;       // index of the current successor node in AST
    bool in_iter;       // if this AST is under repetition

    DfsAstToRe(const AstNode* ast, int32_t height, bool in_iter)
        : ast(ast), re1(nullptr), re2(nullptr), height(height), succ(0), in_iter(in_iter) {}
};

// On-stack information for iterative depth-first conversion of character difference AST to Range.
struct DfsDiffToRange {
    const AstNode* ast; // current subtree of the AST
    Range* range;       // range under construction
    uint8_t succ;       // index of the current successor node in AST

    DfsDiffToRange(const AstNode* ast)
        : ast(ast), range(nullptr), succ(0) {}
};

LOCAL_NODISCARD(RE* fictive_tags(RESpec& spec, int32_t height)) {
    std::vector<Tag>& tags = spec.tags;

    // opening fictive tag
    RE* t1 = re_tag(spec, tags.size(), false);
    tags.emplace_back(Tag::FICTIVE, Tag::FICTIVE, false, false, height + 1);

    // closing fictive tag
    RE* t2 = re_tag(spec, tags.size(), false);
    tags.emplace_back(Tag::FICTIVE, Tag::FICTIVE, false, false, height);

    return re_cat(spec, t1, t2);
}

LOCAL_NODISCARD(RE* capture_tags(
        RESpec& spec, DfsAstToRe& x, bool orbit, const AstNode** psub, size_t* pncap)) {
    std::vector<Tag>& tags = spec.tags;
    bool history = spec.opts->subhistories && (orbit || x.in_iter);
    size_t ncap = *pncap, lcap = ncap;

    const AstNode* ast = *psub;
    if (ast->kind == AstKind::CAP) {
        // save the range of repeated captures and collapse them: (...(R)...) -> (R)
        for (ast = ast->cap; ast && ast->kind == AstKind::CAP; ast = ast->cap) {
            ++ncap;
        }
        // dereference to avoid future check for non-parenthesized rerefences
        if (ast->kind == AstKind::REF) {
            ast = ast->ref.ast;
        }
        *psub = ast;
    }

    // opening capture tag
    RE* t1 = re_tag(spec, tags.size(), false);
    tags.emplace_back(2 * lcap, 2 * ncap, history, orbit, x.height + 1);

    // closing capture tag
    RE* t2 = re_tag(spec, tags.size(), false);
    tags.emplace_back(2 * lcap + 1, 2 * ncap + 1, history, orbit, x.height);

    *pncap = ncap + 1;
    return re_cat(spec, t1, t2);
}

LOCAL_NODISCARD(RE* structural_tags(
        RESpec& spec, DfsAstToRe& x, const AstNode* sub, size_t* pncap)) {
    if (sub->kind == AstKind::CAP) {
        // If this sub-AST is already a capture, no need for structural tags.
    } else if (spec.opts->autotags) {
        // Full parsing: automatically add tags as if this sub-RE was a capture.
        return capture_tags(spec, x, false, &x.ast, pncap);
    } else if (spec.opts->posix_semantics && x.ast->has_caps) {
        // POSIX submatch extraction: add fictive structural tags.
        // See note [POSIX subexpression hierarchy].
        return fictive_tags(spec, x.height);
    }
    return nullptr;
}

// Insert a RE in between a pair of concatenated tags. If there are no tags, just return the RE.
LOCAL_NODISCARD(RE* insert_between_tags(RESpec& spec, RE* tags, RE* re)) {
    if (tags == nullptr) {
        return re;
    } else if (re != nullptr) {
        DCHECK(tags->kind == RE::Kind::CAT);
        DCHECK(tags->cat.re1->kind == RE::Kind::TAG);
        DCHECK(tags->cat.re2->kind == RE::Kind::TAG);
        tags->cat.re2 = re_cat(spec, re, tags->cat.re2);
        if (spec.opts->backward) { // undo the reverse done by concatenation
            std::swap(tags->cat.re2->cat.re1, tags->cat.re2->cat.re2);
        }
    }
    return tags;
}

LOCAL_NODISCARD(Ret check_misuse_of_named_def(RESpec& spec, const AstNode* ast)) {
    DCHECK(ast->kind == AstKind::REF);
    if (spec.opts->posix_syntax) {
        RET_FAIL(spec.msg.error(ast->loc,
                                "implicit grouping is forbidden with '--posix-captures' option, "
                                "please wrap '%s' in capturing parenthesis",
                                ast->ref.name));
    }
    return Ret::OK;
}

LOCAL_NODISCARD(Ret check_tags_used_once(
        RESpec& spec, const Rule& rule, const std::vector<Tag>& tags)) {
    std::set<std::string> names;
    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const char* name = tags[t].name;
        if (name && !names.insert(name).second) {
            RET_FAIL(spec.msg.error(rule.semact->loc,
                                    "tag '%s' is used multiple times in the same rule",
                                    name));
        }
    }
    return Ret::OK;
}

bool is_icase(const opt_t* opts, bool icase) {
    return opts->bCaseInsensitive || icase != opts->bCaseInverted;
}

LOCAL_NODISCARD(Ret char_to_range(RESpec& spec, const AstChar& chr, bool icase, Range** prange)) {
    RangeMgr& rm = spec.rangemgr;
    uint32_t c = chr.chr;

    if (!spec.opts->encoding.validateChar(c)) {
        RET_FAIL(spec.msg.error(chr.loc, "bad code point: '0x%X'", c));
    }

    *prange = icase && is_alpha(c)
           ? rm.add(rm.sym(to_lower_unsafe(c)), rm.sym(to_upper_unsafe(c))) : rm.sym(c);
    return Ret::OK;
}

LOCAL_NODISCARD(Ret cls_to_range(RESpec& spec, const AstNode* ast, Range** prange)) {
    DCHECK(ast->kind == AstKind::CLS);
    RangeMgr& rm = spec.rangemgr;
    Range *r = nullptr;

    for (const AstRange& a : ast->cls.ranges) {
        Range* s = spec.opts->encoding.validateRange(rm, a.lower, a.upper);
        if (!s) {
            RET_FAIL(spec.msg.error(a.loc,
                                    "bad code point range: '0x%X - 0x%X'", a.lower, a.upper));
        }
        r = rm.add(r, s);
    }

    if (ast->cls.negated) {
        r = rm.sub(spec.opts->encoding.fullRange(rm), r);
    }

    *prange = r;
    return Ret::OK;
}

LOCAL_NODISCARD(Ret dot_to_range(RESpec& spec, const AstNode* ast, Range** prange)) {
    DCHECK(ast->kind == AstKind::DOT);
    RangeMgr& rm = spec.rangemgr;
    uint32_t c = '\n';

    if (!spec.opts->encoding.validateChar(c)) {
        RET_FAIL(spec.msg.error(ast->loc, "bad code point: '0x%X'", c));
    }

    *prange = rm.sub(spec.opts->encoding.fullRange(rm), rm.sym(c));
    return Ret::OK;
}

LOCAL_NODISCARD(Ret re_class(RESpec& spec, const loc_t& loc, const Range* range, RE** pre)) {
    if (!range) {
        switch (spec.opts->empty_class_policy) {
        case EmptyClassPolicy::MATCH_EMPTY:
            spec.msg.warn.empty_class(loc);
            *pre = re_nil(spec);
            return Ret::OK;
        case EmptyClassPolicy::MATCH_NONE:
            spec.msg.warn.empty_class(loc);
            break;
        case EmptyClassPolicy::ERROR:
            RET_FAIL(spec.msg.error(loc, "empty character class"));
        }
    }

    switch (spec.opts->encoding.type()) {
    case Enc::Type::UTF16:
        *pre = utf16::range(spec, range);
        break;
    case Enc::Type::UTF8:
        *pre = utf8::range(spec, range);
        break;
    case Enc::Type::EBCDIC:
        *pre = ebcdic::range(spec, range);
        break;
    case Enc::Type::ASCII:
    case Enc::Type::UTF32:
    case Enc::Type::UCS2:
        *pre = re_sym(spec, range);
        break;
    }

    return Ret::OK;
}

LOCAL_NODISCARD(Ret re_string(RESpec& spec, const AstNode* ast, RE** pre)) {
    DCHECK(ast->kind == AstKind::STR);

    RE* x = nullptr;
    bool icase = is_icase(spec.opts, ast->str.icase);

    for (const AstChar& a : ast->str.chars) {
        Range* r;
        CHECK_RET(char_to_range(spec, a, icase, &r));
        RE* y;
        CHECK_RET(re_class(spec, ast->loc, r, &y));
        x = re_cat(spec, x, y);
    }

    *pre = x ? x : re_nil(spec);
    return Ret::OK;
}

LOCAL_NODISCARD(Ret diff_to_range(RESpec& spec,
                                  std::vector<DfsDiffToRange>& stack,
                                  const AstNode* ast0,
                                  Range** prange)) {
    DCHECK(stack.empty());
    stack.emplace_back(ast0);

    Range *range = nullptr;

    while (!stack.empty()) {
        // Ensure that the reference to stack top won't be accidentally invalidated on push.
        if (stack.size() == stack.capacity()) stack.reserve(stack.size() * 2);
        DfsDiffToRange& x = stack.back();

        const AstNode* ast = x.ast;
        switch (ast->kind) {
        case AstKind::NIL:
        case AstKind::DEF:
        case AstKind::TAG:
        case AstKind::CAT:
        case AstKind::ITER:
            goto error;

        case AstKind::CLS:
            CHECK_RET(cls_to_range(spec, ast, &range));
            stack.pop_back();
            break;

        case AstKind::DOT:
            CHECK_RET(dot_to_range(spec, ast, &range));
            stack.pop_back();
            break;

        case AstKind::STR:
            if (ast->str.chars.size() != 1) goto error;
            CHECK_RET(char_to_range(
                    spec, ast->str.chars.front(), is_icase(spec.opts, ast->str.icase), &range));
            stack.pop_back();
            break;

        case AstKind::CAP:
            if (spec.opts->posix_syntax) goto error;
            x.ast = ast->cap; // replace on stack
            break;

        case AstKind::REF:
            CHECK_RET(check_misuse_of_named_def(spec, ast));
            x.ast = ast->ref.ast; // replace on stack
            break;

        case AstKind::DIFF:
            if (x.succ == 0) { // 1st visit: push 1st successor
                ++x.succ;
                stack.emplace_back(ast->diff.ast1);
            } else if (x.succ == 1) { // 2nd visit: push 2nd successor
                ++x.succ;
                x.range = range;
                stack.emplace_back(ast->diff.ast2);
            } else { // 3rd visit: return
                range = spec.rangemgr.sub(x.range, range); // can handle nullptr args
                stack.pop_back();
            }
            break;

        case AstKind::ALT:
            if (x.succ == 0) { // 1st visit: push 1st successor
                ++x.succ;
                stack.emplace_back(ast->alt.ast1);
            } else if (x.succ == 1) { // 2nd visit: push 2nd successor
                ++x.succ;
                x.range = range;
                stack.emplace_back(ast->alt.ast2);
            } else { // 3rd visit: return
                range = spec.rangemgr.add(x.range, range); // can handle nullptr args
                stack.pop_back();
            }
            break;

error:
            RET_FAIL(spec.msg.error(ast->loc, "can only difference char sets"));
        }
    }

    *prange = range;
    return Ret::OK;
}

LOCAL_NODISCARD(Ret ast_to_re(RESpec& spec,
                              std::vector<DfsAstToRe>& stack,
                              std::vector<DfsDiffToRange>& stack_diff,
                              const AstNode* ast0,
                              size_t* pncap,
                              RE** presult)) {
    std::vector<Tag>& tags = spec.tags;
    const opt_t* opts = spec.opts;
    Range* range;
    RE* re;

    DCHECK(stack.empty());
    stack.emplace_back(ast0, 0, false);

    while (!stack.empty()) {
        // Ensure that the reference to stack top won't be accidentally invalidated on push.
        if (stack.size() == stack.capacity()) stack.reserve(stack.size() * 2);
        DfsAstToRe& x = stack.back();

        const AstNode* ast = x.ast;

        if (ast->kind != AstKind::CAP && ast->kind != AstKind::REF) ++x.height;

        switch (ast->kind) {
        case AstKind::NIL:
            re = re_nil(spec);
            stack.pop_back();
            break;

        case AstKind::STR:
            CHECK_RET(re_string(spec, ast, &re));
            stack.pop_back();
            break;

        case AstKind::CLS:
            CHECK_RET(cls_to_range(spec, ast, &range));
            CHECK_RET(re_class(spec, ast->loc, range, &re));
            stack.pop_back();
            break;

        case AstKind::DOT:
            CHECK_RET(dot_to_range(spec, ast, &range));
            CHECK_RET(re_class(spec, ast->loc, range, &re));
            stack.pop_back();
            break;

        case AstKind::DEF: // see note [default regexp]
            range = spec.rangemgr.ran(0, opts->encoding.nCodeUnits());
            re = re_sym(spec, range);
            stack.pop_back();
            break;

        case AstKind::DIFF:
            CHECK_RET(diff_to_range(spec, stack_diff, ast, &range));
            CHECK_RET(re_class(spec, ast->loc, range, &re));
            stack.pop_back();
            break;

        case AstKind::TAG:
            if (ast->tag.name && !opts->tags) {
                RET_FAIL(spec.msg.error(
                        ast->loc, "tags are only allowed with '-T, --tags' option"));
            } else if (opts->posix_syntax) {
                RET_FAIL(spec.msg.error(
                        ast->loc, "simple tags are not allowed with '--posix-captures' option"));
            }
            re = re_tag(spec, tags.size(), false);
            tags.emplace_back(ast->tag.name, ast->tag.history, x.height);
            stack.pop_back();
            break;

        case AstKind::CAP:
            if (!opts->posix_syntax) { // ordinary group, replace with subexpr on stack
                x.ast = ast->cap;
            } else { // POSIX capturing group
                if (x.succ == 0) { // 1st visit: push successor
                    ++x.succ;
                    x.re1 = capture_tags(spec, x, false, &ast, pncap);
                    stack.emplace_back(ast,  x.height, x.in_iter);
                } else { // 2nd visit: return
                    re = insert_between_tags(spec, x.re1, re);
                    stack.pop_back();
                }
            }
            break;

        case AstKind::REF:
            CHECK_RET(check_misuse_of_named_def(spec, ast));
            x.ast = ast->ref.ast;
            break;

        case AstKind::ALT:
            if (x.succ == 0) { // 1st visit: push first successor
                ++x.succ;
                x.re1 = structural_tags(spec, x, ast->alt.ast1, pncap);
                stack.emplace_back(ast->alt.ast1, x.height, x.in_iter);
            } else if (x.succ == 1) { // 2nd visit: push second successor
                ++x.succ;
                x.re1 = insert_between_tags(spec, x.re1, re);
                x.re2 = structural_tags(spec, x, ast->alt.ast2, pncap);
                stack.emplace_back(ast->alt.ast2, x.height, x.in_iter);
            } else { // 3rd visit: return
                x.re2 = insert_between_tags(spec, x.re2, re);
                re = re_alt(spec, x.re1, x.re2);
                stack.pop_back();
            }
            break;

        case AstKind::CAT:
            if (x.succ == 0) { // 1st visit: push first successor
                ++x.succ;
                x.re1 = structural_tags(spec, x, ast->cat.ast1, pncap);
                stack.emplace_back(ast->cat.ast1, x.height, x.in_iter);
            } else if (x.succ == 1) { // 2nd visit: push second successor
                ++x.succ;
                x.re1 = insert_between_tags(spec, x.re1, re);
                x.re2 = structural_tags(spec, x, ast->cat.ast2, pncap);
                stack.emplace_back(ast->cat.ast2, x.height, x.in_iter);
            } else { // 3rd visit: return
                x.re2 = insert_between_tags(spec, x.re2, re);
                re = re_cat(spec, x.re1, x.re2);
                stack.pop_back();
            }
            break;

        case AstKind::ITER:
            DCHECK(ast->iter.min <= ast->iter.max);
            if (x.succ == 0) { // 1st visit: push successor
                ++x.succ;
                const uint32_t m = ast->iter.max;
                ast = ast->iter.ast;
                if ((opts->posix_semantics && ast->kind == AstKind::CAP) || opts->autotags) {
                    x.re1 = capture_tags(spec, x, m > 1, &ast, pncap);
                }
                if (m > 0) {
                    stack.emplace_back(ast, x.height, true);
                } else {
                    re = nullptr;
                }
            } else { // 2nd visit: return
                const uint32_t n = ast->iter.min;
                const uint32_t m = ast->iter.max;
                re = insert_between_tags(spec, x.re1, re);
                if (m > 1) {
                    re = re_iter(spec, re, std::max(n, 1u), m);
                }
                if (n == 0) {
                    re = re_alt(spec, re, re_nil(spec));
                }
                stack.pop_back();
            }
            break;
        }

    }

    *presult = re;
    return Ret::OK;
}

} // anonymous namespace

RESpec::RESpec(const opt_t* opts, Msg& msg)
    : ir_alc(), rangemgr(ir_alc), res(), charset(), tags(), rules(), opts(opts), msg(msg) {}

Ret RESpec::init(const std::vector<AstRule>& ast) {
    rules.resize(ast.size());
    std::vector<DfsAstToRe> stack;
    std::vector<DfsDiffToRange> stack_diff;
    for (size_t i = 0; i < ast.size(); ++i) {
        size_t ltag = tags.size(), ncap = 0;
        RE* re;
        CHECK_RET(ast_to_re(*this, stack, stack_diff, ast[i].ast, &ncap, &re));
        res.push_back(re);

        // init rule
        Rule& rule = rules[i];
        rule.semact = ast[i].semact;
        rule.ltag = ltag;
        rule.htag = tags.size();
        for (rule.ttag = ltag; rule.ttag < rule.htag && !trailing(tags[rule.ttag]); ++rule.ttag);
        rule.ncap = ncap;
        CHECK_RET(check_tags_used_once(*this, rule, tags));
    }
    return Ret::OK;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr size_t Tag::RIGHTMOST;
constexpr size_t Tag::FICTIVE;
constexpr size_t Tag::NONE;
constexpr uint32_t Tag::VARDIST;
constexpr size_t Rule::NONE;

} // namespace re2c
