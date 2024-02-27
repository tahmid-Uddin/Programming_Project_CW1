#ifndef FUNC
#define FUNC

typedef struct Player {
    int xPosition;
    int yPosition; 
} Player;

void readFile(char *filename, char *maze);
int validateMaze(char *maze, Player *player);
void drawMaze(char *maze);
int checkInput(char *input);
int checkValidMove(char input, char *maze, Player *player);
void movePlayer(char input, Player *player, char *maze, int newXPosition, int newYPosition);

#endif