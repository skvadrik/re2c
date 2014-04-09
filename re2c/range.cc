#include "print.h"
#include "range.h"

namespace re2c
{

std::ostream& operator<<(std::ostream &o, const Range &r)
{
	if ((r.ub - r.lb) == 1)
	{
		prtCh(o, r.lb);
	}
	else
	{
		prtCh(o, r.lb);
		o << "-";
		prtCh(o, r.ub - 1);
	}

	return o << r.next;
}

Range *doUnion(Range *r1, Range *r2)
{
	if (r1 == NULL)
		return r2;
	if (r2 == NULL)
		return r1;

	Range *r, **rP = &r;

	for (;;)
	{
		Range *s;

		if (r1->lb <= r2->lb)
		{
			s = new Range(*r1);
		}
		else
		{
			s = new Range(*r2);
		}

		*rP = s;
		rP = &s->next;

		for (;;)
		{
			if (r1->lb <= r2->lb)
			{
				if (r1->lb > s->ub)
					break;

				if (r1->ub > s->ub)
					s->ub = r1->ub;

				if (!(r1 = r1->next))
				{
					uint ub = 0;

					for (; r2 && r2->lb <= s->ub; r2 = r2->next)
						ub = r2->ub;

					if (ub > s->ub)
						s->ub = ub;

					*rP = r2;

					return r;
				}
			}
			else
			{
				if (r2->lb > s->ub)
					break;

				if (r2->ub > s->ub)
					s->ub = r2->ub;

				if (!(r2 = r2->next))
				{
					uint ub = 0;

					for (; r1 && r1->lb <= s->ub; r1 = r1->next)
						ub = r1->ub;

					if (ub > s->ub)
						s->ub = ub;

					*rP = r1;

					return r;
				}
			}
		}
	}

	*rP = NULL;
	return r;
}

Range *doDiff(Range *r1, Range *r2)
{
	Range *r, *s, **rP = &r;

	for (; r1; r1 = r1->next)
	{
		uint lb = r1->lb;

		for (; r2 && r2->ub <= r1->lb; r2 = r2->next)

			;
		for (; r2 && r2->lb < r1->ub; r2 = r2->next)
		{
			if (lb < r2->lb)
			{
				*rP = s = new Range(lb, r2->lb);
				rP = &s->next;
			}

			if ((lb = r2->ub) >= r1->ub)
				goto noMore;
		}

		*rP = s = new Range(lb, r1->ub);
		rP = &s->next;

noMore:
		;
	}

	*rP = NULL;
	return r;
}

} // end namespace re2c
