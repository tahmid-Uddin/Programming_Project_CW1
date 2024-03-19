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
            return 0;
        }
    }
    return sqrt(pow(abs(x - exitX), 2) + pow(abs(y - exitY),2));
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

void PathFinder(Maze *maze, int currentPositionX, int currentPositionY, int exitPositionX, int exitPositionY) {
    int min_index = 0; int min; double distancesArray[4];
    int finished = 0;
    ResetVisited(maze);
    while (finished == 0)  {
        DrawMaze(maze);
        usleep(100000);
        distancesArray[0] = 1000; distancesArray[1] = 1000; distancesArray[2] = 1000; distancesArray[3] = 1000;

        if (currentPositionX != 0 && maze->data[currentPositionY][currentPositionX - 1].data != '#' && maze->data[currentPositionY][currentPositionX - 1].visited != 1) {
            distancesArray[0] = DistanceToExit(currentPositionX - 1, currentPositionY, exitPositionX, exitPositionY);} //left

        if (currentPositionX != maze->cols-1&& maze->data[currentPositionY][currentPositionX + 1].data != '#' && maze->data[currentPositionY][currentPositionX + 1].visited != 1) {
            distancesArray[1] = DistanceToExit(currentPositionX + 1, currentPositionY, exitPositionX, exitPositionY);} //right

        if (currentPositionY != 0&& maze->data[currentPositionY - 1][currentPositionX].data != '#' && maze->data[currentPositionY - 1][currentPositionX].visited != 1) {
            distancesArray[2] = DistanceToExit(currentPositionX, currentPositionY - 1, exitPositionX, exitPositionY);} //up

        if (currentPositionY != maze->rows-1&& maze->data[currentPositionY + 1][currentPositionX].data != '#' && maze->data[currentPositionY + 1][currentPositionX].visited != 1) {
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
                    maze->data[currentPositionY][currentPositionX].data = '.';
                    maze->data[currentPositionY][currentPositionX].visited = 1;
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

void ResetVisited(Maze *maze) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            maze->data[i][j].visited = 0;
        }
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

    // Generate dummy exit points and creates paths to them
    int mazesGenerated = 1;
    int noDummyExits;
    int largestSide;

    double time = clock();
    for (int i = 0; i < mazesGenerated; i++) {
        EmptyMaze(mazePtr, startPositionX, startPositionY, exitPositionX, exitPositionY);
        PopulateMaze(mazePtr, 5);
        if (rows > cols) { largestSide = rows; }
        else { largestSide = cols; }
        noDummyExits = (int)ceil(largestSide * 0.3);

        int dummyExitCoordinates[(noDummyExits * 2)];
        int x; int y;
        
        for (int j = 0; j < noDummyExits; j++) {
            x = rand() % (cols - 1);
            y = rand() % (rows - 1);

            attempts = 0;
            while (((x == startPositionX && y == startPositionY) || (x == exitPositionX && y == exitPositionY) || (maze.data[y][x].data == '.') || (maze.data[y][x].data == '#') ||
                (checkValidCoordinates(x, y, j*2, dummyExitCoordinates, largestSide,startPositionX, startPositionY, exitPositionX, exitPositionY) == 1)) && (attempts < 10)) {
                    x = rand() % (cols - 1);
                    y = rand() % (rows - 1);
                    attempts++;
                }

            if (attempts < 10) {
                dummyExitCoordinates[(j * 2)] = x;
                dummyExitCoordinates[(j * 2) + 1] = y;

                maze.data[y][x].data = 'e';
            }
        }

        //Path to real exit node.
        for (int j = 0; j < noDummyExits; j++) {
            PathFinder(mazePtr, startPositionX, startPositionY, dummyExitCoordinates[j], dummyExitCoordinates[j + 1]);
        }

        PathFinder(mazePtr, startPositionX, startPositionY, exitPositionX, exitPositionY);

        // Populate maze with #
        printf("Paths:\n");
        DrawMaze(mazePtr);
        PopulateMaze(mazePtr, 50);
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