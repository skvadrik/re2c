#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <valarray>
#include <vector>

#include "lib/lex.h"
#include "lib/regcomp_dfa_multipass.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "lib/regoff_trie.h"
#include "src/dfa/dfa.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/regexp.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/range.h"

namespace re2c {

int lex(RE2C_LIB_STYPE* yylval, const char* pattern);
const AstNode* regexp;

} // namespace re2c

using namespace re2c;
using namespace re2c::libre2c;

// redefine CHECK_RET, as it needs to return `int` rather than `Ret`
#undef CHECK_RET
#define CHECK_RET(x) do { if (x != Ret::OK) return 1; } while(0)

int regcomp(regex_t* preg, const char* pattern, int cflags) {
    AstAllocator ast_alc;
    OutAllocator out_alc;

    Msg msg;
    Opt opts(out_alc, msg);

    conopt_t& globopts = const_cast<conopt_t&>(opts.global());
    globopts.set_target(re2c::Target::CODE);
    globopts.set_flex_syntax(true);
    globopts.set_nested_negative_tags(!(cflags & (REG_NFA | REG_MULTIPASS)));

    opts.set_supported_api_styles({"functions"});
    opts.set_supported_code_models({"goto-label"});
    opts.init_tags_history((cflags & REG_SUBHIST) != 0);
    opts.init_tags_automatic((cflags & REG_AUTOTAGS) != 0);
    opts.init_captures(true);
    opts.init_captures_posix((cflags & REG_LEFTMOST) == 0);
    opts.init_captures_array(true);

    CHECK_RET(opts.fix_global_and_defaults());

    const opt_t* opt;
    CHECK_RET(opts.snapshot(&opt));

    preg->flags = cflags;

    Ast ast(ast_alc, out_alc);
    const AstNode* a = parse(pattern, ast);

    std::vector<AstRule> arv{AstRule{a, ast.sem_act(NOWHERE, nullptr, nullptr, false)}};
    RESpec re(opt, msg);
    CHECK_RET(re.init(arv));

    find_fixed_tags(re);
    insert_default_tags(re);

    if ((cflags & REG_NFA) == 0) {
        preg->char2class = new size_t[256];
        split_charset(re);
        for (uint32_t i = 1, j = 0; i < re.charset.size(); ++i) {
            for (; j < re.charset[i]; ++j) {
                preg->char2class[j] = i - 1;
            }
        }
    }

    Tnfa* nfa = new Tnfa;
    CHECK_RET(re_to_nfa(*nfa, std::move(re)));

    DCHECK(nfa->rules.size() == 1);
    preg->re_nsub = nfa->rules[0].ncap + 1;
    preg->re_ntag = nfa->tags.size();

    if (cflags & REG_NFA) {
        preg->nfa = nfa;
        if ((cflags & REG_TRIE) && (cflags & REG_LEFTMOST)) {
            preg->simctx = new lzsimctx_t(*nfa, preg->re_nsub, cflags);
        } else if (cflags & REG_TRIE) {
            preg->simctx = new pzsimctx_t(*nfa, preg->re_nsub, cflags);
        } else if (cflags & REG_LEFTMOST) {
            preg->simctx = new lsimctx_t(*nfa, preg->re_nsub, cflags);
        } else {
            preg->simctx = new psimctx_t(*nfa, preg->re_nsub, cflags);
        }
    } else if (cflags & REG_MULTIPASS) {
        preg->mptdfa = new MpTdfa(std::move(*nfa), opt, cflags);
        delete nfa;
        opt = nullptr; // transfer options ownership to RLDFA

        if (cflags & REG_SUBHIST) {
            preg->regtrie = new regoff_trie_t(preg->mptdfa->tags.size());
        }
    } else {
        Tdfa* dfa = new Tdfa(*new DfaAllocator(), nfa->charset.size(), Rule::NONE, Rule::NONE);
        CHECK_RET(determinization(std::move(*nfa), *dfa, opt, msg, ""));
        preg->dfa = dfa;
        delete nfa;

        cutoff_dead_rules(*dfa, opt, "", msg);
        insert_fallback_tags(*dfa);
        compact_and_optimize_tags(opt, *dfa);

        if (cflags & REG_TSTRING) {
            // T-string does not need intermediate storage for tag values.
        } else if (cflags & REG_SUBHIST) {
            preg->regtrie = new regoff_trie_t(static_cast<size_t>(dfa->maxtagver + 1));
        } else {
            preg->regs = new regoff_t[dfa->maxtagver + 1];
        }
    }

    if (cflags & REG_TSTRING) {
        // T-string is stored in the regexp (reallocated on each regtstring() call if needed), and
        // the user gets an immutable view of it (const ref).
        tstring_t& ts = preg->tstring;
        ts.capacity = 256;
        ts.string = new tchar_t[ts.capacity];
        ts.length = 0;
    } else if (cflags & REG_SUBHIST) {
        // Allocated on every call to regparse() and returned to the user.
    } else {
        // Allocated by the user.
    }

    delete opt;
    return 0;
}

#undef CHECK_RET

