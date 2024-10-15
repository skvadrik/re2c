#!/bin/bash

# Minimalistic test that verifies the binary can run and report its own version.

set -euo pipefail

RE2C_VERSION="$(cat "${TEST_SRCDIR}/re2c/config.h" | sed -rne 's,^#define PACKAGE_VERSION "(.*)"$,\1,p')"

RE2C_BAZEL_VERSION="re2c ${RE2C_VERSION}"

if [[ "$("${TEST_SRCDIR}/re2c/re2c" --version)" == "${RE2C_BAZEL_VERSION}" ]]; then
  echo "PASS"
else
  echo "FAIL"
  exit 1
fi
