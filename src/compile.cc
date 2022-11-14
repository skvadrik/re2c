#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <cctype>

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
#include "src/parse/input.h"
#include "src/regexp/regexp.h"
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
        const AstGram& gram, Output& output, Adfas& dfas, DfaAllocator& dfa_alc)) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    const loc_t& loc = block.loc;
    Msg& msg = output.msg;
    const std::vector<AstRule>& ast = gram.rules;
    const std::string&cond = gram.name;
    const std::string name = make_name(output, cond, loc);
    const std::string& setup = gram.setup.empty() ? "" : gram.setup[0]->text;

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
    Tdfa dfa(dfa_alc, nfa.charset.size(), gram.def_rule, gram.eof_rule);
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

Ret compile(Input& input, Output& output, Opt& opts) {
    Ast ast;
    std::string block_name;
    loc_t block_loc;
    DfaAllocator dfa_alc;

    CHECK_RET(output.gen_prolog(opts, input.tok_loc()));

    const opt_t* accum_opts = output.block().opts;

    for (;;) {
        // parse everything up to the next re2c block
        InputBlock kind;
        CHECK_RET(input.lex_program(output, block_name, kind));
        if (kind == InputBlock::END) break;

        // parse the next re2c block
        AstGrams grams;
        if (kind == InputBlock::USE) {
            const AstBlock* b = ast.blocks.find(block_name);
            if (b == nullptr) return Ret::FAIL;
            grams = b->grams;
            CHECK_RET(opts.restore(b->opts));
        }
        block_loc = input.tok_loc();
        CHECK_RET(parse(input, ast, opts, grams));

        // start new output block with accumulated options
        CHECK_RET(output.new_block(opts, kind, block_name, block_loc));
        OutputBlock& b = output.block();

        if (kind == InputBlock::RULES) {
            // Save AST and options for future use.
            ast.blocks.add(block_name, b.opts, grams);
        } else {
            // Convert AST to a DFA for each condition.
            CHECK_RET(check_and_merge_special_rules(grams, b.opts, output.msg, ast));
            for (const AstGram& gram : grams) {
                CHECK_RET(ast_to_dfa(gram, output, b.dfas, dfa_alc));
            }
            output.gen_stmt(code_dfas(output.allocator));
        }
        output.gen_stmt(code_line_info_input(output.allocator, input.cur_loc()));

        // Do not accumulate whole-program options for rules/reuse/local blocks. Global blocks add
        // their named definitions and configurations to the global scope, local blocks don't.
        // Historically global is the default.
        if (kind == InputBlock::GLOBAL) {
            accum_opts = b.opts;
        } else {
            CHECK_RET(opts.restore(accum_opts));
        }
    }

    output.total_opts = accum_opts ? accum_opts : ast.blocks.last_opts();

    // Early codegen phase that gathers whole-program information.
    for (const blocks_t& bs : {output.cblocks, output.hblocks}) {
        for (OutputBlock* b : bs) {
            output.set_current_block(b);
            gen_code_pass1(output);
        }
        fix_first_block_opts(bs);
    }
    gen_implicit_cond_enum(output);

    // Main codegen phase.
    for (const blocks_t& bs : {output.cblocks, output.hblocks}) {
        for (OutputBlock* b : bs) {
            output.set_current_block(b);
            CHECK_RET(gen_code_pass2(output));
        }
    }

    output.set_current_block(nullptr);

    output.gen_epilog();

    return Ret::OK;
}

} // namespace re2c
