#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ERR(x) printf(x);

int isprime(long long n){
    long long i;
    for(i=2; i*i<=n; i++){
        if(n%i==0) return(0);
    }
    return(1);
}

long long* factorize(long long n){
    if(n <= 0) return(NULL);
    long long *a = NULL;
    long long k = 0;
    long long i, t = n;

    if((a = (long long*)malloc(150*sizeof(long long))) == NULL)
        return(NULL);
    for(i=0; i<150; i++) a[i]=0;

    a[k++]=1;
    i = 2;

    while(t/n<n){
       if(isprime(i)){
          while(n%i==0){
             a[k++]=i;
             n/=i;
          }
       }
       i++;
    }

    if(n>1) a[k++]=n;

    return a;
}

int main(){
    long long n = 0;
    long long *a = NULL, *p = NULL;
    int i;
    char s[100];

    fgets(s,99,stdin);

    for(i=0; i<strlen(s); i++)
    if(isalpha(s[i])) {
       ERR("[error]");
       return(0);
    }

    if(sscanf(s,"%lld",&n)!=1||n<=0){
//     printf("%lld",n);
       ERR("[error]");
       return(0);
    }

    if((a = factorize(n))==NULL){
       ERR("[error]");
       return(0);
    }

    for(p=a; *p!=0; p++){
        printf("%lld ", *p);
    }

    free(a);

    return(0);
}

