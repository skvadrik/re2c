// Included inside re2c_lin_00__http, after lin_base.re.
// Deterministic HTTP header regimes (isolated, names, values; known vs unknown) and parity check.
static std::vector<std::string> build_http_regime(bool known, int mode) {
    static const char* const headers[8] = {
        "Content-Length:", "Content-Type:", "Transfer-Encoding:",
        "Authorization:", "Accept-Encoding:", "User-Agent:",
        "Cache-Control:", "Connection:"
    };
    static const char* const alnum = "abcdefghijklmnopqrstuvwxyz0123456789";
    uint32_t seed = 586u + (known ? 0u : 1000u);
    auto next = [&]() -> uint32_t {
        seed = seed * 1664525u + 1013904223u;
        return seed >> 16;
    };

    std::vector<std::string> names(1024), values(1024);
    for (size_t i = 0; i < 1024; ++i) {
        if (known) {
            names[i] = headers[next() % 8];
        } else {
            size_t len = 4 + (next() % 20);
            std::string s = "X-";
            for (size_t j = 0; j < len; ++j) s += char('a' + (next() % 26));
            s += ':';
            names[i] = s;
        }
        size_t vlen = 1 + (next() % 39);
        std::string v = " ";
        for (size_t j = 0; j < vlen; ++j) v += alnum[next() % 36];
        v += "\r\n";
        values[i] = v;
    }

    if (mode == 0) return names;
    std::string joined;
    for (size_t i = 0; i < 1024; ++i) {
        joined += names[i];
        if (mode == 2) joined += values[i];
    }
    return {joined};
}

static void bench_lin_regime(benchmark::State &state, bool known, int mode, int variant) {
    std::vector<std::string> inputs = build_http_regime(known, mode);
    int64_t bytes = 0;
    long expected = 0;
    std::vector<input_t> views(inputs.size());

    for (size_t i = 0; i < inputs.size(); ++i) {
        std::string &data = inputs[i];
        size_t len = data.size();
        bytes += len;
        data.append(YYMAXFILL, '\0');
        input_t &in = views[i];
        in = input_t();
        in.buf = &data[0];
        in.lim = in.buf + len + YYMAXFILL;
        in.len = len;

        digest_sink_t d0, d1;
        count_sink_t c0, c1;
        int s0 = lex_sentinel_scalar(&in, d0);
        s0 |= lex_sentinel_scalar(&in, c0);
        int s1 = 0;
        switch (variant) {
            case 0: s1 = lex_sentinel_scalar(&in, d1); s1 |= lex_sentinel_scalar(&in, c1); break;
            case 1: s1 = lex_sentinel_linear(&in, d1); s1 |= lex_sentinel_linear(&in, c1); break;
            case 2: s1 = lex_bounded_scalar(&in, d1); s1 |= lex_bounded_scalar(&in, c1); break;
            case 3: s1 = lex_bounded_linear(&in, d1); s1 |= lex_bounded_linear(&in, c1); break;
        }
        if (s0 != 0 || s1 != 0 || d0.value() != d1.value() || c0.value() != c1.value()) {
            state.SkipWithError("token digest or count differs from sentinel-scalar oracle");
            return;
        }
        expected += c1.value();
    }

    for (auto _ : state) {
        count_sink_t c;
        int status = 0;
        for (const input_t &in : views) {
            switch (variant) {
                case 0: status |= lex_sentinel_scalar(&in, c); break;
                case 1: status |= lex_sentinel_linear(&in, c); break;
                case 2: status |= lex_bounded_scalar(&in, c); break;
                case 3: status |= lex_bounded_linear(&in, c); break;
            }
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
    static const char* const modes[3] = {"isolated", "names", "values"};
    static const char* const vnames[4] = {
        "_sentinel-scalar", "_sentinel-linear", "_bounded-scalar", "_bounded-linear"
    };
    for (bool known : {true, false}) {
        for (int mode = 0; mode < 3; ++mode) {
            for (int v = 0; v < 4; ++v) {
                std::string name = std::string("lin-regime-http_")
                    + (known ? "known_" : "unknown_") + modes[mode]
                    + "-" + CXX + vnames[v];
                benchmark::RegisterBenchmark(name.c_str(), bench_lin_regime, known, mode, v);
            }
        }
    }
}

bool test_regimes() {
    static const char* const modes[3] = {"isolated", "names", "values"};
    static const char* const names[6] = {
        "sentinel-scalar", "sentinel-linear",
        "bounded-scalar", "bounded-linear",
        "buffered-scalar", "buffered-linear"
    };
    for (bool known : {true, false}) {
        for (int mode = 0; mode < 3; ++mode) {
            std::vector<std::string> inputs = build_http_regime(known, mode);
            for (size_t idx = 0; idx < inputs.size(); ++idx) {
                std::string &data = inputs[idx];
                size_t len = data.size();
                data.append(YYMAXFILL, '\0');
                input_t in = {};
                in.buf = &data[0];
                in.lim = in.buf + len + YYMAXFILL;
                in.len = len;

                int status[6];
                uint64_t digest[6];
                long count[6];

                {
                    digest_sink_t d; count_sink_t c;
                    int s = lex_sentinel_scalar(&in, d);
                    int sc = lex_sentinel_scalar(&in, c);
                    status[0] = s != 0 ? s : sc;
                    digest[0] = d.value(); count[0] = c.value();
                }
                {
                    digest_sink_t d; count_sink_t c;
                    int s = lex_sentinel_linear(&in, d);
                    int sc = lex_sentinel_linear(&in, c);
                    status[1] = s != 0 ? s : sc;
                    digest[1] = d.value(); count[1] = c.value();
                }
                {
                    digest_sink_t d; count_sink_t c;
                    int s = lex_bounded_scalar(&in, d);
                    int sc = lex_bounded_scalar(&in, c);
                    status[2] = s != 0 ? s : sc;
                    digest[2] = d.value(); count[2] = c.value();
                }
                {
                    digest_sink_t d; count_sink_t c;
                    int s = lex_bounded_linear(&in, d);
                    int sc = lex_bounded_linear(&in, c);
                    status[3] = s != 0 ? s : sc;
                    digest[3] = d.value(); count[3] = c.value();
                }
                {
                    digest_sink_t d; count_sink_t c;
                    input_t bin;
                    init_input_buffered_mem(&bin, &data[0], len);
                    int s = lex_buffered_scalar(&bin, d);
                    free_input(&bin);
                    init_input_buffered_mem(&bin, &data[0], len);
                    int sc = lex_buffered_scalar(&bin, c);
                    free_input(&bin);
                    status[4] = s != 0 ? s : sc;
                    digest[4] = d.value(); count[4] = c.value();
                }
                {
                    digest_sink_t d; count_sink_t c;
                    input_t bin;
                    init_input_buffered_mem(&bin, &data[0], len);
                    int s = lex_buffered_linear(&bin, d);
                    free_input(&bin);
                    init_input_buffered_mem(&bin, &data[0], len);
                    int sc = lex_buffered_linear(&bin, c);
                    free_input(&bin);
                    status[5] = s != 0 ? s : sc;
                    digest[5] = d.value(); count[5] = c.value();
                }

                for (int i = 0; i < 6; ++i) {
                    if (status[i] != 0) {
                        fprintf(stderr, "re2c %s: status %d on regime %s_%s[%zu]\n",
                            names[i], status[i], known ? "known" : "unknown", modes[mode], idx);
                        return false;
                    }
                    if (digest[i] != digest[0]) {
                        fprintf(stderr, "re2c %s: digest %llx != %llx on regime %s_%s[%zu]\n",
                            names[i], (unsigned long long)digest[i],
                            (unsigned long long)digest[0],
                            known ? "known" : "unknown", modes[mode], idx);
                        return false;
                    }
                    if (count[i] != count[0]) {
                        fprintf(stderr, "re2c %s: count %ld != %ld on regime %s_%s[%zu]\n",
                            names[i], count[i], count[0],
                            known ? "known" : "unknown", modes[mode], idx);
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
