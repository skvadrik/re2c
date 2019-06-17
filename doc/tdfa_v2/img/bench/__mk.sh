gnuplot plot.gnuplot

montage plot_realworld.png plot_pathological.png -tile 2x1 -geometry +0+0 plot1.png
montage plot1.png          plot_artificial.png   -tile 1x2 -geometry +0+0 plot.png

rm plot_realworld.png
rm plot_artificial.png
rm plot_pathological.png
rm plot1.png

convert plot.png plot.png

