//随机化假算法，直接把每个更改加起来，用二维差分数组维护
//每次更新的和等于原值*更新次数，当二者相等时认为植物存活
//显然会有很多组奇怪的数据卡这个算法，但是随机化一下就好了

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 10;

vector<long long> now[maxn];
vector<int> v[maxn], cnt[maxn];
int map[maxn];
int main(int argc, char const *argv[])
{
    int n,m,q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i <= n+1;i++){//这个地方我开始时resize的m+10，一直mle
        v[i].resize(m + 2);
        cnt[i].resize(m + 2);
        now[i].resize(m + 2);
    }
    for (int i = 0; i <= m*n;i++){
        map[i] = i;
    }
    random_shuffle(map + 1, map + n * m + 1);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf("%d", &v[i][j]);
                v[i][j] = map[v[i][j]];
                now[i][j] = 0;
                cnt[i][j] = 0;
            }
        }
    while(q--){
        int x1,x2,y1,y2,val;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &val);
        val = map[val];
        now[x1][y1] += val;
        now[x2+1][y1] -= val;
        now[x1][y2 + 1] -= val;
        now[x2 + 1][y2 + 1] += val;

        cnt[x1][y1]++;
        cnt[x2 + 1][y1]--;
        cnt[x1][y2 + 1]--;
        cnt[x2 + 1][y2 + 1]++;
    }

    int ans = 0;
    for(int i=1;i<=n;i++){
        for (int j = 1; j <= m;j++){
            now[i][j] += now[i - 1][j] + now[i][j - 1] - now[i - 1][j - 1];
            cnt[i][j] += cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1];
            if(now[i][j]!=1LL*cnt[i][j]*v[i][j])
                ans++;
        }
    }
    printf("%d\n", ans);

}
