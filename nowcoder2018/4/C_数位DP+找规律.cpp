#include <bits/stdc++.h>

using namespace std;
const int mod = 1e9 + 7;
long long dp[64][3][128];
int digit[64];
int cot;

int judge(int i,int fro){
    return i == fro ? 1 : -1;
}

long long dfs(int pos,bool lim,int num,int fro){
    if(!pos)
        return abs(64 - num);
    if(!lim&&dp[pos][fro][num]!=-1)
        return dp[pos][fro][num];
    int up = lim ? digit[pos] : 1;
    long long cnt = 0;
    for (int i = 0; i <= up;i++){
        if(fro==2&&i==0)
            cnt += dfs(pos - 1, lim && (i == up), num, 2);
        else if(fro==2&&i==1)
            cnt += dfs(pos - 1, lim && (i == up), num, 1);
        else
            cnt += dfs(pos - 1, lim && i == up, num + judge(i, fro), i);
        cnt %= mod;
    }
    if(!lim)
        dp[pos][fro][num] = cnt;
    return cnt;
}

long long solve(long long val){
    int v = 0;
    while(val){
        digit[++v] = val % 2;
        val /= 2;
    }
    return dfs(v, 1, 64, 2);
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
