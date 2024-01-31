#include <stdio.h>
#include "general.h"

#ifndef boardMaker
#define boardMaker

void makeBoard(int row, int column) // as the name suggests, making the board
{
    for (int i = 0; i < 2 * row + 1; i++)
    {
        for (int j = 0; j < 2 * column + 1; j++)
        {
            // ┌
            if (i == 0 & j == 0)
                Board[i][j] = 218;

            // ┐
            else if (i == 0 & j == 2 * row)
                Board[i][j] = 191;

            // └
            else if (i == 2 * row & j == 0)
                Board[i][j] = 192;

            // ┘
            else if (i == 2 * row & j == 2 * row)
                Board[i][j] = 217;

            // ┴
            else if (i == 2 * row & j != 0 & j != 2 * row & j % 2 == 0)
                Board[i][j] = 193;

            // ┬
            else if (i == 0 & j != 0 & j != 2 * row & j % 2 == 0)
                Board[i][j] = 194;

            // ─
            else if (i % 2 == 0 & j % 2 != 0)
                Board[i][j] = 196;

            // │
            else if (j % 2 == 0 & i % 2 != 0)
                Board[i][j] = 179;

            // ├
            else if (j == 0 & i % 2 == 0 & i != 0 & i != 2 * row)
                Board[i][j] = 195;

            // ┤
            else if (j == 2 * row & i % 2 == 0 & i != 0 & i != 2 * row)
                Board[i][j] = 180;

            // ┼
            else if (i % 2 == 0 & i != 0 & i != 2 * row & j != 0 & j != 2 * row)
                Board[i][j] = 197;

            // marking pawns' places with spaces
            else
                Board[i][j] = ' ';
        }
    }
}

// creates a switch array based on the main board
// this is primarily used when applying dfs in the program
// check "motion.h" to see its application
void makeSw()
{
    // all accessible points on the board should be marked with 1
    // and so all the inaccessible ones should be mark with 0

    // first all points are marked 1:
    for (int i = 0; i < 2 * row + 1; i++)
    {
        for (int j = 0; j < 2 * column + 1; j++)
        {
            sw[i][j] = 1;
        }
    }

    // here we mark the mentioned inaccessible points with 0:
    for (int i = 0; i < 2 * row + 1; i++)
    {
        for (int j = 0; j < 2 * column + 1; j++)
        {
            if (i == 0 || i == 2 * row || j == 0 || j == 2 * column) // the edges
            {
                sw[i][j] = 0;
            }
            else if (Board[i][j] == -70 || Board[i][j] == -51) // walls
            {
                sw[i][j] = 0;
            }
            // else if (i % 2 == 1 && j % 2 == 1) // players' pawns
            // {
            //     if (('a' <= Board[i][j] && Board[i][j] <= 'z') || ('A' <= Board[i][j] && Board[i][j] <= 'Z'))
            //     {
            //         sw[i][j] = 0;
            //     }
            // }
            else if (Board[i][j] == -59) // these: ┼
            {
                sw[i][j] = 0;
            }
        }
    }
}

#endif