#!/bin/sh

# sync with master (pull manpage files)
remote=`git config branch.master.remote` \
    && git fetch $remote \
    && git archive --remote=. remotes/$remote/master re2c/doc/manual \
    | tar -C src/ --strip-components=2 -xpf -

sphinx-build -b html src obj

[ $# != 0 ] || #pass an argument to prevent the server from launching
    runhaskell launch.hs
