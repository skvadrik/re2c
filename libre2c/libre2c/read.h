/* read.h
 * Scott Bronson
 * 27 Dec 2004
 *
 * Version VERSION
 */

/** @file read.h
 *
 * Defines utilities intended to be used by ::readproc routines.
 */


#ifndef R2READ_H
#define R2READ_H

#include "scan.h"


/** Removes obsolete data from the front of the scan buffer to
 *  make room for new data added to the back.
 *
 *  @param ss The scanner whose buffer you want to modify.
 *  @returns The number of bytes available at the end of the
 *  	buffer that can accept data.
 */

ssize_t read_shiftbuf(scanstate *ss);

#endif

