#include <bits/stdc++.h>
#define MAX_SIZE 150
using namespace std;

template<typename T>
class Stack{
    public:
      typedef typename array<T, MAX_SIZE>::size_type size_type;

      Stack();
      Stack(const Stack &) = default;
      ~Stack() = default;

      void push(T x);
      T pop();
      bool empty();
      T peek();
      void print();
    private:
      array<T, MAX_SIZE> a;
      size_type top;
};

template<typename T>
Stack<T>::Stack(){
    top = -1;
}

template<typename T>
bool Stack<T>:: empty(){
    return top == -1;
}

template<typename T>
void Stack<T>::push(T val){
    if(top==MAX_SIZE-1){
        throw "Stack Overflow";
    }
    else{
        a[++top] = val;
    }
}

template<typename T>
T Stack<T>::pop(){
    if(empty()){
        throw "Stack Empty";
    }
    else{
        return a[top--];
    }
}

template<typename T>
T Stack<T>::peek(){
    if(empty()){
        throw "Stack Empty";
    }
    else{
        return a[top];
    }
}

template<typename T>
void Stack<T>::print(){
	cout<<"Stack : ";
	for (size_type i = 0; i <= top; ++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
