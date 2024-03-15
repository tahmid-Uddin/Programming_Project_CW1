#ifndef FUNC
#define FUNC

const int MIN_HEIGHT = 5;
const int MIN_WIDTH = 5;
const int MAX_HEIGHT = 100;
const int MAX_WIDTH = 100;

struct player {
    int xPosition;
    int yPosition; 
};

typedef struct player Player;

struct array2D {
    char** data;
    int rows;
    int cols;
    int exitXPosition;
    int exitYPosition;
};

typedef struct array2D Array2D;

int readFile(char *filename);
int validateMazeSize(char *filename);
int validateMazeContents(char *filename, Array2D *maze, Player *player);
void drawMaze(Array2D *maze);
int checkInput(char input[]);
int checkValidMove(char input, Array2D *maze, Player *player);
void movePlayer(char input, Player *player, char *maze, int newXPosition, int newYPosition);
int checkGameOver(Array2D *maze, int newXPosition, int newYPosition);


#endif