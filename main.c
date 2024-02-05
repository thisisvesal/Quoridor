#include "game.h"
#include "getInfo.h"

int main()
{
    setTextColor(0, 15);
    clearScreen();

    // write welcome message
    printf("Welcome to Quoridor game!");
    setTextColor(6, 15);
    printf(" %c\n", 2);
    sleep(2000);
    clearScreen();

    setTextColor(0, 15);
    printf("1) Continue my old game\n");
    printf("2) Start a new game\n");

    // Move this section to validChecks.h as a functionS
    newOrOld = 0;
    while (newOrOld != 1 && newOrOld != 2)
    {
        char newOrOldCopy[30];
        scanf("%s", newOrOldCopy);

        int i;
        for (i = 0; newOrOldCopy[i] && '0' <= newOrOldCopy[i] && newOrOldCopy[i] <= '9'; i++)
        {
            newOrOld += (newOrOldCopy[i] - 48);
            newOrOld *= 10;
        }
        newOrOld /= 10;
        if (newOrOld != 1 && newOrOld != 2)
            printf("Please enter a valid number\n");
    }

    if (newOrOld == 1)
    {
        struct features loadFeatures;
        char loadBoard[101][101];
        struct Player loadPlayers[4];

        FILE *outFeatures = fopen("saveFeatures.bin", "rb");
        FILE *outBoard = fopen("saveBoard.bin", "rb");
        FILE *outPlayers = fopen("savePlayers.bin", "rb");

        if (!outFeatures || !outBoard || !outPlayers)
        {
            printf("You don't have any previously saved games!\n");
            printf("Do you want to start a new game?\n(y/n)\n");
            getchar();
            char response[20] = "\0";
            while (response[1] != 0
            || (response[0] != 'n' && response[0] != 'N' && response[0] != 'y' && response[0] != 'Y'))
            {
                gets(response);
                if ((response[0] == 'n' || response[0] == 'N') && response[1] == 0)
                {
                    printf("Alright :]\n");
                    printf("Press any key to exit \n");
                    getch();

                    return 0;
                }
                else if ((response[0] == 'y' || response[0] == 'Y') && response[1] == 0)
                {
                    newOrOld = 2;
                }
                else
                {
                    printf("Invalid entry!\n");
                }
            }
        }
        else
        {
            fread(&loadFeatures, sizeof(loadFeatures), 1, outFeatures);
            fclose(outFeatures);

            row = loadFeatures.row;
            column = loadFeatures.column;
            color = loadFeatures.color;
            gameMode = loadFeatures.gameMode;
            aiSw = loadFeatures.aiSw;
            turn = loadFeatures.round;

            for (int i = 0; i < 2 * row + 1; i++)
            {
                fread(Board[i], sizeof(char), 2 * column + 1, outBoard);
            }
            fclose(outBoard);

            if (gameMode == 1)
            {
                fread(&loadPlayers, sizeof(struct Player), 2, outPlayers);
            }
            else if (gameMode == 2)
            {
                fread(&loadPlayers, sizeof(struct Player), 4, outPlayers);
            }

            player1 = loadPlayers[0];
            player2 = loadPlayers[1];
            if (gameMode == 2)
            {
                player3 = loadPlayers[2];
                player4 = loadPlayers[3];
            }

            fclose(outPlayers);
        }
    }
    if (newOrOld == 2)
    {
        clearScreen();
        // choosing a theme
        color = chooseBoard();
        clearScreen();

        setTextColor(0, 15);

        // choosing game mode
        printf("How would you like to play?\n");
        printf("1) 2 Player mode\n");
        printf("2) 4 Player mode\n");
        scanf("%d", &gameMode);
        clearScreen();

        if (gameMode == 1)
        {
            printf("1) Play with a friend\n");
            printf("2) Play with AI\n");
            scanf("%d", &aiSw);
            aiSw--;
        }
        if (gameMode == 2)
        {
            printf("1) Play with a friend\n");
            printf("2) Play with AI(1 AI player)\n");
            printf("3) Play with AI(2 AI players)\n");
            printf("4) Play with AI(3 AI players)\n");
            scanf("%d", &aiSw);
            aiSw--;
        }

        getPlayers();
        getRowCol();
        clearScreen();
        getWallCount();
        clearScreen();

        // setting players' wall count:
        player1.wallCount = player2.wallCount = wallCount;
        if (gameMode == 2)
        {
            player3.wallCount = player4.wallCount = wallCount;
        }

        // make the board
        makeBoard(row, column);

        // not sure if this is needed here:
        makeSw();

        // determining the pawns' initial positions:
        positionPlayers();
    }

    getchar();

    // The game loop:
    while (player1.location.x != 2 * row - 1 && player2.location.x != 1 && player3.location.y != 1 && player4.location.y != 2 * column - 1) // while nobody has won
    {
        printPage(determinePlayer());

        if (determinePlayer()->blockedFor > 0)
        {
            determinePlayer()->blockedFor--;
            turn += 1;
            if (gameMode == 1)
                turn %= 2;
            else if (gameMode == 2)
                turn %= 4;

            continue;
        }

        gameRun();
    }

    // The previous loop has ended
    // hence someone has won

    // Announcing the winner:
    winMessage();

    printf("Press any key to exit \n");
    getch();

    return 0;
}