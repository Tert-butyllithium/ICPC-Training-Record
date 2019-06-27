# Codeforces Round 570(Div 3)

通过题目：A-D (4/8)

## A [Nearest Interesting Number](https://codeforces.com/contest/1183/problem/A)

题意：定义interesting number是一个数如果每一位之和是4的倍数，先给出一个数a (1≤𝑎≤1000)，找出一个大于等于a的最小的interesting number

思路：最开始的我wa了一发，因为我只考虑了a到a+4(我是傻逼)

```java
public static void main(String[] args) {
   Scanner scanner=new Scanner(System.in);
   int a=scanner.nextInt();
   for(int i=a;i<=1003;i++){
   if(cal(Integer.toString(i))==0){
       System.out.println(i);
       return;
       }
   }
}

static int cal(String str){
    int res=0;
   	for(char ch:str.toCharArray()){
      res=res+(ch-'0');
      res%=4;
    }
    return res;
}
```

通过时间：7(+1)

## B [Equalize Prices](https://codeforces.com/contest/1183/problem/B)

题解：你有n个货物，每个货物的价格可能不同，你想把他们的价格调成某个数，但是每个商品的调节范围为k，求这个数最大是多少

思路：看最小值+k和最大值-k有没有交集即可，如果有的话，那就是最小值+k

```c++
int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n;i++){
            scanf("%d", &arr[i]);
        }
        sort(arr + 1, arr + 1 + n);
        if(arr[1]+k>=arr[n]-k){
            printf("%d\n", arr[1] + k);
        }
        else{
            puts("-1");
        }
    }
}
```

通过时间：18 

## C [Computer Game](https://codeforces.com/contest/1183/problem/C)

题意：你要用笔记本打游戏，笔记本初始电量为b，你有n轮游戏可以玩。每轮游戏可以直接玩消耗电a，或者边充电边玩消耗b（a严格大于b），问再能打完所有轮的前提下，最多不插电直接玩多少轮

思路：wa了一发，因为该用long long的时候用了int，我是傻逼

```c++
int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        ll k, n, a, b;
        scanf("%lld%lld%lld%lld", &k, &n, &a, &b);
        ll r = k - n * b - 1;
        if (r < 0)
        {
            puts("-1");
            // continue;
        }
        else{
            printf("%lld\n", min(n,r / (a - b)));
        }
    }
}
```

通过时间：31(+1)

## D [Candy Box (easy version)](https://codeforces.com/contest/1183/problem/D)

题意：给你n个糖的类型，你要给一些糖作为礼物，要求每种糖的数量应该是不同的，问这个礼物最多能有多少糖

思路：先计数，然后排个序从大到小遍历，记录上一个选择的值，如果当前值大于上一个值，就把当前值改为上一个值-1

```c++
int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        scanf("%d", &n);
        fill(arr, arr + 1 + n, 0);

        for (int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            arr[x]++;
        }
        ll res = 0;
        sort(arr + 1, arr + 1 + n);
        int cur = maxn;
        for (int i = n; i >= 1 && arr[i]&&cur;i--){
            if(arr[i]<cur){
                res += arr[i];
            }
            else{
                arr[i] = cur - 1;
                res += arr[i];
            }
            cur = arr[i];
        }
        printf("%lld\n", res);
    }
}
```

这个题目错了3发，前两发是想了个假算法，最后一发是由于`memset` 导致TLE

通过时间：75(+3)

## E/H [Subsequences](https://codeforces.com/contest/1183/problem/H)

题意：给一个n长的字符串，现要利用这个字符串的子序列填充一个容量为k的集合(集合元素不重复)(1≤𝑛≤100,1≤𝑘≤10^12^)，每个子序列的代价是n-长度，求填充满的这个集合的最小代价

思路：考虑dp，`dp[i][j]`表示前i个字符中长度为j的不同的字符串数量。用last数组记录第i个字符上一个出现的位置，于是得到状态转移方程如下：

- 如果`last[i]=0` ，也就是说这个位置的字符是整个字符串的第一次出现，这样分两种情况讨论：第i个字符出现与否。于是有`dp[i][j]=dp[i-1][j]+dp[i-1][j-1]`
- 如果`last[i]!=0`，注意到`last[i]-1` 取j-1个字符的每个情况，都会和从`i-1` 取j-1个字符重复。因此在考虑第二种情况：即第i个字符出现时，需要额外减去`dp[last[i]-1][j-1]`。于是，` dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] - dp[last[i]-1][j-1];`

注意这个状态转移方程是指数的，所以最后很显然会溢出。主要到如果`dp[i][j]>k` , 大于k的部分并没有什么意义，直接赋值为k即可

```c++
for (int i = 0; i <= n;i++){
    dp[i][0] = 1;
}
for (int i = 1; i <= n; i++)
{
    dp[i][i] = 1;
    for (int j = 1; j < i; j++)
    {
      if (last[i] == 0){
           dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
      }
      else
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] - dp[last[i]-1][j-1];
      if(dp[i][j]>k)
            dp[i][j] = k;
    }
}
```

通过时间：♾

## F [Topforces Strikes Back](https://codeforces.com/contest/1183/problem/F)

题意：从n个数选至多三个数，要求这些数字互相不整除。对这几个数求和，求这个和的最大值。

思路：虽然数字数量可能很多，但是实际上一个2e5以内的数，最多只有160个因数(166320和196560)。分两种情况处理：

- 取小于等于两个数：最大的数必须取，否则只能取这个最大的值的一个因数，其中最大的是m/2，这样两个数加起来都不会更优于只取一个数
- 取三个数：要么取最大的数然后搭上两个别的数(回到上一种情况)，要么取(如果最大的数是m) m/2, m/3, m/5：因为不包含最大数，说明必然是m的三个因数，否则可以带上最大数达到更大的和。

这样，对这些数字去重然后排序只有就很轻易得到结果了

```c++
#include <bits/stdc++.h>
using namespace std;
set<int,greater<int>> se;

bool test235(int top){
    if(top%30)
        return false;
    return se.count(top / 2) && se.count(top / 3) && se.count(top / 5);
}

int solve_two(){
    if(se.begin()==se.end()){
        return 0;
    }
    int top = *se.begin();
    int ans = top;
    se.erase(se.begin());
    
    for (auto val : se)
    {
        if (top % val)
        {
            ans += val;
            break;
        }
    }
    return ans;
}

int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        scanf("%d", &n);
        se.clear();
        for (int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            se.insert(x);
        }
        int top = *se.begin();
        int ans = solve_two();
        if (test235(top))
        {
            ans = max(ans, top / 2 + top / 3 + top / 5);
        }
        for(int i=1;i*i<=top;i++){
            if(top%i==0){
                se.erase(i);
                se.erase(top/i);
            }
        }
        ans = max(ans, solve_two() + top);
        printf("%d\n", ans);
    }
}
```

通过时间：♾

## G [Candy Box (hard version)](https://codeforces.com/contest/1183/problem/G)

题意：与D相比，对于每颗糖多了一个参数f，如果f为1表示你不喜欢这颗糖，如果f为0则代表你喜欢这颗糖。求在D的约束下(送的糖数量最多)的前提下尽可能送出不喜欢的糖，输出总数量和不喜欢的糖的数量

思路：对于两个种类，如果能送出的糖果数量一样，那么优先选择不喜欢数量更多的那个

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
const int maxn = 2e5 + 10;
int arr[maxn];
int fav[maxn];
priority_queue<pair<int, int>> pq;

int main(){
    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        scanf("%d", &n);
        fill(arr + 1, arr + 1 + n, 0);
        fill(fav + 1, fav + 1 + n, 0);
        for (int i = 1; i <= n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            arr[x]++;
            fav[x] += y;
        }
        while(!pq.empty()){
            pq.pop();
        }
        for (int i = 1; i <= n;i++){
            if(arr[i]){
                pq.emplace(arr[i], fav[i]);
            }
        }
        int cur = maxn;
        ll sz = 0, tot = 0;
        while (!pq.empty()&&cur>0)
        {
            auto top = pq.top();
            pq.pop();
            if(top.first<cur){
                sz += top.first;
                tot += top.second;
                cur = top.first;
            }
            else{
                top.first = cur - 1;
                top.second = min(top.second, top.first);
                pq.push(top);
            }
        }
        printf("%llu %llu\n", sz, tot);
    }
}

```


