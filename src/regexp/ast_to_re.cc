#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/debug/debug.h"
#include "src/encoding/case.h"
#include "src/encoding/enc.h"
#include "src/encoding/ebcdic/ebcdic_regexp.h"
#include "src/encoding/utf16/utf16_regexp.h"
#include "src/encoding/utf8/utf8_regexp.h"
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

/* note [default regexp]
 *
 * Create a byte range that includes all possible input characters.
 * This may include characters, which do not map to any valid symbol
 * in current encoding. For encodings, which directly map symbols to
 * input characters (ASCII, EBCDIC, UTF-32), it equals [^]. For other
 * encodings (UTF-16, UTF-8), [^] and this range are different.
 *
 * Also note that default range doesn't respect encoding policy
 * (the way invalid code points are treated).
 */

/* note [POSIX subexpression hierarchy]
 *
 * POSIX treats subexpressions with and without captures as equal,
 * therefore we have to insert missing captures in subexpressions
 * that influence disambiguation of existing captures. Such cases are:
 * left alternative in union (unless it is already a capture) and first
 * operand in concatenation (unless it is a capture). Of course, this
 * insertion only applies to subexpressions that have nested captures.
 */

static bool has_tags(const AST *);
static RE *ast_to_re(RESpec &, const AST *, size_t &, int32_t, bool);
static RE *re_string(RESpec &, const AST *);
static RE *re_class(RESpec &, const loc_t &, const Range *);
static Range *ast_to_range(RESpec &, const AST *);
static Range *char_to_range(RESpec &, const ASTChar &, bool);
static Range *diff_to_range(RESpec &, const AST *);
static Range *dot_to_range(RESpec &, const AST *);
static Range *cls_to_range(RESpec &, const AST *);
static void check_misuse_of_named_def(RESpec &, const AST *);
static void assert_tags_used_once(RESpec &, const Rule &, const std::vector<Tag> &);
static void init_rule(RESpec &, Rule &, const SemAct *, const std::vector<Tag> &, size_t, size_t);
static bool is_icase(const opt_t *, bool);


RESpec::RESpec(const std::vector<ASTRule> &ast, const opt_t *o, Msg &msg
    , RangeMgr &rm)
    : alc()
    , rangemgr(rm)
    , res()
    , charset(*new std::vector<uint32_t>)
    , tags(*new std::vector<Tag>)
    , rules(*new std::valarray<Rule>(ast.size()))
    , opts(o)
    , msg(msg)
{
    for (size_t i = 0; i < ast.size(); ++i) {
        size_t ltag = tags.size(), ncap = 0;
        res.push_back(ast_to_re(*this, ast[i].ast, ncap, 0, false));
        init_rule(*this, rules[i], ast[i].semact, tags, ltag, ncap);
    }
}

bool has_tags(const AST *ast)
{
    switch (ast->type) {
        case AST::NIL:
        case AST::STR:
        case AST::CLS:
        case AST::DOT:
        case AST::DEFAULT:
        case AST::DIFF: return false;
        case AST::TAG:
        case AST::CAP: return true;
        case AST::ALT: return has_tags(ast->alt.ast1) || has_tags(ast->alt.ast2);
        case AST::CAT: return has_tags(ast->cat.ast1) || has_tags(ast->cat.ast2);
        case AST::REF: return has_tags(ast->ref.ast);
        case AST::ITER: return has_tags(ast->iter.ast);
    }
    return false; /* unreachable */
}

static void add_fictive_tags(RESpec &spec, int32_t height, RE **ptag1, RE **ptag2)
{
    std::vector<Tag> &tags = spec.tags;

    // opening fictive tag
    *ptag1 = re_tag(spec, tags.size(), false);
    tags.push_back(Tag(Tag::FICTIVE, Tag::FICTIVE, false, false, height + 1));

    // closing fictive tag
    *ptag2 = re_tag(spec, tags.size(), false);
    tags.push_back(Tag(Tag::FICTIVE, Tag::FICTIVE, false, false, height));
}

static void add_capture_tags(RESpec &spec, const AST **past,
    size_t &ncap, int32_t height, RE **ptag1, RE **ptag2, bool orbit, bool in_iter)
{
    std::vector<Tag> &tags = spec.tags;
    const size_t lcap = ncap;

    const AST *ast = *past;
    if (ast->type == AST::CAP) {
        // save the range of repeated captures and collapse them: (...(R)...) -> (R)
        for (ast = ast->cap; ast && ast->type == AST::CAP; ast = ast->cap) {
            ++ncap;
        }
        // dereference to avoid future check for non-parenthesized rerefences
        if (ast->type == AST::REF) {
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

static inline void add_structural_tags(RESpec &spec, const AST **past,
    size_t &ncap, int32_t height, RE **ptag1, RE **ptag2, bool orbit, bool in_iter)
{
    if (spec.opts->autotags) {
        // Full parsing: automatically add tags as if this sub-RE was a capture.
        add_capture_tags(spec, past, ncap, height, ptag1, ptag2, orbit, in_iter);
    } else if (spec.opts->posix_semantics && has_tags(*past)) {
        // POSIX submatch extraction: add fictive structural tags.
        // See note [POSIX subexpression hierarchy].
        add_fictive_tags(spec, height, ptag1, ptag2);
    }
}

RE *ast_to_re(RESpec &spec, const AST *ast, size_t &ncap, int32_t height, bool in_iter)
{
    std::vector<Tag> &tags = spec.tags;
    const opt_t *opts = spec.opts;

    if (ast->type != AST::CAP && ast->type != AST::REF) ++height;

    switch (ast->type) {
        case AST::NIL:
            return re_nil(spec);

        case AST::STR:
            return re_string(spec, ast);

        case AST::CLS: {
            Range *r = cls_to_range(spec, ast);
            return re_class(spec, ast->loc, r);
        }

        case AST::DOT: {
            Range *r = dot_to_range(spec, ast);
            return re_class(spec, ast->loc, r);
        }

        case AST::DEFAULT: {
            // see note [default regexp]
            Range *r = spec.rangemgr.ran(0, opts->encoding.nCodeUnits());
            return re_sym(spec, r);
        }

        case AST::DIFF: {
            Range *r = diff_to_range(spec, ast);
            return re_class(spec, ast->loc, r);
        }

        case AST::ALT: {
            RE *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *x, *y;

            if (ast->alt.ast1->type != AST::CAP) {
                add_structural_tags(spec, &ast, ncap, height, &t1, &t2, false, in_iter);
            }
            x = ast_to_re(spec, ast->alt.ast1, ncap, height, in_iter);
            x = re_cat(spec, t1, re_cat(spec, x, t2));

            if (ast->alt.ast2->type != AST::CAP) {
                add_structural_tags(spec, &ast, ncap, height, &t3, &t4, false, in_iter);
            }
            y = ast_to_re(spec, ast->alt.ast2, ncap, height, in_iter);
            y = re_cat(spec, t3, re_cat(spec, y, t4));

            return re_alt(spec, x, y);
        }

        case AST::CAT: {
            RE *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *x, *y;

            if (ast->cat.ast1->type != AST::CAP) {
                add_structural_tags(spec, &ast, ncap, height, &t1, &t2, false, in_iter);
            }
            x = ast_to_re(spec, ast->cat.ast1, ncap, height, in_iter);
            x = re_cat(spec, t1, re_cat(spec, x, t2));

            if (ast->cat.ast2->type != AST::CAP) {
                add_structural_tags(spec, &ast, ncap, height, &t3, &t4, false, in_iter);
            }
            y = ast_to_re(spec, ast->cat.ast2, ncap, height, in_iter);
            y = re_cat(spec, t3, re_cat(spec, y, t4));

            return re_cat(spec, x, y);
        }

        case AST::TAG: {
            if (ast->tag.name && !opts->tags) {
                spec.msg.error(ast->loc
                    , "tags are only allowed with '-T, --tags' option");
                exit(1);
            }
            if (opts->posix_syntax) {
                spec.msg.error(ast->loc
                    , "simple tags are not allowed with '--posix-captures' option");
                exit(1);
            }
            RE *t = re_tag(spec, tags.size(), false);
            tags.push_back(Tag(ast->tag.name, ast->tag.history, height));
            return t;
        }

        case AST::CAP:
            if (!opts->posix_syntax) {
                return ast_to_re(spec, ast->cap, ncap, height, in_iter);
            }
            else {
                RE *y = NULL, *t1 = NULL, *t2 = NULL;
                add_capture_tags(spec, &ast, ncap, height, &t1, &t2, false, in_iter);
                y = ast_to_re(spec, ast, ncap, height, in_iter);
                return re_cat(spec, t1, re_cat(spec, y, t2));
            }

        case AST::REF:
            check_misuse_of_named_def(spec, ast);
            return ast_to_re(spec, ast->ref.ast, ncap, height, in_iter);

        case AST::ITER: {
            const uint32_t n = ast->iter.min;
            const uint32_t n1 = std::max(n, 1u);
            const uint32_t m = std::max(n, ast->iter.max);
            RE *y = NULL, *t1 = NULL, *t2 = NULL;

            ast = ast->iter.ast;

            if ((opts->posix_semantics && ast->type == AST::CAP) || opts->autotags) {
                add_capture_tags(spec, &ast, ncap, height, &t1, &t2, m > 1, in_iter);
            }

            if (m == 0) {
                y = re_cat(spec, t1, t2);
            } else if (m == 1) {
                y = ast_to_re(spec, ast, ncap, height, true);
                y = re_cat(spec, t1, re_cat(spec, y, t2));
            } else  {
                y = ast_to_re(spec, ast, ncap, height, true);
                y = re_cat(spec, t1, y);
                y = re_cat(spec, y, t2);
                y = re_iter(spec, y, n1, m);
            }
            if (n == 0) {
                y = re_alt(spec, y, re_nil(spec));
            }

            return y;
        }
    }

    return NULL; /* unreachable */
}

Range *char_to_range(RESpec &spec, const ASTChar &chr, bool icase)
{
    RangeMgr &rm = spec.rangemgr;
    uint32_t c = chr.chr;

    if (!spec.opts->encoding.validateChar(c)) {
        spec.msg.error(chr.loc, "bad code point: '0x%X'", c);
        exit(1);
    }

    return icase && is_alpha(c)
        ? rm.add(rm.sym(to_lower_unsafe(c)), rm.sym(to_upper_unsafe(c)))
        : rm.sym(c);
}

Range *cls_to_range(RESpec &spec, const AST *ast)
{
    DASSERT(ast->type == AST::CLS);

    RangeMgr &rm = spec.rangemgr;
    std::vector<ASTRange>::const_iterator
        i = ast->cls.ranges->begin(),
        e = ast->cls.ranges->end();
    Range *r = NULL;

    for (; i != e; ++i) {
        Range *s = spec.opts->encoding.validateRange(rm, i->lower, i->upper);
        if (!s) {
            spec.msg.error(i->loc, "bad code point range: '0x%X - 0x%X'"
                , i->lower, i->upper);
            exit(1);
        }
        r = rm.add(r, s);
    }

    if (ast->cls.negated) {
        r = rm.sub(spec.opts->encoding.fullRange(rm), r);
    }

    return r;
}

Range *dot_to_range(RESpec &spec, const AST *ast)
{
    DASSERT(ast->type == AST::DOT);

    RangeMgr &rm = spec.rangemgr;
    uint32_t c = '\n';
    if (!spec.opts->encoding.validateChar(c)) {
        spec.msg.error(ast->loc, "bad code point: '0x%X'", c);
        exit(1);
    }
    return rm.sub(spec.opts->encoding.fullRange(rm), rm.sym(c));
}

Range *diff_to_range(RESpec &spec, const AST *ast)
{
    DASSERT(ast->type == AST::DIFF);
    Range *l = ast_to_range(spec, ast->diff.ast1);
    Range *r = ast_to_range(spec, ast->diff.ast2);
    return l && r ? spec.rangemgr.sub(l, r) : NULL;
}

Range *ast_to_range(RESpec &spec, const AST *ast)
{
    switch (ast->type) {
        case AST::NIL:
        case AST::DEFAULT:
        case AST::TAG:
        case AST::CAT:
        case AST::ITER:
            break;
        case AST::CAP:
            if (spec.opts->posix_syntax) break;
            return ast_to_range(spec, ast->cap);
        case AST::REF:
            check_misuse_of_named_def(spec, ast);
            return ast_to_range(spec, ast->ref.ast);
        case AST::CLS:
            return cls_to_range(spec, ast);
        case AST::DOT:
            return dot_to_range(spec, ast);
        case AST::STR:
            if (ast->str.chars->size() != 1) break;
            return char_to_range(spec, ast->str.chars->front()
                , is_icase(spec.opts, ast->str.icase));
        case AST::DIFF:
            return diff_to_range(spec, ast);
        case AST::ALT: {
            Range *x = ast_to_range(spec, ast->diff.ast1);
            Range *y = ast_to_range(spec, ast->diff.ast2);
            return spec.rangemgr.add(x, y);
        }
    }
    spec.msg.error(ast->loc, "can only difference char sets");
    exit(1);
}

RE *re_string(RESpec &spec, const AST *ast)
{
    DASSERT(ast->type == AST::STR);

    RE *x = NULL;
    std::vector<ASTChar>::const_iterator
        i = ast->str.chars->begin(),
        e = ast->str.chars->end();

    bool icase = is_icase(spec.opts, ast->str.icase);
    for (; i != e; ++i) {
        Range *r = char_to_range(spec, *i, icase);
        RE *y = re_class(spec, ast->loc, r);
        x = re_cat(spec, x, y);
    }

    return x ? x : re_nil(spec);
}

RE *re_class(RESpec &spec, const loc_t &loc, const Range *r)
{
    if (!r) {
        switch (spec.opts->empty_class_policy) {
            case EMPTY_CLASS_MATCH_EMPTY:
                spec.msg.warn.empty_class(loc);
                return re_nil(spec);
            case EMPTY_CLASS_MATCH_NONE:
                spec.msg.warn.empty_class(loc);
                break;
            case EMPTY_CLASS_ERROR:
                spec.msg.error(loc, "empty character class");
                exit(1);
        }
    }

    switch (spec.opts->encoding.type()) {
        case Enc::UTF16:
            return UTF16Range(spec, r);
        case Enc::UTF8:
            return UTF8Range(spec, r);
        case Enc::EBCDIC:
            return EBCDICRange(spec, r);
        case Enc::ASCII:
        case Enc::UTF32:
        case Enc::UCS2:
            return re_sym(spec, r);
    }

    return NULL; /* unreachable */
}

void check_misuse_of_named_def(RESpec &spec, const AST *ast)
{
    DASSERT(ast->type == AST::REF);

    if (spec.opts->posix_syntax) {
        spec.msg.error(ast->loc
            , "implicit grouping is forbidden with '--posix-captures'"
                " option, please wrap '%s' in capturing parenthesis"
            , ast->ref.name->c_str());
        exit(1);
    }
}

void assert_tags_used_once(RESpec &spec, const Rule &rule
    , const std::vector<Tag> &tags)
{
    std::set<std::string> names;
    const std::string *name = NULL;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        name = tags[t].name;
        if (name && !names.insert(*name).second) {
            spec.msg.error(rule.semact->loc
                , "tag '%s' is used multiple times in the same rule"
                , name->c_str());
            exit(1);
        }
    }
}

void init_rule(RESpec &spec, Rule &rule, const SemAct *semact
    , const std::vector<Tag> &tags, size_t ltag, size_t ncap)
{
    rule.semact = semact;
    rule.ltag = ltag;
    rule.htag = tags.size();
    for (rule.ttag = ltag; rule.ttag < rule.htag && !trailing(tags[rule.ttag]); ++rule.ttag);
    rule.ncap = ncap;
    assert_tags_used_once(spec, rule, tags);
}

bool is_icase(const opt_t *opts, bool icase)
{
    return opts->bCaseInsensitive
        || icase != opts->bCaseInverted;
}

} // namespace re2c
