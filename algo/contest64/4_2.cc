/*___________________________________________________________________________
Автор: Иевлев А.А. студент АПО-13

Задача 3_2:
Во всех задачах из следующего списка следует написать структуру данных, 
обрабатывающую команды push* и pop*.
_____________________________________________________________________________
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 ­ push_front
a = 2 ­ pop_front
a = 3 ­ push_back
a = 4 ­ pop_back
Для очереди используются команды 2 и 3. Для дека используются все четыре 
команды. Если дана команда pop*, то число b ­ ожидаемое значение.Если команда 
pop вызвана для пустой структуры данных, то ожидается “­1”.

Формат выходных данных.
Требуется напечатать YES ­ если все ожидаемые значения совпали. 
Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
____________________________________________________________________________
Пример.
in
3
1 44
3 50
2 44
out
YES

in
2
2 -1
1 10
out 
YES

in
2
3 44
4 66
out
NO
___________________________________________________________________________*/

#include <stdio.h>

template <typename T>
class deq{
    private:
        size_t size_buf;
        size_t cap_buf;
        int front;
        int back;
        T *q;
    public:
        deq(size_t size = 64);
        ~deq();
        void reallc();
        size_t size(){ return size_buf; }
        void push_back(const T&);
        void push_front(const T&);
        const T pop_back(void);
        const T pop_front(void);
};

template <typename T>
deq<T>::deq(size_t size){
    q = new T[size];
    cap_buf = size;
    size_buf = 0;
    front = 0;
    back = 0;
}

template <typename T>
deq<T>::~deq(){
    delete []q;
}

template <typename T>
void deq<T>::push_back(const T& x){
    if(size_buf==cap_buf) reallc();
    q[back] = x;
    back++;
    size_buf++;
}

template <typename T>
const T deq<T>::pop_back(){
    T t;
    if(size_buf==0) return -1;
    t = q[back--];
    size_buf--;
    return t;
}

template <typename T>
void deq<T>::push_front(const T& x){
    if(size_buf==cap_buf) reallc();
    for(int i=back; i!=front; i--)
    q[i] = q[i-1];
    back++;
    size_buf++;
    q[front] = x;
}

template <typename T>
const T deq<T>::pop_front(){
    T t;
    if(size_buf==0) return -1;
    t = q[front];
    back--;
    for(int i=front; i<back; i++)
        q[i] = q[i+1];
    size_buf--;
    return t;
}

template<typename T>
void deq<T>::reallc(){
    T *t;
    t = new T[cap_buf*2];
    for(int i=0; i<cap_buf; i++){
        t[i] = q[i];
    }
    delete []q;
    q = t;
}

bool check_expect(int a, int b){
    if(a==1) q.push_front(b); else
    if(a==2) t=q.pop_front(); else
    if(a==3) q.push_back(b); else
    if(a==4) t=q.pop_back();
    if(a==2 || a==4){
        if(t!=b){  
            return false; 
        }
    }
    return true;
}

int main(){
    int n,a,b,t;
    
    scanf("%i", &n);
    deq<int> q;
    
    for(int i=0; i<n; i++){
        scanf("%i%i",&a,&b);
        if(!check_expect(a,b)){
            printf("NO");
            return 0;
        }
   }

    printf("YES");

    return 0;
}

