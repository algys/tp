/*___________________________________________________________________________
Автор: Иевлев А.А. студент АПО-13

Задача 5_4:
Вычисление выражения.
Дано выражение в инфиксной записи. Вычислить его, используя перевод выражения 
в постфиксную запись. Выражение не содержит отрицительных чисел.
Количество операций ≤ 100.
_____________________________________________________________________________
Формат входных данных.
Строка, состоящая их символов “0123456789+/()*”
Гарантируется, что входное выражение корректно, нет деления на 0, вычислимо 
в целых числах. Деление целочисленное.

Формат выходных данных.
Значение выражения.
___________________________________________________________________________*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>

#define BUF_SIZE 1024

template <typename T>
class Stack{
    private:
        size_t size_buf;
        size_t cap_buf;
        T *q;
    public:
        Stack(size_t size = 1024);
        ~Stack();
        void reallc();
        size_t size(){ return size_buf; }
        void push_back(const T&);
        const T pop_back(void);
        const T top_back(void);
        void clear(void);
};

template <typename T>
Stack<T>::Stack(size_t size){
    q = new T[size];
    cap_buf = size;
    size_buf = 0;
}

template <typename T>
Stack<T>::~Stack(){
    delete []q;
}

template <typename T>
void Stack<T>::clear(){
    T *t;
    delete []q;
    t = new T[BUF_SIZE];
    q=t;
    cap_buf=BUF_SIZE;
    size_buf=0;
}

template <typename T>
void Stack<T>::push_back(const T& x){
    if(size_buf==cap_buf) reallc();
    q[size_buf] = x;
    size_buf++;
}

template <typename T>
const T Stack<T>::pop_back(){
    T t;
    if(size_buf == 0) return -1;
    t = q[--size_buf];
    return t;
}

template <typename T>
const T Stack<T>::top_back(){
    T t;
    if(size_buf == 0) return -1;
    t = q[size_buf-1];
    return t;
}

template<typename T>
void Stack<T>::reallc(){
    T *t;
    t = new T[cap_buf*2+1];
    for(int i=0; i<cap_buf; i++){
        t[i] = q[i];
    }
    cap_buf=cap_buf*2+1;
    delete []q;
    q = t;
}

int optype(char c){
    switch(c){
        case '|':
            return 0;
            break;
        case '+':
            return 1;
            break;
        case '-':
            return 2;
            break;
        case '*':
            return 3;
            break;
        case '/':
            return 4;
            break;
        case '(':
            return 5;
            break;
        case ')':
            return 6;
            break;
    }
    return -1;
}

int inftopost(char *s, int *a, int &n){
    int d[6][7] = { {4, 1, 1, 1, 1, 1, 5},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 2, 2, 1, 2},
                    {2, 2, 2, 2, 2, 1, 2},
                    {5, 1, 1, 1, 1, 1, 3} };
    int t,x,len;    
    Stack <int> st;
    st.push_back(0);
    len = strlen(s);  
    s[len++] = '|';

    for(int i=0; i<len; i++){
        if(s[i]!=' '){
            if(isdigit(s[i])){
                sscanf(s+i,"%i",&t);
                while(isdigit(s[i+1])) i++;
                a[n++]=t;
            } 
            else {
                while(d[st.top_back()][optype(s[i])] == 2){
                    x = st.pop_back();
                    a[n++] = -x;
                }
                if(d[st.top_back()][optype(s[i])] == 1){
                    st.push_back(optype(s[i]));
                }
                if(d[st.top_back()][optype(s[i])] == 3){
                    st.pop_back();
                }
            } 
        }
    }
    st.clear();
    return 0;
}

int solve(int *a, int n){
    Stack<int> st;
    int t,x,ans;

    for(int i=0; i<n; i++){
        if(a[i]>=0) st.push_back(a[i]);
        else {
            t = st.pop_back();
            x = st.pop_back();
            switch(a[i]){
                case -1:
                    st.push_back(t+x);
                    break;
                case -2:
                    st.push_back(x-t);
                    break;
                case -3:
                    st.push_back(t*x);
                    break;
                case -4:
                    st.push_back(x/t);
                    break;
            }
        }
    }
    ans = st.pop_back();
    st.clear();

    return ans;
}

int main(){
    char s[BUF_SIZE];
    int  ans, n = 0;
    int a[BUF_SIZE];

    fgets(s,BUF_SIZE-1,stdin);

    inftopost(s, a, n);
    
    ans = solve(a, n);

    printf("%i\n",ans);
    
    return 0;
}

