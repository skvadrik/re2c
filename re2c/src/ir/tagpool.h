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
	size_t orl(size_t t, size_t o);
	size_t andl(size_t t, size_t a);
	size_t andlinv(size_t t, size_t a);
	size_t subst(size_t t, const size_t *represent);
	const bool *operator[](size_t idx);
	FORBID_COPY(Tagpool);
};

} // namespace re2c

#endif // _RE2C_IR_TAGPOOL_
