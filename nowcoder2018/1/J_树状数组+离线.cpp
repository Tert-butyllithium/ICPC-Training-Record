//参考了那个题解。。。似乎直接抄板子的在线主席树是相当玄学的。。。
//倍增之后离线，然后维护一个树状数组
//https://www.cnblogs.com/kkrisen/p/3879517.html

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 10;

int n,q;
int a[maxn],pre[maxn],vis[maxn],last[maxn];
int nxt[maxn],ans[maxn];

struct q{
    int l,r,id;
    bool operator <(const q &other) const{
        return this->l<other.l;
    }
}qs[maxn];

int bit[maxn];
inline int lowbit(int x){return x&-x;}

void update(int x,int y){
    for(int i=x;i<maxn;i+=lowbit(i)){
        bit[i]+=y;
    }
}

int query(int x){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i))
        ans+=bit[i];
    return ans;
}

int query(int x,int y){
    return query(y)-query(x-1);
}

int main(){
    while(scanf("%d%d",&n,&q)!=EOF){
        memset(bit, 0, sizeof(bit));
        memset(vis, 0, sizeof(vis));
        memset(nxt, 0, sizeof(nxt));
        memset(last, -1, sizeof(last));
        
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i+n]=a[i];
        }
        
        for(int i=0;i<q;i++){
            scanf("%d%d",&qs[i].r,&qs[i].l);
            qs[i].r+=n;
            qs[i].id=i;
        }
        
        sort(qs, qs+q);
        n*=2;
        pre[0]=0;
        for(int i=1;i<=n;i++){
            if(!vis[a[i]]){
                vis[a[i]]=1;
                pre[i]=pre[i-1]+1;
            }
            else{
                pre[i]=pre[i-1];
            }
            if(~last[a[i]]){
                nxt[last[a[i]]]=i;
            }
            last[a[i]]=i;
        }
        
        int cur=1;
        for(int i=0;i<q;i++){
            while(cur<qs[i].l){
                if(~nxt[cur])
                    update(nxt[cur], 1);
                cur++;
            }
            ans[qs[i].id]=pre[qs[i].r]-pre[qs[i].l-1]+query(qs[i].l,qs[i].r);
        }
        for(int i=0;i<q;i++)
            printf("%d\n",ans[i]);
    }
}
