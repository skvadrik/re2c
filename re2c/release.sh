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

# try to be portable on various MAKEs
for make_prog in make bmake
do
    rm -rf $builddir
    mkdir $builddir
    cd $builddir
        ../configure --enable-docs && \
        $make_prog bootstrap -j5
        $make_prog distcheck -j5
    cd .. # $builddir
done

# upload files on sourceforge
cd $builddir
    src=release
    src_tarballs=$src/frs/project/re2c/re2c/$version
    src_docs=$src/project-web/re2c/htdocs
    mkdir -p $src_tarballs $src_docs
    cp re2c-$version.tar.gz $src_tarballs
    cp ../doc/index.html doc/manual.html $src_docs
    rsync -rK $src/ skvadrik@web.sourceforge.net:/home
cd .. # $builddir

# commit release
git commit -a -m "Release $version."
git tag $version
git push --follow-tags
git push --follow-tags github master
