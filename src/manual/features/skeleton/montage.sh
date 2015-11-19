gnuplot plot.gnuplot \
    && montage input_1_7.png input_8_1024.png input_1_1024.png -tile 3x1 -geometry +0+0 plot_input.png \
    && rm input_1_7.png input_8_1024.png input_1_1024.png \
    && montage keys_1_7.png keys_8_1024.png keys_1_1024.png -tile 3x1 -geometry +0+0 plot_keys.png \
    && rm keys_1_7.png keys_8_1024.png keys_1_1024.png
