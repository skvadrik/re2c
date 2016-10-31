#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <string>

#include "src/util/c99_stdint.h"
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

struct tagsave_t
{
	static free_list<tagsave_t*> freelist;

	tagsave_t *next;
	tagver_t ver;

	static tagsave_t *convert(const tagver_t *vers, size_t ntag);
	static void swap(tagsave_t &x, tagsave_t &y);
	static bool less(const tagsave_t &x, const tagsave_t &y);
	static bool equal(const tagsave_t &x, const tagsave_t &y);
	static uint32_t hash(const tagsave_t *p);
	tagsave_t(tagsave_t *n, tagver_t v);
	~tagsave_t();
	FORBID_COPY(tagsave_t);
};

struct tagcopy_t
{
	static free_list<tagcopy_t*> freelist;

	tagcopy_t *next;
	tagver_t lhs; // left hand side
	tagver_t rhs; // right hand side

	static bool less(const tagcopy_t &x, const tagcopy_t &y);
	static void swap(tagcopy_t &x, tagcopy_t &y);
	static bool equal(const tagcopy_t &x, const tagcopy_t &y);
	static uint32_t hash(const tagcopy_t *p);
	tagcopy_t(tagcopy_t *n, tagver_t l, tagver_t r);
	~tagcopy_t();
	FORBID_COPY(tagcopy_t);
};

/* must be packed */
struct tagcmd_t
{
	tagsave_t *save;
	tagcopy_t *copy;

	tagcmd_t(): save(NULL), copy(NULL) {}
	tagcmd_t(tagsave_t *s, tagcopy_t *c): save(s), copy(c) {}
	inline bool empty() const
	{
		return save == NULL && copy == NULL;
	}
};

inline bool operator==(const tagcmd_t &x, const tagcmd_t &y)
{
	return x.save == y.save && x.copy == y.copy;
}

inline bool operator!=(const tagcmd_t &x, const tagcmd_t &y)
{
	return !(x == y);
}

inline bool operator<(const tagcmd_t &x, const tagcmd_t &y)
{
	return x.save < y.save
		|| (x.save == y.save && x.copy < y.copy);
}

} // namespace re2c

#endif // _RE2C_IR_TAG_
