# Wordle-Solve

A C++ DLL-based Wordle solver that analyzes letter frequency and positional
data to suggest optimal word guesses.

---

## How It Works

The solver reads a word list and computes a scoring matrix for each letter of
the alphabet across all 5 positions. Each word is then ranked based on how
commonly its letters appear in the word list, both overall and positionally.
After each guess, the solver filters candidates based on the feedback provided
and returns the top 3 suggestions.

---

## Files

| File | Description |
|---|---|
| `WordleHeader.h` | Class declaration for `runWordle` |
| `Wordle.cpp` | Implementation of the solver logic |
| `words.txt` | Word list used for scoring and suggestions |

---

## Building

This project is configured as a Windows DLL.

- **Export:** Define `WORDLESOLVE_EXPORTS` to export the `runWordle` class.
- **Import:** Omit the define to import when consuming the DLL.

---

## Usage

### Initialization

```cpp
runWordle solver("words.txt");

// You can optionally tune the scoring weights:
// runWordle(filename, multiplierBase, multiplierPos)
runWordle solver("words.txt", 0.4, 1.7);
```

* **`multiplierBase`** — scales the overall letter frequency score.
* **`multiplierPos`** — scales the positional letter frequency score.

Once initialized, call `PlayWordle()` with your current game state to get suggestions.

### Other Methods

| Method | Description |
|---|---|
| `Reset()` | Clears all accumulated guess history |
| `isReady()` | Returns true if the word list loaded successfully |
| `setWeight(base, pos)` | Adjusts scoring multipliers and recomputes scores |
| `reAssign(filename, base, pos)` | Reloads word list and recomputes from scratch |
| `getPoints()` | Returns the current scoring matrix |
| `setPoints(matrix)` | Manually sets the scoring matrix |

---

## Scoring

Each letter is scored using the following formula:

```text
score = (overall_frequency * 100 * multiplierBase) + (positional_frequency * 100 * multiplierPos)
```

Frequencies are normalized against the total number of 5-letter words in the
list. Duplicate letters within a word are penalized by 70% of their positional
score to encourage diverse guesses.

---

## Requirements

* **C++17** or later
* **Windows** (uses `__declspec` for DLL export/import)
