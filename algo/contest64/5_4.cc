#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>

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
    t = new T[1024];
    q=t;
    cap_buf=1024;
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


int main(){
    char s0[1024];
    int  len, t, x, n = 0;
    int a[1024];
    int d[6][7] = { {4, 1, 1, 1, 1, 1, 5},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 2, 2, 1, 2},
                    {2, 2, 2, 2, 2, 1, 2},
                    {5, 1, 1, 1, 1, 1, 3} };


    fgets(s0,1023,stdin);
    len = strlen(s0);
    s0[len++] = '|';

    Stack<int> st;
    st.push_back(0);

    for(int i=0; i<len; i++){
        if(s0[i]!=' '){
            if(isdigit(s0[i])){
                sscanf(s0+i,"%i",&t);
                while(isdigit(s0[i+1])) i++;
                a[n++]=t;
            } 
            else {
                while(d[st.top_back()][optype(s0[i])] == 2){
                    x = st.pop_back();
                    a[n++] = -x;
                }
                if(d[st.top_back()][optype(s0[i])] == 1){
                    st.push_back(optype(s0[i]));
                }
                if(d[st.top_back()][optype(s0[i])] == 3){
                    st.pop_back();
                }
            } 
        }
    }

    st.clear();

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

    printf("%i\n",st.pop_back());
    
    return 0;
}

