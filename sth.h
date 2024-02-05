#include <stdio.h>

int getValidInt(int input, int start, int end)
{
    input = 0;
    while (!(start <= input || input <= end))
    {
        char inputCopy[30];
        gets(inputCopy);

        for (int i = 0; inputCopy[i] && '0' <= inputCopy[i] && inputCopy[i] <= '9'; i++)
        {
            input += (inputCopy[i] - 48);
            input *= 10;
        }
        input /= 10;
        if (!(start <= input || input <= end))
            printf("Please enter a valid number\n");
    }
}