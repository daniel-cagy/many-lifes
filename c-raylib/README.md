# Conway's Game of Life in C with raylib

This directory contains a graphical C implementation of Conway's Game of Life
using raylib.

The program opens a fullscreen window, lets you toggle cells with the mouse,
then runs the simulation at an adjustable speed.

## Files

- `life.c` - graphical raylib implementation.

## Build

Compile with a C11-capable compiler and link raylib:

```sh
gcc -std=c11 -Wall -Wextra -pedantic life.c -o life -lraylib -lm
```

Depending on your platform and raylib installation, you may also need to link
system graphics libraries. On Linux, that can look like:

```sh
gcc -std=c11 -Wall -Wextra -pedantic life.c -o life -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

## Run

```sh
./life
```

Controls:

- Left mouse button toggles a cell.
- Enter starts or pauses the simulation.
- R fills the grid with random live and dead cells.
- C clears the grid.
- Up increases the simulation speed while running.
- Down decreases the simulation speed while running.

## Notes

This version uses fixed grid edges. Cells outside the board are treated as
dead, so the grid does not wrap around.
