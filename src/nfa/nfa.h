#ifndef _RE2C_NFA_NFA_
#define _RE2C_NFA_NFA_

#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "src/regexp/regexp.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct clos_t;

// Passes of Goldberg-Radzik shortest path algorithm.
//
// This cannot be a `enum class` because it is used in a bitfield, which triggers compiler
// warnings and errors on some toolchains, see https://github.com/skvadrik/re2c/issues/446.
// It cannot be a plain `enum` defaulting to `int` as well because of -Wsigned-enum-bitfield.
constexpr uint32_t GOR_NOPASS = 0u;
constexpr uint32_t GOR_TOPSORT = 1u;
constexpr uint32_t GOR_LINEAR = 2u;

static constexpr uint32_t NOCLOS = ~0u;

struct TnfaState {
    enum class Kind: uint32_t {ALT, RAN, TAG, FIN} kind;
    uint32_t rule;        // the number of regexp rule that this state belongs to
    TnfaState* out1;      // first outgoing transition (for all states except FIN)
    union {
        TnfaState* out2;  // second outgoing transition (only for ALT states)
        const Range* ran; // character range (only for RAN states)
        tag_info_t tag;   // tag information (number and sign, only for TAG states)
    };
    uint32_t clos;        // GOR1: closure item for this stack
    uint32_t status : 2;  // GOR1: status (values 0, 1, 2)
    uint32_t arcidx : 2;  // GOR1: index of the next transtion (maximum out-dergee is 2)
    uint32_t active : 1;  // GOR1: if the state is on stack (boolean)
    uint32_t indeg  : 27; // GOR1: in-degree (we are unlikely to have more than 2^27 states)
    uint32_t topord;      // state index in topological ordering
};

struct Tnfa {
    TnfaState* states;
    TnfaState* root;

    uint32_t nstates;
    uint32_t ncores;

    IrAllocator ir_alc;
    std::vector<uint32_t> charset;
    std::vector<Rule> rules;
    std::vector<Tag> tags;

    Tnfa();

    TnfaState* make_alt(uint32_t rule, TnfaState* s1, TnfaState* s2) {
        TnfaState* s = make(TnfaState::Kind::ALT, rule);
        s->out1 = s1;
        s->out2 = s2;
        return s;
    }

    TnfaState* make_ran(uint32_t rule, TnfaState* t, const Range* range) {
        TnfaState* s = make(TnfaState::Kind::RAN, rule);
        s->out1 = t;
        s->ran = range;
        return s;
    }

    TnfaState* make_tag(uint32_t rule, TnfaState* t, tag_info_t info) {
        TnfaState* s = make(TnfaState::Kind::TAG, rule);
        s->out1 = t;
        s->tag = info;
        return s;
    }

    TnfaState* make_fin(uint32_t rule) {
        return make(TnfaState::Kind::FIN, rule);
    }

  private:
    TnfaState* make(TnfaState::Kind kind, uint32_t rule) {
        TnfaState* s = &states[nstates++];
        s->kind = kind;
        s->rule = rule;
        s->clos = NOCLOS;
        s->status = GOR_NOPASS;
        s->arcidx = 0;
        s->active = 0;
        s->indeg = 0;
        s->topord = 0;
        return s;
    }

    FORBID_COPY(Tnfa);
};

Ret re_to_nfa(Tnfa& nfa, RESpec&& spec) NODISCARD;

static constexpr uint32_t NONCORE = ~0u;

} // namespace re2c

#endif // _RE2C_NFA_NFA_
