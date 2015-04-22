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

template <typename counter_t>
struct local_increment_t
{
	counter_t & counter;
	inline explicit local_increment_t (counter_t & c)
		: counter (++c)
	{}
	inline ~local_increment_t ()
	{
		--counter;
	}
};

template <typename container_t>
class wrap_iter_t
{
	container_t & cont;
	typename container_t::iterator iter;
	bool wrapped;

public:
	wrap_iter_t (container_t & c)
		: cont (c)
		, iter (cont.begin ())
		, wrapped (false)
	{}
	bool end () const
	{
		return wrapped;
	}
	void operator ++ ()
	{
		if (++iter == cont.end ())
		{
			iter = cont.begin ();
			wrapped = true;
		}
	}
	typename container_t::value_type * operator -> ()
	{
		return iter.operator -> ();
	}
};

struct SkeletonState
{
	typedef std::map<SkeletonState *, std::vector<uint32_t> > go_t;
	typedef local_increment_t<uint8_t> visit;
	typedef wrap_iter_t<go_t> wrap_iter;

	// outgoing arrows
	go_t go;

	// how many times this state has been visited
	// (controls looping when traversing DFA)
	uint8_t visited;

	// rule number (if any)
	uint32_t rule;

	// stuff for constructing path cover (for large DFAs)
	static const uint32_t INVALID_PATH_LEN;
	uint32_t path_len;
	Path * path;

	inline SkeletonState ()
		: go ()
		, visited (0)
		, rule (~0u)
		, path_len (INVALID_PATH_LEN)
		, path (NULL)
	{}
	~SkeletonState ();
	void init (const State * s, const std::map<const State *, SkeletonState *> & m);
	inline bool is_end ()
	{
		return go.size () == 0;
	}
};

struct Skeleton
{
	static const uint32_t MAX_SIZE;
	const uint32_t states_count;
	SkeletonState * states;

	Skeleton (const DFA & dfa);
	~Skeleton ();
	uint32_t estimate_size_all (SkeletonState * s, uint32_t count, uint32_t len);
	uint32_t estimate_size_cover (SkeletonState * s, uint32_t count, uint32_t len);
	void generate_paths (std::vector<Path> & results);
	void emit_data (DataFile & o);
};

void skeleton_emit_prolog (OutputFile & o, uint32_t ind, const char * data_name);
void skeleton_emit_epilog (OutputFile & o, uint32_t ind);
void generate_paths_all (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results);
void generate_paths_cover (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results);

} // namespace re2c

#endif // _skeleton_h
