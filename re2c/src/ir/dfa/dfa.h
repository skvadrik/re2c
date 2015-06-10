#ifndef _RE2C_IR_DFA_DFA_
#define _RE2C_IR_DFA_DFA_

#include "src/ir/dfa/action.h"
#include "src/ir/dfa/state.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

typedef std::map<std::string, std::pair<int, RegExp *> > RegExpMap;

class DFA
{
public:
	uint32_t lbChar;
	uint32_t ubChar;
	uint32_t nStates;
	State * head;
	State ** tail;
	State * toDo;
	const Ins * free_ins;
	const Char * free_rep;

protected:
	accept_t accepts;

public:
	DFA (Ins *, uint32_t, uint32_t, uint32_t, const Char *);
	~DFA ();
	void addState (State **, State *);
	State * findState (Ins **, uint32_t);
	void split (State *);

	void findSCCs ();
	void findBaseState ();
	void prepare (OutputFile & o, uint32_t &);
	void count_used_labels (std::set<label_t> & used, label_t prolog, label_t start, bool force_start) const;
	void emit (Output &, uint32_t &, const RegExpMap *, const std::string &, bool, bool &);

	friend std::ostream & operator << (std::ostream &, const DFA &);

	FORBID_COPY (DFA);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_DFA_
