#include "libre2c_posix/lex.h"
#include "libre2c_posix/regex.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/nfa/nfa.h"
#include "src/dfa/dfa.h"


namespace re2c {

int lex(const char *pattern);
const AST *regexp;

} // namespace re2c

using namespace re2c;

int regcomp(regex_t *preg, const char *pattern, int /* cflags */)
{
    conopt_t globopts;
    globopts.FFlag = true;
    Opt opts(globopts);
    opts.set_posix_captures(true);
    const opt_t *opt = opts.snapshot();

    Warn warn;

    const AST *a = parse(pattern);

    RangeMgr rangemgr;

    ASTRule ar(a, new Code ("", 0));
    std::vector<ASTRule> arv;
    arv.push_back(ar);
    RESpec re(arv, opt, warn, rangemgr);

    split_charset(re);
    for (uint32_t i = 1, j = 0; i < re.charset.size(); ++i) {
        for (; j < re.charset[i]; ++j) {
            preg->char2class[j] = i - 1;
        }
    }

    find_fixed_tags(re);

    insert_default_tags(re);

    nfa_t *nfa = new nfa_t(re);

    dfa_t *dfa = new dfa_t(*nfa, opt, "", warn);

    preg->nfa = nfa;
    preg->dfa = dfa;

    return 0;
}
