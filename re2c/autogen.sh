#!/bin/sh

git clean -fXd

aclocal -W all
autoheader -W all
automake -W all -a -c --foreign
autoconf -W all
