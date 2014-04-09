#ifndef _print_h
#define _print_h

#include <iosfwd>

#include "basics.h"

namespace re2c
{

void prtCh(std::ostream&, uint);
void prtHex(std::ostream&, uint);
void prtChOrHex(std::ostream&, uint);
void printSpan(std::ostream&, uint, uint);

} // end namespace re2c

#endif
