#include "general.h"
#include <stdio.h>

#ifndef desicion
#define decision

typedef struct location
{
    int x, y;
} location;

// This function prioritizes putting walls over moving,
// on certain conditions
// if those conditions are not met,
// -1, -1 is returned, which indicates that we have to move
location aiWallPlace()
{
    location ans;
    ans.x = -1;
    ans.y = -1;
    int moveSw = 1;

    if (determinePlayer()->wallCount == 0)
        return ans;
    if (gameMode == 1)
    {
        if (round == 0)
        {
            if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                Board[player2.location.x - 1][player2.location.y + 2] == -60 &&
                Board[player2.location.x - 1][player2.location.y + 1] == -59)
            {
                // Board[player2.location.x - 1][player2.location.y] = -51;
                // Board[player2.location.x - 1][player2.location.y + 2] = -51;
                // Board[player2.location.x - 1][player2.location.y + 1] = -51;
                ans.x = player2.location.x - 1;
                ans.y = player2.location.y;
                moveSw = 0;
            }
            else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                     Board[player2.location.x - 1][player2.location.y - 2] == -60 &&
                     Board[player2.location.x - 1][player2.location.y - 1] == -59)
            {
                // Board[player2.location.x - 1][player2.location.y] = -51;
                // Board[player2.location.x - 1][player2.location.y - 2] = -51;
                // Board[player2.location.x - 1][player2.location.y - 1] = -51;
                ans.x = player2.location.x - 1;
                ans.y = player2.location.y - 2;
                moveSw = 0;
            }
        }
        else if (round == 1)
        {
            if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                Board[player1.location.x + 1][player1.location.y + 2] == -60 &&
                Board[player1.location.x + 1][player1.location.y + 1] == -59)
            {
                // Board[player1.location.x + 1][player1.location.y] = -51;
                // Board[player1.location.x + 1][player1.location.y + 2] = -51;
                // Board[player1.location.x + 1][player1.location.y + 1] = -51;
                ans.x = player1.location.x + 1;
                ans.y = player1.location.y;
                moveSw = 0;
            }
            else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                     Board[player1.location.x + 1][player1.location.y - 2] == -60 &&
                     Board[player1.location.x + 1][player1.location.y - 1] == -59)
            {
                // Board[player1.location.x + 1][player1.location.y] = -51;
                // Board[player1.location.x + 1][player1.location.y - 2] = -51;
                // Board[player1.location.x + 1][player1.location.y - 1] = -51;
                ans.x = player1.location.x + 1;
                ans.y = player1.location.y - 2;
                moveSw = 0;
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
                    // Board[player1.location.x + 1][player1.location.y] = -51;
                    // Board[player1.location.x + 1][player1.location.y + 2] = -51;
                    // Board[player1.location.x + 1][player1.location.y + 1] = -51;
                    ans.x = player1.location.x + 1;
                    ans.y = player1.location.y;
                    moveSw = 0;
                }
                else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 2] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 1] == -59)
                {
                    // Board[player1.location.x + 1][player1.location.y] = -51;
                    // Board[player1.location.x + 1][player1.location.y - 2] = -51;
                    // Board[player1.location.x + 1][player1.location.y - 1] = -51;
                    ans.x = player1.location.x + 1;
                    ans.y = player1.location.y - 2;
                    moveSw = 0;
                }
            }
            else if (min2Player == 2)
            {
                if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 2] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 1] == -59)
                {
                    // Board[player2.location.x - 1][player2.location.y] = -51;
                    // Board[player2.location.x - 1][player2.location.y + 2] = -51;
                    // Board[player2.location.x - 1][player2.location.y + 1] = -51;
                    ans.x = player2.location.x - 1;
                    ans.y = player2.location.y;
                }
                else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 2] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 1] == -59)
                {
                    // Board[player2.location.x - 1][player2.location.y] = -51;
                    // Board[player2.location.x - 1][player2.location.y - 2] = -51;
                    // Board[player2.location.x - 1][player2.location.y - 1] = -51;
                    ans.x = player2.location.x - 1;
                    ans.y = player2.location.y - 2;
                    moveSw = 0;
                }
            }
            else if (min2Player == 3)
            {
                if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 2][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 1][player3.location.y - 1] == -59)
                {
                    // Board[player3.location.x][player3.location.y - 1] = -70;
                    // Board[player3.location.x + 2][player3.location.y - 1] = -70;
                    // Board[player3.location.x + 1][player3.location.y - 1] = -70;
                    ans.x = player3.location.x;
                    ans.y = player3.location.y - 1;
                }
                else if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 2][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 1][player3.location.y - 1] == -59)
                {
                    // Board[player3.location.x][player3.location.y - 1] = -70;
                    // Board[player3.location.x - 2][player3.location.y - 1] = -70;
                    // Board[player3.location.x - 1][player3.location.y - 1] = -70;
                    ans.x = player3.location.x - 2;
                    ans.y = player3.location.y - 1;
                    moveSw = 0;
                }
            }
            else if (min2Player == 4)
            {
                if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 2][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 1][player4.location.y + 1] == -59)
                {
                    // Board[player4.location.x][player4.location.y + 1] = -70;
                    // Board[player4.location.x + 2][player4.location.y + 1] = -70;
                    // Board[player4.location.x + 1][player4.location.y + 1] = -70;
                    ans.x = player4.location.x;
                    ans.y = player4.location.y + 1;
                    moveSw = 0;
                }
                else if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 2][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 1][player4.location.y + 1] == -59)
                {
                    // Board[player4.location.x][player4.location.y + 1] = -70;
                    // Board[player4.location.x - 2][player4.location.y + 1] = -70;
                    // Board[player4.location.x - 1][player4.location.y + 1] = -70;
                    ans.x = player4.location.x - 2;
                    ans.y = player4.location.y + 1;
                    moveSw = 0;
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
                    // Board[player1.location.x + 1][player1.location.y] = -51;
                    // Board[player1.location.x + 1][player1.location.y + 2] = -51;
                    // Board[player1.location.x + 1][player1.location.y + 1] = -51;
                    ans.x = player1.location.x + 1;
                    ans.y = player1.location.y;
                    moveSw = 0;
                }
                else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 2] == -60 &&
                         Board[player1.location.x + 1][player1.location.y - 1] == -59)
                {
                    // Board[player1.location.x + 1][player1.location.y] = -51;
                    // Board[player1.location.x + 1][player1.location.y - 2] = -51;
                    // Board[player1.location.x + 1][player1.location.y - 1] = -51;
                    ans.x = player1.location.x + 1;
                    ans.y = player1.location.y - 2;
                    moveSw = 0;
                }
            }
            else if (minPlayer == 2)
            {
                if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 2] == -60 &&
                    Board[player2.location.x - 1][player2.location.y + 1] == -59)
                {
                    // Board[player2.location.x - 1][player2.location.y] = -51;
                    // Board[player2.location.x - 1][player2.location.y + 2] = -51;
                    // Board[player2.location.x - 1][player2.location.y + 1] = -51;
                    ans.x = player2.location.x - 1;
                    ans.y = player2.location.y;
                    moveSw = 0;
                }
                else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 2] == -60 &&
                         Board[player2.location.x - 1][player2.location.y - 1] == -59)
                {
                    // Board[player2.location.x - 1][player2.location.y] = -51;
                    // Board[player2.location.x - 1][player2.location.y - 2] = -51;
                    // Board[player2.location.x - 1][player2.location.y - 1] = -51;
                    ans.x = player2.location.x - 1;
                    ans.y = player2.location.y - 2;
                    moveSw = 0;
                }
            }
            else if (minPlayer == 3)
            {
                if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 2][player3.location.y - 1] == -77 &&
                    Board[player3.location.x + 1][player3.location.y - 1] == -59)
                {
                    // Board[player3.location.x][player3.location.y - 1] = -70;
                    // Board[player3.location.x + 2][player3.location.y - 1] = -70;
                    // Board[player3.location.x + 1][player3.location.y - 1] = -70;
                    ans.x = player3.location.x;
                    ans.y = player3.location.y - 1;
                    moveSw = 0;
                }
                else if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 2][player3.location.y - 1] == -77 &&
                         Board[player3.location.x - 1][player3.location.y - 1] == -59)
                {
                    // Board[player3.location.x][player3.location.y - 1] = -70;
                    // Board[player3.location.x - 2][player3.location.y - 1] = -70;
                    // Board[player3.location.x - 1][player3.location.y - 1] = -70;
                    ans.x = player3.location.x - 2;
                    ans.y = player3.location.y - 1;
                    moveSw = 0;
                }
            }
            else if (minPlayer == 4)
            {
                if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 2][player4.location.y + 1] == -77 &&
                    Board[player4.location.x + 1][player4.location.y + 1] == -59)
                {
                    // Board[player4.location.x][player4.location.y + 1] = -70;
                    // Board[player4.location.x + 2][player4.location.y + 1] = -70;
                    // Board[player4.location.x + 1][player4.location.y + 1] = -70;
                    ans.x = player4.location.x;
                    ans.y = player4.location.y + 1;
                    moveSw = 0;
                }
                else if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 2][player4.location.y + 1] == -77 &&
                         Board[player4.location.x - 1][player4.location.y + 1] == -59)
                {
                    // Board[player4.location.x][player4.location.y + 1] = -70;
                    // Board[player4.location.x - 2][player4.location.y + 1] = -70;
                    // Board[player4.location.x - 1][player4.location.y + 1] = -70;
                    ans.x = player4.location.x - 2;
                    ans.y = player4.location.y + 1;
                    moveSw = 0;
                }
            }
        }
    }

    return ans;
}

int isInBottom(struct Player *someone)
{
    if (someone->location.x == 2 * row - 1) return 1;
    else return 0;
}

int isInTop(struct Player *someone)
{
    if (someone->location.x == 1) return 1;
    else return 0;
}

int isOnRight(struct Player *someone)
{
    if (someone->location.y == 2 * column - 1) return 1;
    else return 0;
}

int isOnLeft(struct Player *someone)
{
    if (someone->location.y == 0) return 1;
    else return 0;
}

int isDownFree(struct Player *someone)
{
    if (isInBottom(someone)) return 0;
    else if (Board[someone->location.x + 1][someone->location.y] == -51) return 0;

    return 1;
}

int isUpFree(struct Player *someone)
{
    if (isInTop(someone)) return 0;
    else if (Board[someone->location.x - 1][someone->location.y] == -51) return 0;

    return 1;
}

int isRightFree(struct Player *someone)
{
    if (isOnRight(someone)) return 0;
    else if (Board[someone->location.x][someone->location.y + 1] == -70) return 0;

    return 1;
}

int isLeftFree(struct Player *someone)
{
    if (isOnRight(someone)) return 0;
    else if (Board[someone->location.x][someone->location.y - 1] == -70) return 0;

    return 1;
}

int moveDecision()
{
    // right: 77
    // left: 75
    // up: 72
    // down: 80
    struct Player *someone = determinePlayer();

    if (someone == &player1)
    {
        if (isDownFree(someone))
        {
            return 80;
        }
        else if (isRightFree(someone))
        {
            return 77;
        }
        else if (isLeftFree(someone))
        {
            return 75;
        }
        else if (isUpFree(someone))
        {
            return 72;
        }
    }
    else if (someone == &player2)
    {
        if (isUpFree(someone))
        {
            return 72;
        }
        else if (isRightFree(someone))
        {
            return 77;
        }
        else if (isLeftFree(someone))
        {
            return 75;
        }
        else if (isDownFree(someone))
        {
            return 80;
        }
    }
    else if (someone == &player3)
    {
        if (isLeftFree(someone))
        {
            return 75;
        }
        else if (isUpFree(someone))
        {
            return 72;
        }
        else if (isDownFree(someone))
        {
            return 80;
        }
        else if (isRightFree(someone))
        {
            return 77;
        }
    }
    else if (someone == &player4)
    {
        if (isRightFree(someone))
        {
            return 77;
        }
        else if (isUpFree(someone))
        {
            return 72;
        }
        else if (isDownFree(someone))
        {
            return 80;
        }
        else if (isLeftFree(someone))
        {
            return 75;
        }
    }
    
}

#endif