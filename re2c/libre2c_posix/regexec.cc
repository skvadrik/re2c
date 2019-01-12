#include <assert.h>
#include <stdio.h>

#include "libre2c_posix/lex.h"
#include "libre2c_posix/regex.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/nfa/nfa.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"


using namespace re2c;

static void apply_regops(regoff_t *regs, const tcmd_t *cmd, regoff_t pos)
{
    for (const tcmd_t *p = cmd; p; p = p->next) {
        if (tcmd_t::iscopy(p)) {
            regs[p->lhs] = regs[p->rhs];
        }
        else if (tcmd_t::isset(p)) {
            regs[p->lhs] = *p->history == TAGVER_BOTTOM ? -1 : pos;
        }
        else {
            DASSERT(false);
        }
    }
}

int regexec(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int /* eflags */)
{
    const dfa_t *dfa = preg->dfa;
    int result = REG_NOMATCH;
    regoff_t *regs = new regoff_t[dfa->maxtagver + 1];
    size_t i = 0;
    const char *p = string, *q;
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
        result = 0;
        const regoff_t mlen = p - string - 1;

        apply_regops(regs, s->tcmd[dfa->nchars], mlen);

        const Rule &rule = dfa->rules[0];
        const size_t last = std::min(nmatch * 2, rule.htag);

        pmatch[0].rm_so = 0;
        pmatch[0].rm_eo = mlen;

        for (size_t t = rule.ltag; t < last; ++t) {
            const Tag &tag = dfa->tags[t];
            if (fictive(tag)) continue;

            regoff_t off;
            if (!fixed(tag)) {
                off = regs[dfa->finvers[t]];
            }
            else {
                off = -static_cast<regoff_t>(tag.dist);
                off += tag.base == Tag::RIGHTMOST
                    ? mlen : regs[dfa->finvers[tag.base]];
            }

            regmatch_t *rm = &pmatch[tag.ncap / 2 + 1];
            *((tag.ncap % 2 == 0) ? &rm->rm_so : &rm->rm_eo) = off;
        }
    }

    delete[] regs;
    return result;
}
