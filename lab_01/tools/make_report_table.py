"""Generate LaTeX rows from measured comparison counts."""
import csv
from pathlib import Path

data = Path(__file__).resolve().parents[1] / 'report' / 'data'
with (data / 'comparisons.csv').open() as source:
    rows = list(csv.DictReader(source))
algorithms = ['linear', 'classic', 'branchless', 'recursive']
latex = '\n'.join(
    row['N'] + ' & ' + ' & '.join(
        row[name + '_min'] + ' / ' + row[name + '_max']
        for name in algorithms
    ) + r'\\\hline'
    for row in rows
)
(data / 'comparison_rows.tex').write_text('\\newcommand{\\comparisonrows}{%\n' + latex + '%\n}\n')
