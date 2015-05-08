#!/bin/bash

set -e

if [ $# -ne 1 ]
then
    echo "usage: ./release.sh <version>"
    exit
fi

version="$1"

# edit version in configure.in
lcontext="AC_INIT\(\[re2c\],\["
rcontext="\],\[re2c-general@lists\.sourceforge\.net\]\)"
old="[0-9]+(\.[0-9]+)*(\.dev)?"
new=$version
sed -i -E "s/$lcontext$old$rcontext/$lcontext$new$rcontext/" configure.ac

./autogen.sh
builddir=.build
rm -rf $builddir
mkdir $builddir
cd $builddir

    ../configure --enable-docs && \
    make bootstrap -j5 && \
    make tests && \
    make dist

    # dist-check
    tmpdir=` date +"%Y%m%d%H%M%S%N"`
    mkdir $tmpdir
    cp re2c-$version.tar.gz $tmpdir
    cd $tmpdir
        gunzip re2c-$version.tar.gz
        tar -x -f re2c-$version.tar
        cd re2c-$version
            ./configure && \
            make bootstrap -j5 && \
            make tests

            # upload files on sourceforge
            src=release
            src_tarballs=$src/frs/project/re2c/re2c/$version
            src_docs=$src/project-web/re2c/htdocs
            mkdir -p $src_tarballs
            mkdir -p $src_docs
            cp ../../re2c-$version.tar.gz $src_tarballs
            cp doc/index.html doc/manual.html $src_docs
            rsync -rK $src/ skvadrik@web.sourceforge.net:/home
        cd ..
    cd ..
    rm -r $tmpdir

cd .. # $builddir

# commit release
git commit -a -m "Release $version."
git tag $version
git push
git push --tags
