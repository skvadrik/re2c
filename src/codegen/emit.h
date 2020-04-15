#ifndef _RE2C_CODE_EMIT_
#define _RE2C_CODE_EMIT_

#include <vector>

#include "src/codegen/output.h"
#include "src/adfa/adfa.h"
#include "src/util/smart_ptr.h"


namespace re2c {

typedef std::vector<smart_ptr<DFA> > dfas_t;

void gen_code(Output &output, dfas_t &dfas);

void emit_action(Output &output, const DFA &dfa, const State *s, CodeStmts *stmts);

void gen_settags(Output &output, CodeStmts *tag_actions, const DFA &dfa, tcid_t tcid,
    bool delayed);

void gen_goto(Output &output, CodeStmts *stmts, const State *from, const State *to,
    const DFA &dfa, tcid_t tcid, bool skip, bool eof);

std::string vartag_name(tagver_t ver, const std::string &prefix);

std::string vartag_expr(tagver_t ver, const std::string &prefix,
    const std::string &expression);

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
