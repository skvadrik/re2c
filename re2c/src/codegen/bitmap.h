#ifndef _RE2C_CODEGEN_BITMAP_
#define _RE2C_CODEGEN_BITMAP_

#include "src/util/c99_stdint.h"
#include <vector>

#include "src/util/forbid_copy.h"

namespace re2c {

struct Go;
struct Span;
struct State;
class OutputFile;

struct bitmap_t
{
	const Go *go;
	const State *on;
	uint32_t i;
	uint32_t m;
};

class bitmaps_t
{
	typedef std::vector<bitmap_t> maps_t;
	typedef maps_t::reverse_iterator riter_t;
	typedef maps_t::const_reverse_iterator rciter_t;

	maps_t maps;
	uint32_t ncunit;
	uint32_t *buffer;

public:
	bool used;

	explicit bitmaps_t(uint32_t n);
	~bitmaps_t();
	void insert(const Go *go, const State *s);
	const bitmap_t *find(const Go *go, const State *s) const;
	bool empty() const;
	void gen(OutputFile &o, uint32_t ind);
	FORBID_COPY(bitmaps_t);
};

} // namespace re2c

#endif // _RE2C_CODEGEN_BITMAP_
