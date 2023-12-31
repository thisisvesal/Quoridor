#include <stdio.h>

#ifndef boardMaker
#define boardMaker

int row, column;
char Board[101][101];
int sw[101][101];

void makeBoard(int row, int column)
{
    // ابعاد بورد
    for (int i = 0; i < 2 * row + 1; i++)
    {
        for (int j = 0; j < 2 * column + 1; j++)
        {
            // ╔ 201
            if (i == 0 & j == 0)
                Board[i][j] = 218;
                // ╗ 187
            else if (i == 0 & j == 2 * row)
                Board[i][j] = 191;
                // ╚ 200
            else if (i == 2 * row & j == 0)
                Board[i][j] = 192;
                // ╝ 188
            else if (i == 2 * row & j == 2 * row)
                Board[i][j] = 217;
                // ╩ 202
            else if (i == 2 * row & j != 0 & j != 2 * row & j % 2 == 0)
                Board[i][j] = 193;
                // ╦ 203
            else if (i == 0 & j != 0 & j != 2 * row & j % 2 == 0)
                Board[i][j] = 194;
                // ═ 205
            else if (i % 2 == 0 & j % 2 != 0)
                Board[i][j] = 196;
                // ║ 186
            else if (j % 2 == 0 & i % 2 != 0)
                Board[i][j] = 179;
                // ╠ 204
            else if (j == 0 & i % 2 == 0 & i != 0 & i != 2 * row)
                Board[i][j] = 195;
                // ╠ 185
            else if (j == 2 * row & i % 2 == 0 & i != 0 & i != 2 * row)
                Board[i][j] = 180;
                // ╬ 206
            else if (i % 2 == 0 & i != 0 & i != 2 * row & j != 0 & j != 2 * row)
                Board[i][j] = 197;
                // جایگاه مهره ها
            else
                Board[i][j] = ' ';
        }
    }
}

void makeSw(){
    for (int i = 0; i < 2*row+1 ; i++)
    {
        for (int j = 0; j < 2*column+1 ; j++)
        {
            sw[i][j] = 1;
        }

    }

    for (int i = 0; i < 2*row+1 ; i++)
    {
        for (int j = 0; j < 2*column+1; j++)
        {
            if (i == 0 || i == 2*row || j == 0 || j == 2*column) // the edges
            {
                sw[i][j] = 0;
            }
            else if (Board[i][j] == -70 || Board[i][j] == -51) // walls
            {
                sw[i][j] = 0;
            }
            else if (i % 2 == 1 && j % 2 == 1) // players
            {
                if (('a' <= Board[i][j] && Board[i][j] <= 'z') || ('A' <= Board[i][j] && Board[i][j] <= 'Z'))
                {
                    sw[i][j] = 0;
                }
            }
            else if (Board[i][j] == -59) // these ┼
            {
                sw[i][j] = 0;
            }



        }

    }
}

#endif