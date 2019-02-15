# Day5 数论

## 一些定义和性质

- $\displaystyle\lceil\frac{n}{ab}\rceil=\lceil\frac{\lceil\,n/a\,\rceil}{b}\rceil$, $\displaystyle\lfloor\frac{n}{ab}\rfloor=\lfloor\frac{\lfloor\,n/a\,\rfloor}{b}\rfloor$

- $\displaystyle\lceil\frac{n}{i}\rceil$ 只有$O(\sqrt{N})$ 种取值

- ***数论函数***：定义域为正整数，陪域为复数的函数。我们主要研究定义域为正整数，值域为整数的函数。

- ***积性函数***：满足 若a, b互质，则f (ab) = f (a)f (b) 的数论函 数称为积性函数。 

- ***完全积性函数***：满足 f (ab) = f (a)f (b) 的数论函数称为完全积性函数
- ***狄利克雷卷积***：对于数论函数$\displaystyle f,g​$，定义其狄利克雷卷积$(f * g)(n) = \sum_{d|n} f(d) g(\frac{n}{d})​$

- 两个积性函数的狄利克雷卷积仍为积性函数

## 一些常见的积性函数

- 单位函数 $\displaystyle{e(x)=\cases{1, x=1 \\0,x>1}}​$ 
- 常函数I(x)=1
- 幂函数id(x)=$x^k$ 
- 欧拉函数$\phi(x)$ 代表[1,x]中与x互质的个数=${\displaystyle \varphi (n)=\prod _{i=1}^{r}p_{i}^{k_{i}-1}(p_{i}-1)=\prod _{p\mid n}p^{\alpha _{p}-1}(p-1)=n\prod _{p|n}\left(1-{\frac {1}{p}}\right)}$ 

## 莫比乌斯函数

$\sum\limits_{d|m}\mu(d)=[m=1]​$ 这是莫比乌斯函数最基本的定义，可以用这个可以将“等于1的数量”转化为莫比乌斯函数

## 杜教筛


求 $S(n)=\sum_{i=1}^n f(i)​$，其中 $f​$ 是一个积性函数。

构造一个积性函数 $g$，那么由 $(f*g)(n)=\sum_{d|n}f(d)g(\frac{n}{d})$，得到 $f(n)=(f*g)(n)-\sum_{d|n,d<n}f(d)g(\frac{n}{d})$。

$\displaystyle\begin{eqnarray} g(1)S(n)&=&\sum_{i=1}^n (f*g)(i)-\sum_{i= 1}^{n}\sum_{d|i,d<i}f(d)g(\frac{n}{d}) \ &\overset{t=\frac{i}{d}}{=}& \sum_{i=1}^n (f*g)(i)-\sum_{t=2}^{n} g(t) S(\lfloor \frac{n}{t} \rfloor) \end{eqnarray}$

当然，要能够由此计算 $S(n)$，会对 $f,g$ 提出一些要求：

- $f*g$ 要能够快速求前缀和。
- $g​$ 要能够快速求分段和（前缀和）。
- 对于正常的积性函数 $g(1)=1​$，所以不会有什么问题。

在预处理 $S(n)​$ 前 $n^{\frac{2}{3}}​$ 项的情况下复杂度是 $O(n^{\frac{2}{3}})​$

## A - [HDU 4965](http://acm.hdu.edu.cn/showproblem.php?pid=4965)

两个矩阵A，B，求（A\*B）的N\*N次幂。其中元素都%6 因为N范围是1000，K范围是6，如果直接对A \* B快速幂的话是对一个1000\*1000的矩阵操作，会TLE。所以可以先求出\*A的（N\*N-1）次方，这是一个5\*5的矩阵，再右乘A左乘B

```c++
#include <bits/stdc++.h>
using namespace std;

struct Matrix{
    vector<vector<int>> v;
    int n, m;
    Matrix(int n,int m,int op=0):n(n),m(m){
        v.resize(n);
        for(auto& e:v){
            e.resize(m, 0);
        }
        if(op){
            for (int i = 0; i < n && i < m;i++){
            v[i][i] = 1;
        }http://acm.hdu.edu.cn/showproblem.php?pid=4965
        }
    }
    
    friend Matrix operator *(const Matrix& mat,const Matrix& other){
        Matrix ret = Matrix(mat.n, other.m);
        for (int i = 0; i < mat.n; i++)
        {
            for (int j = 0; j < mat.m;j++){
                for (int k = 0; k < other.m;k++){
                    ret.v[i][k] += mat.v[i][j] * other.v[j][k];
                    ret.v[i][k] %= 6;
                }
            }
        }
        return ret;
    }

    Matrix pow(int t) const{
        Matrix ret = Matrix(this->n,this->n,1);
        Matrix tmp = *this;
        for (; t; t >>= 1,tmp=tmp*tmp)
            if(t&1)
                ret = ret * tmp;
        return ret;
    }

    int sum() const{
        int ret = 0;
        for(auto& c:this->v){
            for(auto& e:c){
                ret += e;
            }
        }
        return ret;
    }
};

int main(int argc,char const *argv[]){
    int n, m;
    while(scanf("%d%d", &n, &m)){
        if(n==0&&m==0)
            break;
        Matrix a(n, m);
        Matrix b(m, n);
        for (int i = 0; i < n;i++){
            for (int j = 0; j < m;j++){
                scanf("%d", &a.v[i][j]);
            }
        }
        for (int i = 0; i < m;i++){
            for (int j = 0; j < n;j++){
                scanf("%d", &b.v[i][j]);
            }
        }
        auto ans = (a * ((b * a).pow(n*n - 1))) * b;
        printf("%d\n", ans.sum());
    }
}

```

## B - UVA 10655

题意：给出两个数字代表a+b和a\*b,再给一个数字n，求$a^n+b^n$ 

题解：首先直接把这两个值带入二次方程求解是错误的，因为a和b可以为复数，如$2+i​$ 与 $2-i​$，我们无法处理这种情况

考虑递推公式：$a^n+b^n=(a^{n-1}+b^{n-1})\cdot{(a+b)}-(a^{n-2}+b^{n-2})\cdot(ab)​$

令$f(n)=a^n+b^n​$，于是有$$\begin{bmatrix}
a+b & -ab \\
1 & 0  
\end{bmatrix} 
\begin{bmatrix}
f(n-1)\\
f(n-2)
\end{bmatrix} =\begin{bmatrix}
f(n)\\
f(n-1)
\end{bmatrix}​$$

然后又是一个矩阵快速幂

```c++
#include <iostream>
using namespace std;
using ll = long long;

struct Mat{
    ll m[2][2];
};
Mat a,e;
const int n = 2;

Mat Mul(Mat x, Mat y)
{
    Mat c;
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        c.m[i][j]=0;
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        for(int k=0;k<n;k++)
            c.m[i][j]=c.m[i][j]+x.m[i][k]*y.m[k][j];
    return c; 
}
Mat pow(Mat x,ll y) 
{
    Mat ans=x;
    while(y)
    {
        if(y&1)
         ans=Mul(ans,x);  
        x=Mul(x,x);
        y>>=1;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    long long p, q;
    int an;
    while (cin >> p >> q)
    {
        if(!(cin>>an)){
            break;//这里wa了很多发，注意终止条件
        }
        a.m[0][0] = p;
        a.m[0][1] = -q;
        a.m[1][0] = 1;
        a.m[1][1] = 0;
        if (an == 0)
        {
            cout << 2 << endl;
            continue;
        }
        if(an==1){
            cout << (long long)p << endl;
            continue;
        }
        if(an==2){
            cout << p * p - 2 * q << endl;
            continue;
        }
        an-=2;
        a=pow(a, an);
        long long ans = a.m[0][0] * p + a.m[0][1] * 2;
        cout << (long long)ans << endl;
    }
    return 0;
}
```

## C - UVA 1386

题意：给定一个n格的环，现在有个距离d，每次变化把环和他周围距离d以内的格子相加，结果mod m，问经过k次变换之后，环上的各个数字

题解：写成矩阵乘法形式很好想：距离d以内的为1，别的都是0。但是矩阵乘法直接N^3会T，需要用循环矩阵优化到N^2

[refer](https://blog.csdn.net/accelerator_/article/details/37992531)

## D - [HDU 5680](http://acm.hdu.edu.cn/showproblem.php?pid=5608)

题意：$f(x)​$ 满足$N^2-3N+2=\sum_{d|N} f(d)​$ ，求$\sum_{i=1}^{N} f(i)​$ ， N<1e9，	且只有5个测试大于1e6

题解：杜教筛裸题

```c++
#include <bits/stdc++.h>
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
using namespace std;
using LL = long long;
const LL mod = 1e9 + 7;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }
const LL inv3 = get_inv(3, mod);

LL mul(LL a,LL b){
    return ((a % mod) * (b % mod)) % mod;
}

LL add(LL a,LL b){
    return (a + b + mod) % mod;
}

namespace dujiao {
    const int M = 1E6;
    LL mu[M] = {0, 1};
    LL f[M];
    inline LL g(LL n){
       return (1ll * n * n % mod - 3ll * n % mod + 2) % mod;
    }

    void init()
    {
        static bool vis[M];
        static LL pr[M], p_sz, d;
        //先利用莫比乌斯函数暴力算前sqrt(N)项前缀和
        FOR (i, 2, M) {
            if (!vis[i]) { pr[p_sz++] = i; mu[i-] = -1; }
            FOR (j, 0, p_sz) {
                if ((d = pr[j] * i) >= M) break;
                vis[d] = 1;
                if (i % pr[j] == 0) {
                    mu[d] = 0;
                    break;
                } else mu[d] = -mu[i];
            }
        }

        FOR(i, 1, M){
            for (int j = i; j < M; j += i)
            {
                f[j] = (f[j] + 1ll * mu[j / i] * g(i) % mod) % mod;
            }
        }

        FOR (i, 2, M) f[i] = (f[i]+ f[i - 1])%mod;
    }
    inline LL s_fg(LL n) {
        n = n % mod;
        return inv3 * n % mod * ((n * n % mod - 3 * n % mod + 2 + mod) % mod) % mod;
    }
    inline LL s_g(LL n) {
        return n % mod;
    }

    LL N, rd[M];
    bool vis[M];
    LL go(LL n) {
        if (n < M) return f[n];
        LL id = N / n;
        if (vis[id]) return rd[id];
        vis[id] = true;
        LL& ret = rd[id] = s_fg(n);
        for (LL l = 2, v, r; l <= n; l = r + 1) {
            v = n / l; r = n / v;
            ret = add(ret, - mul(add(s_g(r) , - s_g(l - 1)),go(v)));
        }
        return ret;
    }
    LL solve(LL n) {
        N = n;
        memset(vis, 0, sizeof vis);
        return go(n);
    }
}

int main(int argc, char const *argv[])
{
    using namespace dujiao;
    init();
    int round, n;
    scanf("%d", &round);
    for (int i = 0; i < round;i++)
    {
        scanf("%d", &n);
        printf("%lld\n", (solve(n) + mod) % mod);
    }
    return 0;
}
```



## E - [HDU 5942](http://acm.hdu.edu.cn/showproblem.php?pid=5942)

题意：定义$f(k)​$ 为k的素因子个数，$g(k)=2^{f(k)}​$ ,给一正整数n，$1\le\,n\le\,10^{12}​$ ，求$\sum\limits_{i=1}^{n}g(i)​$

题解：令$k=p_1^{a_1}\cdots\,p_n^{a_n}​$，则$g(k)=2^{f(k)}=2^m​$，即为集合$\{p^{a_1}_1,\cdots,p^{a_m}_m\}​$的子集个数，该集合一个子集的乘积p与该子集的补集（对全集合的补）的乘积q显然互素，且显然一一对应（k的任一互质的一对因子都可以拆成某个子集所有元素的积，和他的补的所有元素的积），也就是$g(k)=|\{(p,q)=1,pq=k\}|​$ ，记$h(n)=\sum\,g(i)=\sum\limits_{ij\le n}|(i,j)=1|=\sum\limits_{ij\le n}\sum\limits_{d|i, d|j}\mu(d)=\sum\limits_{d=1}^{\sqrt{n}}\mu(d)\sum\limits_{i=1}^{\lfloor n/d^2\rfloor}\lfloor n/d^2i\rfloor​$ 

记$S(n)=\sum\limits_{i=1}^n\lfloor\,n/i\rfloor​$，于是$h(n)=\sum\limits_{d=1}^{\sqrt{n}}\mu(d)S(\lfloor\,n/d^2\rfloor)​$

$S(n)=\sum\limits_{i=1}^{\sqrt{n}}\lfloor\,n/i\rfloor\,-\lfloor\sqrt{n}\rfloor^2​$

记忆S(n)，然后枚举d即可，复杂度难以分析QAQ，另外这题时限15s，但是也卡常（比如分块计算S(n)就疯狂tle，后来还是[oeis](oeis.org)找到的严格$O(\sqrt{n})​$ 公式）

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxn = 1e6 + 5;
const ll mod = 1e9 + 7;

ll mu[maxn], S[maxn];
void get_mu()
{
	mu[1] = 1;
	static bool vis[maxn];
	static ll prime[maxn], sz, d;
	for (ll i = 2; i < maxn;i++){
		if(!vis[i]){
			prime[sz++] = i;
			mu[i] = -1;
		}
		for (ll j = 0; j < sz && (d = i * prime[j]) < maxn;j++){
			vis[d] = 1;
			if(i%prime[j]==0){
				mu[d] = 0;
				break;
			}
			else
				mu[d] = -mu[i];
		}
	}
}

ll getS(ll n){
	ll res = 0;
	ll sq = sqrt(n);
	for (int i = 1; i <= sq; i++)
	{
		res += n / i;
		res %= mod;
	}
	res = (res)*2ll-sq *sq;
	res = (res + mod) % mod;
	return res;
}

ll Sum(ll n){
	if (n < maxn&&S[n]!=-1) return S[n];
	ll res = getS(n);
	if(n<maxn)
		S[n] = res;
	return res;
}

int main(int argc, char const *argv[])
{
	int round;
	scanf("%d", &round);
	get_mu();
	memset(S, -1, sizeof(S));
	for (int ca = 1; ca <= round; ca++)
	{
		ll n;
		scanf("%lld", &n);
		ll c = sqrt(n);
		ll ans = 0;
		for (ll i = 1; i <= c; i++)
		{
			if (mu[i])
				ans = (ans + mu[i] * Sum(n / i / i) + mod) % mod;
		}
		printf("Case #%d: %lld\n", ca, ans);
	}
	return 0;
}

```




## F - [BZOJ 2818](https://www.lydsy.com/JudgeOnline/problem.php?id=2818)

题意：给定整数N，求1<=x,y<=N且gcd(x,y)为素数的数对(x,y)有多少对.

题解：对于某个质数p，如果gcd(x,y)=p,等价于gcd(x/p,y/p)=1。要求满足这等式的数量，不妨令x<y，也就是求所有小于y/p中与之互质的数，即$\phi(y/p)​$ 

于是对于每个质数，就是$2\sum\limits_{i=1}^{\lfloor\,N/p\rfloor}\phi(i)-1​$ , 其中p是枚举的每个质数，\* 2是因为我们假定了x<y，-1是因为要排除x=y=1($\phi(1)=1​$)~~（其实我也不知道为啥-1）~~时的情形。

接下来处理一下欧拉函数的前缀和即可。

（这个代码跑了7s）

```c++
#include <cstdio>
typedef long long ll;
const ll p_max = 1E7 + 100;
ll prime[p_max];
ll phi[p_max];
ll sumphi[p_max];
void get_phi()
{
    phi[1] = 1;
    static bool vis[p_max];
    static ll p_sz, d;
    for (ll i = 2; i < p_max;i++)
    {
        if (!vis[i])
        {
            prime[p_sz++] = i;
            phi[i] = i - 1;
        }
        for (ll j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j)
        {
            vis[d] = 1;
            if (i % prime[j] == 0)
            {
                phi[d] = phi[i] * prime[j];
                break;
            }
            else
                phi[d] = phi[i] * (prime[j] - 1);
        }
    }
    sumphi[0] = phi[0];
    for (int i = 1; i < p_max;i++){
        sumphi[i] = sumphi[i - 1] + phi[i];
    }
}

int main(){
    get_phi();
    ll n;
    scanf("%lld", &n);
    ll ans = 0;
    for (int i = 0; prime[i] <= n;i++){
        ans += 2 * sumphi[(n / prime[i])] - 1;
    }
    printf("%lld\n", ans);
}
```

解法二：令$\displaystyle{f(d):=\sum_{i=1}^N\sum_{j=1}^N[{\gcd(i,j)==d}]}$ , $\displaystyle{g(n):=\sum_{i=1}^N\sum_{i=1}^N{[n|\gcd(i,j)]}}$ , 非常显然，有$\displaystyle{g(n)=\sum_{n|d}f(d)}$ （g(n)=f(n)+f(2n)+f(3n)+…），并且$g(n)=[N/n]^2$ (n|i并且n|j，就是这么多)。 这样就可以莫比乌斯反演，得到$\displaystyle{f(n)=\sum_{n|d}g(d)\mu(d/n)=\sum_{n|d}\mu(d/n)[N/d]^2}$ , 于是$ans=\sum_{n\in prime}f(n)$ , 然后把g(d) 的部分提到外面，就得到$\displaystyle{ans=\sum_{d=1}^N[N/d]^2\sum_{n|d, n\in{prime}}\mu(d/n)}$然后预处理$\sum_{p|d,p\in{prime}}\mu(d/p)$ 即可：

```c++
for(int i:prime){//枚举质数
    for(int j=1;i*j<=N;j++){//枚举d/n
        sum[i*j]+=mu[j]
    }
}
```

（这个代码跑了9580ms）

```c++
#include <cstdio>
typedef long long ll;

const ll p_max = 1E7 + 100;
ll prime[p_max], p_sz, d;
ll mu[p_max];
ll sum[p_max];
void get_mu()
{
    mu[1] = 1;
    static bool vis[p_max];
    mu[1] = 1;
    for (ll i = 2; i < p_max;i++)
    {
        if (!vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
        }
        for (ll j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                break;
            }
            else mu[d] = -mu[i];
        }
    }
}
inline ll sq(ll x){
    return x * x;
}

int main()
{
    get_mu();
    ll n;
    scanf("%lld", &n);
    for (int i = 0; i < p_sz; i++)
    {
        for (ll j = 1; prime[i] * j <= n;j++){
            sum[prime[i] * j] += mu[j];
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n;i++){
        ans += sq(n / i) * sum[i];
    }
    printf("%lld", ans);
}
```

## G - [POJ 2155](http://poj.org/problem?id=2155)

题意：给一个矩阵A，矩阵的元素要么是0要么是1，接下来有两个操作：区间修改和单点查询，区间修改是对一个矩形区域取反

题解：二位树状数组，维护差分数组，取反就是+1，然后所有运算在%2意义下。

```c++
#include <cstdio>
#include <cstring>
inline int lowbit(int x) {
    return x & (-x);
}
const int maxn = 1005;
bool bit[maxn][maxn];

void update(int x,int y,int val){
    for (int i = x; i < maxn;i+=lowbit(i)){
        for (int j = y; j < maxn;j+=lowbit(j)){
            bit[i][j] ^= val;//所有的运算都是异或
        }
    }
}

bool query(int x,int y){
    bool res = 0;
    for (int i = x; i>0;i-=lowbit(i)){
        for (int j = y; j>0;j-=lowbit(j)){
            res ^= bit[i][j];
        }
    }
    return res;
}

char op[1];

int main(){
    int round;
    int m, n;
    scanf("%d", &round);
    while(round--){
        memset(bit, 0, sizeof(bit));
        scanf("%d%d", &m, &n);
        while(n--){
            scanf("%s", op);
            if(op[0]=='C'){
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                x1++, y1++, x2++, y2++;//不先++的话可能会update到0而死循环
                update(x2, y2, 1);//二维差分数组，后两项本应该-1但是这里-1同余到1
                update(x1 - 1, y1 - 1, 1);
                update(x1 - 1, y2, 1);
                update(x2, y1 - 1, 1);
            }
            else{
                int x, y;
                scanf("%d%d", &x, &y);
                printf("%d\n", query(x, y));
            }
        }
        puts("");
    }
}
```

## H - [HDU 1724](http://acm.hdu.edu.cn/showproblem.php?pid=1724)

题意：给一个椭圆（参数a，b）和两个值l和r(-a <= l <= r <= a)，以l和r作两条垂直x轴的直线，求这两条直线与椭圆围成曲边矩形的面积

题解：辛普森公式

注意：刚开始的时候疯狂tle因为公式写的太丑了。。。必要的化简应该被考虑

```c++
#include <bits/stdc++.h>
using namespace std;
using LD = double;
const LD eps = 1e-8;

LD a,b;
LD f(LD x){
    return b*sqrt(1 - (x * x) / (a * a));
}
LD simpson(LD l, LD r)
{
    LD c = (l + r) / 2;
    return (f(l) + 4 * f(c) + f(r)) * (r - l) / 6;
}
LD asr(LD l, LD r, LD eps, LD S)
{
    LD m = (l + r) / 2;
    LD L = simpson(l, m), R = simpson(m, r);
    if (fabs(L + R - S) < 15 * eps)
        return L + R + (L + R - S) / 15;
    return asr(l, m, eps / 2, L) + asr(m, r, eps / 2, R);
}
{
    LD c = (l + r) / 2;
    return (f(l) + 4 * f(c) + f(r)) * (
LD asr(LD l, LD r, LD eps) { return asr(l, r, eps, simpson(l, r)); }

int main()
{
    int round;
    scanf("%d", &round);
    while(round--){
        LD l, r;
        scanf("%lf%lf%lf%lf", &a, &b, &l, &r);
        printf("%.3lf\n", 2.0 * asr(l, r,eps));
    }
}
```

