#include <stdio.h>

#ifndef board
#define board

char Board[101][101];
extern int thisIsATest = 5;

 void boardMake(int n,int m) {

    for (int i = 0; i < 2*n+1; i++) {
        for (int j = 0; j < 2*m+1; j++) {
            //╔
            if(i==0 & j==0) Board[i][j]=201;
                //╗
            else if (i==0 & j==2*m )Board[i][j]=187;
                //╚
            else if (i==2*n & j==0)Board[i][j]=200;
                //╝
            else if( i==2*n & j==2*m )Board[i][j]=188;
                //╩
            else if( i==2*n & j!=0 & j!=2*m & j%2==0 )Board[i][j]=202;
                //╦
            else if( i==0& j!=0 & j!=2*m &j%2==0 )Board[i][j]=203;
                //═
            else if(i % 2 == 0 & j%2!=0)Board[i][j] =205 ;
                //║
            else if (j % 2 == 0 & i%2 != 0) Board[i][j] = 186 ;
                //╠
            else if (j == 0 & i%2==0 & i!=0 & i!=2*n ) Board[i][j] =204 ;
                //╠
            else if(j == 2*m & i%2==0 & i!=0 & i!=2*n ) Board[i][j] =185 ;
                //╬
            else if (i%2==0 & i!=0 & i!=2*n & j!=0 & j!=2*m) Board[i][j] =206 ;
                // جایگاه مهره ها
            else Board[i][j] = ' ';
        }
    }
}

#endif