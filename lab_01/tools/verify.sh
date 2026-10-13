#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
build_dir=$(mktemp -d)
trap 'rm -rf "$build_dir"' EXIT
sources=(src/linear_search.c src/binary_search_classic.c src/binary_search_branchless.c src/binary_search_recursive.c)
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic -O0 -g -Iinc tests/test_search.c "${sources[@]}" -o "$build_dir/test_search"
"$build_dir/test_search"
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic -O0 -Iinc tools/compare_search.c "${sources[@]}" -o "$build_dir/compare_search"
"$build_dir/compare_search" > report/data/comparisons.csv
