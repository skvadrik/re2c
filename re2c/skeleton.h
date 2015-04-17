#ifndef _skeleton_h
#define _skeleton_h

#include <map>
#include <vector>

#include "basics.h"
#include "dfa.h"

namespace re2c
{

struct Path
{
	std::vector<uint> chars;
	uint length;
	uint rule;
	inline Path (const std::vector<uint> & cs, uint l, uint r)
		: chars (cs)
		, length (l)
		, rule (r)
	{}
};

struct Result
{
	uint processed;
	uint consumed;
	uint rule;
	inline explicit Result (const Path & p)
		: processed (p.chars.size ())
		, consumed (p.length)
		, rule (p.rule)
	{}
};

struct SkeletonState
{
	typedef std::map<SkeletonState *, std::vector<uint> > go_t;
	go_t go;
	uint rule;
	uchar visited;
	Path * path;
	inline SkeletonState ()
		: go ()
		, rule (~0u)
		, visited (0)
		, path (NULL)
	{}
	inline bool is_end ()
	{
		return go.size () == 0;
	}
};

struct Skeleton
{
	const uint states_count;
	SkeletonState * states;
	Skeleton (const DFA & dfa);
	~Skeleton ();
	unsigned long count ();
	void generate_data (DataFile & o, uint ind, std::vector<Result> & results);
	void emit_data (DataFile & o);
};

unsigned long count_data (SkeletonState * s, unsigned long count);
void skeleton_emit_prolog (OutputFile & o, uint ind, const char * data_name);
void skeleton_emit_epilog (OutputFile & o, uint ind);
void update (Path & p, SkeletonState * s);
void append (Path & p1, const Path * p2);
void dump_paths (DataFile & o, uint ind, const std::vector<uint> & path);
void generate (DataFile & o, uint ind, SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Result> & results);

} // namespace re2c

#endif // _skeleton_h
