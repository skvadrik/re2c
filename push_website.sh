#!/usr/bin/env bash

source ./utils.sh

rm --recursive --force re2c.org obj
./make.sh nolaunch
cp --recursive obj re2c.org
(
    cd re2c.org
    git init
    git remote add origin "$gitRepoRoot"
    git checkout -b gh-pages
    git add --all
    git commit --message "Initial commit"
    git push --force --set-upstream origin gh-pages
)

echo "The script has finished successfully"
