# include <stdio.h>

char moveType(char moveChar)
{
    if (moveChar == 'w' || moveChar == 'W') return 'w';
    else if (moveChar == 'm' || moveChar == 'M') return 'm';
    else moveType(moveChar);
}

// roundvoid 