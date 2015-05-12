#ifndef __DFA_EMIT__
#define __DFA_EMIT__

#include "src/codegen/output.h"
#include "src/dfa/dfa.h"

namespace re2c {

class DFA;

typedef std::vector<std::string> RegExpIndices;

void genCondTable (OutputFile &, uint32_t, const RegExpMap &);
void genCondGoto (OutputFile &, uint32_t, const RegExpMap &);
void genTypes (Output &, const RegExpMap &);

// helpers
void genYYFill (OutputFile & o, uint32_t, uint32_t need);
std::string genGetCondition ();
void genSetCondition (OutputFile & o, uint32_t ind, const std::string & newcond);
void genGoTo (OutputFile & o, uint32_t ind, const State * from, const State * to, bool & readCh);
void need (OutputFile & o, uint32_t ind, uint32_t n, bool & readCh, bool bSetMarker);
void genCondGotoSub (OutputFile & o, uint32_t ind, RegExpIndices & vCondList, uint32_t cMin, uint32_t cMax);

template<typename _Ty>
std::string replaceParam (std::string str, const std::string & param, const _Ty & value)
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

#endif // __DFA_EMIT__
