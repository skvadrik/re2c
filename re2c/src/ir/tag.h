#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <string>

#include "src/util/lookup.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Tag
{
	static const size_t NONE;

	enum {VAR, FIX} type;
	size_t rule;
	const std::string *name;
	union
	{
		struct
		{
			size_t orig;
		} var;
		struct
		{
			size_t base;
			size_t dist;
		} fix;
	};

	Tag();
	FORBID_COPY(Tag);
};

void init_var_tag(Tag &tag, size_t r, const std::string *n, size_t o);
void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d);

static const size_t ZERO_TAGS = 0;

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

/* must be packed */
struct tagcmd_t
{
	size_t set;
	size_t copy;

	tagcmd_t(): set(ZERO_TAGS), copy(ZERO_TAGS) {}
	tagcmd_t(size_t s, size_t c): set(s), copy(c) {}
	inline bool empty() const
	{
		return set == ZERO_TAGS && copy == ZERO_TAGS;
	}
};

inline bool operator==(const tagcmd_t &x, const tagcmd_t &y)
{
	return x.set == y.set && x.copy == y.copy;
}

inline bool operator!=(const tagcmd_t &x, const tagcmd_t &y)
{
	return !(x == y);
}

inline bool operator<(const tagcmd_t &x, const tagcmd_t &y)
{
	return x.set < y.set
		|| (x.set == y.set && x.copy < y.copy);
}

} // namespace re2c

#endif // _RE2C_IR_TAG_
