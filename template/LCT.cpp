//  Created by Sengxian on 3/28/16.
//  Copyright (c) 2016年 Sengxian. All rights reserved.
//  BZOJ 1180 LCT
//  retrieved from https://blog.sengxian.com/algorithms/lct
#include <bits/srdc++.h>
using namespace std;
const int maxn = 30000 + 10, INF = 0x3f3f3f3f;

inline int ReadInt() {
    int ch = getchar(), n = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}

struct Splay *null;
struct Splay {
    Splay *fa, *ch[2];
    int val, sum, c;
    bool reversed;
    Splay() {}
    Splay(int val): fa(null), val(val), sum(val), reversed(false) {ch[0] = ch[1] = null;}
    inline void maintain() {if (this != null) this -> sum = ch[0] -> sum + ch[1] -> sum + val;}
    inline void reverse() {if (this != null) reversed ^= 1, swap(ch[0], ch[1]), c = c == -1 ? -1 : 1 - c;}
    inline void pushdown() {if (reversed) reversed = 0, ch[0] -> reverse(), ch[1] -> reverse();}
}pool[maxn];

inline void rotate(Splay* &o, int d) {
    Splay *k = o -> ch[d ^ 1];
    k -> ch[d] -> fa = o, k -> fa = o -> fa, o -> fa = k;
    o -> ch[d ^ 1] = k -> ch[d], k -> ch[d] = o;
    o -> maintain(), k -> maintain();
    o = k;
}

void _splay(Splay* &o) {
    o -> pushdown();
    if (o -> c != -1) {
        Splay *k = o -> ch[o -> c];
        k -> pushdown();
        if (k -> c != -1) {
            _splay(k -> ch[k -> c]);
            if (o -> c == k -> c) rotate(o, o -> c ^ 1); else rotate(o -> ch[o -> c], o -> c);
        }
        rotate(o, o -> c ^ 1);
    }
}

inline bool isRoot(Splay *o) {
    return o -> fa == null || (o -> fa -> ch[0] != o && o -> fa -> ch[1] != o);
}

//将节点 u 旋转到所在 splay 的根节点
void splay(Splay *o) {
    o -> c = -1;
    while (!isRoot(o)) {
        if (o == o -> fa -> ch[0]) o -> fa -> c = 0;
        else o -> fa -> c = 1;
        o = o -> fa;
    }
    _splay(o);
}

Splay* access(Splay *o) {
    Splay *k = null;
    while (o != null) {
        splay(o);
        o -> ch[1] = k;
        o -> maintain();
        k = o;
        o = o -> fa;
    }
    while (k -> ch[0] != null) k = k -> ch[0];
    return k;
}

inline void makeRoot(Splay *x) {
    access(x);
    splay(x);
    x -> reverse();
}

inline void link(int x, int y) {
    makeRoot(pool + x);
    (pool + x) -> fa = pool + y;
}

inline bool connected(int x, int y) {
    return access(pool + x) == access(pool + y);
}

inline int Distance(int x, int y) {
    makeRoot(pool + x), access(pool + y), splay(pool + y);
    return (pool + y) -> sum;
}

int n;
char oper[10];
int main() {
    null = new Splay(), null -> val = null -> sum = 0;
    n = ReadInt();
    for (int i = 0; i < n; ++i) {
        pool[i].fa = null, pool[i].ch[0] = pool[i].ch[1] = null;
        pool[i].sum = pool[i].val = ReadInt();
        pool[i].reversed = false;
    }
    int q = ReadInt();
    while (q--) {
        scanf("%s", oper);
        int x = ReadInt() - 1;
        if (oper[0] == 'b') { //判断联通
            int y = ReadInt() - 1;
            if (connected(x, y)) puts("no");
            else puts("yes"), link(x, y);
        }else if (oper[0] == 'p') { //修改权值
            splay(pool + x);
            (pool + x) -> val = ReadInt();
            (pool + x) -> maintain();
        }else if (oper[0] == 'e') { //求路径和
            int y = ReadInt() - 1;
            if (connected(x, y)) printf("%d\n", Distance(x, y));
            else puts("impossible");
        }
    }
    return 0;
}
