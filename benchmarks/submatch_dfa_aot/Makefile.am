SRC_DIR = $(srcdir)/src
ENG_DIR = engines
GEN_DIR = gen
PREGEN_DIR = $(srcdir)/pregen
BIN_DIR = bin
DAT_DIR = data
CFLAGS = -O3 -I $(SRC_DIR)
RAGEL = $(ENG_DIR)/ragel/ragel7
KLEENEX = $(ENG_DIR)/kleenex/kexc
RE2C = $(top_builddir)/re2c
RE2C_FLAGS_COMMON = --reusable --tags --no-generation-date --no-version
RE2C_FLAGS     = $(RE2C_FLAGS_COMMON) -I $(SRC_DIR)/re2c/include
RE2C_FLAGS_EOF = $(RE2C_FLAGS_COMMON) -I $(SRC_DIR)/re2c/include-eof

BENCHMARKS = \
    00__http_rfc7230 \
    01__http_simple \
    02__uri_rfc3986 \
    03__uri_simple \
    04__apache_log \
    05__datetime \
    06__email \
    07__ipv4 \
    \
    10__alt1_2 \
    11__alt1_4 \
    12__alt1_8 \
    13__alt2_2 \
    14__alt2_4 \
    15__alt2_8 \
    16__alt4_2 \
    17__alt4_4 \
    18__alt4_8 \
    \
    20__cat2_0 \
    21__cat2_4 \
    22__cat2_8 \
    23__cat4_0 \
    24__cat4_2 \
    25__cat4_4 \
    26__cat8_0 \
    27__cat8_1 \
    28__cat8_2 \
    \
    30__rep_cat_5_3_2 \
    31__rep_cat_13_11_7 \
    32__rep_cat_23_19_17 \
    33__rep_alt_5_3_2 \
    34__rep_alt_13_11_7 \
    35__rep_alt_23_19_17 \
    36__rep_5_rep_3_rep_2 \
    37__rep_13_rep_11_rep_7 \
    38__rep_23_rep_19_rep_17

COMMON_SRC = $(SRC_DIR)/common.h

GEN_RAGEL = $(patsubst %, $(GEN_DIR)/ragel/%.c, $(BENCHMARKS))

BIN_RAGEL = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RAGEL))

COMMON_RAGEL = $(COMMON_SRC) $(SRC_DIR)/ragel/common.c

GEN_RE2C_TDFA1      = $(patsubst %, $(GEN_DIR)/re2c/%-tdfa1.c,      $(BENCHMARKS))
GEN_RE2C_TDFA0      = $(patsubst %, $(GEN_DIR)/re2c/%-tdfa0.c,      $(BENCHMARKS))
GEN_RE2C_STADFA     = $(patsubst %, $(GEN_DIR)/re2c/%-stadfa.c,     $(BENCHMARKS))
GEN_RE2C_EOF_TDFA1  = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa1.c,  $(BENCHMARKS))
GEN_RE2C_EOF_TDFA0  = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa0.c,  $(BENCHMARKS))
GEN_RE2C_EOF_STADFA = $(patsubst %, $(GEN_DIR)/re2c/%-eof-stadfa.c, $(BENCHMARKS))
GEN_RE2C = \
    $(GEN_RE2C_TDFA1) \
    $(GEN_RE2C_TDFA0) \
    $(GEN_RE2C_STADFA) \
    $(GEN_RE2C_EOF_TDFA1) \
    $(GEN_RE2C_EOF_TDFA0) \
    $(GEN_RE2C_EOF_STADFA)

BIN_RE2C = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RE2C))

COMMON_RE2C = \
    $(COMMON_SRC) \
    $(SRC_DIR)/re2c/common.re \
    $(SRC_DIR)/re2c/include/fill.re \
    $(SRC_DIR)/re2c/include/fill_email.re \
    $(SRC_DIR)/re2c/include-eof/fill.re \
    $(SRC_DIR)/re2c/include-eof/fill_email.re

# Masked benchmarks for which Kleenex either generates very large output
# (tens of megabytes of C code), or even causes out of memory condition.
KLEENEX_MASKED = \
    34__rep_alt_13_11_7 \
    35__rep_alt_23_19_17 \
    37__rep_13_rep_11_rep_7 \
    38__rep_23_rep_19_rep_17

GEN_KLEENEX = $(patsubst %, $(GEN_DIR)/kleenex/%.c, \
	$(filter-out $(KLEENEX_MASKED), $(BENCHMARKS)))

BIN_KLEENEX = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_KLEENEX))

GEN = $(GEN_RAGEL) $(GEN_RE2C) $(GEN_KLEENEX)

BIN_ = $(BIN_RAGEL) $(BIN_RE2C) $(BIN_KLEENEX)
BIN_GCC   = $(patsubst %, %-gcc, $(BIN_))
BIN_CLANG = $(patsubst %, %-clang, $(BIN_))
BIN = $(BIN_GCC) $(BIN_CLANG)

OBJ = $(patsubst %, %.o, $(BIN))

# Some benchmarks share the same data, like 03__uri_simple and 02__uri_rfc3986.
DAT = $(patsubst %, $(DAT_DIR)/%/big, \
    $(sort $(foreach bench, $(BENCHMARKS), \
        $(word 2, $(subst _, , $(bench))))))

all-local: $(BIN) $(DAT)

# always regenerate re2c benchmarks

$(GEN_RE2C_TDFA1): $(GEN_DIR)/%-tdfa1.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS) $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C_EOF_TDFA1): $(GEN_DIR)/%-eof-tdfa1.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS_EOF) $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C_TDFA0): $(GEN_DIR)/%-tdfa0.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS) --no-lookahead $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C_EOF_TDFA0): $(GEN_DIR)/%-eof-tdfa0.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS_EOF) --no-lookahead $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C_STADFA): $(GEN_DIR)/%-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS) --stadfa $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C_EOF_STADFA): $(GEN_DIR)/%-eof-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS_EOF) --stadfa $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

# optionally regenerate ragel and kleenex benchmarks
if REGEN_BENCHMARKS

$(GEN_RAGEL): $(GEN_DIR)/%.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL) $(RAGEL)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RAGEL) -G2 $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/ragel/$(@F) ; then cp -f $@ $(PREGEN_DIR)/ragel/$(@F) ; fi

$(GEN_KLEENEX): $(GEN_DIR)/%.c: $(SRC_DIR)/%.kex $(KLEENEX)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(KLEENEX) compile $< --srcout $@ --act=false --la=true
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/kleenex/$(@F) ; then cp -f $@ $(PREGEN_DIR)/kleenex/$(@F) ; fi

else

$(GEN_RAGEL) $(GEN_KLEENEX): $(GEN_DIR)/%: $(PREGEN_DIR)/%
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)cp -f $< $@

endif

$(BIN_GCC): $(BIN_DIR)/%-gcc: $(GEN_DIR)/%.c
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_at)gcc $(CFLAGS) -c -o $@.o $<
	$(AM_V_GEN)gcc $(CFLAGS) -o $@ $@.o

$(BIN_CLANG): $(BIN_DIR)/%-clang: $(GEN_DIR)/%.c
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_at)clang $(CFLAGS) -c -o $@.o $<
	$(AM_V_GEN)clang $(CFLAGS) -o $@ $@.o

$(DAT): $(DAT_DIR)/%/big: $(DAT_DIR)/%/small
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/$(@D)/small $(@D)
	$(AM_V_GEN)( cd $(@D) && ../../$(srcdir)/data/gen.py )

$(KLEENEX):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/engines/kleenex/getkleenex.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getkleenex.sh )

$(RAGEL):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/engines/ragel/getragel7.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getragel7.sh )

clean-local:
	$(AM_V_at)rm -f $(GEN) $(OBJ) $(BIN) $(DAT)
