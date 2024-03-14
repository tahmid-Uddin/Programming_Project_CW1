#ifndef FUNC
#define FUNC

struct player {
    int xPosition;
    int yPosition; 
};

typedef struct player Player;

int readFile(char *filename);
int validateMazeSize(char *filename);
int validateMazeContents(char *filename, char *maze, Player *player);
void drawMaze(char *maze);
int checkInput(char *input);
int checkValidMove(char input, char *maze, Player *player);
void movePlayer(char input, Player *player, char *maze, int newXPosition, int newYPosition);

#endif