#ifndef _RE2C_IR_TCMD_
#define _RE2C_IR_TCMD_

#include "src/ir/tag.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/free_list.h"
#include "src/util/lookup.h"

namespace re2c
{

struct tagsave_t
{
	static free_list<tagsave_t*> freelist;

	tagsave_t *next;
	tagver_t ver;

	static tagsave_t *convert(const tagver_t *vers, size_t ntag);
	static void swap(tagsave_t &x, tagsave_t &y);
	static bool less(const tagsave_t &x, const tagsave_t &y);
	static bool equal(const tagsave_t &x, const tagsave_t &y);
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
	tagcopy_t(tagcopy_t *n, tagver_t l, tagver_t r);
	~tagcopy_t();
	FORBID_COPY(tagcopy_t);
};

struct tcmd_t
{
	tagsave_t *save;
	tagcopy_t *copy;

	tcmd_t();
};

struct tccmd_t
{
	const tagsave_t *save;
	const tagcopy_t *copy;

	tccmd_t(const tagsave_t *s, const tagcopy_t *c);
};

typedef uint32_t tcid_t;

static const tcid_t TCID0 = 0;

struct tcpool_t
{
private:
	typedef lookup_t<tccmd_t> index_t;
	index_t index;

public:
	tcpool_t();
	tcid_t insert(const tagsave_t *save, const tagcopy_t *copy);
	const tccmd_t &operator[](tcid_t id) const;
};

} // namespace re2c

#endif // _RE2C_IR_TCMD_
