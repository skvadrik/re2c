#ifndef _RE2C_ADFA_ADFA_
#define _RE2C_ADFA_ADFA_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/codegen/code.h"
#include "src/debug/debug.h"
#include "src/msg/location.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"
#include "src/util/uniq_vector.h"


namespace re2c {

class Msg;
class Output;
struct dfa_t;
struct opt_t;
struct Label;
struct State;

static const size_t NOSAVE = std::numeric_limits<size_t>::max();

typedef uniq_vector_t<std::pair<State*, tcid_t> > accept_t;

class Action {
public:
    enum type_t {
        MATCH,
        INITIAL,
        SAVE,
        MOVE,
        ACCEPT,
        RULE
    } type;

    union {
        size_t save;
        const accept_t * accepts;
        size_t rule;
    } info;

public:
    Action();
    void set_initial();
    void set_save(size_t save);
    void set_move();
    void set_accept(const accept_t * accepts);
    void set_rule(size_t rule);
};

struct State {
    State * next;
    State * prev;
    Label *label;
    size_t fill;
    bool fallback;

    size_t rule;
    tcid_t stadfa_tags;
    tcid_t rule_tags;
    tcid_t fall_tags;
    bool isBase;
    CodeGo go;
    Action action;

    State();
    ~State();
    FORBID_COPY (State);
};

struct DFA {
    accept_t accepts;
    const loc_t loc;
    const std::string name;
    const std::string cond;
    uint32_t lbChar;
    uint32_t ubChar;
    uint32_t nStates;
    State *head;
    State *defstate;
    State *eof_state;
    std::vector<State*> finstates;
    const tcid_t tags0;
    std::vector<uint32_t> &charset;
    std::valarray<Rule> &rules;
    std::vector<Tag> &tags;
    std::set<tagver_t> &mtagvers;
    std::set<std::string> stagnames;
    std::set<std::string> stagvars;
    std::set<std::string> mtagnames;
    std::set<std::string> mtagvars;
    const tagver_t *finvers;
    tcpool_t &tcpool;
    size_t max_fill;
    size_t max_nmatch;
    bool need_backup;
    bool need_accept;
    bool oldstyle_ctxmarker;
    tagver_t maxtagver;
    const size_t def_rule;
    const size_t eof_rule;
    const size_t key_size;
    CodeBitmap *bitmap;
    std::string setup;
    Msg &msg;

    Label *start_label;
    Label *initial_label;

    DFA ( const dfa_t &dfa
        , const std::vector<size_t> &fill
        , size_t key
        , const loc_t &loc
        , const std::string &nm
        , const std::string &cn
        , const std::string &su
        , const opt_t *opts
        , Msg &msg
        );
    ~DFA ();
    void reorder();
    void prepare(const opt_t *opts);
    void calc_stats(OutputBlock &out);
    void emit_body(Output &output, CodeList *program) const;
    void emit_dot(Output &output, CodeList *program) const;

private:
    void addState(State*, State *);
    void split (State *);
    void findBaseState(const opt_t *opts);
    void hoist_tags(const opt_t *opts);
    void hoist_tags_and_skip(const opt_t *opts);

    FORBID_COPY (DFA);
};

inline Action::Action(): type(MATCH), info() {}

inline void Action::set_initial()
{
    if (type == MATCH) {
        // ordinary state with no special action
        type = INITIAL;
        info.save = NOSAVE;
    } else if (type == SAVE) {
        // fallback state: do not loose 'yyaccept'
        type = INITIAL;
    } else if (type == INITIAL) {
        // already marked as initial, probably reuse mode
    } else {
        DASSERT(false);
    }
}

inline void Action::set_save(size_t save)
{
    DASSERT(type == MATCH);
    type = SAVE;
    info.save = save;
}

inline void Action::set_move()
{
    DASSERT(type == MATCH);
    type = MOVE;
}

inline void Action::set_accept(const accept_t * accepts)
{
    DASSERT(type == MATCH);
    type = ACCEPT;
    info.accepts = accepts;
}

inline void Action::set_rule(size_t rule)
{
    DASSERT(type == MATCH);
    type = RULE;
    info.rule = rule;
}

inline State::State()
    : next (0)
    , prev (0)
    , label(NULL)
    , fill (0)
    , fallback (false)
    , rule (Rule::NONE)
    , stadfa_tags (TCID0)
    , rule_tags (TCID0)
    , fall_tags (TCID0)
    , isBase (false)
    , go()
    , action ()
{
    init_go(&go);
}

inline State::~State()
{
    operator delete (go.span);
}

} // namespace re2c

#endif // _RE2C_ADFA_ADFA_
