#include "general.h"

#ifndef desicion
#define decision

// Indicates the number of wall placement attempts
// aiWallTry is reset in every call of gameRun()
int aiWallTry = 0;

int distanceOf(struct Player *someone)
{
    if (someone == &player1)
    {
        return 2 * row - player1.location.x - 1;
    }
    else if (someone == &player2)
    {
        return player2.location.x - 1;
    }
    else if (someone == &player3)
    {
        return player3.location.y - 1;
    }
    else if (someone == &player4)
    {
        return 2 * column - player4.location.y - 1;
    }
}

struct Player *minDistancePerson()
{
    struct Player *ans;

    int min = 200;
    if (distanceOf(&player1) < min)
    {
        min = distanceOf(&player1);
        ans = &player1;
    }
    if (distanceOf(&player2) < min)
    {
        min = distanceOf(&player2);
        ans = &player2;
    }
    if (gameMode == 2)
    {
        if (distanceOf(&player3) < min)
        {
            min = distanceOf(&player3);
            ans = &player3;
        }
        if (distanceOf(&player4) < min)
        {
            min = distanceOf(&player4);
            ans = &player4;
        }
    }

    return ans;
}

int isFrontWallFree(struct Player *someone)
{
    if (someone == &player1)
    {
        if (Board[player1.location.x + 1][player1.location.y] == -60 &&
            Board[player1.location.x + 1][player1.location.y + 1] == -59 &&
            Board[player1.location.x + 1][player1.location.y + 2] == -60)
        {
            return 1;
        }
        else if (Board[player1.location.x + 1][player1.location.y] == -60 &&
                Board[player1.location.x + 1][player1.location.y - 1] == -59 &&
                 Board[player1.location.x + 1][player1.location.y - 2] == -60)
        {
            return 2;
        }
    }
    else if (someone == &player2)
    {
        if (Board[player2.location.x - 1][player2.location.y] == -60 &&
            Board[player2.location.x - 1][player2.location.y + 1] == -59 &&
            Board[player2.location.x - 1][player2.location.y + 2] == -60)
        {
            return 1;
        }
        else if (Board[player2.location.x - 1][player2.location.y] == -60 &&
                Board[player2.location.x - 1][player2.location.y - 1] == -60 &&
                 Board[player2.location.x - 1][player2.location.y - 2] == -60)
        {
            return 2;
        }
    }
    else if (someone == &player3)
    {
        if (Board[player3.location.x][player3.location.y - 1] == -77 &&
            Board[player3.location.x + 1][player3.location.y - 1] == -59 &&
            Board[player3.location.x + 2][player3.location.y - 1] == -77)
        {
            return 1;
        }
        else if (Board[player3.location.x][player3.location.y - 1] == -77 &&
                Board[player3.location.x - 1][player3.location.y - 1] == -59 &&
                 Board[player3.location.x - 2][player3.location.y - 1] == -77)
        {
            return 2;
        }
    }
    else if (someone == &player4)
    {
        if (Board[player4.location.x][player4.location.y + 1] == -77 &&
            Board[player4.location.x + 1][player4.location.y + 1] == -59 &&
            Board[player4.location.x + 2][player4.location.y + 1] == -77)
        {
            return 1;
        }
        else if (Board[player4.location.x][player4.location.y + 1] == -77 &&
                Board[player4.location.x - 1][player4.location.y + 1] == -59 &&
                 Board[player4.location.x - 2][player4.location.y + 1] == -77)
        {
            return 2;
        }
    }

    return 0;
}

location frontRightWall(struct Player *someone)
{
    location ans;
    if (someone == &player1)
    {
        ans.x = player1.location.x + 1;
        ans.y = player1.location.y;
        return ans;
    }
    if (someone == &player2)
    {
        ans.x = player2.location.x - 1;
        ans.y = player2.location.y;
        return ans;
    }
    if (someone == &player3)
    {
        ans.x = player3.location.x;
        ans.y = player3.location.y - 1;
        return ans;
    }
    if (someone == &player4)
    {
        ans.x = player4.location.x;
        ans.y = player4.location.y + 1;
        return ans;
    }
}

location frontLeftWall(struct Player *someone)
{
    location ans;
    if (someone == &player1)
    {
        ans.x = player1.location.x + 1;
        ans.y = player1.location.y - 2;
        return ans;
    }
    if (someone == &player2)
    {
        ans.x = player2.location.x - 1;
        ans.y = player2.location.y - 2;
        return ans;
    }
    if (someone == &player3)
    {
        ans.x = player3.location.x - 2;
        ans.y = player3.location.y - 1;
        return ans;
    }
    if (someone == &player4)
    {
        ans.x = player4.location.x - 2;
        ans.y = player4.location.y + 1;
        return ans;
    }
}


// This function decides whether the computer should move or place a wall
// It prioritizes putting walls over moving,
// using certain conditions
// If those conditions are not met,
// -1, -1 is returned, which indicates that we have to move
location aiWallPlace()
{
    location ans;
    ans.x = -1;
    ans.y = -1;

    struct Player *someone = determinePlayer();
    struct Player *closePLayer = minDistancePerson();

    if (someone->wallCount == 0)
    {
        return ans;
    }
    if (someone == closePLayer)
    {
        return ans;
    }
    if (aiWallTry > 2)
    {
        return ans;
    }

    if (!isFrontWallFree(closePLayer))
    {
        return ans;
    }
    else if (isFrontWallFree(closePLayer) == 2)
    {
        aiWallTry++;
        ans = frontLeftWall(closePLayer);
        return ans;
    }
    else if (isFrontWallFree(closePLayer) == 1)
    {
        aiWallTry++;
        ans = frontRightWall(closePLayer);
        return ans;
    }
}


int isInBottom(struct Player *someone)
{
    if (someone->location.x == 2 * row - 1)
        return 1;
    else
        return 0;
}

int isInTop(struct Player *someone)
{
    if (someone->location.x == 1)
        return 1;
    else
        return 0;
}

int isOnRight(struct Player *someone)
{
    if (someone->location.y == 2 * column - 1)
        return 1;
    else
        return 0;
}

int isOnLeft(struct Player *someone)
{
    if (someone->location.y == 1)
        return 1;
    else
        return 0;
}


int isDownFree(struct Player *someone)
{
    if (isInBottom(someone))
        return 0;
    if (Board[someone->location.x + 1][someone->location.y] == -51)
        return 0;
    if (Board[someone->location.x + 2][someone->location.y] != ' ')
        return 0;

    return 1;
}

int isUpFree(struct Player *someone)
{
    if (isInTop(someone))
        return 0;
    if (Board[someone->location.x - 1][someone->location.y] == -51)
        return 0;
    if (Board[someone->location.x - 2][someone->location.y] != ' ')
        return 0;

    return 1;
}

int isRightFree(struct Player *someone)
{
    if (isOnRight(someone))
        return 0;
    if (Board[someone->location.x][someone->location.y + 1] == -70)
        return 0;
    if (Board[someone->location.x][someone->location.y + 2] != ' ')
        return 0;

    return 1;
}

int isLeftFree(struct Player *someone)
{
    if (isOnLeft(someone))
        return 0;
    if (Board[someone->location.x][someone->location.y - 1] == -70)
        return 0;
    if (Board[someone->location.x][someone->location.y - 2] != ' ')
        return 0;

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