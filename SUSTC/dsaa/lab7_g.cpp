#pragma GCC target("avx","avx2","sse4","sse4.1","sse4.2","ssse3","sse3","sse2","sse","f16c")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
// #define debug
#include <bits/stdc++.h>
using namespace std;

const int maxn=40005;
bool vis[maxn];
int arr[maxn];
int chart[maxn][202];
pair<int,int> pairs[maxn];

int n, m;
void get_chart(int x, int y)
{
	priority_queue<int,vector<int>,greater<int>> pq;
	deque<int> enum_list;
	for (int i = x; i <= n; i += y)
	{
		enum_list.push_front(i);
	}
	for(auto c:enum_list){
		if(pq.size()<m){
			pq.push(arr[c]);
			if(pq.size()==m){
				chart[c][y] = pq.top();
			}
		}
		else{
			if(arr[c]>pq.top()){
				pq.pop();
				pq.push(arr[c]);
				chart[c][y] = pq.top();
			}
			else{
				chart[c][y] = pq.top();
			}
		}
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
			for (int x = 1; x <= i; x++)
			{
				get_chart(x, i);
            }
        }
	#ifdef debug
		for (int i = 1; i <= 5;i++){
			for (int j = 1; j <= 5;j++){
				printf(" %d ", chart[i][j]);
			}
			puts("");
		}
	#endif

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
