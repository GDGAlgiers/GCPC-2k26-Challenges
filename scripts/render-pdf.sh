#!/bin/bash
# Render a problem's PDF.
# Run from inside a challenge directory: challenges/<problem-id>/
#
#   ../../scripts/render-pdf.sh
#
# Requirements:
#   sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
#
# Install on macOS:
#   brew install pandoc && brew install --cask basictex
#   sudo tlmgr update --self && sudo tlmgr install collection-xetex collection-latexextra
#
# Install on Windows:
#   pandoc from https://pandoc.org/installing.html
#   MiKTeX from https://miktex.org  (auto-downloads missing packages on first run)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(realpath "$SCRIPT_DIR/..")"
LOGO="$ROOT/assets/gcpc-logo.png"
FONTS="$ROOT/assets/fonts"
TEMPLATE="$ROOT/assets/_gcpc-template.latex"

if [[ ! -f "statement/problem.md" ]]; then
    echo "Error: run this from inside a challenge directory (e.g. challenges/robery/)"
    exit 1
fi

if [[ ! -f "$TEMPLATE" ]]; then
    echo "Error: template not found at $TEMPLATE"
    exit 1
fi

args=(
    "statement/problem.md"
    "--pdf-engine=xelatex"
    "--template=$TEMPLATE"
)

if [[ -f "$LOGO" ]]; then
    args+=("-V" "logo-path=$LOGO")
else
    echo "Warning: logo not found at $LOGO -- rendering without logo"
fi

if [[ -d "$FONTS" ]]; then
    args+=("-V" "fonts-path=$FONTS")
else
    echo "Warning: fonts not found at $FONTS -- using system fallback font"
fi

args+=("-o" "statement/problem.pdf")

echo "[..] Rendering PDF..."
pandoc "${args[@]}"
echo "[ok] PDF written to statement/problem.pdf"
