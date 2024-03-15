#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"


int readFile(char *filename) {
    /*
        Checks if the file exists and return 2 if it doesn't.
        Counts the number of rows and colums of the file and returns the values.
        If file doesn't exist, display "Error: File doesn't exist".
    */
    FILE *fptr;
    fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Error: File doesn't exist\n");
        return 2;
    }

    fclose(fptr);
    return 0;
}


int validateMazeSize(char *filename) {
    /*
        Reads the contents of the maze to see if the maze is valid.
        - Returns 1 if the maze is valid, 0 otherwise.

        Checks if the maze is within the bounds set by the constants.
            - "Error: Invalid Maze size"
        Checks if the maze has uniform row lengths.
            - "Error: All rows and columns are not the same size"

        If any of these checks fail, the relavent error message will be printed.
    */
    FILE *fptr;
    fptr = fopen(filename, "r");

    int buffer = 1000;
    char line[buffer];

    // Counts the number of rows and columns in the file and makes sure that all rows
    // have the same number of columns.
    fgets(line, buffer, fptr);
    int cols = strlen(line);
    int rows = 1;
    int currentColLength;

    while (fgets(line, buffer, fptr)) 
    {
        currentColLength = strlen(line);
        if (currentColLength == cols) {
            rows++;
        }   

        else {
            printf("Error: All rows and columns are not the same size\n");
            fclose(fptr);
            return 3;
        }
    }

    // Checks that the rows and columns are in the valid range.
    printf("%d rows and %d columns", rows, cols);
    if (!(rows >= MIN_HEIGHT && rows <= MAX_HEIGHT && cols - 1 >= MIN_HEIGHT && cols - 1 <= MAX_HEIGHT)) {
        printf("Error: Invalid Maze size\n");
        fclose(fptr);
        return 3;
    }

    fclose(fptr);
    return (rows * 1000) + cols - 1;
}


int validateMazeContents(char *filename, Array2D *maze, Player *player) {
    /*
        Reads the contents of the maze to see if the maze is valid.
        Updates the players x and y position to where the S character is in the maze.
        - Returns 1 if the maze is valid, 0 otherwise.

        Checks if the maze has any invalid characters.
            - "Error: Unknown Characters in the Maze"
        Checks if the maze has a single start and exit point.
            - "Error: Has invalid number of Start and Exits"

        If any of these checks fail, the relavent error message will be printed.
    */

    FILE *fptr;
    fptr = fopen(filename, "r");

    int buffer = 1000;
    int sCounter = 0;
    int eCounter = 0;
    char line[buffer];

    for (int i = 0; i < maze->rows; i++) {
        fgets(line, buffer, fptr);

        for (int j = 0; j < maze->cols; j++) {
            
            if (line[j] == 'S') {
                player->xPosition = j;
                player->yPosition = i;
                sCounter++;
            }

            if (line[j] == 'E') {
                maze->exitXPosition = j;
                maze->exitYPosition = i;
                eCounter++;
            }

            if (line[j] == ' ' || line[j] == '#' || line[j] == 'S' || line[j] == 'E') {
                maze->data[i][j] = line[j];
            }

            else {
                printf("%c", line[j]);
                printf("Error: Unknown Characters in the Maze\n");
                fclose(fptr);
                return 3;
            }            
        }
    }

    if (!(eCounter == 1 && sCounter == 1))
    {
        printf("Error: Has invalid number of Start and Exits");
        return 3;
    }

    fclose(fptr);
    return 0;
}


int checkInput(char input[]) {
    /*
        Checks the user input to see if it is valid.
        - Returns 1 if the input is valid, 0 otherwise.

        Valid inputs are W,A,S,D,M,w,a,s,d,m.
        All other characters are invalid.

        The relavent error message will be printed for invalid inputs.
            - "Error: Invalid user input"
    */

    if ((input[0] == 'W' || input[0] == 'w' || input[0] == 'A' || input[0] == 'a' ||
        input[0] == 'S' || input[0] == 's' || input[0] == 'D' || input[0] == 'd' ||
        input[0] == 'M' || input[0] == 'm') && (strlen(input) == 2)) {
            
        return 0;
    }

    printf("Error: Invalid user input\n");
    return 1;
}


int checkValidMove(char input, Array2D *maze, Player *player) {
    /*
        Checks the square that the user is trying to move
        to see if it is valid. Valid squares are blank spaces,
        S characters, and E characters ONLY.

        The relavent error message will be printed for invalid inputs.
            - "You cannot walk into a wall. Try moving somewhere else!"
            - "You cannot walk off the edge of the maze. Try moving somewhere else!"
    

        Calculates the new x and y position and calls movePlayer() to move the player 
        if the move is valid.

        Returns 1 if the square is valid, 0 otherwise and 2 if the game is over.
    */
    int xChange; int yChange;

    if (input == 'M' || input == 'm') {
        drawMaze(maze);
        return 0;
    }

    else if (input == 'W' || input == 'w') {
        if (player->yPosition == 0) {
            printf("You cannot walk off the edge of the maze. Try moving somewhere else!\n");
            return 1;
        }
        xChange = 0; yChange = -1;
    }

    else if (input == 'S' || input == 's') {
        if (player->yPosition == maze->rows - 1) {
            printf("You cannot walk off the edge of the maze. Try moving somewhere else!\n");
            return 1;
        }
        xChange = 0; yChange = 1;
    }

    else if (input == 'A' || input == 'a') {
        if (player->xPosition == 0) {
            printf("You cannot walk off the edge of the maze. Try moving somewhere else!\n");
            return 1;
        }
        xChange = -1; yChange = 0;
    }

    else if (input == 'D' || input == 'd') {
        if (player->xPosition == maze->cols - 1) {
            printf("You cannot walk off the edge of the maze. Try moving somewhere else!\n");
            return 1;
        }
        xChange = 1; yChange = 0;
    }


    if (maze->data[player->yPosition + yChange][player->xPosition + xChange] == '#') {
        printf("You cannot walk into a wall. Try moving somewhere else!\n");
        return 1;
    }

    maze->data[player->yPosition][player->xPosition] = ' ';
    player->xPosition += xChange;
    player->yPosition += yChange;

    if (checkGameOver(maze, player->xPosition, player->yPosition) == 4) {
        return 4;
    }

    maze->data[player->yPosition][player->xPosition] = 'S';
    
    return 0;    
}


void movePlayer(char input, Player *player, char *maze, int newXPosition, int newYPosition) {
    /*
        -Makes the current player position in the maze a blank space.
        -Updates the x and y position of the player struct.
        -Calls the checkGameOver() function to see if the place the user is
        trying to move to is a the exit.
        -In the new x and y position in the maze, place an "X", which
        shows that the player has moved.

        Returns 1 if the move is normal, 2 if the game is over.
    */
}


void drawMaze(Array2D *maze) {
    /*
        Prints out the maze to the screen.
    */

    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c", maze->data[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}


int checkGameOver(Array2D *maze, int newXPosition, int newYPosition) {
    /*
        Checks if the (newXpositiona, newYPosition) is the exit square.
        Returns 2 if it is, 0 otherwise.
        If it is the exit square, the game is over.
            - "Congratulations! You have completed the maze!"
    */
    if (maze->data[newYPosition][newXPosition] == 'E') {
        printf("Congratulations! You have completed the maze!\n");
        return 4;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    /*
        Checks argv to see if there are any command line arguments.

        If there aren't any arguments, the program will raise an error message and exit.
            - "Error: Filename not given".
        If there are arguments, the first argument is the filename.

        Initialises the player struct.
        Initialises the maze - stored as a two dimensional array of characters.

        Calls the readFile() function to read the file into the maze array.#

        Calls the validateMaze() function to validate the maze.
        If 0 is returned, then the program stops.
        If 1 is returned, then the maze is valid.

        Calls the drawMaze() function to print the maze to the screen.

        *
        Prompts the user to input a move.
        Calls the checkInput() function to check if the input is valid.
        If 0 is returned, then the user is prompted to enter another input.
        If 1 is returned, the input is valid.

        If input is M or m, then the drawMaze() function is called.
        Else, calls the checkValidMove() function to check if the move is valid.
        If 0 is returned, then the user is prompted to enter another input.
        If 1 is returned, the move is valid.
        If 2 is returned, the game is over.
        
        Repeat from * until the game is over.
    */

    if (argv[1] == NULL) {
        printf("Error: Filename not given\n");
        return 2;
    }

    if (readFile(argv[1]) == 2) {
        return 2;
    }

    int mazeSize = validateMazeSize(argv[1]);
    if (mazeSize == 3) {
        return 3;
    }
    
    Player player;
    Player *playerPtr = &player;

    Array2D maze;
    Array2D *mazePtr = &maze;
    maze.rows = mazeSize / 1000;
    maze.cols = mazeSize % 1000;
    maze.data = malloc(maze.rows*sizeof(char*));

    for (int i = 0; i < maze.rows; i++) {
        maze.data[i] = malloc(maze.cols*sizeof(char));
    }
    
    if (validateMazeContents(argv[1], mazePtr, playerPtr) == 3) {
        return 3;
    }

    drawMaze(mazePtr);

    char input[1000]; 
    while (input[0] != 'q') {

        printf("\nEnter WASD to navigate the maze, or M to display the map, or Q to quit the game: ");
        fgets(input, sizeof input, stdin);

        if (checkInput(input) == 0) {
            if (checkValidMove(input[0], mazePtr, playerPtr) == 4) {
                return 0;
            }
        }
    }
    
    printf("Shutting down program\n");
    return 0;
}