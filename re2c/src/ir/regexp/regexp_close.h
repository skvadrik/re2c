#ifndef _RE2C_IR_REGEXP_REGEXP_CLOSE_
#define _RE2C_IR_REGEXP_REGEXP_CLOSE_

#include "src/ir/regexp/regexp.h"

namespace re2c
{

class CloseOp: public RegExp
{
	RegExp * exp;

public:
	inline CloseOp (RegExp * e)
		: exp (e)
	{}
	void split (CharSet &);
	void calcSize (Char *);
	uint32_t compile (Char *, Ins *);
	void decompile ();
	void display (std::ostream & o) const;

	FORBID_COPY (CloseOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_CLOSE_
