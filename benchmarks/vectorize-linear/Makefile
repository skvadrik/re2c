.DEFAULT_GOAL := all
RE2C ?= build/re2c/re2c
RE2GO ?= build/re2c/re2go
CC ?= cc
CXX ?= c++
CFLAGS ?= -O2 -g
CXXFLAGS ?= -O2 -g
BENCHMARK_CFLAGS ?= $(shell pkg-config --cflags benchmark)
BENCHMARK_LIBS ?= $(shell pkg-config --libs benchmark)
BUILD ?= build
SCANNERS = $(foreach f,http sql,$(foreach v,0 1,$(foreach c,0 1,$(f)_$(v)_$(c))))
OBJECTS = $(addprefix $(BUILD)/,$(addsuffix .o,$(SCANNERS)))

.PHONY: generate all check smoke
generate:
	python3 generate.py --re2c "$(RE2C)" --re2go "$(RE2GO)"

all: $(BUILD)/bench
$(BUILD):
	mkdir -p $(BUILD)
$(BUILD)/%.o: generated/c/%.c scanner.h | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -std=c11 -I. -c $< -o $@
$(BUILD)/bench: bench.cc scanner.h generated/variants.h generated/fixtures.h $(OBJECTS) | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++17 $(BENCHMARK_CFLAGS) -I. bench.cc $(OBJECTS) $(BENCHMARK_LIBS) -pthread -o $@
check: $(BUILD)/bench
	./$(BUILD)/bench --check
	go test -count=1 ./...
smoke: $(BUILD)/bench
	./$(BUILD)/bench --benchmark_min_time=0.001s --benchmark_repetitions=1
	go test -run '^$$' -bench . -benchtime=1x -count=1
