#ifndef _RE2C_IR_CTX_
#define _RE2C_IR_CTX_

#include <string>

namespace re2c
{

struct CtxVar
{
	size_t rule;
	const std::string *codename;
	std::string uniqname;

	CtxVar(const std::string *n, size_t r);
	CtxVar(const CtxVar &ctx)
		: rule(ctx.rule)
		, codename(ctx.codename)
		, uniqname(ctx.uniqname)
	{}
	CtxVar& operator=(const CtxVar &ctx)
	{
		rule = ctx.rule;
		codename = ctx.codename;
		uniqname = ctx.uniqname;
		return *this;
	}
	std::string name() const;
	std::string expr() const;
};

struct CtxFix
{
	static const size_t RIGHTMOST;

	size_t rule;
	const std::string *codename;
	size_t base;
	size_t dist;

	CtxFix(const std::string *n, size_t r, size_t b, size_t d)
		: rule(r)
		, codename(n)
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
		size_t fix;
	};

	Trail(): type(NONE) {}
	void make_var(size_t v)
	{
		type = VAR;
		var = v;
	}
	void make_fix(size_t f)
	{
		type = FIX;
		fix = f;
	}
};

} // namespace re2c

#endif // _RE2C_IR_CTX_
