#ifndef _RE2C_IR_REGEXP_REGEXP_CLOSEV_
#define _RE2C_IR_REGEXP_REGEXP_CLOSEV_

#include "src/ir/regexp/regexp.h"

namespace re2c
{

class CloseVOp: public RegExp
{
	RegExp * exp;
	int32_t min;
	int32_t max;

public:
	inline CloseVOp (RegExp * e, int lb, int ub)
		: exp (e)
		, min (lb)
		, max (ub)
	{
		exp->ins_access = PRIVATE;
	}
	void split (CharSet &);
	void calcSize (Char *);
	uint32_t compile (Char *, Ins *);
	void decompile ();
	void display (std::ostream & o) const;

	FORBID_COPY (CloseVOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_CLOSEV_
