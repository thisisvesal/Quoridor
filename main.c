#include "tutorial.h"

int main()
{
    setTextColor(0, 15);
    clearScreen();

    // write welcome message
    printf("Welcome to Quoridor game!");
    setTextColor(6, 15);
    printf(" %c\n", 2);
    sleep(2000);

    while (newOrOld != 1 && newOrOld != 2)
    {
        clearScreen();

        setTextColor(0, 15);
        printf("1) Continue my old game\n");
        printf("2) Start a new game\n");
        printf("3) How to play\n");
        getNewOrOld();

        if (newOrOld == 1)
        {
            int openAGame = loadOldGame();
            if (!openAGame)
            {
                return 0;
            }
            else if (openAGame == 2)
            {
                newGame();
            }
        }
        else if (newOrOld == 2)
        {
            newGame();
        }
        else if (newOrOld == 3)
        {
            getTutorial();
        }
    }

    getchar();

    // The game loop:
    while (player1.location.x != 2 * row - 1 && player2.location.x != 1 && player3.location.y != 1 && player4.location.y != 2 * column - 1) // while nobody has won
    {
        printPage(determinePlayer());

        if (determinePlayer()->blockedFor > 0)
        {
            determinePlayer()->blockedFor--;
            turn += 1;
            if (gameMode == 1)
                turn %= 2;
            else if (gameMode == 2)
                turn %= 4;

            continue;
        }

        gameRun();
    }

    // The previous loop has ended
    // hence someone has won

    // Announcing the winner:
    winMessage();

    printf("Press any key to exit \n");
    getch();

    return 0;
}