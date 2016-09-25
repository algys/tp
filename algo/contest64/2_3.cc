#include <stdio.h>

int main(){
   int a[100000], b[100000], n, m, sum, k=0;

   scanf("%i", &n);
   for(int i=0; i<n; i++)
      scanf("%i", &a[i]);

   scanf("%i", &m);
   for(int i=0; i<m; i++)
      scanf("%i", &b[i]);

   scanf("%i", &sum);

   int i=0, j=m-1;
   while(i<n && j>=0){
      if(sum-b[j]==a[i]) k++;
      if(sum-b[j]>=a[i]) i++; else
      j--;
   }

   printf("%i", k);
   return 0;
}
