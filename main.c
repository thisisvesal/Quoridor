#include"board.h"
#include"boardPrinter.h"

// extern int thisIsATest;
int main() {
    int row,column;
    scanf("%d %d",& row,&column);
    boardMake(row,column);
    //مختصات مهره اول
    int x1,y1;
    x1--;
    y1--;
    scanf("%d%d",&x1,&y1);
    Board[2*x1][2*y1]=83;
    //مختصات مهره دوم
    int x2,y2;
    scanf("%d%d",&x2,&y2);
    x2--;
    y2--;
    Board[2*x2][2*y2]=86;
    //تعداد دیوار بازیکن اول
    int wallCount1;
    scanf("%d",&wallCount1);
    // مختصات دیوار بازیکن اول
    for(int i=0;i<wallCount1;i++) {
        int wx1, wy1;
        char w1;
        scanf("%d%d%c", &wx1, &wy1, &w1);
        if(w1==72){
            Board[2*wx1+1][2*wy1]=178;
            Board[2*wx1+1][2*wy1+1]=178;
            Board[2*wx1+1][2*wy1+2]=178;
        }
        else {
            Board[2*wx1][2*wy1+1]=178;
            Board[2*wx1+1][2*wy1+1]=178;
            Board[2*wx1+2][2*wy1+1]=178;
        }
    }
    //تعداد دیوار بازیکن دوم
    int wallCount2;
    scanf("%d",&wallCount2);
    //مختصات دیوار بازیکن دوم
    for(int i=0;i<wallCount2;i++) {
        int wx2, wy2;
        char w2;
        scanf("%d%d%c", &wx2, &wy2, &w2);
        if(w2==72){
            Board[2*wx2+1][2*wy2]=178;
            Board[2*wx2+1][2*wy2+1]=178;
            Board[2*wx2+1][2*wy2+2]=178;
        }
        else {
            Board[2*wx2][2*wy2+1]=178;
            Board[2*wx2+1][2*wy2+1]=178;
            Board[2*wx2+2][2*wy2+1]=178;
        }
        }
    printBoard (Board,row,column);
    printf("%d", thisIsATest);
    return 0;
}