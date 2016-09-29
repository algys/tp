/*___________________________________________________________________________
Автор: Иевлев А.А. студент АПО-13

Задача 7_2:
В большой IT­фирме есть только одна переговорная комната. 
Желающие посовещаться заполняют заявки с желаемым временем начала и конца. 
Ваша задача определить максимальное количество заявок, 
которое может быть удовлетворено.
Число заявок ≤ 100000.
_____________________________________________________________________________
Формат входных данных.
Вход содержит только пары целых чисел — начала и концы заявок.

Формат выходных данных.
Выход должен содержать натуральное число — максимальное число заявок.
___________________________________________________________________________*/


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
    p *a = new p[200000];
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
    
    delete [] a;

    return 0;

}

