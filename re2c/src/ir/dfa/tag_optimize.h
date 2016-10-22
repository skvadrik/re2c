#ifndef _RE2C_IR_DFA_TAG_OPTIMIZE_
#define _RE2C_IR_DFA_TAG_OPTIMIZE_

#include "src/ir/dfa/dfa.h"

namespace re2c {

void tag_liveness(const dfa_t &dfa, bool *live);
void tag_dce(dfa_t &dfa, const bool *live);
void tag_interference(const dfa_t &dfa, const bool *live, bool *interf);
tagver_t tag_allocation(const dfa_t &dfa, const bool *interf, tagver_t *ver2new);
void tag_renaming(dfa_t &dfa, const tagver_t *ver2new, tagver_t maxver);
void unpack(size_t nver, bool *vers, size_t ntag, const tagver_t *tags);

} // namespace re2c

#endif // _RE2C_IR_DFA_TAG_OPTIMIZE_
