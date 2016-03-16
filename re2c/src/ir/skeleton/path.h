#ifndef _RE2C_IR_SKELETON_PATH_
#define _RE2C_IR_SKELETON_PATH_

#include "src/util/c99_stdint.h"
#include <vector>

#include "src/ir/skeleton/skeleton.h"

namespace re2c
{

class suffix_t
{
	std::vector<size_t> arcs;

public:
	suffix_t() : arcs() {}
	void push(size_t i)
	{
		arcs.push_back(i);
	}
	friend class path_t;
};

class path_t
{
	std::vector<size_t> arcs;

public:
	explicit path_t(size_t i) : arcs()
	{
		arcs.push_back(i);
	}
	size_t len() const
	{
		return arcs.size() - 1;
	}
	size_t len_matching(const Skeleton &skel) const
	{
		std::vector<size_t>::const_reverse_iterator
			tail = arcs.rbegin(),
			head = arcs.rend();
		for (; tail != head; ++tail) {
			RuleInfo *rule = skel.nodes[*tail].rule;
			if (rule == NULL) {
				continue;
			}
			const size_t len = static_cast<size_t>(head - tail) - 1;
			switch (rule->ctx_len) {
				case 0:
					return len;
				case ~0u:
					for (; tail != head; ++tail) {
						if (skel.nodes[*tail].ctx) {
							return static_cast<size_t>(head - tail) - 1;
						}
					}
					assert(false);
				default:
					return len - rule->ctx_len;
			}
		}
		return 0;
	}
	rule_rank_t match(const Skeleton &skel) const
	{
		std::vector<size_t>::const_reverse_iterator
			tail = arcs.rbegin(),
			head = arcs.rend();
		for (; tail != head; ++tail) {
			RuleInfo *rule = skel.nodes[*tail].rule;
			if (rule != NULL) {
				return rule->rank;
			}
		}
		return rule_rank_t::none();
	}
	const Node::arc_t& arc(const Skeleton &skel, size_t i) const
	{
		return skel.nodes[arcs[i]].arcs[arcs[i + 1]];
	}
	const Node::arcset_t& arcset(const Skeleton &skel, size_t i) const
	{
		return skel.nodes[arcs[i]].arcsets[arcs[i + 1]];
	}
	void push(size_t n)
	{
		arcs.push_back(n);
	}
	void pop()
	{
		arcs.pop_back();
	}
	void push_sfx(const suffix_t &suffix)
	{
		arcs.insert(arcs.end(), suffix.arcs.rbegin(), suffix.arcs.rend());
	}
	void pop_sfx(const suffix_t &suffix)
	{
		arcs.resize(arcs.size() - suffix.arcs.size());
	}
	bool operator<(const path_t &p) const
	{
		const size_t
			s1 = arcs.size(),
			s2 = p.arcs.size();
		return (s1 == s2 && arcs < p.arcs)
			|| s1 < s2;
	}
};

} // namespace re2c

#endif // _RE2C_IR_SKELETON_PATH_
