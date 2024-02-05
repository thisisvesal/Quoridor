#include <stdio.h>
#include <stdlib.h>

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

typedef struct location
{
    int x, y;
} location;

struct Player
{
    char name[30];
    char nameInitial;
    location location;
    int wallCount;
    int blockedFor;
    int charmNo;
    int isAi;
} player1, player2, player3, player4;

int row = 0;
int column = 0;
char Board[101][101];
int wallCount = 0;
int sw[101][101];
int gameMode = 0;
int color = 0;
int aiSw = 0;
// integer turn determines whose turn it is
int turn = 0;
int newOrOld = 0;

int getValidInt(int start, int end)
{
    int input = 0;
    while (!(start <= input && input <= end))
    {
        char inputCopy[100];
        gets(inputCopy);

        for (int i = 0; inputCopy[i] && '0' <= inputCopy[i] && inputCopy[i] <= '9'; i++)
        {
            input += (inputCopy[i] - 48);
            input *= 10;
        }
        input /= 10;
        if (!(start <= input && input <= end))
            printf("Please enter a valid number\n");
    }

    return input;
}

struct Player *determinePlayer()
{
    if (gameMode == 1)
    {
        if (turn == 0)
            return &player1;
        else if (turn == 1)
            return &player2;
    }
    else if (gameMode == 2)
    {
        if (turn == 0)
            return &player1;
        else if (turn == 1)
            return &player3;
        else if (turn == 2)
            return &player2;
        else if (turn == 3)
            return &player4;
    }
}

#endif