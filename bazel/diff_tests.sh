#!/bin/bash

# Compare generated result files against golden expectations using `diff -du``.
#
# Env:
#   GOLDEN: List of golden files separated by new-line.
#   RESULT: List of result files separated by new-line.
#   GOLDEN_SED: A `sed` command to perform on golden files.
#   RESULT_SED: A `sed` command to perform on result files.
#
# Note:
#   It is possible to provide multipls `sed` commands using the tool's chaining
#   ability (e.g. '{cmd;cmd;}').

set -euo pipefail

function die() {
    local MSG="${1:-DIED}"
    local SRC="${BASH_SOURCE[1]}"
    SRC="${SRC#${TEST_SRCDIR}}"
    SRC="${SRC#${TEST_TMPDIR}}"
    SRC="${SRC#${RUNFILES_DIR}}"
    SRC="${SRC#/}"
    echo "${MSG} [${SRC}:${BASH_LINENO[0]}: ${FUNCNAME[1]}]" >&2
    exit 1
}

function test_diff() {
    # The passed filenames are relative to their own BUILD file.
    # The path to that file can be derived from `TEST_TARGET`.
    local TARGET_DIR="$(echo "${TEST_TARGET}" | sed -rne "s,//([^:]+):.+,\\1/,p")"
    local GOLDEN="${TARGET_DIR}${1}"
    local RESULT="${TARGET_DIR}${2}"
    local TEST="${TEST_TARGET} : ${GOLDEN}"
    if [[ "${VERBOSE}" == "1" ]]; then
      echo "TEST: ${TEST}"
    fi
    # If $GOLDEN_SED is present, then execute it on $GOLDEN.
    if [[ -n "${GOLDEN_SED}" ]]; then
      local OUT="${TEST_TMPDIR}/${GOLDEN}.src"
      mkdir -p "$(dirname ${OUT})" || die "FAIL: ${TEST}: mkdir $(dirname ${OUT})"
      cat "${GOLDEN}" | sed -re "${GOLDEN_SED}" > "${OUT}" || die "FAIL: ${TEST}: sed ${GOLDEN}"
      GOLDEN="${OUT}"
    fi
    # If $RESULT_SED is present, then execute it on $RESULT.
    if [[ -n "${RESULT_SED}" ]]; then
      local OUT="${TEST_TMPDIR}/${RESULT}.out"
      mkdir -p "$(dirname ${OUT})" || die "FAIL: ${TEST}: mkdir $(dirname ${OUT})"
      cat "${RESULT}" | sed -re "${RESULT_SED}" > "${OUT}" || die "FAIL: ${TEST}: sed ${RESULT}"
      RESULT="${OUT}"
    fi
    # Perform comparison.
    diff --text -du "${GOLDEN}" "${RESULT}" || die "FAIL: ${TEST}: diff"
    if [[ "${VERBOSE}" == "1" ]]; then
      echo "PASS: ${TEST}"
    fi
}

OIFS="${IFS}"
IFS=$'\n'
GOLDEN_ARRAY=(${GOLDEN})
RESULT_ARRAY=(${RESULT})
IFS="${OIFS}"

for (( N=0; N<${#GOLDEN_ARRAY[@]}; N+=1)); do
  test_diff "${GOLDEN_ARRAY[${N}]}" "${RESULT_ARRAY[${N}]}"
done
