#include <limits>

#include "src/ir/rule.h"
#include "src/ir/tag.h"

namespace re2c
{

const size_t Tag::NONE = std::numeric_limits<size_t>::max();

Tag::Tag()
	: type(VAR)
	, rule(Rule::NONE)
	, name(NULL)
{}

Tag::~Tag()
{
	delete name;
}

void init_var_tag(Tag &tag, size_t r, const std::string *n, size_t o)
{
	tag.type = Tag::VAR;
	tag.rule = r;
	tag.name = n;
	tag.var.orig = o;
}

void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d)
{
	tag.type = Tag::FIX;
	tag.rule = r;
	tag.name = n;
	tag.fix.base = b;
	tag.fix.dist = d;
}

} // namespace re2c
