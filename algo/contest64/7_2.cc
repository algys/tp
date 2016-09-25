#include <stdio.h>
#include <stdlib.h>

struct p{
    int a;
    int b;
};

int cmp(const void *a, const void *b){
    p aa = *(p*)a;
    p bb = *(p*)b;
    return aa.b-bb.b;
}


int main(){
    p a[200000];
    int max_id = -1, max = 0, n = 0;
     
    while(scanf("%i%i",&(a[n].a), &(a[n].b))==2){
        n++;
    }
    
    qsort(a,n,sizeof(p),cmp);

    for(int i=0; i<n; i++){
        if(max_id == -1 || a[max_id].b <= a[i].a){
            max++;
            max_id = i;
        }
    }

    printf("%i\n",max);
    
    return 0;

}

