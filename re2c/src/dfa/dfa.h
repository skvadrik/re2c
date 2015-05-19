#ifndef __DFA__
#define __DFA__

#include "src/dfa/action.h"
#include "src/dfa/state.h"
#include "src/util/forbid_copy.h"
#include "src/util/smart_ptr.h"

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
	bool bSaveOnHead;
	accept_t accept_map;

public:
	DFA (Ins *, uint32_t, uint32_t, uint32_t, const Char *);
	~DFA ();
	void addState (State **, State *);
	State * findState (Ins **, uint32_t);
	void split (State *);

	void findSCCs ();
	void findBaseState ();
	void prepare (uint32_t &);
	void emit (Output &, uint32_t &, const RegExpMap *, const std::string &, bool, bool &);

	friend std::ostream & operator << (std::ostream &, const DFA &);

	FORBID_COPY (DFA);
};

smart_ptr<DFA> genCode (RegExp *, Output &, uint32_t);

} // namespace re2c

#endif // __DFA__
