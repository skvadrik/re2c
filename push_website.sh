#!/bin/bash -x

cd re2c.org \
&& rm -rf .git \
&& git init \
&& git remote add origin git@github.com:skvadrik/re2c.git \
&& git checkout -b gh-pages \
&& find . | xargs git add \
&& git commit -m "Initial commit" \
&& git push -f -u origin gh-pages \
&& cd ..

