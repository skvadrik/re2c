#include <stdio.h>
#include <stdarg.h>

#include "src/util/c99_stdint.h"
#include "regex.h"


int test(const char *pattern, const char *string, size_t nmatch, ...)
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

    va_list vl;
    va_start(vl, nmatch);

    for (uint32_t i = 0; i < nmatch; ++i) {
        regoff_t so = va_arg(vl, regoff_t);
        regoff_t eo = va_arg(vl, regoff_t);
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
    va_end(vl);
    regfree(&re);
    delete[] pmatch;

    return result;
}

int main()
{
    int err = 0;

    err |= test("a",        "a",    1, 0,1);
    err |= test("(a)",      "a",    2, 0,1, 0,1);
    err |= test("(a*)",     "aaa",  2, 0,3, 0,3);
    err |= test("(a*)(b*)", "aabb", 3, 0,4, 0,2, 2,4);
    err |= test("(a*)(a*)", "aa",   3, 0,2, 0,2, 2,2);

    return err;
}
