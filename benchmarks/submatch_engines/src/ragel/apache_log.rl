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

#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine parser;

    host    = [0-9\.]+;
    user    = alpha+;
    date    = [^\]]+;
    request = [^"]+;
    status  = digit+;
    size    = (digit+ | '-');
    url     = [^"]*;
    agent   = [^"]*;
    line    =
        host        >{ h1 = p; } %{ h2 = p; }     space
        '-'                                       space
        '-'                                       space
        '[' date    >{ d1 = p; } %{ d2 = p; } ']' space
        '"' request >{ r1 = p; } %{ r2 = p; } '"' space
        status      >{ s1 = p; } %{ s2 = p; }     space
        size        >{ z1 = p; } %{ z2 = p; }     space
        '"' url     >{ l1 = p; } %{ l2 = p; } '"' space
        '"' agent   >{ a1 = p; } %{ a2 = p; } '"' [\n]
    >{
        outstr(out, "{\"host\":\"");
        outs(out, h1, h2);
        outstr(out, "\",\"date\":\"");
        outs(out, d1, d2);
        outstr(out, "\",\"request\":\"");
        outs(out, r1, r2);
        outstr(out, "\",\"status\":\"");
        outs(out, s1, s2);
        outstr(out, "\",\"size\":\"");
        outs(out, z1, z2);
        outstr(out, "\",\"url\":\"");
        outs(out, l1, l2);
        outstr(out, "\",\"agent\":\"");
        outs(out, a1, a2);
        outstr(out, "\"},\n");
    };

    main := line*;
}%%

%% write data;

static void prolog(Output *out)
{
    outc(out, '[');
}

static void epilog(Output *out)
{
    out->pos -= 2;
    outstr(out, "\n]\n");
}

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char *h1, *h2,
        *d1, *r1, *s1, *z1, *l1, *a1,
        *d2, *r2, *s2, *z2, *l2, *a2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
