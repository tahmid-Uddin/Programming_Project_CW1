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
    printf("===========\n");
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c", maze->data[i][j].data);
        }
        printf("\n");
    }
    printf("\n");
}

void PopulateMaze(Maze *maze, int density) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            if (maze->data[i][j].data != '.' && maze->data[i][j].data != 'S' && maze->data[i][j].data != 'E') {
                if (rand() % 100 < density) {
                    maze->data[i][j].data = '#';
                }
            }
            if (maze->data[i][j].data == '.' || maze->data[i][j].data == 'e') {
                maze->data[i][j].data = ' ';
            }    
        }
    }
}

void EmptyMaze(Maze *maze, int startX, int startY, int exitX, int exitY) {
    maze->visitedNodes = 0;
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            maze->data[i][j].data = ' ';
            maze->data[i][j].visited = 0;
        }
    }

    maze->data[startY][startX].data = 'S';
    maze->data[exitY][exitX].data = 'E';
}

void ResetVisited(Maze *maze) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            maze->data[i][j].visited = 0;
        }
    }
}

double DistanceToExit(int x, int y, int exitX, int exitY) {
    
    if (x == exitX) {
        if (y == exitY) {
            return 0;
        }
    }
    return sqrt(pow(abs(x - exitX), 2) + pow(abs(y - exitY),2));
}

int SelectRandomStart(Maze *maze) {
    int visitedNodesX[maze->visitedNodes];
    int visitedNodesY[maze->visitedNodes];
    int counter = 0;
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            if (maze->data[i][j].visited == 1) {
                visitedNodesX[counter] = j;
                visitedNodesY[counter] = i;
                counter ++;
            }
        }
    }
    int x = visitedNodesX[rand() % (counter)];
    int y = visitedNodesY[rand() % (counter)];
    return (x * 1000) + y;
}

void PathFinder(Maze *maze, int currentPositionX, int currentPositionY, int exitPositionX, int exitPositionY) {
    int min_index = 0; int min; double distancesArray[4];
    int finished = 0;

    while (finished == 0)  {
        DrawMaze(maze);
        usleep(50000);
        distancesArray[0] = 10000; distancesArray[1] = 10000; distancesArray[2] = 10000; distancesArray[3] = 10000;

        //&& maze->data[currentPositionY + 1][currentPositionX].data != '#' && maze->data[currentPositionY + 1][currentPositionX].visited != 1

        if (currentPositionX != 0) {
            distancesArray[0] = DistanceToExit(currentPositionX - 1, currentPositionY, exitPositionX, exitPositionY);} //left

        if (currentPositionX != maze->cols-1) {
            distancesArray[1] = DistanceToExit(currentPositionX + 1, currentPositionY, exitPositionX, exitPositionY);} //right

        if (currentPositionY != 0) {
            distancesArray[2] = DistanceToExit(currentPositionX, currentPositionY - 1, exitPositionX, exitPositionY);} //up

        if (currentPositionY != maze->rows-1) {
            distancesArray[3] = DistanceToExit(currentPositionX, currentPositionY + 1, exitPositionX, exitPositionY);} //down
        
        min = distancesArray[0];
        min_index = 0;
        for (int j = 1; j < 4; j++) {
            //printf("%f, ", distancesArray[j]);
            if (min > distancesArray[j]) {
                min = distancesArray[j];
                min_index = j;
            }
        }
    
        if (min_index == 0 && currentPositionX != 0) {currentPositionX--;}
        else if (min_index == 1 && currentPositionX != maze->cols - 1) {currentPositionX++;}
        else if (min_index == 2 && currentPositionY != 0) {currentPositionY--;}
        else if (min_index == 3 && currentPositionY != maze->rows - 1) {currentPositionY++;}

        if (maze->data[currentPositionY][currentPositionX].data != 'S') {
            if (maze->data[currentPositionY][currentPositionX].data != 'E') {
                if (maze->data[currentPositionY][currentPositionX].data != 'e') {
                    if (maze->data[currentPositionY][currentPositionX].data != 's') {
                        maze->data[currentPositionY][currentPositionX].data = '.';
                        maze->data[currentPositionY][currentPositionX].visited = 1;
                        maze->visitedNodes++;
                    }
                }
            }
        }

        if (currentPositionX == exitPositionX) {
            if (currentPositionY == exitPositionY) {
                finished = 1;
            }
        }
    }
}

int checkValidCoordinates(int x, int y, int j, int array[], int largestSide, int startX, int startY, int exitX, int exitY) {
    for (int i = 0; i < j; i = i + 2) {
        if (x == array[i] && y == array[i + 1]) {
            return 1;
        }

        if ((DistanceToExit(x, y, array[i], array[i + 1]) < largestSide * 0.2) ||
            (DistanceToExit(x, y, startX, startY) < largestSide * 0.2) || 
            (DistanceToExit(x, y, exitX, exitY) < largestSide * 0.2)) {
                return 1;
        }


    }
    return 0;
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

    EmptyMaze(mazePtr, startPositionX, startPositionY, exitPositionX, exitPositionY);

    

    // Generate dummy exit points and creates paths to them
    int mazesGenerated = 1;
    int noDummyExits;
    int noDetourPoints;
    int coords;
    int x; int y; int largestSide; 
    double time = clock();

    if (rows > cols) { largestSide = rows; }
    else { largestSide = cols;}

    
    for (int i = 0; i < mazesGenerated; i++) {
        noDummyExits = (int)ceil(largestSide * 0.3);
        int dummyExitCoordinates[(noDummyExits * 2)];

        noDetourPoints = (int)(largestSide * 0.2);
        int detourPointCoordinates[noDetourPoints * 2];
        detourPointCoordinates[0] = startPositionX;
        detourPointCoordinates[1] = startPositionY;

        for (int j = 1; j < noDetourPoints; j++) {
            x = rand() % (cols - 1);
            y = rand() % (rows - 1);
            attempts = 0;
            while (((x == startPositionX && y == startPositionY) || (x == exitPositionX && y == exitPositionY) ||
                   (checkValidCoordinates(x, y, j*2, detourPointCoordinates, largestSide, startPositionX, startPositionY, exitPositionX, exitPositionY) == 1)) && (attempts < 50)) {
                x = rand() % (cols - 1);
                y = rand() % (rows - 1);
            }

            if (attempts < 50) {
                detourPointCoordinates[j * 2] = x;
                detourPointCoordinates[(j * 2) + 1] = y;
                maze.data[y][x].data = 's';
                
                PathFinder(mazePtr, detourPointCoordinates[(j * 2) - 2], detourPointCoordinates[(j * 2) - 1], detourPointCoordinates[(j * 2)], detourPointCoordinates[((j * 2) + 1)]);
            }
        }

        PathFinder(mazePtr, detourPointCoordinates[(noDetourPoints * 2) - 2],  detourPointCoordinates[(noDetourPoints * 2)  - 1], exitPositionX, exitPositionY);

/*
        for (int j = 0; j < noDummyExits; j++) {
            x = rand() % (cols - 1);
            y = rand() % (rows - 1);

            attempts = 0;
            while (((x == startPositionX && y == startPositionY) || (x == exitPositionX && y == exitPositionY) || (maze.data[y][x].data == '.') || (maze.data[y][x].data == '#') ||
                (checkValidCoordinates(x, y, j*2, dummyExitCoordinates, largestSide,startPositionX, startPositionY, exitPositionX, exitPositionY) == 1)) && (attempts < 50)) {
                    x = rand() % (cols - 1);
                    y = rand() % (rows - 1);
                    attempts++;
                }

            if (attempts < 50) {
                dummyExitCoordinates[(j * 2)] = x;
                dummyExitCoordinates[(j * 2) + 1] = y;
                coords = SelectRandomStart(mazePtr);
                PathFinder(mazePtr, coords / 1000, coords % 1000, x, y);
            }
        }

*/

        

        // Populate maze with #
        printf("Paths:\n");
        DrawMaze(mazePtr);
        PopulateMaze(mazePtr, 60);
        printf("Finished Maze:\n");
        DrawMaze(mazePtr);
    }

    time = clock() - time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;  

    printf("Time taken to generate %d mazes: %f seconds\n", mazesGenerated, time_taken);
    printf("Time taken per maze: %f seconds\n", time_taken / mazesGenerated);

    // Creates the maze file.
    FILE *fptr;
    fptr = fopen(filename, "w");
    
    return 0;
}