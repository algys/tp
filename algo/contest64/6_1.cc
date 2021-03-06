/*___________________________________________________________________________
Автор: Иевлев А.А. студент АПО-13

Задача 6_1:
Дано N кубиков. Требуется определить каким количеством способов можно 
выстроить из этих кубиков пирамиду.
_____________________________________________________________________________
Формат входных данных.
На вход подается количество кубиков N.

Формат выходных данных.
Вывести число различных пирамид из N кубиков.
___________________________________________________________________________*/


#include <stdio.h>
#include <algorithm>

int main(){
    long long b[201][201], a[201][201];
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
    
    return 0;
}
