#ifndef _RE2C_CODEGEN_EMIT_
#define _RE2C_CODEGEN_EMIT_

#include "src/codegen/output.h"
#include "src/ir/adfa/adfa.h"

namespace re2c {

void emit_action(OutputFile &o, uint32_t ind, bool &readCh,
	const DFA &dfa, const State *s, const std::set<label_t> &used_labels);
void gen_goto(OutputFile &o, uint32_t ind, bool &readCh, const State *to);
void gen_goto_case(OutputFile &o, uint32_t ind, bool &readCh, const State *to);
void gen_goto_if(OutputFile &o, uint32_t ind, bool &readCh, const State *to);

} // namespace re2c

#endif // _RE2C_CODEGEN_EMIT_
