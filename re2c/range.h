#ifndef _range_h
#define _range_h

#include <iostream>

#include "basics.h"
#include "free_list.h"

namespace re2c
{

class Range
{

public:
	Range	*next;
	uint	lb, ub;		// [lb,ub)

	static free_list<Range*> vFreeList;

public:
	Range(uint l, uint u) : next(NULL), lb(l), ub(u)
	{
		vFreeList.insert(this);
	}

	Range(Range &r) : next(NULL), lb(r.lb), ub(r.ub)
	{
		vFreeList.insert(this);
	}

	~Range()
	{
		vFreeList.erase(this);
	}

	friend std::ostream& operator<<(std::ostream&, const Range&);
	friend std::ostream& operator<<(std::ostream&, const Range*);
};

inline std::ostream& operator<<(std::ostream &o, const Range *r)
{
	return r ? o << *r : o;
}

Range *doUnion(Range *r1, Range *r2);
Range *doDiff(Range *r1, Range *r2);

} // end namespace re2c

#endif
