#ifndef _RE2C_IR_CTX_
#define _RE2C_IR_CTX_

#include <string>

namespace re2c
{

struct CtxVar
{
	const std::string *name;
	std::string fullname;

	CtxVar(const std::string *n, size_t idx);
	CtxVar(const CtxVar &ctx)
		: name(ctx.name)
		, fullname(ctx.fullname)
	{}
	CtxVar& operator=(const CtxVar &ctx)
	{
		name = ctx.name;
		fullname = ctx.fullname;
		return *this;
	}
};

struct CtxFix
{
	static const size_t RIGHTMOST;

	const std::string *name;
	size_t base;
	size_t dist;

	CtxFix(const std::string *n, size_t b, size_t d)
		: name(n)
		, base(b)
		, dist(d)
	{}
};

struct Trail
{
	enum {NONE, VAR, FIX} type;
	union
	{
		size_t var;
		size_t fix; // trailing means rightmost; no need for base
	} pld;

	Trail(): type(NONE), pld() {}
	void make_var(size_t v)
	{
		type = VAR;
		pld.var = v;
	}
	void make_fix(size_t f)
	{
		type = FIX;
		pld.fix = f;
	}
};

} // namespace re2c

#endif // _RE2C_IR_CTX_
