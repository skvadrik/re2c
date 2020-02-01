#include <stddef.h>
#include <valarray>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"


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

static inline regoff_t get_offset(const dfa_t *dfa, size_t tidx,
    const regoff_t *regs, regoff_t mlen)
{
    const Tag &tag = dfa->tags[tidx];
    regoff_t off;
    if (!fixed(tag)) {
        off = regs[dfa->finvers[tidx]];
    }
    else {
        off = tag.base == Tag::RIGHTMOST
            ? mlen : regs[dfa->finvers[tag.base]];
        DASSERT (off != -1);
        off -= static_cast<regoff_t>(tag.dist);
    }
    return off;
}

int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int /* eflags */)
{
    const dfa_t *dfa = preg->dfa;
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

        apply_regops(regs, s->stacmd, p - string - 2);

        if (i == dfa_t::NIL || c == 0) break;

        apply_regops(regs, s->tcmd[j], p - string - 1);
    }

    if (s->rule == Rule::NONE && x != NULL) {
        s = x;
        p = q;
    }

    if (s->rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    int result = 0;
    regmatch_t *m = pmatch, *e = pmatch + nmatch;
    const regoff_t mlen = p - string - 1;
    const Rule &rule = dfa->rules[0];

    apply_regops(regs, s->tcmd[dfa->nchars], mlen);

    m->rm_so = 0;
    m->rm_eo = mlen;
    ++m;

    for (size_t t = rule.ltag; t < rule.htag && m < e; t += 2) {
        const Tag &tag = dfa->tags[t];
        if (!fictive(tag)) {
            const regoff_t so = get_offset(dfa, t,     regs, mlen);
            const regoff_t eo = get_offset(dfa, t + 1, regs, mlen);

            for (size_t j = tag.lsub; j <= tag.hsub && m < e; j += 2, ++m) {
                DASSERT(m - 1 == &pmatch[j / 2]);
                m->rm_so = so;
                m->rm_eo = eo;
            }
        }
    }

    return result;
}

} // namespace libre2c
} // namespace re2c

