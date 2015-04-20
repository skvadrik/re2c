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
	inline void extend (uint r, uint c)
	{
		if (r != ~0u)
		{
			length = chars.size ();
			rule = r;
		}
		chars.push_back (c);
	}
	inline void append (const Path * p)
	{
		if (p->rule != ~0u)
		{
			length = chars.size () + p->length;
			rule = p->rule;
		}
		for (uint i = 0; i < p->chars.size (); ++i)
		{
			chars.push_back (p->chars[i]);
		}
	}
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
	inline void wrap (go_t::iterator & i)
	{
		if (i == go.end ())
		{
			i = go.begin ();
		}
	}
};

struct Skeleton
{
	static const uint MAX_PATHS;
	const uint states_count;
	SkeletonState * states;

	Skeleton (const DFA & dfa);
	~Skeleton ();
	bool estimate_path_count (SkeletonState * s, uint prefixes, uint & result);
	void generate_paths (std::vector<Path> & results);
	void emit_data (DataFile & o);
};

void skeleton_emit_prolog (OutputFile & o, uint ind, const char * data_name);
void skeleton_emit_epilog (OutputFile & o, uint ind);
void generate (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results);

} // namespace re2c

#endif // _skeleton_h
