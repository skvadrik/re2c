#include "src/conf/msg.h"
#include "src/ast/ast.h"

namespace re2c {

void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules, Scanner &input)
{
	if (mode == Scanner::Rules) {
		if (!rflag) {
			input.fatal("found 'rules:re2c' block without -r flag");
		} else if (rules) {
			input.fatal("cannot have a second 'rules:re2c' block");
		}
	} else if (mode == Scanner::Reuse) {
		if (!rflag) {
			input.fatal("found 'use:re2c' block without -r flag");
		} else if (!rules) {
			input.fatal("got 'use:re2c' without 'rules:re2c'");
		}
	} else if (rflag) {
		input.fatal("found standard 're2c' block while using -r flag");
	}
}

void validate_ast(const specs_t &specs, bool cflag)
{
	specs_t::const_iterator i,
		b = specs.begin(),
		e = specs.end();

	for (i = b; i != e; ++i) {
		if (i->defs.size() > 1) {
			error("line %u: code to default rule %sis already defined at line %u",
				i->defs[1]->fline, incond(i->name).c_str(), i->defs[0]->fline);
			exit(1);
		}
	}

	if (!cflag) {
		for (i = b; i != e; ++i) {
			if (i->name != "") {
				error("line %u: conditions are only allowed"
					" with '-c', '--conditions' option",
					i->rules[0].code->fline);
				exit(1);
			}
		}
	} else {
		for (i = b; i != e; ++i) {
			if (i->name == "") {
				error("line %u: non-conditional rules are not allowed"
					" with '-c', '--conditions' option",
					i->rules[0].code->fline);
				exit(1);
			}
		}

		for (i = b; i != e; ++i) {
			if (i->setup.size() > 1) {
				error("line %u: code to setup rule '%s' is already defined at line %u",
					i->setup[1]->fline, i->name.c_str(), i->setup[0]->fline);
				exit(1);
			}
		}

		for (i = b; i != e; ++i) {
			if (i->name != "*" && !i->setup.empty() && i->rules.empty()) {
				error("line %u: setup for non existing condition '%s' found",
					i->setup[0]->fline, i->name.c_str());
				exit(1);
			}
		}

		for (i = b; i != e && !i->setup.empty(); ++i);
		if (i == e) {
			for (i = b; i != e; ++i) {
				if (i->name == "*") {
					error("line %u: setup for all conditions '<!*>' is illegal "
						"if setup for each condition is defined explicitly",
						i->setup[0]->fline);
					exit(1);
				}
			}
		}

		for (i = b; i != e; ++i) {
			if (i->name == "0" && i->rules.size() > 1) {
				error("line %u: startup code is already defined at line %u",
					i->rules[1].code->fline, i->rules[0].code->fline);
				exit(1);
			}
		}
	}
}

} // namespace re2c
