#ifndef __PARSER__
#define __PARSER__

#include <string>

#include "src/codegen/output.h"
#include "src/dfa/re.h"
#include "src/parse/scanner.h"

namespace re2c
{

extern void parse(Scanner &, Output &);
extern void parse_cleanup();

typedef std::set<std::string> CondList;
typedef std::list<RuleOp*> RuleOpList;
typedef std::map<std::string, std::pair<uint32_t, std::string> > SetupMap;
typedef std::map<std::string, Token*> DefaultMap;
typedef std::map<std::string, RegExp *> symbol_table_t;

} // namespace re2c

#endif // __PARSER__
