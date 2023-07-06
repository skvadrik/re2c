#!/usr/bin/env bash

set -x

rm -rf re2c.org obj

./make.sh nolaunch \
&& cp -r obj re2c.org \
&& cd re2c.org \
&& git init \
&& git remote add origin git@github.com:skvadrik/re2c.git \
&& git checkout -b gh-pages \
&& find . | xargs git add \
&& git commit -m "Initial commit" \
&& git push -f -u origin gh-pages \
&& cd ..

