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
    char name[30];
    char nameInitial;
    struct place
    {
        int x, y;
    } location;
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
        if (Board[someoneCopy.location.x][someoneCopy.location.y + 1] != -70  // if not ║
            && Board[someoneCopy.location.x][someoneCopy.location.y + 2] == ' ' // in order not to hit the other player
            && someoneCopy.location.y != 2*column - 1) // if not on the edges
        {
            Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
            someoneCopy.location.y += 2;
            Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
            sw = 0;
        }
    }
    else if (where == 75) // left
    {
        // printf("%d\n", Board[someoneCopy.location.x][someoneCopy.location.y - 1]);
        // sleep(1000);
        if (Board[someoneCopy.location.x][someoneCopy.location.y - 1] != -70 // if not ║
            && Board[someoneCopy.location.x][someoneCopy.location.y - 2] == ' ' // in order not to hit the other player
            && someoneCopy.location.y != 1) // if not on the edges
        {
            Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
            someoneCopy.location.y -= 2;
            Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
            sw = 0;
        }
    }
    else if (where == 72) // up
    {
        if (Board[someoneCopy.location.x - 1][someoneCopy.location.y] != -51 // if not ═
            && Board[someoneCopy.location.x - 2][someoneCopy.location.y] == ' ' // in order not to hit the other player
            && someoneCopy.location.x != 1) // if not on the edges
        {
            Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
            someoneCopy.location.x -= 2;
            Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
            sw = 0;
        }
    }
    else if (where == 80) // down
    {
        if (Board[someoneCopy.location.x + 1][someoneCopy.location.y] != -51 // if not ═
            && Board[someoneCopy.location.x + 2][someoneCopy.location.y] == ' ' // in order not to hit the other player
            && someoneCopy.location.x != 2*row - 1) // if not on the edges
        {
            Board[someoneCopy.location.x][someoneCopy.location.y] = ' ';
            someoneCopy.location.x += 2;
            Board[someoneCopy.location.x][someoneCopy.location.y] = someoneCopy.nameInitial;
            sw = 0;
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
    {
        if (y == 2*column - 1 && Board[x][y-1]!=-51 && Board[x][y-2]!=-70)
        {
            Board[x][y] = Board[x][y - 1]= Board[x][y-2] = 205;
        }
        else if(Board[x][y+1]!=-51 && Board[x][y+2]!=-70){
            Board[x][y]=Board[x][y+1]=Board[x][y+2] = 205;
        }else putWall();
    }
        // ║ 186
    else if (y % 2 == 0 && x % 2 != 0)
    {
        if (x == 2*row - 1 && Board[x-2][y]!=-51 && Board[x-1][y]!=-70)
        {
            Board[x][y]=Board[x-1][y]=Board[x-2][y] = 186;
        }

        else if(Board[x+2][y]!=-51 && Board[x+1][y]!=-70){
            Board[x][y]=Board[x+1][y]=Board[x+2][y] = 186;
        }else putWall();
    }
    else putWall();
}

#endif