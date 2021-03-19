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
RE2C_FLAGS_COMMON = --reusable --tags --no-generation-date
RE2C_FLAGS     = $(RE2C_FLAGS_COMMON) -I $(SRC_DIR)/re2c/include
RE2C_FLAGS_EOF = $(RE2C_FLAGS_COMMON) -I $(SRC_DIR)/re2c/include-eof

BENCHMARKS = \
    alt1_2 alt1_4 alt1_8 \
    alt2_2 alt2_4 alt2_8 \
    alt4_2 alt4_4 alt4_8 \
    cat2_0 cat2_4 cat2_8 \
    cat4_0 cat4_2 cat4_4 \
    cat8_0 cat8_1 cat8_2 \
    iter_a_4 iter_a_16 iter_a_64 \
    iter_b_2_3_5 iter_b_7_11_13 iter_b_17_19_23 \
    iter_c_2_3_5 iter_c_7_11_13 iter_c_17_19_23 \
    apache_log \
    datetime \
    email \
    ipv4 \
    uri_simple \
    uri_rfc3986 \
    http_simple \
    http_rfc7230

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
	iter_b_7_11_13 iter_b_17_19_23 \
	iter_c_7_11_13 iter_c_17_19_23

GEN_KLEENEX = $(patsubst %, $(GEN_DIR)/kleenex/%.c, \
	$(filter-out $(KLEENEX_MASKED), $(BENCHMARKS)))

BIN_KLEENEX = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_KLEENEX))

GEN = $(GEN_RAGEL) $(GEN_RE2C) $(GEN_KLEENEX)

BIN_ = $(BIN_RAGEL) $(BIN_RE2C) $(BIN_KLEENEX)
BIN_GCC   = $(patsubst %, %-gcc, $(BIN_))
BIN_CLANG = $(patsubst %, %-clang, $(BIN_))
BIN = $(BIN_GCC) $(BIN_CLANG)

OBJ = $(patsubst %, %.o, $(BIN))

# Some benchmarks share the same data, like `uri_simple` and `uri_rfc3986`
DAT = $(patsubst %, $(DAT_DIR)/%/big, \
    $(sort $(foreach bench, $(BENCHMARKS), \
        $(firstword $(subst _, , $(bench))))))

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
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/$(@D)/small $(srcdir)/$(@D)/gen_* $(@D)
	$(AM_V_GEN)( cd $(@D) && ./gen_* )

$(KLEENEX):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/engines/kleenex/getkleenex.sh $(srcdir)/engines/kleenex/0001-Updating-for-new-GHC.patch $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getkleenex.sh )

$(RAGEL):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/engines/ragel/getragel7.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getragel7.sh )

clean-local:
	$(AM_V_at)rm -f $(GEN) $(OBJ) $(BIN) $(DAT)
