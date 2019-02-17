# Codeforces Global Round 1

## C

题意: $f(a) = \max_{0 < b < a}{gcd(a \oplus b, a \> \& \> b)}.$ 给一个数字a，求f(a)

解法一：打表找规律发现：如果这个数字不是全“1”（2进制下），那么答案是大于它的最小的2^x-1，（也就是最接近的2进制下全1），而如果是全“1”，这样的数字只有25个，打表预处理即可。

```c++
#include <bits/stdc++.h>
using namespace std;

int dig(int val){
    int res = 0;
    while (val)
    {
        res++;
        val >>= 1;
    }
    return res;
}

int main(){
    map<int, int> m;
    m[1] = 1;m[3] = 1;m[7] = 1;m[15] = 5;m[31] = 1;m[63] = 21;m[127] = 1;m[255] = 85;m[511] = 73;m[1023] = 341;m[2047] = 89;m[4095] = 1365;m[8191] = 1;m[16383] = 5461;m[32767] = 4681;m[65535] = 21845;m[131071] = 1;m[262143] = 87381;m[524287] = 1;m[1048575] = 349525;m[2097151] = 299593;m[4194303] = 1398101; m[8388607] = 178481; m[16777215] = 5592405;m[33554431] = 1082401;

    int n;
    scanf("%d", &n);
    while(n--){
        int x;
        scanf("%d", &x);
        if(m.find(x)!=m.end()){
            printf("%d\n", m[x]);
            continue;
        }
        int c = dig(x);
        printf("%d\n", (1 << c) - 1);
    }
}
```

解法二： 计a的位数为x，$(2^x\le a)$ ，并且 $b = (2^x - 1) \> \oplus a$ , 如果$a\neq 2^x-1$ ，则有$0<b<a$ ，注意到 $ a\&b=a\&(2^x - 1) \> \oplus a=a\oplus a=0$ ,所以$\gcd(a\oplus b, a\& b)=\gcd(2^x-1,0)=2^x-1$ ，显然这就是f(a)。

再考虑当a为$2^x-1​$ 时，此时$a\oplus b=a-b​$, $a\&b=b​$ , gcd(a-b,b)=gcd(a,b) ，那么只需找到a的除自己以外的最大因数即可。

代码略

## D

题意：给定一个n长值域为m的序列，你要将其组成尽可能多的三元组(a,b,c)满足a=b=c或者b=a+1,c=b+1。

题解：对于三个三元组(i,i+1,i+2)，它等价于三个三元组(i,i,i),..,(i+2,i+2,i+2)。也就是说每个三元组至多出现两次，用`dp[i][j][k]` 记录答案，表示前i种牌中并且之后会（至多）有j个(i,i+1,i+2)和k个(i-1,i,i+1)，状态转移时，需要枚举前i个有x个(i-2,i-1,i) ，于是得到转移方程$dp(i,a,b)=\max_{0\leq c \leq 2}(dp(i-1,b,c)+c+(cnt-a-b-c) / 3)$

注意：考虑状态转移时，如果需要考虑情况太多，那么应当尝试把更多的状态记录进去，应该尽量使状态转移方程的枚举量只有一个

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int arr[maxn];
int dp[maxn][3][3];

int main(){
    int n,m;
    scanf("%d%d", &n, &m);
    while(n--){
        int x;
        scanf("%d", &x);
        arr[x]++;
    }
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int a = 0; a < 3;a++){
            for (int b = 0; b < 3;b++){
                for (int c = 0; c < 3;c++){
                    int tmp =arr[i]-(a + b + c);
                    if(tmp>=0&&dp[i-1][b][c]>=0)
                        dp[i][a][b] = max(dp[i][a][b], dp[i - 1][b][c] +c+ tmp / 3);
                }
            }
        }
    }
    int ans = 0;
    for (int a = 0; a < 3;a++){
        for (int b = 0; b < 3;b++){
            ans = max(ans, dp[m][a][b]);
        }
    }
    printf("%d\n", ans);
}

```

