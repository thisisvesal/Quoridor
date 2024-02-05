#include "wall.h"
#include "charms.h"
#include <stdlib.h>

void gameRun()
{
    struct Player *someone = determinePlayer();
    aiWallTry = 0;

    charmSw = 1;

    printPage(someone);

    // moveChar shows if the player wants to move or place a wall
    char moveChar[100] = "\0";

    // getting moveChar:
    while ((moveChar[0] != 'm' && moveChar[0] != 'w' && moveChar[0] != 's' && moveChar[0] != 'l') || moveChar[1] != 0)
    {
        // int aiCharm = randomize(0, 1);
        setTextColor(0, 15);

        if (someone->isAi)
        {
            int dontGetCharm = randomize(0, 2);
            // basically, it gets a charm if dontGetcharm is 0
            // so the probabillity of getting a charm is 1/3 for the computer
            if (!dontGetCharm && someone->charmNo) moveChar[0] = 'l';
            else if (aiWallPlace().x == -1)
                moveChar[0] = 'm';
            else if (putWall())
            {
                someone->wallCount--;

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
        charmSw = 0;
        setTextColor(15, color);
        // save

        FILE *saveBoard, *saveFeatures, *savePlayers;

        // saveColor = fopen("saveColor.bin", "wb");
        // saveGameMode = fopen("saveGameMode.bin", "wb");
        saveBoard = fopen("saveBoard.bin", "wb");
        saveFeatures = fopen("saveFeatures.bin", "wb");
        savePlayers = fopen("savePlayers.bin", "wb");
        if (!saveBoard || !saveFeatures || !savePlayers)
        {
            printf("Can't save the game !\n");
        }
        else
        {
            for (int i = 0; i < 2 * row + 1; i++)
            {
                fwrite(Board[i], sizeof(char), 2 * column + 1, saveBoard);
            }
            fclose(saveBoard);

            struct features features;

            features.row = row;
            features.column = column;
            features.color = color;
            features.gameMode = gameMode;
            features.aiSw = aiSw;
            features.round = turn;

            fwrite(&features, sizeof(features), 1, saveFeatures);
            fclose(saveFeatures);

            if (gameMode == 1)
            {
                struct Player players[2] = {player1, player2};

                fwrite(players, sizeof(struct Player), 2, savePlayers);
            }
            else if (gameMode == 2)
            {
                struct Player players[4] = {player1, player2, player3, player4};

                fwrite(players, sizeof(struct Player), 4, savePlayers);
            }

            fclose(savePlayers);

            printf("\nGame saved");

            setTextColor(color, 15);
            printf("\n\n");
            
            sleep(2000);
        }
    }
}