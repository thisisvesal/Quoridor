#include "design.h"

#ifndef getInfo
#define getInfo

void getPlayers()
{
    player1.isAi = 0;
    player2.isAi = 0;
    player3.isAi = 0;
    player4.isAi = 0;

    if (gameMode == 1 && !aiSw)
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
    else if (gameMode == 1 && aiSw)
    {
        printf("Please enter your name:\n");
        scanf("%s", player1.name);
        player1.nameInitial = player1.name[0];
        clearScreen();
        strcpy(player2.name, "Computer");
        player2.nameInitial = 'C';
        player2.isAi = 1;
    }
    else if (gameMode == 2 && !aiSw)
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

        strcpy(player4.name, "Computer");
        player4.nameInitial = 'C';
        player4.isAi = 1;
        clearScreen();
    }
    else if (gameMode == 2 && aiSw == 2)
    {
        // getting players' names
        printf("Player(1) Please enter your name:\n");
        scanf("%s", player1.name);
        player1.nameInitial = player1.name[0];

        strcpy(player2.name, "Down");
        player2.nameInitial = 'D';
        player2.isAi = 1;

        printf("Player(3) Please enter your name:\n");
        scanf("%s", player3.name);
        player3.nameInitial = player3.name[0];

        strcpy(player4.name, "Left");
        player4.nameInitial = 'L';
        player4.isAi = 1;
        clearScreen();
    }
    else if (gameMode == 2 && aiSw == 3)
    {
        // getting players' names
        printf("Player(1) Please enter your name:\n");
        scanf("%s", player1.name);
        player1.nameInitial = player1.name[0];

        strcpy(player2.name, "Down");
        player2.nameInitial = 'D';
        player2.isAi = 1;

        strcpy(player3.name, "Right");
        player3.nameInitial = 'R';
        player3.isAi = 1;

        strcpy(player4.name, "Left");
        player4.nameInitial = 'L';
        player4.isAi = 1;
        clearScreen();
    }
}

void getRowCol()
{
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
}

void getWallCount()
{
    // getting the number of walls
    int wallIsNum = 0;
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
}

void positionPlayers()
{
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

    player1.charmNo = 1;
    player2.charmNo = 1;
    player3.charmNo = 1;
    player4.charmNo = 1;

    // placing the players in their positions:
    Board[player1.location.x][player1.location.y] = player1.nameInitial;
    Board[player2.location.x][player2.location.y] = player2.nameInitial;
    if (gameMode == 2)
    {
        Board[player3.location.x][player3.location.y] = player3.nameInitial;
        Board[player4.location.x][player4.location.y] = player4.nameInitial;
    }
}

void winMessage()
{
    printf("\n");
    setTextColor(15, color);
    if (player1.location.x == 2 * row - 1)
    {
        printf("%s WINSSSSSSSSSSSSS!!!", player1.name);
    }
    else if (player2.location.x == 1)
    {
        printf("%s WINSSSSSSSSSSSSS!!!!", player2.name);
    }
    if (gameMode == 2)
    {
        if (player3.location.y == 1)
        {
            printf("%s WINSSSSSSSSSSSSS!!!", player3.name);
        }
        else if (player4.location.y == 2 * column - 1)
        {
            printf("%s WINSSSSSSSSSSSSS!!!!", player4.name);
        }
    }
    setTextColor(color, 15);
    printf("\n\n");
}

#endif