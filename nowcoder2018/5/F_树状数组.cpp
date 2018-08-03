//考虑每一个钻石，选取的期望=前面所有比他大的钻石不取的概率*选取他的概率
//然后把每个期望相加就是答案（想加就已经遍历了所有可能）
//先按照每个钻石的权重大到小排序，再利用树状数组维护前缀积，从而O(Log(N))获得在这个钻石前所有比他大的概率积
//https://www.nowcoder.com/discuss/89992?type=101&order=0&pos=1&page=0 

#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int maxn = 1e5 + 10;

void exgcd(const long long a, const long long b, long long &g, long long &x, long long &y) {
    if (!b) g = a, x = 1, y = 0;
    else exgcd(b, a % b, g, y, x), y -= x * (a / b);
}

inline long long inv(const long long num) {
    long long g, x, y;
    exgcd(num, MOD, g, x, y);
    return ((x % MOD) + MOD) % MOD;
}

long long bit[maxn];

inline int lowbit(int x) { return x & -x; }

void update(int x,long long v){
    for (int i = x; i < maxn;i+=lowbit(i)){
        bit[i] = (bit[i] * v) % MOD;
    }
}

long long get(int x){
    long long ans = 1;
    for (int i = x; i > 0;i-=lowbit(i)){
        ans = ans * bit[i] % MOD;
    }
    return ans;
}

struct node{
    int p, d, id;
    node(){}
    node(int p,int d,int id):p(p),d(d),id(id){}
    bool operator < (const node& n) const{
        if(d==n.d)
            return id < n.id;
        return d > n.d;
    }
};
node nodes[maxn];

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    long long _inv = inv(100);
    for (int i = 0; i < maxn;i++)
        bit[i] = 1;
    for (int i = 0; i < n;i++){
        scanf("%d%d", &nodes[i].p, &nodes[i].d);
        nodes[i].id = i+1;
    }
    sort(nodes, nodes + n);
    long long ans = 0;
    for (int i = 0; i < n;i++){
        long long tmp = (get(nodes[i].id-1) * ((_inv * nodes[i].p) % MOD)) % MOD;
        ans = (ans + tmp) % MOD;
        update(nodes[i].id, _inv*(100 - nodes[i].p) % MOD);
    }
    printf("%lld\n", ans);
    return 0;
}
