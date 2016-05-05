#include <limits>
#include <sstream>

#include "src/conf/opt.h"
#include "src/ir/ctx.h"
#include "src/util/strrreplace.h"
#include "src/globals.h"

namespace re2c
{

CtxVar::CtxVar(const std::string *n, size_t r)
	: rule(r)
	, codename(n)
	, uniqname()
{
	std::ostringstream s;
	s << rule;
	if (codename != NULL) {
		s << *codename;
	}
	uniqname = s.str();
}

std::string CtxVar::name() const
{
	return opts->contexts_prefix + uniqname;
}

std::string CtxVar::expr() const
{
	std::string e = opts->contexts_expr;
	strrreplace(e, "@@", opts->contexts_prefix + uniqname);
	return e;
}

const size_t CtxFix::RIGHTMOST = std::numeric_limits<size_t>::max();

} // namespace re2c
