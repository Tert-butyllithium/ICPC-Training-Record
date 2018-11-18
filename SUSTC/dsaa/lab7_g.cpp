#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> rbtree;

const int maxn=40005;
bool vis[maxn];
int arr[maxn];
int chart[maxn][202];
pair<int,int> pairs[maxn];
int n, m;
void get_chart(int x, int y)
{
    rbtree pq;
    for (int i = x; i <= n; i += y)
    {
        pq.insert(arr[i]);
    }
    chart[x][y] = *pq.find_by_order(m-1);
    for (int i = x+y; i <= n; i += y)
    {
        pq.erase(arr[i - y]);
        if (pq.size() >= m)
            chart[i][y] = *pq.find_by_order(m-1);
        else
            chart[i][y] = -1;
        // printf("cur: %d %d %d\n", i,y, chart[i][y]);
    }
}


int main(int argc, char const *argv[]){
    int round;
    scanf("%d",&round);
    while(round--){
        memset(vis,0,sizeof(vis));
        memset(chart, 0, sizeof(chart));
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            scanf("%d",&arr[i]);
        }
        for(int i=0;i<n;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            pairs[i] = make_pair(x, y);
            vis[y] = true;
        }
        m = (int)sqrt(n);
        for (int i = 0; i <= m+1; i++)
        {
            if(!vis[i]) continue;
            for (int x = 1; x <= i;x++){
                get_chart(x, i);
            }
        }
//         #ifdef _GLIBCXX_DEBUG_ASSERT
//         for (int i = 1; i <= 5;i++){
//             for (int j = 1; j <= 5;j++){
//                 printf("%d ", chart[i][j]);
//             }
//             puts("");
//         }
// #endif
        for (int i = 0; i < n;i++){
            if(pairs[i].second>m+1){
                puts("-1");
            }
            else{
                int ans = chart[pairs[i].first][pairs[i].second];
                if(ans>0)
                    printf("%d\n", ans);
                else
                    printf("-1\n");
            }
        }
    }
    return 0;
}
