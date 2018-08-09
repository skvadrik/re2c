#ifndef _RE2C_DFA_TAGPOOL_
#define _RE2C_DFA_TAGPOOL_

#include <stddef.h>
#include <stack>

#include "src/dfa/closure.h"
#include "src/dfa/tagtree.h"
#include "src/re/tag.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"
#include "src/util/slab_allocator.h"

namespace re2c
{

struct nfa_state_t;
struct opt_t;

static const size_t ZERO_TAGS = 0;

struct Tagpool
{
private:
	typedef lookup_t<const tagver_t*> taglookup_t;
	taglookup_t lookup;

public:
	const opt_t *opts;
	const size_t ntags;
	tagver_t *buffer;

	typedef slab_allocator_t<> alc_t;
	alc_t alc;

	tagtree_t history;
	std::stack<nfa_state_t*> astack;
	std::stack<nfa_state_t*> bstack;
	std::stack<clos_t> cstack;

	Tagpool(const opt_t *o, size_t n);
	~Tagpool();
	size_t insert_const(tagver_t ver);
	size_t insert_succ(tagver_t fst);
	size_t insert(const tagver_t *tags);
	const tagver_t *operator[](size_t idx) const;
	FORBID_COPY(Tagpool);
};

} // namespace re2c

#endif // _RE2C_DFA_TAGPOOL_
