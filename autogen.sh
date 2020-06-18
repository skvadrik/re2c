#!/bin/sh

git clean -fX
mkdir -p m4
autoreconf -i -W all
