#include <stdio.h>

int main() {
    int z,m,n,i,j,k;
    scanf("%d %d",&m,&n);
    scanf("%d",&k);
    int a[m][n];
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            a[i][j]=0;
    for(z=1;z<=k;z++){
        int x,y;
        scanf("%d %d", &x, &y);
        a[x - 1][y - 1] = 42;
    }
    for(i=0;i<m;i++){
        for(j=0;j<n ;j++){
            if(a[i][j]==42) {
                if (i - 1 >= 0) { if (a[i - 1][j] != 42) a[i - 1][j]++;}
                if (j - 1 >= 0) { if (a[i][j - 1] != 42) a[i][j - 1]++;}
                if (i + 1 < m) { if (a[i + 1][j] != 42) a[i + 1][j]++;}
                if (j + 1 < n) { if (a[i][j + 1] != 42) a[i][j + 1]++;}
                if ((i - 1) >=0 & (j - 1) >= 0) { if (a[i - 1][j - 1] != 42) a[i - 1][j - 1]++;}
                if (i + 1 < m && j + 1 < n) { if (a[i + 1][j + 1] != 42)a[i + 1][j + 1]++;}
                if (i + 1 <m && j - 1 >= 0) { if (a[i + 1][j - 1] != 42)a[i + 1][j - 1]++;}
                if (i - 1 >= 0 && j + 1 < n) { if (a[i - 1][j + 1] != 42)a[i - 1][j + 1]++;}
            }
        }
    }
    for(i=0;i<m;i++){
        for(j=0;j<n ;j++){
            if(a[i][j]!=42)printf("%d ",a[i][j]);
            else printf("* ");
        }
        printf("\n");
    }
    return 0;
}
