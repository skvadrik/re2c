#ifndef _RE2C_ADFA_ADFA_
#define _RE2C_ADFA_ADFA_

#include <stddef.h>
#include <stdint.h>
#include <limits>
#include <set>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/codegen/output.h"
#include "src/msg/location.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/attribute.h"
#include "src/util/check.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class Msg;
struct Tdfa;
struct opt_t;
struct State;

static constexpr size_t NOSAVE = std::numeric_limits<size_t>::max();

struct AcceptTrans {
    State* state;
    tcid_t tags;

    bool operator==(const AcceptTrans& a) const {
        return state == a.state && tags == a.tags;
    }
};

enum class StateKind { ENTRY, MATCH, MOVE, RULE, ACCEPT };

struct State {
    StateKind kind;

    State* next;
    State* prev;
    Label* label; // labels are allocated in codegen as they live longer

    State* fill_state;
    Label* fill_label;
    size_t fill;

    size_t rule;
    tcid_t rule_tags;
    tcid_t fall_tags;

    State* eof_state;
    tcid_t eof_tags;

    size_t save; // `yyaccept` number for this state, if any

    const uniq_vector_t<AcceptTrans>* accepts; // `yyaccept` transition table

    bool fallback;
    bool fallthru;
    bool is_base;
    bool linked;

    CodeGo go;

    State();
    ~State();

    FORBID_COPY(State);
};

struct Adfa {
    std::vector<uint32_t> charset;
    std::vector<Rule> rules;
    std::vector<Tag> tags;
    std::set<tagver_t> mtagvers;
    tcpool_t tcpool;
    const tagver_t* finvers;
    tagver_t maxtagver;

    const loc_t loc;
    const std::string name;
    const std::string cond;
    Msg& msg;

    uniq_vector_t<AcceptTrans> accepts;

    uint32_t lower_char;
    uint32_t upper_char;
    uint32_t state_count;

    State* head;
    State* default_state;
    State* start_state;
    std::vector<State*> finstates;

    // In goto/label mode, if there's a loop through the start state and --eager-skip isn't used,
    // then the start state has YYSKIP statement that must be bypassed when entering the DFA.
    // So there's a need for a special start label, different from the start state's label.
    Label* custom_start_label;

    std::set<std::string> stagnames;
    std::set<std::string> stagvars;
    std::set<std::string> mtagnames;
    std::set<std::string> mtagvars;

    const size_t def_rule;
    const size_t key_size;
    size_t max_fill;
    size_t max_nmatch;

    bool need_backup;
    bool need_accept;
    bool oldstyle_ctxmarker;

    CodeBitmap* bitmap;

    const SemAct* entry_action;
    const SemAct* pre_rule_action;
    const SemAct* post_rule_action;

    Adfa(Tdfa&& dfa,
         const std::vector<size_t>& fill,
         size_t key,
         const loc_t& loc,
         const std::string& name,
         const std::string& cond,
         const opt_t* opts,
         Msg& msg,
         const SemAct* entry_action,
         const SemAct* pre_rule_action,
         const SemAct* post_rule_action);

    ~Adfa();
    void reorder();
    void prepare(const opt_t* opts);
    Ret calc_stats(OutputBlock& out) NODISCARD;

  private:
    void add_state_after(State* s, State* x);
    void add_state_before(State* s, State* x);
    void add_single_trans(State* s, State* x);
    void split(State* s);
    void find_base_state(const opt_t* opts);
    void hoist_tags(const opt_t* opts);
    void hoist_tags_and_skip(const opt_t* opts);

    FORBID_COPY(Adfa);
};

inline State::State()
        : kind(StateKind::MATCH)
        , next(nullptr)
        , prev(nullptr)
        , label(nullptr)
        , fill_state(nullptr)
        , fill_label(nullptr)
        , fill(0)
        , rule(Rule::NONE)
        , rule_tags(TCID0)
        , fall_tags(TCID0)
        , eof_state(nullptr)
        , eof_tags(TCID0)
        , save(NOSAVE)
        , accepts(nullptr)
        , fallback(false)
        , fallthru(false)
        , is_base(false)
        , linked(false)
        , go() {
    init_go(&go);
}

inline State::~State() {
    operator delete(go.span);
}

} // namespace re2c

#endif // _RE2C_ADFA_ADFA_
