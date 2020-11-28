SRC_DIR = src
GEN_DIR = gen
BIN_DIR = bin
DATA_DIR = data
CC = gcc
CFLAGS = -O3 -g -I $(SRC_DIR)
RAGEL_LIBRARY_PATH = engines/ragel/ragel-7.0.0.12/install/lib:engines/ragel/colm-0.13.0.7/install/lib
RAGEL = LD_LIBRARY_PATH=$(RAGEL_LIBRARY_PATH) engines/ragel/ragel7
RE2C = engines/re2c/re2c
RE2C_FLAGS = --reusable --tags
RE2C_FLAGS_BC = $(RE2C_FLAGS) -I $(SRC_DIR)/re2c/include_bc
RE2C_FLAGS_EOF = $(RE2C_FLAGS) -I $(SRC_DIR)/re2c/include_eof
KLEENEX = engines/kleenex/kexc

BENCHMARKS = \
	alt1_2 alt1_4 alt1_8 \
	alt2_2 alt2_4 alt2_8 \
	alt4_2 alt4_4 alt4_8 \
	cat2_0 cat2_4 cat2_8 \
	cat4_0 cat4_2 cat4_4 \
	cat8_0 cat8_1 cat8_2 \
	apache_log \
	datetime \
	email \
	ipv4 \
	uri_simple \
	uri_rfc3986 \
	http_simple \
	http_rfc7230

COMMON_SRC = $(SRC_DIR)/common.h

GEN_RAGEL_T1 = $(patsubst %, $(GEN_DIR)/ragel/%-T1.c, $(BENCHMARKS))
GEN_RAGEL_F1 = $(patsubst %, $(GEN_DIR)/ragel/%-F1.c, $(BENCHMARKS))
GEN_RAGEL_G2 = $(patsubst %, $(GEN_DIR)/ragel/%-G2.c, $(BENCHMARKS))
GEN_RAGEL = $(GEN_RAGEL_T1) $(GEN_RAGEL_F1) $(GEN_RAGEL_G2)

BIN_RAGEL = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RAGEL))

COMMON_RAGEL = $(COMMON_SRC) $(SRC_DIR)/ragel/common.c

GEN_RE2C_BC_TDFA1     = $(patsubst %, $(GEN_DIR)/re2c/%-bc-tdfa1.c,     $(BENCHMARKS))
GEN_RE2C_EOF_TDFA1    = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa1.c,    $(BENCHMARKS))
GEN_RE2C_BC_TDFA1_ES  = $(patsubst %, $(GEN_DIR)/re2c/%-bc-tdfa1-es.c,  $(BENCHMARKS))
GEN_RE2C_EOF_TDFA1_ES = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa1-es.c, $(BENCHMARKS))
GEN_RE2C_BC_TDFA0     = $(patsubst %, $(GEN_DIR)/re2c/%-bc-tdfa0.c,     $(BENCHMARKS))
GEN_RE2C_EOF_TDFA0    = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa0.c,    $(BENCHMARKS))
GEN_RE2C_BC_STADFA    = $(patsubst %, $(GEN_DIR)/re2c/%-bc-stadfa.c,    $(BENCHMARKS))
GEN_RE2C_EOF_STADFA   = $(patsubst %, $(GEN_DIR)/re2c/%-eof-stadfa.c,   $(BENCHMARKS))
GEN_RE2C = \
    $(GEN_RE2C_BC_TDFA1) \
    $(GEN_RE2C_EOF_TDFA1) \
    $(GEN_RE2C_BC_TDFA1_ES) \
    $(GEN_RE2C_EOF_TDFA1_ES) \
    $(GEN_RE2C_BC_TDFA0) \
    $(GEN_RE2C_EOF_TDFA0) \
    $(GEN_RE2C_BC_STADFA) \
    $(GEN_RE2C_EOF_STADFA)

BIN_RE2C = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RE2C))

COMMON_RE2C = \
    $(COMMON_SRC) \
    $(SRC_DIR)/re2c/common.re \
    $(SRC_DIR)/re2c/include_bc/fill.re \
    $(SRC_DIR)/re2c/include_bc/fill_email.re \
    $(SRC_DIR)/re2c/include_eof/fill.re \
    $(SRC_DIR)/re2c/include_eof/fill_email.re

GEN_KLEENEX = $(patsubst %, $(GEN_DIR)/kleenex/%.c, $(BENCHMARKS))

BIN_KLEENEX = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_KLEENEX))

GEN = $(GEN_RAGEL) $(GEN_RE2C) $(GEN_KLEENEX)

BIN_ = $(BIN_RAGEL) $(BIN_RE2C) $(BIN_KLEENEX)
BIN_GCC   = $(patsubst %, %-gcc, $(BIN_))
BIN_CLANG = $(patsubst %, %-clang, $(BIN_))
BIN = $(BIN_GCC) $(BIN_CLANG)

# Some benchmarks share the same data, like `uri_simple` and `uri_rfc3986`
DATA = $(patsubst %, $(DATA_DIR)/%/big, \
    $(sort $(foreach bench, $(BENCHMARKS), \
        $(firstword $(subst _, , $(bench))))))

all: $(BIN)

$(GEN_RAGEL_T1): $(GEN_DIR)/%-T1.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL)
	@mkdir -p $(@D)
	$(RAGEL) -T1 $< -o $@

$(GEN_RAGEL_F1): $(GEN_DIR)/%-F1.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL)
	@mkdir -p $(@D)
	$(RAGEL) -F1 $< -o $@

$(GEN_RAGEL_G2): $(GEN_DIR)/%-G2.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL)
	@mkdir -p $(@D)
	$(RAGEL) -G2 $< -o $@

$(GEN_RE2C_BC_TDFA1): $(GEN_DIR)/%-bc-tdfa1.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_BC) $< -o $@

$(GEN_RE2C_EOF_TDFA1): $(GEN_DIR)/%-eof-tdfa1.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_EOF) $< -o $@

$(GEN_RE2C_BC_TDFA1_ES): $(GEN_DIR)/%-bc-tdfa1-es.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_BC) --eager-skip $< -o $@

$(GEN_RE2C_EOF_TDFA1_ES): $(GEN_DIR)/%-eof-tdfa1-es.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_EOF) --eager-skip $< -o $@

$(GEN_RE2C_BC_TDFA0): $(GEN_DIR)/%-bc-tdfa0.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_BC) --no-lookahead $< -o $@

$(GEN_RE2C_EOF_TDFA0): $(GEN_DIR)/%-eof-tdfa0.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_EOF) --no-lookahead $< -o $@

$(GEN_RE2C_BC_STADFA): $(GEN_DIR)/%-bc-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_BC) --stadfa $< -o $@

$(GEN_RE2C_EOF_STADFA): $(GEN_DIR)/%-eof-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	@mkdir -p $(@D)
	$(RE2C) $(RE2C_FLAGS_EOF) --stadfa $< -o $@

$(GEN_KLEENEX): $(GEN_DIR)/%.c: $(SRC_DIR)/%.kex
	@mkdir -p $(@D)
	$(KLEENEX) compile $< --srcout $@ --act=false --la=true

$(BIN_GCC): $(BIN_DIR)/%-gcc: $(GEN_DIR)/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ $<

$(BIN_CLANG): $(BIN_DIR)/%-clang: $(GEN_DIR)/%.c
	@mkdir -p $(@D)
	clang $(CFLAGS) -o $@ $<

data: $(DATA)

$(DATA): $(DATA_DIR)/%/big:
	(cd $(@D) && ./gen_*)

clean:
	find bin -type f -delete

clean-gen:
	find gen -type f -delete

clean-data:
	rm -f $(DATA)

clean-logs:
	find logs -type f -delete

clean-all: clean clean-gen clean-data clean-logs
