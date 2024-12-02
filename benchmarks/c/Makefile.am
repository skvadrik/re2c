SRC_DIR = $(srcdir)/src
ENG_DIR = engines
GEN_DIR = gen
PREGEN_DIR = $(srcdir)/pregen
BIN_DIR = bin
DAT_DIR = data
CFLAGS = -O3 -I $(SRC_DIR)
RAGEL = $(ENG_DIR)/ragel/ragel7
KLEENEX = $(ENG_DIR)/kleenex/kexc
RE2C3 = $(ENG_DIR)/re2c/re2c3
RE2C = $(top_builddir)/re2c
RE2C_FLAGS_COMMON = --reusable --tags --no-generation-date --no-version
RE2C_FLAGS     = $(RE2C_FLAGS_COMMON) -I $(SRC_DIR)/re2c/include
RE2C_FLAGS_EOF = $(RE2C_FLAGS_COMMON) -I $(SRC_DIR)/re2c/include-eof

BENCHMARKS = \
    submatch_00__http_rfc7230 \
    submatch_01__http_simple \
    submatch_02__uri_rfc3986 \
    submatch_03__uri_simple \
    submatch_04__apache_log \
    submatch_05__datetime \
    submatch_06__email \
    submatch_07__ipv4 \
    \
    submatch_10__alt1_2 \
    submatch_11__alt1_4 \
    submatch_12__alt1_8 \
    submatch_13__alt2_2 \
    submatch_14__alt2_4 \
    submatch_15__alt2_8 \
    submatch_16__alt4_2 \
    submatch_17__alt4_4 \
    submatch_18__alt4_8 \
    \
    submatch_20__cat2_0 \
    submatch_21__cat2_4 \
    submatch_22__cat2_8 \
    submatch_23__cat4_0 \
    submatch_24__cat4_2 \
    submatch_25__cat4_4 \
    submatch_26__cat8_0 \
    submatch_27__cat8_1 \
    submatch_28__cat8_2 \
    \
    submatch_30__rep_cat_5_3_2 \
    submatch_31__rep_cat_13_11_7 \
    submatch_32__rep_cat_23_19_17 \
    submatch_33__rep_alt_5_3_2 \
    submatch_34__rep_alt_13_11_7 \
    submatch_35__rep_alt_23_19_17 \
    submatch_36__rep_5_rep_3_rep_2 \
    submatch_37__rep_13_rep_11_rep_7 \
    submatch_38__rep_23_rep_19_rep_17

COMMON_SRC = $(SRC_DIR)/common.h

GEN_RAGEL = $(patsubst %, $(GEN_DIR)/ragel/%.c, $(BENCHMARKS))

BIN_RAGEL = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RAGEL))

COMMON_RAGEL = $(COMMON_SRC) $(SRC_DIR)/ragel/common.c

GEN_RE2C_TDFA1     = $(patsubst %, $(GEN_DIR)/re2c/%-tdfa1.c,     $(BENCHMARKS))
GEN_RE2C_EOF_TDFA1 = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa1.c, $(BENCHMARKS))
GEN_RE2C = \
    $(GEN_RE2C_TDFA1) \
    $(GEN_RE2C_EOF_TDFA1)

GEN_RE2C3_TDFA0      = $(patsubst %, $(GEN_DIR)/re2c/%-tdfa0.c,      $(BENCHMARKS))
GEN_RE2C3_EOF_TDFA0  = $(patsubst %, $(GEN_DIR)/re2c/%-eof-tdfa0.c,  $(BENCHMARKS))
GEN_RE2C3_STADFA     = $(patsubst %, $(GEN_DIR)/re2c/%-stadfa.c,     $(BENCHMARKS))
GEN_RE2C3_EOF_STADFA = $(patsubst %, $(GEN_DIR)/re2c/%-eof-stadfa.c, $(BENCHMARKS))
GEN_RE2C3 = \
    $(GEN_RE2C_TDFA0) \
    $(GEN_RE2C_EOF_TDFA0)  \
    $(GEN_RE2C3_STADFA) \
    $(GEN_RE2C3_EOF_STADFA)

BIN_RE2C = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_RE2C) $(GEN_RE2C3))

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
    submatch_34__rep_alt_13_11_7 \
    submatch_35__rep_alt_23_19_17 \
    submatch_37__rep_13_rep_11_rep_7 \
    submatch_38__rep_23_rep_19_rep_17

GEN_KLEENEX = $(patsubst %, $(GEN_DIR)/kleenex/%.c, \
	$(filter-out $(KLEENEX_MASKED), $(BENCHMARKS)))

BIN_KLEENEX = $(patsubst $(GEN_DIR)%.c, $(BIN_DIR)%, $(GEN_KLEENEX))

GEN = $(GEN_RAGEL) $(GEN_RE2C) $(GEN_RE2C3) $(GEN_KLEENEX)

BIN_ = $(BIN_RAGEL) $(BIN_RE2C) $(BIN_KLEENEX)
BIN_GCC   = $(patsubst %, %-gcc, $(BIN_))
BIN_CLANG = $(patsubst %, %-clang, $(BIN_))
BIN = $(BIN_GCC) $(BIN_CLANG)

OBJ = $(patsubst %, %.o, $(BIN))

# Some benchmarks share the same data, like 03__uri_simple and 02__uri_rfc3986.
DAT = $(patsubst %, $(DAT_DIR)/%/big, \
    $(sort $(foreach bench, $(BENCHMARKS), \
        $(word 3, $(subst _, , $(bench))))))

all-local: $(BIN) $(DAT)

# always regenerate re2c benchmarks (except for deprecated algorithms)

$(GEN_RE2C_TDFA1): $(GEN_DIR)/%-tdfa1.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS) $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C_EOF_TDFA1): $(GEN_DIR)/%-eof-tdfa1.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS_EOF) $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi


# optionally regenerate ragel, kleenex and re2c-3.0 benchmarks
# (TDFA(0) and staDFA algorithms were removed in re2c versions after 3.0)

if REGEN_BENCHMARKS

$(GEN_RE2C3_TDFA0): $(GEN_DIR)/%-tdfa0.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C3)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C3) $(RE2C_FLAGS) --no-lookahead $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C3_EOF_TDFA0): $(GEN_DIR)/%-eof-tdfa0.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C3)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C3) $(RE2C_FLAGS_EOF) --no-lookahead $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C3_STADFA): $(GEN_DIR)/%-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C3)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C3) $(RE2C_FLAGS) --stadfa $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RE2C3_EOF_STADFA): $(GEN_DIR)/%-eof-stadfa.c: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C3)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C3) $(RE2C_FLAGS_EOF) --stadfa $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

$(GEN_RAGEL): $(GEN_DIR)/%.c: $(SRC_DIR)/%.rl $(COMMON_RAGEL) $(RAGEL)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RAGEL) -G2 $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/ragel/$(@F) ; then cp -f $@ $(PREGEN_DIR)/ragel/$(@F) ; fi

# don't regenerate kleenex benchmarks, as kleenex is not actively developed
# and it cannot be built with the recent cabal / haskell ecosystem
# $(GEN_KLEENEX): $(GEN_DIR)/%.c: $(SRC_DIR)/%.kex $(KLEENEX)
# 	$(AM_V_at)mkdir -p $(@D)
# 	$(AM_V_GEN)$(KLEENEX) compile $< --srcout $@ --act=false --la=true
# 	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/kleenex/$(@F) ; then cp -f $@ $(PREGEN_DIR)/kleenex/$(@F) ; fi
$(GEN_KLEENEX): $(GEN_DIR)/%: $(PREGEN_DIR)/%
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)cp -f $< $@

else

$(GEN_RAGEL) $(GEN_RE2C3) $(GEN_KLEENEX): $(GEN_DIR)/%: $(PREGEN_DIR)/%
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

$(DAT): $(DAT_DIR)/%/big: $(srcdir)/../_data/%/small
	$(AM_V_at)mkdir -p $(@D) && cp $< $(@D)
	$(AM_V_GEN)( cd $(@D) && ../../$(srcdir)/../_data/gen.py )

$(KLEENEX):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/../_engines/kleenex/getkleenex.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getkleenex.sh )

$(RAGEL):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/../_engines/ragel/getragel7.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getragel7.sh )

$(RE2C3):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/../_engines/re2c/getre2c3.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getre2c3.sh )

clean-local:
	$(AM_V_at)rm -f $(GEN) $(OBJ) $(BIN) $(DAT)
