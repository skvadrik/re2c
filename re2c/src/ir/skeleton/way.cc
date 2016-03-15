#include <stddef.h>
#include <algorithm>

#include "src/ir/skeleton/skeleton.h"
#include "src/ir/skeleton/way.h"

namespace re2c
{

static void fprint_way_arc (FILE * f, const way_arc_t & arc);

// define strict weak ordering on patterns:
// 1st criterion is length (short patterns go first)
// 2nd criterion is lexicographical order (applies to patterns of equal length)
bool cmp_ways (const way_t &w1, const way_t &w2)
{
	const size_t s1 = w1.size();
	const size_t s2 = w2.size();
	if (s1 == s2) {
		for (size_t i = 1; i < s1; ++i) {
			const way_arc_t
				&a1 = w1[i - 1]->arcsets[w1[i]],
				&a2 = w2[i - 1]->arcsets[w2[i]];
			const size_t l1 = a1.size();
			const size_t l2 = a2.size();
			for (size_t j = 0; j < l1; ++j) {
				if (j == l2 || a2[j] < a1[j]) {
					return false;
				} else if (a1[j] < a2[j]) {
					return true;
				}
			}
		}
		return false;
	} else {
		return s1 < s2;
	}
}

void fprint_way(FILE *f, const way_t &w)
{
	fprintf(f, "'");
	const size_t len = w.size();
	for (size_t i = 1; i < len; ++i) {
		if (i > 1) {
			fprintf(f, " ");
		}
		const way_arc_t &arc = w[i - 1]->arcsets[w[i]];
		fprint_way_arc(stderr, arc);
	}
	fprintf(f, "'");
}

void fprint_way_arc (FILE * f, const way_arc_t & arc)
{
	const size_t ranges = arc.size ();
	if (ranges == 1 && arc[0].first == arc[0].second)
	{
		fprintf (f, "\\x%X", arc[0].first);
	}
	else
	{
		fprintf (f, "[");
		for (size_t i = 0; i < ranges; ++i)
		{
			const uint32_t l = arc[i].first;
			const uint32_t u = arc[i].second;
			fprintf (f, "\\x%X", l);
			if (l != u)
			{
				fprintf (f, "-\\x%X", u);
			}
		}
		fprintf (f, "]");
	}
}

} // namespace re2c
