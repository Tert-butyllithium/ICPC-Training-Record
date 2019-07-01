# 暑期集训Day 1解题报告

通过题数：11/12

## A [Jungle Roads](https://cn.vjudge.net/problem/POJ-1251)

题意： N个顶点的无向图,给你每条边的长度,要你求该图的最小生成树.其中每个点用大写字母A-Z表示.

题解：最小生成树裸题

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//using ll = long long;
const int maxn = 30;
struct edge
{
    int from, to, val;
    
    edge(char from=0,char to=0,int val=0):from(from-'A'+1),to(to-'A'+1),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

vector<edge> vec;

int fa[maxn];

int findfa(int x){
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    int n;
    while (scanf("%d",&n)!=EOF&&n)
    {
        for (int i = 0; i < maxn;i++){
            fa[i] = i;
        }
        vec.clear();
        --n;
        while(n--){
            char from[10];
            int k;
            scanf("%s%d", from, &k);
            while(k--){
                char to[10];
                int val;
                scanf("%s%d",to,&val);
                vec.push_back(edge(from[0], to[0], val));
            }
        }
        sort(vec.begin(), vec.end());
        long long res = 0;
        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res+=e.val;
            }
        }
        printf("%lld\n", res);
    }
}
```

通过时间：34

## B [Networking](https://cn.vjudge.net/contest/308403#problem/B)

题意：给n个点，m条边，求最小生成树

题解：最小生成树裸题

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//using ll = long long;
const int maxn = 55;
struct edge
{
    int from, to, val;
    
    edge(int from=0,int to=0,int val=0):from(from),to(to),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

vector<edge> vec;

int fa[maxn];

int findfa(int x){
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    int n;
    while (scanf("%d",&n)!=EOF&&n)
    {
        for (int i = 0; i < maxn;i++){
            fa[i] = i;
        }
        vec.clear();
        int m;
        scanf("%d", &m);
        while(m--){
            int f, t, w;
            scanf("%d%d%d", &f, &t, &w);
            vec.push_back(edge(f, t, w));
        }
        sort(vec.begin(), vec.end());
        long long res = 0;
        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res+=e.val;
            }
        }
        printf("%lld\n", res);
    }
}
```

通过时间：38

## C [Building a Space Station](https://cn.vjudge.net/contest/308403#problem/C)

题意：给n个球的坐标和半径，如果两个球相交或者重合那么视为两个球联通，现在可以在球面之间做一些通道(通道宽度不计)，求最小代价使得全部联通

题解：最小生成树裸题

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
//using ll = long long;
const int maxn = 105;
struct edge
{
    int from, to;
    double val;

    edge(int from=0,int to=0,double val=0):from(from),to(to),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

struct ball{
    double x, y, z, r;
};

vector<edge> vec;
ball balls[maxn];
int fa[maxn];

double sq(double x){
    return x *x;
}

double compute(const ball& a,const ball& b){
    double dist = sqrt(sq(a.x - b.x) + sq(a.y - b.y) + sq(a.z - b.z));
    if(dist<=a.r+b.r){
        return 0;
    }
    else{
        return dist - a.r - b.r;
    }
}

int findfa(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    int n;
    while (scanf("%d",&n)!=EOF&&n)
    {
        for (int i = 0; i < maxn;i++){
            fa[i] = i;
        }
        for (int i = 0; i < n;i++){
            scanf("%lf%lf%lf%lf", &balls[i].x, &balls[i].y, &balls[i].z, &balls[i].r);
        }
        vec.clear();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n;j++){
                vec.push_back(edge(i + 1, j + 1, compute(balls[i], balls[j])));
            }
        }
        sort(vec.begin(), vec.end());
        double res = 0;
        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res+=e.val;
            }
        }
        printf("%.3f\n", res);
    }
}
```

通过时间：53(+1)

RE的一发是因为数组开小了

## D [Constructing Roads](https://cn.vjudge.net/contest/308403#problem/D)

题意：现有N个点，现给出一个N\*N的图表示每两个点之间的距离，另外还有m条边表示已经连通。求最小生成树

题解：最小生成树裸题

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
//using ll = long long;
const int maxn = 105;
int dist[maxn][maxn];
struct edge
{
    int from, to;
    int val;

    edge(int from=0,int to=0,int val=0):from(from),to(to),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};
vector<edge> vec;
int fa[maxn];


int findfa(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        for (int i = 0; i < maxn;i++){
            fa[i] = i;
        }
        vec.clear();
        for (int i = 1; i <= n;i++){
            for (int j = 1; j <= n;j++){
                scanf("%d", &dist[i][j]);
            }
        }
        for (int i = 1; i <= n;i++){
            for (int j = i + 1; j <= n;j++){
                vec.push_back(edge(i, j, min(dist[i][j],dist[j][i])));
            }
        }
        int m;
        scanf("%d", &m);
        while(m--){
            int x, y;
            scanf("%d%d", &x, &y);
            vec.push_back(edge(x, y, 0));
        }

        sort(vec.begin(), vec.end());
        long long res = 0;
        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res+=e.val;
            }
        }
        printf("%lld\n", res);
    }
}
```

通过时间：60

## E [Truck History](https://cn.vjudge.net/contest/308403#problem/E)

题意：n个点，每个点有一个长度为7的字符串。距离为两个字符串的汉明距离，求最小生成树

题解：最小生成树裸题

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
//using ll = long long;
const int maxn = 2005;
int dist[maxn][maxn];
struct edge
{
    int from, to;
    int val;

    edge(int from=0,int to=0,int val=0):from(from),to(to),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

struct node{
    char str[10];
};
node nodes[maxn];

int compute(const node& a,const node& b){
    int res = 0;
    for (int i = 0; i < 7; i++)
    {
        res += (a.str[i] != b.str[i]);
    }
    return res;
}

vector<edge> vec;
int fa[maxn];


int findfa(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    int n;
    while (scanf("%d",&n)!=EOF&&n)
    {
        for (int i = 0; i < maxn;i++){
            fa[i] = i;
        }
        vec.clear();
        for (int i = 1; i <= n;i++){
            scanf("%s", nodes[i].str);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                vec.push_back(edge(i, j, compute(nodes[i],nodes[j])));
            }
        }

        sort(vec.begin(), vec.end());
        long long res = 0;
        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res+=e.val;
            }
        }
        printf("The highest possible quality is 1/%lld.\n", res);
    }
}
```

通过时间：69

## F [Arctic Network](https://cn.vjudge.net/contest/308403#problem/F)

题意：有n个城市，当两个城市直线距离小于D时可以通过无线电连接，另外有s个卫星信道，两个有卫星信道的城市可以直接连接。求最小的D使得所有城市相互连接

题解：先搞出最小生成树，然后可以删掉最大的s-1条边。剩下的最大的就是答案

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <list>
#include <queue>
#include <cstring>
using namespace std;
//using ll = long long;
const int maxn = 505;
int dist[maxn][maxn];
bool vis[maxn];
struct edge
{
    int from, to;
    double val;
    
    edge(int from=0,int to=0,double val=0):from(from),to(to),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

struct node{
    int x, y;
};
node nodes[maxn];

double sq(double x){
    return x * x;
}

double compute(const node& a,const node& b){
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

vector<edge> vec;
int fa[maxn];


int findfa(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    // int n;
    int round;
    scanf("%d", &round);
    while(round--)
    {
        int n, s;
        scanf("%d%d", &s, &n);
        for (int i = 0; i < maxn; i++)
        {
            fa[i] = i;
        }
        vec.clear();
        for (int i = 1; i <= n;i++){
            scanf("%d%d", &nodes[i].x,&nodes[i].y);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                vec.push_back(edge(i, j, compute(nodes[i],nodes[j])));
            }
        }
        
        sort(vec.begin(), vec.end());
        priority_queue<edge> res;

        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res.push(e);
            }
        }
      	//注释部分为第一遍错误的解法：认为删掉一条边需要消耗两个卫星信道
        // memset(vis,0,sizeof(vis));
        // while(s>0&&res.size()){
        //     if(vis[res.top().from]&&vis[res.top().to]){
        //         res.pop();
        //     }
        //     else if(vis[res.top().from]||vis[res.top().to]){
        //         vis[res.top().from]=vis[res.top().to]=1;
        //         s--;
        //         res.pop();
        //     }
        //     else{
        //         vis[res.top().from]=vis[res.top().to]=1;
        //         if(s<2) break;
        //         s-=2;
        //         res.pop();
        //     }
        // }
        int r = s-1;
        while(r--){
            res.pop();
        }
        printf("%.2f\n", res.top().val);
    }
}
```

通过时间：91(+1)

## G [Highways](https://cn.vjudge.net/contest/308403#problem/G)

题意：给n个城市修建高速公路，使得每两个城市都相互连通。其中有一些已经修建好了高速公路。输出要在哪些个城市之间修建高速公路

题解：把修建好了的城市搞成边为0的边（或者直接在并查集里面union）就完事了，然后对于每条边不需要累加，直接输出即可

```c++
#pragma GCC optimize(2)
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
using namespace std;
//using ll = long long;
const int maxn = 755;
typedef pair<int, int> pii;
struct edge
{
    int from, to;
    double val;

    edge(int from = 0, int to = 0, double val = 0) : from(from), to(to), val(val) {}

    bool operator<(const edge &e) const
    {
        return val < e.val;
    }
};

struct node
{
    int x, y;
};
node nodes[maxn];

double sq(double x)
{
    return x * x;
}

double compute(const node &a, const node &b)
{
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

edge vec[maxn * maxn + 1000];
int fa[maxn];

int findfa(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < maxn; i++)
    {
        fa[i] = i;
    }
    // vec.clear();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &nodes[i].x, &nodes[i].y);
    }
    int m;
    scanf("%d", &m);
    int cnt = 0;
    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int fx = findfa(x);
        int fy = findfa(y);
        if(fx!=fy){
            fa[fy] = fx;
        }
        // vec[cnt++] = edge(x, y, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            vec[cnt++] = (edge(i, j, compute(nodes[i], nodes[j])));
        }
    }
    sort(vec, vec + cnt);
    for (int i = 0; i < cnt; i++)
    {
        edge e = vec[i];
        int fx = findfa(e.from);
        int fy = findfa(e.to);
        if (fx != fy)
        {
            fa[fy] = fx;
            if (e.val != 0)
            {
                printf("%d %d\n", e.from, e.to);
            }
        }
    }

}
```

TLE, MLE 了数发，MLE是因为开始的时候我记录了这些个元组最后再输出的，TLE是因为在最外套了一层`while(scanf("%d",&n)!=EOF)` (傻逼poj)

通过时间：120(+5)

## H [Agri-Net](https://cn.vjudge.net/contest/308403#problem/H)

题意：同D，还更简单

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
//using ll = long long;
const int maxn = 105;
int dist[maxn][maxn];
struct edge
{
    int from, to;
    int val;

    edge(int from=0,int to=0,int val=0):from(from),to(to),val(val){}
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

struct ball{
    double x, y, z, r;
};

vector<edge> vec;
int fa[maxn];


int findfa(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

int main(){
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        for (int i = 0; i < maxn;i++){
            fa[i] = i;
        }
        vec.clear();
        for (int i = 1; i <= n;i++){
            for (int j = 1; j <= n;j++){
                scanf("%d", &dist[i][j]);
            }
        }
        for (int i = 1; i <= n;i++){
            for (int j = i + 1; j <= n;j++){
                vec.push_back(edge(i, j, min(dist[i][j],dist[j][i])));
            }
        }

        sort(vec.begin(), vec.end());
        long long res = 0;
        for (int i=0;i<vec.size();i++)
        {
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res+=e.val;
            }
        }
        printf("%lld\n", res);
    }
}
```

通过时间：123

## I [Borg Maze](https://cn.vjudge.net/contest/308403#problem/I)

题意：给一个迷宫，迷宫里面有几种类型的格子：“S”，“A”，“ ”(空格)，和“#”。“#”代表墙，现在要从“S”出发，在你可以使用分身术的情况下，求经过所有“A”的总距离

题解：先BFS求出每两个点的距离，然后建图跑最小生成树即可

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
// using ll = long long;
// using pii = pair<int, int>;
const int maxn = 51;
// const int maxm = 102;
typedef pair<int, int> pii;
char g[maxn][maxn];
int dis[maxn][maxn];
int fa[maxn * maxn];
bool vis[maxn][maxn];
bool mark[maxn][maxn];
const int inf = 0x3f3f3f3f;

struct edge{
    pii from, to;
    int val;
    
    bool operator < (const edge& e) const{
        return val < e.val;
    }
};

vector<edge> vec;

void bfs(int i, int j)
{
    memset(dis, inf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[i][j] = 0;
    queue<pii> que;
   vis[i][j]=1;
    que.push(make_pair(i,j));
    while(!que.empty()){
        pii top = que.front();
        que.pop();
        // vis[top.first][top.second]=1;
        if(g[top.first+1][top.second]!='#'
           &&g[top.first+1][top.second]!='\0'
           &&(!vis[top.first+1][top.second])){
            que.push(make_pair(top.first + 1, top.second));
            vis[top.first+1][top.second]=1;
            dis[top.first + 1][top.second] = min( dis[top.first + 1][top.second],
                                                 dis[top.first][top.second] + 1);
        }
        if (g[top.first - 1][top.second] != '#' 
            && g[top.first - 1][top.second] != '\0'
            &&(!vis[top.first-1][top.second]))
        {
            que.push(make_pair(top.first - 1, top.second));
            vis[top.first-1][top.second]=1;
            dis[top.first - 1][top.second] =min(dis[top.first - 1][top.second], 
                                                dis[top.first][top.second] + 1);
        }
        if (g[top.first][top.second+1] != '#' && 
            g[top.first][top.second+1] != '\0'&&(!vis[top.first][top.second+1]))
        {
            que.push(make_pair(top.first, top.second+1));
            vis[top.first][top.second+1]=1;
            dis[top.first][top.second+1] =min(dis[top.first][top.second+1], 
                                              dis[top.first][top.second] + 1);
        }
        if (g[top.first][top.second-1] != '#' && 
            g[top.first][top.second-1] != '\0'&&(!vis[top.first][top.second-1]))
        {
            que.push(make_pair(top.first, top.second-1));
            vis[top.first][top.second-1]=1;
            dis[top.first][top.second-1] = min(dis[top.first][top.second-1], 
                                               dis[top.first][top.second] + 1);
        }
        if(g[top.first][top.second]=='A'||g[top.first][top.second]=='S'){
            vec.push_back((edge){make_pair(i, j), top, dis[top.first][top.second]});
        }
    }
}

int findfa(int x){
    if(x==fa[x])
        return x;
    return fa[x] = findfa(fa[x]);
}

int findfa(pii p){
    return findfa(p.first + 51 * p.second);
}

int main(){
    // ios::sync_with_stdio(false);
    int round;
    scanf("%d", &round);
    // cin >> round;
    while (round--)
    {
        int x, y;
        vec.clear();
        memset(mark, 0, sizeof(mark));
        scanf("%d%d", &x, &y);
        // getchar();
        char tmp[100];
        gets(tmp);
        for (int i = 1; i <= y; i++)
        {
            // fgets(g[i] + 1, 55, stdin);
            gets(g[i] + 1);
        }
        for (int i = 0;i<maxn*maxn;i++){
            fa[i] = i;
        }
        for (int i = 1; i <= y;i++){
            for (int j = 1; j <= x;j++){
                if(g[i][j]=='A'||g[i][j]=='S'){
                    bfs(i, j);
                }
            }
        }
        sort(vec.begin(), vec.end());
        long long res = 0;
        for (int i = 0; i < vec.size();i++){
            edge e=vec[i];
            int fx = findfa(e.from);
            int fy = findfa(e.to);
            if(fx!=fy){
                fa[fy] = fx;
                res += e.val;
            }
        }
        printf("%lld\n", res);
    }
}
```

本题没有通过，之间一直MLE。唯一有可能超限的地方是bfs过程queue太大爆炸了。造成这种错误的原因是在bfs过程中选择pop(dequeue)的时候打vis标记，但是实际上应该在push(enqueue)的过程打vis标记(这似乎与dfs不同)

## J [The Unique MST](https://cn.vjudge.net/contest/308403#problem/J)

题意：给一张图，问这张图的最小生成树是否是唯一的。

题解：似乎有很多种方法来做这个题，但是最简单的一种当然就是枚举每条边试着删掉看最小生成树是否会改变。注意要防止删了一条边之后整张图不连通

```c++
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
//using ll = long long;
const int maxn = 105;
int n, m;
struct edge
{
    int from, to;
    int val;
    int id;
    
    edge(int from=0,int to=0,int val=0):from(from),to(to),val(val){}
    
    bool operator <(const edge& e) const{
        return val < e.val;
    }
};

vector<edge> vec;
int fa[maxn];

int findfa(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x] = findfa(fa[x]);
}

vector<int> ids;
long long go(int mask){
    for (int i = 0; i < maxn; i++)
    {
        fa[i] = i;
    }
    long long res = 0;
    for (int i=0;i<vec.size();i++)
    {
        if(i==mask) continue;
        edge e=vec[i];
        int fx = findfa(e.from);
        int fy = findfa(e.to);
        if(fx!=fy){
            fa[fy] = fx;
            res+=e.val;
            if(mask==-1){
                ids.push_back(i);
            }
        }
    }
    for(int i=2;i<=n;i++){
        if(findfa(i)!=findfa(1)){
            return -1;
        }
    }
    
    return res;
}

int main(){
    int round;
    scanf("%d", &round);
    while(round--)
        // while (scanf("%d", &n) != EOF)
    {
        
        scanf("%d%d",&n,&m);
        
        vec.clear();
        for (int i = 1; i <= m;i++){
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            vec.push_back(edge(x,y,w));
        }
        sort(vec.begin(), vec.end());
        ids.clear();
        long long correct=go(-1);
        bool flag=true;
        for(int i=0;i<ids.size();i++){
            long long cur=go(ids[i]);
            if(cur==correct){
                flag=false;
            }
        }
        if(flag)
            printf("%lld\n", correct);
        else
            puts("Not Unique!");
    }
}
```

通过时间：215(+1)，wa一发是脑子不清醒的时候wa掉的

## M [畅通工程再续](https://cn.vjudge.net/contest/308403#problem/M)

题意：给n个点的坐标，求最小生成树。但是边长不能小于10，不能大于1000。

题解：最小生成树裸题

```c++
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
//using ll = long long;
const int maxn = 105;
int n, m;
struct edge
{
    int from, to;
    double val;

    edge(int from = 0, int to = 0, double val = 0) : from(from), to(to), val(val) {}

    bool operator<(const edge &e) const
    {
        return val < e.val;
    }
};

struct island
{
    int x, y;
};

island lands[maxn];

double sq(double x)
{
    return x * x;
}

double compute(const island &x, const island &y)
{
    return sqrt(sq(x.x - y.x) + sq(x.y - y.y));
}

vector<edge> vec;
int fa[maxn];

int findfa(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = findfa(fa[x]);
}

vector<int> ids;
double go(int mask)
{
    for (int i = 0; i < maxn; i++)
    {
        fa[i] = i;
    }
    double res = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == mask)
            continue;
        edge e = vec[i];
        int fx = findfa(e.from);
        int fy = findfa(e.to);
        if (fx != fy)
        {
            fa[fy] = fx;
            res += e.val;
            if (mask == -1)
            {
                ids.push_back(i);
            }
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (findfa(i) != findfa(1))
        {
            return -1;
        }
    }

    return res;
}

int main()
{
    int round;
    scanf("%d", &round);
    while (round--)
    {
        // int n;
        scanf("%d", &n);
        vec.clear();
        // m=n*(n-1)/2;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &lands[i].x, &lands[i].y);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                double dist = compute(lands[i], lands[j]);
                if (dist >= 10 && dist <= 1000)
                {
                    vec.push_back(edge(i, j, dist * 100));
                }
            }
        }
        sort(vec.begin(), vec.end());
        double res = go(-1);
        if (res != -1)
            printf("%.1f\n", res);
        else
            puts("oh!");
    }
}
```

通过时间：230
