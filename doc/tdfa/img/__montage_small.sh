#!/bin/bash


w1=`identify -format '%[fx:w]\n' tdfa0_raw.png`
w2=`identify -format '%[fx:w]\n' tdfa1_raw.png`

h1=`identify -format '%[fx:h]\n' tdfa0_raw.png`
h2=`identify -format '%[fx:h]\n' tdfa1_raw.png`
h=$(( h1 > h2 ? h1 : h2 ))

convert -extent ${w1}x${h} -gravity center tdfa0_raw.png _tdfa0_raw.png
convert -extent ${w2}x${h} -gravity center tdfa1_raw.png _tdfa1_raw.png

h1=`identify -format '%[fx:h]\n' tdfa0.png`
h2=`identify -format '%[fx:h]\n' tdfa1.png`
h=$(( h1 > h2 ? h1 : h2 ))

convert -extent ${w1}x${h} -gravity center tdfa0.png     _tdfa0.png
convert -extent ${w2}x${h} -gravity center tdfa1.png     _tdfa1.png

montage -label "(a)" -font "Courier" -pointsize 16 tnfa.png       -geometry +0+0 _tnfa.png
montage -label "(b)" -font "Courier" -pointsize 16 _tdfa0_raw.png -geometry +0+0 __tdfa0_raw.png
montage -label "(c)" -font "Courier" -pointsize 16 _tdfa0.png     -geometry +0+0 __tdfa0.png
montage -label "(d)" -font "Courier" -pointsize 16 _tdfa1_raw.png -geometry +0+0 __tdfa1_raw.png
montage -label "(e)" -font "Courier" -pointsize 16 _tdfa1.png     -geometry +0+0 __tdfa1.png

montage __tdfa0_raw.png __tdfa0.png -tile 1x2 -geometry +0+5 ___tdfa0.png
montage __tdfa1_raw.png __tdfa1.png -tile 1x2 -geometry +0+5 ___tdfa1.png
montage ___tdfa0.png ___tdfa1.png -tile 2x1 -geometry +0+0 _tdfa.png

w=`identify -format '%[fx:w]\n' _tdfa.png`
h=`identify -format '%[fx:h]\n' _tnfa.png`
convert -extent ${w}x${h} -gravity center _tnfa.png __tnfa.png

montage __tnfa.png _tdfa.png -tile 1x2 -geometry +0+5 all.png

rm _*.png

