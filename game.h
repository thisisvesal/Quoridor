#include "wall.h"
#include "charms.h"
#include "getInfo.h"

#ifndef game
#define game

void gameRun()
{
    struct Player *someone = determinePlayer();
    aiWallTry = 0;

    printPage(someone);

    // moveChar shows if the player wants to move or place a wall
    char moveChar[100] = "\0";

    // getting moveChar:
    while ((moveChar[0] != 'm' && moveChar[0] != 'w' && moveChar[0] != 's' && moveChar[0] != 'l') || moveChar[1] != 0)
    {
        setTextColor(0, 15);

        if (someone->isAi)
        {
            int dontGetCharm = randomize(0, 2);
            // basically, we get a charm if dontGetcharm is 0
            // so the probabillity of getting a charm is 1/3 for the computer
            if (!dontGetCharm && someone->charmNo)
                moveChar[0] = 'l';
            else if (aiWallPlace().x == -1)
                moveChar[0] = 'm';
            else if (putWall()) // putwall will return 0 if putting a wall has failed for some reason
            {
                someone->wallCount--;

                // resetting charmNo of the current player for next rounds
                someone->charmNo = 1;

                printPage(someone);

                // changing the round:
                turn += 1;
                if (gameMode == 2)
                {
                    turn %= 4;
                }
                else if (gameMode == 1)
                {
                    turn %= 2;
                }
                return;
            }
            else // here, we declare that a move should be made because putting a wall has not been possible
            {
                moveChar[0] = 'm';
            }
        }
        else
        {
            printf("\nLucky box, Wall or move?\n(l for lucky box, w for wall, m for move)\n");
            gets(moveChar);
            if (moveChar[0] == 'm' && moveChar[1] == 0)
                ;
            if (moveChar[0] == 'w' && moveChar[1] == 0)
                ;
            if (moveChar[0] == 'W' && moveChar[1] == 0)
                moveChar[0] = 'w';
            else if (moveChar[0] == 'M' && moveChar[1] == 0)
                moveChar[0] = 'm';
            else if (moveChar[0] == 'L' && moveChar[1] == 0)
                moveChar[0] = 'l';
            else if (moveChar[0] == 'S' && moveChar[1] == 0)
                moveChar[0] = 's';
        }
    }

    // placing a wall:
    if (moveChar[0] == 'w' && someone->wallCount > 0) // runs only if the player still has walls left
    {
        putWall();
        someone->wallCount--;

        // resetting charmNo of the current player for next rounds
        someone->charmNo = 1;

        printPage(someone);

        // changing the round:
        turn += 1;
        if (gameMode == 2)
        {
            turn %= 4;
        }
        else if (gameMode == 1)
        {
            turn %= 2;
        }
    }
    else if (moveChar[0] == 'w' && someone->wallCount == 0) // if the player is out of walls
    {
        printf("You're out of walls!\n");
        sleep(750);
    }
    else if (moveChar[0] == 'm') // move for someone
    {
        gotoxy(someone->location.x, someone->location.y);
        move(someone);

        // resetting charmNo of the current player for next rounds
        someone->charmNo = 1;

        printPage(someone);

        // changing the round:
        turn += 1;
        if (gameMode == 2)
        {
            turn %= 4;
        }
        else if (gameMode == 1)
        {
            turn %= 2;
        }
    }
    else if (moveChar[0] == 'l')
    {
        if (someone->charmNo > 0)
        {
            getCharm();
            someone->charmNo = 0;
        }
        else
        {
            printf("You've used your charm for this round :]\n");
            sleep(1000);
        }
    }
    else if (moveChar[0] == 's')
    {
        saveGame();
    }
}

#endif