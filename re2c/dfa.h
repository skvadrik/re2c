/* $Id$ */
#ifndef _dfa_h
#define _dfa_h

#include <iosfwd>
#include <map>

#include "go.h"
#include "re.h"

namespace re2c
{

class DFA;

class State;

class Action
{

public:
	State	*state;
	enum type_t
	{
		NONE,
		MATCH,
		INITIAL,
		SAVE,
		MOVE,
		ACCEPT,
		RULE
	} type;

public:
	Action(State*);
	virtual ~Action();

	virtual void emit(Output &, uint32_t, bool&, const std::string&) const = 0;
	virtual bool readAhead() const;

#ifdef PEDANTIC
protected:
	Action(const Action& oth)
		: state(oth.state)
		, type(oth.type)
	{
	}
	Action& operator = (const Action& oth)
	{
		state = oth.state;
		type = oth.type;
		return *this;
	}
#endif
};

class Match: public Action
{
public:
	Match(State*);
	void emit(Output &, uint32_t, bool&, const std::string&) const;
};

class Initial: public Action
{
public:
	uint32_t	label;
	bool setMarker;

public:
	Initial(State*, uint32_t, bool);
	void emit(Output &, uint32_t, bool&, const std::string&) const;
};

class Save: public Match
{

public:
	uint32_t	selector;

public:
	Save(State*, uint32_t);
	void emit(Output &, uint32_t, bool&, const std::string&) const;
};

class Move: public Action
{

public:
	Move(State*);
	void emit(Output &, uint32_t, bool&, const std::string&) const;
};

class Accept: public Action
{

public:
	typedef std::map<uint32_t, State*> RuleMap;

	uint32_t	nRules;
	uint32_t	*saves;
	State	**rules;
	RuleMap mapRules;

public:
	Accept(State*, uint32_t, uint32_t*, State**);
	void emit(Output &, uint32_t, bool&, const std::string&) const;
	void emitBinary(OutputFile & o, uint32_t ind, uint32_t l, uint32_t r, bool &readCh) const;
	void genRuleMap();

#ifdef PEDANTIC
private:
	Accept(const Accept& oth)
		: Action(oth)
		, nRules(oth.nRules)
		, saves(oth.saves)
		, rules(oth.rules)
	{
	}
	Accept& operator=(const Accept& oth)
	{
		new(this) Accept(oth);
		return *this;
	}
#endif
};

class Rule: public Action
{

public:
	RuleOp	*rule;

public:
	Rule(State*, RuleOp*);
	void emit(Output &, uint32_t, bool&, const std::string&) const;

#ifdef PEDANTIC
private:
	Rule (const Rule& oth)
		: Action(oth)
		, rule(oth.rule)
	{
	}
	Rule& operator=(const Rule& oth)
	{
		new(this) Rule(oth);
		return *this;
	}
#endif
};

class State
{

public:
	uint32_t	label;
	RuleOp	*rule;
	State	*next;
	State	*link;
	uint32_t	depth;		// for finding SCCs
	uint32_t	kCount;
	Ins 	**kernel;

	bool    isPreCtxt;
	bool    isBase;
	Go      go;
	Action  *action;

public:
	State();
	~State();
	void emit(Output &, uint32_t, bool&, const std::string&) const;
	friend std::ostream& operator<<(std::ostream&, const State&);
	friend std::ostream& operator<<(std::ostream&, const State*);

#ifdef PEDANTIC
private:
	State(const State& oth)
		: label(oth.label)
		, rule(oth.rule)
		, next(oth.next)
		, link(oth.link)
		, depth(oth.depth)
		, kCount(oth.kCount)
		, kernel(oth.kernel)
		, isBase(oth.isBase)
		, go(oth.go)
		, action(oth.action)
	{
	}
	State& operator = (const State& oth)
	{
		new(this) State(oth);
		return *this;
	}
#endif
};

class DFA
{

public:
	uint32_t	lbChar;
	uint32_t	ubChar;
	uint32_t	nStates;
	State	*head, **tail;
	State	*toDo;
	const Ins     *free_ins;
	const Char    *free_rep;

protected:
	bool    bSaveOnHead;
	uint32_t    *saves;
	State   **rules;

public:
	DFA(Ins*, uint32_t, uint32_t, uint32_t, const Char*);
	~DFA();
	void addState(State**, State*);
	State *findState(Ins**, uint32_t);
	void split(State*);

	void findSCCs();
	void findBaseState();
	void prepare(uint32_t &);
	void emit(Output &, uint32_t&, const RegExpMap*, const std::string&, bool, bool&);

	friend std::ostream& operator<<(std::ostream&, const DFA&);
	friend std::ostream& operator<<(std::ostream&, const DFA*);

#ifdef PEDANTIC
	DFA(const DFA& oth)
		: lbChar(oth.lbChar)
		, ubChar(oth.ubChar)
		, nStates(oth.nStates)
		, head(oth.head)
		, tail(oth.tail)
		, toDo(oth.toDo)
	{
	}
	DFA& operator = (const DFA& oth)
	{
		new(this) DFA(oth);
		return *this;
	}
#endif
};

inline Action::Action(State *s) : state(s), type(NONE)
{
	delete s->action;
	s->action = this;
}

inline Action::~Action()
{
}

inline bool Action::readAhead() const
{
	return (type != MATCH) || (state && state->next && state->next->action && (state->next->action->type != RULE));
}

inline Match::Match(State *s) : Action(s)
{
	type = MATCH;
}

inline Initial::Initial(State *s, uint32_t l, bool b) : Action(s), label(l), setMarker(b)
{
	type = INITIAL;
}

inline Save::Save(State *s, uint32_t i) : Match(s), selector(i)
{
	type = SAVE;
}

inline Move::Move(State *s) : Action(s)
{
	type = MOVE;
}

inline Accept::Accept(State *x, uint32_t n, uint32_t *s, State **r)
		: Action(x), nRules(n), saves(s), rules(r)
{
	type = ACCEPT;
}

inline Rule::Rule(State *s, RuleOp *r) : Action(s), rule(r)
{
	type = RULE;
}

inline std::ostream& operator<<(std::ostream &o, const State *s)
{
	return o << *s;
}

inline std::ostream& operator<<(std::ostream &o, const DFA *dfa)
{
	return o << *dfa;
}

} // end namespace re2c

#endif
