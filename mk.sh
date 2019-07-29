#!/bin/sh -x

# sync with master (pull manpage files)
remote=`git config branch.master.remote` \
    && git fetch $remote \
    && { git archive --remote=. remotes/$remote/master doc/manual \
        | tar -C src/ --strip-components=1 -xpf -; } \
    && { git archive --remote=. remotes/$remote/master examples/*.re \
        | tar -C src/ --strip-components=0 -xpf -; }

sphinx-build -b html src obj

[ $# != 0 ] || #pass an argument to prevent the server from launching
    runhaskell launch.hs
