#include <iostream>
#include <cstring>
#include <algorithm>
#define N 505

//graph[a][b]代表a到b间说真话的人数
int graph[N][N];
int dp[N];

int main(int argc, char const *argv[])
{
    int n;
    while(scanf("%d",&n)!=EOF){
        memset(graph, 0, sizeof(graph));
        memset(dp, 0, sizeof(dp));
        for (int v = 0; v < n;v++){
            int a, b;
            scanf("%d%d", &a, &b);
            if(a+b>n)
                continue;
            //如果是合理的，那么人数++
            if(n-a-b>graph[a+1][n-b])
                graph[a + 1][n - b]++;
            //说真话人数不会大于区间最大值
            else
                graph[a + 1][n - b] = n - a - b;
        }
        for (int i = 1; i <= n;i++){
            for (int j = 0; j < i;j++){
                dp[i] = std::max(dp[i], dp[j] + graph[j + 1][i]);
            }
        }
        printf("%d\n", dp[n]);
    }
}

