#!/bin/sh

objdir="obj" \
    && cd "$objdir" \
    && make -f ../Makefile -j5 \
    && cd ..

