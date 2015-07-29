#include "config.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/globals.h"
#include "src/parse/parser.h"

namespace re2c
{

bool bUsedYYBitmap  = false;
bool bWroteGetState = false;
bool bWroteCondCheck = false;
uint32_t last_fill_index = 0;
CodeNames mapCodeName;
free_list<RegExp*> RegExp::vFreeList;

} // end namespace re2c

using namespace re2c;

int main(int argc, char *argv[])
{
	Opt opts;
	switch (parse_opts (argc, argv, opts))
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
	re2c::Output output (opts.output_file, opts.header_file);
	if (!output.source.open ())
	{
		error ("cannot open output file: %s", opts.output_file);
		return 1;
	}
	if (tFlag && !output.header.open ())
	{
		error ("cannot open header file: %s", opts.header_file);
		return 1;
	}
	if (flag_skeleton && !output.data.open ())
	{
		error ("cannot open data file: %s", output.data.file_name.c_str ());
		return 1;
	}

	Scanner scanner (input, output.source);
	parse (scanner, output);

	return warn.error () ? 1 : 0;
}
