#include "libre2c_posix/regex.h"
#include "libre2c_posix/regex-impl.h"
#include "src/nfa/nfa.h"
#include "src/dfa/dfa.h"


using namespace re2c;

void regfree(regex_t *preg)
{
    delete preg->rmgr;
    delete preg->nfa;
    delete[] preg->pmatch;
    delete[] preg->regs;
    delete[] preg->char2class;

    const dfa_t *dfa = preg->dfa;
    delete &dfa->charset;
    delete &dfa->rules;
    delete &dfa->tags;
    delete &dfa->mtagvers;
    delete[] dfa->finvers;
    delete &dfa->tcpool;
    delete dfa;
}
