#ifndef _RE2C_IR_SKELETON_SKELETON_
#define _RE2C_IR_SKELETON_SKELETON_

#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <valarray>
#include <vector>
#include <utility>

#include "src/ir/regexp/regexp.h"
#include "src/ir/rule.h"
#include "src/util/local_increment.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct dfa_t;
struct OutputFile;
struct path_t;

typedef local_increment_t<uint8_t> local_inc;

struct Node
{
	typedef std::vector<std::pair<uint32_t, uint32_t> > arcset_t;
	typedef std::map<size_t, arcset_t> arcsets_t;

	typedef std::vector<uint32_t> arc_t;
	typedef std::map<size_t, arc_t> arcs_t;

	arcs_t arcs;
	arcsets_t arcsets;
	size_t rule;
	const bool *tags;

	Node();
	void init(const bool *ts, size_t r,
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

	size_t sizeof_key;
	std::valarray<Rule> &rules;
	const size_t defrule;
	const std::valarray<Tag> &tags;

	Skeleton(const dfa_t &dfa, const charset_t &cs, size_t def,
		const std::string &dfa_name, const std::string &dfa_cond,
		uint32_t dfa_line);
	~Skeleton ();
	size_t rule2key(size_t r) const;
	template<typename key_t> key_t rule2key(size_t r, size_t def) const;

	FORBID_COPY(Skeleton);
};

template<typename key_t> key_t Skeleton::rule2key(size_t r, size_t def) const
{
	if (r == Rule::NONE) {
		return std::numeric_limits<key_t>::max();
	} else if (r == def) {
		key_t k = std::numeric_limits<key_t>::max();
		return --k;
	} else {
		return static_cast<key_t>(r);
	}
}

uint32_t maxpath(const Skeleton &skel);
void warn_undefined_control_flow(const Skeleton &skel);
void fprint_default_path(FILE *f, const Skeleton &skel, const path_t &p);
void warn_unreachable(const Skeleton &skel);
void emit_data(const Skeleton &skel);
void emit_prolog(OutputFile & o);
void emit_start(const Skeleton &skel, OutputFile &o, size_t maxfill,
	bool backup, bool backupctx, bool accept, bool basetag,
	const std::set<std::string> &tagnames);
void emit_end(const Skeleton &skel, OutputFile &o, bool backup, bool backupctx);
void emit_epilog(OutputFile &o, const std::set<std::string> &names);
void emit_action(const Skeleton &skel, OutputFile &o, uint32_t ind,
	size_t rule);

} // namespace re2c

#endif // _RE2C_IR_SKELETON_SKELETON_
