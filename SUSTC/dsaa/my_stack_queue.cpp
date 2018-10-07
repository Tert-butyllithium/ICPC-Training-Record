#include <stdio.h>
#include <cstdlib>

// using namespace std::vector;

template <class T>
struct stack
{
    T *raw;
    int index;
    int nums;
    int len;
    stack<T>(int len = 100):len(len)
    {
        index = -1;
        raw = (T *)malloc(sizeof(T) * len);
        nums = 0;
    }


    bool push(T val){
        if(nums>=len){
            return false;
        }
        index = (index + 1) % len;
        raw[index] = val;
        nums++;
        return true;
    }

    T pop(){
        if(nums<=0){
            throw "No such item";
            return raw[0];
        }
        T res = raw[index];
        index--;
        if(index<0){
            index += len;
        }
        nums--;
        return res;
    }

    bool is_empty(){
        return nums == 0;
    }
};

template<class T>
struct queue
{
    T *raw;
    int from, end;
    int len;
    int nums;

    queue(int len=100):len(len){
        raw = (T *)malloc(sizeof(T) * len);
        from = end = nums = 0;
    }

    bool push(T val){
        if(nums>=len){
            return false;
        }
        raw[end]=val;
        end = (end + 1) % len;
        nums++;
        return true;
    }

    T pop(){
        if(nums==0){
             throw std::range_error("the queue is empty");
            return raw[0];
        }
        int res = raw[from];
        from = (from + 1) % len;
        nums--;
        return res;
    }

    bool is_empty() {
        return nums == 0;
    }

    bool is_full(){
        return nums==len;
    }

    int size(){
        return nums;
    }

    T front(){
        return raw[from];
    }

    void clear(){
//        free(raw);
        from=end=nums=0;

    }



};

int main(int argc, char const *argv[])
{
    queue<int> st=queue<int>(10);
    for (int i = 0; i < 100;i++){
        if(!st.push(i)){
            st.pop();
            st.push(i);
        }
    }
    while(!st.is_empty()){
        printf("%d\n", st.pop());
    }
    st.pop();
    st.pop();
    st.pop();
    return 0;
}
