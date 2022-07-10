#ifndef _RE2C_NFA_NFA_
#define _RE2C_NFA_NFA_

#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct clos_t;

// Passes of Goldberg-Radzik shortest path algorithm.
enum class GorPass: uint32_t {
    NOPASS = 0u,
    TOPSORT = 1u,
    LINEAR = 2u
};

static constexpr uint32_t NOCLOS = ~0u;

struct nfa_state_t {
    enum class Kind: uint32_t {ALT, RAN, TAG, FIN} kind;
    union {
        struct {
            nfa_state_t* out1;
            nfa_state_t* out2;
        } alt;
        struct {
            nfa_state_t* out;
            const Range* ran;
        } ran;
        struct {
            nfa_state_t* out;
            tag_info_t info;
        } tag;
    };
    size_t rule;

    // stuff needed for closure algorithms (GOR1 and GTOP)
    uint32_t clos;
    GorPass status  : 2;  // values 0, 1, 2
    uint32_t arcidx : 2;  // maximum out-dergee is 2
    uint32_t active : 1;  // boolean
    uint32_t indeg  : 27; // the rest; we are unlikely to have more than 2^27 states
    uint32_t topord;      // state index in fake topological ordering
};

struct nfa_t {
    nfa_state_t* states;
    nfa_state_t* root;

    uint32_t nstates;
    uint32_t ncores;

    IrAllocator ir_alc;
    std::vector<uint32_t> charset;
    std::vector<Rule> rules;
    std::vector<Tag> tags;

    nfa_t();

    nfa_state_t* make_alt(size_t rule, nfa_state_t* s1, nfa_state_t* s2) {
        nfa_state_t* s = make(nfa_state_t::Kind::ALT, rule);
        s->alt.out1 = s1;
        s->alt.out2 = s2;
        return s;
    }

    nfa_state_t* make_ran(size_t rule, nfa_state_t* t, const Range* range) {
        nfa_state_t* s = make(nfa_state_t::Kind::RAN, rule);
        s->ran.out = t;
        s->ran.ran = range;
        return s;
    }

    nfa_state_t* make_tag(size_t rule, nfa_state_t* t, tag_info_t info) {
        nfa_state_t* s = make(nfa_state_t::Kind::TAG, rule);
        s->tag.out = t;
        s->tag.info = info;
        return s;
    }

    nfa_state_t* make_fin(size_t rule) {
        return make(nfa_state_t::Kind::FIN, rule);
    }

  private:
    nfa_state_t* make(nfa_state_t::Kind kind, size_t rule) {
        nfa_state_t* s = &states[nstates++];
        s->kind = kind;
        s->rule = rule;
        s->clos = NOCLOS;
        s->status = GorPass::NOPASS;
        s->arcidx = 0;
        s->active = 0;
        s->indeg = 0;
        s->topord = 0;
        return s;
    }

    FORBID_COPY(nfa_t);
};

Ret re_to_nfa(nfa_t& nfa, RESpec&& spec) NODISCARD;

static constexpr uint32_t NONCORE = ~0u;

} // namespace re2c

#endif // _RE2C_NFA_NFA_
