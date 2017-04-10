#ifndef _RE2C_DFA_TAGPOOL_
#define _RE2C_DFA_TAGPOOL_

#include "src/dfa/tagtree.h"
#include "src/re/tag.h"
#include "src/util/lookup.h"
#include "src/util/forbid_copy.h"

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

	size_t maxclos;
	tagver_t *orders;

	tagtree_t history;

	explicit Tagpool(size_t n);
	~Tagpool();
	size_t insert_const(tagver_t ver);
	size_t insert_succ(tagver_t fst);
	size_t insert(const tagver_t *tags);
	const tagver_t *operator[](size_t idx) const;
	FORBID_COPY(Tagpool);
};

} // namespace re2c

#endif // _RE2C_DFA_TAGPOOL_
