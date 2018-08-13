#ifndef _RE2C_ADFA_ADFA_
#define _RE2C_ADFA_ADFA_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/adfa/action.h"
#include "src/code/bitmap.h"
#include "src/code/go.h"
#include "src/code/label.h"
#include "src/dfa/tcmd.h"
#include "src/re/rule.h"
#include "src/re/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct opt_t;
class OutputFile;
struct Output;
struct dfa_t;

struct State
{
    label_t label;
    State * next;
    size_t fill;
    bool fallback;

    size_t rule;
    tcid_t rule_tags;
    tcid_t fall_tags;
    bool isBase;
    Go go;
    Action action;

    State ()
        : label (label_t::first ())
        , next (0)
        , fill (0)
        , fallback (false)
        , rule (Rule::NONE)
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
    const std::string name;
    const std::string cond;
    const uint32_t line;
    uint32_t lbChar;
    uint32_t ubChar;
    uint32_t nStates;
    State * head;
    const tcid_t tags0;
    std::vector<uint32_t> &charset;
    std::valarray<Rule> &rules;
    std::vector<Tag> &tags;
    std::set<tagver_t> &mtagvers;
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

    DFA    ( const dfa_t &dfa
        , const std::vector<size_t> &fill
        , size_t def
        , size_t key
        , const std::string &nm
        , const std::string &cn
        , uint32_t ln
        , const std::string &su
        );
    ~DFA ();
    void reorder();
    void prepare(const opt_t *opts);
    void calc_stats(uint32_t ln, bool explicit_tags);
    void emit (Output &, uint32_t &, bool, bool &);

private:
    void addState(State*, State *);
    void split (State *);
    void findBaseState ();
    void hoist_tags();
    void hoist_tags_and_skip(const opt_t *opts);
    void count_used_labels(std::set<label_t> &used, label_t start, label_t initial, bool force_start, bool fFlag) const;
    void emit_body (OutputFile &, uint32_t &, const std::set<label_t> & used_labels, label_t initial) const;
    void emit_dot(OutputFile &o, bool last_cond) const;

    FORBID_COPY (DFA);
};

} // namespace re2c

#endif // _RE2C_ADFA_ADFA_
