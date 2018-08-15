//堆优化的dij
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int maxn = 100005;
const int inf = 0x3f3f3f3f;

struct node{
    int to;
    int id;
    int dis;
    node(int to, int id, int dis=1) : to(to), id(id), dis(dis){}
    node(){}
    bool operator < (const node &n) const{
        if(dis==n.dis)
            return to < n.to;
        return dis > n.dis;
    }
};

vector<node> vecs[maxn];
priority_queue<node> pq;
int dist[maxn];
int n, m;

void clear(){
    while (!pq.empty())
        pq.pop();
    for (int i = 1; i <= n;i++){
        vecs[i].clear();
    }
    fill(dist + 1, dist + n + 1, inf);
}

int main(int argc, char const *argv[])
{
    // freopen("1.in", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF)
    {
        clear();
        while(m--){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vecs[a].push_back(node(b, c));
            vecs[b].push_back(node(a, c));
        }
        dist[1] = 0;
        pq.push(node(1, 0));
        while(!pq.empty()){
            node x = pq.top();
            pq.pop();
            for(auto y:vecs[x.to]){
                if(x.id==y.id)
                    y.dis = 0;
                if(dist[y.to]>x.dis+y.dis){
                    dist[y.to] = x.dis + y.dis;
                    pq.push(node(y.to, y.id, dist[y.to]));
                }
            }
        }
        printf("%d\n", dist[n] == inf ? -1 : dist[n] - 1);//为啥要-1我也不知道
    }
    return 0;
}
