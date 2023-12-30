#include <stdio.h>

void makeBoard(char Board[101][101], int row, int column)
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

int dfs(int canvas[101][101], int row, int column, int x, int y)
{
    canvas[x][y] = -1;
    if (x > 0 && canvas[x - 1][y] == 1)
    {
        dfs(canvas, row, column, x - 1, y);
    }

    if (x + 1 < 2*row + 1 && canvas[x + 1][y] == 1)
    {
        dfs(canvas, row, column, x + 1, y);
    }

    if (y > 0 && canvas[x][y - 1] == 1)
    {
        dfs(canvas, row, column, x, y - 1);
    }

    if (y + 1 < 2*column + 1 && canvas[x][y + 1] == 1)
    {
        dfs(canvas, row, column, x, y + 1);
    }

    for (int i = 0; i < 2*column + 1; i++)
    {
        if (canvas[2*row - 1][i] == -1)
        {
            return 1;
        }
        
    }

    return 0;
}

int main()
{
    char arr[101][101];
    int sw[101][101];
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            sw[i][j] = 1;
        }
        
    }

    // for (int i = 0; i < 11; i++)
    // {
    //     for (int j = 0; j < 11; j++)
    //     {
    //         printf("%d", sw[i][j]);
    //     }
    //     printf("\n");
        
    // }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i == 0 || i == 6 || j == 0 || j == 6 || i == 3)
            {
                sw[i][j] = 0;
            }
            else if (arr[i][j] == -70 || arr[i][j] == -51)
            {
                sw[i][j] = 0;
            }
            else if (i % 2 == 1 && j % 2 == 1)
            {
                if (('a' <= arr[i][j] && arr[i][j] <= 'z') || ('A' <= arr[i][j] && arr[i][j] <= 'Z'))
                {
                    sw[i][j] = 0;
                }
            }
            
            
        }
        
    }

    
    makeBoard(arr, 3, 3);
    printBoard(arr, 3, 3);
    // printf("\n%d\n", dfs(arr, 1, 1, 5, 5));
    //printBoard(sw, 5, 5);
    // printf("%d\n", ' ');
    // printf("%d\n", arr[1][1]);
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%d", sw[i][j]);
        }
        printf("\n");
        
    }
    printf("dfs answer is: ");
    printf("%d\n", dfs(sw, 3, 3, 1, 1));

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%d", sw[i][j]);
        }
        printf("\n");
        
    }
    

    return 0;

}