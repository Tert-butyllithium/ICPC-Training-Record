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
    chart[x][y] = *pq.find_by_order(m);
    for (int i = x+y; i <= n; i += y)
    {
        pq.erase(pq.find(arr[i - y]));
        if(pq.size()>=m)
            chart[i][y] = *pq.find_by_order(m);
        else
            chart[i][y] = -1;
    }
}

int main(int argc, char const *argv[]){
    int round;
    scanf("%d",&round);
    while(round--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=0;i<n;i++){
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
        for (int i = 0; i < n;i++){
            if(pairs[i].second>m+1){
                puts("-1");
            }
            else{
                printf("%d\n", chart[pairs[i].first][pairs[i].second]);
            }
        }
    }
    return 0;
}
