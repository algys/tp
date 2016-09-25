#include <stdio.h>

int t_search(int *a, int n){
   int l = 0, r = n-1;
   while(r-l > 2){
      int m1 = l+(r-l)/3,
          m2 = r-(r-l)/3;
      if(a[m1]<a[m2])
         l = m1;
      else
         r = m2;
   }
   if(a[l]>a[r-1])
     return l;
   else
   if(a[r-1]>a[r])
     return r-1;
   else
     return r;
}

int main(){
   int a[100000], n, m;

   scanf("%i", &n);
   for(int i=0; i<n; i++)
     scanf("%i", &a[i]);

   m = t_search(a,n);

   printf("%i", m);

   return 0;
}
