/* scan-dyn.h
 * Scott Bronson
 * 30 Dec 2004
 *
 * Version VERSION
 *
 * Creates a scanner entirely located on the heap.  You must make
 * sure to eventually call dynscan_free for every scanner created
 * with dynscan_create.
 */

#include "scan.h"


scanstate* dynscan_create(size_t bufsiz);
void dynscan_free(scanstate *ss);

