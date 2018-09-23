//dsaa lab3 F
//题目大意：求所有连续子序列第k大元素的和
//顺手实现了一个链表模板
//通过记录rank和指针，复杂度O(N*k)
#include <bits/stdc++.h>
using namespace std;
using QAQ=long long;
const int maxn = 5e5+10;
int n, k;
int arr[maxn];
int rk[maxn];

template <class T>
struct node
{
    T val;
    node* prev;
    node* next;
    
    node(){}
    node(T val):val(val){
        prev = NULL;
        next = NULL;
    }
};
node<int>* _rank[maxn];

template <class T>
struct linkedlist
{
    int length=0;
    node<T>* head=NULL;
    node<T>* tail=NULL;
    
    size_t size(){
        return length;
    }
    
    void push_back(T val){
        if(length==0){
            head = tail = new node<T>(val);
        }
        else if(length==1){
            tail =new node<T>(val);
            head->next = tail;
            tail->prev = head;
        }
        else{
            node<T>* tmp = new node<T>(val);
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
        }
        length++;
    }
    
    vector<T> to_vector(){
        vector<T> vec;
        for (node<T>* c = head; c != tail->next; c = c->next)
        {
            vec.push_back(c->val);
        }
        return vec;
    }
    
    void clear(){
        if (head == NULL)
            return;
        for (node<T> *c = head->next; c != NULL; c = c->next)
        {
            delete c->prev;
        }
        length = 0;
        head = tail = NULL;
    }
    
    void remove(node<T>* cur){
        auto *p = cur->prev;
        auto *q = cur->next;
        if(p!=NULL)
            p->next = q;
        if(q!=NULL)
            q->prev = p;
        length--;
    }
    
};
linkedlist<int> li;

QAQ cal(node<int>* pos){
    if(li.size()<k) return 0;
    node<int>* left=pos;
    node<int>* right=pos;
    int i=1,j=1;
    QAQ cnt=0;
        while (true) {
            if(i==k||left->prev==NULL) break;
//            reduce+=(left-left->prev-1);
            left=left->prev;
            i++;
        }
        if(i<k){
            int res=k-i+1;
            while(true){
                if(j==res||right->next==NULL) break;
//                reduce+=(right->next-right-1);
                right=right->next;
                j++;
            }
            if(j<res) return 0;
            if(right->next!=NULL){
//                reduce+=(right->next-right-1);
            }
        }
        else{
            if(left->prev!=NULL){
//                reduce+=(left-left->prev-1);
            }
        }
    do{
        QAQ a,b;
        if(right->next==NULL)
            b=n-rk[right->val];
        else
            b=rk[right->next->val]-rk[right->val]-1;
        if(left->prev==NULL){
            a=rk[left->val]-1;
        }
        else{
            a=rk[left->val]-rk[left->prev->val]-1;
        }
        cnt+=(a+1)*(b+1);
        left=left->next;
        right=right->next;
    }while(left!=NULL&&rk[left->val]<=rk[pos->val]&&right!=NULL);
    li.remove(pos);
    return cnt*(1ll*pos->val);
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        li.clear();
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n;i++){
            scanf("%d", &arr[i]);
            li.push_back(arr[i]);
            rk[arr[i]]=i;
            _rank[arr[i]] = li.tail;
        }
        QAQ ans=0;
        for(int i=1;i<=n;i++){
            ans+=cal(_rank[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}




