#include "random.h"
#include "design.h"

#ifndef charms
#define charms

// This prevents applying a charm after the user saves the game
int charmSw = 1;

void addWalls(struct Player *someone)
{
    int num = randomize(2, 4);
    if (num == 4)
        num = 5;

    printf("congrats %s, you get %d extra walls\n", someone->name, num);
    
    if (!someone->isAi) getch();
    else sleep(1500);


    someone->wallCount += num;

    printPage(someone);
    // printf("%s's turn\n", someone->name);
}

int loseWalls(struct Player *someone)
{
    int num = randomize(2, 4);
    if (num == 4)
        num = 5;

    if (someone->wallCount < num)
        return 0;

    printf("sorry %s, you lose %d walls\n", someone->name, num);
    
    if (!someone->isAi) getch();
    else sleep(1500);


    someone->wallCount -= num;

    printPage(someone);
    // printf("%s's turn\n", someone->name);

    return 1;
}

int gainFromLoss(struct Player *gainer)
{
    struct Player *loser;

    if (gameMode == 2)
    {
        struct Player players[4] = {player1, player2, player3, player4};
        if (turn == 0)
        {
            for (size_t i = 0; i < 3; i++)
            {
                players[i] = players[i + 1];
            }
        }
        else if (turn == 1)
        {
            for (size_t i = 2; i < 3; i++)
            {
                players[i] = players[i + 1];
            }
        }
        else if (turn == 2)
        {
            for (size_t i = 1; i < 3; i++)
            {
                players[i] = players[i + 1];
            }
        }

        loser = &players[randomize(0, 2)];
    }
    else
    {
        if (turn == 0)
        {
            loser = &player2;
        }
        else if (turn == 1)
        {
            loser = &player1;
        }
    }

    int num = randomize(1, 2);
    if (loser->wallCount < num)
        return 0;

    printf("%s, you will take %d of %s's walls :]", gainer->name, num, loser->name);
    
    if (!gainer->isAi) getch();
    else sleep(1500);

    gainer->wallCount += num;
    loser->wallCount -= num;

    printPage(gainer);
    // printf("%s's turn\n", gainer->name);

    return 1;
}

void removeAllWalls()
{
    printf("..Removing every wall on the board..\n");
    
    if (!determinePlayer()->isAi) getch();
    else sleep(1500);

    for (int i = 0; i < 2 * row + 1; i++)
    {
        for (int j = 0; j < 2 * column + 1; j++)
        {
            if (Board[i][j] == -51)
            {
                if (j % 2 == 0 && i % 2 == 1)
                    Board[i][j] = -60;
                else
                    Board[i][j] = -59;
            }
            else if (Board[i][j] == -70)
            {
                if (i % 2 == 1 && j % 2 == 0)
                    Board[i][j] = -77;
                else
                    Board[i][j] = -59;
            }
        }
    }
}

int blockRound(struct Player *someone)
{
    struct Player players[4] = {player1, player2, player3, player4};
    if (turn == 0)
    {
        for (size_t i = 0; i < 3; i++)
        {
            players[i] = players[i + 1];
        }
    }
    else if (turn == 1)
    {
        for (size_t i = 2; i < 3; i++)
        {
            players[i] = players[i + 1];
        }
    }
    else if (turn == 2)
    {
        for (size_t i = 1; i < 3; i++)
        {
            players[i] = players[i + 1];
        }
    }

    int freeCount = 0;
    for (size_t i = 0; i < 3; i++)
    {
        if (players[i].blockedFor == 0)
            freeCount++;
    }

    if (freeCount == 0)
        return 0;

    int block = randomize(1, 2);
    someone->blockedFor += block;

    printf("%s, sadly you can't play for %d rounds!\n", someone->name, block);
    
    if (!someone->isAi) getch();
    else sleep(1500);

    printPage(someone);

    return 1;
}

void getCharm()
{
    struct Player *someone = determinePlayer();
    if (someone->blockedFor != 0)
        return;

    /*
        if (!someone->isAi)
        {
            printf("\nPress a key to see your luck!\n");
            
            if (!someone->isAi) getch();
            else sleep(1500);

        }
    */

    if (someone->isAi)
    {
        printf("%s gets a charm this round\n", someone->name);
        sleep(750);
    }

    if (randomize(0, 1))
    {
        int getRandom = randomize(0, 1);
        if (getRandom == 0)
        {
            addWalls(someone);
        }
        else if (getRandom == 1)
        {
            if (gainFromLoss(someone))
                ;
            else
                addWalls(someone);
        }
    }
    else
    {
        int getRandom = randomize(0, 4);
        if (getRandom == 0 || getRandom == 1)
        {
            if (loseWalls(someone))
                ;
            else if (blockRound(someone))
                ;
            else
                removeAllWalls();
        }
        else if (getRandom == 2 || getRandom == 3)
        {
            if (blockRound(someone))
                ;
            else
                removeAllWalls();
        }
        else if (getRandom == 4)
        {
            removeAllWalls();
        }
    }
}

#endif
