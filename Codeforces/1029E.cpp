//利用了set的神奇性质：遍历时是升序
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;

int dep[maxn];
int par[maxn];
bool vis[maxn];
vector<int> vecs[maxn];
set<pair<int,int> > se;

void dfs(int anc,int cur){
    par[cur] = anc;
    dep[cur] = dep[anc] + 1;
    for (auto c : vecs[cur])
    {
        if(c!=anc){
            dfs(cur, c);
        }
    }
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n;i++){
        int u, v;
        scanf("%d%d", &u, &v);
        vecs[u].push_back(v);
        vecs[v].push_back(u);
    }
    memset(vis, 0, sizeof(vis));
    dep[0] = -1;
    dfs(0, 1);
    for (int i = 1; i <= n;i++){
        if(dep[i]>2)
            se.insert(make_pair(-dep[i],i));
    }
    int ans = 0;
    while (!se.empty())
    {
        auto cur = se.begin();
        int fa = par[cur->second];
        auto ir = se.find(make_pair(-dep[fa],fa));
        if(ir!=se.end()){
            se.erase(ir);
        }
        for(auto c:vecs[fa]){
            auto id = se.find(make_pair(-dep[c],c));
            if(id!=se.end())
                se.erase(id);
        }
        ans++;
    }
    /* for (int i = 1; i <= n;i++){
        printf("%d ", dep[i]);
    }
    puts(""); */
    printf("%d\n", ans);
    return 0;
}
