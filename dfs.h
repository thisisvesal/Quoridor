#ifndef dfs
#define dfs


// checking if the route exist for player1
int dfsDown(int sw[101][101], int row, int column, int x, int y)
{
    sw[x][y] = 2;
    if (x > 0 && sw[x - 1][y] == 1)
    {
        dfsDown(sw, row, column, x - 1, y);
    }

    if (x + 1 < 2 * row + 1 && sw[x + 1][y] == 1)
    {
        dfsDown(sw, row, column, x + 1, y);
    }

    if (y > 0 && sw[x][y - 1] == 1)
    {
        dfsDown(sw, row, column, x, y - 1);
    }

    if (y + 1 < 2 * column + 1 && sw[x][y + 1] == 1)
    {
        dfsDown(sw, row, column, x, y + 1);
    }

    for (int i = 0; i < 2 * column + 1; i++)
    {
        if (sw[2 * row - 1][i] == 2)
        {
            return 1;
        }
    }

    return 0;
}

// checking if the route exist for player2
int dfsUp(int sw[101][101], int row, int column, int x, int y)
{
    sw[x][y] = 2;
    if (x > 0 && sw[x - 1][y] == 1)
    {
        dfsUp(sw, row, column, x - 1, y);
    }

    if (x + 1 < 2 * row + 1 && sw[x + 1][y] == 1)
    {
        dfsUp(sw, row, column, x + 1, y);
    }

    if (y > 0 && sw[x][y - 1] == 1)
    {
        dfsUp(sw, row, column, x, y - 1);
    }

    if (y + 1 < 2 * column + 1 && sw[x][y + 1] == 1)
    {
        dfsUp(sw, row, column, x, y + 1);
    }

    for (int i = 0; i < 2 * column + 1; i++)
    {
        if (sw[1][i] == 2)
        {
            return 1;
        }
    }

    return 0;
}

int dfsRight(int sw[101][101], int row, int column, int x, int y)
{
    sw[x][y] = 2;
    if (x > 0 && sw[x][y-1] == 1)
    {
        dfsRight(sw, row, column, x, y-1);
    }

    if (y + 1 < 2 * column + 1 && sw[x][y+1] == 1)
    {
        dfsRight(sw, row, column, x, y+1);
    }

    if (x > 0 && sw[x-1][y] == 1)
    {
        dfsRight(sw, row, column, x-1, y );
    }

    if (x + 1 < 2 * row + 1 && sw[x+1][y] == 1)
    {
        dfsRight(sw, row, column, x+1, y);
    }

    for (int i = 0; i < 2 * row + 1; i++)
    {
        if (sw[i][2*column-1] == 2)
        {
            return 1;
        }
    }

    return 0;
}

int dfsLeft(int sw[101][101], int row, int column, int x, int y)
{
    sw[x][y] = 2;
    if (x > 0 && sw[x][y-1] == 1)
    {
        dfsLeft(sw, row, column, x, y-1);
    }

    if (y + 1 < 2 * column + 1 && sw[x][y+1] == 1)
    {
        dfsLeft(sw, row, column, x, y+1);
    }

    if (x > 0 && sw[x-1][y] == 1)
    {
        dfsLeft(sw, row, column, x-1, y );
    }

    if (x + 1 < 2 * row + 1 && sw[x+1][y] == 1)
    {
        dfsLeft(sw, row, column, x+1, y);
    }

    for (int i = 0; i < 2 * row + 1; i++)
    {
        if (sw[i][1] == 2)
        {
            return 1;
        }
    }

    return 0;
}



#endif