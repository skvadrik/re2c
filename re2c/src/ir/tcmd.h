#ifndef _RE2C_IR_TCMD_
#define _RE2C_IR_TCMD_

#include "src/ir/tag.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"
#include "src/util/slab_allocator.h"

namespace re2c
{

struct tagsave_t
{
	tagsave_t *next;
	tagver_t ver;
	bool bottom;

	static void swap(tagsave_t &x, tagsave_t &y);
	static bool less(const tagsave_t &x, const tagsave_t &y);
	static bool equal(const tagsave_t &x, const tagsave_t &y);
	FORBID_COPY(tagsave_t);
};

struct tagcopy_t
{
	tagcopy_t *next;
	tagver_t lhs; // left hand side
	tagver_t rhs; // right hand side

	static bool less(const tagcopy_t &x, const tagcopy_t &y);
	static void swap(tagcopy_t &x, tagcopy_t &y);
	static bool equal(const tagcopy_t &x, const tagcopy_t &y);
	FORBID_COPY(tagcopy_t);
};

struct tcmd_t
{
	tagsave_t *save;
	tagcopy_t *copy;

	tcmd_t();
	tcmd_t(tagsave_t *s, tagcopy_t *c);
	bool empty() const;
};

struct tccmd_t
{
	const tagsave_t *save;
	const tagcopy_t *copy;

	tccmd_t(const tagsave_t *s, const tagcopy_t *c);
};

typedef uint32_t tcid_t;

static const tcid_t TCID0 = 0;

class tcpool_t
{
	typedef slab_allocator_t<~0u, 4096> alc_t;
	typedef lookup_t<tccmd_t> index_t;

	alc_t alc;
	index_t index;

public:
	tcpool_t();

	tagsave_t *make_save(tagsave_t *next, tagver_t ver, bool bottom);
	tagcopy_t *make_copy(tagcopy_t *next, tagver_t lhs, tagver_t rhs);
	tagsave_t *conv_to_save(const tagver_t *vers, size_t ntag);
	tcmd_t conv_to_tcmd(const tagver_t *vers, const tagver_t *fins, size_t ltag, size_t htag, size_t ntag);

	tcid_t insert(const tagsave_t *save, const tagcopy_t *copy);
	const tccmd_t &operator[](tcid_t id) const;
};

} // namespace re2c

#endif // _RE2C_IR_TCMD_
