set terminal pngcairo dashed font "Courier,mono"
set xtics ("HTTP-RFC3720" 1, "HTTP-simple" 2, "URI-RFC3986" 3, "URI-simple" 4)

set style line 8 lc rgb '#888888' lw 3 lt 1    # TDFA(0)
set style line 1 lc rgb '#888888' lw 3 lt 2    # TDFA(1)
set style line 2 lc rgb '#888888' lw 3 lt 3    # DFA
set style line 3 lc rgb '#000000' lw 1 lt 1    # TDFA(0) -b
set style line 4 lc rgb '#000000' lw 1 lt 2    # TDFA(1) -b
set style line 5 lc rgb '#000000' lw 1 lt 3    # DFA -b
set style line 6 lc rgb '#dddddd' lw 5 lt 1    # TDFA(0) --no-optimize-tags
set style line 7 lc rgb '#dddddd' lw 5 lt 2    # TDFA(1) --no-optimize-tags

set logscale y 2
set ylabel "binary size (K, logscale)"

set output 'size_gcc.png'
set title "size -- gcc"
plot \
     "data" index 6 using 1:6 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:6 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:6 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:6 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:6 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:6 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:6 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:6 ls 2 with lines title "DFA"

set output 'size_clang.png'
set title "size -- clang"
plot \
     "data" index 6 using 1:7 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:7 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:7 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:7 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:7 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:7 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:7 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:7 ls 2 with lines title "DFA"

set output 'size_tcc.png'
set title "size -- tcc"
plot \
     "data" index 6 using 1:8 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:8 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:8 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:8 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:8 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:8 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:8 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:8 ls 2 with lines title "DFA"

set output 'size_pcc.png'
set title "size -- pcc"
plot \
     "data" index 6 using 1:9 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:9 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:9 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:9 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:9 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:9 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:9 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:9 ls 2 with lines title "DFA"




unset logscale
set ylabel "run time (s)"
set yrange [0:16<*]

set output 'time_gcc.png'
set title "time -- gcc"
plot \
     "data" index 6 using 1:10 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:10 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:10 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:10 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:10 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:10 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:10 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:10 ls 2 with lines title "DFA"

set output 'time_clang.png'
set title "time -- clang"
plot \
     "data" index 6 using 1:11 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:11 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:11 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:11 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:11 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:11 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:11 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:11 ls 2 with lines title "DFA"

set output 'time_tcc.png'
set title "time -- tcc"
plot \
     "data" index 6 using 1:12 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:12 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:12 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:12 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:12 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:12 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:12 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:12 ls 2 with lines title "DFA"

set output 'time_pcc.png'
set title "time -- pcc"
plot \
     "data" index 6 using 1:13 ls 6 with lines title "TDFA(0) --no-optimize-tags", \
     "data" index 7 using 1:13 ls 7 with lines title "TDFA(1) --no-optimize-tags", \
     "data" index 3 using 1:13 ls 3 with lines title "TDFA(0) -b", \
     "data" index 4 using 1:13 ls 4 with lines title "TDFA(1) -b", \
     "data" index 5 using 1:13 ls 5 with lines title "DFA -b", \
     "data" index 0 using 1:13 ls 8 with lines title "TDFA(0)", \
     "data" index 1 using 1:13 ls 1 with lines title "TDFA(1)", \
     "data" index 2 using 1:13 ls 2 with lines title "DFA"

