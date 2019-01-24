# Day5 数论

## 一些定义和性质

- $\displaystyle\lceil\frac{n}{ab}\rceil=\lceil\frac{\lceil\,n/a\,\rceil}{b}\rceil$, $\displaystyle\lfloor\frac{n}{ab}\rfloor=\lfloor\frac{\lfloor\,n/a\,\rfloor}{b}\rfloor$

- $\displaystyle\lceil\frac{n}{i}\rceil$ 只有$O(\sqrt{N})$ 种取值

- ***数论函数***：定义域为正整数，陪域为复数的函数。我们主要研究定义域为正整数，值域为整数的函数。

- ***积性函数***：满足 若a, b互质，则f (ab) = f (a)f (b) 的数论函 数称为积性函数。 

- ***完全积性函数***：满足 f (ab) = f (a)f (b) 的数论函数称为完全积性函数
- ***狄利克雷卷积***：对于数论函数$\displaystyle f,g$，定义其狄利克雷卷积$(f * g)(n) = \sum_{d|n} f(d) g(\frac{n}{d})$

- 两个积性函数的狄利克雷卷积仍为积性函数

## 一些常见的积性函数

- 单位函数 $\displaystyle{e(x)=\cases{1, x=1 \\0,x>1}}$ 
- 常函数I(x)=1
- 幂函数id(x)=$x^k$ 
- 欧拉函数$\phi(x)$ 代表[1,x]中与x互质的个数=${\displaystyle \varphi (n)=\prod _{i=1}^{r}p_{i}^{k_{i}-1}(p_{i}-1)=\prod _{p\mid n}p^{\alpha _{p}-1}(p-1)=n\prod _{p|n}\left(1-{\frac {1}{p}}\right)}$ 

## 莫比乌斯恒等式



## 杜教筛


求 $S(n)=\sum_{i=1}^n f(i)$，其中 $f$ 是一个积性函数。

构造一个积性函数 $g$，那么由 $(f*g)(n)=\sum_{d|n}f(d)g(\frac{n}{d})$，得到 $f(n)=(f*g)(n)-\sum_{d|n,d<n}f(d)g(\frac{n}{d})$。

$\displaystyle\begin{eqnarray} g(1)S(n)&=&\sum_{i=1}^n (f*g)(i)-\sum_{i= 1}^{n}\sum_{d|i,d<i}f(d)g(\frac{n}{d}) \ &\overset{t=\frac{i}{d}}{=}& \sum_{i=1}^n (f*g)(i)-\sum_{t=2}^{n} g(t) S(\lfloor \frac{n}{t} \rfloor) \end{eqnarray}$

当然，要能够由此计算 $S(n)$，会对 $f,g$ 提出一些要求：

- $f*g$ 要能够快速求前缀和。
- $g$ 要能够快速求分段和（前缀和）。
- 对于正常的积性函数 $g(1)=1$，所以不会有什么问题。

在预处理 $S(n)$ 前 $n^{\frac{2}{3}}$ 项的情况下复杂度是 $O(n^{\frac{2}{3}})$

## A - HDU 4965

两个矩阵A，B，求（A*B）的N*N次幂。其中元素都%6 因为N范围是1000，K范围是6，如果直接对A \* B快速幂的话是对一个1000\*1000的矩阵操作，会TLE。所以可以先求出\*A的（N\*N-1）次方，这是一个5\*5的矩阵，再右乘A左乘B

[refer](https://blog.csdn.net/baoli1008/article/details/38708059)

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
 
struct mat{
    int n,m;
    vector<vector<int> >a;
    mat(int n,int m):n(n),m(m){
        a.resize(n);
        for(int i=0;i<n;i++){
            a[i].resize(m,0);
        }
    }
    friend mat operator *(const mat &T,const mat &V){
        mat tmp(T.n,V.m);
        for(int i=0;i<T.n;i++){
            for(int j=0;j<T.m;j++){
                for(int k=0;k<V.m;k++){
                    tmp.a[i][k]+=T.a[i][j]*V.a[j][k];
                    tmp.a[i][k]%=6;
                }
            }
        }
        return tmp;
    }
    mat pow(int p){
        mat tmp(n,n);
        mat k(n,n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                k.a[i][j]=a[i][j];
            }
        }
        for(int i=0;i<n;i++){
            tmp.a[i][i]=1;
        }
        while(p){
            if(p&1){
                tmp=tmp*k;
            }
            k=k*k;
            p>>=1;
        }
        return tmp;
    }
};
 
int main(){
    int N,K;
    while(scanf("%d%d",&N,&K)!=EOF){
        if(!N&&!K) break;
        mat x(N,K);
        for(int i=0;i<N;i++){
            for(int j=0;j<K;j++){
                scanf("%d",&x.a[i][j]);
            }
        }
        mat y(K,N);
        for(int i=0;i<K;i++){
            for(int j=0;j<N;j++){
                scanf("%d",&y.a[i][j]);
            }
        }
        mat c(K,K);
        c=y*x;
        mat res(N,N);
        res=c.pow(N*N-1);
        res=x*res;
        res=res*y;
        int ans=0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                ans+=res.a[i][j];
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

## B - UVA 10655

题意：给出两个数字代表a+b和a\*b,再给一个数字n，求$a^n+b^n$ 

题解：首先直接把这两个值带入二次方程求解是错误的，因为a和b可以为复数，如$2+i$ 与 $2-i$，我们无法处理这种情况

考虑递推公式：$a^n+b^n=(a^{n-1}+b^{n-1})\cdot{(a+b)}-(a^{n-2}+b^{n-2})\cdot(ab)$

令$f(n)=a^n+b^n$，于是有$$\begin{bmatrix}
a+b & -ab \\
1 & 0  
\end{bmatrix} 
\begin{bmatrix}
f(n-1)\\
f(n-2)
\end{bmatrix} =\begin{bmatrix}
f(n)\\
f(n-1)
\end{bmatrix}$$

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
        {
            c.m[i][j]=c.m[i][j]+x.m[i][k]*y.m[k][j];
          }
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

题解：直接N^3会T，需要用循环矩阵优化到N^2

[refer](https://blog.csdn.net/accelerator_/article/details/37992531)

## D - HDU 5680

题意：$f(x)$ 满足$N^2-3N+2=\sum_{d|N} f(d)$ ，求$\sum_{i=1}^{N} f(i)$ ， N<1e9，	且只有5个测试大于1e6

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
            if (!vis[i]) { pr[p_sz++] = i; mu[i] = -1; }
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



## E - HDU 5942

//TODO [莫比乌斯函数+容斥原理](https://blog.csdn.net/V5ZSQ/article/details/79849545)

## F - BZOJ 2818

//TODO [莫比乌斯函数](https://blog.csdn.net/u010579068/article/details/47786203)

