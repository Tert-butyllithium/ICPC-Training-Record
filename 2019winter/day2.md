# Day 2

难度 C < D < F < B < E < A < G

## A - [2018 Asia EC Final I](https://codeforces.com/gym/102056/problem/I)

这题当时现场想了好几个小时都没有做出来，一直推不出来dp方程，最后想了个假贪心把队友给演了

题意：一个游戏有两个数值A和D，A表示攻击力，D表示攻击增益（每回合都会A+=D），给n个三元组$(a_i,b_i,c_i)$表示n个回合（n<100），对于每一个回合有三个选项：
- 攻击，造成伤害$A+a_i$, 
- 增加攻击力$c_i$， 也就是$A=A+c_i$
- 增加攻击增益$b_i$，也就是$D=D+b_i$
初始攻击力与攻击增益都是0，求问经过n个回合以后，造成的最大伤害是多少？

题解：首先考虑各个选择对答案的贡献，
- 当选择攻击时，贡献为$a_i$；

- 当选择增加攻击力时候，贡献为
  ![](http://latex.codecogs.com/gif.latex?\\\,y\cdot\\,c_i) 
  其中y表示在i以后选择攻击的次数；

- 当选择增加攻击增益时，贡献为

![](http://latex.codecogs.com/gif.latex?\\sum\limits_{j\in\\{attack\\}}(j-i)\cdot\\,b_i=(z-y\cdot\\,i)b_i)

​       其中集合attack表示在i之后选择攻击的回合序号，z表示选择攻击的回合序号和。因为我们需要额外维护选择在当前天以后攻击的回合数和回合序号数之和，考虑DP方程`dp[x][y][z]`，表示**第x回合，在第x回合之后有y个回合选择攻击，这些攻击的回合序号和为z**， 这样我们就可以得到转移方程：

`dp[x][y+1][z+x]=max(dp[x][y+1][z+x], dp[x+1][y][z]+a[x]);`

`dp[x][y][z]=max(dp[x][y][z],dp[x+1][y][z]+max(c[x]*y,b[x]*(z-x*y)));`

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 102;
using ll = long long;
//这里，由于重现赛的内存只有256m，所以需要用滚动数组的思想进行压缩，
//把dp[maxn][maxn][5060]压成dp[2][maxn][5060];
ll dp[2][maxn][5060];
ll a[maxn], b[maxn], c[maxn];
int n;

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while(t--){
        memset(dp, -1, sizeof(dp));
        scanf("%d", &n);
        ll sumofa=0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
            sumofa += a[i];
        }

        dp[n%2][1][n] = a[n];
        ll ans = 0;
        for (int i = n - 1; i; i--)
        {
            for (int j = n - i; j; j--)
            {
                for (int k = (n+n-j+1)*j/2; k >= (i+i+j-i)*j/2; k--)
                {
                    if (j && k >= i){
                        dp[i%2][j + 1][k + i] = max(dp[i%2][j + 1][k + i], 
                                                    dp[(i + 1)%2][j][k] + a[i]);
                        ans = max(ans, dp[i%2][j+1][k + i]);
                    }
                    dp[i%2][j][k] = max(dp[i%2][j][k], dp[(i + 1)%2][j][k] +
                                        max(c[i] * j, b[i] * (k - i * j)));
                    ans = max(ans, dp[i%2][j][k]);
                }
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}

```






## B - Codeforces 1073E

见Day1 G

## C -  [POJ 3616](http://poj.org/problem?id=3616)

题意：给出m个区间，每个区间对应一个权值，要求选取的区间间隔需要大于等于r，求最大权值和

题解：DP方程： `dp[i]=max{dp[i],dp[j]+w[i]}` ，其中j小于i，复杂度O(m^2)

```c++
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct inteval
{
    int start, end, val;
    bool operator <(const inteval& in) const{
        return end < in.end;
    }
};

inteval intevals[1005];
int dp[1005];

int n,m,r;
int main()
{
    scanf("%d%d%d",&n,&m,&r);
    for (int i = 1; i <= m;i++){
        scanf("%d%d%d", &intevals[i].start, &intevals[i].end, &intevals[i].val);
    }
    sort(intevals+1, intevals + m+1);
    intevals[0].end = -r;
    intevals[0].val = 0;
    int ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++)
    {
        int s = intevals[i].start;
        for (int j = 0; j<=i ;j++){
            if(s>=intevals[j].end+r)
                dp[i] = max(dp[i], dp[j] + intevals[i].val);
            ans = max(ans, dp[i]);
        }
    }
    printf("%d\n", ans);

    return 0;
}
```

## D - [HDU 1176](http://acm.hdu.edu.cn/showproblem.php?pid=1176)

题意：有0~10共11个坐标位置，现在有n个馅饼掉在这11个位置，告诉每个馅饼落下的时刻t和坐标x，且位于x出的人只能接住x-1，x，x+1这三个位置的馅饼，问最多能接住多少馅饼。

题解：考虑DP，`dp[i][j]` 表示第i时刻在j位置可以接住的最多馅饼数。按时间倒序dp，dp方程为

```c++ 
dp[i][j]+=max(max(dp[i+1][j-1],dp[i+1][j]),dp[i+1][j+1])
```
答案为`dp[0][5]`

我的思路：给`dp[0][5]` 赋一个很大的初始值，理论上这个值大于等于五秒内其他位置所有能接到的馅饼总数就行，这样就可以控制它在前五秒一定是按照以5为起点开始。

```c++
#include <bits/stdc++.h>
using namespace std;
using pt = pair<int, int>;
const int maxn=100005;
vector<int> vec[11];
int dp[maxn][11];

int cal_num(int pos, int time){
    return upper_bound(vec[pos].begin(), vec[pos].end(), time) -
           lower_bound(vec[pos].begin(), vec[pos].end(), time);
}

int main(int argc, char const *argv[])
{
    int n;
    while(scanf("%d",&n)&&n){
        for (int i = 0; i < 11;i++){
            vec[i].clear();
        }
        memset(dp, 0, sizeof(dp));
        int pos, t;
        int maxt = 0;
        while (n--)
        {
            scanf("%d%d", &pos, &t);
            vec[pos].push_back(t);
            maxt = max(maxt, t);
        }
        for (int i = 0; i <= 10;i++){
            sort(vec[i].begin(), vec[i].end());
        }
        // pt cur = make_pair(0, 5);
        dp[0][5] = 1000;
        for (int i = 1; i <=maxt; i++)
        {
            for (int j = 0; j <= 10;j++){
                int ca = cal_num(j, i);
                dp[i][j] = dp[i - 1][j] + ca;
                if (j)
                {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + ca);
                }
                if(j<10){
                    dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] + ca);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= 10;i++){
            ans = max(ans, dp[maxt][i]);
        }
        printf("%d\n", ans - 1000);
    }
    return 0;
}
```




## E - [HDU 1074](http://acm.hdu.edu.cn/showproblem.php?pid=1074)

题意：有一堆作业，每个作业给出ddl和做完所需时间，作业数<15，如果在ddl前写不完作业，惩罚分数为做完的时间减去ddl，求作业完成顺序使得惩罚分数和最小。***如果有相同的方案输出字典序较小的那个*** 

题解：状态压缩DP，`dp[s]`表示状态为s时的最小惩罚和，转移算法为：枚举每个作业，如果这个作业已经在状态里面，试着更新`dp[s]` 使得它被子状态中最小的（子状态惩罚+那一个作业的惩罚）更新，并记录这个最后选择的作业的下标。注意如果我们发现有两种更新的惩罚相等，我们应该优先选择字典序更大的那个

```c++
#include <bits/stdc++.h>
const int maxn = 16;
const int inf = 0x3f3f3f3f;
using std::min;
struct pt
{
    int time, sum;
    int prev_stat,last_choice;
} stat[1 << maxn];

int ddl[maxn], cost[maxn];
char name[maxn][105];

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        memset(stat, 0, sizeof(stat));
        scanf("%d", &n);
        for (int i = 0; i < n;i++){
            scanf("%s%d%d", name[i], &ddl[i], &cost[i]);
        }
        int s = 1 << n;
        for (int i = 1; i < s; i++)
        {
            stat[i].sum = inf;
            for (int j = 0; j<n; j++)
            {
                int t = 1 << j;
                if(i&t){
                    int prev = i - t;
                    int res = stat[prev].time + cost[j] - ddl[j];
                    if(res<0)
                        res = 0;
                    if(stat[prev].sum+res<stat[i].sum||
                    (stat[prev].sum+res==stat[i].sum&&
                    strcmp(name[j],name[stat[i].last_choice])>0))
                    {
                        stat[i].sum = stat[prev].sum + res;
                        stat[i].time = stat[prev].time + cost[j];
                        stat[i].last_choice = j;
                        stat[i].prev_stat = prev;
                    }
                }
            }
        }
        s--;
        printf("%d\n", stat[s].sum);
        std::vector<int> vec;
        while(s){
            vec.push_back(stat[s].last_choice);
            s = stat[s].prev_stat;
        }
        std::reverse(vec.begin(), vec.end());
        for(auto c:vec){
            puts(name[c]);
        }
    }
    return 0;
}
```



## F - [HDU 3555](http://acm.hdu.edu.cn/showproblem.php?pid=3555)

 题意：给一个数x，求小于等于x的所有数中含有“49”的个数

题解：简单数位dp，把[“不要62”](http://acm.hdu.edu.cn/showproblem.php?pid=2089) 的“6”改成“4”，“2”改成“9” 就完事了

```c++
#include <cstdio>
#include <cstring>

using ll = long long;
int digital[20];
ll dp[20][2];

ll dfs(int now,int dig,bool flag,int stat){
    if(!flag&&dp[now][stat]!=-1){
        return dp[now][stat];
    }
    if(!now){
        return 1;
    }

    ll amount = 0;
    int up=flag?digital[now]:9;
    for (int i = 0; i <= up;i++){
        if(stat==1&&i==9)
            continue;
        if(i==4){
            amount += dfs(now - 1, i, flag && (i == up), 1);
        }
        else{
            amount += dfs(now - 1, i, flag && (i == up), 0);
        }
    }
    if(!flag){
        dp[now][stat] = amount;
    }
    return amount;
}

ll getans(ll val){
    int cnt = 0;
    while (val)
    {
        digital[++cnt] = val % 10;
        val /= 10;
    }
    return dfs(cnt, 0, 1, 0);
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    memset(dp, -1, sizeof(dp));
    while (round--)
    {
        ll x;
        scanf("%lld", &x);
        printf("%lld\n",x-getans(x)+1);
    }
    return 0;
}
```



## G - [LightOJ 1422](http://www.lightoj.com/volume_showproblem.php?problem=1422)

 题意：一个人要参加n个聚会，每参加一个聚会必须最外面穿上颜色为$c_i$的衣服，如果衣服脱掉了就必须丢弃，问最少需要准备多少件衣服

题解：考虑区间dp，`dp[i][j]` 表示从i到j的聚会需要准备多少件衣服，转移算法：对于每一个i和j之间的k，如果第k个聚会和第j个聚会所需颜色相同，那么`dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j-1])`, 由于只考虑了最后一位与之中相同的情况，故应当枚举长度并且从前往后枚举起点。注意初始化时应该`dp[i][j]=j-i+1` 并且当i>j时`dp[i][j]=0` 。

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
int dp[maxn][maxn];
int arr[maxn];
int n;

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    for (int v = 1; v <= round;v++)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &arr[i]);
        }

        for (int i = 1; i <= n;i++){
            for (int j = i; j <= n;j++){
                dp[i][j] = j - i + 1;
            }
        }
            for (int len = 1; len < n; len++)
            {
                for (int i = 1; i + len <= n; i++)
                {
                    int j = i + len;
                    dp[i][j] = dp[i][j - 1] + 1;//如果最后两个相等会在后面被更新
                    for (int k = 1; k < j; k++)
                    {
                        if (arr[k] == arr[j])
                        {
                            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j - 1]);
                        }
                    }
                }
            }
        printf("Case %d: %d\n", v, dp[1][n]);
    }
    return 0;
}
```

