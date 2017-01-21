# 'echo' is used to perform a dry run

for f in *.txt; do echo mv "$f" "${f/.txt/.tmp}"; done
