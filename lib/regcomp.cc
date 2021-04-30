#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <valarray>
#include <vector>

#include "lib/lex.h"
#include "lib/regcomp_dfa_regless.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/util/range.h"


namespace re2c {

int lex(const char *pattern);
const AST *regexp;

} // namespace re2c

using namespace re2c;
using namespace re2c::libre2c;

int regcomp(regex_t *preg, const char *pattern, int cflags)
{
    conopt_t globopts;
    globopts.nested_negative_tags = !(cflags & (REG_NFA | REG_REGLESS));
    globopts.FFlag = true;
    globopts.backward = cflags & REG_BACKWARD;
    globopts.stadfa = cflags & REG_STADFA;
    Opt opts(globopts);
    Msg msg;
    opts.set_posix_syntax(true);
    opts.set_posix_semantics((cflags & REG_LEFTMOST) == 0);
    const opt_t *opt = opts.snapshot();
    preg->flags = cflags;

    const AST *a = parse(pattern);

    preg->rmgr = new RangeMgr;

    ASTRule ar(a, new SemAct(NOWHERE));
    std::vector<ASTRule> arv;
    arv.push_back(ar);
    RESpec re(arv, opt, msg, *preg->rmgr);

    find_fixed_tags(re);

    insert_default_tags(re);

    nfa_t *nfa = new nfa_t(re);

    nfa_t *nfa0 = NULL;
    if (cflags & REG_BACKWARD) {
        conopt_t globopts0;
        globopts0.FFlag = true;
        Opt opts0(globopts0);
        const opt_t *opt0 = opts0.snapshot();
        RESpec re0(arv, opt0, msg, *preg->rmgr);
        nfa0 = new nfa_t(re0);
        delete opt0;
    }

    DASSERT(nfa->rules.size() == 1);
    preg->re_nsub = nfa->rules[0].ncap + 1;
    preg->pmatch = new regmatch_t[preg->re_nsub];

    dfa_t *dfa = NULL;
    rldfa_t *rldfa = NULL;

    if (cflags & REG_NFA) {
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
    } else {
        preg->char2class = new size_t[256];
        split_charset(re);
        for (uint32_t i = 1, j = 0; i < re.charset.size(); ++i) {
            for (; j < re.charset[i]; ++j) {
                preg->char2class[j] = i - 1;
            }
        }

        dfa = new dfa_t(*nfa, Rule::NONE, Rule::NONE);
        if (cflags & REG_REGLESS) {
            DASSERT((cflags & REG_STADFA) == 0);
            rldfa = new rldfa_t(*nfa, *dfa, opt);
            opt = NULL; // transfer options ownership to RLDFA
        } else {
            determinization(*nfa, *dfa, opt, msg, "");
            cutoff_dead_rules(*dfa, opt, "", msg);
            insert_fallback_tags(opt, *dfa);
            compact_and_optimize_tags(opt, *dfa);
        }

        preg->regs = new regoff_t[dfa->maxtagver + 1];
    }

    preg->nfa = nfa;
    preg->dfa = dfa;
    preg->rldfa = rldfa;

    delete opt;
    return 0;
}
