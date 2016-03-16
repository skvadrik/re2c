#ifndef _RE2C_IR_SKELETON_SKELETON_
#define _RE2C_IR_SKELETON_SKELETON_

#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>

#include "src/ir/regexp/regexp.h"
#include "src/parse/rules.h"
#include "src/util/local_increment.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct dfa_t;
struct OutputFile;
struct path_t;
struct suffix_t;

typedef local_increment_t<uint8_t> local_inc;

struct Node
{
	typedef std::vector<std::pair<uint32_t, uint32_t> > arcset_t;
	typedef std::map<size_t, arcset_t> arcsets_t;

	typedef std::vector<uint32_t> arc_t;
	typedef std::map<size_t, arc_t> arcs_t;

	arcs_t arcs;
	arcsets_t arcsets;
	RuleInfo *rule;
	bool ctx;

	Node();
	void init(bool b, RuleInfo *r,
		const std::vector<std::pair<size_t, uint32_t> > &arcs);
	bool end() const;

	FORBID_COPY(Node);
};

struct Skeleton
{
	const std::string name;
	const std::string cond;
	const uint32_t line;

	const size_t nodes_count;
	Node *nodes;

	// visit counters (for graph traversal)
	uint8_t *loops;

	// paths to end node (for constructing path cover)
	suffix_t **suffixes;

	size_t sizeof_key;
	rules_t rules;

	Skeleton(const dfa_t &dfa, const charset_t &cs, const rules_t &rs,
		const std::string &dfa_name, const std::string &dfa_cond,
		uint32_t dfa_line);
	~Skeleton ();
	uint32_t rule2key(rule_rank_t r) const;
	template<typename key_t> static key_t rule2key(rule_rank_t r);

	FORBID_COPY(Skeleton);
};

template<typename key_t> key_t Skeleton::rule2key(rule_rank_t r)
{
	if (r.is_none()) {
		return std::numeric_limits<key_t>::max();
	} else if (r.is_def()) {
		key_t k = std::numeric_limits<key_t>::max();
		return --k;
	} else {
		return static_cast<key_t>(r.uint32());
	}
}

uint32_t maxpath(Skeleton &skel);
void warn_undefined_control_flow(Skeleton &skel);
void fprint_default_path(FILE *f, const Skeleton &skel, const path_t &p);
void warn_unreachable_nullable_rules(Skeleton &skel);
void emit_data(Skeleton &skel, const char *fname);
void emit_prolog(OutputFile & o);
void emit_start(const Skeleton &skel, OutputFile &o, size_t maxfill,
	bool backup, bool backupctx, bool accept);
void emit_end(const Skeleton &skel, OutputFile &o, bool backup, bool backupctx);
void emit_epilog(OutputFile &o, const std::set<std::string> &names);
void emit_action(const Skeleton &skel, OutputFile &o, uint32_t ind,
	rule_rank_t rank);

} // namespace re2c

#endif // _RE2C_IR_SKELETON_SKELETON_
