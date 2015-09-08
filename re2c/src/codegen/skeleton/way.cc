#include "src/codegen/skeleton/way.h"

namespace re2c
{

static void fprint_way_arc (FILE * f, const way_arc_t & arc);

bool cmp_ways (const way_t & w1, const way_t & w2)
{
	return w1.size () < w2.size ();
}

void fprint_way (FILE * f, const way_t & w)
{
	fprintf (f, "'");
	const size_t len = w.size ();
	for (size_t i = 0 ; i < len; ++i)
	{
		if (i > 0)
		{
			fprintf (f, " ");
		}
		if (w[i] == NULL)
		{
			fprintf (stderr, "(nil)");
		}
		else
		{
			fprint_way_arc (stderr, *w[i]);
		}
	}
	fprintf (f, "'");
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
