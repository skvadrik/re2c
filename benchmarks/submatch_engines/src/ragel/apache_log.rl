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

    action mark { q = p; }

    host    = [0-9\.]+       > mark % { outstr(out, "{\"host\":\"");      outs(out, q, p); };
    user    = alpha+         > mark % { outstr(out, "\",\"user\":\"");    outs(out, q, p); };
    date    = [^\]]+         > mark % { outstr(out, "\",\"date\":\"");    outs(out, q, p); };
    request = [^"]+          > mark % { outstr(out, "\",\"request\":\""); outs(out, q, p); };
    status  = digit+         > mark % { outstr(out, "\",\"status\":\"");  outs(out, q, p); };
    size    = (digit+ | '-') > mark % { outstr(out, "\",\"size\":\"");    outs(out, q, p); };
    url     = [^"]*          > mark % { outstr(out, "\",\"url\":\"");     outs(out, q, p); };
    agent   = [^"]*          > mark % { outstr(out, "\",\"agent\":\"");   outs(out, q, p); };

    line =
        host            space
        '-'             space
        '-'             space
        '[' date ']'    space
        '"' request '"' space
        status          space
        size            space
        '"' url '"'     space
        '"' agent '"'
        [\n] > { outstr(out, "\"},\n"); }
        ;

    main := line*;

    write data;
}%%

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
    char *q;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
