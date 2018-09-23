//题目大意：增长序列。当长度为奇数是求中位数
//主席树模板（杀鸡用牛刀
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
 
struct Node {
    int L, R, sum;
};
Node T[MAXN * 20];
int T_cnt;
 
void insert(int &num, int &x, int L, int R) {
    T[T_cnt++] = T[x]; x = T_cnt - 1;
    ++T[x].sum;
    if(L == R) return ;
    int mid = (L + R) >> 1;
    if(num <= mid) insert(num, T[x].L, L, mid);
    else insert(num, T[x].R, mid + 1, R);
}
 
int query(int i, int j, int k, int L, int R) {
    if(L == R) return L;
    int t = T[T[j].L].sum - T[T[i].L].sum;
    int mid = (R + L) >> 1;
    if(k <= t) return query(T[i].L, T[j].L, k, L, mid);
    else return query(T[i].R, T[j].R, k - t, mid + 1, R);
}
 
struct A {
    int x, idx;
    bool operator < (const A &rhs) const {
        return x < rhs.x;
    }
};
 
A a[MAXN];
 
int _rank[MAXN], root[MAXN];
int n, m;
 
void cal(){
 
    for (int i = 1; i <= n;i+=2){
        int mid = (i + 1) / 2;
        int t = query(root[0], root[i], mid, 1, n);
        printf("%d ", a[t].x);
    }
    puts("");
}
 
void clear(){
    memset(T, 0, sizeof(T));
    memset(_rank, 0, sizeof(_rank));
    memset(root, 0, sizeof(root));
    memset(a, 0, sizeof(a));
}
 
int main() {
    int round;
    scanf("%d", &round);
    while (round--)
    {
        T[0].L = T[0].R = T[0].sum = 0;
        root[0] = 0;
        clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i].x);
            a[i].idx = i;
        }
        sort(a + 1, a + n + 1);
        for(int i = 1; i <= n; ++i) _rank[a[i].idx] = i;
        T_cnt = 1;
        for(int i = 1; i <= n; ++i) {
            root[i] = root[i - 1];
            insert(_rank[i], root[i], 1, n);
        }
        cal();
    }
}
