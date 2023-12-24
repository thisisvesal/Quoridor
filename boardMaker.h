#include <stdio.h>

#ifndef boardMaker
#define boardMaker

int row, column;
char Board[101][101];

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

#endif