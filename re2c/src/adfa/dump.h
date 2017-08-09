#ifndef _RE2C_ADFA_DUMP_
#define _RE2C_ADFA_DUMP_

#include "src/adfa/adfa.h"

namespace re2c
{

struct DFA;

void dump_adfa(const DFA &dfa);

} // namespace re2c

#endif // _RE2C_ADFA_DUMP_
