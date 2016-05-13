#ifndef _RE2C_CODEGEN_EMIT_
#define _RE2C_CODEGEN_EMIT_

#include "src/codegen/output.h"
#include "src/ir/adfa/adfa.h"

namespace re2c {

void emit_action(OutputFile &o, uint32_t ind, bool &readCh,
	const DFA &dfa, const State *s, const std::set<label_t> &used_labels);
void gen_goto(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, size_t tags);
void gen_goto_case(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, size_t tags);
void gen_goto_if(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, size_t tags);
void gen_settags(OutputFile &o, uint32_t ind, const DFA &dfa, size_t tags);
std::string vartag_name(const std::string *name, size_t rule);
std::string vartag_expr(const std::string *name, size_t rule);
std::string subst_tags(const std::string &action,
	const std::valarray<Tag> &tags, size_t ltag, size_t htag);

} // namespace re2c

#endif // _RE2C_CODEGEN_EMIT_
