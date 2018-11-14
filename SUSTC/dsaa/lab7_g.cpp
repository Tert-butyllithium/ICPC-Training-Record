#include <bits/stdc++.h>
using namespace std;
const int maxn=40005;
bool vis[maxn];
int arr[maxn];
int biao[maxn][200];
pair<int,int> pairs[maxn];
int n;

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
            vis[y]=true;
        }
        for(int i=0;i<n;i++){
            if(!vis[i]) continue;
            
        }


    }
    return 0;
}
