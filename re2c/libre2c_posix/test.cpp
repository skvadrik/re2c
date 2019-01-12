#include <stdio.h>

#include "src/util/c99_stdint.h"
#include "regex.h"


static int test(const char *pattern, const char *string
    , size_t nmatch, const regoff_t *submatch)
{
    regex_t re;
    regmatch_t *pmatch = new regmatch_t[nmatch];
    int result;

    result = regcomp(&re, pattern, 0);
    if (result != 0) {
        fprintf(stderr, "regcomp() failed for RE %s\n", pattern);
        goto end;
    }

    result = regexec(&re, string, nmatch, pmatch, 0);
    if (result != 0) {
        fprintf(stderr, "regexec() failed for RE %s and string %s\n"
            , pattern, string);
        goto end;
    }

    for (uint32_t i = 0; i < nmatch; ++i) {
        regoff_t so = submatch[2 * i];
        regoff_t eo = submatch[2 * i + 1];
        const regmatch_t &have = pmatch[i];

        if (so != have.rm_so || eo != have.rm_eo) {
            result = 1;
            fprintf(stderr, "incorrect submatch for RE %s and string %s:\n"
                "\tpmatch[%u].rm_so = %ld (expected %ld)\n"
                "\tpmatch[%u].rm_eo = %ld (expected %ld)\n"
                , pattern, string
                , i, have.rm_so, so
                , i, have.rm_eo, eo);
            goto end;
        }
    }

end:
    regfree(&re);
    delete[] pmatch;

    return result;
}

int main()
{
    int e = 0;

    // poor man's replacement for C++11 initializer lists :)
#define GS                              static const regoff_t gs[]
#define T1(r,s,a,b)                     { GS = {a,b};                     T(r,s,gs); }
#define T2(r,s,a,b,c,d)                 { GS = {a,b,c,d};                 T(r,s,gs); }
#define T3(r,s,a,b,c,d,e,f)             { GS = {a,b,c,d,e,f};             T(r,s,gs); }
#define T4(r,s,a,b,c,d,e,f,g,h)         { GS = {a,b,c,d,e,f,g,h};         T(r,s,gs); }
#define T5(r,s,a,b,c,d,e,f,g,h,i,j)     { GS = {a,b,c,d,e,f,g,h,i,j};     T(r,s,gs); }
#define T6(r,s,a,b,c,d,e,f,g,h,i,j,k,l) { GS = {a,b,c,d,e,f,g,h,i,j,k,l}; T(r,s,gs); }
#define T(r,s,gs) { \
    e |= test(r,s,sizeof(gs)/sizeof(gs[0])/2,gs); \
}

    T1("a",        "a",    0,1);
    T2("(a)",      "a",    0,1, 0,1);
    T2("(a*)",     "aaa",  0,3, 0,3);
    T3("(a*)(b*)", "aabb", 0,4, 0,2, 2,4);
    T3("(a*)(a*)", "aa",   0,2, 0,2, 2,2);

#undef T
#undef T1
#undef T2
#undef T3
#undef T4
#undef T5
#undef T6

    return e;
}
