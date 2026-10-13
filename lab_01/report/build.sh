#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
if command -v latexmk >/dev/null 2>&1 && command -v xelatex >/dev/null 2>&1; then
    latexmk -xelatex -synctex=1 -interaction=nonstopmode -file-line-error -halt-on-error report.tex
elif command -v xelatex >/dev/null 2>&1; then
    for pass in 1 2 3; do
        xelatex -interaction=nonstopmode -halt-on-error report.tex
    done
elif command -v tectonic >/dev/null 2>&1; then
    tectonic --keep-logs report.tex
else
    printf '%s\n' 'Нужен XeLaTeX (TeX Live / MiKTeX) или Tectonic.' >&2
    exit 1
fi
