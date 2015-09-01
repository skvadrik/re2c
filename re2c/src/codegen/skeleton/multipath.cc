#include "src/codegen/skeleton/multipath.h"

namespace re2c
{

multipath_t::multipath_t ()
	: arcs ()
{}

size_t multipath_t::len () const
{
	return arcs.size ();
}

void multipath_t::extend (const arc_t * arc)
{
	arcs.push_back (arc);
}

void multipath_t::fprint_arc (FILE * f, const arc_t & arc)
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

void multipath_t::fprint (FILE * f) const
{
	fprintf (f, "'");
	const size_t len = arcs.size ();
	for (size_t i = 0 ; i < len; ++i)
	{
		if (i > 0)
		{
			fprintf (f, " ");
		}
		if (arcs[i] == NULL)
		{
			fprintf (stderr, "(nil)");
		}
		else
		{
			fprint_arc (stderr, *arcs[i]);
		}
	}
	fprintf (f, "'");
}

bool multipath_t::compare (const multipath_t & x, const multipath_t & y)
{
	return x.arcs.size () < y.arcs.size ();
}

} // namespace re2c
