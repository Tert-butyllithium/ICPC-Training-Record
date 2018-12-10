#pragma GCC target("avx","avx2","sse4","sse4.1","sse4.2","ssse3","sse3","sse2","sse","f16c")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
using std::min;
using std::vector;

const int maxn = 1005;
const int inf = 0x3f3f3f3f;
int n, m;
struct edge
{
    int from, to, val;
    edge(){}
    edge(int f,int t,int v):from(f),to(t),val(v){}
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

vector<edge> edges;

struct point{   
    int x, y;
};

point ps[maxn];

int dis(const point& a,const point &b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

struct segment_set{
    int cost;
    vector<int> vec;
};

vector<segment_set> seg;

int fa[maxn];

int find(int x){
    if(x==fa[x])
        return x;
    else
        return fa[x] = find(fa[x]);
}

void uni(int x,int y){
    x=find(x);
    y=find(y);
    fa[y] = x;
}

int solve(int u){
    int res = 0;
    for (int i = 0; i < maxn;i++)
        fa[i] = i;
    for (int i = 0;i<m;i++){
        if((u>>i)&1){
            res += seg[i].cost;
            for (int j = 1; j < seg[i].vec.size();j++){
                uni(seg[i].vec[j], seg[i].vec[j - 1]);
            }
        }
    }
    //edges should to be sorted;
    for(auto e:edges){
        if(find(e.from)!=find(e.to)){
            res += e.val;
            uni(e.from, e.to);
        }
    }
    return res;
}

void clear(){
    edges.clear();
    seg.clear();
}

int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        clear();
        scanf("%d%d", &n, &m);
        for(int i=0;i<m;i++){
            segment_set s;
            int l;
            scanf("%d", &l);
            scanf("%d", &s.cost);
            while(l--){
                int x;
                scanf("%d", &x);
                s.vec.push_back(x);
            }
            seg.push_back(s);
        }

        for (int i = 1; i <= n;i++){
            scanf("%d%d", &ps[i].x, &ps[i].y);
        }
        
        for (int i = 1; i <= n;i++){
            for (int j = i + 1; j <= n;j++){
                edges.push_back(edge(i, j, dis(ps[i], ps[j])));
            }
        }
        sort(edges.begin(), edges.end());
        int rr = 1 << m;
        int ans = inf;
        for (int i = 0; i < rr; i++)
        {
            int tmp = solve(i);
            ans = min(ans, tmp);
        }
        printf("%d\n", ans);
        if(round)
            puts("");
    }
}
