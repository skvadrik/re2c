/*
Copyright (c) 2013, Emcien Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_LINE_LENGTH 4096

char inbuffer[MAX_LINE_LENGTH];

%%{
    machine parser;

    # Registers the mark action, but delegates its implementation to the host 
    # language
    action mark { mark(); }

    # Define the various components of a log entry
    #
    # > and % denote entering and leaving actions respectively, so this machine
    #   will mark and emit each of the following token types as it sees them
    host    = [0-9\.]+       >mark %{ emit(1, "host");    };
    user    = alpha+         >mark %{ emit(1, "user");    };
    date    = [^\]]+         >mark %{ emit(1, "date");    };
    request = [^"]+          >mark %{ emit(1, "request"); };
    status  = digit+         >mark %{ emit(1, "status");  };
    size    = (digit+ | '-') >mark %{ emit(1, "size");    };
    url     = [^"]*          >mark %{ emit(1, "url");     };
    agent   = [^"]*          >mark %{ emit(0, "agent");   };

    # Assemble the components to define a single line
    line = (
        host            space
        '-'             space
        '-'             space
        '[' date ']'    space
        '"' request '"' space
        status          space
        size            space
        '"' url '"'     space
        '"' agent '"'   '\n'
    );

    # Instantiate the machine
    main := line;

    # Write the state transitions for the instantiated machine
    write data;
}%%

// Ragel-exposed variables
int cs;
char *p, *pe, *ts;

// Marks the start of the last-seen token
static inline void mark() { ts = p; }

// Defines what to do when we finish consuming a token
// In this case, we format it as JSON and write it to a buffer containing the
// partially-constructed object corresponding to the current line
static inline void emit(int comma, const char *type) {
    *p = '\0';
    fputc('"', stdout);
    fputs(type, stdout);
    fputs("\":\"", stdout);
    fputs(ts, stdout);
    fputs(comma ? "\"," : "\"", stdout);
}

int main(int argc, char **argv) {
    PRE
    int lines = 0;

    fputc('[', stdout); // We're printing out a list objects. Here's the start.
    while(fgets(inbuffer, MAX_LINE_LENGTH, stdin) != NULL) {
        // Start writing the JSON object to the buffer 
        // Include a leading comma if we need to separate it from its predecessor
        fputs(lines ? ",\n{" : "{", stdout);

        // Set Ragel to read the contents of the buffer
        p  = inbuffer;
        pe = inbuffer + strlen(inbuffer);
        ts = p;

        // Setup and run the state machine
        // This will consume input from p to pe and call mark() and emit() as
        // specified in our machine definition
        %% write init;
        %% write exec;

        fputs("}", stdout);
        lines ++;
    }
    fputs("\n]\n", stdout);

    POST
    return 0;
}
