#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "general.h"

#ifndef random
#define random

int randomize(int lower, int upper)
{
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}

#endif