//数位dp入门
#include <bits/stdc++.h>

using namespace std;
long long dp[25][2];
int digit[25];

//if4 上一个是不是4; lim 上一个是否是上界
long long dfs(int len, bool if4, bool lim)
{
    if(len==0)
        return 1;
    if(!lim&&dp[len][if4])
        return dp[len][if4];
    int up = lim ? digit[len] : 9;
    long long cnt = 0;
    for (int i = 0; i <= up; i++)
    {
        if(if4&&i==9)
            continue;
        cnt += dfs(len - 1, i == 4, lim&&i == up);
    }
    //如果不是恰好上界，记录下来
    if(!lim)
        dp[len][if4] = cnt;
    return cnt;
}

long long get(long long val){
    int v = 0;
    while (val)
    {
        digit[++v] = val % 10;
        val /= 10;
    }
    return dfs(v, 0, 1);
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    memset(dp, 0, sizeof(dp));
    while(round--){
        long long n;
        scanf("%lld", &n);
        printf("%lld\n", n-get(n)+1);
    }
    return 0;
}
