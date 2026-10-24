//go:build ignore

#include <benchmark/benchmark.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
extern "C" {
#include "scanner.h"
typedef int (*Lex)(Input*, size_t*);
struct Variant { const char *name; Lex lex; bool checked; const char *family; };
#include "generated/variants.h"
}
struct Token { int kind; size_t length; };
struct Record { const unsigned char *data; size_t size; const Token *trace; size_t count; };
struct Fixture { const char *name, *family; const Record *records; size_t count; };
#include "generated/fixtures.h"

static uint64_t run(const Fixture& fixture, Lex lex, size_t capacity,
                    unsigned char *scratch, bool check) {
    uint64_t digest = 14695981039346656037ULL;
    for (size_t r = 0; r < fixture.count; ++r) {
        const Record& record = fixture.records[r];
        Input in = {};
        in.src = record.data; in.size = record.size; in.capacity = capacity;
        in.buf = scratch;
        if (capacity) {
            in.cur = in.tok = in.mar = in.lim = scratch;
        } else {
            in.cur = in.tok = in.mar = const_cast<unsigned char*>(record.data);
            in.lim = in.cur + record.size + PAD; in.eof = 1;
        }
        size_t tokens = 0, bytes = 0;
        for (;;) {
            size_t length = 0;
            int kind = lex(&in, &length);
            if (kind < 0 || (check && (tokens > record.count ||
                kind != record.trace[tokens].kind || length != record.trace[tokens].length))) {
                std::fprintf(stderr, "parity failure: %s record=%zu token=%zu\n", fixture.name, r, tokens);
                std::abort();
            }
            if (!kind) break;
            digest = (digest ^ static_cast<uint64_t>(kind)) * 1099511628211ULL;
            digest = (digest ^ length) * 1099511628211ULL;
            bytes += length; ++tokens;
        }
        if (check && (tokens != record.count || bytes != record.size || (capacity && !in.fills))) std::abort();
    }
    return digest;
}

int main(int argc, char **argv) {
    // Validate the entire token trace before timing, including refill boundaries.
    for (const auto& fixture : fixtures) for (const auto& variant : variants) {
        if (std::strcmp(fixture.family, variant.family)) continue;
        for (size_t capacity : {size_t(0), size_t(64), size_t(97), size_t(4096)}) {
            if (capacity && !variant.checked) continue;
            std::vector<unsigned char> scratch(capacity + PAD);
            run(fixture, variant.lex, capacity, scratch.data(), true);
        }
    }
    std::puts("all token traces match the independent oracle");
    if (argc == 2 && std::strcmp(argv[1], "--check") == 0) return 0;
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    for (const auto& fixture : fixtures) for (const auto& variant : variants) {
        if (std::strcmp(fixture.family, variant.family) || std::strstr(fixture.name, "edges")) continue;
        for (size_t capacity : {size_t(0), size_t(64), size_t(4096)}) {
            if (capacity && !variant.checked) continue;
            const std::string name = std::string(fixture.name) + "/" + variant.name + "/" +
                (capacity ? "refill" + std::to_string(capacity) : variant.checked ? "resident" : "nofill");
            benchmark::RegisterBenchmark(name.c_str(), [=](benchmark::State& state) {
                std::vector<unsigned char> scratch(capacity + PAD);
                size_t bytes = 0, tokens = 0;
                for (size_t r = 0; r < fixture.count; ++r) {
                    bytes += fixture.records[r].size; tokens += fixture.records[r].count;
                }
                const auto expected = run(fixture, variant.lex, capacity, scratch.data(), true);
                for (auto _ : state) {
                    auto digest = run(fixture, variant.lex, capacity, scratch.data(), false);
                    benchmark::DoNotOptimize(digest);
                    if (digest != expected) state.SkipWithError("digest mismatch");
                }
                state.SetBytesProcessed(state.iterations() * bytes);
                state.SetItemsProcessed(state.iterations() * tokens);
            });
        }
    }
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
}
