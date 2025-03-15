SRC_DIR = $(srcdir)/src
ENG_DIR = engines
GEN_DIR = gen
PREGEN_DIR = $(srcdir)/pregen
DAT_DIR = data
RAGEL = $(ENG_DIR)/ragel/ragel7
RE2C = $(top_builddir)/re2c
RE2C_FLAGS = --reusable --tags --no-generation-date --no-version -i

CXXFLAGS = $(AM_CXXFLAGS) -O3 -g -I $(SRC_DIR) -Wall -Wno-unused-const-variable
LDFLAGS = -lbenchmark -lpthread

BENCHMARKS = \
    lex_00__numbers1 \
    lex_01__numbers2 \
    lex_02__words1 \
    lex_03__words2 \
    lex_04__words3 \
    \
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
COMMON_RAGEL = \
    $(COMMON_SRC) \
    $(SRC_DIR)/ragel/base.h
COMMON_RE2C = \
    $(COMMON_SRC) \
    $(SRC_DIR)/re2c/base.re \
    $(SRC_DIR)/re2c/base.h

GEN_RAGEL = $(patsubst %, $(GEN_DIR)/ragel/%.cc, $(BENCHMARKS))
GEN_RE2C = $(patsubst %, $(GEN_DIR)/re2c/%.cc, $(BENCHMARKS))
GEN = $(GEN_RAGEL) $(GEN_RE2C)

SRC = $(GEN_RAGEL) $(GEN_RE2C)

OBJ_GCC = $(patsubst %.cc, %-gcc.o, $(SRC))
OBJ_CLANG = $(patsubst %.cc, %-clang.o, $(SRC))
OBJ_TEST = $(patsubst %.cc, %-test.o, $(SRC))
OBJ = $(OBJ_GCC) $(OBJ_CLANG) $(OBJ_TEST)

# Some benchmarks share the same data, like 03__uri_simple and 02__uri_rfc3986.
DAT = $(patsubst %, $(DAT_DIR)/%/big, \
    $(sort $(foreach bench, $(BENCHMARKS), \
        $(word 3, $(subst _, , $(bench))))))

$(DAT): $(DAT_DIR)/%/big: $(srcdir)/../_data/%/small
	$(AM_V_at)mkdir -p $(@D) && cp $< $(@D)
	$(AM_V_GEN)( cd $(@D) && ../../$(srcdir)/../_data/gen.py )

all-local: bench-gcc bench-clang test $(DAT)

# compile

$(OBJ_GCC): %-gcc.o: %.cc
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)g++ $(CXXFLAGS) -c -o $@ $<

$(OBJ_CLANG): %-clang.o: %.cc
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)clang++ $(CXXFLAGS) -c -o $@ $<

$(OBJ_TEST): %-test.o: %.cc
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)g++ $(CXXFLAGS) -DRUN_IN_TEST_MODE -c -o $@ $<

bench-gcc: src/bench.cc $(OBJ_GCC)
	$(AM_V_GEN)g++ -DCXX=\"gcc\" -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

bench-clang: src/bench.cc $(OBJ_CLANG)
	$(AM_V_GEN)clang++ -DCXX=\"clang\" -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

test: src/test.cc $(OBJ_TEST)
	$(AM_V_GEN)g++ -DRUN_IN_TEST_MODE -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

# always regenerate re2c benchmarks (except for deprecated algorithms)

$(GEN_RE2C): $(GEN_DIR)/%.cc: $(SRC_DIR)/%.re $(COMMON_RE2C) $(RE2C)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RE2C) $(RE2C_FLAGS) $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/re2c/$(@F) ; then cp -f $@ $(PREGEN_DIR)/re2c/$(@F) ; fi

# optionally regenerate other benchmarks

if REGEN_BENCHMARKS

$(GEN_RAGEL): $(GEN_DIR)/%.cc: $(SRC_DIR)/%.rl $(COMMON_RAGEL) $(RAGEL)
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)$(RAGEL) -G2 $< -o $@
	$(AM_V_at)if ! cmp -s $@ $(PREGEN_DIR)/ragel/$(@F) ; then cp -f $@ $(PREGEN_DIR)/ragel/$(@F) ; fi

else

$(GEN_RAGEL) $(GEN_DIR)/%: $(PREGEN_DIR)/%
	$(AM_V_at)mkdir -p $(@D)
	$(AM_V_GEN)cp -f $< $@

endif

# engines

$(RAGEL):
	$(AM_V_at)mkdir -p $(@D) && cp $(srcdir)/../_engines/ragel/getragel7.sh $(@D)
	$(AM_V_GEN)( cd $(@D) && ./getragel7.sh )

# clean

clean-local:
	rm -f $(GEN) $(OBJ) $(DAT) bench-gcc bench-clang test
