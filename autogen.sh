#!/bin/sh
./cvsclean.sh
aclocal
autoheader
automake -a -c --foreign
autoconf
