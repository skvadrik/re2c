#ifndef _RE2C_IR_TAGPOOL_
#define _RE2C_IR_TAGPOOL_

#include <stdlib.h> // malloc
#include <string.h> // memcpy, memcmp

#include "src/util/lookup.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

static const size_t ZERO_TAGS = 0;

struct eqtag_t
{
	size_t ntags;

	explicit eqtag_t(size_t n): ntags(n) {}
	inline bool operator()(const bool *x, const bool *y)
	{
		return memcmp(x, y, ntags * sizeof(bool)) == 0;
	}
};

struct Tagpool
{
private:
	typedef lookup_t<const bool*> taglookup_t;
	taglookup_t lookup;
	bool *buffer;

public:
	const size_t ntags;
	bool *buffer1;
	bool *buffer2;

	explicit Tagpool(size_t n);
	~Tagpool();
	size_t insert(const bool *tags);
	size_t orl(size_t t, size_t o);
	size_t andl(size_t t, size_t a);
	size_t andlinv(size_t t, size_t a);
	size_t subst(size_t t, const size_t *represent);
	const bool *operator[](size_t idx) const;
	FORBID_COPY(Tagpool);
};

} // namespace re2c

#endif // _RE2C_IR_TAGPOOL_
