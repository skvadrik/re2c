#!/usr/bin/env sh

[ $# -ne 1 ] && { echo "usage: $0 <json-input-file>"; exit 1; }

results="$1"
stem="$(basename ${results%.json})"

# Split results into separate files for real-world benchmarks and artificial
# alternative, concatenation and repetition benchmarks. Exclude Ragel from
# artificial benchmarks as it does not cover all cases (results are incorrect).
jq 'map_values(map(select(.name | startswith("alt") and (contains("ragel") | not))))' "${results}" > "${stem}_alt.json"
jq 'map_values(map(select(.name | startswith("cat") and (contains("ragel") | not))))' "${results}" > "${stem}_cat.json"
jq 'map_values(map(select(.name | startswith("rep") and (contains("ragel") | not))))' "${results}" > "${stem}_rep.json"
jq 'map_values(map(select(.name | (startswith("alt") or startswith("cat") or startswith("rep")) | not)))' "${results}" > "${stem}_main.json"
