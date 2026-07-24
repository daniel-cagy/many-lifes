# Conway's Game of Life

This repository is a collection of Conway's Game of Life implementations in
different programming languages.

The goal is to keep each implementation small, readable, and easy to build from
its own directory. The repository currently contains a terminal C version and a
graphical C version built with raylib.

## Implementations

| Language | Directory | Status |
| --- | --- | --- |
| C | [`c/`](c/) | Available |
| C + raylib | [`c-raylib/`](c-raylib/) | Available |

## What Is Conway's Game of Life?

Conway's Game of Life is a cellular automaton played on a grid of cells. Each
cell is either alive or dead, and every generation is computed from the previous
one using the same four rules:

- A live cell with fewer than two live neighbors dies.
- A live cell with two or three live neighbors survives.
- A live cell with more than three live neighbors dies.
- A dead cell with exactly three live neighbors becomes alive.

Even with those simple rules, the system can produce stable shapes, repeating
patterns, and more complex behavior.

## Current Version

The C implementation is an interactive terminal program. It asks for a square
grid size, accepts the initial living cells, then prints each generation until
the pattern stops changing.

See [`c/README.md`](c/README.md) for build and run instructions.

The C + raylib implementation is a graphical version. It opens a fullscreen
window, supports mouse editing, random grid generation, clearing, pausing, and
speed controls.

See [`c-raylib/README.md`](c-raylib/README.md) for build and run instructions.

## Repository Layout

```text
.
├── README.md
├── c/
│   ├── README.md
│   └── life.c
└── c-raylib/
    ├── README.md
    └── life.c
```

## Adding More Implementations

New language implementations should live in their own top-level directory, with
their own README explaining how to build and run that version.
