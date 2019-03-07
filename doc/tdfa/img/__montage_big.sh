#!/bin/bash

w1=`identify -format '%[fx:w]\n' tdfa0_raw.png`
w2=`identify -format '%[fx:w]\n' tdfa1_raw.png`

w=$(( w1 > w2 ? w1 : w2 ))

h=`identify -format '%[fx:h]\n' tnfa.png`
convert -extent ${w}x${h} -gravity center tnfa.png _tnfa.png

h=`identify -format '%[fx:h]\n' tdfa0.png`
convert -extent ${w}x${h} -gravity center tdfa0.png _tdfa0.png

h=`identify -format '%[fx:h]\n' tdfa0.png`
convert -extent ${w}x${h} -gravity center tdfa1.png _tdfa1.png

h=`identify -format '%[fx:h]\n' tdfa0_raw.png`
convert -extent ${w}x${h} -gravity center tdfa0_raw.png _tdfa0_raw.png

h=`identify -format '%[fx:h]\n' tdfa0_raw.png`
convert -extent ${w}x${h} -gravity center tdfa1_raw.png _tdfa1_raw.png

montage -label "(a)" -font "Courier" -pointsize 16 _tnfa.png      -geometry +0+0 __tnfa.png
montage -label "(b)" -font "Courier" -pointsize 16 _tdfa0_raw.png -geometry +0+0 __tdfa0_raw.png
montage -label "(c)" -font "Courier" -pointsize 16 _tdfa0.png     -geometry +0+0 __tdfa0.png
montage -label "(d)" -font "Courier" -pointsize 16 _tdfa1_raw.png -geometry +0+0 __tdfa1_raw.png
montage -label "(e)" -font "Courier" -pointsize 16 _tdfa1.png     -geometry +0+0 __tdfa1.png

montage __tnfa.png \
    __tdfa0_raw.png __tdfa0.png \
    __tdfa1_raw.png __tdfa1.png \
    -tile 1x5 -geometry +0+5 all.png

rm _*.png

