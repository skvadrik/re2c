#include "src/util/c99_stdint.h"
#include <string>

#include "src/code/output.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/ast/input.h"
#include "src/ast/parser.h"
#include "src/ast/scanner.h"

using namespace re2c;

int main(int, char *argv[])
{
	Opt opts;
	Warn warn;

	switch (parse_opts(argv, opts, warn))
	{
		case OK:        break;
		case EXIT_OK:   return 0;
		case EXIT_FAIL: return 1;
	}

	// set up the source stream
	re2c::Input input (opts.source_file);
	if (!input.open ())
	{
		error ("cannot open source file: %s", opts.source_file);
		return 1;
	}

	// set up the output streams
	re2c::Output output(warn);

	Scanner scanner(input, output.source, opts);
	parse(scanner, output);
	if (!output.emit()) {
		return 1;
	}

	return warn.error () ? 1 : 0;
}
