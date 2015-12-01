#ifndef _RE2C_IR_REGEXP_REGEXP_
#define _RE2C_IR_REGEXP_REGEXP_

#include "src/util/c99_stdint.h"
#include <iosfwd>

#include "src/util/free_list.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct CharSet;
union Ins;

typedef uint32_t Char;

class RegExp
{
public:
	static free_list <RegExp *> vFreeList;

	uint32_t size;
	/*
	 * There're several different cases when the same regexp
	 * can be used multiple times:
	 * 	1) named definitions, e.g. digit = [0-9];
	 * 	2) counted repetition, e.g. "a"{3}, "a"{3,}, "a"{3,5}
	 * 	3) multiple DFA's sharing the same regexp , e.g. <c1, c2> "abc" { }
	 * 	4) common suffixes, e.g. suffix [\x80-\xBF] in UTF-8 ranges
	 * In cases 1-3, regexp must be recompiled each time it's reused.
	 * In case 4, regexp should be compiled only once, and instructions
	 * should be shared in order to reduce space.
	 *
	 * Note: if regexp must always be recompiled, it doesn't imply that
	 * parts of this regexp must always be recompiled. It only forces
	 * the compilation function to traverse the regexp after compilation
	 * and reset compilation cache for each sub-regexp. E.g., for a regexp
	 * [^]{3} in UTF-8 mode, each of sub-regexps [^] will have common suffix
	 * [\x80-\xBF] factored out, but they won't share instructions.
	 */
	Ins * ins_cache; /* if non-NULL, points to compiled instructions */
	enum InsAccess
	{
		SHARED,
		PRIVATE
	} ins_access;

	inline RegExp ()
		: size (0)
		, ins_cache (NULL)
		, ins_access (SHARED)
	{
		vFreeList.insert (this);
	}
	inline virtual ~RegExp ()
	{
		vFreeList.erase (this);
	}
	virtual void split (CharSet &) = 0;
	virtual void calcSize (Char *) = 0;
	virtual uint32_t fixedLength ();
	virtual uint32_t compile (Char *, Ins *) = 0;
	virtual void decompile () = 0;
	virtual void display (std::ostream &) const = 0;
	friend std::ostream & operator << (std::ostream & o, const RegExp & re);

	FORBID_COPY (RegExp);
};

RegExp * doAlt (RegExp * e1, RegExp * e2);
RegExp * mkAlt (RegExp * e1, RegExp * e2);
RegExp * doCat (RegExp * e1, RegExp * e2);
RegExp * repeat (RegExp * e, uint32_t n);
RegExp * repeat_from_to (RegExp * e, uint32_t n, uint32_t m);
RegExp * repeat_from (RegExp * e, uint32_t n);

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_
