# Day6 组合数学

- 第一类斯特林数：表示将 n 个不同元素构成 m 个圆排列的数目

  s(n, k) = s(n − 1, k − 1) + (n − 1)s(n − 1, k)

- 第二类斯特林数： 表示将 n 个不同的元素分成 m 个集合的方案数

  S(n, k) = S(n − 1, k − 1) + kS(n − 1, k)

- n个相同元素放到k个不同的集合，每个集合至少一个相应元素：隔板法${n-1}\choose{k-1}$

- 卡特兰数：一个栈 ( 无穷大 ) 的进栈序列为 1, 2, ... , n ,有多少种不同的出栈序
  列 ?

## A - HDU 2048

题意：n个元素，求错排的概率

题解：

显然D1=0，D2=1。当n≥3时，不妨设n排在了第k位，其中k≠n，也就是1≤k≤n-1。那么我们现在考虑k的情况。

- 当k排在第n位时，除了n和k以外还有n-2个数，其错排数为Dn-2。
- 当k不排在第n位时，那么将第n位重新考虑成一个新的“第k位”，这时的包括k在内的剩下n-1个数的每一种错排，都等价于只有n-1个数时的错排（只是其中的第k位会换成第n位）。其错排数为Dn-1。

所以当n排在第k位时共有Dn-2+Dn-1种错排方法，又k有从1到n-1共n-1种取法，我们可以得到：

$D_n=(n-1)(D_{n-1}+D_{n-2}) ​$

注意：没事就别用long double了，容易出事

```c++
#include <bits/stdc++.h>
using namespace std;
double biao[30];
double jiechen[30];

int main(){
    biao[1] = 0;
    biao[2] = 1;
    jiechen[1] = 1;
    jiechen[0] = 1;
    for (int i = 2; i < 30; i++)
    {
        jiechen[i] = 1.00*i* jiechen[i - 1];
    }

    for (int i = 3; i < 30;i++){
        biao[i] =1.00* (i - 1) * (biao[i - 2] + biao[i - 1]);
    }

    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        scanf("%d", &n);
        printf("%.2f%%\n", biao[n] / jiechen[n] * 100.0);
    }
}
```

## B - HDU 1071

题意：给一个抛物线的顶点坐标和这个抛物线与一条直线的两个交点的坐标，求围成图形的面积

题解：高中数学题，根据坐标求出抛物线的参数，写出用积分算就是了，或者用辛普森公式求积分（反正也没有误差）

```c++
#include <bits/stdc++.h>
using namespace std;
double x1, _y1, x2, y2, x3, y3;
double a, b;
double k, c;
const double eps = 1e-8;
inline double sq(double x){return x * x;}
inline double cu(double x){return x * x * x;}

double geta(){ return 1.0*(y2 - _y1) / (sq(x2-x1));}
double getb(){ return _y1;}
void getk_c(){
    k = (y3 - y2) / (x3 - x2);
    c = y2-k*x2;
}

inline double f(double x){
    return a*sq(x-x1)-k*x+(b-c);
}

double simpson(double l, double r)
{
    double c = (l + r) / 2;
    return (f(l) + 4 * f(c) + f(r)) * (r - l) / 6;
}
double asr(double l, double r, double eps, double S)
{
    double m = (l + r) / 2;
    double L = simpson(l, m), R = simpson(m, r);
    if (fabs(L + R - S) < 15 * eps)
        return L + R + (L + R - S) / 15;
    return asr(l, m, eps / 2, L) + asr(m, r, eps / 2, R);
}
double asr(double l, double r, double eps) {
    return asr(l, r, eps, simpson(l, r)); }

int main(){
    std::ios::sync_with_stdio(false);
    int round;
    cin >> round;
	cout << std::fixed << std::setprecision(2);
	while (round--)
	{
        cin >> x1 >> _y1 >> x2 >> y2 >> x3 >> y3;
        a = geta();
        b = getb();
        getk_c();
        cout << asr(x2, x3, eps) << endl;
    }
}
```



## C - UVA 10733

题意：求用n中颜色涂立方体的不同种数，能旋转到的算一种

题解：

- 不变置换(1)(2)(3)(4)(5)(6), 共1个;

- 沿对面中心轴旋转 90度, 270度 (1)(2345)(6), (1)(5432)(6) 同类共 6个;

-  沿对面中心轴旋转 180度 (1)(24)(35)(6), 同类共 3个;

- 沿对角线轴旋转 120度, 240度 (152)(346), (251)(643) 同类共 8个;

- 沿对边中点轴旋转 180度 (16)(25)(43) 同类共 6个;

然后polya原理用一用得到公式:$a_n=(n^6 + 3*n^4 + 12*n^3 + 8*n^2)/24$

~~或者直接在oeis上搜“cube color”第一个就是~~

好像long long也可以，没必要unsigned long long

```c++
#include <cstdio>
unsigned long long pow(unsigned long long n,int p){
    unsigned long long res = 1;
    for (int i = 0; i < p;i++){
        res *= n;
    }
    return res;
}

unsigned long long get(int n){
 return 1ull * (pow(n,6) + 3 * pow(n,4) + 12 * pow(n,3) + 8 * pow(n,2)) / 24;
}

int main(){
    int n;
    while(scanf("%d",&n)&&n){
        printf("%llu\n", get(n));
    }
}
```

## D - HDU 4651

题意：整数拆分公式题

题解： [公式推导](https://www.cnblogs.com/rpSebastian/p/7275968.html) ~~(或者oeis\wikipedia搜索“number partition”)~~

可以得到递推关系：![](https://wikimedia.org/api/rest_v1/media/math/render/svg/89d2907100f525090adfbaeca230d7c7e74f37b3)

其中q_i 是第i个广义五边形数![](https://wikimedia.org/api/rest_v1/media/math/render/svg/c3ec82bd6f9ef7870af2307d3e8d6af380460fef)

（第i个广义五边形数有两个）

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9+7;
const int maxn = 1e5 + 10;
ll p[maxn];

int main(){
    p[0] = 1;
    for (int i = 1; i < maxn;i++){
        ll tmp = 1;
        for (int j = 1; i >= (3 * j * j - j) / 2; j++, tmp *= -1)
        {
            int x = (3 * j * j - j) / 2;
            int y = (3 * j * j + j) / 2;
            p[i]=(p[i]+1ll*tmp*p[i-x]+mod)%mod;
            if(i>=y)
                p[i] = (p[i] + 1ll*tmp * p[i - y] + mod) % mod;
        }
    }
    int round;
    scanf("%d", &round);
    while(round--){
        int x;
        scanf("%d", &x);
        printf("%lld\n", p[x]);
    }
}
```

## E - HDU 5366

题意：一排有N块砖，在砖上放木人桩，每个木人桩之间至少隔两块砖，求共有多少种可能

题解：考虑dp，当扩增到第n块砖时，如果第n块不放砖，那么答案就是dp[n-1]，如果第n块要放砖那么答案就是dp[n-3]，然后 （~~基于调参技巧发现还要+1~~ ） 经过推导发现dp[n]=dp[n-1]+dp[n-3]+1;

或者暴力算出前20个然后找规律 ~~（扔进oeis）~~ 

```c++
#include <bits/stdc++.h>
using ll = long long;
const int maxn = 65;
ll dp[maxn];

int main(){
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < maxn;i++){
        dp[i] = dp[i - 1] + dp[i - 3] + 1;
    }
    int n;
    while(scanf("%d",&n)!=EOF){
        printf("%lld\n", dp[n]);
    }
}
```

## F - HDU 2512

题意：n个不同的物品，放到不超过n个集合，有多少种放法

题解：第二类斯特林数求和（贝尔数）

```c++
#include <bits/stdc++.h>
const int maxn = 2005;
const int mod = 1000;

int s[maxn][maxn];
int ans[maxn];
int find(int n, int k)
{
    return s[n][k];
}

int getans(int x){
    if(ans[x]!=-1)
        return x;
    int res = 0;
        for (int i = 1; i <= x;i++){
            res = (res + find(x, i)) % mod;
    }
    return ans[x]=res;
}

void init(){
    for (int i = 1; i < maxn;i++){
        for (int j = 1; j < maxn;j++){
            if(j>i)
                s[i][j] = 0;
            else if (i == j)
                s[i][j] = 1;
            else if(j==1)
                s[i][j] = 1;
            else
                s[i][j] = (j * s[i - 1][j] % mod + s[i - 1][j - 1]) % mod;
        }
    }

    for (int i = 1; i < maxn;i++){
        for (int j = 1; j <= i;j++){
            ans[i] = (ans[i] + s[i][j]) % mod;
        }
    }
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    init();
    memset(ans, -1, sizeof(ans));
    while (round--)
    {
        int x;
        scanf("%d", &x);
        printf("%d\n", getans(x));
    }
    return 0;
}
```

## G - HDU 4372

题意：有n个建筑高为1～n，从前往后看能看到f个，从后往前看能看到b个，求有多少种可能的排列情况

题解：“中间的”一定是最高的那一栋，先考虑从前往中间看的f-1个栋建筑，就形成了f-1个区域，这f-1个区域的每个除了第一个元素外的全排列，就是每个区域的圆排列，那么就是S(n-1)(f+b-2)，S表示第一类斯特林数，然后再乘上组合数，表示要挑选f-1个集合放在前面。

```c++
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
using ll = long long;
const ll MOD = 1000000007;
const int N=2019;
ll S[N][N];
ll invf[N*2],fac[N*2]={1};

ll bin(ll x, ll n, ll p)
{
	ll ret = p != 1;
	for (x %= p; n; n >>= 1, x = x * x % p)
	if(n & 1) ret = ret * x % p;
	return ret;
}

void init()
{
	S[0][0] = 1;
	FOR(i, 1, N)
	FOR(j, 1, i + 1)
	S[i][j] = (S[i - 1][j - 1] + (i-1) * S[i - 1][j]) % MOD;

	FOR(i,1,N)
	fac[i] = i * fac[i - 1] % MOD;
	invf[N - 1] = bin(fac[N - 1], MOD - 2, MOD);
	FORD (i, N - 2, -1)
           invf[i] = invf[i + 1] * (i + 1) % MOD;
}

inline ll C(ll n, ll m) { // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * invf[m] % MOD * invf[n - m] % MOD;
}

int main(int argc, char const *argv[])
{
	int round;
	scanf("%d", &round);
	init();
	int n, f, b;
	while (round--)
	{
		scanf("%d%d%d", &n, &f, &b);
		f--;b--;
		printf("%lld\n", S[n-1][f + b] * C(f + b, f) % MOD);
	}
	return 0;
}

```

## I - HDU 3723

题意：从坐标系的第一象限，(0,0)点到(n,0)点，不能到x轴以下，每次y值差值最大为1，也就是要么加1，要么减1，要么不变。问有多少种走法

题解：卡特兰数，枚举有多少个0，那么剩下的-1和1的数量必然想相等，并且要先+1再-1，这就满足了卡特兰数的性质。那么T(k)=C(n,2\*k)\*Cat[k]=C(n,2\*k)\*C(2\*k,k)/(k+1), k是枚举量

这题关键其实测试大整数的板子，然而我们都是Java选手

```java
import java.math.BigInteger;
import java.util.*;

public class Main {

    static BigInteger getK(int i,int n){
        return BigInteger.valueOf((n-2*i+2)*(n-2*i+1));
    }


    public static void main(String[] args) {
        Scanner scanner=new Scanner(System.in);
        while(scanner.hasNext()){
            int n=scanner.nextInt();
            BigInteger cur=BigInteger.ONE;
            BigInteger ans=BigInteger.ONE;
            for(int i=1;i<=n/2;i++){
                cur=cur.multiply(getK(i,n)).
                    divide(BigInteger.valueOf(i*(i+1)));
                ans=ans.add(cur);
            }
            String str=ans.toString();
            System.out.println(newBigInteger(
              str.substring(Math.max(0,str.length()-100))));
        }
    }

}
```

## I - SPOJ VLATTICE

题意：一个n\*n\*n的方格，从最左下角(0, 0, 0)最多可以看到多少个点？（不被遮挡）包括方格内部。 

题解：

如果这个点为(0,0,0)，那么显然不能，如果这个点有两个0，那么就是(0,0,1), (0,1,0), (1,0,0)三种，如果只有一个0，那么就是gcd(x,y)=1 的个数×3，否则就是gcd(x,y,z)=1的个数

然后就是一个非常简单的莫比乌斯变换：$\displaystyle\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[\gcd(i,j,k)=1] \Leftrightarrow  \sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n\sum_{d|i,d|j,d|k}\mu(d)\Leftrightarrow\sum_{d=1}^n\mu(d)\lfloor{n/d}\rfloor^3​$ 

（和氏的变换可以理解为：枚举顺序。这里我们枚举i，j，k，再枚举d表示i，j，k的因数，如果改变枚举顺序，先枚举d，那么d的取值范围是1～n，并且对于每个d，他有[n/d]个倍数）

然后二维的只需把立方改成平方就完事了

```c++
#include <bits/stdc++.h>
using ll = long long;
const ll p_max = 1E6 + 10;
ll mu[p_max];
void get_mu()
{
    mu[1] = 1;
    static bool vis[p_max];
    static ll prime[p_max], p_sz, d;
    mu[1] = 1;
    for (int i = 2; i < p_max;i++)
    {
        if (!vis[i])
        {
            prime[p_sz++] = i;
            mu[i] = -1;
        }
        for (ll j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j)
        {
            vis[d] = 1;
            if (i % prime[j] == 0)
            {
                mu[d] = 0;
                break;
            }
            else
                mu[d] = -mu[i];
        }
    }
}


ll cal(int n){
    ll res=0;
    for(int i=1;i<=n;i++){
        if(mu[i]){
            ll tmp = n / i;
            res += mu[i] * tmp * tmp * tmp;
            res += mu[i] * tmp * tmp * 3;
        }
    }
    return res;
}

int main(){
    get_mu();
    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        scanf("%d", &n);
        printf("%lld\n", cal(n) + 3ll);
    }
}
```

## J - ZOJ 3624

题意：4个点 A(0, 0), B(p, 0), C(m, q), D(m, n) ,保证 p < m, q < n,求从 A 走到 D 和从 B 走到 C 两条路径不相交的走法的种数。

题解：总路径数-相交路径数。相交的路径必然至少有一个交点，如果我们选取一个点进行路径交换，那么这条路径就相当与是一条从A走到C和从B走到D的路径。而每个从A走到C和从B走到D的路径必然对应某一条相交的路径。于是所有从A走到C和从B走到D的路径就是相交路径数。

公式就是C(M+N,M)C(Q+M-P,Q)-C(N+M-P,N)C(M+Q-M);

```c++
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define FOR(i, x, y) for (int i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (int i = (x), _##i = (y); i > _##i; --i)

const int M = 200005;
const LL MOD = 100000007;
LL invf[M], fac[M] = {1};

LL bin(LL x, LL n, LL MOD)
{
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1)
            ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

void fac_inv_init(LL n, LL p)
{
    FOR(i, 1, n)
    fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = bin(fac[n - 1], p - 2, p);
    FORD(i, n - 2, -1)
    invf[i] = invf[i + 1] * (i + 1) % p;
}

inline LL C(LL n, LL m)
{ // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * invf[m] % MOD * invf[n - m] % MOD;
}

inline LL mul(LL a,LL b){
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline LL sub(LL a,LL b){
    return (a - b + MOD) % MOD;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    int m, n, p, q;
    fac_inv_init(M, MOD);
    while (cin >> m >> n >> p >> q)
    {
        cout << sub(mul(C(n + m, m), C(m + q - p, q)), 
                    mul(C(m + q, m), C(m + n - p, n)))<<endl;
    }
    return 0;
}
```

