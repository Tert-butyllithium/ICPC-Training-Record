//模拟题, 注意set找一个元素，不管是以什么为序都是O(log N)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn=(1<<20)+7;

struct gift
{
    int k, l, rk;
    gift(int k = 0, int l = 0,int rk=0) : k(k), l(l),rk(rk) {}

    bool operator < (const gift& g) const {
        if(l==g.l){
            return rk < g.rk;
        }
        else{
            return l > g.l;
        }
    }

};

gift gifts[maxn];
set<gift> se;

int main(int argc, char const *argv[])
{
	int round;
    scanf("%d", &round);

    while(round--){
        for (int i = 1; i < maxn;i++){
            gifts[i].k = i;
            gifts[i].l = 0;
            gifts[i].rk = 0;
        }
        se.clear();
        
        int m, n;
        scanf("%d%d", &m, &n);
        int cur = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int t;
            scanf("%d", &t);
            auto f = se.find(gifts[t]);
            if(f==se.end()){
                gifts[t].rk = i;
                if (cur < m)
                {
                    cur++;
                    gifts[t].l++;
                    se.insert(gifts[t]);
                }
                else{
                    ans++;
                    se.erase(se.begin());
                    gifts[t].l = 1;
                    se.insert(gifts[t]);
                }
            }
            else{
                se.erase(f);
                gifts[t].l++;
                se.insert(gifts[t]);
            }
        }
        printf("%d\n", ans);
    }
}
