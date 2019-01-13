#include <stdio.h>
#include <stdlib.h>

#include "libre2c_posix/regex.h"
#include "libre2c_posix/regex-impl.h"
#include "src/util/c99_stdint.h"


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
    if (result != 0 && nmatch > 0) {
        fprintf(stderr, "regexec() failed for RE %s and string %s\n"
            , pattern, string);
        goto end;
    }
    else if (result == 0 && nmatch == 0) {
        fprintf(stderr, "regexec() didn't fail while it should"
            " for RE %s and string %s\n", pattern, string);
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

// Poor man's replacement for C++11 initializer lists. :)
// Variadic macros are non-standard in c++98. Variadic functions have
// subtle problems with types: literals are 'int' by default, so passing
// 'long' as vararg requres suffix 'L', which is easy to forget and hard
// to notice (the problem is platform/toolchain-specific).
#define GS                                  static const regoff_t gs[]
#define T(r,s,gs)                           e |= test(r,s,sizeof(gs)/sizeof(gs[0])/2,gs);
#define T0(r,s)                             e |= test(r,s,0,NULL);
#define T1(r,s,a,b)                         { GS = {a,b};                         T(r,s,gs); }
#define T2(r,s,a,b,c,d)                     { GS = {a,b,c,d};                     T(r,s,gs); }
#define T3(r,s,a,b,c,d,e,f)                 { GS = {a,b,c,d,e,f};                 T(r,s,gs); }
#define T4(r,s,a,b,c,d,e,f,g,h)             { GS = {a,b,c,d,e,f,g,h};             T(r,s,gs); }
#define T5(r,s,a,b,c,d,e,f,g,h,i,j)         { GS = {a,b,c,d,e,f,g,h,i,j};         T(r,s,gs); }
#define T6(r,s,a,b,c,d,e,f,g,h,i,j,k,l)     { GS = {a,b,c,d,e,f,g,h,i,j,k,l};     T(r,s,gs); }
#define T7(r,s,a,b,c,d,e,f,g,h,i,j,k,l,m,n) { GS = {a,b,c,d,e,f,g,h,i,j,k,l,m,n}; T(r,s,gs); }

int main()
{
    int e = 0;

    T1("a",        "a",    0,1);
    T2("(a)",      "a",    0,1, 0,1);
    T2("(a*)",     "aaa",  0,3, 0,3);
    T3("(a*)(b*)", "aabb", 0,4, 0,2, 2,4);
    T3("(a*)(a*)", "aa",   0,2, 0,2, 2,2);
    T2("(a|aa)*",  "aa",   0,2, 0,2);
    T3("(a)|(a)",  "a",    0,1, 0,1, -1,-1);
    T3("(a)*(a)*", "a",    0,1, 0,1, -1,-1);

    // categorize
    T4("(a*)(ab)*(b*)",            "abc",    0,2, 0,1, -1,-1, 1,2);
    T7("((a*)(ab)*)((b*)(a*))",    "aba",    0,3, 0,2, 0,0, 0,2, 2,3, 2,2, 2,3);
    T2("(...?.?)*",                "xxxxxx", 0,6, 4,6);
    T3("(a|ab)(bc|c)",             "abcabc", 0,3, 0,2, 2,3);
    T3("(aba|a*b)(aba|a*b)",       "ababa",  0,5, 0,2, 2,5);
    T2("(a*){2}",                  "xxxxx",  0,0, 0,0);
    T2("(a*)*",                    "a",      0,1, 0,1);
    T2("(aba|a*b)*",               "ababa",  0,5, 2,5);
    T3("(a(b)?)+",                 "aba",    0,3, 2,3, -1,-1);
    T2(".*(.*)",                   "ab",     0,2, 2,2);
    T6("(a?)((ab)?)(b?)a?(ab)?b?", "abab",   0,4, 0,1, 1,1, -1,-1, 1,2, -1,-1);

    // forcedassoc
    T3("(a|ab)(c|bcd)",       "abcd", 0,4, 0,1, 1,4);
    T3("(a|ab)(bcd|c)",       "abcd", 0,4, 0,1, 1,4);
    T3("(ab|a)(c|bcd)",       "abcd", 0,4, 0,1, 1,4);
    T3("(ab|a)(bcd|c)",       "abcd", 0,4, 0,1, 1,4);
    T5("((a|ab)(c|bcd))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("((a|ab)(bcd|c))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("((ab|a)(c|bcd))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("((ab|a)(bcd|c))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("(a|ab)((c|bcd)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T5("(a|ab)((bcd|c)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T5("(ab|a)((c|bcd)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T5("(ab|a)((bcd|c)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T3("(a*)(b|abc)",         "abc",  0,3, 0,0, 0,3);
    T3("(a*)(abc|b)",         "abc",  0,3, 0,0, 0,3);
    T5("((a*)(b|abc))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("((a*)(abc|b))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("(a*)((b|abc)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T5("(a*)((abc|b)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T3("(a*)(b|abc)",         "abc",  0,3, 0,0, 0,3);
    T3("(a*)(abc|b)",         "abc",  0,3, 0,0, 0,3);
    T5("((a*)(b|abc))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("((a*)(abc|b))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("(a*)((b|abc)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T5("(a*)((abc|b)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T2("(a|ab)",              "ab",   0,2, 0,2);
    T2("(ab|a)",              "ab",   0,2, 0,2);
    T3("(a|ab)(b*)",          "ab",   0,2, 0,2, 2,2);
    T3("(ab|a)(b*)",          "ab",   0,2, 0,2, 2,2);

    // glennfowler
    T4("(a?)((ab)?)",                    "ab",      0,2, 0,0, 0,2, 0,2);
    T5("(a?)((ab)?)(b?)",                "ab",      0,2, 0,1, 1,1, -1,-1, 1,2);
    T6("((a?)((ab)?))(b?)",              "ab",      0,2, 0,2, 0,0, 0,2, 0,2, 2,2);
    T6("(a?)(((ab)?)(b?))",              "ab",      0,2, 0,1, 1,2, 1,1, -1,-1, 1,2);
    T2("(.?)",                           "x",       0,1, 0,1);
    T2("(.?){1}",                        "x",       0,1, 0,1);
    T3("(.?)(.?)",                       "x",       0,1, 0,1, 1,1);
    T2("(.?){2}",                        "x",       0,1, 1,1);
    T2("(.?)*",                          "x",       0,1, 0,1);
    T2("(.?.?)",                         "xxx",     0,2, 0,2);
    T2("(.?.?){1}",                      "xxx",     0,2, 0,2);
    T3("(.?.?)(.?.?)",                   "xxx",     0,3, 0,2, 2,3);
    T2("(.?.?){2}",                      "xxx",     0,3, 2,3);
    T4("(.?.?)(.?.?)(.?.?)",             "xxx",     0,3, 0,2, 2,3, 3,3);
    T2("(.?.?){3}",                      "xxx",     0,3, 3,3);
    T2("(.?.?)*",                        "xxx",     0,3, 2,3);
    T4("a?((ab)?)(b?)",                  "ab",      0,2, 1,1, -1,-1, 1,2);
    T4("(a?)((ab)?)b?",                  "ab",      0,2, 0,1, 1,1, -1,-1);
    T3("a?((ab)?)b?",                    "ab",      0,2, 1,1, -1,-1);
    T2("(a*){2}",                        "xxxxx",   0,0, 0,0);
    T3("(ab?)(b?a)",                     "aba",     0,3, 0,2, 2,3);
    T3("(a|ab)(ba|a)",                   "aba",     0,3, 0,2, 2,3);
    T2("(a|ab|ba)",                      "aba",     0,2, 0,2);
    T3("(a|ab|ba)(a|ab|ba)",             "aba",     0,3, 0,2, 2,3);
    T2("(a|ab|ba)*",                     "aba",     0,3, 2,3);
    T2("(aba|a*b)",                      "ababa",   0,3, 0,3);
    T3("(aba|a*b)(aba|a*b)",             "ababa",   0,5, 0,2, 2,5);
    T0("(aba|a*b)(aba|a*b)(aba|a*b)",    "ababa");
    T2("(aba|a*b)*",                     "ababa",   0,5, 2,5);
    T2("(aba|ab|a)",                     "ababa",   0,3, 0,3);
    T3("(aba|ab|a)(aba|ab|a)",           "ababa",   0,5, 0,2, 2,5);
    T4("(aba|ab|a)(aba|ab|a)(aba|ab|a)", "ababa",   0,5, 0,2, 2,4, 4,5);
    T2("(aba|ab|a)*",                    "ababa",   0,5, 2,5);
    T3("(a(b)?)",                        "aba",     0,2, 0,2, 1,2);
    T5("(a(b)?)(a(b)?)",                 "aba",     0,3, 0,2, 1,2, 2,3, -1,-1);
    T3("(a(b)?)+",                       "aba",     0,3, 2,3, -1,-1);
    T3("(.*)(.*)",                       "xx",      0,2, 0,2, 2,2);
    T2(".*(.*)",                         "xx",      0,2, 2,2);
    T2("(a.*z|b.*y)",                    "azbazby", 0,5, 0,5);
    T3("(a.*z|b.*y)(a.*z|b.*y)",         "azbazby", 0,7, 0,5, 5,7);
    T2("(a.*z|b.*y)*",                   "azbazby", 0,7, 5,7);
    T3("(.|..)(.*)",                     "ab",      0,2, 0,2, 2,2);
    T4("((..)*(...)*)",                  "xxx",     0,3, 0,3, -1,-1, 0,3);
    T7("((..)*(...)*)((..)*(...)*)",     "xxx",     0,3, 0,3, -1,-1, 0,3, 3,3, -1,-1, -1,-1);
    T4("((..)*(...)*)*",                 "xxx",     0,3, 0,3, -1,-1, 0,3);

    return e;
}

#undef GS
#undef T
#undef T0
#undef T1
#undef T2
#undef T3
#undef T4
#undef T5
#undef T6
#undef T7
