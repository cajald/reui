#!/bin/sh

if [ -x "./knfmt/knfmt" ]; then
    KNFMT="./knfmt/knfmt"
elif command -v knfmt >/dev/null 2>&1; then
    KNFMT="knfmt"
else
    echo "fmt.sh: error: can't find knfmt" >&2
    echo >&2
    echo "fmt.sh: build knfmt from source with:" >&2
    echo "  $ cd knfmt" >&2
    echo "  $ ./configure" >&2
    echo "  $ make" >&2
    echo "  $ cd .." >&2
    echo >&2
    echo "and then re-run" >&2
    exit 1
fi

find . -path "./knfmt" -prune -o -type f \( -name "*.c" -o -name "*.h" \) -print0 |
    xargs -0 -r "$KNFMT" -i

echo "==> Formatting ok"
