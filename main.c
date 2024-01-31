#include "game.h"

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
    int newOrOld = 0;
    scanf("%d", &newOrOld);
    if (newOrOld == 1)
    {
        struct features loadFeatures;
        char loadBoard[101][101];
        struct Player loadPlayers[4];

        FILE *outFeatures = fopen("saveFeatures.bin", "rb");
        FILE *outBoard = fopen("saveBoard.bin", "rb");
        FILE *outPlayers = fopen("savePlayers.bin", "rb");

        fread(&loadFeatures, sizeof(loadFeatures), 1, outFeatures);
        fclose(outFeatures);

        row = loadFeatures.row;
        column = loadFeatures.column;
        color = loadFeatures.color;
        gameMode = loadFeatures.gameMode;
        aiSw = loadFeatures.aiSw;
        round = loadFeatures.round;

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
    else if (newOrOld == 2)
    {
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
            printf("1) Play with AI\n");
            printf("2) Play with a friend\n");
            scanf("%d", &aiSw);
        }
        if (gameMode == 2)
        {
            printf("1) Play with a friend\n");
            printf("2) Play with AI(1 AI player)\n");
            printf("3) Play with AI(2 AI players)\n");
            printf("4) Play with AI(3 AI players)\n");
            scanf("%d", &aiSw);
        }

        if (gameMode == 1 && aiSw == 2)
        {
            // getting players' names
            printf("Player(1) Please enter your name:\n");
            scanf("%s", player1.name);
            player1.nameInitial = player1.name[0];

            printf("Player(2) Please enter your name:\n");
            scanf("%s", player2.name);
            player2.nameInitial = player2.name[0];
            clearScreen();
        }
        else if (gameMode == 1 && aiSw == 1)
        {
            printf("Please enter your name:\n");
            scanf("%s", player1.name);
            player1.nameInitial = player1.name[0];
            clearScreen();
            strcpy(player2.name, "Computer");
            player2.nameInitial = 'C';
        }
        else if (gameMode == 2 && aiSw == 1)
        {
            // getting players' names
            printf("Player(1) Please enter your name:\n");
            scanf("%s", player1.name);
            player1.nameInitial = player1.name[0];

            printf("Player(2) Please enter your name:\n");
            scanf("%s", player2.name);
            player2.nameInitial = player2.name[0];

            printf("Player(3) Please enter your name:\n");
            scanf("%s", player3.name);
            player3.nameInitial = player3.name[0];

            printf("Player(4) Please enter your name:\n");
            scanf("%s", player4.name);
            player4.nameInitial = player4.name[0];
            clearScreen();
        }
        else if (gameMode == 2 && aiSw == 2)
        {
            // getting players' names
            printf("Player(1) Please enter your name:\n");
            scanf("%s", player1.name);
            player1.nameInitial = player1.name[0];

            printf("Player(2) Please enter your name:\n");
            scanf("%s", player2.name);
            player2.nameInitial = player2.name[0];

            printf("Player(3) Please enter your name:\n");
            scanf("%s", player3.name);
            player3.nameInitial = player3.name[0];

            strcpy(player4.name, "Computer");
            player4.nameInitial = 'C';
            clearScreen();
        }
        else if (gameMode == 2 && aiSw == 3)
        {
            // getting players' names
            printf("Player(1) Please enter your name:\n");
            scanf("%s", player1.name);
            player1.nameInitial = player1.name[0];

            strcpy(player2.name, "Computer1");
            player2.nameInitial = 'C';

            printf("Player(3) Please enter your name:\n");
            scanf("%s", player3.name);
            player3.nameInitial = player3.name[0];

            strcpy(player4.name, "Computer2");
            player4.nameInitial = 'C';
            clearScreen();
        }
        else if (gameMode == 2 && aiSw == 4)
        {
            // getting players' names
            printf("Player(1) Please enter your name:\n");
            scanf("%s", player1.name);
            player1.nameInitial = player1.name[0];

            strcpy(player2.name, "Computer1");
            player2.nameInitial = 'C';

            strcpy(player3.name, "Computer2");
            player3.nameInitial = 'C';

            strcpy(player4.name, "Computer3");
            player4.nameInitial = 'C';
            clearScreen();
        }

        // getting row and column numbers
        int rowIsNum = 0, colIsNum = 0;
        row = column = 0;

        while (!rowIsNum || !colIsNum)
        {
            printf("Please enter the number of rows and columns:\n");
            char rowCopy[30], colCopy[30];
            scanf("%s%s", rowCopy, colCopy);

            int i;
            for (i = 0; rowCopy[i] && '0' <= rowCopy[i] && rowCopy[i] <= '9'; i++)
            {
                row += (rowCopy[i] - 48);
                row *= 10;
            }
            row /= 10;
            if (rowCopy[i] == 0)
            {
                rowIsNum = 1;
            }

            for (i = 0; colCopy[i] && '0' <= colCopy[i] && colCopy[i] <= '9'; i++)
            {
                column += (colCopy[i] - 48);
                column *= 10;
            }
            column /= 10;
            if (colCopy[i] == 0)
            {
                colIsNum = 1;
            }

            if (!rowIsNum || !colIsNum)
            {
                printf("That wasn't a number!\n");
            }
        }
        clearScreen();

        // getting the number of walls
        int wallIsNum = 0;
        int wallCount = 0;
        while (!wallIsNum)
        {
            printf("Please enter the number of walls:\n");
            char wallCountCopy[30];
            scanf("%s", wallCountCopy);

            int i;
            for (i = 0; wallCountCopy[i] && '0' <= wallCountCopy[i] && wallCountCopy[i] <= '9'; i++)
            {
                wallCount += (wallCountCopy[i] - 48);
                wallCount *= 10;
            }
            wallCount /= 10;

            if (wallCountCopy[i] == 0)
            {
                wallIsNum = 1;
            }
            if (!wallIsNum)
            {
                printf("That wasn't a number!\n");
            }
        }
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
        if (column % 2 == 0)
        {
            player1.location.x = 1;
            player1.location.y = column - 1;

            player2.location.x = 2 * row - 1;
            player2.location.y = column + 1;
        }
        else
        {
            player1.location.x = 1;
            player1.location.y = column;

            player2.location.x = 2 * row - 1;
            player2.location.y = column;
        }

        if (gameMode == 2)
        {
            if (row % 2 == 0)
            {
                player3.location.x = row - 1;
                player3.location.y = 2 * column - 1;

                player4.location.x = row + 1;
                player4.location.y = 1;
            }
            else
            {
                player3.location.x = row;
                player3.location.y = 2 * column - 1;

                player4.location.x = row;
                player4.location.y = 1;
            }
        }

        player1.blockedFor = 0;
        player2.blockedFor = 0;
        player3.blockedFor = 0;
        player4.blockedFor = 0;

        // placing the players in their positions:
        Board[player1.location.x][player1.location.y] = player1.nameInitial;
        Board[player2.location.x][player2.location.y] = player2.nameInitial;
        if (gameMode == 2)
        {
            Board[player3.location.x][player3.location.y] = player3.nameInitial;
            Board[player4.location.x][player4.location.y] = player4.nameInitial;
        }
    }

    // first print of the board:
    printPage(&player1);
    // printf("%s's turn\n", player1.name);

    getchar();

    // The game loop:
    while (player1.location.x != 2 * row - 1 && player2.location.x != 1 && player3.location.y != 1 && player4.location.y != 2 * column - 1) // while nobody has won
    {
        printPage(determinePlayer());
        if (charmSw) getCharm();

        if (determinePlayer()->blockedFor > 0)
        {
            determinePlayer()->blockedFor--;
            round += 1;
            if (gameMode == 1)
                round %= 2;
            else if (gameMode == 2)
                round %= 4;

            continue;
        }

        gameRun();
    }

    // The previous loop has ended
    // hence someone has won

    // Determining the winner:
    if (player1.location.x == 2 * row - 1)
    {
        // setTextColor(0, 15);
        printf("%s WINSSSSSSSSSSSSS!!!\n", player1.name);
    }
    else if (player2.location.x == 1)
    {
        // setTextColor(0, 15);
        printf("%s WINSSSSSSSSSSSSS!!!!\n", player2.name);
    }
    if (gameMode == 2)
    {
        if (player3.location.y == 1)
        {
            // setTextColor(0, 15);
            printf("%s WINSSSSSSSSSSSSS!!!\n", player3.name);
        }
        else if (player4.location.y == 2 * column - 1)
        {
            // setTextColor(0, 15);
            printf("%s WINSSSSSSSSSSSSS!!!!\n", player4.name);
        }
    }
    printf("Press any key to exit \n");
    getch();

    return 0;
}