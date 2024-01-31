#include "wall.h"
#include "charms.h"
#include <stdlib.h>

void gameRun()
{
    struct Player *someone = determinePlayer();

    charmSw = 1;

    printPage(someone);

    // moveChar shows if the player wants to move or place a wall
    char moveChar[100] = "\0";
    
    // getting moveChar:
    while ((moveChar[0] != 'm' && moveChar[0] != 'w' && moveChar[0] != 's') || moveChar[1] != 0)
    {
        setTextColor(0, 15);
        if (gameMode == 1)
        {
            if (aiSw == 1 && round == 1)
            {
                int moveCode = randomize(0, 1);
                if (moveCode == 0)
                    moveChar[0] = 'm';
                else if (moveCode == 1)
                    moveChar[0] = 'w';
            }
            else
            {
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
                else if (moveChar[0] == 'S' && moveChar[1] == 0)
                    moveChar[0] = 's';
            }
        }
        if (gameMode == 2)
        {
            if (aiSw == 2 && round == 3)
            {
                int moveCode = randomize(0, 1);
                if (moveCode == 0)
                    moveChar[0] = 'm';
                else if (moveCode == 1)
                    moveChar[0] = 'w';
            }
            else if (aiSw == 3 && (round == 3 || round == 1))
            {
                int moveCode = randomize(0, 1);
                if (moveCode == 0)
                    moveChar[0] = 'm';
                else if (moveCode == 1)
                    moveChar[0] = 'w';
            }
            else if (aiSw == 4 && round != 0)
            {
                int moveCode = randomize(0, 1);
                if (moveCode == 0)
                    moveChar[0] = 'm';
                else if (moveCode == 1)
                    moveChar[0] = 'w';
            }
            else
            {
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
                else if (moveChar[0] == 'S' && moveChar[1] == 0)
                    moveChar[0] = 's';
            }
        }
    }

    // placing a wall:
    if (moveChar[0] == 'w' && someone->wallCount > 0) // runs only if the player still has walls left
    {
        putWall();
        someone->wallCount--;

        printPage(someone);

        // changing the round:
        round += 1;
        if (gameMode == 2)
        {
            round %= 4;
        }
        else if (gameMode == 1)
        {
            round %= 2;
        }
    }
    else if (moveChar[0] == 'w' && someone->wallCount == 0) // if the player is out of walls
    {
        if (aiSw == 1 && round == 1)
        {
            moveChar[0] = 'm';
        }
        else
        {
            printf("You're out of walls!\n");
            sleep(750);
        }
    }
    else if (moveChar[0] == 'm') // move for someone
    {
        gotoxy(someone->location.x, someone->location.y);
        move(someone);
        
        printPage(someone);

        // changing the round:
        round += 1;
        if (gameMode == 2)
        {
            round %= 4;
        }
        else if (gameMode == 1)
        {
            round %= 2;
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
            features.round = round;

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

            printf("\nGame saved\n\n");

            setTextColor(color, 15);

            sleep(2000);
        }
    }
}