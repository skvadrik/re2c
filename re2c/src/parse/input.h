#ifndef _input_h
#define _input_h

#include <stdio.h>
#include <string>

#include "src/util/forbid_copy.h"

namespace re2c {

struct Input
{
	FILE * file;
	std::string file_name;

	Input (const char * fn);
	~Input ();
	bool open ();

	FORBID_COPY (Input);
};

} // namespace re2c

#endif // _input_h
