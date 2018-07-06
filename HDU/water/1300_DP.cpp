#include <iostream>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f

int list[107];
int pri[107];
int dp[107];
int sum[107];
int main(){
    int round;
    scanf("%d",&round);
    while(round--){
        int c;
        scanf("%d", &c);
        sum[0] = 0;
        for (int i = 1; i <= c;i++){
            scanf("%d%d", &list[i], &pri[i]);
            sum[i] = sum[i - 1] + list[i];
        }
        memset(dp, inf, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i <= c;i++){
            for (int j = 0; j < i;j++)
                dp[i] = std::min(dp[i],dp[j] + (sum[i]-sum[j] + 10) * pri[i]);
        }
        printf("%d\n", dp[c]);
    }
}