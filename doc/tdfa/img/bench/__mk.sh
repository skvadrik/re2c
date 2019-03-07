gnuplot plot.gnuplot

montage size_gcc.png size_clang.png -tile 2x1 -geometry +0+0 size_gcc_clang.png
montage size_tcc.png size_pcc.png   -tile 2x1 -geometry +0+0 size_tcc_pcc.png
montage time_gcc.png time_clang.png -tile 2x1 -geometry +0+0 time_gcc_clang.png
montage time_tcc.png time_pcc.png   -tile 2x1 -geometry +0+0 time_tcc_pcc.png

for f in *.png; do convert $f $f; done

rm size_{gcc,clang,tcc,pcc}.png
rm time_{gcc,clang,tcc,pcc}.png

