/* 给一些棋子，若一个棋子只经过行变换或者列变换就能到达另一个棋子，这些能到达的棋子称为一个set，
 * 若 a可以到达b，b可到达c，那么a，b，c 也是一个set
 * 给n个棋子并且标号（1～n），并给出m对编号，要求这些对的棋子类型出现在一个set，
 * 并且每两个相同类型的棋子一定属于同一个set
 * 把每一行（平行）作为只属于特定类型，比如第一行只放类型为1的棋子
 * 然后对于第i对，就把它放在第i列上，两个元素各自在所在行
 * 最后随便找个地方安排那些孤单的点
 * see also：https://blog.csdn.net/Link_Ray/article/details/83446642
 */
 
#include <bits/stdc++.h>
using QAQ = long long;
const int maxn=105;
const int inf = 1e9;

struct grid
{
    //这个color并没有什么用
    int x, y, color;
    grid(){}
    grid(int x,int y,int color):x(x),y(y),color(color){}
};
std::vector<grid> vec[maxn];
int appers[maxn];

int main(int argc, char const *argv[])
{

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        appers[x]++;
        appers[y]++;
        //x放在行数为x，列数为i；y放在行数为x，列数为i
        vec[x].push_back(grid(x, i, x));
        vec[y].push_back(grid(y, i, y));
    }

    for (int i = 1; i <= n; i++)
    {
        if (vec[i].empty())
        {
            vec[i].push_back(grid(inf-i,inf-i, i));
        }
    }


    for (int i = 1; i <= n;i++){
        printf("%d\n", (int)vec[i].size());
        for(auto g:vec[i]){
            printf("%d %d\n", g.x, g.y);
        }
    }
}
