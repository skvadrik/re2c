#include <stddef.h>
#include <valarray>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "lib/regoff_trie.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

namespace re2c {
namespace libre2c {

static void apply_regops(regoff_t* regs, const tcmd_t* cmd, regoff_t pos) {
    for (const tcmd_t* p = cmd; p; p = p->next) {
        if (tcmd_t::iscopy(p)) {
            regs[p->lhs] = regs[p->rhs];
        } else {
            DCHECK(tcmd_t::isset(p));
            regs[p->lhs] = *p->history == TAGVER_BOTTOM ? -1 : pos;
        }
    }
}

int regexec_dfa(
    const regex_t* preg, const char* string, size_t nmatch,regmatch_t pmatch[], int /*eflags*/) {
    const Tdfa* dfa = preg->dfa;
    regoff_t* regs = preg->regs;
    size_t i = 0;
    const char* p = string, *q = p;
    const TdfaState* s, *x = nullptr;

    for (;;) {
        s = dfa->states[i];
        const int32_t c = *p++;
        const size_t j = preg->char2class[c];
        i = s->arcs[j];

        if (s->rule != Rule::NONE) {
            q = p;
            x = s;
        }

        if (i == Tdfa::NIL || c == 0) break;

        apply_regops(regs, s->tcmd[j], p - string - 1);
    }

    if (s->rule == Rule::NONE && x != nullptr) {
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

static void apply_regops_with_history(regoff_trie_t* regtrie, const tcmd_t* cmd, regoff_t pos) {
    for (const tcmd_t* p = cmd; p; p = p->next) {
        const size_t lhs = static_cast<size_t>(p->lhs);
        const size_t rhs = static_cast<size_t>(p->rhs);

        if (tcmd_t::iscopy(p)) {
            regtrie->copy(lhs, rhs);

        } else if (tcmd_t::isset(p)) {
            regtrie->set(lhs, *p->history == TAGVER_BOTTOM ? -1 : pos);

        } else {
            const tagver_t* h = p->history, *h0;
            for (h0 = h; *h != TAGVER_ZERO; ++h);

            if (lhs != rhs) regtrie->copy(lhs, rhs);
            for (; h --> h0; ) {
                regtrie->add(lhs, *h == TAGVER_BOTTOM ? -1 : pos);
            }
        }
    }
}

subhistory_t* regparse_dfa(const regex_t* preg, const char* string, size_t nmatch) {
    const Tdfa* dfa = preg->dfa;
    size_t i = 0;
    const char* p = string, *q = p;
    const TdfaState* s, *x = nullptr;
    regoff_trie_t* regtrie = preg->regtrie;

    regtrie->clear();

    for (;;) {
        s = dfa->states[i];
        const int32_t c = *p++;
        const size_t j = preg->char2class[c];
        i = s->arcs[j];

        if (s->rule != Rule::NONE) {
            q = p;
            x = s;
        }

        if (i == Tdfa::NIL || c == 0) break;

        apply_regops_with_history(regtrie, s->tcmd[j], p - string - 1);
    }

    regoff_t mlen;
    if (s->rule != Rule::NONE) {
        // already in final state, apply final tags
        mlen = p - string - 1;
        apply_regops_with_history(regtrie, s->tcmd[dfa->nchars], mlen);
    } else if (x != nullptr) {
        // rollback to a final state, apply fallback tags
        s = x;
        p = q;
        mlen = p - string - 1;
        apply_regops_with_history(regtrie, s->tcmd[dfa->nchars + 1], mlen);
    } else {
        // no final state on the way => no match
        return nullptr;
    }

    const std::vector<Tag>& tags = dfa->tags;
    const size_t ntags = tags.size();
    const tagver_t* finvers = dfa->finvers;

    const regoff_trie_t::node_t* storage = regtrie->storage;
    const size_t* count = regtrie->count;
    const size_t* lists = regtrie->lists;

    // Find the total number of slots needed for all submatch elements.
    size_t rm_count = 1;
    for (size_t t = 0; t < ntags; t += 2) {
        const Tag& tag = tags[t];
        if (!fictive(tag)) {
            rm_count += count[finvers[t]] * (1 + (tag.hsub - tag.lsub) / 2);
        }
    }
    // The amount of memory (in bytes) needed to store submatch information.
    size_t memsize = nmatch * sizeof(subhistory_t) + rm_count * sizeof(regmatch_t);

    subhistory_t* h0 = static_cast<subhistory_t*>(malloc(memsize)), *h = h0, *lasth = h + nmatch;
    regmatch_t* rm0 = reinterpret_cast<regmatch_t*>(lasth), *rm = rm0;

    h->size = 1;
    h->offs = rm;
    rm += 1;
    h->offs[0].rm_so = 0;
    h->offs[0].rm_eo = mlen;
    ++h;

    for (size_t t = 0; t < ntags && h < lasth; t += 2) {
        const Tag& tag = tags[t];
        if (fictive(tag)) continue;
        DCHECK(!fixed(tag));

        const tagver_t f1 = finvers[t], f2 = finvers[t + 1];
        const size_t so0 = lists[f1], sz_so = count[f1];
        const size_t eo0 = lists[f2];
        CHECK(sz_so == count[f2]);

        // Submatch groups corresponding to this tag pair: there may be more
        // than one capturing parenthesis per tag in regexp like (...(e)...).
        for (size_t k = tag.lsub; k <= tag.hsub && h < lasth; k += 2, ++h) {
            DCHECK(h - 1 == &h0[k / 2]);

            h->size = sz_so;
            h->offs = rm;
            rm += sz_so;

            for (size_t j = sz_so, so = so0, eo = eo0; j --> 0; ) {
                const regoff_trie_t::node_t& n_so = storage[so], &n_eo = storage[eo];
                h->offs[j] = {n_so.off, n_eo.off};
                so = n_so.pred;
                eo = n_eo.pred;
            }
        }
    }

    return h0;
}

} // namespace libre2c
} // namespace re2c
