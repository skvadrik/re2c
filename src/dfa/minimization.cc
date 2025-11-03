#include <string.h>
#include <map>
#include <utility>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"


namespace re2c {

/*
 * note [DFA minimization: table filling algorithm]
 *
 * This algorithm is simple and slow; it's a reference implementation.
 *
 * The algorithm constructs (strictly lower triangular) boolean matrix
 * indexed by DFA states. Each matrix cell (S1,S2) indicates if states
 * S1 and S2 are distinguishable. Initialy states are distinguished
 * according to their rule and tag set. One step of the algorithm
 * updates the matrix as follows: each pair of states S1 and S2 is
 * marked as distinguishable iff exist transitions from S1 and S2 on
 * the same symbol that go to distinguishable states. The algorithm
 * loops until the matrix stops changing.
 */

/*
 * note [DFA minimization: Moore algorithm]
 *
 * The algorithm maintains partition of DFA states.
 * Initial partition is coarse: states are distinguished according
 * to their rule and tag set. Partition is gradually refined: each
 * set of states is split into minimal number of subsets such that
 * for all states in a subset transitions on the same symbol go to
 * the same set of states.
 * The algorithm loops until partition stops changing.
 */

/* note [distinguish states by tags]
 *
 * Final states may have 'rule' tags: tags that must be set when lexer
 * takes epsilon-transition to the binded action. Final states with
 * the same rule but different sets on 'rule' tags cannot be merged.
 *
 * Compare the following two cases:
 *     "ac" | "bc"
 *     "ac" @p | "bc"
 * Tail "c" can be deduplicated in the 1st case, but not in the 2nd.
 */

struct moore_key_t {
    size_t rule;
    tcid_t fincmd;
};

using moore_init_t = std::map<moore_key_t, size_t>;

static bool operator <(const moore_key_t&, const moore_key_t&);
static void minimization_table(size_t*, const std::vector<TdfaState*>&, size_t);
static void minimization_moore(size_t*, const std::vector<TdfaState*>&, size_t);


void minimization(Tdfa& dfa, Minimization type) {
    const size_t count = dfa.states.size();
    size_t* part = new size_t[count];

    switch (type) {
    case Minimization::TABLE:
        minimization_table(part, dfa.states, dfa.nchars); break;
    case Minimization::MOORE:
        minimization_moore(part, dfa.states, dfa.nchars); break;
    }

    size_t* compact = new size_t[count];
    for (size_t i = 0, j = 0; i < count; ++i) {
        if (i == part[i]) {
            compact[i] = j++;
        }
    }

    size_t new_count = 0;
    for (size_t i = 0; i < count; ++i) {
        TdfaState* s = dfa.states[i];

        if (i == part[i]) {
            size_t* arcs = s->arcs;
            for (size_t c = 0; c < dfa.nchars; ++c) {
                if (arcs[c] != Tdfa::NIL) {
                    arcs[c] = compact[part[arcs[c]]];
                }
            }
            dfa.states[new_count++] = s;
        } else {
            delete s;
        }
    }
    dfa.states.resize(new_count);

    delete[] compact;
    delete[] part;
}

void minimization_table(size_t* part, const std::vector<TdfaState*>& states, size_t nchars) {
    const size_t count = states.size();

    bool** tbl = new bool*[count];
    tbl[0] = new bool[count * (count - 1) / 2];
    for (size_t i = 0; i < count - 1; ++i) {
        tbl[i + 1] = tbl[i] + i;
    }

    // see note [distinguish states by tags]
    for (size_t i = 0; i < count; ++i) {
        TdfaState* s1 = states[i];
        for (size_t j = 0; j < i; ++j) {
            TdfaState* s2 = states[j];
            tbl[i][j] = s1->rule != s2->rule || s1->tcid[nchars] != s2->tcid[nchars];
        }
    }

    for (bool loop = true; loop;) {
        loop = false;
        for (size_t i = 0; i < count; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (!tbl[i][j]) {
                    for (size_t k = 0; k < nchars; ++k) {
                        size_t oi = states[i]->arcs[k];
                        size_t oj = states[j]->arcs[k];
                        if (oi < oj) {
                            std::swap(oi, oj);
                        }
                        if (states[i]->tcid[k] != states[j]->tcid[k]
                                || (oi != oj
                                    && (oi == Tdfa::NIL
                                        || oj == Tdfa::NIL
                                        || tbl[oi][oj]))) {
                            tbl[i][j] = true;
                            loop = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Equivalence relation defined by the matrix is transitive
    // by construction. Thus we can simply find the first state
    // which is not distinguishable from current and choose it as a
    // representative: all other states with the same representative
    // have to be equivalent to current state due to transitivity.
    //
    // The only requirement is to deterministically choose the
    // representative: e.g. always choose the one with the lowest
    // index.
    //
    // Note that transitivity is crucial: without it the problem
    // would be equivalent to the clique cover problem.

    for (size_t i = 0; i < count; ++i) {
        part[i] = i;
        for (size_t j = 0; j < i; ++j) {
            if (!tbl[i][j]) {
                part[i] = j;
                break;
            }
        }
    }

    delete[] tbl[0];
    delete[] tbl;
}

void minimization_moore(size_t* part, const std::vector<TdfaState*>& states, size_t nchars) {
    const size_t count = states.size();
    size_t* next = new size_t[count];

    // see note [distinguish states by tags]
    moore_init_t init;
    for (size_t i = 0; i < count; ++i) {
        TdfaState* s = states[i];
        const moore_key_t k = {s->rule, s->tcid[nchars]};
        std::pair<moore_init_t::iterator, bool> p = init.insert(std::make_pair(k, i));
        if (p.second) {
            part[i] = i;
            next[i] = Tdfa::NIL;
        } else {
            const size_t j = p.first->second;
            part[i] = j;
            next[i] = next[j];
            next[j] = i;
        }
    }

    size_t* out = new size_t[nchars * count];
    size_t* diff = new size_t[count];

    for (bool loop = true; loop;) {
        loop = false;

        for (size_t i = 0; i < count; ++i) {
            if (i != part[i] || next[i] == Tdfa::NIL) continue;

            for (size_t j = i; j != Tdfa::NIL; j = next[j]) {
                size_t* o = &out[j * nchars];
                size_t* a = states[j]->arcs;

                for (size_t c = 0; c < nchars; ++c) {
                    o[c] = a[c] == Tdfa::NIL ? Tdfa::NIL : part[a[c]];
                }
            }

            size_t diff_count = 0;
            for (size_t j = i; j != Tdfa::NIL;) {
                const size_t j_next = next[j];
                size_t n = 0;

                for (; n < diff_count; ++n) {
                    const size_t k = diff[n];

                    if (memcmp(&out[j * nchars], &out[k * nchars], nchars * sizeof(size_t)) == 0
                        && memcmp(states[j]->tcid, states[k]->tcid, nchars * sizeof(tcid_t)) == 0) {

                        part[j] = k;
                        next[j] = next[k];
                        next[k] = j;
                        break;
                    }
                }

                if (n == diff_count) {
                    diff[diff_count++] = j;
                    part[j] = j;
                    next[j] = Tdfa::NIL;
                }

                j = j_next;
            }

            loop |= diff_count > 1;
        }
    }

    delete[] out;
    delete[] diff;
    delete[] next;
}

bool operator<(const moore_key_t& x, const moore_key_t& y) {
    if (x.rule < y.rule) return true;
    if (x.rule > y.rule) return false;
    return x.fincmd < y.fincmd;
}

} // namespace re2c

