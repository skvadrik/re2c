#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>

#include "lib/regex.h"
#include "lib/test_helper.h"
#include "src/util/check.h"

static int test(int flags,
                const char* pattern,
                const char* string,
                const char* expected = nullptr) {
    std::vector<std::vector<regoff_t> > submatch;
    if (!parse_submatch(expected, submatch)) {
        fprintf(stderr, "failed to parse submatch string: %s\n", expected);
        exit(1);
    }
    const size_t nmatch = submatch.size();

    static uint32_t total = 0;
    static uint32_t failed = 0;

    const char* prefix = flags & REG_NFA ? "NFA" : "DFA";
    bool with_hist = flags & REG_SUBHIST;
    regex_t re;
    regmatch_t* pmatch = with_hist ? nullptr : new regmatch_t[nmatch];
    subhistory_t* psubhist = nullptr;
    int result;

    result = regcomp(&re, pattern, flags);
    if (result != 0) {
        fprintf(stderr, "%s: regcomp() failed for regexp %s\n", prefix, pattern);
        goto end;
    }

    // run multiple times to ensure everything gets cleaned up properly
    static constexpr uint32_t NRUNS = 2;
    for (uint32_t i = 0; i < NRUNS; ++i) {
        if (with_hist) {
            // With subhistories every regexec() call may allocate offsets. Clean them up at the
            // beginning of the loop, so that the offsets remain available for inspection after the
            // last iteration.
            regfreesub(psubhist);
            psubhist = regparse(&re, string, nmatch);
            result = psubhist ? 0 : 1;
        } else {
            result = regexec(&re, string, nmatch, pmatch, flags);
        }
        if (result != 0) {
            if (nmatch == 0) {
                // failure was expected => it's a success
                result = 0;
            } else if (nmatch > 0) {
                fprintf(stderr,
                        "%s: regexec() failed for regexp %s and string %s\n",
                        prefix, pattern, string);
                goto end;
            }
        } else if (nmatch == 0) {
            // regexed must have failed, something is wrong
            result = REG_NOMATCH;
            fprintf(stderr,
                    "%s: regexec() didn't fail while it should for regexp %s and string %s\n",
                    prefix, pattern, string);
            goto end;
        }
    }

    CHECK(nmatch == 0 || nmatch == re.re_nsub);

    for (uint32_t i = 0; i < nmatch; ++i) {
        const std::vector<regoff_t>& expect_history = submatch[i];
        const size_t expect_size = expect_history.size() / 2;

        if (!with_hist) {
            // Check only the last pair of offsets for each capturing group.
            const regoff_t expect_so = expect_history[2 * expect_size - 2];
            const regoff_t expect_eo = expect_history[2 * expect_size - 1];
            const regmatch_t& actual = pmatch[i];
            if (expect_so != actual.rm_so || expect_eo != actual.rm_eo) {
                result = 1;
                fprintf(stderr,
                        "%s: incorrect submatch for regexp %s and string %s:\n"
                        "\tpmatch[%u].rm_so = %td (expected %td)\n"
                        "\tpmatch[%u].rm_eo = %td (expected %td)\n",
                        prefix, pattern, string,
                        i, actual.rm_so, expect_so,
                        i, actual.rm_eo, expect_eo);
                goto end;
            }
        } else {
            // Check the full history of each capturing group.
            const subhistory_t& actual_history = psubhist[i];
            if (actual_history.size != expect_size) {
                result = 1;
                fprintf(stderr,
                        "%s: wrong subhistory-%u length for regexp %s and string %s: "
                        "expected %zd, have %zd\n",
                        prefix, i, pattern, string, expect_size, actual_history.size);
                goto end;
            }
            for (uint32_t j = 0; j < actual_history.size; ++j) {
                const regoff_t expect_so = expect_history[2 * j];
                const regoff_t expect_eo = expect_history[2 * j + 1];
                const regmatch_t& actual = actual_history.offs[j];
                if (expect_so != actual.rm_so || expect_eo != actual.rm_eo) {
                    result = 1;
                    fprintf(stderr,
                            "%s: incorrect submatch for regexp %s and string %s:\n"
                            "\tpmatch[%u][%u].rm_so = %td (expected %td)\n"
                            "\tpmatch[%u][%u].rm_eo = %td (expected %td)\n",
                            prefix, pattern, string,
                            i, j, actual.rm_so, expect_so,
                            i, j, actual.rm_eo, expect_eo);
                    goto end;
                }
            }
        }
    }

end:
    regfree(&re);
    if (with_hist) {
        regfreesub(psubhist);
    } else {
        delete[] pmatch;
    }

    ++total;
    if (result != 0) {
        ++failed;
        fprintf(stderr, "failed %u of %u\n", failed, total);
    }

    return result;
}

static int test_tstring(const char* pattern, const char* string, const char* expected) {
    regex_t re;
    const tstring_t* tstr = nullptr;
    std::ostringstream s;
    int result;

    result = regcomp(&re, pattern, REG_MULTIPASS | REG_TSTRING);
    if (result != 0) {
        fprintf(stderr, "[t-string] regcomp() failed for regexp %s\n", pattern);
        goto end;
    }

    // run multiple times to ensure everything gets cleaned up properly
    static constexpr uint32_t NRUNS = 2;
    for (uint32_t i = 0; i < NRUNS; ++i) {
        tstr = regtstring(&re, string);
        if (tstr == nullptr) {
            result = 1;
            fprintf(stderr, "regtstring() failed for regexp %s and string %s\n", pattern, string);
            goto end;
        }
    }

    // Convert T-string to a C++ string.
    for (size_t i = 0; i < tstr->length; ++i) {
        const tchar_t c = tstr->string[i];
        if (c < TAG_BASE) {
            CHECK(c < 0xff); // expect 1-byte characters
            s << static_cast<char>(c);
        } else {
            s << c - TAG_BASE;
        }
        s << ' ';
    }

    if (strcmp(expected, s.str().c_str()) != 0) {
        result = 1;
        fprintf(stderr,
                "incorrect t-string for regexp %s and string %s:\n\texpect: %s\n\tactual: %s\n",
                pattern, string, expected, s.str().c_str());
    }

end:
    regfree(&re);
    return result;
}

static int test_all_posix(int f) {
    int e = 0;

    e |= test(f, "(a+(c+))|(b+(d+))", "ac", "(0,2),(0,2),(1,2),(?,?),(?,?)");

    e |= test(f, "(aaaa|aaa|a)+",    "aaaaaaaaaa", "(0,10),(0,4)(4,8)(8,9)(9,10)");
    e |= test(f, "(aaaa|aaa|a){3,}", "aaaaaaaaaa", "(0,10),(0,4)(4,8)(8,9)(9,10)");
    e |= test(f, "(aaaa|aaa|a){3,4}", "aaaaaaaaaa", "(0,10),(0,4)(4,8)(8,9)(9,10)");

    e |= test(f, "(aaaaaa|aaaaa|aaaa|aa|a){3,4}", "aaaaaaaaaaaaaaa",
              "(0,15),(0,6)(6,12)(12,14)(14,15)");

    e |= test(f, "(aaaaa?a?|aa?){1,4}", "aaaaaaaaaaaaaaa", "(0,15),(0,6)(6,12)(12,14)(14,15)");

    e |= test(f, "(((a){3,4}a?)()a|aa?){1,4}", "aaaaaaaaaaaaaaa",
              "(0,15),(0,6)(6,12)(12,14)(14,15),(0,5)(6,11)(?,?)(?,?),"
              "(0,1)(1,2)(2,3)(3,4)(6,7)(7,8)(8,9)(9,10)(?,?)(?,?),(5,5)(11,11)(?,?)(?,?)");

    e |= test(f, "(((aaaa?|a?)){1,4})+", "aaaaaaaaaa",
              "(0,10),(0,10),(0,4)(4,8)(8,9)(9,10),(0,4)(4,8)(8,9)(9,10)");

    e |= test(f, "((((a){2,3}(()|a)(()|a?)a|a?)){2,5})*", "aaaaaaaaaaaaaa",
              "(0,14),(0,14),(0,6)(6,12)(12,13)(13,14),(0,6)(6,12)(12,13)(13,14),"
              "(0,1)(1,2)(2,3)(6,7)(7,8)(8,9)(?,?)(?,?),(3,4)(9,10)(?,?)(?,?),"
              "(?,?)(?,?)(?,?)(?,?),(4,5)(10,11)(?,?)(?,?),(?,?)(?,?)(?,?)(?,?)");

    e |= test(f, "(((((a){3,3}a?|a?)){0,4})?)*", "aaaaaaaaaa",
              "(0,10),(0,10),(0,10),(0,4)(4,8)(8,9)(9,10),"
              "(0,4)(4,8)(8,9)(9,10),(0,1)(1,2)(2,3)(4,5)(5,6)(6,7)(?,?)(?,?)");

    e |= test(f, "(((((a){3,4}|a?)){1,4}|((a)+(a|())){1,2}))*", "aaaaaaaaaa",
              "(0,10),(0,10),(0,10),(0,4)(4,8)(8,9)(9,10),(0,4)(4,8)(8,9)(9,10),"
              "(0,1)(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(?,?)(?,?),(?,?),(?,?),(?,?),(?,?)");

    e |= test(f, "((a?|a?(a?a?)((())+)+))*", "aaaaaa",
              "(0,6),(0,3)(3,6),(0,3)(3,6),(1,3)(4,6),(3,3)(6,6),(3,3)(6,6),(3,3)(6,6)");

    e |= test(f, "(((a?a)){2,3})*", "aaaa", "(0,4),(0,4),(0,2)(2,4),(0,2)(2,4)");

    e |= test(f, "(((aa?a)((aaa)+))+)+", "aaaaaaaaaa",
              "(0,10),(0,10),(0,5)(5,10),(0,2)(5,7),(2,5)(7,10),(2,5)(7,10)");

    e |= test(f, "(((aaa?)((aaa)+))+)+", "aaaaaaaaaa",
              "(0,10),(0,10),(0,5)(5,10),(0,2)(5,7),(2,5)(7,10),(2,5)(7,10)");

    e |= test(f, "(((aaa?)((aaa){1,3})){1,2})*", "aaaaaaaaaa",
              "(0,10),(0,10),(0,5)(5,10),(0,2)(5,7),(2,5)(7,10),(2,5)(7,10)");

    e |= test(f, "((((aaa?)(aaa){1,3})){1,2})*", "aaaaaaaaaa",
              "(0,10),(0,10),(0,5)(5,10),(0,5)(5,10),(0,2)(5,7),(2,5)(7,10)");

    e |= test(f, "((((aaa?)((a){3,3}){1,3})){1,2})*", "aaaaaaaaaa",
              "(0,10),(0,10),(0,5)(5,10),(0,5)(5,10),(0,2)(5,7),(2,5)(7,10),"
              "(2,3)(3,4)(4,5)(7,8)(8,9)(9,10)");

    e |= test(f, "(a|aa)*", "",           "(0,0),(?,?)");
    e |= test(f, "(a|aa)*", "a",          "(0,1),(0,1)");
    e |= test(f, "(a|aa)*", "aa",         "(0,2),(0,2)");
    e |= test(f, "(a|aa)*", "aaa",        "(0,3),(0,2)(2,3)");
    e |= test(f, "(a|aa)*", "aaaa",       "(0,4),(0,2)(2,4)");
    e |= test(f, "(a|aa)*", "aaaaa",      "(0,5),(0,2)(2,4)(4,5)");
    e |= test(f, "(a|aa)*", "aaaaaa",     "(0,6),(0,2)(2,4)(4,6)");
    e |= test(f, "(a|aa)*", "aaaaaaa",    "(0,7),(0,2)(2,4)(4,6)(6,7)");
    e |= test(f, "(a|aa)*", "aaaaaaaa",   "(0,8),(0,2)(2,4)(4,6)(6,8)");
    e |= test(f, "(a|aa)*", "aaaaaaaaa",  "(0,9),(0,2)(2,4)(4,6)(6,8)(8,9)");
    e |= test(f, "(a|aa)*", "aaaaaaaaaa", "(0,10),(0,2)(2,4)(4,6)(6,8)(8,10)");
    e |= test(f, "(aa|a)*", "",           "(0,0),(?,?)");
    e |= test(f, "(aa|a)*", "a",          "(0,1),(0,1)");
    e |= test(f, "(aa|a)*", "aa",         "(0,2),(0,2)");
    e |= test(f, "(aa|a)*", "aaa",        "(0,3),(0,2)(2,3)");
    e |= test(f, "(aa|a)*", "aaaa",       "(0,4),(0,2)(2,4)");
    e |= test(f, "(aa|a)*", "aaaaa",      "(0,5),(0,2)(2,4)(4,5)");
    e |= test(f, "(aa|a)*", "aaaaaa",     "(0,6),(0,2)(2,4)(4,6)");
    e |= test(f, "(aa|a)*", "aaaaaaa",    "(0,7),(0,2)(2,4)(4,6)(6,7)");
    e |= test(f, "(aa|a)*", "aaaaaaaa",   "(0,8),(0,2)(2,4)(4,6)(6,8)");
    e |= test(f, "(aa|a)*", "aaaaaaaaa",  "(0,9),(0,2)(2,4)(4,6)(6,8)(8,9)");
    e |= test(f, "(aa|a)*", "aaaaaaaaaa", "(0,10),(0,2)(2,4)(4,6)(6,8)(8,10)");

    e |= test(f, "(aaa|aa)*", "aaaaaaaaaa", "(0,10),(0,3)(3,6)(6,8)(8,10)");
    e |= test(f, "(aa|aaa)*", "aaaaaaaaaa", "(0,10),(0,3)(3,6)(6,8)(8,10)");

    e |= test(f, "((a*)*)*", "", "(0,0),(0,0),(0,0)");

    e |= test(f, "(y?){0,2}", "", "(0,0),(0,0)");

    e |= test(f, "((y?){2,3}){2}", "yyyyy", "(0,5),(0,3)(3,5),(0,1)(1,2)(2,3)(3,4)(4,5)");

    e |= test(f, "((y?){2,3}){2,3}", "yyyyy", "(0,5),(0,3)(3,5),(0,1)(1,2)(2,3)(3,4)(4,5)");

    e |= test(f, "((y?){2,3})*", "yyyyy", "(0,5),(0,3)(3,5),(0,1)(1,2)(2,3)(3,4)(4,5)");

    e |= test(f, "((y?){3}){2}", "yyyyy", "(0,5),(0,3)(3,5),(0,1)(1,2)(2,3)(3,4)(4,5)(5,5)");

    e |= test(f, "((y?){3}){2,3}", "yyyyy", "(0,5),(0,3)(3,5),(0,1)(1,2)(2,3)(3,4)(4,5)(5,5)");

    e |= test(f, "((y?){3})*", "yyyyy", "(0,5),(0,3)(3,5),(0,1)(1,2)(2,3)(3,4)(4,5)(5,5)");

    e |= test(f, "((y?)*){2}", "yyyyy", "(0,5),(0,5)(5,5),(0,1)(1,2)(2,3)(3,4)(4,5)(5,5)");

    e |= test(f, "((y?)*){2,3}", "yyyyy", "(0,5),(0,5)(5,5),(0,1)(1,2)(2,3)(3,4)(4,5)(5,5)");

    e |= test(f, "((y?)*)*", "yyyyy", "(0,5),(0,5),(0,1)(1,2)(2,3)(3,4)(4,5)");

    e |= test(f, "((a)(b)?)*",   "aba", "(0,3),(0,2)(2,3),(0,1)(2,3),(1,2)(?,?)");
    e |= test(f, "((a)|(b))*",   "ba",  "(0,2),(0,1)(1,2),(?,?)(1,2),(0,1)(?,?)");
    e |= test(f, "((a)|(b))*",   "ab",  "(0,2),(0,1)(1,2),(0,1)(?,?),(?,?)(1,2)");
    e |= test(f, "((a?)|(b?))*", "ab",  "(0,2),(0,1)(1,2),(0,1)(?,?),(?,?)(1,2)");
    e |= test(f, "((a?)|(b?))*", "ba",  "(0,2),(0,1)(1,2),(?,?)(1,2),(0,1)(?,?)");
    e |= test(f, "((a?)|(b?)){2,3}", "ab", "(0,2),(0,1)(1,2),(0,1)(?,?),(?,?)(1,2)");
    e |= test(f, "((a?)|(b?)){3}",   "ab", "(0,2),(0,1)(1,2)(2,2),(0,1)(?,?)(2,2),(?,?)(1,2)(?,?)");

    e |= test(f, "y{3}",                     "yyy", "(0,3)");
    e |= test(f, "y{0,2}",                   "",    "(0,0)");
    e |= test(f, "y{0,2}",                   "y",   "(0,1)");
    e |= test(f, "y{0,2}",                   "yy",  "(0,2)");
    e |= test(f, "(y){3}",                   "yyy", "(0,3),(0,1)(1,2)(2,3)");
    e |= test(f, "(y){0,2}",                 "",    "(0,0),(?,?)");
    e |= test(f, "(y){0,2}",                 "y",   "(0,1),(0,1)");
    e |= test(f, "(y){0,2}",                 "yy",  "(0,2),(0,1)(1,2)");
    e |= test(f, "()",                       "",    "(0,0),(0,0)");
    e |= test(f, "(){2}",                    "",    "(0,0),(0,0)(0,0)");
    e |= test(f, "(){0,2}",                  "",    "(0,0),(0,0)");
    e |= test(f, "(((){0,30}){0,30}){0,30}", "",    "(0,0),(0,0),(0,0),(0,0)");
    e |= test(f, "(y?){2}",                  "y",   "(0,1),(0,1)(1,1)");

    e |= test(f, "a",        "a",    "(0,1)");
    e |= test(f, "(a)",      "a",    "(0,1),(0,1)");
    e |= test(f, "(a*)",     "aaa",  "(0,3),(0,3)");
    e |= test(f, "(a*)(b*)", "aabb", "(0,4),(0,2),(2,4)");
    e |= test(f, "(a*)(a*)", "aa",   "(0,2),(0,2),(2,2)");
    e |= test(f, "(a|aa)*",  "aa",   "(0,2),(0,2)");
    e |= test(f, "(a)|(a)",  "a",    "(0,1),(0,1),(?,?)");
    e |= test(f, "(a)*(a)*", "a",    "(0,1),(0,1),(?,?)");

    e |= test(f, "[a]",      "a",    "(0,1)");
    e |= test(f, "[a]",      "b");
    e |= test(f, "[^a]",     "a");
    e |= test(f, "[^a]",     "b",    "(0,1)");
    e |= test(f, "[ac]*",    "ac",   "(0,2)");
    e |= test(f, "[a-c]*",   "abc",  "(0,3)");
    e |= test(f, "[]]",      "]",    "(0,1)");
    e |= test(f, "[^]]",     "]");
    e |= test(f, "[^]]",     "a",    "(0,1)");
    e |= test(f, "[-]",      "-",    "(0,1)");
    e |= test(f, "[]-]*",    "]-",   "(0,2)");
    e |= test(f, "[-a]*",    "-a",   "(0,2)");
    e |= test(f, "[a-]*",    "-a",   "(0,2)");
    e |= test(f, "[-a-]*",   "-a",   "(0,2)");

    // basic
    e |= test(f, "(..)*(...)*",             "a",          "(0,0),(?,?),(?,?)");
    e |= test(f, "(..)*(...)*",             "abcd",       "(0,4),(0,2)(2,4),(?,?)");
    e |= test(f, "(ab|a)(bc|c)",            "abc",        "(0,3),(0,2),(2,3)");
    e |= test(f, "(ab)c|abc",               "abc",        "(0,3),(0,2)");
    e |= test(f, "(a*)(b?)(b+)b{3}",        "aaabbbbbbb", "(0,10),(0,3),(3,4),(4,7)");
    e |= test(f, "(a*)(b{0,1})(b{1,})b{3}", "aaabbbbbbb", "(0,10),(0,3),(3,4),(4,7)");
    e |= test(f, "((a|a)|a)",               "a",          "(0,1),(0,1),(0,1)");
    e |= test(f, "(a*)(a|aa)",              "aaaa",       "(0,4),(0,3),(3,4)");
    e |= test(f, "a*(a.|aa)",               "aaaa",       "(0,4),(2,4)");
    e |= test(f, "a(b)|c(d)|a(e)f",         "aef",        "(0,3),(?,?),(?,?),(1,2)");
    e |= test(f, "(a|b)?.*",                "b",          "(0,1),(0,1)");
    e |= test(f, "(a|b)c|a(b|c)",           "ac",         "(0,2),(0,1),(?,?)");
    e |= test(f, "(a|b)c|a(b|c)",           "ab",         "(0,2),(?,?),(1,2)");
    e |= test(f, "(a|b)*c|(a|ab)*c",        "abc",        "(0,3),(0,1)(1,2),(?,?)");
    e |= test(f, "(.a|.b).*|.*(.a|.b)",     "xa",         "(0,2),(0,2),(?,?)");
    e |= test(f, "a?(ab|ba)ab",             "abab",       "(0,4),(0,2)");
    e |= test(f, "a?(a[c]{0}b|ba)ab",       "abab",       "(0,4),(0,2)");
    e |= test(f, "ab|abab",                 "abbabab",    "(0,2)");
    e |= test(f, "(aa|aaa)*|(a|aaaaa)",     "aa",         "(0,2),(0,2),(?,?)");
    e |= test(f, "(a.|.a.)*|(a|.a...)",     "aa",         "(0,2),(0,2),(?,?)");
    e |= test(f, "(a)(b)(c)",               "abc",        "(0,3),(0,1),(1,2),(2,3)");

    e |= test(f, "((((((x))))))", "x", "(0,1),(0,1),(0,1),(0,1),(0,1),(0,1),(0,1)");

    e |= test(f, "((((((x))))))*", "xx",
              "(0,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2)");

    e |= test(f, "a?(ab|ba)*",
              "abababababababababababababababababababab"
              "ababababababababababababababababababababa",
              "(0,81),"
              "(1,3)(3,5)(5,7)(7,9)(9,11)(11,13)(13,15)(15,17)(17,19)(19,21)(21,23)"
              "(23,25)(25,27)(27,29)(29,31)(31,33)(33,35)(35,37)(37,39)(39,41)(41,43)"
              "(43,45)(45,47)(47,49)(49,51)(51,53)(53,55)(55,57)(57,59)(59,61)(61,63)"
              "(63,65)(65,67)(67,69)(69,71)(71,73)(73,75)(75,77)(77,79)(79,81)");

    e |= test(f, "a*a*a*a*a*b",   "aaaaaaaaab", "(0,10)");
    e |= test(f, "a[b]+bc",       "abbc",       "(0,4)");
    e |= test(f, "a[b]+bc",       "abbbbc",     "(0,6)");
    e |= test(f, "a[b]?bc",       "abbc",       "(0,4)");
    e |= test(f, "a[b]?bc",       "abc",        "(0,3)");
    e |= test(f, "a[b]?c",        "abc",        "(0,3)");
    e |= test(f, "ab|cd",         "abc",        "(0,2)");
    e |= test(f, "ab|cd",         "abcd",       "(0,2)");
    e |= test(f, "((a))",         "abc",        "(0,1),(0,1),(0,1)");
    e |= test(f, "(a)b(c)",       "abc",        "(0,3),(0,1),(2,3)");
    e |= test(f, "a*",            "aaa",        "(0,3)");
    e |= test(f, "(a*)*",         "-",          "(0,0),(0,0)");
    e |= test(f, "(a*)+",         "-",          "(0,0),(0,0)");
    e |= test(f, "(a*|b)*",       "-",          "(0,0),(0,0)");
    e |= test(f, "(a+|b)*",       "ab",         "(0,2),(0,1)(1,2)");
    e |= test(f, "(a+|b)+",       "ab",         "(0,2),(0,1)(1,2)");
    e |= test(f, "(a+|b)?",       "ab",         "(0,1),(0,1)");
    e |= test(f, "([abc])*d",     "abbbcd",     "(0,6),(0,1)(1,2)(2,3)(3,4)(4,5)");
    e |= test(f, "([abc])*bcd",   "abcd",       "(0,4),(0,1)");
    e |= test(f, "a|b|c|d|e",     "e",          "(0,1)");
    e |= test(f, "(a|b|c|d|e)f",  "ef",         "(0,2),(0,1)");
    e |= test(f, "((a*|b))*",     "-",          "(0,0),(0,0),(0,0)");
    e |= test(f, "(ab|a[b]*)bc",  "abc",        "(0,3),(0,1)");
    e |= test(f, "a([bc]*)c*",    "abc",        "(0,3),(1,3)");
    e |= test(f, "a([bc]*)(c*d)", "abcd",       "(0,4),(1,3),(3,4)");
    e |= test(f, "a([bc]+)(c*d)", "abcd",       "(0,4),(1,3),(3,4)");
    e |= test(f, "a([bc]*)(c+d)", "abcd",       "(0,4),(1,2),(2,4)");
    e |= test(f, "a[bcd]*dcdcde", "adcdcde",    "(0,7)");
    e |= test(f, "(ab|a)b*c",     "abc",        "(0,3),(0,2)");
    e |= test(f, "((a)(b)c)(d)",  "abcd",       "(0,4),(0,3),(0,1),(1,2),(3,4)");
    e |= test(f, "(.*)c(.*)",     "abcde",      "(0,5),(0,2),(3,5)");
    e |= test(f, "a(bc)d",        "abcd",       "(0,4),(1,3)");
    e |= test(f, "a+(b|c)*d+",    "aabcdd",     "(0,6),(2,3)(3,4)");

    // categorize
    e |= test(f, "(a*)(ab)*(b*)", "abc", "(0,2),(0,1),(?,?),(1,2)");

    e |= test(f, "((a*)(ab)*)((b*)(a*))", "aba", "(0,3),(0,2),(0,0),(0,2),(2,3),(2,2),(2,3)");

    e |= test(f, "(...?.?)*",          "xxxxxx", "(0,6),(0,4)(4,6)");
    e |= test(f, "(a|ab)(bc|c)",       "abcabc", "(0,3),(0,2),(2,3)");
    e |= test(f, "(aba|a*b)(aba|a*b)", "ababa",  "(0,5),(0,2),(2,5)");
    e |= test(f, "(a*){2}",            "xxxxx",  "(0,0),(0,0)(0,0)");
    e |= test(f, "(a*)*",              "a",      "(0,1),(0,1)");
    e |= test(f, "(aba|a*b)*",         "ababa",  "(0,5),(0,2)(2,5)");
    e |= test(f, "(a(b)?)+",           "aba",    "(0,3),(0,2)(2,3),(1,2)(?,?)");
    e |= test(f, ".*(.*)",             "ab",     "(0,2),(2,2)");

    e |= test(f, "(a?)((ab)?)(b?)a?(ab)?b?", "abab", "(0,4),(0,1),(1,1),(?,?),(1,2),(?,?)");

    // forcedassoc
    e |= test(f, "(a|ab)(c|bcd)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "(a|ab)(bcd|c)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "(ab|a)(c|bcd)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "(ab|a)(bcd|c)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "((a|ab)(c|bcd))(d*)", "abcd", "(0,4),(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "((a|ab)(bcd|c))(d*)", "abcd", "(0,4),(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "((ab|a)(c|bcd))(d*)", "abcd", "(0,4),(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "((ab|a)(bcd|c))(d*)", "abcd", "(0,4),(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "(a|ab)((c|bcd)(d*))", "abcd", "(0,4),(0,2),(2,4),(2,3),(3,4)");
    e |= test(f, "(a|ab)((bcd|c)(d*))", "abcd", "(0,4),(0,2),(2,4),(2,3),(3,4)");
    e |= test(f, "(ab|a)((c|bcd)(d*))", "abcd", "(0,4),(0,2),(2,4),(2,3),(3,4)");
    e |= test(f, "(ab|a)((bcd|c)(d*))", "abcd", "(0,4),(0,2),(2,4),(2,3),(3,4)");
    e |= test(f, "(a*)(b|abc)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "(a*)(abc|b)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "((a*)(b|abc))(c*)",   "abc",  "(0,3),(0,3),(0,0),(0,3),(3,3)");
    e |= test(f, "((a*)(abc|b))(c*)",   "abc",  "(0,3),(0,3),(0,0),(0,3),(3,3)");
    e |= test(f, "(a*)((b|abc)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a*)((abc|b)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a*)(b|abc)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "(a*)(abc|b)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "((a*)(b|abc))(c*)",   "abc",  "(0,3),(0,3),(0,0),(0,3),(3,3)");
    e |= test(f, "((a*)(abc|b))(c*)",   "abc",  "(0,3),(0,3),(0,0),(0,3),(3,3)");
    e |= test(f, "(a*)((b|abc)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a*)((abc|b)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a|ab)",              "ab",   "(0,2),(0,2)");
    e |= test(f, "(ab|a)",              "ab",   "(0,2),(0,2)");
    e |= test(f, "(a|ab)(b*)",          "ab",   "(0,2),(0,2),(2,2)");
    e |= test(f, "(ab|a)(b*)",          "ab",   "(0,2),(0,2),(2,2)");

    // glennfowler
    e |= test(f, "(a?)((ab)?)",        "ab",   "(0,2),(0,0),(0,2),(0,2)");
    e |= test(f, "(a?)((ab)?)(b?)",    "ab",   "(0,2),(0,1),(1,1),(?,?),(1,2)");
    e |= test(f, "((a?)((ab)?))(b?)",  "ab",   "(0,2),(0,2),(0,0),(0,2),(0,2),(2,2)");
    e |= test(f, "(a?)(((ab)?)(b?))",  "ab",   "(0,2),(0,1),(1,2),(1,1),(?,?),(1,2)");
    e |= test(f, "(.?)",               "x",    "(0,1),(0,1)");
    e |= test(f, "(.?){1}",            "x",    "(0,1),(0,1)");
    e |= test(f, "(.?)(.?)",           "x",    "(0,1),(0,1),(1,1)");
    e |= test(f, "(.?){2}",            "x",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(.?)*",              "x",    "(0,1),(0,1)");
    e |= test(f, "(.?.?)",             "xxx",  "(0,2),(0,2)");
    e |= test(f, "(.?.?){1}",          "xxx",  "(0,2),(0,2)");
    e |= test(f, "(.?.?)(.?.?)",       "xxx",  "(0,3),(0,2),(2,3)");
    e |= test(f, "(.?.?){2}",          "xxx",  "(0,3),(0,2)(2,3)");
    e |= test(f, "(.?.?)(.?.?)(.?.?)", "xxx",  "(0,3),(0,2),(2,3),(3,3)");
    e |= test(f, "(.?.?){3}",          "xxx",  "(0,3),(0,2)(2,3)(3,3)");
    e |= test(f, "(.?.?)*",            "xx",   "(0,2),(0,2)");
    e |= test(f, "(.?.?)*",            "xxx",  "(0,3),(0,2)(2,3)");
    e |= test(f, "(.?.?)*",            "xxxx", "(0,4),(0,2)(2,4)");

    e |= test(f, "a?((ab)?)(b?)",                  "ab",    "(0,2),(1,1),(?,?),(1,2)");
    e |= test(f, "(a?)((ab)?)b?",                  "ab",    "(0,2),(0,1),(1,1),(?,?)");
    e |= test(f, "a?((ab)?)b?",                    "ab",    "(0,2),(1,1),(?,?)");
    e |= test(f, "(ab?)(b?a)",                     "aba",   "(0,3),(0,2),(2,3)");
    e |= test(f, "(a|ab)(ba|a)",                   "aba",   "(0,3),(0,2),(2,3)");
    e |= test(f, "(a|ab|ba)",                      "aba",   "(0,2),(0,2)");
    e |= test(f, "(a|ab|ba)(a|ab|ba)",             "aba",   "(0,3),(0,2),(2,3)");
    e |= test(f, "(a|ab|ba)*",                     "aba",   "(0,3),(0,2)(2,3)");
    e |= test(f, "(aba|a*b)",                      "ababa", "(0,3),(0,3)");
    e |= test(f, "(aba|a*b)(aba|a*b)",             "ababa", "(0,5),(0,2),(2,5)");
    e |= test(f, "(aba|a*b)(aba|a*b)(aba|a*b)",    "ababa");
    e |= test(f, "(aba|ab|a)",                     "ababa", "(0,3),(0,3)");
    e |= test(f, "(aba|ab|a)(aba|ab|a)",           "ababa", "(0,5),(0,2),(2,5)");
    e |= test(f, "(aba|ab|a)(aba|ab|a)(aba|ab|a)", "ababa", "(0,5),(0,2),(2,4),(4,5)");
    e |= test(f, "(aba|ab|a)*",                    "ababa", "(0,5),(0,2)(2,5)");

    e |= test(f, "(a(b)?)",        "aba", "(0,2),(0,2),(1,2)");
    e |= test(f, "(a(b)?)(a(b)?)", "aba", "(0,3),(0,2),(1,2),(2,3),(?,?)");

    e |= test(f, "(.*)(.*)", "xx", "(0,2),(0,2),(2,2)");
    e |= test(f, ".*(.*)",   "xx", "(0,2),(2,2)");

    e |= test(f, "(a.*z|b.*y)",            "azbazby", "(0,5),(0,5)");
    e |= test(f, "(a.*z|b.*y)(a.*z|b.*y)", "azbazby", "(0,7),(0,5),(5,7)");
    e |= test(f, "(a.*z|b.*y)*",           "azbazby", "(0,7),(0,5)(5,7)");

    e |= test(f, "(.|..)(.*)", "ab","(0,2),(0,2),(2,2)");

    e |= test(f, "((..)*(...)*)",              "xxx", "(0,3),(0,3),(?,?),(0,3)");
    e |= test(f, "((..)*(...)*)*",             "xxx", "(0,3),(0,3),(?,?),(0,3)");
    e |= test(f, "((..)*(...)*)((..)*(...)*)", "xxx", "(0,3),(0,3),(?,?),(0,3),(3,3),(?,?),(?,?)");

    // nullsubexpr
    e |= test(f, "(a*)*",      "a",        "(0,1),(0,1)");
    e |= test(f, "(a*)*",      "x",        "(0,0),(0,0)");
    e |= test(f, "(a*)*",      "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a*)*",      "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "(a*)+",      "a",        "(0,1),(0,1)");
    e |= test(f, "(a*)+",      "x",        "(0,0),(0,0)");
    e |= test(f, "(a*)+",      "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a*)+",      "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "(a+)*",      "a",        "(0,1),(0,1)");
    e |= test(f, "(a+)*",      "x",        "(0,0),(?,?)");
    e |= test(f, "(a+)*",      "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a+)*",      "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "(a+)+",      "a",        "(0,1),(0,1)");
    e |= test(f, "(a+)+",      "x");
    e |= test(f, "(a+)+",      "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a+)+",      "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "([a]*)*",    "a",        "(0,1),(0,1)");
    e |= test(f, "([a]*)*",    "x",        "(0,0),(0,0)");
    e |= test(f, "([a]*)*",    "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([a]*)*",    "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "([a]*)+",    "a",        "(0,1),(0,1)");
    e |= test(f, "([a]*)+",    "x",        "(0,0),(0,0)");
    e |= test(f, "([a]*)+",    "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([a]*)+",    "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "([^b]*)*",   "a",        "(0,1),(0,1)");
    e |= test(f, "([^b]*)*",   "b",        "(0,0),(0,0)");
    e |= test(f, "([^b]*)*",   "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([^b]*)*",   "aaaaaab",  "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",   "a",        "(0,1),(0,1)");
    e |= test(f, "([ab]*)*",   "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",   "ababab",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",   "bababa",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",   "b",        "(0,1),(0,1)");
    e |= test(f, "([ab]*)*",   "bbbbbb",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",   "aaaabcde", "(0,5),(0,5)");
    e |= test(f, "([^a]*)*",   "b",        "(0,1),(0,1)");
    e |= test(f, "([^a]*)*",   "bbbbbb",   "(0,6),(0,6)");
    e |= test(f, "([^a]*)*",   "aaaaaa",   "(0,0),(0,0)");
    e |= test(f, "([^ab]*)*",  "ccccxx",   "(0,6),(0,6)");
    e |= test(f, "([^ab]*)*",  "ababab",   "(0,0),(0,0)");
    e |= test(f, "((z)+|a)*",  "zabcde",   "(0,2),(0,1)(1,2),(0,1)(?,?)");
    e |= test(f, "(a)",        "aaa",      "(0,1),(0,1)");
    e |= test(f, "(a*)*(x)",   "x",        "(0,1),(0,0),(0,1)");
    e |= test(f, "(a*)*(x)",   "ax",       "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*)*(x)",   "axa",      "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*)+(x)",   "x",        "(0,1),(0,0),(0,1)");
    e |= test(f, "(a*)+(x)",   "ax",       "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*)+(x)",   "axa",      "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*){2}(x)", "x",        "(0,1),(0,0)(0,0),(0,1)");
    e |= test(f, "(a*){2}(x)", "ax",       "(0,2),(0,1)(1,1),(1,2)");
    e |= test(f, "(a*){2}(x)", "axa",      "(0,2),(0,1)(1,1),(1,2)");

    e |= test(f, "(()|.)(b)",     "ab",    "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "(()|[ab])(b)",  "ab",    "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "(()|[ab])+b",   "aaab",  "(0,4),(0,1)(1,2)(2,3),(?,?)(?,?)(?,?)");
    e |= test(f, "(.|())(b)",     "ab",    "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "([ab]|())(b)",  "ab",    "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "([ab]|())+b",   "aaab",  "(0,4),(0,1)(1,2)(2,3),(?,?)(?,?)(?,?)");
    e |= test(f, "(.?)(b)",       "ab",    "(0,2),(0,1),(1,2)");

    // other
    e |= test(f, "a|(a)",      "a",  "(0,1),(?,?)");
    e |= test(f, "(a)|a",      "a",  "(0,1),(0,1)");
    e |= test(f, "(b)a|b(a)",  "ba", "(0,2),(0,1),(?,?)");
    e |= test(f, "b(a)|(b)a",  "ba", "(0,2),(1,2),(?,?)");
    e |= test(f, "a*|(a|aa)*", "aa", "(0,2),(?,?)");
    e |= test(f, "(a|aa)*|a*", "aa", "(0,2),(0,2)");

    e |= test(f, "(aa*|aaa*)*",                  "aaaaaa", "(0,6),(0,6)");
    e |= test(f, "(aa*|aaa*)(aa*|aaa*)",         "aaaaaa", "(0,6),(0,5),(5,6)");
    e |= test(f, "(aa*|aaa*){2}",                "aaaaaa", "(0,6),(0,5)(5,6)");
    e |= test(f, "((aa)*|(aaa)*)((aa)*|(aaa)*)", "aaaaaa",
              "(0,6),(0,6),(0,2)(2,4)(4,6),(?,?),(6,6),(?,?),(?,?)");
    e |= test(f, "((aa)*|(aaa)*){2}",            "aaaaaa",
              "(0,6),(0,6)(6,6),(0,2)(2,4)(4,6)(?,?),(?,?)(?,?)");
    e |= test(f, "(aa)*|(aaa)*",                 "aaaaaa", "(0,6),(0,2)(2,4)(4,6),(?,?)");

    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XY",         "(0,2),(0,1)(1,2)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XabY",       "(0,4),(0,3)(3,4)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XababY",     "(0,6),(0,4)(4,6)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XabababY",   "(0,8),(0,3)(3,7)(7,8)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XababababY", "(0,10),(0,4)(4,8)(8,10)");

    e |= test(f, "(y){2}",         "");
    e |= test(f, "(y){2}",         "y");
    e |= test(f, "(y){2}",         "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){0,2}",       "",     "(0,0),(?,?)");
    e |= test(f, "(y){0,2}",       "y",    "(0,1),(0,1)");
    e |= test(f, "(y){0,2}",       "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){1,2}",       "");
    e |= test(f, "(y){1,2}",       "y",    "(0,1),(0,1)");
    e |= test(f, "(y){1,2}",       "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){1,2}y",      "");
    e |= test(f, "(y){1,2}y",      "y");
    e |= test(f, "(y){1,2}y",      "yy",   "(0,2),(0,1)");
    e |= test(f, "(y){1,2}y",      "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y){1,2}y?",     "");
    e |= test(f, "(y){1,2}y?",     "y",    "(0,1),(0,1)");
    e |= test(f, "(y){1,2}y?",     "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){1,2}y?",     "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y){2,}",        "");
    e |= test(f, "(y){2,}",        "y");
    e |= test(f, "(y){2,}",        "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){2,}",        "yyy",  "(0,3),(0,1)(1,2)(2,3)");
    e |= test(f, "(y?){2}",        "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){2}",        "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){2}",        "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){0,2}",      "",     "(0,0),(0,0)");
    e |= test(f, "(y?){0,2}|(y?)", "y",    "(0,1),(0,1),(?,?)");
    e |= test(f, "(y?){0,2}",      "y",    "(0,1),(0,1)");
    e |= test(f, "(y?){0,2}",      "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}",      "",     "(0,0),(0,0)");
    e |= test(f, "(y?){1,2}",      "y",    "(0,1),(0,1)");
    e |= test(f, "(y?){1,2}",      "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}y",     "");
    e |= test(f, "(y?){1,2}y",     "y",    "(0,1),(0,0)");
    e |= test(f, "(y?){1,2}y",     "yy",   "(0,2),(0,1)");
    e |= test(f, "(y?){1,2}y",     "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}y?",    "",     "(0,0),(0,0)");
    e |= test(f, "(y?){1,2}y?",    "y",    "(0,1),(0,1)");
    e |= test(f, "(y?){1,2}y?",    "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}y?",    "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y?){2,}",       "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){2,}",       "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){2,}",       "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){2,}",       "yyy",  "(0,3),(0,1)(1,2)(2,3)");
    e |= test(f, "(y|(x?)){1,3}",  "y",    "(0,1),(0,1),(?,?)");
    e |= test(f, "(y[y]?){3}",     "yyyy", "(0,4),(0,2)(2,3)(3,4)");

    // repetition
    e |= test(f, "((..)|(.))",                     "");
    e |= test(f, "((..)|(.))((..)|(.))",           "");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "");
    e |= test(f, "((..)|(.)){1}",                  "");
    e |= test(f, "((..)|(.)){2}",                  "");
    e |= test(f, "((..)|(.)){3}",                  "");
    e |= test(f, "((..)|(.))*",                    "", "(0,0),(?,?),(?,?),(?,?)");

    e |= test(f, "((..)|(.))",                     "a", "(0,1),(0,1),(?,?),(0,1)");
    e |= test(f, "((..)|(.))((..)|(.))",           "a");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "a");
    e |= test(f, "((..)|(.)){1}",                  "a", "(0,1),(0,1),(?,?),(0,1)");
    e |= test(f, "((..)|(.)){2}",                  "a");
    e |= test(f, "((..)|(.)){3}",                  "a");
    e |= test(f, "((..)|(.))*",                    "a", "(0,1),(0,1),(?,?),(0,1)");

    e |= test(f, "((..)|(.))",                     "aa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aa",
              "(0,2),(0,1),(?,?),(0,1),(1,2),(?,?),(1,2)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aa");
    e |= test(f, "((..)|(.)){1}",                  "aa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aa", "(0,2),(0,1)(1,2),(?,?)(?,?),(0,1)(1,2)");
    e |= test(f, "((..)|(.)){3}",                  "aa");
    e |= test(f, "((..)|(.))*",                    "aa", "(0,2),(0,2),(0,2),(?,?)");

    e |= test(f, "((..)|(.))",                     "aaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaa",
              "(0,3),(0,2),(0,2),(?,?),(2,3),(?,?),(2,3)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaa",
              "(0,3),(0,1),(?,?),(0,1),(1,2),(?,?),(1,2),(2,3),(?,?),(2,3)");
    e |= test(f, "((..)|(.)){1}",                  "aaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaa", "(0,3),(0,2)(2,3),(0,2)(?,?),(?,?)(2,3)");
    e |= test(f, "((..)|(.)){3}",                  "aaa",
              "(0,3),(0,1)(1,2)(2,3),(?,?)(?,?)(?,?),(0,1)(1,2)(2,3)");
    e |= test(f, "((..)|(.))*",                    "aaa", "(0,3),(0,2)(2,3),(0,2)(?,?),(?,?)(2,3)");

    e |= test(f, "((..)|(.))",                     "aaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,3),(?,?),(2,3),(3,4),(?,?),(3,4)");
    e |= test(f, "((..)|(.)){1}",                  "aaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");
    e |= test(f, "((..)|(.)){3}",                  "aaaa",
              "(0,4),(0,2)(2,3)(3,4),(0,2)(?,?)(?,?),(?,?)(2,3)(3,4)");
    e |= test(f, "((..)|(.))*",                    "aaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");

    e |= test(f, "((..)|(.))",                     "aaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaaaa",
              "(0,5),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?),(4,5),(?,?),(4,5)");
    e |= test(f, "((..)|(.)){1}",                  "aaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");
    e |= test(f, "((..)|(.)){3}",                  "aaaaa",
              "(0,5),(0,2)(2,4)(4,5),(0,2)(2,4)(?,?),(?,?)(?,?)(4,5)");
    e |= test(f, "((..)|(.))*",                    "aaaaa",
              "(0,5),(0,2)(2,4)(4,5),(0,2)(2,4)(?,?),(?,?)(?,?)(4,5)");

    e |= test(f, "((..)|(.))",                     "aaaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaaaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaaaaa",
              "(0,6),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?),(4,6),(4,6),(?,?)");
    e |= test(f, "((..)|(.)){1}",                  "aaaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaaaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");
    e |= test(f, "((..)|(.)){3}",                  "aaaaaa",
              "(0,6),(0,2)(2,4)(4,6),(0,2)(2,4)(4,6),(?,?)(?,?)(?,?)");
    e |= test(f, "((..)|(.))*",                    "aaaaaa",
              "(0,6),(0,2)(2,4)(4,6),(0,2)(2,4)(4,6),(?,?)(?,?)(?,?)");

    e |= test(f, "X(.?){0,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){1,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){2,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){3,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){4,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){5,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){6,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){7,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){8,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){0,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){1,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){2,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){3,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){4,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){5,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){6,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){7,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){8,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");

    e |= test(f, "(a|ab|c|bcd){0,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){1,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){2,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){3,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){4,}(d*)",   "ababcd");
    e |= test(f, "(a|ab|c|bcd){0,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){1,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){2,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){3,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){4,10}(d*)", "ababcd");
    e |= test(f, "(a|ab|c|bcd)*(d*)",      "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd)+(d*)",      "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){0,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){1,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){2,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){3,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){4,}(d*)",   "ababcd");
    e |= test(f, "(ab|a|c|bcd){0,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){1,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){2,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){3,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){4,10}(d*)", "ababcd");
    e |= test(f, "(ab|a|c|bcd)*(d*)",      "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd)+(d*)",      "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");

    // rightassoc
    e |= test(f, "(a|ab)(c|bcd)(d*)",   "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(a|ab)(bcd|c)(d*)",   "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(ab|a)(c|bcd)(d*)",   "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(ab|a)(bcd|c)(d*)",   "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(a*)(b|abc)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)(abc|b)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)(b|abc)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)(abc|b)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a|ab)(c|bcd)(d|.*)", "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(a|ab)(bcd|c)(d|.*)", "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(ab|a)(c|bcd)(d|.*)", "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(ab|a)(bcd|c)(d|.*)", "abcd", "(0,4),(0,2),(2,3),(3,4)");

    if (!(f & REG_NFA)) {
        e |= test(f, "((a?){1,300})*",
                  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                  "(0,50),(0,50),"
                  "(0,1)(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,9)(9,10)"
                  "(10,11)(11,12)(12,13)(13,14)(14,15)(15,16)(16,17)(17,18)(18,19)(19,20)"
                  "(20,21)(21,22)(22,23)(23,24)(24,25)(25,26)(26,27)(27,28)(28,29)(29,30)"
                  "(30,31)(31,32)(32,33)(33,34)(34,35)(35,36)(36,37)(37,38)(38,39)(39,40)"
                  "(40,41)(41,42)(42,43)(43,44)(44,45)(45,46)(46,47)(47,48)(48,49)(49,50)");
    } else if (!(f & REG_SLOWPREC)) {
        e |= test(f, "((a?){1,1000})*", "aaaa", "(0,4),(0,4),(3,4)");

        e |= test(f, "(((((aa)|((a?)*))*){0,10}){0,10}){0,10}", "",
                  "(0,0),(0,0),(0,0),(0,0),(0,0),(?,?),(0,0),(0,0)");

        e |= test(f, "(((((aa)|((a?)*))*){0,10}){0,10}){0,10}", "aaa",
                  "(0,3),(0,3),(0,3),(0,3),(0,3),(?,?),(0,3),(2,3)");

        e |= test(f, "(((((aa)|((a?)*))*){0,10}){0,10}){0,10}", "aaaaa",
                  "(0,5),(0,5),(0,5),(0,5),(0,5),(?,?),(0,5),(4,5)");
    }

    e |= test(f, "((((a?)+)|(aa))+)", "aaa",
              "(0,3),(0,3),(0,3),(0,3),(0,1)(1,2)(2,3),(?,?)");

    e |= test(f, "(((aa)|((a?)+))+)", "aaa",
              "(0,3),(0,3),(0,3),(?,?),(0,3),(0,1)(1,2)(2,3)");

    e |= test(f, "((a?){1,2}|(a)*)*", "aaaa", "(0,4),(0,4),(?,?),(0,1)(1,2)(2,3)(3,4)");

    e |= test(f, "(((a?){2,3}|(a)*))*", "aaaaa",
              "(0,5),(0,5),(0,5),(?,?),(0,1)(1,2)(2,3)(3,4)(4,5)");

    e |= test(f, "(((a?)|(a?a?))+)", "aa", "(0,2),(0,2),(0,2),(?,?),(0,2)");

    e |= test(f, "((((a)*))*|((((a))*))+)*", "aa",
              "(0,2),(0,2),(0,2),(0,2),(0,1)(1,2),(?,?),(?,?),(?,?),(?,?)");

    e |= test(f, "(((a)*)*|((a)*)+)*", "aa", "(0,2),(0,2),(0,2),(0,1)(1,2),(?,?),(?,?)");

    e |= test(f, "(((a)+)|(((a)+)?))+", "aa",
              "(0,2),(0,2),(0,2),(0,1)(1,2),(?,?),(?,?),(?,?)");

    e |= test(f, "(a*|(a)*)*", "aa", "(0,2),(0,2),(?,?)");

    return e;
}

static int test_all_leftmost(int f) {
    int e = 0;

    e |= test(f, "a",        "a",    "(0,1)");
    e |= test(f, "(a)",      "a",    "(0,1),(0,1)");
    e |= test(f, "(a*)",     "aaa",  "(0,3),(0,3)");
    e |= test(f, "(a*)(b*)", "aabb", "(0,4),(0,2),(2,4)");
    e |= test(f, "(a*)(a*)", "aa",   "(0,2),(0,2),(2,2)");
    e |= test(f, "(a|aa)*",  "aa",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(a)|(a)",  "a",    "(0,1),(0,1),(?,?)");
    e |= test(f, "(a)*(a)*", "a",    "(0,1),(0,1),(?,?)");

    e |= test(f, "[a]",      "a",    "(0,1)");
    e |= test(f, "[a]",      "b");
    e |= test(f, "[^a]",     "a");
    e |= test(f, "[^a]",     "b",    "(0,1)");
    e |= test(f, "[ac]*",    "ac",   "(0,2)");
    e |= test(f, "[a-c]*",   "abc",  "(0,3)");
    e |= test(f, "[]]",      "]",    "(0,1)");
    e |= test(f, "[^]]",     "]");
    e |= test(f, "[^]]",     "a",    "(0,1)");
    e |= test(f, "[-]",      "-",    "(0,1)");
    e |= test(f, "[]-]*",    "]-",   "(0,2)");
    e |= test(f, "[-a]*",    "-a",   "(0,2)");
    e |= test(f, "[a-]*",    "-a",   "(0,2)");
    e |= test(f, "[-a-]*",   "-a",   "(0,2)");

    // basic
    e |= test(f, "(..)*(...)*",             "a",          "(0,0),(?,?),(?,?)");
    e |= test(f, "(..)*(...)*",             "abcd",       "(0,4),(0,2)(2,4),(?,?)");
    e |= test(f, "(ab|a)(bc|c)",            "abc",        "(0,3),(0,2),(2,3)");
    e |= test(f, "(ab)c|abc",               "abc",        "(0,3),(0,2)");
    e |= test(f, "(a*)(b?)(b+)b{3}",        "aaabbbbbbb", "(0,10),(0,3),(3,4),(4,7)");
    e |= test(f, "(a*)(b{0,1})(b{1,})b{3}", "aaabbbbbbb", "(0,10),(0,3),(3,4),(4,7)");
    e |= test(f, "((a|a)|a)",               "a",          "(0,1),(0,1),(0,1)");
    e |= test(f, "(a*)(a|aa)",              "aaaa",       "(0,4),(0,3),(3,4)");
    e |= test(f, "a*(a.|aa)",               "aaaa",       "(0,4),(2,4)");
    e |= test(f, "a(b)|c(d)|a(e)f",         "aef",        "(0,3),(?,?),(?,?),(1,2)");
    e |= test(f, "(a|b)?.*",                "b",          "(0,1),(0,1)");
    e |= test(f, "(a|b)c|a(b|c)",           "ac",         "(0,2),(0,1),(?,?)");
    e |= test(f, "(a|b)c|a(b|c)",           "ab",         "(0,2),(?,?),(1,2)");
    e |= test(f, "(a|b)*c|(a|ab)*c",        "abc",        "(0,3),(0,1)(1,2),(?,?)");
    e |= test(f, "(.a|.b).*|.*(.a|.b)",     "xa",         "(0,2),(0,2),(?,?)");
    e |= test(f, "a?(ab|ba)ab",             "abab",       "(0,4),(0,2)");
    e |= test(f, "a?(a[c]{0}b|ba)ab",       "abab",       "(0,4),(0,2)");
    e |= test(f, "ab|abab",                 "abbabab",    "(0,2)");
    e |= test(f, "(aa|aaa)*|(a|aaaaa)",     "aa",         "(0,2),(0,2),(?,?)");
    e |= test(f, "(a.|.a.)*|(a|.a...)",     "aa",         "(0,2),(0,2),(?,?)");
    e |= test(f, "(a)(b)(c)",               "abc",        "(0,3),(0,1),(1,2),(2,3)");

    e |= test(f, "((((((x))))))", "x", "(0,1),(0,1),(0,1),(0,1),(0,1),(0,1),(0,1)");
    e |= test(f, "((((((x))))))*", "xx",
              "(0,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2),(0,1)(1,2)");

    e |= test(f, "a?(ab|ba)*",
              "abababababababababababababababababababab"
              "ababababababababababababababababababababa",
              "(0,81),"
              "(1,3)(3,5)(5,7)(7,9)(9,11)(11,13)(13,15)(15,17)(17,19)(19,21)(21,23)"
              "(23,25)(25,27)(27,29)(29,31)(31,33)(33,35)(35,37)(37,39)(39,41)(41,43)"
              "(43,45)(45,47)(47,49)(49,51)(51,53)(53,55)(55,57)(57,59)(59,61)(61,63)"
              "(63,65)(65,67)(67,69)(69,71)(71,73)(73,75)(75,77)(77,79)(79,81)");

    e |= test(f, "a*a*a*a*a*b",   "aaaaaaaaab", "(0,10)");
    e |= test(f, "a[b]+bc",       "abbc",       "(0,4)");
    e |= test(f, "a[b]+bc",       "abbbbc",     "(0,6)");
    e |= test(f, "a[b]?bc",       "abbc",       "(0,4)");
    e |= test(f, "a[b]?bc",       "abc",        "(0,3)");
    e |= test(f, "a[b]?c",        "abc",        "(0,3)");
    e |= test(f, "ab|cd",         "abc",        "(0,2)");
    e |= test(f, "ab|cd",         "abcd",       "(0,2)");
    e |= test(f, "((a))",         "abc",        "(0,1),(0,1),(0,1)");
    e |= test(f, "(a)b(c)",       "abc",        "(0,3),(0,1),(2,3)");
    e |= test(f, "a*",            "aaa",        "(0,3)");
    e |= test(f, "(a*)*",         "-",          "(0,0),(0,0)");
    e |= test(f, "(a*)+",         "-",          "(0,0),(0,0)");
    e |= test(f, "(a*|b)*",       "-",          "(0,0),(0,0)");
    e |= test(f, "(a+|b)*",       "ab",         "(0,2),(0,1)(1,2)");
    e |= test(f, "(a+|b)+",       "ab",         "(0,2),(0,1)(1,2)");
    e |= test(f, "(a+|b)?",       "ab",         "(0,1),(0,1)");
    e |= test(f, "([abc])*d",     "abbbcd",     "(0,6),(0,1)(1,2)(2,3)(3,4)(4,5)");
    e |= test(f, "([abc])*bcd",   "abcd",       "(0,4),(0,1)");
    e |= test(f, "a|b|c|d|e",     "e",          "(0,1)");
    e |= test(f, "(a|b|c|d|e)f",  "ef",         "(0,2),(0,1)");
    e |= test(f, "((a*|b))*",     "-",          "(0,0),(0,0),(0,0)");
    e |= test(f, "(ab|a[b]*)bc",  "abc",        "(0,3),(0,1)");
    e |= test(f, "a([bc]*)c*",    "abc",        "(0,3),(1,3)");
    e |= test(f, "a([bc]*)(c*d)", "abcd",       "(0,4),(1,3),(3,4)");
    e |= test(f, "a([bc]+)(c*d)", "abcd",       "(0,4),(1,3),(3,4)");
    e |= test(f, "a([bc]*)(c+d)", "abcd",       "(0,4),(1,2),(2,4)");
    e |= test(f, "a[bcd]*dcdcde", "adcdcde",    "(0,7)");
    e |= test(f, "(ab|a)b*c",     "abc",        "(0,3),(0,2)");
    e |= test(f, "((a)(b)c)(d)",  "abcd",       "(0,4),(0,3),(0,1),(1,2),(3,4)");
    e |= test(f, "(.*)c(.*)",     "abcde",      "(0,5),(0,2),(3,5)");
    e |= test(f, "a(bc)d",        "abcd",       "(0,4),(1,3)");
    e |= test(f, "a+(b|c)*d+",    "aabcdd",     "(0,6),(2,3)(3,4)");

    // categorize
    e |= test(f, "(a*)(ab)*(b*)", "abc", "(0,2),(0,1),(?,?),(1,2)");

    e |= test(f, "((a*)(ab)*)((b*)(a*))", "aba", "(0,3),(0,1),(0,1),(?,?),(1,3),(1,2),(2,3)");

    e |= test(f, "(...?.?)*",          "xxxxxx", "(0,6),(0,4)(4,6)");
    e |= test(f, "(a|ab)(bc|c)",       "abcabc", "(0,3),(0,1),(1,3)");
    e |= test(f, "(aba|a*b)(aba|a*b)", "ababa",  "(0,5),(0,2),(2,5)");
    e |= test(f, "(a*){2}",            "xxxxx",  "(0,0),(0,0)(0,0)");
    e |= test(f, "(a*)*",              "a",      "(0,1),(0,1)");
    e |= test(f, "(aba|a*b)*",         "ababa",  "(0,5),(0,2)(2,5)");
    e |= test(f, "(a(b)?)+",           "aba",    "(0,3),(0,2)(2,3),(1,2)(?,?)");
    e |= test(f, ".*(.*)",             "ab",     "(0,2),(2,2)");

    e |= test(f, "(a?)((ab)?)(b?)a?(ab)?b?", "abab", "(0,4),(0,1),(1,1),(?,?),(1,2),(?,?)");

    // forcedassoc
    e |= test(f, "(a|ab)(c|bcd)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "(a|ab)(bcd|c)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "(ab|a)(c|bcd)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "(ab|a)(bcd|c)",       "abcd", "(0,4),(0,1),(1,4)");
    e |= test(f, "((a|ab)(c|bcd))(d*)", "abcd", "(0,4),(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "((a|ab)(bcd|c))(d*)", "abcd", "(0,4),(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "((ab|a)(c|bcd))(d*)", "abcd", "(0,4),(0,3),(0,2),(2,3),(3,4)");
    e |= test(f, "((ab|a)(bcd|c))(d*)", "abcd", "(0,4),(0,3),(0,2),(2,3),(3,4)");
    e |= test(f, "(a|ab)((c|bcd)(d*))", "abcd", "(0,4),(0,1),(1,4),(1,4),(4,4)");
    e |= test(f, "(a|ab)((bcd|c)(d*))", "abcd", "(0,4),(0,1),(1,4),(1,4),(4,4)");
    e |= test(f, "(ab|a)((c|bcd)(d*))", "abcd", "(0,4),(0,2),(2,4),(2,3),(3,4)");
    e |= test(f, "(ab|a)((bcd|c)(d*))", "abcd", "(0,4),(0,2),(2,4),(2,3),(3,4)");
    e |= test(f, "(a*)(b|abc)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "(a*)(abc|b)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "((a*)(b|abc))(c*)",   "abc",  "(0,3),(0,2),(0,1),(1,2),(2,3)");
    e |= test(f, "((a*)(abc|b))(c*)",   "abc",  "(0,3),(0,2),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)((b|abc)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a*)((abc|b)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a*)(b|abc)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "(a*)(abc|b)",         "abc",  "(0,3),(0,0),(0,3)");
    e |= test(f, "((a*)(b|abc))(c*)",   "abc",  "(0,3),(0,2),(0,1),(1,2),(2,3)");
    e |= test(f, "((a*)(abc|b))(c*)",   "abc",  "(0,3),(0,2),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)((b|abc)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a*)((abc|b)(c*))",   "abc",  "(0,3),(0,1),(1,3),(1,2),(2,3)");
    e |= test(f, "(a|ab)",              "ab",   "(0,2),(0,2)");
    e |= test(f, "(ab|a)",              "ab",   "(0,2),(0,2)");
    e |= test(f, "(a|ab)(b*)",          "ab",   "(0,2),(0,1),(1,2)");
    e |= test(f, "(ab|a)(b*)",          "ab",   "(0,2),(0,2),(2,2)");

    // glennfowler
    e |= test(f, "(a?)((ab)?)",       "ab", "(0,2),(0,0),(0,2),(0,2)");
    e |= test(f, "(a?)((ab)?)(b?)",   "ab", "(0,2),(0,1),(1,1),(?,?),(1,2)");
    e |= test(f, "((a?)((ab)?))(b?)", "ab", "(0,2),(0,1),(0,1),(1,1),(?,?),(1,2)");
    e |= test(f, "(a?)(((ab)?)(b?))", "ab", "(0,2),(0,1),(1,2),(1,1),(?,?),(1,2)");

    e |= test(f, "(.?)",               "x",   "(0,1),(0,1)");
    e |= test(f, "(.?){1}",            "x",   "(0,1),(0,1)");
    e |= test(f, "(.?)(.?)",           "x",   "(0,1),(0,1),(1,1)");
    e |= test(f, "(.?){2}",            "x",   "(0,1),(0,1)(1,1)");
    e |= test(f, "(.?)*",              "x",   "(0,1),(0,1)");
    e |= test(f, "(.?.?)",             "xxx", "(0,2),(0,2)");
    e |= test(f, "(.?.?){1}",          "xxx", "(0,2),(0,2)");
    e |= test(f, "(.?.?)(.?.?)",       "xxx", "(0,3),(0,2),(2,3)");
    e |= test(f, "(.?.?){2}",          "xxx", "(0,3),(0,2)(2,3)");
    e |= test(f, "(.?.?)(.?.?)(.?.?)", "xxx", "(0,3),(0,2),(2,3),(3,3)");
    e |= test(f, "(.?.?){3}",          "xxx", "(0,3),(0,2)(2,3)(3,3)");
    e |= test(f, "(.?.?)*",            "xxx", "(0,3),(0,2)(2,3)");

    e |= test(f, "a?((ab)?)(b?)",                  "ab",    "(0,2),(1,1),(?,?),(1,2)");
    e |= test(f, "(a?)((ab)?)b?",                  "ab",    "(0,2),(0,1),(1,1),(?,?)");
    e |= test(f, "a?((ab)?)b?",                    "ab",    "(0,2),(1,1),(?,?)");
    e |= test(f, "(ab?)(b?a)",                     "aba",   "(0,3),(0,2),(2,3)");
    e |= test(f, "(a|ab)(ba|a)",                   "aba",   "(0,3),(0,1),(1,3)");
    e |= test(f, "(a|ab|ba)",                      "aba",   "(0,2),(0,2)");
    e |= test(f, "(a|ab|ba)(a|ab|ba)",             "aba",   "(0,3),(0,1),(1,3)");
    e |= test(f, "(a|ab|ba)*",                     "aba",   "(0,3),(0,1)(1,3)");
    e |= test(f, "(aba|a*b)",                      "ababa", "(0,3),(0,3)");
    e |= test(f, "(aba|a*b)(aba|a*b)",             "ababa", "(0,5),(0,2),(2,5)");
    e |= test(f, "(aba|a*b)(aba|a*b)(aba|a*b)",    "ababa");
    e |= test(f, "(aba|ab|a)",                     "ababa", "(0,3),(0,3)");
    e |= test(f, "(aba|ab|a)(aba|ab|a)",           "ababa", "(0,5),(0,2),(2,5)");
    e |= test(f, "(aba|ab|a)(aba|ab|a)(aba|ab|a)", "ababa", "(0,5),(0,2),(2,4),(4,5)");
    e |= test(f, "(aba|ab|a)*",                    "ababa", "(0,5),(0,2)(2,5)");

    e |= test(f, "(a(b)?)",        "aba", "(0,2),(0,2),(1,2)");
    e |= test(f, "(a(b)?)(a(b)?)", "aba", "(0,3),(0,2),(1,2),(2,3),(?,?)");

    e |= test(f, "(.*)(.*)",               "xx",      "(0,2),(0,2),(2,2)");
    e |= test(f, ".*(.*)",                 "xx",      "(0,2),(2,2)");
    e |= test(f, "(a.*z|b.*y)",            "azbazby", "(0,5),(0,5)");
    e |= test(f, "(a.*z|b.*y)(a.*z|b.*y)", "azbazby", "(0,7),(0,5),(5,7)");
    e |= test(f, "(a.*z|b.*y)*",           "azbazby", "(0,7),(0,5)(5,7)");
    e |= test(f, "(.|..)(.*)",             "ab",      "(0,2),(0,1),(1,2)");

    e |= test(f, "((..)*(...)*)",              "xxx", "(0,3),(0,3),(?,?),(0,3)");
    e |= test(f, "((..)*(...)*)*",             "xxx", "(0,3),(0,3),(?,?),(0,3)");
    e |= test(f, "((..)*(...)*)((..)*(...)*)", "xxx", "(0,3),(0,3),(?,?),(0,3),(3,3),(?,?),(?,?)");

    // nullsubexpr
    e |= test(f, "(a*)*",        "a",        "(0,1),(0,1)");
    e |= test(f, "(a*)*",        "x",        "(0,0),(0,0)");
    e |= test(f, "(a*)*",        "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a*)*",        "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "(a*)+",        "a",        "(0,1),(0,1)");
    e |= test(f, "(a*)+",        "x",        "(0,0),(0,0)");
    e |= test(f, "(a*)+",        "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a*)+",        "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "(a+)*",        "a",        "(0,1),(0,1)");
    e |= test(f, "(a+)*",        "x",        "(0,0),(?,?)");
    e |= test(f, "(a+)*",        "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a+)*",        "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "(a+)+",        "a",        "(0,1),(0,1)");
    e |= test(f, "(a+)+",        "x");
    e |= test(f, "(a+)+",        "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "(a+)+",        "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "([a]*)*",      "a",        "(0,1),(0,1)");
    e |= test(f, "([a]*)*",      "x",        "(0,0),(0,0)");
    e |= test(f, "([a]*)*",      "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([a]*)*",      "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "([a]*)+",      "a",        "(0,1),(0,1)");
    e |= test(f, "([a]*)+",      "x",        "(0,0),(0,0)");
    e |= test(f, "([a]*)+",      "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([a]*)+",      "aaaaaax",  "(0,6),(0,6)");
    e |= test(f, "([^b]*)*",     "a",        "(0,1),(0,1)");
    e |= test(f, "([^b]*)*",     "b",        "(0,0),(0,0)");
    e |= test(f, "([^b]*)*",     "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([^b]*)*",     "aaaaaab",  "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",     "a",        "(0,1),(0,1)");
    e |= test(f, "([ab]*)*",     "aaaaaa",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",     "ababab",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",     "bababa",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",     "b",        "(0,1),(0,1)");
    e |= test(f, "([ab]*)*",     "bbbbbb",   "(0,6),(0,6)");
    e |= test(f, "([ab]*)*",     "aaaabcde", "(0,5),(0,5)");
    e |= test(f, "([^a]*)*",     "b",        "(0,1),(0,1)");
    e |= test(f, "([^a]*)*",     "bbbbbb",   "(0,6),(0,6)");
    e |= test(f, "([^a]*)*",     "aaaaaa",   "(0,0),(0,0)");
    e |= test(f, "([^ab]*)*",    "ccccxx",   "(0,6),(0,6)");
    e |= test(f, "([^ab]*)*",    "ababab",   "(0,0),(0,0)");
    e |= test(f, "((z)+|a)*",    "zabcde",   "(0,2),(0,1)(1,2),(0,1)(?,?)");
    e |= test(f, "(a)",          "aaa",      "(0,1),(0,1)");
    e |= test(f, "(a*)*(x)",     "x",        "(0,1),(0,0),(0,1)");
    e |= test(f, "(a*)*(x)",     "ax",       "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*)*(x)",     "axa",      "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*)+(x)",     "x",        "(0,1),(0,0),(0,1)");
    e |= test(f, "(a*)+(x)",     "ax",       "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*)+(x)",     "axa",      "(0,2),(0,1),(1,2)");
    e |= test(f, "(a*){2}(x)",   "x",        "(0,1),(0,0)(0,0),(0,1)");
    e |= test(f, "(a*){2}(x)",   "ax",       "(0,2),(0,1)(1,1),(1,2)");
    e |= test(f, "(a*){2}(x)",   "axa",      "(0,2),(0,1)(1,1),(1,2)");
    e |= test(f, "(()|.)(b)",    "ab",       "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "(()|[ab])(b)", "ab",       "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "(()|[ab])+b",  "aaab",     "(0,4),(0,1)(1,2)(2,3),(?,?)(?,?)(?,?)");
    e |= test(f, "(.|())(b)",    "ab",       "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "([ab]|())(b)", "ab",       "(0,2),(0,1),(?,?),(1,2)");
    e |= test(f, "([ab]|())+b",  "aaab",     "(0,4),(0,1)(1,2)(2,3),(?,?)(?,?)(?,?)");
    e |= test(f, "(.?)(b)",      "ab",       "(0,2),(0,1),(1,2)");

    // other
    e |= test(f, "(a|aa)*",    "aaa",  "(0,3),(0,1)(1,2)(2,3)");
    e |= test(f, "(a|aa)*",    "aaaa", "(0,4),(0,1)(1,2)(2,3)(3,4)");
    e |= test(f, "(aa|a)*",    "aaa",  "(0,3),(0,2)(2,3)");
    e |= test(f, "(aa|a)*",    "aaaa", "(0,4),(0,2)(2,4)");
    e |= test(f, "a|(a)",      "a",    "(0,1),(?,?)");
    e |= test(f, "(a)|a",      "a",    "(0,1),(0,1)");
    e |= test(f, "(b)a|b(a)",  "ba",   "(0,2),(0,1),(?,?)");
    e |= test(f, "b(a)|(b)a",  "ba",   "(0,2),(1,2),(?,?)");
    e |= test(f, "a*|(a|aa)*", "aa",   "(0,2),(?,?)");
    e |= test(f, "(a|aa)*|a*", "aa",   "(0,2),(0,1)(1,2)");

    e |= test(f, "(aa*|aaa*)*",                  "aaaaaa", "(0,6),(0,6)");
    e |= test(f, "(aa*|aaa*)(aa*|aaa*)",         "aaaaaa", "(0,6),(0,5),(5,6)");
    e |= test(f, "(aa*|aaa*){2}",                "aaaaaa", "(0,6),(0,5)(5,6)");
    e |= test(f, "((aa)*|(aaa)*)((aa)*|(aaa)*)", "aaaaaa",
              "(0,6),(0,6),(0,2)(2,4)(4,6),(?,?),(6,6),(?,?),(?,?)");
    e |= test(f, "((aa)*|(aaa)*){2}",            "aaaaaa",
              "(0,6),(0,6)(6,6),(0,2)(2,4)(4,6)(?,?),(?,?)(?,?)");
    e |= test(f, "(aa)*|(aaa)*",                 "aaaaaa", "(0,6),(0,2)(2,4)(4,6),(?,?)");

    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XY",         "(0,2),(0,1)(1,2)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XabY",       "(0,4),(0,2)(2,4)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XababY",     "(0,6),(0,1)(1,5)(5,6)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XabababY",   "(0,8),(0,2)(2,6)(6,8)");
    e |= test(f, "(X|Xa|Xab|Xaba|abab|baba|bY|Y)*", "XababababY", "(0,10),(0,1)(1,5)(5,9)(9,10)");

    e |= test(f, "(y){2}",        "");
    e |= test(f, "(y){2}",        "y");
    e |= test(f, "(y){2}",        "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){0,2}",      "",     "(0,0),(?,?)");
    e |= test(f, "(y){0,2}",      "y",    "(0,1),(0,1)");
    e |= test(f, "(y){0,2}",      "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){1,2}",      "");
    e |= test(f, "(y){1,2}",      "y",    "(0,1),(0,1)");
    e |= test(f, "(y){1,2}",      "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){1,2}y",     "");
    e |= test(f, "(y){1,2}y",     "y");
    e |= test(f, "(y){1,2}y",     "yy",   "(0,2),(0,1)");
    e |= test(f, "(y){1,2}y",     "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y){1,2}y?",    "");
    e |= test(f, "(y){1,2}y?",    "y",    "(0,1),(0,1)");
    e |= test(f, "(y){1,2}y?",    "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){1,2}y?",    "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y){2,}",       "");
    e |= test(f, "(y){2,}",       "y");
    e |= test(f, "(y){2,}",       "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y){2,}",       "yyy",  "(0,3),(0,1)(1,2)(2,3)");
    e |= test(f, "(y?){2}",       "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){2}",       "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){2}",       "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){0,2}",     "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){0,2}",     "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){0,2}",     "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}",     "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){1,2}",     "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){1,2}",     "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}y",    "");
    e |= test(f, "(y?){1,2}y",    "y",    "(0,1),(0,0)(0,0)");
    e |= test(f, "(y?){1,2}y",    "yy",   "(0,2),(0,1)(1,1)");
    e |= test(f, "(y?){1,2}y",    "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}y?",   "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){1,2}y?",   "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){1,2}y?",   "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){1,2}y?",   "yyy",  "(0,3),(0,1)(1,2)");
    e |= test(f, "(y?){2,}",      "",     "(0,0),(0,0)(0,0)");
    e |= test(f, "(y?){2,}",      "y",    "(0,1),(0,1)(1,1)");
    e |= test(f, "(y?){2,}",      "yy",   "(0,2),(0,1)(1,2)");
    e |= test(f, "(y?){2,}",      "yyy",  "(0,3),(0,1)(1,2)(2,3)");
    e |= test(f, "(y|(x?)){1,3}", "y",    "(0,1),(0,1)(1,1)(1,1),(?,?)(1,1)(1,1)");
    e |= test(f, "(y[y]?){3}",    "yyyy", "(0,4),(0,2)(2,3)(3,4)");

    // repetition
    e |= test(f, "((..)|(.))",                     "");
    e |= test(f, "((..)|(.))((..)|(.))",           "");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "");
    e |= test(f, "((..)|(.)){1}",                  "");
    e |= test(f, "((..)|(.)){2}",                  "");
    e |= test(f, "((..)|(.)){3}",                  "");
    e |= test(f, "((..)|(.))*",                    "", "(0,0),(?,?),(?,?),(?,?)");

    e |= test(f, "((..)|(.))",                     "a", "(0,1),(0,1),(?,?),(0,1)");
    e |= test(f, "((..)|(.))((..)|(.))",           "a");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "a");
    e |= test(f, "((..)|(.)){1}",                  "a", "(0,1),(0,1),(?,?),(0,1)");
    e |= test(f, "((..)|(.)){2}",                  "a");
    e |= test(f, "((..)|(.)){3}",                  "a");
    e |= test(f, "((..)|(.))*",                    "a", "(0,1),(0,1),(?,?),(0,1)");

    e |= test(f, "((..)|(.))",                     "aa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aa",
              "(0,2),(0,1),(?,?),(0,1),(1,2),(?,?),(1,2)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aa");
    e |= test(f, "((..)|(.)){1}",                  "aa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aa", "(0,2),(0,1)(1,2),(?,?)(?,?),(0,1)(1,2)");
    e |= test(f, "((..)|(.)){3}",                  "aa");
    e |= test(f, "((..)|(.))*",                    "aa", "(0,2),(0,2),(0,2),(?,?)");

    e |= test(f, "((..)|(.))",                     "aaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaa",
              "(0,3),(0,2),(0,2),(?,?),(2,3),(?,?),(2,3)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaa",
              "(0,3),(0,1),(?,?),(0,1),(1,2),(?,?),(1,2),(2,3),(?,?),(2,3)");
    e |= test(f, "((..)|(.)){1}",                  "aaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaa", "(0,3),(0,2)(2,3),(0,2)(?,?),(?,?)(2,3)");
    e |= test(f, "((..)|(.)){3}",                  "aaa",
              "(0,3),(0,1)(1,2)(2,3),(?,?)(?,?)(?,?),(0,1)(1,2)(2,3)");
    e |= test(f, "((..)|(.))*",                    "aaa", "(0,3),(0,2)(2,3),(0,2)(?,?),(?,?)(2,3)");

    e |= test(f, "((..)|(.))",                     "aaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,3),(?,?),(2,3),(3,4),(?,?),(3,4)");
    e |= test(f, "((..)|(.)){1}",                  "aaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");
    e |= test(f, "((..)|(.)){3}",                  "aaaa",
              "(0,4),(0,2)(2,3)(3,4),(0,2)(?,?)(?,?),(?,?)(2,3)(3,4)");
    e |= test(f, "((..)|(.))*",                    "aaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");

    e |= test(f, "((..)|(.))",                     "aaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaaaa",
              "(0,5),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?),(4,5),(?,?),(4,5)");
    e |= test(f, "((..)|(.)){1}",                  "aaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");
    e |= test(f, "((..)|(.)){3}",                  "aaaaa",
              "(0,5),(0,2)(2,4)(4,5),(0,2)(2,4)(?,?),(?,?)(?,?)(4,5)");
    e |= test(f, "((..)|(.))*",                    "aaaaa",
              "(0,5),(0,2)(2,4)(4,5),(0,2)(2,4)(?,?),(?,?)(?,?)(4,5)");

    e |= test(f, "((..)|(.))",                     "aaaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))",           "aaaaaa",
              "(0,4),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?)");
    e |= test(f, "((..)|(.))((..)|(.))((..)|(.))", "aaaaaa",
              "(0,6),(0,2),(0,2),(?,?),(2,4),(2,4),(?,?),(4,6),(4,6),(?,?)");
    e |= test(f, "((..)|(.)){1}",                  "aaaaaa", "(0,2),(0,2),(0,2),(?,?)");
    e |= test(f, "((..)|(.)){2}",                  "aaaaaa",
              "(0,4),(0,2)(2,4),(0,2)(2,4),(?,?)(?,?)");
    e |= test(f, "((..)|(.)){3}",                  "aaaaaa",
              "(0,6),(0,2)(2,4)(4,6),(0,2)(2,4)(4,6),(?,?)(?,?)(?,?)");
    e |= test(f, "((..)|(.))*",                    "aaaaaa",
              "(0,6),(0,2)(2,4)(4,6),(0,2)(2,4)(4,6),(?,?)(?,?)(?,?)");

    e |= test(f, "X(.?){0,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){1,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){2,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){3,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){4,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){5,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){6,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");
    e |= test(f, "X(.?){7,}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)");

    e |= test(f, "X(.?){8,}Y",  "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){0,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){1,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){2,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){3,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){4,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){5,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){6,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){7,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");
    e |= test(f, "X(.?){8,8}Y", "X1234567Y", "(0,9),(1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,8)");

    e |= test(f, "(a|ab|c|bcd){0,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){1,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){2,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){3,}(d*)",   "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){4,}(d*)",   "ababcd");
    e |= test(f, "(a|ab|c|bcd){0,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){1,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){2,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){3,10}(d*)", "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd){4,10}(d*)", "ababcd");
    e |= test(f, "(a|ab|c|bcd)*(d*)",      "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(a|ab|c|bcd)+(d*)",      "ababcd", "(0,6),(0,2)(2,3)(3,6),(6,6)");
    e |= test(f, "(ab|a|c|bcd){0,}(d*)",   "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){1,}(d*)",   "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){2,}(d*)",   "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){3,}(d*)",   "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){4,}(d*)",   "ababcd");
    e |= test(f, "(ab|a|c|bcd){0,10}(d*)", "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){1,10}(d*)", "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){2,10}(d*)", "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){3,10}(d*)", "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd){4,10}(d*)", "ababcd");
    e |= test(f, "(ab|a|c|bcd)*(d*)",      "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");
    e |= test(f, "(ab|a|c|bcd)+(d*)",      "ababcd", "(0,6),(0,2)(2,4)(4,5),(5,6)");

    // rightassoc
    e |= test(f, "(a|ab)(c|bcd)(d*)",   "abcd", "(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "(a|ab)(bcd|c)(d*)",   "abcd", "(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "(ab|a)(c|bcd)(d*)",   "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(ab|a)(bcd|c)(d*)",   "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(a*)(b|abc)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)(abc|b)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)(b|abc)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a*)(abc|b)(c*)",     "abc",  "(0,3),(0,1),(1,2),(2,3)");
    e |= test(f, "(a|ab)(c|bcd)(d|.*)", "abcd", "(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "(a|ab)(bcd|c)(d|.*)", "abcd", "(0,4),(0,1),(1,4),(4,4)");
    e |= test(f, "(ab|a)(c|bcd)(d|.*)", "abcd", "(0,4),(0,2),(2,3),(3,4)");
    e |= test(f, "(ab|a)(bcd|c)(d|.*)", "abcd", "(0,4),(0,2),(2,3),(3,4)");

    // other
    std::string s = "(0,4),(0,4),(0,1)(1,2)(2,3)(3,4)";
    for (size_t i = 0; i < 1000 - 4; ++i) s += "(4,4)";

    e |= test(f, "((a?){1,1000})*", "aaaa", s.c_str());

    return e;
}

static int test_all_tstring() {
    int e = 0;

    e |= test_tstring("a",        "a",   "1 a 2 ");
    e |= test_tstring("(a)",      "a",   "1 3 a 4 2 ");
    e |= test_tstring("(((a)))",  "a",   "1 3 a 4 2 ");
    e |= test_tstring("(a)*",     "aaa", "1 3 a 4 3 a 4 3 a 4 2 ");
    e |= test_tstring("(a(b?))*", "aba", "1 3 5 a 6 7 b 8 4 3 5 a 6 7 8 4 2 ");
    e |= test_tstring("(a(b)?)*", "aba", "1 3 5 a 6 7 9 b 10 8 4 3 5 a 6 7 8 4 2 ");
    e |= test_tstring("(a(b*))*", "abb", "1 3 5 a 6 7 b b 8 4 2 ");
    e |= test_tstring("(a(b)*)*", "abb", "1 3 5 a 6 7 9 b 10 9 b 10 8 4 2 ");
    e |= test_tstring("(a){2}",   "aa",  "1 3 a 4 3 a 4 2 ");
    e |= test_tstring("ab",       "ab",  "1 a b 2 ");
    e |= test_tstring("a(b)",     "ab",  "1 3 a 4 5 b 6 2 ");
    e |= test_tstring("(a)b",     "ab",  "1 3 a 4 5 b 6 2 ");
    e |= test_tstring("(a)(b)",   "ab",  "1 3 a 4 5 b 6 2 ");

    return e;
}

int main() {
    int e = 0;

    e |= test_all_posix(0);
    e |= test_all_posix(REG_MULTIPASS);
    e |= test_all_posix(REG_SUBHIST);
    e |= test_all_posix(REG_SUBHIST | REG_MULTIPASS);

    e |= test_all_leftmost(REG_LEFTMOST);
    e |= test_all_leftmost(REG_LEFTMOST | REG_MULTIPASS);
    e |= test_all_leftmost(REG_LEFTMOST | REG_SUBHIST);
    e |= test_all_leftmost(REG_LEFTMOST | REG_SUBHIST | REG_MULTIPASS);

    e |= test_all_posix(REG_NFA);
    e |= test_all_posix(REG_NFA | REG_TRIE);
    e |= test_all_posix(REG_NFA | REG_SLOWPREC);

    e |= test_all_leftmost(REG_NFA | REG_LEFTMOST);
    e |= test_all_leftmost(REG_NFA | REG_LEFTMOST | REG_TRIE);

    e |= test_all_tstring();

    return e;
}
