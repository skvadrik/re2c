SRC_DIR = src
GEN_DIR = gen
BIN_DIR = bin
DATA_DIR = data
CC = gcc
CFLAGS = -O3 -g -I $(SRC_DIR)
RAGEL_LIBRARY_PATH = engines/ragel/ragel-7.0.0.12/install/lib:engines/ragel/colm-0.13.0.7/install/lib
RAGEL = LD_LIBRARY_PATH=$(RAGEL_LIBRARY_PATH) engines/ragel/ragel7
RE2C = engines/re2c/re2c
KLEENEX = engines/kleenex/kexc

BENCHMARKS = \
	apache_log \
	datetime_to_json \
	email \
	ipv4 \
	uri_simple \
	uri_rfc3986

COMMON_SRC = $(SRC_DIR)/common.h

GEN_RAGEL_T1 = $(patsubst %, $(GEN_DIR)/ragel/%-T1.c, $(BENCHMARKS))
GEN_RAGEL_F1 = $(patsubst %, $(GEN_DIR)/ragel/%-F1.c, $(BENCHMARKS))
GEN_RAGEL_G2 = $(patsubst %, $(GEN_DIR)/ragel/%-G2.c, $(BENCHMARKS))
GEN_RAGEL = $(GEN_RAGEL_T1) $(GEN_RAGEL_F1) $(GEN_RAGEL_G2)
BIN_RAGEL = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RAGEL))
COMMON_RAGEL = $(COMMON_SRC) $(SRC_DIR)/ragel/common.c

GEN_RE2C_           = $(patsubst %, $(GEN_DIR)/re2c/%.c,            $(BENCHMARKS))
GEN_RE2C_EAGER_SKIP = $(patsubst %, $(GEN_DIR)/re2c/%-eager-skip.c, $(BENCHMARKS))
GEN_RE2C_STADFA     = $(patsubst %, $(GEN_DIR)/re2c/%-stadfa.c,     $(BENCHMARKS))
GEN_RE2C = $(GEN_RE2C_) $(GEN_RE2C_EAGER_SKIP) $(GEN_RE2C_STADFA)
BIN_RE2C = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RE2C))
COMMON_RE2C = $(COMMON_SRC) $(SRC_DIR)/re2c/common.re

GEN_KLEENEX = $(patsubst %, $(GEN_DIR)/kleenex/%.c, $(BENCHMARKS))
BIN_KLEENEX = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_KLEENEX))

GEN = $(GEN_RAGEL) $(GEN_RE2C) $(GEN_KLEENEX)

BIN_ = $(BIN_RAGEL) $(BIN_RE2C) $(BIN_KLEENEX)
BIN_GCC   = $(patsubst %, %-gcc, $(BIN_))
BIN_CLANG = $(patsubst %, %-clang, $(BIN_))
BIN = $(BIN_GCC) $(BIN_CLANG)

DATA = $(patsubst %, $(DATA_DIR)/%/big, $(BENCHMARKS))

all: $(BIN)

$(GEN_RAGEL_T1): $(GEN_DIR)/%-T1.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL)
	$(RAGEL) -T1 $< -o $@
$(GEN_RAGEL_F1): $(GEN_DIR)/%-F1.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL)
	$(RAGEL) -F1 $< -o $@
$(GEN_RAGEL_G2): $(GEN_DIR)/%-G2.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL)
	$(RAGEL) -G2 $< -o $@
$(GEN_RE2C_): $(GEN_DIR)/%.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	$(RE2C) --tags $< -o $@
$(GEN_RE2C_EAGER_SKIP): $(GEN_DIR)/%-eager-skip.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	$(RE2C) --tags --eager-skip $< -o $@
$(GEN_RE2C_STADFA): $(GEN_DIR)/%-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C)
	$(RE2C) --tags --stadfa $< -o $@
$(GEN_KLEENEX): $(GEN_DIR)/%.c: $(SRC_DIR)/%.kex
	$(KLEENEX) compile $< --srcout $@ --act=false --la=true

$(BIN_GCC): $(BIN_DIR)/%-gcc: $(GEN_DIR)/%.c
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -o $@ $<
$(BIN_CLANG): $(BIN_DIR)/%-clang: $(GEN_DIR)/%.c
	@mkdir -p $(dir $@)
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
