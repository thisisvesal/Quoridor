#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "boardPrinter.h"
#include "design.h"
#include "boardMaker.h"

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
} player1, player2;

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

// checking if the route exist for player1
int dfsDown(int sw[101][101], int row, int column, int x, int y)
{
    sw[x][y] = 2;
    if (x > 0 && sw[x - 1][y] == 1)
    {
        dfsDown(sw, row, column, x - 1, y);
    }

    if (x + 1 < 2 * row + 1 && sw[x + 1][y] == 1)
    {
        dfsDown(sw, row, column, x + 1, y);
    }

    if (y > 0 && sw[x][y - 1] == 1)
    {
        dfsDown(sw, row, column, x, y - 1);
    }

    if (y + 1 < 2 * column + 1 && sw[x][y + 1] == 1)
    {
        dfsDown(sw, row, column, x, y + 1);
    }

    for (int i = 0; i < 2 * column + 1; i++)
    {
        if (sw[2 * row - 1][i] == 2)
        {
            return 1;
        }
    }

    return 0;
}

// checking if the route exist for player2
int dfsUp(int sw[101][101], int row, int column, int x, int y)
{
    sw[x][y] = 2;
    if (x > 0 && sw[x - 1][y] == 1)
    {
        dfsUp(sw, row, column, x - 1, y);
    }

    if (x + 1 < 2 * row + 1 && sw[x + 1][y] == 1)
    {
        dfsUp(sw, row, column, x + 1, y);
    }

    if (y > 0 && sw[x][y - 1] == 1)
    {
        dfsUp(sw, row, column, x, y - 1);
    }

    if (y + 1 < 2 * column + 1 && sw[x][y + 1] == 1)
    {
        dfsUp(sw, row, column, x, y + 1);
    }

    for (int i = 0; i < 2 * column + 1; i++)
    {
        if (sw[1][i] == 2)
        {
            return 1;
        }
    }

    return 0;
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
        move(someone);
}

// putting fences
void putWall()
{
    int x = row, y = column;
    int contSw = 1;
    gotoxy(x, y);
    // this section allows movement of the cursor until enter is pressed
    // then when enter is hit, a wall will be placed there
    while (1)
    {
        char where = getch();
        if (where == 13)
            break;
        else if (where == 77) // right
        {
            y++;
            gotoxy(x, y);
        }
        else if (where == 75) // left
        {
            y--;
            gotoxy(x, y);
        }
        else if (where == 72) // up
        {
            x--;
            gotoxy(x, y);
        }
        else if (where == 80) // down
        {
            x++;
            gotoxy(x, y);
        }
    }

    // checking if the chosen place is accessible then place it
    // horizontal fences
    // ═ 205
    if (x % 2 == 0 && y % 2 != 0)
    {
        if (y == 2 * column - 1 && Board[x][y] == -60 && Board[x][y - 1] == -59 && Board[x][y - 2] == -60)
        {
            makeSw();
            sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
            if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
            {
                makeSw();
                sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                {
                    Board[x][y] = Board[x][y - 1] = Board[x][y - 2] = 205;
                    contSw = 0;
                }
            }
        }
        else if (Board[x][y] == -60 && Board[x][y + 1] == -59 && Board[x][y + 2] == -60)
        {
            makeSw();
            sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
            if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
            {
                makeSw();
                sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                {
                    Board[x][y] = Board[x][y + 1] = Board[x][y + 2] = 205;
                    contSw = 0;
                }
            }
        }
    }
    // vertical fences
    //  ║ 186
    else if (y % 2 == 0 && x % 2 != 0)
    {
        if (x == 2 * row - 1 && Board[x][y] == -77 && Board[x - 2][y] == -77 && Board[x - 1][y] == -59)
        {
            makeSw();
            sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
            if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
            {
                makeSw();
                sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                {
                    Board[x][y] = Board[x - 1][y] = Board[x - 2][y] = 186;
                    contSw = 0;
                }
            }
        }

        else if (Board[x][y] == -77 && Board[x + 2][y] == -77 && Board[x + 1][y] == -59)
        {
            makeSw();
            sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
            if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
            {
                makeSw();
                sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                {
                    Board[x][y] = Board[x + 1][y] = Board[x + 2][y] = 186;
                    contSw = 0;
                }
            }
        }
    }
    if (contSw)
    {
        putWall();
    }
}

#endif