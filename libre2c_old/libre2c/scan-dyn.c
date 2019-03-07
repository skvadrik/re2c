/* scan-dyn.c
 * Scott Bronson
 * 28 Dec 2004
 *
 * Version VERSION
 *
 * Routines to dynamically allocate and free scanners and their buffers.
 * The scanner will be initialized, but you still need to attach
 * it to a particular type of reader.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "scan-dyn.h"

/** Allocate a scanstate data structure and its associated buffer.
 * Ensure the buffer is large enough to hold the longest token.
 * Pass 0 for bufsiz if you don't want to allocate a buffer
 * (i.e. you're scanning from a contiguous memory block).
 * Ensure you call dynscan_free() when you're done with the scanner.
 */

/** Dynamically allocates a new scanstate data structure
 *
 * Allocates a buffer of the given size for the scanner using malloc.
 * Note that the size is an int: the number of bytes in the buffer
 * must fit into a signed integer on the current architecture.
 * Returns the new scanstate or NULL if there was a memory allocation problem.
 *
 * Remember to call dynscan_free() when you're done scanning.
 */

scanstate* dynscan_create(size_t bufsiz)
{
    scanstate *ss;
    char *bufptr;
    
    ss = malloc(sizeof(scanstate));
    if(!ss) {
        return NULL;
    }

    if(bufsiz) {
        bufptr = malloc(bufsiz);
        if(!bufptr) {
            free(ss);
            return NULL;
        }
    } else {
        bufptr = 0;
    }

    scanstate_init(ss, bufptr, bufsiz);
    return ss;
}


/** Frees a scanstate allocated by dynscan_create().
 */

void dynscan_free(scanstate *ss)
{
    if(ss->bufptr) {
        free((void*)ss->bufptr);
    }

    free(ss);
}

