# GCPC-2k26-Challenges

Contest challenges for **GDG Algiers — GCPC 2026**.

## Problems

| Label | Name | Author | Difficulty | Status |
|-------|------|--------|------------|--------|
| A | [Dungeon Escape](./challenges/dungeon-escape/statement/problem.md) | Lyes Boudjabout | Easy | Published |
| B | [Festival Queue Merges](./challenges/festival-queue-merges/statement/problem.md) | Lyes Boudjabout | Easy | Published |
| C | [Relief Distribution](./challenges/relief-distribution/statement/problem.md) | Lyes Boudjabout | Easy | Published |
| D | [Arduino Breadboard Setup](./challenges/breadboard/statement/problem.md) | Raouf Ould Ali | Medium | Published |
| E | [Circuit Breaker](./challenges/circuit-breaker/statement/problem.md) | Bouzara Zakaria | Medium | Published |
| F | [Cloud Battle](./challenges/cloud/statement/problem.md) | Redhouane Abdellah | Medium | Published |
| G | [Emergency Lane](./challenges/emergency-lane/statement/problem.md) | tarek-ait | Medium | Published |
| H | [Permutation Riddle](./challenges/riddle/statement/problem.md) | Redhouane Abdellah | Medium | Published |
| I | [The Sarrus Oracle](./challenges/sarrus-oracle/statement/problem.md) | tarek-ait | Medium | Published |
| J | [Rassim Sort](./challenges/sort/statement/problem.md) | Redhouane Abdellah | Medium | Published |
| K | [Midnight Relay Tour](./challenges/midnight-relay-tour/statement/problem.md) | tarek-ait | Medium-Hard | Published |
| L | [AI Simulation on Uncle Island](./challenges/ai-simulation-uncle-island/statement/problem.md) | Firas Mohamed Elamine Kiram | Hard | Published |
| M | [Hoggar Trail](./challenges/hoggar-trail/statement/problem.md) | Firas Mohamed Elamine Kiram | Hard | Published |
| N | [Quantum Pyramid](./challenges/quantum-pyramid/statement/problem.md) | Raouf Ould Ali | Hard | Published |
| O | [Card Tricks](./challenges/tricks/statement/problem.md) | Raouf Ould Ali | Hard | Published |

> Status lifecycle: `draft` → `ready` → `tested` → `published`
> Update this table and `contest.yaml` together when adding/changing a problem.

---

## Adding a New Challenge

1. Copy `challenges/_challenge-template/` → `challenges/<problem-id>/`
   - Use a short lowercase slug as the folder name, e.g. `robery` or `allo-nokia`
   - This folder name becomes the problem's external ID in DOMjudge
2. Generate a UUID and put it in `problem.yaml`:
   ```bash
   python3 -c "import uuid; print(uuid.uuid4())"
   ```
3. Fill in `problem.yaml` (name, time_limit) and `domjudge-problem.ini` (color)
4. Write the statement in `statement/problem.md`
5. Add test cases to `data/sample/` and `data/secret/` as `.in`/`.ans` pairs
6. Replace the skeleton solutions in `submissions/accepted/` with real solutions in all 6 languages (c, cpp, py, go, js, java)
7. Write the editorial in `editorial/editorial.md`
8. Add an entry to `contest.yaml` and update the table above

---

## Test Case Format

### Sample vs Secret

| Folder | Visible to contestants? | Purpose |
|--------|------------------------|---------|
| `data/sample/` | **Yes** — shown in problem statement | The same examples printed in the PDF. Contestants can run these themselves. |
| `data/secret/` | **No** — hidden during contest | The real judging test cases. Cover edge cases, large inputs, stress tests, etc. |

DOMjudge imports test cases by scanning for `*.in` / `*.ans` pairs.  
**Do not use `.txt`** — DOMjudge ignores files that don't match these extensions.

### File naming

```
data/
├── sample/
│   ├── 1.in        ← sample test case 1 input
│   └── 1.ans       ← sample test case 1 expected output
└── secret/
    ├── 01.in       ← zero-padded so they sort correctly
    ├── 01.ans
    ├── 01.desc     ← one-liner describing what this case tests (for authors only)
    ├── 02.in
    ├── 02.ans
    └── 02.desc
```

### `.desc` files

Optional one-line description of what a secret test case tests. DOMjudge stores this and shows it to the jury. Examples:
```
edge case: n=1
maximum input: n=100000, all elements equal
random large input
adversarial case: strictly decreasing sequence
```

### Important rules

- No Windows line endings (`\r\n`) — use Unix line endings (`\n`) only
- Both `.in` and `.ans` must end with a newline
- Sample test cases must exactly match the examples printed in `statement/problem.md`

---

## DOMjudge Verdict Types

When a submission is judged, DOMjudge returns one of these verdicts:

| Verdict | Meaning |
|---------|---------|
| **AC** — Accepted | Output matches `.ans` for all test cases within time and memory limits |
| **WA** — Wrong Answer | Output doesn't match `.ans` on at least one test case |
| **TLE** — Time Limit Exceeded | Solution ran longer than `timelimit` seconds on at least one case |
| **MLE** — Memory Limit Exceeded | Solution used more memory than the `memory` limit |
| **RTE** — Run-Time Error | Solution crashed (segfault, exception, non-zero exit code) |
| **CE** — Compile Error | Solution failed to compile |
| **NO** — No Output | Solution produced empty output |

---

## Supported Languages

All accepted solutions must be provided in **all 6 languages**:

| Language | Extension | Notes |
|----------|-----------|-------|
| C | `.c` | gcc, C17 |
| C++ | `.cpp` | g++, C++17 |
| Java | `.java` | OpenJDK — class name must match filename |
| Python 3 | `.py` | CPython 3 |
| Go | `.go` | Go 1.20 (custom-installed on judgehosts) |
| JavaScript | `.js` | Node.js |

---

## Testing a Solution Locally

Run from **inside** the problem directory:

```bash
cd challenges/<problem-id>

# pre-compiled binary
../../scripts/solution_test.sh ./sol

# auto-compiled/interpreted source
../../scripts/solution_test.sh submissions/accepted/sol.cpp
../../scripts/solution_test.sh submissions/accepted/sol.py
../../scripts/solution_test.sh submissions/accepted/sol.go
../../scripts/solution_test.sh submissions/accepted/sol.java
```

The script tests all cases in `data/sample/` first, then `data/secret/`, and reports `AC / WA / TLE` per case. Exits non-zero if any case fails.

---

## Generating PDFs

Authors write Markdown in `statement/problem.md`. Run from inside the challenge directory:

```bash
cd challenges/<problem-id>
../../scripts/render-pdf.sh
```

**Install once (Linux):**
```bash
sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
```

**macOS:**
```bash
brew install pandoc && brew install --cask basictex
sudo tlmgr update --self && sudo tlmgr install collection-xetex collection-latexextra
```

**Windows:** install [Pandoc](https://pandoc.org/installing.html) + [MiKTeX](https://miktex.org) (auto-downloads missing LaTeX packages on first run).

> **No local install needed?** Push your `.md` — the GitHub Actions workflow renders the PDF automatically and uploads it as a downloadable artifact.
