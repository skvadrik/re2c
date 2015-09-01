#ifndef _RE2C_CODEGEN_SKELETON_MULTIPATH_
#define _RE2C_CODEGEN_SKELETON_MULTIPATH_

#include <stdio.h>
#include <vector>

#include "src/util/c99_stdint.h"

namespace re2c
{

class multipath_t
{
public:
	typedef std::vector<std::pair<uint32_t, uint32_t> > arc_t;

private:
	std::vector<const arc_t *> arcs;

public:
	multipath_t ();
	size_t len () const;
	void extend (const arc_t * arc);
	void fprint (FILE * f) const;
	static bool compare (const multipath_t & x, const multipath_t & y);

private:
	static void fprint_arc (FILE * f, const arc_t & arc);
};

} // namespace re2c

#endif // _RE2C_CODEGEN_SKELETON_MULTIPATH_
