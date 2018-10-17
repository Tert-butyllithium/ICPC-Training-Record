//dfs的错误:由于可能后一次更新所需的步数更小，所以遇到这种情况需要整体更新，导致tle
//dfs+bfs 由于上下走是没有限制的，所以优先往上下走，也就是对上下走dfs，对左右走bfs，也就是用一个deque来维护
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2018;
char g[maxn][maxn];
bool vis[maxn][maxn];

int ans;
struct grid{
    int i,j,x,y;
    grid(){}
    grid(int i,int j,int x,int y):i(i),j(j),x(x),y(y){}
};

inline bool judge(int i,int j,int x,int y){
    return vis[i][j]||!g[i][j]||x<0||y<0||g[i][j]=='*';
}


inline bool judge(grid g){
    return judge(g.i, g.j,g.x, g.y);
}


void dfs(int i,int j,int x,int y){
    deque<grid> que;
    que.emplace_back(i,j,x,y);
    while(!que.empty()){
        auto cur=que.front();
        que.pop_front();
        if(judge(cur)) continue;
        vis[cur.i][cur.j]=1;
//        cout << cur.i << " " << cur.j << endl;
        ans++;
        que.push_front(grid(cur.i-1,cur.j,cur.x,cur.y));
        que.push_front(grid(cur.i+1,cur.j,cur.x,cur.y));
        que.emplace_back(cur.i,cur.j-1,cur.x-1,cur.y);
        que.emplace_back(cur.i,cur.j+1,cur.x,cur.y-1);
    }

}

int main(int argc, char const *argv[])
{
    int n, m, r, c, x, y;
    scanf("%d%d%d%d%d%d", &n, &m, &r, &c, &x, &y);
    for (int i = 1; i <= n;i++){
        scanf("%s", g[i] + 1);
    }
    dfs(r, c, x, y);
    printf("%d\n", ans);
}
