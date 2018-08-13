#ifndef _RE2C_DFA_TAGPOOL_
#define _RE2C_DFA_TAGPOOL_

#include <stddef.h>
#include "src/util/c99_stdint.h"

#include "src/re/tag.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"


namespace re2c
{

static const size_t ZERO_TAGS = 0;

struct Tagpool
{
private:
	typedef lookup_t<const tagver_t*> taglookup_t;
	taglookup_t lookup;

public:
	const size_t ntags;
	tagver_t *buffer;

	explicit Tagpool(size_t n);
	~Tagpool();
	uint32_t insert_const(tagver_t ver);
	uint32_t insert_succ(tagver_t fst);
	uint32_t insert(const tagver_t *tags);
	const tagver_t *operator[](uint32_t idx) const;
	FORBID_COPY(Tagpool);
};

} // namespace re2c

#endif // _RE2C_DFA_TAGPOOL_
