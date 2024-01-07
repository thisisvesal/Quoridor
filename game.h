#include "boardMaker.h"
#include "boardPrinter.h"
#include "motion.h"
#include "wall.h"
#include "dfs.h"
#include "design.h"

void gameRun(int *round, int color)
{
    struct Player *someone;
    if (gameMode == 3)
    {
        if (*round == 0)
            someone = &player1;
        else if (*round == 1)
            someone = &player3;
        else if (*round == 2)
            someone = &player2;
        else if (*round == 3)
            someone = &player4;
    }
    else
    {
        if (*round == 0)
            someone = &player1;
        else if (*round == 1)
            someone = &player2;
    }
    printf("%s's turn\n", someone->name);

    char moveChar[100] = "\0";
    // moveChar shows if the player wants to move or place a wall
    // getting moveChar:
    while ((moveChar[0] != 'm' && moveChar[0] != 'w') || moveChar[1] != 0)
    {
        setTextColor(0, 15);
        printf("\nWall or move?\n(enter w for wall, and m for move)\n");
        gets(moveChar);
        if (moveChar[0] == 'm' && moveChar[1] == 0)
            ;
        if (moveChar[0] == 'w' && moveChar[1] == 0)
            ;
        if (moveChar[0] == 'W' && moveChar[1] == 0)
            moveChar[0] = 'w';
        else if (moveChar[0] == 'M' && moveChar[1] == 0)
            moveChar[0] = 'm';
    }

    // placing a wall:
    if (moveChar[0] == 'w' && someone -> wallCount > 0) // runs only if the player still has walls left
    {
        putWall();
        someone -> wallCount --;
        clearScreen();
        setTextColor(color, 15);

        printBoard(Board, row, column);

        printf("%s's remaining walls: ", player1.name);
        printRemainingWalls(player1.wallCount);

        printf("%s's remaining walls: ", player2.name);
        printRemainingWalls(player2.wallCount);
        if (gameMode == 3)
        {
            printf("%s's remaining walls: ", player3.name);
            printRemainingWalls(player3.wallCount);

            printf("%s's remaining walls: ", player4.name);
            printRemainingWalls(player4.wallCount);
        }

        // changing the *round:
        *round += 1;
        if (gameMode == 3)
        {
            *round %= 4;
        }
        else
        {
            *round %= 2;
        }
    }
    else if (moveChar[0] == 'w' && someone -> wallCount == 0) // if the player is out of walls
    {
        printf("You're out of walls!\n");
        sleep(750);
    }
    else if (moveChar[0] == 'm') // move for player 1
    {
        gotoxy(someone -> location.x, someone -> location.y);
        move(someone);
        clearScreen();
        setTextColor(color, 15);

        printBoard(Board, row, column);

        printf("%s's remaining walls: ", player1.name);
        printRemainingWalls(player1.wallCount);

        printf("%s's remaining walls: ", player2.name);
        printRemainingWalls(player2.wallCount);

        if (gameMode == 3)
        {
            printf("%s's remaining walls: ", player3.name);
            printRemainingWalls(player3.wallCount);

            printf("%s's remaining walls: ", player4.name);
            printRemainingWalls(player4.wallCount);
        }

        // changing the *round:
        *round += 1;
        if (gameMode == 3)
        {
            *round %= 4;
        }
        else
        {
            *round %= 2;
        }
    }
}