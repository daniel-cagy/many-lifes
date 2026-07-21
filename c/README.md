# Conway's Game of Life in C

This directory contains a C implementation of Conway's Game of Life.

The program asks for a square grid size, lets you enter the initial living
cells, then prints each generation once per second until the pattern stops
changing.

## Files

- `life.c` - interactive terminal implementation.

## Build

Compile with a C11-capable compiler:

```sh
gcc -std=c11 -Wall -Wextra -pedantic life.c -o life
```

If your platform requires an explicit threads library link, use:

```sh
gcc -std=c11 -Wall -Wextra -pedantic life.c -o life -pthread
```

## Run

```sh
./life
```

Coordinates are entered as `x y`, using 1-based indexing. For example, on a
5 by 5 grid, `1 1` is the top-left cell and `5 5` is the bottom-right cell.

## Notes

This version uses fixed grid edges. Cells outside the board are treated as
dead, so the grid does not wrap around.
