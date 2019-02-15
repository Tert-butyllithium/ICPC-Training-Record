# Codeforces Round 538

[Problems](https://codeforces.com/contest/1114)

## B 

题意：给一个数组，要求划分为k段，使得每一段的前m大的和之和最大，输出答案和划分位置

题解：首先，答案一定是前m×k个最大元素之和，那么找到这些元素记录位置，然后保证每一段包含m个这样的元素即可。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int arr[maxn];
int n, m, k;

struct node{
    int val, id;
    explicit node(int val=0,int id=0):val(val),id(id){}
    bool operator < (const node& n) const{
        if(val==n.val)
            return id > n.id;
        return val < n.val;
    }
};

int main()
{
    vector<int> pos;
    priority_queue<node> pq;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n;i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i <= n;i++){
        pq.emplace(arr[i], i);
    }
    long long sum=0;
    int c=m*k;
    while(!pq.empty()&&c){
        auto top = pq.top();
        pq.pop();
        pos.push_back(top.id);
        sum+=top.val;
        c--;
    }
    printf("%lld\n",sum);
    sort(pos.begin(),pos.end());
    for(int i=m;i<pos.size();i+=m){
        printf("%d ",pos[i-1]);
    }
}
```

## Ｃ

题意：问n!在ｋ进制下末尾有多少个０, (n<1e18, k<1e12)

题解：求n!中含有多少个因数i的公式是\[n/i\]+\[n/i^2\]+\[n/i^3\]+...，那么对k分解质因数，枚举n!中含有多少个相应因数，取最小值即可。分解质因数可以采用枚举因子法，复杂度O(sqrt(k))

最简单的实现会爆unsigned long long，所以干脆用python写

```python
from math import sqrt

#这里可以进行一些优化，使得不爆unsigned long long: while i<=n/k
def times(n:int,k:int):
    res=0
    i=k
    while i <= n:
        res += n//i
        i *= k
    return int(res)

n,b = map(int, input().split())
sq=int(sqrt(b))
ans=int(1e20)
for i in range(2,sq+1):
    cnt = 0
    while b % i == 0:
        # 这里需要统计这个素因子出现的次数
        b //= i
        cnt += 1
    if cnt is 0:
        continue
    ans=min(ans,times(n,i)//cnt)
if b is not 1:
    ans=min(ans,times(n,b))
print(ans)
```

## D

题意：有一排格子上面标有不同的颜色，你可以选择某一个格子作为起点。如果一个线段内所有格子颜色均相等，则称其为一个联通块。你可以改变起点所在联通块的所有格子的颜色，问需要这样的操作多少次才能使这一排格子只剩下一种颜色。

题解：考虑区间dp，容易证明：对于联通块`dp[i][j]`，他的颜色要么与最左边的那一个格子相同，要么与最右边的那一个格子颜色相同。考虑用一个三维数组，`dp[i][j][0]`表示这个区域为最左边颜色所需联通块的操作数，而`dp[i][j][1]` 表示最右边。就可以很简单地得到状态转移方程:

```c++
#include <bits/stdc++.h>
using std::min;
const int maxn = 5005;
int dp[maxn][maxn][2];
int arr[maxn];

void init(){
    memset(dp,0x3f3f3f3f,sizeof(dp));
    for (int i = 0;i<maxn;i++){
        dp[i][i][0]=dp[i][i][1] = 0;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++){
        scanf("%d", &arr[i]);
    }
    init();
    for (int len = 1; len < n; len++)
    {
        for (int i = 1; i + len <= n;i++){
            int j = i + len;
            //0: the color is the same as leftmost; 1: rightmost
            dp[i][j][0] = min(dp[i + 1][j][0] + (arr[i] != arr[i + 1]), 
                              dp[i + 1][j][1] + (arr[i] != arr[j]));
            dp[i][j][1] = min(dp[i][j - 1][0] + (arr[i] != arr[j]),
                              dp[i][j - 1][1] + (arr[j - 1] != arr[j]));
        }
    }
    printf("%d", min(dp[1][n][0],dp[1][n][1]));
}
```

## E 

题意：交互题，有一个乱序的等差数列，现在有两种操作：

- 查询第i个值(1≤i≤1e6)
- 检查是否有元素大于x

这两种操作之和不能超过60次。其中数列容量不超过1e6，元素范围在1e9之内。求数列的最小值和公差

题解：首先二分得到数列最大值an，需要执行第二项操作 log(1e9)=30次，然后随机取30个点，计算他们的差取最大公约数即可求的公差d。an-(n-1)\*d即为最小值(题解证明了随机算法造成的误差极低：1.8e-9)

注意：随机数不要使用`rand()`， 请使用mt19937 和 mt19937_64，

`chrono::steady_clock::now().time_since_epoch().count()` 可用于计时

```c++
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); 
vector<int> permutation(N);
for (int i = 0; i < N; i++) permutation[i] = i;
    shuffle(permutation.begin(), permutation.end(), rng);
```

```c++
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 1e6 + 10;
int n;
int arr[maxn];

int gcd(int x,int y){
    if(y==0)
        return x;
    return gcd(y, x % y);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n;i++){
        arr[i] = i;
    }
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    int left = 1, right = inf;
    int cnt = 0;
    while (left < right)
    {
        int a1 = left + (right - left) / 2;
        printf("> %d\n", a1);
        fflush(stdout);
        int op;
        scanf("%d", &op);
        cnt++;
        if (op)
        {
            left = a1 + 1;
        }
        else{
            right = a1;
        }
    }
    int an = left;
    cnt = min(59 - cnt,n);
    vector<int> element;
    vector<int> diffs;
    shuffle(arr + 1, arr + n + 1,rng);
    for (int i = 1; i <= cnt;i++)
    {
        printf("? %d\n", arr[i]);
        fflush(stdout);
        int x;
        scanf("%d", &x);
        element.push_back(x);
    }
    for (int i = 0; i < element.size(); i++)
    {
        for (int j = i + 1; j < element.size();j++){
            diffs.push_back(abs(element[i] - element[j]));
        }
    }
    int d = diffs[0];
    for (int i : diffs)
    {
        d = gcd(d, i);
    }
    printf("! %d %d\n", an - (n - 1) * d, d);
}
```

