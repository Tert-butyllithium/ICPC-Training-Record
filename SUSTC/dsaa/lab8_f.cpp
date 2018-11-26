//有向无环图求全局最长路：
//拓扑排序+动态规划
#pragma GCC target("avx","avx2","sse4","sse4.1","sse4.2","ssse3","sse3","sse2","sse","f16c")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
using namespace std;
using QAQ=long long;
const int maxn = 100007;
const int inf = 0x3f3f3f3f;

vector<pair<int, int>> vec[maxn];
bool vis[maxn];
QAQ dist[maxn];
int in_degree[maxn];
int n, m;

void clear(){
    for (int i = 1; i < maxn;i++){
        vec[i].clear();
    }
    memset(vis, 0, sizeof(vis));
    memset(in_degree, 0, sizeof(in_degree));
    fill(dist, dist + 1 + n, -inf);
}

void dfs(int cur,vector<int>& topological_sorted){
    if(vis[cur])
        return;
    vis[cur] = true;
    for(auto c:vec[cur]){
        dfs(c.first,topological_sorted);
    }
    topological_sorted.push_back(cur);
}

int find_root(){
    return min_element(in_degree + 1, in_degree + 1 + n) - in_degree;
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        clear();
        scanf("%d%d", &n, &m);
        while(m--){
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            vec[x].push_back(make_pair(y, w));
            in_degree[y]++;
        }
        vector<int> topo;
        for (int i = 1; i <= n;i++){
            dfs(i, topo);
        }
        reverse(topo.begin(), topo.end());
        memset(vis,0,sizeof(vis));

        int s = find_root();
        dist[s] = 0;
        for (auto c:topo){
            for(auto t:vec[c]){
                int d = t.second;
                if(dist[t.first]<dist[c]+d){
                    dist[t.first] = dist[c] + d;
                }
            }
        }
        printf("%lld\n", *max_element(dist + 1, dist + 1 + n));

    }
    return 0;
}
