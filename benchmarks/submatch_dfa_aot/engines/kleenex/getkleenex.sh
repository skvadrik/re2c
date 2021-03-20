set -e

rm -rf kleenexlang
git clone --recursive https://github.com/diku-kmc/kleenexlang.git
cd kleenexlang
cabal v1-sandbox init && cabal v1-sandbox add-source regexps-syntax
cabal v1-install --dependencies-only
cabal v1-configure && cabal v1-build
cd ..
rm -f kexc
ln -s kleenexlang/dist/build/kexc/kexc kexc
