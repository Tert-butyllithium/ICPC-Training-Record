//原题：https://www.nowcoder.com/acm/contest/144/I
//思路：vector也是满足区间加法
#include <bits/stdc++.h>
using namespace std;

const int maxn = (1 << 18) + 21;
const int mod = 998244353;

int T, N, M, ans[maxn], a[maxn], tot;
pair<int, int> seg[maxn];

class cmp{
public:
    bool operator ()(const int &x,const int &y){
        return seg[x].second < seg[y].second;
    }
};

vector<int> vec[maxn<<1];

int round_up(int n){
    int res = 1;
    while(res<n)
        res <<= 1;
    return res;
}

int qi, ql, qr, last;

int query(int x,int l,int r){
    if(r<=ql){
        int res = 0;
        while(!vec[x].empty()&&seg[vec[x].back()].second>=qr){
            if(!ans[vec[x].back()]){
                ++res;
                ans[vec[x].back()=qi;
                last=int(1ll*last*vec[x].back()%mod);
            }
            vec[x].pop_back();
        }
        return res;
    }
    int mid = (l + r) >> 1;
    int res = query(x << 1, l, mid);
    if(ql>mid)
        res += query(x << 1 | 1, mid + 1, r);
    return res;
}

void solve(){
    static int cas = 0;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N;i++){
        scanf("%d%d", &seg[i].first, &seg[i].second);
        a[i] = seg[i].first;
        ans[i] = 0;
    }

    sort(a + 1, a + 1 + N);
    tot = int(unique(a + 1, a + 1 + N) - (a + 1));
    int n = round_up(tot);
    for (int i = 1; i <= N;i++){
        int rk = int(lower_bound(a + 1, a + 1 + tot, seg[i].first) - a);
        vec[n + rk + 1].push_back(i);
    }
    for (int i = 0; i < N;i++){
        sort(vec[i].begin(), vec[i].end(), cmp());
    }
    for (int i = n - 1, i;i--){
        vec[i].resize(vec[i << 1].size() + vec[i << 1 | 1].size());
        merge(vec[i << 1].begin(), vec[i << 1].end(), vec[i << 1 | 1].begin(), vec[i << 1 | 1].end(), vec[i].begin(), cmp());
    }

    last = 0;
    printf("Case #%d: \n", ++cas);
    for (qi = 1; qi <= M;qi++){
        scanf("%d", &qr);
        qr ^= last;
        last = 1;
        ql = int(upper_bound(a + 1, a + 1 + tot, qr) - a - 1);
        int res = ql ? query(1, 1, n) : 0;
        printf("%d\n", res);
        if(!res)
            last = 0;
    }
    for (int i = 1; i <= N;i++){
        printf("%d%c", ans[i], " \n"[i == N]);
    }
    for (int i = 1; i < (n << 1);i++){
        vec[i].clear();
    }
}
