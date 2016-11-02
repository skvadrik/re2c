#include <assert.h>

#include "src/ir/tcmd.h"
#include "src/util/hash32.h"

namespace re2c
{

static uint32_t hash_tcmd(const tagsave_t *save, const tagcopy_t *copy);

free_list<tagsave_t*> tagsave_t::freelist;

tagsave_t::tagsave_t(tagsave_t *n, tagver_t v)
	: next(n)
	, ver(v)
{
	freelist.insert(this);
}

tagsave_t::~tagsave_t()
{
	freelist.erase(this);
}

tagsave_t *tagsave_t::convert(const tagver_t *vers, size_t ntag)
{
	tagsave_t *s = NULL;
	for (size_t t = ntag; t-- > 0;) {
		const tagver_t v = vers[t];
		if (v != TAGVER_ZERO) {
			s = new tagsave_t(s, v);
		}
	}
	return s;
}

void tagsave_t::swap(tagsave_t &x, tagsave_t &y)
{
	std::swap(x.ver, y.ver);
}

bool tagsave_t::less(const tagsave_t &x, const tagsave_t &y)
{
	return x.ver < y.ver;
}

bool tagsave_t::equal(const tagsave_t &x, const tagsave_t &y)
{
	return x.ver == y.ver;
}

free_list<tagcopy_t*> tagcopy_t::freelist;

tagcopy_t::tagcopy_t(tagcopy_t *n, tagver_t l, tagver_t r)
	: next(n)
	, lhs(l)
	, rhs(r)
{
	freelist.insert(this);
}

tagcopy_t::~tagcopy_t()
{
	freelist.erase(this);
}

void tagcopy_t::swap(tagcopy_t &x, tagcopy_t &y)
{
	std::swap(x.lhs, y.lhs);
	std::swap(x.rhs, y.rhs);
}

bool tagcopy_t::less(const tagcopy_t &x, const tagcopy_t &y)
{
	const tagver_t
		lx = x.lhs, ly = y.lhs,
		rx = x.rhs, ry = y.rhs;
	return (lx < ly) || (lx == ly && rx < ry);
}

bool tagcopy_t::equal(const tagcopy_t &x, const tagcopy_t &y)
{
	return x.lhs == y.lhs && x.rhs == y.rhs;
}

tcmd_t::tcmd_t(): save(NULL), copy(NULL) {}

tccmd_t::tccmd_t(const tagsave_t *s, const tagcopy_t *c): save(s), copy(c) {}

tcpool_t::tcpool_t()
	: index()
{
	// empty command must have static number zero
	assert(TCID0 == insert(NULL, NULL));
}

uint32_t hash_tcmd(const tagsave_t *save, const tagcopy_t *copy)
{
	uint32_t h = 0;
	for (const tagsave_t *p = save; p; p = p->next) {
		h = hash32(h, &p->ver, sizeof(p->ver));
	}
	for (const tagcopy_t *p = copy; p; p = p->next) {
		h = hash32(h, &p->lhs, sizeof(p->lhs));
		h = hash32(h, &p->rhs, sizeof(p->rhs));
	}
	return h;
}

template<typename cmd_t>
bool eq(const cmd_t *x, const cmd_t *y)
{
	for (;;) {
		if (!x && !y) return true;
		if (!x || !y) return false;
		if (!cmd_t::equal(*x, *y)) return false;
		x = x->next;
		y = y->next;
	}
}

struct tccmd_eq_t
{
	bool operator()(const tccmd_t &x, const tccmd_t &y) const
	{
		return eq<tagsave_t>(x.save, y.save)
			&& eq<tagcopy_t>(x.copy, y.copy);
	}
};

tcid_t tcpool_t::insert(const tagsave_t *save, const tagcopy_t *copy)
{
	const uint32_t h = hash_tcmd(save, copy);

	const tccmd_t ccmd(save, copy);
	size_t id = index.find_with(h, ccmd, tccmd_eq_t());
	if (id == index_t::NIL) {
		id = index.push(h, ccmd);
	}

	return static_cast<tcid_t>(id);
}

const tccmd_t &tcpool_t::operator[](tcid_t id) const
{
	return index[id];
}

} // namespace re2c
