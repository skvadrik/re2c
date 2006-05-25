/* read.c
 * Scott Bronson
 * 28 Dec 2004
 *
 * Version VERSION
 */


/**
 * @file read.c
 *
 * Defines functions intended to be used by read routines.
 */

#include <string.h>
#include <assert.h>
#include "scan.h"



/** Rearrange the scan buffer.  Only called by readprocs.
 *
 * This moves all in-flight data to the bottom of the buffer
 * to free up more room.
 *
 * Your readproc should read as much as it can between ss->limit
 * and ss->buf+ss->bufsiz.  It should adjust ss->limit to point
 * to the new end of data (the end of the buffer if it was able to
 * execute a complete read).
 *
 * Returns the number of bytes available to read in the buffer.
 */

/* TODO: could optimize for the fast case (no data that needs
 * to be shifted).  However, there's no burning need -- it wouldn't
 * offer much speedup  Bigger buffers would help a lot more.
 * NOTE: the middle line of this macro is incomplete!  Don't use!

#define read_shiftbuf(ss) (ss->token == ss->limit ? \
    (ss->token = ss->cursor = ss->bufptr, 0) : \
    _read_shiftbuf(ss)) 

 */


// cnt tells how many bytes need to be shifted downward.
// The bytes that need to be shifted are those between the token
// and the limit.

ssize_t read_shiftbuf(scanstate *ss)
{
    const char *min;
    ssize_t cnt;

    min = ss->token;
    if(ss->marker && ss->marker < min) {
        min = ss->marker;
    }

    // this tells how many bytes need to be shifted.
    cnt = ss->limit - min;
    if(cnt) {
        ssize_t delta = min - ss->bufptr;
        memmove((void*)ss->bufptr, min, cnt);
        ss->cursor -= delta;
        ss->token -= delta;
        if(ss->marker) ss->marker -= delta;
        ss->limit -= delta;

        assert(ss->limit >= ss->bufptr);
        assert(ss->cursor >= ss->bufptr);
        assert(ss->cursor <= ss->limit);
    } else {
        // nothing to shift so we reset the buffer to maximum size.
        ss->cursor = ss->bufptr;
        ss->token = ss->bufptr;
        if(ss->marker)  ss->marker = ss->bufptr;
        ss->limit = ss->bufptr;
    }

    return ss->bufsiz - (ss->limit - ss->bufptr);
}

