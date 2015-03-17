#ifndef _go_h
#define _go_h

#include <iostream>
#include <vector>

#include "basics.h"
#include "code.h"

namespace re2c
{

class State; // forward
struct If; // forward

struct Span
{
	uint ub;
	State * to;
	uint show (std::ostream&, uint) const;
};

struct Case
{
	std::vector<std::pair<uint, uint> > ranges;
	const State * to;
	void emit (OutputFile & o, uint ind);
};

struct Cases
{
	const State * def;
	Case * cases;
	uint cases_size;
	void add (uint lb, uint ub, State * to);
	Cases (const Span * s, uint n);
	~Cases ();
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct Cond
{
	std::string compare;
	uint value;
	Cond (const std::string & cmp, uint val);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct Binary
{
	Cond * cond;
	If * thn;
	If * els;
	Binary (const Span * s, uint n, const State * next);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct Linear
{
	std::vector<std::pair<const Cond *, const State *> > branches;
	Linear (const Span * s, uint n, const State * next);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct If
{
	enum type_t
	{
		BINARY,
		LINEAR
	} type;
	union
	{
		Binary * binary;
		Linear * linear;
	} info;
	If (type_t t, const Span * sp, uint nsp, const State * next);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct SwitchIf
{
	enum
	{
		SWITCH,
		IF
	} type;
	union
	{
		Cases * cases;
		If * ifs;
	} info;
	SwitchIf (const Span * sp, uint nsp, const State * next);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct Bitmap
{
	const BitMap * bitmap;
	const State * bitmap_state;
	SwitchIf * hgo;
	SwitchIf * lgo;
	Bitmap (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const BitMap * bm, const State * bm_state, const State * next);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct CpgotoTable
{
	uint * table;
	CpgotoTable (const Span * span, uint nSpans);
	void emit (OutputFile & o, uint ind);
};

struct Cpgoto
{
	SwitchIf * hgo;
	CpgotoTable * table;
	Cpgoto (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const State * next);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

struct Dot
{
	const State * from;
	Cases * cases;
	Dot (const Span * sp, uint nsp, const State * from);
	void emit (OutputFile & o);
};

struct Go
{
	uint nSpans; // number of spans
	Span * span;
	enum
	{
		NONE,
		SWITCH_IF,
		BITMAP,
		CPGOTO,
		DOT
	} type;
	union
	{
		SwitchIf * switchif;
		Bitmap * bitmap;
		Cpgoto * cpgoto;
		Dot * dot;
	} info;

	Go ();
	void init (const State * from);
	void emit (OutputFile & o, uint ind, bool & readCh);
};

bool matches(const Span * b1, uint n1, const State * s1, const Span * b2, uint n2, const State * s2);
uint unmap (Span * new_span, const Span * old_span, uint old_nspans, const State * x);

} // namespace re2c

#endif // _go_h
