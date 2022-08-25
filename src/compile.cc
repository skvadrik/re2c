#include <stddef.h>
#include <stdint.h>
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
#include "src/util/range.h"

namespace re2c {

class Msg;

static std::string make_name(Output& output, const std::string& cond, const loc_t& loc) {
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

LOCAL_NODISCARD(Ret ast_to_dfa(
        const spec_t& spec, Output& output, dfas_t& dfas, DfaAllocator& dfa_alc)) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    const loc_t& loc = block.loc;
    Msg& msg = output.msg;
    const std::vector<AstRule>& ast = spec.rules;
    const std::string&cond = spec.name;
    const std::string name = make_name(output, cond, loc);
    const std::string& setup = spec.setup.empty() ? "" : spec.setup[0]->text;

    // Build a mutable tree representation of a regexp from an immutable AST.
    RESpec re(opts, msg);
    CHECK_RET(re.init(ast));
    split_charset(re);
    find_fixed_tags(re);
    insert_default_tags(re);
    warn_nullable(re, cond);

    // Transform regexp to TNFA.
    Tnfa nfa;
    CHECK_RET(re_to_nfa(nfa, std::move(re)));
    DDUMP_NFA(opts, nfa);

    // Transmorm TNFA to TDFA.
    Tdfa dfa(dfa_alc, nfa.charset.size(), spec.def_rule, spec.eof_rule);
    CHECK_RET(determinization(std::move(nfa), dfa, opts, msg, cond));
    DDUMP_DFA_DET(opts, dfa);

    // Skeleton must be constructed after TDFA construction, but prior to any other TDFA
    // transformations.
    Skeleton skeleton(dfa, opts, name, cond, loc, msg);
    CHECK_RET(skeleton.init());
    warn_undefined_control_flow(skeleton);
    if (opts->target == Target::SKELETON) {
        CHECK_RET(emit_data(skeleton));
    }

    cutoff_dead_rules(dfa, opts, cond, msg);

    insert_fallback_tags(dfa);

    // try to minimize the number of tag variables
    compact_and_optimize_tags(opts, dfa);
    DDUMP_DFA_TAGOPT(opts, dfa);

    freeze_tags(dfa);

    minimization(dfa, opts->minimization);
    DDUMP_DFA_MIN(opts, dfa);

    // find strongly connected components and calculate argument to YYFILL
    std::vector<size_t> fill;
    fillpoints(dfa, fill);

    // Transform TDFA to ADFA (DFA with actions, tunnel automaton).
    Adfa* adfa = new Adfa(
            std::move(dfa), fill, skeleton.sizeof_key, loc, name, cond, setup, opts, msg);
    dfas.push_back(std::unique_ptr<Adfa>(adfa));

    // see note [reordering DFA states]
    adfa->reorder();

    // skeleton is constructed, do further DFA transformations
    adfa->prepare(opts);
    DDUMP_ADFA(opts, *adfa);

    // gather overall DFA statistics and add it to the output block
    CHECK_RET(adfa->calc_stats(block));
    block.max_fill = std::max(block.max_fill, adfa->max_fill);
    block.max_nmatch = std::max(block.max_nmatch, adfa->max_nmatch);
    block.used_yyaccept = block.used_yyaccept || adfa->need_accept;

    return Ret::OK;
}

Ret compile(Scanner& input, Output& output, Opt& opts) {
    Ast ast;
    RulesBlocks rblocks;
    const conopt_t* globopts = &opts.glob;
    OutAllocator& out_alc = output.allocator;
    const loc_t& loc0 = input.tok_loc();
    std::string block_name;
    loc_t block_loc;

    output.header_mode(1);
    CHECK_RET(output.new_block(opts, InputBlock::GLOBAL, block_name, loc0));
    output.wversion_time();

    output.header_mode(0);
    CHECK_RET(output.new_block(opts, InputBlock::GLOBAL, block_name, loc0));
    output.wversion_time();
    output.wdelay_stmt(0, code_line_info_input(out_alc, loc0));

    if (globopts->target == Target::SKELETON) {
        output.wdelay_stmt(0, emit_skeleton_prolog(output));
    }

    const opt_t* accum_opts = output.block().opts;

    for (;;) {
        // parse everything up to the next re2c block
        InputBlock kind;
        CHECK_RET(input.echo(output, block_name, kind));
        if (kind == InputBlock::END) break;

        // parse the next re2c block
        specs_t specs;
        if (kind == InputBlock::USE) {
            const RulesBlock* rb = rblocks.find(block_name);
            if (rb == nullptr) return Ret::FAIL;
            specs = rb->specs;
            CHECK_RET(opts.restore(rb->opts));
            output.state_goto = false;
        }
        output.cond_goto = false;
        block_loc = input.tok_loc();
        CHECK_RET(parse(input, specs, opts, rblocks, ast));

        // start new output block with accumulated options
        CHECK_RET(output.new_block(opts, kind, block_name, block_loc));

        if (kind == InputBlock::RULES) {
            // save AST and options for future use
            rblocks.add(block_name, output.block().opts, specs);
        } else {
            CHECK_RET(check_and_merge_special_rules(specs, output.block().opts, output.msg, ast));

            // compile AST to DFA
            DfaAllocator dfa_alc;
            dfas_t dfas;
            for (const spec_t& spec : specs) {
                CHECK_RET(ast_to_dfa(spec, output, dfas, dfa_alc));
            }

            // compile DFA to code
            gen_code(output, dfas);
        }
        output.wdelay_stmt(0, code_line_info_input(out_alc, input.cur_loc()));

        // accumulate whole-program information from this block
        output.gather_info_from_block();

        // Do not accumulate whole-program options for rules/reuse/local blocks. Global blocks add
        // their named definitions and configurations to the global scope, local blocks don't.
        // Historically global is the default.
        if (kind == InputBlock::GLOBAL) {
            accum_opts = output.block().opts;
        } else {
            CHECK_RET(opts.restore(accum_opts));
        }
    }

    output.total_opts = accum_opts ? accum_opts : rblocks.last_opts();

    // For special targets (skeleton and .dot) merge header into the output file.
    if (globopts->target != Target::CODE && output.need_header) {
        output.need_header = false;
        blocks_t& cblocks = output.cblocks, &hblocks = output.hblocks;
        cblocks.insert(cblocks.end(), hblocks.begin(), hblocks.end());
        hblocks.clear();
    }

    if (globopts->target == Target::SKELETON) {
        output.wdelay_stmt(0, emit_skeleton_epilog(output));
    }

    return Ret::OK;
}

} // namespace re2c
