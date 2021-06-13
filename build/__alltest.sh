#!/bin/sh

# normal tests
# - exclude _clang_msan as it requires libc++ built with MSan
for d in __build{,_check_headers,_asan,_ubsan,_clang,_m32,_glibcxx_debug} ; do
    build/${d}.sh \
        && cd ${d} \
        && make check VERBOSE=1 \
        && cd .. \
        || { cd .. ; echo "*** ${d} failed ***"; exit 1; }
done

# skeleton
build/__build.sh \
    && cd __build \
    && ./run_tests.py --skeleton \
    && cd .. \
    || { cd .. ; echo "*** skeleton failed ***"; exit 1; }

# mingw
# - exclude _mingw_slibtool, as it fails to link EXEs due to symbol collisions
build/__build_mingw.sh \
    && cd __build_mingw \
    && make wtests \
    && cd .. \
    || { cd .. ; echo "*** mingw failed ***"; exit 1; }

