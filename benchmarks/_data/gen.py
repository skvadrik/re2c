#!/usr/bin/env python3

import os

# 16 megabytes
LIMIT = 1024 * 1024 * 16

# read the small sample
with open('small', 'rb') as f:
    small = f.read()
    smallsize = len(small)

# copy-paste it enough times to the big file
total = 0
with open('big', 'wb') as f:
    while total < LIMIT:
        f.write(small)
        total += smallsize
