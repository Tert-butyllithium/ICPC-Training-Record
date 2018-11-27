//see https://blog.csdn.net/u013534123/article/details/81610895
//reference https://blog.csdn.net/qingqiu_WD/article/details/81559196
#include<bits/stdc++.h>
#define LL long long
#define IO ios::sync_with_stdio(0);cin.tie(0)
const int N = 2e5 + 10;
using namespace std;

struct edge
{
    int x,y,w;
 
    bool operator < (const edge a) const
    {
        return w>a.w;
    }
 
} e[N];
 
int n,m,f[N],fa[N],dep[N],pre[N];
//pre[i]： index in g[father of i](a vector) represents the edge to node i
int cnt[N],sz[N];
struct Edge{int y,w;};
vector<Edge> g[N];
vector<edge> G;
 
int find(int x)
{
    return f[x]==x?x:f[x]=find(f[x]);
}
 
void dfs(int x,int ff,int d)
{
    fa[x]=ff; dep[x]=d;
    for(int i=0;i<g[x].size();i++)
    {
        int y=g[x][i].y;
        if (y==ff) continue;
        dfs(y,x,d+1); pre[y]=i;
    }
}
 
int main()
{
    IO; int T;
    cin>>T; 
    while(T--)
    {
        cin>>n>>m;
        G.clear();
        for(int i=1;i<=n;i++)
        {
            f[i]=i,g[i].clear();
            sz[i] = 1;
        }
        for(int i=1;i<=m;i++)
            cin>>e[i].x>>e[i].y>>e[i].w;
        sort(e+1,e+1+m);
                                                    //kruskal 最大生成树
                                                
        for(int i=1;i<=m;i++)
        {
            int x=e[i].x,y=e[i].y,w=e[i].w;
            if (find(x)!=find(y))
            {
                f[find(x)]=find(y);
                g[x].push_back(Edge{y,w});
                g[y].push_back(Edge{x,w});
            } else G.push_back(edge{x,y,w});
        }
                                                    //get fa[] & pre[] & dep[]
        dfs(1,0,0);
        //处于同一个环的两个点必须割掉两条边，并且最小的边一定会被割掉
        //最小的边一定不在最大生成树里面，把这些边的权值加到这个环的每条边上
                                                    //delete the minimum edge in the circle
        for(int i=0;i<G.size();i++)
        {
            int x=G[i].x,y=G[i].y,w=G[i].w;
            if (dep[x]<dep[y]) swap(x,y);
            for(;dep[x]>dep[y];x=fa[x])
                g[fa[x]][pre[x]].w+=w;
            for(;x!=y;x=fa[x],y=fa[y])
            {
                g[fa[x]][pre[x]].w+=w;
                g[fa[y]][pre[y]].w+=w;
            }
        }
                                                    //rebuild the graph and sort
        int tot=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<g[i].size();j++)
                if (dep[g[i][j].y]>dep[i])
                    e[++tot]=edge{i,g[i][j].y,g[i][j].w};
        sort(e+1,e+1+tot);
                                                    //initial dsu
        for(int i=1;i<=n;i++) f[i]=i;
                                                    //calculate the answer
        unsigned long long ans=0;
        for(int i=1;i<=tot;i++)
        {
            int x=e[i].x,y=e[i].y,w=e[i].w;
            x=find(x); y=find(y); f[x]=y;
            ans += 1ll * sz[x] * sz[y] * w;
            sz[y] += sz[x];

        }
 
        cout<<ans<<endl;
    }
    return 0;
}
