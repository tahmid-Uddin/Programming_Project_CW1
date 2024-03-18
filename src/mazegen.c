#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "func.h"


void DrawMaze(Maze *maze) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c", maze->data[i][j].data);
        }
        printf("\n");
    }
    printf("\n");
}

double DistanceToExit(int x, int y, int exitX, int exitY) {
    
    if (x == exitX) {
        if (y == exitY) {
            return 1;
        }
    }
    return (1 / (sqrt(pow(abs(x - exitX), 2) + pow(abs(y - exitY), 2))));
}

void EmptyMaze(Maze *maze, int startX, int startY, int exitX, int exitY) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            maze->data[i][j].data = ' ';
            maze->data[i][j].visited = 0;
        }
    }

    maze->data[startY][startX].data = 'S';
    maze->data[exitY][exitX].data = 'E';
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

    printf("%d x %d maze.\n", rows, cols);


    // Initializes the maze array.
    Maze maze;
    Maze *mazePtr = &maze;
    maze.rows = rows;
    maze.cols = cols;
    maze.data = malloc(maze.rows*sizeof(Node));

    for (int i = 0; i < maze.rows; i++) {
        maze.data[i] = malloc(maze.cols*sizeof(Node));
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
    
    startPositionX = 2;
    startPositionY = 2;
    exitPositionX = cols - 2;
    exitPositionY = rows - 2;
    EmptyMaze(mazePtr, startPositionX, startPositionY, exitPositionX, exitPositionY);


    // Random walk algorithmn.
    int currentPositionX; int currentPositionY;
    double left; double right; double up; double down; double sum;
    int adjacentNode1; int adjacentNode2;
    int* probabilitySpace; int direction;
    int stepsAverage = 0; int steps = 1000;

    double time = clock();
    for (int i = 0; i < 1; i++) {
        steps = 0;
        currentPositionX = startPositionX;
        currentPositionY = startPositionY;

        while (maze.data[currentPositionY][currentPositionX].data != 'E') {
            steps++;
            usleep(100000);
            DrawMaze(mazePtr);
            left = 0; right = 0; up = 0; down = 0;

            // Finds the distance between valid adjacent nodes and the exit.
            if (currentPositionX != 0 && maze.data[currentPositionY][currentPositionX - 1].visited == 0) {
                adjacentNode1 = 0; adjacentNode2 = 0;
                if (currentPositionY > 0) {
                    adjacentNode1 = maze.data[currentPositionY - 1][currentPositionX - 1].visited;
                }
                if (currentPositionY < rows - 1) {
                    adjacentNode2 = maze.data[currentPositionY + 1][currentPositionX - 1].visited;
                }

                if (adjacentNode1 == 0 || adjacentNode2 == 0) {
                    left = DistanceToExit(currentPositionX - 1, currentPositionY, exitPositionX, exitPositionY); 
                }
            }

            if (currentPositionX != cols - 1 && maze.data[currentPositionY][currentPositionX + 1].visited == 0) {
                adjacentNode1 = 0; adjacentNode2 = 0;
                if (currentPositionY > 0) {
                    adjacentNode1 = maze.data[currentPositionY - 1][currentPositionX + 1].visited;
                }
                if (currentPositionY < rows - 1) {
                    adjacentNode2 = maze.data[currentPositionY + 1][currentPositionX + 1].visited;
                }

                if (adjacentNode1 == 0 || adjacentNode2 == 0) {
                    right = DistanceToExit(currentPositionX + 1, currentPositionY, exitPositionX, exitPositionY);
                }
            }
                
            if (currentPositionY != 0 && maze.data[currentPositionY - 1][currentPositionX].visited == 0) { 
                adjacentNode1 = 0; adjacentNode2 = 0;
                if (currentPositionX > 0) {
                    adjacentNode1 = maze.data[currentPositionY - 1][currentPositionX - 1].visited;
                }
                if (currentPositionX < cols - 1) {
                    adjacentNode2 = maze.data[currentPositionY - 1][currentPositionX + 1].visited;
                }

                if (adjacentNode1 == 0 || adjacentNode2 == 0) {
                   up = DistanceToExit(currentPositionX, currentPositionY - 1, exitPositionX, exitPositionY);
                }
            }

            if (currentPositionY != rows - 1 && maze.data[currentPositionY + 1][currentPositionX].visited == 0) {
                adjacentNode1 = 0; adjacentNode2 = 0;
                if (currentPositionX > 0) {
                    adjacentNode1 = maze.data[currentPositionY + 1][currentPositionX - 1].visited;
                }
                if (currentPositionX < cols - 1) {
                    adjacentNode2 = maze.data[currentPositionY + 1][currentPositionX + 1].visited;
                }

                if (adjacentNode1 == 0 || adjacentNode2 == 0) {
                   down = DistanceToExit(currentPositionX, currentPositionY + 1, exitPositionX, exitPositionY);
                }
            }

            
            // Creates the probability distribution for each direction.
            sum = left + right + up + down;
            if (sum != 0) {            
                left = round((left / sum) * 1000);
                right = round((right / sum) * 1000);
                up = round((up / sum) * 1000);
                down = round((down / sum) * 1000);
                sum = left + right + up + down;

                printf("Current Position: (%d, %d)\n", currentPositionX, currentPositionY);
                printf("Left: %.1f, Right: %.1f, Up: %.1f, Down: %.1f, Sum: %.1f\n", left/10, right/10, up/10, down/10, sum/10);

                // Creates a probability space of the distribution, which can be used to pick a direction.
    
                probabilitySpace = malloc(sum * sizeof(int));
                for (int i = 0; i < left; i++) {probabilitySpace[i] = 0;}
                for (int i = left - 1; i < left + right; i++) {probabilitySpace[i] = 1;}
                for (int i = left + right - 1; i < left + right + up; i++) {probabilitySpace[i] = 2;}
                for (int i = left + right + up - 1; i < sum; i++) {probabilitySpace[i] = 3;}

                direction = probabilitySpace[rand() % (int)sum];
            }

            else {
                direction = rand() % 4;
            }
        
            
            if (direction == 0 && currentPositionX != 0) {currentPositionX--;}
            else if (direction == 1 && currentPositionX != cols - 1) {currentPositionX++;}
            else if (direction == 2 && currentPositionY != 0) {currentPositionY--;}
            else if (direction == 3 && currentPositionY != rows - 1) {currentPositionY++;}

            if (maze.data[currentPositionY][currentPositionX].data != 'S') {
                if (maze.data[currentPositionY][currentPositionX].data != 'E') {
                    maze.data[currentPositionY][currentPositionX].data = '.';
                    maze.data[currentPositionY][currentPositionX].visited = 1;
                }
            }
        }
        
        stepsAverage = stepsAverage + steps;
    }
    
    time = clock() - time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;  
    

    // Populate maze
    for (int i = 0; i < maze.rows; i++) {
        for (int j = 0; j < maze.cols; j++) {
            if (maze.data[i][j].data!= '.' && maze.data[i][j].data!= 'S' && maze.data[i][j].data != 'E') {
                if (rand() % 10 > 4) {
                    maze.data[i][j].data = '#';
                }
            }
            if (maze.data[i][j].data == '.') {
                maze.data[i][j].data = ' ';
            }    
        }
    }

    DrawMaze(mazePtr);
    printf("\nAverage number of steps from 1000 random walks: %d\n", stepsAverage);
    printf("Time taken: %f seconds\n", time_taken);
    printf("Time taken per maze: %f seconds\n", time_taken / 1000);

    // Creates the maze file.
    FILE *fptr;
    fptr = fopen(filename, "w");
    
    return 0;
}