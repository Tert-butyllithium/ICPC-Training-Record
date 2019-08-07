// 维护区间最大值
namespace seg
{
#define lson (rt << 1)
#define rson (rt << 1 | 1)
ll sum[maxn << 2];
ll pre[maxn << 2];
ll suf[maxn << 2];
ll in[maxn << 2];

void pushup(int rt)
{
    sum[rt] = sum[lson] + sum[rson];
    in[rt] = max(max(in[lson], in[rson]), suf[lson] + pre[rson]);
    pre[rt] = max(pre[lson], sum[lson] + pre[rson]);
    suf[rt] = max(suf[rson], sum[rson] + suf[lson]);
}

void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        sum[rt] += val;
        pre[rt] = suf[rt] = in[rt] = max(0ll, sum[rt]);
        return;
    }
    int mid = (l + r) / 2;
    if (mid >= pos)
    {
        update(lson, l, mid, pos, val);
    }
    else
        update(rson, mid + 1, r, pos, val);
    pushup(rt);
}

void clear()
{
    memset(sum, 0, sizeof(sum));
    memset(in, 0, sizeof(in));
    memset(pre, 0, sizeof(pre));
    memset(suf, 0, sizeof(suf));
}
}; // namespace seg
