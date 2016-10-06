#ifndef _RE2C_CODEGEN_EMIT_
#define _RE2C_CODEGEN_EMIT_

#include "src/codegen/output.h"
#include "src/ir/adfa/adfa.h"

namespace re2c {

typedef std::vector<std::string> code_lines_t;

void emit_action(OutputFile &o, uint32_t ind, bool &readCh,
	const DFA &dfa, const State *s, const std::set<label_t> &used_labels);
void gen_goto_plain(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, const tagcmd_t &tags, bool restore_fallback);
void gen_goto_case(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, const tagcmd_t &tags, bool restore_fallback);
void gen_goto_if(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, const tagcmd_t &tags, bool restore_fallback);
void gen_settags(code_lines_t &code, const DFA &dfa, const tagcmd_t &tags, bool restore_fallback);
std::string vartag_name(const std::string *name, size_t rule);
std::string vartag_expr(const std::string *name, size_t rule);
std::string vartag_name_fallback(const Tag &tag);
std::string vartag_expr_fallback(const Tag &tag);

} // namespace re2c

#endif // _RE2C_CODEGEN_EMIT_
