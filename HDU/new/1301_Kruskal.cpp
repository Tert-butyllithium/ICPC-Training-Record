// Kruskal
/*
 *题目大意： 多个村庄需要联通，求其最小生成树
 *采用Kruskal算法（贪心）
 */
#include <iostream>
#include <cstring>
#include <algorithm>

//存边
struct Edge
{
    int from;
    int to;
    int cost;
    bool operator <(const Edge& e){
        return this->cost < e.cost;
    }
};

Edge edges[100];

/*
 *这一部分是运用并查集，判断将要联通的两个点是否在同一棵树上 
 */
int fa[100];
int findfa(int val){
    if(fa[val]==val)
        return val;
    else
        return fa[val] = findfa(fa[val]);
}

void uni(int a,int b){
    int x = findfa(a);
    int y = findfa(b);
    fa[y] = x;
}

int main(int argc, char const *argv[]){
    int vil;
    while (scanf("%d", &vil)&&vil)
    {
        int v = -1;
        for (int i = 0; i < 100;i++){
            fa[i] = i;
        }

        for (int i = 1; i < vil; i++)
        {
            char c;
            int n;
            //注意getchar()之前需要再来一个吞掉空格
            getchar();
            scanf("%c%d", &c,&n);
            while (n--)
            {
                edges[++v].from = c - 'A';
                getchar();
                char tmp;
                scanf("%c%d", &tmp, &edges[v].cost);
                edges[v].to = tmp - 'A';
            }
        }
        //按照cost排序，优先选择最小的边
        std::sort(edges, edges + v + 1);
        int tot = 0;
        for (int i = 0; i <= v;i++){
            if(findfa(edges[i].from)!=findfa(edges[i].to)){
                uni(edges[i].from, edges[i].to);
                tot += edges[i].cost;
            }
        }
        printf("%d\n", tot);
    }
    return 0;
}

