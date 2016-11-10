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
#include "src/ir/tcmd.h"
#include "src/util/local_increment.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct dfa_t;
struct dfa_state_t;
struct OutputFile;
struct path_t;

typedef local_increment_t<uint8_t> local_inc;

struct Node
{
	struct range_t {
		uint32_t lower;
		uint32_t upper;
		const tcmd_t *cmd;

		range_t(): lower(0), upper(0), cmd(NULL) {}
		range_t(uint32_t l, uint32_t u, const tcmd_t *c)
			: lower(l), upper(u), cmd(c) {}
	};

	typedef std::vector<range_t> arc_t;
	typedef std::map<size_t, arc_t> arcs_t;
	typedef arc_t::const_iterator citer_t;

	arcs_t arcs;
	size_t rule;
	const tcmd_t *cmd;

	Node();
	void init(const dfa_state_t *s, const charset_t &cs, size_t nil);
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
	size_t defrule;
	const std::valarray<Rule> &rules;
	const std::valarray<Tag> &tags;

	Skeleton(const dfa_t &dfa, const charset_t &cs, size_t def,
		const std::string &dfa_name, const std::string &dfa_cond,
		uint32_t dfa_line);
	~Skeleton ();
	FORBID_COPY(Skeleton);
};

template<typename key_t> key_t rule2key(size_t r, size_t def)
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

size_t rule2key(size_t rule, size_t key, size_t def);
uint32_t maxpath(const Skeleton &skel);
void warn_undefined_control_flow(const Skeleton &skel);
void fprint_default_path(FILE *f, const Skeleton &skel, const path_t &p);
void emit_data(const Skeleton &skel);
void emit_prolog(OutputFile & o);
void emit_start(OutputFile &o, size_t maxfill, const std::string &name,
	size_t sizeof_key, size_t def, bool backup, bool accept, bool oldstyle_ctxmarker,
	const std::set<std::string> &tagnames, const std::set<std::string> &tagvars);
void emit_end(OutputFile &o, const std::string &name, bool backup, bool oldstyle_ctxmarker);
void emit_epilog(OutputFile &o, const std::set<std::string> &names);
void emit_action(OutputFile &o, uint32_t ind, const std::string &name, size_t key, size_t def, size_t rule);

} // namespace re2c

#endif // _RE2C_IR_SKELETON_SKELETON_
