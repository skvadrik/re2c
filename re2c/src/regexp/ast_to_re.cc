#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/parse/ast.h"
#include "src/options/msg.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/regexp/empty_class_policy.h"
#include "src/encoding/case.h"
#include "src/encoding/enc.h"
#include "src/encoding/ebcdic/ebcdic_regexp.h"
#include "src/encoding/utf16/utf16_regexp.h"
#include "src/encoding/utf8/utf8_regexp.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/range.h"

namespace re2c {

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
 * operand in concatenation (unless it is a capture or the length of
 * strings accepted by it is fixed). Of course, this insertion only
 * applies to subexpressions that have nested captures.
 */

static bool has_tags(const AST *);
static RE *ast_to_re(RESpec &, const AST *, size_t &, int32_t);
static RE *re_string(RE::alc_t &, const AST *, const opt_t *, Warn &);
static RE *re_class(RE::alc_t &, uint32_t, uint32_t, const Range *, const opt_t *, Warn &);
static Range *ast_to_range(const AST *, const opt_t *);
static Range *char_to_range(uint32_t, const ASTChar &, const opt_t *, bool);
static Range *diff_to_range(const AST *, const opt_t *);
static Range *dot_to_range(const AST *, const opt_t *);
static Range *cls_to_range(const AST *, const opt_t *);
static bool misuse_of_named_def(const AST *, const opt_t *);
static void assert_tags_used_once(const Rule &, const std::vector<Tag> &);
static void init_rule(Rule &, const Code *, const std::vector<Tag> &, size_t, size_t);
static bool is_icase(const opt_t *, bool);


RESpec::RESpec(const std::vector<ASTRule> &ast, const opt_t *o, Warn &w)
    : alc()
    , res()
    , charset(*new std::vector<uint32_t>)
    , tags(*new std::vector<Tag>)
    , rules(*new std::valarray<Rule>(ast.size()))
    , opts(o)
    , warn(w)
{
    for (size_t i = 0; i < ast.size(); ++i) {
        size_t ltag = tags.size(), ncap = 0;
        res.push_back(ast_to_re(*this, ast[i].ast, ncap, 0));
        init_rule(rules[i], ast[i].code, tags, ltag, ncap);
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

RE *ast_to_re(RESpec &spec, const AST *ast, size_t &ncap, int32_t height)
{
    RE::alc_t &alc = spec.alc;
    std::vector<Tag> &tags = spec.tags;
    const opt_t *opts = spec.opts;
    Warn &warn = spec.warn;

    if (ast->type != AST::CAP && ast->type != AST::REF) ++height;

    switch (ast->type) {
        case AST::NIL:
            return re_nil(alc);
        case AST::STR:
            return re_string(alc, ast, opts, warn);
        case AST::CLS: {
            Range *r = cls_to_range(ast, opts);
            return re_class(alc, ast->line, ast->column, r, opts, warn);
        }
        case AST::DOT: {
            Range *r = dot_to_range(ast, opts);
            return re_class(alc, ast->line, ast->column, r, opts, warn);
        }
        case AST::DEFAULT:
            // see note [default regexp]
            return re_sym(alc, Range::ran(0, opts->encoding.nCodeUnits()));
        case AST::ALT: {
            RE *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *x, *y;
            if (opts->posix_captures && has_tags(ast)) {
                // see note [POSIX subexpression hierarchy]
                if (ast->cat.ast1->type != AST::CAP) {
                    t1 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height + 1));
                    t2 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height));
                }
                if (ast->cat.ast2->type != AST::CAP) {
                    t3 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height + 1));
                    t4 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height));
                }
            }
            x = ast_to_re(spec, ast->alt.ast1, ncap, height);
            x = re_cat(alc, t1, re_cat(alc, x, t2));
            y = ast_to_re(spec, ast->alt.ast2, ncap, height);
            y = re_cat(alc, t3, re_cat(alc, y, t4));
            return re_alt(alc, x, y);
        }
        case AST::DIFF: {
            Range *r = diff_to_range(ast, opts);
            return re_class(alc, ast->line, ast->column, r, opts, warn);
        }
        case AST::CAT: {
            RE *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *x, *y;
            if (opts->posix_captures && has_tags(ast)) {
                // see note [POSIX subexpression hierarchy]
                if (ast->cat.ast1->type != AST::CAP) {
                    t1 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height + 1));
                    t2 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height));
                }
                if (ast->cat.ast2->type != AST::CAP) {
                    t3 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height + 1));
                    t4 = re_tag(alc, tags.size(), false);
                    tags.push_back(Tag(Tag::FICTIVE, false, height));
                }
            }
            x = ast_to_re(spec, ast->cat.ast1, ncap, height);
            x = re_cat(alc, t1, re_cat(alc, x, t2));
            y = ast_to_re(spec, ast->cat.ast2, ncap, height);
            y = re_cat(alc, t3, re_cat(alc, y, t4));
            return re_cat(alc, x, y);
        }
        case AST::TAG: {
            if (ast->tag.name && !opts->tags) {
                fatal_lc(ast->line, ast->column,
                    "tags are only allowed with '-T, --tags' option");
            }
            if (opts->posix_captures) {
                fatal_lc(ast->line, ast->column,
                    "simple tags are not allowed with '--posix-captures' option");
            }
            RE *t = re_tag(alc, tags.size(), false);
            tags.push_back(Tag(ast->tag.name, ast->tag.history, height));
            return t;
        }
        case AST::CAP: {
            if (!opts->posix_captures) {
                return ast_to_re(spec, ast->cap, ncap, height);
            }
            const AST *x = ast->cap;
            if (x->type == AST::REF) x = x->ref.ast;

            RE *t1 = re_tag(alc, tags.size(), false);
            tags.push_back(Tag(2 * ncap, false, height + 1));

            RE *t2 = re_tag(alc, tags.size(), false);
            tags.push_back(Tag(2 * ncap + 1, false, height));

            ++ncap;
            return re_cat(alc, t1, re_cat(alc, ast_to_re(spec, x, ncap, height), t2));
        }
        case AST::REF:
            if (misuse_of_named_def(ast, opts)) return NULL;
            return ast_to_re(spec, ast->ref.ast, ncap, height);
        case AST::ITER: {
            const uint32_t
                n = ast->iter.min,
                n1 = std::max(n, 1u),
                m = std::max(n, ast->iter.max);
            const AST *x = ast->iter.ast;

            RE *t1 = NULL, *t2 = NULL;
            if (opts->posix_captures && x->type == AST::CAP) {
                x = x->cap;
                if (x->type == AST::REF) x = x->ref.ast;

                t1 = re_tag(alc, tags.size(), false);
                tags.push_back(Tag(2 * ncap, m > 1, height + 1));

                t2 = re_tag(alc, tags.size(), false);
                tags.push_back(Tag(2 * ncap + 1, m > 1, height));

                ++ncap;
            }

            RE *y = NULL;
            if (m == 0) {
                y = re_cat(alc, t1, t2);
            } else if (m == 1) {
                y = ast_to_re(spec, x, ncap, height);
                y = re_cat(alc, t1, re_cat(alc, y, t2));
            } else  {
                y = ast_to_re(spec, x, ncap, height);
                y = re_cat(alc, t1, y);
                y = re_cat(alc, y, t2);
                y = re_iter(alc, y, n1, m);
            }
            if (n == 0) {
                y = re_alt(alc, y, re_nil(alc));
            }
            return y;
        }
    }
    return NULL; /* unreachable */
}

Range *char_to_range(uint32_t line, const ASTChar &chr, const opt_t *opts
    , bool icase)
{
    uint32_t c = chr.chr;

    if (!opts->encoding.validateChar(c)) {
        fatal_lc(line, chr.column, "bad code point: '0x%X'", c);
    }

    return icase && is_alpha(c)
        ? Range::add(Range::sym(to_lower_unsafe(c)), Range::sym(to_upper_unsafe(c)))
        : Range::sym(c);
}

Range *cls_to_range(const AST *ast, const opt_t *opts)
{
    DASSERT(ast->type == AST::CLS);

    Range *r = NULL;
    std::vector<ASTRange>::const_iterator
        i = ast->cls.ranges->begin(),
        e = ast->cls.ranges->end();

    for (; i != e; ++i) {
        Range *s = opts->encoding.validateRange(i->lower, i->upper);
        if (!s) {
            fatal_lc(ast->line, i->column,
            "bad code point range: '0x%X - 0x%X'", i->lower, i->upper);
        }
        r = Range::add(r, s);
    }

    if (ast->cls.negated) {
        r = Range::sub(opts->encoding.fullRange(), r);
    }

    return r;
}

Range *dot_to_range(const AST *ast, const opt_t *opts)
{
    DASSERT(ast->type == AST::DOT);

    uint32_t c = '\n';
    if (!opts->encoding.validateChar(c)) {
        fatal_lc(ast->line, ast->column, "bad code point: '0x%X'", c);
    }
    return Range::sub(opts->encoding.fullRange(), Range::sym(c));
}

Range *diff_to_range(const AST *ast, const opt_t *opts)
{
    DASSERT(ast->type == AST::DIFF);
    Range *l = ast_to_range(ast->diff.ast1, opts);
    Range *r = ast_to_range(ast->diff.ast2, opts);
    return l && r ? Range::sub(l, r) : NULL;
}

Range *ast_to_range(const AST *ast, const opt_t *opts)
{
    switch (ast->type) {
        case AST::NIL:
        case AST::DEFAULT:
        case AST::TAG:
        case AST::CAT:
        case AST::ITER:
            break;
        case AST::CAP:
            if (opts->posix_captures) break;
            return ast_to_range(ast->cap, opts);
        case AST::REF:
            if (misuse_of_named_def(ast, opts)) return NULL;
            return ast_to_range(ast->ref.ast, opts);
        case AST::CLS:
            return cls_to_range(ast, opts);
        case AST::DOT:
            return dot_to_range(ast, opts);
        case AST::STR:
            if (ast->str.chars->size() != 1) break;
            return char_to_range(ast->line, ast->str.chars->front(), opts
                , is_icase(opts, ast->str.icase));
        case AST::DIFF:
            return diff_to_range(ast, opts);
        case AST::ALT: {
            Range *x = ast_to_range(ast->diff.ast1, opts);
            Range *y = ast_to_range(ast->diff.ast2, opts);
            return Range::add(x, y);
        }
    }
    fatal_lc(ast->line, ast->column, "can only difference char sets");
    return NULL;
}

RE *re_string(RE::alc_t &alc, const AST *ast, const opt_t *opts, Warn &warn)
{
    DASSERT(ast->type == AST::STR);

    RE *x = NULL;
    std::vector<ASTChar>::const_iterator
        i = ast->str.chars->begin(),
        e = ast->str.chars->end();

    bool icase = is_icase(opts, ast->str.icase);
    for (; i != e; ++i) {
        Range *r = char_to_range(ast->line, *i, opts, icase);
        RE *y = re_class(alc, ast->line, i->column, r, opts, warn);
        x = re_cat(alc, x, y);
    }

    return x ? x : re_nil(alc);
}

RE *re_class(RE::alc_t &alc, uint32_t line, uint32_t column, const Range *r
    , const opt_t *opts, Warn &warn)
{
    if (!r) {
        switch (opts->empty_class_policy) {
            case EMPTY_CLASS_MATCH_EMPTY:
                warn.empty_class(line);
                return re_nil(alc);
            case EMPTY_CLASS_MATCH_NONE:
                warn.empty_class(line);
                break;
            case EMPTY_CLASS_ERROR:
                fatal_lc(line, column, "empty character class");
        }
    }

    switch (opts->encoding.type()) {
        case Enc::UTF16:
            return UTF16Range(alc, r);
        case Enc::UTF8:
            return UTF8Range(alc, r);
        case Enc::EBCDIC:
            return EBCDICRange(alc, r);
        case Enc::ASCII:
        case Enc::UTF32:
        case Enc::UCS2:
            return re_sym(alc, r);
    }

    return NULL; /* unreachable */
}

bool misuse_of_named_def(const AST *ast, const opt_t *opts)
{
    DASSERT(ast->type == AST::REF);

    if (!opts->posix_captures) return false;

    fatal_l(ast->line,
        "implicit grouping is forbidden with '--posix-captures'"
        " option, please wrap '%s' in capturing parenthesis",
        ast->ref.name->c_str());
    return true;
}

void assert_tags_used_once(const Rule &rule, const std::vector<Tag> &tags)
{
    std::set<std::string> names;
    const std::string *name = NULL;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        name = tags[t].name;
        if (name && !names.insert(*name).second) {
            fatal_l(rule.code->fline,
                "tag '%s' is used multiple times in the same rule",
                name->c_str());
        }
    }
}

void init_rule(Rule &rule, const Code *code, const std::vector<Tag> &tags,
    size_t ltag, size_t ncap)
{
    rule.code = code;
    rule.ltag = ltag;
    rule.htag = tags.size();
    for (rule.ttag = ltag; rule.ttag < rule.htag && !trailing(tags[rule.ttag]); ++rule.ttag);
    rule.ncap = ncap;
    assert_tags_used_once(rule, tags);
}

bool is_icase(const opt_t *opts, bool icase)
{
    return opts->bCaseInsensitive
        || icase != opts->bCaseInverted;
}

} // namespace re2c
