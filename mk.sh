#!/bin/sh

[ -d master ] || { 
    git worktree prune
    git worktree add master master
}
[ -e src/manual/options/options.rst_  ] ||  #merge manual tree from master
     (cd master/re2c/doc/; tar cf - manual/) | (cd src/; tar xfp -) 

sphinx-build -b html src obj

[ $# != 0 ] || #pass an argument to prevent the server from launching
    runhaskell launch.hs
