#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <string>

#include "src/util/lookup.h"
#include "src/util/forbid_copy.h"
#include "src/util/free_list.h"

namespace re2c
{

typedef int32_t tagver_t;

static const tagver_t TAGVER_ZERO = 0; // absense of tag

struct Tag
{
	static const size_t NONE;

	enum {VAR, FIX} type;
	size_t rule;
	const std::string *name;
	struct
	{
		size_t base;
		size_t dist;
	} fix;

	Tag();
	FORBID_COPY(Tag);
};

void init_var_tag(Tag &tag, size_t r, const std::string *n);
void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d);

static const size_t ZERO_TAGS = 0;

struct Tagpool
{
private:
	typedef lookup_t<const tagver_t*> taglookup_t;
	taglookup_t lookup;
	tagver_t *buffer;

public:
	const size_t ntags;
	tagver_t *buffer1;
	tagver_t *buffer2;

	explicit Tagpool(size_t n);
	~Tagpool();
	size_t insert(const tagver_t *tags);
	const tagver_t *operator[](size_t idx) const;
	FORBID_COPY(Tagpool);
};

struct tagcopy_t
{
	static free_list<tagcopy_t*> freelist;

	tagcopy_t *next;
	tagver_t lhs; // left hand side
	tagver_t rhs; // right hand side

	tagcopy_t(tagcopy_t *n, tagver_t l, tagver_t r);
	~tagcopy_t();
	FORBID_COPY(tagcopy_t);
};

/* must be packed */
struct tagcmd_t
{
	size_t set;
	tagcopy_t *copy;

	tagcmd_t(): set(ZERO_TAGS), copy(NULL) {}
	tagcmd_t(size_t s, tagcopy_t *c): set(s), copy(c) {}
	inline bool empty() const
	{
		return set == ZERO_TAGS && copy == NULL;
	}
};

inline bool operator==(const tagcmd_t &x, const tagcmd_t &y)
{
	return x.set == y.set && x.copy == y.copy;
}

inline bool operator!=(const tagcmd_t &x, const tagcmd_t &y)
{
	return !(x == y);
}

inline bool operator<(const tagcmd_t &x, const tagcmd_t &y)
{
	return x.set < y.set
		|| (x.set == y.set && x.copy < y.copy);
}

} // namespace re2c

#endif // _RE2C_IR_TAG_
