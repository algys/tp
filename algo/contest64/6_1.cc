#include <stdio.h>
#include <algorithm>

int main(){
    long long a[501][501], b[501][501];
    int n, ans = 0;

    scanf("%i", &n);

    b[0][0]=1;
    b[2][2]=2;
    for(int i=1; i<=n; i++){
        a[i][i]=1;
        a[i][1]=1;
        b[i][1]=1;
    }

    for(int i=3; i<=n; i++)
    for(int j=2; j<=i; j++){
        a[i][j]=b[i-j][std::min(j,i-j)];
        b[i][j]=b[i][j-1] + a[i][j];
    }

    printf("%lld\n",b[n][n]);
/*
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            printf("%i ",a[i][j]);
        printf("\n");
    }
 
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            printf("%i ",b[i][j]);
        printf("\n");
    }
    */
    return 0;
}
