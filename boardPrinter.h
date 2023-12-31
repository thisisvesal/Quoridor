#include <stdio.h>

#ifndef boardPrinter
#define boardPrinter

// printing the board
void printBoard(char Board[][101], int row, int column)
{
    for (int i = 0; i < 2 * row + 1; i++)
    {
        for (int j = 0; j < 2 * column + 1; j++)
        {
            printf("%c", Board[i][j]);
        }
        printf("\n");
    }
}

#endif