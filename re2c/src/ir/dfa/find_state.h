#ifndef _RE2C_IR_DFA_FIND_STATE_
#define _RE2C_IR_DFA_FIND_STATE_

#include "src/ir/dfa/closure.h"
#include "src/ir/tagpool.h"
#include "src/util/ord_hash_set.h"

namespace re2c
{

size_t find_state(kitem_t *kernel, kitem_t *kend, ord_hash_set_t &kernels, Tagpool &tagpool);

} // namespace re2c

#endif // _RE2C_IR_DFA_FIND_STATE_
