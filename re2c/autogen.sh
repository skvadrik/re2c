#!/bin/sh
git clean -fXd
aclocal
autoheader
automake -a -c --foreign
autoconf
