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
	, fix()
{}

void init_var_tag(Tag &tag, size_t r, const std::string *n)
{
	tag.type = Tag::VAR;
	tag.rule = r;
	tag.name = n;
}

void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d)
{
	tag.type = Tag::FIX;
	tag.rule = r;
	tag.name = n;
	tag.fix.base = b;
	tag.fix.dist = d;
}

free_list<tagsave_t*> tagsave_t::freelist;

tagsave_t::tagsave_t(tagsave_t *n, tagver_t v)
	: next(n)
	, ver(v)
{
	freelist.insert(this);
}

tagsave_t::~tagsave_t()
{
	freelist.erase(this);
}

tagsave_t *tagsave_t::convert(const tagver_t *vers, size_t ntag)
{
	tagsave_t *s = NULL;
	for (size_t t = ntag; t-- > 0;) {
		const tagver_t v = vers[t];
		if (v != TAGVER_ZERO) {
			s = new tagsave_t(s, v);
		}
	}
	return s;
}

free_list<tagcopy_t*> tagcopy_t::freelist;

tagcopy_t::tagcopy_t(tagcopy_t *n, tagver_t l, tagver_t r)
	: next(n)
	, lhs(l)
	, rhs(r)
{
	freelist.insert(this);
}

tagcopy_t::~tagcopy_t()
{
	freelist.erase(this);
}

} // namespace re2c
