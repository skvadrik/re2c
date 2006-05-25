/* readrand.h
 * Scott Bronson
 * 6 Mar 2006
 *
 * Version VERSION
 *
 * This reader feeds an re2c scanner with a pseudo-endless
 * stream of random binary data.
 */


#include "read.h"


/**
 * Causes the scanner to read a pseudorandom stream of bytes.
 * 
 * This readproc will never return EOF.  You need to use another
 * technique to determine when to stop reading.
 *
 * @param ss The scanner to feed.
 * @param seed The random seed to use.  The same seed is guaranteed
 * to always produce the same stream of bytes (see rand_r(3) for
 * details).
 */

scanstate* readrand_attach(scanstate *ss, int seed);

