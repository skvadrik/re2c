#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"


namespace re2c {
namespace libre2c {

static void apply_regops(regoff_t *regs, const tcmd_t *cmd, regoff_t pos)
{
    for (const tcmd_t *p = cmd; p; p = p->next) {
        if (tcmd_t::iscopy(p)) {
            regs[p->lhs] = regs[p->rhs];
        }
        else {
            DASSERT (tcmd_t::isset(p));
            regs[p->lhs] = *p->history == TAGVER_BOTTOM ? -1 : pos;
        }
    }
}

int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int /* eflags */)
{
    const dfa_t *dfa = preg->dfa;
    int result = REG_NOMATCH;
    regoff_t *regs = preg->regs;
    size_t i = 0;
    const char *p = string, *q = p;
    const dfa_state_t *s, *x = NULL;

    apply_regops(regs, dfa->tcmd0, 0);

    for (;;) {
        s = dfa->states[i];
        const int32_t c = *p++;
        const size_t j = preg->char2class[c];
        i = s->arcs[j];

        if (s->rule != Rule::NONE) {
            q = p;
            x = s;
        }

        if (i == dfa_t::NIL || c == 0) break;

        apply_regops(regs, s->tcmd[j], p - string - 1);
    }

    if (s->rule == Rule::NONE && x != NULL) {
        s = x;
        p = q;
    }

    if (s->rule != Rule::NONE) {
        regmatch_t *m = pmatch;
        result = 0;
        const regoff_t mlen = p - string - 1;

        apply_regops(regs, s->tcmd[dfa->nchars], mlen);

        m->rm_so = 0;
        m->rm_eo = mlen;
        ++m;

        const Rule &rule = dfa->rules[0];
        for (size_t t = rule.ltag; t < rule.htag; ++t) {

            const Tag &tag = dfa->tags[t];
            if (fictive(tag)) continue;
            if (tag.ncap >= nmatch * 2) break;

            regoff_t off;
            if (!fixed(tag)) {
                off = regs[dfa->finvers[t]];
            }
            else {
                off = tag.base == Tag::RIGHTMOST
                    ? mlen : regs[dfa->finvers[tag.base]];
                DASSERT (off != -1);
                off -= static_cast<regoff_t>(tag.dist);
            }

            if (tag.ncap % 2 == 0) {
                m->rm_so = off;
            }
            else {
                m->rm_eo = off;
                ++m;
            }
        }
    }

    return result;
}

} // namespace libre2c
} // namespace re2c

