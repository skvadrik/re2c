#include "src/ir/bytecode/charset.h"
#include "src/util/allocate.h"

namespace re2c {

CharSet::CharSet (uint32_t cunits)
	: fix (0)
	, freeHead (0)
	, freeTail (0)
	, rep (allocate<CharPtr> (cunits))
	, ptn (allocate<CharPtn> (cunits))
{
	for (uint32_t j = 0; j < cunits; ++j)
	{
		rep[j] = &ptn[0];
		ptn[j].nxt = &ptn[j + 1]; /* wrong for j=encoding.nCodeUnits() - 1 but will be corrected below */
		ptn[j].card = 0;
	}
	freeHead = &ptn[1];
	* (freeTail = &ptn[cunits - 1].nxt) = NULL;
	ptn[0].card = cunits;
	ptn[0].nxt = NULL;
}

CharSet::~CharSet ()
{
	operator delete (rep);
	operator delete (ptn);
}

} // namespace re2c
