#ifndef _RE2C_IR_TAGPOOL_
#define _RE2C_IR_TAGPOOL_

#include "src/util/ord_hash_set.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Tagpool
{
	const size_t ntags;

private:
	ord_hash_set_t pool;
	bool *buff;

public:
	explicit Tagpool(size_t n);
	~Tagpool();
	size_t insert(const bool *tags);
	void orl(size_t *pt, size_t o);
	void orl_with_mask(size_t *pt, size_t o, size_t m);
	void andl(size_t *pt, size_t a);
	void subst(size_t *pt, const std::vector<size_t> &represent);
	const bool *operator[](size_t idx);
	FORBID_COPY(Tagpool);
};

} // namespace re2c

#endif // _RE2C_IR_TAGPOOL_
