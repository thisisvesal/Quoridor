#include "general.h"
#include <stdio.h>

int moveDecision()
{
    // right: 77
    // left: 75
    // up: 72
    // down: 80
    struct Player *someone = determinePlayer();

    if (someone == &player1)
    {
        if (Board[someone->location.x - 1][someone->location.y] != '$')
        {
            return 80;
        }
        else if (Board[someone->location.x][someone->location.y + 1] != '$')
        {
            return 77;
        }
        else if (Board[someone->location.x][someone->location.y - 1] != '$')
        {
            return 75;
        }
        else if (Board[someone->location.x + 1][someone->location.y] != '$')
        {
            return 72;
        }
    }
    else if (someone == &player2)
    {
        if (Board[someone->location.x + 1][someone->location.y] != '$')
        {
            return 72;
        }
        else if (Board[someone->location.x][someone->location.y + 1] != '$')
        {
            return 77;
        }
        else if (Board[someone->location.x][someone->location.y - 1] != '$')
        {
            return 75;
        }
        else if (Board[someone->location.x - 1][someone->location.y] != '$')
        {
            return 80;
        }
    }
    else if (someone == &player3)
    {
        if (Board[someone->location.x][someone->location.y - 1] != '$')
        {
            return 75;
        }
        else if (Board[someone->location.x + 1][someone->location.y] != '$')
        {
            return 72;
        }
        else if (Board[someone->location.x - 1][someone->location.y] != '$')
        {
            return 80;
        }
        else if (Board[someone->location.x][someone->location.y + 1] != '$')
        {
            return 77;
        }
    }
    else if (someone == &player4)
    {
        if (Board[someone->location.x][someone->location.y + 1] != '$')
        {
            return 77;
        }
        else if (Board[someone->location.x + 1][someone->location.y] != '$')
        {
            return 72;
        }
        else if (Board[someone->location.x - 1][someone->location.y] != '$')
        {
            return 80;
        }
        else if (Board[someone->location.x][someone->location.y - 1] != '$')
        {
            return 75;
        }
    }
    
}