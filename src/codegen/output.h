#ifndef _RE2C_CODE_OUTPUT_
#define _RE2C_CODE_OUTPUT_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "src/codegen/label.h"
#include "src/msg/location.h"
#include "src/util/counter.h"
#include "src/util/forbid_copy.h"
#include "src/util/uniq_vector.h"


namespace re2c {

class Msg;
struct Opt;
struct opt_t;
template <typename value_t> class uniq_vector_t;

struct OutputFragment;
struct OutputBlock;

typedef std::vector<OutputFragment *> frags_t;
typedef std::vector<OutputBlock *> blocks_t;
typedef frags_t::const_iterator frags_citer_t;
typedef blocks_t::const_iterator blocks_citer_t;

struct ConfTags
{
    std::string format;
    std::string separator;

    ConfTags(const std::string &f, const std::string &s)
        : format(f), separator(s) {}
};

struct OutputFragment
{
    enum type_t
        { CODE
//        , CONFIG
        , COND_GOTO
        , COND_TABLE
        , LINE_INFO_INPUT
        , LINE_INFO_OUTPUT
        , STATE_GOTO
        , STAGS
        , MTAGS
        , TYPES
        , ACCEPT_INIT
        , MAXFILL
        , MAXNMATCH
        , SKIP
        , PEEK
        , BACKUP
        , PEEK_SKIP
        , SKIP_PEEK
        , SKIP_BACKUP
        , BACKUP_SKIP
        , BACKUP_PEEK
        , BACKUP_PEEK_SKIP
        , SKIP_BACKUP_PEEK
        , EMPTY
        };

    type_t type;
    std::ostringstream stream;
    uint32_t indent;
    union
    {
        const ConfTags *tags;
        const loc_t *loc;
    };

    OutputFragment (type_t t, uint32_t i);
    ~OutputFragment ();
    uint32_t count_lines () const;
};

struct OutputBlock
{
    const loc_t loc;
    frags_t fragments;
    bool used_yyaccept;
    bool have_user_code;
    std::vector<std::string> types;
    std::set<std::string> stags;
    std::set<std::string> mtags;
    const opt_t *opts;

    explicit OutputBlock(const loc_t &loc);
    ~OutputBlock();
    FORBID_COPY(OutputBlock);
};

class Output
{
    blocks_t cblocks; /* .c file */
    blocks_t hblocks; /* .h file */
    blocks_t *pblocks; /* selector */

public:
    counter_t<label_t> label_counter;
    uint32_t fill_index;
    bool state_goto;
    bool cond_goto;
    bool warn_condition_order;
    bool need_header;
    Msg &msg;
    std::set<std::string> skeletons;
    size_t max_fill;
    size_t max_nmatch;

    explicit Output(Msg &msg);
    ~Output();

    std::ostream & stream ();
    OutputBlock &block();
    void insert_code ();
    bool open ();
    void new_block(Opt &opts, const loc_t &loc);
    void header_mode(bool on);

    // immediate output
    Output & wraw (const char *s, const char *e);
    Output & wc (char c);
    Output & wc_hex (uint32_t n);
    Output & wu32 (uint32_t n);
    Output & wu32_hex (uint32_t n);
    Output & wu32_width (uint32_t n, int w);
    Output & wu64 (uint64_t n);
    Output & wstring (const std::string & s);
    Output & ws (const char * s);
    Output & wlabel (label_t l);
    Output & wrange (uint32_t u, uint32_t l);
    Output & wversion_time ();
    Output & wuser_start_label ();
    Output & wind (uint32_t ind);

    // delayed output
    Output & wdelay_tags(const ConfTags *cf, bool mtags);
    Output & wdelay_line_info_input (const loc_t &loc);
    Output & wdelay_line_info_output ();
    Output & wdelay_cond_goto(uint32_t ind);
    Output & wdelay_cond_table(uint32_t ind);
    Output & wdelay_state_goto (uint32_t ind);
    Output & wdelay_types ();
    Output & wdelay_yyaccept_init (uint32_t ind);
    Output & wdelay_yymaxfill ();
    Output& wdelay_yymaxnmatch();
    Output& wdelay_skip(uint32_t ind, bool skip);
    Output& wdelay_peek(uint32_t ind, bool peek);
    Output& wdelay_backup(uint32_t ind, bool backup);

    bool emit();
    bool emit_blocks(const std::string &fname, blocks_t &blocks,
        const uniq_vector_t<std::string> &global_types,
        const std::set<std::string> &global_stags,
        const std::set<std::string> &global_mtags);

    FORBID_COPY (Output);
};

void output_tags          (std::ostream &o, uint32_t ind, const ConfTags &conf, const std::set<std::string> &tags, const opt_t *opts);
void output_line_info     (std::ostream &o, uint32_t line, const std::string &fname, bool iflag);
void output_cond_goto     (std::ostream &o, uint32_t ind, const std::vector<std::string> &conds, const opt_t *opts, Msg &msg, bool warn_cond_order, const loc_t &loc);
void output_cond_table    (std::ostream &o, uint32_t ind, const std::vector<std::string> &conds, const opt_t *opts);
void output_state_goto    (std::ostream &o, uint32_t ind, uint32_t start_label, uint32_t fill_index, const opt_t *opts);
void output_types         (std::ostream &o, uint32_t ind, const opt_t *opts, const uniq_vector_t<std::string> &types);
void output_version_time  (std::ostream &o, bool version, bool date);
void output_yyaccept_init (std::ostream &o, uint32_t ind, bool, const opt_t *opts);
void output_yymaxfill     (std::ostream &o, uint32_t ind, size_t max_fill, const opt_t *opts);
void output_yymaxnmatch   (std::ostream &o, uint32_t ind, size_t max_nmatch, const opt_t *opts);

} // namespace re2c

#endif // _RE2C_CODE_OUTPUT_
