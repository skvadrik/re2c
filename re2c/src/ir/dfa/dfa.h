#ifndef _RE2C_IR_DFA_DFA_
#define _RE2C_IR_DFA_DFA_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>

#include "src/ir/dfa/action.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/rules.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Skeleton;
class State;
class label_t;
struct Output;
struct OutputFile;
union Ins;

class DFA
{
	accept_t accepts;
	Skeleton * skeleton;

public:
	std::string name;
	const std::string cond;
	const uint32_t line;

	uint32_t lbChar;
	uint32_t ubChar;
	uint32_t nStates;
	State * head;
	State ** tail;
	State * toDo;
	const Ins * free_ins;

	// statistics
	uint32_t max_fill;
	bool need_backup;
	bool need_backupctx;
	bool need_accept;

public:
	DFA
		( const std::string &
		, uint32_t
		, Ins *
		, uint32_t
		, uint32_t
		, uint32_t
		, const charset_t &
		, rules_t
		);
	~DFA ();
	void emit (Output &, uint32_t &, bool, bool &);

private:
	void addState (State **, State *);
	State * findState (Ins **, Ins **);
	void split (State *);
	void findSCCs ();
	void findBaseState ();
	void calc_stats ();
	void prepare ();
	void count_used_labels (std::set<label_t> & used, label_t prolog, label_t start, bool force_start) const;
	void emit_body (OutputFile &, uint32_t &, const std::set<label_t> & used_labels, label_t initial) const;

	FORBID_COPY (DFA);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_DFA_
