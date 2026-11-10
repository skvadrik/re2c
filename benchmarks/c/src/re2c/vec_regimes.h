// Included inside re2c_vec_00__strings, after vec_base.re.
// Corpus construction and oracle checks are outside the timed loop.
static void bench_regime(benchmark::State &state, int length, int escape_every,
        bool records, const char* file, int mode) {
    std::vector<std::string> inputs;
    if (file) {
        FILE *f = fopen(file, "rb");
        if (!f) {
            state.SkipWithError("cannot open corpus file");
            return;
        }
        std::string data;
        char block[4096];
        size_t n;
        while ((n = fread(block, 1, sizeof(block), f)) != 0) data.append(block, n);
        bool failed = ferror(f) != 0;
        fclose(f);
        if (failed || data.empty() || data.find('\0') != std::string::npos) {
            state.SkipWithError("empty, unreadable or NUL-containing corpus");
            return;
        }
        inputs.push_back(data);
    } else {
        std::string data;
        uint32_t seed = 585;
        for (int i = 0; i < 4096; ++i) {
            std::string literal = "\"";
            int n = length < 0 ? i % 66 : length;
            for (int j = 0; j < n; ++j) {
                seed = seed * 1664525u + 1013904223u;
                if (escape_every && j % escape_every == escape_every - 2) {
                    literal += "\\n";
                    ++j;
                } else {
                    literal += char('a' + (seed >> 24) % 26);
                }
            }
            literal += '"';
            if (records) inputs.push_back(literal);
            else data += literal + ',';
        }
        if (!records) inputs.push_back(data);
    }

    int64_t bytes = 0;
    long expected = 0;
    std::vector<input_t> views(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        std::string &data = inputs[i];
        size_t len = data.size();
        bytes += len;
        // The oracle uses a sentinel. The generated lexer sees only YYMAXFILL padding.
        data.append(YYMAXFILL > 64 ? YYMAXFILL : 64, '\0');
        input_t &in = views[i];
        in = input_t();
        in.buf = &data[0];
        in.lim = in.buf + len + YYMAXFILL;
        in.len = len;
        long count, digest;
        digest_sink_t d;
        count_sink_t c;
        int status = mode == 0 ? lex_bounded_scalar(&in, d)
            : mode == 1 ? lex_bounded_vector_sse2(&in, d)
            : lex_bounded_vector(&in, d);
        int counted = mode == 0 ? lex_bounded_scalar(&in, c)
            : mode == 1 ? lex_bounded_vector_sse2(&in, c)
            : lex_bounded_vector(&in, c);
        if (!ref_vec_strings::oracle(in.buf, len, &count, &digest)
                || status != 0 || counted != 0 || d.value() != digest || c.value() != count) {
            state.SkipWithError("token digest or count differs from handwritten oracle");
            return;
        }
        expected += count;
    }

    for (auto _ : state) {
        count_sink_t c;
        int status = 0;
        for (const input_t &in : views) {
            status |= mode == 0 ? lex_bounded_scalar(&in, c)
                : mode == 1 ? lex_bounded_vector_sse2(&in, c)
                : lex_bounded_vector(&in, c);
        }
        benchmark::DoNotOptimize(c.n);
        benchmark::ClobberMemory();
        if (status != 0 || c.value() != expected) {
            state.SkipWithError("timed pass differs from oracle");
            break;
        }
    }
    state.SetBytesProcessed(state.iterations() * bytes);
}

void register_regimes() {
    for (int mode : {0, 1, 2}) {
        const std::string suffix = std::string("-") + CXX
            + (mode == 0 ? "_bounded-scalar"
                : mode == 1 ? "_bounded-vector-sse2"
                : "_bounded-vector");
        for (int n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 16, 24, 31, 32, 33, 64, 256}) {
            benchmark::RegisterBenchmark(("vec-regime-fixed" + std::to_string(n) + suffix).c_str(),
                bench_regime, n, 0, false, nullptr, mode);
        }
        for (int k : {8, 32, 64}) {
            benchmark::RegisterBenchmark(("vec-regime-escape" + std::to_string(k) + suffix).c_str(),
                bench_regime, 1024, k, false, nullptr, mode);
        }
        benchmark::RegisterBenchmark(("vec-regime-end-buffer" + suffix).c_str(),
            bench_regime, -1, 0, true, nullptr, mode);
        benchmark::RegisterBenchmark(("vec-regime-stream" + suffix).c_str(),
            bench_regime, -1, 0, false, nullptr, mode);
        benchmark::RegisterBenchmark(("vec-regime-csource" + suffix).c_str(),
            bench_regime, 0, 0, false,
            RE2C_BENCH_SOURCE_DIR "/benchmarks/_data/csource/small", mode);
        benchmark::RegisterBenchmark(("vec-regime-headers" + suffix).c_str(),
            bench_regime, 0, 0, false,
            RE2C_BENCH_SOURCE_DIR "/src/util/containers.h", mode);
    }
}
