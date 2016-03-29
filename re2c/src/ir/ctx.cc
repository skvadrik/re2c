#include <limits>
#include <sstream>

#include "src/conf/opt.h"
#include "src/ir/ctx.h"
#include "src/globals.h"

namespace re2c
{

CtxVar::CtxVar(const std::string *n, size_t idx)
	: name(n)
	, fullname()
{
	std::ostringstream s;
	s << opts->ctxprefix << idx;
	if (name != NULL) {
		s << *name;
	}
	fullname = s.str();
}

const size_t CtxFix::RIGHTMOST = std::numeric_limits<size_t>::max();

} // namespace re2c
