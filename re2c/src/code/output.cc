#include <stdio.h>
#include <time.h>
#include <iomanip>

#include "config.h"
#include "src/code/emit.h"
#include "src/code/input_api.h"
#include "src/code/output.h"
#include "src/code/print.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/re/encoding/enc.h"
#include "src/util/string_utils.h"
#include "src/util/uniq_vector.h"

namespace re2c
{

OutputFragment::OutputFragment (type_t t, uint32_t i)
    : type (t)
    , stream ()
    , indent (i)
{}

OutputFragment::~OutputFragment()
{
    if (type == STAGS || type == MTAGS) {
        delete tags;
    } else if (type == LINE_INFO_INPUT) {
        delete line_info;
    }
}

uint32_t OutputFragment::count_lines () const
{
    uint32_t lines = 0;
    const std::string content = stream.str ();
    const char * p = content.c_str ();
    for (uint32_t i = 0; i < content.size (); ++i)
    {
        if (p[i] == '\n')
        {
            ++lines;
        }
    }
    return lines;
}

OutputBlock::OutputBlock ()
    : fragments ()
    , used_yyaccept (false)
    , have_user_code (false)
    , line (0)
    , types ()
    , stags ()
    , mtags ()
    , opts(NULL)
{
    fragments.push_back (new OutputFragment (OutputFragment::CODE, 0));
}

OutputBlock::~OutputBlock ()
{
    for (unsigned int i = 0; i < fragments.size (); ++i)
    {
        delete fragments[i];
    }
    delete opts;
}

Output::Output(Warn &w)
    : cblocks()
    , hblocks()
    , blocks(&cblocks)
    , label_counter()
    , fill_index(0)
    , state_goto(false)
    , cond_goto(false)
    , warn_condition_order(true)
    , need_header(false)
    , warn(w)
    , skeletons()
    , max_fill(1)
    , max_nmatch(1)
{}

Output::~Output ()
{
    for (uint32_t i = 0; i < cblocks.size(); ++i) delete cblocks[i];
    for (uint32_t i = 0; i < hblocks.size(); ++i) delete hblocks[i];
}

void Output::header_mode(bool on)
{
    blocks = on ? &hblocks : &cblocks;
}

OutputBlock& Output::block()
{
    return *blocks->back();
}

std::ostream & Output::stream ()
{
    return block().fragments.back ()->stream;
}

Output &Output::wraw(const char *s, const char *e)
{
    if (s != e && block().opts->target == TARGET_CODE) {
        insert_code();

        // scan for non-whitespace characters
        bool &code = block().have_user_code;
        for (const char *p = s; !code && p < e; ++p) {
            code = !isspace(*p);
        }

        // convert CR LF to LF
        std::ostream &o = stream();
        for (const char *p = s;; ++p) {
            std::streamsize l = p - s;
            if (p == e) {
                o.write(s, l);
                break;
            } else if (*p == '\n') {
                if (p > s && p[-1] == '\r') --l;
                o.write(s, l);
                s = p;
            }
        }
    }
    return *this;
}

Output & Output::wu32_hex (uint32_t n)
{
    insert_code();
    prtHex(stream(), n, block().opts->encoding.szCodeUnit());
    return *this;
}

Output & Output::wc_hex (uint32_t n)
{
    insert_code();
    const opt_t *opts = block().opts;
    const Enc &e = opts->encoding;
    prtChOrHex(stream(), n, e.szCodeUnit(), e.type() == Enc::EBCDIC, opts->target == TARGET_DOT);
    return *this;
}

Output & Output::wrange (uint32_t l, uint32_t u)
{
    insert_code();
    const opt_t *opts = block().opts;
    const Enc &e = opts->encoding;
    printSpan(stream(), l, u, e.szCodeUnit(), e.type() == Enc::EBCDIC, opts->target == TARGET_DOT);
    return *this;
}

Output & Output::wu32_width (uint32_t n, int w)
{
    insert_code();
    stream () << std::setw (w);
    stream () << n;
    return *this;
}

Output & Output::wversion_time ()
{
    insert_code();
    output_version_time(stream(), block().opts->version, !block().opts->bNoGenerationDate);
    return *this;
}

Output & Output::wuser_start_label ()
{
    insert_code();
    const std::string label = block().opts->startlabel;
    if (!label.empty())
    {
        wstring(label).ws(":\n");
    }
    return *this;
}

Output & Output::wc (char c)
{
    insert_code();
    stream () << c;
    return *this;
}

Output & Output::wu32 (uint32_t n)
{
    insert_code();
    stream () << n;
    return *this;
}

Output & Output::wu64 (uint64_t n)
{
    insert_code();
    stream () << n;
    return *this;
}

Output & Output::wstring (const std::string & s)
{
    insert_code();
    stream () << s;
    return *this;
}

Output & Output::ws (const char * s)
{
    insert_code();
    stream () << s;
    return *this;
}

Output & Output::wlabel (label_t l)
{
    insert_code();
    stream () << l;
    return *this;
}

Output & Output::wind (uint32_t ind)
{
    insert_code();
    stream () << indent(ind, block().opts->indString);
    return *this;
}

void Output::insert_code ()
{
    if (block().fragments.back()->type != OutputFragment::CODE) {
        block().fragments.push_back(new OutputFragment(OutputFragment::CODE, 0));
    }
}

Output &Output::wdelay_tags(const ConfTags *cf, bool mtags)
{
    if (block().opts->target == TARGET_CODE) {
        OutputFragment *frag = new OutputFragment(
            mtags ? OutputFragment::MTAGS : OutputFragment::STAGS, 0);
        frag->tags = cf;
        blocks->back()->fragments.push_back(frag);
    }
    return *this;
}

Output & Output::wdelay_line_info_input (uint32_t l, const std::string &fn)
{
    OutputFragment *frag = new OutputFragment(OutputFragment::LINE_INFO_INPUT, 0);
    frag->line_info = new LineInfo(l, fn);
    blocks->back()->fragments.push_back(frag);
    return *this;
}

Output & Output::wdelay_line_info_output ()
{
    block().fragments.push_back (new OutputFragment (OutputFragment::LINE_INFO_OUTPUT, 0));
    return *this;
}

Output & Output::wdelay_cond_goto(uint32_t ind)
{
    if (block().opts->cFlag && !cond_goto) {
        block().fragments.push_back(new OutputFragment(OutputFragment::COND_GOTO, ind));
        cond_goto = true;
    }
    return *this;
}

Output & Output::wdelay_cond_table(uint32_t ind)
{
    if (block().opts->gFlag && block().opts->cFlag && !cond_goto) {
        block().fragments.push_back(new OutputFragment(OutputFragment::COND_TABLE, ind));
    }
    return *this;
}

Output & Output::wdelay_state_goto (uint32_t ind)
{
    if (block().opts->target == TARGET_CODE
        && block().opts->fFlag && !state_goto) {
        block().fragments.push_back (new OutputFragment (OutputFragment::STATE_GOTO, ind));
        state_goto = true;
    }
    return *this;
}

Output & Output::wdelay_types ()
{
    if (block().opts->target == TARGET_CODE) {
        warn_condition_order = false; // see note [condition order]
        block().fragments.push_back (new OutputFragment (OutputFragment::TYPES, 0));
    }
    return *this;
}

Output & Output::wdelay_yyaccept_init (uint32_t ind)
{
    block().fragments.push_back (new OutputFragment (OutputFragment::YYACCEPT_INIT, ind));
    return *this;
}

Output & Output::wdelay_yymaxfill ()
{
    if (block().opts->target == TARGET_CODE) {
        block().fragments.push_back (new OutputFragment (OutputFragment::YYMAXFILL, 0));
    }
    return *this;
}

Output& Output::wdelay_yymaxnmatch()
{
    if (block().opts->target == TARGET_CODE
        && block().opts->posix_captures) {
        block().fragments.push_back (new OutputFragment (OutputFragment::YYMAXNMATCH, 0));
    }
    return *this;
}

Output& Output::wdelay_skip(uint32_t ind, bool skip)
{
    if (skip) {
        OutputFragment *f = new OutputFragment(OutputFragment::SKIP, ind);
        block().fragments.push_back(f);
    }
    return *this;
}

Output& Output::wdelay_peek(uint32_t ind, bool peek)
{
    if (peek) {
        OutputFragment *f = new OutputFragment(OutputFragment::PEEK, ind);
        block().fragments.push_back(f);
    }
    return *this;
}

Output& Output::wdelay_backup(uint32_t ind, bool backup)
{
    if (backup) {
        OutputFragment *f = new OutputFragment(OutputFragment::BACKUP, ind);
        block().fragments.push_back(f);
    }
    return *this;
}

void Output::new_block(Opt &opts)
{
    OutputBlock *b = new OutputBlock;
    b->opts = opts.snapshot();
    blocks->push_back(b);

    // start label hapens to be the only option
    // that must be reset for each new block
    opts.reset_startlabel();
}

static void fix_first_block_opts(blocks_t &blocks)
{
    // If the initial block contains only whitespace and no user code,
    // then re2c options specified in the first re2c block are also
    // applied to the initial block.
    if (blocks.size() >= 2) {
        OutputBlock *fst = blocks[0], *snd = blocks[1];
        if (!fst->have_user_code) {
            *const_cast<opt_t *>(fst->opts) = *snd->opts;
        }
    }
}

static void foldexpr(std::vector<OutputFragment*> &frags)
{
    const size_t n = frags.size();
    for (size_t i = 0; i < n;) {

        if (i + 2 < n) {
            OutputFragment::type_t
                &x = frags[i]->type,
                &y = frags[i + 1]->type,
                &z = frags[i + 2]->type;
            if (x == OutputFragment::BACKUP && y == OutputFragment::PEEK && z == OutputFragment::SKIP) {
                x = OutputFragment::BACKUP_PEEK_SKIP;
                y = z = OutputFragment::EMPTY;
                i += 3;
                continue;
            } else if (x == OutputFragment::SKIP && y == OutputFragment::BACKUP && z == OutputFragment::PEEK) {
                x = OutputFragment::SKIP_BACKUP_PEEK;
                y = z = OutputFragment::EMPTY;
                i += 3;
                continue;
            }
        }

        if (i + 1 < n) {
            OutputFragment::type_t
                &x = frags[i]->type,
                &y = frags[i + 1]->type;
            if (x == OutputFragment::PEEK && y == OutputFragment::SKIP) {
                x = OutputFragment::PEEK_SKIP;
                y = OutputFragment::EMPTY;
                i += 2;
                continue;
            } else if (x == OutputFragment::SKIP && y == OutputFragment::PEEK) {
                x = OutputFragment::SKIP_PEEK;
                y = OutputFragment::EMPTY;
                i += 2;
                continue;
            } else if (x == OutputFragment::SKIP && y == OutputFragment::BACKUP) {
                x = OutputFragment::SKIP_BACKUP;
                y = OutputFragment::EMPTY;
                i += 2;
                continue;
            } else if (x == OutputFragment::BACKUP && y == OutputFragment::PEEK) {
                x = OutputFragment::BACKUP_PEEK;
                y = OutputFragment::EMPTY;
                i += 2;
                continue;
            } else if (x == OutputFragment::BACKUP && y == OutputFragment::SKIP) {
                x = OutputFragment::BACKUP_SKIP;
                y = OutputFragment::EMPTY;
                i += 2;
                continue;
            }
        }

        ++i;
    }
}

bool Output::emit_blocks(const std::string &fname, blocks_t &blocks,
    const uniq_vector_t<std::string> &global_types,
    const std::set<std::string> &global_stags,
    const std::set<std::string> &global_mtags)
{
    FILE *file = NULL;
    std::string filename = fname;
    if (filename.empty()) {
        filename = "<stdout>";
        file = stdout;
    }
    else {
        file = fopen(filename.c_str(), "w");
        if (!file) {
            error("cannot open output file: %s", filename.c_str());
            return false;
        }
    }

    fix_first_block_opts(blocks);

    unsigned int line_count = 1;
    for (unsigned int j = 0; j < blocks.size(); ++j) {
        OutputBlock & b = *blocks[j];
        const opt_t *bopt = b.opts;

        if (bopt->input_api == INPUT_DEFAULT) {
            foldexpr(b.fragments);
        }

        const size_t n = b.fragments.size();
        for (size_t i = 0; i < n; ++i) {
            OutputFragment & f = * b.fragments[i];
            std::ostringstream &o = f.stream;
            const uint32_t ind = f.indent ? f.indent : bopt->topIndent;

            switch (f.type) {
            case OutputFragment::EMPTY:
            case OutputFragment::CODE: break;
            case OutputFragment::LINE_INFO_INPUT:
                output_line_info(o, f.line_info->line, f.line_info->filename, bopt->iFlag);
                break;
            case OutputFragment::LINE_INFO_OUTPUT:
                output_line_info(o, line_count + 1, filename, bopt->iFlag);
                break;
            case OutputFragment::COND_GOTO:
                output_cond_goto(o, ind, b.types,
                    bopt, warn, warn_condition_order, b.line);
                break;
            case OutputFragment::COND_TABLE:
                output_cond_table(o, ind, b.types, bopt);
                break;
            case OutputFragment::STATE_GOTO:
                output_state_goto(o, ind, 0, fill_index, bopt);
                break;
            case OutputFragment::STAGS:
                output_tags(o, ind, *f.tags, global_stags, bopt);
                break;
            case OutputFragment::MTAGS:
                output_tags(o, ind, *f.tags, global_mtags, bopt);
                break;
            case OutputFragment::TYPES:
                output_types(o, ind, block().opts, global_types);
                break;
            case OutputFragment::YYACCEPT_INIT:
                output_yyaccept_init(o, ind, b.used_yyaccept, bopt);
                break;
            case OutputFragment::YYMAXFILL:
                output_yymaxfill(o, ind, max_fill, bopt);
                break;
            case OutputFragment::YYMAXNMATCH:
                output_yymaxnmatch(o, ind, max_nmatch, bopt);
                break;
            case OutputFragment::SKIP:
                output_skip(o, ind, bopt);
                break;
            case OutputFragment::PEEK:
                output_peek(o, ind, bopt);
                break;
            case OutputFragment::BACKUP:
                output_backup(o, ind, bopt);
                break;
            case OutputFragment::PEEK_SKIP:
                output_peek_skip(o, ind, bopt);
                break;
            case OutputFragment::SKIP_PEEK:
                output_skip_peek(o, ind, bopt);
                break;
            case OutputFragment::SKIP_BACKUP:
                output_skip_backup(o, ind, bopt);
                break;
            case OutputFragment::BACKUP_SKIP:
                output_backup_skip(o, ind, bopt);
                break;
            case OutputFragment::BACKUP_PEEK:
                output_backup_peek(o, ind, bopt);
                break;
            case OutputFragment::BACKUP_PEEK_SKIP:
                output_backup_peek_skip(o, ind, bopt);
                break;
            case OutputFragment::SKIP_BACKUP_PEEK:
                output_skip_backup_peek(o, ind, bopt);
                break;
            }

            std::string content = o.str();
            fwrite(content.c_str(), 1, content.size(), file);
            line_count += f.count_lines();
        }
    }

    fclose(file);
    return true;
}

static bool have_cond_frag(const blocks_t &blocks)
{
    for (blocks_citer_t b = blocks.begin(); b != blocks.end(); ++b) {
        const frags_t &fs = (*b)->fragments;
        for (frags_citer_t f = fs.begin(); f != fs.end(); ++f) {
            if ((*f)->type == OutputFragment::TYPES) {
                return true;
            }
        }
    }
    return false;
}

static void add_symbols(const OutputBlock &block,
    uniq_vector_t<std::string> &conds,
    std::set<std::string> &stags,
    std::set<std::string> &mtags)
{
    const std::vector<std::string> &cs = block.types;
    for (size_t j = 0; j < cs.size(); ++j) {
        conds.find_or_add(cs[j]);
    }

    const std::set<std::string> &st = block.stags, &mt = block.mtags;
    stags.insert(st.begin(), st.end());
    mtags.insert(mt.begin(), mt.end());
}

bool Output::emit()
{
    if (warn.error()) return false;

    // gather global lists of conditions and tags
    uniq_vector_t<std::string> conds;
    std::set<std::string> stags, mtags;
    for (uint32_t i = 0; i < cblocks.size(); ++i) {
        add_symbols (*cblocks[i], conds, stags, mtags);
    }
    for (uint32_t i = 0; i < hblocks.size(); ++i) {
        add_symbols (*hblocks[i], conds, stags, mtags);
    }

    // global options are last block's options
    const opt_t *opts = block().opts;
    bool ok = true;

    // emit .h file
    if (!opts->header_file.empty() || need_header) {
        // old-style -t, --type-headers usage implies condition generation
        if (!conds.empty() && !have_cond_frag(hblocks)) {
            std::ostream &os = hblocks.back()->fragments.back ()->stream;
            os << std::endl;
            output_types(os, 0, opts, conds);
        }

        ok &= emit_blocks(opts->header_file, hblocks, conds, stags, mtags);
    }

    // emit .c file
    ok &= emit_blocks(opts->output_file, cblocks, conds, stags, mtags);

    return ok;
}

void output_tags(std::ostream &o, uint32_t ind, const ConfTags &conf,
    const std::set<std::string> &tags, const opt_t *opts)
{
    std::set<std::string>::const_iterator
        tag = tags.begin(),
        end = tags.end();
    o << indent(ind, opts->indString);
    for (;tag != end;) {
        std::string fmt = conf.format;
        strrreplace(fmt, "@@", *tag);
        o << fmt;
        if (++tag == end) {
            break;
        }
        o << conf.separator;
    }
}

void output_state_goto(std::ostream & o, uint32_t ind,
    uint32_t start_label, uint32_t fill_index, const opt_t *opts)
{
    const std::string
        indstr = indent(ind, opts->indString),
        getstate = opts->state_get_naked
            ? opts->state_get
            : opts->state_get + "()";

    o << indstr << "switch (" << getstate << ") {\n";
    if (opts->bUseStateAbort)
    {
        o << indstr << "default: abort();\n";
        o << indstr << "case -1: goto " << opts->labelPrefix << start_label << ";\n";
    }
    else
    {
        o << indstr << "default: goto " << opts->labelPrefix << start_label << ";\n";
    }
    for (uint32_t i = 0; i < fill_index; ++i)
    {
        o << indstr << "case " << i << ": goto " << opts->yyfilllabel << i << ";\n";
    }
    o << indstr << "}\n";
    if (opts->bUseStateNext)
    {
        o << opts->yynext << ":\n";
    }
}

void output_yyaccept_init (std::ostream & o, uint32_t ind, bool used_yyaccept, const opt_t *opts)
{
    if (used_yyaccept)
    {
        o << indent(ind, opts->indString) << "unsigned int " << opts->yyaccept << " = 0;\n";
    }
}

void output_yymaxfill(std::ostream &o, uint32_t ind,
    size_t max_fill, const opt_t *opts)
{
    o << indent(ind, opts->indString) << "#define YYMAXFILL " << max_fill << "\n";
}

void output_yymaxnmatch(std::ostream &o, uint32_t ind,
    size_t max_nmatch, const opt_t *opts)
{
    o << indent(ind, opts->indString) << "#define YYMAXNMATCH " << max_nmatch << "\n";
}

void output_line_info(std::ostream &o, uint32_t line,
    const std::string &fname, bool iflag)
{
    if (!iflag) {
        o << "#line " << line << " \"" << fname << "\"\n";
    }
}

void output_types(std::ostream &o, uint32_t ind, const opt_t *opts,
    const uniq_vector_t<std::string> &types)
{
    const std::string indstr = opts->indString;
    o << indent(ind++, indstr) << "enum " << opts->yycondtype << " {\n";
    for (size_t i = 0; i < types.size(); ++i) {
        o << indent(ind, indstr) << opts->condEnumPrefix << types[i] << ",\n";
    }
    o << indent(--ind, indstr) << "};\n";
}

void output_version_time(std::ostream &o, bool version, bool date)
{
    o << "/* Generated by re2c";
    if (version) {
        o << " " << PACKAGE_VERSION;
    }
    if (date) {
        o << " on ";
        time_t now = time (NULL);
        o.write (ctime (&now), 24);
    }
    o << " */" << "\n";
}

/*
 * note [condition order]
 *
 * In theory re2c makes no guarantee about the order of conditions in
 * the generated lexer. Users should define condition type 'YYCONDTYPE'
 * and use values of this type with 'YYGETCONDITION' and 'YYSETCONDITION'.
 * This way code is independent of internal re2c condition numbering.
 *
 * However, it is possible to manually hardcode condition numbers and make
 * re2c generate condition dispatch without explicit use of condition names
 * (nested 'if' statements with '-b' or computed 'goto' table with '-g').
 * This code is syntactically valid (compiles), but unsafe:
 *     - change of re2c options may break compilation
 *     - change of internal re2c condition numbering may break runtime
 *
 * re2c has to preserve the existing numbering scheme.
 *
 * re2c warns about implicit assumptions about condition order, unless:
 *     - condition type is defined with 'types:re2c' or '-t, --type-header'
 *     - dispatch is independent of condition order: either it uses
 *       explicit condition names or there's only one condition and
 *       dispatch shrinks to unconditional jump
 */

static std::string output_cond_get(const opt_t *opts)
{
    return opts->cond_get + (opts->cond_get_naked ? "" : "()");
}

static void output_cond_goto_binary(std::ostream &o, uint32_t ind,
    const std::vector<std::string> &conds, const opt_t *opts,
    size_t lower, size_t upper)
{
    const std::string indstr = indent(ind, opts->indString);

    if (lower == upper) {
        o << indstr << "goto " << opts->condPrefix << conds[lower] << ";\n";
    } else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        o << indstr << "if (" << output_cond_get(opts) << " < " << middle << ") {\n";
        output_cond_goto_binary(o, ind + 1, conds, opts, lower, middle - 1);
        o << indstr << "} else {\n";
        output_cond_goto_binary(o, ind + 1, conds, opts, middle, upper);
        o << indstr << "}\n";
    }
}

void output_cond_goto(std::ostream &o, uint32_t ind,
    const std::vector<std::string> &conds, const opt_t *opts,
    Warn &warn, bool warn_cond_order, uint32_t line)
{
    const size_t ncond = conds.size();
    const std::string indstr = indent(ind, opts->indString);

    if (opts->target == TARGET_DOT) {
        for (size_t i = 0; i < ncond; ++i) {
            const std::string &cond = conds[i];
            o << "0 -> " << cond << " [label=\"state=" << cond << "\"]\n";
        }
        return;
    }

    if (opts->gFlag) {
        o << indstr << "goto *" << opts->yyctable
            << "[" << output_cond_get(opts) << "];\n";
    } else if (opts->sFlag) {
        if (ncond == 1) warn_cond_order = false;
        output_cond_goto_binary(o, ind, conds, opts, 0, ncond - 1);
    } else {
        warn_cond_order = false;
        o << indstr << "switch (" << output_cond_get(opts) << ") {\n";
        for (size_t i = 0; i < ncond; ++i) {
            const std::string &cond = conds[i];
            o << indstr << "case " << opts->condEnumPrefix << cond
                <<": goto " << opts->condPrefix << cond << ";\n";
        }
        o << indstr << "}\n";
    }

    warn_cond_order &= opts->header_file.empty();

    // see note [condition order]
    if (warn_cond_order) warn.condition_order(line);
}

void output_cond_table(std::ostream &o, uint32_t ind,
    const std::vector<std::string> &conds, const opt_t *opts)
{
    const size_t ncond = conds.size();
    const std::string indstr = opts->indString;

    o << indent(ind++, indstr) << "static void *" << opts->yyctable << "[" << ncond << "] = {\n";
    for (size_t i = 0; i < ncond; ++i) {
        o << indent(ind, indstr) << "&&" << opts->condPrefix << conds[i] << ",\n";
    }
    o << indent(--ind, indstr) << "};\n";
}

} // namespace re2c
