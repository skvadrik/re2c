#ifndef _skeleton_h
#define _skeleton_h

#include <map>
#include <vector>

#include "c99_stdint.h"
#include "dfa.h"

namespace re2c
{

namespace skeleton
{

const uint32_t NO_RULE = 0xFFFFffff;

struct Path
{
	typedef std::vector<uint32_t> chars_t;

	chars_t chars;
	uint32_t length;
	uint32_t rule;

	Path (const chars_t & cs, uint32_t l, uint32_t r);
	void update (uint32_t r);
	void extend (uint32_t r, uint32_t c);
	void append (const Path * p);
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

struct Node
{
	typedef std::map<const State *, Node *> s2n_map;
	typedef std::map<Node *, std::vector<uint32_t> > arcs_t;
	typedef local_increment_t<uint8_t> local_inc;
	typedef wrap_iter_t<arcs_t> wrap_iter;

	// outgoing arcs
	arcs_t arcs;

	// how many times this node has been visited
	// (controls looping in graph traversals)
	uint8_t loop;

	// rule number for corresponding DFA state (if any)
	uint32_t rule;

	// stuff for constructing path cover (for large graphs)
	static const uint32_t UNKNOWN_LEN;
	uint32_t path_len;
	Path * path;

	inline Node () {} // only to allow array allocation with 'new'
	Node (const State * s, const s2n_map & s2n);
	~Node ();
	bool end () const;
	uint32_t estimate_size_all (uint32_t inarcs, uint32_t len);
	uint32_t estimate_size_cover (uint32_t inarcs, uint32_t len);
	void generate_paths_all (const std::vector<Path> & prefixes, std::vector<Path> & results);
	void generate_paths_cover (const std::vector<Path> & prefixes, std::vector<Path> & results);
};

struct Skeleton
{
	static const uint32_t DATA_LIMIT;

	Node * nodes;

	Skeleton (const DFA & dfa);
	~Skeleton ();
	void generate_paths (std::vector<Path> & results);
	void emit_data (DataFile & o);
};

void emit_prolog (OutputFile & o, uint32_t ind, const char * data_name);
void emit_epilog (OutputFile & o, uint32_t ind);

} // namespace skeleton

} // namespace re2c

#endif // _skeleton_h
