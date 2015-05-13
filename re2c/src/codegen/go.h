#ifndef _go_h
#define _go_h

#include <iostream>
#include <vector>

#include "src/codegen/output.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class BitMap;
class State;
struct If;

struct Span
{
	uint32_t ub;
	State * to;
	uint32_t show (std::ostream&, uint32_t) const;

	FORBID_COPY (Span);
};

struct Case
{
	std::vector<std::pair<uint32_t, uint32_t> > ranges;
	const State * to;
	void emit (OutputFile & o, uint32_t ind);

	inline Case ()
		: ranges ()
		, to (NULL)
	{}

	FORBID_COPY (Case);
};

struct Cases
{
	const State * def;
	Case * cases;
	uint32_t cases_size;
	void add (uint32_t lb, uint32_t ub, State * to);
	Cases (const Span * s, uint32_t n);
	~Cases ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
	void used_labels ();

	FORBID_COPY (Cases);
};

struct Cond
{
	std::string compare;
	uint32_t value;
	Cond (const std::string & cmp, uint32_t val);
};

struct Binary
{
	Cond * cond;
	If * thn;
	If * els;
	Binary (const Span * s, uint32_t n, const State * next);
	~Binary ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
	void used_labels ();

	FORBID_COPY (Binary);
};

struct Linear
{
	std::vector<std::pair<const Cond *, const State *> > branches;
	Linear (const Span * s, uint32_t n, const State * next);
	~Linear ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
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
	If (type_t t, const Span * sp, uint32_t nsp, const State * next);
	~If ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
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
	SwitchIf (const Span * sp, uint32_t nsp, const State * next);
	~SwitchIf ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
	void used_labels ();
};

struct GoBitmap
{
	const BitMap * bitmap;
	const State * bitmap_state;
	SwitchIf * hgo;
	SwitchIf * lgo;
	GoBitmap (const Span * span, uint32_t nSpans, const Span * hspan, uint32_t hSpans, const BitMap * bm, const State * bm_state, const State * next);
	~GoBitmap ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
	void used_labels ();

	FORBID_COPY (GoBitmap);
};

struct CpgotoTable
{
	static const uint32_t TABLE_SIZE;
	const State ** table;
	CpgotoTable (const Span * span, uint32_t nSpans);
	~CpgotoTable ();
	void emit (OutputFile & o, uint32_t ind);
	void used_labels ();

	FORBID_COPY (CpgotoTable);
};

struct Cpgoto
{
	SwitchIf * hgo;
	CpgotoTable * table;
	Cpgoto (const Span * span, uint32_t nSpans, const Span * hspan, uint32_t hSpans, const State * next);
	~Cpgoto ();
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
	void used_labels ();

	FORBID_COPY (Cpgoto);
};

struct Dot
{
	const State * from;
	Cases * cases;
	Dot (const Span * sp, uint32_t nsp, const State * from);
	~Dot ();
	void emit (OutputFile & o);

	FORBID_COPY (Dot);
};

struct Go
{
	uint32_t nSpans; // number of spans
	Span * span;
	enum
	{
		EMPTY,
		SWITCH_IF,
		BITMAP,
		CPGOTO,
		DOT
	} type;
	union
	{
		SwitchIf * switchif;
		GoBitmap * bitmap;
		Cpgoto * cpgoto;
		Dot * dot;
	} info;

	Go ();
	~Go ();
	void init (const State * from);
	void emit (OutputFile & o, uint32_t ind, bool & readCh);
	void used_labels ();

	Go (const Go & g)
		: nSpans (g.nSpans)
		, span (g.span)
		, type (g.type)
		, info (g.info)
	{}
	Go & operator = (const Go & g)
	{
		nSpans = g.nSpans;
		span = g.span;
		type = g.type;
		info = g.info;
		return * this;
	}
};

// construct helpers
bool matches(const Span * b1, uint32_t n1, const State * s1, const Span * b2, uint32_t n2, const State * s2);
uint32_t unmap (Span * new_span, const Span * old_span, uint32_t old_nspans, const State * x);

// emit helpers
std::string space (uint32_t this_label);
std::string output_yych (bool & readCh);
void output_if (OutputFile & o, uint32_t ind, bool & readCh, const std::string & compare, uint32_t value);
void output_goto (OutputFile & o, uint32_t ind, bool & readCh, uint32_t to);
std::string output_hgo (OutputFile & o, uint32_t ind, bool & readCh, SwitchIf * hgo);

} // namespace re2c

#endif // _go_h
