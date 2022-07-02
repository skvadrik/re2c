#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/debug/debug.h"
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
#include "src/util/range.h"

namespace re2c {

struct loc_t;

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

static Ret ast_to_re(RESpec&, const AstNode*, size_t&, int32_t, bool, RE*&) NODISCARD;
static Ret re_string(RESpec&, const AstNode*, RE*&) NODISCARD;
static Ret re_class(RESpec&, const loc_t&, const Range*, RE*&) NODISCARD;
static Ret ast_to_range(RESpec&, const AstNode*, Range*&) NODISCARD;
static Ret char_to_range(RESpec&, const AstChar&, bool, Range*&) NODISCARD;
static Ret diff_to_range(RESpec&, const AstNode*, Range*&) NODISCARD;
static Ret dot_to_range(RESpec&, const AstNode*, Range*&) NODISCARD;
static Ret cls_to_range(RESpec&, const AstNode*, Range*&) NODISCARD;
static Ret check_misuse_of_named_def(RESpec&, const AstNode*) NODISCARD;
static Ret check_tags_used_once(RESpec&, const Rule&, const std::vector<Tag>&) NODISCARD;
static bool is_icase(const opt_t*, bool);

static bool has_tags(const AstNode* ast) {
    switch (ast->kind) {
    case AstKind::NIL:
    case AstKind::STR:
    case AstKind::CLS:
    case AstKind::DOT:
    case AstKind::DEF:
    case AstKind::DIFF:
        return false;
    case AstKind::TAG:
    case AstKind::CAP:
        return true;
    case AstKind::ALT:
        return has_tags(ast->alt.ast1) || has_tags(ast->alt.ast2);
    case AstKind::CAT:
        return has_tags(ast->cat.ast1) || has_tags(ast->cat.ast2);
    case AstKind::REF:
        return has_tags(ast->ref.ast);
    case AstKind::ITER:
        return has_tags(ast->iter.ast);
    }
    return false; // unreachable
}

static void add_fictive_tags(RESpec& spec, int32_t height, RE** ptag1, RE** ptag2) {
    std::vector<Tag>& tags = spec.tags;

    // opening fictive tag
    *ptag1 = re_tag(spec, tags.size(), false);
    tags.push_back(Tag(Tag::FICTIVE, Tag::FICTIVE, false, false, height + 1));

    // closing fictive tag
    *ptag2 = re_tag(spec, tags.size(), false);
    tags.push_back(Tag(Tag::FICTIVE, Tag::FICTIVE, false, false, height));
}

static void add_capture_tags(RESpec& spec,
                             const AstNode** past,
                             size_t& ncap,
                             int32_t height,
                             RE** ptag1,
                             RE** ptag2,
                             bool orbit,
                             bool in_iter) {
    std::vector<Tag>& tags = spec.tags;
    const size_t lcap = ncap;

    const AstNode* ast = *past;
    if (ast->kind == AstKind::CAP) {
        // save the range of repeated captures and collapse them: (...(R)...) -> (R)
        for (ast = ast->cap; ast && ast->kind == AstKind::CAP; ast = ast->cap) {
            ++ncap;
        }
        // dereference to avoid future check for non-parenthesized rerefences
        if (ast->kind == AstKind::REF) {
            ast = ast->ref.ast;
        }
        *past = ast;
    }

    bool history = spec.opts->subhistories && (orbit || in_iter);

    // opening capture tag
    *ptag1 = re_tag(spec, tags.size(), false);
    tags.push_back(Tag(2 * lcap, 2 * ncap, history, orbit, height + 1));

    // closing capture tag
    *ptag2 = re_tag(spec, tags.size(), false);
    tags.push_back(Tag(2 * lcap + 1, 2 * ncap + 1, history, orbit, height));

    ++ncap;
}

static inline void add_structural_tags(RESpec& spec,
                                       const AstNode** past,
                                       size_t& ncap,
                                       int32_t height,
                                       RE** ptag1,
                                       RE** ptag2,
                                       bool orbit,
                                       bool in_iter) {
    if (spec.opts->autotags) {
        // Full parsing: automatically add tags as if this sub-RE was a capture.
        add_capture_tags(spec, past, ncap, height, ptag1, ptag2, orbit, in_iter);
    } else if (spec.opts->posix_semantics && has_tags(*past)) {
        // POSIX submatch extraction: add fictive structural tags.
        // See note [POSIX subexpression hierarchy].
        add_fictive_tags(spec, height, ptag1, ptag2);
    }
}

Ret ast_to_re(
        RESpec& spec, const AstNode* ast, size_t& ncap, int32_t height, bool in_iter, RE*& re) {
    std::vector<Tag>& tags = spec.tags;
    const opt_t* opts = spec.opts;
    Range* r;

    if (ast->kind != AstKind::CAP && ast->kind != AstKind::REF) ++height;

    switch (ast->kind) {
    case AstKind::NIL:
        re = re_nil(spec);
        return Ret::OK;

    case AstKind::STR:
        return re_string(spec, ast, re);

    case AstKind::CLS:
        CHECK_RET(cls_to_range(spec, ast, r));
        return re_class(spec, ast->loc, r, re);

    case AstKind::DOT:
        CHECK_RET(dot_to_range(spec, ast, r));
        return re_class(spec, ast->loc, r, re);

    case AstKind::DEF:
        // see note [default regexp]
        r = spec.rangemgr.ran(0, opts->encoding.nCodeUnits());
        re = re_sym(spec, r);
        return Ret::OK;

    case AstKind::DIFF:
        CHECK_RET(diff_to_range(spec, ast, r));
        return re_class(spec, ast->loc, r, re);

    case AstKind::ALT: {
        RE* t1 = nullptr, *t2 = nullptr, *t3 = nullptr, *t4 = nullptr, *x, *y;

        if (ast->alt.ast1->kind != AstKind::CAP) {
            add_structural_tags(spec, &ast, ncap, height, &t1, &t2, false, in_iter);
        }
        CHECK_RET(ast_to_re(spec, ast->alt.ast1, ncap, height, in_iter, x));
        x = re_cat(spec, t1, re_cat(spec, x, t2));

        if (ast->alt.ast2->kind != AstKind::CAP) {
            add_structural_tags(spec, &ast, ncap, height, &t3, &t4, false, in_iter);
        }
        CHECK_RET(ast_to_re(spec, ast->alt.ast2, ncap, height, in_iter, y));
        y = re_cat(spec, t3, re_cat(spec, y, t4));

        re = re_alt(spec, x, y);
        return Ret::OK;
    }

    case AstKind::CAT: {
        RE* t1 = nullptr, *t2 = nullptr, *t3 = nullptr, *t4 = nullptr, *x, *y;

        if (ast->cat.ast1->kind != AstKind::CAP) {
            add_structural_tags(spec, &ast, ncap, height, &t1, &t2, false, in_iter);
        }
        CHECK_RET(ast_to_re(spec, ast->cat.ast1, ncap, height, in_iter, x));
        x = re_cat(spec, t1, re_cat(spec, x, t2));

        if (ast->cat.ast2->kind != AstKind::CAP) {
            add_structural_tags(spec, &ast, ncap, height, &t3, &t4, false, in_iter);
        }
        CHECK_RET(ast_to_re(spec, ast->cat.ast2, ncap, height, in_iter,y));
        y = re_cat(spec, t3, re_cat(spec, y, t4));

        re = re_cat(spec, x, y);
        return Ret::OK;
    }

    case AstKind::TAG:
        if (ast->tag.name && !opts->tags) {
            RET_FAIL(spec.msg.error(ast->loc, "tags are only allowed with '-T, --tags' option"));
        }
        if (opts->posix_syntax) {
            RET_FAIL(spec.msg.error(ast->loc,
                                    "simple tags are not allowed with '--posix-captures' option"));
        }
        re = re_tag(spec, tags.size(), false);
        tags.push_back(Tag(ast->tag.name, ast->tag.history, height));
        return Ret::OK;

    case AstKind::CAP:
        if (!opts->posix_syntax) {
            return ast_to_re(spec, ast->cap, ncap, height, in_iter, re);
        } else {
            RE* y = nullptr, *t1 = nullptr, *t2 = nullptr;
            add_capture_tags(spec, &ast, ncap, height, &t1, &t2, false, in_iter);
            CHECK_RET(ast_to_re(spec, ast, ncap, height, in_iter, y));
            re = re_cat(spec, t1, re_cat(spec, y, t2));
        }
        return Ret::OK;

    case AstKind::REF:
        CHECK_RET(check_misuse_of_named_def(spec, ast));
        return ast_to_re(spec, ast->ref.ast, ncap, height, in_iter, re);

    case AstKind::ITER: {
        const uint32_t n = ast->iter.min;
        const uint32_t n1 = std::max(n, 1u);
        const uint32_t m = std::max(n, ast->iter.max);
        RE* y = nullptr, *t1 = nullptr, *t2 = nullptr;

        ast = ast->iter.ast;

        if ((opts->posix_semantics && ast->kind == AstKind::CAP) || opts->autotags) {
            add_capture_tags(spec, &ast, ncap, height, &t1, &t2, m > 1, in_iter);
        }

        if (m == 0) {
            y = re_cat(spec, t1, t2);
        } else if (m == 1) {
            CHECK_RET(ast_to_re(spec, ast, ncap, height, true, y));
            y = re_cat(spec, t1, re_cat(spec, y, t2));
        } else  {
            CHECK_RET(ast_to_re(spec, ast, ncap, height, true, y));
            y = re_cat(spec, t1, y);
            y = re_cat(spec, y, t2);
            y = re_iter(spec, y, n1, m);
        }
        if (n == 0) {
            y = re_alt(spec, y, re_nil(spec));
        }

        re = y;
        return Ret::OK;
    }}

    return Ret::OK;
}

Ret char_to_range(RESpec& spec, const AstChar& chr, bool icase, Range*& r) {
    RangeMgr& rm = spec.rangemgr;
    uint32_t c = chr.chr;

    if (!spec.opts->encoding.validateChar(c)) {
        RET_FAIL(spec.msg.error(chr.loc, "bad code point: '0x%X'", c));
    }

    r = icase && is_alpha(c)
           ? rm.add(rm.sym(to_lower_unsafe(c)), rm.sym(to_upper_unsafe(c))) : rm.sym(c);
    return Ret::OK;
}

Ret cls_to_range(RESpec& spec, const AstNode* ast, Range*& r) {
    DASSERT(ast->kind == AstKind::CLS);
    RangeMgr& rm = spec.rangemgr;
    r = nullptr;

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

    return Ret::OK;
}

Ret dot_to_range(RESpec& spec, const AstNode* ast, Range*& r) {
    DASSERT(ast->kind == AstKind::DOT);
    RangeMgr& rm = spec.rangemgr;
    uint32_t c = '\n';

    if (!spec.opts->encoding.validateChar(c)) {
        RET_FAIL(spec.msg.error(ast->loc, "bad code point: '0x%X'", c));
    }

    r = rm.sub(spec.opts->encoding.fullRange(rm), rm.sym(c));
    return Ret::OK;
}

Ret diff_to_range(RESpec& spec, const AstNode* ast, Range*& r) {
    DASSERT(ast->kind == AstKind::DIFF);

    Range* x, *y;
    CHECK_RET(ast_to_range(spec, ast->diff.ast1, x));
    CHECK_RET(ast_to_range(spec, ast->diff.ast2, y));
    r = x && y ? spec.rangemgr.sub(x, y) : nullptr;

    return Ret::OK;
}

Ret ast_to_range(RESpec& spec, const AstNode* ast, Range*& r) {
    switch (ast->kind) {
    case AstKind::NIL:
    case AstKind::DEF:
    case AstKind::TAG:
    case AstKind::CAT:
    case AstKind::ITER:
        break;

    case AstKind::CAP:
        if (spec.opts->posix_syntax) break;
        return ast_to_range(spec, ast->cap, r);

    case AstKind::REF:
        CHECK_RET(check_misuse_of_named_def(spec, ast));
        return ast_to_range(spec, ast->ref.ast, r);

    case AstKind::CLS:
        return cls_to_range(spec, ast, r);

    case AstKind::DOT:
        return dot_to_range(spec, ast, r);

    case AstKind::STR:
        if (ast->str.chars.size() != 1) break;
        return char_to_range(spec, ast->str.chars.front(), is_icase(spec.opts, ast->str.icase), r);

    case AstKind::DIFF:
        return diff_to_range(spec, ast, r);

    case AstKind::ALT: {
        Range* x, *y;
        CHECK_RET(ast_to_range(spec, ast->diff.ast1, x));
        CHECK_RET(ast_to_range(spec, ast->diff.ast2, y));
        r = x && y ? spec.rangemgr.add(x, y) : nullptr;

        return Ret::OK;
    }}

    RET_FAIL(spec.msg.error(ast->loc, "can only difference char sets"));
}

Ret re_string(RESpec& spec, const AstNode* ast, RE*& x) {
    DASSERT(ast->kind == AstKind::STR);

    x = nullptr;
    bool icase = is_icase(spec.opts, ast->str.icase);

    for (const AstChar& a : ast->str.chars) {
        Range* r;
        CHECK_RET(char_to_range(spec, a, icase, r));
        RE* y;
        CHECK_RET(re_class(spec, ast->loc, r, y));
        x = re_cat(spec, x, y);
    }

    x = x ? x : re_nil(spec);
    return Ret::OK;
}

Ret re_class(RESpec& spec, const loc_t& loc, const Range* r, RE*& re) {
    if (!r) {
        switch (spec.opts->empty_class_policy) {
        case EmptyClassPolicy::MATCH_EMPTY:
            spec.msg.warn.empty_class(loc);
            re = re_nil(spec);
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
        re = utf16::range(spec, r);
        break;
    case Enc::Type::UTF8:
        re = utf8::range(spec, r);
        break;
    case Enc::Type::EBCDIC:
        re = ebcdic::range(spec, r);
        break;
    case Enc::Type::ASCII:
    case Enc::Type::UTF32:
    case Enc::Type::UCS2:
        re = re_sym(spec, r);
        break;
    }

    return Ret::OK;
}

Ret check_misuse_of_named_def(RESpec& spec, const AstNode* ast) {
    DASSERT(ast->kind == AstKind::REF);
    if (spec.opts->posix_syntax) {
        RET_FAIL(spec.msg.error(ast->loc,
                                "implicit grouping is forbidden with '--posix-captures' option, "
                                "please wrap '%s' in capturing parenthesis",
                                ast->ref.name));
    }
    return Ret::OK;
}

Ret check_tags_used_once(RESpec& spec, const Rule& rule, const std::vector<Tag>& tags) {
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

RESpec::RESpec(const opt_t* opts, Msg& msg, RangeMgr& rangemgr)
    : alc(), rangemgr(rangemgr), res(), charset(), tags(), rules(), opts(opts), msg(msg) {}

Ret RESpec::init(const std::vector<AstRule>& ast) {
    rules.resize(ast.size());
    for (size_t i = 0; i < ast.size(); ++i) {
        size_t ltag = tags.size(), ncap = 0;
        RE* re;
        CHECK_RET(ast_to_re(*this, ast[i].ast, ncap, 0, false, re));
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

} // namespace re2c
