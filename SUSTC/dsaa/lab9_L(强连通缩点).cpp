//tarjan缩点之后，每两个强连通分量之间最多只有一条边
//如果是n个互不相连的强连通分量（如，m=0），那么需要连n条边使他们成环
//考虑入度/出度为0的强连通分量的数量，答案为他们的最大值（选择入度还是出度决定了环的方向）

#pragma GCC target("avx","avx2","sse4","sse4.1","sse4.2","ssse3","sse3","sse2","sse","f16c")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
using std::min;
using std::stack;
using std::vector;

const int maxn=20005;
int idx,tot,low[maxn],inS[maxn],dfn[maxn],scc[maxn];
stack<int> stk;
vector<int> vec[maxn];
int in_degree[maxn], out_degree[maxn];

void tarjan_scc(int u){
    dfn[u] = low[u] = ++idx;
    stk.push(u);
    inS[u] = true;
    for (auto v : vec[u])
    {
        if (!dfn[v])
        {
            tarjan_scc(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inS[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u]==low[u]){
        ++tot;
        int cur = u;
        do
        {
            cur = stk.top();
            stk.pop();
            inS[cur] = false;
            scc[cur] = tot;
        } while (cur != u);
    }
}

void clear(){
    idx = tot = 0;
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(inS, 0, sizeof(inS));
    memset(in_degree,0,sizeof(in_degree));
    memset(out_degree,0,sizeof(out_degree));
    for(int i=0;i<maxn;i++){
        vec[i].clear();
    }
    while(!stk.empty()) stk.pop();
}

int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        clear();
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m;i++){
            int x, y;
            scanf("%d%d", &x, &y);
            vec[x].push_back(y);
        }
        for (int i = 1; i <= n;i++){
            if(!dfn[i]){
                tarjan_scc(i);
            }
        }
        for (int i = 1; i <= n;i++){
            for(auto to:vec[i]){
                if(scc[i]!=scc[to]){
                    out_degree[scc[i]]++;
                    in_degree[scc[to]]++;
                }
            }
        }
        int a = 0, b = 0;
        for (int i = 1; i <= tot; i++)
        {
            if(!in_degree[i])
                a++;
            if(!out_degree[i])
                b++;
        }
        printf("%d\n", tot==1?0:std::max(a, b));
    }
}
