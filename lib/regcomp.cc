#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <valarray>
#include <vector>

#include "lib/lex.h"
#include "lib/regcomp_dfa_regless.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "lib/regoff_trie.h"
#include "src/dfa/dfa.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/range.h"

namespace re2c {

int lex(const char* pattern);
const AstNode* regexp;

} // namespace re2c

using namespace re2c;
using namespace re2c::libre2c;

// redefine CHECK_RET, as it needs to return `int` rather than `Ret`
#undef CHECK_RET
#define CHECK_RET(x) do { if (x != Ret::OK) return 1; } while(0)

int regcomp(regex_t* preg, const char* pattern, int cflags) {
    conopt_t globopts;
    globopts.nested_negative_tags = !(cflags & (REG_NFA | REG_REGLESS));
    globopts.FFlag = true;
    globopts.backward = cflags & REG_BACKWARD;
    Msg msg;
    Opt opts(globopts, msg);
    opts.set_subhistories((cflags & REG_SUBHIST) != 0);
    opts.set_autotags((cflags & REG_AUTOTAGS) != 0);
    opts.set_posix_syntax(true);
    opts.set_posix_semantics((cflags & REG_LEFTMOST) == 0);
    const opt_t* opt;
    CHECK_RET(opts.snapshot(opt));
    preg->flags = cflags;

    Ast ast;
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

    nfa_t* nfa = new nfa_t;
    CHECK_RET(re_to_nfa(*nfa, std::move(re)));

    nfa_t* nfa0 = nullptr;
    if (cflags & REG_BACKWARD) {
        conopt_t globopts0;
        globopts0.FFlag = true;
        Opt opts0(globopts0, msg);
        const opt_t* opt0;
        CHECK_RET(opts0.snapshot(opt0));
        RESpec re0(opt0, msg);
        CHECK_RET(re0.init(arv));
        nfa0 = new nfa_t;
        CHECK_RET(re_to_nfa(*nfa0, std::move(re0)));
        delete opt0;
    }

    DCHECK(nfa->rules.size() == 1);
    preg->re_nsub = nfa->rules[0].ncap + 1;
    preg->re_ntag = nfa->tags.size();

    if (cflags & REG_NFA) {
        preg->nfa = nfa;
        if ((cflags & REG_TRIE) && (cflags & REG_LEFTMOST)) {
            preg->simctx = new lzsimctx_t(*nfa, nfa0, preg->re_nsub, cflags);
        } else if (cflags & REG_TRIE) {
            preg->simctx = new pzsimctx_t(*nfa, nfa0, preg->re_nsub, cflags);
        } else if (cflags & REG_LEFTMOST) {
            preg->simctx = new lsimctx_t(*nfa, nfa0, preg->re_nsub, cflags);
        } else if (cflags & REG_KUKLEWICZ) {
            preg->simctx = new ksimctx_t(*nfa, nfa0, preg->re_nsub, cflags);
        } else {
            preg->simctx = new psimctx_t(*nfa, nfa0, preg->re_nsub, cflags);
        }
    } else if (cflags & REG_REGLESS) {
        preg->rldfa = new rldfa_t(std::move(*nfa), opt, cflags);
        delete nfa;
        opt = nullptr; // transfer options ownership to RLDFA

        if (cflags & REG_SUBHIST) {
            preg->regtrie = new regoff_trie_t(preg->rldfa->tags.size());
        }
    } else {
        dfa_t* dfa = new dfa_t(*new DfaAllocator(), nfa->charset.size(), Rule::NONE, Rule::NONE);
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
        // T-string is stored in RE (reallocated on each regtstring() call if needed), and the user
        // gets an immutable view of it (const ref).
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

