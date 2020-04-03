#ifndef _RE2C_CODE_EMIT_
#define _RE2C_CODE_EMIT_

#include "src/codegen/output.h"
#include "src/adfa/adfa.h"


namespace re2c {

typedef std::vector<std::string> code_lines_t;

void emit_action(Output &o, uint32_t ind, const DFA &dfa, const State *s, const std::set<label_t> &used_labels);
void gen_goto_plain(Output &o, uint32_t ind, const State *from, const State *to, const DFA &dfa, tcid_t tcid, bool skip, bool eof);
void gen_goto_case(Output &o, uint32_t ind, const State *from, const State *to, const DFA &dfa, tcid_t tcid, bool skip, bool eof);
void gen_goto_if(Output &o, uint32_t ind, const State *from, const State *to, const DFA &dfa, tcid_t tcid, bool skip, bool eof);
void gen_settags(code_lines_t &code, const DFA &dfa, tcid_t tcid, const opt_t *opts, bool delayed);
std::string vartag_name(tagver_t ver, const std::string &prefix);
std::string vartag_expr(tagver_t ver, const std::string &prefix, const std::string &expression);
std::string tag_expr(const Tag &tag, bool lvalue);
bool endstate(const State *s);

inline std::string indent(uint32_t n, const std::string &s)
{
    std::string ind;
    for (; n --> 0; ind += s);
    return ind;
}

} // namespace re2c

#endif // _RE2C_CODE_EMIT_
