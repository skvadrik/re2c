#ifndef _RE2C_ADFA_ADFA_
#define _RE2C_ADFA_ADFA_

#include <stddef.h>
#include <stdint.h>
#include <limits>
#include <set>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/codegen/code.h"
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
struct Output;
struct Tdfa;
struct opt_t;
struct Label;
struct State;

static constexpr size_t NOSAVE = std::numeric_limits<size_t>::max();

struct AcceptTrans {
    State* state;
    tcid_t tags;

    bool operator==(const AcceptTrans& a) const {
        return state == a.state && tags == a.tags;
    }
};

class Action {
  public:
    enum class Kind: uint32_t { MATCH, INITIAL, SAVE, MOVE, ACCEPT, RULE } kind;
    union {
        const uniq_vector_t<AcceptTrans>* accepts;
        size_t save;
        size_t rule;
    } info;

  public:
    Action(): kind(Kind::MATCH), info() {}
    void set_initial();
    void set_save(size_t save);
    void set_move();
    void set_accept(const uniq_vector_t<AcceptTrans>* accepts);
    void set_rule(size_t rule);
};

struct State {
    State* next;
    State* prev;
    Label* label; // labels are allocated in codegen as they live longer
    size_t fill;
    bool fallback;

    size_t rule;
    tcid_t rule_tags;
    tcid_t fall_tags;
    bool isBase;
    CodeGo go;
    Action action;

    State();
    ~State();
    FORBID_COPY(State);
};

struct DFA {
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

    uint32_t lbChar;
    uint32_t ubChar;
    uint32_t nStates;
    State* head;
    State* defstate;
    State* eof_state;
    std::vector<State*> finstates;

    std::set<std::string> stagnames;
    std::set<std::string> stagvars;
    std::set<std::string> mtagnames;
    std::set<std::string> mtagvars;

    const size_t def_rule;
    const size_t eof_rule;
    const size_t key_size;
    size_t max_fill;
    size_t max_nmatch;

    bool need_backup;
    bool need_accept;
    bool oldstyle_ctxmarker;

    CodeBitmap* bitmap;
    std::string setup;

    Label* start_label;
    Label* initial_label;

    DFA(Tdfa&& dfa,
        const std::vector<size_t>& fill,
        size_t key,
        const loc_t& loc,
        const std::string& nm,
        const std::string& cn,
        const std::string& su,
        const opt_t* opts,
        Msg& msg);

    ~DFA ();
    void reorder();
    void prepare(const opt_t* opts);
    Ret calc_stats(OutputBlock& out) NODISCARD;
    void emit_dot(Output& output, CodeList* program) const;

  private:
    void addState(State*, State*);
    void split(State*);
    void findBaseState(const opt_t* opts);
    void hoist_tags(const opt_t* opts);
    void hoist_tags_and_skip(const opt_t* opts);

    FORBID_COPY (DFA);
};

inline void Action::set_initial() {
    if (kind == Kind::MATCH) {
        // ordinary state with no special action
        kind = Kind::INITIAL;
        info.save = NOSAVE;
    } else if (kind == Kind::SAVE) {
        // fallback state: do not loose 'yyaccept'
        kind = Kind::INITIAL;
    } else if (kind == Kind::INITIAL) {
        // already marked as initial, probably reuse mode
    } else {
        UNREACHABLE();
    }
}

inline void Action::set_save(size_t save) {
    DCHECK(kind == Kind::MATCH);
    kind = Kind::SAVE;
    info.save = save;
}

inline void Action::set_move() {
    DCHECK(kind == Kind::MATCH);
    kind = Kind::MOVE;
}

inline void Action::set_accept(const uniq_vector_t<AcceptTrans>* accepts) {
    DCHECK(kind == Kind::MATCH);
    kind = Kind::ACCEPT;
    info.accepts = accepts;
}

inline void Action::set_rule(size_t rule) {
    DCHECK(kind == Kind::MATCH);
    kind = Kind::RULE;
    info.rule = rule;
}

inline State::State()
    : next(nullptr),
      prev(nullptr),
      label(nullptr),
      fill(0),
      fallback(false),
      rule(Rule::NONE),
      rule_tags(TCID0),
      fall_tags(TCID0),
      isBase(false),
      go(),
      action() {
    init_go(&go);
}

inline State::~State() {
    operator delete(go.span);
}

} // namespace re2c

#endif // _RE2C_ADFA_ADFA_
