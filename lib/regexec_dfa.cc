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

template<bool stadfa>
int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int /* eflags */)
{
    const dfa_t *dfa = preg->dfa;
    regoff_t *regs = preg->regs;
    size_t i = 0;
    const char *p = string, *q = p;
    const dfa_state_t *s, *x = NULL;

    if (!stadfa) apply_regops(regs, dfa->tcmd0, 0);

    for (;;) {
        s = dfa->states[i];
        const int32_t c = *p++;
        const size_t j = preg->char2class[c];
        i = s->arcs[j];

        if (s->rule != Rule::NONE) {
            q = p;
            x = s;
        }

        if (stadfa) apply_regops(regs, s->stacmd, p - string - 2);

        if (i == dfa_t::NIL || c == 0) break;

        if (!stadfa) apply_regops(regs, s->tcmd[j], p - string - 1);
    }

    if (s->rule == Rule::NONE && x != NULL) {
        s = x;
        p = q;
    }

    if (s->rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    const regoff_t mlen = p - string - 1;
    const getoff_dfa_t fn = { dfa, regs, mlen };
    apply_regops(regs, s->tcmd[dfa->nchars], mlen);
    tags_to_submatch(dfa->tags, nmatch, pmatch, mlen, fn);
    return 0;
}

template int regexec_dfa<true>(const regex_t *, const char *, size_t, regmatch_t[], int);
template int regexec_dfa<false>(const regex_t *, const char *, size_t, regmatch_t[], int);

} // namespace libre2c
} // namespace re2c

