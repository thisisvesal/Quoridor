#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "boardPrinter.h"
#include "design.h"
#include "boardMaker.h"

#ifndef motion
#define motion

struct Player
{
    char nameInitial;
    int location[2];
    int wallCount;
} player1, player2;

void gotoxy(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = y;
    cursorCoord.Y = x;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

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

void sleep(int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}

void move(struct Player *someone)
{
    struct Player someoneCopy;
    someoneCopy = *someone;
    int sw = 1;
    int where = motionDetect();
    if (where == 77) // right
    {
        if (Board[someoneCopy.location[0]][someoneCopy.location[1] + 1] != 186 && someoneCopy.location[1] != 2 * column - 1)
        {
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = ' ';
            someoneCopy.location[1] += 2;
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = someoneCopy.nameInitial;
            sw = 0;
        }
    }
    else if (where == 75) // left
    {
        if (Board[someoneCopy.location[0]][someoneCopy.location[1] - 1] != 186 && someoneCopy.location[1] != 1)
        {
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = ' ';
            someoneCopy.location[1] -= 2;
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = someoneCopy.nameInitial;
            sw = 0;
        }
    }
    else if (where == 72) // up
    {
        if (Board[someoneCopy.location[0] - 1][someoneCopy.location[1]] != 205 && someoneCopy.location[0] != 1)
        {
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = ' ';
            someoneCopy.location[0] += 2;
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = someoneCopy.nameInitial;
            sw = 0;
            printf("up");
        }
    }
    else if (where == 80) // down
    {
        if (Board[someoneCopy.location[0] + 1][someoneCopy.location[1]] != 205 && someoneCopy.location[0] != 2 * row - 1)
        {
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = ' ';
            someoneCopy.location[0] -= 2;
            Board[someoneCopy.location[0]][someoneCopy.location[1]] = someoneCopy.nameInitial;
            sw = 0;
            printf("down");
        }
    }

    *someone = someoneCopy;
    if (sw)
        move(someone);
}

void putWall()
{
    int x = row, y = column;
    gotoxy(x, y);
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

    // ═ 205
    if (x % 2 == 0 && y % 2 != 0)
        Board[x][y] = 205;
    // ║ 186
    else if (y % 2 == 0 && x % 2 != 0)
        Board[x][y] = 186;
    else putWall();
}

#endif