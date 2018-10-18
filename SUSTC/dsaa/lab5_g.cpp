//copy from 毕老师
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int MAXN=500010;
  
char s[5][MAXN];
struct Mem{
    int id,pos;
    Mem(int _i=0,int _p=0){
        id=_i,pos=_p;
    }
};
stack<Mem> ms;
int ans[MAXN];
struct Trie{
    int nexts[MAXN][26],fail[MAXN],ends[MAXN];
    queue<int> que;
    vector<int> G[MAXN];
    int dis[MAXN];
    int root,L;
    int newnode(){
        for(int i = 0;i < 26;i++)
            nexts[L][i] = -1;
        ends[L++]=0;
        return L-1;
    }
    void init(){
        L = 0;
        root = newnode();
    }
    void inserts(char buf[]){
        int len = strlen(buf);
        int now = root;
        for(int i = 0;i < len;i++){
            if(nexts[now][buf[i]-'a'] == -1)
                nexts[now][buf[i]-'a'] = newnode();
            now = nexts[now][buf[i]-'a'];
        }
        ends[now]++;
    }
    void build(){
        queue<int>Q;
        fail[root] = root;
        for(int i = 0;i < 26;i++)
            if(nexts[root][i] == -1)
                nexts[root][i] = root;
            else{
                fail[nexts[root][i]] = root;
                Q.push(nexts[root][i]);
            }
        while( !Q.empty() ){
            int now = Q.front();
            Q.pop();
            ends[now]|=ends[fail[now]];
            for(int i = 0;i < 26;i++)
                if(nexts[now][i] == -1)
                    nexts[now][i] = nexts[fail[now]][i];
                else{
                    fail[nexts[now][i]]=nexts[fail[now]][i];
                    Q.push(nexts[now][i]);
                }
        }
  
        for(int u=0;u<L;u++){
            for(int c=0;c<26;c++){
                if(nexts[u][c]!=-1)
                    G[nexts[u][c]].push_back(u);
            }
        }
        memset(dis,-1,sizeof(dis));
        for(int u=0;u<L;u++){
            if(ends[u]){
                que.push(u);
                dis[u]=0;
            }
        }
        while(!que.empty()){
            int u=que.front();
            que.pop();
            for(int i=0;i<G[u].size();i++){
                int v=G[u][i];
                if(dis[v]==-1){
                    dis[v]=dis[u]+1;
                    que.push(v);
                }
            }
        }
    }
  
    void query(char buf[]){
        while(!ms.empty())
            ms.pop();
        int len = strlen(buf);
        int now = root;
        ans[0]=dis[now];
        for(int i = 0;i < len;i++){
            if(buf[i]=='-'){
                if(ms.empty()){
                    ans[i+1]=ans[0];
                    now=root;
                }
                else{
                    ans[i+1]=ans[ms.top().id];
                    now=ms.top().pos;
                    ms.pop();
                }
            }
            else{
                ms.push(Mem(i,now));
                now=nexts[now][buf[i]-'a'];
                ans[i+1]=dis[now];
            }
        }
        for(int i=0;i<=len;i++)
            printf("%d\n",ans[i]);
    }
};
Trie ac;
char q[MAXN];
int main(){
    int n;
    scanf("%d",&n);
    ac.init();
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
        ac.inserts(s[i]);
    }
    ac.build();
    scanf("%s",q);
    ac.query(q);
  
    return 0;
}
 
