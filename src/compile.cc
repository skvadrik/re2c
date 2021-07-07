#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <cctype>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/compile.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/encoding/range_suffix.h"
#include "src/msg/location.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/parse.h"
#include "src/parse/scanner.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/skeleton/skeleton.h"
#include "src/util/free_list.h"
#include "src/util/range.h"


namespace re2c {

class Msg;

static std::string make_name(Output &output, const std::string &cond, const loc_t &loc)
{
    std::string name;

    // if the block is included from another file, prepend filename for disambiguation
    if (loc.file > 0) {
        name += output.msg.filenames[loc.file];
        for (size_t i = 0; i < name.length(); ++i) {
            if (!std::isalnum(static_cast<unsigned char>(name[i]))) name[i] = '_';
        }
        name += "_";
    }

    std::ostringstream os;
    os << loc.line;
    name += "line" + os.str();

    // if the block has multiple conditions, append condition name for disambiguation
    if (!cond.empty()) name += "_" + cond;

    return name;
}

static smart_ptr<DFA> ast_to_dfa(const spec_t &spec, Output &output)
{
    OutputBlock &block = output.block();
    const opt_t *opts = block.opts;
    const loc_t &loc = block.loc;
    Msg &msg = output.msg;
    const std::vector<ASTRule> &rules = spec.rules;
    const std::string
        &cond = spec.name,
        name = make_name(output, cond, loc),
        &setup = spec.setup.empty() ? "" : spec.setup[0]->text;

    RangeMgr rangemgr;

    RESpec re(rules, opts, msg, rangemgr);
    split_charset(re);
    find_fixed_tags(re);
    insert_default_tags(re);
    warn_nullable(re, cond);

    nfa_t nfa(re);
    DDUMP_NFA(opts, nfa);

    dfa_t dfa(nfa, spec.def_rule, spec.eof_rule);
    determinization(nfa, dfa, opts, msg, cond);
    DDUMP_DFA_DET(opts, dfa);

    rangemgr.clear();

    // skeleton must be constructed after DFA construction
    // but prior to any other DFA transformations
    Skeleton skeleton(dfa, opts, name, cond, loc, msg);
    warn_undefined_control_flow(skeleton);
    if (opts->target == TARGET_SKELETON) {
        emit_data(skeleton);
    }

    cutoff_dead_rules(dfa, opts, cond, msg);

    insert_fallback_tags(opts, dfa);

    // try to minimize the number of tag variables
    compact_and_optimize_tags(opts, dfa);
    DDUMP_DFA_TAGOPT(opts, dfa);

    freeze_tags(dfa);

    minimization(dfa, opts->dfa_minimization);
    DDUMP_DFA_MIN(opts, dfa);

    // find strongly connected components and calculate argument to YYFILL
    std::vector<size_t> fill;
    fillpoints(dfa, fill);

    // ADFA stands for 'DFA with actions'
    DFA *adfa = new DFA(dfa, fill, skeleton.sizeof_key, loc, name, cond,
        setup, opts, msg);

    // see note [reordering DFA states]
    adfa->reorder();

    // skeleton is constructed, do further DFA transformations
    adfa->prepare(opts);
    DDUMP_ADFA(opts, *adfa);

    // gather overall DFA statistics and add it to the output block
    adfa->calc_stats(block);
    block.max_fill = std::max(block.max_fill, adfa->max_fill);
    block.max_nmatch = std::max(block.max_nmatch, adfa->max_nmatch);
    block.used_yyaccept = block.used_yyaccept || adfa->need_accept;

    return make_smart_ptr(adfa);
}

void compile(Scanner &input, Output &output, Opt &opts)
{
    RulesBlocks rblocks;
    const conopt_t *globopts = &opts.glob;
    code_alc_t &alc = output.allocator;
    const loc_t &loc0 = input.tok_loc();
    std::string block_name;
    loc_t block_loc;

    output.header_mode(1);
    output.new_block(opts, INPUT_GLOBAL, block_name, loc0);
    output.wversion_time();

    output.header_mode(0);
    output.new_block(opts, INPUT_GLOBAL, block_name, loc0);
    output.wversion_time();
    output.wdelay_stmt(0, code_line_info_input(alc, loc0));

    if (globopts->target == TARGET_SKELETON) {
        output.wdelay_stmt(0, emit_skeleton_prolog(output));
    }

    const opt_t *accum_opts = output.block().opts;

    for (;;) {
        // parse everything up to the next re2c block
        InputBlockKind kind = input.echo(output, block_name);
        if (kind == INPUT_ERROR) exit(1);
        if (kind == INPUT_END) break;

        // parse the next re2c block
        specs_t specs;
        if (kind == INPUT_USE) {
            const RulesBlock *rb = rblocks.find(block_name);
            if (rb == NULL) exit(1);
            specs = rb->specs;
            opts.restore(rb->opts);
            output.state_goto = false;
        }
        output.cond_goto = false;
        block_loc = input.tok_loc();
        parse(input, specs, opts, rblocks);

        // start new output block with accumulated options
        output.new_block(opts, kind, block_name, block_loc);

        if (kind == INPUT_RULES) {
            // save AST and options for future use
            rblocks.add(block_name, output.block().opts, specs);
        } else {
            check_and_merge_special_rules(specs, output.block().opts, output.msg);

            // compile AST to DFA
            dfas_t dfas;
            for (specs_t::const_iterator i = specs.begin(); i != specs.end(); ++i) {
                dfas.push_back(ast_to_dfa(*i, output));
            }

            // compile DFA to code
            gen_code(output, dfas);
        }
        output.wdelay_stmt(0, code_line_info_input(alc, input.cur_loc()));

        // accumulate whole-program information from this block
        output.gather_info_from_block();

        // Do not accumulate whole-program options for rules/reuse/local blocks.
        // Global blocks add their named definitions and configurations to the
        // global scope, local blocks don't. Historically global is the default.
        if (kind == INPUT_GLOBAL) {
            accum_opts = output.block().opts;
        } else {
            opts.restore(accum_opts);
        }
    }

    output.total_opts = accum_opts ? accum_opts : rblocks.last_opts();

    if (globopts->target == TARGET_SKELETON) {
        output.wdelay_stmt(0, emit_skeleton_epilog(output));
    }

    AST::flist.clear();
    SemAct::flist.clear();
    RangeSuffix::freeList.clear();
}

} // namespace re2c
