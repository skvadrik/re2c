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

	virtual void emit(Output &, uint, bool&, const std::string&) const = 0;
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
	void emit(Output &, uint, bool&, const std::string&) const;
};

class Initial: public Action
{
public:
	uint	label;
	bool setMarker;

public:
	Initial(State*, uint, bool);
	void emit(Output &, uint, bool&, const std::string&) const;
};

class Save: public Match
{

public:
	uint	selector;

public:
	Save(State*, uint);
	void emit(Output &, uint, bool&, const std::string&) const;
};

class Move: public Action
{

public:
	Move(State*);
	void emit(Output &, uint, bool&, const std::string&) const;
};

class Accept: public Action
{

public:
	typedef std::map<uint, State*> RuleMap;

	uint	nRules;
	uint	*saves;
	State	**rules;
	RuleMap mapRules;

public:
	Accept(State*, uint, uint*, State**);
	void emit(Output &, uint, bool&, const std::string&) const;
	void emitBinary(OutputFile & o, uint ind, uint l, uint r, bool &readCh) const;
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
	void emit(Output &, uint, bool&, const std::string&) const;

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
	uint	label;
	RuleOp	*rule;
	State	*next;
	State	*link;
	uint	depth;		// for finding SCCs
	uint	kCount;
	Ins 	**kernel;

	bool    isPreCtxt;
	bool    isBase;
	bool    generated;
	Go      go;
	Action  *action;

public:
	State();
	~State();
	void emit(Output &, uint, bool&, const std::string&) const;
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
		, generated(oth.generated)
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
	uint	lbChar;
	uint	ubChar;
	uint	nStates;
	State	*head, **tail;
	State	*toDo;
	const Ins     *free_ins;
	const Char    *free_rep;

protected:
	bool    bSaveOnHead;
	uint    *saves;
	State   **rules;

public:
	DFA(Ins*, uint, uint, uint, const Char*);
	~DFA();
	void addState(State**, State*);
	State *findState(Ins**, uint);
	void split(State*);

	void findSCCs();
	void findBaseState();
	void prepare(uint &);
	void output_skeleton_prolog (OutputFile & o, uint ind);
	void output_skeleton_epilog (OutputFile & o, uint ind);
	void emit(Output &, uint&, const RegExpMap*, const std::string&, bool, bool&);

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

inline Initial::Initial(State *s, uint l, bool b) : Action(s), label(l), setMarker(b)
{
	type = INITIAL;
}

inline Save::Save(State *s, uint i) : Match(s), selector(i)
{
	type = SAVE;
}

inline Move::Move(State *s) : Action(s)
{
	type = MOVE;
}

inline Accept::Accept(State *x, uint n, uint *s, State **r)
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
