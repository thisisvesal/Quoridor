# include <stdio.h>

#ifdef rounds
#define rounds
char moveType(char moveChar)
{
    if (moveChar == 'w' || moveChar == 'W') return 'w';
    else if (moveChar == 'm' || moveChar == 'M') return 'm';
    else moveType(moveChar);
}

#endif

// roundvoid 