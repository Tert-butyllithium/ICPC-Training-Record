//简单的dp

#include <iostream>
#include <cstring>
#include <cmath>
 
using namespace std;
const int maxn = 100009;
long long dp[maxn];
long long sum[maxn];
 
const int mod = 1000000007;
int main(){
    int q, k;
    scanf("%d%d", &q, &k);
    dp[0] = 0;
    for(int i=1;i<k;i++)
        dp[i] = 1;
    dp[k] = 2;
    dp[k + 1] = 3;
    for (int i = k + 2; i < maxn;i++){
        dp[i] = (dp[i - 1] + dp[i - k - 1])%mod;
    }
    sum[0] = 0;
    for (int i = 1; i < maxn;i++){
        sum[i] = (sum[i - 1] + dp[i])%mod;
    }
 
    while(q--){
        int a, b;
        scanf("%d%d", &a, &b);
        long long ans = sum[b] - sum[a - 1];
        while(ans<0)
            ans += mod;
        printf("%lld\n",ans);
    }
}
