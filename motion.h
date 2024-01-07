#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "boardPrinter.h"
#include "design.h"
#include "boardMaker.h"
#include "dfs.h"

#ifndef motion
#define motion

// players elements
struct Player
{
    char name[30];
    char nameInitial;
    struct place
    {
        int x, y;
    } location;
    int wallCount;
} player1, player2, player3, player4;

// move in the cursor
void gotoxy(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = y;
    cursorCoord.Y = x;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

// recognizing players pawns' move
int motionDetect()
{
    char motionCode;
    motionCode = getch();
    if (motionCode == 0)
    {
        motionCode = getch();
        return motionCode;
        // right: 77
        // left: 75
        // up: 72
        // down: 80
    }
}

// making a delay
void sleep(int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}

// performing pawn's move
void move(struct Player *someone)
{
    struct Player someoneCopy;
    someoneCopy = *someone;
    int contSw = 1;
    int where = motionDetect();
    if (where == 77) // right
    {
        if (Board[someoneCopy.location.x][someoneCopy.location.y + 1] != -70 // if not ║
            && someoneCopy.location.y != 2 * column - 1)                     // if not on the edges
        {
            if (Board[someoneCopy.location.x][someoneCopy.location.y + 2] == ' ') // in order not to hit the other player
            {
                Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                someoneCopy.location.y += 2;
                Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                contSw = 0;
            }
            else // jump over the other player
            {
                if (Board[someoneCopy.location.x][someoneCopy.location.y + 4] == ' ')
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y += 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
            }
        }
    }
    else if (where == 75) // left
    {
        if (Board[someoneCopy.location.x][someoneCopy.location.y - 1] != -70 // if not ║
            && someoneCopy.location.y != 1)                                  // if not on the edges
        {
            if (Board[someoneCopy.location.x][someoneCopy.location.y - 2] == ' ') // in order not to hit the other player
            {
                Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                someoneCopy.location.y -= 2;
                Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                contSw = 0;
            }
            else // jump over the other player
            {
                if (Board[someoneCopy.location.x][someoneCopy.location.y - 4] == ' ')
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y -= 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
            }
        }
    }
    else if (where == 72) // up
    {
        if (Board[someoneCopy.location.x - 1][someoneCopy.location.y] != -51 // if not ═
            && someoneCopy.location.x != 1)                                  // if not on the edges
        {
            if (Board[someoneCopy.location.x - 2][someoneCopy.location.y] == ' ') // in order not to hit the other player
            {
                Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                someoneCopy.location.x -= 2;
                Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                contSw = 0;
            }
            else // jump over the other player
            {
                if (Board[someoneCopy.location.x - 4][someoneCopy.location.y] == ' ')
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x -= 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
            }
        }
    }
    else if (where == 80) // down
    {
        if (Board[someoneCopy.location.x + 1][someoneCopy.location.y] != -51 // if not ═
            && someoneCopy.location.x != 2 * row - 1)                        // if not on the edges
        {
            if (Board[someoneCopy.location.x + 2][someoneCopy.location.y] == ' ') // in order not to hit the other player
            {
                Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                someoneCopy.location.x += 2;
                Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                contSw = 0;
            }
            else // jump over the other player
            {
                if (Board[someoneCopy.location.x + 4][someoneCopy.location.y] == ' ')
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x += 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
            }
        }
    }

    *someone = someoneCopy;
    if (contSw)
    {
        printf("\a");
        move(someone);
    }
}

#endif