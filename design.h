# include <stdio.h>
# include <windows.h>

# ifndef design
# define design

void clearScreen()
{
    system("cls");
}

void setTextColor(int textColor, int backColor)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void arrowKeyPrint()
{
    char keyArr[5][7];
    keyArr[0][0] = keyArr[0][1] = keyArr[0][5] = keyArr[0][6]
    = keyArr[1][0] = keyArr[1][1] = keyArr[1][5] = keyArr[1][6]
    = ' ';

    keyArr[0][2] = keyArr[2][0] = 218;

    keyArr[0][4] = keyArr[2][6] = 191;

    keyArr[0][3]
    = keyArr[2][1] = keyArr[2][3] = keyArr[2][5]
    = keyArr[4][1] = keyArr[4][3] = keyArr[4][5]
    = 196;

    keyArr[1][2] = keyArr[1][4]
    = keyArr[3][0] = keyArr[3][2] = keyArr[3][4] = keyArr[3][6]
    = 179;

    keyArr[2][2] = keyArr[2][4] = 197;

    keyArr[4][2] = keyArr[4][4] = 193;

    keyArr[4][0] = 192;

    keyArr[4][6] = 217;

    keyArr[1][3] = 24;
    keyArr[3][1] = 27;
    keyArr[3][3] = 25;
    keyArr[3][5] = 26;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%c", keyArr[i][j]);
        }
        printf("\n");
    }

}

# endif