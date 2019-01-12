 # DAY 1

难度(按照tag)：F<C<E<B<D<G<A

## A - [Codeforces 875F](http://codeforces.com/problemset/problem/875/F)

题意： n个王子，m个公主，每个公主有两个心仪王子，并携带嫁妆，使得总嫁妆最大

题解：最大基环森林。把每个公主看做边，每个王子作为点，然后当n个王子与n个公主对应时候，会出现最大值，类似kruskal

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
int f[maxn];
bool cir[maxn];
int n, m;

struct edge
{
    int a, b, w;
    bool operator <(const edge& e) const{
        return w > e.w;
    }
};

edge edges[maxn];

int findfa(int x){
    if(x==f[x])
        return x;
    return f[x]=findfa(f[x]);
}

void uni(int x,int y){
    x=findfa(x);
    y=findfa(y);
    f[y] = x;
    cir[x] |= cir[y];//这个地方，当y指向x后，x具有了y的性质（n条边，n个点）
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < maxn;i++){
        f[i] = i;
    }
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= m;i++){
        scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].w);
    }
    sort(edges + 1, edges + 1 + m);
    long long ans = 0;
    for (int i = 1; i <= m; i++)
    {
        const auto &e = edges[i];
        int fa = findfa(e.a);
        int fb = findfa(e.b);
        if (fa!= fb && ((!cir[fa]) || (!cir[fb])))//两个都是基环后不能连，因为会变成2n+1
        {
            uni(e.a, e.b);
            ans += e.w;
        }
        else if(fa==fb&&(!cir[fa])){
            ans += e.w;
            cir[fa] = 1;
        }
    }
    printf("%lld", ans);
    return 0;
}
```

## B - [Codeforces 1047C](https://codeforces.com/problemset/problem/1047/C)

题意：给n个数，求最少删掉几个数可以增大他们的最小公倍数

题解：找出一个数尽可能多的是这些数的因数，这个数应该在$\gcd(a_1,a_2,a_3\cdots\,a_n)$ 到$\max(a_1,a_2,a_3\cdots a_n)$ 之间(左开右闭)，利用筛法的思想找到这些数并且记录出现次数

```c++
#include <bits/stdc++.h>
const int maxn = 3e5 + 10;
const int maxm = 1.5e7;

int arr[maxn];
int appear[maxm];
int ans[maxm];
bool vis[maxm];

int gcd(int a,int b){
    if(b==0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++){
        scanf("%d", &arr[i]);
        appear[arr[i]]++;
    }
    
    int ma = arr[1];
    int g = arr[1];
    for (int i = 2; i <= n;i++){
        g = gcd(g, arr[i]);
        ma = std::max(ma, arr[i]);
    }
    int res = 0;

    for (int t = g + 1; t<=ma; t++){
        if(vis[t])
            continue;
        for (int c = t; c <=ma; c+=t){//实际上只考虑了质数，因为对于合数作为因数一定不是最多的
            ans[t] += appear[c];
            vis[c] = 1;
        }
        if(ans[t]){
            res = std::max(res, ans[t]);
        }
    }
    if(res==0)
        res = n+1;
    printf("%d\n", n - res);
    return 0;
}
```

## C - [Codeforces 748B](https://codeforces.com/problemset/problem/748/B)

题意：许多组字母交换，给两个串问是否有这样的交换使两个串相等

题解：需要一个双射表，并且注意自己对自己的映射

```c++
#include <bits/stdc++.h>
using namespace std;

unordered_map<char,char> m;
unordered_map<char, char> ans;
bool vis[128];
char s[1005];
char t[1005];
int main(int argc, char const *argv[])
{
    scanf("%s%s", s, t);
    int len = strlen(s);
    for (int i = 0; i < len;i++){
        if(m.find(s[i])==m.end()&&m.find(t[i])==m.end()){
            m[s[i]] = t[i];
            m[t[i]] = s[i];
        }
        else if(m[s[i]]!=t[i]||m[t[i]]!=s[i]){
            puts("-1");
            return 0;
        }
    }

    for (auto e : m)
    {
        if((!vis[e.first-'a'])&&(!vis[e.second-'a'])&&e.first!=e.second){
            ans[e.first] = e.second;
        }
        vis[e.first-'a'] = vis[e.second-'a'] = 1;
    }
    printf("%lu\n", ans.size());
    for(auto e:ans){
        if(e.first!=e.second){
            printf("%c %c\n", e.first, e.second);
        }
    }
    return 0;
}
```

## D - [Codeforces 1096D](https://codeforces.com/problemset/problem/1096/D)

题意：“难”的字符串指在这个字符串中可以找到一个子序列：“hard”，例如“hzazrzd”，每个字符对应一个权重，删掉一些字符使得这个字符串不“难”，问这个最小权重和

题解：考虑DP，维护DP方程`dp[n][4]`，第一维表示使得前 n 个字符不含 ‘h’ 的最小代价，第二维表示使得前 n 个字符不含 ‘ha’ 的最小代价，第三维表示使得前 n 个字符不含 ‘har’ 的最小代价，第四维表示使得前 n 个字符不含 ‘hard’ 的最小代价。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

long long arr[maxn];
long long sum[4];
char str[maxn];
int len;

int main(int argc, char const *argv[])
{
    char tar[] = {'h', 'a', 'r', 'd'};
    scanf("%d", &len);
    scanf("%s", str);

    for (int i = 0; i < len;i++){
        scanf("%lld", &arr[i]);
    }
    //为了简便，没有弄一个二维数组dp[n][4]，而是sum[4]
    for (int i = 0; i < len;i++){
        for (int j = 0; j < 4;j++){
            if(str[i]==tar[j]){
                if(j==0){
                    sum[j] += arr[i];
                }
                else{
                    sum[j] = min(sum[j] + arr[i], sum[j - 1]);
                }
            }
        }
    }
    printf("%lld",*min_element(sum,sum+4));
    return 0;
}
```

## E - [Codeforces 1006E](https://codeforces.com/problemset/problem/1006/E)

题意：给一颗树，每个节点可以往自己的子树节点（包括自己）以dfs序发出通知，有q个询问，每个询问对应一个u，k问节点u的通知的第k个收到的是哪一个节点，如果k大于他的所有子节点输出“-1”

题解：因为子节点的dfs序必然是父亲节点的dfs序的子串，所以对根节点做一遍dfs就完事了，顺便维护每个节点的子树大小

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m;
vector<int> order;
vector<int> vec[maxn];
int subs[maxn];
int apper[maxn];

void dfs(int u){
    order.push_back(u);
    for (auto c : vec[u])
    {
        dfs(c);
        subs[u] += subs[c];
    }
}

int main(int argc, char const *argv[])
{
    scanf("%d%d",&n,&m);
    for (int i = 2; i <= n;i++){
        int x;
        scanf("%d", &x);
        vec[x].push_back(i);
    }
    for (int i = 1; i <= n;i++){
        subs[i] = 1;
    }
    dfs(1);
    for (int i = 0; i < order.size();i++){
        apper[order[i]] = i;
    }

    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (y > subs[x])
        {
            puts("-1");
        }
        else
        {
            int f = apper[x];
            printf("%d\n", order[f + y - 1]);
        }
    }
    return 0;
}
```

## [F - Codeforces 1077B](https://codeforces.com/problemset/problem/1077/B) 

题意：n个住户，有开灯（1）和关灯（0）两个状态，给出一串状态，一个住户被打扰当且仅当他的附近两个住户都开灯而且他关灯（“101”），问最少关闭多少盏灯使得没有人被打扰

题解：考虑贪心，从左往右遍历，关掉右边的灯就完事了。我的做法：先算出多少住户被打扰，然后把所有相邻的被打扰住户搞成一个集合，减去这些集合数。（因为一个集合内的所有住户只需要关掉被打扰数-1）

```c++
#include <bits/stdc++.h>
using namespace std;
int arr[105];
bool vis[105];
int n;

bool disturbe(int i){
    if(i<=1||i>=n){
        return false;
    }
    return (!arr[i]) && arr[i - 1] && arr[i + 1];
}


int main(int argc, char const *argv[])
{
    // int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    vector<int> vec;
    for (int i = 1; i <= n; i++)
    {
        if(disturbe(i)){
            vec.push_back(i);
        }
    }
    int tot = 0;
    for (int i = 0; i < vec.size();i++){

        if (i&&vec[i] - vec[i - 1] == 2&&!vis[vec[i-1]])
        {
            vis[vec[i]] = vis[vec[i - 1]] = 1;
            tot--;
        }
        tot++;
    }
    printf("%d", tot);
    return 0;
}
```

## [G - Codeforces 1073E](https://codeforces.com/problemset/problem/1073/E)

题意：给出三个数l, r, k, 求l到r中所有由小于k个数字组成的和

题解：数位DP，考虑`dp[i][j]` ，这个数组是`pair<long long, long long>`， first表示数字的个数，second表示总和，处理数字总和时，枚举当前位为now，现在是第num位，那么这里的数字总和就是pow(10,now-1)*前面数字个数+前面数字总和。数组的第一维表示当前位数（1-18），第二维表示选取的数字状态为j（1-1024），第三维表示k的值（但是cf是单组样例可以省略）

[refer](https://blog.csdn.net/sakura_is_the_best/article/details/83415286)

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1024;
using ll = long long;
int sum[maxn];
ll pow_of_ten[25];
const ll mod = 998244353;
ll digit[20];
pair<ll, ll> dp[25][maxn][15];

int get_digit_number(int now){
    int res=0;
    while(now){
        if(now&1){
            res+=1;
        }
        now >>= 1;
    }
    return res;
}

pair<ll,ll> dfs(int now,bool flag,int ds,int k,bool zero){
    if(!flag&&dp[now][ds][k].first!=-1&&dp[now][ds][k].second!=-1){
        return dp[now][ds][k];
    }
    if(!now){
        pair<ll, ll> pa;
        if(sum[ds]<=k){
            pa.first = 1;
            pa.second = 0;
            return pa;
        }
        pa.first = pa.second = 0;
        return pa;
    }
    int up;
    if(flag){
        up = digit[now];
    }
    else
        up = 9;
    ll number = 0, sum = 0;
    for (int i = 0;i<=up;i++){
        int nz = zero;
        if(i){
            nz = 1;
        }
        int nds = ds;
        if(nz){
            nds |= (1 << i);
        }
        pair<ll, ll> next_digit = dfs(now - 1, flag && (i == up), nds, k, nz);
        number = (number+next_digit.first)%mod;
        sum = (sum + (i * pow_of_ten[now - 1] % mod * next_digit.first % mod) + next_digit.second) % mod;
    }
    if(!flag){
        dp[now][ds][k].first = number;
        dp[now][ds][k].second = sum;
    }
    return make_pair(number, sum);
}

ll getans(ll num, ll k){
    if(num==0){
        return 0;
    }
    int cnt = 0;
    while(num){
        digit[++cnt] = num % 10;
        num /= 10;
    }
    return dfs(cnt, 1, 0, k, 0).second;
}

void init(){
    for (int i = 0; i <maxn;i++){
        sum[i] = get_digit_number(i);
    }
    pow_of_ten[0] = 1;
    for (int i = 1; i < 25;i++){
        pow_of_ten[i] = pow_of_ten[i - 1] * 10 % mod;
    }

    for (int i = 0; i < 25;i++){
        for (int j = 0; j < maxn;j++){
            for (int k = 0; k <= 10;k++){
                dp[i][j][k].first = dp[i][j][k].second = -1;
            }
        }
    }
}

int main(){
    ll l, r, k;
    init();
    scanf("%lld%lld%lld", &l, &r, &k);
    printf("%lld\n", (getans(r, k) - getans(l - 1, k) + mod) % mod);
}
```

