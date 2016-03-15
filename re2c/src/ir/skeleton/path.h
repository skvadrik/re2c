#ifndef _RE2C_IR_SKELETON_PATH_
#define _RE2C_IR_SKELETON_PATH_

#include "src/util/c99_stdint.h"
#include <vector>

#include "src/ir/skeleton/skeleton.h"

namespace re2c
{

class path_t
{
	std::vector<Node*> arcs;

public:
	explicit path_t(Node *n) : arcs()
	{
		arcs.push_back(n);
	}
	path_t(const path_t &p) : arcs(p.arcs) {}
	path_t &operator=(const path_t &p)
	{
		new (this) path_t(p);
		return *this;
	}
	size_t len() const
	{
		return arcs.size() - 1;
	}
	size_t len_matching () const
	{
		std::vector<Node*>::const_reverse_iterator
			tail = arcs.rbegin(),
			head = arcs.rend();
		for (; tail != head; ++tail) {
			RuleInfo *rule = (*tail)->rule;
			if (rule == NULL) {
				continue;
			}
			const size_t len = static_cast<size_t>(head - tail) - 1;
			switch (rule->ctx_len) {
				case 0:
					return len;
				case ~0u:
					for (; tail != head; ++tail) {
						if ((*tail)->ctx) {
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
	rule_rank_t match() const
	{
		std::vector<Node*>::const_reverse_iterator
			tail = arcs.rbegin(),
			head = arcs.rend();
		for (; tail != head; ++tail) {
			RuleInfo *rule = (*tail)->rule;
			if (rule != NULL) {
				return rule->rank;
			}
		}
		return rule_rank_t::none();
	}
	const Node::arc_t& arc(size_t i) const
	{
		return arcs[i]->arcs[arcs[i + 1]];
	}
	const Node::arcset_t& arcset(size_t i) const
	{
		return arcs[i]->arcsets[arcs[i + 1]];
	}
	void push(Node *n)
	{
		arcs.push_back(n);
	}
	void pop()
	{
		arcs.pop_back();
	}
	void append(const path_t *p)
	{
		assert(arcs.back() == p->arcs.front());
		arcs.insert(arcs.end(), p->arcs.begin() + 1, p->arcs.end());
	}
};

} // namespace re2c

#endif // _RE2C_IR_SKELETON_PATH_
