#include "boardMaker.h"
#include "boardPrinter.h"
#include "motion.h"
#include "wall.h"
#include "design.h"
#include <stdlib.h>
#include "random.h"

struct features
{
    int row, column;
    int color;
    int gameMode;
    int aiSw;
    int round;
};

void gameRun()
{
    struct Player *someone;
    if (gameMode == 2)
    {
        if (round == 0)
            someone = &player1;
        else if (round == 1)
            someone = &player3;
        else if (round == 2)
            someone = &player2;
        else if (round == 3)
            someone = &player4;
    }
    else
    {
        if (round == 0)
            someone = &player1;
        else if (round == 1)
            someone = &player2;
    }
    printf("%s's turn\n", someone->name);
    setTextColor(15, color);
    printf("\n(Press S to save your game)\n");

    char moveChar[100] = "\0";
    // moveChar shows if the player wants to move or place a wall
    // getting moveChar:
    while ((moveChar[0] != 'm' && moveChar[0] != 'w' && moveChar[0] != 's') || moveChar[1] != 0)
    {
        setTextColor(0, 15);
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

    // placing a wall:
    if (moveChar[0] == 'w' && someone->wallCount > 0) // runs only if the player still has walls left
    {
        putWall();
        someone->wallCount--;
        clearScreen();
        setTextColor(color, 15);

        printBoard(Board, row, column);

        printf("%s's remaining walls: ", player1.name);
        printRemainingWalls(player1.wallCount);

        printf("%s's remaining walls: ", player2.name);
        printRemainingWalls(player2.wallCount);
        if (gameMode == 2)
        {
            printf("%s's remaining walls: ", player3.name);
            printRemainingWalls(player3.wallCount);

            printf("%s's remaining walls: ", player4.name);
            printRemainingWalls(player4.wallCount);
        }

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
        clearScreen();
        setTextColor(color, 15);

        printBoard(Board, row, column);

        printf("%s's remaining walls: ", player1.name);
        printRemainingWalls(player1.wallCount);

        printf("%s's remaining walls: ", player2.name);
        printRemainingWalls(player2.wallCount);

        if (gameMode == 2)
        {
            printf("%s's remaining walls: ", player3.name);
            printRemainingWalls(player3.wallCount);

            printf("%s's remaining walls: ", player4.name);
            printRemainingWalls(player4.wallCount);
        }

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

            struct features features, loadFeatures;

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
        }
    }
}