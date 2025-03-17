#include <benchmark/benchmark.h>

#include "re2c/base.h"
#include "ragel/base.h"

#define GROUP(qual, name, data, count1, count2) \
    benchmark::RegisterBenchmark(name "-" CXX "_re2c-simple", \
        re2c_##qual::bench_simple(), "data/" #data "/big", count2); \
    benchmark::RegisterBenchmark(name "-" CXX "_re2c-buffered-eof", \
        re2c_##qual::bench_buffered_eof(), "data/" #data "/big", count2); \
    benchmark::RegisterBenchmark(name "-" CXX "_re2c-buffered-scc", \
        re2c_##qual::bench_buffered_scc(), "data/" #data "/big", count2); \
    benchmark::RegisterBenchmark(name "-" CXX "_ragel-simple", \
        ragel_##qual::bench_simple(), "data/" #data "/big", count2); \
    benchmark::RegisterBenchmark(name "-" CXX "_ragel-buffered", \
        ragel_##qual::bench_buffered(), "data/" #data "/big", count2);

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);
    benchmark::SetDefaultTimeUnit(benchmark::kMillisecond);

    GROUP(lex_00__numbers1, "numbers1", numbers1, 230, 16777350);
    GROUP(lex_01__numbers2, "numbers2", numbers2, 5237, 76669680);
    GROUP(lex_02__words1, "words1", words1, 57, 16777266);
    GROUP(lex_03__words2, "words2", words2, 1933, 16778440);
    GROUP(lex_04__words3, "words3", words3, 15248, 16788048);

    GROUP(submatch_00__http_rfc7230, "http-rfc7230", http, 3474, 15445404);
    GROUP(submatch_01__http_simple, "http-simple", http, 3661, 16276806);
    GROUP(submatch_02__uri_rfc3986, "uri-rfc3986", uri, 1929, 16037706);
    GROUP(submatch_03__uri_simple, "uri-simple", uri, 1929, 16037706);
    GROUP(submatch_04__apache_log, "apache-log", apache, 177855, 16184805);
    GROUP(submatch_05__datetime, "datetime", datetime, 15000, 11985000);
    GROUP(submatch_06__email, "email", email, 961, 7141191);
    GROUP(submatch_07__ipv4, "ipv4", ipv4, 66, 10855878);

    GROUP(submatch_10__alt1_2, "alt1-2", alt1, 510, 16236360);
    GROUP(submatch_11__alt1_4, "alt1-4", alt1, 510, 16236360);
    GROUP(submatch_12__alt1_8, "alt1-8", alt1, 510, 16236360);
    GROUP(submatch_13__alt2_2, "alt2-2", alt2, 508, 16296132);
    GROUP(submatch_14__alt2_4, "alt2-4", alt2, 508, 16296132);
    GROUP(submatch_15__alt2_8, "alt2-8", alt2, 508, 16296132);
    GROUP(submatch_16__alt4_2, "alt4-2", alt4, 504, 16355808);
    GROUP(submatch_17__alt4_4, "alt4-4", alt4, 504, 16355808);
    GROUP(submatch_18__alt4_8, "alt4-8", alt4, 504, 16355808);

    GROUP(submatch_20__cat2_0, "cat2-0", cat2, 376, 16777496);
    GROUP(submatch_21__cat2_4, "cat2-4", cat2, 376, 16777496);
    GROUP(submatch_22__cat2_8, "cat2-8", cat2, 376, 16777496);
    GROUP(submatch_23__cat4_0, "cat4-0", cat4, 245, 16777355);
    GROUP(submatch_24__cat4_2, "cat4-2", cat4, 245, 16777355);
    GROUP(submatch_25__cat4_4, "cat4-4", cat4, 245, 16777355);
    GROUP(submatch_26__cat8_0, "cat8-0", cat8, 567, 16777530);
    GROUP(submatch_27__cat8_1, "cat8-1", cat8, 567, 16777530);
    GROUP(submatch_28__cat8_2, "cat8-2", cat8, 567, 16777530);

    GROUP(submatch_30__rep_cat_5_3_2, "rep-cat-5-3-2", rep, 18290, 16790220);
    GROUP(submatch_31__rep_cat_13_11_7, "rep-cat-13-11-7", rep, 18290, 16790220);
    GROUP(submatch_32__rep_cat_23_19_17, "rep-cat-23-19-17", rep, 18290, 16790220);
    GROUP(submatch_33__rep_alt_5_3_2, "rep-alt-5-3-2", rep, 18290, 16790220);
    GROUP(submatch_34__rep_alt_13_11_7, "rep-alt-13-11-7", rep, 18290, 16790220);
    GROUP(submatch_35__rep_alt_23_19_17, "rep-alt-23-19-17", rep, 18290, 16790220);
    GROUP(submatch_36__rep_5_rep_3_rep_2, "rep-5-rep-3-rep-2", rep, 18290, 16790220);
    GROUP(submatch_37__rep_13_rep_11_rep_7, "rep-13-rep-11-rep-7", rep, 18290, 16790220);
    GROUP(submatch_38__rep_23_rep_19_rep_17, "rep-23-rep-19-rep-17", rep, 18290, 16790220);

    benchmark::RunSpecifiedBenchmarks();

    return 0;
}
