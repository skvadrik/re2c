
[ -x ../re2c ] || { echo "*** no re2c found ***"; exit 1; }

ghc check.hs -Wall -fforce-recomp -O2
