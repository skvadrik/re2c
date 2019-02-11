#include "lib/lex.h"
#include "lib/regex.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/nfa/nfa.h"
#include "src/dfa/dfa.h"


namespace re2c {

int lex(const char *pattern);
const AST *regexp;

} // namespace re2c

using namespace re2c;

int regcomp(regex_t *preg, const char *pattern, int cflags)
{
    conopt_t globopts;
    globopts.FFlag = true;
    Opt opts(globopts);
    opts.set_posix_syntax(true);
    opts.set_posix_semantics((cflags & REG_LEFTMOST) == 0);
    const opt_t *opt = opts.snapshot();
    const std::string fname = "void";

    Warn warn;

    preg->flags = cflags;

    const AST *a = parse(pattern);

    preg->rmgr = new RangeMgr;

    ASTRule ar(a, new Code ("", 0));
    std::vector<ASTRule> arv;
    arv.push_back(ar);
    RESpec re(fname, arv, opt, warn, *preg->rmgr);

    find_fixed_tags(re);

    insert_default_tags(re);

    nfa_t *nfa = new nfa_t(re);

    DASSERT(nfa->rules.size() == 1);
    preg->re_nsub = nfa->rules[0].ncap + 1;
    preg->pmatch = new regmatch_t[preg->re_nsub];

    dfa_t *dfa = NULL;
    if (cflags & REG_NFA) {
        const size_t sz = 2 * nfa->size * nfa->size;
        preg->prec_buf1 = new int32_t[sz];
        preg->prec_buf2 = new int32_t[sz];
    }
    else {
        preg->char2class = new size_t[256];
        split_charset(re);
        for (uint32_t i = 1, j = 0; i < re.charset.size(); ++i) {
            for (; j < re.charset[i]; ++j) {
                preg->char2class[j] = i - 1;
            }
        }

        dfa = new dfa_t(*nfa, opt, "", warn, fname);

        compact_and_optimize_tags(opt, *dfa);

        preg->regs = new regoff_t[dfa->maxtagver + 1];
    }

    preg->nfa = nfa;
    preg->dfa = dfa;

    delete opt;
    return 0;
}
