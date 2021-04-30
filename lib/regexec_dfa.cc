#include <assert.h>
#include <stddef.h>
#include <valarray>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "lib/regoff_trie.h"
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

        // apply fallback tags
        apply_regops(regs, s->tcmd[dfa->nchars + 1], p - string - 1);
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

static void apply_regops_with_history(regoff_trie_t *regtrie, const tcmd_t *cmd,
    regoff_t pos)
{
    for (const tcmd_t *p = cmd; p; p = p->next) {
        const size_t lhs = static_cast<size_t>(p->lhs);
        const size_t rhs = static_cast<size_t>(p->rhs);

        if (tcmd_t::iscopy(p)) {
            regtrie->copy(lhs, rhs);

        } else if (tcmd_t::isset(p)) {
            regtrie->set(lhs, *p->history == TAGVER_BOTTOM ? -1 : pos);

        } else {
            const tagver_t *h = p->history, *h0;
            for (h0 = h; *h != TAGVER_ZERO; ++h);

            if (lhs != rhs) regtrie->copy(lhs, rhs);
            for (; h --> h0; ) {
                regtrie->add(lhs, *h == TAGVER_BOTTOM ? -1 : pos);
            }
        }
    }
}

template<bool stadfa>
subhistory_t *regparse_dfa(const regex_t *preg, const char *string, size_t nmatch)
{
    const dfa_t *dfa = preg->dfa;
    size_t i = 0;
    const char *p = string, *q = p;
    const dfa_state_t *s, *x = NULL;
    regoff_trie_t *regtrie = preg->regtrie;

    regtrie->clear();
    if (!stadfa) apply_regops_with_history(regtrie, dfa->tcmd0, 0);

    for (;;) {
        s = dfa->states[i];
        const int32_t c = *p++;
        const size_t j = preg->char2class[c];
        i = s->arcs[j];

        if (s->rule != Rule::NONE) {
            q = p;
            x = s;
        }

        if (stadfa) apply_regops_with_history(regtrie, s->stacmd, p - string - 2);

        if (i == dfa_t::NIL || c == 0) break;

        if (!stadfa) apply_regops_with_history(regtrie, s->tcmd[j], p - string - 1);
    }

    regoff_t mlen;
    if (s->rule != Rule::NONE) {
        // already in final state, apply final tags
        mlen = p - string - 1;
        apply_regops_with_history(regtrie, s->tcmd[dfa->nchars], mlen);

    } else if (x != NULL) {
        // rollback to a final state, apply fallback tags
        s = x;
        p = q;
        mlen = p - string - 1;
        apply_regops_with_history(regtrie, s->tcmd[dfa->nchars + 1], mlen);

    } else {
        // no final state on the way => no match
        return NULL;
    }

    const std::vector<Tag> &tags = dfa->tags;
    const size_t ntags = tags.size();
    const tagver_t *finvers = dfa->finvers;

    const regoff_trie_t::node_t *storage = regtrie->storage;
    const size_t *count = regtrie->count;
    const size_t *lists = regtrie->lists;

    // Find the total number of slots needed for all submatch elements.
    size_t rm_count = 1;
    for (size_t t = 0; t < ntags; t += 2) {
        const Tag &tag = tags[t];
        if (!fictive(tag)) {
            rm_count += count[finvers[t]] * (1 + (tag.hsub - tag.lsub) / 2);
        }
    }
    // The amount of memory (in bytes) needed to store submatch information.
    size_t memsize = nmatch * sizeof(subhistory_t) + rm_count * sizeof(regmatch_t);

    subhistory_t *h0 = (subhistory_t*) malloc(memsize), *h = h0, *lasth = h + nmatch;
    regmatch_t *rm0 = (regmatch_t *)(h0 + nmatch), *rm = rm0;

    h->size = 1;
    h->offs = rm;
    rm += 1;
    h->offs[0].rm_so = 0;
    h->offs[0].rm_eo = mlen;
    ++h;

    for (size_t t = 0; t < ntags && h < lasth; t += 2) {
        const Tag &tag = tags[t];
        if (fictive(tag)) continue;
        DASSERT(!fixed(tag));

        const tagver_t f1 = finvers[t], f2 = finvers[t + 1];
        const size_t so0 = lists[f1], sz_so = count[f1];
        const size_t eo0 = lists[f2];
        assert(sz_so == count[f2]);

        // Submatch groups corresponding to this tag pair: there may be more
        // than one capturing parenthesis per tag in regexp like (...(e)...).
        for (size_t s = tag.lsub; s <= tag.hsub && h < lasth; s += 2, ++h) {
            DASSERT(h - 1 == &h0[s / 2]);

            h->size = sz_so;
            h->offs = rm;
            rm += sz_so;

            for (size_t j = sz_so, so = so0, eo = eo0; j --> 0; ) {
                const regoff_trie_t::node_t &n_so = storage[so], &n_eo = storage[eo];
                const regmatch_t m = {n_so.off, n_eo.off};
                h->offs[j] = m;
                so = n_so.pred;
                eo = n_eo.pred;
            }
        }
    }

    return h0;
}

// explicit instantiation for automaton type
template int regexec_dfa<true>(const regex_t *, const char *, size_t, regmatch_t[], int);
template int regexec_dfa<false>(const regex_t *, const char *, size_t, regmatch_t[], int);
template subhistory_t *regparse_dfa<true>(const regex_t *, const char *, size_t);
template subhistory_t *regparse_dfa<false>(const regex_t *, const char *, size_t);

} // namespace libre2c
} // namespace re2c

