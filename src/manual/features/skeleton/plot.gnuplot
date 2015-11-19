set terminal png font "Courier,mono"



set output 'input_1_7.png'
set title "Size of .input: [0-9a-fA-F]{1..7}"
plot "points_1_7" using 2:3 lc rgb '#ff6600' lw 2 with lines title ".input"

set output 'input_8_1024.png'
set title "Size of .input: [0-9a-fA-F]{8..1024}"
plot "points_8_1024" using 2:3 lc rgb '#ff6600' lw 2 with lines title ".input"

set output 'input_1_1024.png'
set title "Size of .input"
plot "points_1_7"    using 2:3 lc rgb '#ff6600' lw 2 with lines title ".input", \
     "points_8_1024" using 2:3 lc rgb '#ff6600' lw 2 with lines notitle



set output 'keys_1_7.png'
set title "Size of .keys: [0-9a-fA-F]{1..7}"
plot "points_1_7" using 2:4 lc rgb '#003399' lw 2 with lines title ".keys"

set output 'keys_8_1024.png'
set title "Size of .keys: [0-9a-fA-F]{8..1024}"
plot "points_8_1024" using 2:4 lc rgb '#003399' lw 2 with lines title ".keys"

set output 'keys_1_1024.png'
set title "Size of .keys"
plot "points_1_7"    using 2:4 lc rgb '#003399' lw 2 with lines title ".keys", \
     "points_8_1024" using 2:4 lc rgb '#003399' lw 2 with lines notitle



