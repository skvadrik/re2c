#ifndef __EMIT__
#define __EMIT__

#include "src/codegen/output.h"
#include "src/dfa/dfa.h"

namespace re2c {

class DFA;
typedef std::vector<std::string> RegExpIndices;

void emit_action
	( const Action & action
	, OutputFile & o
	, uint32_t ind
	, bool & readCh
	, const State * const s
	, const std::string & condName
	, const std::set<uint32_t> & used_labels
	);

// helpers
void genGoTo (OutputFile & o, uint32_t ind, const State * from, const State * to, bool & readCh);
void genTypes (Output &, const RegExpMap &);

template<typename _Ty> std::string replaceParam (std::string str, const std::string & param, const _Ty & value)
{
	std::ostringstream strValue;
	strValue << value;
	std::string::size_type pos;
	while((pos = str.find(param)) != std::string::npos)
	{
		str.replace(pos, param.length(), strValue.str());
	}
	return str;
}

} // namespace re2c

#endif // __EMIT__
