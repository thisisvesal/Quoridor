# include <stdio.h>

char board[21][21];
// int createBoard(board[][]?) {...}

int main()
{
    // چطوری با تابع روی آرایه دوبعدی عملیات انجام بدیم؟
    // بعد از پیدا کردن جواب حلقه بعد باید تابع بشه
    for (int i = 0; i < 21; i++) // creating the board
    {
        for (int j = 0; j < 21; j++)
        {
            if (j % 2 == 0 && i != 0) // شماره سطر یا ستون زوج شامل دیوار میشه
            {
                board[i][j] = '|'; // دیواری که کاربر بذاره رو میشه با || یا = نمایش داد
            }
            else if (i % 2 == 0)
            {
                board[i][j] = '_';
            }
            else
            {
                board[i][j] = 'D';
            }
        }
        board[2][2] = board[1][2] =  'X';
    }

    for (int i = 0; i < 21; i++) // printing the board
    {
        for (int j = 0; j < 21; j++)
        {
            printf("%c" , board[i][j]);
        }
        printf("\n");
        
    }

    return 0;
}
