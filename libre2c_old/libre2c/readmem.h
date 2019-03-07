/* re2c-mem.c
 * Scott Bronson
 * 30 Dec 2004
 *
 * Version VERSION
 *
 * Allows you to feed an re2c scanner from a memory block.
 */

#include "read.h"


scanstate* readmem_init(scanstate *ss, const char *data, size_t len);
scanstate* readmem_attach(scanstate *ss, const char *data, size_t len);


/**
 * Initializes a readmem from a C string.  The string must exist for
 * as long as the scanner -- the scanner doesn't make a copy.
 */

#define readmem_init_str(ss,str) readmem_init(ss,str,strlen(str))
