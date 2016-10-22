#ifndef _RE2C_IR_SKELETON_PATH_
#define _RE2C_IR_SKELETON_PATH_

#include "src/util/c99_stdint.h"
#include <vector>

#include "src/ir/skeleton/skeleton.h"

namespace re2c
{

struct suffix_t
{
	bool init;

private:
	std::vector<size_t> arcs;

public:

	suffix_t(): init(false), arcs() {}
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
			const Node &node = skel.nodes[*tail];
			if (node.rule == Rule::NONE) continue;

			size_t len = static_cast<size_t>(head - tail) - 1;
			const size_t trail = node.trail;
			if (trail == Tag::NONE) return len;

			const Tag &tag = skel.tags[trail];
			if (tag.type == Tag::FIX) {
				return len - tag.fix.dist;
			} else {
				for (; tail != head; ++tail) {
					if (skel.tagpool[skel.nodes[*tail].tags][trail] == node.trver) {
						return static_cast<size_t>(head - tail) - 1;
					}
				}
				assert(false);
			}
		}
		return 0;
	}
	size_t match(const Skeleton &skel) const
	{
		std::vector<size_t>::const_reverse_iterator
			tail = arcs.rbegin(),
			head = arcs.rend();
		for (; tail != head; ++tail) {
			const size_t rule = skel.nodes[*tail].rule;
			if (rule != Rule::NONE) {
				return rule;
			}
		}
		return Rule::NONE;
	}
	const Node::arc_t& arc(const Skeleton &skel, size_t i) const
	{
		return skel.nodes[arcs[i]].arcs.find(arcs[i + 1])->second;
	}
	const Node::arcset_t& arcset(const Skeleton &skel, size_t i) const
	{
		return skel.nodes[arcs[i]].arcsets.find(arcs[i + 1])->second;
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
