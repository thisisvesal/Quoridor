#include "boardMaker.h"
#include "boardPrinter.h"
#include "motion.h"
#include "design.h"
#include "rounds.h"

int main()
{
    int round = 1;

    setTextColor(0 , 15);
    clearScreen();

    // write welcome message + arrow keys
    printf("Welcome to Quoridor game!");
    setTextColor(6 , 15);
    printf(" %c\n",2);
    sleep(2000);
    clearScreen();

    setTextColor(0 , 15);
    printf("Movment keys:\n");
    setTextColor(4 , 15);
    arrowKeyPrint();
    sleep(2000);
    clearScreen();

    int color;
    color=chooseBoard();
    clearScreen();

    setTextColor(0 , 15);
    printf("Player(1) Please enter your name:\n");
    scanf("%s",player1.name);
    player1.nameInitial=player1.name[0];
    clearScreen();

    printf("Player(2) Please enter your name:\n");
    scanf("%s",player2.name);
    player2.nameInitial=player2.name[0];
    clearScreen();

    printf("Please enter the number of rows and columns:\n");
    scanf("%d%d", &row, &column);
    clearScreen();

    int wallCount;
    printf("Please enter the number of walls:\n");
    scanf("%d",&wallCount);
    player1.wallCount=player2.wallCount=wallCount;
    clearScreen();


    makeBoard(row, column);

    if (column % 2 == 0)
    {
        player1.location.x = 1;
        player1.location.y = column - 1;

        player2.location.x = 2*row - 1;
        player2.location.y = column + 1;
    }
    else
    {
        player1.location.x = 1;
        player1.location.y = column;

        player2.location.x = 2*row - 1;
        player2.location.y = column;
    }

    // مختصات مهره اول
    Board[player1.location.x][player1.location.y] = player1.nameInitial;

    // مختصات مهره دوم
    Board[player2.location.x][player2.location.y] = player2.nameInitial;

    setTextColor(color , 15);
    printBoard(Board, row, column);

    while (player1.location.x != 2*row - 1 && player2.location.x != 1)
    {
        getchar();
        char moveChar = 0;
        if (round == 1)
        {
            while (moveChar != 'm' && moveChar != 'w')
            {
                setTextColor(0 , 15);
                printf("\nWall or move?\n(enter w for wall and m for move)\n");
                scanf("%c", &moveChar);
                if (moveChar == 'W') moveChar = 'w';
                else if (moveChar == 'M') moveChar = 'm';
            }

            if (moveChar == 'w') //wall
            {
                putWall();
                clearScreen();
                setTextColor(color , 15);
                printBoard(Board, row, column);
            }
            else if (moveChar == 'm') //move
            {
                gotoxy(player1.location.x, player1.location.y);
                move(&player1);
                clearScreen();
                setTextColor(color , 15);
                printBoard(Board, row, column);
            }
        }
        else
        {
            while (moveChar != 'm' && moveChar != 'w')
            {
                setTextColor(0 , 15);
                printf("\nWall or move?\n(enter w for wall and m for move)\n");
                scanf("%c", &moveChar);
                if (moveChar == 'W') moveChar = 'w';
                else if (moveChar == 'M') moveChar = 'm';
            }
            if (moveChar == 'w') //wall
            {
                putWall();
                clearScreen();
                setTextColor(color , 15);
                printBoard(Board, row, column);
            }
            else if (moveChar == 'm') //move
            {
                gotoxy(player2.location.x, player2.location.y);
                move(&player2);
                clearScreen();
                setTextColor(color , 15);
                printBoard(Board, row, column);
            }
        }

        round *= -1;
    }
    if (player1.location.x == 2*row - 1)
    {
        setTextColor(0 , 15);
        printf("%s wins!!!\n", player1.name);
        // sleep(5000);
    }
    else
    {
        setTextColor(0 , 15);
        printf("%s wins!!!!\n", player2.name);
        // sleep(5000);
    }
    printf("Press enter to exit \n");
    getch();

    return 0;
}