#ifndef _RE2C_ADFA_ADFA_
#define _RE2C_ADFA_ADFA_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/adfa/action.h"
#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/codegen/label.h"
#include "src/dfa/tcmd.h"
#include "src/msg/location.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"


namespace re2c {

class Msg;
struct opt_t;
class Output;
struct dfa_t;

struct State
{
    label_t label;
    State * next;
    State * prev;
    size_t fill;
    bool fallback;

    size_t rule;
    tcid_t stadfa_tags;
    tcid_t rule_tags;
    tcid_t fall_tags;
    bool isBase;
    Go go;
    Action action;

    State ()
        : label (label_t::first ())
        , next (0)
        , prev (0)
        , fill (0)
        , fallback (false)
        , rule (Rule::NONE)
        , stadfa_tags (TCID0)
        , rule_tags (TCID0)
        , fall_tags (TCID0)
        , isBase (false)
        , go ()
        , action ()
    {}
    ~State ()
    {
        operator delete (go.span);
    }

    FORBID_COPY (State);
};

struct DFA
{
    accept_t accepts;
    const loc_t loc;
    const std::string name;
    const std::string cond;
    uint32_t lbChar;
    uint32_t ubChar;
    uint32_t nStates;
    State * head;
    State *defstate;
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
    const size_t key_size;
    bitmaps_t bitmaps;
    std::string setup;
    const Code *eof_action;
    Msg &msg;

    std::set<label_t> used_labels;
    label_t start_label;
    label_t initial_label;

    DFA ( const dfa_t &dfa
        , const std::vector<size_t> &fill
        , size_t def
        , size_t key
        , const loc_t &loc
        , const std::string &nm
        , const std::string &cn
        , const std::string &su
        , const Code *eof
        , const opt_t *opts
        , Msg &msg
        );
    ~DFA ();
    void reorder();
    void prepare(const opt_t *opts);
    void calc_stats(OutputBlock &out);
    void count_used_labels(const opt_t *opts);
    void emit_body(Output &output, CodeStmts *program) const;
    void emit_dot(Output &output, CodeStmts *program) const;

private:
    void addState(State*, State *);
    void split (State *);
    void findBaseState(const opt_t *opts);
    void hoist_tags(const opt_t *opts);
    void hoist_tags_and_skip(const opt_t *opts);

    FORBID_COPY (DFA);
};

} // namespace re2c

#endif // _RE2C_ADFA_ADFA_
