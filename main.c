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

    // // prints the arrow keys

    // setTextColor(0, 15);
    // printf("You can move in the game using the arrow keys\n");
    // setTextColor(4, 15);
    // arrowKeyPrint();
    // sleep(2000);
    // clearScreen();

    // choosing a theme
    int color;
    color = chooseBoard();
    clearScreen();

    setTextColor(0, 15);

    // choosing game mode
    printf("How would you like to play?\n");
    printf("1) 2 Player mode\n");
    printf("2) 4 Player mode\n");
    scanf("%d", &gameMode);
    clearScreen();

    int aiSw = 0;
    printf("1) Play with AI\n");
    printf("2) Play with a friend\n");
    scanf("%d", &aiSw);

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

        printf("Player(4) Please enter your name:\n");
        scanf("%s", player4.name);
        player4.nameInitial = player4.name[0];
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

    // placing the players in their positions:
    Board[player1.location.x][player1.location.y] = player1.nameInitial;
    Board[player2.location.x][player2.location.y] = player2.nameInitial;
    if (gameMode == 2)
    {
        Board[player3.location.x][player3.location.y] = player3.nameInitial;
        Board[player4.location.x][player4.location.y] = player4.nameInitial;
    }

    // first print of the board:
    setTextColor(color, 15);
    printBoard(Board, row, column);
    printf("%s's remaining walls:", player1.name);
    printRemainingWalls(player1.wallCount);
    printf("%s's remaining walls:", player2.name);
    printRemainingWalls(player2.wallCount);
    if (gameMode == 2)
    {
        printf("%s's remaining walls:", player3.name);
        printRemainingWalls(player3.wallCount);
        printf("%s's remaining walls:", player4.name);
        printRemainingWalls(player4.wallCount);
    }

    // integer round determines whose turn it is
    int round = 0;
    int gameRepCount = 0;

    // The game loop:
    while (player1.location.x != 2 * row - 1 && player2.location.x != 1
           && player3.location.y != 1 && player4.location.y != 2 * column - 1) // while nobody has won
    {
        if (gameRepCount == 0)
        {
            getchar();
            gameRepCount++;
        }
        char moveChar[100] = "\0";
        gameRun(&round, color);
    }

    // The previous loop has ended
    // hence someone has won

    // Determining the winner:
    if (player1.location.x == 2 * row - 1)
    {
        // setTextColor(0, 15);
        printf("%s wins!!!\n", player1.name);
    }
    else if (player2.location.x == 1)
    {
        // setTextColor(0, 15);
        printf("%s wins!!!!\n", player2.name);
    }
    if(gameMode == 2)
    {
        if (player3.location.y == 1)
        {
            // setTextColor(0, 15);
            printf("%s wins!!!\n", player3.name);
        }
        else if (player4.location.y == 2*column - 1)
        {
            // setTextColor(0, 15);
            printf("%s wins!!!!\n", player4.name);
        }
    }
    printf("Press any key to exit \n");
    getch();

    return 0;
}