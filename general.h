#ifndef general
#define general

struct features
{
    int row, column;
    int color;
    int gameMode;
    int aiSw;
    int round;
};

struct Player
{
    char name[30];
    char nameInitial;
    struct place
    {
        int x, y;
    } location;
    int wallCount;
    int blockedFor;
} player1, player2, player3, player4;

int row, column;
char Board[101][101];
int sw[101][101];
int gameMode = 0;
int color = 0;
int aiSw = 0;
// integer round determines whose turn it is
int round = 0;

struct Player* determinePlayer()
{
    if (gameMode == 2)
    {
        if (round == 0)
            return &player1;
        else if (round == 1)
            return &player3;
        else if (round == 2)
            return &player2;
        else if (round == 3)
            return &player4;
    }
    else
    {
        if (round == 0)
            return &player1;
        else if (round == 1)
            return &player2;
    }
}



#endif