//树上博弈：找规律，对于每一层黑色节点数量奇偶判断
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10007;
vector<int> vec[maxn];
int color[maxn];
int cnt[maxn];
bool vis[maxn];

void dfs(int from,int dep){
    if(vis[from]) return;
    vis[from] = true;
    if(color[from])
        cnt[dep]++;
    for (auto c:vec[from]){
        if(!vis[c]){
            dfs(c, dep + 1);
        }
    }
}

void clear(){
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < maxn;i++){
        vec[i].clear();
    }
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        clear();
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n;i++){
            scanf("%d", &color[i]);
        }
        for (int i = 0; i < n-1;i++){
            int x, y;
            scanf("%d%d", &x, &y);
            vec[x].push_back(y);
            vec[y].push_back(x);
        }
        dfs(1, 0);
        bool flag = true;
        for (int i = 0; i < n;i++){
            if(cnt[i]%2)
                flag = false;
        }
        if(!flag){
            puts("YES");
        }
        else{
            puts("NO");
        }
    }
    return 0;
}
