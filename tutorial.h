#include "game.h"

#ifndef tutorial
#define tutorial

void printTutorialText()
{
    clearScreen();
    printf("In Quoridor, the goal is to get your pawn from one side\n");
    sleep(500*4);
    printf("to its opposite side of the board sooner than everyone else\n");
    setTextColor(15, 0);
    printf("Press ENTER to continue");
    setTextColor(0, 15);
    printf("\n");
    getchar();

    clearScreen();
    printf("Each round, you can either make a move towards your goal,\n");
    sleep(500*4);
    printf("Or place a wall so that your opponents can't pass through\n");
    setTextColor(15, 0);
    printf("Press ENTER to continue");
    setTextColor(0, 15);
    printf("\n");
    getchar();

    clearScreen();
    printf("In order to make a move,\n");
    sleep(250*4);
    printf("you should type m when prompted and hit ENTER,\n");
    sleep(300*4);
    printf("Then you can tell the game where you want to go\n");
    sleep(150*4);
    printf("using the arrow keys on your keyboard\n");
    setTextColor(15, 0);
    printf("Press ENTER to continue");
    setTextColor(0, 15);
    printf("\n");
    getchar();

    clearScreen();
    printf("To put a wall,\n");
    sleep(150*4);
    printf("type w when prompted and press enter just like before\n");
    sleep(500*4);
    printf("the game allows you to move the cursor using the arrow keys\n");
    sleep(300*4);
    printf("When you've gotten the cursor to the place you want to put a wall,\n");
    sleep(200*4);
    printf("press enter to tell the game this is the spot you're looking for\n");
    setTextColor(15, 0);
    printf("Press ENTER to continue");
    setTextColor(0, 15);
    printf("\n");
    getchar();

    clearScreen();
    printf("But beware,\n");
    sleep(500*4);
    printf("the unpredictable mystical energy of this game\n");
    sleep(200*4);
    printf("will not hesitate to charm, or even curse you...\n");
    sleep(500*4);
    printf("So, do you wish to try your luck with this magic?\n");
    sleep(500*4);
    printf("If you do, type L and press enter when prompted\n");
    printf("to see what luck brings on you\n");
    sleep(100*4);
    printf("Wish you all the charm and the least of curses in the world :]\n");
    setTextColor(15, 0);
    printf("Press ENTER to continue");
    setTextColor(0, 15);
    printf("\n");
    getchar();

    printf("Here, you can have a go\n");
    setTextColor(15, 0);
    printf("Press ENTER to continue");
    setTextColor(0, 15);
    printf("\n");
    getchar();
    clearScreen();
}

void getTutorial()
{
    printTutorialText();

    wallCount = 6;
    gameMode = 1;
    color = 7;
    aiSw = 1;
    row = column = 5;
    color = 0;

    makeBoard(row, column);
    strcpy(player1.name, "Player");
    player1.nameInitial = 'P';
    player1.isAi = 0;
    player1.charmNo = 1;
    player1.wallCount = wallCount;

    strcpy(player2.name, "Computer");
    player2.nameInitial = 'C';
    player2.isAi = 1;
    player2.charmNo = 1;
    player2.wallCount = wallCount;

    positionPlayers();

    // The game loop:
    while (player1.location.x != 2 * row - 1 && player2.location.x != 1) // while nobody has won
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

    winMessage();

    row = 0;
    column = 0;
    wallCount = 0;
    gameMode = 0;
    color = 0;
    aiSw = 0;
    turn = 0;
    newOrOld = 0;

    setTextColor(15, 0);
    printf("Press any key to continue");
    setTextColor(0, 15);
    printf("\n");
    getch();
    clearScreen();
}

#endif