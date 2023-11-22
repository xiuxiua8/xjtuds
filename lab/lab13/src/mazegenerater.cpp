#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define WALL 1
#define PATH 0
#define START 9
#define END 7

void printMaze(int maze[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

void generateMaze(int maze[ROWS][COLS]) {
    // Set all cells to walls
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = WALL;
        }
    }

    // Place the start and end points
    maze[ROWS - 2][1] = START;  // Start point
    maze[1][COLS - 2] = END;    // End point

    // Seed for random generation
    srand(time(NULL));

    // Generate random paths in the maze
    for (int i = 2; i < ROWS - 2; i++) {
        for (int j = 1; j < COLS - 2; j++) {
            if (rand() % 3 == 0) {
                maze[i][j] = PATH;
            }
        }
    }
}

void saveMazeToFile(int maze[ROWS][COLS], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(file, "%d ", maze[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    int maze[ROWS][COLS];

    generateMaze(maze);

    printf("Generated Maze:\n");
    printMaze(maze);

    saveMazeToFile(maze, "maze.txt");

    printf("Maze saved to maze.txt\n");

    return 0;
}
