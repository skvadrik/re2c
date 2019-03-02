#include "lib/regex.h"
#include "lib/regex_impl.h"
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

    if (preg->flags & REG_NFA) {
        if ((preg->flags & REG_TRIE) && (preg->flags & REG_LEFTMOST)) {
            delete static_cast<libre2c::lzctx_t*>(preg->simctx);
        }
        else if (preg->flags & REG_TRIE) {
            delete static_cast<libre2c::pzctx_t*>(preg->simctx);
        }
        else if (preg->flags & REG_LEFTMOST) {
            delete static_cast<libre2c::lctx_t*>(preg->simctx);
        }
        else {
            delete static_cast<libre2c::pctx_t*>(preg->simctx);
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
