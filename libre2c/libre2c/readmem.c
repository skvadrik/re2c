/* re2c.c
 * Scott Bronson
 * 28 Dec 2004
 *
 * Version VERSION
 *
 * Shows how to scan from an in-memory buffer.  We ignore the buffer
 * and scan directly out of the string.  The read proc
 * just returns eof when the scanner hits the end of the string.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readmem.h"


/** Returns EOF because we're out of data.
 */

static ssize_t readmem_read(scanstate *ss)
{
    return 0;
}


/** Initializes the given scanstate to read from the given string.
 */

scanstate* readmem_init(scanstate *ss, const char *data, size_t len)
{
    scanstate_init(ss, data, len);
    ss->limit = ss->bufptr + ss->bufsiz;
    ss->read = readmem_read;
    return ss;
}


/** Attaches the scanner to the given string.  Use this
 * if you've already malloc'd a scanstate.  It calls scanstate_init
 * so it will blow everything already in the scanstate away.
 *
 * TODO: this is unlike all other attach routines, none of whom
 * blow away the scanstate.  CHANGE THIS.
 */

scanstate* readmem_attach(scanstate *ss, const char *data, size_t len)
{
    // ensure we don't stomp on a pre-existing buffer
    if(ss->bufsiz) {
        return NULL;
    }

    return readmem_init(ss, data, len);
}

