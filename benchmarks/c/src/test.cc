#include "ragel/base.h"
#include "re2c/base.h"

enum Engine {
    E_RE2C = 0x1u,
    E_RAGEL = 0x2u
};

bool quick = false;
bool verbose = false;

#define TEST(name, data, count1, count2, except) do { \
    fprintf(stderr, "checking %s...\n", #name); \
    if ((except & E_RE2C) == 0) { \
        ok &= re2c_##name::test_yyfill_eofrule("data/" #data "/small", count1); \
        if (!quick) ok &= re2c_##name::test_yyfill_eofrule("data/" #data "/big", count2); \
        ok &= re2c_##name::test_yyfill_padding("data/" #data "/small", count1); \
        if (!quick) ok &= re2c_##name::test_yyfill_padding("data/" #data "/big", count2); \
    } \
    if ((except & E_RAGEL) == 0) { \
        ok &= ragel_##name::test("data/" #data "/small", count1); \
        if (!quick) ok &= ragel_##name::test("data/" #data "/big", count2); \
    } \
} while (0)

#define TEST_RAGEL_ERROR(name, data, count1, count2) do { \
    ok &= ragel_##name::test("data/" #data "/small", count1); \
    if (!quick) ok &= ragel_##name::test("data/" #data "/big", count2); \
} while (0)

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--quick") == 0) {
            quick = true;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else {
            fprintf(stderr, "usage: %s [--quick] [--verbose]\n", argv[0]);
            return 1;
        }
    }

    bool ok = true;

    TEST(submatch_00__http_rfc7230, http, 3474, 15445404, 0);
    TEST(submatch_01__http_simple, http, 3661, 16276806, 0);
    TEST(submatch_02__uri_rfc3986, uri, 1929, 16037706, 0);
    TEST(submatch_03__uri_simple, uri, 1929, 16037706, 0);
    TEST(submatch_04__apache_log, apache, 177855, 16184805, 0);
    TEST(submatch_05__datetime, datetime, 15000, 11985000, 0);
    TEST(submatch_06__email, email, 961, 7141191, 0);
    TEST(submatch_07__ipv4, ipv4, 66, 10855878, 0);

    TEST(submatch_10__alt1_2, alt1, 510, 16236360, 0);
    TEST(submatch_11__alt1_4, alt1, 510, 16236360, 0);
    TEST(submatch_12__alt1_8, alt1, 510, 16236360, 0);
    TEST(submatch_13__alt2_2, alt2, 508, 16296132, 0);
    TEST(submatch_14__alt2_4, alt2, 508, 16296132, 0);
    TEST(submatch_15__alt2_8, alt2, 508, 16296132, 0);
    TEST(submatch_16__alt4_2, alt4, 504, 16355808, 0);
    TEST(submatch_17__alt4_4, alt4, 504, 16355808, 0);
    TEST(submatch_18__alt4_8, alt4, 504, 16355808, 0);

    TEST(submatch_20__cat2_0, cat2, 376, 16777496, 0);
    TEST(submatch_21__cat2_4, cat2, 376, 16777496, 0);
    TEST(submatch_22__cat2_8, cat2, 376, 16777496, 0);
    TEST(submatch_23__cat4_0, cat4, 245, 16777355, 0);
    TEST(submatch_24__cat4_2, cat4, 245, 16777355, 0);
    TEST(submatch_25__cat4_4, cat4, 245, 16777355, 0);
    TEST(submatch_26__cat8_0, cat8, 567, 16777530, 0);
    TEST(submatch_27__cat8_1, cat8, 567, 16777530, 0);
    TEST(submatch_28__cat8_2, cat8, 567, 16777530, 0);

    TEST(submatch_30__rep_cat_5_3_2, rep, 18290, 16790220, E_RAGEL);
    TEST(submatch_31__rep_cat_13_11_7, rep, 18290, 16790220, E_RAGEL);
    TEST(submatch_32__rep_cat_23_19_17, rep, 18290, 16790220, E_RAGEL);
    TEST(submatch_33__rep_alt_5_3_2, rep, 18290, 16790220, 0);
    TEST(submatch_34__rep_alt_13_11_7, rep, 18290, 16790220, E_RAGEL);
    TEST(submatch_35__rep_alt_23_19_17, rep, 18290, 16790220, E_RAGEL);
    TEST(submatch_36__rep_5_rep_3_rep_2, rep, 18290, 16790220, 0);
    TEST(submatch_37__rep_13_rep_11_rep_7, rep, 18290, 16790220, E_RAGEL);
    TEST(submatch_38__rep_23_rep_19_rep_17, rep, 18290, 16790220, E_RAGEL);

    // Test that Ragel lexers still fail in the same way.
    TEST_RAGEL_ERROR(submatch_30__rep_cat_5_3_2, rep, 18290, 16790832);
    TEST_RAGEL_ERROR(submatch_31__rep_cat_13_11_7, rep, 18290, 16790832);
    TEST_RAGEL_ERROR(submatch_32__rep_cat_23_19_17, rep, 18290, 16790832);
    TEST_RAGEL_ERROR(submatch_34__rep_alt_13_11_7, rep, 18278, 5593068);
    TEST_RAGEL_ERROR(submatch_35__rep_alt_23_19_17, rep, 18285, 5595210);
    TEST_RAGEL_ERROR(submatch_37__rep_13_rep_11_rep_7, rep, 18278, 5593068);
    TEST_RAGEL_ERROR(submatch_38__rep_23_rep_19_rep_17, rep, 18285, 5595210);

    fprintf(stderr, "%s\n", ok ? "all good :)" : "*** error ***"); \
    return ok ? 0 : 1;
}
