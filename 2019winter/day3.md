# Day3 

## 最小割 - 最大权闭合子图

### Order

题意：有 n 个工作,m 个机器,每种机器有一个价格,每个工作需要使用一些机器,完成后可以获得收入。
你可以选择购买一些机器,求最大收益。收益 = 收入-支出。n, m ≤ 500

题解：

- 工作连源点，相连代表做了该项工作，边权为工作收益；
- 工作连机器，代表需要这些机器，边权为无穷大；
- 机器连汇点，代表**没有**购买这个机器，边权为机器价格；

那么一个完全图就代表：所有工作都做了，但是一个机器也没有买。目标：最小化合法的代价，即要么去掉某些工作，要么购买某些机器，也就是这个图的最小割。答案就是全部工作收益-最小割。

- 如果每种机器还可以按次数租用,求最大收益。
- 把工作连机器的边权更改为租用的费用而非无穷大。

### 汽车展览会

题意：n × m 的矩形停车场,要举办一个展览会。(i, j) 可以停 $a_{i,j}$ 辆车,边相邻的格子不能同时放车。求最多能停多少车。n, m ≤ 50

题解：首先对棋盘黑白染色，黑点与源相连，白点与汇相连，边权为$a_{i,j}$，然后每个黑点与相邻白点相连，边权为无穷大，那么总边权和-最小割即为答案

## A - [BZOJ 1497](https://www.lydsy.com/JudgeOnline/problem.php?id=1497)

题意：有n个用户需要通信，每个用户需要ai和bi两个基站，满足每个用户的需求可以获得ci的收益，建设第j个基站需要pi价格，求最大收益。

题解：最大权闭合子图裸题，可以用来测试板子

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5005;
const int maxm = 50005;
int a[maxm], b[maxm], c[maxm];
int p[maxn];
int n, m;
const int INF=0x3f3f3f3f;

struct E
{
    int to, cp;
    E(int to, int cp){
        this->to=to;
        this->cp=cp;
    }
};
struct Dinic
{
    static const int M = 1E6;
    int m, s, t;
    vector<E> edges;
    vector<int> G[M];
    int d[M];
    int cur[M];
    void init(int n, int s, int t)
    {
        this->s = s;
        this->t = t;
        for (int i = 0; i <= n; i++)
            G[i].clear();
        edges.clear();
        m = 0;
    }
    void addedge(int u, int v, int cap)
    {
        edges.push_back(E(v, cap));
        edges.push_back(E(u, 0));
        G[u].push_back(m++);
        G[v].push_back(m++);
    }
    bool BFS()
    {
        memset(d, 0, sizeof d);
        queue<int> Q;
        Q.push(s);
        d[s] = 1;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for(int i=0;i<G[x].size();i++)
            {
                E &e = edges[G[x][i]];
                if (!d[e.to] && e.cp > 0)
                {
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return d[t];
    }
    int DFS(int u, int cp)
    {
        if (u == t || !cp)
            return cp;
        int tmp = cp, f;
        for (int &i = cur[u]; i < G[u].size(); i++)
        {
            E &e = edges[G[u][i]];
            if (d[u] + 1 == d[e.to])
            {
                f = DFS(e.to, min(cp, e.cp));
                e.cp -= f;
                edges[G[u][i] ^ 1].cp += f;
                cp -= f;
                if (!cp)
                    break;
            }
        }
        return tmp - cp;
    }
    int go()
    {
        int flow = 0;
        while (BFS())
        {
            memset(cur, 0, sizeof cur);
            flow += DFS(s, INF);
        }
        return flow;
    }
} DC;


int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    long long sumofc = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        sumofc += c[i];
    }
    int s=0,t=n+m+10;

    DC.init(t+1,s,t);
    for(int i=1;i<=n;i++){
        DC.addedge(m+i,t,p[i]);
    }

    for(int i=1;i<=m;i++){
        DC.addedge(s,i,c[i]);
        DC.addedge(i,m+a[i],INF);
        DC.addedge(i,m+b[i],INF);
    }

    int res=DC.go();
    printf("%lld",sumofc-res);
    return 0;
}
```

## B - [Codeforces 1095F](https://codeforces.com/problemset/problem/1095/F)

题意：有n个点，每个点上都有一个权。可以任意连接两个点，使他们相连（无向）花费为这两个点权和，还有m组$x_i,y_i,w_i$，表示可以从$x_i$ 连到 $y_i$ 花费为 $w_i$，求最小生成树

题解：考虑贪心，我们在做krushkal的时候是按照边权从小到大枚举。对于每个点而言，他能形成的权值最小边一定是它与权值最小的点所连成的边，这样就可以得到n+m条边，做一遍krushkal即可

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 10;
struct edge{
    int from, to;
    ll val;

    edge(int from=0,int to=0,ll val=0):from(from),to(to),val(val){}
};
vector<edge> vec;
ll a[maxn];
int fa[maxn];

int findfa(int x){
    if(x==fa[x])
        return x;
    else
        return fa[x] = findfa(fa[x]);
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < maxn;i++)
        fa[i] = i;
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n;i++){
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= m;i++){
        int a, b;
        ll w;
        scanf("%d%d%lld", &a, &b, &w);
        vec.emplace_back(a,b,w);
    }

    int min_index = min_element(a + 1, a + 1 + n)-a;
    for (int i = 1; i <= n;i++){
        if(i!=min_index){
            vec.emplace_back(min_index, i, a[i] + a[min_index]);
        }
    }
    sort(vec.begin(), vec.end(), 
         [](const edge &e1, const edge &e2) { return e1.val < e2.val; });
    ll ans = 0;
    for (auto &e : vec)
    {
        int fx = findfa(e.from);
        int fy = findfa(e.to);
        if(fx!=fy){
            ans += e.val;
            fa[fx] = fy;
        }
    }
    printf("%lld", ans);
    return 0;
}
```

## C - Codeforces 980C

题意：给n个数字代表像素点的颜色，范围[0, 255]，你可以将值相邻的若干个数字分成一组，之后将这些数字全部变成最小的那个，例如可以将[0,1,2,3]分成一组，[4]单独一组，[5,6,7,8,9]分成一组，这样所有的k∈[5,9]都会变成5，k∈[0,3]都会变成3，k=4不变，要求每个组的长度不能超过k，求出如何分组使得给你的n个数字按照上述规则变换后得出的新序列字典序最小。

题解：一看到字典序就应该考虑贪心，用并查集维护每个集合的最小值和这个集合的大小，每次新加入元素时从小到大枚举可能的集合，如果两个集合元素个数和加上之间的差值小于等于k，就可以把当前元素合并到更小的那个去，否则直接输出当前集合的最小元素

```c++
#include <bits/stdc++.h>
const int maxp = 256;
int sz[maxp], fa[maxp];

int findfa(int x){
    if(x==fa[x])
        return x;
    else
        return fa[x] = findfa(fa[x]);
}

void uni(int x,int y){
    x = findfa(x);
    y = findfa(y);
    if(x==y)
        return;
    if (x > y)
        std::swap(x, y);
    sz[x] += sz[y];
    fa[y] = x;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < maxp;i++){
        fa[i] = i;
        sz[i] = 1;
    }
    int n,k;
    scanf("%d%d", &n,&k);
    while(n--){
        int x;
        scanf("%d", &x);
        int r = findfa(x);
        if(sz[r]==k){
            printf("%d ", r);
            continue;
        }

        for (int low = std::max(r - k + 1, 0); low <= x; low++)
        {
            if (sz[findfa(low)] + sz[r] + x - low <= k + 1)
            {
                for (int c = low + 1; c <= x; c++)
                    uni(low, c);
                printf("%d ", findfa(low));
                goto label;
                }
        }
        printf("%d ", r);

    label:;
    }
    return 0;
}
```

## D - [BZOJ 1061](https://www.lydsy.com/JudgeOnline/problem.php?id=1061)

题意：一个项目需要N 天才能完成，其中第i 天至少需要Ai 个人。 一共有M 种人可以招募。其中第i 类可以从第Si 天工作到第Ti 天，招募费用是每人Ci 元。求花费最少

题解：

- 单纯性+对偶原理：//TODO [refer](https://www.cnblogs.com/candy99/p/6188913.html) [code](https://www.cnblogs.com/Konjakmoyu/p/6441173.html)

- 或者经过一系列奇怪的转化变成最小费用最大流：把每一天作为一个点，从源点s给最左边的时间点引流，流的大小为U（U为大整数），然后每个时间点i向时间点i+1建边（i，i+1，U-Ai，0），最后设汇点为最右端的时间点。如果所有的时间点Ai都为0的话，流出的流量也为U.Ai不为0，那么源点到汇点的流量被截断了，就要其他支路流量来填补。第i类人建边(li,ri+1,INF,ci)。要求的是最小费用，跑最小费用流时，要求汇点流量必须为U，cost才是最小，否则无解。[refer](https://blog.csdn.net/swust_lian/article/details/50600611)

## E - BZOJ 1022

题意：反尼姆博弈

refer：[**组合游戏略述——浅谈SG游戏的若干拓展及变形.pdf**](https://github.com/oeddyo/algorithm/blob/master/resources/%E7%89%9B%E4%BA%BA%E8%B0%88ACM%E7%BB%8F%E9%AA%8C(%E5%8C%85%E6%8B%AC%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E8%AE%BA%E6%96%87)/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2009%E8%AE%BA%E6%96%87%E9%9B%86/2.%E8%B4%BE%E5%BF%97%E8%B1%AA%E3%80%8A%E7%BB%84%E5%90%88%E6%B8%B8%E6%88%8F%E7%95%A5%E8%BF%B0%E2%80%94%E2%80%94%E6%B5%85%E8%B0%88SG%E6%B8%B8%E6%88%8F%E7%9A%84%E8%8B%A5%E5%B9%B2%E6%8B%93%E5%B1%95%E5%8F%8A%E5%8F%98%E5%BD%A2%E3%80%8B/%E7%BB%84%E5%90%88%E6%B8%B8%E6%88%8F%E7%95%A5%E8%BF%B0%E2%80%94%E2%80%94%E6%B5%85%E8%B0%88SG%E6%B8%B8%E6%88%8F%E7%9A%84%E8%8B%A5%E5%B9%B2%E6%8B%93%E5%B1%95%E5%8F%8A%E5%8F%98%E5%BD%A2.pdf)

题解: 游戏分为两种情况

- 有 N 个堆，每个堆只有一个石子。此时当前仅当N为偶数时先手必胜
- 1. 当sg值不为0时：若还有至少两堆石子的数目大于 1，则先手将 SG 值变为 0 即可；若只有一堆石子数大于 1，则先手总可以将状态变为有奇数个 1。所以，当 SG 不为 0 时先手必胜。
  2. 当sg值为0时：至少有两堆石子的数目大于 1，则先手决策完之后，必定至少有堆的石子数大于 1，且 SG 值不为 0，由上段的论证我们可以发现，此时，无论先手如何决策，都只会将游戏带入先手必胜局，所以先手必败。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;

int main(){
    ios::sync_with_stdio(false);
    int round;
    cin>>round;

    while(round--){
        int ans=0;
        int n;
        cin>>n;
        bool allone=1;
        while(n--){
            int x;
            cin>>x;
            if(x>1) allone=0;
            ans^=x;
        }
        if((ans==0&&allone)||(ans&&!allone)){
            cout<<"John"<<endl;
        }
        else{
            cout<<"Brother"<<endl;
        }
    }
}
```

## F - [Codeforces 1097C](https://codeforces.com/problemset/problem/1097/C) 

题意：给n个括号序列仅由“(”和“)”构成，一个合法的括号序列指序列中每个括号一定有且仅有一个相反的括号与之配对。问这n个括号序列中有最多能找到多少对使得两个序列拼起来构成一个合法的括号序列

题解：将一个括号序列的 “(”看做 +1， “)” 看做 −1 ，我们可以用二元组 (sum,Min) 来描述一个括号序列，其中 sum 表示序列和， Min 表示前缀最小值。若 sum≤0 ，要求 Min=sum ，否则，要求 Min=0 。(也就是避免出现“)(”出现，前缀最小值表示没有被匹配的右括号的最大数量，如果在这之后又出现了没有被匹配的左括号，就应该删掉这个序列)满足上述条件的 sum 之和为 0 的括号序列可以配对，贪心即可。

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn=5e5+10;
const int inf=0x3f3f3f3f;
unordered_map<int,int> ma;
char str[maxn];

int cal(){//我用了一些非常复杂的状态来做可行到不可行的转移
    int len=strlen(str);
    int left=0,right=0;
    int err=0;
    bool first;
    if(str[0]=='(') {left++;first=true;}
    else {right++;first=false;}
    for(int i=1;i<len;i++){
        if(first){
            if(str[i]==')'){
                if(left){left--;}
                else{
                    first=false;
                    right++;
                }
            }
            else{
                left++;
            }
        }
        else{
            if(str[i]=='('){
                    err++;
                    left++;
            }
            else{
                if(left&&err){
                    left--;err--;
                }
                else{
                    right++;
                }
            }

        }
    }
    if(err) return inf;
    return left-right;
}


int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",str);
        int c=cal();
        // cout<<c<<endl;
        if(c!=inf){
            if(ma.find(c)==ma.end()){
                ma[c]=1;
            }
            else{
                ma[c]+=1;
            }
        }
    }
    int ans=0;
    for(auto c:ma){
        if(c.first<0){
            if(ma.find(-c.first)!=ma.end()){
                ans+=min(c.second,ma[-c.first]);
            }
        }
    }
    if(ma.find(0)!=ma.end()){
        ans+=ma[0]/2;
    }
    printf("%d",ans);
    return 0;
}
```

## G - [Codeforces 1096C](https://codeforces.com/problemset/problem/1096/C)

题意：给一个角度ang，求最小的正n变形使得在这个正n变形中找三个点构成角ang

题解：正n变形就是对圆的n等分，三个点一定是这个圆上的圆周角，利用圆心角等于两倍圆周角这个性质可以求出答案为180/gcd(180,ang)，注意如果这样算的角度刚好是180 x (n-1)/n，如ang=120, 求出n=3，这时我们需要的构成圆周角就的第三个点必须在两个相邻点之间，也就是此时答案需要 x 2

```c++
#include <bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
    if(b==0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);
    while(n--){
        int ang;
        scanf("%d",&ang);
        int ans=180/gcd(180,ang);
        if(ang==180*(ans-1)/ans){
            ans*=2;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

