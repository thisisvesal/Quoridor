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
    printf("Welcome to Quoridor game!\n", 2);
    arrowKeyPrint();

    printf("Please enter the number of rows and columns:\n");
    scanf("%d%d", &row, &column);
    clearScreen();

    setTextColor(9 , 15);
    makeBoard(row, column);

    if (column % 2 == 0)
    {
        player1.location[0] = 1;
        player1.location[1] = column - 1;

        player2.location[0] = 2*row - 1;
        player2.location[1] = column + 1;
    }
    else
    {
        player1.location[0] = 1;
        player1.location[1] = column;

        player2.location[0] = 2*row - 1;
        player2.location[1] = column;
    }
    
    // مختصات مهره اول
    player1.nameInitial = 'S';
    Board[player1.location[0]][player1.location[1]] = player1.nameInitial;

    // مختصات مهره دوم
    player2.nameInitial = 'V';
    Board[player2.location[0]][player2.location[1]] = player2.nameInitial;

    printBoard(Board, row, column);

    while (player1.location[0] != 2*row - 1 && player2.location[0] != 1)
    {
        char moveChar = 0;
        if (round == 1)
        {
            while (moveChar != 'm' && moveChar != 'w')
            {
                printf("\nWall or move?\n(enter w for wall and m for move)\n");
                scanf("%c", &moveChar);
                if (moveChar == 'W') moveChar = 'w';
                else if (moveChar == 'M') moveChar = 'm';
            }
            
            if (moveChar == 'w') //wall
            {
                putWall();
                clearScreen();
                printBoard(Board, row, column);
            }
            else if (moveChar == 'm') //move
            {
                move(&player1);
                clearScreen();
                printBoard(Board, row, column);
            }
        }
        else
        {
            while (moveChar != 'm' && moveChar != 'w')
            {
                printf("\nWall or move?\n(enter w for wall and m for move)\n");
                scanf("%c", &moveChar);
                if (moveChar == 'W') moveChar = 'w';
                else if (moveChar == 'M') moveChar = 'm';
            }
            if (moveChar == 'w') //wall
            {
                putWall();
                clearScreen();
                printBoard(Board, row, column);
            }
            else if (moveChar == 'm') //move
            {
                move(&player2);
                clearScreen();
                printBoard(Board, row, column);
            }
        }
        
        round *= -1;
    }
    
    
    return 0;
}