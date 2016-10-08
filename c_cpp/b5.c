#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 512
#define STACK_SIZE 512
#define ERR(x) { printf(x); return 0; }


struct Var {
    char *key;
    int value;
};

typedef struct Vars {
    struct Var* var;
    int cap;
    int size;
} Vars;

typedef struct Stack {
    int *st;
    size_t size;
    size_t cap;
} Stack;


void stack_grow(Stack *stack) {
    stack->st = realloc(stack->st, (stack->cap == 0 ? STACK_SIZE : (stack->cap * 2))*(sizeof(int)));
    stack->cap = (stack->cap == 0 ? STACK_SIZE : (stack->cap * 2));
}

void push(Stack* stack, int x) {
    if(stack->size==stack->cap) stack_grow(stack);
    (stack->st)[(stack->size)++] = x;
}

int pop(Stack* stack) {
    if(stack->size==0) return -9;
    return (stack->st)[--(stack->size)];
}

int top(Stack* stack) {
    if(stack->size==0) return -9;
    return (stack->st)[stack->size-1];
}

int pass_space(char *s, int k){
    while(k>=0&&(s[k]==' '||s[k]=='\n')){
        k--;
    }
    return k;
}

int check_var(char *s, int k){
    int i,t=0;
    for(i=k; i>=0; i--){
        if(isupper(s[i])) return -1;
        if(i<k && isalpha(s[i]) && s[i+1]==' ') return -1;
        if(!isalpha(s[i]) && s[i]!=' ') return -1;
        if(isalpha(s[i])) t=i;
    }
    return t;
}


void vars_grow(Vars* vars){
    vars->cap = (vars->cap == 0 ? BUF_SIZE : (vars->cap * 2));
    vars->var = realloc(vars->var, (vars->cap)*sizeof(struct Var));
}

size_t add_var(Vars* vars, char *s, int value){
    size_t i;
    for(i=0; i<vars->size; ++i){
        if(strcmp((vars->var+i)->key, s)==0){
            (vars->var+i)->value = value;
            return vars->size;
        }
    }
    if(vars->size==vars->cap) 
        vars_grow(vars);
    i = vars->size;
    (vars->var+i)->key = (char*)malloc(sizeof(char)*(strlen(s)+1));
    strcpy((vars->var+i)->key, s);
    (vars->var+i)->value = value;
    (vars->size)++;
 
    return vars->size; 
}

int get_word_value(char *buf, Vars *vars){
    size_t i;
    if(strcmp(buf, "True")==0) return 2;
    if(strcmp(buf, "False")==0) return 1;
    if(strcmp(buf, "(")==0) return -5;
    if(strcmp(buf, ")")==0) return -6;
    if(strcmp(buf, "and")==0) return -3;
    if(strcmp(buf, "or")==0) return -1;
    if(strcmp(buf, "xor")==0) return -2;
    if(strcmp(buf, "not")==0) return -4;

    for(i=0; i<vars->size; ++i){
        if(strcmp(buf, (vars->var+i)->key)==0) return (vars->var+i)->value;
    }

    return -7;
}

int init_vars(Vars* vars, char *s){
    size_t i, j, len, value=0;

    len = strlen(s);
    i = pass_space(s, len-1);
    if(i>=0&&s[i]==';'){
        i = pass_space(s, i-1);
        s[i+1]='\0';
        if(i>4 && strcmp(s+i-3,"True")==0){
            value=1;
            i-=3;   
        } else 
        if(i>5 && strcmp(s+i-4,"False")==0){
            value=0;
            i-=4;            
        } else
        return -1;
        i = pass_space(s, i-1);
        if(s[i]!='=') return -1;
        i = pass_space(s, i-1);
        if((j = check_var(s, i)) == -1) 
            return -1;
        
        s[i+1]='\0';
        if(get_word_value(s, vars)<0&&get_word_value(s, vars)!=-7) return -3;
        add_var(vars, s+j, value+1);
        return value+1;
    }
    if(i==-1) return -2;
    return 0;
}

size_t get_word(char *buf, char *s, size_t k){
    size_t i = k;
    
    while(s[i]==' '||s[i]=='\n'||s[i]=='\t'){
        i++;
        k++;
    }
    if(s[i]=='(' || s[i]==')'){
        buf[i-k]=s[i];
        buf[i-k+1]='\0';
        i++;
    } 
    else {
        while(s[i]!=' '&&s[i]!='('&&s[i]!=')'&&s[i]!='\0'&&s[i]!='\n'&&s[i]!='\t'){
            buf[i-k]=s[i];
            i++;
        }
        buf[i-k]='\0';
    }
    return i;
}


int init_expression(char* s, int* a, Vars *vars){
    size_t i = 0, len = strlen(s), n = 0;
    int t = 0;
    char buf[BUF_SIZE];

    while(i<len){
        i = get_word(buf, s, i);
        if(buf[0]=='\0') break;
        if((t = get_word_value(buf, vars))!=-7){  
                a[n++] = t;
        }
        else 
            return -1;
    }
    return n;
}


int solve(int *a, int n){
    Stack stack = {NULL, 0, 0};
    int t,x,ans,i;
    for(i=0; i<n; i++){
       if(a[i]>=0) push(&stack, a[i]);
        else {
            if((t = pop(&stack))==-9){
                if(stack.cap) free(stack.st);
                return -1;
            }
            switch(a[i]){
                case -1:
                    if((x = pop(&stack))==-9){
                        if(stack.cap) free(stack.st);
                        return -1;
                    }
                    push(&stack, t+x==0?0:1);
                    break;
                case -2:
                    if((x = pop(&stack))==-9){
                        if(stack.cap) free(stack.st);
                        return -1;
                    }
                    push(&stack, (t+x)%2);
                    break;
                case -3:
                    if((x = pop(&stack))==-9){
                        if(stack.cap) free(stack.st);     
                        return -1;
                    }
                    push(&stack, t*x);
                    break;
                case -4:
                    push(&stack, t==0?1:0);
                    break;
            }
        }
    }
    if(stack.size>1){
        if(stack.cap) free(stack.st);
        return -1;
    }
    if((ans = pop(&stack))==-9){
        if(stack.cap) free(stack.st);
        return -1;
    }
    free(stack.st);
    return ans;
}


int inftopost(int *a, int k, int *b){
    int d[6][7] = { {4, 1, 1, 1, 1, 1, 5},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 2, 1, 1, 2},
                    {2, 2, 2, 2, 1, 1, 2},
                    {5, 1, 1, 1, 1, 1, 3} };
    int x, n=0, i;    
    Stack stack = {NULL, 0, 0};
    push(&stack, 0);  
    a[k++] = 0;
    for(i=0; i<k; i++){
        if(a[i]>0){
                b[n++]=a[i]-1;
        } 
        else {
            while(d[top(&stack)][-a[i]] == 2){
                if((x = pop(&stack))==-9){
                    free(stack.st);
                    return -1;
                }
                b[n++] = -x;
            }
            if(d[top(&stack)][-a[i]] == 1){
                push(&stack, -a[i]);
            }
            if(d[top(&stack)][-a[i]] == 3){
                if((x = pop(&stack))==-9){
                    free(stack.st);
                    return -1;
                }
                continue;
            }
            if(d[top(&stack)][-a[i]] == 5){
                free(stack.st);
                return -1;
            }
        } 
    }
    free(stack.st);
    return n;
}


void free_vars(Vars *vars){
    int i;
    if(vars->cap>0){
        for(i=0; i<vars->size; i++){
            free((vars->var+i)->key);
        }
        free(vars->var);
    }
    free(vars);
}


int isempty(char *s){
    int i, len = strlen(s);
    for(i=0; i<len; i++){
        if(s[i]!=' '&&s[i]!='\n'&&s[i]!='\t') return 0;
    }
    return 1;
}


int main(){
    char s[BUF_SIZE];
    Vars *vars = malloc(sizeof(Vars));
    vars->var = NULL;
    vars->size = 0;
    vars->cap = 0;
    int a[BUF_SIZE], n = 0, b[BUF_SIZE], m;
    int t, ans;
    
    
    if(fgets(s,BUF_SIZE,stdin)==NULL){
        free_vars(vars);
        ERR("False\n");
    }

    while(isempty(s)){
        if(fgets(s,BUF_SIZE,stdin)==NULL){
            free_vars(vars);
            ERR("False\n");
        }
    }
    
    while((t=init_vars(vars, s))>0){
        if(fgets(s,BUF_SIZE,stdin)==NULL){
            free_vars(vars);
            ERR("[error]\n");
        }
        while(isempty(s)){
            if(fgets(s,BUF_SIZE,stdin)==NULL){
                free_vars(vars);
                ERR("[error]\n");
            }
        }
    }

    if(t<0){
        free_vars(vars);
        ERR("[error]\n");
    }

    n = init_expression(s, a, vars);
    if(n==-1){
        free_vars(vars);
        ERR("[error]\n");
    }
    
    if(scanf("%s",s)==1){
        free_vars(vars);
        ERR("[error]\n");
    }

    m = inftopost(a, n, b);

    if(m!=-1){
        ans = solve(b, m);
        if(ans==0){
            printf("False\n");
        } 
        else if(ans==1){
            printf("True\n");
        }
        else{
            free_vars(vars);
            ERR("[error]\n");
        } 
    } 
    else{
        free_vars(vars);
        ERR("[error]\n");
    }

    free_vars(vars);
    
    return 0;
}
