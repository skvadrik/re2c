#ifndef _skeleton_h
#define _skeleton_h

#include <map>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/local_increment.h"
#include "src/util/wrap_iterator.h"

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

struct Node
{
	typedef std::map<const State *, Node *> s2n_map;
	typedef std::map<Node *, std::vector<uint32_t> > arcs_t;
	typedef local_increment_t<uint8_t> local_inc;
	typedef wrap_iterator_t<arcs_t> wrap_iter;

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

	Node (const State * s, const s2n_map & s2n);
	~Node ();
	bool end () const;
	uint32_t estimate_size_all (uint32_t inarcs, uint32_t len);
	uint32_t estimate_size_cover (uint32_t inarcs, uint32_t len);
	void generate_paths_all (const std::vector<Path> & prefixes, std::vector<Path> & results);
	void generate_paths_cover (const std::vector<Path> & prefixes, std::vector<Path> & results);

	FORBID_COPY (Node);
};

struct Skeleton
{
	static const uint32_t DATA_LIMIT;

	Node * nodes;

	Skeleton (const DFA & dfa);
	~Skeleton ();
	void generate_paths (std::vector<Path> & results);
	void emit_data (DataFile & o);

	FORBID_COPY (Skeleton);
};

void emit_prolog (OutputFile & o, uint32_t ind, const char * data_name);
void emit_epilog (OutputFile & o, uint32_t ind);

} // namespace skeleton

} // namespace re2c

#endif // _skeleton_h
