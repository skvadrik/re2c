#ifndef _input_h
#define _input_h

#include "stdio.h"
#include <string>

namespace re2c {

struct Input
{
	enum status_t
		{ OK
		, FAIL_OPEN
		} status;
	FILE * file;
	std::string file_name;

	Input (const char * fn);
	~Input ();
};

} // namespace re2c

#endif // _input_h
