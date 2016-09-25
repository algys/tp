#include <stdio.h>

int main(){
   int x,step=3,sqr=1;
   scanf("%i",&x);

   for(int i=0; i<x; step+=2,i++){
	printf("%i ",sqr);
   	sqr+=step;
   }

   return 0;
}

