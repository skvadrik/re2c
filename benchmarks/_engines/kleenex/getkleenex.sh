set -ex

rm -rf kleenexlang
git clone --recursive https://github.com/diku-kmc/kleenexlang.git
cd kleenexlang
mkdir "install"
cabal build
cabal install --install-method=copy --installdir="$(pwd)/install"
cd ..
rm -f kexc
ln -s "kleenexlang/install/kexc" kexc
