#ifndef _input_h
#define _input_h

#include "stdio.h"
#include <string>

namespace re2c {

struct Input
{
	FILE * file;
	std::string file_name;

	Input (const char * fn);
	~Input ();
	bool open ();
};

} // namespace re2c

#endif // _input_h
