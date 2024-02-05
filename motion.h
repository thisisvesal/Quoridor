#include <conio.h>
#include <time.h>
#include "design.h"
#include "dfs.h"
#include "random.h"
#include "decision.h"

#ifndef motion
#define motion

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

    if (determinePlayer()->isAi)
    {
        return moveDecision();
    }
    else
    {
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
                if (Board[someoneCopy.location.x][someoneCopy.location.y + 4] == ' '
                    && Board[someoneCopy.location.x][someoneCopy.location.y + 3] == -77)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y += 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x][someoneCopy.location.y + 6] == ' '
                         && Board[someoneCopy.location.x][someoneCopy.location.y + 3] == -77
                         && Board[someoneCopy.location.x][someoneCopy.location.y + 5] == -77)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y += 6;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x][someoneCopy.location.y + 8] == ' '
                         && Board[someoneCopy.location.x][someoneCopy.location.y + 3] == -77
                         && Board[someoneCopy.location.x][someoneCopy.location.y + 5] == -77
                         && Board[someoneCopy.location.x][someoneCopy.location.y + 7] == -77)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y += 8;
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
                if (Board[someoneCopy.location.x][someoneCopy.location.y - 4] == ' '
                    && Board[someoneCopy.location.x][someoneCopy.location.y - 3] == -77)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y -= 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x][someoneCopy.location.y - 6] == ' '
                         && Board[someoneCopy.location.x][someoneCopy.location.y - 3] == -77
                         && Board[someoneCopy.location.x][someoneCopy.location.y - 5] == -77)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';

                    someoneCopy.location.y -= 6;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x][someoneCopy.location.y - 8] == ' '
                         && Board[someoneCopy.location.x][someoneCopy.location.y - 3] == -77
                         && Board[someoneCopy.location.x][someoneCopy.location.y - 5] == -77
                         && Board[someoneCopy.location.x][someoneCopy.location.y - 7] == -77)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.y -= 8;
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
                if (Board[someoneCopy.location.x - 4][someoneCopy.location.y] == ' '
                    && Board[someoneCopy.location.x - 3][someoneCopy.location.y] == -60)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x -= 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x - 6][someoneCopy.location.y] == ' '
                         && Board[someoneCopy.location.x - 3][someoneCopy.location.y] == -60
                         && Board[someoneCopy.location.x - 5][someoneCopy.location.y] == -60)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x -= 6;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x - 8][someoneCopy.location.y] == ' '
                         && Board[someoneCopy.location.x - 3][someoneCopy.location.y] == -60
                         && Board[someoneCopy.location.x - 5][someoneCopy.location.y] == -60
                         && Board[someoneCopy.location.x - 7][someoneCopy.location.y] == -60)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x -= 8;
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
                if (Board[someoneCopy.location.x + 4][someoneCopy.location.y] == ' '

                    && Board[someoneCopy.location.x + 3][someoneCopy.location.y] == -60)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x += 4;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x + 6][someoneCopy.location.y] == ' '
                         && Board[someoneCopy.location.x + 3][someoneCopy.location.y] == -60
                         && Board[someoneCopy.location.x + 5][someoneCopy.location.y] == -60)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x += 6;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
                else if (Board[someoneCopy.location.x + 8][someoneCopy.location.y] == ' '
                         && Board[someoneCopy.location.x + 3][someoneCopy.location.y] == -60
                         && Board[someoneCopy.location.x + 5][someoneCopy.location.y] == -60
                         && Board[someoneCopy.location.x + 7][someoneCopy.location.y] == -60)
                {
                    Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
                    someoneCopy.location.x += 8;
                    Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
                    contSw = 0;
                }
            }
        }
    }

    *someone = someoneCopy;
    if (contSw)
    {
        move(someone);
    }
}


#endif