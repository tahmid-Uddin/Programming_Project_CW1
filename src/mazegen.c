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
    // 1. The start can only be a distance of 10% of the total width and height
    //    of the maze away from the edge.
    // 2. The exit has to be atleast 40% of the total width and height of the maze
    //    away from the start.

    srand(time(NULL));
    int startPositionX; int startPositionY; 
    int exitPositionX; int exitPositionY;
    int exitMinDistance;
    int valid = 0; int attempts;

    while (valid == 0) { 
        attempts = 0;

        // Creates a random starting position.
        if ((rand() % 2) == 1) { // 50% of the start being at the left or top edge.
            startPositionY = rand() % rows; 
            startPositionX = rand() % (int)(cols * 0.1 + 1); // Left edge.

            if ((rand() % 2) == 1) { // 50% chance of the start being at the left or right edge
                startPositionX = maze.cols - startPositionX - 1; // Right Edge
         }}

        else {
            startPositionX = rand() % cols; 
            startPositionY = rand() % (int)(rows * 0.1 + 1); // Top edge.

            if ((rand() % 2) == 1) { // 50% chance of the start being at the top or bottom edge
                startPositionY = maze.rows - startPositionY - 1; // Bottom Edge
        }}


        while (valid == 0 && attempts < 10) {
            exitPositionX = rand() % cols;
            exitPositionY = rand() % rows;

            if (abs(exitPositionY - startPositionY) > (rows * 0.4)){
                if (abs(exitPositionX - startPositionX) > (cols * 0.4)) {
                    valid = 1;
            }}

            attempts++;       
        }
    }

    maze.data[startPositionY][startPositionX] = 'S';
    maze.data[exitPositionY][exitPositionX] = 'E';

    DrawMaze(mazePtr);

    // Creates the maze file.
    FILE *fptr;
    fptr = fopen(filename, "w");

    return 0;
}