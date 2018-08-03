#include <iostream>
#include <queue>
using namespace std;

const int INF = 0x7fffffff;
int V, E;
int level[205];
int Si, Ei, Ci;

struct Dinic
{
    int c;
    int f;
}edge[205][205];

bool dinic_bfs()      //bfs方法构造层次网络
{
    queue<int> q;
    memset(level, 0, sizeof(level));
    q.push(1);
    level[1] = 1;
    int u, v;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (v = 1; v <= E; v++) {
            if (!level[v] && edge[u][v].c>edge[u][v].f) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[E] != 0;                //question: so it must let the sink node is the Mth?/the way of yj is give the sink node's id
}

int dinic_dfs(int u, int cp) {           //use dfs to augment the flow
    int tmp = cp;
    int v, t;
    if (u == E)
        return cp;
    for (v = 1; v <= E&&tmp; v++) {
        if (level[u] + 1 == level[v]) {
            if (edge[u][v].c>edge[u][v].f) {
                t = dinic_dfs(v, min(tmp, edge[u][v].c - edge[u][v].f));
                edge[u][v].f += t;
                edge[v][u].f -= t;
                tmp -= t;
            }
        }
    }
    return cp - tmp;
}
int dinic() {
    int sum=0, tf=0;
    while (dinic_bfs()) {
        while (tf = dinic_dfs(1, INF))
            sum += tf;
    }
    return sum;
}

int main() {
    while (scanf("%d%d", &V, &E)) {
        memset(edge, 0, sizeof(edge));
        while (V--) {
            scanf("%d%d%d", &Si, &Ei, &Ci);
            edge[Si][Ei].c += Ci;
        }
        int ans = dinic();
        printf("%d\n", ans);
    }
    return 0;
}
