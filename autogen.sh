#!/bin/sh
./cvsclean.sh
aclocal
autoheader
automake -a -c -i --foreign
autoconf
