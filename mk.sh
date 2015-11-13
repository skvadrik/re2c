#!/bin/sh

objdir="obj" \
    && cd "$objdir" \
    && make -f ../Makefile \
    && cd ..

