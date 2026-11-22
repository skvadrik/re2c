// simdjson (https://github.com/simdjson/simdjson) on the json data set, as an upper-bound
// reference for SIMD text processing. This is NOT the same task as the vec_* lexers: simdjson
// validates and parses JSON (the data file is a sequence of JSON documents, parsed with
// parse_many/iterate_many), it does not produce the token stream of re2c/vec_strings_rules.re.
//
// - dom: full DOM parse of all documents (stage 1 structural indexing + stage 2 tape building,
//   including unescaping of all strings).
// - ondemand: On-Demand parse that visits every value and unescapes every key and string.
// - stage1: only the SIMD structural indexing (stage 1) of the whole file, through the internal
//   dom_parser_implementation interface.
//
// Built only with -DRE2C_BENCH_SIMDJSON=ON (simdjson is found with pkg-config); requires C++17.
// Threaded document streams are disabled, so that everything runs on the benchmarked CPU.

#include <stdio.h>
#include <stdlib.h>
#include <simdjson.h>

#include "ref/vec_ref.h"

namespace ref_simdjson {

static simdjson::padded_string load(const char *input) {
    simdjson::padded_string json;
    if (simdjson::padded_string::load(input).get(json)) abort();
    return json;
}

static simdjson::error_code parse_dom(
        simdjson::dom::parser &parser, const simdjson::padded_string &json, long &docs) {
    simdjson::dom::document_stream stream;
    auto err = parser.parse_many(json).get(stream);
    if (err) return err;
    docs = 0;
    for (auto doc : stream) {
        if (doc.error()) return doc.error();
        ++docs;
    }
    return simdjson::SUCCESS;
}

// Visit a value recursively, unescape all keys and strings and parse all numbers.
static simdjson::error_code visit(simdjson::ondemand::value v, size_t &sum) {
    simdjson::ondemand::json_type t;
    auto err = v.type().get(t);
    if (err) return err;
    switch (t) {
    case simdjson::ondemand::json_type::object: {
        simdjson::ondemand::object obj;
        if ((err = v.get_object().get(obj))) return err;
        for (auto field : obj) {
            std::string_view key;
            if ((err = field.unescaped_key().get(key))) return err;
            sum += key.size();
            simdjson::ondemand::value fv;
            if ((err = field.value().get(fv))) return err;
            if ((err = visit(fv, sum))) return err;
        }
        break;
    }
    case simdjson::ondemand::json_type::array: {
        simdjson::ondemand::array arr;
        if ((err = v.get_array().get(arr))) return err;
        for (auto elem : arr) {
            simdjson::ondemand::value ev;
            if ((err = elem.get(ev))) return err;
            if ((err = visit(ev, sum))) return err;
        }
        break;
    }
    case simdjson::ondemand::json_type::string: {
        std::string_view s;
        if ((err = v.get_string().get(s))) return err;
        sum += s.size();
        break;
    }
    case simdjson::ondemand::json_type::number: {
        double d;
        if ((err = v.get_double().get(d))) return err;
        sum += 1;
        break;
    }
    case simdjson::ondemand::json_type::boolean: {
        bool b;
        if ((err = v.get_bool().get(b))) return err;
        sum += b;
        break;
    }
    case simdjson::ondemand::json_type::null:
        if (!v.is_null()) return simdjson::INCORRECT_TYPE;
        break;
    default:
        return simdjson::INCORRECT_TYPE;
    }
    return simdjson::SUCCESS;
}

static simdjson::error_code parse_ondemand(simdjson::ondemand::parser &parser,
        const simdjson::padded_string &json, long &docs, size_t &sum) {
    simdjson::ondemand::document_stream stream;
    auto err = parser.iterate_many(json).get(stream);
    if (err) return err;
    docs = 0;
    sum = 0;
    for (auto doc : stream) {
        simdjson::ondemand::value v;
        if ((err = doc.get_value().get(v))) return err;
        if ((err = visit(v, sum))) return err;
        ++docs;
    }
    return simdjson::SUCCESS;
}

void bench_dom::operator()(benchmark::State &state, const char* input, long expected) const {
    simdjson::padded_string json = load(input);
    simdjson::dom::parser parser;
    parser.threaded = false;
    long docs = 0;
    simdjson::error_code err = simdjson::SUCCESS;
    for (auto _ : state) {
        err = parse_dom(parser, json, docs);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)json.size());
    if (err || docs != expected) state.SkipWithError("simdjson: error");
}

void bench_ondemand::operator()(benchmark::State &state, const char* input, long expected) const {
    simdjson::padded_string json = load(input);
    simdjson::ondemand::parser parser;
    parser.threaded = false;
    long docs = 0;
    size_t sum = 0;
    simdjson::error_code err = simdjson::SUCCESS;
    for (auto _ : state) {
        err = parse_ondemand(parser, json, docs, sum);
        benchmark::DoNotOptimize(sum);
    }
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)json.size());
    if (err || docs != expected) state.SkipWithError("simdjson: error");
}

void bench_stage1::operator()(benchmark::State &state, const char* input, long) const {
    simdjson::padded_string json = load(input);
    const simdjson::implementation *impl = simdjson::get_active_implementation();
    std::unique_ptr<simdjson::internal::dom_parser_implementation> dp;
    simdjson::error_code err = impl->create_dom_parser_implementation(
        json.size(), simdjson::DEFAULT_MAX_DEPTH, dp);
    uint32_t n = 0;
    for (auto _ : state) {
        if (err) break;
        err = dp->stage1(reinterpret_cast<const uint8_t*>(json.data()), json.size(),
            simdjson::stage1_mode::regular);
        n = dp->n_structural_indexes;
        benchmark::DoNotOptimize(n);
    }
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)json.size());
    state.SetLabel(impl->name());
    if (err || n == 0) state.SkipWithError("simdjson: error");
}

bool test(const char* input, long expected_docs) {
    simdjson::padded_string json = load(input);
    bool ok = true;
    long docs = 0;
    size_t sum = 0;

    simdjson::dom::parser dparser;
    dparser.threaded = false;
    auto err = parse_dom(dparser, json, docs);
    if (err || docs != expected_docs) {
        fprintf(stderr, "simdjson dom: %s on %s, %ld documents (expected %ld)\n",
            simdjson::error_message(err), input, docs, expected_docs);
        ok = false;
    }

    simdjson::ondemand::parser oparser;
    oparser.threaded = false;
    err = parse_ondemand(oparser, json, docs, sum);
    if (err || docs != expected_docs) {
        fprintf(stderr, "simdjson ondemand: %s on %s, %ld documents (expected %ld)\n",
            simdjson::error_message(err), input, docs, expected_docs);
        ok = false;
    }

    fprintf(stderr, "simdjson: active implementation %s\n",
        simdjson::get_active_implementation()->name().c_str());
    return ok;
}

} // namespace ref_simdjson
