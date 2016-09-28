#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


long long hash(char *s){
    const int p = 31;
    long long h = 0, p_pow = 1;
    for (size_t i=0; i<strlen(s); ++i)
    {
        h += (s[i] - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    return h;
}

void delspace(char *s){
    size_t i, new_len, len = strlen(s), k=0;
    new_len = len;
    for(i=0; i<len; i++){
        if(s[i]=' ') k++; else 
            s[i-k]=s[i]; 
    }
    s[new_len]='\0';
}

int count_upper(char *s){
    size_t i, len = strlen(s), k=0;
    for(i=0; i<len; i++){
        if(isupper(s[i])) k++;
    }
    return k;
}

int strcmpp(char *s1, size_t begin, size_t end, char *s2){
    size_t i;
    if(strlen(s2)!=end-begin+1) 
        return 0;
    
    for(i=0; i<end+1; i++){
        if(s1[begin+i]!=s2[i]) 
            return 0;
    }
    return 1;
}

int check_type(char *s){
    size_t i, k, len = strlen(s);
    int f1 = 0, f2 = 0;
    if(count_upper(s)==1){
        if(len>6 && strcmp(s+len-6,"=True;")) f1=1; 
        if(len>7 && strcmp(s+len-7,"=False;")) f1=2;
        if(strcmpp(s, 0, len-7, "or")||strcmpp(s, 0, len-7, "and")||
        strcmpp(s, 0, len-7, "not")||strcmpp(s, 0, len-7, "not")) f2 = 1;
        if(f1&&f2) return 0; else return f1;
    } else 
    return 3;
}


int main(){
    char s[100];
    while(fgets(s,100,stdin)!=NULL){
        delspace(s);
        printf("%i\n", check_type(s));
    }
    return 0;
}
