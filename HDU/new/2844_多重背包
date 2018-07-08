#include <iostream>
#include <cstring>
#define maxn 100008

int val[105];
int nums[105];
int dp[maxn];
int cost[maxn];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)&&n){
       for(int i=0;i<n;i++)
           scanf("%d",&val[i]);
       for(int i=0;i<n;i++)
           scanf("%d",&nums[i]);
       
       memset(dp,0,sizeof(dp));
       
       dp[0]=1;
       for(int i=0;i<n;i++){
            memset(cost,0,sizeof(cost));
            for(int j=val[i];j<=m;j++){
                if(!dp[j]&&(dp[j-val[i]])){
                    if(cost[j-val[i]]<nums[i]){
                        dp[j]=1;
                        //cost[j]指的是到j消耗的i
                        cost[j]=cost[j-val[i]]+1;
                    }
                }
            }
       }
       int tot=0;
       for(int i=1;i<=m;i++){
           if(dp[i])
             tot++;
       }
       printf("%d\n",tot);
    }

}
