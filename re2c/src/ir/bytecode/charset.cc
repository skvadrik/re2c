#include "src/ir/bytecode/charset.h"
#include "src/globals.h"
#include "src/util/allocate.h"

namespace re2c {

CharSet::CharSet ()
	: fix (0)
	, freeHead (0)
	, freeTail (0)
	, rep (allocate<CharPtr> (encoding.nCodeUnits ()))
	, ptn (allocate<CharPtn> (encoding.nCodeUnits ()))
{
	for (uint32_t j = 0; j < encoding.nCodeUnits (); ++j)
	{
		rep[j] = &ptn[0];
		ptn[j].nxt = &ptn[j + 1]; /* wrong for j=encoding.nCodeUnits() - 1 but will be corrected below */
		ptn[j].card = 0;
	}
	freeHead = &ptn[1];
	* (freeTail = &ptn[encoding.nCodeUnits() - 1].nxt) = NULL;
	ptn[0].card = encoding.nCodeUnits ();
	ptn[0].nxt = NULL;
}

CharSet::~CharSet ()
{
	operator delete (rep);
	operator delete (ptn);
}

} // namespace re2c
