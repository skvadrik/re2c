set terminal png font "Courier,mono"


set output 'input.png'
set title "Size of .input"
plot "points_1_1024" using 2:3 lc rgb '#ff6600' lw 2 with lines title ".input"

set output 'keys.png'
set title "Size of .keys"
plot "points_1_1024" using 2:4 lc rgb '#003399' lw 2 with lines title ".keys"

set output 'input_keys.png'
set title "Size of .keys and .input"
plot "points_1_1024" using 2:4 lc rgb '#003399' lw 2 with lines title ".keys", \
     "points_1_1024" using 2:3 lc rgb '#ff6600' lw 2 with lines title ".input"

