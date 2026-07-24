#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


void draw_grid(int rows, int cols, int grid[rows][cols], Color life, Color not_life, int cell_size);
void clear_grid(int rows, int cols, int grid[rows][cols]);
void random_grid(int rows, int cols, int grid[rows][cols]);
int num_neighbors(int i, int j, int rows, int cols, int grid[rows][cols]);

int main() {
    srand(time(NULL));

    Color dark_green = {20, 90, 33, 255};
    Color dark_grey = {29, 29, 29, 255};

    const int settings_fps = 60;
    int gameplay_fps = 6;

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Hello Life!!");
    ToggleBorderlessWindowed();
    ToggleFullscreen();
    SetTargetFPS(settings_fps);

    const int SCREEN_WIDTH = GetScreenWidth();
    const int SCREEN_HEIGHT = GetScreenHeight();
    const int CELL_SIZE = 20;
    const int NUM_ROWS = SCREEN_HEIGHT / CELL_SIZE;
    const int NUM_COLS = SCREEN_WIDTH / CELL_SIZE;

    int grid[NUM_ROWS][NUM_COLS];
    
    clear_grid(NUM_ROWS, NUM_COLS, grid);

    int future_grid[NUM_ROWS][NUM_COLS];
    memcpy(future_grid, grid, sizeof(grid));

    int is_running = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            if (is_running) {
                is_running = 0;
                SetTargetFPS(settings_fps);
            }
            else {
                is_running = 1;
                SetTargetFPS(gameplay_fps);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse_position = GetMousePosition();
            int row = mouse_position.y / CELL_SIZE;
            int col = mouse_position.x / CELL_SIZE;
            if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
                grid[row][col] = !grid[row][col];
                future_grid[row][col] = grid[row][col];
            }
        }

        if (IsKeyPressed(KEY_R)) {
            random_grid(NUM_ROWS, NUM_COLS, grid);
            memcpy(future_grid, grid, sizeof(grid));
        }

        if (IsKeyPressed(KEY_C)) {
            clear_grid(NUM_ROWS, NUM_COLS, grid);
            clear_grid(NUM_ROWS, NUM_COLS, future_grid);
        }

        if (IsKeyPressed(KEY_UP) && is_running) {
            SetTargetFPS(gameplay_fps+=2);
        }

        if (IsKeyPressed(KEY_DOWN) && is_running && gameplay_fps > 6) {
            SetTargetFPS(gameplay_fps-=2);
        }

        if (is_running){
            memcpy(future_grid, grid, sizeof(grid));
            for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {
                    int neighbors = num_neighbors(i, j, NUM_ROWS, NUM_COLS, grid);
                    if (grid[i][j] == 0) {
                        if (neighbors == 3) {
                            future_grid[i][j] = 1;
                        }
                    }
                    else {
                        if (neighbors < 2 || neighbors > 3) {
                            future_grid[i][j] = 0;
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        draw_grid(NUM_ROWS, NUM_COLS, grid, dark_green, dark_grey, CELL_SIZE);
        EndDrawing();

        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                grid[i][j] = future_grid[i][j];
            }
        }
    }
    CloseWindow();
    return 0;
}

void draw_grid(int rows, int cols, int grid[rows][cols], Color life, Color not_life, int cell_size) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Color color = grid[i][j] ? life : not_life;
            DrawRectangle(j * cell_size, i * cell_size, cell_size - 1, cell_size - 1, color);
        }
    }
}

void clear_grid(int rows, int cols, int grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }
}

void random_grid(int rows, int cols, int grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

int num_neighbors(int i, int j, int rows, int cols, int grid[rows][cols]) {
    int counter = 0;
    for (int k = i - 1; k <= i + 1; k++) {
        if (k < 0 || k >= rows) {
            continue;
        }
        for (int l = j - 1; l <= j + 1; l++) {
            if (l < 0 || l >= cols) {
                continue;
            }
            if (k == i && l == j) {
                continue;
            }
            if (grid[k][l]) {
                counter++;
            }
        }
    }
    return counter;
}


