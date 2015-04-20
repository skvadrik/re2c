#ifndef _skeleton_h
#define _skeleton_h

#include <map>
#include <vector>

#include "c99_stdint.h"
#include "dfa.h"

namespace re2c
{

struct Path
{
	std::vector<uint32_t> chars;
	uint32_t length;
	uint32_t rule;
	inline Path (const std::vector<uint32_t> & cs, uint32_t l, uint32_t r)
		: chars (cs)
		, length (l)
		, rule (r)
	{}
	inline void update (uint32_t r)
	{
		if (r != ~0u)
		{
			length = chars.size ();
			rule = r;
		}
	}
	inline void extend (uint32_t r, uint32_t c)
	{
		update (r);
		chars.push_back (c);
	}
	inline void append (const Path * p)
	{
		if (p->rule != ~0u)
		{
			length = chars.size () + p->length;
			rule = p->rule;
		}
		for (uint32_t i = 0; i < p->chars.size (); ++i)
		{
			chars.push_back (p->chars[i]);
		}
	}
};

struct SkeletonState
{
	typedef std::map<SkeletonState *, std::vector<uint32_t> > go_t;
	go_t go;
	uint32_t rule;
	uint8_t visited;
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
	static const uint32_t MAX_PATHS;
	const uint32_t states_count;
	SkeletonState * states;

	Skeleton (const DFA & dfa);
	~Skeleton ();
	uint32_t estimate_paths_count (SkeletonState * s, uint32_t count);
	void generate_paths (std::vector<Path> & results);
	void emit_data (DataFile & o);
};

void skeleton_emit_prolog (OutputFile & o, uint32_t ind, const char * data_name);
void skeleton_emit_epilog (OutputFile & o, uint32_t ind);
void generate_paths_all (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results);
void generate_paths_cover (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results);

} // namespace re2c

#endif // _skeleton_h
