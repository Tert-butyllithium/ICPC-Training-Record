//多维的01背包问题，他还是个01背包
//不能dfs，因为全0的会出错？（我也不会dfs）

#include <bits/stdc++.h>
using namespace std;
const int maxn = 38;

//算算空间，37^5=6.9e7，37^4=1.8e6,因此要空间压缩的dp
int dp[maxn][maxn][maxn][maxn];
bool vis[maxn][maxn][maxn][maxn][maxn];
int p[maxn], a[maxn], c[maxn], m[maxn], v[maxn];
int main(int argc, char const *argv[])
{
    int P, A, C, M;
    int n;
    scanf("%d", &n);
    for (int i = 1;i<=n;i++){
        scanf("%d%d%d%d%d", &p[i], &a[i], &c[i], &m[i], &v[i]);
    }
    scanf("%d%d%d%d", &P, &A, &C, &M);
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
    {
        for (int i1 = P; i1 >= p[i];i1--){
            for (int i2 = A; i2 >= a[i];i2--){
                for (int i3 = C; i3 >= c[i];i3--){
                    for (int i4 = M; i4 >= m[i];i4--){
                        if(dp[i1][i2][i3][i4]<dp[i1-p[i]][i2-a[i]][i3-c[i]][i4-m[i]]+v[i]){
                            dp[i1][i2][i3][i4] = dp[i1 - p[i]][i2 - a[i]][i3 - c[i]][i4 - m[i]] + v[i];
                            vis[i][i1][i2][i3][i4] = 1;
                        }
                    }
                }
            }
        }
    }
    vector<int> ans;
    //这个地方要是大于0的
    for (int i = n, i1 = P, i2 = A, i3 = C, i4 = M; i>=0 && i1>=0 && i2>=0 && i3>=0 && i4>=0;i--){
        if(vis[i][i1][i2][i3][i4]){
            ans.push_back(i);
            i1 -= p[i];
            i2 -= a[i];
            i3 -= c[i];
            i4 -= m[i];
        }
    }
    printf("%lu\n", ans.size());
    for (auto it = ans.rbegin(); it != ans.rend();it++){
        printf("%d\n", (*it)-1);
    }  
    return 0;
}
