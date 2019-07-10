// ZOJ 4097
// 双连通分量缩环+lca倍增+并查集维护连通分量
#include <bits/stdc++.h>
using std::min;
using std::pair;
using std::vector;
using pii = pair<int, int>;
const int maxn = 1e5 + 10;

vector<int> G[maxn];
vector<int> G2[maxn];
vector<pii> edges;
int n, m, q, dfn[maxn], low[maxn], belong[maxn], isbridge[maxn << 2];
int faa[maxn];
int bcc_cnt, dfn_clk;
int pa[maxn][20], dep[maxn];

int findfa(int x)
{
    return x == faa[x] ? x : faa[x] = findfa(faa[x]);
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++dfn_clk;
    for (const int &p : G[u])
    {
        int v = edges[p].second;
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
            {
                isbridge[p] = isbridge[p ^ 1] = 1;
            }
        }
        else if (dfn[v] < dfn[u] && v != fa)
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfs(int u)
{
    dfn[u] = 1;
    belong[u] = bcc_cnt;
    for (auto &e : G[u])
    {
        int v = edges[e].second;
        if (!isbridge[e] && !dfn[v])
        {
            dfs(v);
        }
    }
}

void find_ebcc()
{
    dfn_clk = bcc_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(isbridge, 0, sizeof(isbridge));
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            tarjan(i, -1);
        }
    }
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            bcc_cnt++;
            dfs(i);
        }
    }
}

void addedge(int u, int v)
{
    edges.emplace_back(u, v);
    edges.emplace_back(v, u);
    G[u].push_back(edges.size() - 2);
    G[v].push_back(edges.size() - 1);
}

void dfs2(int u, int fa)
{
    for (int i = 1; i <= 19; i++)
    {
        pa[u][i] = pa[pa[u][i - 1]][i - 1];
    }
    for (auto &v : G2[u])
    {
        if (v != fa)
        {
            dep[v] = dep[u] + 1;
            pa[v][0] = u;
            dfs2(v, u);
        }
    }
}

int lca(int x, int y)
{
    if (dep[x] < dep[y])
    {
        std::swap(x, y);
    }
    for (int i = 19; i >= 0; i--)
    {
        if (dep[pa[x][i]] >= dep[y])
            x = pa[x][i];
    }
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
    {
        if (pa[x][i] != pa[y][i])
        {
            x = pa[x][i];
            y = pa[y][i];
        }
    }
    return pa[x][0];
}

void go()
{
    find_ebcc();
    for (int i = 0; i < edges.size(); i += 2)
    {
        int u = edges[i].first, v = edges[i].second;
        if (isbridge[i])
        {
            G2[belong[u]].push_back(belong[v]);
            G2[belong[v]].push_back(belong[u]);
        }
        u = findfa(u);
        v = findfa(v);
        if (u != v)
        {
            if (u < v)
                std::swap(u, v);
            faa[u] = v;
        }
    }
    for (int i = 1; i <= bcc_cnt; i++)
    {
        if (!dep[i])
        {
            dep[i] = 1;
            dfs2(i, -1);
        }
    }
}

int main()
{
    int round;
    scanf("%d", &round);
    while (round--)
    {
        scanf("%d%d%d", &n, &m, &q);
        memset(pa, 0, sizeof(pa));
        memset(dep, 0, sizeof(dep));
        for (int i = 1; i <= n; i++)
        {
            // pa[i][0] = 0;
            G[i].clear();
            G2[i].clear();
            faa[i] = i;
        }
        edges.clear();
        for (int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        go();
        while (q--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if (findfa(u) != findfa(v) || findfa(w) != findfa(u))
            {
                puts("No");
                continue;
            }
            u = belong[u];
            v = belong[v];
            w = belong[w];
            if (v == w)
            {
                if (u == v)
                {
                    puts("Yes");
                }
                else
                {
                    puts("No");
                }
            }
            else
            {
                int anc = lca(v, w);
                if ((lca(u, v) == u || lca(u, w) == u) && lca(anc, u) == anc)
                {
                    puts("Yes");
                }
                else
                {
                    puts("No");
                }
            }
        }
    }
}
