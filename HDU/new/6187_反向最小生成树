//这个题的坐标点并没有什么卵用
//主要是要转化：拆掉最少的等价于找到“最大生成树”，不是为了使其联通，而是保留一棵树而非闭合的图

#include <iostream>
#include <cstring>
#include <algorithm>

#define maxn 200007

struct Edge{
    int from;
    int to;
    int cost;
    bool operator <(const Edge& e){
        return this->cost>e.cost;
    }
};
Edge edges[maxn];

int fa[maxn];
int find(int a){
    if(fa[a]==a)
       return a;
    else
       return fa[a]=find(fa[a]);
}

bool uni(int a,int b){
    int x=find(a);
    int y=find(b);
    fa[y]=x;
    return x!=y;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=0;i<=n;i++)
            fa[i]=i;

        for(int i=0;i<n;i++){
            int x,y;
            scanf("%d%d",&x,&y);
        }
        int tot=0;
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&edges[i].from,&edges[i].to,&edges[i].cost);
            tot+=edges[i].cost;
        }
        std::sort(edges,edges+m);
        int num=0;
        for(int i=0;i<m;i++){
            if(find(edges[i].from)!=find(edges[i].to)){
               uni(edges[i].from,edges[i].to);
               num++;
               tot-=edges[i].cost;
            }
        }
        printf("%d %d\n",m-num,tot);
    }
}
