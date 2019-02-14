#include "lib/regex.h"
#include "src/nfa/nfa.h"
#include "src/dfa/dfa.h"


using namespace re2c;

void regfree(regex_t *preg)
{
    delete preg->rmgr;
    delete &preg->nfa->charset;
    delete &preg->nfa->rules;
    delete &preg->nfa->tags;
    delete preg->nfa;
    delete[] preg->pmatch;

    const int f = preg->flags;
    if (f & REG_NFA) {
        delete[] preg->done;
        if (!(f & REG_TRIE)) {
            delete[] preg->offsets1;
            delete[] preg->offsets2;
            delete[] preg->offsets3;
        }
        if (!(f & REG_LEFTMOST) && !(f & REG_TRIE)) {
            delete[] preg->prec_buf1;
            delete[] preg->prec_buf2;
        }
    }
    else {
        delete[] preg->regs;
        delete[] preg->char2class;
        delete &preg->dfa->mtagvers;
        delete[] preg->dfa->finvers;
        delete &preg->dfa->tcpool;
        delete preg->dfa;
    }
}
