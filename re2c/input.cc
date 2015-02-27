#include "input.h"

namespace re2c {

Input::Input (const char * fn)
	: status (OK)
	, file (NULL)
	, file_name (fn)
{
	if (file_name == "<stdin>")
	{
		file = stdin;
	}
	else
	{
		file = fopen (file_name.c_str (), "rb");
		if (file == NULL)
		{
			status = FAIL_OPEN;
		}
	}
}

Input::~Input ()
{
	if (file != NULL && file != stdin)
	{
		fclose (file);
	}
}

} // namespace re2c
