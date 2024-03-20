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
    int startXPosition;
    int startYPosition;
};
typedef struct array2D Array2D;

struct node {
    char data;
    int visited;
};
typedef struct node Node;

struct mazeStruct {
    Node** data;
    int rows;
    int cols;
    int visitedNodes;
};
typedef struct mazeStruct Maze;

int readFile(char *filename);
int validateMazeSize(char *filename);
int validateMazeContents(char *filename, Array2D *maze, Player *player);
void drawMaze(Array2D *maze, Player *player);
int checkInput(char input[]);
int checkValidMove(char input, Array2D *maze, Player *player);
void movePlayer(char input, Player *player, char *maze, int newXPosition, int newYPosition);
int checkGameOver(Array2D *maze, int newXPosition, int newYPosition);

void DrawMaze(Maze *maze);
double DistanceToExit(int x, int y, int exitX, int exitY);
void EmptyMaze(Maze *maze, int startX, int startY, int exitX, int exitY);
int checkValidCoordinates(int x, int y, int j, int array[], int largestSide, int startX, int startY, int exitX, int exitY);
void PathFinder(Maze *maze, int currentPositionX, int currentPositionY, int exitPositionX, int exitPositionY);
void ResetVisited(Maze *maze);
void PopulateMaze(Maze *maze, int density);
#endif