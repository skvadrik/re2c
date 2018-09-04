#!/bin/sh

# normal tests
for d in __build{,_asan,_ubsan,_lsan,_clang,_clang_msan,_m32} ; do
    ./${d}.sh \
        && cd ${d} \
        && make check VERBOSE=1 \
        && cd .. \
        || { cd .. ; echo "*** ${d} failed ***"; exit 1; }
done

# skeleton
./__build.sh \
    && cd __build \
    && ./run_tests.sh --skeleton \
    && cd .. \
    || { cd .. ; echo "*** skeleton failed ***"; exit 1; }

# mingw
./__build_mingw.sh \
    && cd __build_mingw \
    && make wtests \
    && cd .. \
    || { cd .. ; echo "*** mingw failed ***"; exit 1; }

