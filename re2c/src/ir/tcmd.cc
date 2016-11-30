#include <assert.h>

#include "src/ir/tcmd.h"
#include "src/util/hash32.h"

namespace re2c
{

static uint32_t hash_tcmd(const tagsave_t *save, const tagcopy_t *copy);

void tagsave_t::swap(tagsave_t &x, tagsave_t &y)
{
	std::swap(x.ver, y.ver);
	std::swap(x.bottom, y.bottom);
}

bool tagsave_t::less(const tagsave_t &x, const tagsave_t &y)
{
	const tagver_t xv = x.ver, yv = y.ver;
	return xv < yv || (xv == yv && x.bottom < y.bottom);
}

bool tagsave_t::equal(const tagsave_t &x, const tagsave_t &y)
{
	return x.ver == y.ver && x.bottom == y.bottom;
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
tcmd_t::tcmd_t(tagsave_t *s, tagcopy_t *c): save(s), copy(c) {}
bool tcmd_t::empty() const { return save == NULL && copy == NULL; }

tccmd_t::tccmd_t(const tagsave_t *s, const tagcopy_t *c): save(s), copy(c) {}

tcpool_t::tcpool_t()
	: alc()
	, index()
{
	// empty command must have static number zero
	assert(TCID0 == insert(NULL, NULL));
}

tagsave_t *tcpool_t::make_save(tagsave_t *next, tagver_t ver, bool bottom)
{
	tagsave_t *p = alc.alloct<tagsave_t>(1);
	p->next = next;
	p->ver = ver;
	p->bottom = bottom;
	return p;
}

tagcopy_t *tcpool_t::make_copy(tagcopy_t *next, tagver_t lhs, tagver_t rhs)
{
	tagcopy_t *p = alc.alloct<tagcopy_t>(1);
	p->next = next;
	p->lhs = lhs;
	p->rhs = rhs;
	return p;
}

tagsave_t *tcpool_t::conv_to_save(const tagver_t *bottom, const tagver_t *cursor, size_t ntag)
{
	tagsave_t *s = NULL;
	for (size_t t = ntag; t-- > 0;) {
		const tagver_t b = abs(bottom[t]), c = abs(cursor[t]);
		if (b != TAGVER_ZERO) {
			s = make_save(s, b, true);
		}
		if (c != TAGVER_ZERO) {
			s = make_save(s, c, false);
		}
	}
	return s;
}

tcmd_t tcpool_t::conv_to_tcmd(const tagver_t *vers, const tagver_t *tran,
	const tagver_t *fins, size_t ltag, size_t htag)
{
	tagsave_t *s = NULL;
	tagcopy_t *c = NULL;
	for (size_t t = ltag; t < htag; ++t) {
		const tagver_t u = tran[t], v = abs(vers[t]), f = fins[t];
		if (u != TAGVER_ZERO) {
			s = make_save(s, f, u == TAGVER_BOTTOM);
		} else {
			c = make_copy(c, f, v);
		}
	}
	return tcmd_t(s, c);
}

uint32_t hash_tcmd(const tagsave_t *save, const tagcopy_t *copy)
{
	uint32_t h = 0;
	for (const tagsave_t *p = save; p; p = p->next) {
		h = hash32(h, &p->ver, sizeof(p->ver));
		h = hash32(h, &p->bottom, sizeof(p->bottom));
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
	tccmd_eq_t eq;
	size_t id = index.find_with(h, ccmd, eq);
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
