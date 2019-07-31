// hdu 6621
// 强制在线回答：对于每个区间中距离p距离第k近的距离是多少，
// 利用vector的线段树，二分即可求出在区间的元素排在第几（即：order_of_key)
// 然后对每次查询询问答案即可
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 100005;
int n, m;
int a[maxn];
vector<int> v[maxn << 2];
vector<int>::iterator it;

void build(int id, int l, int r)
{
    v[id].clear();
    for (int i = l; i <= r; i++) //把 l 到 r 的元素都存在vector中
        v[id].push_back(a[i]);
    sort(v[id].begin(), v[id].end());
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
}

int query(int id, int L, int R, int l, int r, int h)
{
    if (l <= L && R <= r)
    {
        //当查待询区间[L, R] 完全包含 [l, r] 则返回该区间的结果
        it = upper_bound(v[id].begin(), v[id].end(), h);
        //找到第一个比val大的位置
        return it - v[id].begin();
        //相减得到小于等于val的个数
    }
    int mid = (L + R) >> 1;
    int ans = 0;
    if (l <= mid)
        ans += query(id << 1, L, mid, l, r, h);
    // 有一部分区间在 [L,mid] 之间
    if (mid < r)
        ans += query(id << 1 | 1, mid + 1, R, l, r, h);
    //有一部分在 [mid+1, R] 之间
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int mxv;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        build(1, 1, n);
        int ans = 0;
        mxv = *max_element(a + 1, a + 1 + n);
        while (m--)
        {
            int l, r, p, k;
            scanf("%d%d%d%d", &l, &r, &p, &k);
            l ^= ans, r ^= ans, p ^= ans, k ^= ans;
            int begin = 0, end = mxv;
            while (end >= begin)
            {
                int hf = (begin + end) / 2;
                int t = query(1, 1, n, l, r, p + hf) - query(1, 1, n, l, r, p - hf - 1);
                if (t < k)
                {
                    begin = hf + 1;
                }
                else
                {
                    end = hf - 1;
                }
            }
            printf("%d\n", ans = begin);
        }
    }
    return 0;
}
