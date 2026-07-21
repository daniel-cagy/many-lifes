#include <stdio.h>
#include <ctype.h>
#include <threads.h>
#include <string.h>

int num_neighbors(int i, int j, int res, int grid[res][res]);

int main(void) {
    int res;
    
    while (1) {
        printf("Enter grid resolution: ");
        int result = scanf(" %d", &res);
        if (result == EOF) {
            printf("\nInput ended.\n");
            return 0;
        }
        if (result != 1 || res < 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\nInvalid input. Resolution must be a positive number.\n");
            continue;
        }
        break;
    }
    int grid[res][res];
    for (int i = 0; i < res; i++) {
        for (int j = 0; j < res; j++) {
            grid[i][j] = 0;
        }
    }

    char input;
    do {
        while (1) {
            printf("Add a living cell? (y / N)\n");
            int result = scanf(" %c", &input);
            if (result == EOF) {
                input = 'N';
                break;
            }
            if (result == 1) {
                input = toupper((unsigned char) input);
                if (input == 'Y' || input == 'N') {
                    break;
                }
            }
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Type Y/y for yes or N/n for no.\n");
        }
        if (input == 'Y') {
            int x, y;
                while (1) {
                    printf("Cell coordinates (x y, or x ENTER y): ");
                    int result = scanf("%d %d", &x, &y);
                    if (result == EOF) {
                        printf("\nInput ended.\n");
                        return 0;
                    }
                    if (result != 2) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("\nInvalid input. Must type x and y values.\n");
                        continue;
                    }
                    x--;
                    y--;
                    if (x < 0 || x > res - 1 || y < 0 || y > res - 1) {
                        printf("\nInvalid input. x and y must be between 1 and %i.\n", res);
                        continue;
                    }
                    grid[y][x] = 1;
                    break;
                }
            }
        } while (input != 'N');

    printf("\n\n");
    
    int future_grid[res][res];
    memcpy(future_grid, grid, sizeof(grid));
    
    int generation = 0;
    while (1) {
        printf("Generation %i:\n", generation);
        for (int i = 0; i < res; i++) {
            for (int j = 0; j < res; j++){
                if (grid[i][j] == 0) {
                    printf("( )");
                    
                    if (num_neighbors(i, j, res, grid) == 3) {
                        future_grid[i][j] = 1;
                    }
                }
                else {
                    printf("(x)");

                    if (num_neighbors(i, j, res, grid) < 2 || num_neighbors(i, j, res, grid) > 3) {
                        future_grid[i][j] = 0;
                    }
                }
            }
            printf("\n");
        }
        printf("\n");

        fflush(stdout);
        struct timespec duration = {.tv_sec = 1, .tv_nsec = 0};
        thrd_sleep(&duration, NULL);

        int changed = 0;
        for (int i = 0; i < res; i++) {
            for (int j = 0; j < res; j++) {
                if (grid[i][j] != future_grid[i][j]) {
                    changed = 1;
                    grid[i][j] = future_grid[i][j];
                }
            }
        }
        if (!changed) {
            break;
        }
        generation++;
    }

    return 0;
}

int num_neighbors(int i, int j, int res, int grid[res][res]) {
    int counter = 0;

    for (int k = i - 1; k <= i + 1; k++) {
        if (k < 0) {
            continue;
        }
        else if (k >= res) {
            break;
        }
        for (int l = j - 1; l <= j + 1; l++) {
            if (l < 0) {
                continue;
            }
            else if (l >= res) {
                break;
            }
            else if (k == i && l == j) {
                continue;
            }
            if (grid[k][l] == 1) {
                counter++;
            }
        } 
    }
    return counter;
}

