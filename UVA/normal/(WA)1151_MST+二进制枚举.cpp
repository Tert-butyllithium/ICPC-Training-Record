#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 1005
using namespace std;

struct Edge
{
    int from;
    int to;
    int cost;

    bool operator < (const Edge& e){
        return cost < e.cost;
    }
};

struct Point
{
    int x;
    int y;
};

Edge edges[N*N];
Point points[N];
vector<int> vec_point[9];
int cost_[9]; 
int fa[N];


int find(int val){
    if(val==fa[val])
        return val;
    else
        return fa[val] = find(fa[val]);
}

void uni(int a,int b){
    int x = find(a);
    int y = find(b);
    fa[y] = x;
}

void ini(int n){
    for (int i = 0; i <= n;i++)
      fa[i]=i;
}

void clear(){
    for (int i = 0; i < 9;i++){
        vecs[i].clear();
        vec_point[i].clear();
        cost_[i] = 0;
    }
}

int dis(int a,int b){
    return (points[a].x - points[b].x) * (points[a].x - points[b].x) + (points[a].y - points[b].y) * (points[a].y - points[b].y);
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m;i++){
            int cs;
            scanf("%d%d", &cs, &cost_[i]);
            for (int j = 0; j < cs;j++){
                int tmp;
                scanf("%d", &tmp);
                vec_point[i].push_back(tmp);
            }
        }
        for (int i = 1; i <= n;i++){
            scanf("%d%d", &points[i].x, &points[i].y);
        }

        int v = -1;
        for (int i = 1;i<=n;i++){
            for (int j = i+1; j <= n;j++){
                edges[++v].from = i;
                edges[v].to = j;
                edges[v].cost = dis(i, j);
            }
        }

        ini(n);
        int tot = 0;
        sort(edges, edges + v + 1);
        for (int i = 0; i <= v;i++){
            if(find(edges[i].from)!=find(edges[i].to)){
                uni(edges[i].from, edges[i].to);
                tot += edges[i].cost;

            }
            
        }
        //二进制枚举，所有子网络枚举。（子网络最多8个）
        for (int cc = 0; cc < (1 << m);cc++){
            ini(n);
            int part = 0;
            for (int i = 0; i < m;i++){
                if(cc&(1<<i)){
                    part += cost_[i];
                    for (int j = 1; j < vec_point[i].size();j++){
                        if(find(vec_point[i][j])!=find(vec_point[i][0])){
                            uni(vec_point[i][j], vec_point[i][0]);
                        }
                    }
                }
            }

            int tot2 = 0;
            sort(edges, edges + v + 1);
            for (int i = 0; i <= v; i++)
            {
                if (find(edges[i].from) != find(edges[i].to))
                {
                    uni(edges[i].from, edges[i].to);
                    tot2 += edges[i].cost;
                }
            }

            tot = min(tot, part + tot2);
        }

        printf("%d", tot);
        if(T)
            putchar('\n');
        clear();
    }
    return 0;
}
