#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"


void DrawMaze(Array2D *maze) {
    printf("\n");
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c", maze->data[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char *argv[]) {
    char *filename = argv[1];
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    

    // Validates dimensions
    if (!(rows >= 5 && rows <= 100 && cols >= 5 && cols <= 100)) {
        printf("Invalid maze size given.\n");
        return 1;
    }


    // Creates the maze file.
    FILE *fptr;
    fptr = fopen(filename, "w");


    // Initializes the maze array.
    Array2D maze;
    Array2D *mazePtr = &maze;
    maze.rows = rows;
    maze.cols = cols;
    maze.data = malloc(maze.rows*sizeof(char*));

    for (int i = 0; i < maze.rows; i++) {
        maze.data[i] = malloc(maze.cols*sizeof(char));
    }

    for (int i = 0; i < maze.rows; i++) {
        for (int j = 0; j < maze.cols; j++) {
            maze.data[i][j] = '.';
        }
    }


    // Creates the Start and Exit of the maze based on certain criteria.
    srand(time(NULL));
    int startPositionX; int startPositionY; 
    int exitPositionX; int exitPositionY;
    int exitMinDistance;

    if ((rand() % 2) == 1) {
        startPositionX = rand() % (int)(cols * 0.1 + 1);
        if ((rand() % 2) == 1) {
            startPositionX = maze.cols - startPositionX - 1;
        }
        startPositionY = rand() % rows;
    }

    else {
        startPositionX = rand() % cols;
        startPositionY = rand() % (int)(rows * 0.1 + 1);
        if ((rand() % 2) == 1) {
            startPositionY = maze.rows - startPositionY - 1;
        }
    }


    exitPositionX = rand() % cols;
    exitPositionY = rand() % rows;
    while ((abs(exitPositionY - startPositionY) < (cols * 0.7)) && 
           (abs(exitPositionX - startPositionX) < (rows * 0.7))) {
        exitPositionX = rand() % cols;
        exitPositionY = rand() % rows;

        printf("Exit Position: (%d, %d)\n", exitPositionX, exitPositionY);
    }


    printf("\nStart Position: (%d, %d)\n", startPositionX, startPositionY);
    printf("Exit Position: (%d, %d)\n", exitPositionX, exitPositionY);

    maze.data[startPositionY][startPositionX] = 'S';
    maze.data[exitPositionY][exitPositionX] = 'E';

    
    DrawMaze(mazePtr);
    
    return 0;
}