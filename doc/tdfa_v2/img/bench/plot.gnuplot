
unset autoscale y
set ylabel "slowdown vs leftmost greedy (times)"

set style line 1 lc rgb '#000000' lw 1
set style line 2 lc rgb '#000000' lw 1 dt ' -'
set style line 3 lc rgb '#000000' lw 1 dt (40.00, 10.00)
set style line 4 lc rgb '#000000' lw 1 dt (20.00, 15.00)
set style line 5 lc rgb '#000000' lw 1 dt (4.00, 20.00, 40, 20)
set style line 6 lc rgb '#000000' lw 1 dt '  -  '
set style line 7 lc rgb '#000000' lw 1 dt (60.00, 15.00)
set style line 8 lc rgb '#000000' lw 1 dt (4, 16)

set output 'plot_realworld.png'
set terminal pngcairo dashed font "Courier,mono" size 800,600
set title "real-world RE"
set xtics (\
    "HTTP 6204-198" 1, \
    "HTTP-small 574-40" 2, \
    "URI 3149-102" 3, \
    "URI-small 234-18" 4, \
    "IPv6 2343-61" 5, \
    "IPv4 235-5" 6, \
    "IPv4-small 57-4" 7, \
    "IPv4-tiny 37-4" 8, \
    "date 154-7" 9, \
    "date-small 65-6" 10, \
    "date-tiny 47-6" 11 \
    ) right rotate by 30
set bmargin 6
set tmargin 2
set lmargin 12
set rmargin 1
set yrange [-1:30]
plot \
     "data_realworld" using 1:2 ls 1 with lines title "leftmost greedy", \
     "data_realworld" using 1:3 ls 2 with lines title "RE2", \
     "data_realworld" using 1:4 ls 3 with lines title "Okui-Suzuki", \
     "data_realworld" using 1:5 ls 4 with lines title "GTOP Okui-Suzuki", \
     "data_realworld" using 1:7 ls 6 with lines title "naive Okui-Suzuki", \
     "data_realworld" using 1:8 ls 7 with lines title "lazy Okui-Suzuki", \
     "data_realworld" using 1:6 ls 5 with lines title "Kuklewicz", \
     "data_realworld" using 1:9 ls 8 with lines title "Cox"


set output 'plot_artificial.png'
set terminal pngcairo dashed font "Courier" size 1300,700
set title "artificial highly ambiguous RE on long (64K) input strings"
set xtics (\
    '(a\{2\}|a\{3\}|a\{5\})*' 1, \
    '(a\{7\}|a\{11\}|a\{13\})*' 2, \
    '(a\{17\}|a\{19\}|a\{23\})*' 3, \
    '(a\{29\}|a\{31\}|a\{37\})*' 4, \
    '(((a)\{2\})|((a)\{3\})|((a)\{5\}))*' 5, \
    '(((a)\{7\})|((a)\{11\})|((a)\{13\}))*' 6, \
    '(((a)\{17\})|((a)\{19\})|((a)\{23\}))*' 7, \
    '(((a)\{29\})|((a)\{31\})|((a)\{37\}))*' 8, \
    "((((((((((a*)*)*)*)*)*)*)*)*)*)*" 9, \
    "(a*)(a*)(a*)(a*)(a*)(a*)(a*)(a*)" 10, \
    "(((a*)(a*)(a*))*((a*)(a*)(a*))*)*" 11, \
    "(((((a*)*)*((a*)*)*((a*)*)*)*)*)*" 12, \
    "(((((a*)*(a*))*(a*))*(a*))*(a*))*" 13, \
    "((a*)((a*)((a*)((a*)(a*)*)*)*)*)*" 14, \
    "(a*)|(a*)|(a*)|(a*)|(a*)|(a*)|(a*)" 15, \
    "((a*)|(a*)|(a*))((a*)|(a*)|(a*))" 16, \
    "((a*)|(a*))((a*)|(a*))((a*)|(a*))" 17, \
    "((a*)|(a*)|(a*))*|((a*)|(a*)|(a*))*" 18, \
    "(((((a*)*)*|((a*)*)*|((a*)*)*)*)*)*" 19, \
    "((a*)|((a*)(a*))|((a*)(a*)(a*)))*" 20, \
    "(((a*)(a*)(a*))|((a*)(a*))|(a*))*" 21 \
    ) right rotate by 30
set bmargin 11
set tmargin 2
set lmargin 15
set rmargin 1
set yrange [-1:30]
plot \
     "data_artificial" using 1:2 ls 1 with lines title "leftmost greedy", \
     "data_artificial" using 1:3 ls 2 with lines title "RE2", \
     "data_artificial" using 1:4 ls 3 with lines title "Okui-Suzuki", \
     "data_artificial" using 1:5 ls 4 with lines title "GTOP Okui-Suzuki", \
     "data_artificial" using 1:7 ls 6 with lines title "naive Okui-Suzuki", \
     "data_artificial" using 1:8 ls 7 with lines title "lazy Okui-Suzuki", \
     "data_artificial" using 1:6 ls 5 with lines title "Kuklewicz", \
     "data_artificial" using 1:9 ls 8 with lines title "Cox"


set output 'plot_pathological.png'
set terminal pngcairo dashed font "Courier" size 500,600
set title "pathological RE"
set xtics (\
    '((a?)\{0,125\})*' 1, \
    '((a?)\{0,250\})*' 2, \
    '((a?)\{0,500\})*' 3, \
    '((a?)\{0,1000\})*' 4, \
    '((a?)\{0,2000\})*' 5 \
    ) right rotate by 30
set bmargin 6
set tmargin 2
set lmargin 12
set rmargin 1
set yrange [-50:32<*]
plot \
     "data_pathological" using 1:2 ls 1 with lines title "leftmost greedy", \
     "data_pathological" using 1:3 ls 2 with lines title "RE2", \
     "data_pathological" using 1:4 ls 3 with lines title "Okui-Suzuki", \
     "data_pathological" using 1:5 ls 4 with lines title "GTOP Okui-Suzuki", \
     "data_pathological" using 1:7 ls 6 with lines title "naive Okui-Suzuki", \
     "data_pathological" using 1:8 ls 7 with lines title "lazy Okui-Suzuki", \
     "data_pathological" using 1:6 ls 5 with lines title "Kuklewicz", \
     "data_pathological" using 1:9 ls 8 with lines title "Cox"
