//这题的关键就是洗牌相当于翻转三次（3*log(N)），而不是删除再插入（N*log(N)）
//实测rope会tle

#include <iostream>
#include <algorithm>

const int maxn = 1e5 + 10;
const int inf = 0x3f3f3f3f;
int size[maxn], key[maxn], f[maxn], child[maxn][2], lazy[maxn];
int a[maxn];
int sz, root;

bool get(int x){
    return child[f[x]][1] == x;
}

void update(int x){
    size[x] = 1;
    if(child[x][0])
        size[x] += size[child[x][0]];
    if(child[x][1])
        size[x] += size[child[x][1]];
}

void pushdown(int x){
    if(lazy[x]&&x){
        lazy[child[x][0]] ^= 1;
        lazy[child[x][1]] ^= 1;
        std::swap(child[x][0],child[x][1]);
        lazy[x] = 0;
    }
}

void rotate(int x){
    int old = f[x], oldf = f[old], whichx = get(x);
    pushdown(old);
    pushdown(x);
    child[old][whichx] = child[x][whichx ^ 1];
    f[child[old][whichx]] = old;
    child[x][whichx ^ 1] = old;
    f[old] = x;
    f[x] = oldf;
    if(oldf)
        child[oldf][child[oldf][1] == old] = x;
    update(old);
    update(x);
}

void splay(int x,int g){
    for (int fa; (fa = f[x]) != g;rotate(x)){
        if(f[fa]!=g) rotate((get(x)==get(f[fa]))?fa:x);
    }
    if(!g)
        root = x;
}

int find(int x){
    int now = root;
    while(1){
        pushdown(now);
        if(x<=size[child[now][0]])
            now = child[now][0];
        else{
            x -= size[child[now][0]] + 1;
            if(!x)
                return now;
            now = child[now][1];
        }
    }
}

int build(int l,int r,int x){
    if(l>r)
        return 0;
    int mid = (l + r) >> 1;
    int now = ++sz;
    key[now] = a[mid];
    f[now] = x;
    lazy[now] = 0;
    child[now][0] = build(l, mid - 1, now);
    child[now][1] = build(mid + 1, r, now);
    update(now);
    return now;
}

void turn(int l,int r){
    l = find(l);
    r = find(r + 2);
    splay(l, 0);
    splay(r, l);
    pushdown(root);
    lazy[child[child[root][1]][0]] ^= 1;
}

void print(int now){
    pushdown(now);
    if(child[now][0])
        print(child[now][0]);
    if(key[now]!=-inf&&key[now]!=inf)
        printf("%d ", key[now]);
    if(child[now][1])
        print(child[now][1]);
}

int main(int argc, char const *argv[])
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n + 1;i++){
        a[i] = i - 1;
    }
    a[1] = inf;
    a[n + 2] = -inf;
    root = build(1, n + 2, 0);
    while(m--){
        int x, y;
        scanf("%d%d", &x, &y);
        turn(1, x + y - 1);
        turn(1, y);
        turn(y + 1, x + y - 1);
    }
    print(root);
    puts("");
    return 0;
}
