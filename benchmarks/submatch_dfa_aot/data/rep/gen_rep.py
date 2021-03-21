#!/usr/bin/env python3

import os


def main():
    total = 0
    limit = 1024 * 1024 * 100 # 100M
    len = (2 + 3 + 5) * (7 + 11 + 13) * (17 + 19 + 23)

    with open('big', 'w') as f:
        while total < limit:
            f.write('a' * len)
            f.write('\n')
            total += len + 1


if __name__ == "__main__":
    main()

