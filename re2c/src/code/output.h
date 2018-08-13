#ifndef _RE2C_CODE_OUTPUT_
#define _RE2C_CODE_OUTPUT_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "src/code/label.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/util/counter.h"
#include "src/util/forbid_copy.h"
#include "src/util/uniq_vector.h"

namespace re2c
{

class Warn;
struct Opt;
struct opt_t;
template <typename value_t> class uniq_vector_t;

struct ConfTags
{
    std::string format;
    std::string separator;

    ConfTags(const std::string &f, const std::string &s)
        : format(f), separator(s) {}
};

struct LineInfo
{
    uint32_t line;
    std::string filename;

    LineInfo(uint32_t l, const std::string &fn)
        : line(l), filename(fn) {}
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
        , YYACCEPT_INIT
        , YYMAXFILL
        , YYMAXNMATCH
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
        const LineInfo *line_info;
    };

    OutputFragment (type_t t, uint32_t i);
    ~OutputFragment ();
    uint32_t count_lines () const;
};

struct OutputBlock
{
    std::vector<OutputFragment *> fragments;
    bool used_yyaccept;
    bool have_user_code;
    uint32_t line;
    std::vector<std::string> types;
    std::set<std::string> stags;
    std::set<std::string> mtags;
    const opt_t *opts;

    OutputBlock ();
    ~OutputBlock ();
    FORBID_COPY(OutputBlock);
};

class OutputFile
{
    std::vector<OutputBlock *> blocks;

public:
    counter_t<label_t> label_counter;
    uint32_t fill_index;
    bool state_goto;
    bool cond_goto;
    bool warn_condition_order;
    Warn &warn;

    explicit OutputFile(Warn &w);
    ~OutputFile();

    std::ostream & stream ();
    OutputBlock &block();
    void insert_code ();
    bool open ();
    void new_block(Opt &opts);

    // immediate output
    OutputFile & wraw (const char *s, const char *e);
    OutputFile & wc (char c);
    OutputFile & wc_hex (uint32_t n);
    OutputFile & wu32 (uint32_t n);
    OutputFile & wu32_hex (uint32_t n);
    OutputFile & wu32_width (uint32_t n, int w);
    OutputFile & wu64 (uint64_t n);
    OutputFile & wstring (const std::string & s);
    OutputFile & ws (const char * s);
    OutputFile & wlabel (label_t l);
    OutputFile & wrange (uint32_t u, uint32_t l);
    OutputFile & wversion_time ();
    OutputFile & wuser_start_label ();
    OutputFile & wind (uint32_t ind);

    // delayed output
    OutputFile & wdelay_tags(const ConfTags *cf, bool mtags);
    OutputFile & wdelay_line_info_input (uint32_t l, const std::string &fn);
    OutputFile & wdelay_line_info_output ();
    OutputFile & wdelay_cond_goto(uint32_t ind);
    OutputFile & wdelay_cond_table(uint32_t ind);
    OutputFile & wdelay_state_goto (uint32_t ind);
    OutputFile & wdelay_types ();
    OutputFile & wdelay_yyaccept_init (uint32_t ind);
    OutputFile & wdelay_yymaxfill ();
    OutputFile& wdelay_yymaxnmatch();
    OutputFile& wdelay_skip(uint32_t ind, bool skip);
    OutputFile& wdelay_peek(uint32_t ind, bool peek);
    OutputFile& wdelay_backup(uint32_t ind, bool backup);

    void fix_first_block_opts();
    void global_lists(uniq_vector_t<std::string> &types,
        std::set<std::string> &stags, std::set<std::string> &mtags) const;

    bool emit(const uniq_vector_t<std::string> &global_types,
        const std::set<std::string> &global_stags,
        const std::set<std::string> &global_mtags,
        size_t max_fill, size_t max_nmatch);

    FORBID_COPY (OutputFile);
};

class HeaderFile
{
    std::ostringstream stream;

public:
    HeaderFile(): stream() {}
    bool emit(const opt_t *opts, const uniq_vector_t<std::string> &types);
    FORBID_COPY (HeaderFile);
};

struct Output
{
    OutputFile source;
    HeaderFile header;
    std::set<std::string> skeletons;
    size_t max_fill;
    size_t max_nmatch;

    explicit Output(Warn &w);
    bool emit();
};

void output_tags          (std::ostream &o, uint32_t ind, const ConfTags &conf, const std::set<std::string> &tags, const opt_t *opts);
void output_line_info     (std::ostream &o, uint32_t line, const std::string &fname, bool iflag);
void output_cond_goto     (std::ostream &o, uint32_t ind, const std::vector<std::string> &conds, const opt_t *opts, Warn &warn, bool warn_cond_order, uint32_t line);
void output_cond_table    (std::ostream &o, uint32_t ind, const std::vector<std::string> &conds, const opt_t *opts);
void output_state_goto    (std::ostream &o, uint32_t ind, uint32_t start_label, uint32_t fill_index, const opt_t *opts);
void output_types         (std::ostream &o, uint32_t ind, const opt_t *opts, const uniq_vector_t<std::string> &types);
void output_version_time  (std::ostream &o, bool version, bool date);
void output_yyaccept_init (std::ostream &o, uint32_t ind, bool, const opt_t *opts);
void output_yymaxfill     (std::ostream &o, uint32_t ind, size_t max_fill, const opt_t *opts);
void output_yymaxnmatch   (std::ostream &o, uint32_t ind, size_t max_nmatch, const opt_t *opts);

} // namespace re2c

#endif // _RE2C_CODE_OUTPUT_
