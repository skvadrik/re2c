#include <stddef.h>
#include <set>
#include <valarray>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/encoding/range_suffix.h"
#include "src/nfa/nfa.h"
#include "src/parse/ast.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/free_list.h"
#include "src/util/range.h"


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
            delete static_cast<libre2c::lzsimctx_t*>(preg->simctx);
        }
        else if (preg->flags & REG_TRIE) {
            delete static_cast<libre2c::pzsimctx_t*>(preg->simctx);
        }
        else if (preg->flags & REG_LEFTMOST) {
            delete static_cast<libre2c::lsimctx_t*>(preg->simctx);
        }
        else if (preg->flags & REG_KUKLEWICZ) {
            delete static_cast<libre2c::ksimctx_t*>(preg->simctx);
        }
        else {
            delete static_cast<libre2c::psimctx_t*>(preg->simctx);
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

    AST::flist.clear();
    RangeSuffix::freeList.clear();
}
