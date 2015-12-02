gnuplot plot.gnuplot \
    && montage keys.png input.png input_keys.png -tile 3x1 -geometry +0+0 plot.png \
    && rm keys.png input.png input_keys.png
