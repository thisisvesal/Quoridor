#include "boardMaker.h"
#include "boardPrinter.h"
#include "motion.h"
#include "design.h"

int main()
{
    setTextColor(0 , 15);
    setTextColor(0, 15);
    clearScreen();

    // write welcome message
    printf("Welcome to Quoridor game!");
    setTextColor(6, 15);
    printf(" %c\n", 2);
    sleep(2000);
    clearScreen();

    // prints the arrow keys
    setTextColor(0, 15);
    printf("You can move in the game using the arrow keys\n");
    setTextColor(4, 15);
    arrowKeyPrint();
    sleep(2000);
    clearScreen();

    // choosing a theme
    int color;
    color = chooseBoard();
    clearScreen();

    // getting players' names
    setTextColor(0, 15);
    printf("Player(1) Please enter your name:\n");
    scanf("%s", player1.name);
    player1.nameInitial = player1.name[0];
    clearScreen();

    printf("Player(2) Please enter your name:\n");
    scanf("%s", player2.name);
    player2.nameInitial = player2.name[0];
    clearScreen();

    // getting row and column numbers
    int rowIsNum = 0, colIsNum = 0;
    while (!rowIsNum || !colIsNum)
    {
        printf("Please enter the number of rows and columns:\n");
        char rowCopy[30], colCopy[30];
        scanf("%s%s", rowCopy, colCopy);

        int i;
        for (i = 0; rowCopy[i] && '0' <= rowCopy[i] && rowCopy[i] <= '9'; i++)
        {
            row += rowCopy[i];
            row *= 10;
        }
        row /= 10;
        if (rowCopy[i] == 0)
        {
            rowIsNum = 1;
        }

        for (i = 0; colCopy[i] && '0' <= colCopy[i] && colCopy[i] <= '9'; i++)
        {
            column += colCopy[i];
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

    // gettinng the number of walls
    int wallIsNum = 0;
    int wallCount;
    while (!wallIsNum)
    {
        printf("Please enter the number of walls:\n");
        char wallCountCopy[30];
        scanf("%s", wallCountCopy);

        int i;
        for (i = 0; wallCountCopy[i] && '0' <= wallCountCopy[i] && wallCountCopy[i] <= '9'; i++)
        {
            wallCount += wallCountCopy[i];
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
    // make the board
    // setting players' wall count:
    player1.wallCount = player2.wallCount = wallCount;
    

    // make the board
    makeBoard(row, column);
    // makeSw();

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

    // placing the players in their positions:
    Board[player1.location.x][player1.location.y] = player1.nameInitial;
    Board[player2.location.x][player2.location.y] = player2.nameInitial;


    // first print of the board:
    setTextColor(color , 15);
    printBoard(Board, row, column);
    printf("Player1 remained walls :");
    printRemainingWalls(player1.wallCount);
    printf("Player2 remained walls :");
    printRemainingWalls(player2.wallCount);

    // integer round determines whose turn it is
    // if it is 1, it's player 1's turn
    // if it is -1, it's player 2's turn
    int round = 1;

    while (player1.location.x != 2*row - 1 && player2.location.x != 1) // while nobody has won
    {
        getchar();
        if (round == 1)
        {
            // moveChar shows if the player wants to move or place a wall
            char moveChar = 0;
            while (moveChar != 'm' && moveChar != 'w')
            {
                setTextColor(0, 15);
                printf("\nWall or move?\n(enter w for wall, and m for move)\n");
                scanf("%c", &moveChar);
                if (moveChar == 'W')
                    moveChar = 'w';
                else if (moveChar == 'M')
                    moveChar = 'm';
            }

            // placing a wall:
            if (moveChar == 'w' && player1.wallCount != 0)  // runs only if the player still has walls left
            if (moveChar == 'w' && player1.wallCount != 0) // runs only if the player still has walls left
            {
                putWall();
                player1.wallCount--;
                clearScreen();
                setTextColor(color, 15);
                printBoard(Board, row, column);
                printf("Player1 remained walls :");
                printRemainingWalls(player1.wallCount);
                printf("Player2 remained walls :");
                printRemainingWalls(player2.wallCount);                // changing the round:

                // changing the round:
                round *= -1;
            }
            else if (moveChar == 'w' && player1.wallCount == 0) // if the player is put of walls
            {
                printf("You're out of walls!\n");
                sleep(750);
            }
            else if (moveChar == 'm') // move for player 1
            {
                gotoxy(player1.location.x, player1.location.y);
                move(&player1);
                clearScreen();
                setTextColor(color, 15);
                printBoard(Board, row, column);
                printf("Player1 remained walls :");
                printRemainingWalls(player1.wallCount);
                printf("Player2 remained walls :");
                printRemainingWalls(player2.wallCount);
                // changing the round:

                round *= -1;
            }
        }
        else
        {
            // moveChar shows if the player wants to move or place a wall
            char moveChar = 0;
            while (moveChar != 'm' && moveChar != 'w')
            {
                setTextColor(0, 15);
                printf("\nWall or move?\n(enter w for wall, and m for move)\n");
                scanf("%c", &moveChar);
                if (moveChar == 'W')
                    moveChar = 'w';
                else if (moveChar == 'M')
                    moveChar = 'm';
            }
            // placing a wall:

            if (moveChar == 'w' && player2.wallCount != 0) // runs only if the player still has walls left
            {
                putWall();
                clearScreen();
                player2.wallCount--;
                setTextColor(color, 15);
                printBoard(Board, row, column);
                printf("Player1 remained walls :");
                printRemainingWalls(player1.wallCount);
                printf("Player2 remained walls :");
                printRemainingWalls(player2.wallCount);

                // changing the round:
                round *= -1;
            }
            else if (moveChar == 'w' && player2.wallCount == 0) // if the player is put of walls
            {
                printf("You're out of walls!\n");
                sleep(750);
            }
            else if (moveChar == 'm') // move for player 2
            {
                gotoxy(player2.location.x, player2.location.y);
                move(&player2);
                clearScreen();
                setTextColor(color, 15);
                printBoard(Board, row, column);
                printf("Player1 remained walls :");
                printRemainingWalls(player1.wallCount);
                printf("Player2 remained walls :");
                printRemainingWalls(player2.wallCount);

                // changing the round:
                round *= -1;
            }
        }
    }

    // The previous loop has ended
    // hence someone has won

    // Determining the winner:
    if (player1.location.x == 2*row - 1)
    {
        setTextColor(0, 15);
        printf("%s wins!!!\n", player1.name);
    }
    else
    {
        setTextColor(0, 15);
        printf("%s wins!!!!\n", player2.name);
    }
    printf("Press enter to exit \n");
    getch();

    return 0;
}