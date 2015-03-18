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
	void used_labels ();
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
	~Binary ();
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
};

struct Linear
{
	std::vector<std::pair<const Cond *, const State *> > branches;
	Linear (const Span * s, uint n, const State * next);
	~Linear ();
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
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
	~If ();
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
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
	~SwitchIf ();
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
};

struct Bitmap
{
	const BitMap * bitmap;
	const State * bitmap_state;
	SwitchIf * hgo;
	SwitchIf * lgo;
	Bitmap (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const BitMap * bm, const State * bm_state, const State * next);
	~Bitmap ();
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
};

struct CpgotoTable
{
	static const uint TABLE_SIZE;
	uint * table;
	CpgotoTable (const Span * span, uint nSpans);
	~CpgotoTable ();
	void emit (OutputFile & o, uint ind);
	void used_labels ();
};

struct Cpgoto
{
	SwitchIf * hgo;
	CpgotoTable * table;
	Cpgoto (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const State * next);
	~Cpgoto ();
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
};

struct Dot
{
	const State * from;
	Cases * cases;
	Dot (const Span * sp, uint nsp, const State * from);
	~Dot ();
	void emit (OutputFile & o);
};

struct Go
{
	uint nSpans; // number of spans
	Span * span;
	enum
	{
		NOT_INITIALIZED,
		EMPTY,
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
	~Go ();
	void init (const State * from);
	void emit (OutputFile & o, uint ind, bool & readCh);
	void used_labels ();
};

bool matches(const Span * b1, uint n1, const State * s1, const Span * b2, uint n2, const State * s2);
uint unmap (Span * new_span, const Span * old_span, uint old_nspans, const State * x);
std::string space (uint this_label);
std::string output_yych (bool & readCh);
void output_if (OutputFile & o, uint ind, bool & readCh, const std::string & compare, uint value);
void output_goto (OutputFile & o, uint ind, bool & readCh, uint to);
std::string output_hgo (OutputFile & o, uint ind, bool & readCh, SwitchIf * hgo);

} // namespace re2c

#endif // _go_h
