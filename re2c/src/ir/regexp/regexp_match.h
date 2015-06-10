#ifndef _RE2C_IR_REGEXP_REGEXP_MATCH_
#define _RE2C_IR_REGEXP_REGEXP_MATCH_

#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c
{

class MatchOp: public RegExp
{
public:
	Range * match;

	inline MatchOp (Range * m)
		: match (m)
	{}
	void split (CharSet &);
	void calcSize (Char *);
	uint32_t fixedLength ();
	uint32_t compile (Char *, Ins *);
	void decompile ();
	void display (std::ostream & o) const;

	FORBID_COPY (MatchOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_MATCH_
