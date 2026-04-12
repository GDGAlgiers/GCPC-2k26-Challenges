#!/bin/bash
# Usage: ./solution_test.sh <solution>
# Run from inside a challenge directory (where data/ exists).
# Accepts: compiled binary, .cpp, .py, .go, .java source files.
#
# Examples:
#   ../../scripts/solution_test.sh ./sol
#   ../../scripts/solution_test.sh sol.cpp
#   ../../scripts/solution_test.sh sol.py
#   ../../scripts/solution_test.sh sol.go

set -uo pipefail

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <solution>"
    echo "  Examples: $0 ./sol  |  $0 sol.cpp  |  $0 sol.py  |  $0 sol.go"
    exit 1
fi

SOLUTION="$1"
BINARY="$SOLUTION"
PASS=0
FAIL=0
TLE=0
GOTMPDIR=""

# Compile if a source file is given
case "$SOLUTION" in
    *.c)
        echo "[..] Compiling $SOLUTION ..."
        gcc -O2 -std=c17 -o /tmp/gcpc_sol "$SOLUTION" -lm || { echo "[!!] Compilation failed"; exit 1; }
        BINARY=/tmp/gcpc_sol
        echo "[ok] Compiled"
        ;;
    *.cpp)
        echo "[..] Compiling $SOLUTION ..."
        g++ -O2 -std=c++17 -o /tmp/gcpc_sol "$SOLUTION" || { echo "[!!] Compilation failed"; exit 1; }
        BINARY=/tmp/gcpc_sol
        echo "[ok] Compiled"
        ;;
    *.java)
        echo "[..] Compiling $SOLUTION ..."
        javac -d /tmp "$SOLUTION" || { echo "[!!] Compilation failed"; exit 1; }
        BINARY="$(basename "${SOLUTION%.java}")"
        echo "[ok] Compiled"
        ;;
    *.go)
        # Compile Go to a binary in an isolated tmpdir to avoid the cgo error
        # caused by .c/.cpp siblings in the same directory.
        echo "[..] Compiling $SOLUTION ..."
        GOTMPDIR=$(mktemp -d)
        cp "$SOLUTION" "$GOTMPDIR/main.go"
        go build -o "$GOTMPDIR/gosol" "$GOTMPDIR/main.go" || {
            echo "[!!] Go compilation failed"
            rm -rf "$GOTMPDIR"
            exit 1
        }
        BINARY="$GOTMPDIR/gosol"
        echo "[ok] Compiled"
        ;;
esac

run_case() {
    local inf="$1"
    case "$SOLUTION" in
        *.py)   timeout 5s python3 "$SOLUTION" < "$inf" ;;
        *.js)   timeout 5s node "$SOLUTION" < "$inf" ;;
        *.java) timeout 5s java -cp /tmp "$BINARY" < "$inf" ;;
        *)      timeout 5s "$BINARY" < "$inf" ;;  # .c .cpp .go (all pre-compiled), binary
    esac
}

test_dir() {
    local dir="$1"
    [[ -d "$dir" ]] || return 0
    local found=0
    for inf in "$dir"/*.in; do
        [[ -f "$inf" ]] || continue
        found=1
        local ans="${inf%.in}.ans"
        if [[ ! -f "$ans" ]]; then
            echo "SKIP  $(basename "$dir")/$(basename "$inf") (missing .ans)"
            continue
        fi

        local actual
        local exit_code=0
        actual=$(run_case "$inf" 2>/dev/null) || exit_code=$?

        local label="$(basename "$dir")/$(basename "$inf")"
        if [[ $exit_code -eq 124 ]]; then
            echo "TLE   $label"
            TLE=$((TLE + 1))
        elif diff -wB <(echo "$actual") "$ans" > /dev/null 2>&1; then
            echo "AC    $label"
            PASS=$((PASS + 1))
        else
            echo "WA    $label"
            FAIL=$((FAIL + 1))
        fi
    done
    [[ $found -eq 1 ]] || echo "(no .in files found in $dir)"
}

test_dir "data/sample"
test_dir "data/secret"

# Cleanup Go tmpdir if one was created
[[ -n "$GOTMPDIR" ]] && rm -rf "$GOTMPDIR"

echo "--------------------"
echo "Results: ${PASS} AC  ${FAIL} WA  ${TLE} TLE"
[[ $((FAIL + TLE)) -eq 0 ]]
