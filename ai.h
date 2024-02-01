#include "motion.h"
#include "boardMaker.h"

#ifndef ai
#define ai

void aiPutWall()
{
    if (gameMode == 1)
    {
        if (round == 0)
        {
            if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                Board[player2.location.x - 1][player2.location.y + 2] == -60 &&
                Board[player2.location.x - 1][player2.location.y + 1] == -59)
            {
                Board[player2.location.x - 1][player2.location.y] = -51;
                Board[player2.location.x - 1][player2.location.y + 2] = -51;
                Board[player2.location.x - 1][player2.location.y + 1] = -51;
            }
            else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                     Board[player2.location.x - 1][player2.location.y - 2] == -60 &&
                     Board[player2.location.x - 1][player2.location.y - 1] == -59)
            {
                Board[player2.location.x - 1][player2.location.y] = -51;
                Board[player2.location.x - 1][player2.location.y - 2] = -51;
                Board[player2.location.x - 1][player2.location.y - 1] = -51;
            }
        }
        else if (round == 1)
        {
            if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                Board[player1.location.x + 1][player1.location.y + 2] == -60 &&
                Board[player1.location.x + 1][player1.location.y + 1] == -59)
            {
                Board[player1.location.x + 1][player1.location.y] = -51;
                Board[player1.location.x + 1][player1.location.y + 2] = -51;
                Board[player1.location.x + 1][player1.location.y + 1] = -51;
            }
            else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                     Board[player1.location.x + 1][player1.location.y - 2] == -60 &&
                     Board[player1.location.x + 1][player1.location.y - 1] == -59)
            {
                Board[player1.location.x + 1][player1.location.y] = -51;
                Board[player1.location.x + 1][player1.location.y - 2] = -51;
                Board[player1.location.x + 1][player1.location.y - 1] = -51;
            }
        }
    }
    else if (gameMode == 2)
    {
        int min = 102;
        int min2 = 200;
        int minPlayer = 0;
        int min2Player = 0;

        if ((player2.location.x) < min)
        {
            min = player2.location.x;
            minPlayer = 2;
        }
        if (2 * column - (player4.location.y) < min)
        {
            min2Player = minPlayer;
            min = 2 * column - (player4.location.y);
            minPlayer = 4;
        }
        else if (2 * column - (player4.location.y) < min2)
        {
            min2Player = 4;
            min2 = 2 * column - (player4.location.y);
        }
        if (player3.location.y < min)
        {
            min2Player = minPlayer;
            min = player3.location.y;
            minPlayer = 3;
        }
        else if (player3.location.y < min2)
        {
            min2Player = 3;
            min2 = player3.location.y;
        }
        if (2 * row - (player1.location.x) < min)
        {
            min2Player = minPlayer;
            min = player1.location.x;
            minPlayer = 1;
        }
        else if (2 * row - (player1.location.x) < min2)
        {
            min2Player = 1;
            min2 = player1.location.x;
        }

        if ((round == 0 && minPlayer == 1) || (round == 1 && minPlayer == 3) || (round == 2 && minPlayer == 2) || (round == 3 && minPlayer == 3))
        {
            if (min2Player == 1)
            {
                if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                    Board[player1.location.x + 1][player1.location.y + 2] == -60 &&
                    Board[player1.location.x + 1][player1.location.y + 1] == -59)
                {
                    Board[player1.location.x + 1][player1.location.y] = -51;
                    Board[player1.location.x + 1][player1.location.y + 2] = -51;
                    Board[player1.location.x + 1][player1.location.y + 1] = -51;
                }
                else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 2] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 1] == -59)
                {
                    Board[player1.location.x + 1][player1.location.y] = -51;
                    Board[player1.location.x + 1][player1.location.y - 2] = -51;
                    Board[player1.location.x + 1][player1.location.y - 1] = -51;
                }
            }
            else if (min2Player == 2)
            {
                if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 2] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 1] == -59)
                {
                    Board[player2.location.x - 1][player2.location.y] = -51;
                    Board[player2.location.x - 1][player2.location.y + 2] = -51;
                    Board[player2.location.x - 1][player2.location.y + 1] = -51;
                }
                else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 2] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 1] == -59)
                {
                    Board[player2.location.x - 1][player2.location.y] = -51;
                    Board[player2.location.x - 1][player2.location.y - 2] = -51;
                    Board[player2.location.x - 1][player2.location.y - 1] = -51;
                }
            }
            else if (min2Player == 3)
            {
                if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 2][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 1][player3.location.y - 1] == -59)
                {
                    Board[player3.location.x][player3.location.y - 1] = -70;
                    Board[player3.location.x + 2][player3.location.y - 1] = -70;
                    Board[player3.location.x + 1][player3.location.y - 1] = -70;
                }
                else if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 2][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 1][player3.location.y - 1] == -59)
                {
                    Board[player3.location.x][player3.location.y - 1] = -70;
                    Board[player3.location.x - 2][player3.location.y - 1] = -70;
                    Board[player3.location.x - 1][player3.location.y - 1] = -70;
                }
            }
            else if (min2Player == 4)
            {
                if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 2][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 1][player4.location.y + 1] == -59)
                {
                    Board[player4.location.x][player4.location.y + 1] = -70;
                    Board[player4.location.x + 2][player4.location.y + 1] = -70;
                    Board[player4.location.x + 1][player4.location.y + 1] = -70;
                }
                else if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 2][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 1][player4.location.y + 1] == -59)
                {
                    Board[player4.location.x][player4.location.y + 1] = -70;
                    Board[player4.location.x - 2][player4.location.y + 1] = -70;
                    Board[player4.location.x - 1][player4.location.y + 1] = -70;
                }
            }
        }
        else
        {
            if (minPlayer == 1)
            {
                if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                    Board[player1.location.x + 1][player1.location.y + 2] == -60 &&
                    Board[player1.location.x + 1][player1.location.y + 1] == -59)
                {
                    Board[player1.location.x + 1][player1.location.y] = -51;
                    Board[player1.location.x + 1][player1.location.y + 2] = -51;
                    Board[player1.location.x + 1][player1.location.y + 1] = -51;
                }
                else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 2] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 1] == -59)
                {
                    Board[player1.location.x + 1][player1.location.y] = -51;
                    Board[player1.location.x + 1][player1.location.y - 2] = -51;
                    Board[player1.location.x + 1][player1.location.y - 1] = -51;
                }
            }
            else if (minPlayer == 2)
            {
                if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 2] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 1] == -59)
                {
                    Board[player2.location.x - 1][player2.location.y] = -51;
                    Board[player2.location.x - 1][player2.location.y + 2] = -51;
                    Board[player2.location.x - 1][player2.location.y + 1] = -51;
                }
                else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 2] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 1] == -59)
                {
                    Board[player2.location.x - 1][player2.location.y] = -51;
                    Board[player2.location.x - 1][player2.location.y - 2] = -51;
                    Board[player2.location.x - 1][player2.location.y - 1] = -51;
                }
            }
            else if (minPlayer == 3)
            {
                if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 2][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 1][player3.location.y - 1] == -59)
                {
                    Board[player3.location.x][player3.location.y - 1] = -70;
                    Board[player3.location.x + 2][player3.location.y - 1] = -70;
                    Board[player3.location.x + 1][player3.location.y - 1] = -70;
                }
                else if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 2][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 1][player3.location.y - 1] == -59)
                {
                    Board[player3.location.x][player3.location.y - 1] = -70;
                    Board[player3.location.x - 2][player3.location.y - 1] = -70;
                    Board[player3.location.x - 1][player3.location.y - 1] = -70;
                }
            }
            else if (minPlayer == 4)
            {
                if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 2][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 1][player4.location.y + 1] == -59)
                {
                    Board[player4.location.x][player4.location.y + 1] = -70;
                    Board[player4.location.x + 2][player4.location.y + 1] = -70;
                    Board[player4.location.x + 1][player4.location.y + 1] = -70;
                }
                else if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 2][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 1][player4.location.y + 1] == -59)
                {
                    Board[player4.location.x][player4.location.y + 1] = -70;
                    Board[player4.location.x - 2][player4.location.y + 1] = -70;
                    Board[player4.location.x - 1][player4.location.y + 1] = -70;
                }
            }
        }
    }
}

#endif
