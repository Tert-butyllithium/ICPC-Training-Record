#pragma GCC target("avx", "avx2", "sse4", "sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "f16c")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, f = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = 1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ '0');
    return f ? -x : x;
}

const int N = 1.5e5 + 7;

int n, m, u, v, s;
int tot = 0, st[N], to[N << 1], nx[N << 1], fa[N], ans[N], vis[N];
int should_be[N];
struct note
{
    int node, id;
};
vector<note> ques[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

void dfs(int u, int from)
{
    for (int i = st[u]; i; i = nx[i])
        if (to[i] != from)
            dfs(to[i], u), fa[to[i]] = u; //将u的儿子合并到u
    int len = ques[u].size();             //处理与u有关的询问
    for (int i = 0; i < len; i++)
        if (vis[ques[u][i].node])
            ans[ques[u][i].id] = getfa(ques[u][i].node); //对应的v已经访问并回溯时，LCA(u,v)就是v的fa里深度最小的一个也就是getfa(v)
    vis[u] = 1;                                          //访问完毕回溯
}

bool flag[N];
void clear()
{
    memset(st, 0, sizeof(st));
    memset(to, 0, sizeof(to));
    memset(nx, 0, sizeof(nx));
    memset(vis, 0, sizeof(vis));
    memset(flag, 0, sizeof(flag));
    for (int i = 0; i < N; i++)
    {
        ques[i].clear();
    }
    tot = 0;
}

int main()
{
    int round = read();
    while (round--)
    {
        clear();
        n = read(), m = read();
        for (int i = 1; i < n; i++)
            v = read(), u = read(), add(u, v), add(v, u), flag[v] = true;
        for (int i = 1; i <= m; i++)
            u = read(), v = read(), ques[u].push_back((note){v, i}), ques[v].push_back((note){u, i}), should_be[i] =(u==v)?-1:v;
        for (int i = 1; i <= n; i++)
            fa[i] = i;
        for (int i = 1; i <= n;i++){
            if(!flag[i]) {
                s = i;
                break;
            }
        }
        dfs(s, 0);
        for (int i = 1; i <= m; i++)
        {
            puts((ans[i] == should_be[i]||should_be[i]==-1)? "Yes" : "No");
        }
    }
    return 0;
}
