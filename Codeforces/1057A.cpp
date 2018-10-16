//找一棵树（有根）的最长链
//没有交，不知道对不对
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200007;
int depth[maxn];
vector<int> vecs[maxn];
int ans[maxn];

void dfs(int prev,int cur,int &dep){
    for(auto c:vecs[cur]){
        dep=0;
        dfs(cur, c, dep);
    }
    dep++;
//    depth[cur] =dep;
    if(dep>depth[ans[prev]]){
        ans[prev]=cur;
    }
}


int main(){
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n;i++){
        int fa;
        scanf("%d", &fa);
        vecs[fa].push_back(i);
    }
    // memset(depth, -1, sizeof(depth));
    int d=0;
    dfs(0, 1, d);
    for (int i = 1; i;i=ans[i]){
        if(i){
            printf("%d ", i);
        }
    }
}
