#ifndef _RE2C_CODEGEN_SKELETON_SKELETON_
#define _RE2C_CODEGEN_SKELETON_SKELETON_

#include <map>

#include "src/codegen/skeleton/path.h"
#include "src/codegen/skeleton/way.h"
#include "src/ir/dfa/dfa.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/local_increment.h"
#include "src/util/u32lim.h"

namespace re2c
{

static const uint32_t ARC_LIMIT = 1024 * 1024 * 1024; // ~1Gb
typedef u32lim_t<ARC_LIMIT> arccount_t;

struct Node
{
	typedef std::map<const State *, Node *> s2n_map;
	typedef std::map<Node *, multiarc_t> arcs_t;
	typedef std::map<Node *, way_arc_t> arcsets_t;
	typedef local_increment_t<uint8_t> local_inc;

	// outgoing arcs
	arcs_t arcs;
	arcsets_t arcsets;

	// how many times this node has been visited
	// (controls looping in graph traversals)
	uint8_t loop;

	// rule number for corresponding DFA state (if any)
	rule_rank_t rule;

	// maximal distance to end node (assuming one iteration per loop)
	static const uint32_t DIST_ERROR;
	static const uint32_t DIST_MAX;
	uint32_t dist;

	// path to end node (for constructing path cover)
	path_t * suffix;

	Node ();
	void init (const State * s, const s2n_map & s2n);
	~Node ();
	bool end () const;
	void calc_dist ();
	arccount_t sizeof_permutate (arccount_t inarcs, arccount_t len);
	template <typename cunit_t, typename key_t>
		void permutate (const multipath_t & prefix, FILE * input, FILE * keys);
	template <typename cunit_t, typename key_t>
		arccount_t cover (const multipath_t & prefix, FILE * input, FILE * keys);
	arccount_t naked_ways (const way_t & prefix, std::vector<way_t> & ways);

	FORBID_COPY (Node);
};

struct Skeleton
{
	const std::string & name;
	const std::string & cond;
	const uint32_t line;

	const uint32_t nodes_count;
	Node * nodes;
	size_t sizeof_key;

	Skeleton (const DFA & dfa);
	~Skeleton ();
	void warn_undefined_control_flow ();
	void emit_data (const char * fname);
	static void emit_prolog (OutputFile & o);
	void emit_start (OutputFile & o, uint32_t maxfill, bool yyaccept) const;
	void emit_end (OutputFile & o) const;
	static void emit_epilog (OutputFile & o, const std::vector<std::string> & names);
	static void emit_action (OutputFile & o, uint32_t ind, rule_rank_t rank, const std::string & name);

	template <typename key_t>
		static key_t maxkey ();
	uint32_t maxkey () const;

private:
	template <typename cunit_t, typename key_t>
		void generate_paths_cunit_key (FILE * input, FILE * keys);
	template <typename cunit_t>
		void generate_paths_cunit (FILE * input, FILE * keys);
	void generate_paths (FILE * input, FILE * keys);

	FORBID_COPY (Skeleton);
};

} // namespace re2c

#endif // _RE2C_CODEGEN_SKELETON_SKELETON_
