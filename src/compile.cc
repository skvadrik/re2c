#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/output.h"
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
#include "src/util/smart_ptr.h"


namespace re2c {

class Msg;

static std::string make_name(const std::string &cond, uint32_t line)
{
    std::ostringstream os;
    os << "line" << line;
    std::string name = os.str();
    if (!cond.empty ())
    {
        name += "_";
        name += cond;
    }
    return name;
}

static smart_ptr<DFA> ast_to_dfa(const spec_t &spec, Output &output)
{
    const opt_t *opts = output.block().opts;
    const loc_t &loc = output.block().loc;
    Msg &msg = output.msg;
    const std::vector<ASTRule> &rules = spec.rules;
    const size_t defrule = spec.defs.empty() ? Rule::NONE : rules.size() - 1;
    const Code *eof = spec.eofs.empty() ? NULL : spec.eofs.front();
    const std::string
        &cond = spec.name,
        name = make_name(cond, loc.line),
        &setup = spec.setup.empty() ? "" : spec.setup[0]->text;

    RangeMgr rangemgr;

    RESpec re(rules, opts, msg, rangemgr);
    split_charset(re);
    find_fixed_tags(re);
    insert_default_tags(re);
    warn_nullable(re, cond);

    nfa_t nfa(re);
    DDUMP_NFA(opts, nfa);

    dfa_t dfa(nfa, opts, cond, msg);
    DDUMP_DFA_DET(opts, dfa);

    rangemgr.clear();

    // skeleton must be constructed after DFA construction
    // but prior to any other DFA transformations
    Skeleton skeleton(dfa, opts, defrule, name, cond, loc, msg);
    warn_undefined_control_flow(skeleton);
    if (opts->target == TARGET_SKELETON) {
        emit_data(skeleton);
    }

    cutoff_dead_rules(dfa, opts, defrule, cond, msg);

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
    DFA *adfa = new DFA(dfa, fill, defrule, skeleton.sizeof_key,
        loc, name, cond, setup, eof, opts, msg);

    // see note [reordering DFA states]
    adfa->reorder();

    // skeleton is constructed, do further DFA transformations
    adfa->prepare(opts);
    DDUMP_ADFA(opts, *adfa);

    // finally gather overall DFA statistics
    adfa->calc_stats(opts);

    // accumulate global statistics from this particular DFA
    output.max_fill = std::max(output.max_fill, adfa->max_fill);
    output.max_nmatch = std::max(output.max_nmatch, adfa->max_nmatch);
    if (adfa->need_accept) {
        output.block().used_yyaccept = true;
    }

    return make_smart_ptr(adfa);
}

void compile(Scanner &input, Output &output, Opt &opts)
{
    specs_t rspecs;
    symtab_t symtab;
    const conopt_t *globopts = &opts.glob;
    const opt_t *ropts = NULL;
    typedef std::vector<smart_ptr<DFA> > dfas_t;

    const loc_t &loc0 = input.tok_loc();

    output.header_mode(1);
    output.new_block(opts, loc0);
    output.wversion_time();

    output.header_mode(0);
    output.new_block(opts, loc0);
    output.wversion_time();
    output.wdelay_line_info_input(loc0);

    if (globopts->target == TARGET_SKELETON) {
        emit_prolog(output);
    }

    for (;;) {
        // parse everything up to the next re2c block
        Scanner::ParseMode mode = input.echo(output);
        if (mode == Scanner::Stop) break;
        validate_mode(mode, globopts->rFlag, ropts, input);

        // parse the next re2c block
        specs_t specs;
        if (mode == Scanner::Reuse) {
            specs = rspecs;
            opts.restore(ropts);
            opts.reset_mapCodeName();
            output.fill_index = 0;
            output.state_goto = false;
            output.cond_goto = false;
        }
        parse(input, specs, symtab, opts);

        // start new output block with accumulated options
        const loc_t &loc = input.cur_loc();
        output.new_block(opts, loc);

        if (mode == Scanner::Rules) {
            // save AST and options for future use
            rspecs = specs;
            ropts = output.block().opts;
        } else {
            validate_ast(specs, output.block().opts, output.msg);
            normalize_ast(specs);

            // compile AST to DFA
            dfas_t dfas;
            for (specs_t::const_iterator i = specs.begin(); i != specs.end(); ++i) {
                dfas.push_back(ast_to_dfa(*i, output));
            }

            // compile DFA to code
            bool prolog = false;
            uint32_t ind = output.block().opts->topIndent;
            for (dfas_t::const_iterator i = dfas.begin(); i != dfas.end(); ++i) {
                (*i)->emit(output, ind, (i + 1) == dfas.end(), prolog);
            }
        }

        output.wdelay_line_info_input(loc);
    }

    if (globopts->target == TARGET_SKELETON) {
        emit_epilog (output, output.skeletons);
    }

    AST::flist.clear();
    Code::flist.clear();
    RangeSuffix::freeList.clear();
}

} // namespace re2c
