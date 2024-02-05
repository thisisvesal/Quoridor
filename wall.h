#include "motion.h"

#ifndef wall
#define wall

location userWallPlace()
{
    location ans;
    ans.x = row;
    ans.y = column;
    gotoxy(ans.x, ans.y);
    // this section allows movement of the cursor until enter is pressed
    // then when enter is hit, a wall will be placed there
    while (1)
    {
        char where = getch();
        if (where == 13)
            break;
        else if (where == 77) // right
        {
            ans.y++;
            gotoxy(ans.x, ans.y);
        }
        else if (where == 75) // left
        {
            ans.y--;
            gotoxy(ans.x, ans.y);
        }
        else if (where == 72) // up
        {
            ans.x--;
            gotoxy(ans.x, ans.y);
        }
        else if (where == 80) // down
        {
            ans.x++;
            gotoxy(ans.x, ans.y);
        }
    }

    return ans;
}
// Also aiWallPlace() is in decision.h, among other computer gameplay functions

// putting fences
int putWall()
{
    // 2 player mode
    int contSw = 1;
    int x, y;

    if (determinePlayer()->isAi)
    {
        location where = aiWallPlace();
        x = where.x;
        y = where.y;
    }
    else
    {
        location where = userWallPlace();
        x = where.x;
        y = where.y;
    }

    // checking if the chosen place is accessible then place it
    // horizontal fences
    // ═ 205
    if (gameMode == 1)
    {
        if (x % 2 == 0 && y % 2 != 0)
        {
            if (y == 2 * column - 1 && Board[x][y] == -60 && Board[x][y - 1] == -59 && Board[x][y - 2] == -60)
            {
                makeSw();
                sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        Board[x][y] = Board[x][y - 1] = Board[x][y - 2] = 205;
                        contSw = 0;
                    }
                }
            }
            else if (Board[x][y] == -60 && Board[x][y + 1] == -59 && Board[x][y + 2] == -60)
            {
                makeSw();
                sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        Board[x][y] = Board[x][y + 1] = Board[x][y + 2] = 205;
                        contSw = 0;
                    }
                }
            }
        }
        // vertical fences
        //  ║ 186
        else if (y % 2 == 0 && x % 2 != 0)
        {
            if (x == 2 * row - 1 && Board[x][y] == -77 && Board[x - 2][y] == -77 && Board[x - 1][y] == -59)
            {
                makeSw();
                sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        Board[x][y] = Board[x - 1][y] = Board[x - 2][y] = 186;
                        contSw = 0;
                    }
                }
            }
            else if (Board[x][y] == -77 && Board[x + 2][y] == -77 && Board[x + 1][y] == -59)
            {
                makeSw();
                sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        Board[x][y] = Board[x + 1][y] = Board[x + 2][y] = 186;
                        contSw = 0;
                    }
                }
            }
        }
        if (contSw)
        {
            printf("\a");
            putWall();
        }
    }
    // 4 player mode
    else if (gameMode == 2)
    {

        // checking if the chosen place is accessible then place it
        // horizontal fences
        // ═ 205
        if (x % 2 == 0 && y % 2 != 0)
        {
            if (y == 2 * column - 1 && Board[x][y] == -60 && Board[x][y - 1] == -59 && Board[x][y - 2] == -60)
            {
                makeSw();
                sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        makeSw();
                        sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                        if (dfsLeft(sw, row, column, player3.location.x, player3.location.y))
                        {
                            makeSw();
                            sw[x][y] = sw[x][y - 1] = sw[x][y - 2] = 0;
                            if (dfsRight(sw, row, column, player4.location.x, player4.location.y))
                            {
                                Board[x][y] = Board[x][y - 1] = Board[x][y - 2] = 205;
                                contSw = 0;
                            }
                        }
                    }
                }
            }
            else if (Board[x][y] == -60 && Board[x][y + 1] == -59 && Board[x][y + 2] == -60)
            {
                makeSw();
                sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        makeSw();
                        sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                        if (dfsLeft(sw, row, column, player3.location.x, player3.location.y))
                        {
                            makeSw();
                            sw[x][y] = sw[x][y + 1] = sw[x][y + 2] = 0;
                            if (dfsRight(sw, row, column, player4.location.x, player4.location.y))
                            {
                                Board[x][y] = Board[x][y + 1] = Board[x][y + 2] = 205;
                                contSw = 0;
                            }
                        }
                    }
                }
            }
        }
        // vertical fences
        //  ║ 186
        else if (y % 2 == 0 && x % 2 != 0)
        {
            if (x == 2 * row - 1 && Board[x][y] == -77 && Board[x - 2][y] == -77 && Board[x - 1][y] == -59)
            {
                makeSw();
                sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        makeSw();
                        sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                        if (dfsLeft(sw, row, column, player3.location.x, player3.location.y))
                        {
                            makeSw();
                            sw[x][y] = sw[x - 1][y] = sw[x - 2][y] = 0;
                            if (dfsRight(sw, row, column, player4.location.x, player4.location.y))
                            {
                                Board[x][y] = Board[x - 1][y] = Board[x - 2][y] = 186;
                                contSw = 0;
                            }
                        }
                    }
                }
            }
            else if (Board[x][y] == -77 && Board[x + 2][y] == -77 && Board[x + 1][y] == -59)
            {
                makeSw();
                sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                if (dfsDown(sw, row, column, player1.location.x, player1.location.y))
                {
                    makeSw();
                    sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                    if (dfsUp(sw, row, column, player2.location.x, player2.location.y))
                    {
                        makeSw();
                        sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                        if (dfsLeft(sw, row, column, player3.location.x, player3.location.y))
                        {
                            makeSw();
                            sw[x][y] = sw[x + 1][y] = sw[x + 2][y] = 0;
                            if (dfsRight(sw, row, column, player4.location.x, player4.location.y))
                            {
                                Board[x][y] = Board[x + 1][y] = Board[x + 2][y] = 186;
                                contSw = 0;
                            }
                        }
                    }
                }
            }
        }

        if (contSw)
        {
            if (determinePlayer()->isAi)
                return 0;
            else
                putWall();
        }
    }

    return 1;
}

#endif