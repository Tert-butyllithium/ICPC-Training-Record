//https://www.jianshu.com/p/8ce6bcbbeb26

const int maxn=10010;
using namespace std;

/*-----------------------------树链剖分---------------------*/
struct node{
    int v,next;
}edges[maxn<<1];int tot,head[maxn],n;
inline void addedge(int u,int v){//邻接表 记录边
    edges[tot].next=head[u];
    edges[tot].v=v;
    head[u]=tot++;
}
int deep[maxn],size[maxn],top[maxn],fa[maxn],p[maxn],son[maxn],fp[maxn];
//深度，结点数，重链的顶端结点，父亲节点，v与其父亲节点的连边在线段树中的位置(v所在的位置)，重儿子，与p数组相反
int pos;
void Init(){
    memset(son,-1,sizeof(son));
    memset(head,-1,sizeof(head));
    tot=pos=0;
}
void dfs1(int u,int pre,int d){//第一遍dfs求出fa，deep，size，son
    deep[u]=d;
    fa[u]=pre;
    size[u]=1;
    for(int i=head[u];i!=-1;i=edges[i].next){
        int v=edges[i].v;
        if(v!=pre){
            dfs1(v,u,d+1);
            size[u]+=size[v];
            if(son[u]==-1||size[son[u]]<size[v]) son[u]=v;
        }
    }
}
void getpos(int u,int sp){//第二遍dfs求出top和p
    top[u]=sp;
    p[u]=pos++;
    fp[p[u]]=u;
    if(son[u]==-1) return ;
    getpos(son[u],sp);
    for(int i=head[u];i!=-1;i=edges[i].next){
        int v=edges[i].v;
        if(v!=son[u]&&v!=fa[u]) getpos(v,v);
    }
}

//基于点权：
void change(int u,int v,int val){
    int f1=top[u],f2=top[v];
    while(f1!=f2){
        if(deep[f1]<deep[f2]){
            swap(f1,f2);
            swap(u,v);
        }
        add(p[f1],val);
        add(p[u]+1,-val);
        u=fa[f1];f1=top[u];
    }
    //没有（u==v)的特判
    if(deep[u]>deep[v]) swap(u,v);
    add(p[u],val);
    add(p[v]+1,-val);
}

//基于边权：
int find(int u,int v){
    int f1=top[u],f2=top[v];
    int ans=0;
    while(f1!=f2){
        if(dep[f1]<dep[f2]){
            swap(f1,f2);
            swap(u,v);
        }
        ans=max(ans,query(p[f1],p[u],1,pos-1,1));
        u=fa[f1];f1=top[u];
    }
    if(u==v) return ans;//有关于u==v的特判
    if(dep[u]>dep[v]) swap(u,v);
    return max(ans,query(p[son[u]],p[v],1,pos-1,1));
}

