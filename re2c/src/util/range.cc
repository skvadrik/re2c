#include "src/util/range.h"

namespace re2c
{

Range * range_union (Range * r1, Range * r2)
{
	Range * r = NULL;
	Range ** p = &r;
	for (;;)
	{
		if (!r1)
		{
			* p = r2;
			break;
		}
		if (!r2)
		{
			* p = r1;
			break;
		}
		if (r2->lb < r1->lb) // swap
		{
			Range * r1_old = r1;
			r1 = r2;
			r2 = r1_old;
		}
		uint32_t ub = r1->ub;
		if (r2->lb < r1->ub)
		{
			for (; r2 && r2->lb < r1->ub; r2 = r2->next)
			{
				if (r1->ub < r2->ub)
				{
					ub = r2->ub;
				}
			}
		}
		* p = new Range (r1->lb, ub);
		p = &(* p)->next;
		r1 = r1->next;
	}
	return r;
}

Range * range_diff (Range * r1, Range * r2)
{
	Range * r = NULL;
	Range ** p = &r;
	for (; r1; r1 = r1->next)
	{
		for (; r2 && r2->ub <= r1->lb; r2 = r2->next);
		uint32_t lb = r1->lb;
		for (; r2 && r2->lb < r1->ub; r2 = r2->next)
		{
			if (lb < r2->lb)
			{
				* p = new Range(lb, r2->lb);
				p = &(* p)->next;
			}
			lb = r2->ub;
		}
		if (lb < r1->ub)
		{
			* p = new Range(lb, r1->ub);
			p = &(* p)->next;
		}
	}
	return r;
}

} // end namespace re2c
