# include <stdio.h>
# include "boardMaker.h"

#ifndef depthfs
#define depthfs


int dfs(int canvas[101][101], int row, int column, int x, int y)
{
    canvas[x][y] = -1;
    if (x > 0 && canvas[x - 1][y] == 1)
    {
        dfs(canvas, row, column,  x - 1, y);
    }

    if (x + 1 < 2*row + 1 && canvas[x + 1][y] == 1)
    {
        dfs(canvas, row, column, x + 1, y);
    }

    if (y > 0 && canvas[x][y - 1] == 1)
    {
        dfs(canvas, row, column,  x, y - 1);
    }

    if (y + 1 < 2*column + 1 && canvas[x][y + 1] == 1)
    {
        dfs(canvas, row, column,  x, y + 1);
    }

    for (int i = 0; i < column; i++)
    {
        if (canvas[2*row - 1][i] == -1)
        {
            return 1;
        }

    }

    return 0;
}

#endif